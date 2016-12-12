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

#ifndef CommonC_Dictionary_h
#define CommonC_Dictionary_h

#include <stdio.h>
#include <CommonC/DictionaryInterface.h>
#include <CommonC/Allocator.h>
#include <CommonC/Enumerator.h>
#include <CommonC/Comparator.h>


/*!
 * @brief A callback to handle custom destruction of a key/value when it is removed from the dictionary.
 * @param Dictionary The collection the element is from.
 * @param Element The element being removed.
 */
typedef void (*CCDictionaryElementDestructor)(CCDictionary Dictionary, void *Element);


typedef struct {
    CCDictionaryElementDestructor keyDestructor;
    CCDictionaryElementDestructor valueDestructor;
    CCDictionaryKeyHasher getHash;
    CCComparator compareKeys;
} CCDictionaryCallbacks;

typedef struct CCDictionaryInfo {
    const CCDictionaryInterface *interface;
    CCAllocatorType allocator;
    CCDictionaryCallbacks callbacks;
    size_t keySize, valueSize;
    void *internal;
} CCDictionaryInfo;


#pragma mark - Creation/Destruction
/*!
 * @brief Create a dictionary based on the intended usage.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this dictionary. This will decided the appropriate
 *        internal implementation to be used.
 *
 * @param KeySize The key size.
 * @param ValueSize The value size.
 * @param Callbacks Optional callbacks for the dictionary. May be NULL.
 * @return An empty dictionary, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCDictionary CCDictionaryCreate(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, const CCDictionaryCallbacks *Callbacks);

/*!
 * @brief Create a dictionary with the specified implementation.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this dictionary.
 * @param KeySize The key size.
 * @param ValueSize The value size.
 * @param Callbacks Optional callbacks for the dictionary. May be NULL.
 * @param Interface The interface to the internal implementation to be used.
 * @return An empty dictionary, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCDictionary CCDictionaryCreateWithImplementation(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, const CCDictionaryCallbacks *Callbacks, const CCDictionaryInterface *Interface);

/*!
 * @brief Destroy an dictionary.
 * @param Dictionary The dictionary to be destroyed.
 */
void CCDictionaryDestroy(CCDictionary CC_DESTROY(Dictionary));


#pragma mark - Insertions/Deletions
/*!
 * @brief Set the value at a given entry reference.
 * @param Dictionary The dictionary to set the value of.
 * @param Entry The entry reference in the dictionary for the value.
 * @param Value The pointer to the value to be copied to the map.
 */
void CCDictionarySetEntry(CCDictionary Dictionary, CCDictionaryEntry Entry, const void *Value);

/*!
 * @brief Remove the value at a given entry reference.
 * @description The entry point for this value will no longer be valid.
 * @param Dictionary The dictionary to remove the value from.
 * @param Entry The entry reference in the dictionary to remove the value of.
 */
void CCDictionaryRemoveEntry(CCDictionary Dictionary, CCDictionaryEntry Entry);

/*!
 * @brief Sets the value at a given key.
 * @warning The size of key/value must be the same size as specified in the dictionary creation.
 * @param Dictionary The dictionary to set the value of.
 * @param Key The pointer to the key to be used to set the value of.
 * @param Value The pointer to the value to be copied to the map.
 */
void CCDictionarySetValue(CCDictionary Dictionary, const void *Key, const void *Value);

/*!
 * @brief Remove the value at a given key.
 * @warning The size of key must be the same size as specified in the dictionary creation.
 * @param Dictionary The dictionary to remove the value from.
 * @param Key The pointer to the key to be used to remove the value of.
 */
void CCDictionaryRemoveValue(CCDictionary Dictionary, const void *Key);

/*!
 * @brief Obtain an entry for a given key.
 * @description If an entry doesn't exist for the key, one will be created. A newly created entry
 *              will be uninitialized, to check for this call @b CCDictionaryEntryIsInitialized.
 *
 * @warning If an entry is created then querying its value is undefined.
 * @param Dictionary The dictionary to create a key for.
 * @param Key The pointer to the key to be found or created.
 * @return The entry reference.
 */
CCDictionaryEntry CCDictionaryEntryForKey(CCDictionary Dictionary, const void *Key);


#pragma mark - Query Info
/*!
 * @brief Check whether a given entry has been initialized.
 * @param Dictionary The dictionary containing the entry.
 * @param Entry The entry reference.
 * @return TRUE if the entry has been initialized, FALSE if is uninitialized.
 */
_Bool CCDictionaryEntryIsInitialized(CCDictionary Dictionary, CCDictionaryEntry Entry);

/*!
 * @brief Find a given key.
 * @description If no key is found, the entry reference will be NULL.
 * @param Dictionary The dictionary to find the key of.
 * @param Key The pointer to the key to be found.
 * @return The entry reference.
 */
CCDictionaryEntry CCDictionaryFindKey(CCDictionary Dictionary, const void *Key);

/*!
 * @brief Get the value of a given entry reference.
 * @param Dictionary The dictionary to get the value of.
 * @param Entry The entry reference in the dictionary for the value.
 * @return The pointer to the value.
 */
void *CCDictionaryGetEntry(CCDictionary Dictionary, CCDictionaryEntry Entry);

/*!
 * @brief Get the value of a given key.
 * @warning The size of key must be the same size as specified in the dictionary creation.
 * @param Dictionary The dictionary to get the value of.
 * @param Key The pointer to the key to be used to get the value for.
 * @return The pointer to the value.
 */
void *CCDictionaryGetValue(CCDictionary Dictionary, const void *Key);

/*!
 * @brief Get the key of a given entry reference.
 * @param Dictionary The dictionary to get the value of.
 * @param Entry The entry reference in the dictionary for the key.
 * @return The pointer to the key.
 */
void *CCDictionaryGetKey(CCDictionary Dictionary, CCDictionaryEntry Entry);

/*!
 * @brief Get the keys in a dictionary.
 * @description Will produce the same order (corresponding pairs) when calling @b CCDictionaryGetValues
 *              if no mutation occurs in-between the two calls. After mutation occurs there is no
 *              guarantee that the order will stay the same.
 *
 * @param Dictionary The dictionary to get the keys of.
 * @return The ordered collection of keys. The collection must be destroyed.
 */
CC_NEW CCOrderedCollection CCDictionaryGetKeys(CCDictionary Dictionary);

/*!
 * @brief Get the values in a dictionary.
 * @description Will produce the same order (corresponding pairs) when calling @b CCDictionaryGetKeys
 *              if no mutation occurs in-between the two calls. After mutation occurs there is no
 *              guarantee that the order will stay the same.
 *
 * @param Dictionary The dictionary to get the values of.
 * @return The ordered collection of values. The collection must be destroyed.
 */
CC_NEW CCOrderedCollection CCDictionaryGetValues(CCDictionary Dictionary);

/*!
 * @brief Get a key enumerator for the dictionary.
 * @param Dictionary The dictionary to obtain a key enumerator for.
 * @param Enumerator A pointer to the enumerator to use.
 */
void CCDictionaryGetKeyEnumerator(CCDictionary Dictionary, CCEnumerator *Enumerator);

/*!
 * @brief Get a value enumerator for the dictionary.
 * @param Dictionary The dictionary to obtain a value enumerator for.
 * @param Enumerator A pointer to the enumerator to use.
 */
void CCDictionaryGetValueEnumerator(CCDictionary Dictionary, CCEnumerator *Enumerator);

/*!
 * @brief Get the current number of key/values in the dictionary.
 * @param Dictionary The dictionary to get the count of.
 * @return The number of key/values.
 */
size_t CCDictionaryGetCount(CCDictionary Dictionary);

/*!
 * @brief Get the value size of the dictionary.
 * @param Dictionary The dictionary to get the key size of.
 * @return The size of keys.
 */
size_t CCDictionaryGetKeySize(CCDictionary Dictionary);

/*!
 * @brief Get the key size of the dictionary.
 * @param Dictionary The dictionary to get the value size of.
 * @return The size of values.
 */
size_t CCDictionaryGetValueSize(CCDictionary Dictionary);

#endif
