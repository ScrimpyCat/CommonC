/*
 *  Copyright (c) 2017, Stefan Johnson
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

#ifndef CommonC_ConcurrentBuffer_h
#define CommonC_ConcurrentBuffer_h

#include <CommonC/Base.h>
#include <CommonC/Container.h>
#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>


/*!
 * @brief A callback to handle custom destruction of buffer data when it is cleared or destroyed.
 * @param Data The data being destroyed.
 */
typedef void (*CCConcurrentBufferDataDestructor)(void *Data);

/*!
 * @brief The concurrent buffer.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentBufferInfo *CCConcurrentBuffer;

CC_CONTAINER_DECLARE_PRESET_1(CCConcurrentBuffer);

/*!
 * @define CC_CONCURRENT_BUFFER_DECLARE
 * @abstract Convenient macro to define a @b CCConcurrentBuffer type that can be referenced by @b CCConcurrentBuffer.
 * @param data The data type.
 */
#define CC_CONCURRENT_BUFFER_DECLARE(data) CC_CONTAINER_DECLARE(CCConcurrentBuffer, data)

/*!
 * @define CC_CONCURRENT_BUFFER
 * @abstract Convenient macro to define an explicitly typed @b CCConcurrentBuffer.
 * @param data The data type.
 */
#define CC_CONCURRENT_BUFFER(data) CC_CONTAINER(CCConcurrentBuffer, data)

/*!
 * @define CCConcurrentBuffer
 * @abstract Convenient macro to define an explicitly typed @b CCConcurrentBuffer.
 * @description In the case that this macro is conflicting with the standalone @b CCConcurrentBuffer type, simply
 *              undefine it and redefine it back to @b CC_CONCURRENT_BUFFER.
 *
 * @param data The data type.
 */
#define CCConcurrentBuffer(data) CC_CONCURRENT_BUFFER(data)

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent buffer.
 * @description This buffer allows for many producer-consumer access.
 * @param Allocator The allocator to be used for the allocation.
 * @param Destructor The data destructor. May be NULL.
 * @return A buffer, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentBuffer CCConcurrentBufferCreate(CCAllocatorType Allocator, CCConcurrentBufferDataDestructor Destructor);

/*!
 * @brief Destroy the buffer.
 * @param Buffer The buffer to be destroyed.
 */
void CCConcurrentBufferDestroy(CCConcurrentBuffer CC_DESTROY(Buffer));

#pragma mark - Read/Write
/*!
 * @brief Write data to the buffer.
 * @description Replaces the current contents of the buffer with the new data. The old data is
 *              destroyed.
 *
 * @param Buffer The buffer to be written to.
 * @param Data The data to write to the buffer.
 */
void CCConcurrentBufferWriteData(CCConcurrentBuffer Buffer, void *CC_OWN(Data));

/*!
 * @brief Write data to the buffer and returns the previous buffer.
 * @description Replaces the current contents of the buffer with the new data. The old data is
 *              returned. This variant should be used instead of @b CCConcurrentBufferWriteData
 *              whenever you want to manually handle the destruction of the data, or need to
 *              inspect what the previous write data was.
 *
 * @param Buffer The buffer to be written to.
 * @param Data The data to write to the buffer.
 * @return The previous write data in the buffer, or NULL if there was no data. Must be destroyed
 *         to free the memory.
 */
CC_NEW void *CCConcurrentBufferWriteDataSwap(CCConcurrentBuffer Buffer, void *CC_OWN(Data));

/*!
 * @brief Read data from the buffer.
 * @description Replaces the current contents of the buffer with NULL.
 * @param Buffer The buffer to be read from.
 * @return The data read from the buffer, or NULL if there was no data. Must be destroyed to
 *         free the memory.
 */
CC_NEW void *CCConcurrentBufferReadData(CCConcurrentBuffer Buffer);

#pragma mark - Query

/*!
 * @brief Get the data destructor from the buffer.
 * @param Buffer The buffer to get the data destructor from.
 * @return The data destructor, or NULL if none was set during creation.
 */
CCConcurrentBufferDataDestructor CCConcurrentBufferGetDataDestructor(CCConcurrentBuffer Buffer);

#endif
