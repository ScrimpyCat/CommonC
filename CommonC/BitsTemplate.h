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
#include <CommonC/Swap.h>

#define CCBitsGet_T(t) CC_TEMPLATE_REF(CCBitsGet, _Bool, t, size_t)
#define CCBitsSet_T(t) CC_TEMPLATE_REF(CCBitsSet, void, t, size_t)
#define CCBitsClear_T(t) CC_TEMPLATE_REF(CCBitsClear, void, t, size_t)
#define CCBitsSetRange_T(t) CC_TEMPLATE_REF(CCBitsSetRange, void, t, size_t, size_t)
#define CCBitsClearRange_T(t) CC_TEMPLATE_REF(CCBitsClearRange, void, t, size_t, size_t)
#define CCBitsCount_T(t) CC_TEMPLATE_REF(CCBitsCount, size_t, t, size_t, size_t)
#define CCBitsAny_T(t) CC_TEMPLATE_REF(CCBitsAny, _Bool, t, size_t, size_t)
#define CCBitsMask_T(t) CC_TEMPLATE_REF(CCBitsMask, size_t, t, t, size_t, size_t, PTYPE(size_t *))
#define CCBitsNot_T(t) CC_TEMPLATE_REF(CCBitsNot, void, t, size_t, size_t)
#define CCBitsOr_T(t) CC_TEMPLATE_REF(CCBitsOr, void, t, t, size_t, size_t)
#define CCBitsAnd_T(t) CC_TEMPLATE_REF(CCBitsAnd, void, t, t, size_t, size_t)
#define CCBitsXor_T(t) CC_TEMPLATE_REF(CCBitsXor, void, t, t, size_t, size_t)

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsGet, (const T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSet, (T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClear, (T Set, const size_t Index));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSetRange, (T Set, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClearRange, (T Set, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCBitsCount, (const T Set, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsAny, (const T Set, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCBitsMask, (const T SetA, const T SetB, const size_t Index, const size_t Count, PTYPE(size_t *) Indexes));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsNot, (const T Set, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsOr, (const T SetA, const T SetB, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsAnd, (const T SetA, const T SetB, const size_t Index, const size_t Count));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsXor, (const T SetA, const T SetB, const size_t Index, const size_t Count));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsGet, (const T Set, const size_t Index))
{
#if CC_HARDWARE_ENDIAN_LITTLE
    return Set[Index / (sizeof(*Set) * 8)] & (1 << (Index % (sizeof(*Set) * 8)));
#else
    return ((uint8_t*)Set)[Index / (sizeof(uint8_t) * 8)] & (1 << (Index % (sizeof(uint8_t) * 8)));
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSet, (T Set, const size_t Index))
{
#if CC_HARDWARE_ENDIAN_LITTLE
    Set[Index / (sizeof(*Set) * 8)] |= 1 << (Index % (sizeof(*Set) * 8));
#else
    ((uint8_t*)Set)[Index / (sizeof(uint8_t) * 8)] |= 1 << (Index % (sizeof(uint8_t) * 8));
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClear, (T Set, const size_t Index))
{
#if CC_HARDWARE_ENDIAN_LITTLE
    Set[Index / (sizeof(*Set) * 8)] &= ~(1 << (Index % (sizeof(*Set) * 8)));
#else
    ((uint8_t*)Set)[Index / (sizeof(uint8_t) * 8)] &= ~(1 << (Index % (sizeof(uint8_t) * 8)));
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsSetRange, (const T Set, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    uint64_t * const Set64 = (uint64_t*)(((uint8_t*)Set) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        Set64[Loop] = -1;
    }
    
    if (Index % 8)
    {
        const uint8_t Byte = ((uint8_t*)Set)[Offset8 - 1];
        const uint8_t Mask = (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        uint8_t RemainderB8 = -1 & Mask;
        
        RemainderB8 |= Byte & ~Mask;
        
        ((uint8_t*)Set)[Offset8 - 1] = RemainderB8;
    }
    
    else if (Count < 8)
    {
        const uint8_t Byte = ((uint8_t*)Set)[Offset8];
        const uint8_t Mask = (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        uint8_t RemainderB8 = -1 & Mask;
        
        RemainderB8 |= Byte & ~Mask;
        
        ((uint8_t*)Set)[Offset8] = RemainderB8;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    uint8_t * const Set8 = ((uint8_t*)Set) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        Set8[Loop] = -1;
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        Set8[Count8] = -1;
    }
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsClearRange, (const T Set, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    uint64_t * const Set64 = (uint64_t*)(((uint8_t*)Set) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        Set64[Loop] = 0;
    }
    
    if (Index % 8)
    {
        const uint8_t Byte = ((uint8_t*)Set)[Offset8 - 1];
        const uint8_t Mask = (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        uint8_t RemainderB8 = Byte & ~Mask;
        
        ((uint8_t*)Set)[Offset8 - 1] = RemainderB8;
    }
    
    else if (Count < 8)
    {
        const uint8_t Byte = ((uint8_t*)Set)[Offset8];
        const uint8_t Mask = (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        uint8_t RemainderB8 = Byte & ~Mask;
        
        ((uint8_t*)Set)[Offset8] = RemainderB8;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    uint8_t * const Set8 = ((uint8_t*)Set) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        Set8[Loop] = 0;
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        Set8[Count8] = 0;
    }
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

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCBitsAny, (const T Set, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    const uint64_t * const Set64 = (uint64_t*)(((uint8_t*)Set) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        if (Set64[Loop]) return TRUE;
    }
    
    if (Index % 8)
    {
        if (((uint8_t*)Set)[Offset8 - 1] & (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff)) return TRUE;
    }
    
    else if (Count < 8)
    {
        if (((uint8_t*)Set)[Offset8] & (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1)) return TRUE;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    const uint8_t * const Set8 = ((uint8_t*)Set) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        if (Set8[Loop]) return TRUE;
    }
    
    if (IndexAdjustedCount % 8)
    {
        if (Index % 8)
        {
            if (Count8 == 7)
            {
                if (Set8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1)) return TRUE;
            }
            
            else
            {
                if (Set8[Count8] << (56 + (8 - (IndexAdjustedCount % 8)))) return TRUE;
            }
        }
        
        else
        {
            if (Set8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1)) return TRUE;
        }
    }
    
    return FALSE;
}

CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCBitsMask, (const T SetA, const T SetB, const size_t Index, const size_t Count, PTYPE(size_t *) Indexes))
{
    size_t IndexCount = 0;
    
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    const uint64_t * const SetA64 = (uint64_t*)(((uint8_t*)SetA) + Offset8);
    const uint64_t * const SetB64 = (uint64_t*)(((uint8_t*)SetB) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        size_t BitBase = (Loop * 64) + (Offset8 * 8);
        uint64_t Mask = SetA64[Loop] & SetB64[Loop];
        
#if CC_HARDWARE_ENDIAN_BIG
        CCSwap(&Mask, sizeof(Mask));
#endif
        
        while (Mask)
        {
            size_t BitIndex = CCBitCountLowestUnset(Mask);
            Mask >>= BitIndex + 1;
            
            if (Indexes) Indexes[IndexCount] = BitIndex + BitBase;
            
            IndexCount++;
            
            BitBase += BitIndex + 1;
        }
    }
    
    uint64_t RemainderA = 0, RemainderB = 0;
    if (Index % 8)
    {
        uint8_t RemainderA8 = ((uint8_t*)SetA)[Offset8 - 1] & (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8 - 1] & (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        
        size_t BitBase = (Offset8 - 1) * 8;
        uint64_t Mask = RemainderA8 & RemainderB8;
        
        while (Mask)
        {
            size_t BitIndex = CCBitCountLowestUnset(Mask);
            Mask >>= BitIndex + 1;
            
            if (Indexes) Indexes[IndexCount] = BitIndex + BitBase;
            
            IndexCount++;
            
            BitBase += BitIndex + 1;
        }
    }
    
    else if (Count < 8)
    {
        RemainderA = ((uint8_t*)SetA)[Offset8] & (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        RemainderB = ((uint8_t*)SetB)[Offset8] & (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    const uint8_t * const SetA8 = ((uint8_t*)SetA) + Offset8 + (Count64 * 8);
    const uint8_t * const SetB8 = ((uint8_t*)SetB) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        RemainderA |= (uint64_t)SetA8[Loop] << (Loop * 8);
        RemainderB |= (uint64_t)SetB8[Loop] << (Loop * 8);
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        if (Index % 8)
        {
            if (Count8 == 7)
            {
                RemainderA |= (uint64_t)(SetA8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1)) << 56;
                RemainderB |= (uint64_t)(SetB8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1)) << 56;
            }
            
            else
            {
                RemainderA |= (uint64_t)(SetA8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1)) << (Count8 * 8);
                RemainderB |= (uint64_t)(SetB8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1)) << (Count8 * 8);
            }
        }
        
        else
        {
            RemainderA |= SetA8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1);
            RemainderB |= SetB8[Count8] & ((1 << (IndexAdjustedCount % 8)) - 1);
        }
    }
    
    size_t BitBase = (Offset8 * 8) + (Count64 * 64);
    uint64_t Mask = RemainderA & RemainderB;
    
    while (Mask)
    {
        size_t BitIndex = CCBitCountLowestUnset(Mask);
        Mask >>= BitIndex + 1;
        
        if (Indexes) Indexes[IndexCount] = BitIndex + BitBase;
        
        IndexCount++;
        
        BitBase += BitIndex + 1;
    }
    
    return IndexCount;
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsNot, (const T Set, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    uint64_t * const Set64 = (uint64_t*)(((uint8_t*)Set) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        Set64[Loop] = ~Set64[Loop];
    }
    
    if (Index % 8)
    {
        const uint8_t Byte = ((uint8_t*)Set)[Offset8 - 1];
        const uint8_t Mask = (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        uint8_t RemainderB8 = ~Byte & Mask;
        
        RemainderB8 |= Byte & ~Mask;
        
        ((uint8_t*)Set)[Offset8 - 1] = RemainderB8;
    }
    
    else if (Count < 8)
    {
        const uint8_t Byte = ((uint8_t*)Set)[Offset8];
        const uint8_t Mask = (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        uint8_t RemainderB8 = ~Byte & Mask;
        
        RemainderB8 |= Byte & ~Mask;
        
        ((uint8_t*)Set)[Offset8] = RemainderB8;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    uint8_t * const Set8 = ((uint8_t*)Set) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        Set8[Loop] = ~Set8[Loop];
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        Set8[Count8] = ~Set8[Count8];
    }
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsOr, (const T SetA, const T SetB, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    uint64_t * const SetA64 = (uint64_t*)(((uint8_t*)SetA) + Offset8);
    uint64_t * const SetB64 = (uint64_t*)(((uint8_t*)SetB) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        SetA64[Loop] |= SetB64[Loop];
    }
    
    if (Index % 8)
    {
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8 - 1] & (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        
        ((uint8_t*)SetA)[Offset8 - 1] |= RemainderB8;
    }
    
    else if (Count < 8)
    {
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8] & (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        
        ((uint8_t*)SetA)[Offset8] |= RemainderB8;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    uint8_t * const SetA8 = ((uint8_t*)SetA) + Offset8 + (Count64 * 8);
    uint8_t * const SetB8 = ((uint8_t*)SetB) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        SetA8[Loop] |= SetB8[Loop];
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        SetA8[Count8] |= SetB8[Count8];
    }
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsAnd, (const T SetA, const T SetB, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    uint64_t * const SetA64 = (uint64_t*)(((uint8_t*)SetA) + Offset8);
    uint64_t * const SetB64 = (uint64_t*)(((uint8_t*)SetB) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        SetA64[Loop] &= SetB64[Loop];
    }
    
    if (Index % 8)
    {
        const uint8_t Mask = (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8 - 1] & Mask;
        
        RemainderB8 |= ~Mask;
        
        ((uint8_t*)SetA)[Offset8 - 1] &= RemainderB8;
    }
    
    else if (Count < 8)
    {
        const uint8_t Mask = (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8] & Mask;
        
        RemainderB8 |= ~Mask;
        
        ((uint8_t*)SetA)[Offset8] |= RemainderB8;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    uint8_t * const SetA8 = ((uint8_t*)SetA) + Offset8 + (Count64 * 8);
    uint8_t * const SetB8 = ((uint8_t*)SetB) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        SetA8[Loop] &= SetB8[Loop];
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        SetA8[Count8] &= SetB8[Count8];
    }
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCBitsXor, (const T SetA, const T SetB, const size_t Index, const size_t Count))
{
    const size_t Offset8 = (Index + 7) / 8;
    const size_t IndexAdjustedCount = (8 - (Index % 8)) <= Count ? ((Index + Count) - (Offset8 * 8)) : 0;
    const size_t Count64 = IndexAdjustedCount / 64;
    uint64_t * const SetA64 = (uint64_t*)(((uint8_t*)SetA) + Offset8);
    uint64_t * const SetB64 = (uint64_t*)(((uint8_t*)SetB) + Offset8);
    
    for (size_t Loop = 0; Loop < Count64; Loop++)
    {
        SetA64[Loop] ^= SetB64[Loop];
    }
    
    if (Index % 8)
    {
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8 - 1] & (0xff << (Index % 8)) & (Count < 8 ? ((1 << ((Index % 8) + Count)) - 1) : 0xff);
        
        ((uint8_t*)SetA)[Offset8 - 1] ^= RemainderB8;
    }
    
    else if (Count < 8)
    {
        uint8_t RemainderB8 = ((uint8_t*)SetB)[Offset8] & (0xff << (Index % 8)) & ((1 << ((Index % 8) + Count)) - 1);
        
        ((uint8_t*)SetA)[Offset8] ^= RemainderB8;
    }
    
    const size_t Count8 = (IndexAdjustedCount / 8) - (Count64 * 8);
    uint8_t * const SetA8 = ((uint8_t*)SetA) + Offset8 + (Count64 * 8);
    uint8_t * const SetB8 = ((uint8_t*)SetB) + Offset8 + (Count64 * 8);
    
    for (size_t Loop = 0; Loop < Count8; Loop++)
    {
        SetA8[Loop] ^= SetB8[Loop];
    }
    
    
    if (IndexAdjustedCount % 8)
    {
        SetA8[Count8] ^= SetB8[Count8];
    }
}
