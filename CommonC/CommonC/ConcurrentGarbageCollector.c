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
    }
    
    return GC;
}

void CCConcurrentGarbageCollectorDestroy(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    //should we guarantee GC is safe to destroy?
    pthread_key_delete(GC->key);
    CCFree(GC);
}

void CCConcurrentGarbageCollectorBegin(CCConcurrentGarbageCollector GC)
{
    CCConcurrentGarbageCollectorNode *LocalEpoch = pthread_getspecific(GC->key);
    if (CC_UNLIKELY(!LocalEpoch))
    {
        LocalEpoch = CCConcurrentGarbageCollectorCreateNode(GC->allocator, sizeof(CCConcurrentGarbageCollectorEpoch), NULL);
        pthread_setspecific(GC->key, LocalEpoch);
    }
    
    const CCConcurrentGarbageCollectorEpoch Epoch = atomic_load(&GC->epoch) % 3;
    *(CCConcurrentGarbageCollectorEpoch*)CCConcurrentGarbageCollectorGetNodeData(LocalEpoch) = Epoch;
    
    CCConcurrentGarbageCollectorManagedList Managed;
    do {
        Managed = atomic_load(&GC->managed[Epoch]);
    } while (!atomic_compare_exchange_weak(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount + 1 })));
}

static void CCConcurrentGarbageCollectorDrain(CCConcurrentGarbageCollector GC, CCConcurrentGarbageCollectorNode *Node)
{
    for ( ; Node; Node = Node->next)
    {
        ((CCConcurrentGarbageCollectorEntry*)CCConcurrentGarbageCollectorGetNodeData(Node))->reclaimer(((CCConcurrentGarbageCollectorEntry*)CCConcurrentGarbageCollectorGetNodeData(Node))->item);
    }
}

void CCConcurrentGarbageCollectorEnd(CCConcurrentGarbageCollector GC)
{
    CCConcurrentGarbageCollectorNode *LocalEpoch = pthread_getspecific(GC->key);
    
    const CCConcurrentGarbageCollectorEpoch Epoch = *(CCConcurrentGarbageCollectorEpoch*)CCConcurrentGarbageCollectorGetNodeData(LocalEpoch);
    CCConcurrentGarbageCollectorManagedList Managed;
    do {
        Managed = atomic_load(&GC->managed[Epoch]);
    } while (!atomic_compare_exchange_weak(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = Managed.list, .refCount = Managed.refCount - 1 })));
    
    Managed = atomic_load(&GC->managed[Epoch]);
    if ((Managed.refCount == 0) && (Managed.list) && (atomic_compare_exchange_strong(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = NULL, .refCount = 0 })))) CCConcurrentGarbageCollectorDrain(GC, Managed.list); //could be combined with the above
}

void CCConcurrentGarbageCollectorManage(CCConcurrentGarbageCollector GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer)
{
    CCConcurrentGarbageCollectorNode *Entry = CCConcurrentGarbageCollectorCreateNode(GC->allocator, sizeof(CCConcurrentGarbageCollectorEntry), &(CCConcurrentGarbageCollectorEntry){ .item = Item, .reclaimer = Reclaimer });
    CCConcurrentGarbageCollectorNode *LocalEpoch = pthread_getspecific(GC->key); //Possibly have begin return the *LocalEpoch or epoch and have that passed around
    const CCConcurrentGarbageCollectorEpoch Epoch = *(CCConcurrentGarbageCollectorEpoch*)CCConcurrentGarbageCollectorGetNodeData(LocalEpoch);
    
    CCConcurrentGarbageCollectorManagedList Managed;
    do {
        Managed = atomic_load(&GC->managed[Epoch]);
        Entry->next = Managed.list;
    } while (!atomic_compare_exchange_weak(&GC->managed[Epoch], &Managed, ((CCConcurrentGarbageCollectorManagedList){ .list = Entry, .refCount = Managed.refCount }))); //could possibly do this in CCConcurrentGarbageCollectorEnd, and instead have a local reference here (in CCConcurrentGarbageCollectorThread).
}
