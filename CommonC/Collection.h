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
 * @header CCCollection
 * CCCollection implements a generic interface to an unorded collection. It uses a data structure
 * that will try provide better performance for how it's intended to be used.
 *
 * Other implementations can be provided given they support all the required functionality.
 */
#ifndef CommonC_Collection_h
#define CommonC_Collection_h

#include <CommonC/Base.h>
#include <CommonC/Container.h>
#include <CommonC/Allocator.h>
#include <CommonC/Enumerator.h>
#include <CommonC/Comparator.h>
#include <CommonC/CollectionTypes.h>
#include <CommonC/CollectionInterface.h>


CC_CONTAINER_DECLARE_PRESET_1(CCCollection);

/*!
 * @define CC_COLLECTION_DECLARE
 * @abstract Convenient macro to define a @b CCCollection type that can be referenced by @b CCCollection.
 * @param element The element type.
 */
#define CC_COLLECTION_DECLARE(element) CC_CONTAINER_DECLARE(CCCollection, element)

/*!
 * @define CC_COLLECTION
 * @abstract Convenient macro to define an explicitly typed @b CCCollection.
 * @param element The element type.
 */
#define CC_COLLECTION(element) CC_CONTAINER(CCCollection, element)

/*!
 * @define CCCollection
 * @abstract Convenient macro to define an explicitly typed @b CCCollection.
 * @description In the case that this macro is conflicting with the standalone @b CCCollection type, simply
 *              undefine it and redefine it back to @b CC_COLLECTION.
 *
 * @param element The element type.
 */
#define CCCollection(element) CC_COLLECTION(element)

/*!
 * @brief A callback to handle custom destruction of an element when it is removed from the collection.
 * @param Collection The collection the element is from.
 * @param Element The element being removed.
 */
typedef void (*CCCollectionElementDestructor)(CCCollection Collection, void *Element);


typedef struct CCCollectionInfo {
    const CCCollectionInterface *interface;
    CCAllocatorType allocator;
    CCCollectionElementDestructor destructor;
    size_t size;
    void *internal;
} CCCollectionInfo;

#pragma mark - Creation/Destruction

/*!
 * @brief Create a collection based on the intended usage.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this collection. This will decided the appropriate
 *        internal implementation to be used.
 *
 * @param ElementSize The element size.
 * @param Destructor An optional element destructor.
 * @return An empty collection, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCCollection CCCollectionCreate(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize, CCCollectionElementDestructor Destructor);

/*!
 * @brief Create a collection with the specified implementation.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this collection.
 * @param ElementSize The element size.
 * @param Destructor An optional element destructor.
 * @param Interface The interface to the internal implementation to be used.
 * @return An empty collection, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCCollection CCCollectionCreateWithImplementation(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize, CCCollectionElementDestructor Destructor, const CCCollectionInterface *Interface);

/*!
 * @brief Destroy a collection.
 * @param Collection The collection to be destroyed.
 */
void CCCollectionDestroy(CCCollection CC_DESTROY(Collection));


#pragma mark - Insertion/Deletion

/*!
 * @brief Add an element to the collection.
 * @param Collection The collection to add the element to.
 * @param Element The element to be copied into the collection.
 * @return The entry reference to the newly added element.
 */
CCCollectionEntry CCCollectionInsertElement(CCCollection Collection, const void *Element);

/*!
 * @brief Remove an element from the collection.
 * @param Collection The collection to remove the element from.
 * @param Entry The reference to the element in the collection to be removed.
 */
void CCCollectionRemoveElement(CCCollection Collection, CCCollectionEntry Entry);

/*!
 * @brief Remove all elements in the collection.
 * @param Collection The collection to remove all the elements from.
 */
void CCCollectionRemoveAllElements(CCCollection Collection);

/*!
 * @brief Add a collection of elements to the collection.
 * @param Collection The collection to add the elements to.
 * @param Elements The collection of elements that will be added.
 * @param Entries A pointer to where the collection of entry references to the added elements
 *        will be stored. Requires collection to be destroyed when no longer needed. May be NULL.
 */
void CCCollectionInsertCollection(CCCollection Collection, CCCollection Elements, CCCollection *Entries);

/*!
 * @brief Remove a collection of elements from the collection.
 * @param Collection The collection to remove the elements from.
 * @param Entries The collection of references to the elements in the collection that will be
 *        removed.
 */
void CCCollectionRemoveCollection(CCCollection Collection, CCCollection Entries);


#pragma mark - Query Info

/*!
 * @brief Get the element from the collection.
 * @param Collection The collection to get the element from.
 * @param Entry The reference to the element in the collection to be retrieved.
 * @return The element.
 */
void *CCCollectionGetElement(CCCollection Collection, CCCollectionEntry Entry);

/*!
 * @brief Get the number of elements currently in the collection.
 * @param Collection The collection to get the count from.
 * @return The number of elements.
 */
size_t CCCollectionGetCount(CCCollection Collection);

/*!
 * @brief Get the element size of the collection.
 * @param Collection The collection to get the element size from.
 * @return The size of each element.
 */
size_t CCCollectionGetElementSize(CCCollection Collection);

/*!
 * @brief Get a collection's internal structure.
 * @param Collection The collection to get the internal structure.
 * @return The internal structure.
 */
void *CCCollectionGetInternal(CCCollection Collection);

/*!
 * @brief Get a collection's interface.
 * @param Collection The collection to get the interface for.
 * @return The interface.
 */
const CCCollectionInterface *CCCollectionGetInterface(CCCollection Collection);

/*!
 * @brief Get entry references to all of the elements in a collection.
 * @param Collection The collection to get all the entry references to.
 * @return A collection with all the entry references. This collection must be destroyed when no longer
 *         in use.
 */
CCCollection CCCollectionGetAllEntries(CCCollection Collection);

/*!
 * @brief Find an element in the collection.
 * @param Collection The collection to search for the element in.
 * @param Element The element to find.
 * @param Comparator An optional comparator function, returning CCComparatorEqual when found the
 *        the match. If NULL it reverts to a memcmp compare.
 * 
 * @return An entry reference to the element if it is found, otherwise NULL if it was not found.
 */
CCCollectionEntry CCCollectionFindElement(CCCollection Collection, const void *Element, CCComparator Comparator);

/*!
 * @brief Find an element in the collection.
 * @param Collection The collection to search for the element in.
 * @param Elements The elements to find.
 * @param Comparator An optional comparator function, returning CCComparatorEqual when found the
 *        the match. If NULL it reverts to a memcmp compare.
 *
 * @return A collection of entry references to the elements it found. An empty collection means no
 *         elements were found. The returned collection must be destroyed when it is no longer needed.
 */
CCCollection CCCollectionFindCollection(CCCollection Collection, CCCollection Elements, CCComparator Comparator);

/*!
 * @brief Get an enumerator for the collection.
 * @param Collection The collection to obtain an enumerator for.
 * @param Enumerator A pointer to the enumerator to use.
 */
void CCCollectionGetEnumerator(CCCollection Collection, CCEnumerator *Enumerator);

/*!
 * @brief Get an enumerable for the collection.
 * @param Collection The collection to obtain an enumerable for.
 * @param Enumerable A pointer to the enumerable to use.
 */
void CCCollectionGetEnumerable(CCCollection Collection, CCEnumerable *Enumerable);

#endif
