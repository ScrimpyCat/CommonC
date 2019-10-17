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
#include "Queue.h"
#include "MemoryAllocation.h"
#include "Assertion.h"

typedef struct CCQueueInfo {
    CCQueueNode *head;
    CCQueueNode *tail;
    size_t count;
} CCQueueInfo;

static void CCQueueDestructor(CCQueue Queue)
{
    if (Queue->head) CCLinkedListDestroy(Queue->head);
}

CCQueue CCQueueCreate(CCAllocatorType Allocator)
{
    CCQueue Queue = CCMalloc(Allocator, sizeof(CCQueueInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Queue)
    {
        Queue->head = NULL;
        Queue->tail = NULL;
        Queue->count = 0;
        
        CCMemorySetDestructor(Queue, (CCMemoryDestructorCallback)CCQueueDestructor);
    }
    
    return Queue;
}

void CCQueueDestroy(CCQueue Queue)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    CC_SAFE_Free(Queue);
}

void CCQueuePush(CCQueue Queue, CCQueueNode *Node)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    Queue->head = Queue->head ? CCLinkedListInsertBefore(Queue->head, Node) : Node;
    
    if (!Queue->tail) Queue->tail = Queue->head;
    
    Queue->count++;
}

CCQueueNode *CCQueuePop(CCQueue Queue)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    CCQueueNode *Tail = Queue->tail;
    if (Tail)
    {
        Queue->tail = CCLinkedListEnumeratePrevious(Queue->tail);
        if (!Queue->tail) Queue->head = NULL;
        
        CCLinkedListRemoveNode(Tail);
        
        Queue->count--;
    }
    
    return Tail;
}

CCQueueNode *CCQueuePeek(CCQueue Queue)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    return Queue->tail;
}

size_t CCQueueGetCount(CCQueue Queue)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    return Queue->count;
}

static void *CCQueueEnumerableHandler(CCEnumerator *Enumerator, CCEnumerableAction Action)
{
    switch (Action)
    {
        case CCEnumerableActionHead:
            Enumerator->state.internal.ptr = (void*)Enumerator->state.internal.extra[0];
            break;
            
        case CCEnumerableActionTail:
            Enumerator->state.internal.ptr = (void*)Enumerator->state.internal.extra[1];
            break;
            
        case CCEnumerableActionNext:
            Enumerator->state.internal.ptr = CCLinkedListEnumeratePrevious(Enumerator->state.internal.ptr);
            break;
            
        case CCEnumerableActionPrevious:
            Enumerator->state.internal.ptr = CCLinkedListEnumerateNext(Enumerator->state.internal.ptr);
            break;
            
        default:
            break;
    }
    
    return Enumerator->state.internal.ptr ? CCQueueGetNodeData(Enumerator->state.internal.ptr) : NULL;
}

void CCQueueGetEnumerable(CCQueue Queue, CCEnumerable *Enumerable)
{
    CCAssertLog(Queue, "Queue must not be null");
    
    *Enumerable = (CCEnumerable){
        .handler = CCQueueEnumerableHandler,
        .enumerator = {
            .ref = Queue,
            .state = {
                .internal = {
                    .ptr = Queue->tail,
                    .extra = { (uintptr_t)Queue->tail, (uintptr_t)Queue->head }
                },
                .type = CCEnumeratorFormatInternal
            }
        }
    };
}
