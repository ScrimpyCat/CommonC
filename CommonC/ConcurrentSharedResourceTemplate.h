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
 A lock-free or optionally wait-free shared resource implementation.
 Allows for many producer-consumer access.
 
 This is a low level interface and should only be used in specific use cases.
 
 Get operations are always wait-free unless Tunlimited is set to true.
 
 Set operations are lock-free unless the max resource size is equal to or greater than the number of threads that will access
 the structure.
 
 Tunlimited should be used when we don't know how many get operations may occur before the next set operation.
 
 The intended usage for this structure is when we want to share a replaceable resource. A resource is ideally some data that
 has ownership constraints, or data that is too large to be shared atomically. When a thread gets the resource it is guaranteed
 to be the latest resource at that point in time, but after that point there is no guarantees that the resource is still the
 latest.
*/

#include <CommonC/Template.h>

#define CC_CONCURRENT_SHARED_RESOURCE_INIT { .nodes = { { .refs = ATOMIC_VAR_INIT(1) } } }

#define CCConcurrentSharedResourceSet_T(t) CC_TEMPLATE_REF(CCConcurrentSharedResourceSet, void, PTYPE(t *), PRIVATE(Titem, item))
#define CCConcurrentSharedResourceGet_T(t) CC_TEMPLATE_REF(CCConcurrentSharedResourceGet, PRIVATE(Titem, item), PTYPE(t *))

#undef CCConcurrentSharedResource

/*!
 * @brief Set the resource to share.
 * @description This operation is wait-free if Tmax is greater than or equal to the number of threads that will access the
 *              structure, otherwise it will be lock-free.
 *
 * @param SharedResource The concurrent shared resource.
 * @param Data The data to share. Ownership is passed to the function, so the caller should not continue to access the
 *              data unless it ensure that it has the right to (e.g. retained or copied).
 */
CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentSharedResourceSet, (PTYPE(T *) SharedResource, PRIVATE(Titem, item) Data));

/*!
 * @brief Get the current resource.
 * @description This operation is wait-free if Tunlimited was set to false, otherwise it will be lock-free.
 * @param SharedResource The concurrent shared resource.
 * @return The resource. Ownership is passed to the caller, so the caller is responsible for its lifetime.
 */
CC_TEMPLATE(static CC_FORCE_INLINE PRIVATE(Titem, item), CCConcurrentSharedResourceGet, (PTYPE(T *) SharedResource));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentSharedResourceSet, (PTYPE(T *) SharedResource, PRIVATE(Titem, item) Data))
{
    size_t Index = ((atomic_load_explicit(&SharedResource->current, memory_order_relaxed) >> 16) + 1) % Tmax;
    while (atomic_load_explicit(&SharedResource->nodes[Index].refs, memory_order_relaxed) || !atomic_compare_exchange_strong_explicit(&SharedResource->nodes[Index].refs, &(size_t){ 0 }, 1, memory_order_acquire, memory_order_relaxed)) Index = (Index + 1) % Tmax;
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused"
    Titem StaleData = SharedResource->nodes[Index].data;
#pragma clang diagnostic pop
    
    SharedResource->nodes[Index].data = Data;
    
    const size_t Prev = atomic_exchange_explicit(&SharedResource->current, Index << 16, memory_order_release);
    const size_t PrevIndex = Prev >> 16, PrevCount = (Prev & 0xffff) << 1;
    
    atomic_fetch_sub_explicit(&SharedResource->nodes[PrevIndex].refs, PrevCount | 1, memory_order_relaxed);
    
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused"
    Tdestructor(StaleData);
#pragma clang diagnostic pop
}

CC_TEMPLATE(static CC_FORCE_INLINE PRIVATE(Titem, item), CCConcurrentSharedResourceGet, (PTYPE(T *) SharedResource))
{
    size_t Index = atomic_fetch_add_explicit(&SharedResource->current, 1, memory_order_acquire) >> 16;
    
    Titem Data = Tshare(SharedResource->nodes[Index].data);
    
    atomic_signal_fence(memory_order_release);
    
    atomic_fetch_add_explicit(&SharedResource->nodes[Index].refs, 2, memory_order_relaxed);
    
    if (Tunlimited)
    {
        size_t Current = atomic_load_explicit(&SharedResource->current, memory_order_relaxed);
        
        while((Current >> 16) == Index)
        {
           if (atomic_compare_exchange_strong_explicit(&SharedResource->current, &Current, Current - 1, memory_order_relaxed, memory_order_relaxed))
           {
               atomic_fetch_sub_explicit(&SharedResource->nodes[Index].refs, 2, memory_order_relaxed);
               break;
           }
        }
    }
    
    return Data;
}

#define CCConcurrentSharedResource(type, size, share, destructor, unlimited) CC_CONCURRENT_SHARED_RESOURCE(type, size, share, destructor, unlimited)
