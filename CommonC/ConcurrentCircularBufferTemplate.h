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
 A wait-free FIFO buffer implementation.
 Allows for single produer-single consumer access.
 
 This is a low level interface and should only be used in specific use case.
 The buffer is a fixed size and will fail to add more items once full.
 
 The intended usage for this structure is when a consumer will constantly clear out the buffer, and wants to process many items
 in one go.
*/

#include <CommonC/Template.h>
#include <CommonC/Enumerable.h>
#include <CommonC/CircularEnumerable.h>

#define CC_CONCURRENT_CIRCULAR_BUFFER_INIT { .head = ATOMIC_VAR_INIT(0), .tail = ATOMIC_VAR_INIT(0) }

#define CCConcurrentCircularBufferGetEnumerable_T(t) CC_TEMPLATE_REF(CCConcurrentCircularBufferGetEnumerable, void, PTYPE(t *), PTYPE(CCEnumerable *))
#define CCConcurrentCircularBufferRelease_T(t) CC_TEMPLATE_REF(CCConcurrentCircularBufferRelease, void, PTYPE(t *), PTYPE(CCEnumerable *))
#define CCConcurrentCircularBufferAddItem_T(t) CC_TEMPLATE_REF(CCConcurrentCircularBufferAddItem, _Bool, PTYPE(t *), const PTYPE(void *))
#define CCConcurrentCircularBufferAddItems_T(t) CC_TEMPLATE_REF(CCConcurrentCircularBufferAddItems, size_t, PTYPE(t *), const PTYPE(void *), size_t)

#undef CCConcurrentCircularBuffer

/*!
 * @brief Get the item enumerable from the circular buffer.
 * @description The enumerable may be used by many threads, but should not be used after a thread releases it.
 * @param Buffer The concurrent circular buffer.
 * @param Enumerable A pointer to where the enumerable should be stored.
 */
CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentCircularBufferGetEnumerable, (PTYPE(T *) Buffer, PTYPE(CCEnumerable *) Enumerable));

/*!
 * @brief Release the items in the enuemrable.
 * @warning The enumerable should not be used after.
 * @param Buffer The concurrent circular buffer.
 * @param Enumerable A pointer to the enumerable to be released.
 */
CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentCircularBufferRelease, (PTYPE(T *) Buffer, PTYPE(CCEnumerable *) Enumerable));

/*!
 * @brief Add an item to the circular buffer.
 * @param Buffer The concurrent circular buffer.
 * @param Item A pointer to the item that should be added to the circular buffer.
 * @return Whether the item was successfully addded (TRUE), or not (FALSE). If it was not, it means that the buffer is
 *         currently full.
 */
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCConcurrentCircularBufferAddItem, (PTYPE(T *) Buffer, const PTYPE(void *) Item));

/*!
 * @brief Add items to the circular buffer.
 * @param Buffer The concurrent circular buffer.
 * @param Items A pointer to the items that should be added to the circular buffer.
 * @param Count The number of items to be added.
 * @return The number of items successfully added. If some items were not added it means that the buffer is currently full.
 */
CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCConcurrentCircularBufferAddItems, (PTYPE(T *) Buffer, const PTYPE(void *) Items, size_t Count));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentCircularBufferGetEnumerable, (PTYPE(T *) Buffer, PTYPE(CCEnumerable *) Enumerable))
{
    const size_t Head = atomic_load_explicit(&Buffer->head, memory_order_relaxed);
    const size_t Tail = atomic_load_explicit(&Buffer->tail, memory_order_acquire);
    const size_t Count = Head <= Tail ? Tail - Head : Tmax - (Head - Tail);
    
    *Enumerable = CCCircularEnumerableCreate(Buffer->items, sizeof(Titem), Count, Head, Tmax);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentCircularBufferRelease, (PTYPE(T *) Buffer, PTYPE(CCEnumerable *) Enumerable))
{
    CCAssertLog((Enumerable->enumerator.ref == Buffer->items) && ((Enumerable->enumerator.state.type & CCEnumeratorFormatMask) == CCEnumeratorFormatCircular), "Enumerable should be the circular buffer enumerable");
    
    atomic_signal_fence(memory_order_release);
    
    atomic_store_explicit(&Buffer->head,  (Enumerable->enumerator.state.circular.start + Enumerable->enumerator.state.circular.count) % Tmax, memory_order_relaxed);
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCConcurrentCircularBufferAddItem, (PTYPE(T *) Buffer, const PTYPE(void *) Item))
{
    const size_t Head = atomic_load_explicit(&Buffer->head, memory_order_relaxed);
    const size_t Tail = atomic_load_explicit(&Buffer->tail, memory_order_relaxed);
    const size_t Next = (Tail + 1) % Tmax;
    
    if (Next != Head)
    {
        Buffer->items[Tail] = *(const Titem*)Item;
        
        atomic_store_explicit(&Buffer->tail, Next, memory_order_release);
        
        return TRUE;
    }
    
    return FALSE;
}

CC_TEMPLATE(static CC_FORCE_INLINE size_t, CCConcurrentCircularBufferAddItems, (PTYPE(T *) Buffer, const PTYPE(void *) Items, size_t Count))
{
    const size_t Head = atomic_load_explicit(&Buffer->head, memory_order_relaxed);
    size_t Tail = atomic_load_explicit(&Buffer->tail, memory_order_relaxed);
    const size_t AvailableCount = Tmax - (Head <= Tail ? Tail - Head : Tmax - (Head - Tail)) - 1;
    
    Count = CCMin(AvailableCount, Count);
    
    if (Count)
    {
        for (size_t Loop = 0; Loop < Count; Loop++)
        {
            Buffer->items[Tail] = ((const Titem*)Items)[Loop];
            
            Tail = (Tail + 1) % Tmax;
        }
        
        atomic_store_explicit(&Buffer->tail, Tail, memory_order_release);
    }
    
    return Count;
}

#define CCConcurrentCircularBuffer(type, size) CC_CONCURRENT_CIRCULAR_BUFFER(type, size)
