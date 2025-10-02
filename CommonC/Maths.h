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

#ifndef CommonC_Maths_h
#define CommonC_Maths_h

#include <math.h>
#include <CommonC/Platform.h>
#include <CommonC/Extensions.h>

#if CC_PLATFORM_POSIX_COMPLIANT
#define CC_PI M_PI
#else
#define CC_PI (4.0 * atan(1.0))
#endif

#define T float
#include <CommonC/Numeric.h>

#define T double
#include <CommonC/Numeric.h>

#define T int8_t
#include <CommonC/Numeric.h>

#define T int16_t
#include <CommonC/Numeric.h>

#define T int32_t
#include <CommonC/Numeric.h>

#define T int64_t
#include <CommonC/Numeric.h>

#define T uint8_t
#include <CommonC/Numeric.h>

#define T uint16_t
#include <CommonC/Numeric.h>

#define T uint32_t
#include <CommonC/Numeric.h>

#define T uint64_t
#include <CommonC/Numeric.h>

#define T size_t
#include <CommonC/Numeric.h>

#define T ptrdiff_t
#include <CommonC/Numeric.h>

#define T intptr_t
#include <CommonC/Numeric.h>

#define T uintptr_t
#include <CommonC/Numeric.h>

#define T intmax_t
#include <CommonC/Numeric.h>

#define T uintmax_t
#include <CommonC/Numeric.h>

#define CC_EXTREMA_PRESERVE_IMPS
#define CC_MIN(a, b) ((a) < (b) ? (a) : (b))
#define CC_MAX(a, b) ((a) > (b) ? (a) : (b))

#define T float
#include <CommonC/Extrema.h>

#define T double
#include <CommonC/Extrema.h>

#define T int8_t
#include <CommonC/Extrema.h>

#define T int16_t
#include <CommonC/Extrema.h>

#define T int32_t
#include <CommonC/Extrema.h>

#define T int64_t
#include <CommonC/Extrema.h>

#define T uint8_t
#include <CommonC/Extrema.h>

#define T uint16_t
#include <CommonC/Extrema.h>

#define T uint32_t
#include <CommonC/Extrema.h>

#define T uint64_t
#include <CommonC/Extrema.h>

#define T size_t
#include <CommonC/Extrema.h>

#define T ptrdiff_t
#include <CommonC/Extrema.h>

#define T intptr_t
#include <CommonC/Extrema.h>

#define T uintptr_t
#include <CommonC/Extrema.h>

#define T intmax_t
#include <CommonC/Extrema.h>

#undef CC_EXTREMA_PRESERVE_IMPS
#define T uintmax_t
#include <CommonC/Extrema.h>

static CC_FORCE_INLINE uint32_t CCFloatGetUlps(const float a, const float b)
{
    return *(uint32_t*)&a > *(uint32_t*)&b ? *(uint32_t*)&a - *(uint32_t*)&b : *(uint32_t*)&b - *(uint32_t*)&a;
}

static CC_FORCE_INLINE _Bool CCFloatEqualUlps(const float a, const float b, const uint32_t MaxUlps)
{
    if (signbit(a) != signbit(b)) return a == b;
    
    return CCFloatGetUlps(a, b) <= MaxUlps;
}

static CC_FORCE_INLINE _Bool CCFloatEqualRelative(float a, float b, const float RelativeDiff)
{
    float Diff = fabsf(a - b);
    
    a = fabsf(a);
    b = fabsf(b);
    
    return Diff <= ((a > b ? a : b) * RelativeDiff);
}

static CC_FORCE_INLINE _Bool CCFloatEqualAbsolute(const float a, const float b, const float Diff)
{
    return fabsf(a - b) <= Diff;
}

#endif
