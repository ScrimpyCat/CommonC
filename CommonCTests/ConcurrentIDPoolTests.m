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
#import "ConcurrentIDPool.h"
#import <stdatomic.h>
#import <pthread.h>

@interface ConcurrentIDPoolTests : XCTestCase

@end

@implementation ConcurrentIDPoolTests

-(void) testExhaustingPool
{
    size_t ID[17];
    CCConcurrentIDPool Pool = CCConcurrentIDPoolCreate(CC_STD_ALLOCATOR, sizeof(ID) / sizeof(size_t));
    
    size_t Sum = 0, ExpectedSum = 0;
    for (size_t Loop = 0; Loop < sizeof(ID) / sizeof(size_t); Loop++)
    {
        XCTAssertTrue(CCConcurrentIDPoolTryAssign(Pool, &ID[Loop]), @"Should assign ID");
        Sum += ID[Loop];
        ExpectedSum += Loop;
    }
    
    XCTAssertEqual(Sum, ExpectedSum, @"Should not assign any ID more than once");
    XCTAssertFalse(CCConcurrentIDPoolTryAssign(Pool, &Sum), @"Should not assign an ID");
    
    CCConcurrentIDPoolRecycle(Pool, ID[0]);
    XCTAssertTrue(CCConcurrentIDPoolTryAssign(Pool, &Sum), @"Should assign ID");
    
    CCConcurrentIDPoolDestroy(Pool);
}

#define THREAD_COUNT 20
#define IDS_PER_THREAD 500
#define ID_POOL (IDS_PER_THREAD * THREAD_COUNT)

static CCConcurrentIDPool P;
static _Atomic(int) Assigned = ATOMIC_VAR_INIT(THREAD_COUNT);
static void *Worker(void *Arg)
{
    uintptr_t Sum = 0;
    size_t ID[IDS_PER_THREAD];
    for (size_t Loop = 0; Loop < IDS_PER_THREAD; Loop++)
    {
        ID[Loop] = CCConcurrentIDPoolAssign(P);
        Sum += ID[Loop];
    }
    
    atomic_fetch_sub_explicit(&Assigned, 1, memory_order_release);
    while (atomic_load_explicit(&Assigned, memory_order_acquire));
    
    for (size_t Loop = 0; Loop < IDS_PER_THREAD; Loop++) CCConcurrentIDPoolRecycle(P, ID[Loop]);
    
    return (void*)Sum;
}

-(void) testMultiThreading
{
    P = CCConcurrentIDPoolCreate(CC_STD_ALLOCATOR, ID_POOL);
    
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
        Sum += CCConcurrentIDPoolAssign(P);
    }
    
    XCTAssertEqual(Sum, Expected, @"All IDs should have been recycled");
    
    CCConcurrentIDPoolDestroy(P);
}

#undef ID_POOL
#define ID_POOL ((IDS_PER_THREAD / 5) * THREAD_COUNT)

static CCConcurrentIDPool P;
static void *Worker2(void *Arg)
{
    size_t ID[IDS_PER_THREAD], Count = 0, FailureCount = 0;
    for (size_t Loop = 0; Loop < IDS_PER_THREAD; )
    {
        if (CCConcurrentIDPoolTryAssign(P, &ID[Count]))
        {
            Loop++;
            Count++;
        }
        
        else if (FailureCount == 10)
        {
            for (size_t Loop = 0; Loop < Count; Loop++) CCConcurrentIDPoolRecycle(P, ID[Loop]);
            FailureCount = 0;
            Count = 0;
        }
        
        else FailureCount++;
    }
    
    for (size_t Loop = 0; Loop < Count; Loop++) CCConcurrentIDPoolRecycle(P, ID[Loop]);
    
    return NULL;
}

-(void) testSmallPoolMultiThreading
{
    P = CCConcurrentIDPoolCreate(CC_STD_ALLOCATOR, ID_POOL);
    
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
        Sum += CCConcurrentIDPoolAssign(P);
        Expected += Loop;
    }
    
    XCTAssertEqual(Sum, Expected, @"All IDs should have been recycled");
    
    CCConcurrentIDPoolDestroy(P);
}

@end
