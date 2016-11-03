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

#import <XCTest/XCTest.h>
#import "Vector3D.h"

@interface Vector3DTests : XCTestCase

@end

#define TEST_VECTOR3_EQUAL(v, equal) XCTAssert((v.x == equal.x) && (v.y == equal.y) && (v.z == equal.z), @"Vector should be equal to { %.1f, %.1f, %.1f }, not { %.1f, %.1f, %.1f }", equal.x, equal.y, equal.z, v.x, v.y, v.z)

@implementation Vector3DTests

-(void) testMake
{
    CCVector3D v = CCVector3DMake(0.0f, 1.0f, 2.0f);
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f) && (v.z == 2.0f), @"Vector should be equal to { 0.0, 1.0, 2.0 }, not { %.1f, %.1f, %.1f }", v.x, v.y, v.z);
    
    v = CCVector3DFill(2.0f);
    XCTAssert((v.x == 2.0f) && (v.y == 2.0f) && (v.z == 2.0f), @"Vector should be equal to { 2.0, 2.0, 2.0 }, not { %.1f, %.1f, %.1f }", v.x, v.y, v.z);
    
    v = CCVector3DZero;
    XCTAssert((v.x == 0.0f) && (v.y == 0.0f) && (v.z == 0.0f), @"Vector should be equal to { 0.0, 0.0, 0.0 }, not { %.1f, %.1f, %.1f }", v.x, v.y, v.z);
}

-(void) testBasicVectorVectorArithmetic
{
    const CCVector3D a = CCVector3DMake(20.0f, 15.0f, 10.0f), b = CCVector3DMake(2.0f, 5.0f, 1.0f);
    
    CCVector3D r = CCVector3Add(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(22.0f, 20.0f, 11.0f));
    
    r = CCVector3Sub(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(18.0f, 10.0f, 9.0f));
    
    r = CCVector3Mul(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(40.0f, 75.0f, 10.0f));
    
    r = CCVector3Div(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(10.0f, 3.0f, 10.0f));
}

-(void) testBasicVectorScalarArithmetic
{
    const CCVector3D a = CCVector3DMake(20.0f, 15.0f, 10.0f);
    const float b = 5.0f;
    
    CCVector3D r = CCVector3AddScalar(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(25.0f, 20.0f, 15.0f));
    
    r = CCVector3SubScalar(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(15.0f, 10.0f, 5.0f));
    
    r = CCVector3MulScalar(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(100.0f, 75.0f, 50.0f));
    
    r = CCVector3DivScalar(a, b);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(4.0f, 3.0f, 2.0f));
}

-(void) testVectorToVectorOperations
{
    CCVector3D a = CCVector3DMake(20.0f, 15.0f, 10.0f), b = CCVector3DMake(2.0f, 5.0f, 1.0f);
    
    CCVector3D r = CCVector3Lerp(a, b, 0.5f);
    TEST_VECTOR3_EQUAL(r, CCVector3DMake(11.0f, 10.0f, 5.5f));
    
    b = CCVector3DMake(0.25f, 0.5f, 0.75f);
    r = CCVector3Project(a, b);
    XCTAssert(CCVector3Parallel(r, b), @"Should project a onto b, and the result should be parallel to b");
    
    r = CCVector3Reject(a, b);
    XCTAssert(CCVector3Ortho(r, b), @"Should reject a from b, and the result should be orthogonal to b");
}

-(void) testVectorReturningScalar
{
    const CCVector3D a = CCVector3DMake(0.0f, 0.0f, 1.0f), b = CCVector3DMake(0.0f, 0.0f, 5.0f);
    
    XCTAssertEqual(CCVector3Dot(a, b), 5.0f);
    XCTAssertEqual(CCVector3Distance(a, b), 4.0f);
    XCTAssertEqual(CCVector3DistanceSquare(a, b), 16.0f);
    XCTAssertEqual(CCVector3Length(a), 1.0f);
    XCTAssertEqual(CCVector3Angle(a, b), 1.0f);
}

-(void) testVectorConditionalOperations
{
    const float v = 10.0f;
    const float smaller = v - 5.0f, larger = v + 5.0f;
    const CCVector3D a = CCVector3DFill(v), b = CCVector3DMake(larger, smaller, v);
    
    TEST_VECTOR3_EQUAL(CCVector3Min(a, b), CCVector3DMake(v, smaller, v));
    TEST_VECTOR3_EQUAL(CCVector3Max(a, b), CCVector3DMake(larger, v, v));
    TEST_VECTOR3_EQUAL(CCVector3Clamp(a, CCVector3DMake(v, smaller, v), CCVector3DMake(v, larger, v)), a);
}

-(void) testSingleVectorOperations
{
    const CCVector3D a = CCVector3DMake(2.0f, 5.0f, 5.0f);
    
    XCTAssertEqual(CCVector3Length(CCVector3Normalize(a)), 1.0f);
    TEST_VECTOR3_EQUAL(CCVector3Neg(a), CCVector3DMake(-2.0f, -5.0f, -5.0f));
}

-(void) testGeometryOperations
{
    const CCVector3D a = CCVector3DMake(1.0f, 0.0f, 0.0f), b = CCVector3DMake(0.0f, 1.0f, 0.0f), c = CCVector3DMake(0.0f, 0.0f, 1.0f);
    
    TEST_VECTOR3_EQUAL(CCVector3Perp(a, b, c), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3PerpR(a, b, c), CCVector3DMake(-1.0f, -1.0f, -1.0f));
    TEST_VECTOR3_EQUAL(CCVector3Normal(a, b, c), CCVector3Normalize(CCVector3DMake(1.0f, 1.0f, 1.0f)));
    TEST_VECTOR3_EQUAL(CCVector3NormalR(a, b, c), CCVector3Normalize(CCVector3DMake(-1.0f, -1.0f, -1.0f)));
}

@end
