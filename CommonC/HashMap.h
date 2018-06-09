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

#ifndef CommonC_HashMap_h
#define CommonC_HashMap_h

#include <CommonC/Base.h>
#include <CommonC/HashMapInterface.h>
#include <CommonC/Allocator.h>
#include <CommonC/Enumerator.h>
#include <CommonC/Comparator.h>
#include <CommonC/Assertion.h>


/*!
 * @brief A callback to handle custom destruction of an element when it is removed from the collection.
 * @param Key The key to generate a hash of.
 * @return The hash representing the key.
 */
typedef uintmax_t (*CCHashMapKeyHasher)(const void *Key);


typedef struct CCHashMapInfo {
    const CCHashMapInterface *interface;
    CCAllocatorType allocator;
    CCHashMapKeyHasher getHash;
    CCComparator compareKeys;
    size_t keySize, valueSize;
    size_t bucketCount;
    void *internal;
} CCHashMapInfo;


#pragma mark - Creation/Destruction
/*!
 * @brief Create a hashmap.
 * @param Allocator The allocator to be used for the allocation.
 * @param KeySize The size of the keys.
 * @param ValueSize The size of the values.
 * @param BucketCount The number of buckets to be allocated.
 * @param Hasher The hashing function to be used to generate a hash for a given key. If
 *        NULL, the key will default as the hash itself. The default hashing works by
 *        converting the key to a uintmax_t, if the key size is smaller than it is promoted,
 *        if larger than the first bytes that make up a uintmax_t are used.
 *
 * @param KeyComparator The key comparison function to be used to determine if two keys
 *        match. If NULL, a byte level comparison is performed.
 *
 * @param Interface The interface to the internal implementation to be used.
 *
 * @return An empty hashmap, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCHashMap CCHashMapCreate(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount, CCHashMapKeyHasher Hasher, CCComparator KeyComparator, const CCHashMapInterface *Interface);

/*!
 * @brief Destroy an hashmap.
 * @param Map The hashmap to be destroyed.
 */
void CCHashMapDestroy(CCHashMap CC_DESTROY(Map));

/*!
 * @brief Rehash the hashmap.
 * @param Map The hashmap to be rehashed.
 * @param BucketCount The number of buckets to be allocated.
 */
void CCHashMapRehash(CCHashMap Map, size_t BucketCount);


#pragma mark - Insertions/Deletions
/*!
 * @brief Set the value at a given entry reference.
 * @param Map The hashmap to set the value of.
 * @param Entry The entry reference in the hashmap for the value.
 * @param Value The pointer to the value to be copied to the map.
 */
void CCHashMapSetEntry(CCHashMap Map, CCHashMapEntry Entry, const void *Value);

/*!
 * @brief Remove the value at a given entry reference.
 * @description The entry point for this value will no longer be valid.
 * @param Map The hashmap to remove the value from.
 * @param Entry The entry reference in the hashmap to remove the value of.
 */
void CCHashMapRemoveEntry(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief Sets the value at a given key.
 * @warning The size of key/value must be the same size as specified in the hashmap creation.
 * @param Map The hashmap to set the value of.
 * @param Key The pointer to the key to be used to set the value of.
 * @param Value The pointer to the value to be copied to the map.
 */
void CCHashMapSetValue(CCHashMap Map, const void *Key, const void *Value);

/*!
 * @brief Remove the value at a given key.
 * @warning The size of key must be the same size as specified in the hashmap creation.
 * @param Map The hashmap to remove the value from.
 * @param Key The pointer to the key to be used to remove the value of.
 */
void CCHashMapRemoveValue(CCHashMap Map, const void *Key);

/*!
 * @brief Obtain an entry for a given key.
 * @description If an entry doesn't exist for the key, one will be created.
 * @warning If an entry is created then querying its value is undefined.
 * @param Map The hashmap to create a key for.
 * @param Key The pointer to the key to be found or created.
 * @param Created Set whether the entry reference was created (TRUE) or whether it
 *        already existed (FALSE). This may be NULL.
 *
 * @return The entry reference.
 */
CCHashMapEntry CCHashMapEntryForKey(CCHashMap Map, const void *Key, _Bool *Created);


#pragma mark - Query Info
/*!
 * @brief Check whether a given entry has been initialized.
 * @param Map The hashmap containing the entry.
 * @param Entry The entry reference.
 * @return TRUE if the entry has been initialized, FALSE if is uninitialized.
 */
_Bool CCHashMapEntryIsInitialized(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief Find a given key.
 * @description If no key is found, the entry reference will be NULL.
 * @param Map The hashmap to find the key of.
 * @param Key The pointer to the key to be found.
 * @return The entry reference.
 */
CCHashMapEntry CCHashMapFindKey(CCHashMap Map, const void *Key);

/*!
 * @brief Get the value of a given entry reference.
 * @param Map The hashmap to get the value of.
 * @param Entry The entry reference in the hashmap for the value.
 * @return The pointer to the value.
 */
void *CCHashMapGetEntry(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief Get the value of a given key.
 * @warning The size of key must be the same size as specified in the hashmap creation.
 * @param Map The hashmap to get the value of.
 * @param Key The pointer to the key to be used to get the value for.
 * @return The pointer to the value.
 */
void *CCHashMapGetValue(CCHashMap Map, const void *Key);

/*!
 * @brief Get the key of a given entry reference.
 * @param Map The hashmap to get the value of.
 * @param Entry The entry reference in the hashmap for the key.
 * @return The pointer to the key.
 */
void *CCHashMapGetKey(CCHashMap Map, CCHashMapEntry Entry);

/*!
 * @brief Get the keys in a hashmap.
 * @description Will produce the same order (corresponding pairs) when calling @b CCHashMapGetValues
 *              if no mutation occurs in-between the two calls. After mutation occurs there is no
 *              guarantee that the order will stay the same.
 *
 * @param Map The hashmap to get the keys of.
 * @return The ordered collection of keys. The collection must be destroyed.
 */
CC_NEW CCOrderedCollection CCHashMapGetKeys(CCHashMap Map);

/*!
 * @brief Get the values in a hashmap.
 * @description Will produce the same order (corresponding pairs) when calling @b CCHashMapGetKeys
 *              if no mutation occurs in-between the two calls. After mutation occurs there is no
 *              guarantee that the order will stay the same.
 *
 * @param Map The hashmap to get the values of.
 * @return The ordered collection of values. The collection must be destroyed.
 */
CC_NEW CCOrderedCollection CCHashMapGetValues(CCHashMap Map);

/*!
 * @brief Get a key enumerator for the hashmap.
 * @param Map The hashmap to obtain a key enumerator for.
 * @param Enumerator A pointer to the enumerator to use.
 */
void CCHashMapGetKeyEnumerator(CCHashMap Map, CCEnumerator *Enumerator);

/*!
 * @brief Get a value enumerator for the hashmap.
 * @param Map The hashmap to obtain a value enumerator for.
 * @param Enumerator A pointer to the enumerator to use.
 */
void CCHashMapGetValueEnumerator(CCHashMap Map, CCEnumerator *Enumerator);

/*!
 * @brief Get the hash for a given key.
 * @param Map The hashmap to get the hash of the key for.
 * @param Key The pointer to the key to get the hash of.
 * @return The hash.
 */
uintmax_t CCHashMapGetKeyHash(CCHashMap Map, const void *Key);

/*!
 * @brief Get the current number of key/values in the hashmap.
 * @param Map The hashmap to get the count of.
 * @return The number of key/values.
 */
size_t CCHashMapGetCount(CCHashMap Map);

/*!
 * @brief Get the current load factor of the hashmap.
 * @description The ratio between the amount of entries to buckets.
 * @param Map The hashmap to get the load factor of.
 * @return The load factor ratio.
 */
float CCHashMapGetLoadFactor(CCHashMap Map);

/*!
 * @brief Get the number of buckets in the hashmap.
 * @param Map The hashmap to get the number of buckets of.
 * @return The number of buckets.
 */
static inline size_t CCHashMapGetBucketCount(CCHashMap Map);

/*!
 * @brief Get the value size of the hashmap.
 * @param Map The hashmap to get the key size of.
 * @return The size of keys.
 */
static inline size_t CCHashMapGetKeySize(CCHashMap Map);

/*!
 * @brief Get the key size of the hashmap.
 * @param Map The hashmap to get the value size of.
 * @return The size of values.
 */
static inline size_t CCHashMapGetValueSize(CCHashMap Map);


#pragma mark -
static inline size_t CCHashMapGetBucketCount(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->bucketCount;
}

static inline size_t CCHashMapGetKeySize(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->keySize;
}

static inline size_t CCHashMapGetValueSize(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->valueSize;
}

#endif
