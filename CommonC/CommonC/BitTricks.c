/*
 *  Copyright (c) 2013, Stefan Johnson
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

#include "BitTricks.h"

//Finds lowest unset bit (00010110 -> 00000001, 00001000 -> 00000001)
uint64_t CCLowestUnsetBit(uint64_t x) //7 -> 8, 8 -> 1
{
    return ~x & (x + 1);
}

//Finds lowest set bit (00010110 -> 00000010, 00001000 -> 00001000)
uint64_t CCLowestSetBit(uint64_t x)
{
    return x & -x;
}

//Finds highest set bit (00010110 -> 00010000, 00001000 -> 00001000)
uint64_t CCHighestSetBit(uint64_t x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    
    return x ^ (x >> 1);
}

//Finds the minimum power of 2 value that can hold x (00010110 -> 00100000, 00001000 -> 00001000)
uint64_t CCNextPowerOf2(uint64_t x)
{
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    
    return x + 1;
}

//Creates a mask for the entire values range (00010110 -> 00011111, 00001000 -> 00001111)
uint64_t CCMaskForValue(uint64_t x)
{
    return x & 0x8000000000000000? UINT64_MAX : CCMaskForLowerBits2(CCHighestSetBit(x) << 1);
}

//Masks the lower bits of a power of 2 value (00010110 -> NA, 00001000 -> 00000111)
uint64_t CCMaskForLowerBits2(uint64_t x) //8 -> 7, 4 -> 3
{
    //assert power of 2
    return x? ~-x : 0;
}

//Creates a mask for the entire range of unset bits after the highest set bit (00010110 -> 11100000, 00001000 -> 11110000)
uint64_t CCMaskForUnsetValue(uint64_t x)
{
    return UINT64_MAX ^ CCMaskForValue(x);
}

//Sums the number of set bits (00010110 -> 00000011, 00001000 -> 00000001)
uint64_t CCCountSetBits(uint64_t x)
{
    /*
    x -= ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
    x += (x >> 8);
    x += (x >> 16);
    x += (x >> 32);
     
    return x & 0x7f;
     */
    
    x -= ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
    x = (x * 0x0101010101010101) >> 56;
    
    return x;
}
