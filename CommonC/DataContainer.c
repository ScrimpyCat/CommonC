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

#define CC_QUICK_COMPILE
#include "DataContainer.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <string.h>


typedef struct {
    void *container;
    size_t elementSize;
    CCDataContainerCount count;
    CCDataContainerEnumerable enumerable;
    CCDataContainerHint hint;
} CCDataContainerInternal;


static void *CCDataContainerConstructor(CCAllocatorType Allocator, CCDataContainerHint Hint, CCDataContainerInit *Data);
static void CCDataContainerDestroy(CCDataContainerInternal *Internal);
static CCDataHint CCDataContainerGetHint(CCDataContainerInternal *Internal);
static size_t CCDataContainerSize(CCDataContainerInternal *Internal);
static CCBufferMap CCDataContainerMapBuffer(CCDataContainerInternal *Internal, ptrdiff_t Offset, size_t Size, CCDataHint Access);
static void CCDataContainerUnmapBuffer(CCDataContainerInternal *Internal, CCBufferMap MappedBuffer);

const CCDataInterface CCDataContainerInterface = {
    .create = (CCDataConstructorCallback)CCDataContainerConstructor,
    .destroy = (CCDataDestructorCallback)CCDataContainerDestroy,
    .hints = (CCDataGetHintCallback)CCDataContainerGetHint,
    .size = (CCDataGetSizeCallback)CCDataContainerSize,
    .map = (CCDataMapBufferCallback)CCDataContainerMapBuffer,
    .unmap = (CCDataUnmapBufferCallback)CCDataContainerUnmapBuffer
};

const CCDataInterface * const CCDataContainer = &CCDataContainerInterface;

CCData CCDataContainerCreate(CCAllocatorType Allocator, CCDataContainerHint Hint, size_t ElementSize, CCDataContainerCount Count, CCDataContainerEnumerable Enumerable, const void *Container, CCDataBufferHash Hash, CCDataBufferDestructor Destructor)
{
    return CCDataCreate(Allocator, (CCDataHint)Hint, &(CCDataContainerInit){ .container = Container, .elementSize = ElementSize, .count = Count, .enumerable = Enumerable }, Hash, Destructor, CCDataContainer);
}

static void *CCDataContainerConstructor(CCAllocatorType Allocator, CCDataContainerHint Hint, CCDataContainerInit *Data)
{
    CCAssertLog(Data, "Init data cannot be null");
    CCAssertLog(Data->container, "Container cannot be null");
    CCAssertLog(Data->enumerable, "Enumerable cannot be null");
    
    CCDataContainerInternal *Internal = CCMalloc(Allocator, sizeof(CCDataContainerInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Internal)
    {
        *Internal = (CCDataContainerInternal){
            .container = CCRetain((void*)Data->container),
            .elementSize = Data->elementSize,
            .count = Data->count,
            .enumerable = Data->enumerable,
            .hint = Hint
        };
    }
    
    return Internal;
}

static void CCDataContainerDestroy(CCDataContainerInternal *Internal)
{
    CC_SAFE_Free(Internal->container);
    
    CCFree(Internal);
}

static CCDataHint CCDataContainerGetHint(CCDataContainerInternal *Internal)
{
    return (CCDataHint)Internal->hint;
}

static size_t CCDataContainerSize(CCDataContainerInternal *Internal)
{
    size_t Count = 0;
    if (!Internal->count)
    {
        CCEnumerable Enumerable;
        Internal->enumerable(Internal->container, &Enumerable);
        
        for (const void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable)) Count++;
    }
    
    else Count = Internal->count(Internal->container);
    
    return Count * Internal->elementSize;
}

static CCBufferMap CCDataContainerMapBuffer(CCDataContainerInternal *Internal, ptrdiff_t Offset, size_t Size, CCDataHint Access)
{
    const size_t PartialStart = Offset % Internal->elementSize, PartialEnd = Size % Internal->elementSize;
    const size_t AlignedOffset = Offset - PartialStart, AlignedSize = Size + (PartialEnd ? Internal->elementSize - PartialEnd : 0);
    
    void *Ptr;
    CC_SAFE_Malloc(Ptr, AlignedSize + (PartialStart ? Internal->elementSize : 0),
                   CC_LOG_ERROR("Failed to map buffer: Failed to allocate memory of size (%zu)", AlignedSize + (PartialStart ? Internal->elementSize : 0));
                   return (CCBufferMap){ .ptr = NULL, .offset = 0, .size = 0, .hint = 0 };
                   );
    
    if (Access & CCDataHintRead)
    {
        CCEnumerable Enumerable;
        Internal->enumerable(Internal->container, &Enumerable);
        
        size_t Index = 0, ContainerIndex = 0, Count = AlignedOffset + AlignedSize + (PartialStart ? Internal->elementSize : 0);
        for (const void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable), ContainerIndex++)
        {
            if ((ContainerIndex * Internal->elementSize) >= AlignedOffset)
            {
                memcpy(Ptr + (Index++ * Internal->elementSize), Element, Internal->elementSize);
                
                if (((ContainerIndex + 1) * Internal->elementSize) == Count) break;
            }
        }
    }
    
    return (CCBufferMap){ .ptr = Ptr + PartialStart, .offset = Offset, .size = Size, .hint = Access };
}

static void CCDataContainerUnmapBuffer(CCDataContainerInternal *Internal, CCBufferMap MappedBuffer)
{
    const size_t PartialStart = MappedBuffer.offset % Internal->elementSize;
    
    void *Ptr = MappedBuffer.ptr - PartialStart;
    if (MappedBuffer.hint & CCDataHintWrite)
    {
        const size_t PartialEnd = MappedBuffer.size % Internal->elementSize;
        const size_t AlignedOffset = MappedBuffer.offset - PartialStart, AlignedSize = MappedBuffer.size + (PartialEnd ? Internal->elementSize - PartialEnd : 0);
        
        CCEnumerable Enumerable;
        Internal->enumerable(Internal->container, &Enumerable);
        
        size_t Index = 0, ContainerIndex = 0, Count = AlignedOffset + AlignedSize + (PartialStart ? Internal->elementSize : 0);
        for (void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable), ContainerIndex++)
        {
            if ((ContainerIndex * Internal->elementSize) >= AlignedOffset)
            {
                memcpy(Element, Ptr + (Index++ * Internal->elementSize), Internal->elementSize);
                
                if (((ContainerIndex + 1) * Internal->elementSize) == Count) break;
            }
        }
    }
    
    CCFree(Ptr);
}
