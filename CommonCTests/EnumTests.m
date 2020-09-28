/*
 *  Copyright (c) 2020, Stefan Johnson
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

#define CC_QUICK_COMPILE
#import <XCTest/XCTest.h>
#import "Extensions.h"
#import "Hacks.h"

@interface EnumTests : XCTestCase
@end

CC_ENUM(uint8_t){ EnumTests_testSize8 };
CC_ENUM(uint16_t){ EnumTests_testSize16 };
CC_ENUM(uint32_t){ EnumTests_testSize32 };
CC_ENUM(uint64_t){ EnumTests_testSize64 };

CC_ENUM(EnumTestsType8, uint8_t){ EnumTestsType8_testSize };
CC_ENUM(EnumTestsType16, uint16_t){ EnumTestsType16_testSize };
CC_ENUM(EnumTestsType32, uint32_t){ EnumTestsType32_testSize };
CC_ENUM(EnumTestsType64, uint64_t){ EnumTestsType64_testSize };

CC_FLAG_ENUM(uint8_t){ EnumTests_testSize8_flag };
CC_FLAG_ENUM(uint16_t){ EnumTests_testSize16_flag };
CC_FLAG_ENUM(uint32_t){ EnumTests_testSize32_flag };
CC_FLAG_ENUM(uint64_t){ EnumTests_testSize64_flag };

CC_FLAG_ENUM(EnumTestsType8_flag, uint8_t){ EnumTestsType8_testSize_flag };
CC_FLAG_ENUM(EnumTestsType16_flag, uint16_t){ EnumTestsType16_testSize_flag };
CC_FLAG_ENUM(EnumTestsType32_flag, uint32_t){ EnumTestsType32_testSize_flag };
CC_FLAG_ENUM(EnumTestsType64_flag, uint64_t){ EnumTestsType64_testSize_flag };

CC_EXTENSIBLE_ENUM(uint8_t){ EnumTests_testSize8_ext };
CC_EXTENSIBLE_ENUM(uint16_t){ EnumTests_testSize16_ext };
CC_EXTENSIBLE_ENUM(uint32_t){ EnumTests_testSize32_ext };
CC_EXTENSIBLE_ENUM(uint64_t){ EnumTests_testSize64_ext };

CC_EXTENSIBLE_ENUM(EnumTestsType8_ext, uint8_t){ EnumTestsType8_testSize_ext };
CC_EXTENSIBLE_ENUM(EnumTestsType16_ext, uint16_t){ EnumTestsType16_testSize_ext };
CC_EXTENSIBLE_ENUM(EnumTestsType32_ext, uint32_t){ EnumTestsType32_testSize_ext };
CC_EXTENSIBLE_ENUM(EnumTestsType64_ext, uint64_t){ EnumTestsType64_testSize_ext };

CC_EXTENSIBLE_FLAG_ENUM(uint8_t){ EnumTests_testSize8_flag_ext };
CC_EXTENSIBLE_FLAG_ENUM(uint16_t){ EnumTests_testSize16_flag_ext };
CC_EXTENSIBLE_FLAG_ENUM(uint32_t){ EnumTests_testSize32_flag_ext };
CC_EXTENSIBLE_FLAG_ENUM(uint64_t){ EnumTests_testSize64_flag_ext };

CC_EXTENSIBLE_FLAG_ENUM(EnumTestsType8_flag_ext, uint8_t){ EnumTestsType8_testSize_flag_ext };
CC_EXTENSIBLE_FLAG_ENUM(EnumTestsType16_flag_ext, uint16_t){ EnumTestsType16_testSize_flag_ext };
CC_EXTENSIBLE_FLAG_ENUM(EnumTestsType32_flag_ext, uint32_t){ EnumTestsType32_testSize_flag_ext };
CC_EXTENSIBLE_FLAG_ENUM(EnumTestsType64_flag_ext, uint64_t){ EnumTestsType64_testSize_flag_ext };

CC_FLAG_ENUM(uint32_t) {
    CC_RESERVED_BIT(EnumTestsBit, 7),
    CC_RESERVED_BIT(EnumTestsBit, 9),
    CC_RESERVED_BITS(EnumTestsBit, 0, 7),
    CC_RESERVED_BITS(EnumTestsBit, 8, 1),
    CC_RESERVED_BITS(EnumTestsBit, 10, 7),
    CC_RESERVED_BITS(EnumTestsBit, 28, 2),
};


@implementation EnumTests

-(void) testBitReservation
{
    XCTAssertEqual(EnumTestsBitReserved0, (1 << 0), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved1, (1 << 1), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved2, (1 << 2), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved3, (1 << 3), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved4, (1 << 4), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved5, (1 << 5), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved6, (1 << 6), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved7, (1 << 7), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved8, (1 << 8), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved9, (1 << 9), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved10, (1 << 10), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved11, (1 << 11), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved12, (1 << 12), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved13, (1 << 13), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved14, (1 << 14), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved15, (1 << 15), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved16, (1 << 16), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved28, (1 << 28), @"should have correct value");
    XCTAssertEqual(EnumTestsBitReserved29, (1 << 29), @"should have correct value");
}

-(void) testSize
{
    XCTAssertEqual(sizeof(EnumTests_testSize8), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize16), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize32), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize64), 8, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTestsType8), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64), 8, @"should have correct size");
    
    XCTAssertEqual(sizeof(EnumTestsType8_testSize), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_testSize), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_testSize), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_testSize), 8, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTests_testSize8_flag), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize16_flag), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize32_flag), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize64_flag), 8, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTestsType8_flag), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_flag), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_flag), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_flag), 8, @"should have correct size");
    
    XCTAssertEqual(sizeof(EnumTestsType8_testSize_flag), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_testSize_flag), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_testSize_flag), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_testSize_flag), 8, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTests_testSize8_ext), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize16_ext), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize32_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize64_ext), 8, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTestsType8_ext), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_ext), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_ext), 8, @"should have correct size");
    
    XCTAssertEqual(sizeof(EnumTestsType8_testSize_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_testSize_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_testSize_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_testSize_ext), 4, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTests_testSize8_flag_ext), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize16_flag_ext), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize32_flag_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTests_testSize64_flag_ext), 8, @"should have correct size");
    
    
    XCTAssertEqual(sizeof(EnumTestsType8_flag_ext), 1, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_flag_ext), 2, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_flag_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_flag_ext), 8, @"should have correct size");
    
    XCTAssertEqual(sizeof(EnumTestsType8_testSize_flag_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType16_testSize_flag_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType32_testSize_flag_ext), 4, @"should have correct size");
    XCTAssertEqual(sizeof(EnumTestsType64_testSize_flag_ext), 4, @"should have correct size");
}

@end
