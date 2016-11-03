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

#ifndef CommonC_Allocator_h
#define CommonC_Allocator_h

#include <stdlib.h>
#include <CommonC/Platform.h>
#include <CommonC/Ownership.h>

typedef struct CCAllocatorType {
    int allocator; //the allocator to be used
    void *data; //additional data to be passed to that allocator
} CCAllocatorType;

#define CC_NULL_ALLOCATOR (CCAllocatorType){ .allocator = -1 } //No allocation
#define CC_STD_ALLOCATOR (CCAllocatorType){ .allocator = 0 } //Uses stdlib
#define CC_CUSTOM_ALLOCATOR(alloc, realloc, dealloc) (CCAllocatorType){ .allocator = 1, .data = (void*[3]){ alloc, realloc, dealloc } }
#define CC_CALLBACK_ALLOCATOR(callback) (CCAllocatorType){ .allocator = 2, .data = callback } //Uses stdlib
#define CC_ALIGNED_ALLOCATOR(alignment) (CCAllocatorType){ .allocator = 3, .data = &(size_t){ alignment } } //Uses stdlib

typedef void *(*CCAllocatorFunction)(void *Data, size_t Size); //Additional data to be passed to the allocator (data from CCAllocatorType data member)
typedef void *(*CCReallocatorFunction)(void *Data, void *Ptr, size_t Size);
typedef void (*CCDeallocatorFunction)(void *Ptr);

typedef void (*CCMemoryDestructorCallback)(void *Ptr);

#if defined(__has_include)

#if __has_include(<stdatomic.h>)
#define CC_ALLOCATOR_USING_STDATOMIC 1
#include <stdatomic.h>
#elif CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#define CC_ALLOCATOR_USING_OSATOMIC 1
#include <libkern/OSAtomic.h>
#else
#warning No atomic support
#endif

#elif CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#define CC_ALLOCATOR_USING_OSATOMIC 1
#include <libkern/OSAtomic.h>
#else
#define CC_ALLOCATOR_USING_STDATOMIC 1
#include <stdatomic.h>
#endif

typedef struct {
    int allocator;
#if CC_ALLOCATOR_USING_STDATOMIC
    _Atomic(int32_t) refCount;
#else
    int32_t refCount;
#endif
    CCMemoryDestructorCallback destructor;
} CCAllocatorHeader;


void CCAllocatorAdd(int Index, CCAllocatorFunction Allocator, CCReallocatorFunction Reallocator, CCDeallocatorFunction Deallocator);
CC_NEW void *CCMemoryAllocate(CCAllocatorType Type, size_t Size);
CC_NEW void *CCMemoryReallocate(CCAllocatorType Type, void *CC_DESTROY(Ptr), size_t Size);
CC_NEW void *CCMemoryRetain(void *Ptr);
void CCMemoryDeallocate(void *CC_DESTROY(Ptr));
CCMemoryDestructorCallback CCMemorySetDestructor(void *Ptr, CCMemoryDestructorCallback Destructor);


#ifndef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_STD_ALLOCATOR
#endif


#if CC_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>

CFAllocatorRef CCCreateCFAllocator(CCAllocatorType Type);
CFAllocatorRef CCDefaultCFAllocator(void); //Uses the CC_DEFAULT_ALLOCATOR
#endif

#endif
