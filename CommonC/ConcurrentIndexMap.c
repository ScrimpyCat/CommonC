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

typedef struct CCConcurrentIndexMapInfo {
    CCAllocatorType allocator;
    size_t size, storageSize, chunkSize;
    _Atomic(size_t) count;
    _Atomic(CCConcurrentIndexMapDataPointer) pointer;
    CCConcurrentGarbageCollector gc;
} CCConcurrentIndexMapInfo;


static void CCConcurrentIndexMapDestructor(CCConcurrentIndexMap Ptr)
{
    CCConcurrentIndexMapDataPointer Pointer = atomic_load(&Ptr->pointer);
    CCFree(Pointer.data);
    CCConcurrentGarbageCollectorDestroy(Ptr->gc);
}

CCConcurrentIndexMap CCConcurrentIndexMapCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ElementStorageSize, size_t ChunkSize, CCConcurrentGarbageCollector GC)
{
    CCAssertLog(ChunkSize >= 1, "ChunkSize must be at least 1");
    CCAssertLog(ElementSize <= ElementStorageSize, "ElementSize should not be greater than ElementStorageSize");
    CCAssertLog(ElementStorageSize == sizeof(_Atomic(uint8_t))
                || ElementStorageSize == sizeof(_Atomic(uint16_t))
                || ElementStorageSize == sizeof(_Atomic(uint32_t))
                || ElementStorageSize == sizeof(_Atomic(uint64_t))
                , "ElementStorageSize must match one of the listed sizes");
    
    
    CCConcurrentIndexMap IndexMap = CCMalloc(Allocator, sizeof(CCConcurrentIndexMapInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (IndexMap)
    {
        *IndexMap = (CCConcurrentIndexMapInfo){
            .allocator = Allocator,
            .size = ElementSize,
            .storageSize = ElementStorageSize,
            .chunkSize = ChunkSize,
            .count = ATOMIC_VAR_INIT(0),
            .pointer = ATOMIC_VAR_INIT(((CCConcurrentIndexMapDataPointer){
                .data = CCMalloc(Allocator, ChunkSize * ElementStorageSize, NULL, CC_DEFAULT_ERROR_CALLBACK),
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
                .mutate = 0,
                .modify = 0
#else
                .mutate = ATOMIC_VAR_INIT(0),
                .modify = ATOMIC_VAR_INIT(0)
#endif
            }))
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
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    CCConcurrentIndexMapDataPointer Pointer = atomic_load(&IndexMap->pointer);
    
    switch (IndexMap->size)
    {
        case sizeof(_Atomic(uint8_t)):
        {
            uint8_t Value = atomic_load_explicit(&((_Atomic(uint8_t)*)Pointer.data)[Index], memory_order_relaxed);
            memcpy(Element, &Value, IndexMap->size);
            break;
        }
            
        case sizeof(_Atomic(uint16_t)):
        {
            uint16_t Value = atomic_load_explicit(&((_Atomic(uint16_t)*)Pointer.data)[Index], memory_order_relaxed);
            memcpy(Element, &Value, IndexMap->size);
            break;
        }
            
        case sizeof(_Atomic(uint32_t)):
        {
            uint32_t Value = atomic_load_explicit(&((_Atomic(uint32_t)*)Pointer.data)[Index], memory_order_relaxed);
            memcpy(Element, &Value, IndexMap->size);
            break;
        }
            
        case sizeof(_Atomic(uint64_t)):
        {
            uint64_t Value = atomic_load_explicit(&((_Atomic(uint64_t)*)Pointer.data)[Index], memory_order_relaxed);
            memcpy(Element, &Value, IndexMap->size);
            break;
        }
            
        default:
            CCAssertLog(1, "Unsupported element type");
            break;
    }
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
}
