/*
 *  Copyright (c) 2013, Stefan Johnson
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

#include "MemoryAllocation.h"

#undef CCMalloc
#undef CCRealloc


void *CCMalloc(CCAllocatorType Type, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallback ErrorCallback)
{
    void *Memory = CCMemoryAllocate(Type, Size);
    if (!Memory)
    {
        if (ErrorCallback) Memory = ErrorCallback((CCFunctionData*)&(CCFunctionDataMalloc){
            .indicator = CCMalloc,
            .info = "Failed to allocate memory.",
            .filename = Filename,
            .functionName = FunctionName,
            .line = Line,
            .type = Type,
            .size = Size
        }, CallbackData);
    }
    
    return Memory;
}

void *CCRealloc(CCAllocatorType Type, void *Ptr, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallback ErrorCallback)
{
    void *Memory = CCMemoryReallocate(Type, Ptr, Size);
    if (!Memory)
    {
        if (ErrorCallback) Memory = ErrorCallback((CCFunctionData*)&(CCFunctionDataRealloc){
            .indicator = CCRealloc,
            .info = "Failed to reallocate memory.",
            .filename = Filename,
            .functionName = FunctionName,
            .line = Line,
            .type = Type,
            .ptr = Ptr,
            .size = Size
        }, CallbackData);
    }
    
    return Memory;
}

void CCFree(void *Ptr)
{
    if (Ptr) CCMemoryDeallocate(Ptr);
}

void *CCRetain(void *Ptr)
{
    return Ptr ? CCMemoryRetain(Ptr) : NULL;
}

int32_t CCRefCount(void *Ptr)
{
    return Ptr ? CCMemoryRefCount(Ptr) : 0;
}

#if __BLOCKS__
void *CCMallocBlock(CCAllocatorType Type, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallbackBlock ErrorCallback)
{
    void *Memory = CCMemoryAllocate(Type, Size);
    if (!Memory)
    {
        if (ErrorCallback) Memory = ErrorCallback((CCFunctionData*)&(CCFunctionDataMalloc){
            .indicator = CCMallocBlock,
            .info = "Failed to allocate memory.",
            .filename = Filename,
            .functionName = FunctionName,
            .line = Line,
            .type = Type,
            .size = Size
        }, CallbackData);
    }
    
    return Memory;
}

void *CCReallocBlock(CCAllocatorType Type, void *Ptr, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallbackBlock ErrorCallback)
{
    void *Memory = CCMemoryReallocate(Type, Ptr, Size);
    if (!Memory)
    {
        if (ErrorCallback) Memory = ErrorCallback((CCFunctionData*)&(CCFunctionDataRealloc){
            .indicator = CCRealloc,
            .info = "Failed to reallocate memory.",
            .filename = Filename,
            .functionName = FunctionName,
            .line = Line,
            .type = Type,
            .ptr = Ptr,
            .size = Size
        }, CallbackData);
    }
    
    return Memory;
}
#endif
