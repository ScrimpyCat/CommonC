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

#ifndef CommonC_Types_h
#define CommonC_Types_h

#include <CommonC/Base.h>
#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>

typedef union {
    struct {
        float x, y;
    } CC_PACKED;
    struct {
        float s, t;
    } CC_PACKED;
    float v[2];
} CCVector2D;

typedef union {
    struct {
        int32_t x, y;
    } CC_PACKED;
    struct {
        int32_t s, t;
    } CC_PACKED;
    int32_t v[2];
} CCVector2Di;

typedef union {
    struct {
        float x, y, z;
    } CC_PACKED;
    struct {
        float r, g, b;
    } CC_PACKED;
    struct {
        float s, t, p;
    } CC_PACKED;
    float v[3];
} CCVector3D, CCColourRGB;

typedef union {
    struct {
        int32_t x, y, z;
    } CC_PACKED;
    struct {
        int32_t r, g, b;
    } CC_PACKED;
    struct {
        int32_t s, t, p;
    } CC_PACKED;
    int32_t v[3];
} CCVector3Di, CCColourRGBi;

typedef union {
    _Alignas(16) struct {
        float x, y, z, w;
    } CC_PACKED;
    _Alignas(16) struct {
        float r, g, b, a;
    } CC_PACKED;
    _Alignas(16) struct {
        float s, t, p, q;
    } CC_PACKED;
    _Alignas(16) float v[4];
} CCVector4D, CCColourRGBA;

typedef union {
    struct {
        int32_t x, y, z, w;
    } CC_PACKED;
    struct {
        int32_t r, g, b, a;
    } CC_PACKED;
    struct {
        int32_t s, t, p, q;
    } CC_PACKED;
    int32_t v[4];
} CCVector4Di, CCColourRGBAi;

typedef struct {
    CCVector2D position, size;
} CCRect;

typedef struct {
    CCVector2Di position, size;
} CCRecti;

typedef union {
    struct {
        CCVector2D x;
        CCVector2D y;
    } CC_PACKED;
    struct {
        CCVector2D c[2];
    } CC_PACKED;
} CCMatrix2;

typedef union {
    struct {
        CCVector3D x;
        CCVector3D y;
        CCVector3D z;
    } CC_PACKED;
    struct {
        CCVector3D c[3];
    } CC_PACKED;
} CCMatrix3;

typedef union {
    struct {
        CCVector4D x;
        CCVector4D y;
        CCVector4D z;
        CCVector4D w;
    } CC_PACKED;
    struct {
        CCVector4D c[4];
    } CC_PACKED;
} CCMatrix4;


#if CC_HARDWARE_VECTOR_SUPPORT_SSE
#include <immintrin.h>

typedef __m128 CCVector;
#else
typedef CCVector4D CCVector;
#endif

#pragma mark -

// MARK: CCVector2D
#define CC_TYPE_CCVector2D(...) CCVector2D
#define CC_TYPE_0_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_1_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_2_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_3_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_4_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_5_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_6_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_7_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_8_CCVector2D CC_TYPE_CCVector2D,
#define CC_TYPE_9_CCVector2D CC_TYPE_CCVector2D,

#define CC_PRESERVE_CC_TYPE_CCVector2D CC_TYPE_CCVector2D

#define CC_TYPE_DECL_CCVector2D(...) CCVector2D, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_1_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_2_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_3_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_4_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_5_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_6_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_7_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_8_CCVector2D CC_TYPE_DECL_CCVector2D,
#define CC_TYPE_DECL_9_CCVector2D CC_TYPE_DECL_CCVector2D,

#define CC_MANGLE_TYPE_0_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_1_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_2_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_3_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_4_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_5_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_6_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_7_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_8_CCVector2D CCVector2D
#define CC_MANGLE_TYPE_9_CCVector2D CCVector2D

// MARK: CCVector2Di
#define CC_TYPE_CCVector2Di(...) CCVector2Di
#define CC_TYPE_0_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_1_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_2_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_3_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_4_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_5_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_6_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_7_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_8_CCVector2Di CC_TYPE_CCVector2Di,
#define CC_TYPE_9_CCVector2Di CC_TYPE_CCVector2Di,

#define CC_PRESERVE_CC_TYPE_CCVector2Di CC_TYPE_CCVector2Di

#define CC_TYPE_DECL_CCVector2Di(...) CCVector2Di, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_1_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_2_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_3_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_4_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_5_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_6_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_7_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_8_CCVector2Di CC_TYPE_DECL_CCVector2Di,
#define CC_TYPE_DECL_9_CCVector2Di CC_TYPE_DECL_CCVector2Di,

#define CC_MANGLE_TYPE_0_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_1_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_2_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_3_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_4_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_5_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_6_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_7_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_8_CCVector2Di CCVector2Di
#define CC_MANGLE_TYPE_9_CCVector2Di CCVector2Di

// MARK: CCVector3D
#define CC_TYPE_CCVector3D(...) CCVector3D
#define CC_TYPE_0_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_1_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_2_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_3_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_4_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_5_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_6_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_7_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_8_CCVector3D CC_TYPE_CCVector3D,
#define CC_TYPE_9_CCVector3D CC_TYPE_CCVector3D,

#define CC_PRESERVE_CC_TYPE_CCVector3D CC_TYPE_CCVector3D

#define CC_TYPE_DECL_CCVector3D(...) CCVector3D, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_1_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_2_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_3_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_4_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_5_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_6_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_7_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_8_CCVector3D CC_TYPE_DECL_CCVector3D,
#define CC_TYPE_DECL_9_CCVector3D CC_TYPE_DECL_CCVector3D,

#define CC_MANGLE_TYPE_0_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_1_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_2_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_3_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_4_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_5_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_6_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_7_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_8_CCVector3D CCVector3D
#define CC_MANGLE_TYPE_9_CCVector3D CCVector3D

// MARK: CCColourRGB
#define CC_TYPE_CCColourRGB(...) CCColourRGB
#define CC_TYPE_0_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_1_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_2_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_3_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_4_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_5_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_6_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_7_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_8_CCColourRGB CC_TYPE_CCColourRGB,
#define CC_TYPE_9_CCColourRGB CC_TYPE_CCColourRGB,

#define CC_PRESERVE_CC_TYPE_CCColourRGB CC_TYPE_CCColourRGB

#define CC_TYPE_DECL_CCColourRGB(...) CCColourRGB, __VA_ARGS__
#define CC_TYPE_DECL_0_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_1_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_2_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_3_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_4_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_5_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_6_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_7_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_8_CCColourRGB CC_TYPE_DECL_CCColourRGB,
#define CC_TYPE_DECL_9_CCColourRGB CC_TYPE_DECL_CCColourRGB,

#define CC_MANGLE_TYPE_0_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_1_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_2_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_3_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_4_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_5_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_6_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_7_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_8_CCColourRGB CCColourRGB
#define CC_MANGLE_TYPE_9_CCColourRGB CCColourRGB

// MARK: CCVector3Di
#define CC_TYPE_CCVector3Di(...) CCVector3Di
#define CC_TYPE_0_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_1_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_2_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_3_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_4_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_5_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_6_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_7_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_8_CCVector3Di CC_TYPE_CCVector3Di,
#define CC_TYPE_9_CCVector3Di CC_TYPE_CCVector3Di,

#define CC_PRESERVE_CC_TYPE_CCVector3Di CC_TYPE_CCVector3Di

#define CC_TYPE_DECL_CCVector3Di(...) CCVector3Di, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_1_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_2_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_3_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_4_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_5_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_6_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_7_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_8_CCVector3Di CC_TYPE_DECL_CCVector3Di,
#define CC_TYPE_DECL_9_CCVector3Di CC_TYPE_DECL_CCVector3Di,

#define CC_MANGLE_TYPE_0_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_1_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_2_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_3_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_4_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_5_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_6_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_7_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_8_CCVector3Di CCVector3Di
#define CC_MANGLE_TYPE_9_CCVector3Di CCVector3Di

// MARK: CCColourRGBi
#define CC_TYPE_CCColourRGBi(...) CCColourRGBi
#define CC_TYPE_0_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_1_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_2_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_3_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_4_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_5_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_6_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_7_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_8_CCColourRGBi CC_TYPE_CCColourRGBi,
#define CC_TYPE_9_CCColourRGBi CC_TYPE_CCColourRGBi,

#define CC_PRESERVE_CC_TYPE_CCColourRGBi CC_TYPE_CCColourRGBi

#define CC_TYPE_DECL_CCColourRGBi(...) CCColourRGBi, __VA_ARGS__
#define CC_TYPE_DECL_0_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_1_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_2_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_3_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_4_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_5_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_6_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_7_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_8_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,
#define CC_TYPE_DECL_9_CCColourRGBi CC_TYPE_DECL_CCColourRGBi,

#define CC_MANGLE_TYPE_0_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_1_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_2_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_3_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_4_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_5_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_6_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_7_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_8_CCColourRGBi CCColourRGBi
#define CC_MANGLE_TYPE_9_CCColourRGBi CCColourRGBi

// MARK: CCVector4D
#define CC_TYPE_CCVector4D(...) CCVector4D
#define CC_TYPE_0_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_1_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_2_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_3_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_4_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_5_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_6_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_7_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_8_CCVector4D CC_TYPE_CCVector4D,
#define CC_TYPE_9_CCVector4D CC_TYPE_CCVector4D,

#define CC_PRESERVE_CC_TYPE_CCVector4D CC_TYPE_CCVector4D

#define CC_TYPE_DECL_CCVector4D(...) CCVector4D, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_1_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_2_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_3_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_4_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_5_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_6_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_7_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_8_CCVector4D CC_TYPE_DECL_CCVector4D,
#define CC_TYPE_DECL_9_CCVector4D CC_TYPE_DECL_CCVector4D,

#define CC_MANGLE_TYPE_0_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_1_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_2_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_3_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_4_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_5_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_6_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_7_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_8_CCVector4D CCVector4D
#define CC_MANGLE_TYPE_9_CCVector4D CCVector4D

// MARK: CCColourRGBA
#define CC_TYPE_CCColourRGBA(...) CCColourRGBA
#define CC_TYPE_0_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_1_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_2_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_3_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_4_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_5_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_6_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_7_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_8_CCColourRGBA CC_TYPE_CCColourRGBA,
#define CC_TYPE_9_CCColourRGBA CC_TYPE_CCColourRGBA,

#define CC_PRESERVE_CC_TYPE_CCColourRGBA CC_TYPE_CCColourRGBA

#define CC_TYPE_DECL_CCColourRGBA(...) CCColourRGBA, __VA_ARGS__
#define CC_TYPE_DECL_0_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_1_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_2_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_3_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_4_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_5_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_6_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_7_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_8_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,
#define CC_TYPE_DECL_9_CCColourRGBA CC_TYPE_DECL_CCColourRGBA,

#define CC_MANGLE_TYPE_0_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_1_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_2_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_3_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_4_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_5_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_6_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_7_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_8_CCColourRGBA CCColourRGBA
#define CC_MANGLE_TYPE_9_CCColourRGBA CCColourRGBA

// MARK: CCVector4Di
#define CC_TYPE_CCVector4Di(...) CCVector4Di
#define CC_TYPE_0_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_1_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_2_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_3_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_4_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_5_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_6_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_7_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_8_CCVector4Di CC_TYPE_CCVector4Di,
#define CC_TYPE_9_CCVector4Di CC_TYPE_CCVector4Di,

#define CC_PRESERVE_CC_TYPE_CCVector4Di CC_TYPE_CCVector4Di

#define CC_TYPE_DECL_CCVector4Di(...) CCVector4Di, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_1_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_2_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_3_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_4_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_5_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_6_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_7_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_8_CCVector4Di CC_TYPE_DECL_CCVector4Di,
#define CC_TYPE_DECL_9_CCVector4Di CC_TYPE_DECL_CCVector4Di,

#define CC_MANGLE_TYPE_0_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_1_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_2_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_3_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_4_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_5_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_6_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_7_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_8_CCVector4Di CCVector4Di
#define CC_MANGLE_TYPE_9_CCVector4Di CCVector4Di

// MARK: CCColourRGBAi
#define CC_TYPE_CCColourRGBAi(...) CCColourRGBAi
#define CC_TYPE_0_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_1_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_2_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_3_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_4_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_5_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_6_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_7_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_8_CCColourRGBAi CC_TYPE_CCColourRGBAi,
#define CC_TYPE_9_CCColourRGBAi CC_TYPE_CCColourRGBAi,

#define CC_PRESERVE_CC_TYPE_CCColourRGBAi CC_TYPE_CCColourRGBAi

#define CC_TYPE_DECL_CCColourRGBAi(...) CCColourRGBAi, __VA_ARGS__
#define CC_TYPE_DECL_0_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_1_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_2_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_3_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_4_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_5_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_6_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_7_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_8_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,
#define CC_TYPE_DECL_9_CCColourRGBAi CC_TYPE_DECL_CCColourRGBAi,

#define CC_MANGLE_TYPE_0_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_1_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_2_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_3_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_4_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_5_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_6_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_7_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_8_CCColourRGBAi CCColourRGBAi
#define CC_MANGLE_TYPE_9_CCColourRGBAi CCColourRGBAi

// MARK: CCRect
#define CC_TYPE_CCRect(...) CCRect
#define CC_TYPE_0_CCRect CC_TYPE_CCRect,
#define CC_TYPE_1_CCRect CC_TYPE_CCRect,
#define CC_TYPE_2_CCRect CC_TYPE_CCRect,
#define CC_TYPE_3_CCRect CC_TYPE_CCRect,
#define CC_TYPE_4_CCRect CC_TYPE_CCRect,
#define CC_TYPE_5_CCRect CC_TYPE_CCRect,
#define CC_TYPE_6_CCRect CC_TYPE_CCRect,
#define CC_TYPE_7_CCRect CC_TYPE_CCRect,
#define CC_TYPE_8_CCRect CC_TYPE_CCRect,
#define CC_TYPE_9_CCRect CC_TYPE_CCRect,

#define CC_PRESERVE_CC_TYPE_CCRect CC_TYPE_CCRect

#define CC_TYPE_DECL_CCRect(...) CCRect, __VA_ARGS__
#define CC_TYPE_DECL_0_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_1_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_2_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_3_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_4_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_5_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_6_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_7_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_8_CCRect CC_TYPE_DECL_CCRect,
#define CC_TYPE_DECL_9_CCRect CC_TYPE_DECL_CCRect,

#define CC_MANGLE_TYPE_0_CCRect CCRect
#define CC_MANGLE_TYPE_1_CCRect CCRect
#define CC_MANGLE_TYPE_2_CCRect CCRect
#define CC_MANGLE_TYPE_3_CCRect CCRect
#define CC_MANGLE_TYPE_4_CCRect CCRect
#define CC_MANGLE_TYPE_5_CCRect CCRect
#define CC_MANGLE_TYPE_6_CCRect CCRect
#define CC_MANGLE_TYPE_7_CCRect CCRect
#define CC_MANGLE_TYPE_8_CCRect CCRect
#define CC_MANGLE_TYPE_9_CCRect CCRect

// MARK: CCMatrix2
#define CC_TYPE_CCMatrix2(...) CCMatrix2
#define CC_TYPE_0_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_1_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_2_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_3_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_4_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_5_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_6_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_7_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_8_CCMatrix2 CC_TYPE_CCMatrix2,
#define CC_TYPE_9_CCMatrix2 CC_TYPE_CCMatrix2,

#define CC_PRESERVE_CC_TYPE_CCMatrix2 CC_TYPE_CCMatrix2

#define CC_TYPE_DECL_CCMatrix2(...) CCMatrix2, __VA_ARGS__
#define CC_TYPE_DECL_0_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_1_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_2_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_3_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_4_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_5_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_6_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_7_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_8_CCMatrix2 CC_TYPE_DECL_CCMatrix2,
#define CC_TYPE_DECL_9_CCMatrix2 CC_TYPE_DECL_CCMatrix2,

#define CC_MANGLE_TYPE_0_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_1_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_2_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_3_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_4_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_5_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_6_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_7_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_8_CCMatrix2 CCMatrix2
#define CC_MANGLE_TYPE_9_CCMatrix2 CCMatrix2

// MARK: CCMatrix3
#define CC_TYPE_CCMatrix3(...) CCMatrix3
#define CC_TYPE_0_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_1_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_2_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_3_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_4_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_5_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_6_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_7_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_8_CCMatrix3 CC_TYPE_CCMatrix3,
#define CC_TYPE_9_CCMatrix3 CC_TYPE_CCMatrix3,

#define CC_PRESERVE_CC_TYPE_CCMatrix3 CC_TYPE_CCMatrix3

#define CC_TYPE_DECL_CCMatrix3(...) CCMatrix3, __VA_ARGS__
#define CC_TYPE_DECL_0_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_1_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_2_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_3_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_4_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_5_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_6_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_7_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_8_CCMatrix3 CC_TYPE_DECL_CCMatrix3,
#define CC_TYPE_DECL_9_CCMatrix3 CC_TYPE_DECL_CCMatrix3,

#define CC_MANGLE_TYPE_0_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_1_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_2_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_3_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_4_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_5_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_6_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_7_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_8_CCMatrix3 CCMatrix3
#define CC_MANGLE_TYPE_9_CCMatrix3 CCMatrix3

// MARK: CCMatrix4
#define CC_TYPE_CCMatrix4(...) CCMatrix4
#define CC_TYPE_0_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_1_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_2_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_3_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_4_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_5_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_6_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_7_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_8_CCMatrix4 CC_TYPE_CCMatrix4,
#define CC_TYPE_9_CCMatrix4 CC_TYPE_CCMatrix4,

#define CC_PRESERVE_CC_TYPE_CCMatrix4 CC_TYPE_CCMatrix4

#define CC_TYPE_DECL_CCMatrix4(...) CCMatrix4, __VA_ARGS__
#define CC_TYPE_DECL_0_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_1_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_2_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_3_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_4_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_5_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_6_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_7_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_8_CCMatrix4 CC_TYPE_DECL_CCMatrix4,
#define CC_TYPE_DECL_9_CCMatrix4 CC_TYPE_DECL_CCMatrix4,

#define CC_MANGLE_TYPE_0_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_1_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_2_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_3_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_4_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_5_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_6_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_7_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_8_CCMatrix4 CCMatrix4
#define CC_MANGLE_TYPE_9_CCMatrix4 CCMatrix4

// MARK: CCVector
#define CC_TYPE_CCVector(...) CCVector
#define CC_TYPE_0_CCVector CC_TYPE_CCVector,
#define CC_TYPE_1_CCVector CC_TYPE_CCVector,
#define CC_TYPE_2_CCVector CC_TYPE_CCVector,
#define CC_TYPE_3_CCVector CC_TYPE_CCVector,
#define CC_TYPE_4_CCVector CC_TYPE_CCVector,
#define CC_TYPE_5_CCVector CC_TYPE_CCVector,
#define CC_TYPE_6_CCVector CC_TYPE_CCVector,
#define CC_TYPE_7_CCVector CC_TYPE_CCVector,
#define CC_TYPE_8_CCVector CC_TYPE_CCVector,
#define CC_TYPE_9_CCVector CC_TYPE_CCVector,

#define CC_PRESERVE_CC_TYPE_CCVector CC_TYPE_CCVector

#define CC_TYPE_DECL_CCVector(...) CCVector, __VA_ARGS__
#define CC_TYPE_DECL_0_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_1_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_2_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_3_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_4_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_5_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_6_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_7_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_8_CCVector CC_TYPE_DECL_CCVector,
#define CC_TYPE_DECL_9_CCVector CC_TYPE_DECL_CCVector,

#define CC_MANGLE_TYPE_0_CCVector CCVector
#define CC_MANGLE_TYPE_1_CCVector CCVector
#define CC_MANGLE_TYPE_2_CCVector CCVector
#define CC_MANGLE_TYPE_3_CCVector CCVector
#define CC_MANGLE_TYPE_4_CCVector CCVector
#define CC_MANGLE_TYPE_5_CCVector CCVector
#define CC_MANGLE_TYPE_6_CCVector CCVector
#define CC_MANGLE_TYPE_7_CCVector CCVector
#define CC_MANGLE_TYPE_8_CCVector CCVector
#define CC_MANGLE_TYPE_9_CCVector CCVector

#endif
