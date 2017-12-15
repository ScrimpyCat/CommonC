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

@end
