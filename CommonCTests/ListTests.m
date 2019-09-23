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

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import "List.h"

@interface ListTests : XCTestCase

@end

@implementation ListTests

-(void) setUp
{
    [super setUp];
}

-(void) tearDown
{
    [super tearDown];
}

-(void) testPageSize
{
    CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 1, 1);
    
    XCTAssertEqual(CCListGetPageSize(List), 1, @"Should be the size specified on creation");
    
    CCListDestroy(List);
    
    
    List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 2, 10);
    
    XCTAssertEqual(CCListGetPageSize(List), 10, @"Should be the size specified on creation");
    
    CCListDestroy(List);
    
    
    List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 3, 10);
    
    XCTAssertEqual(CCListGetPageSize(List), 12, @"Should round up the page size");
    
    CCListDestroy(List);
    
    
    List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 30, 10);
    
    XCTAssertEqual(CCListGetPageSize(List), 30, @"Should round up the page size");
    
    CCListDestroy(List);
}

-(void) testCreation
{
    CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 1, 1);
    
    XCTAssertEqual(CCListGetCount(List), 0, @"Should be empty");
    XCTAssertEqual(CCListGetElementSize(List), sizeof(int), @"Should be the size specified on creation");
    
    CCListDestroy(List);
}

-(void) testAppending
{
    for (size_t PageSize = 1; PageSize <= 3; PageSize++)
    {
        CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 1, PageSize);
        
        CCListAppendElement(List, &(int){ 1 });
        CCListAppendElement(List, &(int){ 2 });
        CCListAppendElement(List, &(int){ 3 });
        
        XCTAssertEqual(CCListGetCount(List), 3, @"Should contain 3 elements");
        XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 0), 1, @"Should be the first element");
        XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 1), 2, @"Should be the second element");
        XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 2), 3, @"Should be the third element");
        
        CCListDestroy(List);
    }
    
    
    for (size_t Loop = 0; Loop < 10; Loop++)
    {
        for (size_t Loop2 = 0; Loop2 < 10; Loop2++)
        {
            for (size_t ChunkSize = 1; ChunkSize < 20; ChunkSize++)
            {
                for (size_t PageSize = 1; PageSize < 20; PageSize++)
                {
                    CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), ChunkSize, PageSize);
                    
                    if (Loop) CCListAppendElements(List, (int[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, Loop);
                    if (Loop2) CCListAppendElements(List, (int[]){ 10, 20, 30, 40, 50, 60, 70, 80, 90 }, Loop2);
                    
                    XCTAssertEqual(CCListGetCount(List), Loop + Loop2, @"Should contain the correct number of elements");
                    for (size_t Loop3 = 0; Loop3 < Loop; Loop3++)
                    {
                        XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, Loop3), Loop3 + 1, @"Should contain the correct element from the first source");
                    }
                    
                    for (size_t Loop3 = 0; Loop3 < Loop2; Loop3++)
                    {
                        XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, Loop3 + Loop), (Loop3 + 1) * 10, @"Should contain the correct element from the second source");
                    }
                    
                    CCListDestroy(List);
                }
            }
        }
    }
}

-(void) testReplacing
{
    for (size_t PageSize = 1; PageSize <= 3; PageSize++)
    {
        for (size_t Index = 0; Index < 3; Index++)
        {
            CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 3, PageSize);
            
            CCListAppendElement(List, &(int){ 1 });
            CCListAppendElement(List, &(int){ 2 });
            CCListAppendElement(List, &(int){ 3 });
            
            CCListReplaceElementAtIndex(List, Index, &(int){ 123 });
            
            XCTAssertEqual(CCListGetCount(List), 3, @"Should contain 3 elements");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 0), (Index == 0 ? 123 : 1), @"Should be the correct element");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 1), (Index == 1 ? 123 : 2), @"Should be the correct element");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 2), (Index == 2 ? 123 : 3), @"Should be the correct element");
            
            CCListDestroy(List);
        }
    }
}

-(void) testInserting
{
    for (size_t PageSize = 1; PageSize <= 3; PageSize++)
    {
        for (size_t Index = 0; Index < 3; Index++)
        {
            CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 3, PageSize);
            
            CCListAppendElement(List, &(int){ 1 });
            CCListAppendElement(List, &(int){ 2 });
            CCListAppendElement(List, &(int){ 3 });
            
            CCListInsertElementAtIndex(List, Index, &(int){ 123 });
            
            XCTAssertEqual(CCListGetCount(List), 4, @"Should contain 4 elements");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 0), (Index == 0 ? 123 : 1), @"Should be the correct element");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 1), (Index == 1 ? 123 : (Index < 1 ? 1 : 2)), @"Should be the correct element");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 2), (Index == 2 ? 123 : 2), @"Should be the correct element");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 3), 3, @"Should now be the third element");
            
            CCListDestroy(List);
        }
    }
}

-(void) testRemoval
{
    for (size_t PageSize = 1; PageSize <= 3; PageSize++)
    {
        for (size_t Index = 0; Index < 3; Index++)
        {
            CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 3, PageSize);
            
            CCListAppendElement(List, &(int){ 1 });
            CCListAppendElement(List, &(int){ 2 });
            CCListAppendElement(List, &(int){ 3 });
            
            CCListRemoveElementAtIndex(List, Index);
            
            XCTAssertEqual(CCListGetCount(List), 2, @"Should contain 2 elements");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 0), (Index == 0 ? 2 : 1), @"Should be the correct element");
            XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 1), (Index <= 1 ? 3 : 2), @"Should be the correct element");
            
            CCListDestroy(List);
        }
    }
}

@end

