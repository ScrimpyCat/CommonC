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
#include <string.h>

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
    CCConcurrentIndexMap indexMap;
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
    _Bool (*initElement)(CCConcurrentIndexMap, void *, size_t, const void *);
    void (*copyElement)(void *, size_t, const void *, size_t);
    _Bool (*getElement)(CCConcurrentIndexMap, const void *, size_t, void *);
    _Bool (*removeElement)(CCConcurrentIndexMap, const void *, size_t);
    void (*destroyElement)(CCConcurrentIndexMap, const void *, size_t);
    _Bool (*setElement)(CCConcurrentIndexMap, const void *, size_t, const void *, void *);
    _Bool (*compareAndSwapElement)(CCConcurrentIndexMap, const void *, size_t, const void *, const void *);
    _Bool (*appendElement)(CCConcurrentIndexMap, const void *, size_t *, size_t, const void *, void **);
} CCConcurrentIndexMapAtomicOperation;

typedef struct CCConcurrentIndexMapInfo {
    CCAllocatorType allocator;
    size_t size, chunkSize;
    _Atomic(CCConcurrentIndexMapDataPointer) pointer;
    CCConcurrentGarbageCollector gc;
} CCConcurrentIndexMapInfo;

#define CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE_SIZE(x) (x <= 8 ? (x <= 4 ? (x <= 2 ? (x <= 1 ? 1 : 2) : 4) : 8) : 16)
#define CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE(x) \
typedef struct { uint8_t e[x - 1]; } CCConcurrentIndexMapAtomicElementType##x; \
typedef struct { CCConcurrentIndexMapAtomicElementType##x element; uint8_t set; uint8_t pad[CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE_SIZE(x) - x]; } CCConcurrentIndexMapAtomicType##x; \
_Static_assert(sizeof(CCConcurrentIndexMapAtomicType##x) == CC_CONCURRENT_INDEX_MAP_ATOMIC_TYPE_SIZE(x), "CCConcurrentIndexMapAtomicType"#x " should be padded to a power of 2 size"); \
static _Bool CCConcurrentIndexMapAtomicInitElement##x(CCConcurrentIndexMap IndexMap, void *Data, size_t Index, const void *Element) \
{ \
    atomic_init(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], Element ? ((CCConcurrentIndexMapAtomicType##x){ .set = TRUE, .element = *(CCConcurrentIndexMapAtomicElementType##x*)Element }) : ((CCConcurrentIndexMapAtomicType##x){ .set = FALSE })); \
    return TRUE; \
} \
static void CCConcurrentIndexMapAtomicCopyElement##x(void *Data, size_t Index, const void *SrcData, size_t SrcIndex) \
{ \
    CCConcurrentIndexMapAtomicType##x Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)SrcData)[SrcIndex], memory_order_relaxed); \
    atomic_store_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], Value, memory_order_relaxed); \
} \
static _Bool CCConcurrentIndexMapAtomicGetElement##x(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index, void *Out) \
{ \
    CCConcurrentIndexMapAtomicType##x Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], memory_order_relaxed); \
    if ((Value.set) && (Out)) *(CCConcurrentIndexMapAtomicElementType##x*)Out = Value.element; \
    return Value.set; \
} \
static _Bool CCConcurrentIndexMapAtomicRemoveElement##x(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index) \
{ \
    CCConcurrentIndexMapAtomicType##x Value = atomic_exchange_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], ((CCConcurrentIndexMapAtomicType##x){ .set = FALSE }), memory_order_relaxed); \
    return Value.set; \
} \
static void CCConcurrentIndexMapAtomicDestroyElement##x(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index) \
{ \
} \
static _Bool CCConcurrentIndexMapAtomicSetElement##x(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index, const void *New, void *Out) \
{ \
    CCConcurrentIndexMapAtomicType##x Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], memory_order_relaxed); \
    if (!Value.set) return FALSE; \
    Value = atomic_exchange_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], ((CCConcurrentIndexMapAtomicType##x){ .set = TRUE, .element = *(CCConcurrentIndexMapAtomicElementType##x*)New }), memory_order_relaxed); \
    if ((Value.set) && (Out)) *(CCConcurrentIndexMapAtomicElementType##x*)Out = Value.element; \
    return Value.set; \
} \
static _Bool CCConcurrentIndexMapAtomicCompareAndSwapElement##x(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index, const void *New, const void *Match) \
{ \
    return atomic_compare_exchange_strong_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[Index], &((CCConcurrentIndexMapAtomicType##x){ .set = TRUE, .element = *(CCConcurrentIndexMapAtomicElementType##x*)Match }), ((CCConcurrentIndexMapAtomicType##x){ .set = TRUE, .element = *(CCConcurrentIndexMapAtomicElementType##x*)New }), memory_order_relaxed, memory_order_relaxed); \
} \
static _Bool CCConcurrentIndexMapAtomicAppendElement##x(CCConcurrentIndexMap IndexMap, const void *Data, size_t *Index, size_t MaxCount, const void *New, void **State) \
{ \
    for ( ; *Index < MaxCount; (*Index)++) \
    { \
        CCConcurrentIndexMapAtomicType##x Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[*Index], memory_order_relaxed); \
        if (!Value.set) \
        { \
            if (atomic_compare_exchange_strong_explicit(&((_Atomic(CCConcurrentIndexMapAtomicType##x)*)Data)[*Index], &Value, ((CCConcurrentIndexMapAtomicType##x){ .set = TRUE, .element = *(CCConcurrentIndexMapAtomicElementType##x*)New }), memory_order_relaxed, memory_order_relaxed)) return TRUE; \
        } \
    } \
    return FALSE; \
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
} CCConcurrentIndexMapAtomicTypePtr;

static _Bool CCConcurrentIndexMapAtomicInitElementPtr(CCConcurrentIndexMap IndexMap, void *Data, size_t Index, const void *New)
{
    if (New)
    {
        void *Element = CCMalloc(IndexMap->allocator, IndexMap->size, NULL, CC_DEFAULT_ERROR_CALLBACK);
        if (!Element) return FALSE;
        
        memcpy(Element, New, IndexMap->size);
        
        atomic_init(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], ((CCConcurrentIndexMapAtomicTypePtr){ .ptr = Element }));
    }
    
    else atomic_init(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], ((CCConcurrentIndexMapAtomicTypePtr){ .ptr = NULL }));
    
    return TRUE;
}

static void CCConcurrentIndexMapAtomicCopyElementPtr(void *Data, size_t Index, const void *SrcData, size_t SrcIndex)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)SrcData)[SrcIndex], memory_order_relaxed);
    CCRetain(Value.ptr);
    
    atomic_store_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], Value, memory_order_relaxed);
}

static _Bool CCConcurrentIndexMapAtomicGetElementPtr(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index, void *Out)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], memory_order_relaxed);
    if ((Value.ptr) && (Out)) memcpy(Out, Value.ptr, IndexMap->size);
    return Value.ptr;
}

static _Bool CCConcurrentIndexMapAtomicRemoveElementPtr(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_exchange_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], ((CCConcurrentIndexMapAtomicTypePtr){ .ptr = NULL }), memory_order_relaxed);
    
    if (Value.ptr) CCConcurrentGarbageCollectorManage(IndexMap->gc, Value.ptr, CCFree);
    
    return Value.ptr;
}

static void CCConcurrentIndexMapAtomicDestroyElementPtr(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], memory_order_relaxed);
    
    if (Value.ptr) CCFree(Value.ptr);
}

static _Bool CCConcurrentIndexMapAtomicSetElementPtr(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index, const void *New, void *Out)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], memory_order_relaxed);
    if (!Value.ptr) return FALSE;
    
    void *Element = CCMalloc(IndexMap->allocator, IndexMap->size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (!Element) return FALSE;
    
    memcpy(Element, New, IndexMap->size);
    
    Value = atomic_exchange_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], ((CCConcurrentIndexMapAtomicTypePtr){ .ptr = Element }), memory_order_release);
    
    if (Value.ptr)
    {
        if (Out) memcpy(Out, Value.ptr, IndexMap->size);
        CCConcurrentGarbageCollectorManage(IndexMap->gc, Value.ptr, CCFree);
    }
    
    return Value.ptr;
}

static _Bool CCConcurrentIndexMapAtomicCompareAndSwapElementPtr(CCConcurrentIndexMap IndexMap, const void *Data, size_t Index, const void *New, const void *Match)
{
    CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], memory_order_relaxed);
    if (!Value.ptr) return FALSE;
    
    void *Element = CCMalloc(IndexMap->allocator, IndexMap->size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (!Element) return FALSE;
    
    memcpy(Element, New, IndexMap->size);
    
    _Bool Success = FALSE;
    for ( ; ; )
    {
        if (!memcmp(Value.ptr, Match, IndexMap->size))
        {
            Success = atomic_compare_exchange_strong_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[Index], &Value, ((CCConcurrentIndexMapAtomicTypePtr){ .ptr = Element }), memory_order_relaxed, memory_order_relaxed);
            
            if (Success)
            {
                CCConcurrentGarbageCollectorManage(IndexMap->gc, Value.ptr, CCFree);
                break;
            }
        }
        
        else
        {
            CCFree(Element);
            break;
        }
    }
    
    return Success;
}

static _Bool CCConcurrentIndexMapAtomicAppendElementPtr(CCConcurrentIndexMap IndexMap, const void *Data, size_t *Index, size_t MaxCount, const void *New, void **State)
{
    void *Element = *State;
    if (!Element)
    {
        Element = CCMalloc(IndexMap->allocator, IndexMap->size, NULL, CC_DEFAULT_ERROR_CALLBACK);
        if (!Element)
        {
            *Index = SIZE_MAX;
            return FALSE;
        }
        
        memcpy(Element, New, IndexMap->size);

        *State = Element;
    }
    
    for ( ; *Index < MaxCount; (*Index)++)
    {
        CCConcurrentIndexMapAtomicTypePtr Value = atomic_load_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[*Index], memory_order_relaxed);
        if (!Value.ptr)
        {
            if (atomic_compare_exchange_strong_explicit(&((_Atomic(CCConcurrentIndexMapAtomicTypePtr)*)Data)[*Index], &Value, ((CCConcurrentIndexMapAtomicTypePtr){ .ptr = Element }), memory_order_release, memory_order_relaxed)) return TRUE;
        }
    }
    
    return FALSE;
}

#define CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(x) \
{ \
    .size = sizeof(_Atomic(CCConcurrentIndexMapAtomicType##x)), \
    .initElement = CCConcurrentIndexMapAtomicInitElement##x, \
    .copyElement = CCConcurrentIndexMapAtomicCopyElement##x, \
    .getElement = CCConcurrentIndexMapAtomicGetElement##x, \
    .removeElement = CCConcurrentIndexMapAtomicRemoveElement##x, \
    .destroyElement = CCConcurrentIndexMapAtomicDestroyElement##x, \
    .setElement = CCConcurrentIndexMapAtomicSetElement##x, \
    .compareAndSwapElement = CCConcurrentIndexMapAtomicCompareAndSwapElement##x, \
    .appendElement = CCConcurrentIndexMapAtomicAppendElement##x \
}

static CCConcurrentIndexMapAtomicOperation CCConcurrentIndexMapAtomicOperations[] = {
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(1),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(2),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(3),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(4),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(5),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(6),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(7),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(8),
#if CC_HARDWARE_PTR_64
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(9),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(10),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(11),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(12),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(13),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(14),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(15),
    CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(16)
#endif
};

static CCConcurrentIndexMapAtomicOperation CCConcurrentIndexMapAtomicPtrOperation = CC_CONCURRENT_INDEX_MAP_ATOMIC_OPERATION(Ptr);

static inline _Bool CCConcurrentIndexMapRequiresExternalStorage(size_t ElementSize)
{
    return ElementSize >= (sizeof(CCConcurrentIndexMapAtomicOperations) / sizeof(typeof(*CCConcurrentIndexMapAtomicOperations)));
}

static inline const CCConcurrentIndexMapAtomicOperation *CCConcurrentIndexMapGetAtomicOperation(size_t ElementSize)
{
    return CCConcurrentIndexMapRequiresExternalStorage(ElementSize) ? &CCConcurrentIndexMapAtomicPtrOperation : &CCConcurrentIndexMapAtomicOperations[ElementSize];
}

static inline size_t CCConcurrentIndexMapGetMaxCount(CCConcurrentIndexMap IndexMap, size_t Count)
{
    return ((Count / IndexMap->chunkSize) + ((Count % IndexMap->chunkSize) || (!Count))) * IndexMap->chunkSize;
}

static void CCConcurrentIndexMapDestructor(CCConcurrentIndexMap IndexMap)
{
    CCConcurrentIndexMapDataPointer Pointer = atomic_load(&IndexMap->pointer);
    CCFree(Pointer.data);
    
    CCConcurrentGarbageCollectorDestroy(IndexMap->gc);
}

static void CleanupElements(CCConcurrentIndexMapData *Data)
{
    const CCConcurrentIndexMapAtomicOperation *Atomic =  CCConcurrentIndexMapGetAtomicOperation(Data->indexMap->size);
    for (size_t Loop = 0, MaxCount = CCConcurrentIndexMapGetMaxCount(Data->indexMap, atomic_load_explicit(&Data->count, memory_order_relaxed)); Loop < MaxCount; Loop++) Atomic->destroyElement(Data->indexMap, Data->buffer, Loop);
}

CCConcurrentIndexMap CCConcurrentIndexMapCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, CCConcurrentGarbageCollector GC)
{
    CCAssertLog(ChunkSize >= 1, "ChunkSize must be at least 1");
    
    CCConcurrentIndexMap IndexMap = CCMalloc(Allocator, sizeof(CCConcurrentIndexMapInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (IndexMap)
    {
        const CCConcurrentIndexMapAtomicOperation *Atomic = CCConcurrentIndexMapGetAtomicOperation(ElementSize);
        CCConcurrentIndexMapData *Data = CCMalloc(Allocator, sizeof(CCConcurrentIndexMapData) + (ChunkSize * Atomic->size), NULL, CC_DEFAULT_ERROR_CALLBACK);
        
        Data->indexMap = IndexMap;
        atomic_init(&Data->count, 0);
        for (size_t Loop = 0; Loop < ChunkSize; Loop++) Atomic->initElement(IndexMap, Data->buffer, Loop, NULL);
        
        CCMemorySetDestructor(Data, (CCMemoryDestructorCallback)CleanupElements);
        
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
            })),
            .gc = GC
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
    
    return IndexMap->size;
}

_Bool CCConcurrentIndexMapGetElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, void *Element)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
    const size_t Count = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
    const size_t MaxCount = CCConcurrentIndexMapGetMaxCount(IndexMap, Count);
    
    const _Bool Exists = Index < MaxCount ? CCConcurrentIndexMapGetAtomicOperation(IndexMap->size)->getElement(IndexMap, Pointer.data->buffer, Index, Element) : FALSE;
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Exists;
}

_Bool CCConcurrentIndexMapReplaceElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, const void *Element, void *ReplacedElement)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    CCAssertLog(Element, "Element must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
    CCConcurrentIndexMapDataPointer Pointer;
    do {
        Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
    } while (!atomic_compare_exchange_weak_explicit(&IndexMap->pointer, &Pointer, ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify + 1, .mutate = Pointer.mutate, .data = Pointer.data }), memory_order_acquire, memory_order_relaxed));
#else
    atomic_fetch_add_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->modify, 1, memory_order_acquire);
    
    CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
#endif
    
    const size_t Count = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
    const size_t MaxCount = CCConcurrentIndexMapGetMaxCount(IndexMap, Count);
    
    const _Bool Exists = Index < MaxCount ? CCConcurrentIndexMapGetAtomicOperation(IndexMap->size)->setElement(IndexMap, Pointer.data->buffer, Index, Element, ReplacedElement) : FALSE;
    
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
    if (!atomic_compare_exchange_strong_explicit(&IndexMap->pointer, &((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify + 1, .mutate = Pointer.mutate, .data = Pointer.data }), ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify, .mutate = Pointer.mutate + Exists, .data = Pointer.data }), memory_order_release, memory_order_relaxed))
    {
        do {
            Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
        } while (!atomic_compare_exchange_weak_explicit(&IndexMap->pointer, &Pointer, ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify - 1, .mutate = Pointer.mutate + Exists, .data = Pointer.data }), memory_order_release, memory_order_relaxed));
    }
#else
    if (Exists) atomic_fetch_add_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->mutate, 1, memory_order_relaxed);
    atomic_fetch_sub_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->modify, 1, memory_order_release);
#endif
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Exists;
}

_Bool CCConcurrentIndexMapReplaceExactElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, const void *Element, const void *Match)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    CCAssertLog(Element, "Element must not be null");
    CCAssertLog(Match, "Match must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
    CCConcurrentIndexMapDataPointer Pointer;
    do {
        Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
    } while (!atomic_compare_exchange_weak_explicit(&IndexMap->pointer, &Pointer, ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify + 1, .mutate = Pointer.mutate, .data = Pointer.data }), memory_order_acquire, memory_order_relaxed));
#else
    atomic_fetch_add_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->modify, 1, memory_order_acquire);
    
    CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
#endif
    
    const size_t Count = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
    const size_t MaxCount = CCConcurrentIndexMapGetMaxCount(IndexMap, Count);
    
    const _Bool Exists = Index < MaxCount ? CCConcurrentIndexMapGetAtomicOperation(IndexMap->size)->compareAndSwapElement(IndexMap, Pointer.data->buffer, Index, Element, Match) : FALSE;
    
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
    if (!atomic_compare_exchange_strong_explicit(&IndexMap->pointer, &((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify + 1, .mutate = Pointer.mutate, .data = Pointer.data }), ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify, .mutate = Pointer.mutate + Exists, .data = Pointer.data }), memory_order_release, memory_order_relaxed))
    {
        do {
            Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
        } while (!atomic_compare_exchange_weak_explicit(&IndexMap->pointer, &Pointer, ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify - 1, .mutate = Pointer.mutate + Exists, .data = Pointer.data }), memory_order_release, memory_order_relaxed));
    }
#else
    if (Exists) atomic_fetch_add_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->mutate, 1, memory_order_relaxed);
    atomic_fetch_sub_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->modify, 1, memory_order_release);
#endif
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Exists;
}

static CCConcurrentIndexMapData *CCConcurrentIndexMapResize(CCConcurrentIndexMap IndexMap, CCConcurrentIndexMapData *PrevData, size_t Count, size_t MaxCount, size_t SkipIndex, size_t ExtraIndex)
{
    const CCConcurrentIndexMapAtomicOperation *Atomic = CCConcurrentIndexMapGetAtomicOperation(IndexMap->size);
    CCConcurrentIndexMapData *Data = CCMalloc(IndexMap->allocator, sizeof(CCConcurrentIndexMapData) + (MaxCount * Atomic->size), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (Data)
    {
        Data->indexMap = IndexMap;
        atomic_init(&Data->count, Count + (SkipIndex == SIZE_MAX ? 1 : 0));
        for (size_t Loop = 0; Loop < Count; Loop++) Atomic->copyElement(Data->buffer, (Loop < ExtraIndex ? Loop : Loop + 1), PrevData->buffer, (Loop < SkipIndex ? Loop : Loop + 1));
        for (size_t Loop = (Count < ExtraIndex ? Count : Count + 1); Loop < MaxCount; Loop++) Atomic->initElement(IndexMap, Data->buffer, Loop, NULL);
        
        CCMemorySetDestructor(Data, (CCMemoryDestructorCallback)CleanupElements);
    }
    
    return Data;
}

size_t CCConcurrentIndexMapAppendElement(CCConcurrentIndexMap IndexMap, const void *Element)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    CCAssertLog(Element, "Element must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    const CCConcurrentIndexMapAtomicOperation *Atomic =  CCConcurrentIndexMapGetAtomicOperation(IndexMap->size);
    
    size_t Index;
    void *State = NULL;
    for ( ; ; )
    {
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
        CCConcurrentIndexMapDataPointer Pointer;
        do {
            Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
        } while (!atomic_compare_exchange_weak_explicit(&IndexMap->pointer, &Pointer, ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify + 1, .mutate = Pointer.mutate, .data = Pointer.data }), memory_order_acquire, memory_order_relaxed));
#else
        atomic_fetch_add_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->modify, 1, memory_order_acquire);
        
        CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
#endif
        
        Index = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
        const size_t MaxCount = CCConcurrentIndexMapGetMaxCount(IndexMap, Index);
        
        const _Bool Success = Atomic->appendElement(IndexMap, Pointer.data->buffer, &Index, MaxCount, Element, &State);
        if (Success)
        {
            atomic_fetch_add_explicit(&Pointer.data->count, 1, memory_order_relaxed);
            
#if !CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
            atomic_fetch_add_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->mutate, 1, memory_order_relaxed);
#endif
            
            State = NULL;
        }
        
#if CC_CONCURRENT_INDEX_MAP_STRICT_COMPLIANCE
        if (!atomic_compare_exchange_strong_explicit(&IndexMap->pointer, &((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify + 1, .mutate = Pointer.mutate, .data = Pointer.data }), ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify, .mutate = Pointer.mutate + Success, .data = Pointer.data }), memory_order_release, memory_order_relaxed))
        {
            do {
                Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
            } while (!atomic_compare_exchange_weak_explicit(&IndexMap->pointer, &Pointer, ((CCConcurrentIndexMapDataPointer){ .modify = Pointer.modify - 1, .mutate = Pointer.mutate + Success, .data = Pointer.data }), memory_order_release, memory_order_relaxed));
        }
#else
        atomic_fetch_sub_explicit(&((CCConcurrentIndexMapDataPointer*)&IndexMap->pointer)->modify, 1, memory_order_release);
#endif
        
        if ((Success) || (CC_UNLIKELY(Index == SIZE_MAX))) break;
        
        if (Index == atomic_load_explicit(&Pointer.data->count, memory_order_relaxed))
        {
            CCConcurrentIndexMapData *Data = CCConcurrentIndexMapResize(IndexMap, Pointer.data, Index, MaxCount + IndexMap->chunkSize, SIZE_MAX, SIZE_MAX);
            if ((!Data) || (!Atomic->initElement(IndexMap, Data->buffer, Index, Element)))
            {
                if (Data)
                {
                    for (size_t Loop = 0, Count = atomic_load_explicit(&Data->count, memory_order_relaxed); Loop < Count; Loop++) Atomic->removeElement(IndexMap, Data->buffer, Loop);
                    CCFree(Data);
                }
                
                Index = SIZE_MAX;
                break;
            }
            
            else if (atomic_compare_exchange_strong_explicit(&IndexMap->pointer, &((CCConcurrentIndexMapDataPointer){ .modify = 0, .mutate = Pointer.mutate, .data = Pointer.data }), ((CCConcurrentIndexMapDataPointer){ .modify = 0, .mutate = Pointer.mutate + 1, .data = Data }), memory_order_release, memory_order_relaxed))
            {
                CCConcurrentGarbageCollectorManage(IndexMap->gc, Pointer.data, CCFree);
                break;
            }
            
            else CCFree(Data);
        }
    }
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    if (State) CCFree(State);
    
    return Index;
}

_Bool CCConcurrentIndexMapRemoveElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, void *RemovedElement)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    _Bool Removed = FALSE;
    for (const CCConcurrentIndexMapAtomicOperation *Atomic =  CCConcurrentIndexMapGetAtomicOperation(IndexMap->size); ; )
    {
        CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
        const size_t Count = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
        
        if ((Index >= Count) || (!Count)) break;
        
        CCConcurrentIndexMapData *Data = CCConcurrentIndexMapResize(IndexMap, Pointer.data, Count - 1, CCConcurrentIndexMapGetMaxCount(IndexMap, Count - 1), Index, SIZE_MAX);
        if (Data)
        {
            if (atomic_compare_exchange_strong_explicit(&IndexMap->pointer, &((CCConcurrentIndexMapDataPointer){ .modify = 0, .mutate = Pointer.mutate, .data = Pointer.data }), ((CCConcurrentIndexMapDataPointer){ .modify = 0, .mutate = Pointer.mutate + 1, .data = Data }), memory_order_release, memory_order_relaxed))
            {
                Atomic->getElement(IndexMap, Pointer.data->buffer, Index, RemovedElement);
                CCConcurrentGarbageCollectorManage(IndexMap->gc, Pointer.data, CCFree);
                
                Removed = TRUE;
                break;
            }
    
            else CCFree(Data);
        }
    }
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Removed;
}

_Bool CCConcurrentIndexMapInsertElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, void *Element)
{
    CCAssertLog(IndexMap, "IndexMap must not be null");
    
    CCConcurrentGarbageCollectorBegin(IndexMap->gc);
    
    _Bool Inserted = FALSE;
    for (const CCConcurrentIndexMapAtomicOperation *Atomic =  CCConcurrentIndexMapGetAtomicOperation(IndexMap->size); ; )
    {
        CCConcurrentIndexMapDataPointer Pointer = atomic_load_explicit(&IndexMap->pointer, memory_order_relaxed);
        const size_t Count = atomic_load_explicit(&Pointer.data->count, memory_order_relaxed);
        
        if ((Index >= Count) || (!Count)) break;
        
       CCConcurrentIndexMapData *Data = CCConcurrentIndexMapResize(IndexMap, Pointer.data, Count, CCConcurrentIndexMapGetMaxCount(IndexMap, Count + 1), SIZE_MAX, Index);
        if (Data)
        {
            if ((Atomic->initElement(IndexMap, Data->buffer, Index, Element)) && (atomic_compare_exchange_strong_explicit(&IndexMap->pointer, &((CCConcurrentIndexMapDataPointer){ .modify = 0, .mutate = Pointer.mutate, .data = Pointer.data }), ((CCConcurrentIndexMapDataPointer){ .modify = 0, .mutate = Pointer.mutate + 1, .data = Data }), memory_order_release, memory_order_relaxed)))
            {
                CCConcurrentGarbageCollectorManage(IndexMap->gc, Pointer.data, CCFree);
                
                Inserted = TRUE;
                break;
            }
            
            else CCFree(Data);
        }
    }
    
    CCConcurrentGarbageCollectorEnd(IndexMap->gc);
    
    return Inserted;
}
