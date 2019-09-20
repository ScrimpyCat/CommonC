/*
 *  Copyright (c) 2015, Stefan Johnson
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

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import "Array.h"

@interface ArrayTests : XCTestCase

@end

@implementation ArrayTests

-(void) setUp
{
    [super setUp];
}

-(void) tearDown
{
    [super tearDown];
}

-(void) testCreation
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(int), 1);

    XCTAssertEqual(CCArrayGetCount(Array), 0, @"Should be empty");
    XCTAssertEqual(CCArrayGetElementSize(Array), sizeof(int), @"Should be the size specified on creation");
    
    CCArrayDestroy(Array);
}

-(void) testAppending
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(int), 1);
    
    CCArrayAppendElement(Array, &(int){ 1 });
    CCArrayAppendElement(Array, &(int){ 2 });
    CCArrayAppendElement(Array, &(int){ 3 });
    
    XCTAssertEqual(CCArrayGetCount(Array), 3, @"Should contain 3 elements");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 0), 1, @"Should be the first element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 1), 2, @"Should be the second element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 2), 3, @"Should be the third element");
    
    CCArrayDestroy(Array);
    
    
    for (size_t Loop = 0; Loop < 10; Loop++)
    {
        for (size_t Loop2 = 0; Loop2 < 10; Loop2++)
        {
            for (size_t ChunkSize = 1; ChunkSize < 20; ChunkSize++)
            {
                Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(int), ChunkSize);
                
                if (Loop) CCArrayAppendElements(Array, (int[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, Loop);
                if (Loop2) CCArrayAppendElements(Array, (int[]){ 10, 20, 30, 40, 50, 60, 70, 80, 90 }, Loop2);
                
                XCTAssertEqual(CCArrayGetCount(Array), Loop + Loop2, @"Should contain the correct number of elements");
                for (size_t Loop3 = 0; Loop3 < Loop; Loop3++)
                {
                    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, Loop3), Loop3 + 1, @"Should contain the correct element from the first source");
                }
                
                for (size_t Loop3 = 0; Loop3 < Loop2; Loop3++)
                {
                    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, Loop3 + Loop), (Loop3 + 1) * 10, @"Should contain the correct element from the second source");
                }
                
                CCArrayDestroy(Array);
            }
        }
    }
}

-(void) testReplacing
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(int), 3);
    
    CCArrayAppendElement(Array, &(int){ 1 });
    CCArrayAppendElement(Array, &(int){ 2 });
    CCArrayAppendElement(Array, &(int){ 3 });
    
    CCArrayReplaceElementAtIndex(Array, 1, &(int){ 123 });
    
    XCTAssertEqual(CCArrayGetCount(Array), 3, @"Should contain 3 elements");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 0), 1, @"Should be the first element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 1), 123, @"Should be the replaced element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 2), 3, @"Should be the third element");
    
    CCArrayDestroy(Array);
}

-(void) testInserting
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(int), 3);
    
    CCArrayAppendElement(Array, &(int){ 1 });
    CCArrayAppendElement(Array, &(int){ 2 });
    CCArrayAppendElement(Array, &(int){ 3 });
    
    CCArrayInsertElementAtIndex(Array, 1, &(int){ 123 });
    
    XCTAssertEqual(CCArrayGetCount(Array), 4, @"Should contain 4 elements");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 0), 1, @"Should be the first element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 1), 123, @"Should be the inserted element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 2), 2, @"Should now be the second element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 3), 3, @"Should now be the third element");
    
    CCArrayDestroy(Array);
}

-(void) testRemoval
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(int), 3);
    
    CCArrayAppendElement(Array, &(int){ 1 });
    CCArrayAppendElement(Array, &(int){ 2 });
    CCArrayAppendElement(Array, &(int){ 3 });
    
    CCArrayRemoveElementAtIndex(Array, 1);
    
    XCTAssertEqual(CCArrayGetCount(Array), 2, @"Should contain 2 elements");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 0), 1, @"Should be the first element");
    XCTAssertEqual(*(int*)CCArrayGetElementAtIndex(Array, 1), 3, @"Should now be the third element");
    
    CCArrayDestroy(Array);
}

@end
