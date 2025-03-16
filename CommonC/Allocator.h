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
    int32_t allocator; //the allocator to be used
    void *data; //additional data to be passed to that allocator. Must ensure the lifetime of that data extends past the lifetime of the allocation.
} CCAllocatorType;

typedef struct {
    size_t current;
    size_t count;
    CCAllocatorType allocators[];
} CCAllocatorGroup;


#define CC_ALLOCATORS(...) ((CCAllocatorType){ .allocator = -2, &(union { CCAllocatorGroup group; struct { size_t current; size_t count; CCAllocatorType allocators[CC_VA_ARG_COUNT(__VA_ARGS__)]; } internal; }){ .internal = { .current = 0, .count = CC_VA_ARG_COUNT(__VA_ARGS__), .allocators = { __VA_ARGS__ } } }.group }) //Array of allocators to apply a unique one to each child allocation. The last allocator is used for all remaining allocations.
#define CC_NULL_ALLOCATOR ((CCAllocatorType){ .allocator = -1 }) //No allocation
#define CC_STATIC_ALLOCATOR ((CCAllocatorType){ .allocator = 0 }) //No allocation (requires static memory)
#define CC_STD_ALLOCATOR ((CCAllocatorType){ .allocator = 1 }) //Uses stdlib
#define CC_CUSTOM_ALLOCATOR(alloc, realloc, dealloc) ((CCAllocatorType){ .allocator = 2, .data = (void*[3]){ alloc, realloc, dealloc } })
#define CC_CALLBACK_ALLOCATOR(callback) ((CCAllocatorType){ .allocator = 3, .data = callback }) //Uses stdlib
#define CC_ALIGNED_ALLOCATOR(alignment) ((CCAllocatorType){ .allocator = 4, .data = &(size_t){ alignment } }) //Uses stdlib
#define CC_BOUNDS_CHECK_ALLOCATOR ((CCAllocatorType){ .allocator = 5 }) //Uses stdlib
#define CC_DEBUG_ALLOCATOR ((CCAllocatorType){ .allocator = 6, .data = &(CCDebugAllocatorInfo){ .line = __LINE__, .file = __FILE__ } }) //Uses stdlib
#define CC_ZONE_ALLOCATOR(zone) ((CCAllocatorType){ .allocator = 7, .data = zone }) // Uses memory zone
#define CC_AUTORELEASE_ALLOCATOR(zone) ((CCAllocatorType){ .allocator = 8, .data = zone }) // Uses memory zone without retaining
#define CC_POOL_ALLOCATOR(pool) ((CCAllocatorType){ .allocator = 9, .data = pool }) // Uses the memory pool

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
    int32_t allocator;
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

/*!
 * @define CC_STATIC_ALLOC
 * @abstract Convenient macro to statically allocate memory of type.
 * @description A static allocation can be reallocated up to the size of @b type.
 * @param type The type to be allocated.
 * @optional init The data the memory should be initialised with (assignment). Must be
 *           wrapped in parantheses. If this parameter is not passed then the memory is
 *           uninitialised.
 */
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

/*!
 * @define CC_STATIC_ALLOC_BSS
 * @abstract Convenient macro to statically allocate zero-filled memory of type.
 * @note This static allocation can not be reallocated. This is functionally similar to @b CC_NULL_ALLOCATOR
 *       but can be stored in bss section. This is not intented to be used locally.
 *
 * @param type The type to be allocated.
 * @optional init The data the memory should be initialised with (assignment). Must be
 *           wrapped in parantheses.
 */
#define CC_STATIC_ALLOC_BSS(type) \
((void*)&(struct { \
    size_t size; \
    CCAllocatorHeader header; \
    typeof(type) ptr; \
}){ \
    .size = 0, \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_STATIC_ALLOCATOR.allocator), \
    .ptr = {0} \
}.ptr)

#define CC_TYPE_CCAllocatorType(...) CCAllocatorType
#define CC_TYPE_0_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_1_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_2_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_3_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_4_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_5_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_6_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_7_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_8_CCAllocatorType CC_TYPE_CCAllocatorType,
#define CC_TYPE_9_CCAllocatorType CC_TYPE_CCAllocatorType,

#define CC_PRESERVE_CC_TYPE_CCAllocatorType CC_TYPE_CCAllocatorType

#define CC_TYPE_DECL_CCAllocatorType(...) CCAllocatorType, __VA_ARGS__
#define CC_TYPE_DECL_0_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_1_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_2_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_3_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_4_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_5_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_6_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_7_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_8_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,
#define CC_TYPE_DECL_9_CCAllocatorType CC_TYPE_DECL_CCAllocatorType,

#define CC_MANGLE_TYPE_0_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_1_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_2_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_3_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_4_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_5_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_6_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_7_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_8_CCAllocatorType CCAllocatorType
#define CC_MANGLE_TYPE_9_CCAllocatorType CCAllocatorType

#define CC_TYPE_CCMemoryDestructorCallback(...) CCMemoryDestructorCallback
#define CC_TYPE_0_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_1_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_2_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_3_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_4_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_5_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_6_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_7_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_8_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,
#define CC_TYPE_9_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback,

#define CC_PRESERVE_CC_TYPE_CCMemoryDestructorCallback CC_TYPE_CCMemoryDestructorCallback

#define CC_TYPE_DECL_CCMemoryDestructorCallback(...) CCMemoryDestructorCallback, __VA_ARGS__
#define CC_TYPE_DECL_0_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_1_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_2_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_3_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_4_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_5_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_6_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_7_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_8_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,
#define CC_TYPE_DECL_9_CCMemoryDestructorCallback CC_TYPE_DECL_CCMemoryDestructorCallback,

#define CC_MANGLE_TYPE_0_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_1_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_2_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_3_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_4_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_5_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_6_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_7_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_8_CCMemoryDestructorCallback CCMemoryDestructorCallback
#define CC_MANGLE_TYPE_9_CCMemoryDestructorCallback CCMemoryDestructorCallback

#endif
