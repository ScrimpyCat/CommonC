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
#import "LinkedList.h"


typedef struct {
    int a;
    int b;
} TestData;

typedef struct {
    CCLinkedListNode node;
    TestData data;
} TestList;

@interface LinkedListTests : XCTestCase

@end

@implementation LinkedListTests

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
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    
    XCTAssertEqual(((TestList*)List)->data.a, 1, @"Should be initialized with the passed values");
    XCTAssertEqual(((TestList*)List)->data.b, 2, @"Should be initialized with the passed values");
    
    CCLinkedListDestroy(List);
}

-(void) testInsertion
{
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    
    List = CCLinkedListInsert(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    List = CCLinkedListInsert(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    
    XCTAssertTrue(CCLinkedListIsHead(List), @"Should return the head of the two inputs"); //in our case will be the absolute head
    
    CCLinkedList N = List;
    int a = 0, b = 0;
    do
    {
        a += ((TestList*)List)->data.a;
        b += ((TestList*)List)->data.b;
    } while ((N = CCLinkedListEnumerateNext(N)));
    
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    CCLinkedListDestroy(List);
}

-(void) testInsertionAfter
{
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    
    CCLinkedListNode *Tail, *RTail;
    CCLinkedList HList = CCLinkedListInsertAfter(List, Tail = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    CCLinkedList RList = CCLinkedListInsertAfter(Tail, RTail = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    
    XCTAssertTrue(CCLinkedListIsHead(List), @"Should remain the head");
    XCTAssertTrue(CCLinkedListIsHead(HList), @"Should be the head");
    XCTAssertFalse(CCLinkedListIsHead(RList), @"Should not be the head");
    XCTAssertTrue(CCLinkedListIsTail(RTail), @"Should be the tail");
    
    
    CCLinkedList N = List;
    int a = 0, b = 0;
    do
    {
        a += ((TestList*)N)->data.a;
        b += ((TestList*)N)->data.b;
    } while ((N = CCLinkedListEnumerateNext(N)));
    
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    CCLinkedListDestroy(List);
}

-(void) testInsertionBefore
{
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    
    CCLinkedListNode *Head;
    CCLinkedList HList = CCLinkedListInsertBefore(List, Head = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    CCLinkedList RList = CCLinkedListInsertBefore(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    
    XCTAssertTrue(CCLinkedListIsTail(List), @"Should be the tail");
    XCTAssertTrue(CCLinkedListIsHead(HList), @"Should be the head");
    XCTAssertFalse(CCLinkedListIsHead(RList), @"Should not be the head");
    XCTAssertTrue(CCLinkedListIsHead(Head), @"Should be the head");
    
    List = HList;
    
    CCLinkedList N = List;
    int a = 0, b = 0;
    do
    {
        a += ((TestList*)N)->data.a;
        b += ((TestList*)N)->data.b;
    } while ((N = CCLinkedListEnumerateNext(N)));
    
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    CCLinkedListDestroy(List);
}

-(void) testAppending
{
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    
    CCLinkedListAppend(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    CCLinkedListNode *Tail;
    CCLinkedList RList = CCLinkedListAppend(List, Tail = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    
    XCTAssertTrue(CCLinkedListIsHead(List), @"Should remain the head");
    XCTAssertTrue(CCLinkedListIsTail(Tail), @"Should be the tail");
    XCTAssertEqual(Tail, RList, @"Should return the tail");
    
    
    CCLinkedList N = List;
    int a = 0, b = 0;
    do
    {
        a += ((TestList*)N)->data.a;
        b += ((TestList*)N)->data.b;
    } while ((N = CCLinkedListEnumerateNext(N)));
    
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    CCLinkedListDestroy(List);
}

-(void) testPrepending
{
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    
    CCLinkedList RList = CCLinkedListPrepend(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    CCLinkedListNode *Head;
    RList = CCLinkedListPrepend(RList, Head = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    
    XCTAssertTrue(CCLinkedListIsTail(List), @"Should remain the tail");
    XCTAssertTrue(CCLinkedListIsHead(Head), @"Should be the head");
    XCTAssertTrue(CCLinkedListIsHead(RList), @"Should return the head");
    
    
    CCLinkedList N = List;
    int a = 0, b = 0;
    do
    {
        a += ((TestList*)N)->data.a;
        b += ((TestList*)N)->data.b;
    } while ((N = CCLinkedListEnumeratePrevious(N)));
    
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    RList = CCLinkedListPrepend(List, Head = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    XCTAssertTrue(CCLinkedListIsHead(RList), @"Should place node at the head regardless of current relative list passed in");
    
    CCLinkedListDestroy(RList);
}

-(void) testRemoval
{
    CCLinkedList List = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 });
    CCLinkedListAppend(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    CCLinkedListNode *Node;
    CCLinkedListAppend(List, Node = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 3, 3 }));
    CCLinkedListAppend(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 1, 2 }));
    
    
    CCLinkedListRemoveNode(Node);
    CCLinkedListDestroyNode(Node);
    
    CCLinkedList N = List;
    int a = 0, b = 0;
    do
    {
        XCTAssertNotEqual(((TestList*)N)->data.a, 3, @"Should have been removed");
        XCTAssertNotEqual(((TestList*)N)->data.b, 3, @"Should have been removed");
        a += ((TestList*)N)->data.a;
        b += ((TestList*)N)->data.b;
    } while ((N = CCLinkedListEnumerateNext(N)));
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    CCLinkedListNode *Begin, *End;
    CCLinkedListAppend(List, Begin = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 3, 3 }));
    CCLinkedListAppend(List, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 3, 3 }));
    CCLinkedListAppend(List, End = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(TestData), &(TestData){ 3, 3 }));
    
    CCLinkedListRemove(Begin, End);
    CCLinkedListDestroy(Begin);
    
    N = List;
    a = 0, b = 0;
    do
    {
        XCTAssertNotEqual(((TestList*)N)->data.a, 3, @"Should have been removed");
        XCTAssertNotEqual(((TestList*)N)->data.b, 3, @"Should have been removed");
        a += ((TestList*)N)->data.a;
        b += ((TestList*)N)->data.b;
    } while ((N = CCLinkedListEnumerateNext(N)));
    
    XCTAssertEqual(a, 3, @"Should have the correct value when list is summed");
    XCTAssertEqual(b, 6, @"Should have the correct value when list is summed");
    
    CCLinkedListDestroy(List);
}

@end
