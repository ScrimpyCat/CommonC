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

#ifndef Common_TaskQueue_h
#define Common_TaskQueue_h

#include <CommonC/Allocator.h>
#include <CommonC/Ownership.h>
#include <CommonC/Task.h>
#include <CommonC/ConcurrentGarbageCollector.h>

/*!
 * @brief The execution type for the task queue.
 */
typedef enum {
    /// Tasks are executed simultaneously.
    CCTaskQueueExecuteConcurrently,
    /// Tasks are executed one after the other.
    CCTaskQueueExecuteSerially
} CCTaskQueueExecute;

/*!
 * @brief A task queue.
 * @description Allows @b CCRetain.
 */
typedef struct CCTaskQueueInfo *CCTaskQueue;

#pragma mark - Creation / Destruction
/*!
 * @brief Get the default task queue.
 * @description This is a concurrent queue with an epoch garbage collector.
 * @return The default task queue.
 */
CCTaskQueue CCTaskQueueDefault(void);

/*!
 * @brief Create a task queue.
 * @param Allocator The allocator to be used for the allocation.
 * @param ExecutionType The execution behaviour for the queue.
 * @param GC The garbage collector to be used internally.
 * @return A task queue, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCTaskQueue CCTaskQueueCreate(CCAllocatorType Allocator, CCTaskQueueExecute ExecutionType, CCConcurrentGarbageCollector GC);

/*!
 * @brief Destroy a task queue.
 * @param Queue The task queue to be destroyed.
 */
void CCTaskQueueDestroy(CCTaskQueue CC_DESTROY(Queue));

#pragma mark - Insertions/Deletions
/*!
 * @brief Add a task to the end of the queue.
 * @param Queue The task queue to manage the task.
 * @param Task The task to be added.
 */
void CCTaskQueuePush(CCTaskQueue Queue, CCTask CC_OWN(Task));

/*!
 * @brief Retrieve the next task.
 * @description If the queue is to be executed serially, it won't pop the task if the task before
 *              it is still running.
 *
 * @warning If the queue is to be executed serially pausing a thread currently inside this function
 *          leads to the possibility of the queue no longer progressing (not until the thread is
 *          resumed). However the queue will never block.
 *
 * @param Queue The task queue to retrieve the task from.
 * @result The task or NULL.
 */
CC_NEW CCTask CCTaskQueuePop(CCTaskQueue Queue);

#pragma mark - Info
/*!
 * @brief Check if the queue was empty.
 * @warning It does not guarantee that the queue is still empty after returning.
 * @param Queue The task queue to check emptiness of.
 * @result TRUE if the task queue was empty, otherwise FALSE if it still has tasks.
 */
_Bool CCTaskQueueIsEmpty(CCTaskQueue Queue);

#endif
