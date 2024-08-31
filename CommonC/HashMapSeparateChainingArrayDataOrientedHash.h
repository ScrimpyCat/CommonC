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

/*!
 * @header CCHashMapSeparateChainingArrayDataOrientedHash
 * CCHashMapSeparateChainingArrayDataOrientedHash is an interface for an array backed separately chained
 * hashmap implementation. How this differs from @b CCHashMapSeparateChainingArray and is that hashes, 
 * are stored in a separate array to keys and values. Is better when there's a poor hash distribution
 * or a poor load factor, otherwise @b CCHashMapSeparateChainingArray is likely the better variation.
 *
 * Fast Operations:
 * - Lookup. (slower than other @b CCHashMapSeparateChainingArray* variants)
 * - Insertion. (slower than other @b CCHashMapSeparateChainingArray* variants)
 *
 * Moderate Operations:
 * - Enumerating of keys. (faster than other @b CCHashMapSeparateChainingArray variant)
 * - Enumerating of values. (faster than other @b CCHashMapSeparateChainingArray variant)
 */
#ifndef CommonC_HashMapSeparateChainingArrayDataOrientedHash_h
#define CommonC_HashMapSeparateChainingArrayDataOrientedHash_h

#include <CommonC/HashMapInterface.h>
#include <CommonC/Array.h>

typedef struct {
    size_t count;
    CCArray(CCArray(uintmax_t)) hashes;
    CCArray(CCArray) buckets;
} CCHashMapSeparateChainingArrayDataOrientedHashInternal;

extern const CCHashMapInterface CCHashMapSeparateChainingArrayDataOrientedHashInterface;

#define CCHashMapSeparateChainingArrayDataOrientedHash &CCHashMapSeparateChainingArrayDataOrientedHashInterface

/*!
 * @define CC_STATIC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH
 * @abstract Convenient macro to create a temporary (allocation free) @b CCHashMapSeparateChainingArrayDataOrientedHash.
 *           for a CCHashMap internal.
 *
 * @discussion If used globally it will last for the life of the program, however if used within a function
 *             it will last for the entirety of the local scope.
 *
 * @param count The key/value count.
 * @param hashes The array of array of hashes. May be NULL.
 * @param buckets The array of array of hash, key, value. May be NULL.
 */
#define CC_STATIC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH(count, hashes, buckets) CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH_CREATE(count, hashes, buckets)

/*!
 * @define CC_CONST_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH
 * @abstract Convenient macro to create a temporary constant (allocation free) @b CCHashMapSeparateChainingArrayDataOrientedHash.
 *           for a CCHashMap internal.
 *
 * @discussion If used globally it will last for the life of the program, however if used within a function
 *             it will last for the entirety of the local scope.
 *
 * @param count The key/value count.
 * @param hashes The array of array of hashes. May be NULL.
 * @param buckets The array of array of hash, key, value. May be NULL.
 */
#define CC_CONST_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH(count, hashes, buckets) CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH_CREATE(count, hashes, buckets, const)

#define CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_HASH_CREATE(count_, hashes_, buckets_, __VA_ARGS__) \
((CCHashMapSeparateChainingArrayDataOrientedHashInternal)&(__VA_ARGS__ struct { \
    CCAllocatorHeader header; \
    CCHashMapSeparateChainingArrayDataOrientedHashInternal info; \
}){ \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_NULL_ALLOCATOR.allocator), \
    .info = { \
        .count = count_, \
        .hashes = hashes_, \
        .buckets = buckets_ \
    } \
}.info)

#endif
