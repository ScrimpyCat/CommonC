/*
 *  Copyright (c) 2016, Stefan Johnson
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
#include "CollectionFastArray.h"
#include "Array.h"
#include "MemoryAllocation.h"
#include "Collection.h"
#include "CollectionEnumerator.h"


static int CCCollectionFastArrayHintWeight(CCCollectionHint Hint);
static void *CCCollectionFastArrayConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize);
static CCCollectionEntry CCCollectionFastArrayInsert(CCArray Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);
static void CCCollectionFastArrayRemove(CCArray Internal, CCCollectionEntry Entry, CCAllocatorType Allocator);
static void *CCCollectionFastArrayElement(CCArray Internal, CCCollectionEntry Entry);
static void *CCCollectionFastArrayEnumerator(CCArray Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action);
static CCCollectionEntry CCCollectionFastArrayEnumeratorEntry(CCArray Internal, CCEnumeratorState *Enumerator);
static void CCCollectionFastArrayRemoveAll(CCArray Internal, CCAllocatorType Allocator);
static void CCCollectionFastArrayRemoveCollection(CCArray Internal, CCCollection Entries, CCAllocatorType Allocator);

static CCCollectionEntry ConvertIndexToEntry(CCArray Internal, size_t Index);
static size_t ConvertEntryToIndex(CCArray Internal, CCCollectionEntry Entry);
static CCCollectionEntry CCOrderedCollectionFastArrayInsert(CCArray Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize);
static CCCollectionEntry CCOrderedCollectionFastArrayReplace(CCArray Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize);
static void CCOrderedCollectionFastArrayRemove(CCArray Internal, size_t Index, CCAllocatorType Allocator);
static CCCollectionEntry CCOrderedCollectionFastArrayAppend(CCArray Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);
static void *CCOrderedCollectionFastArrayElement(CCArray Internal, size_t Index);


static const CCOrderedCollectionInterface CCOrderedCollectionFastArrayInterface = {
    .insert = (CCOrderedCollectionInsertCallback)CCOrderedCollectionFastArrayInsert,
    .entry = (CCOrderedCollectionEntryCallback)ConvertIndexToEntry,
    .index = (CCOrderedCollectionIndexCallback)ConvertEntryToIndex,
    .optional = {
        .replace = (CCOrderedCollectionReplaceCallback)CCOrderedCollectionFastArrayReplace,
        .remove = (CCOrderedCollectionRemoveCallback)CCOrderedCollectionFastArrayRemove,
        .append = (CCOrderedCollectionAppendCallback)CCOrderedCollectionFastArrayAppend,
        .element = (CCOrderedCollectionElementCallback)CCOrderedCollectionFastArrayElement
    }
};

const CCCollectionInterface CCCollectionFastArrayInterface = {
    .hintWeight = CCCollectionFastArrayHintWeight,
    .create = CCCollectionFastArrayConstructor,
    .destroy = (CCCollectionDestructorCallback)CCArrayDestroy,
    .count = (CCCollectionCountCallback)CCArrayGetCount,
    .insert = (CCCollectionInsertCallback)CCCollectionFastArrayInsert,
    .remove =  (CCCollectionRemoveCallback)CCCollectionFastArrayRemove,
    .element = (CCCollectionElementCallback)CCCollectionFastArrayElement,
    .enumerator = (CCCollectionEnumeratorCallback)CCCollectionFastArrayEnumerator,
    .enumeratorReference = (CCCollectionEnumeratorEntryCallback)CCCollectionFastArrayEnumeratorEntry,
    .optional = {
        .ordered = &CCOrderedCollectionFastArrayInterface,
        .removeAll = (CCCollectionRemoveAllCallback)CCCollectionFastArrayRemoveAll,
        .removeCollection = (CCCollectionRemoveCollectionCallback)CCCollectionFastArrayRemoveCollection
    }
};

const CCCollectionInterface * const CCCollectionFastArray = &CCCollectionFastArrayInterface;


static CCCollectionEntry ConvertIndexToEntry(CCArray Internal, size_t Index)
{
    return (CCCollectionEntry)(Index + 1);
}

static size_t ConvertEntryToIndex(CCArray Internal, CCCollectionEntry Entry)
{
    return (size_t)Entry - 1;
}

static int CCCollectionFastArrayHintWeight(CCCollectionHint Hint)
{
    return CCCollectionHintWeightCreate(Hint,
                                        CCCollectionHintHeavyEnumerating
                                        | CCCollectionHintHeavyInserting
                                        | CCCollectionHintConstantLength
                                        | CCCollectionHintConstantElements
                                        | CCCollectionHintOrdered
                                        | CCOrderedCollectionHintHeavyReplacing
                                        | CCOrderedCollectionHintHeavyAppending,
                                        CCCollectionHintHeavyDeleting,
                                        CCCollectionHintHeavyFinding
                                        | CCOrderedCollectionHintHeavyPrepending
                                        | CCOrderedCollectionHintHeavySorting
                                        | CCOrderedCollectionHintHeavyInserting);
}

static void *CCCollectionFastArrayConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize)
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
    
    return CCArrayCreate(Allocator, ElementSize, ChunkSize);
}

static CCCollectionEntry CCCollectionFastArrayInsert(CCArray Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
{
    return (CCCollectionEntry)(CCArrayAppendElement(Internal, Element) + 1);
}

static void CCCollectionFastArrayRemove(CCArray Internal, CCCollectionEntry Entry, CCAllocatorType Allocator)
{
    CCArrayRemoveElementAtIndex(Internal, (size_t)Entry - 1);
}

static void *CCCollectionFastArrayElement(CCArray Internal, CCCollectionEntry Entry)
{
    return CCArrayGetElementAtIndex(Internal, (size_t)Entry - 1);
}

static void *CCCollectionFastArrayEnumerator(CCArray Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
{
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatBatch;
            Enumerator->batch.count = CCArrayGetCount(Internal);
            Enumerator->batch.index = 0;
            Enumerator->batch.stride = CCArrayGetElementSize(Internal);
            Enumerator->batch.ptr = Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal, 0) : NULL;
            return Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal, Enumerator->batch.index) : NULL;
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatBatch;
            Enumerator->batch.count = CCArrayGetCount(Internal);
            Enumerator->batch.index = CCArrayGetCount(Internal) - 1;
            Enumerator->batch.stride = CCArrayGetElementSize(Internal);
            Enumerator->batch.ptr = Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal, 0) : NULL;
            return Enumerator->batch.count ? CCArrayGetElementAtIndex(Internal, Enumerator->batch.index) : NULL;
            
        default:
            break;
    }
    
    return NULL;
}

static CCCollectionEntry CCCollectionFastArrayEnumeratorEntry(CCArray Internal, CCEnumeratorState *Enumerator)
{
    return (CCCollectionEntry)(Enumerator->batch.index + 1);
}

static void CCCollectionFastArrayRemoveAll(CCArray Internal, CCAllocatorType Allocator)
{
    CCArrayRemoveAllElements(Internal);
}

static void CCCollectionFastArrayRemoveCollection(CCArray Internal, CCCollection Entries, CCAllocatorType Allocator)
{
    //TODO: Sort entries
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Entries, &Enumerator);
    
    for (CCCollectionEntry *Entry = CCCollectionEnumeratorGetTail(&Enumerator); Entry; Entry = CCCollectionEnumeratorPrevious(&Enumerator))
    {
        CCArrayRemoveElementAtIndex(Internal, (size_t)*Entry - 1);
    }
}

static CCCollectionEntry CCOrderedCollectionFastArrayInsert(CCArray Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize)
{
    if (Index == CCArrayGetCount(Internal)) Index = CCArrayAppendElement(Internal, Element);
    else Index = CCArrayInsertElementAtIndex(Internal, Index, Element);
    
    return (CCCollectionEntry)(Index + 1);
}

static CCCollectionEntry CCOrderedCollectionFastArrayReplace(CCArray Internal, const void *Element, size_t Index, CCAllocatorType Allocator, size_t ElementSize)
{
    CCArrayReplaceElementAtIndex(Internal, Index, Element);
    
    return (CCCollectionEntry)(Index + 1);
}

static void CCOrderedCollectionFastArrayRemove(CCArray Internal, size_t Index, CCAllocatorType Allocator)
{
    CCArrayRemoveElementAtIndex(Internal, Index);
}

static CCCollectionEntry CCOrderedCollectionFastArrayAppend(CCArray Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
{
    return (CCCollectionEntry)(CCArrayAppendElement(Internal, Element) + 1);
}

static void *CCOrderedCollectionFastArrayElement(CCArray Internal, size_t Index)
{
    return CCArrayGetElementAtIndex(Internal, Index);
}
