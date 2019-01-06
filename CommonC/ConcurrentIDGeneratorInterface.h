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

#ifndef CommonC_ConcurrentIDGeneratorInterface_h
#define CommonC_ConcurrentIDGeneratorInterface_h

#include <CommonC/Allocator.h>

#pragma mark - Required Callbacks
/*!
 * @brief A callback to create the internal implementation for the ID generator.
 * @param Allocator The allocator to be used for the creation.
 * @param Count The number of IDs the generator should be able to provide.
 * @return The created internal structure.
 */
typedef void *(*CCConcurrentIDGeneratorConstructorCallback)(CCAllocatorType Allocator, size_t Count);

/*!
 * @brief A callback to destroy the internal implementation for the ID generator.
 * @param Internal The pointer to the internal of the ID generator.
 */
typedef void (*CCConcurrentIDGeneratorDestructorCallback)(void *Internal);

/*!
 * @brief A callback to obtain an ID from the ID generator.
 * @param Internal The pointer to the internal of the ID generator.
 * @return The ID that has been assigned. This ID must not be assigned again until it has been recycled.
 */
typedef uintptr_t (*CCConcurrentIDGeneratorAssignCallback)(void *Internal);

/*!
 * @brief A callback to try obtain an ID from the ID generator.
 * @param Internal The pointer to the internal of the ID generator.
 * @param ID The pointer to where the assigned ID should be stored. This ID must not be assigned again until
 *        it has been recycled. This will not be NULL.
 *
 * @return Whether an ID was assigned (TRUE), or not (FALSE).
 */
typedef _Bool (*CCConcurrentIDGeneratorTryAssignCallback)(void *Internal, uintptr_t *ID);

/*!
 * @brief A callback to make an ID available again.
 * @param Internal The pointer to the internal of the ID generator.
 * @param ID The ID to be recycled.
 */
typedef void (*CCConcurrentIDGeneratorRecycleCallback)(void *Internal, uintptr_t ID);

/*!
 * @brief A callback to get the max ID this generator may assign.
 * @param Internal The pointer to the internal of the ID generator.
 * @return The max ID it may assign.
 */
typedef uintptr_t (*CCConcurrentIDGeneratorGetMaxIDCallback)(void *Internal);


#pragma mark -

/*!
 * @brief The interface to the internal implementation.
 */
typedef struct {
    CCConcurrentIDGeneratorConstructorCallback create;
    CCConcurrentIDGeneratorDestructorCallback destroy;
    CCConcurrentIDGeneratorAssignCallback assign;
    CCConcurrentIDGeneratorTryAssignCallback try;
    CCConcurrentIDGeneratorRecycleCallback recycle;
    CCConcurrentIDGeneratorGetMaxIDCallback max;
} CCConcurrentIDGeneratorInterface;

#endif
