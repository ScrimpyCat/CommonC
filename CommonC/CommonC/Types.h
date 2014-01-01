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

#include <stdint.h>
#include <stdbool.h>

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif


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
    struct {
        float x, y, z, w;
    } CC_PACKED;
    struct {
        float r, g, b, a;
    } CC_PACKED;
    struct {
        float s, t, p, q;
    } CC_PACKED;
    float v[4];
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


#if CC_HARDWARE_VECTOR_SUPPORT_SSE
#include <immintrin.h>

typedef __v4sf CCVector;
#else
typedef CCVector4D CCVector;
#endif

#endif
