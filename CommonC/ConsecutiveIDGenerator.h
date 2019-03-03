/*
 *  Copyright (c) 2018, Stefan Johnson
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
 * @header CCConsecutiveIDGenerator
 * CCConsecutiveIDGenerator is an interface for a consecutive (0 to Count-1) ID generator.
 * This ID generator is lock-free and is ideally meant for when you need a consecutive ID
 * (index) and have a known amount of possible accessors (which should be relatively small).
 * Those accessors can then retrieve or recycle as frequently or infrequently
 * as they want.
 *
 * This ID creation pattern is not suited for small pools where IDs are not recycled frequently,
 * but lots of threads are attempting to retrieve an ID, as this will result in many threads
 * being starved. Nor is it suited for situations where a large number of IDs needs to be
 * distributed, as this will result in retrieval time taking too long (if those IDs are not being
 * recycled frequently enough).
 *
 * Allows for many producer-consumer access.
 */
#ifndef CommonC_ConcurrentIDPool_h
#define CommonC_ConcurrentIDPool_h

#include <CommonC/ConcurrentIDGeneratorInterface.h>

/*!
 * @brief A lockfree consecutive ID generator.
 * @description The base ID will start at 0 and go up to (Count - 1). Due to this if the
 *              Count = 2^8 then the ID will be one that can fit within an uint8_t.
 *
 * @performance Assigning is lock-free and has a worst case of O(n + n/8). While recycling
 *              is a wait-free O(1) operation.
 */
extern const CCConcurrentIDGeneratorInterface * const CCConsecutiveIDGenerator;

#endif
