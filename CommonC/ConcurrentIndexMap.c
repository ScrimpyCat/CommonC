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
    _Atomic(size_t) count;
    uint8_t buffer[];
} CCConcurrentIndexMapData;

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
    CCConcurrentIndexMapData *data;
} CCConcurrentIndexMapDataPointer;

#if !CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
#if CC_HARDWARE_PTR_64
_Static_assert(sizeof(_Atomic(CCConcurrentIndexMapDataPointer)) == 16, "Native types are not atomic, please set CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE");
#elif CC_HARDWARE_PTR_32
_Static_assert(sizeof(_Atomic(CCConcurrentIndexMapDataPointer)) == 8, "Native types are not atomic, please set CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE");
#endif
#endif

typedef struct {
    size_t size;
    _Bool (*getElement)(const void *, size_t, void *, size_t OutSize);
} CCConcurrentIndexMapAtomicOperation;

typedef struct CCConcurrentIndexMapInfo {
    CCAllocatorType allocator;
    size_t size, chunkSize;
    _Atomic(CCConcurrentIndexMapDataPointer) pointer;
    CCConcurrentGarbageCollector gc;
} CCConcurrentIndexMapInfo;

#define CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(x) \
typedef struct { uint8_t e[x - 1]; } CCConcurrentIndexMapAtomicElementType##x; \
typedef struct { CCConcurrentIndexMapAtomicElementType##x element; uint8_t set; } CCConcurrentIndexMapAtomicType##x; \
_Static_assert(sizeof(CCConcurrentIndexMapAtomicType##x) == x, "CCConcurrentIndexMapAtomicType"#x " should have a size of "#x); \
static _Bool CCConcurrentIndexMapAtomicGetElement##x(const void *Data, size_t Index, void *Out, size_t OutSize) \
{ \
    CCConcurrentIndexMapAtomicType##x Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)(Data + sizeof(_Atomic(size_t))))[Index], memory_order_relaxed); \
    if (Value.set) *(CCConcurrentIndexMapAtomicElementType##x*)Out = Value.element; \
    return Value.set; \
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

typedef struct {
    void *ptr;
    _Bool set;
} CCConcurrentIndexMapAtomicTypePtr;

static _Bool CCConcurrentIndexMapAtomicGetElementPtr(const void *Data, size_t Index, void *Out, size_t OutSize)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)(Data + sizeof(_Atomic(size_t))))[Index], memory_order_relaxed);
    if ((Value.set) && (Value.ptr)) memcpy(Out, Value.ptr, OutSize);
    return (Value.set) && (Value.ptr);
}


static CCConcurrentIndexMapAtomicOperation CCConcurrentIndexMapAtomicOperations[] = {
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType1)), .getElement = CCConcurrentIndexMapAtomicGetElement1 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType2)), .getElement = CCConcurrentIndexMapAtomicGetElement2 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType3)), .getElement = CCConcurrentIndexMapAtomicGetElement3 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType4)), .getElement = CCConcurrentIndexMapAtomicGetElement4 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType5)), .getElement = CCConcurrentIndexMapAtomicGetElement5 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType6)), .getElement = CCConcurrentIndexMapAtomicGetElement6 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType7)), .getElement = CCConcurrentIndexMapAtomicGetElement7 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType8)), .getElement = CCConcurrentIndexMapAtomicGetElement8 },
#if CC_HARDWARE_PTR_64
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType9)), .getElement = CCConcurrentIndexMapAtomicGetElement9 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType10)), .getElement = CCConcurrentIndexMapAtomicGetElement10 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType11)), .getElement = CCConcurrentIndexMapAtomicGetElement11 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType12)), .getElement = CCConcurrentIndexMapAtomicGetElement12 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType13)), .getElement = CCConcurrentIndexMapAtomicGetElement13 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType14)), .getElement = CCConcurrentIndexMapAtomicGetElement14 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType15)), .getElement = CCConcurrentIndexMapAtomicGetElement15 },
    { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType16)), .getElement = CCConcurrentIndexMapAtomicGetElement16 },
#endif
};

static CCConcurrentIndexMapAtomicOperation CCConcurrentIndexMapAtomicPtrOperation = { .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicTypePtr)), .getElement = CCConcurrentIndexMapAtomicGetElementPtr };

static inline _Bool CCConcurrentIndexMapRequiresExternalStorage(size_t ElementSize)
{
    return ElementSize >= (sizeof(CCConcurrentIndexMapAtomicOperations) / sizeof(typeof(*CCConcurrentIndexMapAtomicOperations)));
}

static inline CCConcurrentIndexMapAtomicOperation *CCConcurrentIndexMapGetAtomicOperation(size_t ElementSize)
{
    return CCConcurrentIndexMapRequiresExternalStorage(ElementSize) ? &CCConcurrentIndexMapAtomicPtrOperation : &CCConcurrentIndexMapAtomicOperations[ElementSize];
}

static void CCConcurrentIndexMapDestructor(CCConcurrentIndexMap Ptr)
{
    CCConcurrentIndexMapDataPointer Pointer = atomic_load(&Ptr->pointer);
    CCFree(Pointer.data);
    
    CCConcurrentGarbageCollectorDestroy(Ptr->gc);
}

CCConcurrentIndexMap CCConcurrentIndexMapCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, CCConcurrentGarbageCollector GC)
{
    CCAssertLog(ChunkSize >= 1, "ChunkSize must be at least 1");
    
    CCConcurrentIndexMap IndexMap = CCMalloc(Allocator, sizeof(CCConcurrentIndexMapInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (IndexMap)
    {
        CCConcurrentIndexMapData *Data = CCMalloc(Allocator, sizeof(CCConcurrentIndexMapData) + (ChunkSize * CCConcurrentIndexMapGetAtomicOperation(ElementSize)->size), NULL, CC_DEFAULT_ERROR_CALLBACK);
        atomic_init(&Data->count, 0);
        
        *IndexMap = (CCConcurrentIndexMapInfo){
            .allocator = Allocator,
            .size = ElementSize,
            .chunkSize = ChunkSize,
            .pointer = ATOMIC_VAR_INIT(((CCConcurrentIndexMapDataPointer){
                .data = Data,
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
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
    const size_t Count = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Count;
}

size_t CCConcurrentIndexMapGetElementSize(CCConcurrentIndexMap IndexMap)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    return IndexMap->chunkSize;
}

_Bool CCConcurrentIndexMapGetElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, void *Element)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
    const size_t MaxCount = ((atomic_load_explicit(&Pointer.data->count, memory_order_relaxed) / IndexMap->chunkSize) + 1) * IndexMap->chunkSize;
    
    const _Bool Exists = Index < MaxCount ? CCConcurrentIndexMapGetAtomicOperation(IndexMap->size)->getElement(Pointer.data->buffer, Index, Element, IndexMap->size) : FALSE;
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Exists;
}
