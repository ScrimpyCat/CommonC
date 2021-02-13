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

#ifndef CommonC_DataContainer_h
#define CommonC_DataContainer_h

#include <CommonC/Base.h>
#include <CommonC/Data.h>
#include <CommonC/Enumerable.h>

/*!
 * @brief A callback to handle retrieving the element count of the container.
 * @param Container The container.
 * @return The number of elements.
 */
typedef size_t (*CCDataContainerCount)(const void *Container);

/*!
 * @brief A callback to handle retrieving the enumerable for the container.
 * @param Container The container.
 * @param Enumerable The enumerable for the container.
 */
typedef void (*CCDataContainerEnumerable)(const void *Container, CCEnumerable *Enumerable);

/*!
 * @typedef CCDataContainerHint
 * @brief Hints specific to CCDataContainer.
 */
CC_EXTENSIBLE_FLAG_ENUM(uint32_t) {
    ///Mask for hints for a data container.
    CCDataContainerHintMask = 0xff00,
    CCDataContainerHintFree = (1 << 8)
};

typedef CCDataHint CCDataContainerHint;

typedef struct {
    const void *container;
    size_t elementSize;
    CCDataContainerCount count;
    CCDataContainerEnumerable enumerable;
} CCDataContainerInit;

extern const CCDataInterface * const CCDataContainer;

/*!
 * @brief Create a data container for generic enumerable containers.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this data container.
 * @param ElementSize The size of the elements in the @p Container.
 * @param Count The callback to retrieve the number of elements in the @p Container. May be NULL,
 *        in which case the count is inferred from the enumerable. If the count differs from the
 *        true number of elements in the container then reads and writes will be limited to the
 *        size of the count, or if the count is larger than the container then the data will be
 *        unused.
 *
 * @param Enumerable The callback to retrieve the enumerable for the @p Container, must not be
 *        NULL.
 *
 * @param Container The generic enumerable container to be stored in the data container, must not be
 *        NULL. See @p Hint for behaviour.
 *
 * @param Hash An optional hashing function to be performed instead of the default for the internal
 *        implementation.
 *
 * @param Destructor An optional destructor to perform any custom cleanup on destroy.
 * @return A data container, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCData CCDataContainerCreate(CCAllocatorType Allocator, CCDataContainerHint Hint, size_t ElementSize, CCDataContainerCount Count, CCDataContainerEnumerable Enumerable, const void *CC_RETAIN(Container), CCDataBufferHash Hash, CCDataBufferDestructor Destructor);

#endif
