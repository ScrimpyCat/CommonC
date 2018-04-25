/*
 *  Copyright (c) 2018, Stefan Johnson
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
#import "ConcurrentIndexMap.h"
#import "EpochGarbageCollector.h"
#import "LazyGarbageCollector.h"
#import <stdatomic.h>
#import <pthread.h>

@interface ConcurrentIndexMapTests : XCTestCase

@property (readonly) const CCConcurrentGarbageCollectorInterface *gc;

@end

@implementation ConcurrentIndexMapTests

-(const CCConcurrentGarbageCollectorInterface *) gc
{
    return CCEpochGarbageCollector;
}

-(void) testCreation
{
    CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 1, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 0, @"Should be empty");
    XCTAssertEqual(CCConcurrentIndexMapGetElementSize(IndexMap), sizeof(int), @"Should be the size specified on creation");
    
    CCConcurrentIndexMapDestroy(IndexMap);
}

-(void) testAppending
{
    CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 1, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
    
    int Value;
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 1, @"Should be the first element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 2, @"Should be the second element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 3, @"Should be the third element");
    
    XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 4 });
    
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 4, @"Should be the fourth element");
    
    CCConcurrentIndexMapDestroy(IndexMap);
    
    
    
    IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 2, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 1, @"Should be the first element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 2, @"Should be the second element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 3, @"Should be the third element");
    
    XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 4 });
    
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 4, @"Should be the fourth element");
    
    CCConcurrentIndexMapDestroy(IndexMap);
    
    
    
    IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 4, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 1, @"Should be the first element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 2, @"Should be the second element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 3, @"Should be the third element");
    
    XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 4 });
    
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 4, @"Should be the fourth element");
    
    CCConcurrentIndexMapDestroy(IndexMap);
}

-(void) testReplacing
{
    CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 1, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
    
    int Value;
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 0, &(int){ 10 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 1, "Should retrieve the previous element");
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 1, &(int){ 20 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 2, "Should retrieve the previous element");
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 2, &(int){ 30 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 3, "Should retrieve the previous element");
    
    XCTAssertFalse(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 3, &(int){ 40 }, &Value), "Should not replace an element that does not exist");
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 10, @"Should be the first element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 20, @"Should be the second element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 30, @"Should be the third element");
    
    XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
    
    CCConcurrentIndexMapDestroy(IndexMap);
    
    
    
    IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 2, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
    
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 0, &(int){ 10 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 1, "Should retrieve the previous element");
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 1, &(int){ 20 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 2, "Should retrieve the previous element");
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 2, &(int){ 30 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 3, "Should retrieve the previous element");
    
    XCTAssertFalse(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 3, &(int){ 40 }, &Value), "Should not replace an element that does not exist");
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 10, @"Should be the first element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 20, @"Should be the second element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 30, @"Should be the third element");
    
    XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
    
    CCConcurrentIndexMapDestroy(IndexMap);
    
    
    
    IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 4, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
    CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
    
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 0, &(int){ 10 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 1, "Should retrieve the previous element");
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 1, &(int){ 20 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 2, "Should retrieve the previous element");
    XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 2, &(int){ 30 }, &Value), "Should replace the element");
    XCTAssertEqual(Value, 3, "Should retrieve the previous element");
    
    XCTAssertFalse(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 3, &(int){ 40 }, &Value), "Should not replace an element that does not exist");
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 10, @"Should be the first element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 20, @"Should be the second element");
    XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
    XCTAssertEqual(Value, 30, @"Should be the third element");
    
    XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
    
    CCConcurrentIndexMapDestroy(IndexMap);
}

@end

@interface ConcurrentIndexMapTestsLazyGC : ConcurrentIndexMapTests
@end

@implementation ConcurrentIndexMapTestsLazyGC

-(const CCConcurrentGarbageCollectorInterface *) gc
{
    return CCLazyGarbageCollector;
}

@end
