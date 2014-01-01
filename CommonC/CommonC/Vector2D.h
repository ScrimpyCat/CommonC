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
#include <math.h>


#define CCVector2DMake(x, y) (CCVector2D){ x, y }
#define CCVector2DFill(x) CCVector2DMake(x, x)
#define CCVector2DZero CCVector2DFill(0.0f)



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
    return (CCVector2D){ a.x + b.x, a.y + b.y };
}

static CC_FORCE_INLINE CCVector2D CCVector2Sub(const CCVector2D a, const CCVector2D b)
{
    return (CCVector2D){ a.x - b.x, a.y - b.y };
}

static CC_FORCE_INLINE CCVector2D CCVector2Mul(const CCVector2D a, const CCVector2D b)
{
    return (CCVector2D){ a.x * b.x, a.y * b.y };
}

static CC_FORCE_INLINE CCVector2D CCVector2Div(const CCVector2D a, const CCVector2D b)
{
    return (CCVector2D){ a.x / b.x, a.y / b.y };
}

static CC_FORCE_INLINE float CCVector2Dot(const CCVector2D a, const CCVector2D b)
{
    return (a.x * b.x) + (a.y * b.y);
}

static CC_FORCE_INLINE float CCVector2Distance(const CCVector2D a, const CCVector2D b)
{
    return CCVector2Length(CCVector2Sub(a, b));
}

static CC_FORCE_INLINE float CCVector2DistanceSquare(const CCVector2D a, const CCVector2D b)
{
    CCVector2D d = CCVector2Sub(a, b);
    return CCVector2Dot(d, d);
}

static CC_FORCE_INLINE float CCVector2Angle(const CCVector2D a, const CCVector2D b)
{
    return CCVector2Dot(a, b) / (CCVector2Length(a) * CCVector2Length(b));
}

//Promotes vec2 to vec3 (where z = 0), so only needs to workout the z of the cross as xy = 0
static CC_FORCE_INLINE float CCVector2Cross(const CCVector2D a, const CCVector2D b)
{
    return (a.x * b.y) - (a.y * b.x);
}

static CC_FORCE_INLINE CCVector2D CCVector2Lerp(const CCVector2D a, const CCVector2D b, const float t)
{
    return CCVector2Add(a, CCVector2MulScalar(CCVector2Sub(b, a), t));
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
    return sqrtf(CCVector2Dot(a, a));
}

static CC_FORCE_INLINE CCVector2D CCVector2Normalize(const CCVector2D a)
{
    const float Length = CCVector2Length(a);
    
    if (Length == 0.0f) return CCVector2DZero;
    else return CCVector2DivScalar(a, Length);
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

#endif
