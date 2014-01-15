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

#ifndef CommonC_Vector2D_h
#define CommonC_Vector2D_h

#include <CommonC/Types.h>
#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <math.h>


#define CCVector2DMake(x, y) (CCVector2D){ x, y }
#define CCVector2DFill(x) CCVector2DMake(x, x)
#define CCVector2DZero CCVector2DFill(0.0f)



#pragma mark - Vectorized Vector2D

static CC_FORCE_INLINE CCVector CCVectorizeVector2DWithZero(const CCVector2D a); //Allows it to avoid an interleaved move, however is unsafe to use with vectorized normalize.
static CC_FORCE_INLINE CCVector CCVectorizeVector2D(const CCVector2D a);
static CC_FORCE_INLINE CCVector2D CCVectorizeGetVector2D(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorizeVector2DPack(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE void CCVectorizeVector2DUnpack(const CCVector v, CCVector2D *a, CCVector2D *b);
static CC_FORCE_INLINE CCVector2D CCVectorizeExtractVector2D(const CCVector a, size_t i);

static CC_FORCE_INLINE CCVector CCVectorize2Add(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Sub(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Mul(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Div(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2AddScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2SubScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2MulScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2DivScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2Dot(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Length(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2Distance(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2DistanceSquare(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Angle(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Cross(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Lerp(const CCVector a, const CCVector b, const float t);
static CC_FORCE_INLINE CCVector CCVectorize2Project(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Reject(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Perp(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2PerpR(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2Normalize(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2Neg(const CCVector a);

static CC_FORCE_INLINE CCVector CCVectorize2Min(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Max(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2Clamp(const CCVector a, const CCVector min, const CCVector max);


static CC_FORCE_INLINE CCVector CCVectorize2ScalarDot(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarLength(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarDistance(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarDistanceSquare(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarAngle(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarCross(const CCVector a, const CCVector b);


static CC_FORCE_INLINE CCVector CCVectorize2PackedAdd(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedSub(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedMul(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedDiv(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedAddScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedSubScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedMulScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedDivScalar(const CCVector a, const float b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedDot(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedLength(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2PackedDistance(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedDistanceSquare(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedAngle(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedCross(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedLerp(const CCVector a, const CCVector b, const float t);
static CC_FORCE_INLINE CCVector CCVectorize2PackedProject(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedReject(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedPerp(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2PackedPerpR(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2PackedNormalize(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2PackedNeg(const CCVector a);

static CC_FORCE_INLINE CCVector CCVectorize2PackedMin(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedMax(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2PackedClamp(const CCVector a, const CCVector min, const CCVector max);


static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedDot(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedLength(const CCVector a);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedDistance(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedDistanceSquare(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedAngle(const CCVector a, const CCVector b);
static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedCross(const CCVector a, const CCVector b);



#pragma mark - Vector2D

static CC_FORCE_INLINE CCVector2D CCVector2Add(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Sub(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Mul(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Div(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2AddScalar(const CCVector2D a, const float b);
static CC_FORCE_INLINE CCVector2D CCVector2SubScalar(const CCVector2D a, const float b);
static CC_FORCE_INLINE CCVector2D CCVector2MulScalar(const CCVector2D a, const float b);
static CC_FORCE_INLINE CCVector2D CCVector2DivScalar(const CCVector2D a, const float b);
static CC_FORCE_INLINE float CCVector2Dot(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE float CCVector2Length(const CCVector2D a);
static CC_FORCE_INLINE float CCVector2Distance(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE float CCVector2DistanceSquare(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE float CCVector2Angle(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE float CCVector2Cross(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Lerp(const CCVector2D a, const CCVector2D b, const float t);
static CC_FORCE_INLINE CCVector2D CCVector2Project(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Reject(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Perp(const CCVector2D a);
static CC_FORCE_INLINE CCVector2D CCVector2PerpR(const CCVector2D a);
static CC_FORCE_INLINE CCVector2D CCVector2Normalize(const CCVector2D a);
static CC_FORCE_INLINE CCVector2D CCVector2Neg(const CCVector2D a);
static CC_FORCE_INLINE _Bool CCVector2Parallel(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE _Bool CCVector2Ortho(const CCVector2D a, const CCVector2D b);

static CC_FORCE_INLINE CCVector2D CCVector2Min(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Max(const CCVector2D a, const CCVector2D b);
static CC_FORCE_INLINE CCVector2D CCVector2Clamp(const CCVector2D a, const CCVector2D min, const CCVector2D max);


#pragma mark -
#pragma mark Vector, Vector operations

static CC_FORCE_INLINE CCVector2D CCVector2Add(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector v = *(CCVector*)&(CCVector4D){ a.x, b.x, a.y, b.y };
    v = _mm_hadd_ps(v, v);
    return *(CCVector2D*)&v;
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(CCVector2D*)&(CCVector){ CCVectorize2Add(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return (CCVector2D){ a.x + b.x, a.y + b.y };
#endif
}

static CC_FORCE_INLINE CCVector2D CCVector2Sub(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector v = *(CCVector*)&(CCVector4D){ a.x, b.x, a.y, b.y };
    v = _mm_hsub_ps(v, v);
    return *(CCVector2D*)&v;
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(CCVector2D*)&(CCVector){ CCVectorize2Sub(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return (CCVector2D){ a.x - b.x, a.y - b.y };
#endif
}

static CC_FORCE_INLINE CCVector2D CCVector2Mul(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(CCVector2D*)&(CCVector){ CCVectorize2Mul(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return (CCVector2D){ a.x * b.x, a.y * b.y };
#endif
}

static CC_FORCE_INLINE CCVector2D CCVector2Div(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(CCVector2D*)&(CCVector){ CCVectorize2Div(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return (CCVector2D){ a.x / b.x, a.y / b.y };
#endif
}

static CC_FORCE_INLINE float CCVector2Dot(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(float*)&(CCVector){ CCVectorize2ScalarDot(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return (a.x * b.x) + (a.y * b.y);
#endif
}

static CC_FORCE_INLINE float CCVector2Distance(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(float*)&(CCVector){ CCVectorize2ScalarDistance(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return CCVector2Length(CCVector2Sub(a, b));
#endif
}

static CC_FORCE_INLINE float CCVector2DistanceSquare(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(float*)&(CCVector){ CCVectorize2ScalarDistanceSquare(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    CCVector2D d = CCVector2Sub(a, b);
    return CCVector2Dot(d, d);
#endif
}

static CC_FORCE_INLINE float CCVector2Angle(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(float*)&(CCVector){ CCVectorize2ScalarAngle(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return CCVector2Dot(a, b) / (CCVector2Length(a) * CCVector2Length(b));
#endif
}

//Promotes vec2 to vec3 (where z = 0), so only needs to workout the z of the cross as xy = 0
static CC_FORCE_INLINE float CCVector2Cross(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(float*)&(CCVector){ CCVectorize2ScalarCross(CCVectorizeVector2DWithZero(a), CCVectorizeVector2DWithZero(b)) };
#else
    return (a.x * b.y) - (a.y * b.x);
#endif
}

static CC_FORCE_INLINE CCVector2D CCVector2Lerp(const CCVector2D a, const CCVector2D b, const float t)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector v0 = CCVectorizeVector2DWithZero(a), v1 = CCVectorizeVector2DWithZero(b);
    return *(CCVector2D*)&(CCVector){ CCVectorize2Add(v0, CCVectorize2MulScalar(CCVectorize2Sub(v1, v0), t)) };
#else
    return CCVector2Add(a, CCVector2MulScalar(CCVector2Sub(b, a), t));
#endif
}

static CC_FORCE_INLINE CCVector2D CCVector2Project(const CCVector2D a, const CCVector2D b)
{
    return CCVector2MulScalar(b, CCVector2Dot(a, b) / CCVector2Dot(b, b));
}

static CC_FORCE_INLINE CCVector2D CCVector2Reject(const CCVector2D a, const CCVector2D b)
{
    return CCVector2Sub(a, CCVector2Project(a, b));
}

static CC_FORCE_INLINE CCVector2D CCVector2Min(const CCVector2D a, const CCVector2D b)
{
    return (CCVector2D){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y };
}

static CC_FORCE_INLINE CCVector2D CCVector2Max(const CCVector2D a, const CCVector2D b)
{
    return (CCVector2D){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y };
}

static CC_FORCE_INLINE CCVector2D CCVector2Clamp(const CCVector2D a, const CCVector2D min, const CCVector2D max)
{
    return CCVector2Min(CCVector2Max(a, min), max);
}

static CC_FORCE_INLINE _Bool CCVector2Parallel(const CCVector2D a, const CCVector2D b)
{
    return fabsf(CCVector2Cross(a, b)) < 1e-6f; //TODO: replace with better zero check
}

static CC_FORCE_INLINE _Bool CCVector2Ortho(const CCVector2D a, const CCVector2D b)
{
    return fabsf(CCVector2Dot(a, b)) < 1e-6f; //TODO: replace with better zero check
}

#pragma mark -
#pragma mark Vector, Scalar operations
static CC_FORCE_INLINE CCVector2D CCVector2AddScalar(const CCVector2D a, const float b)
{
    return (CCVector2D){ a.x + b, a.y + b };
}

static CC_FORCE_INLINE CCVector2D CCVector2SubScalar(const CCVector2D a, const float b)
{
    return (CCVector2D){ a.x - b, a.y - b };
}

static CC_FORCE_INLINE CCVector2D CCVector2MulScalar(const CCVector2D a, const float b)
{
    return (CCVector2D){ a.x * b, a.y * b };
}

static CC_FORCE_INLINE CCVector2D CCVector2DivScalar(const CCVector2D a, const float b)
{
    return (CCVector2D){ a.x / b, a.y / b };
}

#pragma mark -
#pragma mark Vector operations

static CC_FORCE_INLINE float CCVector2Length(const CCVector2D a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return *(float*)&(CCVector){ CCVectorize2ScalarLength(CCVectorizeVector2DWithZero(a)) };
#else
    return sqrtf(CCVector2Dot(a, a));
#endif
}

static CC_FORCE_INLINE CCVector2D CCVector2Normalize(const CCVector2D a)
{
    const float Length = CCVector2Length(a);
    CCAssertLog(Length != 0.0f);
    
    return CCVector2DivScalar(a, Length);
}

static CC_FORCE_INLINE CCVector2D CCVector2Neg(const CCVector2D a)
{
    return (CCVector2D){ -a.x, -a.y };
}

static CC_FORCE_INLINE CCVector2D CCVector2Perp(const CCVector2D a)
{
    return (CCVector2D){ -a.y, a.x };
}

static CC_FORCE_INLINE CCVector2D CCVector2PerpR(const CCVector2D a)
{
    return (CCVector2D){ a.y, -a.x };
}


#pragma mark -
#pragma mark Vectorized setters and getters

static CC_FORCE_INLINE CCVector CCVectorizeVector2DWithZero(const CCVector2D a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_loadl_pi(_mm_setzero_ps(), (__m64*)&a);
#else
    return (CCVector){ a.x, a.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorizeVector2D(const CCVector2D a)
{
    return CCVectorizeVector2DPack(a, a);
}

static CC_FORCE_INLINE CCVector2D CCVectorizeGetVector2D(const CCVector a)
{
    return *(CCVector2D*)&a;
}

static CC_FORCE_INLINE CCVector CCVectorizeVector2DPack(const CCVector2D a, const CCVector2D b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_set_ps(b.y, b.x, a.y, a.x);
#else
    return (CCVector){ a.x, a.y, b.x, b.y };
#endif
}

static CC_FORCE_INLINE void CCVectorizeVector2DUnpack(const CCVector v, CCVector2D *a, CCVector2D *b)
{
    *a = *(CCVector2D*)&v;
    *b = *((CCVector2D*)&v + 1);
}

static CC_FORCE_INLINE CCVector2D CCVectorizeExtractVector2D(const CCVector a, size_t i)
{
    return *((CCVector2D*)&a + i);
}

#pragma mark -
#pragma mark Vectorized Vector, Vector operations

static CC_FORCE_INLINE CCVector CCVectorize2Add(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, b);
#else
    return (CCVector){ a.x + b.x, a.y + b.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Sub(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, b);
#else
    return (CCVector){ a.x - b.x, a.y - b.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Mul(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, b);
#else
    return (CCVector){ a.x * b.x, a.y * b.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Div(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, b);
#else
    return (CCVector){ a.x / b.x, a.y / b.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Dot(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE4_1
    return _mm_dp_ps(a, b, 0x33);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector Temp = CCVectorize2Mul(a, b);
    Temp = _mm_hadd_ps(Temp, Temp);
    return _mm_unpacklo_ps(Temp, Temp);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector TempXYXY = CCVectorize2Mul(a, b);
    CCVector TempYXYX = _mm_shuffle_ps(TempXYXY, TempXYXY, _MM_SHUFFLE(2, 3, 0, 1));
    
    return CCVectorize2Add(TempXYXY, TempYXYX);
#else
    const float r0 = (a.x * b.x) + (a.y * b.y);
    return (CCVector){ r0, r0, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarDot(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE4_1
    return _mm_dp_ps(a, b, 0x31);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector Temp = CCVectorize2Mul(a, b);
    return _mm_hadd_ps(Temp, Temp);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return CCVectorize2Dot(a, b);
#else
    return (CCVector){ (a.x * b.x) + (a.y * b.y), 0.0f, 0.0f, 0.0f };
#endif

}

static CC_FORCE_INLINE CCVector CCVectorize2Distance(const CCVector a, const CCVector b)
{
    return CCVectorize2Length(CCVectorize2Sub(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarDistance(const CCVector a, const CCVector b)
{
    return CCVectorize2ScalarLength(CCVectorize2Sub(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize2DistanceSquare(const CCVector a, const CCVector b)
{
    CCVector d = CCVectorize2Sub(a, b);
    return CCVectorize2Dot(d, d);
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarDistanceSquare(const CCVector a, const CCVector b)
{
    CCVector d = CCVectorize2Sub(a, b);
    return CCVectorize2ScalarDot(d, d);
}

static CC_FORCE_INLINE CCVector CCVectorize2Angle(const CCVector a, const CCVector b)
{
    return CCVectorize2Div(CCVectorize2Dot(a, b), CCVectorize2Mul(CCVectorize2Length(a), CCVectorize2Length(b)));
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarAngle(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ss(CCVectorize2ScalarDot(a, b), _mm_mul_ss(CCVectorize2ScalarLength(a), CCVectorize2ScalarLength(b)));
#else
    return CCVectorize2Div(CCVectorize2ScalarDot(a, b), CCVectorize2Mul(CCVectorize2ScalarLength(a), CCVectorize2ScalarLength(b)));
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Cross(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector Temp = CCVectorize2Mul(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));
    Temp = _mm_hsub_ps(Temp, Temp);
    return _mm_unpacklo_ps(Temp, Temp);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector Temp = CCVectorize2Mul(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));
    
    CCVector r = CCVectorize2Sub(Temp, _mm_shuffle_ps(Temp, Temp, _MM_SHUFFLE(3, 3, 1, 1)));
    return _mm_shuffle_ps(r,r, _MM_SHUFFLE(2, 2, 0, 0));
#else
    const float r0 = (a.x * b.y) - (a.y * b.x);
    return (CCVector){ r0, r0, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarCross(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector Temp = CCVectorize2Mul(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));
    return _mm_hsub_ps(Temp, Temp);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector Temp = CCVectorize2Mul(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));
    
    return CCVectorize2Sub(Temp, _mm_shuffle_ps(Temp, Temp, _MM_SHUFFLE(3, 3, 1, 1)));
#else
    return (CCVector){ (a.x * b.y) - (a.y * b.x), 0.0f, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Lerp(const CCVector a, const CCVector b, const float t)
{
    return CCVectorize2Add(a, CCVectorize2MulScalar(CCVectorize2Sub(b, a), t));
}

static CC_FORCE_INLINE CCVector CCVectorize2Project(const CCVector a, const CCVector b)
{
    return CCVectorize2Mul(b, CCVectorize2Div(CCVectorize2Dot(a, b), CCVectorize2Dot(b, b)));
}

static CC_FORCE_INLINE CCVector CCVectorize2Reject(const CCVector a, const CCVector b)
{
    return CCVectorize2Sub(a, CCVectorize2Project(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize2Min(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_min_ps(a, b);
#else
    return (CCVector){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Max(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_max_ps(a, b);
#else
    return (CCVector){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Clamp(const CCVector a, const CCVector min, const CCVector max)
{
    return CCVectorize2Min(CCVectorize2Max(a, min), max);
}

#pragma mark -
#pragma mark Vectorized Vector, Scalar operations

static CC_FORCE_INLINE CCVector CCVectorize2AddScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x + b, a.y + b, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2SubScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x - b, a.y - b, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2MulScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x * b, a.y * b, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2DivScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x / b, a.y / b, 0.0f, 0.0f };
#endif
}

#pragma mark -
#pragma mark Vectorized Vector operations

static CC_FORCE_INLINE CCVector CCVectorize2Length(const CCVector a)
{
    CCVector d = CCVectorize2Dot(a, a);
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sqrt_ps(d);
#else
    float r0 = sqrtf(d.x);
    return (CCVector){ r0, r0, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarLength(const CCVector a)
{
    CCVector d = CCVectorize2ScalarDot(a, a);
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sqrt_ss(d);
#else
    return (CCVector){ sqrtf(d.x), 0.0f, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Perp(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    CCVector r =  _mm_xor_ps(a, _mm_set_epi32(1 << 31, 0, 1 << 31, 0));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector r = _mm_xor_ps(a, _mm_set_ps(-0.0f, 0.0f, -0.0f, 0.0f));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#else
    return (CCVector){ -a.y, a.x, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PerpR(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    CCVector r =  _mm_xor_ps(a, _mm_set_epi32(0, 1 << 31, 0, 1 << 31));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector r =  _mm_xor_ps(a, _mm_set_ps(0.0f, -0.0f, 0.0f, -0.0f));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#else
    return (CCVector){ a.y, -a.x, 0.0f, 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2Normalize(const CCVector a)
{
    CCVector Length = CCVectorize2Length(a);
    CCAssertLog((CCVectorizeExtractVector2D(Length, 0).x != 0.0f) && (CCVectorizeExtractVector2D(Length, 1).x != 0.0f));
    
    return CCVectorize2Div(a, Length);
}

static CC_FORCE_INLINE CCVector CCVectorize2Neg(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    return _mm_xor_ps(a, _mm_set1_epi32(1 << 31));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_xor_ps(a, _mm_set1_ps(-0.0f));
#else
    return (CCVector){ -a.x, -a.y, 0.0f, 0.0f };
#endif
}


#pragma mark -
#pragma mark Packed Vectorized Vector, Vector operations

static CC_FORCE_INLINE CCVector CCVectorize2PackedAdd(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, b);
#else
    return (CCVector){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedSub(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, b);
#else
    return (CCVector){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedMul(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, b);
#else
    return (CCVector){ a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedDiv(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, b);
#else
    return (CCVector){ a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedDot(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE4_1
    return _mm_or_ps(_mm_dp_ps(a, b, 0x33), _mm_dp_ps(a, b, 0xcc));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector Temp = CCVectorize2PackedMul(a, b);
    Temp = _mm_hadd_ps(Temp, Temp);
    return _mm_unpacklo_ps(Temp, Temp);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector TempXYXY = CCVectorize2PackedMul(a, b);
    CCVector TempYXYX = _mm_shuffle_ps(TempXYXY, TempXYXY, _MM_SHUFFLE(2, 3, 0, 1));
    
    return CCVectorize2PackedAdd(TempXYXY, TempYXYX);
#else
    const float r0 = (a.x * b.x) + (a.y * b.y), r1 = (a.z * b.z) + (a.w * b.w);
    return (CCVector){ r0, r0, r1, r1 };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedDot(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE4_1
    return _mm_or_ps(_mm_dp_ps(a, b, 0x31), _mm_dp_ps(a, b, 0xc4));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return CCVectorize2PackedDot(a, b);
#else
    return (CCVector){ (a.x * b.x) + (a.y * b.y), 0.0f, (a.z * b.z) + (a.w * b.w), 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedDistance(const CCVector a, const CCVector b)
{
    return CCVectorize2PackedLength(CCVectorize2PackedSub(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedDistance(const CCVector a, const CCVector b)
{
    return CCVectorize2ScalarPackedLength(CCVectorize2PackedSub(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedDistanceSquare(const CCVector a, const CCVector b)
{
    CCVector d = CCVectorize2PackedSub(a, b);
    return CCVectorize2PackedDot(d, d);
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedDistanceSquare(const CCVector a, const CCVector b)
{
    CCVector d = CCVectorize2PackedSub(a, b);
    return CCVectorize2ScalarPackedDot(d, d);
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedAngle(const CCVector a, const CCVector b)
{
    return CCVectorize2PackedDiv(CCVectorize2PackedDot(a, b), CCVectorize2PackedMul(CCVectorize2PackedLength(a), CCVectorize2PackedLength(b)));
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedAngle(const CCVector a, const CCVector b)
{
    return CCVectorize2PackedDiv(CCVectorize2ScalarPackedDot(a, b), CCVectorize2PackedMul(CCVectorize2ScalarPackedLength(a), CCVectorize2ScalarPackedLength(b)));
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedCross(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE3
    CCVector Temp = CCVectorize2PackedMul(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));
    Temp = _mm_hsub_ps(Temp, Temp);
    return _mm_unpacklo_ps(Temp, Temp);
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector Temp = CCVectorize2PackedMul(a, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)));
    
    CCVector r = CCVectorize2PackedSub(Temp, _mm_shuffle_ps(Temp, Temp, _MM_SHUFFLE(3, 3, 1, 1)));
    return _mm_shuffle_ps(r,r, _MM_SHUFFLE(2, 2, 0, 0));
#else
    const float r0 = (a.x * b.y) - (a.y * b.x), r1 = (a.z * b.w) - (a.w * b.z);
    return (CCVector){ r0, r0, r1, r1 };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedCross(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return CCVectorize2PackedCross(a, b);
#else
    return (CCVector){ (a.x * b.y) - (a.y * b.x), 0.0f, (a.z * b.w) - (a.w * b.z), 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedLerp(const CCVector a, const CCVector b, const float t)
{
    return CCVectorize2PackedAdd(a, CCVectorize2PackedMulScalar(CCVectorize2PackedSub(b, a), t));
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedProject(const CCVector a, const CCVector b)
{
    return CCVectorize2PackedMul(b, CCVectorize2PackedDiv(CCVectorize2PackedDot(a, b), CCVectorize2PackedDot(b, b)));
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedReject(const CCVector a, const CCVector b)
{
    return CCVectorize2PackedSub(a, CCVectorize2PackedProject(a, b));
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedMin(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_min_ps(a, b);
#else
    return (CCVector){ a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z, a.w < b.w ? a.w : b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedMax(const CCVector a, const CCVector b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_max_ps(a, b);
#else
    return (CCVector){ a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z, a.w > b.w ? a.w : b.w };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedClamp(const CCVector a, const CCVector min, const CCVector max)
{
    return CCVectorize2PackedMin(CCVectorize2PackedMax(a, min), max);
}

#pragma mark -
#pragma mark Packed Vectorized Vector, Scalar operations

static CC_FORCE_INLINE CCVector CCVectorize2PackedAddScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_add_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x + b, a.y + b, a.z + b, a.w + b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedSubScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sub_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x - b, a.y - b, a.z - b, a.w - b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedMulScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_mul_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x * b, a.y * b, a.z * b, a.w * b };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedDivScalar(const CCVector a, const float b)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_div_ps(a, _mm_set1_ps(b));
#else
    return (CCVector){ a.x / b, a.y / b, a.z / b, a.w / b };
#endif
}

#pragma mark -
#pragma mark Packed Vectorized Vector operations

static CC_FORCE_INLINE CCVector CCVectorize2PackedLength(const CCVector a)
{
    CCVector d = CCVectorize2PackedDot(a, a);
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sqrt_ps(d);
#else
    float r0 = sqrtf(d.x), r1 = sqrtf(d.z);
    return (CCVector){ r0, r0, r1, r1 };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2ScalarPackedLength(const CCVector a)
{
    CCVector d = CCVectorize2ScalarPackedDot(a, a);
#if CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_sqrt_ps(d);
#else
    return (CCVector){ sqrtf(d.x), 0.0f, sqrtf(d.z), 0.0f };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedPerp(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    CCVector r =  _mm_xor_ps(a, _mm_set_epi32(1 << 31, 0, 1 << 31, 0));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector r = _mm_xor_ps(a, _mm_set_ps(-0.0f, 0.0f, -0.0f, 0.0f));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#else
    return (CCVector){ -a.y, a.x, -a.w, a.z };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedPerpR(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    CCVector r =  _mm_xor_ps(a, _mm_set_epi32(0, 1 << 31, 0, 1 << 31));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    CCVector r =  _mm_xor_ps(a, _mm_set_ps(0.0f, -0.0f, 0.0f, -0.0f));
    return _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 3, 0, 1));
#else
    return (CCVector){ a.y, -a.x, a.w, -a.z };
#endif
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedNormalize(const CCVector a)
{
    CCVector Length = CCVectorize2PackedLength(a);
    CCAssertLog((CCVectorizeExtractVector2D(Length, 0).x != 0.0f) && (CCVectorizeExtractVector2D(Length, 1).x != 0.0f));
    
    return CCVectorize2PackedDiv(a, Length);
}

static CC_FORCE_INLINE CCVector CCVectorize2PackedNeg(const CCVector a)
{
#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
    return _mm_xor_ps(a, _mm_set1_epi32(1 << 31));
#elif CC_HARDWARE_VECTOR_SUPPORT_SSE
    return _mm_xor_ps(a, _mm_set1_ps(-0.0f));
#else
    return (CCVector){ -a.x, -a.y, -a.z, -a.w };
#endif
}


#endif
