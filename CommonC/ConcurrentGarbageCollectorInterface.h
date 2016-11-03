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

#ifndef CommonC_ConcurrentGarbageCollectorInterface_h
#define CommonC_ConcurrentGarbageCollectorInterface_h

#include <CommonC/Allocator.h>

/*!
 * @brief The function used when reclaiming the item.
 */
typedef void (*CCConcurrentGarbageCollectorReclaimer)(void*);


#pragma mark - Required Callbacks
/*!
 * @brief A callback to create the internal implementation for the garbage collector.
 * @param Allocator The allocator to be used for the creation.
 * @return The created internal structure.
 */
typedef void *(*CCConcurrentGarbageCollectorConstructorCallback)(CCAllocatorType Allocator);

/*!
 * @brief A callback to destroy the internal implementation for the garbage collector.
 * @param Internal The pointer to the internal of the garbage collector.
 */
typedef void (*CCConcurrentGarbageCollectorDestructorCallback)(void *Internal);

/*!
 * @brief A callback to start collecting.
 * @description Any managed pointers added or accessed in this section must be safe.
 * @param Internal The pointer to the internal of the garbage collector.
 * @param Allocator The allocator to be used for any internal allocations.
 */
typedef void (*CCConcurrentGarbageCollectorBeginCallback)(void *Internal, CCAllocatorType Allocator);

/*!
 * @brief A callback to stop collecting.
 * @param Internal The pointer to the internal of the garbage collector.
 * @param Allocator The allocator to be used for any internal allocations.
 */
typedef void (*CCConcurrentGarbageCollectorEndCallback)(void *Internal, CCAllocatorType Allocator);

/*!
 * @brief A callback to add a pointer to be managed by the garbage collector.
 * @param Internal The pointer to the internal of the garbage collector.
 * @param Item The item to be managed.
 * @param Reclaimer The function to be called when the item can be reclaimed (destroyed).
 * @param Allocator The allocator to be used for any internal allocations.
 */
typedef void (*CCConcurrentGarbageCollectorManageCallback)(void *Internal, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer, CCAllocatorType Allocator);


#pragma mark -

/*!
 * @brief The interface to the internal implementation.
 */
typedef struct {
    CCConcurrentGarbageCollectorConstructorCallback create;
    CCConcurrentGarbageCollectorDestructorCallback destroy;
    CCConcurrentGarbageCollectorBeginCallback begin;
    CCConcurrentGarbageCollectorEndCallback end;
    CCConcurrentGarbageCollectorManageCallback manage;
} CCConcurrentGarbageCollectorInterface;

#endif
