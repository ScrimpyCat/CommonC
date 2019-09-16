/*
 *  Copyright (c) 2016, Stefan Johnson
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this list
 *     of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice, this
 *     list of conditions and the following disclaimer in the documentation and/or other
 *     materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define CC_QUICK_COMPILE
#include "EpochGarbageCollector.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include "Logging.h"
#include "Platform.h"
#include <stdatomic.h>
#include <string.h>

#if defined(__has_include)

#if __has_include(<threads.h>)
#define CC_GC_USING_STDTHREADS 1
#include <threads.h>
#elif CC_PLATFORM_POSIX_COMPLIANT
#define CC_GC_USING_PTHREADS 1
#include <pthread.h>
#else
#error No thread support
#endif

#elif CC_PLATFORM_POSIX_COMPLIANT
#define CC_GC_USING_PTHREADS 1
#include <pthread.h>
#else
#define CC_GC_USING_STDTHREADS 1
#include <threads.h>
#endif


typedef struct CCEpochGarbageCollectorNode {
    struct CCEpochGarbageCollectorNode *next;
} CCEpochGarbageCollectorNode;

typedef struct {
    CCEpochGarbageCollectorNode node;
    uint8_t data[];
} CCEpochGarbageCollectorNodeData;

typedef uint64_t CCEpochGarbageCollectorEpoch;

typedef struct {
    CCEpochGarbageCollectorNode *list;
    uint32_t refCount;
} CCEpochGarbageCollectorManagedList;

typedef struct {
    _Atomic(CCEpochGarbageCollectorManagedList) managed[3];
    _Atomic(CCEpochGarbageCollectorEpoch) epoch;
#if CC_GC_USING_PTHREADS
    pthread_key_t key;
#elif CC_GC_USING_STDTHREADS
    tss_t key;
#endif
} CCEpochGarbageCollectorInternal;

static void *CCEpochGarbageCollectorConstructor(CCAllocatorType Allocator);
static void CCEpochGarbageCollectorDestructor(CCEpochGarbageCollectorInternal *Internal);
static void CCEpochGarbageCollectorBegin(CCEpochGarbageCollectorInternal *Internal, CCAllocatorType Allocator);
static void CCEpochGarbageCollectorEnd(CCEpochGarbageCollectorInternal *Internal, CCAllocatorType Allocator);
static void CCEpochGarbageCollectorManage(CCEpochGarbageCollectorInternal *Internal, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer, CCAllocatorType Allocator);


const CCConcurrentGarbageCollectorInterface CCEpochGarbageCollectorInterface = {
    .create = CCEpochGarbageCollectorConstructor,
    .destroy = (CCConcurrentGarbageCollectorDestructorCallback)CCEpochGarbageCollectorDestructor,
    .begin = (CCConcurrentGarbageCollectorBeginCallback)CCEpochGarbageCollectorBegin,
    .end = (CCConcurrentGarbageCollectorEndCallback)CCEpochGarbageCollectorEnd,
    .manage = (CCConcurrentGarbageCollectorManageCallback)CCEpochGarbageCollectorManage,
};


const CCConcurrentGarbageCollectorInterface * const CCEpochGarbageCollector = &CCEpochGarbageCollectorInterface;


CCEpochGarbageCollectorNode *CCEpochGarbageCollectorCreateNode(CCAllocatorType Allocator, size_t Size, const void *Data)
{
    CCEpochGarbageCollectorNode *Node = CCMalloc(Allocator, sizeof(CCEpochGarbageCollectorNode) + Size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Node)
    {
        Node->next = NULL;
        if (Data) memcpy(((CCEpochGarbageCollectorNodeData*)Node)->data, Data, Size);
    }
    
    return Node;
}

void CCEpochGarbageCollectorDestroyNode(CCEpochGarbageCollectorNode *Node)
{
    CCAssertLog(Node, "Node must not be null");
    
    CCFree(Node);
}

static inline void *CCEpochGarbageCollectorGetNodeData(CCEpochGarbageCollectorNode *Node)
{
    return ((CCEpochGarbageCollectorNodeData*)Node)->data;
}

typedef struct {
    void *item;
    CCConcurrentGarbageCollectorReclaimer reclaimer;
} CCEpochGarbageCollectorEntry;

typedef struct {
    CCEpochGarbageCollectorNode *head;
    CCEpochGarbageCollectorNode *tail;
    CCEpochGarbageCollectorEpoch epoch;
} CCEpochGarbageCollectorThread;

static void CCEpochGarbageCollectorDrain(CCEpochGarbageCollectorInternal *GC, CCEpochGarbageCollectorNode *Node, CCEpochGarbageCollectorEpoch Epoch);

static void *CCEpochGarbageCollectorConstructor(CCAllocatorType Allocator)
{
    CCEpochGarbageCollectorInternal *GC = CCMalloc(Allocator, sizeof(CCEpochGarbageCollectorInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (GC)
    {
#if CC_GC_USING_PTHREADS
        if (pthread_key_create(&GC->key, CCFree))
#elif CC_GC_USING_STDTHREADS
        if (tss_create(&GC->key, CCFree) != thrd_success)
#endif
        {
            CCFree(GC);
            return NULL;
        }
        
        atomic_init(&GC->managed[0], (CCEpochGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
        atomic_init(&GC->managed[1], (CCEpochGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
        atomic_init(&GC->managed[2], (CCEpochGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
        atomic_init(&GC->epoch, 0);        
    }
    
    return GC;
}

void CCEpochGarbageCollectorDestructor(CCEpochGarbageCollectorInternal *GC)
{
#if CC_GC_USING_PTHREADS
    pthread_key_delete(GC->key);
#elif CC_GC_USING_STDTHREADS
    tss_delete(GC->key);
#endif
    
    for (int Loop = 0; Loop < 3; Loop++)
    {
        CCEpochGarbageCollectorManagedList Managed = atomic_load_explicit(&GC->managed[Loop], memory_order_relaxed);
        CCEpochGarbageCollectorDrain(GC, Managed.list, atomic_load_explicit(&GC->epoch, memory_order_relaxed));
    }
    
    CCFree(GC);
}

void CCEpochGarbageCollectorBegin(CCEpochGarbageCollectorInternal *GC, CCAllocatorType Allocator)
{
#if CC_GC_USING_PTHREADS
    CCEpochGarbageCollectorThread *LocalEpoch = pthread_getspecific(GC->key);
#elif CC_GC_USING_STDTHREADS
    CCEpochGarbageCollectorThread *LocalEpoch = tss_get(GC->key);
#endif
    
    if (CC_UNLIKELY(!LocalEpoch))
    {
        CC_SAFE_Malloc(LocalEpoch, sizeof(CCEpochGarbageCollectorThread),
                       CC_LOG_ERROR("Failed to create thread local state.");
                       return;
                       );
        
        LocalEpoch->epoch = 0;
#if CC_GC_USING_PTHREADS
        pthread_setspecific(GC->key, LocalEpoch);
#elif CC_GC_USING_STDTHREADS
        tss_set(GC->key, LocalEpoch);
#endif
    }
    
    for (CCEpochGarbageCollectorEpoch GlobalEpoch = atomic_load_explicit(&GC->epoch, memory_order_relaxed); ; )
    {
        CCEpochGarbageCollectorEpoch Epoch = (GlobalEpoch + 2) % 3;
        *LocalEpoch = (CCEpochGarbageCollectorThread){ .head = NULL, .tail = NULL, .epoch = Epoch };
        
        CCEpochGarbageCollectorManagedList Managed;
        do {
            Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
        } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount + 1 }), memory_order_relaxed, memory_order_relaxed));
        
        CCEpochGarbageCollectorEpoch NewGlobalEpoch = atomic_load_explicit(&GC->epoch, memory_order_relaxed);
        if (GlobalEpoch == NewGlobalEpoch) break;
        
        GlobalEpoch = NewGlobalEpoch;
        
        if (!atomic_compare_exchange_strong_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 }), memory_order_relaxed, memory_order_relaxed))
        {
            do {
                Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
            } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 }), memory_order_relaxed, memory_order_relaxed));
        }
    }
}

static void CCEpochGarbageCollectorDrain(CCEpochGarbageCollectorInternal *GC, CCEpochGarbageCollectorNode *Node, CCEpochGarbageCollectorEpoch Epoch)
{
    while (Node)
    {
        ((CCEpochGarbageCollectorEntry*)CCEpochGarbageCollectorGetNodeData(Node))->reclaimer(((CCEpochGarbageCollectorEntry*)CCEpochGarbageCollectorGetNodeData(Node))->item);
        
        CCEpochGarbageCollectorNode *Temp = Node;
        Node = Node->next;
        CCEpochGarbageCollectorDestroyNode(Temp);
    }
    
    atomic_compare_exchange_strong_explicit(&GC->epoch, &Epoch, Epoch + 1, memory_order_relaxed, memory_order_relaxed);
}

void CCEpochGarbageCollectorEnd(CCEpochGarbageCollectorInternal *GC, CCAllocatorType Allocator)
{
#if CC_GC_USING_PTHREADS
    CCEpochGarbageCollectorThread *LocalEpoch = pthread_getspecific(GC->key);
#elif CC_GC_USING_STDTHREADS
    CCEpochGarbageCollectorThread *LocalEpoch = tss_get(GC->key);
#endif
    const CCEpochGarbageCollectorEpoch GlobalEpoch = atomic_load_explicit(&GC->epoch, memory_order_relaxed);
    const CCEpochGarbageCollectorEpoch Epoch = LocalEpoch->epoch;
    
    CCEpochGarbageCollectorManagedList Managed;
    if (LocalEpoch->head)
    {
        do {
            Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
            LocalEpoch->tail->next = Managed.list;
        } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = LocalEpoch->head, .refCount = Managed.refCount - 1 }), memory_order_release, memory_order_relaxed));
    }
    
    else
    {
        do {
            Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
        } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 }), memory_order_relaxed, memory_order_relaxed));
    }
    
    const CCEpochGarbageCollectorEpoch StaleEpoch = GlobalEpoch % 3;
    Managed = atomic_load_explicit(&GC->managed[StaleEpoch], memory_order_relaxed);
    if (Managed.refCount == 0)
    {
        CCEpochGarbageCollectorManagedList NextManaged = atomic_load_explicit(&GC->managed[(StaleEpoch + 1) % 3], memory_order_relaxed);
        if ((NextManaged.refCount == 0) && (atomic_compare_exchange_strong_explicit(&GC->managed[StaleEpoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = NULL, .refCount = 0 }), memory_order_acquire, memory_order_relaxed)))
        {
            if (GlobalEpoch == atomic_load_explicit(&GC->epoch, memory_order_relaxed)) CCEpochGarbageCollectorDrain(GC, Managed.list, GlobalEpoch);
            else if (Managed.list)
            {
                CCEpochGarbageCollectorNode *List = Managed.list, *Tail = Managed.list;
                while (Tail->next) Tail = Tail->next;
                
                for (CCEpochGarbageCollectorEpoch GlobalEpoch = atomic_load_explicit(&GC->epoch, memory_order_relaxed); ; )
                {
                    CCEpochGarbageCollectorEpoch Epoch = (GlobalEpoch + 2) % 3;
                    CCEpochGarbageCollectorManagedList Managed;
                    do {
                        Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
                    } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount + 1 }), memory_order_relaxed, memory_order_relaxed));
                    
                    CCEpochGarbageCollectorEpoch NewGlobalEpoch = atomic_load_explicit(&GC->epoch, memory_order_relaxed);
                    if (GlobalEpoch == NewGlobalEpoch)
                    {
                        do {
                            Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
                            Tail->next = Managed.list;
                        } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = List, .refCount = Managed.refCount - 1 }), memory_order_release, memory_order_relaxed));
                        
                        break;
                    }
                    
                    GlobalEpoch = NewGlobalEpoch;
                    
                    if (!atomic_compare_exchange_strong_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 }), memory_order_relaxed, memory_order_relaxed))
                    {
                        do {
                            Managed = atomic_load_explicit(&GC->managed[Epoch], memory_order_relaxed);
                        } while (!atomic_compare_exchange_weak_explicit(&GC->managed[Epoch], &Managed, ((CCEpochGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 }), memory_order_relaxed, memory_order_relaxed));
                    }
                }
            }
        }
    }
}

void CCEpochGarbageCollectorManage(CCEpochGarbageCollectorInternal *GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer, CCAllocatorType Allocator)
{
    CCEpochGarbageCollectorNode *Entry = CCEpochGarbageCollectorCreateNode(Allocator, sizeof(CCEpochGarbageCollectorEntry), &(CCEpochGarbageCollectorEntry){ .item = Item, .reclaimer = Reclaimer });
#if CC_GC_USING_PTHREADS
    CCEpochGarbageCollectorThread *LocalEpoch = pthread_getspecific(GC->key);
#elif CC_GC_USING_STDTHREADS
    CCEpochGarbageCollectorThread *LocalEpoch = tss_get(GC->key);
#endif
    
    Entry->next = LocalEpoch->head;
    LocalEpoch->head = Entry;
    
    if (!LocalEpoch->tail) LocalEpoch->tail = LocalEpoch->head;
}
