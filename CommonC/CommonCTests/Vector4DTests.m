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

#import <XCTest/XCTest.h>
#import "Vector4D.h"

@interface Vector4DTests : XCTestCase

@end

#define TEST_VECTOR4_EQUAL(v, equal) XCTAssert((v.x == equal.x) && (v.y == equal.y) && (v.z == equal.z) && (v.w == equal.w), @"Vector should be equal to { %.1f, %.1f, %.1f, %.1f }, not { %.1f, %.1f, %.1f, %.1f }", equal.x, equal.y, equal.z, equal.w, v.x, v.y, v.z, v.w)

@implementation Vector4DTests

-(void) testMake
{
    CCVector4D v = CCVector4DMake(0.0f, 1.0f, 2.0f, 3.0f);
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f) && (v.z == 2.0f) && (v.w == 3.0f), @"Vector should be equal to { 0.0, 1.0, 2.0, 3.0 }, not { %.1f, %.1f, %.1f, %.1f }", v.x, v.y, v.z, v.w);
    
    v = CCVector4DFill(2.0f);
    XCTAssert((v.x == 2.0f) && (v.y == 2.0f) && (v.z == 2.0f) && (v.w == 2.0f), @"Vector should be equal to { 2.0, 2.0, 2.0, 2.0 }, not { %.1f, %.1f, %.1f, %.1f }", v.x, v.y, v.z, v.w);
    
    v = CCVector4DZero;
    XCTAssert((v.x == 0.0f) && (v.y == 0.0f) && (v.z == 0.0f) && (v.w == 0.0f), @"Vector should be equal to { 0.0, 0.0, 0.0, 0.0 }, not { %.1f, %.1f, %.1f, %.1f }", v.x, v.y, v.z, v.w);
}

-(void) testBasicVectorVectorArithmetic
{
    const CCVector4D a = CCVector4DMake(20.0f, 15.0f, 10.0f, 100.0f), b = CCVector4DMake(2.0f, 5.0f, 1.0f, 10.0f);
    
    CCVector4D r = CCVector4Add(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(22.0f, 20.0f, 11.0f, 110.0f));
    
    r = CCVector4Sub(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(18.0f, 10.0f, 9.0f, 90.0f));
    
    r = CCVector4Mul(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(40.0f, 75.0f, 10.0f, 1000.0f));
    
    r = CCVector4Div(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(10.0f, 3.0f, 10.0f, 10.0f));
}

-(void) testBasicVectorScalarArithmetic
{
    const CCVector4D a = CCVector4DMake(20.0f, 15.0f, 10.0f, 5.0f);
    const float b = 5.0f;
    
    CCVector4D r = CCVector4AddScalar(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(25.0f, 20.0f, 15.0f, 10.0f));
    
    r = CCVector4SubScalar(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(15.0f, 10.0f, 5.0f, 0.0f));
    
    r = CCVector4MulScalar(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(100.0f, 75.0f, 50.0f, 25.0f));
    
    r = CCVector4DivScalar(a, b);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(4.0f, 3.0f, 2.0f, 1.0f));
}

-(void) testVectorToVectorOperations
{
    CCVector4D a = CCVector4DMake(20.0f, 15.0f, 10.0f, 0.0f), b = CCVector4DMake(2.0f, 5.0f, 1.0f, 10.0f);
    
    CCVector4D r = CCVector4Lerp(a, b, 0.5f);
    TEST_VECTOR4_EQUAL(r, CCVector4DMake(11.0f, 10.0f, 5.5f, 5.0f));
    
    b = CCVector4DMake(0.25f, 0.5f, 0.75f, 0.0f);
    r = CCVector4Project(a, b);
    XCTAssert(CCVector4Parallel(r, b), @"Should project a onto b, and the result should be parallel to b");
    
    r = CCVector4Reject(a, b);
    XCTAssert(CCVector4Ortho(r, b), @"Should reject a from b, and the result should be orthogonal to b");
}

-(void) testVectorReturningScalar
{
    const CCVector4D a = CCVector4DMake(0.0f, 0.0f, 0.0f, 1.0f), b = CCVector4DMake(0.0f, 0.0f, 0.0f, 5.0f);
    
    XCTAssertEqual(CCVector4Dot(a, b), 5.0f);
    XCTAssertEqual(CCVector4Distance(a, b), 4.0f);
    XCTAssertEqual(CCVector4DistanceSquare(a, b), 16.0f);
    XCTAssertEqual(CCVector4Length(a), 1.0f);
    XCTAssertEqual(CCVector4Angle(a, b), 1.0f);
}

-(void) testVectorConditionalOperations
{
    const float v = 10.0f;
    const float smaller = v - 5.0f, larger = v + 5.0f;
    const CCVector4D a = CCVector4DFill(v), b = CCVector4DMake(larger, smaller, v, v);
    
    TEST_VECTOR4_EQUAL(CCVector4Min(a, b), CCVector4DMake(v, smaller, v, v));
    TEST_VECTOR4_EQUAL(CCVector4Max(a, b), CCVector4DMake(larger, v, v, v));
    TEST_VECTOR4_EQUAL(CCVector4Clamp(a, CCVector4DMake(v, smaller, v, v), CCVector4DMake(v, larger, v, v)), a);
}

-(void) testSingleVectorOperations
{
    const CCVector4D a = CCVector4DMake(2.0f, 5.0f, 5.0f, 10.0f);
    
    XCTAssertEqual(CCVector4Length(CCVector4Normalize(a)), 1.0f);
    TEST_VECTOR4_EQUAL(CCVector4Neg(a), CCVector4DMake(-2.0f, -5.0f, -5.0f, -10.0f));
}

-(void) testGeometryOperations
{
    const CCVector4D a = CCVector4DMake(1.0f, 0.0f, 0.0f, 0.0f), b = CCVector4DMake(0.0f, 1.0f, 0.0f, 0.0f), c = CCVector4DMake(0.0f, 0.0f, 1.0f, 0.0f);
    
    TEST_VECTOR4_EQUAL(CCVector4Perp(a, b, c), CCVector4DMake(1.0f, 1.0f, 1.0f, 0.0f));
    TEST_VECTOR4_EQUAL(CCVector4PerpR(a, b, c), CCVector4DMake(-1.0f, -1.0f, -1.0f, 0.0f));
    TEST_VECTOR4_EQUAL(CCVector4Normal(a, b, c), CCVector4Normalize(CCVector4DMake(1.0f, 1.0f, 1.0f, 0.0f)));
    TEST_VECTOR4_EQUAL(CCVector4NormalR(a, b, c), CCVector4Normalize(CCVector4DMake(-1.0f, -1.0f, -1.0f, 0.0f)));
}

@end
