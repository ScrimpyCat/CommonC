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

#ifndef CommonC_Simd64Types_arm_h
#define CommonC_Simd64Types_arm_h

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
