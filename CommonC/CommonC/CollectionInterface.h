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
 * @param Hint The hints describing the intended usage of the collection.
 * @return A higher value is weighted in-favour of a lower value.
 */
typedef int (*CCCollectionHintWeightCallback)(CCCollectionHint Hint);

/*!
 * @brief A callback to create the internal implementation for the collection.
 * @param Allocator The allocator to be used for the creation.
 * @param Hint The hints describing the intended usage of the collection.
 * @param ElementSize The size of the elements.
 * @return The created internal structure.
 */
typedef void *(*CCCollectionConstructorCallback)(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize);

/*!
 * @brief A callback to destroy the internal implementation for the collection.
 * @param Internal The pointer to the internal of the collection.
 */
typedef void (*CCCollectionDestructorCallback)(void *Internal);

/*!
 * @brief A callback to get the current number of elements in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @return The number of elements in the collection.
 */
typedef size_t (*CCCollectionCountCallback)(void *Internal);

/*!
 * @brief A callback to add an element into the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The pointer to the element to be copied to the collection.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @param ElementSize The size of the element.
 * @return A reference to this entry.
 */
typedef CCCollectionEntry (*CCCollectionInsertCallback)(void *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief A callback to remove an element from the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Entry The entry reference in the collection to be removed.
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCCollectionRemoveCallback)(void *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator);

/*!
 * @brief A callback to retrieve an element from the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Entry The entry reference in the collection to be retrieved.
 * @return The element.
 */
typedef void *(*CCCollectionElementCallback)(void *Internal, CCCollectionEntry Entry);

/*!
 * @brief A callback to set the enumerator for the collection on a given action.
 * @param Internal The pointer to the internal of the collection.
 * @param Enumerator The pointer to the enumerator to be used.
 * @param Action The action to be performed.
 * @return The current element at the new position the enumerator has been set to.
 */
typedef void *(*CCCollectionEnumeratorCallback)(void *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action);

/*!
 * @brief A callback to get the entry reference for the current enumerator position.
 * @param Internal The pointer to the internal of the collection.
 * @param Enumerator The pointer enumerator to be used.
 * @return An entry reference to the current enumerator position.
 */
typedef CCCollectionEntry (*CCCollectionEnumeratorEntryCallback)(void *Internal, CCEnumeratorState *Enumerator);

#pragma mark Ordered

/*!
 * @brief A callback to insert an element into the collection at a given index.
 * @description Index may be the next position after the last.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The pointer to the element to be copied to the collection.
 * @param Index The index in the collection the element should be inserted.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @param ElementSize The size of the element.
 * @return A reference to this entry.
 */
typedef CCCollectionEntry (*CCOrderedCollectionInsertCallback)(void *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief A callback to get the entry reference for an element at an index.
 * @param Internal The pointer to the internal of the collection.
 * @param Index The index in the collection to get an entry reference to.
 * @return An entry reference to element at the given index.
 */
typedef CCCollectionEntry (*CCOrderedCollectionEntryCallback)(void *Internal, size_t Index);

/*!
 * @brief A callback to retrieve an index for an entry in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Entry The entry reference in the collection to get the index of.
 * @return The index.
 */
typedef size_t (*CCOrderedCollectionIndexCallback)(void *Internal, CCCollectionEntry Entry);

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
typedef CCCollectionEntry (*CCCollectionFindCallback)(void *Internal, const void *Element, CCComparator Comparator, size_t ElementSize);

/*!
 * @brief A callback to add a collection of elements into the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Elements The collection of elements to be added.
 * @param Entries The pointer to where a collection of the entries should be created, or NULL
 *        in which case no entries need to be returned.
 *
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @param ElementSize The size of the element.
 */
typedef void (*CCCollectionInsertCollectionCallback)(void *Internal, CCCollection Elements, CCCollection *Entries, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief A callback to remove a collection of elements from the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Entries The collection of entry references in the collection to be removed.
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCCollectionRemoveCollectionCallback)(void *Internal, CCCollection Entries, CCAllocatorType Allocator);

#pragma mark Ordered

/*!
 * @brief An optional callback to replace an element in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The pointer to the element to be copied to the collection.
 * @param Index The index of the element to be replaced.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @param ElementSize The size of the element.
 * @return A reference to this entry.
 */
typedef CCCollectionEntry (*CCOrderedCollectionReplaceCallback)(void *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief An optional callback to remove an element in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Index The index of the element to be removed.
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCOrderedCollectionRemoveCallback)(void *Internal, size_t Index, CCAllocatorType Allocator);

/*!
 * @brief An optional callback to append an element to the end of a collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The pointer to the element to be copied to the collection.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @param ElementSize The size of the element.
 * @return A reference to this entry.
 */
typedef CCCollectionEntry (*CCOrderedCollectionAppendCallback)(void *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief An optional callback to prepend an element to the end of a collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Element The pointer to the element to be copied to the collection.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @param ElementSize The size of the element.
 * @return A reference to this entry.
 */
typedef CCCollectionEntry (*CCOrderedCollectionPrependCallback)(void *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);

/*!
 * @brief An optional callback to get the element at index.
 * @param Internal The pointer to the internal of the collection.
 * @param Index The index in the collection to get the element.
 * @return The element at the given index.
 */
typedef void *(*CCOrderedCollectionElementCallback)(void *Internal, size_t Index);

/*!
 * @brief An optional callback to get the entry reference for the last element.
 * @param Internal The pointer to the internal of the collection.
 * @return An entry reference to the last element.
 */
typedef CCCollectionEntry (*CCOrderedCollectionEntryLastCallback)(void *Internal);

/*!
 * @brief An optional callback to remove the last element in the collection.
 * @param Internal The pointer to the internal of the collection.
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCOrderedCollectionRemoveLastCallback)(void *Internal, CCAllocatorType Allocator);


#pragma mark -

/*!
 * @brief The interface to te internal ordered implementation.
 * @description Optional interfaces do not need to be implemented and will instead be supported
 *              through reusing the required interfaces.
 */
typedef struct {
    CCOrderedCollectionInsertCallback insert;
    CCOrderedCollectionEntryCallback entry;
    CCOrderedCollectionIndexCallback index;
    struct {
        CCOrderedCollectionReplaceCallback replace;
        CCOrderedCollectionRemoveCallback remove;
        CCOrderedCollectionAppendCallback append;
        CCOrderedCollectionPrependCallback prepend;
        CCOrderedCollectionElementCallback element;
        CCOrderedCollectionEntryLastCallback lastEntry;
        CCOrderedCollectionRemoveLastCallback removeLast;
    } optional;
} CCOrderedCollectionInterface;

/*!
 * @brief The interface to the internal implementation.
 * @description Optional interfaces do not need to be implemented and will instead be supported
 *              through reusing the required interfaces.
 */
typedef struct {
    CCCollectionHintWeightCallback hintWeight;
    CCCollectionConstructorCallback create;
    CCCollectionDestructorCallback destroy;
    CCCollectionCountCallback count;
    CCCollectionInsertCallback insert;
    CCCollectionRemoveCallback remove;
    CCCollectionElementCallback element;
    CCCollectionEnumeratorCallback enumerator;
    CCCollectionEnumeratorEntryCallback enumeratorReference;
    struct {
        const CCOrderedCollectionInterface *ordered;
        CCCollectionFindCallback find;
        CCCollectionInsertCollectionCallback insertCollection;
        CCCollectionRemoveCollectionCallback removeCollection;
    } optional;
} CCCollectionInterface;


#pragma mark - Interface Handling

/*!
 * @brief The maximum weight value produced by CCCollectionHintWeightCreate.
 * @description This is the maximum weight any of the framework's interfaces may reach. To push
 * your own interfaces above the internal ones, you use can use this max weight to add onto. Where
 * CCCollectionHintWeightMax + 1 is guaranteed to be chosen above any of the internal interfaces
 * that are provided.
 */
extern const int CCCollectionHintWeightMax;

/*!
 * @brief Calculate a weight for the given hint combination.
 * @description The max value returned by this is CCCollectionHintWeightMax.
 * @param Hint The hints describing the intended usage of the collection.
 * @param FastHints Hints with a worst case that is considered fast for the given operation.
 * @param ModerateHints Hints with a worst case that is considered decent for the given operation.
 * @param SlowHints Hints with worst case that is considered slow for the given operation.
 * @return The weight value.
 */
int CCCollectionHintWeightCreate(CCCollectionHint Hint, CCCollectionHint FastHints, CCCollectionHint ModerateHints, CCCollectionHint SlowHints);

/*!
 * @brief Register a collection interface with the system.
 * @description The interface is chosen based on how appropriate it is with the current hints.
 * @param Interface The interface to register.
 */
void CCCollectionRegisterInterface(const CCCollectionInterface *Interface);

/*!
 * @brief Deregister a collection interface from the system.
 * @description The interface can no longer be chosen.
 * @param Interface The interface to register.
 */
void CCCollectionDeregisterInterface(const CCCollectionInterface *Interface);

#endif
