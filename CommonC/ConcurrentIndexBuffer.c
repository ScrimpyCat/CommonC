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

#include "ConcurrentIndexBuffer.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include "ConcurrentBuffer.h"
#include "ConcurrentIDGenerator.h"
#include "ConsecutiveIDGenerator.h"

typedef struct CCConcurrentIndexBufferInfo {
    CCConcurrentIDGenerator indexPool;
    CCConcurrentBuffer buffer;
} CCConcurrentIndexBufferInfo;

static void CCConcurrentIndexBufferDestructor(CCConcurrentIndexBuffer IndexBuffer)
{
    CCConcurrentBufferDestroy(IndexBuffer->buffer);
    CCConcurrentIDGeneratorDestroy(IndexBuffer->indexPool);
}

CCConcurrentIndexBuffer CCConcurrentIndexBufferCreate(CCAllocatorType Allocator, size_t Count)
{
    CCAssertLog(Count, "Count must not be 0");
    CCAssertLog(Count != SIZE_MAX, "Count must not SIZE_MAX");
    
    CCConcurrentIndexBuffer IndexBuffer = CCMalloc(Allocator, sizeof(CCConcurrentIndexBufferInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (IndexBuffer)
    {
        *IndexBuffer = (CCConcurrentIndexBufferInfo){
            .indexPool = CCConcurrentIDGeneratorCreate(Allocator, Count, CCConsecutiveIDGenerator),
            .buffer = CCConcurrentBufferCreate(Allocator, NULL)
        };
        
        CCMemorySetDestructor(IndexBuffer, (CCMemoryDestructorCallback)CCConcurrentIndexBufferDestructor);
    }
    
    return IndexBuffer;
}

void CCConcurrentIndexBufferDestroy(CCConcurrentIndexBuffer IndexBuffer)
{
    CCAssertLog(IndexBuffer, "IndexBuffer must not be null");
    
    CC_SAFE_Free(IndexBuffer);
}

size_t CCConcurrentIndexBufferWriteAcquire(CCConcurrentIndexBuffer IndexBuffer)
{
    CCAssertLog(IndexBuffer, "IndexBuffer must not be null");
    
    return CCConcurrentIDGeneratorAssign(IndexBuffer->indexPool);
}

_Bool CCConcurrentIndexBufferReadAcquire(CCConcurrentIndexBuffer IndexBuffer, size_t *Index)
{
    CCAssertLog(IndexBuffer, "IndexBuffer must not be null");
    
    uintptr_t ReadIndex = (uintptr_t)CCConcurrentBufferReadData(IndexBuffer->buffer);
    if (ReadIndex)
    {
        *Index = ReadIndex - 1;
        return TRUE;
    }
    
    return FALSE;
}

void CCConcurrentIndexBufferStage(CCConcurrentIndexBuffer IndexBuffer, size_t Index)
{
    CCAssertLog(IndexBuffer, "IndexBuffer must not be null");
    
    uintptr_t PrevIndex = (uintptr_t)CCConcurrentBufferWriteDataSwap(IndexBuffer->buffer, (void*)(uintptr_t)(Index + 1));
    
    if (PrevIndex) CCConcurrentIDGeneratorRecycle(IndexBuffer->indexPool, PrevIndex - 1);
}

void CCConcurrentIndexBufferDiscard(CCConcurrentIndexBuffer IndexBuffer, size_t Index)
{
    CCAssertLog(IndexBuffer, "IndexBuffer must not be null");
    
    CCConcurrentIDGeneratorRecycle(IndexBuffer->indexPool, Index);
}
