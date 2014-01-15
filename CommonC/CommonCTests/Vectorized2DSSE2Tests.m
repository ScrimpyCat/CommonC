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

#import "Vector2D.h"

@interface Vectorized2DSSE2Tests : XCTestCase

@end

#define TEST_VECTOR2_EQUAL(v, equal) XCTAssert((v.x == equal.x) && (v.y == equal.y), @"Vector should be equal to { %.1f, %.1f }, not { %.1f, %.1f }", equal.x, equal.y, v.x, v.y)

@implementation Vectorized2DSSE2Tests

-(void) testMake
{
    CCVector2D v = CCVectorizeGetVector2D(CCVectorizeVector2D(CCVector2DMake(0.0f, 1.0f)));
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f), @"Vector should be equal to { 0.0, 1.0 }, not { %.1f, %.1f }", v.x, v.y);
    
    v = CCVectorizeExtractVector2D(CCVectorizeVector2D(CCVector2DMake(0.0f, 1.0f)), 0);
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f), @"Vector should be equal to { 0.0, 1.0 }, not { %.1f, %.1f }", v.x, v.y);
    
    v = CCVectorizeExtractVector2D(CCVectorizeVector2DPack(CCVector2DZero, CCVector2DMake(0.0f, 1.0f)), 1);
    XCTAssert((v.x == 0.0f) && (v.y == 1.0f), @"Vector should be equal to { 0.0, 1.0 }, not { %.1f, %.1f }", v.x, v.y);
}

-(void) testBasicVectorVectorArithmetic
{
    const CCVector2D a = CCVector2DMake(20.0f, 15.0f), b = CCVector2DMake(2.0f, 5.0f);
    const CCVector2D c = CCVector2DMake(3.0f, 4.0f), d = CCVector2DMake(0.2f, 0.5f);
    
    CCVector v0 = CCVectorizeVector2DPack(a, c), v1 = CCVectorizeVector2DPack(b, d);
    
    CCVector r = CCVectorize2PackedAdd(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(22.0f, 20.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(3.2f, 4.5f));
    
    r = CCVectorize2PackedSub(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(18.0f, 10.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(2.8f, 3.5f));
    
    r = CCVectorize2PackedMul(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(40.0f, 75.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(0.6f, 2.0f));
    
    r = CCVectorize2PackedDiv(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(10.0f, 3.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(15.0f, 8.0f));
    
    
    v0 = CCVectorizeVector2D(a), v1 = CCVectorizeVector2D(b);
    
    r = CCVectorize2PackedAdd(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(22.0f, 20.0f));
    
    r = CCVectorize2PackedSub(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(18.0f, 10.0f));
    
    r = CCVectorize2PackedMul(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(40.0f, 75.0f));
    
    r = CCVectorize2PackedDiv(v0, v1);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(10.0f, 3.0f));
}

-(void) testBasicVectorScalarArithmetic
{
    const CCVector2D a = CCVector2DMake(20.0f, 15.0f), c = CCVector2DMake(0.2f, 0.5f);
    const float b = 5.0f;
    
    CCVector v = CCVectorizeVector2DPack(a, c);
    CCVector r = CCVectorize2PackedAddScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(25.0f, 20.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(5.2f, 5.5f));
    
    r = CCVectorize2PackedSubScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(15.0f, 10.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(-4.8f, -4.5f));
    
    r = CCVectorize2PackedMulScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(100.0f, 75.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(1.0f, 2.5f));
    
    r = CCVectorize2PackedDivScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(4.0f, 3.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(0.04f, 0.1f));
    
    
    v = CCVectorizeVector2DPack(a, c);
    r = CCVectorize2PackedAddScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(25.0f, 20.0f));
    
    r = CCVectorize2PackedSubScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(15.0f, 10.0f));
    
    r = CCVectorize2PackedMulScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(100.0f, 75.0f));
    
    r = CCVectorize2PackedDivScalar(v, b);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(4.0f, 3.0f));
}

-(void) testVectorToVectorOperations
{
    CCVector2D a = CCVector2DMake(20.0f, 15.0f), b = CCVector2DMake(2.0f, 5.0f);
    CCVector2D c = CCVector2DMake(3.0f, 4.0f), d = CCVector2DMake(0.2f, 0.5f);
    
    CCVector v0 = CCVectorizeVector2DPack(a, c), v1 = CCVectorizeVector2DPack(b, d);
    
    CCVector r = CCVectorize2PackedLerp(v0, v1, 0.5f);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(11.0f, 10.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 1), CCVector2DMake(1.6f, 2.25f));
    
    
    b = CCVector2DMake(0.25f, 0.5f);
    v1 = CCVectorizeVector2DPack(b, d);
    
    r = CCVectorize2PackedProject(v0, v1);
    XCTAssert(CCVector2Parallel(CCVectorizeExtractVector2D(r, 0), b), @"Should project a onto b, and the result should be parallel to b");
    XCTAssert(CCVector2Parallel(CCVectorizeExtractVector2D(r, 1), d), @"Should project c onto d, and the result should be parallel to d");
    
    r = CCVectorize2PackedReject(v0, v1);
    XCTAssert(CCVector2Ortho(CCVectorizeExtractVector2D(r, 0), b), @"Should reject a from b, and the result should be orthogonal to b");
    XCTAssert(CCVector2Ortho(CCVectorizeExtractVector2D(r, 1), d), @"Should reject c from d, and the result should be orthogonal to d");
    
    
    
    b = CCVector2DMake(2.0f, 5.0f);
    v0 = CCVectorizeVector2D(a), v1 = CCVectorizeVector2D(b);
    
    r = CCVectorize2PackedLerp(v0, v1, 0.5f);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(r, 0), CCVector2DMake(11.0f, 10.0f));
    
    
    b = CCVector2DMake(0.25f, 0.5f);
    v1 = CCVectorizeVector2D(b);
    
    r = CCVectorize2PackedProject(v0, v1);
    XCTAssert(CCVector2Parallel(CCVectorizeExtractVector2D(r, 0), b), @"Should project a onto b, and the result should be parallel to b");
    
    r = CCVectorize2PackedReject(v0, v1);
    XCTAssert(CCVector2Ortho(CCVectorizeExtractVector2D(r, 0), b), @"Should reject a from b, and the result should be orthogonal to b");
}

-(void) testVectorReturningScalar
{
    const CCVector2D a = CCVector2DMake(0.0f, 1.0f), b = CCVector2DMake(0.0f, 5.0f);
    const CCVector2D c = CCVector2DMake(1.0f, 0.0f), d = CCVector2DMake(2.0f, 0.0f);
    
    CCVector v0 = CCVectorizeVector2DPack(a, c), v1 = CCVectorizeVector2DPack(b, d);
    CCVector r = CCVectorize2PackedDot(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 5.0f);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 1).x, 2.0f);
    
    r = CCVectorize2PackedDistance(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 4.0f);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 1).x, 1.0f);
    
    r = CCVectorize2PackedDistanceSquare(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 16.0f);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 1).x, 1.0f);
    
    r = CCVectorize2PackedLength(v0);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 1.0f);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 1).x, 1.0f);
    
    r = CCVectorize2PackedAngle(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 1.0f);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 1).x, 1.0f);
    
    
    
    v0 = CCVectorizeVector2D(a), v1 = CCVectorizeVector2D(b);
    r = CCVectorize2PackedDot(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 5.0f);
    
    r = CCVectorize2PackedDistance(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 4.0f);
    
    r = CCVectorize2PackedDistanceSquare(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 16.0f);
    
    r = CCVectorize2PackedLength(v0);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 1.0f);
    
    r = CCVectorize2PackedAngle(v0, v1);
    XCTAssertEqual(CCVectorizeExtractVector2D(r, 0).x, 1.0f);
}

-(void) testVectorConditionalOperations
{
    const float v = 10.0f;
    const float smaller = v - 5.0f, larger = v + 5.0f;
    CCVector a = CCVectorizeVector2DPack(CCVector2DFill(v), CCVector2DFill(v)), b = CCVectorizeVector2DPack(CCVector2DMake(larger, smaller), CCVector2DMake(larger, smaller));
    
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedMin(a, b), 0), CCVector2DMake(v, smaller));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedMax(a, b), 0), CCVector2DMake(larger, v));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedClamp(a, CCVectorizeVector2DPack(CCVector2DMake(v, smaller), CCVector2DMake(v, smaller)), CCVectorizeVector2DPack(CCVector2DMake(v, larger), CCVector2DMake(v, larger))), 0), CCVectorizeExtractVector2D(a, 0));
    
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedMin(a, b), 1), CCVector2DMake(v, smaller));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedMax(a, b), 1), CCVector2DMake(larger, v));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedClamp(a, CCVectorizeVector2DPack(CCVector2DMake(v, smaller), CCVector2DMake(v, smaller)), CCVectorizeVector2DPack(CCVector2DMake(v, larger), CCVector2DMake(v, larger))), 1), CCVectorizeExtractVector2D(a, 1));
}

-(void) testSingleVectorOperations
{
    const CCVector2D a = CCVector2DMake(2.0f, 5.0f), b = CCVector2DMake(1.0f, 1.5f);
    CCVector v = CCVectorizeVector2DPack(a, b);
    
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedPerp(v), 0), CCVector2DMake(-5.0f, 2.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedPerpR(v), 0), CCVector2DMake(5.0f, -2.0f));
    XCTAssertEqual(CCVectorizeExtractVector2D(CCVectorize2PackedLength(CCVectorize2PackedNormalize(v)), 0).x, 1.0f);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedNeg(v), 0), CCVector2DMake(-2.0f, -5.0f));
    
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedPerp(v), 1), CCVector2DMake(-1.5f, 1.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedPerpR(v), 1), CCVector2DMake(1.5f, -1.0f));
    XCTAssertEqual(CCVectorizeExtractVector2D(CCVectorize2PackedLength(CCVectorize2PackedNormalize(v)), 1).x, 1.0f);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedNeg(v), 1), CCVector2DMake(-1.0f, -1.5f));
    
    
    v = CCVectorizeVector2D(a);
    
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedPerp(v), 0), CCVector2DMake(-5.0f, 2.0f));
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedPerpR(v), 0), CCVector2DMake(5.0f, -2.0f));
    XCTAssertEqual(CCVectorizeExtractVector2D(CCVectorize2PackedLength(CCVectorize2PackedNormalize(v)), 0).x, 1.0f);
    TEST_VECTOR2_EQUAL(CCVectorizeExtractVector2D(CCVectorize2PackedNeg(v), 0), CCVector2DMake(-2.0f, -5.0f));
}


@end

#endif
