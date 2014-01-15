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

#if !__SSE4_1__
#warning "Will not run test. Missing support for SSE4.1 either not enabled or hardware can't support."
#else
#import <XCTest/XCTest.h>

//#undef __SSE__
//#undef __SSE2__
//#undef __SSE3__
//#undef __SSSE3__
//#undef __SSE4_1__
#undef __SSE4_2__
#undef __AVX__

#import "Vector2D.h"

@interface Vector2DSSE4_1Tests : XCTestCase

@end

#define TEST_VECTOR2_EQUAL(v, equal) XCTAssert((v.x == equal.x) && (v.y == equal.y), @"Vector should be equal to { %.1f, %.1f }, not { %.1f, %.1f }", equal.x, equal.y, v.x, v.y)

@implementation Vector2DSSE4_1Tests

-(void) testMake
{
    CCVector2D v = CCVector2DMake(0.0f, 1.0f);
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f), @"Vector should be equal to { 0.0, 1.0 }, not { %.1f, %.1f }", v.x, v.y);
    
    v = CCVector2DFill(2.0f);
    XCTAssert((v.x == 2.0f) && (v.y == 2.0f), @"Vector should be equal to { 2.0, 2.0 }, not { %.1f, %.1f }", v.x, v.y);
    
    v = CCVector2DZero;
    XCTAssert((v.x == 0.0f) && (v.y == 0.0f), @"Vector should be equal to { 0.0, 0.0 }, not { %.1f, %.1f }", v.x, v.y);
}

-(void) testBasicVectorVectorArithmetic
{
    const CCVector2D a = CCVector2DMake(20.0f, 15.0f), b = CCVector2DMake(2.0f, 5.0f);
    
    CCVector2D r = CCVector2Add(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(22.0f, 20.0f));
    
    r = CCVector2Sub(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(18.0f, 10.0f));
    
    r = CCVector2Mul(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(40.0f, 75.0f));
    
    r = CCVector2Div(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(10.0f, 3.0f));
}

-(void) testBasicVectorScalarArithmetic
{
    const CCVector2D a = CCVector2DMake(20.0f, 15.0f);
    const float b = 5.0f;
    
    CCVector2D r = CCVector2AddScalar(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(25.0f, 20.0f));
    
    r = CCVector2SubScalar(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(15.0f, 10.0f));
    
    r = CCVector2MulScalar(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(100.0f, 75.0f));
    
    r = CCVector2DivScalar(a, b);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(4.0f, 3.0f));
}

-(void) testVectorToVectorOperations
{
    CCVector2D a = CCVector2DMake(20.0f, 15.0f), b = CCVector2DMake(2.0f, 5.0f);
    
    CCVector2D r = CCVector2Lerp(a, b, 0.5f);
    TEST_VECTOR2_EQUAL(r, CCVector2DMake(11.0f, 10.0f));
    
    b = CCVector2DMake(0.25f, 0.5f);
    r = CCVector2Project(a, b);
    XCTAssert(CCVector2Parallel(r, b), @"Should project a onto b, and the result should be parallel to b");
    
    r = CCVector2Reject(a, b);
    XCTAssert(CCVector2Ortho(r, b), @"Should reject a from b, and the result should be orthogonal to b");
}

-(void) testVectorReturningScalar
{
    const CCVector2D a = CCVector2DMake(0.0f, 1.0f), b = CCVector2DMake(0.0f, 5.0f);
    
    XCTAssertEqual(CCVector2Dot(a, b), 5.0f);
    XCTAssertEqual(CCVector2Distance(a, b), 4.0f);
    XCTAssertEqual(CCVector2DistanceSquare(a, b), 16.0f);
    XCTAssertEqual(CCVector2Length(a), 1.0f);
    XCTAssertEqual(CCVector2Angle(a, b), 1.0f);
}

-(void) testVectorConditionalOperations
{
    const float v = 10.0f;
    const float smaller = v - 5.0f, larger = v + 5.0f;
    const CCVector2D a = CCVector2DFill(v), b = CCVector2DMake(larger, smaller);
    
    TEST_VECTOR2_EQUAL(CCVector2Min(a, b), CCVector2DMake(v, smaller));
    TEST_VECTOR2_EQUAL(CCVector2Max(a, b), CCVector2DMake(larger, v));
    TEST_VECTOR2_EQUAL(CCVector2Clamp(a, CCVector2DMake(v, smaller), CCVector2DMake(v, larger)), a);
}

-(void) testSingleVectorOperations
{
    const CCVector2D a = CCVector2DMake(2.0f, 5.0f);
    
    TEST_VECTOR2_EQUAL(CCVector2Perp(a), CCVector2DMake(-5.0f, 2.0f));
    TEST_VECTOR2_EQUAL(CCVector2PerpR(a), CCVector2DMake(5.0f, -2.0f));
    XCTAssertEqual(CCVector2Length(CCVector2Normalize(a)), 1.0f);
    TEST_VECTOR2_EQUAL(CCVector2Neg(a), CCVector2DMake(-2.0f, -5.0f));
}

@end

#endif
