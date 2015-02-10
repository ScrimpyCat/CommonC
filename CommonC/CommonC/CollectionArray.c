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

#include "CollectionArray.h"
#include "Array.h"


static int CCCollectionArrayHintWeight(CCCollectionHint Hint);
static void *CCCollectionArrayConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize);
static void CCCollectionArrayDestructor(void *Internal);
static size_t CCCollectionArrayCount(void *Internal);
static CCCollectionEntry CCCollectionArrayInsert(void *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize);
static void CCCollectionArrayRemove(void *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator);
static void *CCCollectionArrayElement(void *Internal, CCCollectionEntry Entry);
static void *CCCollectionArrayEnumerator(void *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action);
static CCCollectionEntry CCCollectionArrayEnumeratorEntry(void *Internal, CCEnumeratorState *Enumerator);


const CCCollectionInterface CCCollectionArray = {
    .hintWeight = CCCollectionArrayHintWeight,
    .create = CCCollectionArrayConstructor,
    .destroy = CCCollectionArrayDestructor,
    .count = CCCollectionArrayCount,
    .insert = CCCollectionArrayInsert,
    .remove =  CCCollectionArrayRemove,
    .element = CCCollectionArrayElement,
    .enumerator = CCCollectionArrayEnumerator,
    .enumeratorReference = CCCollectionArrayEnumeratorEntry,
};


static int CCCollectionArrayHintWeight(CCCollectionHint Hint)
{
    return 0;
}

static void *CCCollectionArrayConstructor(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize)
{
    return CCArrayCreate(Allocator, ElementSize, 5);
}

static void CCCollectionArrayDestructor(void *Internal)
{
    CCArrayDestroy(Internal);
}

static size_t CCCollectionArrayCount(void *Internal)
{
    return CCArrayGetCount(Internal);
}

static CCCollectionEntry CCCollectionArrayInsert(void *Internal, const void *Element, CCAllocatorType Allocator, size_t ElementSize)
{
    size_t Index = CCArrayAppendElement(Internal, Element);
    
    return Index != SIZE_MAX ? (CCCollectionEntry)Index : NULL;
}

static void CCCollectionArrayRemove(void *Internal, CCCollectionEntry Entry, CCAllocatorType Allocator)
{
    CCArrayRemoveElementAtIndex(Internal, Entry ? (size_t)Entry : SIZE_MAX);
}

static void *CCCollectionArrayElement(void *Internal, CCCollectionEntry Entry)
{
    return CCArrayGetElementAtIndex(Internal, Entry ? (size_t)Entry : SIZE_MAX);
}

static void *CCCollectionArrayEnumerator(void *Internal, CCEnumeratorState *Enumerator, CCCollectionEnumeratorAction Action)
{
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatBatch;
            Enumerator->batch.count = CCArrayGetCount(Internal);
            Enumerator->batch.index = 0;
            Enumerator->batch.stride = CCArrayGetElementSize(Internal);
            Enumerator->batch.ptr = CCArrayGetElementAtIndex(Internal, 0);
            return CCArrayGetElementAtIndex(Internal, Enumerator->batch.index);
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatBatch;
            Enumerator->batch.count = CCArrayGetCount(Internal);
            Enumerator->batch.index = CCArrayGetCount(Internal) - 1;
            Enumerator->batch.stride = CCArrayGetElementSize(Internal);
            Enumerator->batch.ptr = CCArrayGetElementAtIndex(Internal, 0);
            return CCArrayGetElementAtIndex(Internal, Enumerator->batch.index);
            
        default:
            break;
    }
    
    return NULL;
}

static CCCollectionEntry CCCollectionArrayEnumeratorEntry(void *Internal, CCEnumeratorState *Enumerator)
{
    return (CCCollectionEntry)Enumerator->batch.index;
}
