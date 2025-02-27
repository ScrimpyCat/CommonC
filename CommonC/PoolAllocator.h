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

#ifndef CommonC_PoolAllocator_h
#define CommonC_PoolAllocator_h

#include <CommonC/Extensions.h>
#include <CommonC/Allocator.h>
#include <CommonC/Assertion.h>
#include <CommonC/Alignment.h>

typedef struct CCPoolAllocatorInfo {
    size_t blockSize;
    size_t count, max;
    void *pool;
    struct {
        size_t count;
        size_t *indexes;
    } available;
} CCPoolAllocatorInfo;

/*!
 * @brief The pool allocator.
 * @description Allows @b CCRetain.
 */
typedef struct CCPoolAllocatorInfo *CCPoolAllocator;

typedef struct {
    CCPoolAllocator pool;
    size_t index;
} CCPoolAllocatorRef;

typedef struct {
    CCPoolAllocatorRef ref;
    CCAllocatorHeader header;
} CCPoolAllocatorHeader;

/*!
 * @define CC_POOL_ALLOCATOR_CREATE
 * @abstract Convenient macro to create a temporary (allocation free) @b CCPoolAllocator.
 * @discussion If used globally the pool allocator will last for the life of the program, however if used within
 *             a function it will last for the entirety of the local scope.
 *
 * @param size The size of the allocations from the pool.
 * @param align The alignment of the allocations from the pool.
 * @param maximum The maximum number of allocations in the pool.
 */
#define CC_POOL_ALLOCATOR_CREATE(size, align, maximum) \
((CCPoolAllocator)&(struct { \
    CCAllocatorHeader header; \
    CCPoolAllocatorInfo info; \
}){ \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_NULL_ALLOCATOR.allocator), \
    .info = { \
        .blockSize = CC_ALIGN(size, align), \
        .count = 0, \
        .max = maximum, \
        .pool = (uint8_t*)&(struct { CCPoolAllocatorHeader header; _Alignas(align) uint8_t data[size]; }[maximum]){}[0].data - sizeof(CCPoolAllocatorHeader), \
        .available = { \
            .count = 0, \
            .indexes = (size_t[maximum]){}, \
        } \
    } \
}.info)


/*!
 * @brief Create a pool allocator.
 * @param Allocator The allocator to be used for the pool itself.
 * @param Size The size of the allocations from the pool.
 * @param Alignment The alignment of the allocations from the pool.
 * @param Max The maximum number of allocations in the pool.
 * @return The pool allocator. Must be destroyed to free the memory.
 */
CC_NEW CCPoolAllocator CCPoolAllocatorCreate(CCAllocatorType Allocator, size_t Size, size_t Alignment, size_t Max);

/*!
 * @brief Destroy a pool allocator.
 * @note It's safe to destroy all references to the pool allocator while still maintaining references to allocations
 *       from the pool. The pool will only be destroyed once all allocations have also been freed.
 *
 * @param Pool The pool allocator to be destroyed.
 */
void CCPoolAllocatorDestroy(CCPoolAllocator CC_DESTROY(Pool));

/*!
 * @brief Get the pool index for the allocation.
 * @param Ptr The allocation to get the index of.
 * @return The index in the pool for the allocation.
 */
static CC_FORCE_INLINE size_t CCPoolAllocatorGetIndex(void *Ptr);

/*!
 * @brief Get the pointer to the allocation for a given index in the pool.
 * @param Pool The pool allocator.
 * @param Index The index in the pool to get the pointer to the allocation for. Note the the allocation must exist.
 * @return A pointer to the allocation.
 */
static CC_FORCE_INLINE void *CCPoolAllocatorGetMemory(CCPoolAllocator Pool, size_t Index);

#pragma mark -

static CC_FORCE_INLINE size_t CCPoolAllocatorGetIndex(void *Ptr)
{
    const CCPoolAllocatorHeader *Header = (CCPoolAllocatorHeader*)Ptr - 1;
    
    CCAssertLog(Header->ref.pool, "Unallocated memory");
    
    return Header->ref.index;
}

static CC_FORCE_INLINE void *CCPoolAllocatorGetMemory(CCPoolAllocator Pool, size_t Index)
{
    CCAssertLog(Pool, "Pool must not be null");
    CCAssertLog(Index < Pool->max, "Index must not exceed pool max");
    
    CCPoolAllocatorHeader *Header = (CCPoolAllocatorHeader*)(Pool->pool + (Pool->blockSize * Index));
    
    CCAssertLog(Header->ref.pool, "Unallocated memory");
    
    return &Header->header + 1;
}

#endif
