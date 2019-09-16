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
#include "LazyGarbageCollector.h"
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


typedef struct CCLazyGarbageCollectorNode {
    struct CCLazyGarbageCollectorNode *next;
} CCLazyGarbageCollectorNode;

typedef struct {
    CCLazyGarbageCollectorNode node;
    uint8_t data[];
} CCLazyGarbageCollectorNodeData;

typedef struct {
    CCLazyGarbageCollectorNode *list;
    uint32_t refCount;
} CCLazyGarbageCollectorManagedList;

typedef struct {
    _Atomic(CCLazyGarbageCollectorManagedList) managed;
#if CC_GC_USING_PTHREADS
    pthread_key_t key;
#elif CC_GC_USING_STDTHREADS
    tss_t key;
#endif
} CCLazyGarbageCollectorInternal;

static void *CCLazyGarbageCollectorConstructor(CCAllocatorType Allocator);
static void CCLazyGarbageCollectorDestructor(CCLazyGarbageCollectorInternal *Internal);
static void CCLazyGarbageCollectorBegin(CCLazyGarbageCollectorInternal *Internal, CCAllocatorType Allocator);
static void CCLazyGarbageCollectorEnd(CCLazyGarbageCollectorInternal *Internal, CCAllocatorType Allocator);
static void CCLazyGarbageCollectorManage(CCLazyGarbageCollectorInternal *Internal, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer, CCAllocatorType Allocator);


const CCConcurrentGarbageCollectorInterface CCLazyGarbageCollectorInterface = {
    .create = CCLazyGarbageCollectorConstructor,
    .destroy = (CCConcurrentGarbageCollectorDestructorCallback)CCLazyGarbageCollectorDestructor,
    .begin = (CCConcurrentGarbageCollectorBeginCallback)CCLazyGarbageCollectorBegin,
    .end = (CCConcurrentGarbageCollectorEndCallback)CCLazyGarbageCollectorEnd,
    .manage = (CCConcurrentGarbageCollectorManageCallback)CCLazyGarbageCollectorManage,
};


const CCConcurrentGarbageCollectorInterface * const CCLazyGarbageCollector = &CCLazyGarbageCollectorInterface;


CCLazyGarbageCollectorNode *CCLazyGarbageCollectorCreateNode(CCAllocatorType Allocator, size_t Size, const void *Data)
{
    CCLazyGarbageCollectorNode *Node = CCMalloc(Allocator, sizeof(CCLazyGarbageCollectorNode) + Size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Node)
    {
        Node->next = NULL;
        if (Data) memcpy(((CCLazyGarbageCollectorNodeData*)Node)->data, Data, Size);
    }
    
    return Node;
}

void CCLazyGarbageCollectorDestroyNode(CCLazyGarbageCollectorNode *Node)
{
    CCAssertLog(Node, "Node must not be null");
    
    CCFree(Node);
}

static inline void *CCLazyGarbageCollectorGetNodeData(CCLazyGarbageCollectorNode *Node)
{
    return ((CCLazyGarbageCollectorNodeData*)Node)->data;
}

typedef struct {
    void *item;
    CCConcurrentGarbageCollectorReclaimer reclaimer;
} CCLazyGarbageCollectorEntry;

typedef struct {
    CCLazyGarbageCollectorNode *head;
    CCLazyGarbageCollectorNode *tail;
} CCLazyGarbageCollectorThread;

static void CCLazyGarbageCollectorDrain(CCLazyGarbageCollectorInternal *GC, CCLazyGarbageCollectorNode *Node);

static void *CCLazyGarbageCollectorConstructor(CCAllocatorType Allocator)
{
    CCLazyGarbageCollectorInternal *GC = CCMalloc(Allocator, sizeof(CCLazyGarbageCollectorInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
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
        
        atomic_init(&GC->managed, (CCLazyGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
    }
    
    return GC;
}

void CCLazyGarbageCollectorDestructor(CCLazyGarbageCollectorInternal *GC)
{
#if CC_GC_USING_PTHREADS
    pthread_key_delete(GC->key);
#elif CC_GC_USING_STDTHREADS
    tss_delete(GC->key);
#endif
    
    CCLazyGarbageCollectorManagedList Managed = atomic_load_explicit(&GC->managed, memory_order_relaxed);
    CCLazyGarbageCollectorDrain(GC, Managed.list);
    
    CCFree(GC);
}

void CCLazyGarbageCollectorBegin(CCLazyGarbageCollectorInternal *GC, CCAllocatorType Allocator)
{
#if CC_GC_USING_PTHREADS
    CCLazyGarbageCollectorThread *Local = pthread_getspecific(GC->key);
#elif CC_GC_USING_STDTHREADS
    CCLazyGarbageCollectorThread *Local = tss_get(GC->key);
#endif
    
    if (CC_UNLIKELY(!Local))
    {
        CC_SAFE_Malloc(Local, sizeof(CCLazyGarbageCollectorThread),
                       CC_LOG_ERROR("Failed to create thread local state.");
                       return;
                       );
        
#if CC_GC_USING_PTHREADS
        pthread_setspecific(GC->key, Local);
#elif CC_GC_USING_STDTHREADS
        tss_set(GC->key, Local);
#endif
    }
    
    *Local = (CCLazyGarbageCollectorThread){ .head = NULL, .tail = NULL };
    
    CCLazyGarbageCollectorManagedList Managed;
    do {
        Managed = atomic_load_explicit(&GC->managed, memory_order_relaxed);
    } while (!atomic_compare_exchange_weak_explicit(&GC->managed, &Managed, ((CCLazyGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount + 1 }), memory_order_relaxed, memory_order_relaxed));
}

static void CCLazyGarbageCollectorDrain(CCLazyGarbageCollectorInternal *GC, CCLazyGarbageCollectorNode *Node)
{
    while (Node)
    {
        ((CCLazyGarbageCollectorEntry*)CCLazyGarbageCollectorGetNodeData(Node))->reclaimer(((CCLazyGarbageCollectorEntry*)CCLazyGarbageCollectorGetNodeData(Node))->item);
        
        CCLazyGarbageCollectorNode *Temp = Node;
        Node = Node->next;
        CCLazyGarbageCollectorDestroyNode(Temp);
    }
}

void CCLazyGarbageCollectorEnd(CCLazyGarbageCollectorInternal *GC, CCAllocatorType Allocator)
{
#if CC_GC_USING_PTHREADS
    CCLazyGarbageCollectorThread *Local = pthread_getspecific(GC->key);
#elif CC_GC_USING_STDTHREADS
    CCLazyGarbageCollectorThread *Local = tss_get(GC->key);
#endif
    
    CCLazyGarbageCollectorManagedList Managed;
    if (Local->head)
    {
        do {
            Managed = atomic_load_explicit(&GC->managed, memory_order_relaxed);
            Local->tail->next = Managed.list;
        } while (!atomic_compare_exchange_weak_explicit(&GC->managed, &Managed, ((CCLazyGarbageCollectorManagedList){ .list = Managed.refCount == 1 ? NULL : Local->head, .refCount = Managed.refCount - 1 }), memory_order_release, memory_order_relaxed));
        
        if (Managed.refCount == 1) CCLazyGarbageCollectorDrain(GC, Local->head);
    }
    
    else
    {
        do {
            Managed = atomic_load_explicit(&GC->managed, memory_order_relaxed);
        } while (!atomic_compare_exchange_weak_explicit(&GC->managed, &Managed, ((CCLazyGarbageCollectorManagedList){ .list = Managed.refCount == 1 ? NULL : Managed.list, .refCount = Managed.refCount - 1 }), memory_order_relaxed, memory_order_relaxed));
        
        if ((Managed.refCount == 1) && (Managed.list)) CCLazyGarbageCollectorDrain(GC, Managed.list);
    }    
}

void CCLazyGarbageCollectorManage(CCLazyGarbageCollectorInternal *GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer, CCAllocatorType Allocator)
{
    CCLazyGarbageCollectorNode *Entry = CCLazyGarbageCollectorCreateNode(Allocator, sizeof(CCLazyGarbageCollectorEntry), &(CCLazyGarbageCollectorEntry){ .item = Item, .reclaimer = Reclaimer });
#if CC_GC_USING_PTHREADS
    CCLazyGarbageCollectorThread *Local = pthread_getspecific(GC->key);
#elif CC_GC_USING_STDTHREADS
    CCLazyGarbageCollectorThread *Local = tss_get(GC->key);
#endif
    
    Entry->next = Local->head;
    Local->head = Entry;
    
    if (!Local->tail) Local->tail = Local->head;
}
