/*
 *  Copyright (c) 2019, Stefan Johnson
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
#import "Enumerable.h"
#import "Collection.h"

@interface EnumerableTests : XCTestCase

@end

@implementation EnumerableTests

-(void) testSimpleEnumerable
{
    int Data[] = { 1, 2, 3, 4, 5 };
    CCEnumerable Enumerable = CCEnumerableCreate(Data, sizeof(int), 5);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Should be set to the head");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 3, @"Should get the current value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 4, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Should get the next value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetHead(&Enumerable), 1, @"Should be set to the head");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 1, @"Should get the previous value");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetHead(&Enumerable), 1, @"Should be set to the head");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetTail(&Enumerable), 5, @"Should be set to the tail");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 4, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 3, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 3, @"Should get the current value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 2, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 1, @"Should get the previous value");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetTail(&Enumerable), 5, @"Should be set to the tail");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 4, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Should get the next value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetTail(&Enumerable), 5, @"Should be set to the tail");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Should be at the end");
}

@end
