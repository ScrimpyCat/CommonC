/*
 *  Copyright (c) 2019, Stefan Johnson
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

#include "ConcurrentIDGenerator.h"
#include "MemoryAllocation.h"
#include "Assertion.h"

typedef struct CCConcurrentIDGeneratorInfo {
    const CCConcurrentIDGeneratorInterface *interface;
    void *internal;
} CCConcurrentIDGeneratorInfo;


static void CCConcurrentIDGeneratorDestructor(CCConcurrentIDGenerator Generator)
{
    Generator->interface->destroy(Generator->internal);
}

CCConcurrentIDGenerator CCConcurrentIDGeneratorCreate(CCAllocatorType Allocator, size_t Count, const CCConcurrentIDGeneratorInterface *Interface)
{
    CCConcurrentIDGenerator Generator = CCMalloc(Allocator, sizeof(CCConcurrentIDGeneratorInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Generator)
    {
        *Generator = (CCConcurrentIDGeneratorInfo){
            .interface = Interface,
            .internal = Interface->create(Allocator, Count)
        };
        
        if (!Generator->internal)
        {
            CC_LOG_ERROR("Failed to create ID generator: Implementation failure (%p)", Interface);
            CCFree(Generator);
            Generator = NULL;
        }
        
        else CCMemorySetDestructor(Generator, (CCMemoryDestructorCallback)CCConcurrentIDGeneratorDestructor);
    }
    
    else
    {
        CC_LOG_ERROR("Failed to create ID generator: Failed to allocate memory of size (%zu)", sizeof(CCConcurrentIDGeneratorInfo));
    }
    
    return Generator;
}

void CCConcurrentIDGeneratorDestroy(CCConcurrentIDGenerator Generator)
{
    CCAssertLog(Generator, "Generator must not be null");
    
    CCFree(Generator);
}

uintptr_t CCConcurrentIDGeneratorAssign(CCConcurrentIDGenerator Generator)
{
    CCAssertLog(Generator, "Generator must not be null");
    
    return Generator->interface->assign(Generator->internal);
}

_Bool CCConcurrentIDGeneratorTryAssign(CCConcurrentIDGenerator Generator, uintptr_t *ID)
{
    CCAssertLog(Generator, "Generator must not be null");
    
    return Generator->interface->try(Generator->internal, ID);
}

void CCConcurrentIDGeneratorRecycle(CCConcurrentIDGenerator Generator, uintptr_t ID)
{
    CCAssertLog(Generator, "Generator must not be null");
    
    Generator->interface->recycle(Generator->internal, ID);
}

uintptr_t CCConcurrentIDGeneratorGetMaxID(CCConcurrentIDGenerator Generator)
{
    CCAssertLog(Generator, "Generator must not be null");
    
    return Generator->interface->max(Generator->internal);
}
