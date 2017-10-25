/*
 *  Copyright (c) 2014, Stefan Johnson
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

#ifndef CommonC_Vector3D_h
#define CommonC_Vector3D_h

#include <CommonC/Types.h>
#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <CommonC/Maths.h>
#include <math.h>


#define CCVector3DMake(x, y, z) (CCVector3D){ (x), (y), (z) }
#define CCVector3DFill(x) CCVector3DMake(x, x, x)
#define CCVector3DZero CCVector3DFill(0.0f)

#define CCVector3DiMake(x, y, z) (CCVector3Di){ (x), (y), (z) }
#define CCVector3DiFill(x) CCVector3DiMake(x, x, x)
#define CCVector3DiZero CCVector3DiFill(0)



#pragma mark - Vectorized Vector3D

static CC_FORCE_INLINE CCVector CCVectorizeVector3D(const CCVector3D a);
static CC_FORCE_INLINE CCVector CCVectorizeVector3Di(const CCVector3Di a);
static CC_FORCE_INLINE CCVector3D CCVectorizeGetVector3D(const CCVector a);
static CC_FORCE_INLINE CCVector3Di CCVectorizeGetVector3Di(const CCVector a);

static CC_FORCE_INLINE CCVector CCVectorize3Add(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Sub(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Mul(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Div(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3AddScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize3SubScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize3MulScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize3DivScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize3Dot(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Length(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize3Distance(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3DistanceSquare(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Angle(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Cross(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Lerp(const CCVector a, const CCVector b, const float t);
static CC_FORCE_INLINE CCVector CCVectorize3Project(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Reject(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Perp(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize3PerpR(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize3Normal(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize3NormalR(const CCVector a, const CCVector b, const CCVector c);
static CC_FORCE_INLINE CCVector CCVectorize3Normalize(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize3Neg(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize3Abs(const CCVector a);

static CC_FORCE_INLINE CCVector CCVectorize3Min(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Max(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3Clamp(const CCVector a, const CCVector min, const CCVector max);

static CC_FORCE_INLINE CCVector CCVectorize3CompareEqualUlps(const CCVector a, const CCVector b, CCVector MaxUlps);
static CC_FORCE_INLINE CCVector CCVectorize3CompareEqualRelative(const CCVector a, const CCVector b, const CCVector RelativeDiff);
static CC_FORCE_INLINE CCVector CCVectorize3CompareEqualAbsolute(const CCVector a, const CCVector b, const CCVector Diff);
static CC_FORCE_INLINE CCVector CCVectorize3CompareEqual(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3CompareLessThan(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3CompareLessThanEqual(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3CompareGreaterThan(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize3CompareGreaterThanEqual(const CCVector a, const CCVector b);


#pragma mark - Vector3D

static CC_FORCE_INLINE CCVector3D CCVector3Add(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Sub(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Mul(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Div(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3AddScalar(const CCVector3D a, const float b);
static CC_FORCE_INLINE CCVector3D CCVector3SubScalar(const CCVector3D a, const float b);
static CC_FORCE_INLINE CCVector3D CCVector3MulScalar(const CCVector3D a, const float b);
static CC_FORCE_INLINE CCVector3D CCVector3DivScalar(const CCVector3D a, const float b);
static CC_FORCE_INLINE float CCVector3Dot(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE float CCVector3Length(const CCVector3D a);
static CC_FORCE_INLINE float CCVector3Distance(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE float CCVector3DistanceSquare(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE float CCVector3Angle(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Cross(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Lerp(const CCVector3D a, const CCVector3D b, const float t);
static CC_FORCE_INLINE CCVector3D CCVector3Project(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Reject(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Perp(const CCVector3D a, const CCVector3D b, const CCVector3D c);
static CC_FORCE_INLINE CCVector3D CCVector3PerpR(const CCVector3D a, const CCVector3D b, const CCVector3D c);
static CC_FORCE_INLINE CCVector3D CCVector3Normal(const CCVector3D a, const CCVector3D b, const CCVector3D c);
static CC_FORCE_INLINE CCVector3D CCVector3NormalR(const CCVector3D a, const CCVector3D b, const CCVector3D c);
static CC_FORCE_INLINE CCVector3D CCVector3Normalize(const CCVector3D a);
static CC_FORCE_INLINE CCVector3D CCVector3Neg(const CCVector3D a);
static CC_FORCE_INLINE CCVector3D CCVector3Abs(const CCVector3D a);
static CC_FORCE_INLINE _Bool CCVector3Parallel(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE _Bool CCVector3Ortho(const CCVector3D a, const CCVector3D b);

static CC_FORCE_INLINE CCVector3D CCVector3Min(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Max(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Clamp(const CCVector3D a, const CCVector3D min, const CCVector3D max);

static CC_FORCE_INLINE _Bool CCVector3EqualUlps(const CCVector3D a, const CCVector3D b, CCVector3Di MaxUlps);
static CC_FORCE_INLINE _Bool CCVector3EqualRelative(const CCVector3D a, const CCVector3D b, const CCVector3D RelativeDiff);
static CC_FORCE_INLINE _Bool CCVector3EqualAbsolute(const CCVector3D a, const CCVector3D b, const CCVector3D Diff);
static CC_FORCE_INLINE _Bool CCVector3Equal(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE _Bool CCVector3LessThan(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE _Bool CCVector3LessThanEqual(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE _Bool CCVector3GreaterThan(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE _Bool CCVector3GreaterThanEqual(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3CompareEqualUlps(const CCVector3D a, const CCVector3D b, CCVector3Di MaxUlps);
static CC_FORCE_INLINE CCVector3D CCVector3CompareEqualRelative(const CCVector3D a, const CCVector3D b, const CCVector3D RelativeDiff);
static CC_FORCE_INLINE CCVector3D CCVector3CompareEqualAbsolute(const CCVector3D a, const CCVector3D b, const CCVector3D Diff);
static CC_FORCE_INLINE CCVector3D CCVector3CompareEqual(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3CompareLessThan(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3CompareLessThanEqual(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3CompareGreaterThan(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3CompareGreaterThanEqual(const CCVector3D a, const CCVector3D b);


#pragma mark -
#pragma mark Vector, Vector operations

static CC_FORCE_INLINE CCVector3D CCVector3Add(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x + b.x, a.y + b.y, a.z + b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3Sub(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x - b.x, a.y - b.y, a.z - b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3Mul(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x * b.x, a.y * b.y, a.z * b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3Div(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x / b.x, a.y / b.y, a.z / b.z };
}

static CC_FORCE_INLINE float CCVector3Dot(const CCVector3D a, const CCVector3D b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

static CC_FORCE_INLINE float CCVector3Distance(const CCVector3D a, const CCVector3D b)
{
    return CCVector3Length(CCVector3Sub(a, b));
}

static CC_FORCE_INLINE float CCVector3DistanceSquare(const CCVector3D a, const CCVector3D b)
{
    CCVector3D d = CCVector3Sub(a, b);
    return CCVector3Dot(d, d);
}

static CC_FORCE_INLINE float CCVector3Angle(const CCVector3D a, const CCVector3D b)
{
    return CCVector3Dot(a, b) / (CCVector3Length(a) * CCVector3Length(b));
}

static CC_FORCE_INLINE CCVector3D CCVector3Cross(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
}

static CC_FORCE_INLINE CCVector3D CCVector3Lerp(const CCVector3D a, const CCVector3D b, const float t)
{
    return CCVector3Add(a, CCVector3MulScalar(CCVector3Sub(b, a), t));
}

static CC_FORCE_INLINE CCVector3D CCVector3Project(const CCVector3D a, const CCVector3D b)
{
    return CCVector3MulScalar(b, CCVector3Dot(a, b) / CCVector3Dot(b, b));
}

static CC_FORCE_INLINE CCVector3D CCVector3Reject(const CCVector3D a, const CCVector3D b)
{
    return CCVector3Sub(a, CCVector3Project(a, b));
}

static CC_FORCE_INLINE CCVector3D CCVector3Min(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3Max(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3Clamp(const CCVector3D a, const CCVector3D min, const CCVector3D max)
{
    return CCVector3Min(CCVector3Max(a, min), max);
}

static CC_FORCE_INLINE _Bool CCVector3Parallel(const CCVector3D a, const CCVector3D b)
{
    CCVector3D v = CCVector3Cross(a, b);
    return (fabsf(v.x) < 1e-6f) && (fabsf(v.y) < 1e-6f) && (fabsf(v.z) < 1e-6f); //TODO: replace with better zero check
}

static CC_FORCE_INLINE _Bool CCVector3Ortho(const CCVector3D a, const CCVector3D b)
{
    return fabsf(CCVector3Dot(a, b)) < 1e-6f; //TODO: replace with better zero check
}

static CC_FORCE_INLINE _Bool CCVector3EqualUlps(const CCVector3D a, const CCVector3D b, CCVector3Di MaxUlps)
{
    return CCFloatEqualUlps(a.x, b.x, MaxUlps.x) && CCFloatEqualUlps(a.y, b.y, MaxUlps.y) && CCFloatEqualUlps(a.z, b.z, MaxUlps.z);
}

static CC_FORCE_INLINE _Bool CCVector3EqualRelative(const CCVector3D a, const CCVector3D b, const CCVector3D RelativeDiff)
{
    return CCFloatEqualRelative(a.x, b.x, RelativeDiff.x) && CCFloatEqualRelative(a.y, b.y, RelativeDiff.y) && CCFloatEqualRelative(a.z, b.z, RelativeDiff.z);
}

static CC_FORCE_INLINE _Bool CCVector3EqualAbsolute(const CCVector3D a, const CCVector3D b, const CCVector3D Diff)
{
    return CCFloatEqualAbsolute(a.x, b.x, Diff.x) && CCFloatEqualAbsolute(a.y, b.y, Diff.y) && CCFloatEqualAbsolute(a.z, b.z, Diff.z);
}

static CC_FORCE_INLINE _Bool CCVector3Equal(const CCVector3D a, const CCVector3D b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

static CC_FORCE_INLINE _Bool CCVector3LessThan(const CCVector3D a, const CCVector3D b)
{
    return a.x < b.x && a.y < b.y && a.z < b.z;
}

static CC_FORCE_INLINE _Bool CCVector3LessThanEqual(const CCVector3D a, const CCVector3D b)
{
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

static CC_FORCE_INLINE _Bool CCVector3GreaterThan(const CCVector3D a, const CCVector3D b)
{
    return a.x > b.x && a.y > b.y && a.z > b.z;
}

static CC_FORCE_INLINE _Bool CCVector3GreaterThanEqual(const CCVector3D a, const CCVector3D b)
{
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareEqualUlps(const CCVector3D a, const CCVector3D b, CCVector3Di MaxUlps)
{
    return (CCVector3D){ CCFloatEqualUlps(a.x, b.x, MaxUlps.x), CCFloatEqualUlps(a.y, b.y, MaxUlps.y), CCFloatEqualUlps(a.z, b.z, MaxUlps.z) };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareEqualRelative(const CCVector3D a, const CCVector3D b, const CCVector3D RelativeDiff)
{
    return (CCVector3D){ CCFloatEqualRelative(a.x, b.x, RelativeDiff.x), CCFloatEqualRelative(a.y, b.y, RelativeDiff.y), CCFloatEqualRelative(a.z, b.z, RelativeDiff.z) };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareEqualAbsolute(const CCVector3D a, const CCVector3D b, const CCVector3D Diff)
{
    return (CCVector3D){ CCFloatEqualAbsolute(a.x, b.x, Diff.x), CCFloatEqualAbsolute(a.y, b.y, Diff.y), CCFloatEqualAbsolute(a.z, b.z, Diff.z) };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareEqual(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x == b.x, a.y == b.y, a.z == b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareLessThan(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x < b.x, a.y < b.y, a.z < b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareLessThanEqual(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x <= b.x, a.y <= b.y, a.z <= b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareGreaterThan(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x > b.x, a.y > b.y, a.z > b.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3CompareGreaterThanEqual(const CCVector3D a, const CCVector3D b)
{
    return (CCVector3D){ a.x >= b.x, a.y >= b.y, a.z >= b.z };
}

#pragma mark -
#pragma mark Vector, Scalar operations
static CC_FORCE_INLINE CCVector3D CCVector3AddScalar(const CCVector3D a, const float b)
{
    return (CCVector3D){ a.x + b, a.y + b, a.z + b };
}

static CC_FORCE_INLINE CCVector3D CCVector3SubScalar(const CCVector3D a, const float b)
{
    return (CCVector3D){ a.x - b, a.y - b, a.z - b };
}

static CC_FORCE_INLINE CCVector3D CCVector3MulScalar(const CCVector3D a, const float b)
{
    return (CCVector3D){ a.x * b, a.y * b, a.z * b };
}

static CC_FORCE_INLINE CCVector3D CCVector3DivScalar(const CCVector3D a, const float b)
{
    return (CCVector3D){ a.x / b, a.y / b, a.z / b };
}

#pragma mark -
#pragma mark Vector operations

static CC_FORCE_INLINE float CCVector3Length(const CCVector3D a)
{
    return sqrtf(CCVector3Dot(a, a));
}

static CC_FORCE_INLINE CCVector3D CCVector3Normalize(const CCVector3D a)
{
    const float Length = CCVector3Length(a);
    CCAssertLog(Length != 0.0f);
    
    return CCVector3DivScalar(a, Length);
}

static CC_FORCE_INLINE CCVector3D CCVector3Neg(const CCVector3D a)
{
    return (CCVector3D){ -a.x, -a.y, -a.z };
}

static CC_FORCE_INLINE CCVector3D CCVector3Abs(const CCVector3D a)
{
    return (CCVector3D){ fabsf(a.x), fabsf(a.y), fabsf(a.z) };
}

#pragma mark -
#pragma mark Geometry operations

static CC_FORCE_INLINE CCVector3D CCVector3Perp(const CCVector3D a, const CCVector3D b, const CCVector3D c)
{
    return CCVector3Cross(CCVector3Sub(b, a), CCVector3Sub(c, a));
}

static CC_FORCE_INLINE CCVector3D CCVector3PerpR(const CCVector3D a, const CCVector3D b, const CCVector3D c)
{
    return CCVector3Cross(CCVector3Sub(c, a), CCVector3Sub(b, a));
}

static CC_FORCE_INLINE CCVector3D CCVector3Normal(const CCVector3D a, const CCVector3D b, const CCVector3D c)
{
    return CCVector3Normalize(CCVector3Perp(a, b, c));
}

static CC_FORCE_INLINE CCVector3D CCVector3NormalR(const CCVector3D a, const CCVector3D b, const CCVector3D c)
{
    return CCVector3Normalize(CCVector3PerpR(a, b, c));
}



#pragma mark -
#pragma mark Vectorized setters and getters

static CC_FORCE_INLINE CCVector CCVectorizeVector3D(const CCVector3D a)
{
    return *(CCVector*)&(CCVector4D){ a.x, a.y, a.z, 0.0f };
}

static CC_FORCE_INLINE CCVector CCVectorizeVector3Di(const CCVector3Di a)
{
    return CCVectorizeVector3D(*(CCVector3D*)&a);
}

static CC_FORCE_INLINE CCVector3D CCVectorizeGetVector3D(const CCVector a)
{
    return *(CCVector3D*)&a;
}

static CC_FORCE_INLINE CCVector3Di CCVectorizeGetVector3Di(const CCVector a)
{
    return *(CCVector3Di*)&a;
}

#pragma mark -
#pragma mark Vectorized Vector, Vector operations

static CC_FORCE_INLINE CCVector CCVectorize3Add(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, b);
#else
    return (CCVector){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Sub(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, b);
#else
    return (CCVector){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Mul(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, b);
#else
    return (CCVector){ a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Div(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, b);
#else
    return (CCVector){ a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Dot(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE4_1
    return _mm_dp_ps(a, b, 0x77);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector TempXYZ = CCVectorize3Mul(a, b);
    CCVector TempZXY = _mm_shuffle_ps(TempXYZ, TempXYZ, _MM_SHUFFLE(0, 1, 0, 2));
    CCVector TempYZX = _mm_shuffle_ps(TempXYZ, TempXYZ, _MM_SHUFFLE(0, 0, 2, 1));
    
    return CCVectorize3Add(TempYZX, CCVectorize3Add(TempXYZ, TempZXY));
#else
    const float r = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return (CCVector){ r, r, r, r };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Distance(const CCVector a, const CCVector b)
{
    return CCVectorize3Length(CCVectorize3Sub(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize3DistanceSquare(const CCVector a, const CCVector b)
{
    CCVector d = CCVectorize3Sub(a, b);
    return CCVectorize3Dot(d, d);
}

static CC_FORCE_INLINE CCVector CCVectorize3Angle(const CCVector a, const CCVector b)
{
    return CCVectorize3Div(CCVectorize3Dot(a, b), CCVectorize3Mul(CCVectorize3Length(a), CCVectorize3Length(b)));
}

static CC_FORCE_INLINE CCVector CCVectorize3Cross(const CCVector a, const CCVector b)
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

static CC_FORCE_INLINE CCVector CCVectorize3Lerp(const CCVector a, const CCVector b, const float t)
{
    return CCVectorize3Add(a, CCVectorize3MulScalar(CCVectorize3Sub(b, a), t));
}

static CC_FORCE_INLINE CCVector CCVectorize3Project(const CCVector a, const CCVector b)
{
    return CCVectorize3Mul(b, CCVectorize3Div(CCVectorize3Dot(a, b), CCVectorize3Dot(b, b)));
}

static CC_FORCE_INLINE CCVector CCVectorize3Reject(const CCVector a, const CCVector b)
{
    return CCVectorize3Sub(a, CCVectorize3Project(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize3Min(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_min_ps(a, b);
#else
    return (CCVector){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z, a.w < b.w ? a.w : b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Max(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_max_ps(a, b);
#else
    return (CCVector){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z, a.w > b.w ? a.w : b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Clamp(const CCVector a, const CCVector min, const CCVector max)
{
    return CCVectorize3Min(CCVectorize3Max(a, min), max);
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareEqualUlps(const CCVector a, const CCVector b, CCVector MaxUlps)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    CCVector3D Sign = CCVectorizeGetVector3D(_mm_xor_ps(a, b));
    if ((signbit(Sign.x)) && (signbit(Sign.y)) && (signbit(Sign.z))) return CCVectorize3CompareEqual(a, b);
    
    return _mm_and_ps(_mm_cmpeq_epi32(_mm_max_ps(_mm_sub_epi32(_mm_max_ps(a, b), _mm_min_ps(a, b)), MaxUlps), MaxUlps), _mm_set1_ps(1.0f));
#else
    return CCVectorizeVector3D(CCVector3CompareEqualUlps(CCVectorizeGetVector3D(a), CCVectorizeGetVector3D(b), CCVectorizeGetVector3Di(MaxUlps)));
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareEqualRelative(const CCVector a, const CCVector b, const CCVector RelativeDiff)
{
    CCVector Diff = CCVectorize3Abs(CCVectorize3Sub(a, b));
    
    return CCVectorize3CompareLessThanEqual(Diff, CCVectorize3Mul(CCVectorize3Max(CCVectorize3Abs(a), CCVectorize3Abs(b)), RelativeDiff));
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareEqualAbsolute(const CCVector a, const CCVector b, const CCVector Diff)
{
    return CCVectorize3CompareLessThanEqual(CCVectorize3Abs(CCVectorize3Sub(a, b)), Diff);
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareEqual(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_and_ps(_mm_cmpeq_ps(a, b), _mm_set1_ps(1.0f));
#else
    return (CCVector){ a.x == b.x, a.y == b.y, a.z == b.z, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareLessThan(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_and_ps(_mm_cmplt_ps(a, b), _mm_set1_ps(1.0f));
#else
    return (CCVector){ a.x < b.x, a.y < b.y, a.z < b.z, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareLessThanEqual(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_and_ps(_mm_cmple_ps(a, b), _mm_set1_ps(1.0f));
#else
    return (CCVector){ a.x <= b.x, a.y <= b.y, a.z <= b.z, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareGreaterThan(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_and_ps(_mm_cmpgt_ps(a, b), _mm_set1_ps(1.0f));
#else
    return (CCVector){ a.x > b.x, a.y > b.y, a.z > b.z, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3CompareGreaterThanEqual(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_and_ps(_mm_cmpge_ps(a, b), _mm_set1_ps(1.0f));
#else
    return (CCVector){ a.x >= b.x, a.y >= b.y, a.z >= b.z, 0.0f };
#endif
}

#pragma mark -
#pragma mark Vectorized Vector, Scalar operations

static CC_FORCE_INLINE CCVector CCVectorize3AddScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x + b, a.y + b, a.z + b, a.w + b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3SubScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x - b, a.y - b, a.z - b, a.w - b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3MulScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x * b, a.y * b, a.z * b, a.w * b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3DivScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x / b, a.y / b, a.z / b, a.w / b };
#endif
}

#pragma mark -
#pragma mark Vectorized Vector operations

static CC_FORCE_INLINE CCVector CCVectorize3Length(const CCVector a)
{
    CCVector d = CCVectorize3Dot(a, a);
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sqrt_ps(d);
#else
    float r = sqrtf(d.x);
    return (CCVector){ r, r, r, r };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Normalize(const CCVector a)
{
    CCVector Length = CCVectorize3Length(a);
    CCAssertLog(CCVectorizeGetVector3D(Length).x != 0.0f);
    
    return CCVectorize3Div(a, Length);
}

static CC_FORCE_INLINE CCVector CCVectorize3Neg(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    return _mm_xor_ps(a, (CCVector)_mm_set1_epi32(1 << 31));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_xor_ps(a, _mm_set1_ps(-0.0f));
#else
    return (CCVector){ -a.x, -a.y, -a.z, -a.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize3Abs(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    return _mm_andnot_ps((CCVector)_mm_set1_epi32(1 << 31), a);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_andnot_ps(_mm_set1_ps(-0.0f), a);
#else
    return (CCVector){ fabsf(a.x), fabsf(a.y), fabsf(a.z), 0.0f };
#endif
}

#pragma mark -
#pragma mark Geometry operations

static CC_FORCE_INLINE CCVector CCVectorize3Perp(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize3Cross(CCVectorize3Sub(b, a), CCVectorize3Sub(c, a));
}

static CC_FORCE_INLINE CCVector CCVectorize3PerpR(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize3Cross(CCVectorize3Sub(c, a), CCVectorize3Sub(b, a));
}

static CC_FORCE_INLINE CCVector CCVectorize3Normal(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize3Normalize(CCVectorize3Perp(a, b, c));
}

static CC_FORCE_INLINE CCVector CCVectorize3NormalR(const CCVector a, const CCVector b, const CCVector c)
{
    return CCVectorize3Normalize(CCVectorize3PerpR(a, b, c));
}


#endif
