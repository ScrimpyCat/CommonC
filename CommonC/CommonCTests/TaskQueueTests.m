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
    
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[0], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[1], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[2], @"Should retrieve the correct task");
    
    CCTaskQueueDestroy(Queue);
    
    
    Queue = CCTaskQueueCreate(CC_STD_ALLOCATOR, CCTaskQueueExecuteSerially, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, CCEpochGarbageCollector));
    CCTaskQueuePush(Queue, Tasks[0]);
    CCTaskQueuePush(Queue, Tasks[1]);
    CCTaskQueuePush(Queue, Tasks[2]);
    
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[0], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should not retrieve the next task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should not retrieve the next task");
    
    CCTaskRun(Tasks[0]);
    
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[1], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should not retrieve the next task");
    
    CCTaskRun(Tasks[1]);
    
    XCTAssertEqual(CCTaskQueuePop(Queue), Tasks[2], @"Should retrieve the correct task");
    XCTAssertEqual(CCTaskQueuePop(Queue), NULL, @"Should be empty");
    
    CCTaskQueueDestroy(Queue);
    
    CCTaskDestroy(Tasks[0]);
    CCTaskDestroy(Tasks[1]);
    CCTaskDestroy(Tasks[2]);
}

@end
