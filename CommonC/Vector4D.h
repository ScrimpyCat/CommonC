/*
 *  Copyright (c) 2016, Stefan Johnson
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

#ifndef CommonC_Vector4D_h
#define CommonC_Vector4D_h

#include <CommonC/Types.h>
#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <CommonC/Maths.h>
#include <math.h>


#define CCVector4DMake(x, y, z, w) (CCVector4D){ (x), (y), (z), (w) }
#define CCVector4DFill(x) CCVector4DMake(x, x, x, x)
#define CCVector4DZero CCVector4DFill(0.0f)

#define CCVector4DiMake(x, y, z, w) (CCVector4Di){ (x), (y), (z), (w) }
#define CCVector4DiFill(x) CCVector4DiMake(x, x, x, x)
#define CCVector4DiZero CCVector4DiFill(0)



#pragma mark - Vectorized Vector4D

static CC_FORCE_INLINE CCVector CCVectorizeVector4D(const CCVector4D a);
static CC_FORCE_INLINE CCVector4D CCVectorizeGetVector4D(const CCVector a);

static CC_FORCE_INLINE CCVector CCVectorize4Add(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Sub(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Mul(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Div(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4AddScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize4SubScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize4MulScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize4DivScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize4Dot(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Length(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize4Distance(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4DistanceSquare(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Angle(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Cross(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Lerp(const CCVector a, const CCVector b, const float t);
static CC_FORCE_INLINE CCVector CCVectorize4Project(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Reject(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Perp(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize4PerpR(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize4Normal(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize4NormalR(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize4Normalize(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize4Neg(const CCVector a);

static CC_FORCE_INLINE CCVector CCVectorize4Min(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Max(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize4Clamp(const CCVector a, const CCVector min, const CCVector max);


#pragma mark - Vector4D

static CC_FORCE_INLINE CCVector4D CCVector4Add(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Sub(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Mul(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Div(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4AddScalar(const CCVector4D a, const float b);
static CC_FORCE_INLINE CCVector4D CCVector4SubScalar(const CCVector4D a, const float b);
static CC_FORCE_INLINE CCVector4D CCVector4MulScalar(const CCVector4D a, const float b);
static CC_FORCE_INLINE CCVector4D CCVector4DivScalar(const CCVector4D a, const float b);
static CC_FORCE_INLINE float CCVector4Dot(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE float CCVector4Length(const CCVector4D a);
static CC_FORCE_INLINE float CCVector4Distance(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE float CCVector4DistanceSquare(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE float CCVector4Angle(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Cross(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Lerp(const CCVector4D a, const CCVector4D b, const float t);
static CC_FORCE_INLINE CCVector4D CCVector4Project(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Reject(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Perp(const CCVector4D a, const CCVector4D b, const CCVector4D c);
static CC_FORCE_INLINE CCVector4D CCVector4PerpR(const CCVector4D a, const CCVector4D b, const CCVector4D c);
static CC_FORCE_INLINE CCVector4D CCVector4Normal(const CCVector4D a, const CCVector4D b, const CCVector4D c);
static CC_FORCE_INLINE CCVector4D CCVector4NormalR(const CCVector4D a, const CCVector4D b, const CCVector4D c);
static CC_FORCE_INLINE CCVector4D CCVector4Normalize(const CCVector4D a);
static CC_FORCE_INLINE CCVector4D CCVector4Neg(const CCVector4D a);
static CC_FORCE_INLINE _Bool CCVector4Parallel(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE _Bool CCVector4Ortho(const CCVector4D a, const CCVector4D b);

static CC_FORCE_INLINE CCVector4D CCVector4Min(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Max(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4Clamp(const CCVector4D a, const CCVector4D min, const CCVector4D max);

static CC_FORCE_INLINE _Bool CCVector4EqualUlps(const CCVector4D a, const CCVector4D b, CCVector4Di MaxUlps);
static CC_FORCE_INLINE _Bool CCVector4EqualRelative(const CCVector4D a, const CCVector4D b, const CCVector4D RelativeDiff);
static CC_FORCE_INLINE _Bool CCVector4EqualAbsolute(const CCVector4D a, const CCVector4D b, const CCVector4D Diff);
static CC_FORCE_INLINE _Bool CCVector4Equal(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE _Bool CCVector4LessThan(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE _Bool CCVector4LessThanEqual(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE _Bool CCVector4GreaterThan(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE _Bool CCVector4GreaterThanEqual(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4CompareEqualUlps(const CCVector4D a, const CCVector4D b, CCVector4Di MaxUlps);
static CC_FORCE_INLINE CCVector4D CCVector4CompareEqualRelative(const CCVector4D a, const CCVector4D b, const CCVector4D RelativeDiff);
static CC_FORCE_INLINE CCVector4D CCVector4CompareEqualAbsolute(const CCVector4D a, const CCVector4D b, const CCVector4D Diff);
static CC_FORCE_INLINE CCVector4D CCVector4CompareEqual(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4CompareLessThan(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4CompareLessThanEqual(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4CompareGreaterThan(const CCVector4D a, const CCVector4D b);
static CC_FORCE_INLINE CCVector4D CCVector4CompareGreaterThanEqual(const CCVector4D a, const CCVector4D b);


#pragma mark -
#pragma mark Vector, Vector operations

static CC_FORCE_INLINE CCVector4D CCVector4Add(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4Sub(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4Mul(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4Div(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
}

static CC_FORCE_INLINE float CCVector4Dot(const CCVector4D a, const CCVector4D b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

static CC_FORCE_INLINE float CCVector4Distance(const CCVector4D a, const CCVector4D b)
{
    return CCVector4Length(CCVector4Sub(a, b));
}

static CC_FORCE_INLINE float CCVector4DistanceSquare(const CCVector4D a, const CCVector4D b)
{
    CCVector4D d = CCVector4Sub(a, b);
    return CCVector4Dot(d, d);
}

static CC_FORCE_INLINE float CCVector4Angle(const CCVector4D a, const CCVector4D b)
{
    return CCVector4Dot(a, b) / (CCVector4Length(a) * CCVector4Length(b));
}

static CC_FORCE_INLINE CCVector4D CCVector4Cross(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
        0.0f
    };
}

static CC_FORCE_INLINE CCVector4D CCVector4Lerp(const CCVector4D a, const CCVector4D b, const float t)
{
    return CCVector4Add(a, CCVector4MulScalar(CCVector4Sub(b, a), t));
}

static CC_FORCE_INLINE CCVector4D CCVector4Project(const CCVector4D a, const CCVector4D b)
{
    return CCVector4MulScalar(b, CCVector4Dot(a, b) / CCVector4Dot(b, b));
}

static CC_FORCE_INLINE CCVector4D CCVector4Reject(const CCVector4D a, const CCVector4D b)
{
    return CCVector4Sub(a, CCVector4Project(a, b));
}

static CC_FORCE_INLINE CCVector4D CCVector4Min(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z, a.w < b.w ? a.w : b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4Max(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z, a.w > b.w ? a.w : b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4Clamp(const CCVector4D a, const CCVector4D min, const CCVector4D max)
{
    return CCVector4Min(CCVector4Max(a, min), max);
}

static CC_FORCE_INLINE _Bool CCVector4Parallel(const CCVector4D a, const CCVector4D b)
{
    CCVector4D v = CCVector4Cross(a, b);
    return (fabsf(v.x) < 1e-6f) && (fabsf(v.y) < 1e-6f) && (fabsf(v.z) < 1e-6f); //TODO: replace with better zero check
}

static CC_FORCE_INLINE _Bool CCVector4Ortho(const CCVector4D a, const CCVector4D b)
{
    return fabsf(CCVector4Dot(a, b)) < 1e-6f; //TODO: replace with better zero check
}

static CC_FORCE_INLINE _Bool CCVector4EqualUlps(const CCVector4D a, const CCVector4D b, CCVector4Di MaxUlps)
{
    return CCFloatEqualUlps(a.x, b.x, MaxUlps.x) && CCFloatEqualUlps(a.y, b.y, MaxUlps.y) && CCFloatEqualUlps(a.z, b.z, MaxUlps.z) && CCFloatEqualUlps(a.w, b.w, MaxUlps.w);
}

static CC_FORCE_INLINE _Bool CCVector4EqualRelative(const CCVector4D a, const CCVector4D b, const CCVector4D RelativeDiff)
{
    return CCFloatEqualRelative(a.x, b.x, RelativeDiff.x) && CCFloatEqualRelative(a.y, b.y, RelativeDiff.y) && CCFloatEqualRelative(a.z, b.z, RelativeDiff.z) && CCFloatEqualRelative(a.w, b.w, RelativeDiff.w);
}

static CC_FORCE_INLINE _Bool CCVector4EqualAbsolute(const CCVector4D a, const CCVector4D b, const CCVector4D Diff)
{
    return CCFloatEqualAbsolute(a.x, b.x, Diff.x) && CCFloatEqualAbsolute(a.y, b.y, Diff.y) && CCFloatEqualAbsolute(a.z, b.z, Diff.z) && CCFloatEqualAbsolute(a.w, b.w, Diff.w);
}

static CC_FORCE_INLINE _Bool CCVector4Equal(const CCVector4D a, const CCVector4D b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

static CC_FORCE_INLINE _Bool CCVector4LessThan(const CCVector4D a, const CCVector4D b)
{
    return a.x < b.x && a.y < b.y && a.z < b.z && a.w < b.w;
}

static CC_FORCE_INLINE _Bool CCVector4LessThanEqual(const CCVector4D a, const CCVector4D b)
{
    return a.x <= b.x && a.y <= b.y && a.z <= b.z && a.w <= b.w;
}

static CC_FORCE_INLINE _Bool CCVector4GreaterThan(const CCVector4D a, const CCVector4D b)
{
    return a.x > b.x && a.y > b.y && a.z > b.z && a.w > b.w;
}

static CC_FORCE_INLINE _Bool CCVector4GreaterThanEqual(const CCVector4D a, const CCVector4D b)
{
    return a.x >= b.x && a.y >= b.y && a.z >= b.z && a.w >= b.w;
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareEqualUlps(const CCVector4D a, const CCVector4D b, CCVector4Di MaxUlps)
{
    return (CCVector4D){ CCFloatEqualUlps(a.x, b.x, MaxUlps.x), CCFloatEqualUlps(a.y, b.y, MaxUlps.y), CCFloatEqualUlps(a.z, b.z, MaxUlps.z), CCFloatEqualUlps(a.w, b.w, MaxUlps.w) };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareEqualRelative(const CCVector4D a, const CCVector4D b, const CCVector4D RelativeDiff)
{
    return (CCVector4D){ CCFloatEqualRelative(a.x, b.x, RelativeDiff.x), CCFloatEqualRelative(a.y, b.y, RelativeDiff.y), CCFloatEqualRelative(a.z, b.z, RelativeDiff.z), CCFloatEqualRelative(a.w, b.w, RelativeDiff.w) };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareEqualAbsolute(const CCVector4D a, const CCVector4D b, const CCVector4D Diff)
{
    return (CCVector4D){ CCFloatEqualAbsolute(a.x, b.x, Diff.x), CCFloatEqualAbsolute(a.y, b.y, Diff.y), CCFloatEqualAbsolute(a.z, b.z, Diff.z), CCFloatEqualAbsolute(a.w, b.w, Diff.w) };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareEqual(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareLessThan(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareLessThanEqual(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareGreaterThan(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w };
}

static CC_FORCE_INLINE CCVector4D CCVector4CompareGreaterThanEqual(const CCVector4D a, const CCVector4D b)
{
    return (CCVector4D){ a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w };
}

#pragma mark -
#pragma mark Vector, Scalar operations
static CC_FORCE_INLINE CCVector4D CCVector4AddScalar(const CCVector4D a, const float b)
{
    return (CCVector4D){ a.x + b, a.y + b, a.z + b, a.w + b };
}

static CC_FORCE_INLINE CCVector4D CCVector4SubScalar(const CCVector4D a, const float b)
{
    return (CCVector4D){ a.x - b, a.y - b, a.z - b, a.w - b };
}

static CC_FORCE_INLINE CCVector4D CCVector4MulScalar(const CCVector4D a, const float b)
{
    return (CCVector4D){ a.x * b, a.y * b, a.z * b, a.w * b };
}

static CC_FORCE_INLINE CCVector4D CCVector4DivScalar(const CCVector4D a, const float b)
{
    return (CCVector4D){ a.x / b, a.y / b, a.z / b, a.w / b };
}

#pragma mark -
#pragma mark Vector operations

static CC_FORCE_INLINE float CCVector4Length(const CCVector4D a)
{
    return sqrtf(CCVector4Dot(a, a));
}

static CC_FORCE_INLINE CCVector4D CCVector4Normalize(const CCVector4D a)
{
    const float Length = CCVector4Length(a);
    CCAssertLog(Length != 0.0f);
    
    return CCVector4DivScalar(a, Length);
}

static CC_FORCE_INLINE CCVector4D CCVector4Neg(const CCVector4D a)
{
    return (CCVector4D){ -a.x, -a.y, -a.z, -a.w };
}

#pragma mark -
#pragma mark Geometry operations

static CC_FORCE_INLINE CCVector4D CCVector4Perp(const CCVector4D a, const CCVector4D b, const CCVector4D c)
{
    return CCVector4Cross(CCVector4Sub(b, a), CCVector4Sub(c, a));
}

static CC_FORCE_INLINE CCVector4D CCVector4PerpR(const CCVector4D a, const CCVector4D b, const CCVector4D c)
{
    return CCVector4Cross(CCVector4Sub(c, a), CCVector4Sub(b, a));
}

static CC_FORCE_INLINE CCVector4D CCVector4Normal(const CCVector4D a, const CCVector4D b, const CCVector4D c)
{
    return CCVector4Normalize(CCVector4Perp(a, b, c));
}

static CC_FORCE_INLINE CCVector4D CCVector4NormalR(const CCVector4D a, const CCVector4D b, const CCVector4D c)
{
    return CCVector4Normalize(CCVector4PerpR(a, b, c));
}



#pragma mark -
#pragma mark Vectorized setters and getters

static CC_FORCE_INLINE CCVector CCVectorizeVector4D(const CCVector4D a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return (CCVector)_mm_load_ps((float*)&a);
#else
    return (CCVector)a;
#endif
}

static CC_FORCE_INLINE CCVector4D CCVectorizeGetVector4D(const CCVector a)
{
    return *(CCVector4D*)&a;
}

#pragma mark -
#pragma mark Vectorized Vector, Vector operations

static CC_FORCE_INLINE CCVector CCVectorize4Add(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, b);
#else
    return (CCVector){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Sub(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, b);
#else
    return (CCVector){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Mul(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, b);
#else
    return (CCVector){ a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Div(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, b);
#else
    return (CCVector){ a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Dot(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE4_1
    return _mm_dp_ps(a, b, 0xff);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector TempXYZW = CCVectorize4Mul(a, b);
    CCVector TempWXYZ = _mm_shuffle_ps(TempXYZW, TempXYZW, _MM_SHUFFLE(2, 1, 0, 3));
    CCVector TempZWXY = _mm_shuffle_ps(TempXYZW, TempXYZW, _MM_SHUFFLE(1, 0, 3, 2));
    CCVector TempYZWX = _mm_shuffle_ps(TempXYZW, TempXYZW, _MM_SHUFFLE(0, 3, 2, 1));
    
    return CCVectorize4Add(CCVectorize4Add(TempYZWX, TempZWXY), CCVectorize4Add(TempXYZW, TempWXYZ));
#else
    const float r = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    return (CCVector){ r, r, r, r };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Distance(const CCVector a, const CCVector b)
{
    return CCVectorize4Length(CCVectorize4Sub(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize4DistanceSquare(const CCVector a, const CCVector b)
{
    CCVector d = CCVectorize4Sub(a, b);
    return CCVectorize4Dot(d, d);
}

static CC_FORCE_INLINE CCVector CCVectorize4Angle(const CCVector a, const CCVector b)
{
    return CCVectorize4Div(CCVectorize4Dot(a, b), CCVectorize4Mul(CCVectorize4Length(a), CCVectorize4Length(b)));
}

static CC_FORCE_INLINE CCVector CCVectorize4Cross(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector aYZX = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
    CCVector bYZX = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
    
    CCVector r = _mm_sub_ps(_mm_mul_ps(a, bYZX), _mm_mul_ps(aYZX, b));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(3, 0, 2, 1));
#else
    return (CCVector){
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
        0.0f
    };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Lerp(const CCVector a, const CCVector b, const float t)
{
    return CCVectorize4Add(a, CCVectorize4MulScalar(CCVectorize4Sub(b, a), t));
}

static CC_FORCE_INLINE CCVector CCVectorize4Project(const CCVector a, const CCVector b)
{
    return CCVectorize4Mul(b, CCVectorize4Div(CCVectorize4Dot(a, b), CCVectorize4Dot(b, b)));
}

static CC_FORCE_INLINE CCVector CCVectorize4Reject(const CCVector a, const CCVector b)
{
    return CCVectorize4Sub(a, CCVectorize4Project(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize4Min(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_min_ps(a, b);
#else
    return (CCVector){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z, a.w < b.w ? a.w : b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Max(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_max_ps(a, b);
#else
    return (CCVector){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z, a.w > b.w ? a.w : b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Clamp(const CCVector a, const CCVector min, const CCVector max)
{
    return CCVectorize4Min(CCVectorize4Max(a, min), max);
}

#pragma mark -
#pragma mark Vectorized Vector, Scalar operations

static CC_FORCE_INLINE CCVector CCVectorize4AddScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x + b, a.y + b, a.z + b, a.w + b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4SubScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x - b, a.y - b, a.z - b, a.w - b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4MulScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x * b, a.y * b, a.z * b, a.w * b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4DivScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x / b, a.y / b, a.z / b, a.w / b };
#endif
}

#pragma mark -
#pragma mark Vectorized Vector operations

static CC_FORCE_INLINE CCVector CCVectorize4Length(const CCVector a)
{
    CCVector d = CCVectorize4Dot(a, a);
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sqrt_ps(d);
#else
    float r = sqrtf(d.x);
    return (CCVector){ r, r, r, r };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize4Normalize(const CCVector a)
{
    CCVector Length = CCVectorize4Length(a);
    CCAssertLog(CCVectorizeGetVector4D(Length).x != 0.0f);
    
    return CCVectorize4Div(a, Length);
}

static CC_FORCE_INLINE CCVector CCVectorize4Neg(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    return _mm_xor_ps(a, (CCVector)_mm_set1_epi32(1 << 31));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_xor_ps(a, _mm_set1_ps(-0.0f));
#else
    return (CCVector){ -a.x, -a.y, -a.z, -a.w };
#endif
}

#pragma mark -
#pragma mark Geometry operations

static CC_FORCE_INLINE CCVector CCVectorize4Perp(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize4Cross(CCVectorize4Sub(b, a), CCVectorize4Sub(c, a));
}

static CC_FORCE_INLINE CCVector CCVectorize4PerpR(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize4Cross(CCVectorize4Sub(c, a), CCVectorize4Sub(b, a));
}

static CC_FORCE_INLINE CCVector CCVectorize4Normal(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize4Normalize(CCVectorize4Perp(a, b, c));
}

static CC_FORCE_INLINE CCVector CCVectorize4NormalR(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize4Normalize(CCVectorize4PerpR(a, b, c));
}


#endif
