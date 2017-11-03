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

#undef __SSE__
#undef __SSE2__
#undef __SSE3__
#undef __SSSE3__
#undef __SSE4_1__
#undef __SSE4_2__
#undef __AVX__

#import "Vector4D.h"

@interface Vectorized4DTests : XCTestCase

@end

#define TEST_VECTOR4_EQUAL(v, equal) XCTAssert((v.x == equal.x) && (v.y == equal.y) && (v.z == equal.z) && (v.w == equal.w), @"Vector should be equal to { %.1f, %.1f, %.1f, %.1f }, not { %.1f, %.1f, %.1f, %.1f }", equal.x, equal.y, equal.z, equal.w, v.x, v.y, v.z, v.w)

@implementation Vectorized4DTests

-(void) testMake
{
    CCVector4D v = CCVectorizeGetVector4D(CCVectorizeVector4D(CCVector4DMake(0.0f, 1.0f, 2.0f, 3.0f)));
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f) && (v.z == 2.0f) && (v.w == 3.0f), @"Vector should be equal to { 0.0, 1.0, 2.0, 3.0f }, not { %.1f, %.1f, %.1f, %.1f }", v.x, v.y, v.z, v.w);
}

-(void) testBasicVectorVectorArithmetic
{
    const CCVector4D a = CCVector4DMake(20.0f, 15.0f, 10.0f, 100.0f), b = CCVector4DMake(2.0f, 5.0f, 1.0f, 10.0f);
    
    CCVector v0 = CCVectorizeVector4D(a), v1 = CCVectorizeVector4D(b);
    
    CCVector r = CCVectorize4Add(v0, v1);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(22.0f, 20.0f, 11.0f, 110.0f));
    
    r = CCVectorize4Sub(v0, v1);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(18.0f, 10.0f, 9.0f, 90.0f));
    
    r = CCVectorize4Mul(v0, v1);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(40.0f, 75.0f, 10.0f, 1000.0f));
    
    r = CCVectorize4Div(v0, v1);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(10.0f, 3.0f, 10.0f, 10.0f));
}

-(void) testBasicVectorScalarArithmetic
{
    const CCVector4D a = CCVector4DMake(20.0f, 15.0f, 10.0f, 5.0f);
    const float b = 5.0f;
    
    CCVector v = CCVectorizeVector4D(a);
    CCVector r = CCVectorize4AddScalar(v, b);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(25.0f, 20.0f, 15.0f, 10.0f));
    
    r = CCVectorize4SubScalar(v, b);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(15.0f, 10.0f, 5.0f, 0.0f));
    
    r = CCVectorize4MulScalar(v, b);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(100.0f, 75.0f, 50.0f, 25.0f));
    
    r = CCVectorize4DivScalar(v, b);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(4.0f, 3.0f, 2.0f, 1.0f));
}

-(void) testVectorToVectorOperations
{
    CCVector4D a = CCVector4DMake(20.0f, 15.0f, 10.0f, 0.0f), b = CCVector4DMake(2.0f, 5.0f, 1.0f, 10.0f);
    
    CCVector v0 = CCVectorizeVector4D(a), v1 = CCVectorizeVector4D(b);
    
    CCVector r = CCVectorize4Lerp(v0, v1, 0.5f);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(r), CCVector4DMake(11.0f, 10.0f, 5.5f, 5.0f));
    
    
    b = CCVector4DMake(0.25f, 0.5f, 0.75f, 0.0f);
    v1 = CCVectorizeVector4D(b);
    
    r = CCVectorize4Project(v0, v1);
    XCTAssert(CCVector4Parallel(CCVectorizeGetVector4D(r), b), @"Should project a onto b, and the result should be parallel to b");
    
    r = CCVectorize4Reject(v0, v1);
    XCTAssert(CCVector4Ortho(CCVectorizeGetVector4D(r), b), @"Should reject a from b, and the result should be orthogonal to b");
}

-(void) testVectorReturningScalar
{
    const CCVector4D a = CCVector4DMake(0.0f, 0.0f, 0.0f, 1.0f), b = CCVector4DMake(0.0f, 0.0f, 0.0f, 5.0f);
    
    CCVector v0 = CCVectorizeVector4D(a), v1 = CCVectorizeVector4D(b);
    CCVector r = CCVectorize4Dot(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector4D(r).x, 5.0f);
    
    r = CCVectorize4Distance(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector4D(r).x, 4.0f);
    
    r = CCVectorize4DistanceSquare(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector4D(r).x, 16.0f);
    
    r = CCVectorize4Length(v0);
    XCTAssertEqual(CCVectorizeGetVector4D(r).x, 1.0f);
    
    r = CCVectorize4Angle(v0, v1);
    XCTAssertEqual(CCVectorizeGetVector4D(r).x, 1.0f);
}

-(void) testVectorConditionalOperations
{
    const float v = 10.0f;
    const float smaller = v - 5.0f, larger = v + 5.0f;
    CCVector a = CCVectorizeVector4D(CCVector4DFill(v)), b = CCVectorizeVector4D(CCVector4DMake(larger, smaller, v, v));
    
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Min(a, b)), CCVector4DMake(v, smaller, v, v));
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Max(a, b)), CCVector4DMake(larger, v, v, v));
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Clamp(a, CCVectorizeVector4D(CCVector4DMake(v, smaller, v, v)), CCVectorizeVector4D(CCVector4DMake(v, larger, v, v)))), CCVectorizeGetVector4D(a));
}

-(void) testSingleVectorOperations
{
    const CCVector4D a = CCVector4DMake(2.0f, 5.0f, 5.0f, 10.0f);
    CCVector v = CCVectorizeVector4D(a);
    
    XCTAssertEqual(CCVectorizeGetVector4D(CCVectorize4Length(CCVectorize4Normalize(v))).x, 1.0f);
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Neg(v)), CCVector4DMake(-2.0f, -5.0f, -5.0f, -10.0f));
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Abs(CCVectorize4Neg(v))), a);
}

-(void) testGeometryOperations
{
    const CCVector4D a = CCVector4DMake(1.0f, 0.0f, 0.0f, 0.0f), b = CCVector4DMake(0.0f, 1.0f, 0.0f, 0.0f), c = CCVector4DMake(0.0f, 0.0f, 1.0f, 0.0f);
    CCVector v0 = CCVectorizeVector4D(a), v1 = CCVectorizeVector4D(b), v2 = CCVectorizeVector4D(c);
    
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Perp(v0, v1, v2)), CCVector4DMake(1.0f, 1.0f, 1.0f, 0.0f));
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4PerpR(v0, v1, v2)), CCVector4DMake(-1.0f, -1.0f, -1.0f, 0.0f));
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4Normal(v0, v1, v2)), CCVector4Normalize(CCVector4DMake(1.0f, 1.0f, 1.0f, 0.0f)));
    TEST_VECTOR4_EQUAL(CCVectorizeGetVector4D(CCVectorize4NormalR(v0, v1, v2)), CCVector4Normalize(CCVector4DMake(-1.0f, -1.0f, -1.0f, 0.0f)));
}

@end
