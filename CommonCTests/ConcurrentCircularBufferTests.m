/*
 *  Copyright (c) 2024, Stefan Johnson
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

#define Titem int
#define Tmax 6
#include "ConcurrentCircularBuffer.h"

#define Titem int
#define Tmax 3
#include "ConcurrentCircularBuffer.h"

@interface ConcurrentCircularBufferTests : XCTestCase
@end

@implementation ConcurrentCircularBufferTests

-(void) testAddingItems
{
    CCConcurrentCircularBuffer(int, 6) BufferI6 = CC_CONCURRENT_CIRCULAR_BUFFER_INIT;
    
    CCEnumerable Enumerable;
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable), NULL, @"Enumerable should be empty");
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 1 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 2 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 3 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 4 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 5 }), @"Should add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 6 }), @"Should not add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 7 }), @"Should not add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 4, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 1 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 2 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 3 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 4 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 5 }), @"Should add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 6 }), @"Should not add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 7 }), @"Should not add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 1 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 2 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 3 }), @"Should add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 4 }), @"Should add the item");
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 5 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 6 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 7 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 8 }), @"Should add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 9 }), @"Should not add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI6, &(int){ 10 }), @"Should not add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 4, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 6, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 7, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 8, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    int Values[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI6, Values, 7), 5, @"Should add only some of the items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 4, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI6, Values, 5), 5, @"Should add all items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI6, Values, 3), 3, @"Should add all items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI6, Values + 3, 1), 1, @"Should add all items");
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI6, Values + 4, 6), 4, @"Should add only some of the items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI6, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 4, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 6, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 7, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 8, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI6, &Enumerable);
    
    
    
    CCConcurrentCircularBuffer(int, 3) BufferI3 = CC_CONCURRENT_CIRCULAR_BUFFER_INIT;
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable), NULL, @"Enumerable should be empty");
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 1 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 2 }), @"Should add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 3 }), @"Should not add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 4 }), @"Should not add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 1 }), @"Should add the item");
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 2 }), @"Should add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 3 }), @"Should not add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 4 }), @"Should not add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 1 }), @"Should add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 2 }), @"Should add the item");
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
    
    XCTAssertTrue(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 3 }), @"Should add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 4 }), @"Should not add the item");
    XCTAssertFalse(CCConcurrentCircularBufferAddItem(&BufferI3, &(int){ 5 }), @"Should not add the item");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
        
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI3, Values, 4), 2, @"Should add only some of the items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI3, Values, 2), 2, @"Should add all items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI3, Values, 1), 1, @"Should add all items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI3, Values + 1, 1), 1, @"Should add all items");
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
    
    XCTAssertEqual(CCConcurrentCircularBufferAddItems(&BufferI3, Values + 2, 4), 1, @"Should add only some of the items");
    
    CCConcurrentCircularBufferGetEnumerable(&BufferI3, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 2, @"Enumerable should contain the correct value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Enumerable should contain the correct value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Enumerable should not contain anymore values");
    
    CCConcurrentCircularBufferRelease(&BufferI3, &Enumerable);
}

@end
