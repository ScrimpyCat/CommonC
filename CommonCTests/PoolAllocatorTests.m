/*
 *  Copyright (c) 2025, Stefan Johnson
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
#import "PoolAllocator.h"
#include <stdalign.h>
#import "Alignment.h"

@interface PoolAllocatorTests : XCTestCase

@end

@implementation PoolAllocatorTests

-(void) testPool
{
    struct {
        CCPoolAllocatorHeader header;
        int data;
    } TestPool[4];
    
    size_t TestPoolIndexes[4];
    
    struct {
        CCAllocatorHeader header;
        CCPoolAllocatorInfo info;
    } PoolAllocator = {
        .header = CC_ALLOCATOR_HEADER_INIT(CC_STATIC_ALLOCATOR.allocator),
        .info = {
            .blockSize = sizeof(*TestPool),
            .count = 0,
            .max = 4,
            .pool = TestPool,
            .available = {
                .count = 0,
                .indexes = TestPoolIndexes
            }
        }
    };
    
    CCPoolAllocator Pool = &PoolAllocator.info;
    
    int *PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    int *PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual(PtrA, &TestPool[0].data, @"Should get the correct block");
    XCTAssertEqual(PtrB, &TestPool[1].data, @"Should get the correct block");
    
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrA), 0, @"Should get the correct block index");
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrB), 1, @"Should get the correct block index");
    
    XCTAssertEqual(CCPoolAllocatorGetMemory(Pool, 0), &TestPool[0].data, @"Should get the correct block");
    XCTAssertEqual(CCPoolAllocatorGetMemory(Pool, 1), &TestPool[1].data, @"Should get the correct block");
    
    CCFree(PtrA);
    
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual(PtrA, &TestPool[0].data, @"Should get the correct block");
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrA), 0, @"Should get the correct block index");
    
    int *PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    int *PtrD = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    int *PtrE = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual(PtrC, &TestPool[2].data, @"Should get the correct block");
    XCTAssertEqual(PtrD, &TestPool[3].data, @"Should get the correct block");
    XCTAssertEqual(PtrE, NULL, @"Should run out of blocks");
    
    PtrE = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    XCTAssertEqual(PtrE, NULL, @"Should run out of blocks");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
    CCFree(PtrD);
    
    PtrD = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual(PtrA, &TestPool[0].data, @"Should get the correct block");
    XCTAssertEqual(PtrB, &TestPool[1].data, @"Should get the correct block");
    XCTAssertEqual(PtrC, &TestPool[2].data, @"Should get the correct block");
    XCTAssertEqual(PtrD, &TestPool[3].data, @"Should get the correct block");
    
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrA), 0, @"Should get the correct block index");
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrB), 1, @"Should get the correct block index");
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrC), 2, @"Should get the correct block index");
    XCTAssertEqual(CCPoolAllocatorGetIndex(PtrD), 3, @"Should get the correct block index");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
    CCFree(PtrD);
    
    
    
    Pool = CCPoolAllocatorCreate(CC_STD_ALLOCATOR, sizeof(int), alignof(int), 4);
    
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual((uintptr_t)PtrA, CC_ALIGN((uintptr_t)PtrA, alignof(int)), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrB, CC_ALIGN((uintptr_t)PtrB, alignof(int)), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrC, CC_ALIGN((uintptr_t)PtrC, alignof(int)), @"allocated memory should be aligned");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
    
    CCPoolAllocatorDestroy(Pool);
    
    
    
    Pool = CCPoolAllocatorCreate(CC_STD_ALLOCATOR, sizeof(int), 16, 4);
    
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual((uintptr_t)PtrA, CC_ALIGN((uintptr_t)PtrA, 16), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrB, CC_ALIGN((uintptr_t)PtrB, 16), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrC, CC_ALIGN((uintptr_t)PtrC, 16), @"allocated memory should be aligned");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
    
    CCPoolAllocatorDestroy(Pool);
    
    
    
    Pool = CCPoolAllocatorCreate(CC_STD_ALLOCATOR, sizeof(int), 64, 4);
    
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual((uintptr_t)PtrA, CC_ALIGN((uintptr_t)PtrA, 64), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrB, CC_ALIGN((uintptr_t)PtrB, 64), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrC, CC_ALIGN((uintptr_t)PtrC, 64), @"allocated memory should be aligned");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
    
    CCPoolAllocatorDestroy(Pool);
    
    
    
    Pool = CCPoolAllocatorCreate(CC_STD_ALLOCATOR, sizeof(int), 128, 4);
    
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual((uintptr_t)PtrA, CC_ALIGN((uintptr_t)PtrA, 128), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrB, CC_ALIGN((uintptr_t)PtrB, 128), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrC, CC_ALIGN((uintptr_t)PtrC, 128), @"allocated memory should be aligned");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
    
    CCPoolAllocatorDestroy(Pool);
    
    
    
    Pool = CC_POOL_ALLOCATOR_CREATE(sizeof(int), 128, 4);
    
    PtrA = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrB = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    PtrC = CCMalloc(CC_POOL_ALLOCATOR(Pool), sizeof(int), NULL, NULL);
    
    XCTAssertEqual((uintptr_t)PtrA, CC_ALIGN((uintptr_t)PtrA, 128), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrB, CC_ALIGN((uintptr_t)PtrB, 128), @"allocated memory should be aligned");
    XCTAssertEqual((uintptr_t)PtrC, CC_ALIGN((uintptr_t)PtrC, 128), @"allocated memory should be aligned");
    
    CCFree(PtrA);
    CCFree(PtrB);
    CCFree(PtrC);
}

@end
