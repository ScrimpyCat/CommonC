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
 * @brief Read data from the buffer.
 * @description Replaces the current contents of the buffer with NULL.
 * @param Buffer The buffer to be read from.
 * @return The data read from the buffer, or NULL if there was no data. Must be destroyed to
 *         free the memory.
 */
CC_NEW void *CCConcurrentBufferReadData(CCConcurrentBuffer Buffer);

#endif
