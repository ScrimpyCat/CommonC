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

#import "MemoryAllocationTests.h"

#define CC_DEFAULT_ERROR_CALLBACK NULL
#import "MemoryAllocation.h"

@implementation MemoryAllocationTests

-(void) testCCMallocNullAllocator
{
    void *Ptr = CCMalloc(CC_NULL_ALLOCATOR, 128, NULL, NULL);
    STAssertTrue(Ptr == NULL, @"NULL Allocator must return null.");
    CCFree(Ptr);
    
    
#undef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_NULL_ALLOCATOR
    
    CC_SAFE_Malloc(Ptr, 128);
    STAssertTrue(Ptr == NULL, @"CC_DEFAULT_ALLOCATOR Should override default allocator when using convenience macro allocates.");
    CC_SAFE_Free(Ptr);
    
#undef CC_ALLOC_ON_STACK_MAX
#undef CC_SHOULD_ALLOC_ON_STACK
#define CC_ALLOC_ON_STACK_MAX 0
#define CC_SHOULD_ALLOC_ON_STACK 0
    
    CC_TEMP_Malloc(Ptr, 128);
    STAssertTrue(Ptr == NULL, @"CC_DEFAULT_ALLOCATOR Should override default allocator when using convenience macro allocates.");
    CC_TEMP_Free(Ptr);

#undef CC_ALLOC_ON_STACK_MAX
#undef CC_SHOULD_ALLOC_ON_STACK
#define CC_ALLOC_ON_STACK_MAX 256
#define CC_SHOULD_ALLOC_ON_STACK 64
    
#undef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_STD_ALLOCATOR
}

-(void) testCCSafeMallocFailure
{
#undef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_NULL_ALLOCATOR
    
    int Failed = 0;
    void *Ptr;
    CC_SAFE_Malloc(Ptr, 128, Failed = 0xdeadbeef;);
    if (!Ptr) STAssertTrue(Failed == 0xdeadbeef, @"CC_SAFE_Malloc Should fail on null.");
    CC_SAFE_Free(Ptr);
    
#undef CC_ALLOC_ON_STACK_MAX
#undef CC_SHOULD_ALLOC_ON_STACK
#define CC_ALLOC_ON_STACK_MAX 0
#define CC_SHOULD_ALLOC_ON_STACK 0
    
    Failed = 0;
    CC_TEMP_Malloc(Ptr, 128, Failed = 0xdeadbeef;);
    if (!Ptr) STAssertTrue(Failed == 0xdeadbeef, @"CC_SAFE_Malloc Should fail on null.");
    CC_TEMP_Free(Ptr);
    
#undef CC_ALLOC_ON_STACK_MAX
#undef CC_SHOULD_ALLOC_ON_STACK
#define CC_ALLOC_ON_STACK_MAX 256
#define CC_SHOULD_ALLOC_ON_STACK 64
    
#undef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_STD_ALLOCATOR
}

-(void) testCCTempMallocStackBasedAllocation
{
#undef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_NULL_ALLOCATOR
    
    void *Ptr;
    CC_TEMP_Malloc(Ptr, 128);
    STAssertTrue(Ptr != NULL, @"CC_TEMP_Malloc Should fallback to stack based allocation."); //Assumes we didn't run out of stack space (however would crash then)
    CC_TEMP_Free(Ptr);
    
#undef CC_DEFAULT_ALLOCATOR
#define CC_DEFAULT_ALLOCATOR CC_STD_ALLOCATOR
}

static void *FuncData;
static _Bool FuncCalled = NO;
static void *Callback(CCFunctionData *FunctionData, void *Data)
{
    FuncData = Data;
    FuncCalled = YES;
    return (void*)0xdeadcafe;
}

-(void) testCCMallocCallback
{
    __block _Bool Called = NO;
    void *Ptr = CCMalloc(CC_NULL_ALLOCATOR, 128, (void*)0xdeadbeef, ^void *(CCFunctionData *FunctionData, void *Data){
        STAssertTrue(Data == (void*)0xdeadbeef, @"CCMalloc Should pass data to the callback block.");
        Called = YES;
        return (void*)0xdeadcafe;
    });
    if (Called)
    {
        STAssertTrue(Ptr == (void*)0xdeadcafe, @"CCMalloc Should return the return of the callback block on failure.");
    }

    else
    {
        STAssertTrue(Ptr != NULL, @"CCMalloc Should call the callback block on failure.");
        CCFree(Ptr);
    }
    
    
    Ptr = CCMalloc(CC_NULL_ALLOCATOR, 128, (void*)0xdeadbeef, Callback);
    if (FuncCalled)
    {
        STAssertTrue(FuncData == (void*)0xdeadbeef, @"CCMalloc Should pass data to the callback function.");
        STAssertTrue(Ptr == (void*)0xdeadcafe, @"CCMalloc Should return the return of the callback function on failure.");
    }
    
    else
    {
        STAssertTrue(Ptr != NULL, @"CCMalloc Should call the callback function on failure.");
        CCFree(Ptr);
    }
}

@end
