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
#import "OrderedCollectionTests.h"
#import "OrderedCollection.h"
#import "CollectionEnumerator.h"
#import "LinkedList.h"


typedef struct {
    CCLinkedListNode *end;
    size_t count;
} CollectionListData;

typedef struct {
    CCLinkedListNode node;
    CollectionListData data;
} CollectionListInternal;

static int CollectionListHintWeight(CCCollectionHint Hint)
{
    return 0;
}

static void *CollectionListConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize)
{
    return CCLinkedListCreateNode(Allocator, sizeof(CollectionListData), &(CollectionListData){ .end = NULL, .count = 0 });
}

static void CollectionListDestructor(CollectionListInternal *Internal)
{
    CCLinkedListDestroy((CCLinkedList)Internal);
}

static size_t CollectionListCount(CollectionListInternal *Internal)
{
    return Internal->data.count;
}

static CCCollectionEntry CollectionListInsert(CollectionListInternal *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
{
    CCLinkedListNode *Node = CCLinkedListCreateNode(Allocator, ElementSize, Element);
    if (Node)
    {
        CCLinkedListNode *End = Internal->data.end ? Internal->data.end : (CCLinkedListNode*)Internal;
        Internal->data.end = CCLinkedListAppend(End, Node);
        Internal->data.count++;
    }
    
    return Node;
}

static void CollectionListRemove(CollectionListInternal *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator)
{
    if (CCLinkedListIsTail((CCLinkedListNode*)Entry))
    {
        Internal->data.end = CCLinkedListEnumeratePrevious((CCLinkedListNode*)Entry);
        if (CCLinkedListIsHead(Internal->data.end)) Internal->data.end = NULL;
    }
    
    CCLinkedListDestroyNode((CCLinkedListNode*)Entry);
    Internal->data.count--;
}

static void *CollectionListElement(CollectionListInternal *Internal, CCCollectionEntry Entry)
{
    return CCLinkedListGetNodeData((CCLinkedListNode*)Entry);
}

static void *CollectionListEnumerator(CollectionListInternal *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
{
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatInternal;
            Enumerator->internal.ptr = CCLinkedListEnumerateNext((CCLinkedList)Internal);
            break;
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatInternal;
            Enumerator->internal.ptr = Internal->data.end;
            break;
            
        case CCCollectionEnumeratorActionNext:
            Enumerator->internal.ptr = CCLinkedListEnumerateNext(Enumerator->internal.ptr);
            break;
            
        case CCCollectionEnumeratorActionPrevious:
            Enumerator->internal.ptr = CCLinkedListEnumeratePrevious(Enumerator->internal.ptr);
            if (Enumerator->internal.ptr == Internal) Enumerator->internal.ptr = NULL;
            break;
            
        case CCCollectionEnumeratorActionCurrent:
            break;
    }
    
    return Enumerator->internal.ptr ? ((CCLinkedListNodeData*)Enumerator->internal.ptr)->data : NULL;
}

static CCCollectionEntry CollectionListEnumeratorEntry(CollectionListInternal *Internal, CCEnumeratorState *Enumerator)
{
    return Enumerator->internal.ptr;
}

static CCCollectionEntry OrderedCollectionEntry(CollectionListInternal *Internal, size_t Index)
{
    CCLinkedListNode *Node = CCLinkedListEnumerateNext((CCLinkedList)Internal);
    for (size_t Loop = 0; Loop < Index && Node; Loop++) Node = CCLinkedListEnumerateNext(Node);
    
    return (CCCollectionEntry)Node;
}

static size_t OrderedCollectionIndex(CollectionListInternal *Internal, CCCollectionEntry Entry)
{
    CCLinkedListNode *Node = CCLinkedListEnumerateNext((CCLinkedList)Internal);
    for (size_t Loop = 0; Node; Loop++)
    {
        if (Node == (CCLinkedListNode*)Entry) return Loop;
        
        Node = CCLinkedListEnumerateNext(Node);
    }
    
    return SIZE_MAX;
}

static CCCollectionEntry OrderedCollectionInsert(CollectionListInternal *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize)
{
    CCLinkedListNode *Node = OrderedCollectionEntry(Internal, Index), *E = CCLinkedListCreateNode(Allocator, ElementSize, Element);
    if (Node) CCLinkedListInsertBefore(Node, E);
    else Internal->data.end = CCLinkedListAppend((CCLinkedList)Internal, E);
    
    Internal->data.count++;
    
    return (CCCollectionEntry)E;
}



static const CCOrderedCollectionInterface OrderedCollectionList = {
    .insert = (CCOrderedCollectionInsertCallback)OrderedCollectionInsert,
    .entry = (CCOrderedCollectionEntryCallback)OrderedCollectionEntry,
    .index = (CCOrderedCollectionIndexCallback)OrderedCollectionIndex
};

static const CCCollectionInterface CollectionList = {
    .hintWeight = CollectionListHintWeight,
    .create = CollectionListConstructor,
    .destroy = (CCCollectionDestructorCallback)CollectionListDestructor,
    .count = (CCCollectionCountCallback)CollectionListCount,
    .insert = (CCCollectionInsertCallback)CollectionListInsert,
    .remove =  (CCCollectionRemoveCallback)CollectionListRemove,
    .element = (CCCollectionElementCallback)CollectionListElement,
    .enumerator = (CCCollectionEnumeratorCallback)CollectionListEnumerator,
    .enumeratorReference = (CCCollectionEnumeratorEntryCallback)CollectionListEnumeratorEntry,
    .optional = {
        .ordered = &OrderedCollectionList
    }
};


@implementation OrderedCollectionTests

-(void) setUp
{
    [super setUp];
    self.interface = &CollectionList;
}

-(void) testIndexing
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionEntry a1 = CCOrderedCollectionAppendElement(Collection, &(int){ 1 });
    CCCollectionEntry a2 = CCOrderedCollectionAppendElement(Collection, &(int){ 2 });
    CCCollectionEntry a3 = CCOrderedCollectionAppendElement(Collection, &(int){ 3 });
    
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 0), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 1), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 2), 3, @"Should return the valid element");
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Collection, &Enumerator);
    
    XCTAssertEqual(*(int*)CCCollectionEnumeratorGetCurrent(&Enumerator), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 3, @"Should return the valid element");
    
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a1), 0, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a2), 1, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a3), 2, @"Should return the correct index");
    
    CCCollectionDestroy(Collection);
}

-(void) testIndexedInserting
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionEntry a1 = CCOrderedCollectionInsertElementAtIndex(Collection, &(int){ 1 }, 0);
    CCCollectionEntry a2 = CCOrderedCollectionInsertElementAtIndex(Collection, &(int){ 2 }, 0);
    CCCollectionEntry a3 = CCOrderedCollectionInsertElementAtIndex(Collection, &(int){ 3 }, 0);
    
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 0), 3, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 1), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 2), 1, @"Should return the valid element");
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Collection, &Enumerator);
    
    XCTAssertEqual(*(int*)CCCollectionEnumeratorGetCurrent(&Enumerator), 3, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 1, @"Should return the valid element");
    
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a1), 2, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a2), 1, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a3), 0, @"Should return the correct index");
    
    CCCollectionDestroy(Collection);
}

-(void) testIndexedRemoving
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionEntry a1 = CCOrderedCollectionAppendElement(Collection, &(int){ 1 });
    CCOrderedCollectionAppendElement(Collection, &(int){ 2 });
    CCCollectionEntry a3 = CCOrderedCollectionAppendElement(Collection, &(int){ 3 });
    
    CCOrderedCollectionRemoveElementAtIndex(Collection, 1);
    
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 0), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 1), 3, @"Should return the valid element");
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Collection, &Enumerator);
    
    XCTAssertEqual(*(int*)CCCollectionEnumeratorGetCurrent(&Enumerator), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 3, @"Should return the valid element");
    
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a1), 0, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a3), 1, @"Should return the correct index");
    
    CCCollectionDestroy(Collection);
    
    
    
    Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCOrderedCollectionAppendElement(Collection, &(int){ 1 });
    CCOrderedCollectionAppendElement(Collection, &(int){ 2 });
    
    CCOrderedCollectionRemoveLastElement(Collection);
    CCOrderedCollectionRemoveLastElement(Collection);
    
    XCTAssertEqual(CCCollectionGetCount(Collection), 0, @"Should be empty");
    
    CCCollectionDestroy(Collection);
}

-(void) testIndexedReplacing
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionEntry a1 = CCOrderedCollectionAppendElement(Collection, &(int){ 1 });
    CCCollectionEntry a2 = CCOrderedCollectionAppendElement(Collection, &(int){ 2 });
    CCCollectionEntry a3 = CCOrderedCollectionAppendElement(Collection, &(int){ 3 });
    
    a2 = CCOrderedCollectionReplaceElementAtIndex(Collection, &(int){ 4 }, 1);
    
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 0), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 1), 4, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(Collection, 2), 3, @"Should return the valid element");
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Collection, &Enumerator);
    
    XCTAssertEqual(*(int*)CCCollectionEnumeratorGetCurrent(&Enumerator), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 4, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionEnumeratorNext(&Enumerator), 3, @"Should return the valid element");
    
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a1), 0, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a2), 1, @"Should return the correct index");
    XCTAssertEqual(CCOrderedCollectionGetIndex(Collection, a3), 2, @"Should return the correct index");
    
    CCCollectionDestroy(Collection);
}

@end
