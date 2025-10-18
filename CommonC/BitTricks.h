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

/*
 Tricks from:
 http://graphics.stanford.edu/~seander/bithacks.html
 http://resnet.uoregon.edu/~gurney_j/jmpc/bitwise.html
 */

#ifndef CommonC_BitTricks_h
#define CommonC_BitTricks_h

#include <CommonC/Base.h>
#include <CommonC/Extensions.h>


/*!
 * @brief Finds lowest unset bit.
 * @example (00010110 -> 00000001, 00001000 -> 00000001)
 * @return The lowest unset bit.
 */
static CC_FORCE_INLINE uint64_t CCBitLowestUnset(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Finds lowest set bit.
 * @example (00010110 -> 00000010, 00001000 -> 00001000)
 * @return The lowest set bit.
 */
static CC_FORCE_INLINE uint64_t CCBitLowestSet(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Finds highest set bit.
 * @example (00010110 -> 00010000, 00001000 -> 00001000)
 * @return The highest set bit.
 */
static CC_FORCE_INLINE uint64_t CCBitHighestSet(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Finds the minimum power of 2 value that can hold @b x.
 * @example (00010110 -> 00100000, 00001000 -> 00001000)
 * @return The next power of 2.
 */
static CC_FORCE_INLINE uint64_t CCBitNextPowerOf2(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Creates a mask for the entire values range.
 * @example (00010110 -> 00011111, 00001000 -> 00001111)
 * @return Mask for value.
 */
static CC_FORCE_INLINE uint64_t CCBitMaskForValue(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Masks the lower bits of a power of 2 value.
 * @example (00010110 -> NA, 00001000 -> 00000111)
 * @return Mask for lower bits of power of 2.
 */
static CC_FORCE_INLINE uint64_t CCBitMaskForLowerPowerOf2(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit.
 * @example (00010110 -> 11100000, 00001000 -> 11110000)
 * @return Mask for highest unset bits.
 */
static CC_FORCE_INLINE uint64_t CCBitMaskForUnsetValue(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Sums the number of set bits.
 * @example (00010110 -> 00000011, 00001000 -> 00000001)
 * @return Sum of set bits.
 */
static CC_FORCE_INLINE uint64_t CCBitCountSet(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Sums the number of lowest unset bits.
 * @example (00010110 -> 00000001, 00001000 -> 00000011)
 * @return Sum of the lowest unset bits.
 */
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitCountLowestUnset(uint64_t x);

/*!
 * @brief Set n least significant bits
 * @return Set n bits.
 */
static CC_FORCE_INLINE uint64_t CCBitSet(uint64_t n) CC_CONSTANT_FUNCTION;

/*!
 * @brief Checks if the value is a power of 2
 * @return Whether or not the value is a power of 2.
 */
static CC_FORCE_INLINE _Bool CCBitIsPowerOf2(uint64_t x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Checks if the float value is a power of 2
 * @return Whether or not the value is a power of 2.
 */
static CC_FORCE_INLINE _Bool CCBitFloat32IsPowerOf2(float x) CC_CONSTANT_FUNCTION;

/*!
 * @brief Checks if the double value is a power of 2
 * @return Whether or not the value is a power of 2.
 */
static CC_FORCE_INLINE _Bool CCBitFloat64IsPowerOf2(double x) CC_CONSTANT_FUNCTION;


#pragma mark - Implementations

//Finds lowest unset bit (00010110 -> 00000001, 00001000 -> 00000001)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitLowestUnset(uint64_t x) //7 -> 8, 8 -> 1
{
    return ~x & (x + 1);
}

//Finds lowest set bit (00010110 -> 00000010, 00001000 -> 00001000)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitLowestSet(uint64_t x)
{
    return x & -x;
}

//Finds highest set bit (00010110 -> 00010000, 00001000 -> 00001000)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitHighestSet(uint64_t x)
{
    x = CCBitMaskForValue(x);
    
    return x ^ (x >> 1);
}

//Finds the minimum power of 2 value that can hold x (00010110 -> 00100000, 00001000 -> 00001000)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitNextPowerOf2(uint64_t x)
{
    return CCBitMaskForValue(x - 1) + 1;
}

//Creates a mask for the entire values range (00010110 -> 00011111, 00001000 -> 00001111)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitMaskForValue(uint64_t x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    
    return x;
}

//Masks the lower bits of a power of 2 value (00010110 -> NA, 00001000 -> 00000111)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitMaskForLowerPowerOf2(uint64_t x) //8 -> 7, 4 -> 3
{
    //assert power of 2
    return x? ~-x : 0;
}

//Creates a mask for the entire range of unset bits after the highest set bit (00010110 -> 11100000, 00001000 -> 11110000)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitMaskForUnsetValue(uint64_t x)
{
    return UINT64_MAX ^ CCBitMaskForValue(x);
}

//Sums the number of set bits (00010110 -> 00000011, 00001000 -> 00000001)
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitCountSet(uint64_t x)
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

static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitCountLowestUnset(uint64_t x)
{
    if (!x) return 64;
    
#if __has_builtin(__builtin_ctzll)
    return __builtin_ctzll(x);
#else
    return CCBitCountSet(CCBitMaskForLowerPowerOf2(CCBitLowestSet(x)));
#endif
}

//Set n least significant bits
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION uint64_t CCBitSet(uint64_t n)
{
    return n == 64 ? UINT64_MAX : ((UINT64_C(1) << n) - 1);
}

//Checks if the value is a power of 2
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION _Bool CCBitIsPowerOf2(uint64_t x)
{
    return x && !(x & ~-x);
}

//Checks if the float value is a power of 2
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION _Bool CCBitFloat32IsPowerOf2(float x)
{
//    return !!((*(uint32_t*)&x) & 0x7f800000) & !((*(uint32_t*)&x) & 0x7fffff);
    return x != 0.0f && !((*(uint32_t*)&x) & 0x7fffff);
}

//Checks if the double value is a power of 2
static CC_FORCE_INLINE CC_CONSTANT_FUNCTION _Bool CCBitFloat64IsPowerOf2(double x)
{
//    return !!((*(uint64_t*)&x) & 0x7ff0000000000000) & !((*(uint64_t*)&x) & 0xfffffffffffff);
    return x != 0.0 && !((*(uint64_t*)&x) & 0xfffffffffffff);
}

#endif
