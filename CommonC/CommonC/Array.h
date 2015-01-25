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

#include <stddef.h>
#include <stdint.h>
#include <CommonC/Allocator.h>
#include <CommonC/Assertion.h>

typedef struct {
    size_t size, chunkSize;
    size_t count;
    void *data;
} CCArrayInfo, *CCArray;


#pragma mark - Creation/Destruction
/*!
 * @brief Create an array.
 * @param Allocator The allocator to be used for the allocation.
 * @param ElementSize The size of the data elements.
 * @param ChunkSize The number of elements to fit with each allocation. Must be at least 1.
 * @return An empty array, or NULL on failure. Must be destroyed to free the memory.
 */
CCArray CCArrayCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize);

/*!
 * @brief Destroy an array.
 * @param Array The array to be destroyed.
 */
void CCArrayDestroy(CCArray Array);


#pragma mark - Insertions/Deletions
/*!
 * @brief Appends the element to the end of the array.
 * @description Increases the arrays count by 1.
 * @warning The size of element must be the same size as specified in the array creation.
 * @param Element The pointer to the element to be copied to the end of the array.
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCArrayAppendElement(CCArray Array, const void *Element);

/*!
 * @brief Replace element at index with new element.
 * @warning Index must not be out of bounds.
 * @param Array The array to replace an element of.
 * @param Index The position of the element to be replaced.
 * @param Element The replacement element.
 */
void CCArrayReplaceElementAtIndex(CCArray Array, size_t Index, const void *Element);


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

#endif
