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

#define CC_QUICK_COMPILE
#include "CollectionArray.h"
#include "Array.h"
#include "LinkedList.h"
#include "MemoryAllocation.h"


typedef struct {
    CCLinkedListNode node;
    size_t index;
} CCCollectionArrayEntry;

typedef struct {
    CCArray array;
    CCLinkedList entries; //TODO: change to a hash map
} CCCollectionArrayInternal;


static int CCCollectionArrayHintWeight(CCCollectionHint Hint);
static void *CCCollectionArrayConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize);
static void CCCollectionArrayDestructor(CCCollectionArrayInternal *Internal);
static size_t CCCollectionArrayCount(CCCollectionArrayInternal *Internal);
static CCCollectionEntry CCCollectionArrayInsert(CCCollectionArrayInternal *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);
static void CCCollectionArrayRemove(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator);
static void *CCCollectionArrayElement(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry);
static void *CCCollectionArrayEnumerator(CCCollectionArrayInternal *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action);
static CCCollectionEntry CCCollectionArrayEnumeratorEntry(CCCollectionArrayInternal *Internal, CCEnumeratorState *Enumerator);

static CCCollectionEntry ConvertIndexToEntry(CCCollectionArrayInternal *Internal, size_t Index);
static size_t ConvertEntryToIndex(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry);
static CCCollectionEntry CCOrderedCollectionArrayInsert(CCCollectionArrayInternal *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize);
static CCCollectionEntry CCOrderedCollectionArrayReplace(CCCollectionArrayInternal *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize);
static void *CCOrderedCollectionArrayElement(CCCollectionArrayInternal *Internal, size_t Index);
static void CCOrderedCollectionArrayRemove(CCCollectionArrayInternal *Internal, size_t Index, CCAllocatorType Allocator);


static const CCOrderedCollectionInterface CCOrderedCollectionArrayInterface = {
    .insert = (CCOrderedCollectionInsertCallback)CCOrderedCollectionArrayInsert,
    .entry = (CCOrderedCollectionEntryCallback)ConvertIndexToEntry,
    .index = (CCOrderedCollectionIndexCallback)ConvertEntryToIndex,
    .optional = {
        .replace = (CCOrderedCollectionReplaceCallback)CCOrderedCollectionArrayReplace,
        .remove = (CCOrderedCollectionRemoveCallback)CCOrderedCollectionArrayRemove,
        .element = (CCOrderedCollectionElementCallback)CCOrderedCollectionArrayElement
    }
};

const CCCollectionInterface CCCollectionArrayInterface = {
    .hintWeight = CCCollectionArrayHintWeight,
    .create = CCCollectionArrayConstructor,
    .destroy = (CCCollectionDestructorCallback)CCCollectionArrayDestructor,
    .count = (CCCollectionCountCallback)CCCollectionArrayCount,
    .insert = (CCCollectionInsertCallback)CCCollectionArrayInsert,
    .remove =  (CCCollectionRemoveCallback)CCCollectionArrayRemove,
    .element = (CCCollectionElementCallback)CCCollectionArrayElement,
    .enumerator = (CCCollectionEnumeratorCallback)CCCollectionArrayEnumerator,
    .enumeratorReference = (CCCollectionEnumeratorEntryCallback)CCCollectionArrayEnumeratorEntry,
    .optional = {
        .ordered = &CCOrderedCollectionArrayInterface
    }
};

const CCCollectionInterface * const CCCollectionArray = &CCCollectionArrayInterface;


static CCCollectionArrayEntry *FindEntryForIndex(CCCollectionArrayInternal *Internal, size_t Index)
{
    CCCollectionArrayEntry *Node = NULL;
    if (Internal->entries)
    {
        CCLinkedListNode *N = Internal->entries;
        do
        {
            if (((CCCollectionArrayEntry*)N)->index == Index)
            {
                Node = (CCCollectionArrayEntry*)N;
                break;
            }
        } while ((N = CCLinkedListEnumerateNext(N)));
    }
    
    return Node;
}

static CCCollectionEntry ConvertIndexToEntry(CCCollectionArrayInternal *Internal, size_t Index)
{
    CCCollectionArrayEntry *Node = FindEntryForIndex(Internal, Index);
    if (!Node)
    {
        Node = (CCCollectionArrayEntry*)CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(size_t), &Index);
        if (Internal->entries) Internal->entries = CCLinkedListInsert(Internal->entries, (CCLinkedListNode*)Node);
        else Internal->entries = (CCLinkedList)Node;
    }
    
    return Node;
}

static size_t ConvertEntryToIndex(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry)
{
    return Entry ? ((CCCollectionArrayEntry*)Entry)->index : SIZE_MAX;
}

static void ShiftEntriesDownAfterIndex(CCCollectionArrayInternal *Internal, size_t Index)
{
    for (CCLinkedListNode *N = Internal->entries; N; N = CCLinkedListEnumerateNext(N))
    {
        if (((CCCollectionArrayEntry*)N)->index >= Index) ((CCCollectionArrayEntry*)N)->index--;
    }
}

static void ShiftEntriesUpAfterIndex(CCCollectionArrayInternal *Internal, size_t Index)
{
    for (CCLinkedListNode *N = Internal->entries; N; N = CCLinkedListEnumerateNext(N))
    {
        if (((CCCollectionArrayEntry*)N)->index >= Index) ((CCCollectionArrayEntry*)N)->index++;
    }
}

static void RemoveEntry(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry)
{
    if (Entry)
    {
        const size_t Index = ((CCCollectionArrayEntry*)Entry)->index;
        
        if (CCLinkedListIsHead((CCLinkedList)Entry)) Internal->entries = CCLinkedListEnumerateNext((CCLinkedList)Entry);
        CCLinkedListDestroyNode((CCLinkedListNode*)Entry);
        
        ShiftEntriesDownAfterIndex(Internal, Index);
    }
}

static void RemoveEntryForIndex(CCCollectionArrayInternal *Internal, size_t Index)
{
    RemoveEntry(Internal, FindEntryForIndex(Internal, Index));
}

static int CCCollectionArrayHintWeight(CCCollectionHint Hint)
{
    return CCCollectionHintWeightCreate(Hint,
                                        CCCollectionHintHeavyEnumerating
                                        | CCCollectionHintHeavyInserting
                                        | CCCollectionHintConstantLength
                                        | CCCollectionHintConstantElements
                                        | CCCollectionHintOrdered
                                        | CCOrderedCollectionHintHeavyReplacing
                                        | CCOrderedCollectionHintHeavyAppending,
                                        0,
                                        CCCollectionHintHeavyFinding
                                        | CCCollectionHintHeavyDeleting
                                        | CCOrderedCollectionHintHeavyPrepending
                                        | CCOrderedCollectionHintHeavySorting
                                        | CCOrderedCollectionHintHeavyInserting);
}

static void *CCCollectionArrayConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize)
{
    CCCollectionArrayInternal *Internal = CCMalloc(Allocator, sizeof(CCCollectionArrayInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Internal)
    {
        size_t ChunkSize = 5;
        switch (Hint & CCCollectionHintSizeMask)
        {
            case CCCollectionHintSizeSmall:
                ChunkSize = 5;
                break;
                
            case CCCollectionHintSizeMedium:
                ChunkSize = 20;
                break;
                
            case CCCollectionHintSizeLarge:
                ChunkSize = 50;
                break;
        }
        
        *Internal = (CCCollectionArrayInternal){
            .array = CCArrayCreate(Allocator, ElementSize, ChunkSize),
            .entries = NULL
        };
        
        if (!Internal->array)
        {
            CCFree(Internal);
            Internal = NULL;
        }
    }
    
    return Internal;
}

static void CCCollectionArrayDestructor(CCCollectionArrayInternal *Internal)
{
    CCArrayDestroy(Internal->array);
    if (Internal->entries) CCLinkedListDestroy(Internal->entries);
    
    CCFree(Internal);
}

static size_t CCCollectionArrayCount(CCCollectionArrayInternal *Internal)
{
    return CCArrayGetCount(Internal->array);
}

static CCCollectionEntry CCCollectionArrayInsert(CCCollectionArrayInternal *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
{
    size_t Index = CCArrayAppendElement(Internal->array, Element);
    
    return ConvertIndexToEntry(Internal, Index);
}

static void CCCollectionArrayRemove(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator)
{
    CCArrayRemoveElementAtIndex(Internal->array, ConvertEntryToIndex(Internal, Entry));
    RemoveEntry(Internal, Entry);
}

static void *CCCollectionArrayElement(CCCollectionArrayInternal *Internal, CCCollectionEntry Entry)
{
    return CCArrayGetElementAtIndex(Internal->array, ConvertEntryToIndex(Internal, Entry));
}

static void *CCCollectionArrayEnumerator(CCCollectionArrayInternal *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
{
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatBatch;
            Enumerator->batch.count = CCArrayGetCount(Internal->array);
            Enumerator->batch.index = 0;
            Enumerator->batch.stride = CCArrayGetElementSize(Internal->array);
            Enumerator->batch.ptr = Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal->array, 0) : NULL;
            return Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal->array, Enumerator->batch.index) : NULL;
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatBatch;
            Enumerator->batch.count = CCArrayGetCount(Internal->array);
            Enumerator->batch.index = CCArrayGetCount(Internal->array) - 1;
            Enumerator->batch.stride = CCArrayGetElementSize(Internal->array);
            Enumerator->batch.ptr = Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal->array, 0) : NULL;
            return Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal->array, Enumerator->batch.index) : NULL;
            
        default:
            break;
    }
    
    return NULL;
}

static CCCollectionEntry CCCollectionArrayEnumeratorEntry(CCCollectionArrayInternal *Internal, CCEnumeratorState *Enumerator)
{
    return ConvertIndexToEntry(Internal, Enumerator->batch.index);
}

static CCCollectionEntry CCOrderedCollectionArrayInsert(CCCollectionArrayInternal *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize)
{
    if (Index == CCArrayGetCount(Internal->array)) Index = CCArrayAppendElement(Internal->array, Element);
    else Index = CCArrayInsertElementAtIndex(Internal->array, Index, Element);
    
    ShiftEntriesUpAfterIndex(Internal, Index);
    
    return ConvertIndexToEntry(Internal, Index);
}

static CCCollectionEntry CCOrderedCollectionArrayReplace(CCCollectionArrayInternal *Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize)
{
    CCArrayReplaceElementAtIndex(Internal->array, Index, Element);
    
    return ConvertIndexToEntry(Internal, Index);
}

static void CCOrderedCollectionArrayRemove(CCCollectionArrayInternal *Internal, size_t Index, CCAllocatorType Allocator)
{
    CCArrayRemoveElementAtIndex(Internal->array, Index);
    RemoveEntryForIndex(Internal, Index);
}

static void *CCOrderedCollectionArrayElement(CCCollectionArrayInternal *Internal, size_t Index)
{
    return CCArrayGetElementAtIndex(Internal->array, Index);
}
