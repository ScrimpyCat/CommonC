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
#include <CommonC/BitTricks.h>

#define CCBitsGet_T(t) CC_TEMPLATE_REF(CCBitsGet, _Bool, t, size_t)
#define CCBitsSet_T(t) CC_TEMPLATE_REF(CCBitsSet, void, t, size_t)
#define CCBitsClear_T(t) CC_TEMPLATE_REF(CCBitsClear, void, t, size_t)
#define CCBitsCount_T(t) CC_TEMPLATE_REF(CCBitsCount, size_t, t, size_t, size_t)

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsGet, (const T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSet, (T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClear, (T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCBitsCount, (const T Set, const size_t Index, const size_t Count));

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

CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCBitsCount, (const T Set, const size_t Index, const size_t Count))
{
    size_t SetCount = 0;
    
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    const uint64_t * const Set64 = (uint64_t*)(((uint8_t*)Set) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        SetCount += CCBitCountSet(Set64[Loop]);
    }
    
    uint64_t Remainder = 0;
    if (Index % 8)
    {
        Remainder = ((uint8_t*)Set)[Offset8 - 1] & (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
    }
    
    else if (Count < 8)
    {
        Remainder = ((uint8_t*)Set)[Offset8] & (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    const uint8_t * const Set8 = ((uint8_t*)Set) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        Remainder |= (uint64_t)Set8[Loop] << ((Loop + 1) * 8);
    }
    
    if (IndexAdjustedCount % 8)
    {
        if (Index % 8)
        {
            if (Count8 == 7)
            {
                SetCount += CCBitCountSet(Remainder);
                Remainder = Set8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1);
            }
            
            else
            {
                Remainder |= (uint64_t)Set8[Count8] << (56 + (8 - (IndexAdjustedCount % 8)));
            }
        }
        
        else
        {
            Remainder |= Set8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1);
        }
    }
    
    SetCount += CCBitCountSet(Remainder);
    
    return SetCount;
}
