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
 * @header CCHashMapSeparateChainingArray
 * CCHashMapSeparateChainingArray is an interface for an array backed separately chained hashmap
 * implementation. Hashes, keys, and values are all stored together in the same block.
 *
 * Fast Operations:
 * - Lookup.
 * - Insertion.
 *
 * Moderate Operations:
 * - Enumerating of keys. (slower than other @b CCHashMapSeparateChainingArray* variants)
 * - Enumerating of values. (slower than other @b CCHashMapSeparateChainingArray* variants)
 */
#ifndef CommonC_HashMapSeparateChainingArray_h
#define CommonC_HashMapSeparateChainingArray_h

#include <CommonC/HashMapInterface.h>
#include <CommonC/Array.h>

typedef struct {
    size_t count;
    CCArray(CCArray) buckets;
} CCHashMapSeparateChainingArrayInternal;

extern const CCHashMapInterface CCHashMapSeparateChainingArrayInterface;

#define CCHashMapSeparateChainingArray &CCHashMapSeparateChainingArrayInterface

/*!
 * @define CC_STATIC_HASH_MAP_SEPARATE_CHAINING_ARRAY
 * @abstract Convenient macro to create a temporary (allocation free) @b CCHashMapSeparateChainingArray.
 *           for a CCHashMap internal.
 *
 * @discussion If used globally it will last for the life of the program, however if used within a function
 *             it will last for the entirety of the local scope.
 *
 * @param count The key/value count.
 * @param buckets The array of array of hash, key, value. May be NULL.
 */
#define CC_STATIC_HASH_MAP_SEPARATE_CHAINING_ARRAY(count, buckets) CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_CREATE(count, buckets)

/*!
 * @define CC_CONST_HASH_MAP_SEPARATE_CHAINING_ARRAY
 * @abstract Convenient macro to create a temporary constant (allocation free) @b CCHashMapSeparateChainingArray.
 *           for a CCHashMap internal.
 *
 * @discussion If used globally it will last for the life of the program, however if used within a function
 *             it will last for the entirety of the local scope.
 *
 * @param count The key/value count.
 * @param buckets The array of array of hash, key, value. May be NULL.
 */
#define CC_CONST_HASH_MAP_SEPARATE_CHAINING_ARRAY(count, buckets) CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_CREATE(count, buckets, const)

#define CC_HASH_MAP_SEPARATE_CHAINING_ARRAY_CREATE(count_, buckets_, ...) \
((CCHashMapSeparateChainingArrayInternal*)&(__VA_ARGS__ struct { \
    CCAllocatorHeader header; \
    CCHashMapSeparateChainingArrayInternal info; \
}){ \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_NULL_ALLOCATOR.allocator), \
    .info = { \
        .count = count_, \
        .buckets = buckets_ \
    } \
}.info)

#endif
