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

#ifndef CommonC_Queue_h
#define CommonC_Queue_h

#include <CommonC/LinkedList.h>
#include <CommonC/Ownership.h>

typedef struct {
    CCLinkedList head;
    CCLinkedList tail;
} CCQueueInfo, *CCQueue;

#pragma mark - Creation / Destruction
/*!
 * @brief Allocate and initialize a new FIFO queue.
 * @param Allocator The allocator to be used for the allocation.
 * @return A FIFO queue, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCQueue CCQueueCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a queue.
 * @param Queue The queue to be destroyed.
 */
void CCQueueDestroy(CCQueue CC_DESTROY(Queue));

#pragma mark - Enqueue/Dequeue
/*!
 * @brief Push the node to the end of the queue.
 * @param Queue The queue to have the node added to.
 * @param Node The node to be added to the queue.
 */
void CCQueuePush(CCQueue Queue, CCLinkedListNode *CC_OWN(Node));

/*!
 * @brief Pop the node at the start of the queue.
 * @param Queue The queue to have the node removed from.
 * @result The node removed from the queue, or NULL if empty. Must be destroyed to
 *         free the memory.
 */
CC_NEW CCLinkedListNode *CCQueuePop(CCQueue Queue);

#endif
