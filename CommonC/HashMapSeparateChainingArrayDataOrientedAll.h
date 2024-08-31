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
 * @header CCHashMapSeparateChainingArrayDataOrientedAll
 * CCHashMapSeparateChainingArrayDataOrientedAll is an interface for an array backed separately chained
 * hashmap implementation. How this differs from @b CCHashMapSeparateChainingArrayDataOrientedHash and
 * @b CCHashMapSeparateChainingArray is that hashes, keys, and values are all stored in separate arrays.
 * This allows for improved enumeration of keys or values, but a reduction in lookup and insertion compared
 * to the other separately chained array variants. Is better when there's a poor hash distribution or
 * a poor load factor, otherwise @b CCHashMapSeparateChainingArray is likely the better variation.
 *
 * Fast Operations:
 * - Lookup. (slower than other @b CCHashMapSeparateChainingArray* variants)
 * - Insertion. (slower than other @b CCHashMapSeparateChainingArray* variants)
 *
 * Moderate Operations:
 * - Enumerating of keys. (faster than other @b CCHashMapSeparateChainingArray* variants)
 * - Enumerating of values. (faster than other @b CCHashMapSeparateChainingArray* variants)
 */
#ifndef CommonC_HashMapSeparateChainingArrayDataOrientedAll_h
#define CommonC_HashMapSeparateChainingArrayDataOrientedAll_h

#include <CommonC/HashMapInterface.h>
#include <CommonC/Array.h>

typedef struct {
    size_t count;
    CCArray(CCArray(uintmax_t)) hashes;
    CCArray(CCArray) keys;
    CCArray(CCArray) values;
} CCHashMapSeparateChainingArrayDataOrientedAllInternal;

extern const CCHashMapInterface CCHashMapSeparateChainingArrayDataOrientedAllInterface;

#define CCHashMapSeparateChainingArrayDataOrientedAll &CCHashMapSeparateChainingArrayDataOrientedAllInterface

/*!
 * @define CC_STATIC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL
 * @abstract Convenient macro to create a temporary (allocation free) @b CCHashMapSeparateChainingArrayDataOrientedAll.
 *           for a CCHashMap internal.
 *
 * @discussion If used globally it will last for the life of the program, however if used within a function
 *             it will last for the entirety of the local scope.
 *
 * @param count The key/value count.
 * @param hashes The array of array of hashes. May be NULL.
 * @param keys The array of array of keys. May be NULL.
 * @param values The array of array of values. May be NULL.
 */
#define CC_STATIC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL(count, hashes, keys, values) CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL_CREATE(count, hashes, keys, values)

/*!
 * @define CC_CONST_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL
 * @abstract Convenient macro to create a temporary constant (allocation free) @b CCHashMapSeparateChainingArrayDataOrientedAll.
 *           for a CCHashMap internal.
 *
 * @discussion If used globally it will last for the life of the program, however if used within a function
 *             it will last for the entirety of the local scope.
 *
 * @param count The key/value count.
 * @param hashes The array of array of hashes. May be NULL.
 * @param keys The array of array of keys. May be NULL.
 * @param values The array of array of values. May be NULL.
 */
#define CC_CONST_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL(count, hashes, keys, values) CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL_CREATE(count, hashes, keys, values, const)

#define CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_DATA_ORIENTED_ALL_CREATE(count_, hashes_, keys_, values_, __VA_ARGS__) \
((CCHashMapSeparateChainingArrayDataOrientedAllInternal)&(__VA_ARGS__ struct { \
    CCAllocatorHeader header; \
    CCHashMapSeparateChainingArrayDataOrientedAllInternal info; \
}){ \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_NULL_ALLOCATOR.allocator), \
    .info = { \
        .count = count_, \
        .hashes = hashes_, \
        .keys = keys_, \
        .values = values_ \
    } \
}.info)

#endif
