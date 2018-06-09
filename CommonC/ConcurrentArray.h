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

#ifndef CommonC_ConcurrentArray_h
#define CommonC_ConcurrentArray_h

#include <CommonC/Base.h>
#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>
#include <CommonC/ConcurrentGarbageCollector.h>


/*!
 * @brief The concurrent array.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentArrayInfo *CCConcurrentArray;

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent array.
 * @description This array allows for many producer-consumer access.
 * @param Allocator The allocator to be used for the allocation.
 * @param ElementSize The size of the data elements.
 * @param ChunkSize The number of elements to fit with each allocation. Must be at least 1.
 * @param GC The garbage collector to be used in this queue.
 * @return An array, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentArray CCConcurrentArrayCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, CCConcurrentGarbageCollector CC_OWN(GC));

/*!
 * @brief Destroy an array.
 * @param Array The array to be destroyed.
 */
void CCConcurrentArrayDestroy(CCConcurrentArray CC_DESTROY(Array));

#pragma mark - Insertions/Deletions
/*!
 * @brief Appends the element to the end of the array.
 * @description Increases the array's count by 1.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Array The array to append the element to.
 * @param Element The pointer to the element to be copied to the end of the array. This must not
 *        be NULL.
 *
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCConcurrentArrayAppendElement(CCConcurrentArray Array, const void *Element);

/*!
 * @brief Replace element at index with new element.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Array The array to replace an element of.
 * @param Index The position of the element to be replaced.
 * @param Element The replacement element. This must not be NULL.
 * @param ReplacedElement A pointer to where the old value that was replaced can be written to. If NULL
 *        this will be ignored.
 * @return Whether or not an element was replaced at the given index.
 */
_Bool CCConcurrentArrayReplaceElementAtIndex(CCConcurrentArray Array, size_t Index, const void *Element, void *ReplacedElement);

/*!
 * @brief Replace element at index with new element if the existing element matches.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Array The array to replace an element of.
 * @param Index The position of the element to be replaced.
 * @param Element The replacement element. This must not be NULL.
 * @param Match The value the element currently needs to be in order to perform the replace. This
 *        must not be NULL.
 *
 * @return Whether or not an element was replaced at the given index.
 */
_Bool CCConcurrentArrayReplaceExactElementAtIndex(CCConcurrentArray Array, size_t Index, const void *Element, const void *Match);

/*!
 * @brief Removes an element at a given index from the array.
 * @description Decreases the array's count by 1.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Array The array to remove an element from.
 * @param Index The position of the element to be removed.
 * @param RemovedElement A pointer to where the old value that was removed can be written to. If NULL
 *        this will be ignored.
 *
 * @return Whether or not an element was removed at the given index.
 */
_Bool CCConcurrentArrayRemoveElementAtIndex(CCConcurrentArray Array, size_t Index, void *RemovedElement);

/*!
 * @brief Insert an element at a given index into the array.
 * @description Increases the array's count by 1.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Array The array to insert the element into.
 * @param Index The position in the array for the element to be inserted.
 * @param Element The pointer to the element to be copied to the give position in the array. This must
 *        not be NULL.
 *
 * @return Whether or not an element was inserted at the given index.
 */
_Bool CCConcurrentArrayInsertElementAtIndex(CCConcurrentArray Array, size_t Index, void *Element);

#pragma mark - Query Info
/*!
 * @brief Get the current number of elements in the array.
 * @note This should only be used as a rough indicator of the current number of elements if calling it
 *       during mutation operations on other threads.
 *
 * @param Array The array to get the count of.
 * @return The number of elements.
 */
size_t CCConcurrentArrayGetCount(CCConcurrentArray Array);

/*!
 * @brief Get the element size of the array.
 * @param Array The array to get the element size of.
 * @return The size of elements.
 */
size_t CCConcurrentArrayGetElementSize(CCConcurrentArray Array);

/*!
 * @brief Get the element at index.
 * @param Array The array to get the element of.
 * @param Index The index of the element.
 * @param Element A pointer to where the value should be written to. If NULL this will be ignored.
 * @return Whether or not an element existed at the given index.
 */
_Bool CCConcurrentArrayGetElementAtIndex(CCConcurrentArray Array, size_t Index, void *Element);

#endif
