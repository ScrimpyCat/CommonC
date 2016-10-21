/*
 *  Copyright (c) 2016, Stefan Johnson
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

#ifndef CommonC_ConcurrentGarbageCollector_h
#define CommonC_ConcurrentGarbageCollector_h

#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>
#include <stdint.h>
#include <stddef.h>
#include <stdatomic.h>

typedef void (*CCConcurrentGarbageCollectorReclaimer)(void*);

typedef struct CCConcurrentGarbageCollectorNode {
    struct CCConcurrentGarbageCollectorNode *next;
} CCConcurrentGarbageCollectorNode;

typedef struct {
    CCConcurrentGarbageCollectorNode node;
    uint8_t data[];
} CCConcurrentGarbageCollectorNodeData;

typedef uint64_t CCConcurrentGarbageCollectorEpoch;

typedef struct {
    CCConcurrentGarbageCollectorNode *list;
    uint32_t refCount;
} CCConcurrentGarbageCollectorManagedList;

typedef struct {
    CCAllocatorType allocator;
    _Atomic(CCConcurrentGarbageCollectorManagedList) managed[3];
    _Atomic(CCConcurrentGarbageCollectorEpoch) epoch;
    pthread_key_t key;
} CCConcurrentGarbageCollectorInfo, *CCConcurrentGarbageCollector;

#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent garbage collector.
 * @param Allocator The allocator to be used for the allocation.
 * @return A garbage collector, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentGarbageCollector CCConcurrentGarbageCollectorCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a garbage collector.
 * @warning All usage by other threads must have finish before final destruction.
 * @param GC The garbage collector to be destroyed.
 */
void CCConcurrentGarbageCollectorDestroy(CCConcurrentGarbageCollector CC_DESTROY(GC));

void CCConcurrentGarbageCollectorBegin(CCConcurrentGarbageCollector GC);

void CCConcurrentGarbageCollectorEnd(CCConcurrentGarbageCollector GC);

void CCConcurrentGarbageCollectorManage(CCConcurrentGarbageCollector GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer);

#endif
