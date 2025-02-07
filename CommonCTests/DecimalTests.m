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
#import "Decimal.h"

@interface DecimalTests : XCTestCase
@end

@implementation DecimalTests

-(void) testMultiplyingInteger
{
    uint64_t Value = 0;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), 0, @"should be the correct result");
    
    
    Value = 1;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), Value * 1000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), Value * 2000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), Value * 5000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), Value * 2500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), Value * 25000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), Value * 1250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), Value * 12500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), Value * 125000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = 2;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), Value * 1000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), Value * 2000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), Value * 5000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), Value * 2500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), Value * 25000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), Value * 1250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), Value * 12500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), Value * 125000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = 10;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), Value * 1000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), Value * 2000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), Value * 5000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), Value * 2500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), Value * 25000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), Value * 1250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), Value * 12500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), Value * 125000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = 2147483648;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), Value * 1000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), Value * 2000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), Value * 5000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), Value * 2500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), Value * 25000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), Value * 1250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), Value * 12500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), Value * 125000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = 0xffffffff;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), Value * 1000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), Value * 2000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), Value * 5000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), Value * 2500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), Value * 25000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), Value * 1250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), Value * 12500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), Value * 125000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = UINT64_C(4294967296);
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), Value * 1000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), Value * 2000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), Value * 5000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), Value * 2500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), Value * 25000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), Value * 1250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), Value * 12500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), Value * 125000, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = UINT64_C(36063981391316016);
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");


    Value = UINT64_C(36063981391316019);
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), Value * 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), Value * 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), Value * 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), Value * 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), Value * 200, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), Value * 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), Value * 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), Value * 500, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), Value * 25, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), Value * 250, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), Value * 125, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = UINT64_C(0xffffffff00000000) + (2147483648 >> 1);
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
    
    
    Value = UINT64_MAX;
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 0 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = 3 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -1 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -2 }), 0, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 0, .exp = -3 }), 0, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 0 }), Value * 1, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -1 }), Value / 10, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -2 }), Value / 100, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 1, .exp = -3 }), Value / 1000, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -1 }), Value / 5, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -2 }), Value / 50, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 2, .exp = -3 }), Value / 500, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -1 }), Value / 2, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -2 }), Value / 20, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 5, .exp = -3 }), Value / 200, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -1 }), (Value * 2) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -2 }), Value / 4, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 25, .exp = -3 }), Value / 40, @"should be the correct result");
    
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 0 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 1 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 2 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = 3 }), UINT64_MAX, @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -1 }), (Value * 12) + (Value / 2), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -2 }), Value + (Value / 4), @"should be the correct result");
    XCTAssertEqual(CCDecimalMultiplyU64(Value, (CCDecimal){ .coef = 125, .exp = -3 }), Value / 8, @"should be the correct result");
}

@end
