/*
 *  Copyright (c) 2015, Stefan Johnson
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

/*!
 * @header CCArray
 * CCArray implements a basic dynamic array.
 *
 * It keeps an array of the same sized elements in contiguous memory. And allows for
 * elements to be added or replaced. It does not allow for deletion.
 */

#ifndef CommonC_Array_h
#define CommonC_Array_h

#include <CommonC/Base.h>
#include <CommonC/Container.h>
#include <CommonC/Allocator.h>
#include <CommonC/Assertion.h>
#include <CommonC/Enumerable.h>

typedef struct CCArrayInfo {
    size_t size, chunkSize;
    size_t count;
    void *data;
} CCArrayInfo;

/*!
 * @brief The array.
 * @description Allows @b CCRetain.
 */
typedef struct CCArrayInfo *CCArray;

CC_CONTAINER_DECLARE_PRESET_1(CCArray);

/*!
 * @define CC_ARRAY_DECLARE
 * @abstract Convenient macro to define a @b CCArray type that can be referenced by @b CCArray.
 * @param element The element type.
 */
#define CC_ARRAY_DECLARE(element) CC_CONTAINER_DECLARE(CCArray, element)

/*!
 * @define CC_ARRAY
 * @abstract Convenient macro to define an explicitly typed @b CCArray.
 * @param element The element type.
 */
#define CC_ARRAY(element) CC_CONTAINER(CCArray, element)

/*!
 * @define CCArray
 * @abstract Convenient macro to define an explicitly typed @b CCArray.
 * @description In the case that this macro is conflicting with the standalone @b CCArray type, simply
 *              undefine it and redefine it back to @b CC_ARRAY.
 *
 * @param element The element type.
 */
#define CCArray(element) CC_ARRAY(element)


#pragma mark - Creation/Destruction
/*!
 * @brief Create an array.
 * @param Allocator The allocator to be used for the allocation.
 * @param ElementSize The size of the data elements.
 * @param ChunkSize The number of elements to fit with each allocation. Must be at least 1.
 * @return An empty array, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCArray CCArrayCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize);

/*!
 * @brief Destroy an array.
 * @param Array The array to be destroyed.
 */
void CCArrayDestroy(CCArray CC_DESTROY(Array));


#pragma mark - Insertions/Deletions
/*!
 * @brief Appends the element to the end of the array.
 * @description Increases the array's count by 1.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Array The array to append the element to.
 * @param Element The pointer to the element to be copied to the end of the array. If NULL it
 *        will create an uninitialized element.
 *
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCArrayAppendElement(CCArray Array, const void *Element);

/*!
 * @brief Appends the elements to the end of the array.
 * @description Increases the array's count by the number of elements.
 * @warning The size of the elements must be the same size as specified in the array creation.
 * @param Array The array to append the elements to.
 * @param Elements The pointer to the elements to be copied to the end of the array. If NULL it
 *        will create an uninitialized element.
 *
 * @param Count The number of elements to be appended. Must not be 0.
 * @return The index the first element was added or SIZE_MAX on failure.
 */
size_t CCArrayAppendElements(CCArray Array, const void *Elements, size_t Count);

/*!
 * @brief Replace element at index with new element.
 * @warning The size of element must be the same size as specified in the array creation. And the
 *          Index must not be out of bounds.
 *
 * @param Array The array to replace an element of.
 * @param Index The position of the element to be replaced.
 * @param Element The replacement element. If NULL the operation does nothing.
 */
void CCArrayReplaceElementAtIndex(CCArray Array, size_t Index, const void *Element);

/*!
 * @brief Insert an element at a given index into the array.
 * @description Increases the array's count by 1.
 * @performance The further away from the end of the array the index is, the slower it is. It has
 *              a worst case of O(n).
 *
 * @warning The size of element must be the same size as specified in the array creation. And the
 *          Index must not be out of bounds
 *
 * @param Array The array to insert the element into.
 * @param Index The position in the array for the element to be inserted.
 * @param Element The pointer to the element to be copied to the give position in the array. If NULL
 *        it will create an uninitialized element.
 *
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCArrayInsertElementAtIndex(CCArray Array, size_t Index, const void *Element);

/*!
 * @brief Removes an element at a given index from the array.
 * @description Decreases the array's count by 1.
 * @performance The further away from the end of the array the index is, the slower it is. It has
 *              a worst case of O(n).
 *
 * @warning Index must not be out of bounds.
 * @param Array The array to remove an element from.
 * @param Index The position in the array for the element to be removed from.
 */
void CCArrayRemoveElementAtIndex(CCArray Array, size_t Index);

/*!
 * @brief Removes the elements at a given index from the array.
 * @description Decreases the array's count by the number of elements removed.
 * @performance The further away from the end of the array the index is, the slower it is. It has
 *              a worst case of O(n-k) where k is the number of items removed.
 *
 * @warning Index and count must not be out of bounds.
 * @param Array The array to remove the elements from.
 * @param Index The position in the array for the elements to be removed from.
 * @param Count The number of elements to be removed.
 */
void CCArrayRemoveElementsAtIndex(CCArray Array, size_t Index, size_t Count);

/*!
 * @brief Removes all elements from the array.
 * @description Sets the arrays count to 0.
 * @param Array The array to remove all elements from.
 */
void CCArrayRemoveAllElements(CCArray Array);


#pragma mark - Query Info
/*!
 * @brief Get the current number of elements in the array.
 * @param Array The array to get the count of.
 * @return The number of elements.
 */
static inline size_t CCArrayGetCount(CCArray Array);

/*!
 * @brief Get the element size of the array.
 * @param Array The array to get the element size of.
 * @return The size of elements.
 */
static inline size_t CCArrayGetElementSize(CCArray Array);

/*!
 * @brief Get the element at index.
 * @warning Index must not be out of bounds.
 * @param Array The array to get the element of.
 * @param Index The index of the element.
 * @return The pointer to the element.
 */
static inline void *CCArrayGetElementAtIndex(CCArray Array, size_t Index);

/*!
 * @brief Get the chunk size of the array.
 * @param Array The array to get the chunk size of.
 * @return The chunk size of the array.
 */
static inline size_t CCArrayGetChunkSize(CCArray Array);

/*!
 * @brief Get an enumerable for the array.
 * @param Array The array to obtain an enumerable for.
 * @param Enumerable A pointer to the enumerable to use.
 */
static inline void CCArrayGetEnumerable(CCArray Array, CCEnumerable *Enumerable);


#pragma mark -
static inline size_t CCArrayGetCount(CCArray Array)
{
    CCAssertLog(Array, "Array must not be null");
    
    return Array->count;
}

static inline size_t CCArrayGetElementSize(CCArray Array)
{
    CCAssertLog(Array, "Array must not be null");
    
    return Array->size;
}

static inline void *CCArrayGetElementAtIndex(CCArray Array, size_t Index)
{
    CCAssertLog(Array, "Array must not be null");
    CCAssertLog(CCArrayGetCount(Array) > Index, "Index must not be out of bounds");
    
    return Array->data + (Index * CCArrayGetElementSize(Array));
}

static inline size_t CCArrayGetChunkSize(CCArray Array)
{
    CCAssertLog(Array, "Array must not be null");
    
    return Array->chunkSize;
}

static inline void CCArrayGetEnumerable(CCArray Array, CCEnumerable *Enumerable)
{
    CCAssertLog(Array, "Array must not be null");
    
    *Enumerable = CCEnumerableCreate(Array->data, Array->size, Array->count);
}

#endif
