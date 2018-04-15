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

#include "ConcurrentIndexMap.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <stdatomic.h>

/*
 CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE enforces standard compliant usage of atomic types. This however will
 result in all operations requiring CAS-loops.
 */
#define CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE 0

#if !CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
#if !CC_HARDWARE_PTR_64 && !CC_HARDWARE_PTR_32
#undef CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
#define CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE 1
#endif
#endif

typedef struct {
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
    uint32_t mutate;
    uint32_t modify;
#else
    uint16_t mutate;
    uint16_t modify;
#endif
#else
#if CC_HARDWARE_PTR_64
    _Atomic(uint32_t) mutate;
    _Atomic(uint32_t) modify;
#else
    _Atomic(uint16_t) mutate;
    _Atomic(uint16_t) modify;
#endif
#endif
    void *data;
} CCConcurrentIndexMapDataPointer;

#if !CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
_Static_assert(sizeof(_Atomic(CCConcurrentIndexMapDataPointer)) == 16, "Native types are not atomic, please set CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE");
#elif CC_HARDWARE_PTR_32
_Static_assert(sizeof(_Atomic(CCConcurrentIndexMapDataPointer)) == 8, "Native types are not atomic, please set CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE");
#endif
#endif

typedef struct {
    void (*getElement)(const void *, size_t, void *);
} CCConcurrentIndexMapAtomicOperation;

typedef struct CCConcurrentIndexMapInfo {
    CCAllocatorType allocator;
    size_t size, chunkSize;
    _Atomic(size_t) count;
    _Atomic(CCConcurrentIndexMapDataPointer) pointer;
    CCConcurrentGarbageCollector gc;
    CCConcurrentIndexMapAtomicOperation atomic;
} CCConcurrentIndexMapInfo;

#define CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(x) \
typedef struct { uint8_t e[x]; } CCConcurrentIndexMapAtomicType##x; \
static void CCConcurrentIndexMapAtomicGetElement##x(const void *Data, size_t Index, void *Out) \
{ \
    *(CCConcurrentIndexMapAtomicType##x*)Out = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], memory_order_relaxed); \
}

CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(1)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(2)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(3)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(4)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(5)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(6)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(7)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(8)
#if CC_HARDWARE_PTR_64
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(9)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(10)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(11)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(12)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(13)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(14)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(15)
CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(16)
#endif

static CCConcurrentIndexMapAtomicOperation CCConcurrentIndexMapAtomicOperations[] = {
    { .getElement = CCConcurrentIndexMapAtomicGetElement1 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement2 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement3 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement4 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement5 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement6 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement7 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement8 },
#if CC_HARDWARE_PTR_64
    { .getElement = CCConcurrentIndexMapAtomicGetElement9 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement10 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement11 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement12 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement13 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement14 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement15 },
    { .getElement = CCConcurrentIndexMapAtomicGetElement16 }
#endif
};

static void CCConcurrentIndexMapDestructor(CCConcurrentIndexMap Ptr)
{
    CCConcurrentIndexMapDataPointer Pointer = atomic_load(&Ptr->pointer);
    CCFree(Pointer.data);
    
    CCConcurrentGarbageCollectorDestroy(Ptr->gc);
}

CCConcurrentIndexMap CCConcurrentIndexMapCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, CCConcurrentGarbageCollector GC)
{
    CCAssertLog(ChunkSize >= 1, "ChunkSize must be at least 1");
    CCAssertLog((ElementSize > 0) && (ElementSize <= (sizeof(CCConcurrentIndexMapAtomicOperations) / sizeof(typeof(*CCConcurrentIndexMapAtomicOperations)))), "ElementSize must match one of valid predefined sizes");
    
    
    CCConcurrentIndexMap IndexMap = CCMalloc(Allocator, sizeof(CCConcurrentIndexMapInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (IndexMap)
    {
        *IndexMap = (CCConcurrentIndexMapInfo){
            .allocator = Allocator,
            .size = ElementSize,
            .chunkSize = ChunkSize,
            .count = ATOMIC_VAR_INIT(0),
            .pointer = ATOMIC_VAR_INIT(((CCConcurrentIndexMapDataPointer){
                .data = CCMalloc(Allocator, ChunkSize * ElementSize, NULL, CC_DEFAULT_ERROR_CALLBACK),
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
                .mutate = 0,
                .modify = 0
#else
                .mutate = ATOMIC_VAR_INIT(0),
                .modify = ATOMIC_VAR_INIT(0)
#endif
            })),
            .atomic = CCConcurrentIndexMapAtomicOperations[ElementSize - 1]
        };
        
        CCMemorySetDestructor(IndexMap, (CCMemoryDestructorCallback)CCConcurrentIndexMapDestructor);
    }

    
    return IndexMap;
}

void CCConcurrentIndexMapDestroy(CCConcurrentIndexMap IndexMap)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    CCFree(IndexMap);
}

size_t CCConcurrentIndexMapGetCount(CCConcurrentIndexMap IndexMap)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    return atomic_load_explicit(&IndexMap->count, memory_order_relaxed);
}

size_t CCConcurrentIndexMapGetElementSize(CCConcurrentIndexMap IndexMap)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    return IndexMap->chunkSize;
}

void CCConcurrentIndexMapGetElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, void *Element)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    CCAssertLog(CCConcurrentIndexMapGetCount(IndexMap) > Index, "Index must not be out of bounds");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    CCConcurrentIndexMapDataPointer Pointer = atomic_load(&IndexMap->pointer);
    IndexMap->atomic.getElement(Pointer.data, Index, Element);
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
}
