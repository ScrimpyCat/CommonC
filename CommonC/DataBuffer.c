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
#include "DataBuffer.h"
#include "MemoryAllocation.h"
#include "Assertion.h"
#include <string.h>


typedef struct {
    void *buffer;
    size_t size;
    CCDataBufferHint hint;
} CCDataBufferInternal;


static void *CCDataBufferConstructor(CCAllocatorType Allocator, CCDataBufferHint Hint, CCDataBufferInit *Data);
static void CCDataBufferDestroy(CCDataBufferInternal *Internal);
static CCDataHint CCDataBufferGetHint(CCDataBufferInternal *Internal);
static size_t CCDataBufferSize(CCDataBufferInternal *Internal);
static CCBufferMap CCDataBufferMapBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, CCDataHint Access);
static void CCDataBufferUnmapBuffer(CCDataBufferInternal *Internal, CCBufferMap MappedBuffer);
static _Bool CCDataBufferResize(CCDataBufferInternal *Internal, size_t Size);
static void *CCDataBufferGetBuffer(CCDataBufferInternal *Internal);
static void CCDataBufferModifiedRange(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size);
static size_t CCDataBufferReadBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, void *Buffer);
static size_t CCDataBufferWriteBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, const void *Buffer);
static size_t CCDataBufferCopyBuffer(CCDataBufferInternal *SrcInternal, ptrdiff_t SrcOffset, size_t Size, CCDataBufferInternal *DstInternal, ptrdiff_t DstOffset);
static size_t CCDataBufferFillBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, uint8_t Fill);

const CCDataInterface CCDataBufferInterface = {
    .create = (CCDataConstructorCallback)CCDataBufferConstructor,
    .destroy = (CCDataDestructorCallback)CCDataBufferDestroy,
    .hints = (CCDataGetHintCallback)CCDataBufferGetHint,
    .size = (CCDataGetSizeCallback)CCDataBufferSize,
    .map = (CCDataMapBufferCallback)CCDataBufferMapBuffer,
    .unmap = (CCDataUnmapBufferCallback)CCDataBufferUnmapBuffer,
    .optional = {
        .resize = (CCDataResizeCallback)CCDataBufferResize,
        .buffer = (CCDataGetBufferCallback)CCDataBufferGetBuffer,
        .modifiedBuffer = (CCDataModifiedRangeCallback)CCDataBufferModifiedRange,
        .read = (CCDataReadBufferCallback)CCDataBufferReadBuffer,
        .write = (CCDataWriteBufferCallback)CCDataBufferWriteBuffer,
        .copy = (CCDataCopyBufferCallback)CCDataBufferCopyBuffer,
        .fill = (CCDataFillBufferCallback)CCDataBufferFillBuffer
    }
};

const CCDataInterface * const CCDataBuffer = &CCDataBufferInterface;

CCData CCDataBufferCreate(CCAllocatorType Allocator, CCDataBufferHint Hint, size_t Size, const void *Buffer, CCDataBufferHash Hash, CCDataBufferDestructor Destructor)
{
    return CCDataCreate(Allocator, (CCDataHint)Hint, &(CCDataBufferInit){ .buffer = Buffer, .size = Size }, Hash, Destructor, CCDataBuffer);
}

static void *CCDataBufferConstructor(CCAllocatorType Allocator, CCDataBufferHint Hint, CCDataBufferInit *Data)
{
    CCAssertLog(Data, "Init data cannot be null");
    CCAssertLog(Data->buffer, "Buffer cannot be null");
    
    CCDataBufferInternal *Internal = CCMalloc(Allocator, sizeof(CCDataBufferInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Internal)
    {
        void *Buffer = (void*)Data->buffer;
        if ((Hint & CCDataBufferHintCopy) == CCDataBufferHintCopy)
        {
            Buffer = CCMalloc(Allocator, Data->size, NULL, CC_DEFAULT_ERROR_CALLBACK);
            if (!Buffer)
            {
                CCFree(Internal);
                return NULL;
            }
            
            memcpy(Buffer, Data->buffer, Data->size);
        }
        
        *Internal = (CCDataBufferInternal){
            .buffer = Buffer,
            .size = Data->size,
            .hint = Hint
        };
    }
    
    return Internal;
}

static void CCDataBufferDestroy(CCDataBufferInternal *Internal)
{
    if (Internal->hint & CCDataBufferHintFree)
    {
        CC_SAFE_Free(Internal->buffer);
    }
    
    CCFree(Internal);
}

static CCDataHint CCDataBufferGetHint(CCDataBufferInternal *Internal)
{
    return (CCDataHint)Internal->hint;
}

static size_t CCDataBufferSize(CCDataBufferInternal *Internal)
{
    return Internal->size;
}

static CCBufferMap CCDataBufferMapBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, CCDataHint Access)
{
    return (CCBufferMap){ .ptr = Internal->buffer + Offset, .offset = Offset, .size = Size, .hint = Access };
}

static void CCDataBufferUnmapBuffer(CCDataBufferInternal *Internal, CCBufferMap MappedBuffer)
{
}

static _Bool CCDataBufferResize(CCDataBufferInternal *Internal, size_t Size)
{
    void *Buffer = CCRealloc(CC_NULL_ALLOCATOR, Internal->buffer, Size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Buffer)
    {
        Internal->buffer = Buffer;
        Internal->size = Size;
        return TRUE;
    }
    
    return FALSE;
}

static void *CCDataBufferGetBuffer(CCDataBufferInternal *Internal)
{
    return Internal->buffer;
}

static void CCDataBufferModifiedRange(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size)
{
}

static size_t CCDataBufferReadBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, void *Buffer)
{
    memcpy(Buffer, Internal->buffer + Offset, Size);
    
    return Size;
}

static size_t CCDataBufferWriteBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, const void *Buffer)
{
    memcpy(Internal->buffer + Offset, Buffer, Size);
    
    return Size;
}

static size_t CCDataBufferCopyBuffer(CCDataBufferInternal *SrcInternal, ptrdiff_t SrcOffset, size_t Size, CCDataBufferInternal *DstInternal, ptrdiff_t DstOffset)
{
    memcpy(DstInternal->buffer + DstOffset, SrcInternal->buffer + SrcOffset, Size);
    
    return Size;
}

static size_t CCDataBufferFillBuffer(CCDataBufferInternal *Internal, ptrdiff_t Offset, size_t Size, uint8_t Fill)
{
    memset(Internal->buffer + Offset, Fill, Size);
    
    return Size;
}

