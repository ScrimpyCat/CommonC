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

#import "AllocatorTests.h"
#import "Allocator.h"
#import "MemoryAllocation.h"

static _Bool CalledA = NO, CalledD = NO, PassedData = NO, HeaderIntact = NO, CorrectPtr = NO;
static uint8_t Memory[128];
static void *AllocatorFunction(void *Data, size_t Size)
{
    CalledA = YES;
    PassedData = *(int*)Data == 0xdeadbeef;
    
    assert(Size + sizeof(int) <= sizeof(Memory)); //update memory to be able to handle that size
    int *Ptr = (void*)Memory;
    *Ptr++ = 0xdeadcafe;
    return Ptr;
}

static void DeallocatorFunction(void *Ptr)
{
    CalledD = YES;
    int *Data = &((int*)Ptr)[-1];
    
    HeaderIntact = *Data == 0xdeadcafe;
    CorrectPtr = Data == (void*)Memory;
}


@implementation AllocatorTests

-(void) setUp
{
    [super setUp];
    
    // Set-up code here.
    CCAllocatorAdd(1, AllocatorFunction, NULL, DeallocatorFunction);
}

-(void) tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

-(void) testAllocation
{
    void *Ptr = CCAllocate((CCAllocatorType){ .allocator = 1, .data = &(int){ 0xdeadbeef } }, 1);
    STAssertTrue(CalledA, @"CCAllocate should call the custom allocator.");
    if (CalledA) STAssertTrue(PassedData, @"CCAllocate Should pass in the data in CCAllocatorType.");
    
    CCDeallocate(Ptr);
    STAssertTrue(CalledD, @"CCDeallocate should call the custom deallocator.");
    if (CalledD)
    {
        STAssertTrue(HeaderIntact, @"No function besides this and the allocator should access this section of memory.");
        STAssertTrue(CorrectPtr, @"Original pointer should remain the same.");
    }
    
    
    CalledA = NO, CalledD = NO, PassedData = NO, HeaderIntact = NO, CorrectPtr = NO;
    Ptr = CCMalloc(((CCAllocatorType){ .allocator = 1, .data = &(int){ 0xdeadbeef } }), 1, NULL, NULL);
    STAssertTrue(CalledA, @"CCAllocate should call the custom allocator.");
    if (CalledA) STAssertTrue(PassedData, @"CCAllocate Should pass in the data in CCAllocatorType.");
    
    CCFree(Ptr);
    STAssertTrue(CalledD, @"CCDeallocate should call the custom deallocator.");
    if (CalledD)
    {
        STAssertTrue(HeaderIntact, @"No function besides this and the allocator should access this section of memory.");
        STAssertTrue(CorrectPtr, @"Original pointer should remain the same.");
    }
}

@end
