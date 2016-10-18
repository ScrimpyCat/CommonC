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
#import "ConcurrentQueue.h"

@interface ConcurrentQueueTests : XCTestCase

@end

@implementation ConcurrentQueueTests

-(void) testEmptyDequeues
{
    CCConcurrentQueue Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCConcurrentQueuePop(Queue), NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(CCConcurrentQueuePop(Queue), NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(CCConcurrentQueuePop(Queue), NULL, @"Should return null when nothing left to dequeue");
    
    CCConcurrentQueueDestroy(Queue);
}

-(void) testNodeReuse
{
    CCConcurrentQueue Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    
    CCConcurrentQueuePush(Queue, CCConcurrentQueuePop(Queue));
    
    CCConcurrentQueueNode *N = CCConcurrentQueuePop(Queue);
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N), 2, @"Should return the correct element");
    CCConcurrentQueueDestroyNode(N);
    
    N = CCConcurrentQueuePop(Queue);
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N), 1, @"Should return the correct element");
    CCConcurrentQueueDestroyNode(N);
    
    CCConcurrentQueueDestroy(Queue);
}

-(void) testOrdering
{
    CCConcurrentQueueNode *N[10] = { NULL };
    CCConcurrentQueue Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    N[0] = CCConcurrentQueuePop(Queue);
    
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    N[1] = CCConcurrentQueuePop(Queue);
    
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 4 }));
    
    N[2] = CCConcurrentQueuePop(Queue);
    
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 5 }));
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 6 }));
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 7 }));
    
    N[3] = CCConcurrentQueuePop(Queue);
    N[4] = CCConcurrentQueuePop(Queue);
    N[5] = CCConcurrentQueuePop(Queue);
    N[6] = CCConcurrentQueuePop(Queue);
    N[7] = CCConcurrentQueuePop(Queue);
    N[8] = CCConcurrentQueuePop(Queue);
    N[9] = CCConcurrentQueuePop(Queue);
    
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 8 }));
    CCConcurrentQueuePush(Queue, CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 9 }));
    
    CCConcurrentQueueDestroy(Queue);
    
    XCTAssertEqual(N[0], NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[1]), 1, @"Should return the first element");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[2]), 2, @"Should return the second element");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[3]), 3, @"Should return the third element");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[4]), 4, @"Should return the fourth element");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[5]), 5, @"Should return the fifth element");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[6]), 6, @"Should return the sixth element");
    XCTAssertEqual(*(int*)CCConcurrentQueueGetNodeData(N[7]), 7, @"Should return the seventh element");
    XCTAssertEqual(N[8], NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(N[9], NULL, @"Should return null when nothing left to dequeue");
    
    for (int Loop = 0; Loop < 10; Loop++)
    {
        if (N[Loop])
        {
            CCConcurrentQueueDestroyNode(N[Loop]);
        }
    }
}

@end
