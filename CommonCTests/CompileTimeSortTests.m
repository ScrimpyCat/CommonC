/*
 *  Copyright (c) 2022, Stefan Johnson
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

@interface CompileTimeSortTests : XCTestCase

@end

@implementation CompileTimeSortTests

uint64_t x[3] = { CC_UNIQUE_SORT(99, 18, 64) };
uint64_t y[2] = { CC_UNIQUE_SORT(2, 0) };
uint64_t u[3] = { CC_UNIQUE_SORT(99, 64, 64) };

- (void)testExample
{
    XCTAssertEqual(x[0], 18, @"Should sort");
    XCTAssertEqual(x[1], 64, @"Should sort");
    XCTAssertEqual(x[2], 99, @"Should sort");
    
    XCTAssertEqual(y[0], 0, @"Should sort");
    XCTAssertEqual(y[1], 2, @"Should sort");
    
    XCTAssertEqual(u[0], 64, @"Should remove duplicates");
    XCTAssertEqual(u[1], 99, @"Should remove duplicates");
    XCTAssertEqual(u[2], 0, @"Should remove duplicates");
}

@end
