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
//TODO: Need to add some missing functionality
//TODO: Optimize by adding SIMD versions, and the naive approach could be optimized too
//TODO: Add tests
//TODO: Add mat3x3 Mat2x2
#ifndef CommonC_Matrix4_h
#define CommonC_Matrix4_h

#include <CommonC/Types.h>
#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <CommonC/Vector.h>
#include <math.h>


#define CCMatrix4Make(x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3, x4, y4, z4, w4) (CCMatrix4){ \
    .x = { (x1), (x2), (x3), (x4) }, \
    .y = { (y1), (y2), (y3), (y4) }, \
    .z = { (z1), (z2), (z3), (z4) }, \
    .w = { (w1), (w2), (w3), (w4) } \
}
#define CCMatrix4Fill(x) CCMatrix4Make(x, x, x, x, \
                                       x, x, x, x, \
                                       x, x, x, x, \
                                       x, x, x, x)
#define CCMatrix4Zero CCMatrix4Fill(0.0f)
#define CCMatrix4Identity CCMatrix4Make(1.0f, 0.0f, 0.0f, 0.0f, \
                                        0.0f, 1.0f, 0.0f, 0.0f, \
                                        0.0f, 0.0f, 1.0f, 0.0f, \
                                        0.0f, 0.0f, 0.0f, 1.0f)


#pragma mark - Matrix4

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeTranslation(const CCVector3D a);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotation(const float radians, const CCVector3D a);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotationX(const float radians);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotationY(const float radians);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotationZ(const float radians);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeScale(const CCVector3D a);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeOrtho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeFrustum(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakePerspective(const float fovy, const float aspect, const float zNear, const float zFar);
//static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeLookAt(const float eyeX, const float eyeY, const float eyeZ, const float centerX, const float centerY, const float centerZ, const float upX, const float upY, const float upZ);

//static CC_FORCE_INLINE CCMatrix2 CCMatrix4GetMatrix2(const CCMatrix4 m);
//static CC_FORCE_INLINE CCMatrix3 CCMatrix4GetMatrix3(const CCMatrix4 m);
//static CC_FORCE_INLINE CCVector4D CCMatrix4GetRowVector4D(const CCMatrix4 m, int index);
//static CC_FORCE_INLINE CCVector4D CCMatrix4SetRowVector4D(const CCMatrix4 m, int index, CCVector4D v);
//static CC_FORCE_INLINE CCVector4D CCMatrix4GetColumnVector4D(const CCMatrix4 m, int index);
//static CC_FORCE_INLINE CCVector4D CCMatrix4SetColumnVector4D(const CCMatrix4 m, int index, CCVector4D v);
//static CC_FORCE_INLINE CCMatrix4 CCMatrix4Add(const CCMatrix4 a, const CCMatrix4 b);
//static CC_FORCE_INLINE CCMatrix4 CCMatrix4Sub(const CCMatrix4 a, const CCMatrix4 b);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Mul(const CCMatrix4 a, const CCMatrix4 b);
static CC_FORCE_INLINE CCVector3D CCMatrix4MulPositionVector3D(const CCMatrix4 m, const CCVector3D v);
static CC_FORCE_INLINE CCVector3D CCMatrix4MulDirectionVector3D(const CCMatrix4 m, const CCVector3D v);
static CC_FORCE_INLINE CCVector3D CCMatrix4MulProjectVector3D(const CCMatrix4 m, const CCVector3D v);
static CC_FORCE_INLINE CCVector4D CCMatrix4MulVector4D(const CCMatrix4 m, const CCVector4D v);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Translate(const CCMatrix4 m, const CCVector3D a);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Rotate(const CCMatrix4 m, const float radians, const CCVector3D a);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4RotateX(const CCMatrix4 m, const float radians);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4RotateY(const CCMatrix4 m, const float radians);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4RotateZ(const CCMatrix4 m, const float radians);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Scale(const CCMatrix4 m, const CCVector3D a);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Ortho(const CCMatrix4 m, const float left, const float right, const float bottom, const float top, const float zNear, const float zFar);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Frustum(const CCMatrix4 m, const float left, const float right, const float bottom, const float top, const float zNear, const float zFar);
static CC_FORCE_INLINE CCMatrix4 CCMatrix4Perspective(const CCMatrix4 m, const float fovy, const float aspect, const float zNear, const float zFar);
//static CC_FORCE_INLINE CCMatrix4 CCMatrix4LookAt(const CCMatrix4 m, const float eyeX, const float eyeY, const float eyeZ, const float centerX, const float centerY, const float centerZ, const float upX, const float upY, const float upZ);

#pragma mark -

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeTranslation(const CCVector3D a)
{
    return CCMatrix4Make(1.0f, 0.0f, 0.0f, a.x,
                         0.0f, 1.0f, 0.0f, a.y,
                         0.0f, 0.0f, 1.0f, a.z,
                         0.0f, 0.0f, 0.0f, 1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotation(const float radians, const CCVector3D a)
{
    const float c = cosf(radians);
    const float cp = 1.0f - c;
    const float s = sinf(radians);
    const CCVector3D v = CCVector3Normalize(a);
    const CCVector3D vs = CCVector3MulScalar(v, s);
    
    return CCMatrix4Make((v.x * v.x * cp) + c,    (v.x * v.y * cp) - vs.z, (v.x * v.z * cp) + vs.y, 0.0f,
                         (v.y * v.x * cp) + vs.z, (v.y * v.y * cp) + c,    (v.y * v.z * cp) - vs.x, 0.0f,
                         (v.z * v.x * cp) - vs.y, (v.z * v.y * cp) + vs.x, (v.z * v.z * cp) + c,    0.0f,
                         0.0f,                    0.0f,                    0.0f,                    1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotationX(const float radians)
{
    const float c = cosf(radians);
    const float s = sinf(radians);
    
    return CCMatrix4Make(1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f,    c,   -s, 0.0f,
                         0.0f,    s,    c, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotationY(const float radians)
{
    const float c = cosf(radians);
    const float s = sinf(radians);
    
    return CCMatrix4Make(   c, 0.0f,    s, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                           -s, 0.0f,    c, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeRotationZ(const float radians)
{
    const float c = cosf(radians);
    const float s = sinf(radians);
    
    return CCMatrix4Make(   c,   -s, 0.0f, 0.0f,
                            s,    c, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeScale(const CCVector3D a)
{
    return CCMatrix4Make(a.x,  0.0f, 0.0f, 0.0f,
                         0.0f, a.y,  0.0f, 0.0f,
                         0.0f, 0.0f, a.z,  0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeOrtho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
    return CCMatrix4Make(2.0f / (right - left),					 0.0f,					  0.0f,	 -((right + left) / (right - left)),
                         0.0f,                  2.0f / (top - bottom),					  0.0f,	 -((top + bottom) / (top - bottom)),
                         0.0f,                                   0.0f,  -2.0f / (zFar - zNear),	 -((zFar + zNear) / (zFar - zNear)),
                         0.0f,                                   0.0f,					  0.0f,								   1.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakeFrustum(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
    return CCMatrix4Make((2.0f * zNear) / (right - left),                            0.0f,    (right + left) / (right - left),                                      0.0f,
                                                    0.0f, (2.0f * zNear) / (top - bottom),    (top + bottom) / (top - bottom),                                      0.0f,
                                                    0.0f,                            0.0f, -((zFar + zNear) / (zFar - zNear)), -((2.0f * zFar * zNear) / (zFar - zNear)),
                                                    0.0f,                            0.0f,                              -1.0f,                                      0.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4MakePerspective(const float fovy, const float aspect, const float zNear, const float zFar)
{
    const float f = 1.0f / tanf(fovy / 2.0f);
    
    return CCMatrix4Make(f / aspect, 0.0f,                            0.0f,                                   0.0f,
                               0.0f,    f,                            0.0f,                                   0.0f,
                               0.0f, 0.0f, (zFar + zNear) / (zNear - zFar), (2.0f * zFar * zNear) / (zNear - zFar),
                               0.0f, 0.0f,                           -1.0f,                                   0.0f);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Mul(const CCMatrix4 a, const CCMatrix4 b)
{
    return CCMatrix4Make((a.x.v[0] * b.x.v[0]) + (a.y.v[0] * b.x.v[1]) + (a.z.v[0] * b.x.v[2]) + (a.w.v[0] * b.x.v[3]), (a.x.v[0] * b.y.v[0]) + (a.y.v[0] * b.y.v[1]) + (a.z.v[0] * b.y.v[2]) + (a.w.v[0] * b.y.v[3]), (a.x.v[0] * b.z.v[0]) + (a.y.v[0] * b.z.v[1]) + (a.z.v[0] * b.z.v[2]) + (a.w.v[0] * b.z.v[3]), (a.x.v[0] * b.w.v[0]) + (a.y.v[0] * b.w.v[1]) + (a.z.v[0] * b.w.v[2]) + (a.w.v[0] * b.w.v[3]),
                         (a.x.v[1] * b.x.v[0]) + (a.y.v[1] * b.x.v[1]) + (a.z.v[1] * b.x.v[2]) + (a.w.v[1] * b.x.v[3]), (a.x.v[1] * b.y.v[0]) + (a.y.v[1] * b.y.v[1]) + (a.z.v[1] * b.y.v[2]) + (a.w.v[1] * b.y.v[3]), (a.x.v[1] * b.z.v[0]) + (a.y.v[1] * b.z.v[1]) + (a.z.v[1] * b.z.v[2]) + (a.w.v[1] * b.z.v[3]), (a.x.v[1] * b.w.v[0]) + (a.y.v[1] * b.w.v[1]) + (a.z.v[1] * b.w.v[2]) + (a.w.v[1] * b.w.v[3]),
                         (a.x.v[2] * b.x.v[0]) + (a.y.v[2] * b.x.v[1]) + (a.z.v[2] * b.x.v[2]) + (a.w.v[2] * b.x.v[3]), (a.x.v[2] * b.y.v[0]) + (a.y.v[2] * b.y.v[1]) + (a.z.v[2] * b.y.v[2]) + (a.w.v[2] * b.y.v[3]), (a.x.v[2] * b.z.v[0]) + (a.y.v[2] * b.z.v[1]) + (a.z.v[2] * b.z.v[2]) + (a.w.v[2] * b.z.v[3]), (a.x.v[2] * b.w.v[0]) + (a.y.v[2] * b.w.v[1]) + (a.z.v[2] * b.w.v[2]) + (a.w.v[2] * b.w.v[3]),
                         (a.x.v[3] * b.x.v[0]) + (a.y.v[3] * b.x.v[1]) + (a.z.v[3] * b.x.v[2]) + (a.w.v[3] * b.x.v[3]), (a.x.v[3] * b.y.v[0]) + (a.y.v[3] * b.y.v[1]) + (a.z.v[3] * b.y.v[2]) + (a.w.v[3] * b.y.v[3]), (a.x.v[3] * b.z.v[0]) + (a.y.v[3] * b.z.v[1]) + (a.z.v[3] * b.z.v[2]) + (a.w.v[3] * b.z.v[3]), (a.x.v[3] * b.w.v[0]) + (a.y.v[3] * b.w.v[1]) + (a.z.v[3] * b.w.v[2]) + (a.w.v[3] * b.w.v[3]));
}

static CC_FORCE_INLINE CCVector3D CCMatrix4MulPositionVector3D(const CCMatrix4 m, const CCVector3D v)
{
    CCVector4D r = CCMatrix4MulVector4D(m, CCVector4DMake(v.x, v.y, v.z, 1.0f));
    return CCVector3DMake(r.x, r.y, r.z);
}

static CC_FORCE_INLINE CCVector3D CCMatrix4MulDirectionVector3D(const CCMatrix4 m, const CCVector3D v)
{
    CCVector4D r = CCMatrix4MulVector4D(m, CCVector4DMake(v.x, v.y, v.z, 0.0f));
    return CCVector3DMake(r.x, r.y, r.z);
}

static CC_FORCE_INLINE CCVector3D CCMatrix4MulProjectVector3D(const CCMatrix4 m, const CCVector3D v)
{
    CCVector4D r = CCMatrix4MulVector4D(m, CCVector4DMake(v.x, v.y, v.z, 1.0f));
    return CCVector3MulScalar(CCVector3DMake(r.x, r.y, r.z), 1.0f / r.w);
}

static CC_FORCE_INLINE CCVector4D CCMatrix4MulVector4D(const CCMatrix4 m, const CCVector4D v)
{
    CCVector4D x = CCVector4MulScalar(m.x, v.x);
    CCVector4D y = CCVector4MulScalar(m.y, v.y);
    CCVector4D z = CCVector4MulScalar(m.z, v.z);
    CCVector4D w = CCVector4MulScalar(m.w, v.w);
    
    return CCVector4DMake(x.v[0] + y.v[0] + z.v[0] + w.v[0],
                          x.v[1] + y.v[1] + z.v[1] + w.v[1],
                          x.v[2] + y.v[2] + z.v[2] + w.v[2],
                          x.v[3] + y.v[3] + z.v[3] + w.v[3]);
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Translate(const CCMatrix4 m, const CCVector3D a)
{
    return CCMatrix4Mul(m, CCMatrix4MakeTranslation(a));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Rotate(const CCMatrix4 m, const float radians, const CCVector3D a)
{
    return CCMatrix4Mul(m, CCMatrix4MakeRotation(radians, a));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4RotateX(const CCMatrix4 m, const float radians)
{
    return CCMatrix4Mul(m, CCMatrix4MakeRotationX(radians));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4RotateY(const CCMatrix4 m, const float radians)
{
    return CCMatrix4Mul(m, CCMatrix4MakeRotationY(radians));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4RotateZ(const CCMatrix4 m, const float radians)
{
    return CCMatrix4Mul(m, CCMatrix4MakeRotationZ(radians));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Scale(const CCMatrix4 m, const CCVector3D a)
{
    return CCMatrix4Mul(m, CCMatrix4MakeScale(a));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Ortho(const CCMatrix4 m, const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
    return CCMatrix4Mul(m, CCMatrix4MakeOrtho(left, right, bottom, top, zNear, zFar));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Frustum(const CCMatrix4 m, const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{
    return CCMatrix4Mul(m, CCMatrix4MakeFrustum(left, right, bottom, top, zNear, zFar));
}

static CC_FORCE_INLINE CCMatrix4 CCMatrix4Perspective(const CCMatrix4 m, const float fovy, const float aspect, const float zNear, const float zFar)
{
    return CCMatrix4Mul(m, CCMatrix4MakePerspective(fovy, aspect, zNear, zFar));
}

#endif
