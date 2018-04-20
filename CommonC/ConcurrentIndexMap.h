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

#ifndef CommonC_ConcurrentIndexMap_h
#define CommonC_ConcurrentIndexMap_h

/*
 Lock-free index map. This is an array (O(1) lookup) that has wait-free guarantees for
 indexed lookups and replacements. While it supports all the common array conventions,
 it can however block resize operations. To avoid this issue it is recommended that you
 use it with a large chunk size (so resize requests are more spread out or ideally
 never occur). But this doesn't completely avoid the issue, if a thread dies during a
 mutation operation, any future thread that attempts to make a resize will block
 indefinitely. If you need a concurrent array without this limitation, use a
 CCConcurrentArray. However in doing so you lose the wait-free guarantees for
 replacement operations, but the structure is completely lock-free.
 
 Allows for many producer-consumer access.
 */

#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>
#include <CommonC/ConcurrentGarbageCollector.h>
#include <stdint.h>
#include <stddef.h>


/*!
 * @brief The concurrent index map.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentIndexMapInfo *CCConcurrentIndexMap;

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent index map.
 * @description This index map allows for many producer-consumer access.
 * @param Allocator The allocator to be used for the allocation.
 * @param ElementSize The size of the data elements.
 * @param ChunkSize The number of elements to fit with each allocation. Must be at least 1.
 * @param GC The garbage collector to be used in this queue.
 * @return An index map, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentIndexMap CCConcurrentIndexMapCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, CCConcurrentGarbageCollector CC_OWN(GC));

/*!
 * @brief Destroy an index map.
 * @param IndexMap The index map to be destroyed.
 */
void CCConcurrentIndexMapDestroy(CCConcurrentIndexMap CC_DESTROY(IndexMap));

#pragma mark - Insertions/Deletions
/*!
 * @brief Appends the element to the end of the index map.
 * @description Increases the index map's count by 1.
 * @warning The size of element must be the same size as specified in the index map creation.
 * @param IndexMap The index map to append the element to.
 * @param Element The pointer to the element to be copied to the end of the index map. If NULL it
 *        will create an uninitialized element.
 *
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCConcurrentIndexMapAppendElement(CCConcurrentIndexMap IndexMap, const void *Element);

/*!
 * @brief Replace element at index with new element.
 * @warning The size of element must be the same size as specified in the index map creation.
 * @param IndexMap The index map to replace an element of.
 * @param Index The position of the element to be replaced.
 * @param Element The replacement element. This must not be NULL.
 * @param ReplacedElement A pointer to where the old value that was replaced can be written to. If NULL
 *        this will be ignored.
 * @return Whether or not an element was replaced at the given index.
 */
_Bool CCConcurrentIndexMapReplaceElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, const void *Element, void *ReplacedElement);

#pragma mark - Query Info
/*!
 * @brief Get the current number of elements in the index map.
 * @note This should only be used as a rough indicator of the current number of elements if calling it
 *       during mutation operations on other threads.
 *
 * @param IndexMap The index map to get the count of.
 * @return The number of elements.
 */
size_t CCConcurrentIndexMapGetCount(CCConcurrentIndexMap IndexMap);

/*!
 * @brief Get the element size of the index map.
 * @param IndexMap The index map to get the element size of.
 * @return The size of elements.
 */
size_t CCConcurrentIndexMapGetElementSize(CCConcurrentIndexMap IndexMap);

/*!
 * @brief Get the element at index.
 * @param IndexMap The index map to get the element of.
 * @param Index The index of the element.
 * @param Element A pointer to where the value should be written to. If NULL this will be ignored.
 * @return Whether or not an element existed at the given index.
 */
_Bool CCConcurrentIndexMapGetElementAtIndex(CCConcurrentIndexMap IndexMap, size_t Index, void *Element);

#endif
