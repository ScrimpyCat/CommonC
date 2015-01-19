/*
 *  Copyright (c) 2013, Stefan Johnson
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

#include "Allocator.h"
#include "Assertion_Private.h"
#include "CallbackAllocator.h"


#pragma mark - Standard Allocator Implementation
static void *StandardAllocator(void *Data, size_t Size)
{
    return malloc(Size);
}

static void *StandardReallocator(void *Data, void *Ptr, size_t Size)
{
    return realloc(Ptr, Size);
}

static void StandardDeallocator(void *Ptr)
{
    free(Ptr);
}


#pragma mark - Callback Allocator Implementation
static void *CallbackAllocator(CCCallbackAllocatorFunction Data, size_t Size)
{
    if (Data) Data(CCCallbackAllocatorEventAllocatePre, NULL, &Size);
    
    void **Ptr = malloc(Size + sizeof(CCCallbackAllocatorFunction));
    if (Ptr) *Ptr++ = Data;
    
    if (Data) Data(CCCallbackAllocatorEventAllocatePost, Ptr, &Size);
    
    return Ptr;
}

static void *CallbackReallocator(CCCallbackAllocatorFunction Data, void *Ptr, size_t Size)
{
    Data = ((void**)Ptr)[-1];
    if (Data) Data(CCCallbackAllocatorEventReallocatePre, Ptr, &Size);
    
    Ptr = (void**)realloc((void**)Ptr - 1, Size + sizeof(CCCallbackAllocatorFunction)) + 1;
    
    if (Data) Data(CCCallbackAllocatorEventReallocatePost, Ptr, &Size);
    
    return Ptr;
}

static void CallbackDeallocator(void *Ptr)
{
    CCCallbackAllocatorFunction Data = ((void**)Ptr)[-1];
    if (Data) Data(CCCallbackAllocatorEventDeallocatePre, Ptr, NULL);
    
    free((void**)Ptr - 1);
}


#pragma mark -

#define CC_ALLOCATORS_MAX 20 //If more is needed just recompile.
_Static_assert(CC_ALLOCATORS_MAX >= 3, "Allocator max too small, must allow for the default allocators.");



static struct {
    //lock
    struct {
        CCAllocatorFunction allocator;
        CCReallocatorFunction reallocator;
        CCDeallocatorFunction deallocator;
    } allocators[CC_ALLOCATORS_MAX];
} Allocators = {
    .allocators = {
        { .allocator = StandardAllocator, .reallocator = StandardReallocator, .deallocator = StandardDeallocator },
        { .allocator = (CCAllocatorFunction)CallbackAllocator, .reallocator = (CCReallocatorFunction)CallbackReallocator, .deallocator = CallbackDeallocator }
    }
};


void CCAllocatorAdd(int Index, CCAllocatorFunction Allocator, CCReallocatorFunction Reallocator, CCDeallocatorFunction Deallocator)
{
    CCAssertLog((Index > 0) && (Index < CC_ALLOCATORS_MAX), "Index (%d) cannot be negative, or 0 (replace standard allocator), or exceed the maximum number of allocators (%d).", Index, CC_ALLOCATORS_MAX);
    
    //Allocators.lock <- lock
    if ((Allocators.allocators[Index].allocator) || (Allocators.allocators[Index].reallocator) || (Allocators.allocators[Index].deallocator)) CC_LOG_WARNING("Replacing allocator (%p:%p:%p) at index (%d) with (%p:%p:%p).", Allocators.allocators[Index].allocator, Allocators.allocators[Index].reallocator, Allocators.allocators[Index].deallocator, Index, Allocator, Reallocator, Deallocator);
    Allocators.allocators[Index].allocator = Allocator;
    Allocators.allocators[Index].reallocator = Reallocator;
    Allocators.allocators[Index].deallocator = Deallocator;
    //release lock
}

void *CCAllocate(CCAllocatorType Type, size_t Size)
{
    const int Index = Type.allocator;
    if (Index < 0) return NULL;
    
    CCAssertLog(Index < CC_ALLOCATORS_MAX, "Index (%d) exceeds the number of allocators available (%d).", Index, CC_ALLOCATORS_MAX);
    const CCAllocatorFunction Allocator = Allocators.allocators[Index].allocator;
    
    int *Ptr = NULL;
    if (Allocator)
    {
        const size_t NewSize = Size + sizeof(int);
        if (NewSize > Size)
        {
            Ptr = Allocator(Type.data, NewSize);
            (*Ptr++) = Index;
        }
        
        else CC_LOG_DEBUG("Internal error: Integer overflow. Try reducing allocation size (%zu). #Attention #Error", Size);
    }
    
    return Ptr;
}

void *CCReallocate(CCAllocatorType Type, void *Ptr, size_t Size)
{
    if (!Ptr) return CCAllocate(Type, Size);
    
    int Index = ((int*)Ptr)[-1];
    CCAssertLog(Index < CC_ALLOCATORS_MAX, "Memory has been modified outside of its bounds.");
    const CCReallocatorFunction Reallocator = Allocators.allocators[Index].reallocator;
    
    const size_t NewSize = Size + sizeof(int);
    if (NewSize > Size)
    {
        Ptr = Reallocator? ((int*)Reallocator(Type.data, (int*)Ptr - 1, NewSize) + 1) : NULL;
    }
    
    else
    {
        CC_LOG_DEBUG("Internal error: Integer overflow. Try reducing allocation size (%zu). #Attention #Error", Size);
        Ptr = NULL;
    }
    
    return Ptr;
}

void CCDeallocate(void *Ptr)
{
    int Index = ((int*)Ptr)[-1];
    CCAssertLog(Index < CC_ALLOCATORS_MAX, "Memory has been modified outside of its bounds.");
    const CCDeallocatorFunction Deallocator = Allocators.allocators[Index].deallocator;
    
    if (Deallocator) Deallocator((int*)Ptr - 1);
}
