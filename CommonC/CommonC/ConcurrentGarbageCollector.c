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

#include "ConcurrentGarbageCollector.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>
#include <pthread.h>

typedef struct CCConcurrentGarbageCollectorNode {
    struct CCConcurrentGarbageCollectorNode *next;
} CCConcurrentGarbageCollectorNode;

typedef struct {
    CCConcurrentGarbageCollectorNode node;
    uint8_t data[];
} CCConcurrentGarbageCollectorNodeData;

typedef uint64_t CCConcurrentGarbageCollectorEpoch;

typedef struct {
    CCConcurrentGarbageCollectorNode *list;
    uint32_t refCount;
} CCConcurrentGarbageCollectorManagedList;

typedef struct CCConcurrentGarbageCollectorInfo {
    CCAllocatorType allocator;
    _Atomic(CCConcurrentGarbageCollectorManagedList) managed[3];
    _Atomic(CCConcurrentGarbageCollectorEpoch) epoch;
    pthread_key_t key;
} CCConcurrentGarbageCollectorInfo;


CCConcurrentGarbageCollectorNode *CCConcurrentGarbageCollectorCreateNode(CCAllocatorType Allocator, size_t Size, const void *Data)
{
    CCConcurrentGarbageCollectorNode *Node = CCMalloc(Allocator, sizeof(CCConcurrentGarbageCollectorNode) + Size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Node)
    {
        Node->next = NULL;
        if (Data) memcpy(((CCConcurrentGarbageCollectorNodeData*)Node)->data, Data, Size);
    }
    
    return Node;
}

void CCConcurrentGarbageCollectorDestroyNode(CCConcurrentGarbageCollectorNode *Node)
{
    CCAssertLog(Node, "Node must not be null");
    
    CCFree(Node);
}

static inline void *CCConcurrentGarbageCollectorGetNodeData(CCConcurrentGarbageCollectorNode *Node)
{
    return ((CCConcurrentGarbageCollectorNodeData*)Node)->data;
}

typedef struct {
    void *item;
    CCConcurrentGarbageCollectorReclaimer reclaimer;
} CCConcurrentGarbageCollectorEntry;

typedef struct {
    CCConcurrentGarbageCollectorNode *head;
    CCConcurrentGarbageCollectorNode *tail;
    CCConcurrentGarbageCollectorEpoch epoch;
} CCConcurrentGarbageCollectorThread;

static void CCConcurrentGarbageCollectorDrain(CCConcurrentGarbageCollector GC, CCConcurrentGarbageCollectorNode *Node);

static void CCConcurrentGarbageCollectorDestructor(CCConcurrentGarbageCollector GC)
{
    pthread_key_delete(GC->key);
    
    for (int Loop = 0; Loop < 3; Loop++)
    {
        CCConcurrentGarbageCollectorManagedList Managed = atomic_load(&GC->managed[Loop]);
        CCConcurrentGarbageCollectorDrain(GC, Managed.list);
    }
}

CCConcurrentGarbageCollector CCConcurrentGarbageCollectorCreate(CCAllocatorType Allocator)
{
    CCConcurrentGarbageCollector GC = CCMalloc(Allocator, sizeof(CCConcurrentGarbageCollectorInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (GC)
    {
        if (pthread_key_create(&GC->key, (void(*)(void *))CCConcurrentGarbageCollectorDestroyNode))
        {
            CCFree(GC);
            return NULL;
        }
        
        GC->allocator = Allocator;
        atomic_init(&GC->managed[0], (CCConcurrentGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
        atomic_init(&GC->managed[1], (CCConcurrentGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
        atomic_init(&GC->managed[2], (CCConcurrentGarbageCollectorManagedList){ .list = NULL, .refCount = 0 });
        atomic_init(&GC->epoch, 0);
        
        CCMemorySetDestructor(GC, (CCMemoryDestructorCallback)CCConcurrentGarbageCollectorDestructor);
    }
    
    return GC;
}

void CCConcurrentGarbageCollectorDestroy(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    CCFree(GC);
}

void CCConcurrentGarbageCollectorBegin(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    CCConcurrentGarbageCollectorNode *LocalEpoch = pthread_getspecific(GC->key);
    if (CC_UNLIKELY(!LocalEpoch))
    {
        LocalEpoch = CCConcurrentGarbageCollectorCreateNode(GC->allocator, sizeof(CCConcurrentGarbageCollectorThread), &(CCConcurrentGarbageCollectorThread){ .epoch = 0 });
        pthread_setspecific(GC->key, LocalEpoch);
    }
    
    const CCConcurrentGarbageCollectorEpoch PrevEpoch = ((CCConcurrentGarbageCollectorThread*)CCConcurrentGarbageCollectorGetNodeData(LocalEpoch))->epoch;
    CCConcurrentGarbageCollectorEpoch Epoch = atomic_load(&GC->epoch) % 3;
    Epoch = PrevEpoch <= Epoch ? (Epoch + 1) % 3 : PrevEpoch;
    *(CCConcurrentGarbageCollectorThread*)CCConcurrentGarbageCollectorGetNodeData(LocalEpoch) = (CCConcurrentGarbageCollectorThread){ .head = NULL, .tail = NULL, .epoch = Epoch };
    
    CCConcurrentGarbageCollectorManagedList Managed;
    do {
        Managed = atomic_load(&GC->managed[Epoch]);
    } while (!atomic_compare_exchange_weak(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount + 1 })));
}

static void CCConcurrentGarbageCollectorDrain(CCConcurrentGarbageCollector GC, CCConcurrentGarbageCollectorNode *Node)
{
    while (Node)
    {
        ((CCConcurrentGarbageCollectorEntry*)CCConcurrentGarbageCollectorGetNodeData(Node))->reclaimer(((CCConcurrentGarbageCollectorEntry*)CCConcurrentGarbageCollectorGetNodeData(Node))->item);
        
        CCConcurrentGarbageCollectorNode *Temp = Node;
        Node = Node->next;
        CCConcurrentGarbageCollectorDestroyNode(Temp);
    }
    
    atomic_fetch_add(&GC->epoch, 1);
}

void CCConcurrentGarbageCollectorEnd(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    CCConcurrentGarbageCollectorThread *LocalEpoch = CCConcurrentGarbageCollectorGetNodeData(pthread_getspecific(GC->key));
    const CCConcurrentGarbageCollectorEpoch Epoch = LocalEpoch->epoch;
    LocalEpoch->epoch = Epoch <= ((atomic_load(&GC->epoch) + 1) % 3) ? (Epoch + 1) % 3 : Epoch;
    
    CCConcurrentGarbageCollectorManagedList Managed;
    if (LocalEpoch->head)
    {
        do {
            Managed = atomic_load(&GC->managed[Epoch]);
            LocalEpoch->tail->next = Managed.list;
        } while (!atomic_compare_exchange_weak(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = LocalEpoch->head, .refCount = Managed.refCount - 1 })));
    }
    
    else
    {
        do {
            Managed = atomic_load(&GC->managed[Epoch]);
        } while (!atomic_compare_exchange_weak(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 })));
    }
    
    const CCConcurrentGarbageCollectorEpoch StaleEpoch = ((Epoch + 3) - 2) % 3;
    Managed = atomic_load(&GC->managed[StaleEpoch]);
    if ((Managed.refCount == 0) && (atomic_compare_exchange_strong(&GC->managed[StaleEpoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = NULL, .refCount = 0 })))) CCConcurrentGarbageCollectorDrain(GC, Managed.list);
}

void CCConcurrentGarbageCollectorManage(CCConcurrentGarbageCollector GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer)
{
    CCAssertLog(GC, "GC must not be null");
    
    CCConcurrentGarbageCollectorNode *Entry = CCConcurrentGarbageCollectorCreateNode(GC->allocator, sizeof(CCConcurrentGarbageCollectorEntry), &(CCConcurrentGarbageCollectorEntry){ .item = Item, .reclaimer = Reclaimer });
    CCConcurrentGarbageCollectorThread *LocalEpoch = CCConcurrentGarbageCollectorGetNodeData(pthread_getspecific(GC->key)); //Possibly have begin return the *LocalEpoch or epoch and have that passed around
    
    Entry->next = LocalEpoch->head;
    LocalEpoch->head = Entry;
    
    if (!LocalEpoch->tail) LocalEpoch->tail = LocalEpoch->head;
}
