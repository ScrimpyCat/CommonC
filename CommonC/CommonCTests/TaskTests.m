/*
 *  Copyright (c) 2016, Stefan Johnson
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
#import "Task.h"
#import "Extensions.h"
#import <stdatomic.h>
#import <pthread.h>

@interface TaskTests : XCTestCase

@end

@implementation TaskTests

static _Bool DestructedInput = FALSE, DestructedOutput = FALSE;
static void InputDestructor(void *Ptr)
{
    DestructedInput = TRUE;
}

static void OutputDestructor(void *Ptr)
{
    DestructedOutput = TRUE;
}

-(void) testDestructing
{
    CCTask Task = CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 0, OutputDestructor, 0, NULL, InputDestructor);
    CCTaskDestroy(Task);
    
    XCTAssertFalse(DestructedInput, @"Input destructor should not be called");
    XCTAssertFalse(DestructedOutput, @"Output destructor should not be called");
    
    
    Task = CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, OutputDestructor, 16, NULL, InputDestructor);
    CCTaskDestroy(Task);
    
    XCTAssertTrue(DestructedInput, @"Input destructor should be called");
    XCTAssertTrue(DestructedOutput, @"Output destructor should be called");
}

static _Bool OutputIsZeroed = FALSE;
static void TestFunc(const int *In, int *Out)
{
    OutputIsZeroed = !*Out;
    *Out = *In;
}

-(void) testRunning
{
    CCTask Task = CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)TestFunc, sizeof(int), NULL, sizeof(int), &(int){ 1234 }, NULL);
    
    XCTAssertFalse(CCTaskIsFinished(Task), @"Task should not have run yet");
    
    CCTaskRun(Task);
    
    XCTAssertTrue(CCTaskIsFinished(Task), @"Task should have run");
    XCTAssertEqual(*(int*)CCTaskGetResult(Task), 1234, @"Should return the correct value");
    XCTAssertTrue(OutputIsZeroed, @"Initial output should be set to zeroes");
    
    CCTaskDestroy(Task);
}

#define THREAD_COUNT 10
#define RUN_COUNT 10
#define COUNT 1000000

_Atomic(int) Begin;
static CCTask ConcurrentTask;

static void Inc(const void *In, _Atomic(uint64_t) *Out)
{
    atomic_fetch_add(&Begin, 1);
    for (int Loop = 0; Loop < COUNT; Loop++) atomic_fetch_add(Out, 1);
}


static void *Runner(void *Arg)
{
    for (int Loop = 0; Loop < RUN_COUNT; Loop++) CCTaskRun(ConcurrentTask);
    
    return NULL;
}

-(void) testConcurrentRun
{
    ConcurrentTask = CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)Inc, sizeof(_Atomic(uint64_t)), NULL, 0, NULL, NULL);
    
    pthread_t Runners[THREAD_COUNT];
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(Runners + Loop, NULL, Runner, NULL);
    }
    
    while (atomic_load(&Begin) != (RUN_COUNT * THREAD_COUNT)) CC_SPIN_WAIT();
    uint64_t Result = atomic_load((_Atomic(uint64_t)*)CCTaskGetResult(ConcurrentTask));
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(Runners[Loop], NULL);
    }
    
    CCTaskDestroy(ConcurrentTask);
    
    XCTAssertEqual(Result, RUN_COUNT * THREAD_COUNT * COUNT, @"Should return the correct result");
}

@end
