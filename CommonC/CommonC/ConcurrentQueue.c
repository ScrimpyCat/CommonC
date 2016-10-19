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

#include "ConcurrentQueue.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>

CCConcurrentQueueNode *CCConcurrentQueueCreateNode(CCAllocatorType Allocator, size_t Size, const void *Data)
{
    CCConcurrentQueueNode *Node = CCMalloc(Allocator, sizeof(CCConcurrentQueueNode) + Size, NULL, CC_DEFAULT_ERROR_CALLBACK);

    if (Node)
    {
        atomic_init(&Node->next, (CCConcurrentQueuePointer){ .node = NULL, .tag = 0 });
        atomic_init(&Node->prev, (CCConcurrentQueuePointer){ .node = NULL, .tag = 0 });
        if (Data) memcpy(((CCConcurrentQueueNodeData*)Node)->data, Data, Size);
    }

    return Node;
}

void CCConcurrentQueueDestroyNode(CCConcurrentQueueNode *Node)
{
    CCAssertLog(Node, "Node must not be null");
    
    CCFree(Node);
}

static inline CCConcurrentQueueNode *CCConcurrentQueueAcquireNode(CCConcurrentQueue Queue, CCConcurrentQueueNode *Node)
{
    return CCRetain(Node);
}

static inline CCConcurrentQueueNode *CCConcurrentQueueReleaseNode(CCConcurrentQueue Queue, CCConcurrentQueueNode *Node)
{
    CCFree(Node);
    return Node;
}

CCConcurrentQueue CCConcurrentQueueCreate(CCAllocatorType Allocator)
{
    CCConcurrentQueue Queue = CCMalloc(Allocator, sizeof(CCConcurrentQueueInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Queue)
    {
        CCConcurrentQueueNode *Dummy = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
        atomic_init(&Queue->head, (CCConcurrentQueuePointer){ .node = Dummy, .tag = 0 });
        atomic_init(&Queue->tail, (CCConcurrentQueuePointer){ .node = Dummy, .tag = 0 });
    }
    
    return Queue;
}

void CCConcurrentQueueDestroy(CCConcurrentQueue Queue)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    for (CCConcurrentQueueNode *N; (N = CCConcurrentQueuePop(Queue)); )
    {
        CCConcurrentQueueDestroyNode(N);
    }
    
    CCConcurrentQueuePointer Head = atomic_load(&Queue->head);
    CCConcurrentQueueReleaseNode(Queue, Head.node);
    
    CC_SAFE_Free(Queue);
}

static inline _Bool CCConcurrentQueuePointerIsEqual(CCConcurrentQueuePointer a, CCConcurrentQueuePointer b)
{
    return (a.node == b.node) && (a.tag == b.tag);
}

void CCConcurrentQueuePush(CCConcurrentQueue Queue, CCConcurrentQueueNode *Node)
{
    CCAssertLog(Queue, "Queue must not be null");
    CCAssertLog(Node, "Node must not be null");
    
    CCConcurrentQueueAcquireNode(Queue, Node);
    
    for ( ; ; )
    {
        CCConcurrentQueuePointer Tail = atomic_load(&Queue->tail);
        
        atomic_store(&Node->next, ((CCConcurrentQueuePointer){ .node = Tail.node, .tag = Tail.tag + 1 }));
        if (atomic_compare_exchange_weak(&Queue->tail, &Tail, ((CCConcurrentQueuePointer){ .node = Node, .tag = Tail.tag + 1 })))
        {
            atomic_store(&Tail.node->prev, ((CCConcurrentQueuePointer){ .node = Node, .tag = Tail.tag }));
            break;
        }
    }
}

static void CCConcurrentQueueFixList(CCConcurrentQueue Queue, CCConcurrentQueuePointer Tail, CCConcurrentQueuePointer Head)
{
    for (CCConcurrentQueuePointer CurNode = Tail; CCConcurrentQueuePointerIsEqual(Head, atomic_load(&Queue->head)) && !CCConcurrentQueuePointerIsEqual(CurNode, Head); )
    {
        CCConcurrentQueuePointer CurNodeNext = atomic_load(&CurNode.node->next);
        atomic_store(&CurNodeNext.node->prev, ((CCConcurrentQueuePointer){ .node = CurNode.node, .tag = CurNode.tag - 1 }));
        
        CurNode = (CCConcurrentQueuePointer){ .node = CurNodeNext.node, .tag = CurNode.tag - 1 };
    }
}

CCConcurrentQueueNode *CCConcurrentQueuePop(CCConcurrentQueue Queue)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    for ( ; ; )
    {
        CCConcurrentQueuePointer Head = atomic_load(&Queue->head), Tail = atomic_load(&Queue->tail);
        CCConcurrentQueuePointer FirstNodePrev = atomic_load(&Head.node->prev);
        
        if (CCConcurrentQueuePointerIsEqual(Head, atomic_load(&Queue->head)))
        {
            if ((FirstNodePrev.node) && (!CCConcurrentQueuePointerIsEqual(Tail, Head)))
            {
                if (FirstNodePrev.tag != Head.tag)
                {
                    CCConcurrentQueueFixList(Queue, Tail, Head);
                    continue;
                }
                
                else if (atomic_compare_exchange_weak(&Queue->head, &Head, ((CCConcurrentQueuePointer){ .node = FirstNodePrev.node, .tag = Head.tag + 1 })))
                {
                    CCConcurrentQueueReleaseNode(Queue, Head.node);
                    return FirstNodePrev.node;
                }
            }
            
            else break;
        }
    }
    
    return NULL;
}
