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

#ifndef CommonC_Task_h
#define CommonC_Task_h

#include <CommonC/Allocator.h>
#include <CommonC/Ownership.h>

/*!
 * @brief The function to be executed.
 * @param In The arguments passed into the function.
 * @param Out The result of the function.
 */
typedef void (*CCTaskFunction)(const void *In, void *Out);

/*!
 * @brief An execution task.
 * @description Allows @b CCRetain.
 */
typedef struct CCTaskInfo *CCTask;

#pragma mark - Creation / Destruction
/*!
 * @brief Create an executable task.
 * @param Allocator The allocator to be used for the allocation.
 * @param Function The function to be executed.
 * @param OutputSize The size of the output.
 * @param OutputDestructor The destructor for the output. @b Note: It should be able to
 *        handle that the default value (if the output has not been set) will be 0.
 *
 * @param InputSize The size of the input.
 * @param Input The input to be copied to be passed to the function.
 * @param InputDestructor The destructor for the input.
 * @return An exectuable task, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCTask CCTaskCreate(CCAllocatorType Allocator, CCTaskFunction Function, size_t OutputSize, CCMemoryDestructorCallback OutputDestructor, size_t InputSize, const void *Input, CCMemoryDestructorCallback InputDestructor);

/*!
 * @brief Destroy a task.
 * @param Task The task to be destroyed.
 */
void CCTaskDestroy(CCTask CC_DESTROY(Task));

#pragma mark - Control
/*!
 * @brief Run the task on the current thread.
 * @warning This is not a threadsafe operation. If running it simultaneously on different
 *          threads, the burden of threadsafety falls onto the function implementor.
 *
 * @param Task The task to be executed.
 */
void CCTaskRun(CCTask Task);

/*!
 * @brief Check if the task has finished.
 * @description This does not block and will only return TRUE when it has completed running.
 *              If the task is run simultaneously, all execution will need to return before
 *              this returns true.
 *
 * @param Task The task to check has finished running.
 * @result TRUE if the task has completed, otherwise FALSE if it has not run or is still running.
 */
_Bool CCTaskIsFinished(CCTask Task);

/*!
 * @brief Wait for the task to complete.
 * @warning This will block the current thread forever if the task never completes.
 * @param Task The task to wait for.
 */
void CCTaskWait(CCTask Task);

/*!
 * @brief Wait for the task to complete and get the result.
 * @description If the task has already completed this will return immediately.
 * @warning This will block the current thread forever if the task never completes.
 * @param Task The task to get the result from.
 * @result The result.
 */
void *CCTaskGetResult(CCTask Task);

#endif
