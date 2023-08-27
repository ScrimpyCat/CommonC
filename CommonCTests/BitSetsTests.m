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

static size_t TestCount8(CCBits(uint8_t, 0) Bits, size_t Index, size_t Count)
{
    size_t Sum = 0;
    for (size_t Loop = 0; Loop < Count; Loop++) Sum += CCBitsGet(Bits, Index + Loop);
    
    return Sum;
}
static size_t TestCount32(CCBits(uint32_t, 0) Bits, size_t Index, size_t Count)
{
    size_t Sum = 0;
    for (size_t Loop = 0; Loop < Count; Loop++) Sum += CCBitsGet(Bits, Index + Loop);
    
    return Sum;
}

-(void) testCount
{
#define ASSERT_COUNT(bits, index, count) XCTAssertEqual(CCBitsCount(bits, index, count), ASSERT_FUNC(bits, index, count), @"should count the correct number of bits in range %zu,%zu", (size_t)index, (size_t)count);
    
#define ASSERT_FUNC TestCount8
    
    CCBits(uint8_t, 193) x;
    
    CC_BITS_INIT_SET(x);
    
    CCBitsClear(x, 7);
    
    CCBitsClear(x, 144);
    
    CCBitsClear(x, 152);
    CCBitsClear(x, 153);
    
    CCBitsClear(x, 160);
    CCBitsClear(x, 161);
    CCBitsClear(x, 162);
    
    CCBitsClear(x, 168);
    CCBitsClear(x, 169);
    CCBitsClear(x, 170);
    CCBitsClear(x, 171);
    
    CCBitsClear(x, 176);
    CCBitsClear(x, 177);
    CCBitsClear(x, 178);
    CCBitsClear(x, 179);
    CCBitsClear(x, 180);
    
    CCBitsClear(x, 184);
    CCBitsClear(x, 185);
    CCBitsClear(x, 186);
    CCBitsClear(x, 187);
    CCBitsClear(x, 188);
    CCBitsClear(x, 189);
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_COUNT(x, Index, Count);
        }
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        if (Index % 3 == 0) CCBitsClear(x, Index);
        else if (Index % 5 == 0) CCBitsClear(x, Index);
        else if (Index % 18 == 0) CCBitsClear(x, Index);
        else if (Index % 29 == 0) CCBitsClear(x, Index);
        else if (Index % 53 == 0) CCBitsClear(x, Index);
        else if (Index % 120 == 0) CCBitsClear(x, Index);
        else if (Index % 122 == 0) CCBitsClear(x, Index);
        else if (Index % 124 == 0) CCBitsClear(x, Index);
        else if (Index % 128 == 0) CCBitsClear(x, Index);
        else if (Index % 133 == 0) CCBitsClear(x, Index);
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_COUNT(x, Index, Count);
        }
    }

#undef ASSERT_FUNC
#define ASSERT_FUNC TestCount32
    
    CCBits(uint32_t, 193) x32;
    
    CC_BITS_INIT_SET(x32);
    
    CCBitsClear(x32, 7);
    
    CCBitsClear(x32, 144);
    
    CCBitsClear(x32, 152);
    CCBitsClear(x32, 153);
    
    CCBitsClear(x32, 160);
    CCBitsClear(x32, 161);
    CCBitsClear(x32, 162);
    
    CCBitsClear(x32, 168);
    CCBitsClear(x32, 169);
    CCBitsClear(x32, 170);
    CCBitsClear(x32, 171);
    
    CCBitsClear(x32, 176);
    CCBitsClear(x32, 177);
    CCBitsClear(x32, 178);
    CCBitsClear(x32, 179);
    CCBitsClear(x32, 180);
    
    CCBitsClear(x32, 184);
    CCBitsClear(x32, 185);
    CCBitsClear(x32, 186);
    CCBitsClear(x32, 187);
    CCBitsClear(x32, 188);
    CCBitsClear(x32, 189);
    
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_COUNT(x32, Index, Count);
        }
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        if (Index % 3 == 0) CCBitsClear(x32, Index);
        else if (Index % 5 == 0) CCBitsClear(x32, Index);
        else if (Index % 18 == 0) CCBitsClear(x32, Index);
        else if (Index % 29 == 0) CCBitsClear(x32, Index);
        else if (Index % 53 == 0) CCBitsClear(x32, Index);
        else if (Index % 120 == 0) CCBitsClear(x32, Index);
        else if (Index % 122 == 0) CCBitsClear(x32, Index);
        else if (Index % 124 == 0) CCBitsClear(x32, Index);
        else if (Index % 128 == 0) CCBitsClear(x32, Index);
        else if (Index % 133 == 0) CCBitsClear(x32, Index);
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_COUNT(x32, Index, Count);
        }
    }
}

-(void) testAny
{
#define ASSERT_ANY(bits, index, count) XCTAssertEqual(CCBitsAny(bits, index, count), !!ASSERT_FUNC(bits, index, count), @"should check if any bits in range %zu,%zu are set", (size_t)index, (size_t)count);
    
#undef ASSERT_FUNC
#define ASSERT_FUNC TestCount8
    
    CCBits(uint8_t, 193) x;
    
    CC_BITS_INIT_SET(x);
    
    CCBitsClear(x, 7);
    
    CCBitsClear(x, 144);
    
    CCBitsClear(x, 152);
    CCBitsClear(x, 153);
    
    CCBitsClear(x, 160);
    CCBitsClear(x, 161);
    CCBitsClear(x, 162);
    
    CCBitsClear(x, 168);
    CCBitsClear(x, 169);
    CCBitsClear(x, 170);
    CCBitsClear(x, 171);
    
    CCBitsClear(x, 176);
    CCBitsClear(x, 177);
    CCBitsClear(x, 178);
    CCBitsClear(x, 179);
    CCBitsClear(x, 180);
    
    CCBitsClear(x, 184);
    CCBitsClear(x, 185);
    CCBitsClear(x, 186);
    CCBitsClear(x, 187);
    CCBitsClear(x, 188);
    CCBitsClear(x, 189);
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_ANY(x, Index, Count);
        }
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        if (Index % 3 == 0) CCBitsClear(x, Index);
        else if (Index % 5 == 0) CCBitsClear(x, Index);
        else if (Index % 18 == 0) CCBitsClear(x, Index);
        else if (Index % 29 == 0) CCBitsClear(x, Index);
        else if (Index % 53 == 0) CCBitsClear(x, Index);
        else if (Index % 120 == 0) CCBitsClear(x, Index);
        else if (Index % 122 == 0) CCBitsClear(x, Index);
        else if (Index % 124 == 0) CCBitsClear(x, Index);
        else if (Index % 128 == 0) CCBitsClear(x, Index);
        else if (Index % 133 == 0) CCBitsClear(x, Index);
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_ANY(x, Index, Count);
        }
    }

#undef ASSERT_FUNC
#define ASSERT_FUNC TestCount32
    
    CCBits(uint32_t, 193) x32;
    
    CC_BITS_INIT_SET(x32);
    
    CCBitsClear(x32, 7);
    
    CCBitsClear(x32, 144);
    
    CCBitsClear(x32, 152);
    CCBitsClear(x32, 153);
    
    CCBitsClear(x32, 160);
    CCBitsClear(x32, 161);
    CCBitsClear(x32, 162);
    
    CCBitsClear(x32, 168);
    CCBitsClear(x32, 169);
    CCBitsClear(x32, 170);
    CCBitsClear(x32, 171);
    
    CCBitsClear(x32, 176);
    CCBitsClear(x32, 177);
    CCBitsClear(x32, 178);
    CCBitsClear(x32, 179);
    CCBitsClear(x32, 180);
    
    CCBitsClear(x32, 184);
    CCBitsClear(x32, 185);
    CCBitsClear(x32, 186);
    CCBitsClear(x32, 187);
    CCBitsClear(x32, 188);
    CCBitsClear(x32, 189);
    
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_ANY(x32, Index, Count);
        }
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        if (Index % 3 == 0) CCBitsClear(x32, Index);
        else if (Index % 5 == 0) CCBitsClear(x32, Index);
        else if (Index % 18 == 0) CCBitsClear(x32, Index);
        else if (Index % 29 == 0) CCBitsClear(x32, Index);
        else if (Index % 53 == 0) CCBitsClear(x32, Index);
        else if (Index % 120 == 0) CCBitsClear(x32, Index);
        else if (Index % 122 == 0) CCBitsClear(x32, Index);
        else if (Index % 124 == 0) CCBitsClear(x32, Index);
        else if (Index % 128 == 0) CCBitsClear(x32, Index);
        else if (Index % 133 == 0) CCBitsClear(x32, Index);
    }
    
    for (size_t Index = 0; Index < 192; Index++)
    {
        for (size_t Count = 1, Max = 192 - Index; Count <= Max; Count++)
        {
            ASSERT_ANY(x32, Index, Count);
        }
    }
}

@end
