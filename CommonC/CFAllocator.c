/*
 *  Copyright (c) 2014, Stefan Johnson
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
#include "Allocator.h"
#include "MemoryAllocation.h"
#include "Logging_Private.h"
#include "Platform.h"
#include "Extensions.h"


#if CC_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>


static void *_CCAllocateCFAllocator(CFIndex Size, CFOptionFlags Hint, void *Info)
{
    return CCMemoryAllocate(CC_DEFAULT_ALLOCATOR, Size);
}

static void *_CCReallocateCFAllocator(void *Ptr, CFIndex Size, CFOptionFlags Hint, void *Info)
{
    return CCMemoryReallocate(CC_DEFAULT_ALLOCATOR, Ptr, Size);
}

static void _CCDeallocateCFAllocator(void *Ptr, void *Info)
{
    return CCMemoryDeallocate(Ptr);
}

static CC_CONSTRUCTOR CFAllocatorRef CCAllocatorCFAllocator(void)
{
    static CFAllocatorRef _CCAllocatorCFAllocator = NULL;
    if (!_CCAllocatorCFAllocator)
    {
        _CCAllocatorCFAllocator = CFAllocatorCreate(kCFAllocatorUseContext, &(CFAllocatorContext){
            .version = 0,
            .info = NULL,
            .retain = NULL,
            .release = NULL,
            .copyDescription = NULL,
            .allocate = _CCAllocateCFAllocator,
            .reallocate = _CCReallocateCFAllocator,
            .deallocate = _CCDeallocateCFAllocator,
            .preferredSize = NULL
        });
    }
    
    return _CCAllocatorCFAllocator;
}

static void *CCAllocateCFAllocator(CFIndex Size, CFOptionFlags Hint, CCAllocatorType *Info)
{
    return CCMemoryAllocate(*Info, Size);
}

static void *CCReallocateCFAllocator(void *Ptr, CFIndex Size, CFOptionFlags Hint, CCAllocatorType *Info)
{
    return CCMemoryReallocate(*Info, Ptr, Size);
}

static void CCDeallocateCFAllocator(void *Ptr, CCAllocatorType *Info)
{
    return CCMemoryDeallocate(Ptr);
}

CFAllocatorRef CCCreateCFAllocator(CCAllocatorType Type)
{
    CCAllocatorType *AllocType;
    CC_SAFE_Malloc(AllocType, sizeof(CCAllocatorType),
                   CC_LOG_ERROR("Could not create CF allocator for type(%d)", Type.allocator);
                   return kCFAllocatorNull;
                   );
    
    *AllocType = Type;
    return CFAllocatorCreate(CCAllocatorCFAllocator(), &(CFAllocatorContext){
        .version = 0,
        .info = AllocType,
        .retain = NULL,
        .release = NULL,
        .copyDescription = NULL,
        .allocate = (CFAllocatorAllocateCallBack)CCAllocateCFAllocator,
        .reallocate = (CFAllocatorReallocateCallBack)CCReallocateCFAllocator,
        .deallocate = (CFAllocatorDeallocateCallBack)CCDeallocateCFAllocator,
        .preferredSize = NULL
    });
}

CC_CONSTRUCTOR CFAllocatorRef CCDefaultCFAllocator(void)
{
    static CFAllocatorRef _CCDefaultCFAllocator = NULL;
    if (!_CCDefaultCFAllocator)
    {
        _CCDefaultCFAllocator = CCCreateCFAllocator(CC_DEFAULT_ALLOCATOR);
    }
    
    return _CCDefaultCFAllocator;
}

#endif
