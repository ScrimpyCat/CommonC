/*
 *  Copyright (c) 2018, Stefan Johnson
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

#include "ConcurrentIDPool.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>

typedef struct CCConcurrentIDPoolInfo {
    size_t size;
    _Atomic(uint8_t) pool[];
} CCConcurrentIDPoolInfo;

CCConcurrentIDPool CCConcurrentIDPoolCreate(CCAllocatorType Allocator, size_t PoolSize)
{
    CCAssertLog(PoolSize >= 1, "PoolSize must be at least 1");
    
    CCConcurrentIDPool IDPool = CCMalloc(Allocator, sizeof(CCConcurrentIDPoolInfo) + (sizeof(typeof(IDPool->pool[0])) * PoolSize), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (IDPool)
    {
        IDPool->size = PoolSize;
        for (size_t Loop = 0; Loop < PoolSize; Loop++) atomic_init(&IDPool->pool[Loop], 0);
    }
    
    return IDPool;
}

void CCConcurrentIDPoolDestroy(CCConcurrentIDPool IDPool)
{
    CCAssertLog(IDPool, "IDPool must not be null");
    CCFree(IDPool);
}

size_t CCConcurrentIDPoolAssign(CCConcurrentIDPool IDPool)
{
    size_t ID;
    while (!CCConcurrentIDPoolTryAssign(IDPool, &ID)) CC_SPIN_WAIT();
    
    return ID;
}

_Bool CCConcurrentIDPoolTryAssign(CCConcurrentIDPool IDPool, size_t *ID)
{
    for (size_t Loop = 0, Count = IDPool->size; Loop < Count; Loop += (sizeof(uint64_t) / sizeof(typeof(IDPool->pool[0]))))
    {
        uint64_t Sample = atomic_load_explicit((_Atomic(uint64_t)*)&IDPool->pool[Loop], memory_order_relaxed);
        if (Sample != UINT64_MAX)
        {
            for (size_t Loop2 = Loop, SampleCount = Loop + (sizeof(uint64_t) / sizeof(typeof(IDPool->pool[0]))); Loop2 < SampleCount; Loop2++)
            {
                if (atomic_exchange_explicit(&IDPool->pool[Loop2], UINT8_MAX, memory_order_relaxed) == 0)
                {
                    *ID = Loop2;
                    atomic_thread_fence(memory_order_acquire);
                    return TRUE;
                }
            }
        }
    }
    
    return FALSE;
}

void CCConcurrentIDPoolRecycle(CCConcurrentIDPool IDPool, size_t ID)
{
    CCAssertLog(ID < IDPool->size, "ID must have been assigned from this pool");
    
    atomic_store_explicit(&IDPool->pool[ID], 0, memory_order_release);
}
