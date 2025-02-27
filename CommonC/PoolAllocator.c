/*
 *  Copyright (c) 2025, Stefan Johnson
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

#include "PoolAllocator.h"
#include "MemoryAllocation.h"

CCPoolAllocator CCPoolAllocatorCreate(CCAllocatorType Allocator, size_t Size, size_t Alignment, size_t Max)
{
    const size_t BlockSize = CC_ALIGN(Size + sizeof(CCPoolAllocatorHeader), Alignment);
    
    CCPoolAllocator Pool = CCMalloc(Allocator, sizeof(CCPoolAllocatorInfo) + (sizeof(size_t) * Max) + (BlockSize * Max), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Pool)
    {
        *Pool = (CCPoolAllocatorInfo){
            .blockSize = BlockSize,
            .count = 0,
            .max = Max,
            .pool = (void*)CC_ALIGN((uintptr_t)((uint8_t*)Pool + sizeof(CCPoolAllocatorInfo) + (sizeof(size_t) * Max) + sizeof(CCPoolAllocatorHeader)), Alignment) - sizeof(CCPoolAllocatorHeader),
            .available = {
                .count = 0,
                .indexes = (void*)((uint8_t*)Pool + sizeof(CCPoolAllocatorInfo))
            }
        };
    }
    
    return Pool;
}

void CCPoolAllocatorDestroy(CCPoolAllocator Pool)
{
    CCAssertLog(Pool, "Pool must not be null");
    
    CCFree(Pool);
}
