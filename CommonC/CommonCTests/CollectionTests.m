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
#import "CollectionTests.h"
#import "Collection.h"
#import "CollectionEnumerator.h"
#import "LinkedList.h"


static int TestHintWeight(CCCollectionHint Hint)
{
    return INT_MAX;
}

static void *TestConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize)
{
    return CCLinkedListCreateNode(Allocator, 0, NULL);
}

static void TestDestructor(void *Internal)
{
    
}

size_t TestCount(CCLinkedList Internal)
{
    size_t Count = 0;
    while ((Internal = CCLinkedListEnumerateNext(Internal))) Count++;
    
    return Count;
}

CCCollectionEntry TestInsert(CCLinkedList Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
{
    CCCollectionEntry ref = CCLinkedListCreateNode(Allocator, ElementSize, Element);
    CCLinkedListInsertAfter(Internal, ref);
    
    return ref;
}

static void TestRemove(CCLinkedList Internal, CCCollectionEntry Entry, CCAllocatorType Allocator)
{
    CCLinkedListDestroyNode((CCLinkedListNode*)Entry);
}

static void *TestElement(CCLinkedList Internal, CCCollectionEntry Entry)
{
    return Entry ? ((CCLinkedListNodeData*)Entry)->data : NULL;
}

static void *TestEnumeratorFixed(CCLinkedList Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
{
    CCLinkedListNode *Nodes[4];
    size_t Index;
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatFixedBatch;
            
            Index = 0;
            for ( ; (Internal = CCLinkedListEnumerateNext(Internal)) && Index < 4; Index++)
            {
                Enumerator->fixedBatch.ptr[Index] = ((CCLinkedListNodeData*)Internal)->data;
            }
            
            Enumerator->fixedBatch.index = 0;
            Enumerator->fixedBatch.count = Index;
            break;
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatFixedBatch;
            
            Internal = CCLinkedListGetTail(Internal);
            
            Nodes[0] = Internal;
            Index = 1;
            for ( ; (Internal = CCLinkedListEnumeratePrevious(Internal)) && Internal->prev && Index < 4; Index++)
            {
                Nodes[Index] = Internal;
            }
            
            if ((Nodes[0]) && (Nodes[0]->prev))
            {
                for (size_t Loop = 0; (Loop < Index) && (Nodes[Loop]->prev); Loop++)
                {
                    Enumerator->fixedBatch.ptr[(Index - 1) - Loop] = ((CCLinkedListNodeData*)Nodes[Loop])->data;
                }
                
                Enumerator->fixedBatch.index = Index - 1;
                Enumerator->fixedBatch.count = Index;
            }
            
            else Enumerator->fixedBatch.count = 0;
            break;
            
        case CCCollectionEnumeratorActionNext:
            for (void *Last = Enumerator->fixedBatch.ptr[Enumerator->fixedBatch.index]; (Internal = CCLinkedListEnumerateNext(Internal)) && (Last != ((CCLinkedListNodeData*)Internal)->data); );
            
            Index = 0;
            for ( ; (Internal = CCLinkedListEnumerateNext(Internal)) && Index < 4; Index++)
            {
                Enumerator->fixedBatch.ptr[Index] = ((CCLinkedListNodeData*)Internal)->data;
            }
            
            Enumerator->fixedBatch.index = 0;
            Enumerator->fixedBatch.count = Index;
            break;
        
        case CCCollectionEnumeratorActionPrevious:
            Internal = CCLinkedListGetTail(Internal);
            
            for (void *Last = Enumerator->fixedBatch.ptr[Enumerator->fixedBatch.index]; Internal && (Last != ((CCLinkedListNodeData*)Internal)->data); Internal = CCLinkedListEnumeratePrevious(Internal));
            
            if (((CCLinkedListNodeData*)Internal)->data != Enumerator->fixedBatch.ptr[Enumerator->fixedBatch.index])
            {
                Nodes[0] = Internal;
                Index = 1;
                for ( ; (Internal = CCLinkedListEnumeratePrevious(Internal)) && Index < 4; Index++)
                {
                    Nodes[Index] = Internal;
                }
                
                if ((Nodes[0]) && (Nodes[0]->prev))
                {
                    for (size_t Loop = 0; (Loop < Index) && (Nodes[Loop]->prev); Loop++)
                    {
                        Enumerator->fixedBatch.ptr[(Index - 1) - Loop] = ((CCLinkedListNodeData*)Nodes[Loop])->data;
                    }
                    
                    Enumerator->fixedBatch.index = Index - 1;
                    Enumerator->fixedBatch.count = Index;
                }
                
                else Enumerator->fixedBatch.count = 0;
            }
            
            else Enumerator->fixedBatch.count = 0;
            break;
            
        case CCCollectionEnumeratorActionCurrent:
            break;
    }
    
    return Enumerator->fixedBatch.count ? Enumerator->fixedBatch.ptr[Enumerator->fixedBatch.index] : NULL;
}

static void *TestEnumeratorInternal(CCLinkedList Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
{
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatInternal;
            Enumerator->internal.ptr = CCLinkedListEnumerateNext(Internal);
            break;
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatInternal;
            Enumerator->internal.ptr = CCLinkedListGetTail(Internal);
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

static CCCollectionEntry TestEnumeratorEntryFixed(void *Internal, CCEnumeratorState *Enumerator)
{
    //TODO: implement
    return NULL;
}

static CCCollectionEntry TestEnumeratorEntryInternal(void *Internal, CCEnumeratorState *Enumerator)
{
    return Enumerator->internal.ptr;
}

static CCCollectionEntry TestFind(CCLinkedList Internal, const void *Element, CCComparator Comparator, size_t ElementSize)
{
    CCCollectionEntry ref = NULL;
    if (Comparator)
    {
        while ((Internal = CCLinkedListEnumerateNext(Internal)))
        {
            if (Comparator(((CCLinkedListNodeData*)Internal)->data, Element) == CCComparisonResultEqual)
            {
                ref = Internal;
                break;
            }
        }
    }
    
    else
    {
        while ((Internal = CCLinkedListEnumerateNext(Internal)))
        {
            if (!memcmp(((CCLinkedListNodeData*)Internal)->data, Element, ElementSize))
            {
                ref = Internal;
                break;
            }
        }
    }
    
    return ref;
}


static CCCollectionInterface TestCollectionInternal = {
    .hintWeight = TestHintWeight,
    .create = TestConstructor,
    .destroy = TestDestructor,
    .count = (CCCollectionCount)TestCount,
    .insert = (CCCollectionInsert)TestInsert,
    .remove = (CCCollectionRemove)TestRemove,
    .element = (CCCollectionElement)TestElement,
    .enumerator = (CCCollectionEnumerator)TestEnumeratorInternal,
    .enumeratorReference = TestEnumeratorEntryInternal,
    .optional = {
        .find = (CCCollectionFind)TestFind
    }
};

static CCCollectionInterface TestCollectionInternalWithoutFind = {
    .hintWeight = TestHintWeight,
    .create = TestConstructor,
    .destroy = TestDestructor,
    .count = (CCCollectionCount)TestCount,
    .insert = (CCCollectionInsert)TestInsert,
    .remove = (CCCollectionRemove)TestRemove,
    .element = (CCCollectionElement)TestElement,
    .enumerator = (CCCollectionEnumerator)TestEnumeratorInternal,
    .enumeratorReference = TestEnumeratorEntryInternal,
    .optional = {
        .find = NULL
    }
};

static CCCollectionInterface TestCollectionFixed = {
    .hintWeight = TestHintWeight,
    .create = TestConstructor,
    .destroy = TestDestructor,
    .count = (CCCollectionCount)TestCount,
    .insert = (CCCollectionInsert)TestInsert,
    .remove = (CCCollectionRemove)TestRemove,
    .element = (CCCollectionElement)TestElement,
    .enumerator = (CCCollectionEnumerator)TestEnumeratorFixed,
    .enumeratorReference = TestEnumeratorEntryFixed,
    .optional = {
        .find = (CCCollectionFind)TestFind
    }
};


@implementation CollectionTests
@synthesize interface;

-(void) setUp
{
    [super setUp];
    self.interface = &TestCollectionInternal;
}

-(void) tearDown
{
    [super tearDown];
}

-(void) testCreation
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    XCTAssertEqual(CCCollectionGetCount(Collection), 0, @"Should be empty");
    XCTAssertEqual(CCCollectionGetElement(Collection, NULL), NULL, @"Should return null for invalid entry");
    XCTAssertEqual(CCCollectionGetElementSize(Collection), sizeof(int), @"Should be the size specified on creation");
    
    CCCollectionDestroy(Collection);
}

-(void) testInsertion
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionEntry a1 = CCCollectionInsertElement(Collection, &(int){ 1 });
    CCCollectionEntry a2 = CCCollectionInsertElement(Collection, &(int){ 2 });
    CCCollectionEntry a3 = CCCollectionInsertElement(Collection, &(int){ 3 });
    
    XCTAssertEqual(CCCollectionGetCount(Collection), 3, @"Should contain 3 elements");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a1), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a2), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a3), 3, @"Should return the valid element");
    
    CCCollectionDestroy(Collection);
}

-(void) testRemoval
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionEntry a1 = CCCollectionInsertElement(Collection, &(int){ 1 });
    CCCollectionEntry a2 = CCCollectionInsertElement(Collection, &(int){ 2 });
    CCCollectionEntry a3 = CCCollectionInsertElement(Collection, &(int){ 3 });
    
    CCCollectionRemoveElement(Collection, a2);
    
    XCTAssertEqual(CCCollectionGetCount(Collection), 2, @"Should contain 2 elements");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a1), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a3), 3, @"Should return the valid element");
    
    CCCollectionDestroy(Collection);
}

static _Bool TestElementDestroyed = FALSE;
static void TestElementDestructor(CCCollection Collection, int *Element)
{
    TestElementDestroyed = *Element == 2;
}

-(void) testDestructor
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), (CCCollectionElementDestructor)TestElementDestructor, self.interface);
    
    CCCollectionInsertElement(Collection, &(int){ 1 });
    CCCollectionEntry a2 = CCCollectionInsertElement(Collection, &(int){ 2 });
    CCCollectionInsertElement(Collection, &(int){ 3 });
    
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a2), 2, @"Should return the valid element");
    
    CCCollectionRemoveElement(Collection, a2);
    
    XCTAssertTrue(TestElementDestroyed, @"Should have destroyed the correct element");
    
    CCCollectionDestroy(Collection);
    
    XCTAssertFalse(TestElementDestroyed, @"Should have destroyed the remaining elements");
}

static CCComparisonResult TestComparatorEqual(const int *left, const int *right)
{
    return *left == *right ? CCComparisonResultEqual : CCComparisonResultInvalid;
}

-(void) testFinding
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionInsertElement(Collection, &(int){ 1 });
    CCCollectionInsertElement(Collection, &(int){ 2 });
    CCCollectionInsertElement(Collection, &(int){ 3 });
    
    CCCollectionEntry a1 = CCCollectionFindElement(Collection, &(int){ 1 }, NULL);
    CCCollectionEntry a2 = CCCollectionFindElement(Collection, &(int){ 2 }, NULL);
    CCCollectionEntry a3 = CCCollectionFindElement(Collection, &(int){ 3 }, NULL);
    CCCollectionEntry a4 = CCCollectionFindElement(Collection, &(int){ 4 }, NULL);
    
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a1), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a2), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a3), 3, @"Should return the valid element");
    XCTAssertEqual(CCCollectionGetElement(Collection, a4), NULL, @"Should return null for an invalid entry");
    
    
    a1 = CCCollectionFindElement(Collection, &(int){ 1 }, (CCComparator)TestComparatorEqual);
    a2 = CCCollectionFindElement(Collection, &(int){ 2 }, (CCComparator)TestComparatorEqual);
    a3 = CCCollectionFindElement(Collection, &(int){ 3 }, (CCComparator)TestComparatorEqual);
    a4 = CCCollectionFindElement(Collection, &(int){ 4 }, (CCComparator)TestComparatorEqual);
    
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a1), 1, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a2), 2, @"Should return the valid element");
    XCTAssertEqual(*(int*)CCCollectionGetElement(Collection, a3), 3, @"Should return the valid element");
    XCTAssertEqual(CCCollectionGetElement(Collection, a4), NULL, @"Should return null for an invalid entry");
    
    CCCollectionDestroy(Collection);
}

-(void) testEnumerating
{
    CCCollection Collection = CCCollectionCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(int), NULL, self.interface);
    
    CCCollectionInsertElement(Collection, &(int){ 1 });
    CCCollectionInsertElement(Collection, &(int){ 2 });
    CCCollectionInsertElement(Collection, &(int){ 3 });
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Collection, &Enumerator);
    
    XCTAssertEqual(CCCollectionEnumeratorGetCurrent(&Enumerator), CCCollectionEnumeratorGetHead(&Enumerator), @"Initially obtaining the enumerator should be positioned to the head");
    
    int *Element = CCCollectionEnumeratorGetCurrent(&Enumerator);
    int Total = 0;
    size_t Count = 0;
    do
    {
        Total += *Element;
        Count++;
    }
    while ((Element = CCCollectionEnumeratorNext(&Enumerator)));
    
    XCTAssertEqual(Count, 3, @"Should enumerate over 3 elements");
    XCTAssertEqual(Total, 6, @"Should enumerate over each element once");
    
    
    Element = CCCollectionEnumeratorGetTail(&Enumerator);
    Total = 0;
    Count = 0;
    do
    {
        Total += *Element;
        Count++;
    }
    while ((Element = CCCollectionEnumeratorPrevious(&Enumerator)));
    
    XCTAssertEqual(Count, 3, @"Should enumerate over 3 elements");
    XCTAssertEqual(Total, 6, @"Should enumerate over each element once");
    
    
    CCCollectionDestroy(Collection);
}

@end



@interface CollectionInternalWithoutFindTests : CollectionTests

@end

@implementation CollectionInternalWithoutFindTests

-(void) setUp
{
    [super setUp];
    self.interface = &TestCollectionInternalWithoutFind;
}

@end



@interface CollectionFixedTests : CollectionTests

@end

@implementation CollectionFixedTests

-(void) setUp
{
    [super setUp];
    self.interface = &TestCollectionFixed;
}

@end
