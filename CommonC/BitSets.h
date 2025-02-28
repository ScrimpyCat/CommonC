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

#ifndef CommonC_BitSets_h
#define CommonC_BitSets_h

#include <CommonC/Alignment.h>

/*!
 * @define CCBits
 * @brief Create an array of bits.
 * @param type The base type for the array.
 * @param count The number of bits needing to be stored.
*/
#define CCBits(type, count) typeof((type[CC_ALIGN(count, (sizeof(type) * 8)) / (sizeof(type) * 8)]){})

/*!
 * @define CC_BITS_INIT_SET
 * @brief Sets the entire array of bits.
 * @warning This should only be used with the variable declared by @b CCBits.
*/
#define CC_BITS_INIT_SET(set) memset(set, -1, sizeof(set))

/*!
 * @define CC_BITS_INIT_SET
 * @brief Clears the entire array of bits.
 * @warning This should only be used with the variable declared by @b CCBits.
*/
#define CC_BITS_INIT_CLEAR(set) memset(set, 0, sizeof(set))

/*!
 * @define CC_BITS_COPY
 * @brief Copies the entire array of bits from the src to dst.
 * @warning This should only be used with the variables declared by @b CCBits.
*/
#define CC_BITS_COPY(dst, src) _Static_assert(sizeof(src) == sizeof(dst), "Src and Dst must be the same size"); memcpy(dst, src, sizeof(dst))

/*!
 * @define CC_BITS_BLOCK_SIZE
 * @brief Get the size of one block (number of bits in a block) for the array of bits.
*/
#define CC_BITS_BLOCK_SIZE(set) (sizeof(*set) * 8)

#define Tbase uint8_t
#include <CommonC/Bits.h>

#define Tbase uint16_t
#include <CommonC/Bits.h>

#define Tbase uint32_t
#include <CommonC/Bits.h>

#define Tbase uint64_t
#include <CommonC/Bits.h>

#endif
