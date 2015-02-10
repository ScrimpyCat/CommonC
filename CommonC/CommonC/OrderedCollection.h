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
 * @header CCOrderedCollection
 * CCOrderedCollection implements a generic interface to an orded collection. It uses a data structure
 * that will try provide better performance for how it's intended to be used.
 *
 * Other implementations can be provided given they support all the required functionality.
 *
 * It is compatible with CCCollection, as a CCOrderedCollection is a valid CCCollection interface.
 */
#ifndef CommonC_OrderedCollection_h
#define CommonC_OrderedCollection_h

#include <CommonC/Collection.h>


#pragma mark - Insertion/Deletion

/*!
 * @brief Insert an element to the collection.
 * @warning The index must be within the collection's bounds or the index after the last element.
 * @param Collection The collection to add the element to.
 * @param Element The element to be copied into the collection.
 * @param Index The index in the collection the element should be inserted to.
 * @return The entry reference to the newly added element.
 */
CCCollectionEntry CCOrderedCollectionInsertElementAtIndex(CCOrderedCollection Collection, const void *Element, size_t Index);

/*!
 * @brief Append an element to the collection.
 * @param Collection The collection to add the element to.
 * @param Element The element to be copied into the collection.
 * @return The entry reference to the newly added element.
 */
CCCollectionEntry CCOrderedCollectionAppendElement(CCOrderedCollection Collection, const void *Element);
/*!
 * @brief Prepend an element to the collection.
 * @param Collection The collection to add the element to.
 * @param Element The element to be copied into the collection.
 * @return The entry reference to the newly added element.
 */
CCCollectionEntry CCOrderedCollectionPrependElement(CCOrderedCollection Collection, const void *Element);

/*!
 * @brief Replace an element at a given index in the collection.
 * @warning The index must be within the collection's bounds.
 * @param Collection The collection to add the element to.
 * @param Element The element to be copied into the collection.
 * @param Index The index in the collection the element should be replace.
 * @return The entry reference to the newly added element.
 */
CCCollectionEntry CCOrderedCollectionReplaceElementAtIndex(CCOrderedCollection Collection, const void *Element, size_t Index);

/*!
 * @brief Remove an element from the collection.
 * @warning The index must be within the collection's bounds.
 * @param Collection The collection to add the element to.
 * @param Index The index of the element in the collection to be removed.
 */
void CCOrderedCollectionRemoveElementAtIndex(CCOrderedCollection Collection, size_t Index);

/*!
 * @brief Remove the last element from the collection.
 * @param Collection The collection to add the element to.
 */
void CCOrderedCollectionRemoveLastElement(CCOrderedCollection Collection);

/*!
 * @brief Remove the first element from the collection.
 * @param Collection The collection to add the element to.
 */
void CCOrderedCollectionRemoveFirstElement(CCOrderedCollection Collection);

#pragma mark - Query Info

/*!
 * @brief Get the entry at the index in the collection.
 * @warning The index must be within the collection's bounds.
 * @param Collection The collection to get the element from.
 * @param Index The index of the element in the collection to get the reference to.
 * @return The entry.
 */
CCCollectionEntry CCOrderedCollectionGetEntryAtIndex(CCOrderedCollection Collection, size_t Index);

/*!
 * @brief Get the last entry in the collection.
 * @param Collection The collection to get the element from.
 * @return The entry.
 */
CCCollectionEntry CCOrderedCollectionGetLastEntry(CCOrderedCollection Collection);

/*!
 * @brief Get the first entry in the collection.
 * @param Collection The collection to get the element from.
 * @return The entry.
 */
CCCollectionEntry CCOrderedCollectionGetFirstEntry(CCOrderedCollection Collection);

/*!
 * @brief Get the element from the collection.
 * @param Collection The collection to get the element from.
 * @param Entry The reference to the element in the collection to be retrieved.
 * @return The index.
 */
size_t CCOrderedCollectionGetIndex(CCOrderedCollection Collection, CCCollectionEntry Entry);

/*!
 * @brief Get the element at the index in collection.
 * @warning The index must be within the collection's bounds.
 * @param Collection The collection to get the element from.
 * @param Index The index of the element in the collection to be retrieved.
 * @return The element.
 */
void *CCOrderedCollectionGetElementAtIndex(CCOrderedCollection Collection, size_t Index);


#endif
