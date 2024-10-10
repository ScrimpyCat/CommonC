/*
 *  Copyright (c) 2024, Stefan Johnson
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

/*
 A wait-free swap buffer implementation.
 Allows for single producer-single consumer access.
 
 This is a low level interface and should only be used in specific use case.
 */

#include <CommonC/Template.h>

#define CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG 0x80

#define CC_CONCURRENT_SWAP_BUFFER_INIT { .index = ATOMIC_VAR_INIT(0), .write = 1, .read = 2 }

#define CCConcurrentSwapBufferGetFuture_T(t) CC_TEMPLATE_REF(CCConcurrentSwapBufferGetFuture, PTYPE(void *), PTYPE(t *))
#define CCConcurrentSwapBufferApply_T(t) CC_TEMPLATE_REF(CCConcurrentSwapBufferApply, void, PTYPE(t *))
#define CCConcurrentSwapBufferRead_T(t) CC_TEMPLATE_REF(CCConcurrentSwapBufferRead, const PTYPE(void *), PTYPE(t *))

#undef CCConcurrentSwapBuffer

/*!
 * @brief Get the future buffer to be swapped.
 * @warning If reading from this buffer on a different thread than the writer, an acquire memory barrier must be used.
 * @param Buffer The concurrent swap buffer.
 * @return A pointer to the future buffer.
 */
CC_TEMPLATE(static CC_FORCE_INLINE PTYPE(void *), CCConcurrentSwapBufferGetFuture, (PTYPE(T *) Buffer));

/*!
 * @brief Apply the future buffer.
 * @param Buffer The concurrent swap buffer.
 */
CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentSwapBufferApply, (PTYPE(T *) Buffer));

/*!
 * @brief Read from the last applied buffer.
 * @param Buffer The concurrent swap buffer.
 * @return The pointer to the last applied buffer.
 */
CC_TEMPLATE(static CC_FORCE_INLINE const PTYPE(void *), CCConcurrentSwapBufferRead, (PTYPE(T *) Buffer));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE PTYPE(void *), CCConcurrentSwapBufferGetFuture, (PTYPE(T *) Buffer))
{
    return &Buffer->buffer[Buffer->write];
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentSwapBufferApply, (PTYPE(T *) Buffer))
{
    size_t Next = atomic_load_explicit(&Buffer->index, memory_order_relaxed);
    
    if (Next & CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG)
    {
        Next = atomic_exchange_explicit(&Buffer->index, Buffer->write | CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG, memory_order_release);
    }
    
    else
    {
        atomic_store_explicit(&Buffer->index, Buffer->write | CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG, memory_order_release);
    }
    
    Buffer->write = Next & ~CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG;
}

CC_TEMPLATE(static CC_FORCE_INLINE const PTYPE(void *), CCConcurrentSwapBufferRead, (PTYPE(T *) Buffer))
{
    size_t Index = Buffer->read;
    
    if (atomic_load_explicit(&Buffer->index, memory_order_relaxed) & CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG)
    {
        Index = atomic_exchange_explicit(&Buffer->index, Index, memory_order_consume) ^ CC_CONCURRENT_SWAP_BUFFER_MODIFIED_FLAG;
        
        Buffer->read = Index;
    }
    
    return &Buffer->buffer[Index];
}

#define CCConcurrentSwapBuffer(type) CC_CONCURRENT_SWAP_BUFFER(type)
