/*
*  Copyright (c) 2023, Stefan Johnson
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

#import <XCTest/XCTest.h>
#import "MemoryAllocation.h"
#import "Alignment.h"

@interface AlignedAllocatorTests : XCTestCase

@end

@implementation AlignedAllocatorTests

-(void) testAlignment
{
    int *Ptr = CCMalloc(CC_ALIGNED_ALLOCATOR(64), sizeof(int), NULL, NULL);
    *Ptr = 0x636261;
    
    XCTAssertEqual((uintptr_t)Ptr, CC_ALIGN((uintptr_t)Ptr, 64), @"allocated memory should be aligned");
    
    Ptr = CCRealloc(CC_ALIGNED_ALLOCATOR(64), Ptr, sizeof(int) * 1024, NULL, NULL);
    
    XCTAssertEqual((uintptr_t)Ptr, CC_ALIGN((uintptr_t)Ptr, 64), @"allocated memory should be aligned");
    XCTAssertEqual(*Ptr, 0x636261, @"should preserve the old data");
    
    CCFree(Ptr);
    
    Ptr = CCMalloc(CC_ALIGNED_ALLOCATOR(16384), sizeof(int), NULL, NULL);
    *Ptr = 0x636261;
    
    XCTAssertEqual((uintptr_t)Ptr, CC_ALIGN((uintptr_t)Ptr, 16384), @"allocated memory should be aligned");
    
    Ptr = CCRealloc(CC_ALIGNED_ALLOCATOR(16384), Ptr, sizeof(int) * 1024, NULL, NULL);
    
    XCTAssertEqual((uintptr_t)Ptr, CC_ALIGN((uintptr_t)Ptr, 16384), @"allocated memory should be aligned");
    XCTAssertEqual(*Ptr, 0x636261, @"should preserve the old data");
    
    CCFree(Ptr);
}

@end
