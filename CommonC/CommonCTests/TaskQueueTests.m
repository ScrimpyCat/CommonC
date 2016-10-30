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
#import "TaskQueue.h"
#import "EpochGarbageCollector.h"
#import <stdatomic.h>
#import <pthread.h>

@interface TaskQueueTests : XCTestCase

@end

@implementation TaskQueueTests

static int DestructedCount = 0;
static void TestDestructor(void *Ptr)
{
    DestructedCount++;
}

-(void) testDestruction
{
    CCTaskQueue Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteConcurrently, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueueDestroy(Queue);
    
    XCTAssertEqual(DestructedCount, 3, @"Should destroy tasks");
    
    
    DestructedCount = 0;
    Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteConcurrently, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    
    CCTask Task1 = CCTaskQueuePop(Queue);
    CCTask Task2 = CCTaskQueuePop(Queue);
    
    CCTaskQueueDestroy(Queue);
    
    XCTAssertEqual(DestructedCount, 1, @"Should destroy tasks");
    CCTaskDestroy(Task1);
    CCTaskDestroy(Task2);
    XCTAssertEqual(DestructedCount, 3, @"Should destroy tasks");
    
    
    DestructedCount = 0;
    Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteSerially, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, (CCTaskFunction)0x1, 16, TestDestructor, 0, NULL, NULL));
    
    Task1 = CCTaskQueuePop(Queue);
    Task2 = CCTaskQueuePop(Queue);
    
    CCTaskQueueDestroy(Queue);
    
    XCTAssertEqual(DestructedCount, 2, @"Should destroy tasks");
    CCTaskDestroy(Task1);
    XCTAssertEqual(Task2, NULL, @"Should be null");
    XCTAssertEqual(DestructedCount, 3, @"Should destroy tasks");
}

static void TestFunc(const void *In, void *Out)
{
}

-(void) testExecution
{
    CCTask Tasks[3] = {
        CCTaskCreate(CC_STD_ALLOCATOR, TestFunc, 0, NULL, 0, NULL, NULL),
        CCTaskCreate(CC_STD_ALLOCATOR, TestFunc, 0, NULL, 0, NULL, NULL),
        CCTaskCreate(CC_STD_ALLOCATOR, TestFunc, 0, NULL, 0, NULL, NULL)
    };
    
    CCTaskQueue Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteConcurrently, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    CCTaskQueuePush(Queue, Tasks[0]);
    CCTaskQueuePush(Queue, Tasks[1]);
    CCTaskQueuePush(Queue, Tasks[2]);
    
    XCTAssertFalse(CCTaskQueueIsEmpty(Queue), @"Should not be empty");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[0], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[1], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[2], @"Should retrieve the correct task");
    XCTAssertTrue(CCTaskQueueIsEmpty(Queue), @"Should be empty");
    
    CCTaskQueueDestroy(Queue);
    
    
    Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteSerially, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    CCTaskQueuePush(Queue, Tasks[0]);
    CCTaskQueuePush(Queue, Tasks[1]);
    CCTaskQueuePush(Queue, Tasks[2]);
    
    XCTAssertFalse(CCTaskQueueIsEmpty(Queue), @"Should not be empty");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[0], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should not retrieve the next task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should not retrieve the next task");
    
    CCTaskRun(Tasks[0]);
    
    XCTAssertFalse(CCTaskQueueIsEmpty(Queue), @"Should not be empty");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[1], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should not retrieve the next task");
    
    CCTaskRun(Tasks[1]);
    
    XCTAssertFalse(CCTaskQueueIsEmpty(Queue), @"Should not be empty");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[2], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should be empty");
    XCTAssertTrue(CCTaskQueueIsEmpty(Queue), @"Should be empty");
    
    CCTaskQueueDestroy(Queue);
    
    CCTaskDestroy(Tasks[0]);
    CCTaskDestroy(Tasks[1]);
    CCTaskDestroy(Tasks[2]);
}

#define THREAD_COUNT 10
#define TASK_COUNT 100
#define COUNT 1000000

static _Atomic(uint64_t) ConcurrentCount = ATOMIC_VAR_INIT(UINT64_C(0));
static uint64_t SerialCount = 0;

static void SafeInc(const void *In, void *Out)
{
    for (int Loop = 0; Loop < COUNT; Loop++) atomic_fetch_add(&ConcurrentCount, 1);
}

static void UnsafeInc(const void *In, void *Out)
{
    for (int Loop = 0; Loop < COUNT; Loop++) SerialCount++;
}

static void *Runner(CCTaskQueue Queue)
{
    while (!CCTaskQueueIsEmpty(Queue))
    {
        CCTask Task = CCTaskQueuePop(Queue);
        if (Task)
        {
            CCTaskRun(Task);
            CCTaskDestroy(Task);
        }
    }
    
    return NULL;
}

-(void) testThreading
{
    CCTaskQueue Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteConcurrently, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    
    for (int Loop = 0; Loop < TASK_COUNT; Loop++) CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, SafeInc, 0, NULL, 0, NULL, NULL));
    
    pthread_t Runners[THREAD_COUNT];
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(Runners + Loop, NULL, (void*(*)(void*))Runner, Queue);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(Runners[Loop], NULL);
    }
    
    XCTAssertTrue(CCTaskQueueIsEmpty(Queue), @"Should be empty");
    XCTAssertEqual(ConcurrentCount, TASK_COUNT * COUNT, @"Should return the correct result");
    
    CCTaskQueueDestroy(Queue);
    
    
    
    Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteSerially, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    
    for (int Loop = 0; Loop < TASK_COUNT; Loop++) CCTaskQueuePush(Queue, CCTaskCreate(CC_STD_ALLOCATOR, UnsafeInc, 0, NULL, 0, NULL, NULL));
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(Runners + Loop, NULL, (void*(*)(void*))Runner, Queue);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(Runners[Loop], NULL);
    }
    
    XCTAssertTrue(CCTaskQueueIsEmpty(Queue), @"Should be empty");
    XCTAssertEqual(SerialCount, TASK_COUNT * COUNT, @"Should return the correct result");
    
    CCTaskQueueDestroy(Queue);
}

@end
