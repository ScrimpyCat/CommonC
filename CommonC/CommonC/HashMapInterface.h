/*
 *  Copyright (c) 2016, Stefan Johnson
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

#ifndef CommonC_HashMapInterface_h
#define CommonC_HashMapInterface_h

#include <CommonC/Allocator.h>
#include <CommonC/OrderedCollection.h>
#include <CommonC/Enumerator.h>

/*!
 * @brief The hashmap.
 * @description Allows @b CCRetain.
 */
typedef struct CCHashMapInfo *CCHashMap;

/*!
 * @brief The reference to an entry in the collection.
 */
typedef uintptr_t CCHashMapEntry;

/*!
 * @brief The type of action the enumerator callback will need to perform.
 */
typedef enum {
    ///Set the enumerator to the head end of the hashmap and return the key/value there.
    CCHashMapEnumeratorActionHead,
    ///Set the enumerator to the tail end of the hashmap and return the key/value there.
    CCHashMapEnumeratorActionTail,
    ///Set the enumerator to the next position in the hashmap, and return the key/value there.
    CCHashMapEnumeratorActionNext,
    ///Set the enumerator to the previous position in the hashmap, and return the key/value there.
    CCHashMapEnumeratorActionPrevious,
    ///Return the key/value at the current position.
    CCHashMapEnumeratorActionCurrent
} CCHashMapEnumeratorAction;

/*!
 * @brief The type of enumerator.
 */
typedef enum {
    CCHashMapEnumeratorTypeMask = 1,
    ///A key enumerator.
    CCHashMapEnumeratorTypeKey = (0 << 0),
    ///A value enumerator.
    CCHashMapEnumeratorTypeValue = (1 << 0)
} CCHashMapEnumeratorType;


#pragma mark - Required Callbacks
/*!
 * @brief A callback to create the internal implementation for the hashmap.
 * @param Allocator The allocator to be used for the creation.
 * @param Hint The hints describing the intended usage of the collection.
 * @param KeySize The size of the keys.
 * @param ValueSize The size of the values.
 * @param BucketCount The number of buckets to be allocated.
 * @return The created internal structure.
 */
typedef void *(*CCHashMapConstructorCallback)(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount);

/*!
 * @brief A callback to destroy the internal implementation for the hashmap.
 * @param Internal The pointer to the internal of the hashmap.
 */
typedef void (*CCHashMapDestructorCallback)(void *Internal);

/*!
 * @brief A callback to get the number of entries currently in the map.
 * @param Map The hashmap to get the count of.
 * @return The number of entries.
 */
typedef size_t (*CCHashMapGetCountCallback)(CCHashMap Map);

/*!
 * @brief A callback to find a given key.
 * @param Map The hashmap to find the key of.
 * @param Key The pointer to the key to be found.
 * @return The entry reference.
 */
typedef CCHashMapEntry (*CCHashMapFindKeyCallback)(CCHashMap Map, void *Key);

/*!
 * @brief A callback to create an entry for a given key.
 * @param Map The hashmap to create a key for.
 * @param Key The pointer to the key to be found or created.
 * @param Created Set whether the entry reference was created (TRUE) or whether it
 *        already existed (FALSE). Note: This may be NULL.
 *
 * @return The entry reference.
 */
typedef CCHashMapEntry (*CCHashMapEntryForKeyCallback)(CCHashMap Map, void *Key, _Bool *Created);

/*!
 * @brief A callback to get a key for a given entry reference.
 * @param Map The hashmap to create a key for.
 * @param Entry The entry reference in the hashmap for the key.
 * @return The pointer to the key.
 */
typedef void *(*CCHashMapGetKeyCallback)(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief A callback to get the value of a given entry reference.
 * @param Map The hashmap to get the value of.
 * @param Entry The entry reference in the hashmap for the value.
 * @return The pointer to the value.
 */
typedef void *(*CCHashMapGetEntryCallback)(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief A callback to set the value at a given entry reference.
 * @param Map The hashmap to set the value of.
 * @param Entry The entry reference in the hashmap for the value.
 * @param Value The pointer to the value to be copied to the map.
 */
typedef void (*CCHashMapSetEntryCallback)(CCHashMap Map, CCHashMapEntry Entry, void *Value);

/*!
 * @brief A callback to remove the value at a given entry reference.
 * @description The entry point for this value will no longer be valid.
 * @param Map The hashmap to remove the value from.
 * @param Entry The entry reference in the hashmap to remove the value of.
 */
typedef void (*CCHashMapRemoveEntryCallback)(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief A callback to set the enumerator for the hashmap on a given action and type.
 * @param Map The hashmap to enumerate.
 * @param Enumerator The pointer to the enumerator to be used.
 * @param Action The action to be performed.
 * @param Type The type of enumerator.
 * @return The current element at the new position the enumerator has been set to.
 */
typedef void *(*CCHashMapEnumeratorCallback)(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorAction Action, CCHashMapEnumeratorType Type);

/*!
 * @brief A callback to get the entry reference for the current enumerator position.
 * @param Map The hashmap being enumerated.
 * @param Enumerator The pointer enumerator to be used.
 * @param Type The type of enumerator.
 * @return An entry reference to the current enumerator position.
 */
typedef CCHashMapEntry (*CCHashMapEnumeratorEntryCallback)(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorType Type);


#pragma mark - Optional Callbacks

/*!
 * @brief An optional callback to rehash the hashmap.
 * @param Map The hashmap to rehash.
 * @param BucketCount The number of buckets to be allocated.
 */
typedef void (*CCHashMapRehashCallback)(CCHashMap Map, size_t BucketCount);

/*!
 * @brief An optional callback to get the value of a given key.
 * @param Map The hashmap to get the value of.
 * @param Key The pointer to the key to be used to get the value for.
 * @return The pointer to the value.
 */
typedef void *(*CCHashMapGetValueCallback)(CCHashMap Map, void *Key);

/*!
 * @brief An optional callback to set the value at a given key.
 * @param Map The hashmap to set the value of.
 * @param Key The pointer to the key to be used to set the value of.
 * @param Value The pointer to the value to be copied to the map.
 */
typedef void (*CCHashMapSetValueCallback)(CCHashMap Map, void *Key, void *Value);

/*!
 * @brief An optional callback to remove the value at a given key.
 * @description The entry point for this value will no longer be valid.
 * @param Map The hashmap to remove the value from.
 * @param Key The pointer to the key to be used to remove the value of.
 */
typedef void (*CCHashMapRemoveValueCallback)(CCHashMap Map, void *Key);

/*!
 * @brief An optional callback to retrieve the keys in the hashmap.
 * @description Must produce the same order (corresponding pairs) when calling @b CCHashMapGetValues
 *              if no mutation occurs in-between the two calls.
 *
 * @param Map The hashmap to get the keys of.
 * @return The ordered collection of keys. Ownership of this collection is passed to the caller.
 */
typedef CCOrderedCollection (*CCHashMapGetKeysCallback)(CCHashMap Map);

/*!
 * @brief An optional callback to retrieve the values in a hashmap.
 * @description Must produce the same order (corresponding pairs) when calling @b CCHashMapGetKeys
 *              if no mutation occurs in-between the two calls.
 *
 * @param Map The hashmap to get the values of.
 * @return The ordered collection of values. Ownership of this collection is passed to the caller.
 */
typedef CCOrderedCollection (*CCHashMapGetValuesCallback)(CCHashMap Map);


#pragma mark -

/*!
 * @brief The interface to the internal implementation.
 * @description Optional interfaces do not need to be implemented and will instead be supported
 *              through reusing the required interfaces.
 */
typedef struct {
    CCHashMapConstructorCallback create;
    CCHashMapDestructorCallback destroy;
    CCHashMapGetCountCallback count;
    CCHashMapFindKeyCallback findKey;
    CCHashMapEntryForKeyCallback entryForKey;
    CCHashMapGetKeyCallback getKey;
    CCHashMapGetEntryCallback getEntry;
    CCHashMapSetEntryCallback setEntry;
    CCHashMapRemoveEntryCallback removeEntry;
    CCHashMapEnumeratorCallback enumerator;
    CCHashMapEnumeratorEntryCallback enumeratorReference;
    struct {
        CCHashMapRehashCallback rehash;
        CCHashMapGetValueCallback getValue;
        CCHashMapSetValueCallback setValue;
        CCHashMapRemoveValueCallback removeValue;
        CCHashMapGetKeysCallback keys;
        CCHashMapGetValuesCallback values;
    } optional;
} CCHashMapInterface;

#endif
