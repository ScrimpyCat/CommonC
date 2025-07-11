/*
 *  Copyright (c) 2025, Stefan Johnson
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

#ifndef CommonC_Simd64_h
#define CommonC_Simd64_h

#include <CommonC/Types.h>
#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <CommonC/Maths.h>
#include <CommonC/BitTricks.h>

#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
#include <arm_neon.h>

typedef int8x8_t CCSimd_s8x8;
typedef int16x4_t CCSimd_s16x4;
typedef int32x2_t CCSimd_s32x2;

typedef uint8x8_t CCSimd_u8x8;
typedef uint16x4_t CCSimd_u16x4;
typedef uint32x2_t CCSimd_u32x2;

typedef float32x2_t CCSimd_f32x2;
#endif


static CC_FORCE_INLINE CCSimd_s8x8 CCSimdZero_s8x8(void);
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdZero_s16x4(void);
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdZero_s32x2(void);

static CC_FORCE_INLINE CCSimd_u8x8 CCSimdZero_u8x8(void);
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdZero_u16x4(void);
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdZero_u32x2(void);

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdZero_f32x2(void);


static CC_FORCE_INLINE CCSimd_s8x8 CCSimdFill_s8x8(const int8_t v);
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdFill_s16x4(const int16_t v);
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdFill_s32x2(const int32_t v);

static CC_FORCE_INLINE CCSimd_u8x8 CCSimdFill_u8x8(const uint8_t v);
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdFill_u16x4(const uint16_t v);
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdFill_u32x2(const uint32_t v);

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdFill_f32x2(const float v);


static CC_FORCE_INLINE CCSimd_s8x8 CCSimdLoad_s8x8(const int8_t v[8]);
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdLoad_s16x4(const int16_t v[4]);
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdLoad_s32x2(const int32_t v[2]);

static CC_FORCE_INLINE CCSimd_u8x8 CCSimdLoad_u8x8(const uint8_t v[8]);
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdLoad_u16x4(const uint16_t v[4]);
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdLoad_u32x2(const uint32_t v[2]);

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdLoad_f32x2(const float v[2]);


static CC_FORCE_INLINE void CCSimdStore_s8x8(int8_t dst[8], const CCSimd_s8x8 src);
static CC_FORCE_INLINE void CCSimdStore_s16x4(int16_t dst[4], const CCSimd_s16x4 src);
static CC_FORCE_INLINE void CCSimdStore_s32x2(int32_t dst[2], const CCSimd_s32x2 src);

static CC_FORCE_INLINE void CCSimdStore_u8x8(uint8_t dst[8], const CCSimd_u8x8 src);
static CC_FORCE_INLINE void CCSimdStore_u16x4(uint16_t dst[4], const CCSimd_u16x4 src);
static CC_FORCE_INLINE void CCSimdStore_u32x2(uint32_t dst[2], const CCSimd_u32x2 src);

static CC_FORCE_INLINE void CCSimdStore_f32x2(float dst[2], const CCSimd_f32x2 src);

// TODO: interleaved loads and stores

static CC_FORCE_INLINE int8_t CCSimdGet_s8x8(const CCSimd_s8x8 a, uint8_t index);
static CC_FORCE_INLINE int16_t CCSimdGet_s16x4(const CCSimd_s16x4 a, uint8_t index);
static CC_FORCE_INLINE int32_t CCSimdGet_s32x2(const CCSimd_s32x2 a, uint8_t index);

static CC_FORCE_INLINE uint8_t CCSimdGet_u8x8(const CCSimd_u8x8 a, uint8_t index);
static CC_FORCE_INLINE uint16_t CCSimdGet_u16x4(const CCSimd_u16x4 a, uint8_t index);
static CC_FORCE_INLINE uint32_t CCSimdGet_u32x2(const CCSimd_u32x2 a, uint8_t index);

static CC_FORCE_INLINE float CCSimdGet_f32x2(const CCSimd_f32x2 a, uint8_t index);


static CC_FORCE_INLINE CCSimd_s8x8 CCSimdSet_s8x8(const CCSimd_s8x8 a, uint8_t index, int8_t v);
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdSet_s16x4(const CCSimd_s16x4 a, uint8_t index, int16_t v);
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdSet_s32x2(const CCSimd_s32x2 a, uint8_t index, int32_t v);

static CC_FORCE_INLINE CCSimd_u8x8 CCSimdSet_u8x8(const CCSimd_u8x8 a, uint8_t index, uint8_t v);
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdSet_u16x4(const CCSimd_u16x4 a, uint8_t index, uint16_t v);
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdSet_u32x2(const CCSimd_u32x2 a, uint8_t index, uint32_t v);

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSet_f32x2(const CCSimd_f32x2 a, uint8_t index, float v);


static CC_FORCE_INLINE CCSimd_s8x8 CCSimdSetSequence_s8x8(const CCSimd_s8x8 a, int8_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7);
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdSetSequence_s16x4(const CCSimd_s16x4 a, int16_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdSetSequence_s32x2(const CCSimd_s32x2 a, int32_t v, _Bool v0, _Bool v1);

static CC_FORCE_INLINE CCSimd_u8x8 CCSimdSetSequence_u8x8(const CCSimd_u8x8 a, uint8_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7);
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdSetSequence_u16x4(const CCSimd_u16x4 a, uint16_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdSetSequence_u32x2(const CCSimd_u32x2 a, uint32_t v, _Bool v0, _Bool v1);

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSetSequence_f32x2(const CCSimd_f32x2 a, float v, _Bool v0, _Bool v1);


#pragma mark - Maths
#pragma mark Add

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] + [0, 0, 1, 1, 1, 2, 2, 2] -> [1, 2, 4, 5, 6, 8, 9, 10]
 * @param a An 8 element vector of 8-bit signed integers as the addend.
 * @param b An 8 element vector of 8-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdAdd_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [5, 6, 7, 8] + [1, 2, 2, 2] -> [6, 8, 9, 10]
 * @param a A 4 element vector of 16-bit signed integers as the addend.
 * @param b A 4 element vector of 16-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdAdd_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [7, 8] + [2, 2] -> [9, 10]
 * @param a A 2 element vector of 32-bit signed integers as the addend.
 * @param b A 2 element vector of 32-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdAdd_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] + [0, 0, 1, 1, 1, 2, 2, 2] -> [1, 2, 4, 5, 6, 8, 9, 10]
 * @param a An 8 element vector of 8-bit unsigned integers as the addend.
 * @param b An 8 element vector of 8-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdAdd_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [5, 6, 7, 8] + [1, 2, 2, 2] -> [6, 8, 9, 10]
 * @param a A 4 element vector of 16-bit unsigned integers as the addend.
 * @param b A 4 element vector of 16-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdAdd_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [7, 8] + [2, 2] -> [9, 10]
 * @param a A 2 element vector of 32-bit unsigned integers as the addend.
 * @param b A 2 element vector of 32-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdAdd_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [7.5, 8.5] + [2, 2] -> [9.5, 10.5]
 * @param a A 2 element vector of 32-bit floats as the addend.
 * @param b A 2 element vector of 32-bit floats as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdAdd_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Subtract

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] - [0, 0, 1, 1, 1, 2, 2, 2] -> [1, 2, 2, 3, 4, 4, 5, 6]
 * @param a An 8 element vector of 8-bit signed integers as the minuend.
 * @param b An 8 element vector of 8-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdSub_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [5, 6, 7, 8] - [1, 2, 2, 2] -> [4, 4, 5, 6]
 * @param a A 4 element vector of 16-bit signed integers as the minuend.
 * @param b A 4 element vector of 16-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdSub_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [7, 8] - [2, 2] -> [5, 6]
 * @param a A 2 element vector of 32-bit signed integers as the minuend.
 * @param b A 2 element vector of 32-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdSub_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] - [0, 0, 1, 1, 1, 2, 2, 2] -> [1, 2, 2, 3, 4, 4, 5, 6]
 * @param a An 8 element vector of 8-bit unsigned integers as the minuend.
 * @param b An 8 element vector of 8-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdSub_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [5, 6, 7, 8] - [1, 2, 2, 2] -> [4, 4, 5, 6]
 * @param a A 4 element vector of 16-bit unsigned integers as the minuend.
 * @param b A 4 element vector of 16-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdSub_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [7, 8] - [2, 2] -> [5, 6]
 * @param a A 2 element vector of 32-bit unsigned integers as the minuend.
 * @param b A 2 element vector of 32-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdSub_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [7.5, 8.5] - [2, 2] -> [5.5, 6.5]
 * @param a A 2 element vector of 32-bit floats as the minuend.
 * @param b A 2 element vector of 32-bit floats as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSub_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Multiply

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2] -> [0, 0, 3, 4, 5, 12, 14, 16]
 * @param a An 8 element vector of 8-bit signed integers as the multiplier.
 * @param b An 8 element vector of 8-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMul_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [5, 6, 7, 8] * [1, 2, 2, 2] -> [5, 12, 14, 16]
 * @param a A 4 element vector of 16-bit signed integers as the multiplier.
 * @param b A 4 element vector of 16-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMul_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [7, 8] * [2, 2] -> [14, 16]
 * @param a A 2 element vector of 32-bit signed integers as the multiplier.
 * @param b A 2 element vector of 32-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMul_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2] -> [0, 0, 3, 4, 5, 12, 14, 16]
 * @param a An 8 element vector of 8-bit unsigned integers as the multiplier.
 * @param b An 8 element vector of 8-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMul_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [5, 6, 7, 8] * [1, 2, 2, 2] -> [5, 12, 14, 16]
 * @param a A 4 element vector of 16-bit unsigned integers as the multiplier.
 * @param b A 4 element vector of 16-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMul_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [7, 8] * [2, 2] -> [14, 16]
 * @param a A 2 element vector of 32-bit unsigned integers as the multiplier.
 * @param b A 2 element vector of 32-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMul_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [7.5, 8.5] * [2, 2] -> [15, 17]
 * @param a A 2 element vector of 32-bit floats as the multiplier.
 * @param b A 2 element vector of 32-bit floats as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMul_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Multiply and Add

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 1, 4, 5, 6, 13, 15, 17]
 * @param a An 8 element vector of 8-bit signed integers to multiply.
 * @param b An 8 element vector of 8-bit signed integers to multiply.
 * @param c An 8 element vector of 8-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMadd_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, const CCSimd_s8x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([5, 6, 7, 8] * [1, 2, 2, 2]) + [1, 1, 1, 1] -> [6, 13, 15, 17]
 * @param a A 4 element vector of 16-bit signed integers to multiply.
 * @param b A 4 element vector of 16-bit signed integers to multiply.
 * @param c A 4 element vector of 16-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMadd_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, const CCSimd_s16x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([7, 8] * [2, 2]) + [1, 1] -> [15, 17]
 * @param a A 2 element vector of 32-bit signed integers to multiply.
 * @param b A 2 element vector of 32-bit signed integers to multiply.
 * @param c A 2 element vector of 32-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMadd_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, const CCSimd_s32x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 1, 4, 5, 6, 13, 15, 17]
 * @param a An 8 element vector of 8-bit unsigned integers to multiply.
 * @param b An 8 element vector of 8-bit unsigned integers to multiply.
 * @param c An 8 element vector of 8-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMadd_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, const CCSimd_u8x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([5, 6, 7, 8] * [1, 2, 2, 2]) + [1, 1, 1, 1] -> [6, 13, 15, 17]
 * @param a A 4 element vector of 16-bit unsigned integers to multiply.
 * @param b A 4 element vector of 16-bit unsigned integers to multiply.
 * @param c A 4 element vector of 16-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMadd_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, const CCSimd_u16x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([7, 8] * [2, 2]) + [1, 1] -> [15, 17]
 * @param a A 2 element vector of 32-bit unsigned integers to multiply.
 * @param b A 2 element vector of 32-bit unsigned integers to multiply.
 * @param c A 2 element vector of 32-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMadd_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, const CCSimd_u32x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([7.5, 8.5] * [2, 2]) + [1, 1] -> [16, 18]
 * @param a A 2 element vector of 32-bit floats to multiply.
 * @param b A 2 element vector of 32-bit floats to multiply.
 * @param c A 2 element vector of 32-bit floats to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMadd_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, const CCSimd_f32x2 c);


#pragma mark Negated Multiply and Add

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 1, -2, -3, -4, -11, -13, -15]
 * @param a An 8 element vector of 8-bit signed integers to multiply.
 * @param b An 8 element vector of 8-bit signed integers to multiply.
 * @param c An 8 element vector of 8-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdNegMadd_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, const CCSimd_s8x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([5, 6, 7, 8] * [1, 2, 2, 2]) + [1, 1, 1, 1] -> [-4, -11, -13, -15]
 * @param a A 4 element vector of 16-bit signed integers to multiply.
 * @param b A 4 element vector of 16-bit signed integers to multiply.
 * @param c A 4 element vector of 16-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdNegMadd_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, const CCSimd_s16x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([7, 8] * [2, 2]) + [1, 1] -> [-13, -15]
 * @param a A 2 element vector of 32-bit signed integers to multiply.
 * @param b A 2 element vector of 32-bit signed integers to multiply.
 * @param c A 2 element vector of 32-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdNegMadd_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, const CCSimd_s32x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 1, -2, -3, -4, -11, -13, -15]
 * @param a An 8 element vector of 8-bit unsigned integers to multiply.
 * @param b An 8 element vector of 8-bit unsigned integers to multiply.
 * @param c An 8 element vector of 8-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdNegMadd_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, const CCSimd_u8x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([5, 6, 7, 8] * [1, 2, 2, 2]) + [1, 1, 1, 1] -> [-4, -11, -13, -15]
 * @param a A 4 element vector of 16-bit unsigned integers to multiply.
 * @param b A 4 element vector of 16-bit unsigned integers to multiply.
 * @param c A 4 element vector of 16-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdNegMadd_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, const CCSimd_u16x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([7, 8] * [2, 2]) + [1, 1] -> [-13, -15]
 * @param a A 2 element vector of 32-bit unsigned integers to multiply.
 * @param b A 2 element vector of 32-bit unsigned integers to multiply.
 * @param c A 2 element vector of 32-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdNegMadd_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, const CCSimd_u32x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([7.5, 8.5] * [2, 2]) + [1, 1] -> [-14, -16]
 * @param a A 2 element vector of 32-bit floats to multiply.
 * @param b A 2 element vector of 32-bit floats to multiply.
 * @param c A 2 element vector of 32-bit floats to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdNegMadd_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, const CCSimd_f32x2 c);


#pragma mark Multiply and Sub

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [-1, -1, 2, 3, 4, 11, 13, 15]
 * @param a An 8 element vector of 8-bit signed integers to multiply.
 * @param b An 8 element vector of 8-bit signed integers to multiply.
 * @param c An 8 element vector of 8-bit signed integers to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMsub_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, const CCSimd_s8x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([5, 6, 7, 8] * [1, 2, 2, 2]) - [1, 1, 1, 1] -> [4, 11, 13, 15]
 * @param a A 4 element vector of 16-bit signed integers to multiply.
 * @param b A 4 element vector of 16-bit signed integers to multiply.
 * @param c A 4 element vector of 16-bit signed integers to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMsub_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, const CCSimd_s16x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([7, 8] * [2, 2]) - [1, 1] -> [13, 15]
 * @param a A 2 element vector of 32-bit signed integers to multiply.
 * @param b A 2 element vector of 32-bit signed integers to multiply.
 * @param c A 2 element vector of 32-bit signed integers to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMsub_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, const CCSimd_s32x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [-1, -1, 2, 3, 4, 11, 13, 15]
 * @param a An 8 element vector of 8-bit unsigned integers to multiply.
 * @param b An 8 element vector of 8-bit unsigned integers to multiply.
 * @param c An 8 element vector of 8-bit unsigned integers to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMsub_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, const CCSimd_u8x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([5, 6, 7, 8] * [1, 2, 2, 2]) - [1, 1, 1, 1] -> [4, 11, 13, 15]
 * @param a A 4 element vector of 16-bit unsigned integers to multiply.
 * @param b A 4 element vector of 16-bit unsigned integers to multiply.
 * @param c A 4 element vector of 16-bit unsigned integers to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMsub_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, const CCSimd_u16x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([7, 8] * [2, 2]) - [1, 1] -> [13, 15]
 * @param a A 2 element vector of 32-bit unsigned integers to multiply.
 * @param b A 2 element vector of 32-bit unsigned integers to multiply.
 * @param c A 2 element vector of 32-bit unsigned integers to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMsub_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, const CCSimd_u32x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and sub all elements of @b c.
 * @description (a * b) - c
 * @example ([7.5, 8.5] * [2, 2]) - [1, 1] -> [14, 16]
 * @param a A 2 element vector of 32-bit floats to multiply.
 * @param b A 2 element vector of 32-bit floats to multiply.
 * @param c A 2 element vector of 32-bit floats to sub.
 * @return The vector representing the multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMsub_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, const CCSimd_f32x2 c);


#pragma mark Negated Multiply and Sub

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 1, -4, -5, -6, -13, -15, -17]
 * @param a An 8 element vector of 8-bit signed integers to multiply.
 * @param b An 8 element vector of 8-bit signed integers to multiply.
 * @param c An 8 element vector of 8-bit signed integers to sub.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdNegMsub_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, const CCSimd_s8x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([5, 6, 7, 8] * [1, 2, 2, 2]) - [1, 1, 1, 1] -> [-6, -13, -15, -17]
 * @param a A 4 element vector of 16-bit signed integers to multiply.
 * @param b A 4 element vector of 16-bit signed integers to multiply.
 * @param c A 4 element vector of 16-bit signed integers to sub.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdNegMsub_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, const CCSimd_s16x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([7, 8] * [2, 2]) - [1, 1] -> [-15, -17]
 * @param a A 2 element vector of 32-bit signed integers to multiply.
 * @param b A 2 element vector of 32-bit signed integers to multiply.
 * @param c A 2 element vector of 32-bit signed integers to sub.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdNegMsub_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, const CCSimd_s32x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([1, 2, 3, 4, 5, 6, 7, 8] * [0, 0, 1, 1, 1, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 1, -4, -5, -6, -13, -15, -17]
 * @param a An 8 element vector of 8-bit unsigned integers to multiply.
 * @param b An 8 element vector of 8-bit unsigned integers to multiply.
 * @param c An 8 element vector of 8-bit unsigned integers to sub.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdNegMsub_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, const CCSimd_u8x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([5, 6, 7, 8] * [1, 2, 2, 2]) - [1, 1, 1, 1] -> [-6, -13, -15, -17]
 * @param a A 4 element vector of 16-bit unsigned integers to multiply.
 * @param b A 4 element vector of 16-bit unsigned integers to multiply.
 * @param c A 4 element vector of 16-bit unsigned integers to sub.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdNegMsub_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, const CCSimd_u16x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([7, 8] * [2, 2]) - [1, 1] -> [-15, -17]
 * @param a A 2 element vector of 32-bit unsigned integers to multiply.
 * @param b A 2 element vector of 32-bit unsigned integers to multiply.
 * @param c A 2 element vector of 32-bit unsigned integers to sub.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdNegMsub_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, const CCSimd_u32x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([7.5, 8.5] * [2, 2]) - [1, 1] -> [-16, -18]
 * @param a A 2 element vector of 32-bit floats to multiply.
 * @param b A 2 element vector of 32-bit floats to multiply.
 * @param c A 2 element vector of 32-bit floats to add.
 * @return The vector representing the negated multiply and sub.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdNegMsub_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, const CCSimd_f32x2 c);


#pragma mark Divide

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] / [3, 3, 3, 3, 3, 3, 3, 3] -> [0, 0, 1, 1, 1, 2, 2, 2]
 * @param a An 8 element vector of 8-bit signed integers as the dividend.
 * @param b An 8 element vector of 8-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdDiv_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [5, 6, 7, 8] / [3, 3, 3, 3] -> [1, 2, 2, 2]
 * @param a A 4 element vector of 16-bit signed integers as the dividend.
 * @param b A 4 element vector of 16-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdDiv_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [7, 8] / [3, 3] -> [2, 2]
 * @param a A 2 element vector of 32-bit signed integers as the dividend.
 * @param b A 2 element vector of 32-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdDiv_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] / [3, 3, 3, 3, 3, 3, 3, 3] -> [0, 0, 1, 1, 1, 2, 2, 2]
 * @param a An 8 element vector of 8-bit unsigned integers as the dividend.
 * @param b An 8 element vector of 8-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdDiv_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [5, 6, 7, 8] / [3, 3, 3, 3] -> [1, 2, 2, 2]
 * @param a A 4 element vector of 16-bit unsigned integers as the dividend.
 * @param b A 4 element vector of 16-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdDiv_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [7, 8] / [3, 3] -> [2, 2]
 * @param a A 2 element vector of 32-bit unsigned integers as the dividend.
 * @param b A 2 element vector of 32-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdDiv_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [7, 8] / [3, 3] -> [2.333333, 2.666667]
 * @param a A 2 element vector of 32-bit floats as the dividend.
 * @param b A 2 element vector of 32-bit floats as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdDiv_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Modulo

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] % [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 2, 0, 1, 2, 0, 1, 2]
 * @param a An 8 element vector of 8-bit signed integers as the dividend.
 * @param b An 8 element vector of 8-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMod_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [5, 6, 7, 8] % [3, 3, 3, 3] -> [2, 0, 1, 2]
 * @param a A 4 element vector of 16-bit signed integers as the dividend.
 * @param b A 4 element vector of 16-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMod_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [7, 8] % [3, 3] -> [1, 2]
 * @param a A 2 element vector of 32-bit signed integers as the dividend.
 * @param b A 2 element vector of 32-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMod_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] % [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 2, 0, 1, 2, 0, 1, 2]
 * @param a An 8 element vector of 8-bit unsigned integers as the dividend.
 * @param b An 8 element vector of 8-bit unsigned integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMod_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [5, 6, 7, 8] % [3, 3, 3, 3] -> [2, 0, 1, 2]
 * @param a A 4 element vector of 16-bit unsigned integers as the dividend.
 * @param b A 4 element vector of 16-bit unsigned integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMod_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [7, 8] % [3, 3] -> [1, 2]
 * @param a A 2 element vector of 32-bit signed integers as the dividend.
 * @param b A 2 element vector of 32-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMod_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [7.5, 8.5] % [3, 3] -> [1.5, 2.5]
 * @param a A 2 element vector of 32-bit floats as the dividend.
 * @param b A 2 element vector of 32-bit floats as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMod_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Rounding

/*!
 * @brief Round all elements to nearest with halves away from zero.
 * @example [10.5, 11.5] -> [11, 12]; [-10.5, -11.5] -> [-11, -12]
 * @param a The 2 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdRoundNearestAway_f32x2(const CCSimd_f32x2 a);


/*!
 * @brief Round all elements to nearest with halves to even.
 * @example [10.5, 11.5] -> [10, 12]; [-10.5, -11.5] -> [-10, -12]
 * @param a The 2 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdRoundNearestEven_f32x2(const CCSimd_f32x2 a);


/*!
 * @brief Round all elements to zero.
 * @example [10.5, 11.5] -> [10, 11]; [-10.5, -11.5] -> [-10, -11]
 * @param a The 2 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdRoundZero_f32x2(const CCSimd_f32x2 a);


/*!
 * @brief Round all elements down.
 * @example [10.5, 11.5] -> [10, 11]; [-10.5, -11.5] -> [-11, -12]
 * @param a The 2 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdFloor_f32x2(const CCSimd_f32x2 a);


/*!
 * @brief Round all lanes up.
 * @example [10.5, 11.5] -> [11, 12]; [-10.5, -11.5] -> [-10, -11]
 * @param a The 2 lane vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCeil_f32x2(const CCSimd_f32x2 a);


#pragma mark Horizontal Add

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [36, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 8-bit signed integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal add to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal add to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v4 The lane mask to indicate the horizontal add to store in [4]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v5 The lane mask to indicate the horizontal add to store in [5]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v6 The lane mask to indicate the horizontal add to store in [6]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v7 The lane mask to indicate the horizontal add to store in [7]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdHadd_s8x8(const CCSimd_s8x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [10, undefined, undefined, undefined]
 * @param a A 4 element vector of 16-bit signed integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal add to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal add to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdHadd_s16x4(const CCSimd_s16x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [3, undefined]
 * @param a A 2 element vector of 32-bit signed integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdHadd_s32x2(const CCSimd_s32x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [36, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 8-bit unsigned integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal add to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal add to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v4 The lane mask to indicate the horizontal add to store in [4]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v5 The lane mask to indicate the horizontal add to store in [5]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v6 The lane mask to indicate the horizontal add to store in [6]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v7 The lane mask to indicate the horizontal add to store in [7]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdHadd_u8x8(const CCSimd_u8x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [10, undefined, undefined, undefined]
 * @param a A 4 element vector of 16-bit unsigned integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal add to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal add to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdHadd_u16x4(const CCSimd_u16x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [3, undefined]
 * @param a A 2 element vector of 32-bit unsigned integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdHadd_u32x2(const CCSimd_u32x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1.5, 2.5].(CC_SIMD_LANE_MASK(0, 1), 0) -> [4, undefined]
 * @param a A 2 element vector of 32-bit floats to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdHadd_f32x2(const CCSimd_f32x2 a, uint8_t v0, uint8_t v1);


#pragma mark Horizontal Subtract

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [36, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [1, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 8-bit signed integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal subtract to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal subtract to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v4 The lane mask to indicate the horizontal subtract to store in [4]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v5 The lane mask to indicate the horizontal subtract to store in [5]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v6 The lane mask to indicate the horizontal subtract to store in [6]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v7 The lane mask to indicate the horizontal subtract to store in [7]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdHsub_s8x8(const CCSimd_s8x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [10, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [1, undefined, undefined, undefined]
 * @param a A 4 element vector of 16-bit signed integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal subtract to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal subtract to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdHsub_s16x4(const CCSimd_s16x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [3, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [1, undefined]
 * @param a A 2 element vector of 32-bit signed integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdHsub_s32x2(const CCSimd_s32x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [36, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [1, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 8-bit unsigned integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal subtract to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal subtract to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v4 The lane mask to indicate the horizontal subtract to store in [4]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v5 The lane mask to indicate the horizontal subtract to store in [5]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v6 The lane mask to indicate the horizontal subtract to store in [6]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v7 The lane mask to indicate the horizontal subtract to store in [7]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdHsub_u8x8(const CCSimd_u8x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [10, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [1, undefined, undefined, undefined]
 * @param a A 4 element vector of 16-bit unsigned integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the horizontal subtract to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the horizontal subtract to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdHsub_u16x4(const CCSimd_u16x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [3, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [1, undefined]
 * @param a A 2 element vector of 32-bit unsigned integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdHsub_u32x2(const CCSimd_u32x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [4, 2.5].(CC_SIMD_LANE_MASK(0, 1), 0) -> [1.5, undefined]
 * @param a A 2 element vector of 32-bit floats to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdHsub_f32x2(const CCSimd_f32x2 a, uint8_t v0, uint8_t v1);


#pragma mark Dot Product

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[2, 2, 2, 2, 2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [72, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 8-bit signed integers to use for the dot product.
 * @param b An 8 element vector of 8-bit signed integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the dot product to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the dot product to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v4 The lane mask to indicate the dot product to store in [4]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v5 The lane mask to indicate the dot product to store in [5]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v6 The lane mask to indicate the dot product to store in [6]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v7 The lane mask to indicate the dot product to store in [7]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdDot_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4]x[2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [20, undefined, undefined, undefined]
 * @param a A 4 element vector of 16-bit signed integers to use for the dot product.
 * @param b A 4 element vector of 16-bit signed integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the dot product to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the dot product to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdDot_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2]x[2, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [6, undefined]
 * @param a A 2 element vector of 32-bit signed integers to use for the dot product.
 * @param b A 2 element vector of 32-bit signed integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdDot_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[2, 2, 2, 2, 2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [72, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 8-bit unsigned integers to use for the dot product.
 * @param b An 8 element vector of 8-bit unsigned integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the dot product to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the dot product to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v4 The lane mask to indicate the dot product to store in [4]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v5 The lane mask to indicate the dot product to store in [5]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v6 The lane mask to indicate the dot product to store in [6]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v7 The lane mask to indicate the dot product to store in [7]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdDot_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4]x[2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [20, undefined, undefined, undefined]
 * @param a A 4 element vector of 16-bit unsigned integers to use for the dot product.
 * @param b A 4 element vector of 16-bit unsigned integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v2 The lane mask to indicate the dot product to store in [2]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v3 The lane mask to indicate the dot product to store in [3]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdDot_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2]x[2, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [6, undefined]
 * @param a A 2 element vector of 32-bit unsigned integers to use for the dot product.
 * @param b A 2 element vector of 32-bit unsigned integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdDot_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1.5, 2.5]x[2, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [8, undefined]
 * @param a A 2 element vector of 32-bit floats to use for the dot product.
 * @param b A 2 element vector of 32-bit floats to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdDot_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, uint8_t v0, uint8_t v1);


#pragma mark Sum

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> 36
 * @param a An 8 element vector of 8-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int8_t CCSimdSum_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [5, 6, 7, 8] -> 26
 * @param a A 4 element vector of 16-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int16_t CCSimdSum_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [7, 8] -> 15
 * @param a A 2 element vector of 32-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int32_t CCSimdSum_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> 36
 * @param a An 8 element vector of 8-bit unsigned integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint8_t CCSimdSum_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [5, 6, 7, 8] -> 26
 * @param a A 4 element vector of 16-bit unsigned integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint16_t CCSimdSum_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [7, 8] -> 15
 * @param a A 2 element vector of 32-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint32_t CCSimdSum_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [7.5, 8] -> 15.5
 * @param a A 2 element vector of 32-bit floats to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE float CCSimdSum_f32x2(const CCSimd_f32x2 a);


#pragma mark Negate

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8] -> [-1, -2, -3, -4, -5, -6, -7, -8]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdNeg_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4] -> [-1, -2, -3, -4]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdNeg_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2] -> [-1, -2]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdNeg_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8] -> [-1, -2, -3, -4, -5, -6, -7, -8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdNeg_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4] -> [-1, -2, -3, -4]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdNeg_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2] -> [-1, -2]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdNeg_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1.5, 2.5] -> [-1.5, -2.5]
 * @param a A 2 element vector of 32-bit floats.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdNeg_f32x2(const CCSimd_f32x2 a);


#pragma mark Absolute

/*!
 * @brief Absolute each element in @b a.
 * @example [-1, -2, -3, -4, -5, -6, -7, -8] -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdAbs_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Absolute each element in @b a.
 * @example [-1, -2, -3, -4] -> [1, 2, 3, 4]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdAbs_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Absolute each element in @b a.
 * @example [-1, -2] -> [1, 2]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdAbs_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Absolute each element in @b a.
 * @example [-1, -2, -3, -4, -5, -6, -7, -8] -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdAbs_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Absolute each element in @b a.
 * @example [-1, -2, -3, -4] -> [1, 2, 3, 4]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdAbs_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Absolute each element in @b a.
 * @example [-1, -2] -> [1, 2]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdAbs_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Absolute each element in @b a.
 * @example [-1.5, -2.5] -> [1.5, 2.5]
 * @param a A 2 element vector of 32-bit floats.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdAbs_f32x2(const CCSimd_f32x2 a);


#pragma mark Min

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMin_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40], [10, 2, 30, 4]) -> [1, 2, 3, 4]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMin_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20], [10, 2]) -> [1, 2]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMin_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMin_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40], [10, 2, 30, 4]) -> [1, 2, 3, 4]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMin_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20], [10, 2]) -> [1, 2]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMin_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([7.5, 8.5], [2, 2]) -> [9.5, 10.5]
 * @param a A 2 element vector of 32-bit floats.
 * @param b A 2 element vector of 32-bit floats.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMin_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Max

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [10, 20, 30, 40, 50, 60, 70, 80]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMax_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40], [10, 2, 30, 4]) -> [10, 20, 30, 40]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMax_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20], [10, 2]) -> [10, 20]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMax_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [10, 20, 30, 40, 50, 60, 70, 80]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMax_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40], [10, 2, 30, 4]) -> [10, 20, 30, 40]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMax_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20], [10, 2]) -> [10, 20]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMax_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([7.5, 8.5], [2, 2]) -> [9.5, 10.5]
 * @param a A 2 element vector of 32-bit floats.
 * @param b A 2 element vector of 32-bit floats.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMax_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Clamp

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4, 5, 6, 7, 8], [10 10, 10, 10, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1]) -> [10, 10, 10, 10, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers to be clamped.
 * @param min An 8 element vector of 8-bit signed integers to use as the minimum.
 * @param max An 8 element vector of 8-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdClamp_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 min, const CCSimd_s8x8 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4], [10 10, 0, 0], [0, 0, 1, 1]) -> [10, 10, 1, 1]
 * @param a A 4 element vector of 16-bit signed integers to be clamped.
 * @param min A 4 element vector of 16-bit signed integers to use as the minimum.
 * @param max A 4 element vector of 16-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdClamp_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 min, const CCSimd_s16x4 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2], [10, 0], [0, 1]) -> [10, 1]
 * @param a A 2 element vector of 32-bit signed integers to be clamped.
 * @param min A 2 element vector of 32-bit signed integers to use as the minimum.
 * @param max A 2 element vector of 32-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdClamp_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 min, const CCSimd_s32x2 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4, 5, 6, 7, 8], [10 10, 10, 10, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1]) -> [10, 10, 10, 10, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers to be clamped.
 * @param min An 8 element vector of 8-bit unsigned integers to use as the minimum.
 * @param max An 8 element vector of 8-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdClamp_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 min, const CCSimd_u8x8 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4], [10 10, 0, 0], [0, 0, 1, 1]) -> [10, 10, 1, 1]
 * @param a A 4 element vector of 16-bit unsigned integers to be clamped.
 * @param min A 4 element vector of 16-bit unsigned integers to use as the minimum.
 * @param max A 4 element vector of 16-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdClamp_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 min, const CCSimd_u16x4 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2], [10, 0], [0, 1]) -> [10, 1]
 * @param a A 2 element vector of 32-bit unsigned integers to be clamped.
 * @param min A 2 element vector of 32-bit unsigned integers to use as the minimum.
 * @param max A 2 element vector of 32-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdClamp_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 min, const CCSimd_u32x2 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([7.5, 8.5], [2, 2]) -> [9.5, 10.5]
 * @param a A 2 element vector of 32-bit floats to be clamped.
 * @param min A 2 element vector of 32-bit floats to use as the minimum.
 * @param max A 2 element vector of 32-bit floats to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdClamp_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 min, const CCSimd_f32x2 max);


#pragma mark Sine

/*!
 * @brief Compute the sine of each radian element in the vector.
 * @param a A 2 element vector of 32-bit floats to be sined.
 * @return The sined vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the sine of each positive radian element in the vector.
 * @param a A 2 element vector of 32-bit floats to be sined.
 * @return The sined vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the sine of each -pi to pi (-180° to 180°) radian element in the vector.
 * @param a A 2 element vector of 32-bit floats to be sined.
 * @return The sined vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPiRadSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the sine of each 0 to pi (0° to 180°) radian element in the vector.
 * @param a A 2 element vector of 32-bit floats to be sined.
 * @return The sined vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosPiRadSin_f32x2(const CCSimd_f32x2 a);


#pragma mark - Reordering
#pragma mark Swizzle

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2, 3, 4, 5, 6, 7, 8].(0,1,0,1,2,3,2,3) -> [1, 2, 1, 2, 3, 4, 3, 4]
 * @param a An 8 element vector of 8-bit signed integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @param v4 The index of the element in @b a to be moved to [4].
 * @param v5 The index of the element in @b a to be moved to [5].
 * @param v6 The index of the element in @b a to be moved to [6].
 * @param v7 The index of the element in @b a to be moved to [7].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdSwizzle_s8x8(const CCSimd_s8x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2, 3, 4].(0,1,0,1) -> [1, 2, 1, 2]
 * @param a A 4 element vector of 16-bit signed integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdSwizzle_s16x4(const CCSimd_s16x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2].(0,0) -> [1, 1]
 * @param a A 2 element vector of 32-bit signed integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdSwizzle_s32x2(const CCSimd_s32x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2, 3, 4, 5, 6, 7, 8].(0,1,0,1,2,3,2,3) -> [1, 2, 1, 2, 3, 4, 3, 4]
 * @param a An 8 element vector of 8-bit unsigned integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @param v4 The index of the element in @b a to be moved to [4].
 * @param v5 The index of the element in @b a to be moved to [5].
 * @param v6 The index of the element in @b a to be moved to [6].
 * @param v7 The index of the element in @b a to be moved to [7].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdSwizzle_u8x8(const CCSimd_u8x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2, 3, 4].(0,1,0,1) -> [1, 2, 1, 2]
 * @param a A 4 element vector of 16-bit unsigned integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdSwizzle_u16x4(const CCSimd_u16x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2].(0,0) -> [1, 1]
 * @param a A 2 element vector of 32-bit unsigned integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdSwizzle_u32x2(const CCSimd_u32x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [1, 2].(0,0) -> [1, 1]
 * @param a A 2 element vector of 32-bit floats to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSwizzle_f32x2(const CCSimd_f32x2 a, uint8_t v0, uint8_t v1);


#pragma mark Interleave

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(0,1,0,1,0,1,0,1) -> [1, 20, 3, 40, 5, 60, 7, 80]
 * @param a An 8 element vector of 8-bit signed integers to interleave.
 * @param b An 8 element vector of 8-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v4 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v5 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v6 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v7 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdInterleave_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(0,1,0,1) -> [1, 20, 3, 40]
 * @param a An 4 element vector of 16-bit signed integers to interleave.
 * @param b An 4 element vector of 16-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdInterleave_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2]x[10, 20].(0,1) -> [1, 20]
 * @param a An 2 element vector of 32-bit signed integers to interleave.
 * @param b An 2 element vector of 32-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdInterleave_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(0,1,0,1,0,1,0,1) -> [1, 20, 3, 40, 5, 60, 7, 80]
 * @param a An 8 element vector of 8-bit unsigned integers to interleave.
 * @param b An 8 element vector of 8-bit unsigned integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v4 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v5 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v6 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v7 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdInterleave_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(0,1,0,1) -> [1, 20, 3, 40]
 * @param a An 4 element vector of 16-bit unsigned integers to interleave.
 * @param b An 4 element vector of 16-bit unsigned integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdInterleave_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2]x[10, 20].(0,1) -> [1, 20]
 * @param a An 2 element vector of 32-bit signed integers to interleave.
 * @param b An 2 element vector of 32-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdInterleave_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2]x[10, 20].(0,1) -> [1, 20]
 * @param a An 2 element vector of 32-bit floats to interleave.
 * @param b An 2 element vector of 32-bit floats to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdInterleave_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, uint8_t v0, uint8_t v1);


#pragma mark Merge

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(CC_SIMD_B1,CC_SIMD_A1,CC_SIMD_A1,CC_SIMD_B1, CC_SIMD_B1,CC_SIMD_A1,CC_SIMD_A1,CC_SIMD_B1) -> [20, 2, 2, 20, 20, 2, 2, 20]
 * @param a An 8 element vector of 8-bit signed integers to merge.
 * @param b An 8 element vector of 8-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v4 The vector element argument to be moved to [4]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v5 The vector element argument to be moved to [5]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v6 The vector element argument to be moved to [6]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v7 The vector element argument to be moved to [7]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMerge_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(CC_SIMD_B1,CC_SIMD_A1,CC_SIMD_A1,CC_SIMD_B1) -> [20, 2, 2, 20]
 * @param a An 4 element vector of 16-bit signed integers to merge.
 * @param b An 4 element vector of 16-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMerge_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2]x[10, 20].(CC_SIMD_B1,CC_SIMD_A1) -> [20, 2]
 * @param a An 2 element vector of 32-bit signed integers to merge.
 * @param b An 2 element vector of 32-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMerge_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(CC_SIMD_B1,CC_SIMD_A1,CC_SIMD_A1,CC_SIMD_B1, CC_SIMD_B1,CC_SIMD_A1,CC_SIMD_A1,CC_SIMD_B1) -> [20, 2, 2, 20, 20, 2, 2, 20]
 * @param a An 8 element vector of 8-bit unsigned integers to merge.
 * @param b An 8 element vector of 8-bit unsigned integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v4 The vector element argument to be moved to [4]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v5 The vector element argument to be moved to [5]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v6 The vector element argument to be moved to [6]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v7 The vector element argument to be moved to [7]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMerge_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(CC_SIMD_B1,CC_SIMD_A1,CC_SIMD_A1,CC_SIMD_B1) -> [20, 2, 2, 20]
 * @param a An 4 element vector of 16-bit signed integers to merge.
 * @param b An 4 element vector of 16-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMerge_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2]x[10, 20].(CC_SIMD_B1,CC_SIMD_A1) -> [20, 2]
 * @param a An 2 element vector of 32-bit unsigned integers to merge.
 * @param b An 2 element vector of 32-bit unsigned integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMerge_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2]x[10, 20].(CC_SIMD_B1,CC_SIMD_A1) -> [20, 2]
 * @param a An 2 element vector of 32-bit floats to merge.
 * @param b An 2 element vector of 32-bit floats to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdMerge_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b, uint8_t v0, uint8_t v1);


#pragma mark -

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosPiRadSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(M_PI);
    const CCSimd_f32x2 M = CCSimdFill_f32x2(4.0f);
    const CCSimd_f32x2 PiSqr5 = CCSimdFill_f32x2(5.0f * M_PI * M_PI);
    
    CCSimd_f32x2 Value = a;
    
    // Bhāskara I's sine approximation
    Value = CCSimdMul_f32x2(M, CCSimdMul_f32x2(Value, CCSimdSub_f32x2(Pi, Value)));
    Value = CCSimdDiv_f32x2(CCSimdMul_f32x2(M, Value), CCSimdSub_f32x2(PiSqr5, Value));
    
    return Value;
}

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 Pi2 = CCSimdFill_f32x2(M_PI * 2.0f);
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(M_PI);
    const CCSimd_f32x2 NegOne = CCSimdFill_f32x2(-1.0f);
    
    CCSimd_f32x2 Value = a;
    
    CCSimd_f32x2 Sign = CCSimdFloor_f32x2(CCSimdDiv_f32x2(CCSimdMod_f32x2(Value, Pi2), Pi));
    Sign = CCSimdSub_f32x2(CCSimdNeg_f32x2(CCSimdAdd_f32x2(Sign, Sign)), NegOne);
    
    Value = CCSimdMod_f32x2(Value, Pi);
    
    Value = CCSimdPosPiRadSin_f32x2(Value);
        
    return CCSimdMul_f32x2(Value, Sign);
}

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPiRadSin_f32x2(const CCSimd_f32x2 a)
{
    CCSimd_f32x2 Value = CCSimdAbs_f32x2(a);
    
    CCSimd_u32x2 Sign = vshl_n_u32(vshr_n_u32(vreinterpret_u32_f32(a), 31), 31);
    
    Value = CCSimdPosPiRadSin_f32x2(Value);
    
    return vreinterpret_f32_u32(veor_u32(vreinterpret_u32_f32(Value), Sign));
}

static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 Pi2 = CCSimdFill_f32x2(M_PI * 2.0f);
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(M_PI);
    const CCSimd_f32x2 NegOne = CCSimdFill_f32x2(-1.0f);
    
    CCSimd_f32x2 Value = CCSimdAbs_f32x2(a);
    
    CCSimd_f32x2 Sign = CCSimdFloor_f32x2(CCSimdDiv_f32x2(CCSimdMod_f32x2(Value, Pi2), Pi));
    Sign = CCSimdSub_f32x2(CCSimdNeg_f32x2(CCSimdAdd_f32x2(Sign, Sign)), NegOne);
    Sign = vreinterpret_f32_u32(veor_u32(vreinterpret_u32_f32(Sign), vshl_n_u32(vshr_n_u32(vreinterpret_u32_f32(a), 31), 31)));
    
    Value = CCSimdMod_f32x2(Value, Pi);
    
    Value = CCSimdPosPiRadSin_f32x2(Value);
    
    return CCSimdMul_f32x2(Value, Sign);
}

#define CC_SIMD_64_2_ELEMENT_INTEGER_TYPES \
(s32, 2), \
(u32, 2)

#define CC_SIMD_64_4_ELEMENT_INTEGER_TYPES \
(s16, 4), \
(u16, 4)

#define CC_SIMD_64_8_ELEMENT_INTEGER_TYPES \
(s8, 8), \
(u8, 8)

#define CC_SIMD_64_2_ELEMENT_FLOAT_TYPES \
(f32, 2)

#define CC_SIMD_64_SIGNED_TYPES \
(s32, 2), \
(s16, 4), \
(s8, 8), \
(f32, 2)

#define CC_SIMD_64_UNSIGNED_TYPES \
(u32, 2), \
(u16, 4), \
(u8, 8)

#define CC_SIMD_64_2_ELEMENT_TYPES \
CC_SIMD_64_2_ELEMENT_INTEGER_TYPES, \
CC_SIMD_64_2_ELEMENT_FLOAT_TYPES

#define CC_SIMD_64_4_ELEMENT_TYPES \
CC_SIMD_64_4_ELEMENT_INTEGER_TYPES

#define CC_SIMD_64_8_ELEMENT_TYPES \
CC_SIMD_64_8_ELEMENT_INTEGER_TYPES

#define CC_SIMD_64_TYPES \
CC_SIMD_64_8_ELEMENT_TYPES, \
CC_SIMD_64_4_ELEMENT_TYPES, \
CC_SIMD_64_2_ELEMENT_TYPES

#define CC_SIMD_64_INTEGER_TYPES \
CC_SIMD_64_8_ELEMENT_INTEGER_TYPES, \
CC_SIMD_64_4_ELEMENT_INTEGER_TYPES, \
CC_SIMD_64_2_ELEMENT_INTEGER_TYPES

#define CC_SIMD_64_FLOAT_TYPES \
CC_SIMD_64_2_ELEMENT_FLOAT_TYPES

#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON

#define CC_SIMD_IMPL(base, count, kind) (void){ return CC_SIMD_NAME(CCSimdFill, base, count)(0); }
CC_SIMD_DECL(CCSimdZero, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) v){ return vdup_n_##base(v); }
CC_SIMD_DECL(CCSimdFill, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) src[count]){ return vld1_##base(src); }
CC_SIMD_DECL(CCSimdLoad, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (CC_SIMD_BASE_TYPE(base) dst[count], const CC_SIMD_TYPE(base, count) src){ vst1_##base(dst, src); }
CC_SIMD_DECL(CCSimdStore, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 2, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vget_lane_##base(a, 0); \
        case 1: return vget_lane_##base(a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 4, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vget_lane_##base(a, 0); \
        case 1: return vget_lane_##base(a, 1); \
        case 2: return vget_lane_##base(a, 2); \
        case 3: return vget_lane_##base(a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 8, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vget_lane_##base(a, 0); \
        case 1: return vget_lane_##base(a, 1); \
        case 2: return vget_lane_##base(a, 2); \
        case 3: return vget_lane_##base(a, 3); \
        case 4: return vget_lane_##base(a, 4); \
        case 5: return vget_lane_##base(a, 5); \
        case 6: return vget_lane_##base(a, 6); \
        case 7: return vget_lane_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 2, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vset_lane_##base(v, a, 0); \
        case 1: return vset_lane_##base(v, a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 4, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vset_lane_##base(v, a, 0); \
        case 1: return vset_lane_##base(v, a, 1); \
        case 2: return vset_lane_##base(v, a, 2); \
        case 3: return vset_lane_##base(v, a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 8, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vset_lane_##base(v, a, 0); \
        case 1: return vset_lane_##base(v, a, 1); \
        case 2: return vset_lane_##base(v, a, 2); \
        case 3: return vset_lane_##base(v, a, 3); \
        case 4: return vset_lane_##base(v, a, 4); \
        case 5: return vset_lane_##base(v, a, 5); \
        case 6: return vset_lane_##base(v, a, 6); \
        case 7: return vset_lane_##base(v, a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1) \
{ \
    switch ((v1 << 1) | v0) \
    { \
        case 0: return a; \
        case 1: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 0, v); \
        case 2: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 1, v); \
        case 3: return CC_SIMD_NAME(CCSimdFill, base, count)(v); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

// FIXME: some interleaves are causing gpr use
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3) \
{ \
    switch ((v3 << 3) | (v2 << 2) | (v1 << 1) | v0) \
    { \
        case 0: return a; \
        case 1: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 0, v); \
        case 2: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 1, v); \
        case 3: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 1, 0, 0); \
        case 4: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 2, v); \
        case 5: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 0, 1, 0); \
        case 6: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 1, 1, 0); \
        case 7: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 1, 1, 0); \
        case 8: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 3, v); \
        case 9: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 0, 0, 1); \
        case 10: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 1, 0, 1); \
        case 11: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 1, 0, 1); \
        case 12: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 0, 1, 1); \
        case 13: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 0, 1, 1); \
        case 14: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 1, 1, 1); \
        case 15: return CC_SIMD_NAME(CCSimdFill, base, count)(v); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 0, v); \
    if (v1) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 1, v); \
    if (v2) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 2, v); \
    if (v3) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 3, v); \
    if (v4) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 4, v); \
    if (v5) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 5, v); \
    if (v6) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 6, v); \
    if (v7) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 7, v); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vadd_##base(a, b); }
CC_SIMD_DECL(CCSimdAdd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vsub_##base(a, b); }
CC_SIMD_DECL(CCSimdSub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmul_##base(a, b); }
CC_SIMD_DECL(CCSimdMul, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), c); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfma_##base(c, a, b); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b)), c); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfms_##base(c, a, b); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), c); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfma_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b)), c); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfms_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#if CC_SIMD_COMPATIBILITY
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = vset_lane_##base(vget_lane_##base(a, 0) / vget_lane_##base(b, 0), Result, 0); \
    Result = vset_lane_##base(vget_lane_##base(a, 1) / vget_lane_##base(b, 1), Result, 1); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = vset_lane_##base(vget_lane_##base(a, 0) / vget_lane_##base(b, 0), Result, 0); \
    Result = vset_lane_##base(vget_lane_##base(a, 1) / vget_lane_##base(b, 1), Result, 1); \
    Result = vset_lane_##base(vget_lane_##base(a, 2) / vget_lane_##base(b, 2), Result, 2); \
    Result = vset_lane_##base(vget_lane_##base(a, 3) / vget_lane_##base(b, 3), Result, 3); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = vset_lane_##base(vget_lane_##base(a, 0) / vget_lane_##base(b, 0), Result, 0); \
    Result = vset_lane_##base(vget_lane_##base(a, 1) / vget_lane_##base(b, 1), Result, 1); \
    Result = vset_lane_##base(vget_lane_##base(a, 2) / vget_lane_##base(b, 2), Result, 2); \
    Result = vset_lane_##base(vget_lane_##base(a, 3) / vget_lane_##base(b, 3), Result, 3); \
    Result = vset_lane_##base(vget_lane_##base(a, 4) / vget_lane_##base(b, 4), Result, 4); \
    Result = vset_lane_##base(vget_lane_##base(a, 5) / vget_lane_##base(b, 5), Result, 5); \
    Result = vset_lane_##base(vget_lane_##base(a, 6) / vget_lane_##base(b, 6), Result, 6); \
    Result = vset_lane_##base(vget_lane_##base(a, 7) / vget_lane_##base(b, 7), Result, 7); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL
#endif

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vdiv_##base(a, b); }
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#if CC_SIMD_COMPATIBILITY
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdDiv, base, count)(a, b), b)); }
CC_SIMD_DECL(CCSimdMod, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL
#endif

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdFloor, base, count)(CC_SIMD_NAME(CCSimdDiv, base, count)(a, b)), b)); }
CC_SIMD_DECL(CCSimdMod, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrnda_##base(a); }
CC_SIMD_DECL(CCSimdRoundNearestAway, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndn_##base(a); }
CC_SIMD_DECL(CCSimdRoundNearestEven, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrnd_##base(a); }
CC_SIMD_DECL(CCSimdRoundZero, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndm_##base(a); }
CC_SIMD_DECL(CCSimdFloor, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndp_##base(a); }
CC_SIMD_DECL(CCSimdCeil, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_HADD_MASK(x0, x1) ((x1) << 2) | (x0)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 <= 3) && (v1 <= 3), "Index masks must not exceed lane count"); \
    \
    switch (CC_SIMD_HADD_MASK(v0, v1)) \
    { \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), 0): \
        case CC_SIMD_HADD_MASK(0, CC_SIMD_LANE_MASK(1)): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(1)): \
        case 0: return a; \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 1); \
            \
        case CC_SIMD_HADD_MASK(0, CC_SIMD_LANE_MASK(0)): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), 0): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0); \
            \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 0, 1); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 0, 1); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
            \
        case CC_SIMD_HADD_MASK(0, CC_SIMD_LANE_MASK(0, 1)): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), 0): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_HADD_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 | ((v0 << 4) & 16), CC_SIMD_A0 | ((v1 << 4) & 16), CC_SIMD_A0 | ((v2 << 4) & 16), CC_SIMD_A0 | ((v3 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 | ((v0 << 3) & 16), CC_SIMD_A1 | ((v1 << 3) & 16), CC_SIMD_A1 | ((v2 << 3) & 16), CC_SIMD_A1 | ((v3 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 | ((v0 << 2) & 16), CC_SIMD_A2 | ((v1 << 2) & 16), CC_SIMD_A2 | ((v2 << 2) & 16), CC_SIMD_A2 | ((v3 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 | ((v0 << 1) & 16), CC_SIMD_A3 | ((v1 << 1) & 16), CC_SIMD_A3 | ((v2 << 1) & 16), CC_SIMD_A3 | ((v3 << 1) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 | ((v0 << 4) & 16), CC_SIMD_A0 | ((v1 << 4) & 16), CC_SIMD_A0 | ((v2 << 4) & 16), CC_SIMD_A0 | ((v3 << 4) & 16), CC_SIMD_A0 | ((v4 << 4) & 16), CC_SIMD_A0 | ((v5 << 4) & 16), CC_SIMD_A0 | ((v6 << 4) & 16), CC_SIMD_A0 | ((v7 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 | ((v0 << 3) & 16), CC_SIMD_A1 | ((v1 << 3) & 16), CC_SIMD_A1 | ((v2 << 3) & 16), CC_SIMD_A1 | ((v3 << 3) & 16), CC_SIMD_A1 | ((v4 << 3) & 16), CC_SIMD_A1 | ((v5 << 3) & 16), CC_SIMD_A1 | ((v6 << 3) & 16), CC_SIMD_A1 | ((v7 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 | ((v0 << 2) & 16), CC_SIMD_A2 | ((v1 << 2) & 16), CC_SIMD_A2 | ((v2 << 2) & 16), CC_SIMD_A2 | ((v3 << 2) & 16), CC_SIMD_A2 | ((v4 << 2) & 16), CC_SIMD_A2 | ((v5 << 2) & 16), CC_SIMD_A2 | ((v6 << 2) & 16), CC_SIMD_A2 | ((v7 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 | ((v0 << 1) & 16), CC_SIMD_A3 | ((v1 << 1) & 16), CC_SIMD_A3 | ((v2 << 1) & 16), CC_SIMD_A3 | ((v3 << 1) & 16), CC_SIMD_A3 | ((v4 << 1) & 16), CC_SIMD_A3 | ((v5 << 1) & 16), CC_SIMD_A3 | ((v6 << 1) & 16), CC_SIMD_A3 | ((v7 << 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L4 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A4 | ((v0 << 0) & 16), CC_SIMD_A4 | ((v1 << 0) & 16), CC_SIMD_A4 | ((v2 << 0) & 16), CC_SIMD_A4 | ((v3 << 0) & 16), CC_SIMD_A4 | ((v4 << 0) & 16), CC_SIMD_A4 | ((v5 << 0) & 16), CC_SIMD_A4 | ((v6 << 0) & 16), CC_SIMD_A4 | ((v7 << 0) & 16)); \
    const CC_SIMD_TYPE(base, count) L5 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A5 | ((v0 >> 1) & 16), CC_SIMD_A5 | ((v1 >> 1) & 16), CC_SIMD_A5 | ((v2 >> 1) & 16), CC_SIMD_A5 | ((v3 >> 1) & 16), CC_SIMD_A5 | ((v4 >> 1) & 16), CC_SIMD_A5 | ((v5 >> 1) & 16), CC_SIMD_A5 | ((v6 >> 1) & 16), CC_SIMD_A5 | ((v7 >> 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L6 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A6 | ((v0 >> 2) & 16), CC_SIMD_A6 | ((v1 >> 2) & 16), CC_SIMD_A6 | ((v2 >> 2) & 16), CC_SIMD_A6 | ((v3 >> 2) & 16), CC_SIMD_A6 | ((v4 >> 2) & 16), CC_SIMD_A6 | ((v5 >> 2) & 16), CC_SIMD_A6 | ((v6 >> 2) & 16), CC_SIMD_A6 | ((v7 >> 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L7 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A7 | ((v0 >> 3) & 16), CC_SIMD_A7 | ((v1 >> 3) & 16), CC_SIMD_A7 | ((v2 >> 3) & 16), CC_SIMD_A7 | ((v3 >> 3) & 16), CC_SIMD_A7 | ((v4 >> 3) & 16), CC_SIMD_A7 | ((v5 >> 3) & 16), CC_SIMD_A7 | ((v6 >> 3) & 16), CC_SIMD_A7 | ((v7 >> 3) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)), CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L4, L5), CC_SIMD_NAME(CCSimdAdd, base, count)(L6, L7))); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_HSUB_MASK(x0, x1) ((x1) << 2) | (x0)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 <= 3) && (v1 <= 3), "Index masks must not exceed lane count"); \
    \
    switch (CC_SIMD_HSUB_MASK(v0, v1)) \
    { \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), 0): \
        case CC_SIMD_HSUB_MASK(0, CC_SIMD_LANE_MASK(1)): \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(1)): \
        case 0: return a; \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 1); \
            \
        case CC_SIMD_HSUB_MASK(0, CC_SIMD_LANE_MASK(0)): \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), 0): \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0); \
            \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), a), 0, 1); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), a), 0, 1); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
            \
        case CC_SIMD_HSUB_MASK(0, CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), a); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), 0): return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0), CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 1)); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_HSUB_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    const uint8_t AdjustV0 = CCBitCountLowestUnset(v0); \
    const uint8_t AdjustV1 = CCBitCountLowestUnset(v1); \
    const uint8_t AdjustV2 = CCBitCountLowestUnset(v2); \
    const uint8_t AdjustV3 = CCBitCountLowestUnset(v3); \
    \
    v0 >>= AdjustV0; \
    v1 >>= AdjustV1; \
    v2 >>= AdjustV2; \
    v3 >>= AdjustV3; \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A0 + (AdjustV0 * ((v0 >> 0) & 1))) | ((v0 << 4) & 16), (CC_SIMD_A0 + (AdjustV1 * ((v1 >> 0) & 1))) | ((v1 << 4) & 16), (CC_SIMD_A0 + (AdjustV2 * ((v2 >> 0) & 1))) | ((v2 << 4) & 16), (CC_SIMD_A0 + (AdjustV3 * ((v3 >> 0) & 1))) | ((v3 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A1 + (AdjustV0 * ((v0 >> 1) & 1))) | ((v0 << 3) & 16), (CC_SIMD_A1 + (AdjustV1 * ((v1 >> 1) & 1))) | ((v1 << 3) & 16), (CC_SIMD_A1 + (AdjustV2 * ((v2 >> 1) & 1))) | ((v2 << 3) & 16), (CC_SIMD_A1 + (AdjustV3 * ((v3 >> 1) & 1))) | ((v3 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A2 + (AdjustV0 * ((v0 >> 2) & 1))) | ((v0 << 2) & 16), (CC_SIMD_A2 + (AdjustV1 * ((v1 >> 2) & 1))) | ((v1 << 2) & 16), (CC_SIMD_A2 + (AdjustV2 * ((v2 >> 2) & 1))) | ((v2 << 2) & 16), (CC_SIMD_A2 + (AdjustV3 * ((v3 >> 2) & 1))) | ((v3 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A3 + (AdjustV0 * ((v0 >> 3) & 1))) | ((v0 << 1) & 16), (CC_SIMD_A3 + (AdjustV1 * ((v1 >> 3) & 1))) | ((v1 << 1) & 16), (CC_SIMD_A3 + (AdjustV2 * ((v2 >> 3) & 1))) | ((v2 << 1) & 16), (CC_SIMD_A3 + (AdjustV3 * ((v3 >> 3) & 1))) | ((v3 << 1) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSub, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)); \
}
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    const uint8_t AdjustV0 = CCBitCountLowestUnset(v0); \
    const uint8_t AdjustV1 = CCBitCountLowestUnset(v1); \
    const uint8_t AdjustV2 = CCBitCountLowestUnset(v2); \
    const uint8_t AdjustV3 = CCBitCountLowestUnset(v3); \
    const uint8_t AdjustV4 = CCBitCountLowestUnset(v4); \
    const uint8_t AdjustV5 = CCBitCountLowestUnset(v5); \
    const uint8_t AdjustV6 = CCBitCountLowestUnset(v6); \
    const uint8_t AdjustV7 = CCBitCountLowestUnset(v7); \
    \
    v0 >>= AdjustV0; \
    v1 >>= AdjustV1; \
    v2 >>= AdjustV2; \
    v3 >>= AdjustV3; \
    v4 >>= AdjustV4; \
    v5 >>= AdjustV5; \
    v6 >>= AdjustV6; \
    v7 >>= AdjustV7; \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 + (AdjustV0 * ((v0 >> 0) & 1)) | ((v0 << 4) & 16), CC_SIMD_A0 + (AdjustV1 * ((v1 >> 0) & 1)) | ((v1 << 4) & 16), CC_SIMD_A0 + (AdjustV2 * ((v2 >> 0) & 1)) | ((v2 << 4) & 16), CC_SIMD_A0 + (AdjustV3 * ((v3 >> 0) & 1)) | ((v3 << 4) & 16), CC_SIMD_A0 + (AdjustV4 * ((v4 >> 0) & 1)) | ((v4 << 4) & 16), CC_SIMD_A0 + (AdjustV5 * ((v5 >> 0) & 1)) | ((v5 << 4) & 16), CC_SIMD_A0 + (AdjustV6 * ((v6 >> 0) & 1)) | ((v6 << 4) & 16), CC_SIMD_A0 + (AdjustV7 * ((v7 >> 0) & 1)) | ((v7 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 + (AdjustV0 * ((v0 >> 1) & 1)) | ((v0 << 3) & 16), CC_SIMD_A1 + (AdjustV1 * ((v1 >> 1) & 1)) | ((v1 << 3) & 16), CC_SIMD_A1 + (AdjustV2 * ((v2 >> 1) & 1)) | ((v2 << 3) & 16), CC_SIMD_A1 + (AdjustV3 * ((v3 >> 1) & 1)) | ((v3 << 3) & 16), CC_SIMD_A1 + (AdjustV4 * ((v4 >> 1) & 1)) | ((v4 << 3) & 16), CC_SIMD_A1 + (AdjustV5 * ((v5 >> 1) & 1)) | ((v5 << 3) & 16), CC_SIMD_A1 + (AdjustV6 * ((v6 >> 1) & 1)) | ((v6 << 3) & 16), CC_SIMD_A1 + (AdjustV7 * ((v7 >> 1) & 1)) | ((v7 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 + (AdjustV0 * ((v0 >> 2) & 1)) | ((v0 << 2) & 16), CC_SIMD_A2 + (AdjustV1 * ((v1 >> 2) & 1)) | ((v1 << 2) & 16), CC_SIMD_A2 + (AdjustV2 * ((v2 >> 2) & 1)) | ((v2 << 2) & 16), CC_SIMD_A2 + (AdjustV3 * ((v3 >> 2) & 1)) | ((v3 << 2) & 16), CC_SIMD_A2 + (AdjustV4 * ((v4 >> 2) & 1)) | ((v4 << 2) & 16), CC_SIMD_A2 + (AdjustV5 * ((v5 >> 2) & 1)) | ((v5 << 2) & 16), CC_SIMD_A2 + (AdjustV6 * ((v6 >> 2) & 1)) | ((v6 << 2) & 16), CC_SIMD_A2 + (AdjustV7 * ((v7 >> 2) & 1)) | ((v7 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 + (AdjustV0 * ((v0 >> 3) & 1)) | ((v0 << 1) & 16), CC_SIMD_A3 + (AdjustV1 * ((v1 >> 3) & 1)) | ((v1 << 1) & 16), CC_SIMD_A3 + (AdjustV2 * ((v2 >> 3) & 1)) | ((v2 << 1) & 16), CC_SIMD_A3 + (AdjustV3 * ((v3 >> 3) & 1)) | ((v3 << 1) & 16), CC_SIMD_A3 + (AdjustV4 * ((v4 >> 3) & 1)) | ((v4 << 1) & 16), CC_SIMD_A3 + (AdjustV5 * ((v5 >> 3) & 1)) | ((v5 << 1) & 16), CC_SIMD_A3 + (AdjustV6 * ((v6 >> 3) & 1)) | ((v6 << 1) & 16), CC_SIMD_A3 + (AdjustV7 * ((v7 >> 3) & 1)) | ((v7 << 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L4 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A4 + (AdjustV0 * ((v0 >> 4) & 1)) | ((v0 << 0) & 16), CC_SIMD_A4 + (AdjustV1 * ((v1 >> 4) & 1)) | ((v1 << 0) & 16), CC_SIMD_A4 + (AdjustV2 * ((v2 >> 4) & 1)) | ((v2 << 0) & 16), CC_SIMD_A4 + (AdjustV3 * ((v3 >> 4) & 1)) | ((v3 << 0) & 16), CC_SIMD_A4 + (AdjustV4 * ((v4 >> 4) & 1)) | ((v4 << 0) & 16), CC_SIMD_A4 + (AdjustV5 * ((v5 >> 4) & 1)) | ((v5 << 0) & 16), CC_SIMD_A4 + (AdjustV6 * ((v6 >> 4) & 1)) | ((v6 << 0) & 16), CC_SIMD_A4 + (AdjustV7 * ((v7 >> 4) & 1)) | ((v7 << 0) & 16)); \
    const CC_SIMD_TYPE(base, count) L5 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A5 + (AdjustV0 * ((v0 >> 5) & 1)) | ((v0 >> 1) & 16), CC_SIMD_A5 + (AdjustV1 * ((v1 >> 5) & 1)) | ((v1 >> 1) & 16), CC_SIMD_A5 + (AdjustV2 * ((v2 >> 5) & 1)) | ((v2 >> 1) & 16), CC_SIMD_A5 + (AdjustV3 * ((v3 >> 5) & 1)) | ((v3 >> 1) & 16), CC_SIMD_A5 + (AdjustV4 * ((v4 >> 5) & 1)) | ((v4 >> 1) & 16), CC_SIMD_A5 + (AdjustV5 * ((v5 >> 5) & 1)) | ((v5 >> 1) & 16), CC_SIMD_A5 + (AdjustV6 * ((v6 >> 5) & 1)) | ((v6 >> 1) & 16), CC_SIMD_A5 + (AdjustV7 * ((v7 >> 5) & 1)) | ((v7 >> 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L6 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A6 + (AdjustV0 * ((v0 >> 6) & 1)) | ((v0 >> 2) & 16), CC_SIMD_A6 + (AdjustV1 * ((v1 >> 6) & 1)) | ((v1 >> 2) & 16), CC_SIMD_A6 + (AdjustV2 * ((v2 >> 6) & 1)) | ((v2 >> 2) & 16), CC_SIMD_A6 + (AdjustV3 * ((v3 >> 6) & 1)) | ((v3 >> 2) & 16), CC_SIMD_A6 + (AdjustV4 * ((v4 >> 6) & 1)) | ((v4 >> 2) & 16), CC_SIMD_A6 + (AdjustV5 * ((v5 >> 6) & 1)) | ((v5 >> 2) & 16), CC_SIMD_A6 + (AdjustV6 * ((v6 >> 6) & 1)) | ((v6 >> 2) & 16), CC_SIMD_A6 + (AdjustV7 * ((v7 >> 6) & 1)) | ((v7 >> 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L7 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A7 + (AdjustV0 * ((v0 >> 7) & 1)) | ((v0 >> 3) & 16), CC_SIMD_A7 + (AdjustV1 * ((v1 >> 7) & 1)) | ((v1 >> 3) & 16), CC_SIMD_A7 + (AdjustV2 * ((v2 >> 7) & 1)) | ((v2 >> 3) & 16), CC_SIMD_A7 + (AdjustV3 * ((v3 >> 7) & 1)) | ((v3 >> 3) & 16), CC_SIMD_A7 + (AdjustV4 * ((v4 >> 7) & 1)) | ((v4 >> 3) & 16), CC_SIMD_A7 + (AdjustV5 * ((v5 >> 7) & 1)) | ((v5 >> 3) & 16), CC_SIMD_A7 + (AdjustV6 * ((v6 >> 7) & 1)) | ((v6 >> 3) & 16), CC_SIMD_A7 + (AdjustV7 * ((v7 >> 7) & 1)) | ((v7 >> 3) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSub, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)), CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L4, L5), CC_SIMD_NAME(CCSimdAdd, base, count)(L6, L7))); \
}
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_DOT_MASK(x0, x1) ((x1) << 2) | (x0)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 <= 3) && (v1 <= 3), "Index masks must not exceed lane count"); \
    \
    switch (CC_SIMD_DOT_MASK(v0, v1)) \
    { \
        case 0: return a; \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), 0, 0); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), 1, 1); \
        case CC_SIMD_DOT_MASK(0, CC_SIMD_LANE_MASK(1)): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), 0): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdMul, base, count)(a, b); \
        case CC_SIMD_DOT_MASK(0, CC_SIMD_LANE_MASK(0)): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), 0): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), 1, 0); \
            \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)); \
            \
        case CC_SIMD_DOT_MASK(0, CC_SIMD_LANE_MASK(0, 1)): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), 0): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_DOT_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), v0, v1, v2, v3); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), v0, v1, v2, v3, v4, v5, v6, v7); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vaddv_##base(a); }
CC_SIMD_DECL(CCSimdSum, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vneg_##base(a); }
CC_SIMD_DECL(CCSimdNeg, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_SIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_CAT(vreinterpret_, base, _, CC_SIMD_SIGNED(base))(CC_CAT(vneg_, CC_SIMD_SIGNED(base))(CC_CAT(vreinterpret_, CC_SIMD_SIGNED(base), _, base)(a))); }
CC_SIMD_DECL(CCSimdNeg, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_UNSIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vabs_##base(a); }
CC_SIMD_DECL(CCSimdAbs, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_SIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return a; }
CC_SIMD_DECL(CCSimdAbs, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_UNSIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmin_##base(a, b); }
CC_SIMD_DECL(CCSimdMin, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmax_##base(a, b); }
CC_SIMD_DECL(CCSimdMax, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) min, const CC_SIMD_TYPE(base, count) max){ return CC_SIMD_NAME(CCSimdMin, base, count)(CC_SIMD_NAME(CCSimdMax, base, count)(a, min), max); }
CC_SIMD_DECL(CCSimdClamp, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2), "Indexes must not exceed lane count"); \
    \
    switch ((v0 << 1) | v1) \
    { \
        case 0: return vdup_lane_##base(a, 0); \
        case 1: return a; \
        case 2: return vrev64_##base(a); \
        case 3: return vdup_lane_##base(a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 < 4) && (v1 < 4) && (v2 < 4) && (v3 < 4), "Indexes must not exceed lane count"); \
    \
    switch ((v0 << 6) | (v1 << 4) | (v2 << 2) | v3) \
    { \
        case 0: return vdup_lane_##base(a, 0); \
        case 1: return vzip1_##base(vdup_lane_##base(a, 0), a); /* vext_##base(vdup_lane_##base(a, 0), a, 2); //vset_lane_##base(vget_lane_##base(a, 0), vzip1_##base(a, a), 2); */ \
        case 2: return vuzp1_##base(vdup_lane_##base(a, 0), a); /* vtrn1_##base(vdup_lane_##base(a, 0), a); */ \
        case 3: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 1); \
        case 4: return vzip1_##base(a, vdup_lane_##base(a, 0)); \
        case 5: return vzip1_##base(a, a); \
        case 6: return vext_##base(vdup_lane_##base(a, 0), a, 3); /* vext_##base(vrev64_##base(a), a, 3); */ \
        case 7: return vuzp2_##base(vdup_lane_##base(a, 0), a); \
        case 8: return vtrn1_##base(a, vdup_lane_##base(a, 0)); \
        case 9: return vtrn1_##base(a, vzip1_##base(a, a)); \
        case 10: return vtrn1_##base(a, a); /* vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 2), 2); */ \
        case 11: return vset_lane_##base(vget_lane_##base(a, 0), a, 1); \
        case 12: return vset_lane_##base(vget_lane_##base(a, 3), vdup_lane_##base(a, 0), 2); \
        case 13: return vset_lane_##base(vget_lane_##base(a, 3), vzip1_##base(a, a), 2); \
        case 14: return vset_lane_##base(vget_lane_##base(a, 0), vrev32_##base(a), 0); \
        case 15: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 2); \
        case 16: return vzip2_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 17: return vreinterpret_##base##_##kind##32(vdup_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0)); /* vreinterpret_##base##_##kind##32(vzip1_##kind##32(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(a))); // vtrn1_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 1)); */ \
        case 18: return vset_lane_##base(vget_lane_##base(a, 1), vuzp1_##base(a, a), 1); \
        case 19: return vset_lane_##base(vget_lane_##base(a, 0), a, 2); /* vtrn2_##base(vdup_lane_##base(a, 0), a); // vext_##base(vrev64_##base(a), vrev32_##base(a), 3); */ \
        case 20: return vzip1_##base(a, vrev32_##base(a)); \
        case 21: return vzip1_##base(a, vdup_lane_##base(a, 1)); /* vset_lane_##base(vget_lane_##base(a, 1), vzip1_##base(a, a), 1); */ \
        case 22: return vzip1_##base(a, vext_##base(a, a, 1)); \
        case 23: return vset_lane_##base(vget_lane_##base(a, 1), a, 2); \
        case 24: return vset_lane_##base(vget_lane_##base(a, 0), a, 3); \
        case 25: return vset_lane_##base(vget_lane_##base(a, 1), a, 3); /* vtrn1_##base(a, vdup_lane_##base(a, 1)); */ \
        case 26: return vset_lane_##base(vget_lane_##base(a, 2), a, 3); \
        case 27: return a; \
        case 28: return vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0), vreinterpret_##kind##32_##base(vext_##base(a, a, 1)), 0)); \
        case 29: return vset_lane_##base(vget_lane_##base(a, 3), vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0), vreinterpret_##kind##32_##base(a), 1)), 2); \
        case 30: return vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0), vreinterpret_##kind##32_##base(vrev32_##base(a)), 0)); \
        case 31: return vset_lane_##base(vget_lane_##base(a, 3), a, 2); \
        case 32: return vuzp1_##base(a, vdup_lane_##base(a, 0)); \
        case 33: return vset_lane_##base(vget_lane_##base(a, 1), vuzp1_##base(a, a), 3); \
        case 34: return vuzp1_##base(a, a); \
        case 35: return vzip2_##base(vdup_lane_##base(a, 0), a); \
        case 36: return vset_lane_##base(vget_lane_##base(a, 0), vrev64_##base(a), 0); \
        case 37: return vuzp1_##base(a, vdup_lane_##base(a, 1)); \
        case 38: return vzip1_##base(a, vdup_lane_##base(a, 2)); \
        case 39: return vuzp2_##base(vrev32_##base(a), a); /* vuzp1_##base(a, vrev32_##base(a)); */ \
        case 40: return vuzp1_##base(a, vext_##base(a, a, 2)); /* vuzp2_##base(vrev32_##base(a), vrev64_##base(a)); */ \
        case 41: return vset_lane_##base(vget_lane_##base(a, 1), vset_lane_##base(vget_lane_##base(a, 2), a, 1), 3); \
        case 42: return vuzp1_##base(a, vdup_lane_##base(a, 2)); /* vtrn1_##base(a, vdup_lane_##base(a, 2)); */ \
        case 43: return vset_lane_##base(vget_lane_##base(a, 2), a, 1); \
        case 44: return vset_lane_##base(vget_lane_##base(a, 0), vext_##base(a, a, 1), 0); \
        case 45: return vuzp1_##base(a, vrev64_##base(a)); \
        case 46: return vset_lane_##base(vget_lane_##base(a, 3), vuzp1_##base(a, a), 2); \
        case 47: return vuzp1_##base(a, vdup_lane_##base(a, 3)); \
        case 48: return vset_lane_##base(vget_lane_##base(a, 3), vdup_lane_##base(a, 0), 1); \
        case 49: return vtrn1_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 50: return vzip1_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 51: return vtrn1_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3)); /* vtrn2_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3)); */ \
        case 52: return vzip1_##base(a, vext_##base(a, a, 3)); \
        case 53: return vset_lane_##base(vget_lane_##base(a, 3), vzip1_##base(a, a), 1); \
        case 54: return vzip1_##base(a, vrev64_##base(a)); \
        case 55: return vzip1_##base(a, vdup_lane_##base(a, 3)); \
        case 56: return vext_##base(vrev32_##base(a), a, 1); \
        case 57: return vext_##base(vrev64_##base(a), vrev64_##base(a), 3); /* vtrn1_##base(a, vrev64_##base(a)); // vext_##base(vrev32_##base(a), vrev32_##base(a), 1); */ \
        case 58: return vset_lane_##base(vget_lane_##base(a, 3), vtrn1_##base(a, a), 1); \
        case 59: return vset_lane_##base(vget_lane_##base(a, 3), a, 1); /* vtrn1_##base(a, vdup_lane_##base(a, 3)); // vext_##base(vrev32_##base(a), vrev64_##base(a), 1); */ \
        case 60: return vzip1_##base(vzip1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 61: return vuzp1_##base(vuzp1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 62: return vzip2_##base(vext_##base(vrev32_##base(a), vrev32_##base(a), 3), vrev32_##base(a)); \
        case 63: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 3); \
        case 64: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); /* vzip1_##base(vrev32_##base(a), vdup_lane_##base(a, 0)); */ \
        case 65: return vzip1_##base(vrev32_##base(a), a); /* vext_##base(vrev64_##base(a), a, 2); */ \
        case 66: return vset_lane_##base(vget_lane_##base(a, 0), vrev32_##base(a), 2); \
        case 67: return vext_##base(vzip1_##base(a, vext_##base(a, a, 3)), vzip1_##base(a, vext_##base(a, a, 3)), 2); \
        case 68: return vext_##base(vrev64_##base(a), vrev32_##base(a), 2); /* vtrn1_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 0)); */ \
        case 69: return vzip1_##base(vdup_lane_##base(a, 1), a); \
        case 70: return vext_##base(vdup_lane_##base(a, 1), a, 3); /* vtrn1_##base(vdup_lane_##base(a, 1), a); */ \
        case 71: return vset_lane_##base(vget_lane_##base(a, 0), vuzp2_##base(a, a), 1); \
        case 72: return vrev32_##base(vuzp1_##base(vzip1_##base(a, a), a)); /* vext_##base(vuzp1_##base(a, vzip1_##base(a, a)), vuzp1_##base(a, vzip1_##base(a, a)), 3); */ \
        case 73: return vzip1_##base(vext_##base(a, a, 1), a); \
        case 74: return vset_lane_##base(vget_lane_##base(a, 2), vrev32_##base(a), 2); \
        case 75: return vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1), vreinterpret_##kind##32_##base(vrev32_##base(a)), 1)); \
        case 76: return vtrn2_##base(a, vdup_lane_##base(a, 0)); /* vtrn1_##base(vrev32_##base(a), vdup_lane_##base(a, 0)); */ \
        case 77: return vset_lane_##base(vget_lane_##base(a, 1), vrev32_##base(a), 3); \
        case 78: return vext_##base(vrev64_##base(a), vrev64_##base(a), 2); /* vtrn1_##base(vrev32_##base(a), a); */ \
        case 79: return vset_lane_##base(vget_lane_##base(a, 3), vrev32_##base(a), 3); \
        case 80: return vzip2_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 81: return vext_##base(vdup_lane_##base(a, 1), a, 2); /* vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); // vzip1_##base(vrev32_##base(a), vdup_lane_##base(a, 1)); */ \
        case 82: return vuzp1_##base(vdup_lane_##base(a, 1), a); \
        case 83: return vset_lane_##base(vget_lane_##base(a, 0), vtrn2_##base(a, a), 2); \
        case 84: return vext_##base(vdup_lane_##base(a, 1), a, 1); /* vzip2_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); */ \
        case 85: return vdup_lane_##base(a, 1); \
        case 86: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 1); \
        case 87: return vuzp2_##base(vdup_lane_##base(a, 1), a); /* vtrn2_##base(vdup_lane_##base(a, 1), a); */ \
        case 88: return vset_lane_##base(vget_lane_##base(a, 0), vset_lane_##base(vget_lane_##base(a, 1), a, 0), 3); \
        case 89: return vset_lane_##base(vget_lane_##base(a, 2), vdup_lane_##base(a, 1), 2); \
        case 90: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 2); \
        case 91: return vset_lane_##base(vget_lane_##base(a, 1), a, 0); \
        case 92: return vset_lane_##base(vget_lane_##base(a, 1), vext_##base(a, a, 1), 1); \
        case 93: return vtrn2_##base(a, vdup_lane_##base(a, 1)); /* vtrn1_##base(vrev32_##base(a), vdup_lane_##base(a, 1)); */ \
        case 94: return vset_lane_##base(vget_lane_##base(a, 1), vrev32_##base(a), 1); \
        case 95: return vtrn2_##base(a, a); /* vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 3), 2); */ \
        case 96: return vset_lane_##base(vget_lane_##base(a, 0), vext_##base(a, a, 1), 2); \
        case 97: return vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0), vreinterpret_##kind##32_##base(vext_##base(a, a, 1)), 1)); \
        case 98: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); /* vzip1_##base(vrev32_##base(a), vdup_lane_##base(a, 2)); */ \
        case 99: return vzip2_##base(vrev64_##base(a), a); \
        case 100: return vtrn2_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); \
        case 101: return vset_lane_##base(vget_lane_##base(a, 2), vdup_lane_##base(a, 1), 1); \
        case 102: return vtrn1_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2)); \
        case 103: return vzip2_##base(vdup_lane_##base(a, 1), a); \
        case 104: return vset_lane_##base(vget_lane_##base(a, 2), vext_##base(a, a, 1), 2); \
        case 105: return vzip1_##base(vext_##base(a, a, 1), vrev32_##base(vext_##base(a, a, 1))); \
        case 106: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 3); \
        case 107: return vzip2_##base(vext_##base(a, a, 3), a); \
        case 108: return vext_##base(a, a, 1); \
        case 109: return vext_##base(a, vrev32_##base(a), 1); \
        case 110: return vext_##base(a, vdup_lane_##base(a, 2), 1); /* vtrn2_##base(a, vdup_lane_##base(a, 2)); */ \
        case 111: return vext_##base(a, vdup_lane_##base(a, 3), 1); /* vext_##base(a, vrev64_##base(a), 1); */ \
        case 112: return vuzp2_##base(a, vdup_lane_##base(a, 0)); \
        case 113: return vset_lane_##base(vget_lane_##base(a, 1), vext_##base(a, a, 2), 0); \
        case 114: return vuzp1_##base(vrev32_##base(a), a); /* vuzp2_##base(a, vrev32_##base(a)); */ \
        case 115: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); /* vzip1_##base(vrev32_##base(a), vdup_lane_##base(a, 3)); */ \
        case 116: return vset_lane_##base(vget_lane_##base(a, 0), vuzp2_##base(a, a), 3); \
        case 117: return vuzp2_##base(a, vdup_lane_##base(a, 1)); \
        case 118: return vzip1_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); \
        case 119: return vuzp2_##base(a, a); \
        case 120: return vuzp2_##base(a, vrev64_##base(a)); \
        case 121: return vuzp2_##base(a, vuzp1_##base(a, vdup_lane_##base(a, 1))); \
        case 122: return vuzp2_##base(a, vdup_lane_##base(a, 2)); \
        case 123: return vset_lane_##base(vget_lane_##base(a, 2), vuzp2_##base(a, a), 2); \
        case 124: return vset_lane_##base(vget_lane_##base(a, 3), vext_##base(a, a, 1), 1); \
        case 125: return vuzp2_##base(a, vext_##base(a, a, 2)); /* vuzp1_##base(vrev32_##base(a), vrev64_##base(a)); */ \
        case 126: return vset_lane_##base(vget_lane_##base(a, 3), vrev32_##base(a), 1); \
        case 127: return vuzp2_##base(a, vdup_lane_##base(a, 3)); /* vtrn2_##base(a, vdup_lane_##base(a, 3)); */ \
        case 128: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); /* vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 0), 3); */ \
        case 129: return vset_lane_##base(vget_lane_##base(a, 0), vext_##base(a, a, 2), 1); \
        case 130: return vuzp1_##base(vext_##base(a, a, 2), a); /* vuzp2_##base(vrev64_##base(a), vrev32_##base(a)); */ \
        case 131: return vuzp2_##base(vext_##base(a, a, 1), vuzp2_##base(vext_##base(a, a, 1), a)); \
        case 132: return vrev64_##base(vuzp1_##base(vzip1_##base(a, a), a)); /* vext_##base(vuzp1_##base(a, vzip1_##base(a, a)), vuzp1_##base(a, vzip1_##base(a, a)), 1); */ \
        case 133: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); \
        case 134: return vext_##base(vdup_lane_##base(a, 2), a, 3); /* vext_##base(vrev32_##base(a), a, 3); */ \
        case 135: return vuzp2_##base(vrev64_##base(a), a); \
        case 136: return vuzp2_##base(vrev64_##base(a), vrev64_##base(a)); /* vtrn1_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 0)); */ \
        case 137: return vzip1_##base(vdup_lane_##base(a, 2), a); \
        case 138: return vtrn1_##base(vdup_lane_##base(a, 2), a); /* vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); */ \
        case 139: return vset_lane_##base(vget_lane_##base(a, 0), vset_lane_##base(vget_lane_##base(a, 2), a, 0), 1); \
        case 140: return vzip2_##base(a, vdup_lane_##base(a, 0)); \
        case 141: return vzip1_##base(vext_##base(a, a, 2), a); \
        case 142: return vtrn1_##base(vzip2_##base(a, a), a); \
        case 143: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 144: return vext_##base(vrev64_##base(a), a, 1); \
        case 145: return vext_##base(vrev64_##base(a), vrev32_##base(a), 1); \
        case 146: return vuzp2_##base(vuzp1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 147: return vext_##base(vrev64_##base(a), vrev64_##base(a), 1); /* vext_##base(vrev32_##base(a), vrev32_##base(a), 3); // vtrn2_##base(vrev64_##base(a), a); */ \
        case 148: return vzip2_##base(vext_##base(vrev64_##base(a), vrev64_##base(a), 3), vrev64_##base(a)); \
        case 149: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 3); \
        case 150: return vzip1_##base(vrev32_##base(vext_##base(a, a, 1)), vext_##base(a, a, 1)); \
        case 151: return vset_lane_##base(vget_lane_##base(a, 1), vset_lane_##base(vget_lane_##base(a, 2), a, 0), 2); \
        case 152: return vzip2_##base(vdup_lane_##base(a, 2), vrev64_##base(a)); \
        case 153: return vtrn1_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1)); \
        case 154: return vset_lane_##base(vget_lane_##base(a, 1), vdup_lane_##base(a, 2), 1); \
        case 155: return vset_lane_##base(vget_lane_##base(a, 2), a, 0); /* vtrn2_##base(vdup_lane_##base(a, 2), a); */ \
        case 156: return vzip2_##base(a, vrev64_##base(a)); \
        case 157: return vzip2_##base(a, vdup_lane_##base(a, 1)); \
        case 158: return vzip2_##base(a, vext_##base(a, a, 3)); \
        case 159: return vset_lane_##base(vget_lane_##base(a, 1), vzip2_##base(a, a), 1); \
        case 160: return vext_##base(vtrn1_##base(a, a), vtrn1_##base(a, a), 2); /* vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 0), 2); */ \
        case 161: return vext_##base(vdup_lane_##base(a, 2), a, 2); \
        case 162: return vuzp1_##base(vdup_lane_##base(a, 2), a); \
        case 163: return vset_lane_##base(vget_lane_##base(a, 0), vzip2_##base(a, a), 2); \
        case 164: return vset_lane_##base(vget_lane_##base(a, 2), vrev64_##base(a), 0); \
        case 165: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 2); \
        case 166: return vset_lane_##base(vget_lane_##base(a, 1), vdup_lane_##base(a, 2), 2); \
        case 167: return vuzp2_##base(vdup_lane_##base(a, 2), a); \
        case 168: return vext_##base(vdup_lane_##base(a, 2), a, 1); \
        case 169: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 1); \
        case 170: return vdup_lane_##base(a, 2); \
        case 171: return vzip2_##base(vdup_lane_##base(a, 2), a); \
        case 172: return vset_lane_##base(vget_lane_##base(a, 2), vext_##base(a, a, 1), 0); \
        case 173: return vset_lane_##base(vget_lane_##base(a, 1), vzip2_##base(a, a), 3); \
        case 174: return vzip2_##base(a, vdup_lane_##base(a, 2)); \
        case 175: return vzip2_##base(a, a); \
        case 176: return vext_##base(a, vdup_lane_##base(a, 0), 2); \
        case 177: return vext_##base(a, a, 2); /* vreinterpret_##base##_##kind##32(vrev64_##kind##32(vreinterpret_##kind##32_##base(a))) */ \
        case 178: return vset_lane_##base(vget_lane_##base(a, 2), vext_##base(a, a, 2), 3); \
        case 179: return vtrn2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 180: return vext_##base(a, vrev32_##base(a), 2); \
        case 181: return vext_##base(a, vdup_lane_##base(a, 1), 2); \
        case 182: return vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1), vreinterpret_##kind##32_##base(vext_##base(a, a, 3)), 0)); \
        case 183: return vset_lane_##base(vget_lane_##base(a, 2), vuzp2_##base(a, a), 0); \
        case 184: return vset_lane_##base(vget_lane_##base(a, 0), vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1), vreinterpret_##kind##32_##base(a), 0)), 3); \
        case 185: return vext_##base(vrev32_##base(a), vrev64_##base(a), 3); /* vtrn1_##base(vdup_lane_##base(a, 2), vrev64_##base(a)); */ \
        case 186: return vext_##base(a, vdup_lane_##base(a, 2), 2); /* vzip1_##base(vdup_lane_##base(a, 2), vrev64_##base(a)); */ \
        case 187: return vreinterpret_##base##_##kind##32(vdup_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1)); /* vreinterpret_##base##_##kind##32(vzip2_##kind##32(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(a))); // vtrn1_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 3)); */ \
        case 188: return vzip2_##base(a, vext_##base(a, a, 1)); \
        case 189: return vset_lane_##base(vget_lane_##base(a, 3), vext_##base(a, a, 2), 2); \
        case 190: return vext_##base(a, vrev64_##base(a), 2); /* vzip2_##base(a, vrev32_##base(a)); */ \
        case 191: return vext_##base(a, vdup_lane_##base(a, 3), 2); /* vzip2_##base(a, vdup_lane_##base(a, 3)); */ \
        case 192: return vext_##base(a, vdup_lane_##base(a, 0), 3); \
        case 193: return vzip1_##base(vext_##base(a, a, 3), a); \
        case 194: return vset_lane_##base(vget_lane_##base(a, 0), vext_##base(a, a, 3), 2); \
        case 195: return vzip1_##base(vext_##base(a, a, 3), vzip1_##base(a, vext_##base(a, a, 3))); \
        case 196: return vtrn1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 197: return vset_lane_##base(vget_lane_##base(a, 3), vzip1_##base(a, a), 0); \
        case 198: return vext_##base(a, a, 3); \
        case 199: return vset_lane_##base(vget_lane_##base(a, 3), vext_##base(a, a, 3), 3); \
        case 200: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 201: return vzip1_##base(vrev64_##base(a), a); \
        case 202: return vset_lane_##base(vget_lane_##base(a, 2), vext_##base(a, a, 3), 2); \
        case 203: return vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1), vreinterpret_##kind##32_##base(vext_##base(a, a, 3)), 1)); \
        case 204: return vtrn1_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 0)); \
        case 205: return vzip1_##base(vdup_lane_##base(a, 3), a); \
        case 206: return vtrn1_##base(vdup_lane_##base(a, 3), a); \
        case 207: return vset_lane_##base(vget_lane_##base(a, 0), vdup_lane_##base(a, 3), 1); \
        case 208: return vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 209: return vset_lane_##base(vget_lane_##base(a, 3), vreinterpret_##base##_##kind##32(vset_lane_##kind##32(vget_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0), vreinterpret_##kind##32_##base(a), 1)), 0); \
        case 210: return vuzp1_##base(vrev64_##base(a), a); \
        case 211: return vext_##base(a, vrev32_##base(a), 3); \
        case 212: return vset_lane_##base(vget_lane_##base(a, 1), vrev64_##base(a), 1); \
        case 213: return vext_##base(a, vdup_lane_##base(a, 1), 3); /* vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); */ \
        case 214: return vset_lane_##base(vget_lane_##base(a, 1), vext_##base(a, a, 3), 1); \
        case 215: return vuzp2_##base(vext_##base(a, a, 2), a); /* vuzp1_##base(vrev64_##base(a), vrev32_##base(a)); */ \
        case 216: return vzip2_##base(vrev32_##base(a), vrev64_##base(a)); \
        case 217: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); \
        case 218: return vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 219: return vset_lane_##base(vget_lane_##base(a, 3), a, 0); \
        case 220: return vzip2_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 221: return vuzp1_##base(vrev64_##base(a), vrev64_##base(a)); /* vtrn1_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 1)); */ \
        case 222: return vrev64_##base(vuzp2_##base(vzip2_##base(a, a), a)); /* vext_##base(vuzp2_##base(a, vzip2_##base(a, a)), vuzp2_##base(a, vzip2_##base(a, a)), 3); */ \
        case 223: return vtrn2_##base(vdup_lane_##base(a, 3), a); /* vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); // vtrn1_##base(vdup_lane_##base(a, 3), vrev32_##base(a)); */ \
        case 224: return vset_lane_##base(vget_lane_##base(a, 0), vrev64_##base(a), 2); \
        case 225: return vext_##base(vrev32_##base(a), a, 2); \
        case 226: return vset_lane_##base(vget_lane_##base(a, 3), vuzp1_##base(a, a), 0); \
        case 227: return vzip2_##base(vext_##base(a, a, 1), a); \
        case 228: return vrev64_##base(a); \
        case 229: return vset_lane_##base(vget_lane_##base(a, 1), vrev64_##base(a), 3); \
        case 230: return vtrn1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 231: return vset_lane_##base(vget_lane_##base(a, 3), vrev64_##base(a), 3); \
        case 232: return vset_lane_##base(vget_lane_##base(a, 2), vrev64_##base(a), 2); \
        case 233: return vext_##base(a, vuzp2_##base(vuzp1_##base(a, a), a), 3); \
        case 234: return vext_##base(a, vdup_lane_##base(a, 2), 3); /* return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); */ \
        case 235: return vzip2_##base(vrev32_##base(a), a); \
        case 236: return vtrn2_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 237: return vrev32_##base(vuzp2_##base(vzip2_##base(a, a), a)); /* vext_##base(vuzp2_##base(a, vzip2_##base(a, a)), vuzp2_##base(a, vzip2_##base(a, a)), 1); */ \
        case 238: return vext_##base(vrev32_##base(a), vrev64_##base(a), 2); /* vtrn1_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 2)); */ \
        case 239: return vzip2_##base(vdup_lane_##base(a, 3), a); \
        case 240: return vext_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 0), 2); \
        case 241: return vext_##base(vdup_lane_##base(a, 3), a, 2); \
        case 242: return vuzp1_##base(vdup_lane_##base(a, 3), a); \
        case 243: return vset_lane_##base(vget_lane_##base(a, 0), vdup_lane_##base(a, 3), 2); \
        case 244: return vset_lane_##base(vget_lane_##base(a, 3), vrev64_##base(a), 1); \
        case 245: return vext_##base(vtrn2_##base(a, a), vtrn2_##base(a, a), 2); \
        case 246: return vset_lane_##base(vget_lane_##base(a, 3), vext_##base(a, a, 3), 1); \
        case 247: return vuzp2_##base(vdup_lane_##base(a, 3), a); \
        case 248: return vzip2_##base(vrev32_##base(a), vext_##base(a, a, 1)); \
        case 249: return vext_##base(a, vrev64_##base(a), 3); \
        case 250: return vzip1_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 251: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 252: return vext_##base(vdup_lane_##base(a, 3), a, 1); \
        case 253: return vtrn1_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 254: return vzip1_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 255: return vdup_lane_##base(a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 < 8) && (v1 < 8) && (v2 < 8) && (v3 < 8) && (v4 < 8) && (v5 < 8) && (v6 < 8) && (v7 < 8), "Indexes must not exceed lane count"); \
    \
    return vtbl1_##base(a, CC_SIMD_NAME(CCSimdLoad, base, count)((CC_SIMD_BASE_TYPE(base)[8]){ v0, v1, v2, v3, v4, v5, v6, v7, })); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 1) | v1) \
    { \
        case 0: return a; \
        case 1: return vset_lane_##base(vget_lane_##base(b, 1), a, 1); \
        case 2: /*return vset_lane_##base(vget_lane_##base(b, 0), a, 0); */ return vcopy_lane_##base(a, 0, b, 0); \
        case 3: return b; \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 3) | (v1 << 2) | (v2 << 1) | v3) \
    { \
        case 0: return a; \
        case 1: return vset_lane_##base(vget_lane_##base(b, 3), a, 3); \
        case 2: return vset_lane_##base(vget_lane_##base(b, 2), a, 2); \
        case 3: return vreinterpret_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 2)(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b), 0, 1)); \
        case 4: return vset_lane_##base(vget_lane_##base(b, 1), a, 1); \
        case 5: return vtrn2_##base(vrev32_##base(a), b); \
        case 6: return vset_lane_##base(vget_lane_##base(a, 3), vset_lane_##base(vget_lane_##base(a, 0), b, 0), 3); \
        case 7: return vset_lane_##base(vget_lane_##base(a, 0), b, 0); \
        case 8: return vset_lane_##base(vget_lane_##base(b, 0), a, 0); \
        case 9: return vset_lane_##base(vget_lane_##base(b, 3), vset_lane_##base(vget_lane_##base(b, 0), a, 0), 3); \
        case 10: return vtrn2_##base(vrev32_##base(b), a); \
        case 11: return vset_lane_##base(vget_lane_##base(a, 1), b, 1); \
        case 12: return vreinterpret_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 2)(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b), 1, 0)); \
        case 13: return vset_lane_##base(vget_lane_##base(a, 2), b, 2); \
        case 14: return vset_lane_##base(vget_lane_##base(a, 3), b, 3); \
        case 15: return b; \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2) && (v4 < 2) && (v5 < 2) && (v6 < 2) && (v7 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 7) | (v1 << 6) | (v2 << 5) | (v3 << 4) | (v4 << 3) | (v5 << 2) | (v6 << 1) | v7) \
    { \
        case 0: return a; \
        case 1: return vset_lane_##base(vget_lane_##base(b, 7), a, 7); \
        case 2: return vset_lane_##base(vget_lane_##base(b, 6), a, 6); \
        case 4: return vset_lane_##base(vget_lane_##base(b, 5), a, 5); \
        case 8: return vset_lane_##base(vget_lane_##base(b, 4), a, 4); \
        case 16: return vset_lane_##base(vget_lane_##base(b, 3), a, 3); \
        case 32: return vset_lane_##base(vget_lane_##base(b, 2), a, 2); \
        case 64: return vset_lane_##base(vget_lane_##base(b, 1), a, 1); \
        case 128: return vset_lane_##base(vget_lane_##base(b, 0), a, 0); \
        case 255: return b; \
            \
        case 3: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 0, 0, 1)); \
        case 12: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 0, 1, 0)); \
        case 15: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 0, 1, 1)); \
        case 48: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 0, 0)); \
        case 51: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 0, 1)); \
        case 60: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 1, 0)); \
        case 63: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 1, 1)); \
        case 192: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 0, 0)); \
        case 195: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 0, 1)); \
        case 204: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 1, 0)); \
        case 207: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 1, 1)); \
        case 240: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 1, 0, 0)); \
        case 243: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 1, 0, 1)); \
        case 252: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 1, 1, 0)); \
    } \
    \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = vset_lane_##base(vget_lane_##base(b, 0), Result, 0); \
    if (v1) Result = vset_lane_##base(vget_lane_##base(b, 1), Result, 1); \
    if (v2) Result = vset_lane_##base(vget_lane_##base(b, 2), Result, 2); \
    if (v3) Result = vset_lane_##base(vget_lane_##base(b, 3), Result, 3); \
    if (v4) Result = vset_lane_##base(vget_lane_##base(b, 4), Result, 4); \
    if (v5) Result = vset_lane_##base(vget_lane_##base(b, 5), Result, 5); \
    if (v6) Result = vset_lane_##base(vget_lane_##base(b, 6), Result, 6); \
    if (v7) Result = vset_lane_##base(vget_lane_##base(b, 7), Result, 7); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_MERGE_MASK(x0, x1) ((x0) << 5) | (x1)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog(((v0 & 0xf) < 2) && ((v1 & 0xf) < 2), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1) & ~0x11), "Indexes must only reference either a or b"); \
    \
    switch (CC_SIMD_MERGE_MASK(v0, v1)) \
    { \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0): return vzip1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1): return vzip2_##base(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0): return vext_##base(a, b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1): return vzip2_##base(a, b); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0): return vzip1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1): return vzip2_##base(CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, 0, 0), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0): return vext_##base(b, a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1): return vzip2_##base(b, a); \
    } \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 1, v1 & 1), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 1, v1 & 1), v0 >> 4, v1 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_MERGE_MASK

#define CC_SIMD_MERGE_MASK(x0, x1, x2, x3) ((x0) << 15) | ((x1) << 10) | ((x2) << 5) | (x3)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog(((v0 & 0xf) < 4) && ((v1 & 0xf) < 4) && ((v2 & 0xf) < 4) && ((v3 & 0xf) < 4), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1 | v2 | v3) & ~0x13), "Indexes must only reference either a or b"); \
    \
    switch (CC_SIMD_MERGE_MASK(v0, v1, v2, v3)) \
    { \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B3): return vreinterpret_##base##_##kind##32(vzip2_s32(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A3): return vreinterpret_##base##_##kind##32(vzip2_s32(vreinterpret_##kind##32_##base(b), vreinterpret_##kind##32_##base(a))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_A1): return vreinterpret_##base##_##kind##32(vzip1_s32(vreinterpret_##kind##32_##base(b), vreinterpret_##kind##32_##base(a))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_B1): return vreinterpret_##base##_##kind##32(vzip1_s32(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b))); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B1): return vzip1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A1): return vzip1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B3): return vzip2_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A3): return vzip2_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B2): return vuzp1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A2): return vuzp1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B3): return vuzp2_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A3): return vuzp2_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B2): return vtrn1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A2): return vtrn1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B3): return vtrn2_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A3): return vtrn2_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B0): return vext_##base(a, b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A0): return vext_##base(b, a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B1): return vext_##base(a, b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A1): return vext_##base(b, a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vext_##base(a, b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vext_##base(b, a, 3); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A0): return vrev64_##base(vzip1_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B0): return vrev64_##base(vzip1_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A2): return vrev64_##base(vzip2_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B2): return vrev64_##base(vzip2_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_A0): return vrev64_##base(vuzp1_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_B0): return vrev64_##base(vuzp1_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_A1): return vrev64_##base(vuzp2_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_B1): return vrev64_##base(vuzp2_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A0): return vrev64_##base(vtrn1_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B0): return vrev64_##base(vtrn1_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A1): return vrev64_##base(vtrn2_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B1): return vrev64_##base(vtrn2_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vrev64_##base(vext_##base(a, b, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3): return vrev32_##base(vext_##base(a, b, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vrev64_##base(vext_##base(b, a, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3): return vrev32_##base(vext_##base(b, a, 1)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_A2): return vrev64_##base(vext_##base(a, b, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B0): return vrev32_##base(vext_##base(a, b, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_B2): return vrev64_##base(vext_##base(b, a, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A0): return vrev32_##base(vext_##base(b, a, 2)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A3): return vrev64_##base(vext_##base(a, b, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B1): return vrev32_##base(vext_##base(a, b, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B3): return vrev64_##base(vext_##base(b, a, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A1): return vrev32_##base(vext_##base(b, a, 3)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B1): return vzip1_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B1): return vzip1_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B2): return vzip1_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B0): return vzip1_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B2): return vzip1_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B0): return vzip1_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A2): return vzip1_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A0): return vzip1_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A1): return vzip1_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A1): return vzip1_##base(vrev32_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A2): return vzip1_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A0): return vzip1_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B3): return vzip2_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B3): return vzip2_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B0): return vzip2_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B2): return vzip2_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A0): return vzip2_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A2): return vzip2_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A3): return vzip2_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A3): return vzip2_##base(vrev32_##base(b), a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_B2): return vuzp1_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B2): return vuzp1_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B1): return vuzp1_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B3): return vuzp1_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B1): return vuzp1_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_B3): return vuzp1_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A1): return vuzp1_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A3): return vuzp1_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_A2): return vuzp1_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A2): return vuzp1_##base(vrev32_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A1): return vuzp1_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_A3): return vuzp1_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B3): return vuzp2_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B0): return vuzp2_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_B0): return vuzp2_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B2): return vuzp2_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A0): return vuzp2_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A3): return vuzp2_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_A0): return vuzp2_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A2): return vuzp2_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B2): return vtrn1_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2): return vtrn1_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B1): return vtrn1_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B3): return vtrn1_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B1): return vtrn1_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B3): return vtrn1_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A1): return vtrn1_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A3): return vtrn1_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A2): return vtrn1_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2): return vtrn1_##base(vrev32_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A1): return vtrn1_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A3): return vtrn1_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3): return vtrn2_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B0): return vtrn2_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B0): return vtrn2_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B2): return vtrn2_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A0): return vtrn2_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3): return vtrn2_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A0): return vtrn2_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A2): return vtrn2_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B0): return vext_##base(vrev64_##base(a), b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B0): return vext_##base(vrev32_##base(a), b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B3): return vext_##base(a, vrev64_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B1): return vext_##base(a, vrev32_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B3): return vext_##base(vrev32_##base(a), vrev64_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B1): return vext_##base(vrev64_##base(a), vrev32_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B1): return vext_##base(vrev32_##base(a), vrev32_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A3): return vext_##base(b, vrev64_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A1): return vext_##base(b, vrev32_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A0): return vext_##base(vrev64_##base(b), a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A0): return vext_##base(vrev32_##base(b), a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A3): return vext_##base(vrev32_##base(b), vrev64_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A1): return vext_##base(vrev64_##base(b), vrev32_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A1): return vext_##base(vrev32_##base(b), vrev32_##base(a), 1); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1): return vext_##base(vrev64_##base(a), b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B1): return vext_##base(vrev32_##base(a), b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B2): return vext_##base(a, vrev64_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B0): return vext_##base(a, vrev32_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B2): return vext_##base(vrev32_##base(a), vrev64_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B0): return vext_##base(vrev64_##base(a), vrev32_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A2): return vext_##base(b, vrev64_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A0): return vext_##base(b, vrev32_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A1): return vext_##base(vrev64_##base(b), a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A1): return vext_##base(vrev32_##base(b), a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A2): return vext_##base(vrev32_##base(b), vrev64_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A0): return vext_##base(vrev64_##base(b), vrev32_##base(a), 2); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vext_##base(vrev64_##base(a), b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vext_##base(vrev32_##base(a), b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vext_##base(a, vrev64_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vext_##base(a, vrev32_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vext_##base(vrev32_##base(a), vrev64_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vext_##base(vrev64_##base(a), vrev32_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vext_##base(vrev32_##base(a), vrev32_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vext_##base(b, vrev64_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vext_##base(b, vrev32_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vext_##base(vrev64_##base(b), a, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vext_##base(vrev32_##base(b), a, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vext_##base(vrev32_##base(b), vrev64_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vext_##base(vrev64_##base(b), vrev32_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vext_##base(vrev32_##base(b), vrev32_##base(a), 3); \
    } \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 3, v1 & 3, v2 & 3, v3 & 3), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 3, v1 & 3, v2 & 3, v3 & 3), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_MERGE_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog(((v0 & 0xf) < 8) && ((v1 & 0xf) < 8) && ((v2 & 0xf) < 8) && ((v3 & 0xf) < 8) && ((v4 & 0xf) < 8) && ((v5 & 0xf) < 8) && ((v6 & 0xf) < 8) && ((v7 & 0xf) < 8), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7) & ~0x17), "Indexes must only reference either a or b"); \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 7, v1 & 7, v2 & 7, v3 & 7, v4 & 7, v5 & 7, v6 & 7, v7 & 7), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 7, v1 & 7, v2 & 7, v3 & 7, v4 & 7, v5 & 7, v6 & 7, v7 & 7), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4, v4 >> 4, v5 >> 4, v6 >> 4, v7 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#endif

#endif
