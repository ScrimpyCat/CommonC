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

#include "CollectionList.h"
#include "LinkedList.h"


typedef struct {
    CCLinkedListNode *end;
    size_t count;
} CCCollectionListData;

typedef struct {
    CCLinkedListNode node;
    CCCollectionListData data;
} CCCollectionListInternal;

static int CCCollectionListHintWeight(CCCollectionHint Hint);
static void *CCCollectionListConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize);
static void CCCollectionListDestructor(CCCollectionListInternal *Internal);
static size_t CCCollectionListCount(CCCollectionListInternal *Internal);
static CCCollectionEntry CCCollectionListInsert(CCCollectionListInternal *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);
static void CCCollectionListRemove(CCCollectionListInternal *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator);
static void *CCCollectionListElement(CCCollectionListInternal *Internal, CCCollectionEntry Entry);
static void *CCCollectionListEnumerator(CCCollectionListInternal *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action);
static CCCollectionEntry CCCollectionListEnumeratorEntry(CCCollectionListInternal *Internal, CCEnumeratorState *Enumerator);


const CCCollectionInterface CCCollectionList = {
    .hintWeight = CCCollectionListHintWeight,
    .create = CCCollectionListConstructor,
    .destroy = (CCCollectionDestructor)CCCollectionListDestructor,
    .count = (CCCollectionCount)CCCollectionListCount,
    .insert = (CCCollectionInsert)CCCollectionListInsert,
    .remove =  (CCCollectionRemove)CCCollectionListRemove,
    .element = (CCCollectionElement)CCCollectionListElement,
    .enumerator = (CCCollectionEnumerator)CCCollectionListEnumerator,
    .enumeratorReference = (CCCollectionEnumeratorEntry)CCCollectionListEnumeratorEntry,
};


static int CCCollectionListHintWeight(CCCollectionHint Hint)
{
    return 0;
}

static void *CCCollectionListConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize)
{
    return CCLinkedListCreateNode(Allocator, sizeof(CCCollectionListData), &(CCCollectionListData){ .end = NULL, .count = 0 });
}

static void CCCollectionListDestructor(CCCollectionListInternal *Internal)
{
    CCLinkedListDestroy((CCLinkedList)Internal);
}

static size_t CCCollectionListCount(CCCollectionListInternal *Internal)
{
    return Internal->data.count;
}

static CCCollectionEntry CCCollectionListInsert(CCCollectionListInternal *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
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

static void CCCollectionListRemove(CCCollectionListInternal *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator)
{
    if (CCLinkedListIsTail((CCLinkedListNode*)Entry))
    {
        Internal->data.end = CCLinkedListEnumeratePrevious((CCLinkedListNode*)Entry);
        if (CCLinkedListIsHead(Internal->data.end)) Internal->data.end = NULL;
    }
    
    CCLinkedListDestroyNode((CCLinkedListNode*)Entry);
    Internal->data.count--;
}

static void *CCCollectionListElement(CCCollectionListInternal *Internal, CCCollectionEntry Entry)
{
    return CCLinkedListGetNodeData((CCLinkedListNode*)Entry);
}

static void *CCCollectionListEnumerator(CCCollectionListInternal *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
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

static CCCollectionEntry CCCollectionListEnumeratorEntry(CCCollectionListInternal *Internal, CCEnumeratorState *Enumerator)
{
    return Enumerator->internal.ptr;
}

