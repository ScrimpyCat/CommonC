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

#ifndef CommonC_Enumerable_h
#define CommonC_Enumerable_h

#include <CommonC/Enumerator.h>
#include <CommonC/Extensions.h>


/*!
 * @brief The type of action the enumerable handler callback will need to perform.
 */
typedef CC_ENUM(CCEnumerableAction, uint8_t) {
    ///Set the enumerable to the head end of the enumerable and return the value there.
    CCEnumerableActionHead,
    ///Set the enumerable to the tail end of the enumerable and return the value there.
    CCEnumerableActionTail,
    ///Set the enumerable to the next position in the enumerable, and return the value there.
    CCEnumerableActionNext,
    ///Set the enumerable to the previous position in the enumerable, and return the value there.
    CCEnumerableActionPrevious,
    ///Return the value at the current position.
    CCEnumerableActionCurrent
};

/*!
 * @brief A callback to set the enumerator of the enumerable on a given action.
 * @param Enumerator The pointer to the enumerator to be used.
 * @param Action The action to be performed.
 * @return The current value at the new position the enumerator has been set to.
 */
typedef void *(*CCEnumerableHandlerCallback)(CCEnumerator *Enumerator, CCEnumerableAction Action);

/*!
 * @brief An enumerable.
 * @description Provides a generic interface to an enumerator.
 */
typedef struct CCEnumerable {
    CCEnumerableHandlerCallback handler;
    CCEnumerator enumerator;
} CCEnumerable;


/*!
 * @brief Create an enumerable for a contiguous array of values.
 * @param Ptr A pointer to the first value.
 * @param Stride The size of the value.
 * @param Count The number of values.
 * @return The enumerable.
 */
static CC_FORCE_INLINE CCEnumerable CCEnumerableCreate(void *Ptr, size_t Stride, size_t Count);

/*!
 * @brief Get the current value in the enumerable.
 * @param Enumerable The enumerable to get the value from.
 * @return The current value.
 */
static CC_FORCE_INLINE void *CCEnumerableGetCurrent(CCEnumerable *Enumerable);

/*!
 * @brief Set the enumerable to the head.
 * @param Enumerable The enumerable to point to the head.
 * @return The current value.
 */
static CC_FORCE_INLINE void *CCEnumerableGetHead(CCEnumerable *Enumerable);

/*!
 * @brief Set the enumerable to the tail.
 * @param Enumerable The enumerable to point to the tail.
 * @return The current value.
 */
static CC_FORCE_INLINE void *CCEnumerableGetTail(CCEnumerable *Enumerable);

/*!
 * @brief Set the enumerable to the next position.
 * @description Once the enumerable has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerable The enumerable to point to the next value.
 * @return The current value or NULL if it has reached the end.
 */
static CC_FORCE_INLINE void *CCEnumerableNext(CCEnumerable *Enumerable);

/*!
 * @brief Set the enumerable to the previous position.
 * @description Once the enumerable has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerable The enumerable to point to the previous value.
 * @return The current value or NULL if it has reached the end.
 */
static CC_FORCE_INLINE void *CCEnumerablePrevious(CCEnumerable *Enumerable);


void *CCEnumerableHandler(CCEnumerator *Enumerator, CCEnumerableAction Action);

#pragma mark -

static CC_FORCE_INLINE CCEnumerable CCEnumerableCreate(void *Ptr, size_t Stride, size_t Count)
{
    return (CCEnumerable){
        .handler = CCEnumerableHandler,
        .enumerator = {
            .ref = Ptr,
            .state = {
                .batch = {
                    .ptr = Ptr,
                    .count = Count,
                    .stride = Stride,
                    .index = 0
                },
                .type = CCEnumeratorFormatBatch
            }
        }
    };
}

static CC_FORCE_INLINE void *CCEnumerableGetCurrent(CCEnumerable *Enumerable)
{
    switch (Enumerable->enumerator.state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatInternal:
            return Enumerable->handler(&Enumerable->enumerator, CCEnumerableActionCurrent);
            
        case CCEnumeratorFormatFixedBatch:
            return Enumerable->enumerator.state.fixedBatch.count ? Enumerable->enumerator.state.fixedBatch.ptr[Enumerable->enumerator.state.fixedBatch.index] : NULL;
            
        case CCEnumeratorFormatBatch:
            return Enumerable->enumerator.state.batch.count ? Enumerable->enumerator.state.batch.ptr + (Enumerable->enumerator.state.batch.index * Enumerable->enumerator.state.batch.stride) : NULL;
            
        case CCEnumeratorFormatCircular:
            return Enumerable->enumerator.state.circular.count ? Enumerable->enumerator.state.circular.ptr + ((Enumerable->enumerator.state.circular.index % Enumerable->enumerator.state.circular.max) * Enumerable->enumerator.state.circular.stride) : NULL;
    }
    
    return NULL;
}

static CC_FORCE_INLINE void *CCEnumerableGetHead(CCEnumerable *Enumerable)
{
    return Enumerable->handler(&Enumerable->enumerator, CCEnumerableActionHead);
}

static CC_FORCE_INLINE void *CCEnumerableGetTail(CCEnumerable *Enumerable)
{
    return Enumerable->handler(&Enumerable->enumerator, CCEnumerableActionTail);
}

static CC_FORCE_INLINE void *CCEnumerableNext(CCEnumerable *Enumerable)
{
    switch (Enumerable->enumerator.state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatFixedBatch:
            if (Enumerable->enumerator.state.fixedBatch.count == 0) return NULL;
            else if (Enumerable->enumerator.state.fixedBatch.index + 1 < Enumerable->enumerator.state.fixedBatch.count) return Enumerable->enumerator.state.fixedBatch.ptr[++Enumerable->enumerator.state.fixedBatch.index];
            break;
            
        case CCEnumeratorFormatBatch:
            if (Enumerable->enumerator.state.batch.count == 0) return NULL;
            else if (Enumerable->enumerator.state.batch.index + 1 < Enumerable->enumerator.state.batch.count) return Enumerable->enumerator.state.batch.ptr + (++Enumerable->enumerator.state.batch.index * Enumerable->enumerator.state.batch.stride);
            break;
            
        case CCEnumeratorFormatCircular:
            if (Enumerable->enumerator.state.circular.count == 0) return NULL;
            else if ((Enumerable->enumerator.state.circular.index + 1) < (Enumerable->enumerator.state.circular.count + Enumerable->enumerator.state.circular.start)) return Enumerable->enumerator.state.circular.ptr + ((++Enumerable->enumerator.state.circular.index % Enumerable->enumerator.state.circular.max) * Enumerable->enumerator.state.circular.stride);
            break;
            
        default:
            break;
    }
    
    return Enumerable->handler(&Enumerable->enumerator, CCEnumerableActionNext);
}

static CC_FORCE_INLINE void *CCEnumerablePrevious(CCEnumerable *Enumerable)
{
    switch (Enumerable->enumerator.state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatFixedBatch:
            if (Enumerable->enumerator.state.fixedBatch.count == 0) return NULL;
            else if (Enumerable->enumerator.state.fixedBatch.index > 0) return Enumerable->enumerator.state.fixedBatch.ptr[--Enumerable->enumerator.state.fixedBatch.index];
            break;
            
        case CCEnumeratorFormatBatch:
            if (Enumerable->enumerator.state.batch.count == 0) return NULL;
            else if (Enumerable->enumerator.state.batch.index > 0) return Enumerable->enumerator.state.batch.ptr + (--Enumerable->enumerator.state.batch.index * Enumerable->enumerator.state.batch.stride);
            break;
            
        case CCEnumeratorFormatCircular:
            if (Enumerable->enumerator.state.circular.count == 0) return NULL;
            else if (Enumerable->enumerator.state.circular.index > Enumerable->enumerator.state.circular.start) return Enumerable->enumerator.state.circular.ptr + ((--Enumerable->enumerator.state.circular.index % Enumerable->enumerator.state.circular.max) * Enumerable->enumerator.state.circular.stride);
            break;
            
        default:
            break;
    }
    
    return Enumerable->handler(&Enumerable->enumerator, CCEnumerableActionPrevious);
}

#pragma mark - Template Type

#define CC_TYPE_CCEnumerable(...) CCEnumerable
#define CC_TYPE_0_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_1_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_2_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_3_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_4_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_5_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_6_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_7_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_8_CCEnumerable CC_TYPE_CCEnumerable,
#define CC_TYPE_9_CCEnumerable CC_TYPE_CCEnumerable,

#define CC_PRESERVE_CC_TYPE_CCEnumerable CC_TYPE_CCEnumerable

#define CC_TYPE_DECL_CCEnumerable(...) CCEnumerable, __VA_ARGS__
#define CC_TYPE_DECL_0_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_1_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_2_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_3_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_4_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_5_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_6_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_7_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_8_CCEnumerable CC_TYPE_DECL_CCEnumerable,
#define CC_TYPE_DECL_9_CCEnumerable CC_TYPE_DECL_CCEnumerable,

#define CC_MANGLE_TYPE_0_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_1_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_2_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_3_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_4_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_5_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_6_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_7_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_8_CCEnumerable CCEnumerable
#define CC_MANGLE_TYPE_9_CCEnumerable CCEnumerable

#endif

