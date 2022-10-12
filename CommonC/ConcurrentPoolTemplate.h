/*
 *  Copyright (c) 2022, Stefan Johnson
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
 A lock-free (or wait-free when supporting mixed size atomics) FIFO pool implementation.
 Allows for single produer-many consumer access.
 
 This is a low level interface and should only be used in specific use cases.
 The pool is fixed size and so the producer should only add more items to the pool once it knows consumers have popped enough items.
*/

#include <CommonC/Template.h>

#if CC_HARDWARE_PTR_64
typedef uint32_t CCConcurrentPoolIndex;
#elif CC_HARDWARE_PTR_32
typedef uint16_t CCConcurrentPoolIndex;
#endif

typedef struct {
    CCConcurrentPoolIndex index;
    CCConcurrentPoolIndex last;
} CCConcurrentPoolPointer;

#define CCConcurrentPool(t) CCConcurrentPool_(CC_MANGLE_TYPE(t))
#define CCConcurrentPool_(...) CCConcurrentPool__(__VA_ARGS__)
#define CCConcurrentPool__(sig) CCConcurrentPool_##sig

typedef union {
    _Atomic(CCConcurrentPoolPointer) pointer;
#if CC_HARDWARE_SUPPORT_ATOMICS_MIXED_SIZE
    struct {
        _Atomic(CCConcurrentPoolIndex) index;
        _Atomic(CCConcurrentPoolIndex) last;
    };
#endif
} CCConcurrentPool;

typedef struct {
    union {
        _Atomic(CCConcurrentPoolPointer) pointer;
#if CC_HARDWARE_SUPPORT_ATOMICS_MIXED_SIZE
        struct {
            _Atomic(CCConcurrentPoolIndex) index;
            _Atomic(CCConcurrentPoolIndex) last;
        };
#endif
    };
    CC_TYPE_DECL(T) items[];
} CCConcurrentPool(T);

#if CC_HARDWARE_SUPPORT_ATOMICS_MIXED_SIZE
typedef CCConcurrentPoolIndex CCConcurrentPoolStage;
#else
typedef struct {
    CCConcurrentPoolPointer pointer;
    CCConcurrentPoolIndex last;
} CCConcurrentPoolStage;
#endif


// CCConcurrentPoolIndex
#define CC_TYPE_CCConcurrentPoolIndex(...) CCConcurrentPoolIndex
#define CC_TYPE_0_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_1_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_2_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_3_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_4_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_5_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_6_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_7_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_8_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,
#define CC_TYPE_9_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex,

#define CC_PRESERVE_CC_TYPE_CCConcurrentPoolIndex CC_TYPE_CCConcurrentPoolIndex

#define CC_TYPE_DECL_CCConcurrentPoolIndex(...) CCConcurrentPoolIndex, __VA_ARGS__
#define CC_TYPE_DECL_0_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_1_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_2_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_3_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_4_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_5_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_6_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_7_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_8_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,
#define CC_TYPE_DECL_9_CCConcurrentPoolIndex CC_TYPE_DECL_CCConcurrentPoolIndex,

#define CC_MANGLE_TYPE_0_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_1_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_2_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_3_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_4_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_5_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_6_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_7_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_8_CCConcurrentPoolIndex CCConcurrentPoolIndex
#define CC_MANGLE_TYPE_9_CCConcurrentPoolIndex CCConcurrentPoolIndex

// CCConcurrentPoolStage
#define CC_TYPE_CCConcurrentPoolStage(...) CCConcurrentPoolStage
#define CC_TYPE_0_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_1_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_2_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_3_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_4_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_5_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_6_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_7_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_8_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,
#define CC_TYPE_9_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage,

#define CC_PRESERVE_CC_TYPE_CCConcurrentPoolStage CC_TYPE_CCConcurrentPoolStage

#define CC_TYPE_DECL_CCConcurrentPoolStage(...) CCConcurrentPoolStage, __VA_ARGS__
#define CC_TYPE_DECL_0_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_1_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_2_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_3_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_4_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_5_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_6_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_7_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_8_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,
#define CC_TYPE_DECL_9_CCConcurrentPoolStage CC_TYPE_DECL_CCConcurrentPoolStage,

#define CC_MANGLE_TYPE_0_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_1_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_2_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_3_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_4_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_5_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_6_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_7_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_8_CCConcurrentPoolStage CCConcurrentPoolStage
#define CC_MANGLE_TYPE_9_CCConcurrentPoolStage CCConcurrentPoolStage

// CCConcurrentPool
#define CC_TYPE_CCConcurrentPool(...) CCConcurrentPool
#define CC_TYPE_0_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_1_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_2_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_3_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_4_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_5_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_6_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_7_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_8_CCConcurrentPool CC_TYPE_CCConcurrentPool,
#define CC_TYPE_9_CCConcurrentPool CC_TYPE_CCConcurrentPool,

#define CC_PRESERVE_CC_TYPE_CCConcurrentPool CC_TYPE_CCConcurrentPool

#define CC_TYPE_DECL_CCConcurrentPool(...) CCConcurrentPool, __VA_ARGS__
#define CC_TYPE_DECL_0_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_1_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_2_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_3_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_4_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_5_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_6_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_7_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_8_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,
#define CC_TYPE_DECL_9_CCConcurrentPool CC_TYPE_DECL_CCConcurrentPool,

#define CC_MANGLE_TYPE_0_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_1_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_2_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_3_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_4_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_5_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_6_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_7_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_8_CCConcurrentPool CCConcurrentPool
#define CC_MANGLE_TYPE_9_CCConcurrentPool CCConcurrentPool

#define CCConcurrentPoolPop_strong_T(t) CC_TEMPLATE_REF(CCConcurrentPoolPop_strong, _Bool, PTYPE(CCConcurrentPool *), PTYPE(PTYPE(t *) *), CCConcurrentPoolIndex)
#define CCConcurrentPoolPop_weak_T(t) CC_TEMPLATE_REF(CCConcurrentPoolPop_weak, _Bool, PTYPE(CCConcurrentPool *), PTYPE(PTYPE(t *) *), CCConcurrentPoolIndex)
#define CCConcurrentPoolPush_T(t) CC_TEMPLATE_REF(CCConcurrentPoolPush, void, PTYPE(CCConcurrentPool *), PTYPE(t *), CCConcurrentPoolIndex, CCConcurrentPoolIndex)
#define CCConcurrentPoolStagePush_T(t) CC_TEMPLATE_REF(CCConcurrentPoolStagePush, void, PTYPE(CCConcurrentPool *), t, CCConcurrentPoolIndex, PTYPE(CCConcurrentPoolStage *))

/*!
 * @brief Pop the next item from the pool.
 * @description This variant provides strong guarantees for the CAS and as such is better suited outside of a tight loop.
 * @param Pool The concurrent pool.
 * @param Ref The pointer to where the reference to the item in the pool should be stored. The data at the pointer is only
 *            safe to access while nothing else has been pushed over it.
 *
 * @param Max The max size of the pool.
 * @return Whether an item was retrieved or not. Returns TRUE if an item was retrieved, FALSE if one was not.
 */
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCConcurrentPoolPop_strong, (PTYPE(CCConcurrentPool *) Pool, PTYPE(PTYPE(T *) *) Ref, CCConcurrentPoolIndex Max));

/*!
 * @brief Pop the next item from the pool.
 * @description This variant provides weak guarantees for the CAS and as such is better suited inside of a tight loop.
 * @param Pool The concurrent pool.
 * @param Ref The pointer to where the reference to the item in the pool should be stored. The data at the pointer is only
 *            safe to access while nothing else has been pushed over it.
 *
 * @param Max The max size of the pool.
 * @return Whether an item was retrieved or not. Returns TRUE if an item was retrieved, FALSE if one was not.
 */
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCConcurrentPoolPop_weak, (PTYPE(CCConcurrentPool *) Pool, PTYPE(PTYPE(T *) *) Ref, CCConcurrentPoolIndex Max));

/*!
 * @brief Push items onto the pool.
 * @param Pool The concurrent pool.
 * @param Items A pointer to the items that should be pushed onto the pool.
 * @param Count The number of items to be pushed.
 * @param Max The max size of the pool.
 */
CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentPoolPush, (PTYPE(CCConcurrentPool *) Pool, PTYPE(T *) Items, CCConcurrentPoolIndex Count, CCConcurrentPoolIndex Max));

/*!
 * @brief Initialise the stage object to begin staging item pushes.
 * @description Stages are used to add items to the pool but defer pushing them.
 * @note This function must be called to re-initialise the stage object any time another stage object has been committed or the
 *       unstaged @b CCConcurrentPoolPush was used. It does not need to be re-initialised if only the returned stage is used to
 *       commit.
 *
 * @param Pool The concurrent pool.
 * @return The stage that represents the current state of the pool.
 */
static CC_FORCE_INLINE CCConcurrentPoolStage CCConcurrentPoolStageBegin(CCConcurrentPool *Pool);

/*!
 * @brief Stage an item to be pushed onto the pool.
 * @param Pool The concurrent pool.
 * @param Item The item to be pushed.
 * @param Max The max size of the pool.
 * @param Stage The stage object to be used. Only one stage object can be used at a time, if more than one is used before another
 *              has been committed, items may be overwritten.
 */
CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentPoolStagePush, (PTYPE(CCConcurrentPool *) Pool, T Item, CCConcurrentPoolIndex Max, PTYPE(CCConcurrentPoolStage *) Stage));

/*!
 * @brief Commit a stage.
 * @param Pool The concurrent pool.
 * @param Stage The stage object to be committed. This stage object may be re-used without re-initialising it, any other stage object
 *              must be re-initialised.
 */
static CC_FORCE_INLINE void CCConcurrentPoolStageCommit(CCConcurrentPool *Pool, CCConcurrentPoolStage *Stage);

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCConcurrentPoolPop_strong, (PTYPE(CCConcurrentPool *) Pool, PTYPE(PTYPE(T *) *) Ref, CCConcurrentPoolIndex Max))
{
    CCConcurrentPoolPointer Pointer = atomic_load_explicit(&((CCConcurrentPool(T)*)Pool)->pointer, memory_order_relaxed);
    
    if  (Pointer.index != Pointer.last)
    {
        if (atomic_compare_exchange_strong_explicit(&((CCConcurrentPool(T)*)Pool)->pointer, &Pointer, ((CCConcurrentPoolPointer){ .index = Pointer.index + 1, .last = Pointer.last }), memory_order_consume, memory_order_relaxed))
        {
            *Ref = &((CCConcurrentPool(T)*)Pool)->items[Pointer.index % Max];
            
            return TRUE;
        }
    }
    
    return FALSE;
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCConcurrentPoolPop_weak, (PTYPE(CCConcurrentPool *) Pool, PTYPE(PTYPE(T *) *) Ref, CCConcurrentPoolIndex Max))
{
    CCConcurrentPoolPointer Pointer = atomic_load_explicit(&((CCConcurrentPool(T)*)Pool)->pointer, memory_order_relaxed);
    
    if  (Pointer.index != Pointer.last)
    {
        if (atomic_compare_exchange_weak_explicit(&((CCConcurrentPool(T)*)Pool)->pointer, &Pointer, ((CCConcurrentPoolPointer){ .index = Pointer.index + 1, .last = Pointer.last }), memory_order_consume, memory_order_relaxed))
        {
            *Ref = &((CCConcurrentPool(T)*)Pool)->items[Pointer.index % Max];
            
            return TRUE;
        }
    }
    
    return FALSE;
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentPoolPush, (PTYPE(CCConcurrentPool *) Pool, PTYPE(T *) Items, CCConcurrentPoolIndex Count, CCConcurrentPoolIndex Max))
{
    CCConcurrentPoolStage Stage = CCConcurrentPoolStageBegin(Pool);
    
    for (size_t Loop = 0; Loop < Count; Loop++) CCConcurrentPoolStagePush_T(T)(Pool, Items[Loop], Max, &Stage);
    
    CCConcurrentPoolStageCommit(Pool, &Stage);
}

static CC_FORCE_INLINE CCConcurrentPoolStage CCConcurrentPoolStageBegin(CCConcurrentPool *Pool)
{
#if CC_HARDWARE_SUPPORT_ATOMICS_MIXED_SIZE
    return atomic_load_explicit(&Pool->last, memory_order_relaxed);
#else
    const CCConcurrentPoolPointer Pointer = atomic_load_explicit(&Pool->pointer, memory_order_relaxed);
    
    return (CCConcurrentPoolStage){ .pointer = Pointer, .last = Pointer.last };
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCConcurrentPoolStagePush, (PTYPE(CCConcurrentPool *) Pool, T Item, CCConcurrentPoolIndex Max, PTYPE(CCConcurrentPoolStage *) Stage))
{
#if CC_HARDWARE_SUPPORT_ATOMICS_MIXED_SIZE
    ((CCConcurrentPool(T)*)Pool)->items[(*Stage)++ % Max] = Item;
#else
    ((CCConcurrentPool(T)*)Pool)->items[Stage->last++ % Max] = Item;
#endif
}

static CC_FORCE_INLINE void CCConcurrentPoolStageCommit(CCConcurrentPool *Pool, CCConcurrentPoolStage *Stage)
{
#if CC_HARDWARE_SUPPORT_ATOMICS_MIXED_SIZE
    atomic_store_explicit(&((CCConcurrentPool(T)*)Pool)->last, *Stage, memory_order_release);
#else
    while (!atomic_compare_exchange_weak_explicit(&Pool->pointer, &Stage->pointer, ((CCConcurrentPoolPointer){ .index = Stage->pointer.index, .last = Stage->last }), memory_order_release, memory_order_relaxed));
#endif
}
