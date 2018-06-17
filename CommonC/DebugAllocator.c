/*
 *  Copyright (c) 2018, Stefan Johnson
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

#include "DebugAllocator.h"
#include "ConcurrentIndexMap.h"
#include "ConcurrentGarbageCollector.h"
#include "EpochGarbageCollector.h"
#include "ConcurrentQueue.h"
#include "Dictionary.h"
#include "DictionaryEnumerator.h"
#include "TypeCallbacks.h"
#include "Array.h"
#include "Assertion.h"
#include <stdatomic.h>

typedef struct {
    void *ptr;
    const char *file;
    int line;
} CCDebugAllocatorTrackedPtr;

typedef struct {
    CCConcurrentIndexMap allocations;
    CCConcurrentQueue availableIndexes;
} CCDebugAllocatorContext;

static _Atomic(CCDebugAllocatorContext) Context = ATOMIC_VAR_INIT(((CCDebugAllocatorContext){ NULL, NULL }));
void CCDebugAllocatorTrack(void *Ptr, CCDebugAllocatorInfo Info)
{
    CCAssertLog(Ptr, "Ptr must not be null");
    
    CCDebugAllocatorContext Ctx = atomic_load_explicit(&Context, memory_order_acquire);
    if (!Ctx.allocations)
    {
        Ctx.allocations = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(CCDebugAllocatorTrackedPtr), 16, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
        Ctx.availableIndexes = CCConcurrentQueueCreate(CC_STD_ALLOCATOR, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
        
        if (!atomic_compare_exchange_strong_explicit(&Context, &((CCDebugAllocatorContext){ NULL, NULL }), Ctx, memory_order_release, memory_order_relaxed))
        {
            Ctx = atomic_load_explicit(&Context, memory_order_acquire);
        }
    }
    
    if (Ctx.allocations)
    {
        CCConcurrentQueueNode *Node = CCConcurrentQueuePop(Ctx.availableIndexes);
        if (Node)
        {
            CCConcurrentIndexMapReplaceElementAtIndex(Ctx.allocations, *(size_t*)CCConcurrentQueueGetNodeData(Node), &(CCDebugAllocatorTrackedPtr){ .ptr = Ptr, .file = Info.file, .line = Info.line }, NULL);
            CCConcurrentQueueDestroyNode(Node);
        }
        
        else CCConcurrentIndexMapAppendElement(Ctx.allocations, &(CCDebugAllocatorTrackedPtr){ .ptr = Ptr, .file = Info.file, .line = Info.line });
    }
}

static _Bool CCDebugAllocatorTrackedIndex(void *Ptr, size_t *Index, CCDebugAllocatorContext *Ctx)
{
    if (Ctx->allocations)
    {
        CCDebugAllocatorTrackedPtr Tracked;
        for (size_t Loop = 0; CCConcurrentIndexMapGetElementAtIndex(Ctx->allocations, Loop, &Tracked); Loop++)
        {
            if (Tracked.ptr == Ptr)
            {
                if (Index) *Index = Loop;
                return TRUE;
            }
        }
    }
    
    return FALSE;
}

void CCDebugAllocatorTrackReplaced(void *OldPtr, void *NewPtr, CCDebugAllocatorInfo Info)
{
    CCAssertLog(OldPtr, "OldPtr must not be null");
    CCAssertLog(NewPtr, "NewPtr must not be null");
    
    CCDebugAllocatorContext Ctx = atomic_load_explicit(&Context, memory_order_acquire);
    
    size_t Index;
    if (CCDebugAllocatorTrackedIndex(OldPtr, &Index, &Ctx)) CCConcurrentIndexMapReplaceElementAtIndex(Ctx.allocations, Index, &(CCDebugAllocatorTrackedPtr){ .ptr = NewPtr, .file = Info.file, .line = Info.line }, NULL);
}

void CCDebugAllocatorUntrack(void *Ptr)
{
    CCAssertLog(Ptr, "Ptr must not be null");
    
    CCDebugAllocatorContext Ctx = atomic_load_explicit(&Context, memory_order_acquire);
    
    size_t Index;
    if (CCDebugAllocatorTrackedIndex(Ptr, &Index, &Ctx)) CCConcurrentIndexMapReplaceElementAtIndex(Ctx.allocations, Index, &(CCDebugAllocatorTrackedPtr){ .ptr = NULL, .file = NULL, .line = 0 }, NULL);
}

_Bool CCDebugAllocatorIsTracking(void *Ptr)
{
    CCAssertLog(Ptr, "Ptr must not be null");
    
    CCDebugAllocatorContext Ctx = atomic_load_explicit(&Context, memory_order_acquire);
    
    return CCDebugAllocatorTrackedIndex(Ptr, NULL, &Ctx);
}

static CCDictionary CCDebugAllocatorDump(void)
{
    CCDictionary Files = CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeMedium, sizeof(const char*), sizeof(CCDictionary), &(CCDictionaryCallbacks){
        .valueDestructor = CCDictionaryDestructorForDictionary
    });
    
    CCDebugAllocatorContext Ctx = atomic_load_explicit(&Context, memory_order_acquire);
    if (Ctx.allocations)
    {
        CCDebugAllocatorTrackedPtr Tracked;
        for (size_t Loop = 0; CCConcurrentIndexMapGetElementAtIndex(Ctx.allocations, Loop, &Tracked); Loop++)
        {
            if (Tracked.ptr)
            {
                CCDictionary Lines;
                CCDictionaryEntry FileEntry = CCDictionaryEntryForKey(Files, &Tracked.file);
                if (!CCDictionaryEntryIsInitialized(Files, FileEntry))
                {
                    Lines = CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeMedium, sizeof(int), sizeof(CCArray), &(CCDictionaryCallbacks){
                        .valueDestructor = CCArrayDestructorForDictionary
                    });
                    CCDictionarySetEntry(Files, FileEntry, &Lines);
                }
                
                else Lines = *(CCDictionary*)CCDictionaryGetEntry(Files, FileEntry);
                
                CCArray Allocations;
                CCDictionaryEntry LineEntry = CCDictionaryEntryForKey(Lines, &Tracked.line);
                if (!CCDictionaryEntryIsInitialized(Lines, LineEntry))
                {
                    Allocations = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(void*), 8);
                    CCDictionarySetEntry(Lines, LineEntry, &Allocations);
                }
                
                else Allocations = *(CCArray*)CCDictionaryGetEntry(Lines, LineEntry);
                
                CCArrayAppendElement(Allocations, &Tracked.ptr);
            }
        }
    }
    
    return Files;
}

void CCDebugAllocatorPrint(void)
{
    CCDictionary Dump = CCDebugAllocatorDump();
    
    CC_DICTIONARY_FOREACH_VALUE(CCDictionary, Lines, Dump)
    {
        CCDictionaryEntry FileEntry = CCDictionaryEnumeratorGetEntry(&CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR);
        
        printf("%s:\n", *(const char**)CCDictionaryGetKey(Dump, FileEntry));
        
        CC_DICTIONARY_FOREACH_VALUE(CCArray, Allocations, Lines)
        {
            CCDictionaryEntry LineEntry = CCDictionaryEnumeratorGetEntry(&CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR);
            const int Line = *(int*)CCDictionaryGetKey(Lines, LineEntry);
            
            for (size_t Loop = 0, Count = CCArrayGetCount(Allocations); Loop < Count; Loop++)
            {
                printf("\t%d: %p\n", Line, *(void**)CCArrayGetElementAtIndex(Allocations, Loop));
            }
        }
    }
    
    CCDictionaryDestroy(Dump);
}
