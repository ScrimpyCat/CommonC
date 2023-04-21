/*
*  Copyright (c) 2023, Stefan Johnson
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
#import "BitSets.h"

@interface BitSetsTests : XCTestCase

@end

@implementation BitSetsTests

-(void) testSets
{
    CCBits(uint8_t, 12) x;
    
    CC_BITS_INIT_SET(x);
    
    XCTAssertTrue(CCBitsGet(x, 0), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 1), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 2), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 3), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 4), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 5), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 6), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 7), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 8), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 9), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 10), @"should be initialised as true");
    XCTAssertTrue(CCBitsGet(x, 11), @"should be initialised as true");
    
    CCBitsClear(x, 4);
    CCBitsClear(x, 9);
    
    XCTAssertTrue(CCBitsGet(x, 0), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 1), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 2), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 3), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 4), @"should be cleared");
    XCTAssertTrue(CCBitsGet(x, 5), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 6), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 7), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 8), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 9), @"should be cleared");
    XCTAssertTrue(CCBitsGet(x, 10), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 11), @"should be unchanged");
    
    CC_BITS_INIT_CLEAR(x);
    
    XCTAssertFalse(CCBitsGet(x, 0), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 1), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 2), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 3), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 4), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 5), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 6), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 7), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 8), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 9), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 10), @"should be initialised as false");
    XCTAssertFalse(CCBitsGet(x, 11), @"should be initialised as false");
    
    CCBitsSet(x, 4);
    CCBitsSet(x, 9);
    
    XCTAssertFalse(CCBitsGet(x, 0), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 1), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 2), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 3), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 4), @"should be set");
    XCTAssertFalse(CCBitsGet(x, 5), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 6), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 7), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 8), @"should be unchanged");
    XCTAssertTrue(CCBitsGet(x, 9), @"should be set");
    XCTAssertFalse(CCBitsGet(x, 10), @"should be unchanged");
    XCTAssertFalse(CCBitsGet(x, 11), @"should be unchanged");
}

@end
