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
#include <math.h>


#define CCVector3DMake(x, y, z) (CCVector3D){ x, y, z }
#define CCVector3DFill(x) CCVector3DMake(x, x, x)
#define CCVector3DZero CCVector3DFill(0.0f)



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
static CC_FORCE_INLINE _Bool CCVector3Parallel(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE _Bool CCVector3Ortho(const CCVector3D a, const CCVector3D b);

static CC_FORCE_INLINE CCVector3D CCVector3Min(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Max(const CCVector3D a, const CCVector3D b);
static CC_FORCE_INLINE CCVector3D CCVector3Clamp(const CCVector3D a, const CCVector3D min, const CCVector3D max);


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


#endif
