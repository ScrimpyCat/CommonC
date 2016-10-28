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

#include "Task.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include "Logging.h"
#include <stdatomic.h>
#include <stdint.h>

typedef struct CCTaskInfo {
    void *input;
    void *output;
    CCTaskFunction function;
    _Atomic(_Bool) completed;
} CCTaskInfo;


static void CCTaskDestructor(CCTask Task)
{
    if (Task->input) CCFree(Task->input);
    if (Task->output) CCFree(Task->output);
}

CCTask CCTaskCreate(CCAllocatorType Allocator, CCTaskFunction Function, size_t OutputSize, CCMemoryDestructorCallback OutputDestructor, size_t InputSize, const void *Input, CCMemoryDestructorCallback InputDestructor)
{
    CCTask Task = CCMalloc(Allocator, sizeof(CCTaskInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Task)
    {
        *Task = (CCTaskInfo){ .input = NULL, .output = NULL, .function = Function };
        atomic_init(&Task->completed, FALSE);
        
        CCMemorySetDestructor(Task, (CCMemoryDestructorCallback)CCTaskDestructor);
        
        if (InputSize)
        {
            Task->input = CCMalloc(Allocator, InputSize, NULL, CC_DEFAULT_ERROR_CALLBACK);
            if (!Task->input)
            {
                CC_LOG_ERROR("Failed to create task: Failed to allocate input memory of size (%zu)", InputSize);
                CCFree(Task);
                
                return Task;
            }
            
            if (Input) memcpy(Task->input, Input, InputSize);
            
            CCMemorySetDestructor(Task->input, InputDestructor);
        }
        
        if (OutputSize)
        {
            Task->output = CCMalloc(Allocator, OutputSize, NULL, CC_DEFAULT_ERROR_CALLBACK);
            if (!Task->output)
            {
                CC_LOG_ERROR("Failed to create task: Failed to allocate input memory of size (%zu)", OutputSize);
                CCFree(Task);
                
                return Task;
            }
            
            memset(Task->output, 0, OutputSize);
            
            CCMemorySetDestructor(Task->output, OutputDestructor);
        }
    }
    
    return Task;
}

void CCTaskDestroy(CCTask Task)
{
    CCAssertLog(Task, "Task must not be null");
    
    CCFree(Task);
}

//void CCTaskRun(CCTask Task);
//
//_Bool CCTaskIsFinished(CCTask Task);
//
//void CCTaskWait(CCTask Task);
//
//void *CCTaskGetResult(CCTask Task);
