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

static _Bool CalledA = NO, CalledD = NO, PassedData = NO, HeaderIntact = NO, CorrectPtr = NO, CalledDtor = NO;
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

static void DestructorFunction(void *Ptr)
{
    CalledDtor = YES;
}

static const uint32_t TestAllocator = 19;
@implementation AllocatorTests

+(void) setUp
{
    [super setUp];
    
    // Set-up code here.
    CCAllocatorAdd(TestAllocator, AllocatorFunction, NULL, DeallocatorFunction);
}

-(void) setUp
{
    [super setUp];
    
    CalledA = NO; CalledD = NO; PassedData = NO; HeaderIntact = NO; CorrectPtr = NO; CalledDtor = NO;
}

-(void) tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

-(void) testAllocation
{
    void *Ptr = CCMemoryAllocate((CCAllocatorType){ .allocator = TestAllocator, .data = &(int){ 0xdeadbeef } }, 1);
    XCTAssertTrue(CalledA, @"CCAllocate should call the custom allocator.");
    if (CalledA) XCTAssertTrue(PassedData, @"CCAllocate Should pass in the data in CCAllocatorType.");
    
    XCTAssertEqual(CCMemoryRetain(Ptr), Ptr);
    
    CCMemoryDeallocate(Ptr);
    XCTAssertFalse(CalledD, @"CCDeallocate should not call the custom deallocator.");
    XCTAssertFalse(CalledDtor, @"Should not call custom destructor");
    
    CCMemoryDeallocate(Ptr);
    XCTAssertTrue(CalledD, @"CCDeallocate should call the custom deallocator.");
    if (CalledD)
    {
        XCTAssertTrue(HeaderIntact, @"No function besides this and the allocator should access this section of memory.");
        XCTAssertTrue(CorrectPtr, @"Original pointer should remain the same.");
    }
    
    XCTAssertFalse(CalledDtor, @"Should not call custom destructor");
    
    
    CalledA = NO; CalledD = NO; PassedData = NO; HeaderIntact = NO; CorrectPtr = NO;
    Ptr = CCMalloc(((CCAllocatorType){ .allocator = TestAllocator, .data = &(int){ 0xdeadbeef } }), 1, NULL, NULL);
    XCTAssertTrue(CalledA, @"CCAllocate should call the custom allocator.");
    if (CalledA) XCTAssertTrue(PassedData, @"CCAllocate Should pass in the data in CCAllocatorType.");
    
    CCMemorySetDestructor(Ptr, DestructorFunction);
    
    CCFree(Ptr);
    XCTAssertTrue(CalledD, @"CCDeallocate should call the custom deallocator.");
    if (CalledD)
    {
        XCTAssertTrue(HeaderIntact, @"No function besides this and the allocator should access this section of memory.");
        XCTAssertTrue(CorrectPtr, @"Original pointer should remain the same.");
    }
    
    XCTAssertTrue(CalledDtor, @"Should call custom destructor");
}

-(void) testAllocationGroups
{
    CCAllocatorType GroupAllocator = CC_ALLOCATORS(((CCAllocatorType){ .allocator = TestAllocator, .data = &(int){ 0xdeadbeef } }), CC_STD_ALLOCATOR);
    
    int *PtrA = CCMemoryAllocate(GroupAllocator, sizeof(int));
    
    XCTAssertTrue(CalledA, @"CCAllocate should call the custom allocator.");
    
    int *PtrB = CCMemoryAllocate(GroupAllocator, sizeof(int));
    int *PtrC = CCMemoryAllocate(GroupAllocator, sizeof(int));
    
    *PtrA = 1;
    *PtrB = 2;
    *PtrC = 3;
    
    XCTAssertEqual(*PtrA, 1, @"Should be a unique allocation");
    XCTAssertEqual(*PtrB, 2, @"Should be a unique allocation");
    XCTAssertEqual(*PtrC, 3, @"Should be a unique allocation");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
}

@end
