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

#ifndef CommonC_DictionaryInterface_h
#define CommonC_DictionaryInterface_h

#include <CommonC/Allocator.h>
#include <CommonC/OrderedCollection.h>
#include <CommonC/Enumerator.h>

/*!
 * @brief The dictionary.
 * @description Allows @b CCRetain.
 */
typedef struct CCDictionaryInfo *CCDictionary;

/*!
 * @brief The reference to an entry in the collection.
 */
typedef uintptr_t CCDictionaryEntry;

/*!
 * @typedef CCDictionaryHint
 * @brief Hints for the indended usage of the dictionary.
 */
typedef enum {
    ///Mask for hints for a dictionary.
    CCDictionaryHintMask = 0xff,
    ///Dictionary will involve a lot of enumerations.
    CCDictionaryHintHeavyEnumerating = (1 << 0),
    ///Dictionary will involve a lot of object lookups.
    CCDictionaryHintHeavyFinding = (1 << 1),
    ///Dictionary will involve a lot of inserting.
    CCDictionaryHintHeavyInserting = (1 << 2),
    ///Dictionary will involve a lot of deleting.
    CCDictionaryHintHeavyDeleting = (1 << 3),
    ///The number of elements in the dictionary won't change (unlikely to do any inserting/deleting).
    CCDictionaryHintConstantLength = (1 << 4),
    ///The elements won't change (unlikely to do any deleting/replacing).
    CCDictionaryHintConstantElements = (1 << 5),
    
    ///Mask for size hints.
    CCDictionaryHintSizeMask = 0xc0000000,
    ///Dictionary will have not many elements.
    CCDictionaryHintSizeSmall = (1 << 30),
    ///Dictionary will have a moderate amount of elements.
    CCDictionaryHintSizeMedium = (0 << 30),
    ///Dictionary will have lots of elements.
    CCDictionaryHintSizeLarge = (unsigned int)(2 << 30)
} CCDictionaryHint;

/*!
 * @brief The type of action the enumerator callback will need to perform.
 */
typedef enum {
    ///Set the enumerator to the head end of the dictionary and return the key/value there.
    CCDictionaryEnumeratorActionHead,
    ///Set the enumerator to the tail end of the dictionary and return the key/value there.
    CCDictionaryEnumeratorActionTail,
    ///Set the enumerator to the next position in the dictionary, and return the key/value there.
    CCDictionaryEnumeratorActionNext,
    ///Set the enumerator to the previous position in the dictionary, and return the key/value there.
    CCDictionaryEnumeratorActionPrevious,
    ///Return the key/value at the current position.
    CCDictionaryEnumeratorActionCurrent
} CCDictionaryEnumeratorAction;

/*!
 * @brief The type of enumerator.
 */
typedef enum {
    CCDictionaryEnumeratorTypeMask = 1,
    ///A key enumerator.
    CCDictionaryEnumeratorTypeKey = (0 << 0),
    ///A value enumerator.
    CCDictionaryEnumeratorTypeValue = (1 << 0)
} CCDictionaryEnumeratorType;

/*!
 * @brief A callback to handle custom destruction of an element when it is removed from the collection.
 * @param Key The key to generate a hash of.
 * @return The hash representing the key.
 */
typedef uintmax_t (*CCDictionaryKeyHasher)(void *Key);


#pragma mark - Required Callbacks
/*!
 * @brief A callback that will return a weight for how ideal this implementation is for the intended
 * usage.
 *
 * @param Hint The hints describing the intended usage of the dictionary.
 * @return A higher value is weighted in-favour of a lower value.
 */
typedef int (*CCDictionaryHintWeightCallback)(CCDictionaryHint Hint);

/*!
 * @brief A callback to create the internal implementation for the dictionary.
 * @param Allocator The allocator to be used for the creation.
 * @param Hint The hints describing the intended usage of the collection.
 * @param KeySize The size of the keys.
 * @param ValueSize The size of the values.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the implementation will use some default hashing behaviour.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, the implementation will use some default comparison behaviour.
 *
 * @return The created internal structure.
 */
typedef void *(*CCDictionaryConstructorCallback)(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator);

/*!
 * @brief A callback to destroy the internal implementation for the dictionary.
 * @param Internal The pointer to the internal of the dictionary.
 */
typedef void (*CCDictionaryDestructorCallback)(void *Internal);

/*!
 * @brief A callback to get the number of entries currently in the map.
 * @param Internal The pointer to the internal of the dictionary.
 * @return The number of entries.
 */
typedef size_t (*CCDictionaryGetCountCallback)(void *Internal);

/*!
 * @brief A callback to check if an entry has been initialized.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Entry The entry to check.
 * @return Whether the entry is initialized or not.
 */
typedef _Bool (*CCDictionaryEntryIsInitializedCallback)(void *Internal, CCDictionaryEntry Entry);

/*!
 * @brief A callback to find a given key.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Key The pointer to the key to be found.
 * @param KeySize The size of the key.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the implementation will use some default hashing behaviour.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, the implementation will use some default comparison behaviour.
 *
 * @return The entry reference.
 */
typedef CCDictionaryEntry (*CCDictionaryFindKeyCallback)(void *Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator);

/*!
 * @brief A callback to create an entry for a given key.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Key The pointer to the key to be found or created.
 * @param KeySize The size of the key.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the implementation will use some default hashing behaviour.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, the implementation will use some default comparison behaviour.
 *
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @return The entry reference.
 */
typedef CCDictionaryEntry (*CCDictionaryEntryForKeyCallback)(void *Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator);

/*!
 * @brief A callback to get a key for a given entry reference.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Entry The entry reference in the dictionary for the key.
 * @return The pointer to the key.
 */
typedef void *(*CCDictionaryGetKeyCallback)(void *Internal, CCDictionaryEntry Entry);

/*!
 * @brief A callback to get the value of a given entry reference.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Entry The entry reference in the dictionary for the value.
 * @return The pointer to the value.
 */
typedef void *(*CCDictionaryGetEntryCallback)(void *Internal, CCDictionaryEntry Entry);

/*!
 * @brief A callback to set the value at a given entry reference.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Entry The entry reference in the dictionary for the value.
 * @param Value The pointer to the value to be copied to the map.
 * @param ValueSize The size of the value.
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCDictionarySetEntryCallback)(void *Internal, CCDictionaryEntry Entry, void *Value, size_t ValueSize, CCAllocatorType Allocator);

/*!
 * @brief A callback to remove the value at a given entry reference.
 * @description The entry point for this value will no longer be valid.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Entry The entry reference in the dictionary to remove the value of.
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCDictionaryRemoveEntryCallback)(void *Internal, CCDictionaryEntry Entry, CCAllocatorType Allocator);

/*!
 * @brief A callback to set the enumerator for the dictionary on a given action and type.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Enumerator The pointer to the enumerator to be used.
 * @param Action The action to be performed.
 * @param Type The type of enumerator.
 * @return The current element at the new position the enumerator has been set to.
 */
typedef void *(*CCDictionaryEnumeratorCallback)(void *Internal, CCEnumeratorState *Enumerator, CCDictionaryEnumeratorAction Action, CCDictionaryEnumeratorType Type);

/*!
 * @brief A callback to get the entry reference for the current enumerator position.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Enumerator The pointer enumerator to be used.
 * @param Type The type of enumerator.
 * @return An entry reference to the current enumerator position.
 */
typedef CCDictionaryEntry (*CCDictionaryEnumeratorEntryCallback)(void *Internal, CCEnumeratorState *Enumerator, CCDictionaryEnumeratorType Type);


#pragma mark - Optional Callbacks

/*!
 * @brief An optional callback to get the value of a given key.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Key The pointer to the key to be used to get the value for.
 * @param KeySize The size of the key.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the implementation will use some default hashing behaviour.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, the implementation will use some default comparison behaviour.
 *
 * @return The pointer to the value.
 */
typedef void *(*CCDictionaryGetValueCallback)(void *Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator);

/*!
 * @brief An optional callback to set the value at a given key.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Key The pointer to the key to be used to set the value of.
 * @param Value The pointer to the value to be copied to the map.
 * @param KeySize The size of the key.
 * @param ValueSize The size of the value.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the implementation will use some default hashing behaviour.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, the implementation will use some default comparison behaviour.
 *
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCDictionarySetValueCallback)(void *Internal, void *Key, void *Value, size_t KeySize, size_t ValueSize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator);

/*!
 * @brief An optional callback to remove the value at a given key.
 * @description The entry point for this value will no longer be valid.
 * @param Internal The pointer to the internal of the dictionary.
 * @param Key The pointer to the key to be used to remove the value of.
 * @param KeySize The size of the key.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the implementation will use some default hashing behaviour.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, the implementation will use some default comparison behaviour.
 *
 * @param Allocator The allocator to be used for any internal allocation needed.
 */
typedef void (*CCDictionaryRemoveValueCallback)(void *Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator);

/*!
 * @brief An optional callback to retrieve the keys in the dictionary.
 * @description Must produce the same order (corresponding pairs) when calling @b CCDictionaryGetValues
 *              if no mutation occurs in-between the two calls.
 *
 * @param Internal The pointer to the internal of the dictionary.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @return The ordered collection of keys. Ownership of this collection is passed to the caller.
 */
typedef CCOrderedCollection (*CCDictionaryGetKeysCallback)(void *Internal, CCAllocatorType Allocator);

/*!
 * @brief An optional callback to retrieve the values in a dictionary.
 * @description Must produce the same order (corresponding pairs) when calling @b CCDictionaryGetKeys
 *              if no mutation occurs in-between the two calls.
 *
 * @param Internal The pointer to the internal of the dictionary.
 * @param Allocator The allocator to be used for any internal allocation needed.
 * @return The ordered collection of values. Ownership of this collection is passed to the caller.
 */
typedef CCOrderedCollection (*CCDictionaryGetValuesCallback)(void *Internal, CCAllocatorType Allocator);


#pragma mark -

/*!
 * @brief The interface to the internal implementation.
 * @description Optional interfaces do not need to be implemented and will instead be supported
 *              through reusing the required interfaces.
 */
typedef struct {
    CCDictionaryHintWeightCallback hintWeight;
    CCDictionaryConstructorCallback create;
    CCDictionaryDestructorCallback destroy;
    CCDictionaryGetCountCallback count;
    CCDictionaryEntryIsInitializedCallback initialized;
    CCDictionaryFindKeyCallback findKey;
    CCDictionaryEntryForKeyCallback entryForKey;
    CCDictionaryGetKeyCallback getKey;
    CCDictionaryGetEntryCallback getEntry;
    CCDictionarySetEntryCallback setEntry;
    CCDictionaryRemoveEntryCallback removeEntry;
    CCDictionaryEnumeratorCallback enumerator;
    CCDictionaryEnumeratorEntryCallback enumeratorReference;
    struct {
        CCDictionaryGetValueCallback getValue;
        CCDictionarySetValueCallback setValue;
        CCDictionaryRemoveValueCallback removeValue;
        CCDictionaryGetKeysCallback keys;
        CCDictionaryGetValuesCallback values;
    } optional;
} CCDictionaryInterface;


#pragma mark - Interface Handling

/*!
 * @brief The maximum weight value produced by CCDictionaryHintWeightCreate.
 * @description This is the maximum weight any of the framework's interfaces may reach. To push
 * your own interfaces above the internal ones, you use can use this max weight to add onto. Where
 * CCDictionaryHintWeightMax + 1 is guaranteed to be chosen above any of the internal interfaces
 * that are provided.
 */
extern const int CCDictionaryHintWeightMax;

/*!
 * @brief Calculate a weight for the given hint combination.
 * @description The max value returned by this is CCDictionaryHintWeightMax.
 * @param Hint The hints describing the intended usage of the dictionary.
 * @param FastHints Hints with a worst case that is considered fast for the given operation.
 * @param ModerateHints Hints with a worst case that is considered decent for the given operation.
 * @param SlowHints Hints with worst case that is considered slow for the given operation.
 * @return The weight value.
 */
int CCDictionaryHintWeightCreate(CCDictionaryHint Hint, CCDictionaryHint FastHints, CCDictionaryHint ModerateHints, CCDictionaryHint SlowHints);

/*!
 * @brief Register a dictionary interface with the system.
 * @description The interface is chosen based on how appropriate it is with the current hints.
 * @param Interface The interface to register.
 */
void CCDictionaryRegisterInterface(const CCDictionaryInterface *Interface);

/*!
 * @brief Deregister a dictionary interface from the system.
 * @description The interface can no longer be chosen.
 * @param Interface The interface to register.
 */
void CCDictionaryDeregisterInterface(const CCDictionaryInterface *Interface);

#endif
