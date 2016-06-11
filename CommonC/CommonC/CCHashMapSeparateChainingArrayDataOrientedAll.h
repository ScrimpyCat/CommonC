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
 * @b CCHashMapSeparateChainingArray. Is that hashes, keys, and values are all stored in separate arrays.
 * This allows for improved enumeration of keys or values, but a reduction in lookup and insertion compared
 * to the other separately chained array variants.
 *
 * Fast Operations:
 * - Lookup. (slower than other @b CCHashMapSeparateChainingArray* variants)
 * - Insertion. (slower than other @b CCHashMapSeparateChainingArray* variants)
 *
 * Moderate Operations:
 * - Enumerating of keys. (faster than other @b CCHashMapSeparateChainingArray* variants)
 * - Enumerating of values. (faster than other @b CCHashMapSeparateChainingArray* variants)
 */
#ifndef CommonC_CCHashMapSeparateChainingArrayDataOrientedAll_h
#define CommonC_CCHashMapSeparateChainingArrayDataOrientedAll_h

#include <CommonC/HashMapInterface.h>

extern const CCHashMapInterface * const CCHashMapSeparateChainingArrayDataOrientedAll;

#endif
