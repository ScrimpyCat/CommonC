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

#include "ConsecutiveIDGenerator.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>

/*
 CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE enforces standard compliant usage of atomic types. This however will
 result in no batched operations.
 */
#ifndef CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
#define CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE 0
#endif

#if !CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
#if !CC_HARDWARE_PTR_64 && !CC_HARDWARE_PTR_32
#undef CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
#define CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE 1
#endif
#endif

typedef struct {
    size_t size;
#if CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
    atomic_flag pool[];
#else
    _Atomic(uint8_t) pool[];
#endif
} CCConsecutiveIDGeneratorInternal;

#if !CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
typedef uint64_t CCConsecutiveIDGeneratorSample;
#define CC_CONCURRENT_ID_POOL_SAMPLE_MAX UINT64_MAX
#else
typedef uint32_t CCConsecutiveIDGeneratorSample;
#define CC_CONCURRENT_ID_POOL_SAMPLE_MAX UINT32_MAX
#endif
#endif

#if !CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
_Static_assert(sizeof(_Atomic(CCConsecutiveIDGeneratorSample)) == 8, "Native types are not atomic, please set CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE");
#elif CC_HARDWARE_PTR_32
_Static_assert(sizeof(_Atomic(CCConsecutiveIDGeneratorSample)) == 4, "Native types are not atomic, please set CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE");
#endif
#endif


static void *CCConsecutiveIDGeneratorConstructor(CCAllocatorType Allocator, size_t Count);
static void CCConsecutiveIDGeneratorDestructor(CCConsecutiveIDGeneratorInternal *Internal);
static _Bool CCConsecutiveIDGeneratorTryAssign(CCConsecutiveIDGeneratorInternal *Internal, uintptr_t *ID);
static void CCConsecutiveIDGeneratorRecycle(CCConsecutiveIDGeneratorInternal *Internal, uintptr_t ID);
static uintptr_t CCConsecutiveIDGeneratorGetMaxID(CCConsecutiveIDGeneratorInternal *Internal);

const CCConcurrentIDGeneratorInterface CCConsecutiveIDGeneratorInterface = {
    .create = CCConsecutiveIDGeneratorConstructor,
    .destroy = (CCConcurrentIDGeneratorDestructorCallback)CCConsecutiveIDGeneratorDestructor,
    .try = (CCConcurrentIDGeneratorTryAssignCallback)CCConsecutiveIDGeneratorTryAssign,
    .recycle = (CCConcurrentIDGeneratorRecycleCallback)CCConsecutiveIDGeneratorRecycle,
    .max = (CCConcurrentIDGeneratorGetMaxIDCallback)CCConsecutiveIDGeneratorGetMaxID
};


const CCConcurrentIDGeneratorInterface * const CCConsecutiveIDGenerator = &CCConsecutiveIDGeneratorInterface;

void *CCConsecutiveIDGeneratorConstructor(CCAllocatorType Allocator, size_t PoolSize)
{
    CCConsecutiveIDGeneratorInternal *IDPool;
#if CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
    const size_t PaddedPoolCount = PoolSize;
#else
    const size_t PaddedPoolCount = ((((PoolSize - 1) / (sizeof(CCConsecutiveIDGeneratorSample) / sizeof(typeof(IDPool->pool[0])))) + 1) * (sizeof(CCConsecutiveIDGeneratorSample) / sizeof(typeof(IDPool->pool[0]))));
#endif
    IDPool = CCMalloc(Allocator, sizeof(CCConsecutiveIDGeneratorInternal) + (PaddedPoolCount * sizeof(typeof(IDPool->pool[0]))), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (IDPool)
    {
        IDPool->size = PoolSize;
#if CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
        for (size_t Loop = 0; Loop < PoolSize; Loop++) atomic_flag_clear_explicit(&IDPool->pool[Loop], memory_order_relaxed);
#else
        for (size_t Loop = 0; Loop < PoolSize; Loop++) atomic_init(&IDPool->pool[Loop], 0);
        for (size_t Loop = PoolSize, PadCount = PaddedPoolCount; Loop < PadCount; Loop++) atomic_init(&IDPool->pool[Loop], UINT8_MAX);
#endif
    }
    
    return IDPool;
}

void CCConsecutiveIDGeneratorDestructor(CCConsecutiveIDGeneratorInternal *IDPool)
{
    CCFree(IDPool);
}

_Bool CCConsecutiveIDGeneratorTryAssign(CCConsecutiveIDGeneratorInternal *IDPool, uintptr_t *ID)
{
#if CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
    for (size_t Loop = 0, Count = IDPool->size; Loop < Count; Loop++)
    {
        if (!atomic_flag_test_and_set_explicit(&IDPool->pool[Loop], memory_order_relaxed))
        {
            *ID = Loop;
            atomic_thread_fence(memory_order_acquire);
            return TRUE;
        }
    }
#else
    for (size_t Loop = 0, Count = IDPool->size; Loop < Count; Loop += (sizeof(CCConsecutiveIDGeneratorSample) / sizeof(typeof(IDPool->pool[0]))))
    {
        CCConsecutiveIDGeneratorSample Sample = atomic_load_explicit((_Atomic(CCConsecutiveIDGeneratorSample)*)&IDPool->pool[Loop], memory_order_relaxed);
        if (Sample != CC_CONCURRENT_ID_POOL_SAMPLE_MAX)
        {
            for (size_t Loop2 = Loop, SampleCount = Loop + (sizeof(CCConsecutiveIDGeneratorSample) / sizeof(typeof(IDPool->pool[0]))); Loop2 < SampleCount; Loop2++)
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
#endif
    
    return FALSE;
}

void CCConsecutiveIDGeneratorRecycle(CCConsecutiveIDGeneratorInternal *IDPool, uintptr_t ID)
{
    CCAssertLog(ID < IDPool->size, "ID must have been assigned from this pool");
    
#if CC_CONSECUTIVE_ID_GENERATOR_STRICT_COMPLIANCE
    CCAssertLog(atomic_flag_test_and_set_explicit(&IDPool->pool[ID], memory_order_relaxed), "ID must be assigned");
    atomic_flag_clear_explicit(&IDPool->pool[ID], memory_order_release);
#else
    CCAssertLog(atomic_load_explicit(&IDPool->pool[ID], memory_order_relaxed), "ID must be assigned");
    atomic_store_explicit(&IDPool->pool[ID], 0, memory_order_release);
#endif
}

size_t CCConsecutiveIDGeneratorGetMaxID(CCConsecutiveIDGeneratorInternal *IDPool)
{
    return IDPool->size;
}
