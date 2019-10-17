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
#import "Queue.h"

@interface QueueTests : XCTestCase

@end

@implementation QueueTests

-(void) testEmptyDequeues
{
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCQueuePop(Queue), NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(CCQueuePop(Queue), NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(CCQueuePop(Queue), NULL, @"Should return null when nothing left to dequeue");
    
    CCQueueDestroy(Queue);
}

-(void) testNodeReuse
{
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    
    CCQueuePush(Queue, CCQueuePop(Queue));
    
    CCQueueNode *N = CCQueuePop(Queue);
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N), 2, @"Should return the correct element");
    CCQueueDestroyNode(N);
    
    N = CCQueuePop(Queue);
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N), 1, @"Should return the correct element");
    CCQueueDestroyNode(N);
    
    CCQueueDestroy(Queue);
}

-(void) testOrdering
{
    CCQueueNode *N[10] = { NULL };
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);

    N[0] = CCQueuePop(Queue);

    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    N[1] = CCQueuePop(Queue);

    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 4 }));

    N[2] = CCQueuePop(Queue);

    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 5 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 6 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 7 }));

    N[3] = CCQueuePop(Queue);
    N[4] = CCQueuePop(Queue);
    N[5] = CCQueuePop(Queue);
    N[6] = CCQueuePop(Queue);
    N[7] = CCQueuePop(Queue);
    N[8] = CCQueuePop(Queue);
    N[9] = CCQueuePop(Queue);

    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 8 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 9 }));

    CCQueueDestroy(Queue);
    
    XCTAssertEqual(N[0], NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[1]), 1, @"Should return the first element");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[2]), 2, @"Should return the second element");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[3]), 3, @"Should return the third element");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[4]), 4, @"Should return the fourth element");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[5]), 5, @"Should return the fifth element");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[6]), 6, @"Should return the sixth element");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(N[7]), 7, @"Should return the seventh element");
    XCTAssertEqual(N[8], NULL, @"Should return null when nothing left to dequeue");
    XCTAssertEqual(N[9], NULL, @"Should return null when nothing left to dequeue");
    
    for (int Loop = 0; Loop < 10; Loop++)
    {
        if (N[Loop])
        {
            CCQueueDestroyNode(N[Loop]);
        }
    }
}

-(void) testPeeking
{
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCQueuePeek(Queue), NULL, @"Should return null when nothing left in the queue");
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    
    XCTAssertEqual(*(int*)CCQueueGetNodeData(CCQueuePeek(Queue)), 1, @"Should return the first element");
    
    CCQueueDestroyNode(CCQueuePop(Queue));
    XCTAssertEqual(*(int*)CCQueueGetNodeData(CCQueuePeek(Queue)), 2, @"Should return the first element");
    
    CCQueueDestroyNode(CCQueuePop(Queue));
    XCTAssertEqual(*(int*)CCQueueGetNodeData(CCQueuePeek(Queue)), 3, @"Should return the first element");
    
    CCQueueDestroyNode(CCQueuePop(Queue));
    XCTAssertEqual(CCQueuePeek(Queue), NULL, @"Should return null when nothing left in the queue");
    
    CCQueueDestroy(Queue);
}

-(void) testCount
{
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCQueueGetCount(Queue), 0, @"Should get the correct count");
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    XCTAssertEqual(CCQueueGetCount(Queue), 1, @"Should get the correct count");
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    XCTAssertEqual(CCQueueGetCount(Queue), 2, @"Should get the correct count");
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    XCTAssertEqual(CCQueueGetCount(Queue), 3, @"Should get the correct count");
    
    CCQueueDestroyNode(CCQueuePop(Queue));
    XCTAssertEqual(CCQueueGetCount(Queue), 2, @"Should get the correct count");
    
    CCQueueDestroyNode(CCQueuePop(Queue));
    XCTAssertEqual(CCQueueGetCount(Queue), 1, @"Should get the correct count");
    
    CCQueueDestroyNode(CCQueuePop(Queue));
    XCTAssertEqual(CCQueueGetCount(Queue), 0, @"Should get the correct count");
    
    CCQueueDestroy(Queue);
}

-(void) testEnumerating
{
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);
        
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 4 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 5 }));
    
    CCEnumerable Enumerable;
    CCQueueGetEnumerable(Queue, &Enumerable);
    
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 1, @"Should be set to the head");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 3, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 3, @"Should get the current value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 4, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Should get the next value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetHead(&Enumerable), 1, @"Should be set to the head");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 2, @"Should get the next value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 1, @"Should get the previous value");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetHead(&Enumerable), 1, @"Should be set to the head");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetTail(&Enumerable), 5, @"Should be set to the tail");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 4, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 3, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerableGetCurrent(&Enumerable), 3, @"Should get the current value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 2, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 1, @"Should get the previous value");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetTail(&Enumerable), 5, @"Should be set to the tail");
    XCTAssertEqual(*(int*)CCEnumerablePrevious(&Enumerable), 4, @"Should get the previous value");
    XCTAssertEqual(*(int*)CCEnumerableNext(&Enumerable), 5, @"Should get the next value");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Should be at the end");
    
    XCTAssertEqual(*(int*)CCEnumerableGetTail(&Enumerable), 5, @"Should be set to the tail");
    XCTAssertEqual(CCEnumerableNext(&Enumerable), NULL, @"Should be at the end");
    
    CCQueueDestroy(Queue);
}

@end
