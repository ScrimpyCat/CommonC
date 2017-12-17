/*
 *  Copyright (c) 2017, Stefan Johnson
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
#import "ConcurrentBuffer.h"
#import <stdatomic.h>
#import <pthread.h>

@interface ConcurrentBufferTests : XCTestCase

@end

@implementation ConcurrentBufferTests

-(void) testReadWithoutWrite
{
    CCConcurrentBuffer Buffer = CCConcurrentBufferCreate(CC_STD_ALLOCATOR, NULL);
    
    XCTAssertEqual(CCConcurrentBufferReadData(Buffer), NULL, @"Should return NULL if no buffer was written to");
    XCTAssertEqual(CCConcurrentBufferReadData(Buffer), NULL, @"Should return NULL if no buffer was written to");
    
    CCConcurrentBufferDestroy(Buffer);
}

-(void) testReadWithWrite
{
    CCConcurrentBuffer Buffer = CCConcurrentBufferCreate(CC_STD_ALLOCATOR, NULL);
    
    CCConcurrentBufferWriteData(Buffer, (void*)1);
    XCTAssertEqual(CCConcurrentBufferReadData(Buffer), (void*)1, @"Should read the corret buffer");
    XCTAssertEqual(CCConcurrentBufferReadData(Buffer), NULL, @"Should read the correct buffer");
    
    CCConcurrentBufferWriteData(Buffer, (void*)2);
    CCConcurrentBufferWriteData(Buffer, (void*)3);
    XCTAssertEqual(CCConcurrentBufferReadData(Buffer), (void*)3, @"Should read the corret buffer");
    
    CCConcurrentBufferDestroy(Buffer);
}

static int DestructorCount = 0, DestructorSum = 0;
void Destructor(void *Data)
{
    DestructorCount++;
    DestructorSum += (uintptr_t)Data;
}

-(void) testDestructorCallback
{
    CCConcurrentBuffer Buffer = CCConcurrentBufferCreate(CC_STD_ALLOCATOR, Destructor);
    
    CCConcurrentBufferWriteData(Buffer, (void*)1); //destroyed
    CCConcurrentBufferWriteData(Buffer, (void*)2); //destroyed
    CCConcurrentBufferWriteData(Buffer, (void*)4);
    
    XCTAssertEqual(DestructorCount, 2, @"Should have called the destructor 2 times");
    XCTAssertEqual(DestructorSum, 3, @"Should receive the correct buffers");
    
    CCConcurrentBufferReadData(Buffer);
    CCConcurrentBufferWriteData(Buffer, (void*)8);
    
    XCTAssertEqual(DestructorCount, 2, @"Should have called the destructor 2 times");
    XCTAssertEqual(DestructorSum, 3, @"Should receive the correct buffers");
    
    CCConcurrentBufferDestroy(Buffer);
}

#define READ_THREADS 20
#define WRITE_THREADS 10

#define COUNT 1000000
#define NULL_READ_ALLOWANCE 1000

static _Atomic(int) DestroyedBuffers = ATOMIC_VAR_INIT(0);
static void BufferDestructor(void *Ptr)
{
    atomic_fetch_add_explicit(&DestroyedBuffers, 1, memory_order_relaxed);
}

static CCConcurrentBuffer B;
static void *Writer(void *Arg)
{
    for (int Loop = 0; Loop < COUNT; Loop++)
    {
        CCConcurrentBufferWriteData(B, (void*)1);
    }
    
    return NULL;
}

static _Atomic(int) Count = ATOMIC_VAR_INIT(0);
static void *Reader(void *Arg)
{
    uintptr_t Sum = 0;
    for (int NullCount = 0; NullCount < NULL_READ_ALLOWANCE; NullCount++)
    {
        uintptr_t Value = (uintptr_t)CCConcurrentBufferReadData(B);
        Sum += Value;
        if (Value == 0) NullCount++;
    }

    return (void*)Sum;
}

-(void) testMultiThreading
{
    atomic_store(&DestroyedBuffers, 0);
    atomic_store(&Count, 0);
    B = CCConcurrentBufferCreate(CC_STD_ALLOCATOR, BufferDestructor);
    
    pthread_t Write[WRITE_THREADS], Read[READ_THREADS];
    for (int Loop = 0; Loop < WRITE_THREADS; Loop++)
    {
        pthread_create(Write + Loop, NULL, Writer, NULL);
    }
    
    for (int Loop = 0; Loop < READ_THREADS; Loop++)
    {
        pthread_create(Read + Loop, NULL, Reader, NULL);
    }
    
    for (int Loop = 0; Loop < WRITE_THREADS; Loop++)
    {
        pthread_join(Write[Loop], NULL);
    }
    
    int Sum = atomic_load_explicit(&DestroyedBuffers, memory_order_relaxed);
    for (int Loop = 0; Loop < READ_THREADS; Loop++)
    {
        uintptr_t Result = 0;
        pthread_join(Read[Loop], (void**)&Result);
        Sum += (int)Result;
    }
    
    Sum += (int)CCConcurrentBufferReadData(B);
    
    CCConcurrentBufferDestroy(B);
    
    XCTAssertEqual(Sum, (WRITE_THREADS * COUNT), @"No buffers should be over-retained");
}

@end
