/*
 *  Copyright (c) 2015, Stefan Johnson
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

#ifndef CommonC_DataBuffer_h
#define CommonC_DataBuffer_h

#include <CommonC/Base.h>
#include <CommonC/Data.h>

/*!
 * @typedef CCDataBufferHint
 * @brief Hints specific to CCDataBuffer.
 */
CC_EXTENSIBLE_FLAG_ENUM(uint32_t) {
    ///Mask for hints for a data container.
    CCDataBufferHintMask = 0xff00,
    CCDataBufferHintFree = (1 << 8),
    CCDataBufferHintCopy = (1 << 9) | CCDataBufferHintFree
};

typedef CCDataHint CCDataBufferHint;

typedef struct {
    const void *buffer;
    size_t size;
} CCDataBufferInit;

extern const CCDataInterface * const CCDataBuffer;

/*!
 * @brief Create a data container for regular heap memory.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this data container.
 *
 *        @b CCDataBufferHintCopy indicates that the input @p Buffer should be copied.
 *
 *        @b CCDataBufferHintFree indicates that the input @p Buffer should be freed on destroy.
 *
 *        Otherwise will just hold a weak reference to the input @p Buffer.
 *
 * @param Size The size of the @p Buffer.
 * @param Buffer The buffer to be stored in the container, must not be NULL. See @p Hint for behaviour.
 * @param Hash An optional hashing function to be performed instead of the default for the internal
 *        implementation.
 *
 * @param Destructor An optional destructor to perform any custom cleanup on destroy.
 * @return A data buffer, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCData CCDataBufferCreate(CCAllocatorType Allocator, CCDataBufferHint Hint, size_t Size, const void *Buffer, CCDataBufferHash Hash, CCDataBufferDestructor Destructor);

#endif
