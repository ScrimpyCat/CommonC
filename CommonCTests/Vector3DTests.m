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

-(void) testEquality
{
    const CCVector3D a = CCVector3DMake(2.0f, 5.0f, 2.0f), b = CCVector3DMake(1.0f, 5.0f, 1.0f), c = CCVector3DMake(0.0f, 7.0f, 0.0f), d = CCVector3DMake(10.0f, 10.0f, 10.0f);
    
    XCTAssertFalse(CCVector3LessThan(a, a));
    XCTAssertFalse(CCVector3LessThan(a, b));
    XCTAssertFalse(CCVector3LessThan(a, c));
    XCTAssertTrue(CCVector3LessThan(a, d));
    XCTAssertTrue(CCVector3LessThanEqual(a, a));
    XCTAssertFalse(CCVector3LessThanEqual(a, b));
    XCTAssertFalse(CCVector3LessThanEqual(a, c));
    XCTAssertTrue(CCVector3LessThanEqual(a, d));
    XCTAssertFalse(CCVector3GreaterThan(a, a));
    XCTAssertFalse(CCVector3GreaterThan(a, b));
    XCTAssertFalse(CCVector3GreaterThan(a, c));
    XCTAssertTrue(CCVector3GreaterThan(d, a));
    XCTAssertTrue(CCVector3GreaterThanEqual(a, a));
    XCTAssertTrue(CCVector3GreaterThanEqual(a, b));
    XCTAssertFalse(CCVector3GreaterThanEqual(a, c));
    XCTAssertTrue(CCVector3GreaterThanEqual(d, a));
    
    XCTAssertTrue(CCVector3Equal(a, a));
    XCTAssertFalse(CCVector3Equal(a, b));
    XCTAssertFalse(CCVector3Equal(a, c));
    
    CCVector3Di Ulps = { 1, 1, 1 };
    XCTAssertTrue(CCVector3EqualUlps(a, a, Ulps));
    XCTAssertFalse(CCVector3EqualUlps(a, b, Ulps));
    XCTAssertFalse(CCVector3EqualUlps(a, c, Ulps));
    
    Ulps = (CCVector3Di){ CCFloatGetUlps(2.0f, 1.0f), CCFloatGetUlps(5.0f, 7.0f), CCFloatGetUlps(2.0f, 1.0f) };
    XCTAssertTrue(CCVector3EqualUlps(a, a, Ulps));
    XCTAssertTrue(CCVector3EqualUlps(a, b, Ulps));
    XCTAssertFalse(CCVector3EqualUlps(a, c, Ulps));
    
    CCVector3D RelativeDiff = CCVector3DMake(0.0f, 0.0f, 0.0f);
    XCTAssertTrue(CCVector3EqualRelative(a, a, RelativeDiff));
    XCTAssertFalse(CCVector3EqualRelative(a, b, RelativeDiff));
    XCTAssertFalse(CCVector3EqualRelative(a, c, RelativeDiff));
    
    RelativeDiff = CCVector3DMake(1.0f, 0.0f, 1.0f);
    XCTAssertTrue(CCVector3EqualRelative(a, a, RelativeDiff));
    XCTAssertTrue(CCVector3EqualRelative(a, b, RelativeDiff));
    XCTAssertFalse(CCVector3EqualRelative(a, c, RelativeDiff));
    
    CCVector3D Diff = CCVector3DMake(0.0f, 0.0f, 0.0f);
    XCTAssertTrue(CCVector3EqualAbsolute(a, a, Diff));
    XCTAssertFalse(CCVector3EqualAbsolute(a, b, Diff));
    XCTAssertFalse(CCVector3EqualAbsolute(a, c, Diff));
    
    Diff = CCVector3DMake(1.0f, 2.0f, 1.0f);
    XCTAssertTrue(CCVector3EqualAbsolute(a, a, Diff));
    XCTAssertTrue(CCVector3EqualAbsolute(a, b, Diff));
    XCTAssertFalse(CCVector3EqualAbsolute(a, c, Diff));
    
    
    
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThan(a, a), CCVector3DMake(0.0f, 0.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThan(a, b), CCVector3DMake(0.0f, 0.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThan(a, c), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThan(a, d), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThanEqual(a, a), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThanEqual(a, b), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThanEqual(a, c), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareLessThanEqual(a, d), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThan(a, a), CCVector3DMake(0.0f, 0.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThan(a, b), CCVector3DMake(1.0f, 0.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThan(a, c), CCVector3DMake(1.0f, 0.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThan(d, a), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThanEqual(a, a), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThanEqual(a, b), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThanEqual(a, c), CCVector3DMake(1.0f, 0.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareGreaterThanEqual(d, a), CCVector3DMake(1.0f, 1.0f, 1.0f));
    
    TEST_VECTOR3_EQUAL(CCVector3CompareEqual(a, a), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqual(a, b), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqual(a, c), CCVector3DMake(0.0f, 0.0f, 0.0f));
    
    Ulps = (CCVector3Di){ 1, 1, 1 };
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualUlps(a, a, Ulps), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualUlps(a, b, Ulps), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualUlps(a, c, Ulps), CCVector3DMake(0.0f, 0.0f, 0.0f));
    
    Ulps = (CCVector3Di){ CCFloatGetUlps(2.0f, 1.0f), CCFloatGetUlps(5.0f, 7.0f), CCFloatGetUlps(2.0f, 1.0f) };
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualUlps(a, a, Ulps), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualUlps(a, b, Ulps), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualUlps(a, c, Ulps), CCVector3DMake(0.0f, 1.0f, 0.0f));
    
    RelativeDiff = CCVector3DMake(0.0f, 0.0f, 0.0f);
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualRelative(a, a, RelativeDiff), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualRelative(a, b, RelativeDiff), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualRelative(a, c, RelativeDiff), CCVector3DMake(0.0f, 0.0f, 0.0f));
    
    RelativeDiff = CCVector3DMake(1.0f, 0.0f, 1.0f);
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualRelative(a, a, RelativeDiff), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualRelative(a, b, RelativeDiff), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualRelative(a, c, RelativeDiff), CCVector3DMake(1.0f, 0.0f, 1.0f));
    
    Diff = CCVector3DMake(0.0f, 0.0f, 0.0f);
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualAbsolute(a, a, Diff), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualAbsolute(a, b, Diff), CCVector3DMake(0.0f, 1.0f, 0.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualAbsolute(a, c, Diff), CCVector3DMake(0.0f, 0.0f, 0.0f));
    
    Diff = CCVector3DMake(1.0f, 2.0f, 1.0f);
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualAbsolute(a, a, Diff), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualAbsolute(a, b, Diff), CCVector3DMake(1.0f, 1.0f, 1.0f));
    TEST_VECTOR3_EQUAL(CCVector3CompareEqualAbsolute(a, c, Diff), CCVector3DMake(0.0f, 1.0f, 0.0f));
}

@end
