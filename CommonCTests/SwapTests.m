/*
 *  Copyright (c) 2026, Stefan Johnson
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
#import "Order.h"
#import "Swap.h"

@interface SwapTests : XCTestCase

@end

@implementation SwapTests

-(void) testSwap
{
    uint8_t Data[128];
    
    for (size_t Count = 0; Count < 128; Count++)
    {
        for (size_t Loop = 0; Loop < 128; Loop++) Data[Loop] = Loop;
        CCSwap(Data, Count);
        for (size_t Loop = 0; Loop < Count; Loop++) XCTAssertEqual(Data[Loop], Count - Loop - 1, @"Should swap");
        for (size_t Loop = Count; Loop < 128; Loop++) XCTAssertEqual(Data[Loop], Loop, @"Should not swap");
    }
    
    XCTAssertEqual(CC_SWAP(0x0102030405060708ULL, 8), 0x0807060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x01020304050607ULL, 7), 0x07060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x010203040506ULL, 6), 0x060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x0102030405ULL, 5), 0x0504030201ULL, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x01020304, 4), 0x04030201, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x010203, 3), 0x030201, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x0102, 2), 0x0201, @"Should swap");
    XCTAssertEqual(CC_SWAP(0x01, 1), 0x01, @"Should swap");
}

-(void) testOrder
{
#if CC_HARDWARE_ENDIAN_LITTLE
    XCTAssertEqual(CC_LITTLE(0x0102030405060708ULL, 8), 0x0102030405060708ULL, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x01020304050607ULL, 7), 0x01020304050607ULL, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x010203040506ULL, 6), 0x010203040506ULL, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x0102030405ULL, 5), 0x0102030405ULL, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x01020304, 4), 0x01020304, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x010203, 3), 0x010203, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x0102, 2), 0x0102, @"Should not swap");
    XCTAssertEqual(CC_LITTLE(0x01, 1), 0x01, @"Should not swap");
    
    XCTAssertEqual(CC_LITTLE_64(0x0102030405060708ULL), 0x0102030405060708ULL, @"Should not swap");
    XCTAssertEqual(CC_LITTLE_32(0x01020304), 0x01020304, @"Should not swap");
    XCTAssertEqual(CC_LITTLE_16(0x0102), 0x0102, @"Should not swap");
    XCTAssertEqual(CC_LITTLE_8(0x01), 0x01, @"Should not swap");
    
    XCTAssertEqual(CC_BIG(0x0102030405060708ULL, 8), 0x0807060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_BIG(0x01020304050607ULL, 7), 0x07060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_BIG(0x010203040506ULL, 6), 0x060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_BIG(0x0102030405ULL, 5), 0x0504030201ULL, @"Should swap");
    XCTAssertEqual(CC_BIG(0x01020304, 4), 0x04030201, @"Should swap");
    XCTAssertEqual(CC_BIG(0x010203, 3), 0x030201, @"Should swap");
    XCTAssertEqual(CC_BIG(0x0102, 2), 0x0201, @"Should swap");
    XCTAssertEqual(CC_BIG(0x01, 1), 0x01, @"Should swap");
    
    XCTAssertEqual(CC_BIG_64(0x0102030405060708ULL), 0x0807060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_BIG_32(0x01020304), 0x04030201, @"Should swap");
    XCTAssertEqual(CC_BIG_16(0x0102), 0x0201, @"Should swap");
    XCTAssertEqual(CC_BIG_8(0x01), 0x01, @"Should swap");
#elif CC_HARDWARE_ENDIAN_BIG
    XCTAssertEqual(CC_BIG(0x0102030405060708ULL, 8), 0x0102030405060708ULL, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x01020304050607ULL, 7), 0x01020304050607ULL, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x010203040506ULL, 6), 0x010203040506ULL, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x0102030405ULL, 5), 0x0102030405ULL, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x01020304, 4), 0x01020304, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x010203, 3), 0x010203, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x0102, 2), 0x0102, @"Should not swap");
    XCTAssertEqual(CC_BIG(0x01, 1), 0x01, @"Should not swap");
    
    XCTAssertEqual(CC_BIG_64(0x0102030405060708ULL), 0x0102030405060708ULL, @"Should not swap");
    XCTAssertEqual(CC_BIG_32(0x01020304), 0x01020304, @"Should not swap");
    XCTAssertEqual(CC_BIG_16(0x0102), 0x0102, @"Should not swap");
    XCTAssertEqual(CC_BIG_8(0x01), 0x01, @"Should not swap");
    
    XCTAssertEqual(CC_LITTLE(0x0102030405060708ULL, 8), 0x0807060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x01020304050607ULL, 7), 0x07060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x010203040506ULL, 6), 0x060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x0102030405ULL, 5), 0x0504030201ULL, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x01020304, 4), 0x04030201, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x010203, 3), 0x030201, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x0102, 2), 0x0201, @"Should swap");
    XCTAssertEqual(CC_LITTLE(0x01, 1), 0x01, @"Should swap");
    
    XCTAssertEqual(CC_LITTLE_64(0x0102030405060708ULL), 0x0807060504030201ULL, @"Should swap");
    XCTAssertEqual(CC_LITTLE_32(0x01020304), 0x04030201, @"Should swap");
    XCTAssertEqual(CC_LITTLE_16(0x0102), 0x0201, @"Should swap");
    XCTAssertEqual(CC_LITTLE_8(0x01), 0x01, @"Should swap");
#endif
}

-(void) testMappable
{
    uint64_t Values[22] = {
#if CC_HARDWARE_ENDIAN_LITTLE
        CC_MAP(CC_LITTLE_64, 0x0102030405060708ULL, 0x090a0b0c0d0e0f10ULL),
        CC_MAP(CC_LITTLE_32, 0x01020304, 0x05060708, 0x090a0b0c),
        CC_MAP(CC_LITTLE_16, 0x0102, 0x0304, 0x0506),
        CC_MAP(CC_LITTLE_8, 0x01, 0x02, 0x03),
        CC_MAP(CC_BIG_64, 0x0102030405060708ULL, 0x090a0b0c0d0e0f10ULL),
        CC_MAP(CC_BIG_32, 0x01020304, 0x05060708, 0x090a0b0c),
        CC_MAP(CC_BIG_16, 0x0102, 0x0304, 0x0506),
        CC_MAP(CC_BIG_8, 0x01, 0x02, 0x03)
#elif CC_HARDWARE_ENDIAN_BIG
        CC_MAP(CC_BIG_64, 0x0102030405060708ULL, 0x090a0b0c0d0e0f10ULL),
        CC_MAP(CC_BIG_32, 0x01020304, 0x05060708, 0x090a0b0c),
        CC_MAP(CC_BIG_16, 0x0102, 0x0304, 0x0506),
        CC_MAP(CC_BIG_8, 0x01, 0x02, 0x03),
        CC_MAP(CC_LITTLE_64, 0x0102030405060708ULL, 0x090a0b0c0d0e0f10ULL),
        CC_MAP(CC_LITTLE_32, 0x01020304, 0x05060708, 0x090a0b0c),
        CC_MAP(CC_LITTLE_16, 0x0102, 0x0304, 0x0506),
        CC_MAP(CC_LITTLE_8, 0x01, 0x02, 0x03)
#endif
    };
    
    XCTAssertEqual(Values[0], 0x0102030405060708ULL, @"Should not swap");
    XCTAssertEqual(Values[1], 0x090a0b0c0d0e0f10ULL, @"Should not swap");
    XCTAssertEqual(Values[2], 0x01020304, @"Should not swap");
    XCTAssertEqual(Values[3], 0x05060708, @"Should not swap");
    XCTAssertEqual(Values[4], 0x090a0b0c, @"Should not swap");
    XCTAssertEqual(Values[5], 0x0102, @"Should not swap");
    XCTAssertEqual(Values[6], 0x0304, @"Should not swap");
    XCTAssertEqual(Values[7], 0x0506, @"Should not swap");
    XCTAssertEqual(Values[8], 0x01, @"Should not swap");
    XCTAssertEqual(Values[9], 0x02, @"Should not swap");
    XCTAssertEqual(Values[10], 0x03, @"Should not swap");
    
    XCTAssertEqual(Values[11], 0x0807060504030201ULL, @"Should swap");
    XCTAssertEqual(Values[12], 0x100f0e0d0c0b0a09ULL, @"Should swap");
    XCTAssertEqual(Values[13], 0x04030201, @"Should swap");
    XCTAssertEqual(Values[14], 0x08070605, @"Should swap");
    XCTAssertEqual(Values[15], 0x0c0b0a09, @"Should swap");
    XCTAssertEqual(Values[16], 0x0201, @"Should swap");
    XCTAssertEqual(Values[17], 0x0403, @"Should swap");
    XCTAssertEqual(Values[18], 0x0605, @"Should swap");
    XCTAssertEqual(Values[19], 0x01, @"Should swap");
    XCTAssertEqual(Values[20], 0x02, @"Should swap");
    XCTAssertEqual(Values[21], 0x03, @"Should swap");
}

@end
