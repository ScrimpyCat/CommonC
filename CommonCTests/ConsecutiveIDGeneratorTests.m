/*
 *  Copyright (c) 2019, Stefan Johnson
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
#import "ConcurrentIDGenerator.h"
#import "ConsecutiveIDGenerator.h"
#import <stdatomic.h>
#import <pthread.h>

@interface ConsecutiveIDGeneratorTests : XCTestCase

@end

@implementation ConsecutiveIDGeneratorTests

-(void) testExhaustingPool
{
    size_t ID[17];
    CCConcurrentIDGenerator Pool = CCConcurrentIDGeneratorCreate(CC_STD_ALLOCATOR, sizeof(ID) / sizeof(size_t), CCConsecutiveIDGenerator);
    
    XCTAssertEqual(17, CCConcurrentIDGeneratorGetMaxID(Pool), @"Should return the correct size");
    
    size_t Sum = 0, ExpectedSum = 0, MaxID = 0, MinID = SIZE_MAX;
    for (size_t Loop = 0; Loop < sizeof(ID) / sizeof(size_t); Loop++)
    {
        XCTAssertTrue(CCConcurrentIDGeneratorTryAssign(Pool, &ID[Loop]), @"Should assign ID");
        Sum += ID[Loop];
        ExpectedSum += Loop;
        if (MaxID < ID[Loop]) MaxID = ID[Loop];
        if (MinID > ID[Loop]) MinID = ID[Loop];
    }
    
    XCTAssertEqual(MinID, 0, @"IDs should start from 0");
    XCTAssertEqual(MaxID, 16, @"IDs should end at size - 1");
    XCTAssertEqual(Sum, ExpectedSum, @"Should not assign any ID more than once");
    XCTAssertFalse(CCConcurrentIDGeneratorTryAssign(Pool, &Sum), @"Should not assign an ID");
    
    CCConcurrentIDGeneratorRecycle(Pool, ID[0]);
    XCTAssertTrue(CCConcurrentIDGeneratorTryAssign(Pool, &Sum), @"Should assign ID");
    
    CCConcurrentIDGeneratorDestroy(Pool);
}

#define THREAD_COUNT 20
#define IDS_PER_THREAD 500
#define ID_POOL (IDS_PER_THREAD * THREAD_COUNT)

static CCConcurrentIDGenerator P;
static _Atomic(int) Assigned = ATOMIC_VAR_INIT(THREAD_COUNT);
static void *Worker(void *Arg)
{
    uintptr_t Sum = 0;
    size_t ID[IDS_PER_THREAD];
    for (size_t Loop = 0; Loop < IDS_PER_THREAD; Loop++)
    {
        ID[Loop] = CCConcurrentIDGeneratorAssign(P);
        Sum += ID[Loop];
    }
    
    atomic_fetch_sub_explicit(&Assigned, 1, memory_order_release);
    while (atomic_load_explicit(&Assigned, memory_order_acquire));
    
    for (size_t Loop = 0; Loop < IDS_PER_THREAD; Loop++) CCConcurrentIDGeneratorRecycle(P, ID[Loop]);
    
    return (void*)Sum;
}

-(void) testMultiThreading
{
    P = CCConcurrentIDGeneratorCreate(CC_STD_ALLOCATOR, ID_POOL, CCConsecutiveIDGenerator);
    
    pthread_t Threads[THREAD_COUNT];
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(Threads + Loop, NULL, Worker, NULL);
    }
    
    uintptr_t Sum = 0, Expected = 0;
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        uintptr_t Result = 0;
        pthread_join(Threads[Loop], (void**)&Result);
        Sum += (uintptr_t)Result;
        
        for (size_t Loop2 = 0; Loop2 < IDS_PER_THREAD; Loop2++) Expected += (Loop * IDS_PER_THREAD) + Loop2;
    }
    
    XCTAssertEqual(Sum, Expected, @"Should not assign any ID more than once");
    
    Sum = 0;
    for (size_t Loop = 0; Loop < ID_POOL; Loop++)
    {
        Sum += CCConcurrentIDGeneratorAssign(P);
    }
    
    XCTAssertEqual(Sum, Expected, @"All IDs should have been recycled");
    
    CCConcurrentIDGeneratorDestroy(P);
}

#undef ID_POOL
#define ID_POOL ((IDS_PER_THREAD / 5) * THREAD_COUNT)

static CCConcurrentIDGenerator P;
static void *Worker2(void *Arg)
{
    size_t ID[IDS_PER_THREAD], Count = 0, FailureCount = 0;
    for (size_t Loop = 0; Loop < IDS_PER_THREAD; )
    {
        if (CCConcurrentIDGeneratorTryAssign(P, &ID[Count]))
        {
            Loop++;
            Count++;
        }
        
        else if (FailureCount == 10)
        {
            for (size_t Loop = 0; Loop < Count; Loop++) CCConcurrentIDGeneratorRecycle(P, ID[Loop]);
            FailureCount = 0;
            Count = 0;
        }
        
        else FailureCount++;
    }
    
    for (size_t Loop = 0; Loop < Count; Loop++) CCConcurrentIDGeneratorRecycle(P, ID[Loop]);
    
    return NULL;
}

-(void) testSmallPoolMultiThreading
{
    P = CCConcurrentIDGeneratorCreate(CC_STD_ALLOCATOR, ID_POOL, CCConsecutiveIDGenerator);
    
    pthread_t Threads[THREAD_COUNT];
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(Threads + Loop, NULL, Worker2, NULL);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(Threads[Loop], NULL);
    }
    
    uintptr_t Sum = 0, Expected = 0;
    for (size_t Loop = 0; Loop < ID_POOL; Loop++)
    {
        Sum += CCConcurrentIDGeneratorAssign(P);
        Expected += Loop;
    }
    
    XCTAssertEqual(Sum, Expected, @"All IDs should have been recycled");
    
    CCConcurrentIDGeneratorDestroy(P);
}

@end
