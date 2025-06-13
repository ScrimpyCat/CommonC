/*
 *  Copyright (c) 2025, Stefan Johnson
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
#import "Maths.h"
#import "Vector.h"

#define Ttype int
#include <CommonC/Range.h>

#define Ttype float
#include <CommonC/Range.h>

@interface RangeTests : XCTestCase
@end

@implementation RangeTests

-(void) testCreation
{
    CCRange(int) RangeI = CCRangeMake(4, 2);
    CCRange(float) RangeF = CCRangeMake(4.0f, 2.0f);
    CCRange(CCVector2D) Range2D = CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(20.0f, 25.0f));
    
    XCTAssertEqual(RangeI.start, 4, @"should have the correct value");
    XCTAssertEqual(RangeI.length, 2, @"should have the correct value");
    
    XCTAssertEqual(RangeF.start, 4.0f, @"should have the correct value");
    XCTAssertEqual(RangeF.length, 2.0f, @"should have the correct value");
    
    XCTAssertEqual(Range2D.start.x, 5.0f, @"should have the correct value");
    XCTAssertEqual(Range2D.start.y, 10.0f, @"should have the correct value");
    XCTAssertEqual(Range2D.length.x, 20.0f, @"should have the correct value");
    XCTAssertEqual(Range2D.length.y, 25.0f, @"should have the correct value");
}

-(void) testIntersects
{
    CCRange(int) RangeI = CCRangeMake(4, 2);
    
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(0, 2)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(0, 1)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(0, 0)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(3, 2)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(3, 1)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(3, 0)), @"should not contain");
    XCTAssertTrue(CCRangeContains(RangeI, CCRangeMake(4, 2)), @"should contain");
    XCTAssertTrue(CCRangeContains(RangeI, CCRangeMake(4, 1)), @"should contain");
    XCTAssertTrue(CCRangeContains(RangeI, CCRangeMake(4, 0)), @"should contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(5, 2)), @"should not contain");
    XCTAssertTrue(CCRangeContains(RangeI, CCRangeMake(5, 1)), @"should contain");
    XCTAssertTrue(CCRangeContains(RangeI, CCRangeMake(5, 0)), @"should contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(6, 2)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(6, 1)), @"should not contain");
    XCTAssertTrue(CCRangeContains(RangeI, CCRangeMake(6, 0)), @"should contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(7, 2)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(7, 1)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeI, CCRangeMake(7, 0)), @"should not contain");
    
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(0, 2)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(0, 1)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(0, 0)), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(3, 2)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(3, 1)), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(3, 0)), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(4, 2)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(4, 1)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(4, 0)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(5, 2)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(5, 1)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(5, 0)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(6, 2)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(6, 1)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeI, CCRangeMake(6, 0)), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(7, 2)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(7, 1)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeI, CCRangeMake(7, 0)), @"should not intersect");
    
    
    CCRange(float) RangeF = CCRangeMake(4.0f, 2.0f);
    
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(0.0f, 2.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(0.0f, 1.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(0.0f, 0.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(3.0f, 2.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(3.0f, 1.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(3.0f, 0.0f)), @"should not contain");
    XCTAssertTrue(CCRangeContains(RangeF, CCRangeMake(4.0f, 2.0f)), @"should contain");
    XCTAssertTrue(CCRangeContains(RangeF, CCRangeMake(4.0f, 1.0f)), @"should contain");
    XCTAssertTrue(CCRangeContains(RangeF, CCRangeMake(4.0f, 0.0f)), @"should contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(5.0f, 2.0f)), @"should not contain");
    XCTAssertTrue(CCRangeContains(RangeF, CCRangeMake(5.0f, 1.0f)), @"should contain");
    XCTAssertTrue(CCRangeContains(RangeF, CCRangeMake(5.0f, 0.0f)), @"should contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(6.0f, 2.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(6.0f, 1.0f)), @"should not contain");
    XCTAssertTrue(CCRangeContains(RangeF, CCRangeMake(6.0f, 0.0f)), @"should contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(7.0f, 2.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(7.0f, 1.0f)), @"should not contain");
    XCTAssertFalse(CCRangeContains(RangeF, CCRangeMake(7.0f, 0.0f)), @"should not contain");
    
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(0.0f, 2.0f)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(0.0f, 1.0f)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(0.0f, 0.0f)), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(3.0f, 2.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(3.0f, 1.0f)), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(3.0f, 0.0f)), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(4.0f, 2.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(4.0f, 1.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(4.0f, 0.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(5.0f, 2.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(5.0f, 1.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(5.0f, 0.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(6.0f, 2.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(6.0f, 1.0f)), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(RangeF, CCRangeMake(6.0f, 0.0f)), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(7.0f, 2.0f)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(7.0f, 1.0f)), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(RangeF, CCRangeMake(7.0f, 0.0f)), @"should not intersect");
    
    
    CCRange(CCVector2D) Range2D = CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 2.0f));
    
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not contain");
    
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not contain");
    
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertTrue(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not contain");
    
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not contain");
    
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not contain");
    
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    XCTAssertFalse(CCRangeContains(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not contain");
    
    
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(0.0f, 0.0f))), @"should not intersect");
    
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(2.0f, 1.0f))), @"should not intersect");
    
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(4.0f, 2.0f))), @"should not intersect");
    
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(5.0f, 2.0f))), @"should not intersect");
    
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(4.0f, 3.0f))), @"should not intersect");
    
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(0.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(4.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(5.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(7.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertTrue(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(9.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(10.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(11.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 0.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 9.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 10.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 11.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 12.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
    XCTAssertFalse(CCRangeIntersects(Range2D, CCRangeMake(CCVector2DMake(12.0f, 13.0f), CCVector2DMake(5.0f, 3.0f))), @"should not intersect");
}

-(void) testGetIntersection
{
    CCRange(int) RangeI = CCRangeMake(4, 2);
    CCRange(int) ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(1, 3));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 0, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(1, 4));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 1, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(1, 5));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 2, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(1, 8));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 2, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(1, 4));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 1, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(4, 0));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 0, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(4, 1));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 1, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(4, 2));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 2, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(4, 3));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 2, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(4, 4));
    
    XCTAssertEqual(ResultI.start, 4, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 2, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(5, 0));
    
    XCTAssertEqual(ResultI.start, 5, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 0, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(5, 1));
    
    XCTAssertEqual(ResultI.start, 5, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 1, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(5, 2));
    
    XCTAssertEqual(ResultI.start, 5, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 1, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(6, 0));
    
    XCTAssertEqual(ResultI.start, 6, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 0, @"should get the intersection");
    
    
    ResultI = CCRangeGetIntersection(RangeI, CCRangeMake(6, 1));
    
    XCTAssertEqual(ResultI.start, 6, @"should get the intersection");
    XCTAssertEqual(ResultI.length, 0, @"should get the intersection");
    
    
    
    CCRange(CCVector2D) Range2D = CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 2.0f));
    CCRange(CCVector2D) Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(4.0f, 6.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(6.0f, 6.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(4.0f, 7.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(6.0f, 7.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(8.0f, 6.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(4.0f, 8.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(8.0f, 8.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(10.0f, 6.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(4.0f, 10.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(1.0f, 4.0f), CCVector2DMake(10.0f, 10.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(0.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(2.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(0.0f, 1.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(2.0f, 1.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(0.0f, 2.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(4.0f, 2.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(6.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(0.0f, 4.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(5.0f, 10.0f), CCVector2DMake(6.0f, 4.0f)));
    
    XCTAssertEqual(Result2D.start.x, 5.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 10.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 4.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 2.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(0.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(2.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(0.0f, 1.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(2.0f, 1.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(4.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(0.0f, 2.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(7.0f, 11.0f), CCVector2DMake(4.0f, 2.0f)));
    
    XCTAssertEqual(Result2D.start.x, 7.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 11.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 2.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 1.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(0.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 9.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 12.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(2.0f, 0.0f)));
    
    XCTAssertEqual(Result2D.start.x, 9.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 12.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(0.0f, 1.0f)));
    
    XCTAssertEqual(Result2D.start.x, 9.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 12.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
    
    
    Result2D = CCRangeGetIntersection(Range2D, CCRangeMake(CCVector2DMake(9.0f, 12.0f), CCVector2DMake(2.0f, 1.0f)));
    
    XCTAssertEqual(Result2D.start.x, 9.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.start.y, 12.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.x, 0.0f, @"should get the intersection");
    XCTAssertEqual(Result2D.length.y, 0.0f, @"should get the intersection");
}

@end
