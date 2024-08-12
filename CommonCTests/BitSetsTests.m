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

-(void) testMask
{
    CCBits(uint8_t, 193) a;
    CCBits(uint8_t, 193) b;
    
    CC_BITS_INIT_SET(a);
    CC_BITS_INIT_SET(b);
    
    size_t Indexes[193];
    size_t Count = CCBitsMask(a, b, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 193, @"should get the correct number of indexes");
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        XCTAssertEqual(Indexes[Loop], Loop, @"should get the correct indexes");
    }
    
    CC_BITS_INIT_CLEAR(a);
    
    Count = CCBitsMask(a, b, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 0, @"should get the correct number of indexes");
    
    CCBitsSet(a, 0);
    
    Count = CCBitsMask(a, b, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 1, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    
    
    CCBitsSet(a, 2);
    
    Count = CCBitsMask(a, b, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    
    
    CCBitsSet(a, 192);
    
    Count = CCBitsMask(a, b, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 192, @"should get the correct indexes");
    
    
    CCBitsSet(a, 64);
    
    Count = CCBitsMask(a, b, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 4, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 1, 192, Indexes);
    
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 2, 191, Indexes);
    
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 2, 190, Indexes);
    
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    
    
    CCBitsSet(a, 4);
    CCBitsSet(a, 6);
    CCBitsSet(a, 8);
    CCBitsSet(a, 9);
    CCBitsSet(a, 10);
    
    CCBitsSet(a, 191);
    CCBitsSet(a, 190);
    CCBitsSet(a, 189);
    CCBitsSet(a, 188);
    CCBitsSet(a, 187);
    CCBitsSet(a, 186);
    CCBitsSet(a, 185);
    
    Count = CCBitsMask(a, b, 2, 190, Indexes);
    
    XCTAssertEqual(Count, 14, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 8, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 9, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 10, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[4], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[5], 4, @"should get the correct indexes");
    XCTAssertEqual(Indexes[6], 6, @"should get the correct indexes");
    XCTAssertEqual(Indexes[7], 185, @"should get the correct indexes");
    XCTAssertEqual(Indexes[8], 186, @"should get the correct indexes");
    XCTAssertEqual(Indexes[9], 187, @"should get the correct indexes");
    XCTAssertEqual(Indexes[10], 188, @"should get the correct indexes");
    XCTAssertEqual(Indexes[11], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[12], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[13], 191, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 2, 4, Indexes);
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 4, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 0, 4, Indexes);
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 183, 10, Indexes);
    XCTAssertEqual(Count, 8, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 185, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 186, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 187, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 188, @"should get the correct indexes");
    XCTAssertEqual(Indexes[4], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[5], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[6], 191, @"should get the correct indexes");
    XCTAssertEqual(Indexes[7], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 183, 5, Indexes);
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 185, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 186, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 187, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a, b, 188, 6, Indexes);
    XCTAssertEqual(Count, 5, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 188, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 191, @"should get the correct indexes");
    XCTAssertEqual(Indexes[4], 192, @"should get the correct indexes");
    
    
    CC_BITS_INIT_CLEAR(b);
    
    CCBitsSet(b, 8);
    CCBitsSet(b, 9);
    CCBitsSet(b, 10);
    CCBitsSet(b, 11);
    CCBitsSet(b, 191);
    CCBitsSet(b, 190);
    CCBitsSet(b, 189);
    
    Count = CCBitsMask(a, b, 2, 190, Indexes);
    
    XCTAssertEqual(Count, 6, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 8, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 9, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 10, @"should get the correct indexes");
    XCTAssertEqual(Indexes[11], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[12], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[13], 191, @"should get the correct indexes");
    
    
    
    CCBits(uint32_t, 193) a32;
    CCBits(uint32_t, 193) b32;
    
    CC_BITS_INIT_SET(a32);
    CC_BITS_INIT_SET(b32);
    
    Count = CCBitsMask(a32, b32, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 193, @"should get the correct number of indexes");
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        XCTAssertEqual(Indexes[Loop], Loop, @"should get the correct indexes");
    }
    
    CC_BITS_INIT_CLEAR(a32);
    
    Count = CCBitsMask(a32, b32, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 0, @"should get the correct number of indexes");
    
    CCBitsSet(a32, 0);
    
    Count = CCBitsMask(a32, b32, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 1, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    
    
    CCBitsSet(a32, 2);
    
    Count = CCBitsMask(a32, b32, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    
    
    CCBitsSet(a32, 192);
    
    Count = CCBitsMask(a32, b32, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 192, @"should get the correct indexes");
    
    
    CCBitsSet(a32, 64);
    
    Count = CCBitsMask(a32, b32, 0, 193, Indexes);
    
    XCTAssertEqual(Count, 4, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 1, 192, Indexes);
    
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 2, 191, Indexes);
    
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 2, 190, Indexes);
    
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    
    
    CCBitsSet(a32, 4);
    CCBitsSet(a32, 6);
    CCBitsSet(a32, 8);
    CCBitsSet(a32, 9);
    CCBitsSet(a32, 10);
    
    CCBitsSet(a32, 191);
    CCBitsSet(a32, 190);
    CCBitsSet(a32, 189);
    CCBitsSet(a32, 188);
    CCBitsSet(a32, 187);
    CCBitsSet(a32, 186);
    CCBitsSet(a32, 185);
    
    Count = CCBitsMask(a32, b32, 2, 190, Indexes);
    
    XCTAssertEqual(Count, 14, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 8, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 9, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 10, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 64, @"should get the correct indexes");
    XCTAssertEqual(Indexes[4], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[5], 4, @"should get the correct indexes");
    XCTAssertEqual(Indexes[6], 6, @"should get the correct indexes");
    XCTAssertEqual(Indexes[7], 185, @"should get the correct indexes");
    XCTAssertEqual(Indexes[8], 186, @"should get the correct indexes");
    XCTAssertEqual(Indexes[9], 187, @"should get the correct indexes");
    XCTAssertEqual(Indexes[10], 188, @"should get the correct indexes");
    XCTAssertEqual(Indexes[11], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[12], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[13], 191, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 2, 4, Indexes);
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 2, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 4, @"should get the correct indexes");
    
    Count = CCBitsMask(a32, b32, 0, 4, Indexes);
    XCTAssertEqual(Count, 2, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 0, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 2, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 183, 10, Indexes);
    XCTAssertEqual(Count, 8, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 185, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 186, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 187, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 188, @"should get the correct indexes");
    XCTAssertEqual(Indexes[4], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[5], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[6], 191, @"should get the correct indexes");
    XCTAssertEqual(Indexes[7], 192, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 183, 5, Indexes);
    XCTAssertEqual(Count, 3, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 185, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 186, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 187, @"should get the correct indexes");
    
    
    Count = CCBitsMask(a32, b32, 188, 6, Indexes);
    XCTAssertEqual(Count, 5, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 188, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[3], 191, @"should get the correct indexes");
    XCTAssertEqual(Indexes[4], 192, @"should get the correct indexes");
    
    
    CC_BITS_INIT_CLEAR(b32);
    
    CCBitsSet(b32, 8);
    CCBitsSet(b32, 9);
    CCBitsSet(b32, 10);
    CCBitsSet(b32, 11);
    CCBitsSet(b32, 191);
    CCBitsSet(b32, 190);
    CCBitsSet(b32, 189);
    
    Count = CCBitsMask(a32, b32, 2, 190, Indexes);
    
    XCTAssertEqual(Count, 6, @"should get the correct number of indexes");
    XCTAssertEqual(Indexes[0], 8, @"should get the correct indexes");
    XCTAssertEqual(Indexes[1], 9, @"should get the correct indexes");
    XCTAssertEqual(Indexes[2], 10, @"should get the correct indexes");
    XCTAssertEqual(Indexes[11], 189, @"should get the correct indexes");
    XCTAssertEqual(Indexes[12], 190, @"should get the correct indexes");
    XCTAssertEqual(Indexes[13], 191, @"should get the correct indexes");
}

@end
