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

#ifndef CommonC_ConcurrentQueue_h
#define CommonC_ConcurrentQueue_h

/*
 Lock-free FIFO queue implementation: http://www.cs.tau.ac.il/%7Eshanir/nir-pubs-web/Papers/FIFO_Queues.pdf or mirror: https://www.offblast.org/stuff/books/FIFO_Queues.pdf
 Allows for many producer-consumer access.
 */

#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    struct CCConcurrentQueueNode *node;
    uint32_t tag;
} CCConcurrentQueuePointer;

typedef struct CCConcurrentQueueNode {
    _Atomic(CCConcurrentQueuePointer) next;
    _Atomic(CCConcurrentQueuePointer) prev;
} CCConcurrentQueueNode;

typedef struct {
    CCConcurrentQueueNode node;
    uint8_t data[];
} CCConcurrentQueueNodeData;

typedef struct {
    _Atomic(CCConcurrentQueuePointer) head;
    _Atomic(CCConcurrentQueuePointer) tail;
    CCConcurrentQueueNode dummy;
} CCConcurrentQueueInfo, *CCConcurrentQueue;

#pragma mark - Creation / Destruction
/*!
 * @brief Allocate and initialize a new node.
 * @param Allocator The allocator to be used for the allocation.
 * @param Size The size of the data.
 * @param Data The data to initialize the node with. May be NULL.
 * @return A pointer to the created node containing the data (if not NULL), or NULL on failure.
 *         Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentQueueNode *CCConcurrentQueueCreateNode(CCAllocatorType Allocator, size_t Size, const void *Data);

/*!
 * @brief Destroy the node.
 * @param Node The node to be destroyed.
 */
void CCConcurrentQueueDestroyNode(CCConcurrentQueueNode *CC_DESTROY(Node));

/*!
 * @brief Create a concurrent FIFO queue.
 * @description This queue allows for many producer-consumer access.
 * @param Allocator The allocator to be used for the allocation.
 * @return A FIFO queue, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentQueue CCConcurrentQueueCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a queue.
 * @param Queue The queue to be destroyed.
 */
void CCConcurrentQueueDestroy(CCConcurrentQueue CC_DESTROY(Queue));

#pragma mark - Enqueue/Dequeue
/*!
 * @brief Push the node to the end of the queue.
 * @param Queue The queue to have the node added to.
 * @param Node The node to be added to the queue.
 */
void CCConcurrentQueuePush(CCConcurrentQueue Queue, CCConcurrentQueueNode *CC_OWN(Node));

/*!
 * @brief Pop the node at the start of the queue.
 * @param Queue The queue to have the node removed from.
 * @result The node removed from the queue, or NULL if empty. Must be destroyed to
 *         free the memory.
 */
CC_NEW CCConcurrentQueueNode *CCConcurrentQueuePop(CCConcurrentQueue Queue);

#pragma mark - Query
/*!
 * @brief Get a pointer to the data in the node.
 * @param Node The node to get the data of.
 * @return A pointer to the data it contains.
 */
static inline void *CCConcurrentQueueGetNodeData(CCConcurrentQueueNode *Node);


#pragma mark -

static inline void *CCConcurrentQueueGetNodeData(CCConcurrentQueueNode *Node)
{
    return ((CCConcurrentQueueNodeData*)Node)->data;
}

#endif
