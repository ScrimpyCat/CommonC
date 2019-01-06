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

#ifndef CommonC_ConcurrentIDPool_h
#define CommonC_ConcurrentIDPool_h

/*
 Lock-free ID creation. This is a fixed size ID pool that is assigned temporarily on
 request. If the pool has IDs available then retrieving one will be (O(n + n/8) on the
 successful worst case lookup). If the pool has been exhausted then depending on the
 type of retrieval (blocking vs non-blocking) it will either fail or wait until an ID
 is recycled. As long as the pool hasn't been exhausted, the calls are guaranteed to
 return with an ID. This ID creation pattern is not suited for small pools where IDs
 are not recycled frequently, but lots of threads are attempting to retrieve an ID,
 as this will result in many threads being starved. Nor is it suited for situations
 where a large number of IDs needs to be distributed, as this will result in retrieval
 time taking too long (if those IDs are not being recycled frequently enough). Where this
 is suited is when you have a known amount of possible accessors, and that amount is
 quite small. Those accessors can then retrieve or recycle as frequently or infrequently
 as they want.
 
 Allows for many producer-consumer access.
 */

#include <CommonC/Base.h>
#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>


/*!
 * @brief The concurrent ID pool.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentIDPoolInfo *CCConcurrentIDPool;

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent ID pool.
 * @description This ID pool allows for many producer-consumer access.
 * @param Allocator The allocator to be used for the allocation.
 * @param PoolSize The number of IDs that will be allocated. The base ID will start 0, and go up
 *                 to (PoolSize - 1). Due to this if the PoolSize = 2^8 then the ID
 *                 will be one that can fit within an uint8_t.
 *
 * @return An ID pool, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentIDPool CCConcurrentIDPoolCreate(CCAllocatorType Allocator, size_t PoolSize);

/*!
 * @brief Destroy an ID pool.
 * @param IDPool The ID pool to be destroyed.
 */
void CCConcurrentIDPoolDestroy(CCConcurrentIDPool CC_DESTROY(IDPool));

#pragma mark - Retrieve/Recycle
/*!
 * @brief Obtain an ID from the ID pool.
 * @performance This operation is lock-free but will block whilst the ID pool is exhausted.
 * @param IDPool The ID pool to get the ID from.
 * @return The ID that has been assigned. This ID must be recycled in order for it to become available
 *         again.
 */
size_t CCConcurrentIDPoolAssign(CCConcurrentIDPool IDPool);

/*!
 * @brief Try obtain an ID from the ID pool.
 * @description This will return if the ID pool has been exhausted
 * @performance This operation is lock-free and has a worst case of O(n + n/8).
 * @param IDPool The ID pool to get the ID from.
 * @param ID The pointer to where the assigned ID should be stored. This ID must be recycled in order
 *           for it to become available again. This must not be NULL.
 *
 * @return Whether an ID was assigned (TRUE), or not (FALSE).
 */
_Bool CCConcurrentIDPoolTryAssign(CCConcurrentIDPool IDPool, size_t *ID);

/*!
 * @brief Recycle an ID back into the ID pool.
 * @performance Wait-free O(1) operation.
 * @param IDPool The ID pool to recycle the ID to.
 * @param ID The ID to be recycled.
 */
void CCConcurrentIDPoolRecycle(CCConcurrentIDPool IDPool, size_t ID);

#pragma mark - Info

/*!
 * @brief Get the size of the pool.
 * @description The size - 1 will be the maximum ID that can be returned by this pool.
 * @param IDPool The ID pool to get the size of.
 * @return The size of this pool.
 */
size_t CCConcurrentIDPoolGetSize(CCConcurrentIDPool IDPool);

#endif
