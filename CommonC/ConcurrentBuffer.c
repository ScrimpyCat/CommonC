/*
 *  Copyright (c) 2017, Stefan Johnson
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

#include "ConcurrentBuffer.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>

typedef struct CCConcurrentBufferInfo {
    CCAllocatorType allocator;
    CCConcurrentBufferDataDestructor destructor;
    _Atomic(void*) data;
} CCConcurrentBufferInfo;

static void CCConcurrentBufferDestructor(CCConcurrentBuffer Buffer)
{
    if (Buffer->destructor)
    {
        Buffer->destructor(atomic_load(&Buffer->data));
    }
}

CCConcurrentBuffer CCConcurrentBufferCreate(CCAllocatorType Allocator, CCConcurrentBufferDataDestructor Destructor)
{
    CCConcurrentBuffer Buffer = CCMalloc(Allocator, sizeof(CCConcurrentBufferInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Buffer)
    {
        *Buffer = (CCConcurrentBufferInfo){
            .allocator = Allocator,
            .destructor = Destructor,
            .data = ATOMIC_VAR_INIT(NULL)
        };
        
        CCMemorySetDestructor(Buffer, (CCMemoryDestructorCallback)CCConcurrentBufferDestructor);
    }
    
    return Buffer;
}

void CCConcurrentBufferDestroy(CCConcurrentBuffer Buffer)
{
    CCAssertLog(Buffer, "Buffer must not be null");
    
    CC_SAFE_Free(Buffer);
}

void CCConcurrentBufferWriteData(CCConcurrentBuffer Buffer, void *Data)
{
    CCAssertLog(Buffer, "Buffer must not be null");
    
    void *Ptr = atomic_exchange(&Buffer->data, Data);
    if (Buffer->destructor)
    {
        Buffer->destructor(Ptr);
    }
}

void *CCConcurrentBufferReadData(CCConcurrentBuffer Buffer)
{
    CCAssertLog(Buffer, "Buffer must not be null");
    
    return atomic_exchange(&Buffer->data, NULL);
}
