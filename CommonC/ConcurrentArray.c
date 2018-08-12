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

#include "ConcurrentArray.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>
#include <string.h>

/*
 CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE enforces standard compliant usage of atomic types. This however will
 result in all operations requiring CAS-loops.
 */
#define CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE 0

#if !CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE
#if !CC_HARDWARE_PTR_64 && !CC_HARDWARE_PTR_32
#undef CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE
#define CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE 1
#endif
#endif

typedef struct {
    void *element;
    uintptr_t tag;
} CCConcurrentArrayBufferPointer;

typedef struct {
    CCConcurrentArray array;
    _Atomic(size_t) count;
    _Atomic(CCConcurrentArrayBufferPointer) buffer[];
} CCConcurrentArrayData;

typedef struct {
#if CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
    uint64_t mutate;
#else
    uint32_t mutate;
#endif
#else
#if CC_HARDWARE_PTR_64
    _Atomic(uint64_t) mutate;
#else
    _Atomic(uint32_t) mutate;
#endif
#endif
    CCConcurrentArrayData *data;
} CCConcurrentArrayDataPointer;

#if !CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
_Static_assert(sizeof(_Atomic(CCConcurrentArrayDataPointer)) == 16, "Native types are not atomic, please set CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE");
#elif CC_HARDWARE_PTR_32
_Static_assert(sizeof(_Atomic(CCConcurrentArrayDataPointer)) == 8, "Native types are not atomic, please set CC_CONCURRENT_ARRAY_STRICT_COMPLIANCE");
#endif
#endif

typedef struct CCConcurrentArrayInfo {
    CCAllocatorType allocator;
    size_t size, chunkSize;
    _Atomic(CCConcurrentArrayDataPointer) pointer;
    CCConcurrentGarbageCollector gc;
} CCConcurrentArrayInfo;
