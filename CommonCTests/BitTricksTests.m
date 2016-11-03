/*
 *  Copyright (c) 2013, Stefan Johnson
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

#import "BitTricksTests.h"
#import "BitTricks.h"


#define TEST_(x, r, func) XCTAssertEqual(func(x), (r), @"Test value: (%" PRIu64 ") should be (%" PRIu64 "). Instead saying it is: (%" PRIu64 ").", x, r, func(x));
#define TEST_BOOL_(x, r, func) XCTAssertEqual(func(x), (r), @"Test value: (%" PRIu64 ") should be (%d). Instead saying it is: (%d).", x, r, func(x));
#define TEST_FLOAT_BOOL_(x, r, func) XCTAssertEqual(func(x), (r), @"Test value: (%f) should be (%d). Instead saying it is: (%d).", x, r, func(x));

@implementation BitTricksTests

-(void) testCCLowestUnsetBit
{
#define TEST_LUB(x, r) TEST_(x, r, CCBitLowestUnset)
    //0 set bits
    TEST_LUB(UINT64_C(0), UINT64_C(1));
    
    //1 set bits
    TEST_LUB(UINT64_C(1), UINT64_C(2));
    for (int Loop = 1; Loop < 64; Loop++) TEST_LUB(UINT64_C(1) << Loop, UINT64_C(1));
    
    //n set bits
    for (uint64_t Loop = 0, n = 1; Loop < 63; Loop++, n = (n << 1) | 1) TEST_LUB(n, UINT64_C(1) << (Loop + 1));
}

-(void) testCCLowestSetBit
{
#define TEST_LSB(x, r) TEST_(x, r, CCBitLowestSet)
    //0 set bits
    TEST_LSB(UINT64_C(0), UINT64_C(0));
    
    //1 set bits
    for (int Loop = 0; Loop < 64; Loop++) TEST_LSB(UINT64_C(1) << Loop, UINT64_C(1) << Loop);
    
    //n set bits
    for (uint64_t Loop = 0, n = 1; Loop < 64; Loop++, n = (n << 1) | 1) TEST_LSB(n, UINT64_C(1));
}

-(void) testCCHighestSetBit
{
#define TEST_MSB(x, r) TEST_(x, r, CCBitHighestSet)
    //0 set bits
    TEST_MSB(UINT64_C(0), UINT64_C(0));
    
    //1 set bits
    for (int Loop = 0; Loop < 64; Loop++) TEST_MSB(UINT64_C(1) << Loop, UINT64_C(1) << Loop);
    
    //n set bits
    for (uint64_t Loop = 0, n = 1; Loop < 64; Loop++, n = (n << 1) | 1) TEST_MSB(n, UINT64_C(1) << Loop);
}

-(void) testCCNextPowerOf2
{
#define TEST_NEXT_POWER_2(x, r) TEST_(x, r, CCBitNextPowerOf2)
    //0 set bits
    TEST_NEXT_POWER_2(UINT64_C(0), UINT64_C(0));
    
    //1 set bits
    for (int Loop = 0; Loop < 64; Loop++) TEST_NEXT_POWER_2(UINT64_C(1) << Loop, UINT64_C(1) << Loop);
    
    //n set bits
    for (uint64_t Loop = 1, n = 3; Loop < 63; Loop++, n = (n << 1) | 1) TEST_NEXT_POWER_2(n, UINT64_C(1) << (Loop + 1));
}

-(void) testCCMaskForValue
{
#define TEST_MASK_FOR_VALUE(x, r) TEST_(x, r, CCBitMaskForValue)
    //0 set bits
    TEST_MASK_FOR_VALUE(UINT64_C(0), UINT64_C(0));
    
    //1 set bits
    for (uint64_t Loop = 0, n = 1; Loop < 64; Loop++, n = (n << 1) | 1) TEST_MASK_FOR_VALUE(UINT64_C(1) << Loop, n);
    
    //n set bits
    for (uint64_t Loop = 0, n = 1; Loop < 64; Loop++, n = (n << 1) | 1) TEST_MASK_FOR_VALUE(n, n);
}

-(void) testCCMaskForLowerBits2
{
#define TEST_MASK_FOR_LOWER_BITS_POWER_2(x, r) TEST_(x, r, CCBitMaskForLowerPowerOf2)
    //0 set bits
    TEST_MASK_FOR_LOWER_BITS_POWER_2(UINT64_C(0), UINT64_C(0));
    
    //1 set bits
    for (uint64_t Loop = 0, n = 0; Loop < 64; Loop++, n = (n << 1) | 1) TEST_MASK_FOR_LOWER_BITS_POWER_2(UINT64_C(1) << Loop, n);
}

-(void) testCCMaskForUnsetValue
{
#define TEST_MASK_FOR_UNSET_VALUE(x, r) TEST_(x, r, CCBitMaskForUnsetValue)
    //0 set bits
    TEST_MASK_FOR_UNSET_VALUE(UINT64_C(0), UINT64_MAX);
    
    //1 set bits
    for (int Loop = 0; Loop < 63; Loop++) TEST_MASK_FOR_UNSET_VALUE(UINT64_C(1) << Loop, UINT64_MAX << (Loop + 1));
    
    //n set bits
    for (uint64_t Loop = 0, n = 1; Loop < 63; Loop++, n = (n << 1) | 1) TEST_MASK_FOR_UNSET_VALUE(n, UINT64_MAX << (Loop + 1));
    
    //64th set bit
    TEST_MASK_FOR_UNSET_VALUE(UINT64_C(1) << 63, UINT64_C(0));
}

-(void) testCCCountSetBits
{
#define TEST_SET_BIT_COUNT(x, r) XCTAssertEqual(CCBitCountSet(x), (r), @"Test value: %" PRIu64 " should contain %" PRIu64 " set bits. Instead saying it contains: %" PRIu64, x, r, CCBitCountSet(x));
    //0 set bits
    TEST_SET_BIT_COUNT(UINT64_C(0), UINT64_C(0));
    
    //1 set bits
    for (int Loop = 0; Loop < 64; Loop++) TEST_SET_BIT_COUNT(UINT64_C(1) << Loop, UINT64_C(1));
    
    //n set bits
    for (uint64_t Loop = 0, n = 1; Loop < 64; Loop++, n = (n << 1) | 1) TEST_SET_BIT_COUNT(n, Loop + 1);
}

-(void) testCCBitSet
{
    XCTAssertEqual(CCBitSet(0), 0, @"Should set 0 bits");
    XCTAssertEqual(CCBitSet(1), 1, @"Should set 1 bits");
    XCTAssertEqual(CCBitSet(2), 3, @"Should set 2 bits");
    XCTAssertEqual(CCBitSet(3), 7, @"Should set 3 bits");
    XCTAssertEqual(CCBitSet(64), UINT64_MAX, @"Should set all bits");
}

-(void) testCCBitIsPowerOf2
{
#define TEST_BIT_IS_POWER_2(x, r) TEST_BOOL_(x, r, CCBitIsPowerOf2)
    
    //0 set bits
    TEST_BIT_IS_POWER_2(UINT64_C(0), FALSE);
    
    //1 set bits
    for (int Loop = 0; Loop < 64; Loop++) TEST_BIT_IS_POWER_2(UINT64_C(1) << Loop, TRUE);
    
    //n set bits
    for (uint64_t Loop = 1, n = 3; Loop < 64; Loop++, n = (n << 1) | 1) TEST_BIT_IS_POWER_2(n, FALSE);
}

-(void) testCCBitFloat32IsPowerOf2
{
#define TEST_FLOAT_IS_POWER_2(x, r) TEST_FLOAT_BOOL_(x, r, CCBitFloat32IsPowerOf2)
    
    //0.0
    TEST_FLOAT_IS_POWER_2(0.0f, FALSE);
    
    //Powers of 2
    for (int Loop = 1; Loop < 255; Loop++) TEST_FLOAT_IS_POWER_2((*(float*)&(uint32_t){ (Loop << 23) }), TRUE);
    
    //Non powers of 2
    for (int Loop = 0; Loop < 255; Loop++) TEST_FLOAT_IS_POWER_2((*(float*)&(uint32_t){ (Loop << 23) | 1 }), FALSE);
}

-(void) testCCBitFloat64IsPowerOf2
{
#define TEST_DOUBLE_IS_POWER_2(x, r) TEST_FLOAT_BOOL_(x, r, CCBitFloat64IsPowerOf2)
    
    //0.0
    TEST_DOUBLE_IS_POWER_2(0.0, FALSE);
    
    //Powers of 2
    for (uint64_t Loop = 1; Loop < 2047; Loop++) TEST_DOUBLE_IS_POWER_2((*(double*)&(uint64_t){ (Loop << 52) }), TRUE);
    
    //Non powers of 2
    for (uint64_t Loop = 0; Loop < 2047; Loop++) TEST_DOUBLE_IS_POWER_2((*(double*)&(uint64_t){ (Loop << 52) | 1 }), FALSE);
}

@end
