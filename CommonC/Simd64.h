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

#define CC_SIMD_INTERNAL_POLY_VALUE(name, i) name.val[i]

#define CC_SIMD_INTERNAL_POLY_TYPE(base, count, poly) CC_SIMD_INTERNAL_POLY_TYPE_(CC_SIMD_INTERNAL_POLY_TYPE_##base, count, poly)
#define CC_SIMD_INTERNAL_POLY_TYPE_(base, count, poly) CC_SIMD_INTERNAL_POLY_TYPE__(base, count, poly)
#define CC_SIMD_INTERNAL_POLY_TYPE__(base, count, poly) base##x##count##x##poly##_t

#define CC_SIMD_INTERNAL_POLY_TYPE_s8 int8
#define CC_SIMD_INTERNAL_POLY_TYPE_s16 int16
#define CC_SIMD_INTERNAL_POLY_TYPE_s32 int32
#define CC_SIMD_INTERNAL_POLY_TYPE_s64 int64
#define CC_SIMD_INTERNAL_POLY_TYPE_u8 uint8
#define CC_SIMD_INTERNAL_POLY_TYPE_u16 uint16
#define CC_SIMD_INTERNAL_POLY_TYPE_u32 uint32
#define CC_SIMD_INTERNAL_POLY_TYPE_u64 uint64
#define CC_SIMD_INTERNAL_POLY_TYPE_f32 float32
#define CC_SIMD_INTERNAL_POLY_TYPE_f64 double64
#endif


typedef struct { CCSimd_s8x8 v[2]; } CCSimd_s8x8x2;
typedef struct { CCSimd_s8x8 v[3]; } CCSimd_s8x8x3;
typedef struct { CCSimd_s8x8 v[4]; } CCSimd_s8x8x4;
typedef struct { CCSimd_s16x4 v[2]; } CCSimd_s16x4x2;
typedef struct { CCSimd_s16x4 v[3]; } CCSimd_s16x4x3;
typedef struct { CCSimd_s16x4 v[4]; } CCSimd_s16x4x4;
typedef struct { CCSimd_s32x2 v[2]; } CCSimd_s32x2x2;
typedef struct { CCSimd_s32x2 v[3]; } CCSimd_s32x2x3;
typedef struct { CCSimd_s32x2 v[4]; } CCSimd_s32x2x4;

typedef struct { CCSimd_u8x8 v[2]; } CCSimd_u8x8x2;
typedef struct { CCSimd_u8x8 v[3]; } CCSimd_u8x8x3;
typedef struct { CCSimd_u8x8 v[4]; } CCSimd_u8x8x4;
typedef struct { CCSimd_u16x4 v[2]; } CCSimd_u16x4x2;
typedef struct { CCSimd_u16x4 v[3]; } CCSimd_u16x4x3;
typedef struct { CCSimd_u16x4 v[4]; } CCSimd_u16x4x4;
typedef struct { CCSimd_u32x2 v[2]; } CCSimd_u32x2x2;
typedef struct { CCSimd_u32x2 v[3]; } CCSimd_u32x2x3;
typedef struct { CCSimd_u32x2 v[4]; } CCSimd_u32x2x4;

typedef struct { CCSimd_f32x2 v[2]; } CCSimd_f32x2x2;
typedef struct { CCSimd_f32x2 v[3]; } CCSimd_f32x2x3;
typedef struct { CCSimd_f32x2 v[4]; } CCSimd_f32x2x4;


#pragma mark - Setting and Getting
#pragma mark Zero

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdZero_s8x8(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdZero_s16x4(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdZero_s32x2(void);


/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdZero_u8x8(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdZero_u16x4(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdZero_u32x2(void);

/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdZero_f32x2(void);


#pragma mark Fill

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdFill_s8x8(const int8_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdFill_s16x4(const int16_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdFill_s32x2(const int32_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdFill_u8x8(const uint8_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdFill_u16x4(const uint16_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdFill_u32x2(const uint32_t v);

/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdFill_f32x2(const float v);


#pragma mark Load

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdLoad_s8x8(const int8_t v[8]);

/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdLoad_s16x4(const int16_t v[4]);

/*!
 * @brief Load a vector from memory.
 * @param v A pointer to the data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdLoad_s32x2(const int32_t v[2]);

/*!
 * @brief Load a vector from memory.
 * @param v A pointer to the data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdLoad_u8x8(const uint8_t v[8]);

/*!
 * @brief Load a vector from memory.
 * @param v A pointer to the data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdLoad_u16x4(const uint16_t v[4]);

/*!
 * @brief Load a vector from memory.
 * @param v A pointer to the data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdLoad_u32x2(const uint32_t v[2]);

/*!
 * @brief Load a vector from memory.
 * @param v A pointer to the data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdLoad_f32x2(const float v[2]);


#pragma mark Store

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src An 8 element vector of 8-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s8x8(int8_t dst[8], const CCSimd_s8x8 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 4 element vector of 16-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s16x4(int16_t dst[4], const CCSimd_s16x4 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 2 element vector of 32-bit signed integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_s32x2(int32_t dst[2], const CCSimd_s32x2 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src An 8 element vector of 8-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u8x8(uint8_t dst[8], const CCSimd_u8x8 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 4 element vector of 16-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u16x4(uint16_t dst[4], const CCSimd_u16x4 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 2 element vector of 32-bit unsigned integers to store.
 */
static CC_FORCE_INLINE void CCSimdStore_u32x2(uint32_t dst[2], const CCSimd_u32x2 src);

/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src A 2 element vector of 32-bit floats to store.
 */
static CC_FORCE_INLINE void CCSimdStore_f32x2(float dst[2], const CCSimd_f32x2 src);


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
static CC_FORCE_INLINE CCSimd_s8x8x2 CCSimdInterleaveLoad_s8x8x2(const int8_t v[16]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x4x2 CCSimdInterleaveLoad_s16x4x2(const int16_t v[8]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x2x2 CCSimdInterleaveLoad_s32x2x2(const int32_t v[4]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x8x2 CCSimdInterleaveLoad_u8x8x2(const uint8_t v[16]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x4x2 CCSimdInterleaveLoad_u16x4x2(const uint16_t v[8]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x2x2 CCSimdInterleaveLoad_u32x2x2(const uint32_t v[4]);

/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x2x2 CCSimdInterleaveLoad_f32x2x2(const float v[4]);


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
static CC_FORCE_INLINE CCSimd_s8x8x3 CCSimdInterleaveLoad_s8x8x3(const int8_t v[24]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x4x3 CCSimdInterleaveLoad_s16x4x3(const int16_t v[12]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x2x3 CCSimdInterleaveLoad_s32x2x3(const int32_t v[6]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x8x3 CCSimdInterleaveLoad_u8x8x3(const uint8_t v[24]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x4x3 CCSimdInterleaveLoad_u16x4x3(const uint16_t v[12]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x2x3 CCSimdInterleaveLoad_u32x2x3(const uint32_t v[6]);

/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x2x3 CCSimdInterleaveLoad_f32x2x3(const float v[6]);


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
static CC_FORCE_INLINE CCSimd_s8x8x4 CCSimdInterleaveLoad_s8x8x4(const int8_t v[32]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s16x4x4 CCSimdInterleaveLoad_s16x4x4(const int16_t v[16]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_s32x2x4 CCSimdInterleaveLoad_s32x2x4(const int32_t v[8]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u8x8x4 CCSimdInterleaveLoad_u8x8x4(const uint8_t v[32]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u16x4x4 CCSimdInterleaveLoad_u16x4x4(const uint16_t v[16]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_u32x2x4 CCSimdInterleaveLoad_u32x2x4(const uint32_t v[8]);

/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_f32x2x4 CCSimdInterleaveLoad_f32x2x4(const float v[8]);


#pragma mark Interleaved Stores
#pragma mark 2 Vector Interleaved Store

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s8x8x2(int8_t dst[16], const CCSimd_s8x8x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s16x4x2(int16_t dst[8], const CCSimd_s16x4x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit signed integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s32x2x2(int32_t dst[4], const CCSimd_s32x2x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 8-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u8x8x2(uint8_t dst[16], const CCSimd_u8x8x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 16-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u16x4x2(uint16_t dst[8], const CCSimd_u16x4x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit unsigned integers to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u32x2x2(uint32_t dst[4], const CCSimd_u32x2x2 src);

/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit floats to store. Every poly  vector[index % 2]
 *            will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f32x2x2(float dst[4], const CCSimd_f32x2x2 src);


#pragma mark 3 Vector Interleaved Store

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s8x8x3(int8_t dst[24], const CCSimd_s8x8x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s16x4x3(int16_t dst[12], const CCSimd_s16x4x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit signed integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s32x2x3(int32_t dst[6], const CCSimd_s32x2x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 8-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u8x8x3(uint8_t dst[24], const CCSimd_u8x8x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 16-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u16x4x3(uint16_t dst[12], const CCSimd_u16x4x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit unsigned integers to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u32x2x3(uint32_t dst[6], const CCSimd_u32x2x3 src);

/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit floats to store. Every poly vector[index % 3]
 *            will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f32x2x3(float dst[6], const CCSimd_f32x2x3 src);


#pragma mark 3 Vector Interleaved Store

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s8x8x4(int8_t dst[32], const CCSimd_s8x8x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s16x4x4(int16_t dst[16], const CCSimd_s16x4x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_s32x2x4(int32_t dst[8], const CCSimd_s32x2x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 8 element vectors of 8-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u8x8x4(uint8_t dst[32], const CCSimd_u8x8x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 4 element vectors of 16-bit signed integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u16x4x4(uint16_t dst[16], const CCSimd_u16x4x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit unsigned integers to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_u32x2x4(uint32_t dst[8], const CCSimd_u32x2x4 src);

/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two 2 element vectors of 32-bit floats to store. Every poly vector[index % 4]
 *            will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_f32x2x4(float dst[8], const CCSimd_f32x2x4 src);


#pragma mark Get Element

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 8 element vector of 8-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int8_t CCSimdGet_s8x8(const CCSimd_s8x8 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 4 element vector of 16-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int16_t CCSimdGet_s16x4(const CCSimd_s16x4 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 2 element vector of 32-bit signed integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE int32_t CCSimdGet_s32x2(const CCSimd_s32x2 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 8 element vector of 8-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint8_t CCSimdGet_u8x8(const CCSimd_u8x8 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 4 element vector of 16-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint16_t CCSimdGet_u16x4(const CCSimd_u16x4 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 2 element vector of 32-bit unsigned integers.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE uint32_t CCSimdGet_u32x2(const CCSimd_u32x2 a, uint8_t index);

/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The 2 element vector of 32-bit floats.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE float CCSimdGet_f32x2(const CCSimd_f32x2 a, uint8_t index);


#pragma mark Set Element

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 8 element vector of 8-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdSet_s8x8(const CCSimd_s8x8 a, uint8_t index, int8_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 4 element vector of 16-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdSet_s16x4(const CCSimd_s16x4 a, uint8_t index, int16_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 2 element vector of 32-bit signed integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdSet_s32x2(const CCSimd_s32x2 a, uint8_t index, int32_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 8 element vector of 8-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdSet_u8x8(const CCSimd_u8x8 a, uint8_t index, uint8_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 4 element vector of 16-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdSet_u16x4(const CCSimd_u16x4 a, uint8_t index, uint16_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 2 element vector of 32-bit unsigned integers.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdSet_u32x2(const CCSimd_u32x2 a, uint8_t index, uint32_t v);

/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The 2 element vector of 32-bit floats.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSet_f32x2(const CCSimd_f32x2 a, uint8_t index, float v);


#pragma mark Set Sequence

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 8 element vector of 8-bit signed integers.
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
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdSetSequence_s8x8(const CCSimd_s8x8 a, int8_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 4 element vector of 16-bit signed integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdSetSequence_s16x4(const CCSimd_s16x4 a, int16_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 2 element vector of 32-bit signed integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdSetSequence_s32x2(const CCSimd_s32x2 a, int32_t v, _Bool v0, _Bool v1);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 8 element vector of 8-bit unsigned integers.
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
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdSetSequence_u8x8(const CCSimd_u8x8 a, uint8_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 4 element vector of 16-bit unsigned integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @param v2 Whether the element should be set (1) or not (0).
 * @param v3 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdSetSequence_u16x4(const CCSimd_u16x4 a, uint16_t v, _Bool v0, _Bool v1, _Bool v2, _Bool v3);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 2 element vector of 32-bit unsigned integers.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdSetSequence_u32x2(const CCSimd_u32x2 a, uint32_t v, _Bool v0, _Bool v1);

/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The 2 element vector of 32-bit floats.
 * @param v The value to set the elements to.
 * @param v0 Whether the element should be set (1) or not (0).
 * @param v1 Whether the element should be set (1) or not (0).
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSetSequence_f32x2(const CCSimd_f32x2 a, float v, _Bool v0, _Bool v1);


#pragma mark - Types
#pragma mark Reinterpret

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Reinterpret_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Reinterpret_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Reinterpret_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Reinterpret_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Reinterpret_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Reinterpret_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Reinterpret the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Reinterpret_f32x2(const CCSimd_f32x2 a);


#pragma mark Cast

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Cast_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Cast_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Cast_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 4 element vector of 16-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Cast_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Cast_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Cast_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit signed integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Cast_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimd_s8x8_Cast_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimd_u8x8_Cast_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimd_s16x4_Cast_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 4 element vector of 16-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimd_u16x4_Cast_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Cast_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Cast_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit unsigned integers.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Cast_u32x2(const CCSimd_u32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimd_s32x2_Cast_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimd_u32x2_Cast_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Cast the vector @b a.
 * @param a An 2 element vector of 32-bit floats.
 * @return The Casted vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimd_f32x2_Cast_f32x2(const CCSimd_f32x2 a);


#pragma mark - Bitwise Operations
#pragma mark Not

/*!
 * @brief NOT all elements of @b a.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] -> [-2, -2, -2, -2, -2, -2, -2, -2]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdNot_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief NOT all elements of @b a.
 * @example [1, 1, 1, 1] -> [-2, -2, -2, -2]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdNot_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief NOT all elements of @b a.
 * @example [1, 1] -> [-2, -2]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdNot_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief NOT all elements of @b a.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] -> [-2, -2, -2, -2, -2, -2, -2, -2]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdNot_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief NOT all elements of @b a.
 * @example [1, 1, 1, 1] -> [-2, -2, -2, -2]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdNot_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief NOT all elements of @b a.
 * @example [1, 1] -> [-2, -2]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdNot_u32x2(const CCSimd_u32x2 a);


#pragma mark And

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdAnd_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1] & [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdAnd_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1] & [3, 3] -> [1, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdAnd_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdAnd_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1, 1, 1] & [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdAnd_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief AND all elements of @b a and @b b.
 * @example [1, 1] & [3, 3] -> [1, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdAnd_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark And Not

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdAndNot_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] & [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdAndNot_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1] & [3, 3] -> [2, 2]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdAndNot_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] & [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdAndNot_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] & [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdAndNot_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief AND all elements of NOT @b a and @b b.
 * @example ~[1, 1] & [3, 3] -> [2, 2]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdAndNot_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Or

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [3, 3, 3, 3, 3, 3, 3, 3]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdOr_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] | [2, 2, 2, 2] -> [3, 3, 3, 3]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdOr_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1] | [2, 2] -> [3, 3]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdOr_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [3, 3, 3, 3, 3, 3, 3, 3]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdOr_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] | [2, 2, 2, 2] -> [3, 3, 3, 3]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdOr_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief OR all elements of @b a and @b b.
 * @example [1, 1] | [2, 2] -> [3, 3]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdOr_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Or Not

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [-1, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdOrNot_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] | [2, 2, 2, 2] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdOrNot_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1] | [2, 2] -> [-1, -1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdOrNot_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1, 1, 1, 1, 1] | [2, 2, 2, 2, 2, 2, 2, 2] -> [-1, -1, -1, -1, -1, -1, -1, -1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdOrNot_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1, 1, 1] | [2, 2, 2, 2] -> [-1, -1, -1, -1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdOrNot_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief OR all elements of NOT @b a and @b b.
 * @example ~[1, 1] | [2, 2] -> [-1, -1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdOrNot_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Xor

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] ^ [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdXor_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] ^ [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdXor_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1] ^ [3, 3] -> [2, 2]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdXor_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] ^ [3, 3, 3, 3, 3, 3, 3, 3] -> [2, 2, 2, 2, 2, 2, 2, 2]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdXor_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1, 1, 1] ^ [3, 3, 3, 3] -> [2, 2, 2, 2]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdXor_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief XOR all elements of @b a and @b b.
 * @example [1, 1] ^ [3, 3] -> [2, 2]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdXor_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Shift Left

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdShiftLeft_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1] << [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdShiftLeft_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1] << [3, 3] -> [8, 8]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdShiftLeft_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdShiftLeft_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1, 1, 1] << [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdShiftLeft_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Left shift all elements of @b a by @b b.
 * @example [1, 1] << [3, 3] -> [8, 8]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdShiftLeft_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Shift Left N

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdShiftLeftN_s8x8(const CCSimd_s8x8 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1] << 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdShiftLeftN_s16x4(const CCSimd_s16x4 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1] << 3 -> [8, 8]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdShiftLeftN_s32x2(const CCSimd_s32x2 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] << 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdShiftLeftN_u8x8(const CCSimd_u8x8 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1, 1, 1] << 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdShiftLeftN_u16x4(const CCSimd_u16x4 a, const uint8_t n);

/*!
 * @brief Left shift all elements of @b a by @b n.
 * @example [1, 1] << 3 -> [8, 8]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdShiftLeftN_u32x2(const CCSimd_u32x2 a, const uint8_t n);


#pragma mark Shift Right

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param b An 8 element vector of 8-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdShiftRight_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8] >> [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param b A 4 element vector of 16-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdShiftRight_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b b.
 * @example [8, 8] >> [3, 3] -> [1, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param b A 2 element vector of 32-bit signed integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdShiftRight_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdShiftRight_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8, 8, 8] >> [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdShiftRight_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Right shift all elements of @b a by @b b.
 * @example [8, 8] >> [3, 3] -> [1, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdShiftRight_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Shift Right N

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdShiftRightN_s8x8(const CCSimd_s8x8 a, const uint8_t n);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8] >> 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdShiftRightN_s16x4(const CCSimd_s16x4 a, const uint8_t n);

/*!
 * @brief Right arithmetic shift all elements of @b a by @b n.
 * @example [8, 8] >> 3 -> [1, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdShiftRightN_s32x2(const CCSimd_s32x2 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] >> 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdShiftRightN_u8x8(const CCSimd_u8x8 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8, 8, 8] >> 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdShiftRightN_u16x4(const CCSimd_u16x4 a, const uint8_t n);

/*!
 * @brief Right shift all elements of @b a by @b n.
 * @example [8, 8] >> 3 -> [1, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdShiftRightN_u32x2(const CCSimd_u32x2 a, const uint8_t n);


#pragma mark Rotate Left

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] rol [3, 3, 3, 3, 3, 3, 3, 3] -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdRotateLeft_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1, 1, 1] rol [3, 3, 3, 3] -> [8, 8, 8, 8]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdRotateLeft_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Left rotate all elements of @b a by @b b.
 * @example [1, 1] rol [3, 3] -> [8, 8]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdRotateLeft_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Rotate Left N

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1, 1, 1, 1, 1] rol 3 -> [8, 8, 8, 8, 8, 8, 8, 8]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdRotateLeftN_u8x8(const CCSimd_u8x8 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1, 1, 1] rol 3 -> [8, 8, 8, 8]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdRotateLeftN_u16x4(const CCSimd_u16x4 a, const uint8_t n);

/*!
 * @brief Left rotate all elements of @b a by @b n.
 * @example [1, 1] rol 3 -> [8, 8]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdRotateLeftN_u32x2(const CCSimd_u32x2 a, const uint8_t n);


#pragma mark Rotate Right

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] ror [3, 3, 3, 3, 3, 3, 3, 3] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param b An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdRotateRight_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8, 8, 8] ror [3, 3, 3, 3] -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param b A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdRotateRight_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Right rotate all elements of @b a by @b b.
 * @example [8, 8] ror [3, 3] -> [1, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param b A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdRotateRight_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);


#pragma mark Rotate Right N

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8, 8, 8, 8, 8] ror 3 -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdRotateRightN_u8x8(const CCSimd_u8x8 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8, 8, 8] ror 3 -> [1, 1, 1, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdRotateRightN_u16x4(const CCSimd_u16x4 a, const uint8_t n);

/*!
 * @brief Right rotate all elements of @b a by @b n.
 * @example [8, 8] ror 3 -> [1, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @param n The number of bits to roate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdRotateRightN_u32x2(const CCSimd_u32x2 a, const uint8_t n);


#pragma mark - Bit Maths
#pragma mark Lowest Unset Bits

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdLowestUnset_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdLowestUnset_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2] -> [2, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdLowestUnset_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdLowestUnset_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2, 1, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdLowestUnset_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 * @example [1, 2] -> [2, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdLowestUnset_u32x2(const CCSimd_u32x2 a);


#pragma mark Lowest Set Bits

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdLowestSet_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [1, 2, 1, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdLowestSet_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [1, 2] -> [2, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdLowestSet_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [1, 2, 1, 2, 1, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdLowestSet_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [1, 2, 1, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdLowestSet_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Finds lowest set bit of all elements of @b a.
 * @example [1, 2] -> [2, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdLowestSet_u32x2(const CCSimd_u32x2 a);


#pragma mark Highest Set Bits

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1, 3, 1] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdHighestSet_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdHighestSet_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1] -> [2, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdHighestSet_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1, 3, 1] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdHighestSet_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1, 3, 1] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdHighestSet_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Finds highest set bit of all elements of @b a.
 * @example [3, 1] -> [2, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdHighestSet_u32x2(const CCSimd_u32x2 a);


#pragma mark Next Power of 2

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1, 3, 1] -> [4, 1, 4, 1, 4, 1, 4, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdNextPow2_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1] -> [4, 1, 4, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdNextPow2_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1] -> [4, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdNextPow2_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1, 3, 1] -> [4, 1, 4, 1, 4, 1, 4, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdNextPow2_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1, 3, 1] -> [4, 1, 4, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdNextPow2_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 * @example [3, 1] -> [4, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdNextPow2_u32x2(const CCSimd_u32x2 a);


#pragma mark Mask Value

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1, 2, 1] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMask_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMask_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1] -> [3, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMask_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1, 2, 1] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMask_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1, 2, 1] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMask_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 * @example [2, 1] -> [3, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMask_u32x2(const CCSimd_u32x2 a);


#pragma mark Mask Lower Power of 2

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2, 4, 2] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskLowerPow2_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskLowerPow2_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2] -> [3, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskLowerPow2_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2, 4, 2] -> [3, 1, 3, 1, 3, 1, 3, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskLowerPow2_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2, 4, 2] -> [3, 1, 3, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskLowerPow2_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 * @example [4, 2] -> [3, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskLowerPow2_u32x2(const CCSimd_u32x2 a);


#pragma mark Mask Highest Unset Value

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2, 1, 2] -> [-2, -4, -2, -4, -2, -4, -2, -4]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskHighestUnset_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2] -> [-2, -4, -2, -4]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskHighestUnset_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2] -> [-2, -4]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskHighestUnset_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2, 1, 2] -> [-2, -4, -2, -4, -2, -4, -2, -4]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskHighestUnset_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2, 1, 2] -> [-2, -4, -2, -4]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskHighestUnset_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 * @example [1, 2] -> [-2, -4]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskHighestUnset_u32x2(const CCSimd_u32x2 a);


#pragma mark Count Trailing Zero Bits

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [0, 1, 0, 2, 0, 1, 0, 3]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCountLowestUnset_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [0, 1, 0, 2]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCountLowestUnset_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2] -> [0, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCountLowestUnset_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [0, 1, 0, 2, 0, 1, 0, 3]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCountLowestUnset_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [0, 1, 0, 2]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCountLowestUnset_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 * @example [1, 2] -> [0, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCountLowestUnset_u32x2(const CCSimd_u32x2 a);


#pragma mark Count Leading Zero Bits

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [31, 30, 30, 29, 29, 29, 29, 28]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCountHighestUnset_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [31, 30, 30, 29]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCountHighestUnset_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2] -> [31, 30]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCountHighestUnset_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] -> [31, 30, 30, 29, 29, 29, 29, 28]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCountHighestUnset_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2, 3, 4] -> [31, 30, 30, 29]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCountHighestUnset_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Count the leading zero bits of all elements of @b a.
 * @example [1, 2] -> [31, 30]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCountHighestUnset_u32x2(const CCSimd_u32x2 a);


#pragma mark Count Set Bits

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2, 3, 2, 3, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCountSet_s8x8(const CCSimd_s8x8 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCountSet_s16x4(const CCSimd_s16x4 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2] -> [2, 1]
 * @param a A 2 element vector of 32-bit signed integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCountSet_s32x2(const CCSimd_s32x2 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2, 3, 2, 3, 2] -> [2, 1, 2, 1, 2, 1, 2, 1]
 * @param a An 8 element vector of 8-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCountSet_u8x8(const CCSimd_u8x8 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2, 3, 2] -> [2, 1, 2, 1]
 * @param a A 4 element vector of 16-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCountSet_u16x4(const CCSimd_u16x4 a);

/*!
 * @brief Count the set bits of all elements of @b a.
 * @example [3, 2] -> [2, 1]
 * @param a A 2 element vector of 32-bit unsigned integers.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCountSet_u32x2(const CCSimd_u32x2 a);


#pragma mark - Comparisons
#pragma mark Equal

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, 1, 0, 1, 0, 1, 0, 1]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCompareEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [5, 6, 7, 8] == [0, 6, 0, 8] -> [0, 1, 0, 1]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCompareEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [7, 8] == [0, 8] -> [0, 1]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCompareEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, 1, 0, 1, 0, 1, 0, 1]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCompareEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [5, 6, 7, 8] == [0, 6, 0, 8] -> [0, 1, 0, 1]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCompareEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [7, 8] == [0, 8] -> [0, 1]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCompareEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [7.5, 8.5] == [0.0, 8.5] -> [0.0, 1.0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCompareEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Masked Equal

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, -1, 0, -1, 0, -1, 0, -1]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskCompareEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [5, 6, 7, 8] == [0, 6, 0, 8] -> [0, -1, 0, -1]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskCompareEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [7, 8] == [0, 8] -> [0, -1]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskCompareEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] == [0, 2, 0, 4, 0, 6, 0, 8] -> [0, -1, 0, -1, 0, -1, 0, -1]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskCompareEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [5, 6, 7, 8] == [0, 6, 0, 8] -> [0, -1, 0, -1]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskCompareEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [7, 8] == [0, 8] -> [0, -1]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 * @example [7.5, 8.5] == [0.0, 8.5] -> [0, -1]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Not Equal

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCompareNotEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [5, 6, 7, 8] != [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCompareNotEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [7, 8] != [0, 8] -> [1. 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCompareNotEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCompareNotEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [5, 6, 7, 8] != [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCompareNotEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [7, 8] != [0, 8] -> [1. 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCompareNotEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [7.5, 8.5] != [0.0, 8.5] -> [1.0, 0.0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCompareNotEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Masked Not Equal

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskCompareNotEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [5, 6, 7, 8] != [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskCompareNotEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [7, 8] != [0, 8] -> [1. 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskCompareNotEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] != [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskCompareNotEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [5, 6, 7, 8] != [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskCompareNotEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [7, 8] != [0, 8] -> [1. 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareNotEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 * @example [7.5, 8.5] != [0.0, 8.5] -> [-1, 0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareNotEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Less Than

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] < [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCompareLessThan_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [5, 6, 7, 8] < [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCompareLessThan_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [7, 8] < [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCompareLessThan_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] < [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCompareLessThan_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [5, 6, 7, 8] < [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCompareLessThan_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [7, 8] < [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCompareLessThan_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [7.5, 8.5] < [10.0, 8.5] -> [1.0, 0.0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCompareLessThan_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Masked Less Than

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] < [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskCompareLessThan_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [5, 6, 7, 8] < [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskCompareLessThan_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [7, 8] < [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskCompareLessThan_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] < [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskCompareLessThan_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [5, 6, 7, 8] < [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskCompareLessThan_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [7, 8] < [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareLessThan_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than @b b.
 * @example [7.5, 8.5] < [10.0, 8.5] -> [-1, 0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareLessThan_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Less Than Or Equal

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] <= [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCompareLessThanEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [5, 6, 7, 8] <= [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCompareLessThanEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [7, 8] <= [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCompareLessThanEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] <= [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCompareLessThanEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [5, 6, 7, 8] <= [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCompareLessThanEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [7, 8] <= [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCompareLessThanEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [7.5, 8.5] <= [10.0, 8.5] -> [1.0, 1.0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCompareLessThanEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Masked Less Than Or Equal

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] <= [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskCompareLessThanEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [5, 6, 7, 8] <= [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskCompareLessThanEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [7, 8] <= [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskCompareLessThanEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] <= [10, 2, 10, 4, 10, 6, 10, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskCompareLessThanEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [5, 6, 7, 8] <= [10, 6, 10, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskCompareLessThanEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [7, 8] <= [10, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareLessThanEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 * @example [7.5, 8.5] <= [10.0, 8.5] -> [-1, -1]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareLessThanEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Greater Than

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCompareGreaterThan_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [5, 6, 7, 8] > [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCompareGreaterThan_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [7, 8] > [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCompareGreaterThan_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCompareGreaterThan_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [5, 6, 7, 8] > [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCompareGreaterThan_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [7, 8] > [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCompareGreaterThan_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [7.5, 8.5] > [0.0, 8.5] -> [1.0, 0.0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCompareGreaterThan_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Masked Greater Than

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskCompareGreaterThan_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [5, 6, 7, 8] > [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskCompareGreaterThan_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [7, 8] > [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskCompareGreaterThan_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] > [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 0, 1, 0, 1, 0, 1, 0]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskCompareGreaterThan_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [5, 6, 7, 8] > [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskCompareGreaterThan_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [7, 8] > [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareGreaterThan_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 * @example [7.5, 8.5] > [0.0, 8.5] -> [-1, 0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareGreaterThan_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Greater Than Or Equal

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdCompareGreaterThanEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [5, 6, 7, 8] >= [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdCompareGreaterThanEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [7, 8] >= [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdCompareGreaterThanEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdCompareGreaterThanEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [5, 6, 7, 8] >= [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdCompareGreaterThanEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [7, 8] >= [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdCompareGreaterThanEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [7.5, 8.5] >= [0.0, 8.5] -> [1.0, 1.0]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCompareGreaterThanEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


#pragma mark Masked Greater Than Or Equal

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit signed integers to compare.
 * @param b An 8 element vector of 8-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdMaskCompareGreaterThanEqual_s8x8(const CCSimd_s8x8 a, const CCSimd_s8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [5, 6, 7, 8] >= [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit signed integers to compare.
 * @param b A 4 element vector of 16-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdMaskCompareGreaterThanEqual_s16x4(const CCSimd_s16x4 a, const CCSimd_s16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [7, 8] >= [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit signed integers to compare.
 * @param b A 2 element vector of 32-bit signed integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdMaskCompareGreaterThanEqual_s32x2(const CCSimd_s32x2 a, const CCSimd_s32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [1, 2, 3, 4, 5, 6, 7, 8] >= [0, 2, 0, 4, 0, 6, 0, 8] -> [1, 1, 1, 1, 1, 1, 1, 1]
 * @param a An 8 element vector of 8-bit unsigned integers to compare.
 * @param b An 8 element vector of 8-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdMaskCompareGreaterThanEqual_u8x8(const CCSimd_u8x8 a, const CCSimd_u8x8 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [5, 6, 7, 8] >= [0, 6, 0, 8] -> [1, 0, 1, 0]
 * @param a A 4 element vector of 16-bit unsigned integers to compare.
 * @param b A 4 element vector of 16-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdMaskCompareGreaterThanEqual_u16x4(const CCSimd_u16x4 a, const CCSimd_u16x4 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [7, 8] >= [0, 8] -> [1, 0]
 * @param a A 2 element vector of 32-bit unsigned integers to compare.
 * @param b A 2 element vector of 32-bit unsigned integers to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareGreaterThanEqual_u32x2(const CCSimd_u32x2 a, const CCSimd_u32x2 b);

/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 * @example [7.5, 8.5] >= [0.0, 8.5] -> [-1, -1]
 * @param a A 2 element vector of 32-bit floats to compare.
 * @param b A 2 element vector of 32-bit floats to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdMaskCompareGreaterThanEqual_f32x2(const CCSimd_f32x2 a, const CCSimd_f32x2 b);


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


#pragma mark Square Root

/*!
 * @brief Compute the square root of each element in the vector.
 * @param a A 2 element vector of 32-bit floats to get the square root of.
 * @return The square root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSqrt_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the reciprocal square root of each element in the vector.
 * @param a A 2 element vector of 32-bit floats to get the inverse square root of.
 * @return The inverse square root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdInvSqrt_f32x2(const CCSimd_f32x2 a);


#pragma mark Cube Root

/*!
 * @brief Compute the cube root of each element in the vector.
 * @param a A 2 element vector of 32-bit floats to get the cube root of.
 * @return The cube root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCbrt_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the reciprocal cube root of each element in the vector.
 * @param a A 2 element vector of 32-bit floats to get the inverse cube root of.
 * @return The inverse cube root vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdInvCbrt_f32x2(const CCSimd_f32x2 a);


#pragma mark Power

/*!
 * @brief Compute value of each element in the vector @b Base raised by vector @b Exponent.
 * @param Base A 2 element vector of 32-bit floats to raised.
 * @param Exponent A 2 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPow_f32x2(const CCSimd_f32x2 Base, const CCSimd_f32x2 Exponent);


#pragma mark 2 Power

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 8 element vector of 8-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s8x8 CCSimdPow2_s8x8(const CCSimd_s8x8 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 4 element vector of 16-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s16x4 CCSimdPow2_s16x4(const CCSimd_s16x4 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 2 element vector of 32-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_s32x2 CCSimdPow2_s32x2(const CCSimd_s32x2 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 8 element vector of 8-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u8x8 CCSimdPow2_u8x8(const CCSimd_u8x8 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 4 element vector of 16-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u16x4 CCSimdPow2_u16x4(const CCSimd_u16x4 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 2 element vector of 32-bit unsigned integers to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_u32x2 CCSimdPow2_u32x2(const CCSimd_u32x2 Exponent);

/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent A 2 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPow2_f32x2(const CCSimd_f32x2 Exponent);


#pragma mark Exponent

/*!
 * @brief Computes e^n (Euler's number 2.7182818..) for each element raised by vector @b a.
 * @param a A 2 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdExp_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Computes 2^n for each element raised by vector @b a.
 * @param a A 2 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdExp2_f32x2(const CCSimd_f32x2 a);


#pragma mark Logarithm

/*!
 * @brief Computes base e logarithm for each element in vector @b a.
 * @param a A 2 element vector of 32-bit floats to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdLog_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Computes base 2 logarithm for each element in vector @b a.
 * @param a A 2 element vector of 32-bit floats to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdLog2_f32x2(const CCSimd_f32x2 a);


#pragma mark Sine

/*!
 * @brief Compute the sine of each radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the sine of each positive radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the sine of each -pi to pi (-180° to 180°) radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPiRadSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the sine of each 0 to pi (0° to 180°) radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosPiRadSin_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the arc sine of each element in the vector.
 * @param a A 2 element vector of 32-bit float.
 * @return The arc sine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcSin_f32x2(const CCSimd_f32x2 a);

#pragma mark Cosine

/*!
 * @brief Compute the cosine of each -pi/2 to pi/2 (-90° to 90°) radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdHalfPiRadCos_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the cosine of each radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCos_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the arc cosine of each element in the vector.
 * @param a A 2 element vector of 32-bit float.
 * @return The arc cosine vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcCos_f32x2(const CCSimd_f32x2 a);


#pragma mark Tangent

/*!
 * @brief Compute the tangent of each radian element in the vector.
 * @param a A 2 element vector of 32-bit floats to be tanned.
 * @return The tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdTan_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the arc tangent of each -tan(pi/4) to tan(pi/4) (-1 to 1) element in the vector.
 * @param a A 2 element vector of 32-bit float.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdQtrPiArcTan_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the arc tangent of each element in the vector.
 * @param a A 2 element vector of 32-bit float.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcTan_f32x2(const CCSimd_f32x2 a);

/*!
 * @brief Compute the arc tangent of y / x of each element in the vector.
 * @note When @b CC_SIMD_ARCTAN2_PRINCIPAL is defined the range (-pi, pi] is used, otherwise the default
 *       uses [-pi, pi]. By default when x and y are 0 the result is undefined, if @b CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO
 *       is defined 0.0 is returned, or @b CC_SIMD_ARCTAN2_UNDEFINED can be defined to the desired return value.
 *
 * @param y A 2 element vector of 32-bit float.
 * @param x A 2 element vector of 32-bit float.
 * @return The arc tangent vector of y / x.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcTan2_f32x2(const CCSimd_f32x2 y, const CCSimd_f32x2 x);


#pragma mark Cosecant

/*!
 * @brief Compute the cosecant (reciprocal sine) of each radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The cosecant vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCsc_f32x2(const CCSimd_f32x2 a);


#pragma mark Secant

/*!
 * @brief Compute the secant (reciprocal cosine) of each radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The secant vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSec_f32x2(const CCSimd_f32x2 a);


#pragma mark Cotangent

/*!
 * @brief Compute the cotangent (reciprocal tangent) of each radian element in the vector.
 * @param a A 2 element vector of 32-bit float radians.
 * @return The cotangent vector.
 */
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCot_f32x2(const CCSimd_f32x2 a);


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

#undef CC_SIMD_MISSING_CCSimdZero
#undef CC_SIMD_MISSING_CCSimdSetSequence
#undef CC_SIMD_MISSING_CCSimdAndNot
#undef CC_SIMD_MISSING_CCSimdRotateLeft
#undef CC_SIMD_MISSING_CCSimdRotateLeftN
#undef CC_SIMD_MISSING_CCSimdRotateRight
#undef CC_SIMD_MISSING_CCSimdRotateRightN
#undef CC_SIMD_MISSING_CCSimdLowestUnset
#undef CC_SIMD_MISSING_CCSimdLowestSet
#undef CC_SIMD_MISSING_CCSimdHighestSet
#undef CC_SIMD_MISSING_CCSimdNextPow2
#undef CC_SIMD_MISSING_CCSimdMask
#undef CC_SIMD_MISSING_CCSimdMaskLowerPow2
#undef CC_SIMD_MISSING_CCSimdMaskHighestUnset
#undef CC_SIMD_MISSING_CCSimdCountLowestUnset
#undef CC_SIMD_MISSING_CCSimdCountSet
#undef CC_SIMD_MISSING_CCSimdCompareEqual
#undef CC_SIMD_MISSING_CCSimdCompareNotEqual
#undef CC_SIMD_MISSING_CCSimdCompareLessThan
#undef CC_SIMD_MISSING_CCSimdCompareLessThanEqual
#undef CC_SIMD_MISSING_CCSimdCompareGreaterThan
#undef CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual
#undef CC_SIMD_MISSING_CCSimdMaskCompareNotEqual
#undef CC_SIMD_MISSING_CCSimdMadd
#undef CC_SIMD_MISSING_CCSimdNegMadd
#undef CC_SIMD_MISSING_CCSimdMsub
#undef CC_SIMD_MISSING_CCSimdNegMsub
#undef CC_SIMD_MISSING_CCSimdDiv
#undef CC_SIMD_MISSING_CCSimdMod
#undef CC_SIMD_MISSING_CCSimdHadd
#undef CC_SIMD_MISSING_CCSimdHsub
#undef CC_SIMD_MISSING_CCSimdDot
#undef CC_SIMD_MISSING_CCSimdClamp

#undef CC_SIMD_MISSING_CCSimdPosPiRadSin_f32x2
#undef CC_SIMD_MISSING_CCSimdHalfPiRadCos_f32x2
#undef CC_SIMD_MISSING_CCSimdPosSin_f32x2
#undef CC_SIMD_MISSING_CCSimdPiRadSin_f32x2
#undef CC_SIMD_MISSING_CCSimdSin_f32x2
#undef CC_SIMD_MISSING_CCSimdArcSin_f32x2
#undef CC_SIMD_MISSING_CCSimdCos_f32x2
#undef CC_SIMD_MISSING_CCSimdArcCos_f32x2
#undef CC_SIMD_MISSING_CCSimdTan_f32x2
#undef CC_SIMD_MISSING_CCSimdQtrPiArcTan_f32x2
#undef CC_SIMD_MISSING_CCSimdArcTan_f32x2
#undef CC_SIMD_MISSING_CCSimdArcTan2_f32x2
#undef CC_SIMD_MISSING_CCSimdCsc_f32x2
#undef CC_SIMD_MISSING_CCSimdSec_f32x2
#undef CC_SIMD_MISSING_CCSimdCot_f32x2
#undef CC_SIMD_MISSING_CCSimdLog2_f32x2
#undef CC_SIMD_MISSING_CCSimdLog_f32x2
#undef CC_SIMD_MISSING_CCSimdPow_f32x2
#undef CC_SIMD_MISSING_CCSimdPow2_f32x2
#undef CC_SIMD_MISSING_CCSimdExp_f32x2
#undef CC_SIMD_MISSING_CCSimdExp2_f32x2
#undef CC_SIMD_MISSING_CCSimdCbrt_f32x2
#undef CC_SIMD_MISSING_CCSimdInvCbrt_f32x2

#define CC_SIMD_MISSING_CCSimdZero CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdSetSequence CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdAndNot CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdRotateLeft CC_SIMD_64_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdRotateLeftN CC_SIMD_64_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdRotateRight CC_SIMD_64_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdRotateRightN CC_SIMD_64_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdLowestUnset CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdLowestSet CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdHighestSet CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdNextPow2 CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdMask CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdMaskLowerPow2 CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdMaskHighestUnset CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdCountLowestUnset CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdCountSet CC_SIMD_64_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdCompareEqual CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdCompareNotEqual CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdCompareLessThan CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdCompareLessThanEqual CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdCompareGreaterThan CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdMaskCompareNotEqual CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdMadd CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdNegMadd CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdMsub CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdNegMsub CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdDiv CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdMod CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdHadd CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdHsub CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdDot CC_SIMD_64_TYPES
#define CC_SIMD_MISSING_CCSimdClamp CC_SIMD_64_TYPES

#define CC_SIMD_MISSING_CCSimdPosPiRadSin_f32x2
#define CC_SIMD_MISSING_CCSimdHalfPiRadCos_f32x2
#define CC_SIMD_MISSING_CCSimdPosSin_f32x2
#define CC_SIMD_MISSING_CCSimdPiRadSin_f32x2
#define CC_SIMD_MISSING_CCSimdSin_f32x2
#define CC_SIMD_MISSING_CCSimdArcSin_f32x2
#define CC_SIMD_MISSING_CCSimdCos_f32x2
#define CC_SIMD_MISSING_CCSimdArcCos_f32x2
#define CC_SIMD_MISSING_CCSimdTan_f32x2
#define CC_SIMD_MISSING_CCSimdQtrPiArcTan_f32x2
#define CC_SIMD_MISSING_CCSimdArcTan_f32x2
#define CC_SIMD_MISSING_CCSimdArcTan2_f32x2
#define CC_SIMD_MISSING_CCSimdCsc_f32x2
#define CC_SIMD_MISSING_CCSimdSec_f32x2
#define CC_SIMD_MISSING_CCSimdCot_f32x2
#define CC_SIMD_MISSING_CCSimdLog2_f32x2
#define CC_SIMD_MISSING_CCSimdLog_f32x2
#define CC_SIMD_MISSING_CCSimdPow_f32x2
#define CC_SIMD_MISSING_CCSimdPow2_f32x2
#define CC_SIMD_MISSING_CCSimdExp_f32x2
#define CC_SIMD_MISSING_CCSimdExp2_f32x2
#define CC_SIMD_MISSING_CCSimdCbrt_f32x2
#define CC_SIMD_MISSING_CCSimdInvCbrt_f32x2

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

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) v){ return vdup_n_##base(v); }
CC_SIMD_DECL(CCSimdFill, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) src[count]){ return vld1_##base(src); }
CC_SIMD_DECL(CCSimdLoad, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (CC_SIMD_BASE_TYPE(base) dst[count], const CC_SIMD_TYPE(base, count) src){ vst1_##base(dst, src); }
CC_SIMD_DECL(CCSimdStore, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, n, kind) (const CC_SIMD_BASE_TYPE(base) src[count * n]) \
{ \
    CC_SIMD_INTERNAL_POLY_TYPE(base, count, n) Result = vld##n##_##base((void*)src); \
    return ((CC_SIMD_POLY_TYPE(base, count, n)){ .v = { CC_REPEAT(0, n, CC_SIMD_INTERNAL_POLY_VALUE, Result) } }); \
}
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 2, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 3, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 4, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, n, kind) (CC_SIMD_BASE_TYPE(base) dst[count * n], const CC_SIMD_POLY_TYPE(base, count, n) src) \
{ \
    vst##n##_##base((void*)dst, ((CC_SIMD_INTERNAL_POLY_TYPE(base, count, n)){ .val = { CC_REPEAT(0, n, CC_SIMD_POLY_VALUE, src) } })); \
}
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 2, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 3, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 4, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
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

#define vreinterpret_s8_s8(x) (x)
#define vreinterpret_s16_s16(x) (x)
#define vreinterpret_s32_s32(x) (x)
#define vreinterpret_u8_u8(x) (x)
#define vreinterpret_u16_u16(x) (x)
#define vreinterpret_u32_u32(x) (x)
#define vreinterpret_f32_f32(x) (x)

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_s8_##base(a); }
CC_SIMD_DECL(CCSimd_s8x8_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s8x8), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_s16_##base(a); }
CC_SIMD_DECL(CCSimd_s16x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s16x4), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_s32_##base(a); }
CC_SIMD_DECL(CCSimd_s32x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s32x2), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_u8_##base(a); }
CC_SIMD_DECL(CCSimd_u8x8_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u8x8), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_u16_##base(a); }
CC_SIMD_DECL(CCSimd_u16x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u16x4), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_u32_##base(a); }
CC_SIMD_DECL(CCSimd_u32x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u32x2), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_f32_##base(a); }
CC_SIMD_DECL(CCSimd_f32x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_f32x2), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define vcvt_s8_s8(x) (x)
#define vcvt_s8_u8(x) (x)
#define vcvt_u8_s8(x) (x)
#define vcvt_s16_s16(x) (x)
#define vcvt_s16_u16(x) (x)
#define vcvt_u16_s16(x) (x)
#define vcvt_s32_s32(x) (x)
#define vcvt_s32_u32(x) (x)
#define vcvt_u32_s32(x) (x)
#define vcvt_u8_u8(x) (x)
#define vcvt_u8_s8(x) (x)
#define vcvt_s8_u8(x) (x)
#define vcvt_u16_u16(x) (x)
#define vcvt_u16_s16(x) (x)
#define vcvt_s16_u16(x) (x)
#define vcvt_u32_u32(x) (x)
#define vcvt_u32_s32(x) (x)
#define vcvt_s32_u32(x) (x)
#define vcvt_f32_f32(x) (x)

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_s8_##base(a); }
CC_SIMD_DECL(CCSimd_s8x8_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s8x8), CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_s16_##base(a); }
CC_SIMD_DECL(CCSimd_s16x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s16x4), CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_s32_##base(a); }
CC_SIMD_DECL(CCSimd_s32x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s32x2), CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_u8_##base(a); }
CC_SIMD_DECL(CCSimd_u8x8_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u8x8), CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_u16_##base(a); }
CC_SIMD_DECL(CCSimd_u16x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u16x4), CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_u32_##base(a); }
CC_SIMD_DECL(CCSimd_u32x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u32x2), CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_f32_##base(a); }
CC_SIMD_DECL(CCSimd_f32x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_f32x2), CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vmvn_##base(a); }
CC_SIMD_DECL(CCSimdNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vand_##base(a, b); }
CC_SIMD_DECL(CCSimdAnd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vorr_##base(a, b); }
CC_SIMD_DECL(CCSimdOr, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vorn_##base(a, b); }
CC_SIMD_DECL(CCSimdOrNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return veor_##base(a, b); }
CC_SIMD_DECL(CCSimdXor, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vshl_##base(a, b); }
CC_SIMD_DECL(CCSimdShiftLeft, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshl_n_##base(a, 1); \
        case 2: return vshl_n_##base(a, 2); \
        case 3: return vshl_n_##base(a, 3); \
        case 4: return vshl_n_##base(a, 4); \
        case 5: return vshl_n_##base(a, 5); \
        case 6: return vshl_n_##base(a, 6); \
        case 7: return vshl_n_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshl_n_##base(a, 1); \
        case 2: return vshl_n_##base(a, 2); \
        case 3: return vshl_n_##base(a, 3); \
        case 4: return vshl_n_##base(a, 4); \
        case 5: return vshl_n_##base(a, 5); \
        case 6: return vshl_n_##base(a, 6); \
        case 7: return vshl_n_##base(a, 7); \
        case 8: return vshl_n_##base(a, 8); \
        case 9: return vshl_n_##base(a, 9); \
        case 10: return vshl_n_##base(a, 10); \
        case 11: return vshl_n_##base(a, 11); \
        case 12: return vshl_n_##base(a, 12); \
        case 13: return vshl_n_##base(a, 13); \
        case 14: return vshl_n_##base(a, 14); \
        case 15: return vshl_n_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshl_n_##base(a, 1); \
        case 2: return vshl_n_##base(a, 2); \
        case 3: return vshl_n_##base(a, 3); \
        case 4: return vshl_n_##base(a, 4); \
        case 5: return vshl_n_##base(a, 5); \
        case 6: return vshl_n_##base(a, 6); \
        case 7: return vshl_n_##base(a, 7); \
        case 8: return vshl_n_##base(a, 8); \
        case 9: return vshl_n_##base(a, 9); \
        case 10: return vshl_n_##base(a, 10); \
        case 11: return vshl_n_##base(a, 11); \
        case 12: return vshl_n_##base(a, 12); \
        case 13: return vshl_n_##base(a, 13); \
        case 14: return vshl_n_##base(a, 14); \
        case 15: return vshl_n_##base(a, 15); \
        case 16: return vshl_n_##base(a, 16); \
        case 17: return vshl_n_##base(a, 17); \
        case 18: return vshl_n_##base(a, 18); \
        case 19: return vshl_n_##base(a, 19); \
        case 20: return vshl_n_##base(a, 20); \
        case 21: return vshl_n_##base(a, 21); \
        case 22: return vshl_n_##base(a, 22); \
        case 23: return vshl_n_##base(a, 23); \
        case 24: return vshl_n_##base(a, 24); \
        case 25: return vshl_n_##base(a, 25); \
        case 26: return vshl_n_##base(a, 26); \
        case 27: return vshl_n_##base(a, 27); \
        case 28: return vshl_n_##base(a, 28); \
        case 29: return vshl_n_##base(a, 29); \
        case 30: return vshl_n_##base(a, 30); \
        case 31: return vshl_n_##base(a, 31); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vshl_##base(a, CC_SIMD_NAME(CCSimdNeg, base, count)(b)); }
CC_SIMD_DECL(CCSimdShiftRight, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshr_n_##base(a, 1); \
        case 2: return vshr_n_##base(a, 2); \
        case 3: return vshr_n_##base(a, 3); \
        case 4: return vshr_n_##base(a, 4); \
        case 5: return vshr_n_##base(a, 5); \
        case 6: return vshr_n_##base(a, 6); \
        case 7: return vshr_n_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshr_n_##base(a, 1); \
        case 2: return vshr_n_##base(a, 2); \
        case 3: return vshr_n_##base(a, 3); \
        case 4: return vshr_n_##base(a, 4); \
        case 5: return vshr_n_##base(a, 5); \
        case 6: return vshr_n_##base(a, 6); \
        case 7: return vshr_n_##base(a, 7); \
        case 8: return vshr_n_##base(a, 8); \
        case 9: return vshr_n_##base(a, 9); \
        case 10: return vshr_n_##base(a, 10); \
        case 11: return vshr_n_##base(a, 11); \
        case 12: return vshr_n_##base(a, 12); \
        case 13: return vshr_n_##base(a, 13); \
        case 14: return vshr_n_##base(a, 14); \
        case 15: return vshr_n_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshr_n_##base(a, 1); \
        case 2: return vshr_n_##base(a, 2); \
        case 3: return vshr_n_##base(a, 3); \
        case 4: return vshr_n_##base(a, 4); \
        case 5: return vshr_n_##base(a, 5); \
        case 6: return vshr_n_##base(a, 6); \
        case 7: return vshr_n_##base(a, 7); \
        case 8: return vshr_n_##base(a, 8); \
        case 9: return vshr_n_##base(a, 9); \
        case 10: return vshr_n_##base(a, 10); \
        case 11: return vshr_n_##base(a, 11); \
        case 12: return vshr_n_##base(a, 12); \
        case 13: return vshr_n_##base(a, 13); \
        case 14: return vshr_n_##base(a, 14); \
        case 15: return vshr_n_##base(a, 15); \
        case 16: return vshr_n_##base(a, 16); \
        case 17: return vshr_n_##base(a, 17); \
        case 18: return vshr_n_##base(a, 18); \
        case 19: return vshr_n_##base(a, 19); \
        case 20: return vshr_n_##base(a, 20); \
        case 21: return vshr_n_##base(a, 21); \
        case 22: return vshr_n_##base(a, 22); \
        case 23: return vshr_n_##base(a, 23); \
        case 24: return vshr_n_##base(a, 24); \
        case 25: return vshr_n_##base(a, 25); \
        case 26: return vshr_n_##base(a, 26); \
        case 27: return vshr_n_##base(a, 27); \
        case 28: return vshr_n_##base(a, 28); \
        case 29: return vshr_n_##base(a, 29); \
        case 30: return vshr_n_##base(a, 30); \
        case 31: return vshr_n_##base(a, 31); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vclz_##base(a); }
CC_SIMD_DECL(CCSimdCountHighestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vceq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vceq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vclt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vclt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcle_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcle_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcge_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcge_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
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

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfma_##base(c, a, b); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMadd
#define CC_SIMD_MISSING_CCSimdMadd CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfms_##base(c, a, b); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdNegMadd
#define CC_SIMD_MISSING_CCSimdNegMadd CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfma_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMsub
#define CC_SIMD_MISSING_CCSimdMsub CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfms_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdNegMsub
#define CC_SIMD_MISSING_CCSimdNegMsub CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vdiv_##base(a, b); }
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdDiv
#define CC_SIMD_MISSING_CCSimdDiv CC_SIMD_64_INTEGER_TYPES

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

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vsqrt_##base(a); }
CC_SIMD_DECL(CCSimdSqrt, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrsqrte_##base(a); }
CC_SIMD_DECL(CCSimdInvSqrt, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
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
        case 1: return vzip1_##base(vdup_lane_##base(a, 0), a); \
        case 2: return vuzp1_##base(vdup_lane_##base(a, 0), a); \
        case 3: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 1); \
        case 4: return vzip1_##base(a, vdup_lane_##base(a, 0)); \
        case 5: return vzip1_##base(a, a); \
        case 6: return vext_##base(vdup_lane_##base(a, 0), a, 3); \
        case 7: return vuzp2_##base(vdup_lane_##base(a, 0), a); \
        case 8: return vtrn1_##base(a, vdup_lane_##base(a, 0)); \
        case 9: return vtrn1_##base(a, vzip1_##base(a, a)); \
        case 10: return vtrn1_##base(a, a); \
        case 11: return vcopy_lane_##base(a, 1, a, 0); \
        case 12: return vcopy_lane_##base(vdup_lane_##base(a, 0), 2, a, 3); \
        case 13: return vcopy_lane_##base(vzip1_##base(a, a), 2, a, 3); \
        case 14: return vcopy_lane_##base(vrev32_##base(a), 0, a, 0); \
        case 15: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 2); \
        case 16: return vzip2_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 17: return vreinterpret_##base##_##kind##32(vdup_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0)); \
        case 18: return vcopy_lane_##base(vuzp1_##base(a, a), 1, a, 1); \
        case 19: return vcopy_lane_##base(a, 2, a, 0); \
        case 20: return vzip1_##base(a, vrev32_##base(a)); \
        case 21: return vzip1_##base(a, vdup_lane_##base(a, 1)); \
        case 22: return vzip1_##base(a, vext_##base(a, a, 1)); \
        case 23: return vcopy_lane_##base(a, 2, a, 1); \
        case 24: return vcopy_lane_##base(a, 3, a, 0); \
        case 25: return vcopy_lane_##base(a, 3, a, 1); \
        case 26: return vcopy_lane_##base(a, 3, a, 2); \
        case 27: return a; \
        case 28: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 1)), 0, vreinterpret_##kind##32_##base(a), 0)); \
        case 29: return vcopy_lane_##base(vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1, vreinterpret_##kind##32_##base(a), 0)), 2, a, 3); \
        case 30: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vrev32_##base(a)), 0, vreinterpret_##kind##32_##base(a), 0)); \
        case 31: return vcopy_lane_##base(a, 2, a, 3); \
        case 32: return vuzp1_##base(a, vdup_lane_##base(a, 0)); \
        case 33: return vcopy_lane_##base(vuzp1_##base(a, a), 3, a, 1); \
        case 34: return vuzp1_##base(a, a); \
        case 35: return vzip2_##base(vdup_lane_##base(a, 0), a); \
        case 36: return vcopy_lane_##base(vrev64_##base(a), 0, a, 0); \
        case 37: return vuzp1_##base(a, vdup_lane_##base(a, 1)); \
        case 38: return vzip1_##base(a, vdup_lane_##base(a, 2)); \
        case 39: return vuzp2_##base(vrev32_##base(a), a); \
        case 40: return vuzp1_##base(a, vext_##base(a, a, 2)); \
        case 41: return vcopy_lane_##base(vcopy_lane_##base(a, 1, a, 2), 3, a, 1); \
        case 42: return vuzp1_##base(a, vdup_lane_##base(a, 2)); \
        case 43: return vcopy_lane_##base(a, 1, a, 2); \
        case 44: return vcopy_lane_##base(vext_##base(a, a, 1), 0, a, 0); \
        case 45: return vuzp1_##base(a, vrev64_##base(a)); \
        case 46: return vcopy_lane_##base(vuzp1_##base(a, a), 2, a, 3); \
        case 47: return vuzp1_##base(a, vdup_lane_##base(a, 3)); \
        case 48: return vcopy_lane_##base(vdup_lane_##base(a, 0), 1, a, 3); \
        case 49: return vtrn1_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 50: return vzip1_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 51: return vtrn1_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3)); \
        case 52: return vzip1_##base(a, vext_##base(a, a, 3)); \
        case 53: return vcopy_lane_##base(vzip1_##base(a, a), 1, a, 3); \
        case 54: return vzip1_##base(a, vrev64_##base(a)); \
        case 55: return vzip1_##base(a, vdup_lane_##base(a, 3)); \
        case 56: return vext_##base(vrev32_##base(a), a, 1); \
        case 57: return vext_##base(vrev64_##base(a), vrev64_##base(a), 3); \
        case 58: return vcopy_lane_##base(vtrn1_##base(a, a), 1, a, 3); \
        case 59: return vcopy_lane_##base(a, 1, a, 3); \
        case 60: return vzip1_##base(vzip1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 61: return vuzp1_##base(vuzp1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 62: return vzip2_##base(vext_##base(vrev32_##base(a), vrev32_##base(a), 3), vrev32_##base(a)); \
        case 63: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 3); \
        case 64: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 65: return vzip1_##base(vrev32_##base(a), a); \
        case 66: return vcopy_lane_##base(vrev32_##base(a), 2, a, 0); \
        case 67: return vext_##base(vzip1_##base(a, vext_##base(a, a, 3)), vzip1_##base(a, vext_##base(a, a, 3)), 2); \
        case 68: return vext_##base(vrev64_##base(a), vrev32_##base(a), 2); \
        case 69: return vzip1_##base(vdup_lane_##base(a, 1), a); \
        case 70: return vext_##base(vdup_lane_##base(a, 1), a, 3); \
        case 71: return vcopy_lane_##base(vuzp2_##base(a, a), 1, a, 0); \
        case 72: return vrev32_##base(vuzp1_##base(vzip1_##base(a, a), a)); \
        case 73: return vzip1_##base(vext_##base(a, a, 1), a); \
        case 74: return vcopy_lane_##base(vrev32_##base(a), 2, a, 2); \
        case 75: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vrev32_##base(a)), 1, vreinterpret_##kind##32_##base(a), 1)); \
        case 76: return vtrn2_##base(a, vdup_lane_##base(a, 0)); \
        case 77: return vcopy_lane_##base(vrev32_##base(a), 3, a, 1); \
        case 78: return vext_##base(vrev64_##base(a), vrev64_##base(a), 2); \
        case 79: return vcopy_lane_##base(vrev32_##base(a), 3, a, 3); \
        case 80: return vzip2_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 81: return vext_##base(vdup_lane_##base(a, 1), a, 2); \
        case 82: return vuzp1_##base(vdup_lane_##base(a, 1), a); \
        case 83: return vcopy_lane_##base(vtrn2_##base(a, a), 2, a, 0); \
        case 84: return vext_##base(vdup_lane_##base(a, 1), a, 1); \
        case 85: return vdup_lane_##base(a, 1); \
        case 86: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 1); \
        case 87: return vuzp2_##base(vdup_lane_##base(a, 1), a); \
        case 88: return vcopy_lane_##base(vcopy_lane_##base(a, 0, a, 1), 3, a, 0); \
        case 89: return vcopy_lane_##base(vdup_lane_##base(a, 1), 2, a, 2); \
        case 90: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 2); \
        case 91: return vcopy_lane_##base(a, 0, a, 1); \
        case 92: return vcopy_lane_##base(vext_##base(a, a, 1), 1, a, 1); \
        case 93: return vtrn2_##base(a, vdup_lane_##base(a, 1)); \
        case 94: return vcopy_lane_##base(vrev32_##base(a), 1, a, 1); \
        case 95: return vtrn2_##base(a, a); \
        case 96: return vcopy_lane_##base(vext_##base(a, a, 1), 2, a, 0); \
        case 97: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 1)), 1, vreinterpret_##kind##32_##base(a), 0)); \
        case 98: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 99: return vzip2_##base(vrev64_##base(a), a); \
        case 100: return vtrn2_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); \
        case 101: return vcopy_lane_##base(vdup_lane_##base(a, 1), 1, a, 2); \
        case 102: return vtrn1_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2)); \
        case 103: return vzip2_##base(vdup_lane_##base(a, 1), a); \
        case 104: return vcopy_lane_##base(vext_##base(a, a, 1), 2, a, 2); \
        case 105: return vzip1_##base(vext_##base(a, a, 1), vrev32_##base(vext_##base(a, a, 1))); \
        case 106: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 3); \
        case 107: return vzip2_##base(vext_##base(a, a, 3), a); \
        case 108: return vext_##base(a, a, 1); \
        case 109: return vext_##base(a, vrev32_##base(a), 1); \
        case 110: return vext_##base(a, vdup_lane_##base(a, 2), 1); \
        case 111: return vext_##base(a, vdup_lane_##base(a, 3), 1); \
        case 112: return vuzp2_##base(a, vdup_lane_##base(a, 0)); \
        case 113: return vcopy_lane_##base(vext_##base(a, a, 2), 0, a, 1); \
        case 114: return vuzp1_##base(vrev32_##base(a), a); \
        case 115: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 116: return vcopy_lane_##base(vuzp2_##base(a, a), 3, a, 0); \
        case 117: return vuzp2_##base(a, vdup_lane_##base(a, 1)); \
        case 118: return vzip1_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); \
        case 119: return vuzp2_##base(a, a); \
        case 120: return vuzp2_##base(a, vrev64_##base(a)); \
        case 121: return vuzp2_##base(a, vuzp1_##base(a, vdup_lane_##base(a, 1))); \
        case 122: return vuzp2_##base(a, vdup_lane_##base(a, 2)); \
        case 123: return vcopy_lane_##base(vuzp2_##base(a, a), 2, a, 2); \
        case 124: return vcopy_lane_##base(vext_##base(a, a, 1), 1, a, 3); \
        case 125: return vuzp2_##base(a, vext_##base(a, a, 2)); \
        case 126: return vcopy_lane_##base(vrev32_##base(a), 1, a, 3); \
        case 127: return vuzp2_##base(a, vdup_lane_##base(a, 3)); \
        case 128: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 129: return vcopy_lane_##base(vext_##base(a, a, 2), 1, a, 0); \
        case 130: return vuzp1_##base(vext_##base(a, a, 2), a); \
        case 131: return vuzp2_##base(vext_##base(a, a, 1), vuzp2_##base(vext_##base(a, a, 1), a)); \
        case 132: return vrev64_##base(vuzp1_##base(vzip1_##base(a, a), a)); \
        case 133: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); \
        case 134: return vext_##base(vdup_lane_##base(a, 2), a, 3); \
        case 135: return vuzp2_##base(vrev64_##base(a), a); \
        case 136: return vuzp2_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 137: return vzip1_##base(vdup_lane_##base(a, 2), a); \
        case 138: return vtrn1_##base(vdup_lane_##base(a, 2), a); \
        case 139: return vcopy_lane_##base(vcopy_lane_##base(a, 0, a, 2), 1, a, 0); \
        case 140: return vzip2_##base(a, vdup_lane_##base(a, 0)); \
        case 141: return vzip1_##base(vext_##base(a, a, 2), a); \
        case 142: return vtrn1_##base(vzip2_##base(a, a), a); \
        case 143: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 144: return vext_##base(vrev64_##base(a), a, 1); \
        case 145: return vext_##base(vrev64_##base(a), vrev32_##base(a), 1); \
        case 146: return vuzp2_##base(vuzp1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 147: return vext_##base(vrev64_##base(a), vrev64_##base(a), 1); \
        case 148: return vzip2_##base(vext_##base(vrev64_##base(a), vrev64_##base(a), 3), vrev64_##base(a)); \
        case 149: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 3); \
        case 150: return vzip1_##base(vrev32_##base(vext_##base(a, a, 1)), vext_##base(a, a, 1)); \
        case 151: return vcopy_lane_##base(vcopy_lane_##base(a, 0, a, 2), 2, a, 1); \
        case 152: return vzip2_##base(vdup_lane_##base(a, 2), vrev64_##base(a)); \
        case 153: return vtrn1_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1)); \
        case 154: return vcopy_lane_##base(vdup_lane_##base(a, 2), 1, a, 1); \
        case 155: return vcopy_lane_##base(a, 0, a, 2); \
        case 156: return vzip2_##base(a, vrev64_##base(a)); \
        case 157: return vzip2_##base(a, vdup_lane_##base(a, 1)); \
        case 158: return vzip2_##base(a, vext_##base(a, a, 3)); \
        case 159: return vcopy_lane_##base(vzip2_##base(a, a), 1, a, 1); \
        case 160: return vext_##base(vtrn1_##base(a, a), vtrn1_##base(a, a), 2); \
        case 161: return vext_##base(vdup_lane_##base(a, 2), a, 2); \
        case 162: return vuzp1_##base(vdup_lane_##base(a, 2), a); \
        case 163: return vcopy_lane_##base(vzip2_##base(a, a), 2, a, 0); \
        case 164: return vcopy_lane_##base(vrev64_##base(a), 0, a, 2); \
        case 165: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 2); \
        case 166: return vcopy_lane_##base(vdup_lane_##base(a, 2), 2, a, 1); \
        case 167: return vuzp2_##base(vdup_lane_##base(a, 2), a); \
        case 168: return vext_##base(vdup_lane_##base(a, 2), a, 1); \
        case 169: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 1); \
        case 170: return vdup_lane_##base(a, 2); \
        case 171: return vzip2_##base(vdup_lane_##base(a, 2), a); \
        case 172: return vcopy_lane_##base(vext_##base(a, a, 1), 0, a, 2); \
        case 173: return vcopy_lane_##base(vzip2_##base(a, a), 3, a, 1); \
        case 174: return vzip2_##base(a, vdup_lane_##base(a, 2)); \
        case 175: return vzip2_##base(a, a); \
        case 176: return vext_##base(a, vdup_lane_##base(a, 0), 2); \
        case 177: return vext_##base(a, a, 2); \
        case 178: return vcopy_lane_##base(vext_##base(a, a, 2), 3, a, 2); \
        case 179: return vtrn2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 180: return vext_##base(a, vrev32_##base(a), 2); \
        case 181: return vext_##base(a, vdup_lane_##base(a, 1), 2); \
        case 182: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 3)), 0, vreinterpret_##kind##32_##base(a), 1)); \
        case 183: return vcopy_lane_##base(vuzp2_##base(a, a), 0, a, 2); \
        case 184: return vcopy_lane_##base(vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0, vreinterpret_##kind##32_##base(a), 1)), 3, a, 0); \
        case 185: return vext_##base(vrev32_##base(a), vrev64_##base(a), 3); \
        case 186: return vext_##base(a, vdup_lane_##base(a, 2), 2); \
        case 187: return vreinterpret_##base##_##kind##32(vdup_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1)); \
        case 188: return vzip2_##base(a, vext_##base(a, a, 1)); \
        case 189: return vcopy_lane_##base(vext_##base(a, a, 2), 2, a, 3); \
        case 190: return vext_##base(a, vrev64_##base(a), 2); \
        case 191: return vext_##base(a, vdup_lane_##base(a, 3), 2); \
        case 192: return vext_##base(a, vdup_lane_##base(a, 0), 3); \
        case 193: return vzip1_##base(vext_##base(a, a, 3), a); \
        case 194: return vcopy_lane_##base(vext_##base(a, a, 3), 2, a, 0); \
        case 195: return vzip1_##base(vext_##base(a, a, 3), vzip1_##base(a, vext_##base(a, a, 3))); \
        case 196: return vtrn1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 197: return vcopy_lane_##base(vzip1_##base(a, a), 0, a, 3); \
        case 198: return vext_##base(a, a, 3); \
        case 199: return vcopy_lane_##base(vext_##base(a, a, 3), 3, a, 3); \
        case 200: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 201: return vzip1_##base(vrev64_##base(a), a); \
        case 202: return vcopy_lane_##base(vext_##base(a, a, 3), 2, a, 2); \
        case 203: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 3)), 1, vreinterpret_##kind##32_##base(a), 1)); \
        case 204: return vtrn1_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 0)); \
        case 205: return vzip1_##base(vdup_lane_##base(a, 3), a); \
        case 206: return vtrn1_##base(vdup_lane_##base(a, 3), a); \
        case 207: return vcopy_lane_##base(vdup_lane_##base(a, 3), 1, a, 0); \
        case 208: return vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 209: return vcopy_lane_##base(vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1, vreinterpret_##kind##32_##base(a), 0)), 0, a, 3); \
        case 210: return vuzp1_##base(vrev64_##base(a), a); \
        case 211: return vext_##base(a, vrev32_##base(a), 3); \
        case 212: return vcopy_lane_##base(vrev64_##base(a), 1, a, 1); \
        case 213: return vext_##base(a, vdup_lane_##base(a, 1), 3); \
        case 214: return vcopy_lane_##base(vext_##base(a, a, 3), 1, a, 1); \
        case 215: return vuzp2_##base(vext_##base(a, a, 2), a); \
        case 216: return vzip2_##base(vrev32_##base(a), vrev64_##base(a)); \
        case 217: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); \
        case 218: return vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 219: return vcopy_lane_##base(a, 0, a, 3); \
        case 220: return vzip2_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 221: return vuzp1_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 222: return vrev64_##base(vuzp2_##base(vzip2_##base(a, a), a)); \
        case 223: return vtrn2_##base(vdup_lane_##base(a, 3), a); \
        case 224: return vcopy_lane_##base(vrev64_##base(a), 2, a, 0); \
        case 225: return vext_##base(vrev32_##base(a), a, 2); \
        case 226: return vcopy_lane_##base(vuzp1_##base(a, a), 0, a, 3); \
        case 227: return vzip2_##base(vext_##base(a, a, 1), a); \
        case 228: return vrev64_##base(a); \
        case 229: return vcopy_lane_##base(vrev64_##base(a), 3, a, 1); \
        case 230: return vtrn1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 231: return vcopy_lane_##base(vrev64_##base(a), 3, a, 3); \
        case 232: return vcopy_lane_##base(vrev64_##base(a), 2, a, 2); \
        case 233: return vext_##base(a, vuzp2_##base(vuzp1_##base(a, a), a), 3); \
        case 234: return vext_##base(a, vdup_lane_##base(a, 2), 3); \
        case 235: return vzip2_##base(vrev32_##base(a), a); \
        case 236: return vtrn2_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 237: return vrev32_##base(vuzp2_##base(vzip2_##base(a, a), a)); \
        case 238: return vext_##base(vrev32_##base(a), vrev64_##base(a), 2); \
        case 239: return vzip2_##base(vdup_lane_##base(a, 3), a); \
        case 240: return vext_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 0), 2); \
        case 241: return vext_##base(vdup_lane_##base(a, 3), a, 2); \
        case 242: return vuzp1_##base(vdup_lane_##base(a, 3), a); \
        case 243: return vcopy_lane_##base(vdup_lane_##base(a, 3), 2, a, 0); \
        case 244: return vcopy_lane_##base(vrev64_##base(a), 1, a, 3); \
        case 245: return vext_##base(vtrn2_##base(a, a), vtrn2_##base(a, a), 2); \
        case 246: return vcopy_lane_##base(vext_##base(a, a, 3), 1, a, 3); \
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
        case 1: return vcopy_lane_##base(a, 1, b, 1); \
        case 2: return vcopy_lane_##base(a, 0, b, 0); \
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
        case 1: return vcopy_lane_##base(a, 3, b, 3); \
        case 2: return vcopy_lane_##base(a, 2, b, 2); \
        case 3: return vreinterpret_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 2)(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b), 0, 1)); \
        case 4: return vcopy_lane_##base(a, 1, b, 1); \
        case 5: return vtrn2_##base(vrev32_##base(a), b); \
        case 6: return vcopy_lane_##base(vcopy_lane_##base(b, 0, a, 0), 3, a, 3); \
        case 7: return vcopy_lane_##base(b, 0, a, 0); \
        case 8: return vcopy_lane_##base(a, 0, b, 0); \
        case 9: return vcopy_lane_##base(vcopy_lane_##base(a, 0, b, 0), 3, b, 3); \
        case 10: return vtrn2_##base(vrev32_##base(b), a); \
        case 11: return vcopy_lane_##base(b, 1, a, 1); \
        case 12: return vreinterpret_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 2)(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b), 1, 0)); \
        case 13: return vcopy_lane_##base(b, 2, a, 2); \
        case 14: return vcopy_lane_##base(b, 3, a, 3); \
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
        case 1: return vcopy_lane_##base(a, 7, b, 7); \
        case 2: return vcopy_lane_##base(a, 6, b, 6); \
        case 4: return vcopy_lane_##base(a, 5, b, 5); \
        case 8: return vcopy_lane_##base(a, 4, b, 4); \
        case 16: return vcopy_lane_##base(a, 3, b, 3); \
        case 32: return vcopy_lane_##base(a, 2, b, 2); \
        case 64: return vcopy_lane_##base(a, 1, b, 1); \
        case 128: return vcopy_lane_##base(a, 0, b, 0); \
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
    if (v0) Result = vcopy_lane_##base(Result, 0, b, 0); \
    if (v1) Result = vcopy_lane_##base(Result, 1, b, 1); \
    if (v2) Result = vcopy_lane_##base(Result, 2, b, 2); \
    if (v3) Result = vcopy_lane_##base(Result, 3, b, 3); \
    if (v4) Result = vcopy_lane_##base(Result, 4, b, 4); \
    if (v5) Result = vcopy_lane_##base(Result, 5, b, 5); \
    if (v6) Result = vcopy_lane_##base(Result, 6, b, 6); \
    if (v7) Result = vcopy_lane_##base(Result, 7, b, 7); \
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

#pragma mark - Fallback Implementations

#ifdef CC_SIMD_MISSING_CCSimdZero
#define CC_SIMD_IMPL(base, count, kind) (void){ return CC_SIMD_NAME(CCSimdFill, base, count)(0); }
CC_SIMD_DECL(CCSimdZero, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdZero)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdSetSequence
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
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
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
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
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
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdAndNot
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNot, base, count)(a), b); }
CC_SIMD_DECL(CCSimdAndNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdAndNot)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateLeft
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    const CC_SIMD_TYPE(base, count) Mask = CC_SIMD_NAME(CCSimdFill, base, count)(CC_SIMD_BITS(base) - 1); \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftLeft, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(b, Mask)), CC_SIMD_NAME(CCSimdShiftRight, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(b), Mask))); \
}
CC_SIMD_DECL(CCSimdRotateLeft, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateLeft)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateLeftN
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    const uint8_t Mask = CC_SIMD_BITS(base) - 1; \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftLeftN, base, count)(a, n & Mask), CC_SIMD_NAME(CCSimdShiftRightN, base, count)(a, -n & Mask)); \
}
CC_SIMD_DECL(CCSimdRotateLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateLeftN)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateRight
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    const CC_SIMD_TYPE(base, count) Mask = CC_SIMD_NAME(CCSimdFill, base, count)(CC_SIMD_BITS(base) - 1); \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftRight, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(b, Mask)), CC_SIMD_NAME(CCSimdShiftLeft, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(b), Mask))); \
}
CC_SIMD_DECL(CCSimdRotateRight, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateRight)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateRightN
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    const uint8_t Mask = CC_SIMD_BITS(base) - 1; \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftRightN, base, count)(a, n & Mask), CC_SIMD_NAME(CCSimdShiftLeftN, base, count)(a, -n & Mask)); \
}
CC_SIMD_DECL(CCSimdRotateRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateRightN)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdLowestUnset
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNot, base, count)(a), CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(1))); }
CC_SIMD_DECL(CCSimdLowestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdLowestUnset)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdLowestSet
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_SIMD_NAME(CCSimdAnd, base, count)(a, CC_SIMD_NAME(CCSimdNeg, base, count)(a)); }
CC_SIMD_DECL(CCSimdLowestSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdLowestSet)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdHighestSet
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = CC_SIMD_NAME(CCSimdMask, base, count)(a); \
    \
    return CC_SIMD_NAME(CCSimdXor, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _, CC_SIMD_NAME(Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), _, CC_SIMD_NAME(Reinterpret, base, count))(Result), 1))); \
}
CC_SIMD_DECL(CCSimdHighestSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdHighestSet)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdNextPow2
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) One = CC_SIMD_NAME(CCSimdFill, base, count)(1); \
    CC_SIMD_TYPE(base, count) Result = CC_SIMD_NAME(CCSimdSub, base, count)(a, One); \
    \
    Result = CC_SIMD_NAME(CCSimdMask, base, count)(Result); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(Result, One); \
}
CC_SIMD_DECL(CCSimdNextPow2, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdNextPow2)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMask
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u8x8)(CCSimdShiftRightN_u8x8(CC_SIMD_NAME(CCSimd_u8x8_Reinterpret, base, count)(Result), 1))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u8x8)(CCSimdShiftRightN_u8x8(CC_SIMD_NAME(CCSimd_u8x8_Reinterpret, base, count)(Result), 2))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u8x8)(CCSimdShiftRightN_u8x8(CC_SIMD_NAME(CCSimd_u8x8_Reinterpret, base, count)(Result), 4))); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u16x4)(CCSimdShiftRightN_u16x4(CC_SIMD_NAME(CCSimd_u16x4_Reinterpret, base, count)(Result), 1))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u16x4)(CCSimdShiftRightN_u16x4(CC_SIMD_NAME(CCSimd_u16x4_Reinterpret, base, count)(Result), 2))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u16x4)(CCSimdShiftRightN_u16x4(CC_SIMD_NAME(CCSimd_u16x4_Reinterpret, base, count)(Result), 4))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u16x4)(CCSimdShiftRightN_u16x4(CC_SIMD_NAME(CCSimd_u16x4_Reinterpret, base, count)(Result), 8))); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u32x2)(CCSimdShiftRightN_u32x2(CC_SIMD_NAME(CCSimd_u32x2_Reinterpret, base, count)(Result), 1))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u32x2)(CCSimdShiftRightN_u32x2(CC_SIMD_NAME(CCSimd_u32x2_Reinterpret, base, count)(Result), 2))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u32x2)(CCSimdShiftRightN_u32x2(CC_SIMD_NAME(CCSimd_u32x2_Reinterpret, base, count)(Result), 4))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u32x2)(CCSimdShiftRightN_u32x2(CC_SIMD_NAME(CCSimd_u32x2_Reinterpret, base, count)(Result), 8))); \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u32x2)(CCSimdShiftRightN_u32x2(CC_SIMD_NAME(CCSimd_u32x2_Reinterpret, base, count)(Result), 16))); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMaskLowerPow2
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) Mask = CC_SIMD_NAME(CCSimdMaskCompareNotEqual, base, count)(a, CC_SIMD_NAME(CCSimdZero, base, count)()); \
    const CC_SIMD_TYPE(base, count) Result = CC_SIMD_NAME(CCSimdNot, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(a)); \
    \
    return CC_SIMD_NAME(CCSimdAnd, base, count)(Mask, Result); \
}
CC_SIMD_DECL(CCSimdMaskLowerPow2, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMaskLowerPow2)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMaskHighestUnset
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    return CC_SIMD_NAME(CCSimdXor, base, count)(CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_MAX >> (64 - CC_SIMD_BITS(base))), CC_SIMD_NAME(CCSimdMask, base, count)(a)); \
}
CC_SIMD_DECL(CCSimdMaskHighestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMaskHighestUnset)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCountLowestUnset
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) AllZero = CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdCompareEqual, base, count)(a, CC_SIMD_NAME(CCSimdZero, base, count)()), CC_SIMD_NAME(CCSimdFill, base, count)(CC_SIMD_BITS(base))); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdCountSet, base, count)(CC_SIMD_NAME(CCSimdMaskLowerPow2, base, count)(CC_SIMD_NAME(CCSimdLowestSet, base, count)(a))), AllZero); \
}
CC_SIMD_DECL(CCSimdCountLowestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdCountLowestUnset)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCountSet
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) Mask55 = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x5555555555555555) >> (64 - CC_SIMD_BITS(base))); \
    const CC_SIMD_TYPE(base, count) Mask33 = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x3333333333333333) >> (64 - CC_SIMD_BITS(base))); \
    const CC_SIMD_TYPE(base, count) Mask0f = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x0f0f0f0f0f0f0f0f) >> (64 - CC_SIMD_BITS(base))); \
    const CC_SIMD_TYPE(base, count) Mask01 = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x0101010101010101) >> (64 - CC_SIMD_BITS(base))); \
    \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdSub, base, count)(Result, CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdShiftRightN, base, count)(Result, 1), Mask55)); \
    Result = CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAnd, base, count)(Result, Mask33), CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdShiftRightN, base, count)(Result, 2), Mask33)); \
    Result = CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(Result, CC_SIMD_NAME(CCSimdShiftRightN, base, count)(Result, 4)), Mask0f); \
    Result = CC_SIMD_NAME(CCSimdShiftRightN, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(Result, Mask01), CC_SIMD_BITS(base) - 8); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdCountSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdCountSet)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareNotEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareNotEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareNotEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareNotEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareNotEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareLessThan
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareLessThan, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThan))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareLessThan, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThan))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareLessThanEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareLessThanEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThanEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareLessThanEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThanEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareGreaterThan
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThan, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThan))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThan, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThan))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThanEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThanEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMaskCompareNotEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNot, base, count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdMaskCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMaskCompareNotEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNot, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdMaskCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdMaskCompareNotEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMadd
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), c); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMadd)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdNegMadd
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b)), c); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdNegMadd)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMsub
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), c); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMsub)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdNegMsub
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b)), c); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdNegMsub)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdDiv
#if CC_SIMD_COMPATIBILITY
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    for (size_t Loop = 0; Loop < count; Loop++) \
    { \
        Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, Loop, CC_SIMD_NAME(CCSimdGet, base, count)(a, Loop) / CC_SIMD_NAME(CCSimdGet, base, count)(b, Loop)); \
    } \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdDiv)
#undef CC_SIMD_IMPL
#endif
#endif

#ifdef CC_SIMD_MISSING_CCSimdMod
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdDiv, base, count)(a, b), b)); }
CC_SIMD_DECL(CCSimdMod, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMod))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdFloor, base, count)(CC_SIMD_NAME(CCSimdDiv, base, count)(a, b)), b)); }
CC_SIMD_DECL(CCSimdMod, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdMod))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdHadd
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
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
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
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
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
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdHsub
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
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHsub))
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
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHsub))
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
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHsub))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdDot
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
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdDot))
#undef CC_SIMD_IMPL
#undef CC_SIMD_DOT_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), v0, v1, v2, v3); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdDot))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), v0, v1, v2, v3, v4, v5, v6, v7); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdDot))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdClamp
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) min, const CC_SIMD_TYPE(base, count) max){ return CC_SIMD_NAME(CCSimdMin, base, count)(CC_SIMD_NAME(CCSimdMax, base, count)(a, min), max); }
CC_SIMD_DECL(CCSimdClamp, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdClamp)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdPosPiRadSin_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosPiRadSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(CC_PI);
    const CCSimd_f32x2 M = CCSimdFill_f32x2(4.0f);
    const CCSimd_f32x2 PiSqr5 = CCSimdFill_f32x2(5.0f * CC_PI * CC_PI);
    
    CCSimd_f32x2 Value = a;
    
    // Bhāskara I's sine approximation
    Value = CCSimdMul_f32x2(M, CCSimdMul_f32x2(Value, CCSimdSub_f32x2(Pi, Value)));
    Value = CCSimdDiv_f32x2(CCSimdMul_f32x2(M, Value), CCSimdSub_f32x2(PiSqr5, Value));
    
    return Value;
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdHalfPiRadCos_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdHalfPiRadCos_f32x2(const CCSimd_f32x2 a)
{
#if CC_SIMD_HALF_PI_RAD_COS_ACCURACY == 0
    const CCSimd_f32x2 M = CCSimdFill_f32x2(4.0f);
    const CCSimd_f32x2 PiSqr = CCSimdFill_f32x2(CC_PI * CC_PI);
    
    CCSimd_f32x2 Value = a;
    
    // Bhāskara I's cosine approximation
    Value = CCSimdMul_f32x2(Value, Value);
    Value = CCSimdDiv_f32x2(CCSimdNegMadd_f32x2(M, Value, PiSqr), CCSimdAdd_f32x2(PiSqr, Value));
    
    return Value;
#elif CC_SIMD_HALF_PI_RAD_COS_ACCURACY >= 1
    // More accurate but requires more gpr use
    
    // https://math.stackexchange.com/questions/976462/a-1400-years-old-approximation-to-the-sine-function-by-mahabhaskariya-of-bhaskar/4763600#4763600
    // (9): 0.99940323+𝑥^2(−0.49558085+0.036791683𝑥^2)
    
    const CCSimd_f32x2 X = CCSimdFill_f32x2(0.99940323f);
    const CCSimd_f32x2 Y = CCSimdFill_f32x2(-0.49558085f);
    const CCSimd_f32x2 Z = CCSimdFill_f32x2(0.036791683f);
    
    CCSimd_f32x2 Value = a;
    
    Value = CCSimdMul_f32x2(Value, Value);
    Value = CCSimdMadd_f32x2(Value, CCSimdMadd_f32x2(Value, Z, Y), X);
    
    return Value;
#endif
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdPosSin_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPosSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 Pi2 = CCSimdFill_f32x2(CC_PI * 2.0f);
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(CC_PI);
    const CCSimd_f32x2 NegOne = CCSimdFill_f32x2(-1.0f);
    
    CCSimd_f32x2 Value = a;
    
    CCSimd_f32x2 Sign = CCSimdFloor_f32x2(CCSimdDiv_f32x2(CCSimdMod_f32x2(Value, Pi2), Pi));
    Sign = CCSimdSub_f32x2(CCSimdNeg_f32x2(CCSimdAdd_f32x2(Sign, Sign)), NegOne);
    
    Value = CCSimdMod_f32x2(Value, Pi);
    
    Value = CCSimdPosPiRadSin_f32x2(Value);
        
    return CCSimdMul_f32x2(Value, Sign);
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdPiRadSin_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPiRadSin_f32x2(const CCSimd_f32x2 a)
{
    CCSimd_f32x2 Value = CCSimdAbs_f32x2(a);
    
    CCSimd_u32x2 Sign = CCSimdShiftLeftN_u32x2(CCSimdShiftRightN_u32x2(CCSimd_u32x2_Reinterpret_f32x2(a), 31), 31);
    
    Value = CCSimdPosPiRadSin_f32x2(Value);
    
    return CCSimd_f32x2_Reinterpret_u32x2(CCSimdXor_u32x2(CCSimd_u32x2_Reinterpret_f32x2(Value), Sign));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdSin_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 Pi2 = CCSimdFill_f32x2(CC_PI * 2.0f);
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(CC_PI);
    const CCSimd_f32x2 NegOne = CCSimdFill_f32x2(-1.0f);
    
    CCSimd_f32x2 Value = CCSimdAbs_f32x2(a);
    
    CCSimd_f32x2 Sign = CCSimdFloor_f32x2(CCSimdDiv_f32x2(CCSimdMod_f32x2(Value, Pi2), Pi));
    Sign = CCSimdSub_f32x2(CCSimdNeg_f32x2(CCSimdAdd_f32x2(Sign, Sign)), NegOne);
    Sign = CCSimd_f32x2_Reinterpret_u32x2(CCSimdXor_u32x2(CCSimd_u32x2_Reinterpret_f32x2(Sign), CCSimdShiftLeftN_u32x2(CCSimdShiftRightN_u32x2(CCSimd_u32x2_Reinterpret_f32x2(a), 31), 31)));
    
    Value = CCSimdMod_f32x2(Value, Pi);
    
    Value = CCSimdPosPiRadSin_f32x2(Value);
    
    return CCSimdMul_f32x2(Value, Sign);
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcSin_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcSin_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 HalfPi = CCSimdFill_f32x2(CC_PI / 2.0f);
    
#if CC_SIMD_ARCSIN_ACCURACY < 2
    // Based off 4.4.45 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CCSimd_f32x2 a0 = CCSimdFill_f32x2(1.5707288f);
    const CCSimd_f32x2 a1 = CCSimdFill_f32x2(-0.2121144f);
    const CCSimd_f32x2 a2 = CCSimdFill_f32x2(0.0742610f);
    const CCSimd_f32x2 a3 = CCSimdFill_f32x2(-0.0187293f);
#else
    // Based off 4.4.46 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CCSimd_f32x2 a0 = CCSimdFill_f32x2(1.5707963050f);
    const CCSimd_f32x2 a1 = CCSimdFill_f32x2(-0.2145988016f);
    const CCSimd_f32x2 a2 = CCSimdFill_f32x2(0.0889789874f);
    const CCSimd_f32x2 a3 = CCSimdFill_f32x2(-0.0501743046f);
    const CCSimd_f32x2 a4 = CCSimdFill_f32x2(0.0308918810f);
    const CCSimd_f32x2 a5 = CCSimdFill_f32x2(-0.0170881256f);
    const CCSimd_f32x2 a6 = CCSimdFill_f32x2(0.0066700901f);
    const CCSimd_f32x2 a7 = CCSimdFill_f32x2(-0.0012624911f);
#endif
    
    const CCSimd_f32x2 x1 = a;
    const CCSimd_f32x2 x2 = CCSimdMul_f32x2(x1, x1);
    const CCSimd_f32x2 x3 = CCSimdMul_f32x2(x1, x2);
#if CC_SIMD_ARCSIN_ACCURACY >= 2
    const CCSimd_f32x2 x4 = CCSimdMul_f32x2(x2, x2);
    const CCSimd_f32x2 x5 = CCSimdMul_f32x2(x2, x3);
    const CCSimd_f32x2 x6 = CCSimdMul_f32x2(x3, x3);
    const CCSimd_f32x2 x7 = CCSimdMul_f32x2(x3, x4);
#endif
    
    CCSimd_f32x2 Result = a0;
    Result = CCSimdMadd_f32x2(a1, x1, Result);
    Result = CCSimdMadd_f32x2(a2, x2, Result);
    Result = CCSimdMadd_f32x2(a3, x3, Result);
#if CC_SIMD_ARCSIN_ACCURACY >= 2
    Result = CCSimdMadd_f32x2(a4, x4, Result);
    Result = CCSimdMadd_f32x2(a5, x5, Result);
    Result = CCSimdMadd_f32x2(a6, x6, Result);
    Result = CCSimdMadd_f32x2(a7, x7, Result);
#endif
    
    Result = CCSimdMul_f32x2(CCSimdPow_f32x2(CCSimdSub_f32x2(CCSimdFill_f32x2(1.0f), a), CCSimdFill_f32x2(0.5f)), Result);
    
    return CCSimdSub_f32x2(HalfPi, Result);
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdCos_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCos_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 HalfPi = CCSimdFill_f32x2(CC_PI / 2.0f);
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(CC_PI);
    const CCSimd_f32x2 Two = CCSimdFill_f32x2(2.0f);
    const CCSimd_f32x2 NegOne = CCSimdFill_f32x2(-1.0f);
    
    CCSimd_f32x2 Value = CCSimdAdd_f32x2(a, HalfPi);
    
    CCSimd_f32x2 Sign = CCSimdFloor_f32x2(CCSimdMod_f32x2(CCSimdDiv_f32x2(Value, Pi), Two));
    Sign = CCSimdSub_f32x2(CCSimdNeg_f32x2(CCSimdAdd_f32x2(Sign, Sign)), NegOne);
    
    Value = CCSimdSub_f32x2(CCSimdMod_f32x2(Value, Pi), HalfPi);
    
    return CCSimdMul_f32x2(CCSimdHalfPiRadCos_f32x2(Value), Sign);
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcCos_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcCos_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 HalfPi = CCSimdFill_f32x2(CC_PI / 2.0f);
   
    return CCSimdSub_f32x2(HalfPi, CCSimdArcSin_f32x2(a));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdTan_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdTan_f32x2(const CCSimd_f32x2 a)
{
    return CCSimdDiv_f32x2(CCSimdSin_f32x2(a), CCSimdCos_f32x2(a));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdQtrPiArcTan_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdQtrPiArcTan_f32x2(const CCSimd_f32x2 a)
{
#if CC_SIMD_QTR_PI_ARCTAN_ACCURACY < 2
    // Based off 4.4.48 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CCSimd_f32x2 One = CCSimdFill_f32x2(1.0f);
    const CCSimd_f32x2 C28 = CCSimdFill_f32x2(0.28f);
    
    return CCSimdDiv_f32x2(a, CCSimdMadd_f32x2(CCSimdMul_f32x2(a, a), C28, One));
#else
    // Based off 4.4.47 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CCSimd_f32x2 a1 = CCSimdFill_f32x2(0.9998660f);
    const CCSimd_f32x2 a3 = CCSimdFill_f32x2(-0.3302995f);
    const CCSimd_f32x2 a5 = CCSimdFill_f32x2(0.1801410f);
    const CCSimd_f32x2 a7 = CCSimdFill_f32x2(-0.0851330f);
    const CCSimd_f32x2 a9 = CCSimdFill_f32x2(0.0208351f);
    
    const CCSimd_f32x2 x1 = a;
    const CCSimd_f32x2 x2 = CCSimdMul_f32x2(x1, x1);
    const CCSimd_f32x2 x3 = CCSimdMul_f32x2(x1, x2);
    const CCSimd_f32x2 x4 = CCSimdMul_f32x2(x2, x2);
    const CCSimd_f32x2 x5 = CCSimdMul_f32x2(x2, x3);
    const CCSimd_f32x2 x7 = CCSimdMul_f32x2(x3, x4);
    const CCSimd_f32x2 x9 = CCSimdMul_f32x2(x4, x5);
    
    CCSimd_f32x2 Result = CCSimdMul_f32x2(a1, x1);
    Result = CCSimdMadd_f32x2(a3, x3, Result);
    Result = CCSimdMadd_f32x2(a5, x5, Result);
    Result = CCSimdMadd_f32x2(a7, x7, Result);
    Result = CCSimdMadd_f32x2(a9, x9, Result);
    
    return Result;
#endif
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcTan_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcTan_f32x2(const CCSimd_f32x2 a)
{
    const CCSimd_f32x2 One = CCSimdFill_f32x2(1.0f);
    const CCSimd_f32x2 NegOne = CCSimdFill_f32x2(-1.0f);
    const CCSimd_f32x2 HalfPi = CCSimdFill_f32x2(CC_PI / 2.0f);
    
    const CCSimd_u32x2 Sign = CCSimdShiftLeftN_u32x2(CCSimdMaskCompareLessThan_f32x2(a, NegOne), 31);
    const CCSimd_u32x2 BoundsMask = CCSimdMaskCompareLessThanEqual_f32x2(CCSimd_f32x2_Reinterpret_u32x2(CCSimdXor_u32x2(Sign, CCSimd_u32x2_Reinterpret_f32x2(a))), One);
    
    CCSimd_f32x2 Bounds = CCSimd_f32x2_Reinterpret_u32x2(CCSimdAndNot_u32x2(BoundsMask, CCSimdOr_u32x2(Sign, CCSimd_u32x2_Reinterpret_f32x2(HalfPi))));
    
    const CCSimd_f32x2 Radians = CCSimdQtrPiArcTan_f32x2(CCSimd_f32x2_Reinterpret_u32x2(CCSimdOr_u32x2(CCSimdAnd_u32x2(BoundsMask, CCSimd_u32x2_Reinterpret_f32x2(a)), CCSimdAndNot_u32x2(BoundsMask, CCSimd_u32x2_Reinterpret_f32x2(CCSimdDiv_f32x2(One, a))))));
    
    return CCSimd_f32x2_Reinterpret_u32x2(CCSimdOr_u32x2(CCSimdAnd_u32x2(BoundsMask, CCSimd_u32x2_Reinterpret_f32x2(Radians)), CCSimdAndNot_u32x2(BoundsMask, CCSimd_u32x2_Reinterpret_f32x2(CCSimdSub_f32x2(Bounds, Radians)))));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcTan2_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdArcTan2_f32x2(const CCSimd_f32x2 y, const CCSimd_f32x2 x)
{
    const CCSimd_f32x2 Zero = CCSimdZero_f32x2();
    const CCSimd_f32x2 Pi = CCSimdFill_f32x2(CC_PI);
    const CCSimd_f32x2 HalfPi = CCSimdFill_f32x2(CC_PI / 2.0f);
    
    const CCSimd_u32x2 MaskX = CCSimdMaskCompareNotEqual_f32x2(x, Zero);
    const CCSimd_u32x2 MaskY = CCSimdMaskCompareLessThanEqual_f32x2(x, Zero);
#ifdef CC_SIMD_ARCTAN2_PRINCIPAL // (-pi, pi]
    const CCSimd_u32x2 Sign = CCSimdShiftLeftN_u32x2(CCSimdMaskCompareLessThan_f32x2(y, Zero), 31);
#else // [-pi, pi]
    const CCSimd_u32x2 Sign = CCSimdShiftLeftN_u32x2(CCSimdShiftRightN_u32x2(CCSimd_u32x2_Reinterpret_f32x2(y), 31), 31);
#endif
#if defined(CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO) || defined(CC_SIMD_ARCTAN2_UNDEFINED)
    const CCSimd_u32x2 IsZero = CCSimdOr_u32x2(MaskX, CCSimdMaskCompareNotEqual_f32x2(y, Zero));
#endif
#ifdef CC_SIMD_ARCTAN2_UNDEFINED
    const CCSimd_f32x2 Undefined = CCSimdFill_f32x2(CC_SIMD_ARCTAN2_UNDEFINED);
#endif
        
    const CCSimd_f32x2 ResultYX = CCSimd_f32x2_Reinterpret_u32x2(CCSimdAnd_u32x2(CCSimd_u32x2_Reinterpret_f32x2(CCSimdArcTan_f32x2(CCSimdDiv_f32x2(y, x))), MaskX));
    const CCSimd_f32x2 ResultPi = CCSimd_f32x2_Reinterpret_u32x2(CCSimdOr_u32x2(Sign, CCSimdOr_u32x2(CCSimdAndNot_u32x2(MaskX, CCSimd_u32x2_Reinterpret_f32x2(HalfPi)), CCSimdAnd_u32x2(CCSimdAnd_u32x2(MaskX, CCSimd_u32x2_Reinterpret_f32x2(Pi)), MaskY))));
    
    CCSimd_f32x2 Result = CCSimdAdd_f32x2(ResultYX, ResultPi);
    
#ifdef CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO
    return CCSimd_f32x2_Reinterpret_u32x2(CCSimdAnd_u32x2(IsZero, CCSimd_u32x2_Reinterpret_f32x2(Result)));
#elif defined(CC_SIMD_ARCTAN2_UNDEFINED)
    return CCSimd_f32x2_Reinterpret_u32x2(CCSimdOr_u32x2(CCSimdAnd_u32x2(IsZero, CCSimd_u32x2_Reinterpret_f32x2(Result)), CCSimdAndNot_u32x2(IsZero, CCSimd_u32x2_Reinterpret_f32x2(Undefined))));
#else
    return Result;
#endif
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdCsc_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCsc_f32x2(const CCSimd_f32x2 a)
{
    return CCSimdDiv_f32x2(CCSimdFill_f32x2(1.0f), CCSimdSin_f32x2(a));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdSec_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdSec_f32x2(const CCSimd_f32x2 a)
{
    return CCSimdDiv_f32x2(CCSimdFill_f32x2(1.0f), CCSimdCos_f32x2(a));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdCot_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCot_f32x2(const CCSimd_f32x2 a)
{
    return CCSimdDiv_f32x2(CCSimdFill_f32x2(1.0f), CCSimdTan_f32x2(a));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdLog2_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdLog2_f32x2(const CCSimd_f32x2 a)
{
    // Based off Paul Mineiro's fastlog2 from fastapprox v0.3.2: http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    const CCSimd_f32x2 C0 = CCSimdFill_f32x2(1.1920928955078125e-7f);
    const CCSimd_f32x2 C1 = CCSimdFill_f32x2(124.22551499f);
    const CCSimd_f32x2 C2 = CCSimdFill_f32x2(1.498030302f);
    const CCSimd_f32x2 C3 = CCSimdFill_f32x2(1.72587999f);
    const CCSimd_f32x2 C4 = CCSimdFill_f32x2(0.3520887068f);
    const CCSimd_u32x2 U = CCSimdOr_u32x2(CCSimdAnd_u32x2(CCSimd_u32x2_Reinterpret_f32x2(a), CCSimdFill_u32x2(0x7fffff)), CCSimdFill_u32x2(0x3f000000));
    CCSimd_f32x2 Result = CCSimd_f32x2_Cast_u32x2(CCSimd_u32x2_Reinterpret_f32x2(a));
    
    Result = CCSimdMul_f32x2(Result, C0);
    
    return CCSimdSub_f32x2(CCSimdSub_f32x2(CCSimdSub_f32x2(Result, C1), CCSimdMul_f32x2(C2, CCSimd_f32x2_Reinterpret_u32x2(U))), CCSimdDiv_f32x2(C3, CCSimdAdd_f32x2(C4, CCSimd_f32x2_Reinterpret_u32x2(U))));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdLog_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdLog_f32x2(const CCSimd_f32x2 a)
{
    // Based off Paul Mineiro's fastlog from fastapprox v0.3.2: http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    return CCSimdMul_f32x2(CCSimdFill_f32x2(0.69314718f), CCSimdLog2_f32x2(a));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdPow_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPow_f32x2(const CCSimd_f32x2 Base, const CCSimd_f32x2 Exponent)
{
    return CCSimdExp_f32x2(CCSimdMul_f32x2(Exponent, CCSimdLog_f32x2(Base)));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdPow2_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdPow2_f32x2(const CCSimd_f32x2 Exponent)
{
    const CCSimd_s32x2 ExpBase = CCSimdFill_s32x2(0x7f);
    
    return CCSimd_f32x2_Reinterpret_s32x2(CCSimdShiftLeftN_s32x2(CCSimdAdd_s32x2(CCSimd_s32x2_Cast_f32x2(Exponent), ExpBase), 23));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdExp_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdExp_f32x2(const CCSimd_f32x2 a)
{
#if CC_SIMD_EXP_ACCURACY < 4
    // Taylor series approximation
    const CCSimd_f32x2 x0 = CCSimdFill_f32x2(1.0f);
    const CCSimd_f32x2 x1 = a;
    const CCSimd_f32x2 x2 = CCSimdMul_f32x2(x1, x1);
    const CCSimd_f32x2 x3 = CCSimdMul_f32x2(x1, x2);
    
#if CC_SIMD_EXP_ACCURACY >= 1
    const CCSimd_f32x2 x4 = CCSimdMul_f32x2(x2, x2);
    const CCSimd_f32x2 x5 = CCSimdMul_f32x2(x2, x3);
#if CC_SIMD_EXP_ACCURACY >= 2
    const CCSimd_f32x2 x6 = CCSimdMul_f32x2(x3, x3);
    const CCSimd_f32x2 x7 = CCSimdMul_f32x2(x3, x4);
#if CC_SIMD_EXP_ACCURACY >= 3
    const CCSimd_f32x2 x8 = CCSimdMul_f32x2(x4, x4);
    const CCSimd_f32x2 x9 = CCSimdMul_f32x2(x4, x5);
#endif
#endif
#endif
    
    CCSimd_f32x2 Result = CCSimdAdd_f32x2(x0, x1);
    Result = CCSimdMadd_f32x2(x2, CCSimdFill_f32x2(1.0f / 2.0f), Result);
    Result = CCSimdMadd_f32x2(x3, CCSimdFill_f32x2(1.0f / 6.0f), Result);
    
#if CC_SIMD_EXP_ACCURACY >= 1
    Result = CCSimdMadd_f32x2(x4, CCSimdFill_f32x2(1.0f / 24.0f), Result);
    Result = CCSimdMadd_f32x2(x5, CCSimdFill_f32x2(1.0f / 120.0f), Result);
#if CC_SIMD_EXP_ACCURACY >= 2
    Result = CCSimdMadd_f32x2(x6, CCSimdFill_f32x2(1.0f / 720.0f), Result);
    Result = CCSimdMadd_f32x2(x7, CCSimdFill_f32x2(1.0f / 5040.0f), Result);
#if CC_SIMD_EXP_ACCURACY >= 3
    Result = CCSimdMadd_f32x2(x8, CCSimdFill_f32x2(1.0f / 40320.0f), Result);
    Result = CCSimdMadd_f32x2(x9, CCSimdFill_f32x2(1.0f / 362880.0f), Result);
#endif
#endif
#endif
    
    return CCSimdMax_f32x2(Result, CCSimdZero_f32x2());
#else
    // Based off Julien Pommier's SIMD adaptation of Cephes: http://gruntthepeon.free.fr/ssemath/
    const CCSimd_f32x2 One = CCSimdFill_f32x2(1.0f);
    const CCSimd_f32x2 Half = CCSimdFill_f32x2(0.5f);
    const CCSimd_f32x2 Min = CCSimdFill_f32x2(-88.3762626647949f);
    const CCSimd_f32x2 Max = CCSimdNeg_f32x2(Min);
    const CCSimd_f32x2 Log2e = CCSimdFill_f32x2(1.44269504088896341f);
    
    const CCSimd_f32x2 C1 = CCSimdFill_f32x2(0.693359375f);
    const CCSimd_f32x2 C2 = CCSimdFill_f32x2(-2.12194440e-4f);
    
    const CCSimd_f32x2 P0 = CCSimdFill_f32x2(1.9875691500e-4f);
    const CCSimd_f32x2 P1 = CCSimdFill_f32x2(1.3981999507e-3f);
    const CCSimd_f32x2 P2 = CCSimdFill_f32x2(8.3334519073e-3f);
    const CCSimd_f32x2 P3 = CCSimdFill_f32x2(4.1665795894e-2f);
    const CCSimd_f32x2 P4 = CCSimdFill_f32x2(1.6666665459e-1f);
    const CCSimd_f32x2 P5 = CCSimdFill_f32x2(5.0000001201e-1f);
    
    CCSimd_f32x2 x = CCSimdClamp_f32x2(a, Min, Max);
    CCSimd_f32x2 Px = CCSimdFloor_f32x2(CCSimdMadd_f32x2(x, Log2e, Half));
    
    x = CCSimdNegMadd_f32x2(Px, C1, x);
    x = CCSimdNegMadd_f32x2(Px, C2, x);
    
    CCSimd_f32x2 xx = CCSimdMul_f32x2(x, x);
    
    CCSimd_f32x2 Result = P0;
    Result = CCSimdMadd_f32x2(Result, x, P1);
    Result = CCSimdMadd_f32x2(Result, x, P2);
    Result = CCSimdMadd_f32x2(Result, x, P3);
    Result = CCSimdMadd_f32x2(Result, x, P4);
    Result = CCSimdMadd_f32x2(Result, x, P5);
    Result = CCSimdMadd_f32x2(Result, xx, x);
    Result = CCSimdAdd_f32x2(Result, One);
    
    return CCSimdMul_f32x2(Result, CCSimdPow2_f32x2(Px));
#endif
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdExp2_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdExp2_f32x2(const CCSimd_f32x2 a)
{
#if CC_SIMD_EXP2_ACCURACY < 2
    // Based off Hao Hao Tan's 3rd-order polynomial approximation: https://gudgud96.github.io/2024/01/02/exp-2/
    const CCSimd_f32x2 C0 = CCSimdFill_f32x2(0.05700169f);
    const CCSimd_f32x2 C1 = CCSimdFill_f32x2(0.24858144f);
    const CCSimd_f32x2 C2 = CCSimdFill_f32x2(0.69282515f);
    const CCSimd_f32x2 C3 = CCSimdFill_f32x2(0.99916080f);
    
    const CCSimd_f32x2 Fractional = CCSimdSub_f32x2(a, CCSimdRoundZero_f32x2(a));
    
    CCSimd_f32x2 Result = Fractional;
    Result = CCSimdMadd_f32x2(Result, C0, C1);
    Result = CCSimdMadd_f32x2(Result, Fractional, C2);
    Result = CCSimdMadd_f32x2(Result, Fractional, C3);
    
    return CCSimdMul_f32x2(Result, CCSimdPow2_f32x2(a));
#else
    // Based off Paul Mineiro's fastpow2 from fastapprox v0.3.2: http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    const CCSimd_f32x2 Zero = CCSimdZero_f32x2();
    const CCSimd_f32x2 Min = CCSimdFill_f32x2(-126.0f);
    const CCSimd_f32x2 C127 = CCSimdFill_f32x2(121.2740575f);
    const CCSimd_f32x2 C27 = CCSimdFill_f32x2(27.7280233f);
    const CCSimd_f32x2 C4 = CCSimdFill_f32x2(4.84252568f);
    const CCSimd_f32x2 C1 = CCSimdFill_f32x2(1.49012907f);
    const CCSimd_f32x2 Base = CCSimdFill_f32x2(0x800000);
    
    const CCSimd_f32x2 Offset = CCSimdCompareLessThan_f32x2(a, Zero);
    
    const CCSimd_f32x2 Mask = CCSimdMaskCompareLessThan_f32x2(a, Min);
    const CCSimd_f32x2 Clip = CCSimd_f32x2_Reinterpret_u32x2(CCSimdOr_u32x2(CCSimdAndNot_u32x2(Mask, CCSimd_u32x2_Reinterpret_f32x2(a)), CCSimdAnd_u32x2(Mask, CCSimd_u32x2_Reinterpret_f32x2(Min))));
    
    const CCSimd_f32x2 Z = CCSimdSub_f32x2(CCSimdAdd_f32x2(Clip, Offset), CCSimdRoundZero_f32x2(Clip));
    
    CCSimd_f32x2 Result = CCSimdNegMadd_f32x2(C1, Z, CCSimdAdd_f32x2(CCSimdAdd_f32x2(Clip, C127), CCSimdDiv_f32x2(C27, CCSimdSub_f32x2(C4, Z))));
    
    return CCSimd_f32x2_Reinterpret_u32x2(CCSimd_u32x2_Cast_f32x2(CCSimdMul_f32x2(Base, Result)));
#endif
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdCbrt_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdCbrt_f32x2(const CCSimd_f32x2 a)
{
    return CCSimdPow_f32x2(a, CCSimdFill_f32x2(1.0f / 3.0f));
}
#endif

#ifdef CC_SIMD_MISSING_CCSimdInvCbrt_f32x2
static CC_FORCE_INLINE CCSimd_f32x2 CCSimdInvCbrt_f32x2(const CCSimd_f32x2 a)
{
    return CCSimdDiv_f32x2(CCSimdFill_f32x2(1.0f), CCSimdCbrt_f32x2(a));
}
#endif

#endif
