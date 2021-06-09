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

#include <CommonC/Base.h>
#include <CommonC/Platform.h>
#include <CommonC/Ownership.h>
#include <CommonC/DebugAllocator.h>

typedef struct CCAllocatorType {
    int allocator; //the allocator to be used
    void *data; //additional data to be passed to that allocator
} CCAllocatorType;

#define CC_NULL_ALLOCATOR (CCAllocatorType){ .allocator = -1 } //No allocation
#define CC_STD_ALLOCATOR (CCAllocatorType){ .allocator = 0 } //Uses stdlib
#define CC_CUSTOM_ALLOCATOR(alloc, realloc, dealloc) (CCAllocatorType){ .allocator = 1, .data = (void*[3]){ alloc, realloc, dealloc } }
#define CC_CALLBACK_ALLOCATOR(callback) (CCAllocatorType){ .allocator = 2, .data = callback } //Uses stdlib
#define CC_ALIGNED_ALLOCATOR(alignment) (CCAllocatorType){ .allocator = 3, .data = &(size_t){ alignment } } //Uses stdlib
#define CC_BOUNDS_CHECK_ALLOCATOR (CCAllocatorType){ .allocator = 4 } //Uses stdlib
#define CC_DEBUG_ALLOCATOR (CCAllocatorType){ .allocator = 5, .data = &(CCDebugAllocatorInfo){ .line = __LINE__, .file = __FILE__ } } //Uses stdlib
#define CC_STATIC_ALLOCATOR (CCAllocatorType){ .allocator = 6 } //No allocation (requires static memory)

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

#if CC_ALLOCATOR_USING_STDATOMIC
#define CC_ALLOCATOR_HEADER_INIT(alloc) (CCAllocatorHeader){ .allocator = alloc, .refCount = ATOMIC_VAR_INIT(0), .destructor = NULL }
#else
#define CC_ALLOCATOR_HEADER_INIT(alloc) (CCAllocatorHeader){ .allocator = alloc, .refCount = 0, .destructor = NULL }
#endif


/*!
 * @brief Add a custom allocator.
 * @param Index The index to be used to reference the allocator.
 * @param Allocator The function to handle allocate.
 * @param Reallocator The function to handle reallocate.
 * @param Deallocator The function to handle deallocate.
 */
void CCAllocatorAdd(int Index, CCAllocatorFunction Allocator, CCReallocatorFunction Reallocator, CCDeallocatorFunction Deallocator);

/*!
 * @brief Allocate some memory.
 * @param Type The allocator type information to be used.
 * @param Size The amount of memory to be allocated.
 * @return The pointer to the new memory allocation. A subsequent call must be made to
 *         @b CCMemoryDeallocate in order to release the reference/free the memory.
 */
CC_NEW void *CCMemoryAllocate(CCAllocatorType Type, size_t Size);

/*!
 * @brief Reallocate the memory allocation.
 * @param Type The allocator type information to be used.
 * @param Ptr The pointer to the memory allocation.
 * @param Size The amount of memory to be allocated.
 * @return The pointer to the new memory allocation. A subsequent call must be made to
 *         @b CCMemoryDeallocate in order to release the reference/free the memory.
 */
CC_NEW void *CCMemoryReallocate(CCAllocatorType Type, void *CC_DESTROY(Ptr), size_t Size);

/*!
 * @brief Retain a reference to the memory allocation.
 * @description The function is threadsafe.
 * @param Ptr The pointer to the memory allocation.
 * @return The pointer to the memory allocation (or Ptr). A subsequent call must be made to
 *         @b CCMemoryDeallocate in order to release the reference/free the memory.
 */
CC_NEW void *CCMemoryRetain(void *Ptr);

/*!
 * @brief Get the number of retained references to the memory allocation.
 * @description The function is threadsafe.
 * @param Ptr The pointer to the memory allocation.
 * @return The number of references to this memory allocation.
 */
int32_t CCMemoryRefCount(void *Ptr);

/*!
 * @brief Deallocate the memory allocation.
 * @description Releases a reference to the memory, once all references to the memory have been
 *              released the memory is deallocated. This function is threadsafe.
 *
 * @param Ptr The pointer to the memory allocation.
 */
void CCMemoryDeallocate(void *CC_DESTROY(Ptr));

/*!
 * @brief Set a destructor callback for the memory allocation.
 * @description The callback will be called on deallocation.
 * @param Ptr The pointer to the memory allocation.
 * @param Destructor The destructor callback.
 * @return The previous destructor callback.
 */
CCMemoryDestructorCallback CCMemorySetDestructor(void *Ptr, CCMemoryDestructorCallback Destructor);


#ifndef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_STD_ALLOCATOR
#endif


#if CC_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>

/*!
 * @brief Create a CoreFoundation object allocator that uses one of the provided allocators.
 * @param Type The allocator type information to be used.
 * @return The CFAllocator reference.
 */
CFAllocatorRef CCCreateCFAllocator(CCAllocatorType Type);

/*!
 * @brief Create a CoreFoundation object allocator that uses the allocator specified by the
 *        @b CC_DEFAULT_ALLOCATOR define.
 *
 * @return The CFAllocator reference.
 */
CFAllocatorRef CCDefaultCFAllocator(void); //Uses the CC_DEFAULT_ALLOCATOR
#endif


#include <CommonC/Hacks.h>

#define CC_STATIC_ALLOC(...) CC_VA_CALL(CC_STATIC_ALLOC_, __VA_ARGS__)

#define CC_STATIC_ALLOC_1(type) \
((void*)&(struct { \
    size_t size; \
    CCAllocatorHeader header; \
    typeof(type) ptr; \
}){ \
    .size = sizeof(CCAllocatorHeader) + sizeof(type), \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_STATIC_ALLOCATOR.allocator) \
}.ptr)

#define CC_STATIC_ALLOC_2(type, init) \
((void*)&(struct { \
    size_t size; \
    CCAllocatorHeader header; \
    typeof(type) ptr; \
}){ \
    .size = sizeof(CCAllocatorHeader) + sizeof(type), \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_STATIC_ALLOCATOR.allocator), \
    .ptr = CC_STATIC_ALLOC_CONSUME init \
}.ptr)

#define CC_STATIC_ALLOC_CONSUME(...) __VA_ARGS__

#endif
