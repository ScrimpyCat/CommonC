/*
 *  Copyright (c) 2024, Stefan Johnson
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

#ifndef CommonC_CircularEnumerable_h
#define CommonC_CircularEnumerable_h

#include <CommonC/Enumerable.h>
#include <CommonC/Assertion.h>


/*!
 * @brief Create an enumerable for a circular buffer of values.
 * @param Ptr A pointer to the base of the buffer.
 * @param Stride The size of the value.
 * @param Count The number of values.
 * @param Start The index to start from.
 * @param Max The maximum size of the buffer.
 * @return The enumerable.
 */
static CC_FORCE_INLINE CCEnumerable CCCircularEnumerableCreate(void *Ptr, size_t Stride, size_t Count, size_t Start, size_t Max);

void *CCCircularEnumerableHandler(CCEnumerator *Enumerator, CCEnumerableAction Action);

#pragma mark -

static CC_FORCE_INLINE CCEnumerable CCCircularEnumerableCreate(void *Ptr, size_t Stride, size_t Count, size_t Start, size_t Max)
{
    CCAssertLog(Count <= Max, "Count should not exceed Max");
    CCAssertLog(Start < Max, "Start must not be out of bounds");
    
    return (CCEnumerable){
        .handler = CCCircularEnumerableHandler,
        .enumerator = {
            .ref = Ptr,
            .state = {
                .circular = {
                    .ptr = Ptr,
                    .count = Count,
                    .stride = Stride,
                    .index = Start,
                    .max = Max,
                    .start = Start
                },
                .type = CCEnumeratorFormatCircular
            }
        }
    };
}

#endif
