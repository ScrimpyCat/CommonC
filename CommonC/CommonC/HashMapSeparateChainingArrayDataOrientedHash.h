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
 * are stored in a separate array to keys and values. Is better when there's a portioned hash distribution
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

extern const CCHashMapInterface * const CCHashMapSeparateChainingArrayDataOrientedHash;

#endif
