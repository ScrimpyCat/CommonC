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

#ifndef CommonC_Simd128_h
#define CommonC_Simd128_h

#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <CommonC/Maths.h>
#include <CommonC/BitTricks.h>

#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
#include <CommonC/Simd128Types_arm.h>
#endif


typedef struct { CCSimd_s8x16 v[2]; } CCSimd_s8x16x2;
typedef struct { CCSimd_s8x16 v[3]; } CCSimd_s8x16x3;
typedef struct { CCSimd_s8x16 v[4]; } CCSimd_s8x16x4;
typedef struct { CCSimd_s16x8 v[2]; } CCSimd_s16x8x2;
typedef struct { CCSimd_s16x8 v[3]; } CCSimd_s16x8x3;
typedef struct { CCSimd_s16x8 v[4]; } CCSimd_s16x8x4;
typedef struct { CCSimd_s32x4 v[2]; } CCSimd_s32x4x2;
typedef struct { CCSimd_s32x4 v[3]; } CCSimd_s32x4x3;
typedef struct { CCSimd_s32x4 v[4]; } CCSimd_s32x4x4;
typedef struct { CCSimd_s64x2 v[2]; } CCSimd_s64x2x2;
typedef struct { CCSimd_s64x2 v[3]; } CCSimd_s64x2x3;
typedef struct { CCSimd_s64x2 v[4]; } CCSimd_s64x2x4;

typedef struct { CCSimd_u8x16 v[2]; } CCSimd_u8x16x2;
typedef struct { CCSimd_u8x16 v[3]; } CCSimd_u8x16x3;
typedef struct { CCSimd_u8x16 v[4]; } CCSimd_u8x16x4;
typedef struct { CCSimd_u16x8 v[2]; } CCSimd_u16x8x2;
typedef struct { CCSimd_u16x8 v[3]; } CCSimd_u16x8x3;
typedef struct { CCSimd_u16x8 v[4]; } CCSimd_u16x8x4;
typedef struct { CCSimd_u32x4 v[2]; } CCSimd_u32x4x2;
typedef struct { CCSimd_u32x4 v[3]; } CCSimd_u32x4x3;
typedef struct { CCSimd_u32x4 v[4]; } CCSimd_u32x4x4;
typedef struct { CCSimd_u64x2 v[2]; } CCSimd_u64x2x2;
typedef struct { CCSimd_u64x2 v[3]; } CCSimd_u64x2x3;
typedef struct { CCSimd_u64x2 v[4]; } CCSimd_u64x2x4;

typedef struct { CCSimd_f32x4 v[2]; } CCSimd_f32x4x2;
typedef struct { CCSimd_f32x4 v[3]; } CCSimd_f32x4x3;
typedef struct { CCSimd_f32x4 v[4]; } CCSimd_f32x4x4;
typedef struct { CCSimd_f64x2 v[2]; } CCSimd_f64x2x2;
typedef struct { CCSimd_f64x2 v[3]; } CCSimd_f64x2x3;
typedef struct { CCSimd_f64x2 v[4]; } CCSimd_f64x2x4;


#pragma mark - Setting and Getting
#pragma mark Zero

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdZero_s8x16(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdZero_s16x8(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdZero_s32x4(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdZero_s64x2(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdZero_u8x16(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdZero_u16x8(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdZero_u32x4(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdZero_u64x2(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdZero_f32x4(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdZero_f64x2(void);


#pragma mark Fill

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdFill_s8x16(const int8_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdFill_s16x8(const int16_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdFill_s32x4(const int32_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdFill_s64x2(const int64_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdFill_u8x16(const uint8_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdFill_u16x8(const uint16_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdFill_u32x4(const uint32_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdFill_u64x2(const uint64_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdFill_f32x4(const float v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdFill_f64x2(const double v);


#pragma mark Load

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdLoad_s8x16(const int8_t v[16]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdLoad_s16x8(const int16_t v[8]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdLoad_s32x4(const int32_t v[4]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdLoad_s64x2(const int64_t v[2]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdLoad_u8x16(const uint8_t v[16]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdLoad_u16x8(const uint16_t v[8]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdLoad_u32x4(const uint32_t v[4]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdLoad_u64x2(const uint64_t v[2]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdLoad_f32x4(const float v[4]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdLoad_f64x2(const double v[2]);


#pragma mark Store

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 16 element vector of 8-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s8x16(int8_t dst[16], const CCSimd_s8x16 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src An 8 element vector of 16-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s16x8(int16_t dst[8], const CCSimd_s16x8 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 4 element vector of 32-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s32x4(int32_t dst[4], const CCSimd_s32x4 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 2 element vector of 64-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s64x2(int64_t dst[2], const CCSimd_s64x2 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 16 element vector of 8-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u8x16(uint8_t dst[16], const CCSimd_u8x16 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src An 8 element vector of 16-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u16x8(uint16_t dst[8], const CCSimd_u16x8 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 4 element vector of 32-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u32x4(uint32_t dst[4], const CCSimd_u32x4 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 2 element vector of 64-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u64x2(uint64_t dst[2], const CCSimd_u64x2 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 4 element vector of 32-bit floats to store.
 */
static CC_FORCE_INLINE void CCSimdStore_f32x4(float dst[4], const CCSimd_f32x4 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 2 element vector of 64-bit floats to store.
 */
static CC_FORCE_INLINE void CCSimdStore_f64x2(double dst[2], const CCSimd_f64x2 src);


#pragma mark Interleaved Loads
#pragma mark 2 Vector Interleaved Load

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s8x16x2 CCSimdInterleaveLoad_s8x16x2(const int8_t v[32]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x8x2 CCSimdInterleaveLoad_s16x8x2(const int16_t v[16]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x4x2 CCSimdInterleaveLoad_s32x4x2(const int32_t v[8]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s64x2x2 CCSimdInterleaveLoad_s64x2x2(const int64_t v[4]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x16x2 CCSimdInterleaveLoad_u8x16x2(const uint8_t v[32]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x8x2 CCSimdInterleaveLoad_u16x8x2(const uint16_t v[16]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x4x2 CCSimdInterleaveLoad_u32x4x2(const uint32_t v[8]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u64x2x2 CCSimdInterleaveLoad_u64x2x2(const uint64_t v[4]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x4x2 CCSimdInterleaveLoad_f32x4x2(const float v[8]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f64x2x2 CCSimdInterleaveLoad_f64x2x2(const double v[4]);


#pragma mark 3 Vector Interleaved Load

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s8x16x3 CCSimdInterleaveLoad_s8x16x3(const int8_t v[48]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x8x3 CCSimdInterleaveLoad_s16x8x3(const int16_t v[24]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x4x3 CCSimdInterleaveLoad_s32x4x3(const int32_t v[12]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s64x2x3 CCSimdInterleaveLoad_s64x2x3(const int64_t v[6]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x16x3 CCSimdInterleaveLoad_u8x16x3(const uint8_t v[48]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x8x3 CCSimdInterleaveLoad_u16x8x3(const uint16_t v[24]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x4x3 CCSimdInterleaveLoad_u32x4x3(const uint32_t v[12]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u64x2x3 CCSimdInterleaveLoad_u64x2x3(const uint64_t v[6]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x4x3 CCSimdInterleaveLoad_f32x4x3(const float v[12]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f64x2x3 CCSimdInterleaveLoad_f64x2x3(const double v[6]);


#pragma mark 4 Vector Interleaved Load

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s8x16x4 CCSimdInterleaveLoad_s8x16x4(const int8_t v[64]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x8x4 CCSimdInterleaveLoad_s16x8x4(const int16_t v[32]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x4x4 CCSimdInterleaveLoad_s32x4x4(const int32_t v[16]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s64x2x4 CCSimdInterleaveLoad_s64x2x4(const int64_t v[8]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x16x4 CCSimdInterleaveLoad_u8x16x4(const uint8_t v[64]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x8x4 CCSimdInterleaveLoad_u16x8x4(const uint16_t v[32]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x4x4 CCSimdInterleaveLoad_u32x4x4(const uint32_t v[16]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u64x2x4 CCSimdInterleaveLoad_u64x2x4(const uint64_t v[8]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x4x4 CCSimdInterleaveLoad_f32x4x4(const float v[16]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f64x2x4 CCSimdInterleaveLoad_f64x2x4(const double v[8]);


#pragma mark Interleaved Stores
#pragma mark 2 Vector Interleaved Store

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 16 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s8x16x2(int8_t dst[32], const CCSimd_s8x16x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s16x8x2(int16_t dst[16], const CCSimd_s16x8x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 32-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s32x4x2(int32_t dst[8], const CCSimd_s32x4x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 64-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s64x2x2(int64_t dst[4], const CCSimd_s64x2x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 16 element vectors of 8-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u8x16x2(uint8_t dst[32], const CCSimd_u8x16x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 16-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u16x8x2(uint16_t dst[16], const CCSimd_u16x8x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 32-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u32x4x2(uint32_t dst[8], const CCSimd_u32x4x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 64-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u64x2x2(uint64_t dst[4], const CCSimd_u64x2x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 32-bit floats to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f32x4x2(float dst[8], const CCSimd_f32x4x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 64-bit floats to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f64x2x2(double dst[4], const CCSimd_f64x2x2 src);


#pragma mark 3 Vector Interleaved Store

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 16 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s8x16x3(int8_t dst[48], const CCSimd_s8x16x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 8 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s16x8x3(int16_t dst[24], const CCSimd_s16x8x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 4 element vectors of 32-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s32x4x3(int32_t dst[12], const CCSimd_s32x4x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 2 element vectors of 64-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s64x2x3(int64_t dst[6], const CCSimd_s64x2x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 16 element vectors of 8-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u8x16x3(uint8_t dst[48], const CCSimd_u8x16x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 8 element vectors of 16-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u16x8x3(uint16_t dst[24], const CCSimd_u16x8x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 4 element vectors of 32-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u32x4x3(uint32_t dst[12], const CCSimd_u32x4x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 2 element vectors of 64-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u64x2x3(uint64_t dst[6], const CCSimd_u64x2x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 4 element vectors of 32-bit floats to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f32x4x3(float dst[12], const CCSimd_f32x4x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three 2 element vectors of 64-bit floats to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f64x2x3(double dst[6], const CCSimd_f64x2x3 src);


#pragma mark 4 Vector Interleaved Store

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 16 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s8x16x4(int8_t dst[64], const CCSimd_s8x16x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 8 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s16x8x4(int16_t dst[32], const CCSimd_s16x8x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 4 element vectors of 32-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s32x4x4(int32_t dst[16], const CCSimd_s32x4x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 2 element vectors of 64-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s64x2x4(int64_t dst[8], const CCSimd_s64x2x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 16 element vectors of 8-bit unsigned integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u8x16x4(uint8_t dst[64], const CCSimd_u8x16x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 8 element vectors of 16-bit unsigned integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u16x8x4(uint16_t dst[32], const CCSimd_u16x8x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 4 element vectors of 32-bit unsigned integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u32x4x4(uint32_t dst[16], const CCSimd_u32x4x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 2 element vectors of 64-bit unsigned integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u64x2x4(uint64_t dst[8], const CCSimd_u64x2x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 4 element vectors of 32-bit floats to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f32x4x4(float dst[16], const CCSimd_f32x4x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four 2 element vectors of 64-bit floats to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f64x2x4(double dst[8], const CCSimd_f64x2x4 src);


#pragma mark Get Element

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 16 element vector of 8-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int8_t CCSimdGet_s8x16(const CCSimd_s8x16 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 8 element vector of 16-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int16_t CCSimdGet_s16x8(const CCSimd_s16x8 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 4 element vector of 32-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int32_t CCSimdGet_s32x4(const CCSimd_s32x4 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 2 element vector of 64-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int64_t CCSimdGet_s64x2(const CCSimd_s64x2 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 16 element vector of 8-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint8_t CCSimdGet_u8x16(const CCSimd_u8x16 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 8 element vector of 16-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint16_t CCSimdGet_u16x8(const CCSimd_u16x8 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 4 element vector of 32-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint32_t CCSimdGet_u32x4(const CCSimd_u32x4 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 2 element vector of 64-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint64_t CCSimdGet_u64x2(const CCSimd_u64x2 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 4 element vector of 32-bit floats.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE float CCSimdGet_f32x4(const CCSimd_f32x4 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 2 element vector of 64-bit floats.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE double CCSimdGet_f64x2(const CCSimd_f64x2 a, uint8_t index);


#pragma mark Set Element

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 16 element vector of 8-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdSet_s8x16(const CCSimd_s8x16 a, uint8_t index, int8_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 8 element vector of 16-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdSet_s16x8(const CCSimd_s16x8 a, uint8_t index, int16_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 4 element vector of 32-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdSet_s32x4(const CCSimd_s32x4 a, uint8_t index, int32_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 2 element vector of 64-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdSet_s64x2(const CCSimd_s64x2 a, uint8_t index, int64_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 16 element vector of 8-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdSet_u8x16(const CCSimd_u8x16 a, uint8_t index, uint8_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 8 element vector of 16-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdSet_u16x8(const CCSimd_u16x8 a, uint8_t index, uint16_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 4 element vector of 32-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdSet_u32x4(const CCSimd_u32x4 a, uint8_t index, uint32_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 2 element vector of 64-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdSet_u64x2(const CCSimd_u64x2 a, uint8_t index, uint64_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 4 element vector of 32-bit floats.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSet_f32x4(const CCSimd_f32x4 a, uint8_t index, float v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 2 element vector of 64-bit floats.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSet_f64x2(const CCSimd_f64x2 a, uint8_t index, double v);


#pragma mark Set Sequence

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 16 element vector of 8-bit signed integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @param v4 Whether the element should be set (1) or not (0).
 * @param v5 Whether the element should be set (1) or not (0).
 * @param v6 Whether the element should be set (1) or not (0).
 * @param v7 Whether the element should be set (1) or not (0).
 * @param v8 Whether the element should be set (1) or not (0).
 * @param v9 Whether the element should be set (1) or not (0).
 * @param v10 Whether the element should be set (1) or not (0).
 * @param v11 Whether the element should be set (1) or not (0).
 * @param v12 Whether the element should be set (1) or not (0).
 * @param v13 Whether the element should be set (1) or not (0).
 * @param v14 Whether the element should be set (1) or not (0).
 * @param v15 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdSetSequence_s8x16(const CCSimd_s8x16 a, int8_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7, _Bool v8, _Bool v9, _Bool v10, _Bool v11, _Bool v12, _Bool v13, _Bool v14, _Bool v15);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 8 element vector of 16-bit signed integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @param v4 Whether the element should be set (1) or not (0).
 * @param v5 Whether the element should be set (1) or not (0).
 * @param v6 Whether the element should be set (1) or not (0).
 * @param v7 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdSetSequence_s16x8(const CCSimd_s16x8 a, int16_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 4 element vector of 32-bit signed integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdSetSequence_s32x4(const CCSimd_s32x4 a, int32_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 2 element vector of 64-bit signed integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdSetSequence_s64x2(const CCSimd_s64x2 a, int64_t v, _Bool v0, _Bool v1);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 16 element vector of 8-bit unsigned integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @param v4 Whether the element should be set (1) or not (0).
 * @param v5 Whether the element should be set (1) or not (0).
 * @param v6 Whether the element should be set (1) or not (0).
 * @param v7 Whether the element should be set (1) or not (0).
 * @param v8 Whether the element should be set (1) or not (0).
 * @param v9 Whether the element should be set (1) or not (0).
 * @param v10 Whether the element should be set (1) or not (0).
 * @param v11 Whether the element should be set (1) or not (0).
 * @param v12 Whether the element should be set (1) or not (0).
 * @param v13 Whether the element should be set (1) or not (0).
 * @param v14 Whether the element should be set (1) or not (0).
 * @param v15 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdSetSequence_u8x16(const CCSimd_u8x16 a, uint8_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7, _Bool v8, _Bool v9, _Bool v10, _Bool v11, _Bool v12, _Bool v13, _Bool v14, _Bool v15);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 8 element vector of 16-bit unsigned integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @param v4 Whether the element should be set (1) or not (0).
 * @param v5 Whether the element should be set (1) or not (0).
 * @param v6 Whether the element should be set (1) or not (0).
 * @param v7 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdSetSequence_u16x8(const CCSimd_u16x8 a, uint16_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 4 element vector of 32-bit unsigned integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdSetSequence_u32x4(const CCSimd_u32x4 a, uint32_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 2 element vector of 64-bit unsigned integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdSetSequence_u64x2(const CCSimd_u64x2 a, uint64_t v, _Bool v0, _Bool v1);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 4 element vector of 32-bit floats.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSetSequence_f32x4(const CCSimd_f32x4 a, float v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 2 element vector of 64-bit floats.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSetSequence_f64x2(const CCSimd_f64x2 a, double v, _Bool v0, _Bool v1);


#pragma mark - Types
#pragma mark Reinterpret

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Reinterpret_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Reinterpret_f64x2(const CCSimd_f64x2 a);


#pragma mark Cast

/*!
 * @brief Cast the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Cast_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Cast_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Cast_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Cast_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Cast_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Cast_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Cast_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Cast_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Cast_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Cast_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimd_s8x16_Cast_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimd_u8x16_Cast_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimd_s16x8_Cast_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimd_u16x8_Cast_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Cast_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Cast_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Cast_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Cast_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Cast_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Cast_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimd_s32x4_Cast_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimd_u32x4_Cast_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 4 element vector of 32-bit floats.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimd_f32x4_Cast_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimd_s64x2_Cast_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimd_u64x2_Cast_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a A 2 element vector of 64-bit floats.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimd_f64x2_Cast_f64x2(const CCSimd_f64x2 a);


#pragma mark - Bitwise Operations
#pragma mark Not

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdNot_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] -> [-2, -2, -2, -2, -2, -2, -2, -2]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdNot_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1, 1, 1] -> [-2, -2, -2, -2]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdNot_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1] -> [-2, -2]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdNot_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdNot_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] -> [-2, -2, -2, -2, -2, -2, -2, -2]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdNot_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1, 1, 1] -> [-2, -2, -2, -2]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdNot_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief NOT all elements of @b a.
 * @example ~[1, 1] -> [-2, -2]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdNot_u64x2(const CCSimd_u64x2 a);


#pragma mark And

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdAnd_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdAnd_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1] & [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdAnd_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1] & [3, 3] -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdAnd_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdAnd_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdAnd_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1] & [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdAnd_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1] & [3, 3] -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdAnd_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark And Not

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdAndNot_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdAndNot_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] & [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdAndNot_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1] & [3, 3] -> [2, 2]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdAndNot_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdAndNot_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdAndNot_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] & [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdAndNot_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1] & [3, 3] -> [2, 2]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdAndNot_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Or

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdOr_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [3, 3, 3, 3, 3, 3, 3, 3]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdOr_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] | [2, 2, 2, 2] -> [3, 3, 3, 3]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdOr_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1] | [2, 2] -> [3, 3]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdOr_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdOr_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [3, 3, 3, 3, 3, 3, 3, 3]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdOr_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] | [2, 2, 2, 2] -> [3, 3, 3, 3]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdOr_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1] | [2, 2] -> [3, 3]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdOr_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Or Not

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdOrNot_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [-2, -2, -2, -2, -2, -2, -2, -2]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdOrNot_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] | [2, 2, 2, 2] -> [-2, -2, -2, -2]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdOrNot_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1] | [2, 2] -> [-2, -2]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdOrNot_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdOrNot_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [-2, -2, -2, -2, -2, -2, -2, -2]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdOrNot_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] | [2, 2, 2, 2] -> [-2, -2, -2, -2]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdOrNot_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1] | [2, 2] -> [-2, -2]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdOrNot_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Xor

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] ^ [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdXor_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] ^ [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdXor_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] ^ [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdXor_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1] ^ [3, 3] -> [2, 2]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdXor_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] ^ [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdXor_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] ^ [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdXor_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] ^ [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdXor_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1] ^ [3, 3] -> [2, 2]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdXor_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Shift Left

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] << [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdShiftLeft_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdShiftLeft_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1] << [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdShiftLeft_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1] << [3, 3] -> [8, 8]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdShiftLeft_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] << [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdShiftLeft_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdShiftLeft_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1] << [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdShiftLeft_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1] << [3, 3] -> [8, 8]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdShiftLeft_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Shift Left N

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] << 3 -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdShiftLeftN_s8x16(const CCSimd_s8x16 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdShiftLeftN_s16x8(const CCSimd_s16x8 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1] << 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdShiftLeftN_s32x4(const CCSimd_s32x4 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1] << 3 -> [8, 8]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdShiftLeftN_s64x2(const CCSimd_s64x2 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] << 3 -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdShiftLeftN_u8x16(const CCSimd_u8x16 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdShiftLeftN_u16x8(const CCSimd_u16x8 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1] << 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdShiftLeftN_u32x4(const CCSimd_u32x4 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1] << 3 -> [8, 8]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdShiftLeftN_u64x2(const CCSimd_u64x2 a, const uint8_t n);


#pragma mark Shift Right

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] >> [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdShiftRight_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdShiftRight_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8] >> [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdShiftRight_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8] >> [3, 3] -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdShiftRight_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] >> [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdShiftRight_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdShiftRight_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8] >> [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdShiftRight_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8] >> [3, 3] -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdShiftRight_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Shift Right N

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] >> 3 -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdShiftRightN_s8x16(const CCSimd_s8x16 a, const uint8_t n);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdShiftRightN_s16x8(const CCSimd_s16x8 a, const uint8_t n);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8] >> 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdShiftRightN_s32x4(const CCSimd_s32x4 a, const uint8_t n);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8] >> 3 -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdShiftRightN_s64x2(const CCSimd_s64x2 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] >> 3 -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdShiftRightN_u8x16(const CCSimd_u8x16 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdShiftRightN_u16x8(const CCSimd_u16x8 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8] >> 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdShiftRightN_u32x4(const CCSimd_u32x4 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8] >> 3 -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdShiftRightN_u64x2(const CCSimd_u64x2 a, const uint8_t n);


#pragma mark Rotate Left

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] rol [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdRotateLeft_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] rol [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdRotateLeft_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1] rol [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdRotateLeft_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1] rol [3, 3] -> [8, 8]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdRotateLeft_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] rol [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdRotateLeft_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] rol [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdRotateLeft_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1] rol [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdRotateLeft_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1] rol [3, 3] -> [8, 8]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdRotateLeft_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Rotate Left N

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] rol 3 -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdRotateLeftN_s8x16(const CCSimd_s8x16 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] rol 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdRotateLeftN_s16x8(const CCSimd_s16x8 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1] rol 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdRotateLeftN_s32x4(const CCSimd_s32x4 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1] rol 3 -> [8, 8]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdRotateLeftN_s64x2(const CCSimd_s64x2 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] rol 3 -> [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdRotateLeftN_u8x16(const CCSimd_u8x16 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] rol 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdRotateLeftN_u16x8(const CCSimd_u16x8 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1] rol 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdRotateLeftN_u32x4(const CCSimd_u32x4 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1] rol 3 -> [8, 8]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdRotateLeftN_u64x2(const CCSimd_u64x2 a, const uint8_t n);


#pragma mark Rotate Right

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] ror [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdRotateRight_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] ror [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdRotateRight_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8] ror [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdRotateRight_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8] ror [3, 3] -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdRotateRight_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] ror [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdRotateRight_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] ror [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdRotateRight_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8] ror [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdRotateRight_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8] ror [3, 3] -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdRotateRight_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);


#pragma mark Rotate Right N

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] ror 3 -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdRotateRightN_s8x16(const CCSimd_s8x16 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] ror 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdRotateRightN_s16x8(const CCSimd_s16x8 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8] ror 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdRotateRightN_s32x4(const CCSimd_s32x4 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8] ror 3 -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdRotateRightN_s64x2(const CCSimd_s64x2 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8] ror 3 -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdRotateRightN_u8x16(const CCSimd_u8x16 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] ror 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdRotateRightN_u16x8(const CCSimd_u16x8 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8] ror 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdRotateRightN_u32x4(const CCSimd_u32x4 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8] ror 3 -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdRotateRightN_u64x2(const CCSimd_u64x2 a, const uint8_t n);


#pragma mark - Bit Maths
#pragma mark Lowest Unset Bits

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdLowestUnset_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdLowestUnset_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdLowestUnset_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2] -> [2, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdLowestUnset_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdLowestUnset_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdLowestUnset_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdLowestUnset_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2] -> [2, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdLowestUnset_u64x2(const CCSimd_u64x2 a);


#pragma mark Lowest Set Bits

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6, 5, 6, 5, 6, 5, 6, 5, 6, 5, 6, 5, 6, 5, 6] -> [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdLowestSet_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6, 5, 6, 5, 6, 5, 6] -> [1, 2, 1, 2, 1, 2, 1, 2]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdLowestSet_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6, 5, 6] -> [1, 2, 1, 2]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdLowestSet_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6] -> [1, 2]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdLowestSet_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6, 5, 6, 5, 6, 5, 6, 5, 6, 5, 6, 5, 6, 5, 6] -> [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdLowestSet_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6, 5, 6, 5, 6, 5, 6] -> [1, 2, 1, 2, 1, 2, 1, 2]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdLowestSet_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6, 5, 6] -> [1, 2, 1, 2]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdLowestSet_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [5, 6] -> [1, 2]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdLowestSet_u64x2(const CCSimd_u64x2 a);


#pragma mark Highest Set Bits

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1] -> [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdHighestSet_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdHighestSet_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdHighestSet_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1] -> [2, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdHighestSet_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1] -> [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdHighestSet_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdHighestSet_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdHighestSet_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1] -> [2, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdHighestSet_u64x2(const CCSimd_u64x2 a);


#pragma mark Next Power of 2

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1] -> [4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdNextPow2_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1] -> [4, 1, 4, 1, 4, 1, 4, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdNextPow2_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1] -> [4, 1, 4, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdNextPow2_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1] -> [4, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdNextPow2_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1] -> [4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdNextPow2_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1, 3, 1, 3, 1] -> [4, 1, 4, 1, 4, 1, 4, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdNextPow2_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1] -> [4, 1, 4, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdNextPow2_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1] -> [4, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdNextPow2_u64x2(const CCSimd_u64x2 a);


#pragma mark Mask Value

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1] -> [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMask_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1, 2, 1, 2, 1] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMask_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMask_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1] -> [3, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMask_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1] -> [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMask_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1, 2, 1, 2, 1] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMask_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMask_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1] -> [3, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMask_u64x2(const CCSimd_u64x2 a);


#pragma mark Mask Lower Power of 2

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2] -> [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskLowerPow2_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2, 4, 2, 4, 2] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskLowerPow2_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskLowerPow2_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2] -> [3, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskLowerPow2_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2] -> [3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskLowerPow2_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2, 4, 2, 4, 2] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskLowerPow2_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskLowerPow2_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2] -> [3, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskLowerPow2_u64x2(const CCSimd_u64x2 a);


#pragma mark Mask Highest Unset Value

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2] -> [-2, -4, -2, -4, -2, -4, -2, -4, -2, -4, -2, -4, -2, -4, -2, -4]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskHighestUnset_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2, 1, 2, 1, 2] -> [-2, -4, -2, -4, -2, -4, -2, -4]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskHighestUnset_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2] -> [-2, -4, -2, -4]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskHighestUnset_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2] -> [-2, -4]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskHighestUnset_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2] -> [-2, -4, -2, -4, -2, -4, -2, -4, -2, -4, -2, -4, -2, -4, -2, -4]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskHighestUnset_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2, 1, 2, 1, 2] -> [-2, -4, -2, -4, -2, -4, -2, -4]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskHighestUnset_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2] -> [-2, -4, -2, -4]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskHighestUnset_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2] -> [-2, -4]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskHighestUnset_u64x2(const CCSimd_u64x2 a);


#pragma mark Count Trailing Zero Bits

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCountLowestUnset_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [0, 1, 0, 2, 0, 1, 0, 3]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCountLowestUnset_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [0, 1, 0, 2]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCountLowestUnset_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCountLowestUnset_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 4]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCountLowestUnset_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [0, 1, 0, 2, 0, 1, 0, 3]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCountLowestUnset_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [0, 1, 0, 2]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCountLowestUnset_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCountLowestUnset_u64x2(const CCSimd_u64x2 a);


#pragma mark Count Leading Zero Bits

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCountHighestUnset_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [15, 14, 14, 13, 13, 13, 13, 12]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCountHighestUnset_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [31, 30, 30, 29]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCountHighestUnset_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2] -> [63, 62]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCountHighestUnset_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 3]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCountHighestUnset_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [15, 14, 14, 13, 13, 13, 13, 12]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCountHighestUnset_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [31, 30, 30, 29]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCountHighestUnset_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2] -> [63, 62]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCountHighestUnset_u64x2(const CCSimd_u64x2 a);


#pragma mark Count Set Bits

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2] -> [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1]
 * @param a A 16 element vector of 8-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCountSet_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2, 3, 2, 3, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 16-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCountSet_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 32-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCountSet_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2] -> [2, 1]
 * @param a A 2 element vector of 64-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCountSet_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2] -> [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCountSet_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2, 3, 2, 3, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCountSet_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCountSet_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2] -> [2, 1]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCountSet_u64x2(const CCSimd_u64x2 a);


#pragma mark - Comparisons
#pragma mark Equal

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] == [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCompareEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, 1, 0, 1, 0, 1, 0, 1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCompareEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4] == [0, 2, 0, 4] -> [0, 1, 0, 1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCompareEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2] == [0, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCompareEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] == [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCompareEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, 1, 0, 1, 0, 1, 0, 1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCompareEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4] == [0, 2, 0, 4] -> [0, 1, 0, 1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCompareEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2] == [0, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCompareEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1.5, 2.5, 3.5, 4.5] == [0, 2.5, 0, 4.5] -> [0, 1, 0, 1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCompareEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1.5, 2.5] == [0, 2.5] -> [0, 1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCompareEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Masked Equal

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] == [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskCompareEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, -1, 0, -1, 0, -1, 0, -1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskCompareEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4] == [0, 2, 0, 4] -> [0, -1, 0, -1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskCompareEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2] == [0, 2] -> [0, -1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskCompareEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] == [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskCompareEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, -1, 0, -1, 0, -1, 0, -1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskCompareEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4] == [0, 2, 0, 4] -> [0, -1, 0, -1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2] == [0, 2] -> [0, -1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1.5, 2.5, 3.5, 4.5] == [0, 2.5, 0, 4.5] -> [0, -1, 0, -1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1.5, 2.5] == [0, 2.5] -> [0, -1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Not Equal

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] != [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCompareNotEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCompareNotEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4] != [0, 2, 0, 4] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCompareNotEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2] != [0, 2] -> [1, 0]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCompareNotEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] != [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCompareNotEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCompareNotEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4] != [0, 2, 0, 4] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCompareNotEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2] != [0, 2] -> [1, 0]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCompareNotEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1.5, 2.5, 3.5, 4.5] != [0, 2.5, 0, 4.5] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCompareNotEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1.5, 2.5] != [0, 2.5] -> [1, 0]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCompareNotEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Masked Not Equal

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] != [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [-1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskCompareNotEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [-1, 0, -1, 0, -1, 0, -1, 0]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskCompareNotEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4] != [0, 2, 0, 4] -> [-1, 0, -1, 0]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskCompareNotEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2] != [0, 2] -> [-1, 0]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskCompareNotEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] != [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [-1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskCompareNotEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [-1, 0, -1, 0, -1, 0, -1, 0]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskCompareNotEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4] != [0, 2, 0, 4] -> [-1, 0, -1, 0]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareNotEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2] != [0, 2] -> [-1, 0]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareNotEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1.5, 2.5, 3.5, 4.5] != [0, 2.5, 0, 4.5] -> [-1, 0, -1, 0]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareNotEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1.5, 2.5] != [0, 2.5] -> [-1, 0]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareNotEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Less Than

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] < [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCompareLessThan_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] < [0, 2, 4, 6, 8, 10, 12, 14] -> [0, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCompareLessThan_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3] < [0, 2, 4, 6] -> [0, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCompareLessThan_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1] < [0, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCompareLessThan_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] < [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCompareLessThan_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] < [0, 2, 4, 6, 8, 10, 12, 14] -> [0, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCompareLessThan_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3] < [0, 2, 4, 6] -> [0, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCompareLessThan_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1] < [0, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCompareLessThan_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0.5, 1.5, 2.5, 3.5] < [0.5, 2.5, 4.5, 6.5] -> [0, 1, 1, 1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCompareLessThan_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0.5, 1.5] < [0.5, 2.5] -> [0, 1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCompareLessThan_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Masked Less Than

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] < [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskCompareLessThan_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] < [0, 2, 4, 6, 8, 10, 12, 14] -> [0, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskCompareLessThan_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3] < [0, 2, 4, 6] -> [0, -1, -1, -1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskCompareLessThan_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1] < [0, 2] -> [0, -1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskCompareLessThan_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] < [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskCompareLessThan_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] < [0, 2, 4, 6, 8, 10, 12, 14] -> [0, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskCompareLessThan_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1, 2, 3] < [0, 2, 4, 6] -> [0, -1, -1, -1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareLessThan_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0, 1] < [0, 2] -> [0, -1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareLessThan_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0.5, 1.5, 2.5, 3.5] < [0.5, 2.5, 4.5, 6.5] -> [0, -1, -1, -1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareLessThan_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [0.5, 1.5] < [0.5, 2.5] -> [0, -1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareLessThan_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Less Than Or Equal

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] <= [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCompareLessThanEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] <= [0, 2, 4, 6, 8, 10, 12, 14] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCompareLessThanEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3] <= [0, 2, 4, 6] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCompareLessThanEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1] <= [0, 2] -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCompareLessThanEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] <= [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCompareLessThanEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] <= [0, 2, 4, 6, 8, 10, 12, 14] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCompareLessThanEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3] <= [0, 2, 4, 6] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCompareLessThanEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1] <= [0, 2] -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCompareLessThanEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0.5, 1.5, 2.5, 3.5] <= [0.5, 2.5, 4.5, 6.5] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCompareLessThanEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0.5, 1.5] <= [0.5, 2.5] -> [1, 1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCompareLessThanEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Masked Less Than Or Equal

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] <= [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskCompareLessThanEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] <= [0, 2, 4, 6, 8, 10, 12, 14] -> [-1, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskCompareLessThanEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3] <= [0, 2, 4, 6] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskCompareLessThanEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1] <= [0, 2] -> [-1, -1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskCompareLessThanEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] <= [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30] -> [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskCompareLessThanEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3, 4, 5, 6, 7] <= [0, 2, 4, 6, 8, 10, 12, 14] -> [-1, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskCompareLessThanEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1, 2, 3] <= [0, 2, 4, 6] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareLessThanEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0, 1] <= [0, 2] -> [-1, -1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareLessThanEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0.5, 1.5, 2.5, 3.5] <= [0.5, 2.5, 4.5, 6.5] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareLessThanEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [0.5, 1.5] <= [0.5, 2.5] -> [-1, -1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareLessThanEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Greater Than

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] > [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCompareGreaterThan_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCompareGreaterThan_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4] > [0, 2, 0, 4] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCompareGreaterThan_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2] > [0, 2] -> [1, 0]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCompareGreaterThan_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] > [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCompareGreaterThan_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCompareGreaterThan_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4] > [0, 2, 0, 4] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCompareGreaterThan_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2] > [0, 2] -> [1, 0]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCompareGreaterThan_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1.5, 2.5, 3.5, 4.5] > [0, 2.5, 0, 4.5] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCompareGreaterThan_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1.5, 2.5] > [0, 2.5] -> [1, 0]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCompareGreaterThan_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Masked Greater Than

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] > [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [-1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskCompareGreaterThan_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [-1, 0, -1, 0, -1, 0, -1, 0]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskCompareGreaterThan_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4] > [0, 2, 0, 4] -> [-1, 0, -1, 0]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskCompareGreaterThan_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2] > [0, 2] -> [-1, 0]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskCompareGreaterThan_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] > [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [-1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskCompareGreaterThan_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [-1, 0, -1, 0, -1, 0, -1, 0]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskCompareGreaterThan_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4] > [0, 2, 0, 4] -> [-1, 0, -1, 0]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareGreaterThan_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2] > [0, 2] -> [-1, 0]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareGreaterThan_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1.5, 2.5, 3.5, 4.5] > [0, 2.5, 0, 4.5] -> [-1, 0, -1, 0]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareGreaterThan_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1.5, 2.5] > [0, 2.5] -> [-1, 0]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareGreaterThan_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Greater Than Or Equal

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] >= [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdCompareGreaterThanEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdCompareGreaterThanEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4] >= [0, 2, 0, 4] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdCompareGreaterThanEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2] >= [0, 2] -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdCompareGreaterThanEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] >= [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdCompareGreaterThanEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdCompareGreaterThanEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4] >= [0, 2, 0, 4] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdCompareGreaterThanEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2] >= [0, 2] -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdCompareGreaterThanEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1.5, 2.5, 3.5, 4.5] >= [0, 2.5, 0, 4.5] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCompareGreaterThanEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1.5, 2.5] >= [0, 2.5] -> [1, 1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCompareGreaterThanEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Masked Greater Than Or Equal

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] >= [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
 * @param a A 16 element vector of 8-bit signed integers to compare.
 * @param b A 16 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMaskCompareGreaterThanEqual_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [-1, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 16-bit signed integers to compare.
 * @param b An 8 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMaskCompareGreaterThanEqual_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4] >= [0, 2, 0, 4] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 32-bit signed integers to compare.
 * @param b A 4 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMaskCompareGreaterThanEqual_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2] >= [0, 2] -> [-1, -1]
 * @param a A 2 element vector of 64-bit signed integers to compare.
 * @param b A 2 element vector of 64-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMaskCompareGreaterThanEqual_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] >= [0, 2, 0, 4, 0, 6, 0, 8, 0, 10, 0, 12, 0, 14, 0, 16] -> [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
 * @param a A 16 element vector of 8-bit unsigned integers to compare.
 * @param b A 16 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMaskCompareGreaterThanEqual_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [-1, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 16-bit unsigned integers to compare.
 * @param b An 8 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMaskCompareGreaterThanEqual_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4] >= [0, 2, 0, 4] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 32-bit unsigned integers to compare.
 * @param b A 4 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareGreaterThanEqual_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2] >= [0, 2] -> [-1, -1]
 * @param a A 2 element vector of 64-bit unsigned integers to compare.
 * @param b A 2 element vector of 64-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareGreaterThanEqual_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1.5, 2.5, 3.5, 4.5] >= [0, 2.5, 0, 4.5] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 32-bit floats to compare.
 * @param b A 4 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMaskCompareGreaterThanEqual_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1.5, 2.5] >= [0, 2.5] -> [-1, -1]
 * @param a A 2 element vector of 64-bit floats to compare.
 * @param b A 2 element vector of 64-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMaskCompareGreaterThanEqual_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark - Maths
#pragma mark Add

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] + [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8] -> [1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24]
 * @param a A 16 element vector of 8-bit signed integers as the addend.
 * @param b A 16 element vector of 8-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdAdd_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] + [0, 1, 1, 2, 2, 3, 3, 4] -> [1, 3, 4, 6, 7, 9, 10, 12]
 * @param a An 8 element vector of 16-bit signed integers as the addend.
 * @param b An 8 element vector of 16-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdAdd_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4] + [0, 1, 1, 2] -> [1, 3, 4, 6]
 * @param a A 4 element vector of 32-bit signed integers as the addend.
 * @param b A 4 element vector of 32-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdAdd_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2] + [0, 1] -> [1, 3]
 * @param a A 2 element vector of 64-bit signed integers as the addend.
 * @param b A 2 element vector of 64-bit signed integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdAdd_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] + [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8] -> [1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24]
 * @param a A 16 element vector of 8-bit unsigned integers as the addend.
 * @param b A 16 element vector of 8-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdAdd_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] + [0, 1, 1, 2, 2, 3, 3, 4] -> [1, 3, 4, 6, 7, 9, 10, 12]
 * @param a An 8 element vector of 16-bit unsigned integers as the addend.
 * @param b An 8 element vector of 16-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdAdd_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2, 3, 4] + [0, 1, 1, 2] -> [1, 3, 4, 6]
 * @param a A 4 element vector of 32-bit unsigned integers as the addend.
 * @param b A 4 element vector of 32-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdAdd_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1, 2] + [0, 1] -> [1, 3]
 * @param a A 2 element vector of 64-bit unsigned integers as the addend.
 * @param b A 2 element vector of 64-bit unsigned integers as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdAdd_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1.5, 2.5, 3.5, 4.5] + [0.0, 1.0, 1.0, 2.0] -> [1.5, 3.5, 4.5, 6.5]
 * @param a A 4 element vector of 32-bit floats as the addend.
 * @param b A 4 element vector of 32-bit floats as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdAdd_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Add all elements of @b a and @b b.
 * @example [1.5, 2.5] + [0.0, 1.0] -> [1.5, 3.5]
 * @param a A 2 element vector of 64-bit floats as the addend.
 * @param b A 2 element vector of 64-bit floats as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdAdd_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Subtract

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] - [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8] -> [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8]
 * @param a A 16 element vector of 8-bit signed integers as the minuend.
 * @param b A 16 element vector of 8-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdSub_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] - [0, 1, 1, 2, 2, 3, 3, 4] -> [1, 1, 2, 2, 3, 3, 4, 4]
 * @param a An 8 element vector of 16-bit signed integers as the minuend.
 * @param b An 8 element vector of 16-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdSub_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4] - [0, 1, 1, 2] -> [1, 1, 2, 2]
 * @param a A 4 element vector of 32-bit signed integers as the minuend.
 * @param b A 4 element vector of 32-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdSub_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2] - [0, 1] -> [1, 1]
 * @param a A 2 element vector of 64-bit signed integers as the minuend.
 * @param b A 2 element vector of 64-bit signed integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdSub_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] - [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8] -> [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8]
 * @param a A 16 element vector of 8-bit unsigned integers as the minuend.
 * @param b A 16 element vector of 8-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdSub_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] - [0, 1, 1, 2, 2, 3, 3, 4] -> [1, 1, 2, 2, 3, 3, 4, 4]
 * @param a An 8 element vector of 16-bit unsigned integers as the minuend.
 * @param b An 8 element vector of 16-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdSub_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2, 3, 4] - [0, 1, 1, 2] -> [1, 1, 2, 2]
 * @param a A 4 element vector of 32-bit unsigned integers as the minuend.
 * @param b A 4 element vector of 32-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdSub_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1, 2] - [0, 1] -> [1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers as the minuend.
 * @param b A 2 element vector of 64-bit unsigned integers as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdSub_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1.5, 2.5, 3.5, 4.5] - [0.0, 1.0, 1.0, 2.0] -> [1.5, 1.5, 2.5, 2.5]
 * @param a A 4 element vector of 32-bit floats as the minuend.
 * @param b A 4 element vector of 32-bit floats as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSub_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Subtract all elements of @b b from @b a.
 * @example [1.5, 2.5] - [0.0, 1.0] -> [1.5, 1.5]
 * @param a A 2 element vector of 64-bit floats as the minuend.
 * @param b A 2 element vector of 64-bit floats as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSub_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Multiply

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] * [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] -> [0, 2, 6, 12, 20, 30, 42, 56, 72, 90, 110, 132, 156, 182, 210, 240]
 * @param a A 16 element vector of 8-bit signed integers as the multiplier.
 * @param b A 16 element vector of 8-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMul_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] * [0, 1, 2, 3, 4, 5, 6, 7] -> [0, 2, 6, 12, 20, 30, 42, 56]
 * @param a An 8 element vector of 16-bit signed integers as the multiplier.
 * @param b An 8 element vector of 16-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMul_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4] * [0, 1, 2, 3] -> [0, 2, 6, 12]
 * @param a A 4 element vector of 32-bit signed integers as the multiplier.
 * @param b A 4 element vector of 32-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMul_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2] * [0, 1] -> [0, 2]
 * @param a A 2 element vector of 64-bit signed integers as the multiplier.
 * @param b A 2 element vector of 64-bit signed integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMul_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] * [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] -> [0, 2, 6, 12, 20, 30, 42, 56, 72, 90, 110, 132, 156, 182, 210, 240]
 * @param a A 16 element vector of 8-bit unsigned integers as the multiplier.
 * @param b A 16 element vector of 8-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMul_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] * [0, 1, 2, 3, 4, 5, 6, 7] -> [0, 2, 6, 12, 20, 30, 42, 56]
 * @param a An 8 element vector of 16-bit unsigned integers as the multiplier.
 * @param b An 8 element vector of 16-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMul_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2, 3, 4] * [0, 1, 2, 3] -> [0, 2, 6, 12]
 * @param a A 4 element vector of 32-bit unsigned integers as the multiplier.
 * @param b A 4 element vector of 32-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMul_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1, 2] * [0, 1] -> [0, 2]
 * @param a A 2 element vector of 64-bit unsigned integers as the multiplier.
 * @param b A 2 element vector of 64-bit unsigned integers as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMul_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1.5, 2.5, 3.5, 4.5] * [0.0, 1.0, 2.0, 3.0] -> [0.0, 2.5, 7.0, 13.5]
 * @param a A 4 element vector of 32-bit floats as the multiplier.
 * @param b A 4 element vector of 32-bit floats as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMul_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Multiply all elements of @b a by @b b.
 * @example [1.5, 2.5] * [0.0, 1.0] -> [0.0, 2.5]
 * @param a A 2 element vector of 64-bit floats as the multiplier.
 * @param b A 2 element vector of 64-bit floats as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMul_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Multiply and Add

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31]
 * @param a A 16 element vector of 8-bit signed integers to multiply.
 * @param b A 16 element vector of 8-bit signed integers to multiply.
 * @param c A 16 element vector of 8-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMadd_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, const CCSimd_s8x16 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 3, 5, 7, 9, 11, 13, 15]
 * @param a An 8 element vector of 16-bit signed integers to multiply.
 * @param b An 8 element vector of 16-bit signed integers to multiply.
 * @param c An 8 element vector of 16-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMadd_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, const CCSimd_s16x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1, 2, 3] * [2, 2, 2, 2]) + [1, 1, 1, 1] -> [1, 3, 5, 7]
 * @param a A 4 element vector of 32-bit signed integers to multiply.
 * @param b A 4 element vector of 32-bit signed integers to multiply.
 * @param c A 4 element vector of 32-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMadd_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, const CCSimd_s32x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1] * [2, 2]) + [1, 1] -> [1, 3]
 * @param a A 2 element vector of 64-bit signed integers to multiply.
 * @param b A 2 element vector of 64-bit signed integers to multiply.
 * @param c A 2 element vector of 64-bit signed integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMadd_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, const CCSimd_s64x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31]
 * @param a A 16 element vector of 8-bit unsigned integers to multiply.
 * @param b A 16 element vector of 8-bit unsigned integers to multiply.
 * @param c A 16 element vector of 8-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMadd_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, const CCSimd_u8x16 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, 3, 5, 7, 9, 11, 13, 15]
 * @param a An 8 element vector of 16-bit unsigned integers to multiply.
 * @param b An 8 element vector of 16-bit unsigned integers to multiply.
 * @param c An 8 element vector of 16-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMadd_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, const CCSimd_u16x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1, 2, 3] * [2, 2, 2, 2]) + [1, 1, 1, 1] -> [1, 3, 5, 7]
 * @param a A 4 element vector of 32-bit unsigned integers to multiply.
 * @param b A 4 element vector of 32-bit unsigned integers to multiply.
 * @param c A 4 element vector of 32-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMadd_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, const CCSimd_u32x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0, 1] * [2, 2]) + [1, 1] -> [1, 3]
 * @param a A 2 element vector of 64-bit unsigned integers to multiply.
 * @param b A 2 element vector of 64-bit unsigned integers to multiply.
 * @param c A 2 element vector of 64-bit unsigned integers to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMadd_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, const CCSimd_u64x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0.5, 1.5, 2.5, 3.5] * [2.0, 2.0, 2.0, 2.0]) + [1.0, 1.0, 1.0, 1.0] -> [2.0, 4.0, 6.0, 8.0]
 * @param a A 4 element vector of 32-bit floats to multiply.
 * @param b A 4 element vector of 32-bit floats to multiply.
 * @param c A 4 element vector of 32-bit floats to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMadd_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, const CCSimd_f32x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 * @example ([0.5, 1.5] * [2.0, 2.0]) + [1.0, 1.0] -> [2.0, 4.0]
 * @param a A 2 element vector of 64-bit floats to multiply.
 * @param b A 2 element vector of 64-bit floats to multiply.
 * @param c A 2 element vector of 64-bit floats to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMadd_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, const CCSimd_f64x2 c);


#pragma mark Negated Multiply and Add

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [1, -1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29]
 * @param a A 16 element vector of 8-bit signed integers to multiply.
 * @param b A 16 element vector of 8-bit signed integers to multiply.
 * @param c A 16 element vector of 8-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdNegMadd_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, const CCSimd_s8x16 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, -1, -3, -5, -7, -9, -11, -13]
 * @param a An 8 element vector of 16-bit signed integers to multiply.
 * @param b An 8 element vector of 16-bit signed integers to multiply.
 * @param c An 8 element vector of 16-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdNegMadd_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, const CCSimd_s16x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1, 2, 3] * [2, 2, 2, 2]) + [1, 1, 1, 1] -> [1, -1, -3, -5]
 * @param a A 4 element vector of 32-bit signed integers to multiply.
 * @param b A 4 element vector of 32-bit signed integers to multiply.
 * @param c A 4 element vector of 32-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdNegMadd_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, const CCSimd_s32x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1] * [2, 2]) + [1, 1] -> [1, -1]
 * @param a A 2 element vector of 64-bit signed integers to multiply.
 * @param b A 2 element vector of 64-bit signed integers to multiply.
 * @param c A 2 element vector of 64-bit signed integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdNegMadd_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, const CCSimd_s64x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [1, -1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29]
 * @param a A 16 element vector of 8-bit unsigned integers to multiply.
 * @param b A 16 element vector of 8-bit unsigned integers to multiply.
 * @param c A 16 element vector of 8-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdNegMadd_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, const CCSimd_u8x16 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) + [1, 1, 1, 1, 1, 1, 1, 1] -> [1, -1, -3, -5, -7, -9, -11, -13]
 * @param a An 8 element vector of 16-bit unsigned integers to multiply.
 * @param b An 8 element vector of 16-bit unsigned integers to multiply.
 * @param c An 8 element vector of 16-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdNegMadd_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, const CCSimd_u16x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1, 2, 3] * [2, 2, 2, 2]) + [1, 1, 1, 1] -> [1, -1, -3, -5]
 * @param a A 4 element vector of 32-bit unsigned integers to multiply.
 * @param b A 4 element vector of 32-bit unsigned integers to multiply.
 * @param c A 4 element vector of 32-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdNegMadd_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, const CCSimd_u32x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0, 1] * [2, 2]) + [1, 1] -> [1, -1]
 * @param a A 2 element vector of 64-bit unsigned integers to multiply.
 * @param b A 2 element vector of 64-bit unsigned integers to multiply.
 * @param c A 2 element vector of 64-bit unsigned integers to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdNegMadd_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, const CCSimd_u64x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0.5, 1.5, 2.5, 3.5] * [2.0, 2.0, 2.0, 2.0]) + [1.0, 1.0, 1.0, 1.0] -> [0.0, -2.0, -4.0, -6.0]
 * @param a A 4 element vector of 32-bit floats to multiply.
 * @param b A 4 element vector of 32-bit floats to multiply.
 * @param c A 4 element vector of 32-bit floats to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdNegMadd_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, const CCSimd_f32x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 * @example -([0.5, 1.5] * [2.0, 2.0]) + [1.0, 1.0] -> [0.0, -2.0]
 * @param a A 2 element vector of 64-bit floats to multiply.
 * @param b A 2 element vector of 64-bit floats to multiply.
 * @param c A 2 element vector of 64-bit floats to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdNegMadd_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, const CCSimd_f64x2 c);


#pragma mark Multiply and Sub

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [-1, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29]
 * @param a A 16 element vector of 8-bit signed integers to multiply.
 * @param b A 16 element vector of 8-bit signed integers to multiply.
 * @param c A 16 element vector of 8-bit signed integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMsub_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, const CCSimd_s8x16 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [-1, 1, 3, 5, 7, 9, 11, 13]
 * @param a An 8 element vector of 16-bit signed integers to multiply.
 * @param b An 8 element vector of 16-bit signed integers to multiply.
 * @param c An 8 element vector of 16-bit signed integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMsub_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, const CCSimd_s16x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1, 2, 3] * [2, 2, 2, 2]) - [1, 1, 1, 1] -> [-1, 1, 3, 5]
 * @param a A 4 element vector of 32-bit signed integers to multiply.
 * @param b A 4 element vector of 32-bit signed integers to multiply.
 * @param c A 4 element vector of 32-bit signed integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMsub_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, const CCSimd_s32x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1] * [2, 2]) - [1, 1] -> [-1, 1]
 * @param a A 2 element vector of 64-bit signed integers to multiply.
 * @param b A 2 element vector of 64-bit signed integers to multiply.
 * @param c A 2 element vector of 64-bit signed integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMsub_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, const CCSimd_s64x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [-1, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29]
 * @param a A 16 element vector of 8-bit unsigned integers to multiply.
 * @param b A 16 element vector of 8-bit unsigned integers to multiply.
 * @param c A 16 element vector of 8-bit unsigned integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMsub_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, const CCSimd_u8x16 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [-1, 1, 3, 5, 7, 9, 11, 13]
 * @param a An 8 element vector of 16-bit unsigned integers to multiply.
 * @param b An 8 element vector of 16-bit unsigned integers to multiply.
 * @param c An 8 element vector of 16-bit unsigned integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMsub_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, const CCSimd_u16x8 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1, 2, 3] * [2, 2, 2, 2]) - [1, 1, 1, 1] -> [-1, 1, 3, 5]
 * @param a A 4 element vector of 32-bit unsigned integers to multiply.
 * @param b A 4 element vector of 32-bit unsigned integers to multiply.
 * @param c A 4 element vector of 32-bit unsigned integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMsub_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, const CCSimd_u32x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0, 1] * [2, 2]) - [1, 1] -> [-1, 1]
 * @param a A 2 element vector of 64-bit unsigned integers to multiply.
 * @param b A 2 element vector of 64-bit unsigned integers to multiply.
 * @param c A 2 element vector of 64-bit unsigned integers to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMsub_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, const CCSimd_u64x2 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0.5, 1.5, 2.5, 3.5] * [2.0, 2.0, 2.0, 2.0]) - [1.0, 1.0, 1.0, 1.0] -> [0.0, 2.0, 4.0, 6.0]
 * @param a A 4 element vector of 32-bit floats to multiply.
 * @param b A 4 element vector of 32-bit floats to multiply.
 * @param c A 4 element vector of 32-bit floats to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMsub_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, const CCSimd_f32x4 c);

/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 * @example ([0.5, 1.5] * [2.0, 2.0]) - [1.0, 1.0] -> [0.0, 2.0]
 * @param a A 2 element vector of 64-bit floats to multiply.
 * @param b A 2 element vector of 64-bit floats to multiply.
 * @param c A 2 element vector of 64-bit floats to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMsub_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, const CCSimd_f64x2 c);


#pragma mark Negated Multiply and Sub

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [-1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29, -31]
 * @param a A 16 element vector of 8-bit signed integers to multiply.
 * @param b A 16 element vector of 8-bit signed integers to multiply.
 * @param c A 16 element vector of 8-bit signed integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdNegMsub_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, const CCSimd_s8x16 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [-1, -3, -5, -7, -9, -11, -13, -15]
 * @param a An 8 element vector of 16-bit signed integers to multiply.
 * @param b An 8 element vector of 16-bit signed integers to multiply.
 * @param c An 8 element vector of 16-bit signed integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdNegMsub_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, const CCSimd_s16x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1, 2, 3] * [2, 2, 2, 2]) - [1, 1, 1, 1] -> [-1, -3, -5, -7]
 * @param a A 4 element vector of 32-bit signed integers to multiply.
 * @param b A 4 element vector of 32-bit signed integers to multiply.
 * @param c A 4 element vector of 32-bit signed integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdNegMsub_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, const CCSimd_s32x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1] * [2, 2]) - [1, 1] -> [-1, -3]
 * @param a A 2 element vector of 64-bit signed integers to multiply.
 * @param b A 2 element vector of 64-bit signed integers to multiply.
 * @param c A 2 element vector of 64-bit signed integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdNegMsub_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, const CCSimd_s64x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15] * [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1] -> [-1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29, -31]
 * @param a A 16 element vector of 8-bit unsigned integers to multiply.
 * @param b A 16 element vector of 8-bit unsigned integers to multiply.
 * @param c A 16 element vector of 8-bit unsigned integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdNegMsub_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, const CCSimd_u8x16 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1, 2, 3, 4, 5, 6, 7] * [2, 2, 2, 2, 2, 2, 2, 2]) - [1, 1, 1, 1, 1, 1, 1, 1] -> [-1, -3, -5, -7, -9, -11, -13, -15]
 * @param a An 8 element vector of 16-bit unsigned integers to multiply.
 * @param b An 8 element vector of 16-bit unsigned integers to multiply.
 * @param c An 8 element vector of 16-bit unsigned integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdNegMsub_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, const CCSimd_u16x8 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1, 2, 3] * [2, 2, 2, 2]) - [1, 1, 1, 1] -> [-1, -3, -5, -7]
 * @param a A 4 element vector of 32-bit unsigned integers to multiply.
 * @param b A 4 element vector of 32-bit unsigned integers to multiply.
 * @param c A 4 element vector of 32-bit unsigned integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdNegMsub_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, const CCSimd_u32x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0, 1] * [2, 2]) - [1, 1] -> [-1, -3]
 * @param a A 2 element vector of 64-bit unsigned integers to multiply.
 * @param b A 2 element vector of 64-bit unsigned integers to multiply.
 * @param c A 2 element vector of 64-bit unsigned integers to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdNegMsub_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, const CCSimd_u64x2 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0.5, 1.5, 2.5, 3.5] * [2.0, 2.0, 2.0, 2.0]) - [1.0, 1.0, 1.0, 1.0] -> [-2.0, -4.0, -6.0, -8.0]
 * @param a A 4 element vector of 32-bit floats to multiply.
 * @param b A 4 element vector of 32-bit floats to multiply.
 * @param c A 4 element vector of 32-bit floats to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdNegMsub_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, const CCSimd_f32x4 c);

/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 * @example -([0.5, 1.5] * [2.0, 2.0]) - [1.0, 1.0] -> [-2.0, -4.0]
 * @param a A 2 element vector of 64-bit floats to multiply.
 * @param b A 2 element vector of 64-bit floats to multiply.
 * @param c A 2 element vector of 64-bit floats to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdNegMsub_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, const CCSimd_f64x2 c);


#pragma mark Divide

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] / [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8]
 * @param a A 16 element vector of 8-bit signed integers as the dividend.
 * @param b A 16 element vector of 8-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdDiv_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] / [2, 2, 2, 2, 2, 2, 2, 2] -> [0, 1, 1, 2, 2, 3, 3, 4]
 * @param a An 8 element vector of 16-bit signed integers as the dividend.
 * @param b An 8 element vector of 16-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdDiv_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4] / [2, 2, 2, 2] -> [0, 1, 1, 2]
 * @param a A 4 element vector of 32-bit signed integers as the dividend.
 * @param b A 4 element vector of 32-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdDiv_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2] / [2, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit signed integers as the dividend.
 * @param b A 2 element vector of 64-bit signed integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdDiv_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] / [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8]
 * @param a A 16 element vector of 8-bit unsigned integers as the dividend.
 * @param b A 16 element vector of 8-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdDiv_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] / [2, 2, 2, 2, 2, 2, 2, 2] -> [0, 1, 1, 2, 2, 3, 3, 4]
 * @param a An 8 element vector of 16-bit unsigned integers as the dividend.
 * @param b An 8 element vector of 16-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdDiv_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2, 3, 4] / [2, 2, 2, 2] -> [0, 1, 1, 2]
 * @param a A 4 element vector of 32-bit unsigned integers as the dividend.
 * @param b A 4 element vector of 32-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdDiv_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1, 2] / [2, 2] -> [0, 1]
 * @param a A 2 element vector of 64-bit unsigned integers as the dividend.
 * @param b A 2 element vector of 64-bit unsigned integers as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdDiv_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1.5, 2.5, 3.5, 4.5] / [2.0, 2.0, 2.0, 2.0] -> [0.75, 1.25, 1.75, 2.25]
 * @param a A 4 element vector of 32-bit floats as the dividend.
 * @param b A 4 element vector of 32-bit floats as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdDiv_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Divide all elements of @b a by @b b.
 * @example [1.5, 2.5] / [2.0, 2.0] -> [0.75, 1.25]
 * @param a A 2 element vector of 64-bit floats as the dividend.
 * @param b A 2 element vector of 64-bit floats as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdDiv_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Modulo

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] % [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
 * @param a A 16 element vector of 8-bit signed integers as the dividend.
 * @param b A 16 element vector of 8-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMod_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] % [2, 2, 2, 2, 2, 2, 2, 2] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 16-bit signed integers as the dividend.
 * @param b An 8 element vector of 16-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMod_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4] % [2, 2, 2, 2] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit signed integers as the dividend.
 * @param b A 4 element vector of 32-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMod_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2] % [2, 2] -> [1, 0]
 * @param a A 2 element vector of 64-bit signed integers as the dividend.
 * @param b A 2 element vector of 64-bit signed integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMod_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] % [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] -> [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
 * @param a A 16 element vector of 8-bit unsigned integers as the dividend.
 * @param b A 16 element vector of 8-bit unsigned integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMod_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] % [2, 2, 2, 2, 2, 2, 2, 2] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 16-bit unsigned integers as the dividend.
 * @param b An 8 element vector of 16-bit unsigned integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMod_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2, 3, 4] % [2, 2, 2, 2] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 32-bit unsigned integers as the dividend.
 * @param b A 4 element vector of 32-bit unsigned integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMod_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1, 2] % [2, 2] -> [1, 0]
 * @param a A 2 element vector of 64-bit unsigned integers as the dividend.
 * @param b A 2 element vector of 64-bit unsigned integers as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMod_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1.5, 2.5, 3.5, 4.5] % [2.0, 2.0, 2.0, 2.0] -> [1.5, 0.5, 1.5, 0.5]
 * @param a A 4 element vector of 32-bit floats as the dividend.
 * @param b A 4 element vector of 32-bit floats as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMod_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Modulo of all elements of @b a by @b b.
 * @example [1.5, 2.5] % [2.0, 2.0] -> [1.5, 0.5]
 * @param a A 2 element vector of 64-bit floats as the dividend.
 * @param b A 2 element vector of 64-bit floats as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMod_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Rounding

/*!
 * @brief Round all elements to nearest with halves away from zero.
 * @example [1.5, 2.5, 3.5, 4.5] -> [2, 3, 4, 5]
 * @example [-1.5, -2.5, -3.5, -4.5] -> [-2, -3, -4, -5]
 * @param a A 4 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdRoundNearestAway_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Round all elements to nearest with halves away from zero.
 * @example [1.5, 2.5] -> [2, 3]
 * @example [-1.5, -2.5] -> [-2, -3]
 * @param a A 2 element vector of 64-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdRoundNearestAway_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Round all elements to nearest with halves to even.
 * @example [1.5, 2.5, 3.5, 4.5] -> [2, 2, 4, 4]
 * @example [-1.5, -2.5, -3.5, -4.5] -> [-2, -2, -4, -4]
 * @param a A 4 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdRoundNearestEven_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Round all elements to nearest with halves to even.
 * @example [1.5, 2.5] -> [2, 2]
 * @example [-1.5, -2.5] -> [-2, -2]
 * @param a A 2 element vector of 64-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdRoundNearestEven_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Round all elements to zero.
 * @example [1.5, 2.5, 3.5, 4.5] -> [1, 2, 3, 4]
 * @example [-1.5, -2.5, -3.5, -4.5] -> [-1, -2, -3, -4]
 * @param a A 4 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdRoundZero_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Round all elements to zero.
 * @example [1.5, 2.5] -> [1, 2]
 * @example [-1.5, -2.5] -> [-1, -2]
 * @param a A 2 element vector of 64-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdRoundZero_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Round all elements down.
 * @example [1.5, 2.5, 3.5, 4.5] -> [1, 2, 3, 4]
 * @example [-1.5, -2.5, -3.5, -4.5] -> [-2, -3, -4, -5]
 * @param a A 4 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdFloor_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Round all elements down.
 * @example [1.5, 2.5] -> [1, 2]
 * @example [-1.5, -2.5] -> [-2, -3]
 * @param a A 2 element vector of 64-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdFloor_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Round all elements up.
 * @example [1.5, 2.5, 3.5, 4.5] -> [2, 3, 4, 5]
 * @example [-1.5, -2.5, -3.5, -4.5] -> [-1, -2, -3, -4]
 * @param a A 4 element vector of 32-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCeil_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Round all elements up.
 * @example [1.5, 2.5] -> [2, 3]
 * @example [-1.5, -2.5] -> [-1, -2]
 * @param a A 2 element vector of 64-bit floats.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCeil_f64x2(const CCSimd_f64x2 a);


#pragma mark Horizontal Add

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) -> [136, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a A 16 element vector of 8-bit signed integers to horizontally add.
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
 * @param v8 The lane mask to indicate the horizontal add to store in [8]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v9 The lane mask to indicate the horizontal add to store in [9]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v10 The lane mask to indicate the horizontal add to store in [10]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v11 The lane mask to indicate the horizontal add to store in [11]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v12 The lane mask to indicate the horizontal add to store in [12]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v13 The lane mask to indicate the horizontal add to store in [13]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v14 The lane mask to indicate the horizontal add to store in [14]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v15 The lane mask to indicate the horizontal add to store in [15]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdHadd_s8x16(const CCSimd_s8x16 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [36, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 16-bit signed integers to horizontally add.
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
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdHadd_s16x8(const CCSimd_s16x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [10, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit signed integers to horizontally add.
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
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdHadd_s32x4(const CCSimd_s32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [3, undefined]
 * @param a A 2 element vector of 64-bit signed integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdHadd_s64x2(const CCSimd_s64x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) -> [136, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a A 16 element vector of 8-bit unsigned integers to horizontally add.
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
 * @param v8 The lane mask to indicate the horizontal add to store in [8]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v9 The lane mask to indicate the horizontal add to store in [9]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v10 The lane mask to indicate the horizontal add to store in [10]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v11 The lane mask to indicate the horizontal add to store in [11]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v12 The lane mask to indicate the horizontal add to store in [12]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v13 The lane mask to indicate the horizontal add to store in [13]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v14 The lane mask to indicate the horizontal add to store in [14]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v15 The lane mask to indicate the horizontal add to store in [15]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdHadd_u8x16(const CCSimd_u8x16 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [36, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 16-bit unsigned integers to horizontally add.
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
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdHadd_u16x8(const CCSimd_u16x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [10, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit unsigned integers to horizontally add.
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
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdHadd_u32x4(const CCSimd_u32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [3, undefined]
 * @param a A 2 element vector of 64-bit unsigned integers to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdHadd_u64x2(const CCSimd_u64x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1.5, 2.5, 3.5, 4.5].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [12.0, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit floats to horizontally add.
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
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdHadd_f32x4(const CCSimd_f32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [1.5, 2.5].(CC_SIMD_LANE_MASK(0, 1), 0) -> [4.0, undefined]
 * @param a A 2 element vector of 64-bit floats to horizontally add.
 * @param v0 The lane mask to indicate the horizontal add to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal add to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdHadd_f64x2(const CCSimd_f64x2 a, uint8_t v0, uint8_t v1);


#pragma mark Horizontal Subtract

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [136, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) -> [1, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a A 16 element vector of 8-bit signed integers to horizontally subtract.
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
 * @param v8 The lane mask to indicate the horizontal subtract to store in [8]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v9 The lane mask to indicate the horizontal subtract to store in [9]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v10 The lane mask to indicate the horizontal subtract to store in [10]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v11 The lane mask to indicate the horizontal subtract to store in [11]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v12 The lane mask to indicate the horizontal subtract to store in [12]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v13 The lane mask to indicate the horizontal subtract to store in [13]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v14 The lane mask to indicate the horizontal subtract to store in [14]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v15 The lane mask to indicate the horizontal subtract to store in [15]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdHsub_s8x16(const CCSimd_s8x16 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [36, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [1, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 16-bit signed integers to horizontally subtract.
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
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdHsub_s16x8(const CCSimd_s16x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [10, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [1, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit signed integers to horizontally subtract.
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
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdHsub_s32x4(const CCSimd_s32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [3, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [1, undefined]
 * @param a A 2 element vector of 64-bit signed integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdHsub_s64x2(const CCSimd_s64x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [136, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) -> [1, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a A 16 element vector of 8-bit unsigned integers to horizontally subtract.
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
 * @param v8 The lane mask to indicate the horizontal subtract to store in [8]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v9 The lane mask to indicate the horizontal subtract to store in [9]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v10 The lane mask to indicate the horizontal subtract to store in [10]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v11 The lane mask to indicate the horizontal subtract to store in [11]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v12 The lane mask to indicate the horizontal subtract to store in [12]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v13 The lane mask to indicate the horizontal subtract to store in [13]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v14 The lane mask to indicate the horizontal subtract to store in [14]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v15 The lane mask to indicate the horizontal subtract to store in [15]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdHsub_u8x16(const CCSimd_u8x16 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [36, 2, 3, 4, 5, 6, 7, 8].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [1, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 16-bit unsigned integers to horizontally subtract.
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
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdHsub_u16x8(const CCSimd_u16x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [10, 2, 3, 4].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [1, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit unsigned integers to horizontally subtract.
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
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdHsub_u32x4(const CCSimd_u32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [3, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [1, undefined]
 * @param a A 2 element vector of 64-bit unsigned integers to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdHsub_u64x2(const CCSimd_u64x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [12.0, 2.5, 3.5, 4.5].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [1.5, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit floats to horizontally subtract.
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
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdHsub_f32x4(const CCSimd_f32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 * @example [4.0, 2.5].(CC_SIMD_LANE_MASK(0, 1), 0) -> [1.5, undefined]
 * @param a A 2 element vector of 64-bit floats to horizontally subtract.
 * @param v0 The lane mask to indicate the horizontal subtract to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the horizontal subtract to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdHsub_f64x2(const CCSimd_f64x2 a, uint8_t v0, uint8_t v1);


#pragma mark Dot Product

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]x[2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) -> [272, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a A 16 element vector of 8-bit signed integers to use for the dot product.
 * @param b A 16 element vector of 8-bit signed integers to use for the dot product.
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
 * @param v8 The lane mask to indicate the dot product to store in [8]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v9 The lane mask to indicate the dot product to store in [9]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v10 The lane mask to indicate the dot product to store in [10]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v11 The lane mask to indicate the dot product to store in [11]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v12 The lane mask to indicate the dot product to store in [12]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v13 The lane mask to indicate the dot product to store in [13]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v14 The lane mask to indicate the dot product to store in [14]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v15 The lane mask to indicate the dot product to store in [15]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdDot_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[2, 2, 2, 2, 2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [72, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 16-bit signed integers to use for the dot product.
 * @param b An 8 element vector of 16-bit signed integers to use for the dot product.
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
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdDot_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4]x[2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [20, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit signed integers to use for the dot product.
 * @param b A 4 element vector of 32-bit signed integers to use for the dot product.
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
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdDot_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2]x[2, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [6, undefined]
 * @param a A 2 element vector of 64-bit signed integers to use for the dot product.
 * @param b A 2 element vector of 64-bit signed integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdDot_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]x[2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) -> [272, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a A 16 element vector of 8-bit unsigned integers to use for the dot product.
 * @param b A 16 element vector of 8-bit unsigned integers to use for the dot product.
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
 * @param v8 The lane mask to indicate the dot product to store in [8]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v9 The lane mask to indicate the dot product to store in [9]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v10 The lane mask to indicate the dot product to store in [10]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v11 The lane mask to indicate the dot product to store in [11]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v12 The lane mask to indicate the dot product to store in [12]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v13 The lane mask to indicate the dot product to store in [13]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v14 The lane mask to indicate the dot product to store in [14]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v15 The lane mask to indicate the dot product to store in [15]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdDot_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[2, 2, 2, 2, 2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7), 0, 0, 0, 0, 0, 0, 0) -> [72, undefined, undefined, undefined, undefined, undefined, undefined, undefined]
 * @param a An 8 element vector of 16-bit unsigned integers to use for the dot product.
 * @param b An 8 element vector of 16-bit unsigned integers to use for the dot product.
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
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdDot_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2, 3, 4]x[2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [20, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit unsigned integers to use for the dot product.
 * @param b A 4 element vector of 32-bit unsigned integers to use for the dot product.
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
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdDot_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1, 2]x[2, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [6, undefined]
 * @param a A 2 element vector of 64-bit unsigned integers to use for the dot product.
 * @param b A 2 element vector of 64-bit unsigned integers to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdDot_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1.5, 2.5, 3.5, 4.5]x[2, 2, 2, 2].(CC_SIMD_LANE_MASK(0, 1, 2, 3), 0, 0, 0) -> [24.0, undefined, undefined, undefined]
 * @param a A 4 element vector of 32-bit floats to use for the dot product.
 * @param b A 4 element vector of 32-bit floats to use for the dot product.
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
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdDot_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 * @example [1.5, 2.5]x[2, 2].(CC_SIMD_LANE_MASK(0, 1), 0) -> [8.0, undefined]
 * @param a A 2 element vector of 64-bit floats to use for the dot product.
 * @param b A 2 element vector of 64-bit floats to use for the dot product.
 * @param v0 The lane mask to indicate the dot product to store in [0]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @param v1 The lane mask to indicate the dot product to store in [1]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the
 *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).
 *
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdDot_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, uint8_t v0, uint8_t v1);


#pragma mark Sum

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> 136
 * @param a A 16 element vector of 8-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int8_t CCSimdSum_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> 36
 * @param a An 8 element vector of 16-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int16_t CCSimdSum_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4] -> 10
 * @param a A 4 element vector of 32-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int32_t CCSimdSum_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2] -> 3
 * @param a A 2 element vector of 64-bit signed integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE int64_t CCSimdSum_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> 136
 * @param a A 16 element vector of 8-bit unsigned integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint8_t CCSimdSum_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> 36
 * @param a An 8 element vector of 16-bit unsigned integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint16_t CCSimdSum_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2, 3, 4] -> 10
 * @param a A 4 element vector of 32-bit unsigned integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint32_t CCSimdSum_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1, 2] -> 3
 * @param a A 2 element vector of 64-bit unsigned integers to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE uint64_t CCSimdSum_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1.5, 2.5, 3.5, 4.5] -> 12.0
 * @param a A 4 element vector of 32-bit floats to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE float CCSimdSum_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Sum the elements of @b a.
 * @example [1.5, 2.5] -> 4.0
 * @param a A 2 element vector of 64-bit floats to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE double CCSimdSum_f64x2(const CCSimd_f64x2 a);


#pragma mark Negate

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16]
 * @param a A 16 element vector of 8-bit signed integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdNeg_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8] -> [-1, -2, -3, -4, -5, -6, -7, -8]
 * @param a An 8 element vector of 16-bit signed integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdNeg_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4] -> [-1, -2, -3, -4]
 * @param a A 4 element vector of 32-bit signed integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdNeg_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2] -> [-1, -2]
 * @param a A 2 element vector of 64-bit signed integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdNeg_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16]
 * @param a A 16 element vector of 8-bit unsigned integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdNeg_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8] -> [-1, -2, -3, -4, -5, -6, -7, -8]
 * @param a An 8 element vector of 16-bit unsigned integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdNeg_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2, 3, 4] -> [-1, -2, -3, -4]
 * @param a A 4 element vector of 32-bit unsigned integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdNeg_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1, 2] -> [-1, -2]
 * @param a A 2 element vector of 64-bit unsigned integers to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdNeg_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1.5, 2.5, 3.5, 4.5] -> [-1.5, -2.5, -3.5, -4.5]
 * @param a A 4 element vector of 32-bit floats to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdNeg_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Negate each element in @b a.
 * @example -[1.5, 2.5] -> [-1.5, -2.5]
 * @param a A 2 element vector of 64-bit floats to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdNeg_f64x2(const CCSimd_f64x2 a);


#pragma mark Absolute

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
 * @param a A 16 element vector of 8-bit signed integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdAbs_s8x16(const CCSimd_s8x16 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8] -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 16-bit signed integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdAbs_s16x8(const CCSimd_s16x8 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2, 3, 4] -> [1, 2, 3, 4]
 * @param a A 4 element vector of 32-bit signed integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdAbs_s32x4(const CCSimd_s32x4 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2] -> [1, 2]
 * @param a A 2 element vector of 64-bit signed integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdAbs_s64x2(const CCSimd_s64x2 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16] -> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
 * @param a A 16 element vector of 8-bit unsigned integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdAbs_u8x16(const CCSimd_u8x16 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2, 3, 4, 5, 6, 7, 8] -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 16-bit unsigned integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdAbs_u16x8(const CCSimd_u16x8 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2, 3, 4] -> [1, 2, 3, 4]
 * @param a A 4 element vector of 32-bit unsigned integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdAbs_u32x4(const CCSimd_u32x4 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1, 2] -> [1, 2]
 * @param a A 2 element vector of 64-bit unsigned integers to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdAbs_u64x2(const CCSimd_u64x2 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1.5, 2.5, 3.5, 4.5] -> [1.5, 2.5, 3.5, 4.5]
 * @param a A 4 element vector of 32-bit floats to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdAbs_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Absolute each element in @b a.
 * @example -[1.5, 2.5] -> [1.5, 2.5]
 * @param a A 2 element vector of 64-bit floats to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdAbs_f64x2(const CCSimd_f64x2 a);


#pragma mark Min

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120, 13, 140, 15, 160], [10, 2, 30, 4, 50, 6, 70, 8, 90, 10, 110, 12, 130, 14, 150, 16]) -> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMin_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMin_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40], [10, 2, 30, 4]) -> [1, 2, 3, 4]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMin_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20], [10, 2]) -> [1, 2]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMin_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120, 13, 140, 15, 160], [10, 2, 30, 4, 50, 6, 70, 8, 90, 10, 110, 12, 130, 14, 150, 16]) -> [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMin_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [1, 2, 3, 4, 5, 6, 7, 8]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMin_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20, 3, 40], [10, 2, 30, 4]) -> [1, 2, 3, 4]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMin_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1, 20], [10, 2]) -> [1, 2]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMin_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1.0, 20.0, 3.0, 40.0], [15.75, 2.5, 36.75, 4.5]) -> [1.0, 2.5, 3.0, 4.5]
 * @param a A 4 element vector of 32-bit floats.
 * @param b A 4 element vector of 32-bit floats.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMin_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Get the min of each element from @b a and @b b.
 * @example min([1.0, 20.0], [15.75, 2.5]) -> [1.0, 2.5]
 * @param a A 2 element vector of 64-bit floats.
 * @param b A 2 element vector of 64-bit floats.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMin_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Max

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120, 13, 140, 15, 160], [10, 2, 30, 4, 50, 6, 70, 8, 90, 10, 110, 12, 130, 14, 150, 16]) -> [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160]
 * @param a A 16 element vector of 8-bit signed integers.
 * @param b A 16 element vector of 8-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMax_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [10, 20, 30, 40, 50, 60, 70, 80]
 * @param a An 8 element vector of 16-bit signed integers.
 * @param b An 8 element vector of 16-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMax_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40], [10, 2, 30, 4]) -> [10, 20, 30, 40]
 * @param a A 4 element vector of 32-bit signed integers.
 * @param b A 4 element vector of 32-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMax_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20], [10, 2]) -> [10, 20]
 * @param a A 2 element vector of 64-bit signed integers.
 * @param b A 2 element vector of 64-bit signed integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMax_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120, 13, 140, 15, 160], [10, 2, 30, 4, 50, 6, 70, 8, 90, 10, 110, 12, 130, 14, 150, 16]) -> [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160]
 * @param a A 16 element vector of 8-bit unsigned integers.
 * @param b A 16 element vector of 8-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMax_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40, 5, 60, 7, 80], [10, 2, 30, 4, 50, 6, 70, 8]) -> [10, 20, 30, 40, 50, 60, 70, 80]
 * @param a An 8 element vector of 16-bit unsigned integers.
 * @param b An 8 element vector of 16-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMax_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20, 3, 40], [10, 2, 30, 4]) -> [10, 20, 30, 40]
 * @param a A 4 element vector of 32-bit unsigned integers.
 * @param b A 4 element vector of 32-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMax_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1, 20], [10, 2]) -> [10, 20]
 * @param a A 2 element vector of 64-bit unsigned integers.
 * @param b A 2 element vector of 64-bit unsigned integers.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMax_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1.0, 20.0, 3.0, 40.0], [15.75, 2.5, 36.75, 4.5]) -> [15.75, 20.0, 36.75, 40.0]
 * @param a A 4 element vector of 32-bit floats.
 * @param b A 4 element vector of 32-bit floats.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMax_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b);

/*!
 * @brief Get the max of each element from @b a and @b b.
 * @example max([1.0, 20.0], [15.75, 2.5]) -> [15.75, 20.0]
 * @param a A 2 element vector of 64-bit floats.
 * @param b A 2 element vector of 64-bit floats.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMax_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b);


#pragma mark Clamp

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]) -> [2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
 * @param a A 16 element vector of 8-bit signed integers to be clamped.
 * @param min A 16 element vector of 8-bit signed integers to use as the minimum.
 * @param max A 16 element vector of 8-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdClamp_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 min, const CCSimd_s8x16 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4, 5, 6, 7, 8], [2, 2, 2, 2, 2, 2, 2, 2], [3, 3, 3, 3, 3, 3, 3, 3]) -> [2, 2, 3, 3, 3, 3, 3, 3]
 * @param a An 8 element vector of 16-bit signed integers to be clamped.
 * @param min An 8 element vector of 16-bit signed integers to use as the minimum.
 * @param max An 8 element vector of 16-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdClamp_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 min, const CCSimd_s16x8 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4], [2, 2, 2, 2], [3, 3, 3, 3]) -> [2, 2, 3, 3]
 * @param a A 4 element vector of 32-bit signed integers to be clamped.
 * @param min A 4 element vector of 32-bit signed integers to use as the minimum.
 * @param max A 4 element vector of 32-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdClamp_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 min, const CCSimd_s32x4 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2], [2, 2], [3, 3]) -> [2, 2]
 * @param a A 2 element vector of 64-bit signed integers to be clamped.
 * @param min A 2 element vector of 64-bit signed integers to use as the minimum.
 * @param max A 2 element vector of 64-bit signed integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdClamp_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 min, const CCSimd_s64x2 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]) -> [2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
 * @param a A 16 element vector of 8-bit unsigned integers to be clamped.
 * @param min A 16 element vector of 8-bit unsigned integers to use as the minimum.
 * @param max A 16 element vector of 8-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdClamp_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 min, const CCSimd_u8x16 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4, 5, 6, 7, 8], [2, 2, 2, 2, 2, 2, 2, 2], [3, 3, 3, 3, 3, 3, 3, 3]) -> [2, 2, 3, 3, 3, 3, 3, 3]
 * @param a An 8 element vector of 16-bit unsigned integers to be clamped.
 * @param min An 8 element vector of 16-bit unsigned integers to use as the minimum.
 * @param max An 8 element vector of 16-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdClamp_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 min, const CCSimd_u16x8 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2, 3, 4], [2, 2, 2, 2], [3, 3, 3, 3]) -> [2, 2, 3, 3]
 * @param a A 4 element vector of 32-bit unsigned integers to be clamped.
 * @param min A 4 element vector of 32-bit unsigned integers to use as the minimum.
 * @param max A 4 element vector of 32-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdClamp_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 min, const CCSimd_u32x4 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1, 2], [2, 2], [3, 3]) -> [2, 2]
 * @param a A 2 element vector of 64-bit unsigned integers to be clamped.
 * @param min A 2 element vector of 64-bit unsigned integers to use as the minimum.
 * @param max A 2 element vector of 64-bit unsigned integers to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdClamp_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 min, const CCSimd_u64x2 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1.5, 2.5, 3.5, 4.5], [2.0, 2.0, 2.0, 2.0], [3.0, 3.0, 3.0, 3.0]) -> [2.0, 2.5, 3.0, 3.0]
 * @param a A 4 element vector of 32-bit floats to be clamped.
 * @param min A 4 element vector of 32-bit floats to use as the minimum.
 * @param max A 4 element vector of 32-bit floats to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdClamp_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 min, const CCSimd_f32x4 max);

/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 * @example clamp([1.5, 2.5], [2.0, 2.0], [3.0, 3.0]) -> [2.0, 2.5]
 * @param a A 2 element vector of 64-bit floats to be clamped.
 * @param min A 2 element vector of 64-bit floats to use as the minimum.
 * @param max A 2 element vector of 64-bit floats to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdClamp_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 min, const CCSimd_f64x2 max);


#pragma mark Square Root

/*!
 * @brief Compute the square root of each element in the vector.
 * @param a A 4 element vector of 32-bit floats to get the square root of.
 * @return The square root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSqrt_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the square root of each element in the vector.
 * @param a A 2 element vector of 64-bit floats to get the square root of.
 * @return The square root vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSqrt_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the reciprocal square root of each element in the vector.
 * @param a A 4 element vector of 32-bit floats to get the inverse square root of.
 * @return The inverse square root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdInvSqrt_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the reciprocal square root of each element in the vector.
 * @param a A 2 element vector of 64-bit floats to get the inverse square root of.
 * @return The inverse square root vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdInvSqrt_f64x2(const CCSimd_f64x2 a);


#pragma mark Cube Root

/*!
 * @brief Compute the cube root of each element in the vector.
 * @param a A 4 element vector of 32-bit floats to get the cube root of.
 * @return The cube root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCbrt_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the cube root of each element in the vector.
 * @param a A 2 element vector of 64-bit floats to get the cube root of.
 * @return The cube root vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCbrt_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the reciprocal cube root of each element in the vector.
 * @param a A 4 element vector of 32-bit floats to get the inverse cube root of.
 * @return The inverse cube root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdInvCbrt_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the reciprocal cube root of each element in the vector.
 * @param a A 2 element vector of 64-bit floats to get the inverse cube root of.
 * @return The inverse cube root vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdInvCbrt_f64x2(const CCSimd_f64x2 a);


#pragma mark Power

/*!
 * @brief Compute value of each element in the vector @b Base raised by vector @b Exponent.
 * @param Base A 4 element vector of 32-bit floats to be raised.
 * @param Exponent A 4 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdPow_f32x4(const CCSimd_f32x4 Base, const CCSimd_f32x4 Exponent);

/*!
 * @brief Compute value of each element in the vector @b Base raised by vector @b Exponent.
 * @param Base A 2 element vector of 64-bit floats to be raised.
 * @param Exponent A 2 element vector of 64-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdPow_f64x2(const CCSimd_f64x2 Base, const CCSimd_f64x2 Exponent);


#pragma mark 2 Power

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 16 element vector of 8-bit signed integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdPow2_s8x16(const CCSimd_s8x16 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent An 8 element vector of 16-bit signed integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdPow2_s16x8(const CCSimd_s16x8 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 4 element vector of 32-bit signed integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdPow2_s32x4(const CCSimd_s32x4 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 2 element vector of 64-bit signed integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdPow2_s64x2(const CCSimd_s64x2 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 16 element vector of 8-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdPow2_u8x16(const CCSimd_u8x16 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent An 8 element vector of 16-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdPow2_u16x8(const CCSimd_u16x8 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 4 element vector of 32-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdPow2_u32x4(const CCSimd_u32x4 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 2 element vector of 64-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdPow2_u64x2(const CCSimd_u64x2 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 4 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdPow2_f32x4(const CCSimd_f32x4 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 2 element vector of 64-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdPow2_f64x2(const CCSimd_f64x2 Exponent);


#pragma mark Exponent

/*!
 * @brief Computes e^n (Euler's number 2.7182818..) for each element raised by vector @b a.
 * @param a A 4 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdExp_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Computes e^n (Euler's number 2.7182818..) for each element raised by vector @b a.
 * @param a A 2 element vector of 64-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdExp_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Computes 2^n for each element raised by vector @b a.
 * @param a A 4 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdExp2_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Computes 2^n for each element raised by vector @b a.
 * @param a A 2 element vector of 64-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdExp2_f64x2(const CCSimd_f64x2 a);


#pragma mark Logarithm

/*!
 * @brief Computes base e logarithm for each element in vector @b a.
 * @param a A 4 element vector of 32-bit floats to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdLog_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Computes base e logarithm for each element in vector @b a.
 * @param a A 2 element vector of 64-bit floats to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdLog_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Computes base 2 logarithm for each element in vector @b a.
 * @param a A 4 element vector of 32-bit floats to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdLog2_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Computes base 2 logarithm for each element in vector @b a.
 * @param a A 2 element vector of 64-bit floats to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdLog2_f64x2(const CCSimd_f64x2 a);


#pragma mark Sine

/*!
 * @brief Compute the sine of each radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSin_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the sine of each radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSin_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the sine of each positive radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdPosSin_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the sine of each positive radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdPosSin_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the sine of each -pi to pi (-180° to 180°) radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdPiRadSin_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the sine of each -pi to pi (-180° to 180°) radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdPiRadSin_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the sine of each 0 to pi (0° to 180°) radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdPosPiRadSin_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the sine of each 0 to pi (0° to 180°) radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdPosPiRadSin_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the arc sine of each element in the vector.
 * @param a A 4 element vector of 32-bit float.
 * @return The arc sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdArcSin_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the arc sine of each element in the vector.
 * @param a A 2 element vector of 64-bit float.
 * @return The arc sine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdArcSin_f64x2(const CCSimd_f64x2 a);


#pragma mark Cosine

/*!
 * @brief Compute the cosine of each -pi/2 to pi/2 (-90° to 90°) radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdHalfPiRadCos_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the cosine of each -pi/2 to pi/2 (-90° to 90°) radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdHalfPiRadCos_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the cosine of each radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCos_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the cosine of each radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCos_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the arc cosine of each element in the vector.
 * @param a A 4 element vector of 32-bit float.
 * @return The arc cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdArcCos_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the arc cosine of each element in the vector.
 * @param a A 2 element vector of 64-bit float.
 * @return The arc cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdArcCos_f64x2(const CCSimd_f64x2 a);


#pragma mark Tangent

/*!
 * @brief Compute the tangent of each radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdTan_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the tangent of each radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdTan_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the arc tangent of each -tan(pi/4) to tan(pi/4) (-1 to 1) element in the vector.
 * @param a A 4 element vector of 32-bit float.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdQtrPiArcTan_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the arc tangent of each -tan(pi/4) to tan(pi/4) (-1 to 1) element in the vector.
 * @param a A 2 element vector of 64-bit float.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdQtrPiArcTan_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the arc tangent of each element in the vector.
 * @param a A 4 element vector of 32-bit float.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdArcTan_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the arc tangent of each element in the vector.
 * @param a A 2 element vector of 64-bit float.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdArcTan_f64x2(const CCSimd_f64x2 a);

/*!
 * @brief Compute the arc tangent of y / x of each element in the vector.
 * @note When @b CC_SIMD_ARCTAN2_PRINCIPAL is defined the range (-pi, pi] is used, otherwise the default
 *       uses [-pi, pi]. By default when x and y are 0 the result is undefined, if @b CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO
 *       is defined 0.0 is returned, or @b CC_SIMD_ARCTAN2_UNDEFINED can be defined to the desired return value.
 *
 * @param y A 4 element vector of 32-bit float.
 * @param x A 4 element vector of 32-bit float.
 * @return The arc tangent vector of y / x.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdArcTan2_f32x4(const CCSimd_f32x4 y, const CCSimd_f32x4 x);

/*!
 * @brief Compute the arc tangent of y / x of each element in the vector.
 * @note When @b CC_SIMD_ARCTAN2_PRINCIPAL is defined the range (-pi, pi] is used, otherwise the default
 *       uses [-pi, pi]. By default when x and y are 0 the result is undefined, if @b CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO
 *       is defined 0.0 is returned, or @b CC_SIMD_ARCTAN2_UNDEFINED can be defined to the desired return value.
 *
 * @param y A 2 element vector of 64-bit float.
 * @param x A 2 element vector of 64-bit float.
 * @return The arc tangent vector of y / x.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdArcTan2_f64x2(const CCSimd_f64x2 y, const CCSimd_f64x2 x);


#pragma mark Cosecant

/*!
 * @brief Compute the cosecant (reciprocal sine) of each radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The cosecant vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCsc_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the cosecant (reciprocal sine) of each radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The cosecant vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCsc_f64x2(const CCSimd_f64x2 a);


#pragma mark Secant

/*!
 * @brief Compute the secant (reciprocal cosine) of each radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The secant vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSec_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the secant (reciprocal cosine) of each radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The secant vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSec_f64x2(const CCSimd_f64x2 a);


#pragma mark Cotangent

/*!
 * @brief Compute the cotangent (reciprocal tangent) of each radian element in the vector.
 * @param a A 4 element vector of 32-bit float radians.
 * @return The cotangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdCot_f32x4(const CCSimd_f32x4 a);

/*!
 * @brief Compute the cotangent (reciprocal tangent) of each radian element in the vector.
 * @param a A 2 element vector of 64-bit float radians.
 * @return The cotangent vector.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdCot_f64x2(const CCSimd_f64x2 a);


#pragma mark - Reordering
#pragma mark Swizzle

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) -> [160, 150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10]
 * @param a A 16 element vector of 8-bit signed integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @param v4 The index of the element in @b a to be moved to [4].
 * @param v5 The index of the element in @b a to be moved to [5].
 * @param v6 The index of the element in @b a to be moved to [6].
 * @param v7 The index of the element in @b a to be moved to [7].
 * @param v8 The index of the element in @b a to be moved to [8].
 * @param v9 The index of the element in @b a to be moved to [9].
 * @param v10 The index of the element in @b a to be moved to [10].
 * @param v11 The index of the element in @b a to be moved to [11].
 * @param v12 The index of the element in @b a to be moved to [12].
 * @param v13 The index of the element in @b a to be moved to [13].
 * @param v14 The index of the element in @b a to be moved to [14].
 * @param v15 The index of the element in @b a to be moved to [15].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdSwizzle_s8x16(const CCSimd_s8x16 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40, 50, 60, 70, 80].(7, 6, 5, 4, 3, 2, 1, 0) -> [80, 70, 60, 50, 40, 30, 20, 10]
 * @param a An 8 element vector of 16-bit signed integers to swizzle.
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
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdSwizzle_s16x8(const CCSimd_s16x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40].(3, 2, 1, 0) -> [40, 30, 20, 10]
 * @param a A 4 element vector of 32-bit signed integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdSwizzle_s32x4(const CCSimd_s32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20].(1, 0) -> [20, 10]
 * @param a A 2 element vector of 64-bit signed integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdSwizzle_s64x2(const CCSimd_s64x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) -> [160, 150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10]
 * @param a A 16 element vector of 8-bit unsigned integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @param v4 The index of the element in @b a to be moved to [4].
 * @param v5 The index of the element in @b a to be moved to [5].
 * @param v6 The index of the element in @b a to be moved to [6].
 * @param v7 The index of the element in @b a to be moved to [7].
 * @param v8 The index of the element in @b a to be moved to [8].
 * @param v9 The index of the element in @b a to be moved to [9].
 * @param v10 The index of the element in @b a to be moved to [10].
 * @param v11 The index of the element in @b a to be moved to [11].
 * @param v12 The index of the element in @b a to be moved to [12].
 * @param v13 The index of the element in @b a to be moved to [13].
 * @param v14 The index of the element in @b a to be moved to [14].
 * @param v15 The index of the element in @b a to be moved to [15].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdSwizzle_u8x16(const CCSimd_u8x16 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40, 50, 60, 70, 80].(7, 6, 5, 4, 3, 2, 1, 0) -> [80, 70, 60, 50, 40, 30, 20, 10]
 * @param a An 8 element vector of 16-bit unsigned integers to swizzle.
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
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdSwizzle_u16x8(const CCSimd_u16x8 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40].(3, 2, 1, 0) -> [40, 30, 20, 10]
 * @param a A 4 element vector of 32-bit unsigned integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdSwizzle_u32x4(const CCSimd_u32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20].(1, 0) -> [20, 10]
 * @param a A 2 element vector of 64-bit unsigned integers to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdSwizzle_u64x2(const CCSimd_u64x2 a, uint8_t v0, uint8_t v1);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20, 30, 40].(3, 2, 1, 0) -> [40, 30, 20, 10]
 * @param a A 4 element vector of 32-bit floats to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @param v2 The index of the element in @b a to be moved to [2].
 * @param v3 The index of the element in @b a to be moved to [3].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdSwizzle_f32x4(const CCSimd_f32x4 a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 * @example [10, 20].(1, 0) -> [20, 10]
 * @param a A 2 element vector of 64-bit floats to swizzle.
 * @param v0 The index of the element in @b a to be moved to [0].
 * @param v1 The index of the element in @b a to be moved to [1].
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdSwizzle_f64x2(const CCSimd_f64x2 a, uint8_t v0, uint8_t v1);


#pragma mark Interleave

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]x[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1) -> [1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120, 13, 140, 15, 160]
 * @param a A 16 element vector of 8-bit signed integers to interleave.
 * @param b A 16 element vector of 8-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v4 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v5 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v6 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v7 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v8 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v9 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v10 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v11 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v12 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v13 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v14 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v15 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdInterleave_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(0, 1, 0, 1, 0, 1, 0, 1) -> [1, 20, 3, 40, 5, 60, 7, 80]
 * @param a An 8 element vector of 16-bit signed integers to interleave.
 * @param b An 8 element vector of 16-bit signed integers to interleave.
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
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdInterleave_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(0, 1, 0, 1) -> [1, 20, 3, 40]
 * @param a A 4 element vector of 32-bit signed integers to interleave.
 * @param b A 4 element vector of 32-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdInterleave_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2]x[10, 20].(0, 1) -> [1, 20]
 * @param a A 2 element vector of 64-bit signed integers to interleave.
 * @param b A 2 element vector of 64-bit signed integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdInterleave_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]x[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1) -> [1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120, 13, 140, 15, 160]
 * @param a A 16 element vector of 8-bit unsigned integers to interleave.
 * @param b A 16 element vector of 8-bit unsigned integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v4 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v5 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v6 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v7 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v8 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v9 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v10 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v11 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v12 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v13 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v14 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v15 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdInterleave_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(0, 1, 0, 1, 0, 1, 0, 1) -> [1, 20, 3, 40, 5, 60, 7, 80]
 * @param a An 8 element vector of 16-bit unsigned integers to interleave.
 * @param b An 8 element vector of 16-bit unsigned integers to interleave.
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
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdInterleave_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(0, 1, 0, 1) -> [1, 20, 3, 40]
 * @param a A 4 element vector of 32-bit unsigned integers to interleave.
 * @param b A 4 element vector of 32-bit unsigned integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdInterleave_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2]x[10, 20].(0, 1) -> [1, 20]
 * @param a A 2 element vector of 64-bit unsigned integers to interleave.
 * @param b A 2 element vector of 64-bit unsigned integers to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdInterleave_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(0, 1, 0, 1) -> [1, 20, 3, 40]
 * @param a A 4 element vector of 32-bit floats to interleave.
 * @param b A 4 element vector of 32-bit floats to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v2 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v3 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdInterleave_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Interleave the elements of @b a and @b b.
 * @example [1, 2]x[10, 20].(0, 1) -> [1, 20]
 * @param a A 2 element vector of 64-bit floats to interleave.
 * @param b A 2 element vector of 64-bit floats to interleave.
 * @param v0 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @param v1 The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b.
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdInterleave_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, uint8_t v0, uint8_t v1);


#pragma mark Merge

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]x[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20]
 * @param a A 16 element vector of 8-bit signed integers to merge.
 * @param b A 16 element vector of 8-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v4 The vector element argument to be moved to [4]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v5 The vector element argument to be moved to [5]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v6 The vector element argument to be moved to [6]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v7 The vector element argument to be moved to [7]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v8 The vector element argument to be moved to [8]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v9 The vector element argument to be moved to [9]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v10 The vector element argument to be moved to [10]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v11 The vector element argument to be moved to [11]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v12 The vector element argument to be moved to [12]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v13 The vector element argument to be moved to [13]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v14 The vector element argument to be moved to [14]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v15 The vector element argument to be moved to [15]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s8x16 CCSimdMerge_s8x16(const CCSimd_s8x16 a, const CCSimd_s8x16 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20, 2, 20, 2, 20]
 * @param a An 8 element vector of 16-bit signed integers to merge.
 * @param b An 8 element vector of 16-bit signed integers to merge.
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
static CC_FORCE_INLINE CCSimd_s16x8 CCSimdMerge_s16x8(const CCSimd_s16x8 a, const CCSimd_s16x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20]
 * @param a A 4 element vector of 32-bit signed integers to merge.
 * @param b A 4 element vector of 32-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s32x4 CCSimdMerge_s32x4(const CCSimd_s32x4 a, const CCSimd_s32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2]x[10, 20].(CC_SIMD_A1, CC_SIMD_B1) -> [2, 20]
 * @param a A 2 element vector of 64-bit signed integers to merge.
 * @param b A 2 element vector of 64-bit signed integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_s64x2 CCSimdMerge_s64x2(const CCSimd_s64x2 a, const CCSimd_s64x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]x[10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20, 2, 20]
 * @param a A 16 element vector of 8-bit unsigned integers to merge.
 * @param b A 16 element vector of 8-bit unsigned integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v4 The vector element argument to be moved to [4]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v5 The vector element argument to be moved to [5]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v6 The vector element argument to be moved to [6]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v7 The vector element argument to be moved to [7]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v8 The vector element argument to be moved to [8]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v9 The vector element argument to be moved to [9]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v10 The vector element argument to be moved to [10]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v11 The vector element argument to be moved to [11]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v12 The vector element argument to be moved to [12]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v13 The vector element argument to be moved to [13]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v14 The vector element argument to be moved to [14]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v15 The vector element argument to be moved to [15]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCSimdMerge_u8x16(const CCSimd_u8x16 a, const CCSimd_u8x16 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4, 5, 6, 7, 8]x[10, 20, 30, 40, 50, 60, 70, 80].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20, 2, 20, 2, 20]
 * @param a An 8 element vector of 16-bit unsigned integers to merge.
 * @param b An 8 element vector of 16-bit unsigned integers to merge.
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
static CC_FORCE_INLINE CCSimd_u16x8 CCSimdMerge_u16x8(const CCSimd_u16x8 a, const CCSimd_u16x8 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20]
 * @param a A 4 element vector of 32-bit unsigned integers to merge.
 * @param b A 4 element vector of 32-bit unsigned integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u32x4 CCSimdMerge_u32x4(const CCSimd_u32x4 a, const CCSimd_u32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2]x[10, 20].(CC_SIMD_A1, CC_SIMD_B1) -> [2, 20]
 * @param a A 2 element vector of 64-bit unsigned integers to merge.
 * @param b A 2 element vector of 64-bit unsigned integers to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_u64x2 CCSimdMerge_u64x2(const CCSimd_u64x2 a, const CCSimd_u64x2 b, uint8_t v0, uint8_t v1);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2, 3, 4]x[10, 20, 30, 40].(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B1) -> [2, 20, 2, 20]
 * @param a A 4 element vector of 32-bit floats to merge.
 * @param b A 4 element vector of 32-bit floats to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v2 The vector element argument to be moved to [2]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v3 The vector element argument to be moved to [3]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_f32x4 CCSimdMerge_f32x4(const CCSimd_f32x4 a, const CCSimd_f32x4 b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3);

/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 * @example [1, 2]x[10, 20].(CC_SIMD_A1, CC_SIMD_B1) -> [2, 20]
 * @param a A 2 element vector of 64-bit floats to merge.
 * @param b A 2 element vector of 64-bit floats to merge.
 * @param v0 The vector element argument to be moved to [0]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @param v1 The vector element argument to be moved to [1]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element.
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_f64x2 CCSimdMerge_f64x2(const CCSimd_f64x2 a, const CCSimd_f64x2 b, uint8_t v0, uint8_t v1);


#pragma mark -

#define CC_SIMD_128_2_ELEMENT_INTEGER_TYPES \
(s64, 2), \
(u64, 2)

#define CC_SIMD_128_4_ELEMENT_INTEGER_TYPES \
(s32, 4), \
(u32, 4)

#define CC_SIMD_128_8_ELEMENT_INTEGER_TYPES \
(s16, 8), \
(u16, 8)

#define CC_SIMD_128_16_ELEMENT_INTEGER_TYPES \
(s8, 16), \
(u8, 16)

#define CC_SIMD_128_2_ELEMENT_FLOAT_TYPES \
(f64, 2)

#define CC_SIMD_128_4_ELEMENT_FLOAT_TYPES \
(f32, 4)

#define CC_SIMD_128_SIGNED_TYPES \
(s64, 2), \
(s32, 4), \
(s16, 8), \
(s8, 16), \
(f64, 2), \
(f32, 4)

#define CC_SIMD_128_UNSIGNED_TYPES \
(u64, 2), \
(u32, 4), \
(u16, 8), \
(u8, 16)

#define CC_SIMD_128_2_ELEMENT_TYPES \
CC_SIMD_128_2_ELEMENT_INTEGER_TYPES, \
CC_SIMD_128_2_ELEMENT_FLOAT_TYPES

#define CC_SIMD_128_4_ELEMENT_TYPES \
CC_SIMD_128_4_ELEMENT_INTEGER_TYPES, \
CC_SIMD_128_4_ELEMENT_FLOAT_TYPES

#define CC_SIMD_128_8_ELEMENT_TYPES \
CC_SIMD_128_8_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_16_ELEMENT_TYPES \
CC_SIMD_128_16_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_TYPES \
CC_SIMD_128_16_ELEMENT_TYPES, \
CC_SIMD_128_8_ELEMENT_TYPES, \
CC_SIMD_128_4_ELEMENT_TYPES, \
CC_SIMD_128_2_ELEMENT_TYPES

#define CC_SIMD_128_INTEGER_TYPES \
CC_SIMD_128_16_ELEMENT_INTEGER_TYPES, \
CC_SIMD_128_8_ELEMENT_INTEGER_TYPES, \
CC_SIMD_128_4_ELEMENT_INTEGER_TYPES, \
CC_SIMD_128_2_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_INTEGER_64_TYPES CC_SIMD_128_2_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_INTEGER_32_TYPES CC_SIMD_128_4_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_INTEGER_16_TYPES CC_SIMD_128_8_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_INTEGER_8_TYPES CC_SIMD_128_16_ELEMENT_INTEGER_TYPES

#define CC_SIMD_128_FLOAT_TYPES \
CC_SIMD_128_4_ELEMENT_FLOAT_TYPES, \
CC_SIMD_128_2_ELEMENT_FLOAT_TYPES

#define CC_SIMD_WIDTH 128
#include <CommonC/SimdFallbackDefaults.h>

#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
#include <CommonC/Simd128_arm.h>
#endif

#pragma mark - Fallback Implementations

#include <CommonC/SimdFallback.h>
#undef CC_SIMD_WIDTH

#endif
