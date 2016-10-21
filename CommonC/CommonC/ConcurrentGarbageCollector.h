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

#ifndef CommonC_ConcurrentGarbageCollector_h
#define CommonC_ConcurrentGarbageCollector_h

#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>

typedef void (*CCConcurrentGarbageCollectorReclaimer)(void*);

/*!
 * @brief The garbage collector.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentGarbageCollectorInfo *CCConcurrentGarbageCollector;

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent garbage collector.
 * @param Allocator The allocator to be used for the allocation.
 * @return A garbage collector, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentGarbageCollector CCConcurrentGarbageCollectorCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a garbage collector.
 * @warning All usage by other threads must have finish before final destruction.
 * @param GC The garbage collector to be destroyed.
 */
void CCConcurrentGarbageCollectorDestroy(CCConcurrentGarbageCollector CC_DESTROY(GC));

/*!
 * @brief Start collecting.
 * @description Any managed pointers added or accessed in this section is safe.
 * @param GC The garbage collector to be used.
 */
void CCConcurrentGarbageCollectorBegin(CCConcurrentGarbageCollector GC);

/*!
 * @brief Stop collecting.
 * @param GC The garbage collector to be used.
 */
void CCConcurrentGarbageCollectorEnd(CCConcurrentGarbageCollector GC);

/*!
 * @brief Add a pointer to be managed by the garbage collector.
 * @param GC The garbage collector to be used.
 * @param Item The item to be managed.
 * @param Reclaimer The function to be called when the item can be reclaimed (destroyed).
 */
void CCConcurrentGarbageCollectorManage(CCConcurrentGarbageCollector GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer);

#endif
