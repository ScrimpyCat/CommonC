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

#ifndef CommonC_ConcurrentIndexBuffer_h
#define CommonC_ConcurrentIndexBuffer_h

#include <CommonC/Base.h>
#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>

/*!
 * @brief The concurrent index buffer.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentIndexBufferInfo *CCConcurrentIndexBuffer;

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent index buffer.
 * @description This buffer allows for many producer-consumer access.
 * @param Allocator The allocator to be used for the allocation.
 * @param Count The number of indexes available. Ideally this should be the number of threads that will
 *        access it + 1. If you cannot know how many threads may be using it, then a @b CCConcurrentBuffer
 *        would likely be better.
 *
 * @return An index buffer, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentIndexBuffer CCConcurrentIndexBufferCreate(CCAllocatorType Allocator, size_t Count);

/*!
 * @brief Destroy the index buffer.
 * @param IndexBuffer The index buffer to be destroyed.
 */
void CCConcurrentIndexBufferDestroy(CCConcurrentIndexBuffer CC_DESTROY(IndexBuffer));

#pragma mark - Read/Write
/*!
 * @brief Acquire a write index.
 * @performance If all the indexes have been acquired, this operation will block.
 * @param IndexBuffer The index buffer to acquire a write index from.
 * @return The index that may be used by a write action. This index must be
 *         released using @b CCConcurrentIndexBufferStage in order to make it available
 *         to read (or future writes), or @b CCConcurrentIndexBufferDiscard in order to
 *         discard the write and make it available to other writers.
 */
size_t CCConcurrentIndexBufferWriteAcquire(CCConcurrentIndexBuffer IndexBuffer);

/*!
 * @brief Acquire a read index if one is available.
 * @performance This operation is wait-free.
 * @param IndexBuffer The index buffer to acquire a read index from.
 * @param Index A pointer to where the index should be written to, if was acquired. If an index
 *              was acquired it must be released using @b CCConcurrentIndexBufferDiscard in order
 *              to make it available to writers again, or @b CCConcurrentIndexBufferStage in order
 *              to make it available to read (or future writes).
 *
 * @return Whether a read index was acquired (TRUE) or not (FALSE).
 */
_Bool CCConcurrentIndexBufferReadAcquire(CCConcurrentIndexBuffer IndexBuffer, size_t *Index);

/*!
 * @brief Release an index and make it available for reading (replacing the previous index).
 * @performance This operation is wait-free.
 * @param IndexBuffer The index buffer to release an index to.
 * @param Index The index to be released.
 */
void CCConcurrentIndexBufferStage(CCConcurrentIndexBuffer IndexBuffer, size_t Index);

/*!
 * @brief Release an index and do not make it available for reading.
 * @performance This operation is wait-free.
 * @param IndexBuffer The index buffer to release an index to.
 * @param Index The index to be released.
 */
void CCConcurrentIndexBufferDiscard(CCConcurrentIndexBuffer IndexBuffer, size_t Index);

#endif
