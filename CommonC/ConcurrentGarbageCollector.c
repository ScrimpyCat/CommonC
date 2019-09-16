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

#define CC_QUICK_COMPILE
#include "ConcurrentGarbageCollector.h"
#include "MemoryAllocation.h"
#include "Assertion.h"

typedef struct CCConcurrentGarbageCollectorInfo {
    const CCConcurrentGarbageCollectorInterface *interface;
    CCAllocatorType allocator;
    void *internal;
} CCConcurrentGarbageCollectorInfo;


static void CCConcurrentGarbageCollectorDestructor(CCConcurrentGarbageCollector GC)
{
    GC->interface->destroy(GC->internal);
}

CCConcurrentGarbageCollector CCConcurrentGarbageCollectorCreate(CCAllocatorType Allocator, const CCConcurrentGarbageCollectorInterface *Interface)
{
    CCConcurrentGarbageCollector GC = CCMalloc(Allocator, sizeof(CCConcurrentGarbageCollectorInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (GC)
    {
        *GC = (CCConcurrentGarbageCollectorInfo){
            .interface = Interface,
            .allocator = Allocator,
            .internal = Interface->create(Allocator)
        };
        
        if (!GC->internal)
        {
            CC_LOG_ERROR("Failed to create garbage collector: Implementation failure (%p)", Interface);
            CCFree(GC);
            GC = NULL;
        }
        
        else CCMemorySetDestructor(GC, (CCMemoryDestructorCallback)CCConcurrentGarbageCollectorDestructor);
    }
    
    else
    {
        CC_LOG_ERROR("Failed to create garbage collector: Failed to allocate memory of size (%zu)", sizeof(CCConcurrentGarbageCollectorInfo));
    }
    
    return GC;
}

void CCConcurrentGarbageCollectorDestroy(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    CCFree(GC);
}

void CCConcurrentGarbageCollectorBegin(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    GC->interface->begin(GC->internal, GC->allocator);
}

void CCConcurrentGarbageCollectorEnd(CCConcurrentGarbageCollector GC)
{
    CCAssertLog(GC, "GC must not be null");
    
    GC->interface->end(GC->internal, GC->allocator);
}

void CCConcurrentGarbageCollectorManage(CCConcurrentGarbageCollector GC, void *Item, CCConcurrentGarbageCollectorReclaimer Reclaimer)
{
    CCAssertLog(GC, "GC must not be null");
    
    GC->interface->manage(GC->internal, Item, Reclaimer, GC->allocator);
}
