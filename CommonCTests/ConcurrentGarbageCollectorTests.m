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

#import <XCTest/XCTest.h>
#import "ConcurrentGarbageCollector.h"
#import "EpochGarbageCollector.h"
#import "LazyGarbageCollector.h"
#import <stdatomic.h>
#import <pthread.h>

@interface ConcurrentGarbageCollectorTests : XCTestCase

@property (readonly) const CCConcurrentGarbageCollectorInterface *gc;
@property (nonatomic) uintptr_t reclaimationSum;

-(void) forceFlush: (CCConcurrentGarbageCollector)gc;

@end

@implementation ConcurrentGarbageCollectorTests

-(const CCConcurrentGarbageCollectorInterface *) gc
{
    return CCEpochGarbageCollector;
}

-(void) forceFlush: (CCConcurrentGarbageCollector)gc
{
    CCConcurrentGarbageCollectorBegin(gc);
    CCConcurrentGarbageCollectorEnd(gc);
    
    CCConcurrentGarbageCollectorBegin(gc);
    CCConcurrentGarbageCollectorEnd(gc);
}

#define THREAD_COUNT 10

static _Atomic(uintptr_t) ReclaimationSum = ATOMIC_VAR_INIT(0);

-(uintptr_t) reclaimationSum
{
    return atomic_load(&ReclaimationSum);
}

-(void) setReclaimationSum: (uintptr_t)value
{
    atomic_store(&ReclaimationSum, value);
}

static void ReclaimationCounter(void *Arg)
{
    atomic_fetch_add_explicit(&ReclaimationSum, (uintptr_t)Arg, memory_order_relaxed);
}

-(void) testManagement
{
    CCConcurrentGarbageCollector GC = CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc);
    
    self.reclaimationSum = 0;
    CCConcurrentGarbageCollectorBegin(GC);
    CCConcurrentGarbageCollectorEnd(GC);
    
    [self forceFlush: GC];
    XCTAssertEqual(self.reclaimationSum, 0, "Should have nothing to reclaim");
    
    
    self.reclaimationSum = 0;
    CCConcurrentGarbageCollectorBegin(GC);
    CCConcurrentGarbageCollectorManage(GC, (void*)1, ReclaimationCounter);
    CCConcurrentGarbageCollectorEnd(GC);
    
    [self forceFlush: GC];
    XCTAssertEqual(self.reclaimationSum, 1, "Should have reclaimed");
    
    
    self.reclaimationSum = 0;
    CCConcurrentGarbageCollectorBegin(GC);
    CCConcurrentGarbageCollectorManage(GC, (void*)2, ReclaimationCounter);
    CCConcurrentGarbageCollectorManage(GC, (void*)3, ReclaimationCounter);
    CCConcurrentGarbageCollectorEnd(GC);
    
    [self forceFlush: GC];
    XCTAssertEqual(self.reclaimationSum, 5, "Should have reclaimed");
    
    
    self.reclaimationSum = 0;
    CCConcurrentGarbageCollectorBegin(GC);
    CCConcurrentGarbageCollectorManage(GC, (void*)4, ReclaimationCounter);
    
    XCTAssertEqual(self.reclaimationSum, 0, "Should not reclaim");
    
    CCConcurrentGarbageCollectorEnd(GC);
    
    [self forceFlush: GC];
    XCTAssertEqual(self.reclaimationSum, 4, "Should have reclaimed");
    
    CCConcurrentGarbageCollectorDestroy(GC);
}

#define CYCLE_COUNT 1000000

typedef struct {
    ConcurrentGarbageCollectorTests *test;
    uintptr_t value;
} ThreadArg;

static CCConcurrentGarbageCollector GC;
static void *Cycles(void *Arg)
{
    for (int Loop = 0; Loop < CYCLE_COUNT; Loop++)
    {
        CCConcurrentGarbageCollectorBegin(GC);
        CCConcurrentGarbageCollectorEnd(GC);
    }
    
    [((ThreadArg*)Arg)->test forceFlush: GC];
    
    return NULL;
}

static void *ManagedCycles(void *Arg)
{
    for (int Loop = 0; Loop < CYCLE_COUNT; Loop++)
    {
        CCConcurrentGarbageCollectorBegin(GC);
        CCConcurrentGarbageCollectorManage(GC, (void*)(((ThreadArg*)Arg)->value + Loop), ReclaimationCounter);
        CCConcurrentGarbageCollectorEnd(GC);
    }
    
    [((ThreadArg*)Arg)->test forceFlush: GC];
    
    return NULL;
}

-(void) testSingleThreadedManage
{
    self.reclaimationSum = 0;
    GC = CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc);
    
    pthread_t Threads[THREAD_COUNT - 1];
    ThreadArg Args[THREAD_COUNT - 1];
    
    for (int Loop = 0; Loop < THREAD_COUNT - 1; Loop++)
    {
        Args[Loop] = (ThreadArg){ .value = 0, .test = self };
        pthread_create(Threads + Loop, NULL, Cycles, Args + Loop);
    }
    
    ManagedCycles(&(ThreadArg){ .value = 1, .test = self });
    
    for (int Loop = 0; Loop < THREAD_COUNT - 1; Loop++)
    {
        pthread_join(Threads[Loop], NULL);
    }
    
    CCConcurrentGarbageCollectorDestroy(GC);
    
    size_t CorrectSum = 0;
    for (int Loop = 0; Loop < 1; Loop++)
    {
        for (int Loop2 = 0; Loop2 < CYCLE_COUNT; Loop2++)
        {
            CorrectSum += Loop + (Loop2 + 1);
        }
    }
    
    XCTAssertEqual(self.reclaimationSum, CorrectSum, "Should have reclaimed all managed entities");
}

-(void) testMutliThreadedManage
{
    self.reclaimationSum = 0;
    GC = CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc);
    
    pthread_t Threads[THREAD_COUNT];
    ThreadArg Args[THREAD_COUNT];
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        Args[Loop] = (ThreadArg){ .value = Loop + 1, .test = self };
        pthread_create(Threads + Loop, NULL, ManagedCycles, Args + Loop);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(Threads[Loop], NULL);
    }
    
    CCConcurrentGarbageCollectorDestroy(GC);
    
    size_t CorrectSum = 0;
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        for (int Loop2 = 0; Loop2 < CYCLE_COUNT; Loop2++)
        {
            CorrectSum += Loop + (Loop2 + 1);
        }
    }
    
    XCTAssertEqual(self.reclaimationSum, CorrectSum, "Should have reclaimed all managed entities");
}

static void *ManagedCycles2(void *Arg)
{
    for (int Loop = 0; Loop < CYCLE_COUNT; Loop++)
    {
        CCConcurrentGarbageCollectorBegin(GC);
        for (int Loop2 = 0, Wait = arc4random() % 20; Loop2 < Wait; Loop2++);
        CCConcurrentGarbageCollectorManage(GC, (void*)(((ThreadArg*)Arg)->value + Loop), ReclaimationCounter);
        for (int Loop2 = 0, Wait = arc4random() % 20; Loop2 < Wait; Loop2++);
        CCConcurrentGarbageCollectorEnd(GC);
    }
    
    [((ThreadArg*)Arg)->test forceFlush: GC];
    
    return NULL;
}

-(void) testMutliThreadedManage2
{
    self.reclaimationSum = 0;
    GC = CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc);
    
    pthread_t Threads[THREAD_COUNT];
    ThreadArg Args[THREAD_COUNT];
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        Args[Loop] = (ThreadArg){ .value = Loop + 1, .test = self };
        pthread_create(Threads + Loop, NULL, ManagedCycles2, Args + Loop);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(Threads[Loop], NULL);
    }
    
    CCConcurrentGarbageCollectorDestroy(GC);
    
    size_t CorrectSum = 0;
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        for (int Loop2 = 0; Loop2 < CYCLE_COUNT; Loop2++)
        {
            CorrectSum += Loop + (Loop2 + 1);
        }
    }
    
    XCTAssertEqual(self.reclaimationSum, CorrectSum, "Should have reclaimed all managed entities");
}

static _Bool References[CYCLE_COUNT] = {0};
static void ReclaimReference(void *Ref)
{
    References[(uintptr_t)Ref] = TRUE;
}

static _Bool EarlyRecycle = FALSE;
static void *ManagedCycles3(void *Arg)
{
    uintptr_t LocalSum = 0;
    for (int Loop = 0; Loop < CYCLE_COUNT; Loop++)
    {
        CCConcurrentGarbageCollectorBegin(GC);
        CCConcurrentGarbageCollectorManage(GC, (void*)(uintptr_t)Loop, ReclaimReference);
        
        LocalSum += ((ThreadArg*)Arg)->value + Loop;
        
        for (int Loop2 = 0, Wait = arc4random() % 30; Loop2 < Wait; Loop2++);
        if (References[Loop]) EarlyRecycle = TRUE;
        
        CCConcurrentGarbageCollectorEnd(GC);
    }
    
    [((ThreadArg*)Arg)->test forceFlush: GC];
    
    return NULL;
}

-(void) testEarlyReclaimation
{
    memset(References, 0, sizeof(_Bool) * CYCLE_COUNT);
    
    GC = CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc);
    
    pthread_t Threads[THREAD_COUNT - 1];
    ThreadArg Args[THREAD_COUNT - 1];
    
    for (int Loop = 0; Loop < THREAD_COUNT - 1; Loop++)
    {
        Args[Loop] = (ThreadArg){ .value = 0, .test = self };
        pthread_create(Threads + Loop, NULL, Cycles, Args + Loop);
    }
    
    ManagedCycles3(&(ThreadArg){ .value = 0, .test = self });
    
    for (int Loop = 0; Loop < THREAD_COUNT - 1; Loop++)
    {
        pthread_join(Threads[Loop], NULL);
    }
    
    CCConcurrentGarbageCollectorDestroy(GC);
    
    XCTAssertFalse(EarlyRecycle, "Should not have reclaimed entities still in use");
}

@end

@interface ConcurrentGarbageCollectorTestsLazyGC : ConcurrentGarbageCollectorTests
@end

@implementation ConcurrentGarbageCollectorTestsLazyGC

-(const CCConcurrentGarbageCollectorInterface *) gc
{
    return CCLazyGarbageCollector;
}

-(void) forceFlush: (CCConcurrentGarbageCollector)gc
{
}

@end
