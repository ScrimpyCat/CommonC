/*
 *  Copyright (c) 2023, Stefan Johnson
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

#include <CommonC/Template.h>

#define CCBitsGet_T(t) CC_TEMPLATE_REF(CCBitsGet, _Bool, t, size_t)
#define CCBitsSet_T(t) CC_TEMPLATE_REF(CCBitsSet, void, t, size_t)
#define CCBitsClear_T(t) CC_TEMPLATE_REF(CCBitsClear, void, t, size_t)

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsGet, (const T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSet, (T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClear, (T Set, const size_t Index));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsGet, (const T Set, const size_t Index))
{
    return Set[Index / (sizeof(*Set) * 8)] & (1 << (Index % (sizeof(*Set) * 8)));
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSet, (T Set, const size_t Index))
{
    Set[Index / (sizeof(*Set) * 8)] |= 1 << (Index % (sizeof(*Set) * 8));
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClear, (T Set, const size_t Index))
{
    Set[Index / (sizeof(*Set) * 8)] &= ~(1 << (Index % (sizeof(*Set) * 8)));
}
