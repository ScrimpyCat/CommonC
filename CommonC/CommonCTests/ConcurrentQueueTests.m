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
#import <stdatomic.h>
#import <pthread.h>

@interface ConcurrentQueueTests : XCTestCase

@end

@implementation ConcurrentQueueTests

static int DestroyedNode2 = 0;
static void NodeDestructor2(void *Ptr)
{
    DestroyedNode2++;
}

-(void) testNodeDestruction
{
    CCConcurrentQueue Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    CCConcurrentQueueNode *N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    
    CCConcurrentQueueDestroy(Queue);
    
    XCTAssertEqual(DestroyedNode2, 1, @"No nodes should be over-retained");
    
    
    DestroyedNode2 = 0;
    Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    CCConcurrentQueueDestroyNode(CCConcurrentQueuePop(Queue));
    
    CCConcurrentQueueDestroy(Queue);
    
    XCTAssertEqual(DestroyedNode2, 1, @"No nodes should be over-retained");
    
    
    DestroyedNode2 = 0;
    Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    CCConcurrentQueueDestroyNode(CCConcurrentQueuePop(Queue));
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    CCConcurrentQueueDestroyNode(CCConcurrentQueuePop(Queue));
    
    CCConcurrentQueueDestroy(Queue);
    
    XCTAssertEqual(DestroyedNode2, 2, @"No nodes should be over-retained");
    
    
    DestroyedNode2 = 0;
    Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    CCConcurrentQueueDestroyNode(CCConcurrentQueuePop(Queue));
    
    CCConcurrentQueueDestroy(Queue);
    
    XCTAssertEqual(DestroyedNode2, 2, @"No nodes should be over-retained");

    
    DestroyedNode2 = 0;
    Queue = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    
    N = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, 0, NULL);
    CCMemorySetDestructor(N, NodeDestructor2);
    
    CCConcurrentQueuePush(Queue, N);
    CCConcurrentQueueDestroyNode(CCConcurrentQueuePop(Queue));
    CCConcurrentQueueDestroyNode(CCConcurrentQueuePop(Queue));
    
    CCConcurrentQueueDestroy(Queue);
    
    XCTAssertEqual(DestroyedNode2, 2, @"No nodes should be over-retained");
}

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

#define PUSH_THREADS 20
#define POP_THREADS 15

#define NODE_COUNT 1000

static _Atomic(int) DestroyedNodes = ATOMIC_VAR_INIT(0);
static void NodeDestructor(void *Ptr)
{
    atomic_fetch_add_explicit(&DestroyedNodes, 1, memory_order_relaxed);
}

static CCConcurrentQueue Q;
static void *Pusher(void *Arg)
{
    for (int Loop = 0; Loop < NODE_COUNT; Loop++)
    {
        CCConcurrentQueueNode *Node = CCConcurrentQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ *(int*)Arg + Loop });
        CCMemorySetDestructor(Node, NodeDestructor);
        CCConcurrentQueuePush(Q, Node);
    }
    
    return NULL;
}

static _Atomic(int) Count = ATOMIC_VAR_INIT(0);
static void *Popper(void *Arg)
{
    uintptr_t Sum = 0;
    for ( ; atomic_load_explicit(&Count, memory_order_relaxed) < (NODE_COUNT * PUSH_THREADS); )
    {
        CCConcurrentQueueNode *Node = CCConcurrentQueuePop(Q);
        if (Node)
        {
            atomic_fetch_add_explicit(&Count, 1, memory_order_relaxed);
            Sum += *(int*)CCConcurrentQueueGetNodeData(Node);
            CCConcurrentQueueDestroyNode(Node);
        }
    }
    
    return (void*)Sum;
}

-(void) testMultiThreading
{
    Q = CCConcurrentQueueCreate(CC_STD_ALLOCATOR);
    
    pthread_t Push[PUSH_THREADS], Pop[POP_THREADS];
    int PushArgs[PUSH_THREADS];
    
    for (int Loop = 0; Loop < PUSH_THREADS; Loop++)
    {
        PushArgs[Loop] = Loop * 100;
        pthread_create(Push + Loop, NULL, Pusher, PushArgs + Loop);
    }
    
    for (int Loop = 0; Loop < POP_THREADS; Loop++)
    {
        pthread_create(Pop + Loop, NULL, Popper, NULL);
    }
    
    for (int Loop = 0; Loop < PUSH_THREADS; Loop++)
    {
        pthread_join(Push[Loop], NULL);
    }
    
    int Sum = 0;
    for (int Loop = 0; Loop < POP_THREADS; Loop++)
    {
        uintptr_t Result = 0;
        pthread_join(Pop[Loop], (void**)&Result);
        Sum += (int)Result;
    }
    
    int Actual = 0;
    for (int Loop = 0; Loop < PUSH_THREADS; Loop++)
    {
        for (int Loop2 = 0; Loop2 < NODE_COUNT; Loop2++)
        {
            Actual += PushArgs[Loop] + Loop2;
        }
    }
    
    XCTAssertEqual(Sum, Actual, @"Should calculate the correct result");
    XCTAssertEqual(atomic_load_explicit(&DestroyedNodes, memory_order_relaxed), (PUSH_THREADS * NODE_COUNT), @"No nodes should be over-retained");
    
    CCConcurrentQueueDestroy(Q);
}

@end
