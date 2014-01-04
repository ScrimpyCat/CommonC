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

#if !__SSE2__
#warning "Will not run test. Missing support for SSE2 either not enabled or hardware can't support."
#else
#import <XCTest/XCTest.h>

//#undef __SSE__
//#undef __SSE2__
#undef __SSE3__
#undef __SSSE3__
#undef __SSE4_1__
#undef __SSE4_2__
#undef __AVX__

#import "Vector3D.h"

@interface Vectorized3DSSE2Tests : XCTestCase

@end

#define TEST_VECTOR3_EQUAL(v, equal) XCTAssert((v.x == equal.x) && (v.y == equal.y) && (v.z == equal.z), @"Vector should be equal to { %.1f, %.1f, %.1f }, not { %.1f, %.1f, %.1f }", equal.x, equal.y, equal.z, v.x, v.y, v.z)

@implementation Vectorized3DSSE2Tests

-(void) testMake
{
    CCVector3D v = CCVectorizeGetVector3D(CCVectorizeVector3D(CCVector3DMake(0.0f, 1.0f, 2.0f)));
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f) && (v.z == 2.0f), @"Vector should be equal to { 0.0, 1.0, 2.0 }, not { %.1f, %.1f, %.1f }", v.x, v.y, v.z);
}

-(void) testBasicVectorVectorArithmetic
{
    const CCVector3D a = CCVector3DMake(20.0f, 15.0f, 10.0f), b = CCVector3DMake(2.0f, 5.0f, 1.0f);
    
    CCVector v0 = CCVectorizeVector3D(a), v1 = CCVectorizeVector3D(b);
    
    CCVector r = CCVectorize3Add(v0, v1);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(22.0f, 20.0f, 11.0f));
    
    r = CCVectorize3Sub(v0, v1);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(18.0f, 10.0f, 9.0f));
    
    r = CCVectorize3Mul(v0, v1);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(40.0f, 75.0f, 10.0f));
    
    r = CCVectorize3Div(v0, v1);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(10.0f, 3.0f, 10.0f));
}

-(void) testBasicVectorScalarArithmetic
{
    const CCVector3D a = CCVector3DMake(20.0f, 15.0f, 10.0f);
    const float b = 5.0f;
    
    CCVector v = CCVectorizeVector3D(a);
    CCVector r = CCVectorize3AddScalar(v, b);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(25.0f, 20.0f, 15.0f));
    
    r = CCVectorize3SubScalar(v, b);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(15.0f, 10.0f, 5.0f));
    
    r = CCVectorize3MulScalar(v, b);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(100.0f, 75.0f, 50.0f));
    
    r = CCVectorize3DivScalar(v, b);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(4.0f, 3.0f, 2.0f));
}

-(void) testVectorToVectorOperations
{
    CCVector3D a = CCVector3DMake(20.0f, 15.0f, 10.0f), b = CCVector3DMake(2.0f, 5.0f, 1.0f);
    
    CCVector v0 = CCVectorizeVector3D(a), v1 = CCVectorizeVector3D(b);
    
    CCVector r = CCVectorize3Lerp(v0, v1, 0.5f);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(r), CCVector3DMake(11.0f, 10.0f, 5.5f));
    
    
    b = CCVector3DMake(0.25f, 0.5f, 0.75f);
    v1 = CCVectorizeVector3D(b);
    
    r = CCVectorize3Project(v0, v1);
    XCTAssert(CCVector3Parallel(CCVectorizeGetVector3D(r), b), @"Should project a onto b, and the result should be parallel to b");
    
    r = CCVectorize3Reject(v0, v1);
    XCTAssert(CCVector3Ortho(CCVectorizeGetVector3D(r), b), @"Should reject a from b, and the result should be orthogonal to b");
}

-(void) testVectorReturningScalar
{
    const CCVector3D a = CCVector3DMake(0.0f, 0.0f, 1.0f), b = CCVector3DMake(0.0f, 0.0f, 5.0f);
    
    CCVector v0 = CCVectorizeVector3D(a), v1 = CCVectorizeVector3D(b);
    CCVector r = CCVectorize3Dot(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector3D(r).x, 5.0f);
    
    r = CCVectorize3Distance(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector3D(r).x, 4.0f);
    
    r = CCVectorize3DistanceSquare(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector3D(r).x, 16.0f);
    
    r = CCVectorize3Length(v0);
    XCTAssertEqual(CCVectorizeGetVector3D(r).x, 1.0f);
    
    r = CCVectorize3Angle(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector3D(r).x, 1.0f);
}

-(void) testVectorConditionalOperations
{
    const float v = 10.0f;
    const float smaller = v - 5.0f, larger = v + 5.0f;
    CCVector a = CCVectorizeVector3D(CCVector3DFill(v)), b = CCVectorizeVector3D(CCVector3DMake(larger, smaller, v));
    
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3Min(a, b)), CCVector3DMake(v, smaller, v));
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3Max(a, b)), CCVector3DMake(larger, v, v));
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3Clamp(a, CCVectorizeVector3D(CCVector3DMake(v, smaller, v)), CCVectorizeVector3D(CCVector3DMake(v, larger, v)))), CCVectorizeGetVector3D(a));
}

-(void) testSingleVectorOperations
{
    const CCVector3D a = CCVector3DMake(2.0f, 5.0f, 5.0f);
    CCVector v = CCVectorizeVector3D(a);
    
    XCTAssertEqual(CCVectorizeGetVector3D(CCVectorize3Length(CCVectorize3Normalize(v))).x, 1.0f);
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3Neg(v)), CCVector3DMake(-2.0f, -5.0f, -5.0f));
}

-(void) testGeometryOperations
{
    const CCVector3D a = CCVector3DMake(1.0f, 0.0f, 0.0f), b = CCVector3DMake(0.0f, 1.0f, 0.0f), c = CCVector3DMake(0.0f, 0.0f, 1.0f);
    CCVector v0 = CCVectorizeVector3D(a), v1 = CCVectorizeVector3D(b), v2 = CCVectorizeVector3D(c);
    
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3Perp(v0, v1, v2)), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3PerpR(v0, v1, v2)), CCVector3DMake(-1.0f, -1.0f, -1.0f));
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3Normal(v0, v1, v2)), CCVector3Normalize(CCVector3DMake(1.0f, 1.0f, 1.0f)));
    TEST_VECTOR3_EQUAL(CCVectorizeGetVector3D(CCVectorize3NormalR(v0, v1, v2)), CCVector3Normalize(CCVector3DMake(-1.0f, -1.0f, -1.0f)));
}

@end

#endif
