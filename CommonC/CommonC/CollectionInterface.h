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

#ifndef CommonC_CollectionInterface_h
#define CommonC_CollectionInterface_h

#include <CommonC/CollectionTypes.h>
#include <CommonC/Enumerator.h>
#include <CommonC/Comparator.h>
#include <CommonC/Allocator.h>


#pragma mark - Required Callbacks
/*!
 * @brief A callback that will return a weight for how ideal this implementation is for the intended
 * usage.
 *
 * @return A higher value is weighted in-favour of a lower value.
 */
typedef int (*CCCollectioHintWeight)(CCCollectionHint Hint);

/*!
 * @brief A callback to create the internal implementation for the collection.
 * @param Allocator The allocator to be used for the creation.
 * @param Hint The hints describing the intended usage of the collection.
 * @param ElementSize The size of the elements.
 * @return The created internal structure.
 */
typedef void *(*CCCollectionConstructor)(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize);

/*!
 * @brief A callback to destroy the internal implementation for the collection.
 * @param Internal The pointer to the internal of the collection.
 */
typedef void (*CCCollectionDestructor)(void *Internal);

/*!
 * @brief A callback to get the current number of elements in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @return The number of elements in the collection.
 */
typedef size_t (*CCCollectionCount)(void *Internal);

/*!
 * @brief A callback to add an element into the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The pointer to the element to be copied to the collection.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @return A reference to this entry.
 */
typedef CCCollectionEntry (*CCCollectionInsert)(void *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief A callback to remove an element from the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Entry The entry reference in the collection to be removed.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @return A reference to this entry.
 */
typedef void (*CCCollectionRemove)(void *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator);

/*!
 * @brief A callback to retrieve an element from the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Entry The entry reference in the collection to be retrieved.
 * @return The element.
 */
typedef void *(*CCCollectionElement)(void *Internal, CCCollectionEntry Entry);

/*!
 * @brief A callback to set the enumerator for the collection on a given action.
 * @param Internal The pointer to the internal of the collection.
 * @param Enumerator The pointer to the enumerator to be used.
 * @param Action The action to be performed.
 * @return The current element at the new position the enumerator has been set to.
 */
typedef void *(*CCCollectionEnumerator)(void *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action);

/*!
 * @brief A callback to get the entry reference for the current enumerator position.
 * @param Internal The pointer to the internal of the collection.
 * @param Enumerator The pointer enumerator to be used.
 * @return An entry reference to the current enumerator position.
 */
typedef CCCollectionEntry (*CCCollectionEnumeratorEntry)(void *Internal, CCEnumeratorState *Enumerator);

#pragma mark - Optional Callbacks

/*!
 * @brief An optional callback to find an element in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The element to find.
 * @param Comparator The comparison to be performed, or NULL in which case it defaults to
 *        comparing using a memcmp.
 *
 * @param ElementSize The size of the element.
 * @return The entry reference to the element, or NULL if it was not found.
 */
typedef CCCollectionEntry (*CCCollectionFind)(void *Internal, const void *Element, CCComparator Comparator, size_t ElementSize);

#pragma mark -

/*!
 * @brief The interface to the internal implementation.
 * @description Optional interfaces do not need to be implemented and will instead be supported
 *              through reusing the required interfaces.
 */
typedef struct {
    CCCollectioHintWeight hintWeight;
    CCCollectionConstructor create;
    CCCollectionDestructor destroy;
    CCCollectionCount count;
    CCCollectionInsert insert;
    CCCollectionRemove remove;
    CCCollectionElement element;
    CCCollectionEnumerator enumerator;
    CCCollectionEnumeratorEntry enumeratorReference;
    struct {
        CCCollectionFind find;
    } optional;
} CCCollectionInterface;

#endif
