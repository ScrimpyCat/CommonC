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
#import "ConcurrentIndexBuffer.h"

@interface ConcurrentIndexBuffer : XCTestCase

@end

@implementation ConcurrentIndexBuffer

-(void) testReadWithoutWrite
{
    CCConcurrentIndexBuffer IndexBuffer = CCConcurrentIndexBufferCreate(CC_STD_ALLOCATOR, 3);
    
    XCTAssertFalse(CCConcurrentIndexBufferReadAcquire(IndexBuffer, &(size_t){ 0 }), @"Should return false no index was staged");
    XCTAssertFalse(CCConcurrentIndexBufferReadAcquire(IndexBuffer, &(size_t){ 0 }), @"Should return false no index was staged");
    
    CCConcurrentIndexBufferDestroy(IndexBuffer);
}

-(void) testReadWithWrite
{
    CCConcurrentIndexBuffer IndexBuffer = CCConcurrentIndexBufferCreate(CC_STD_ALLOCATOR, 3);
    
    size_t Index = CCConcurrentIndexBufferWriteAcquire(IndexBuffer), ReadIndex;
    XCTAssertFalse(CCConcurrentIndexBufferReadAcquire(IndexBuffer, &ReadIndex), @"Should return false no index was staged");
    
    CCConcurrentIndexBufferStage(IndexBuffer, Index);
    XCTAssertTrue(CCConcurrentIndexBufferReadAcquire(IndexBuffer, &ReadIndex), @"Should return true when index is staged");
    XCTAssertEqual(Index, ReadIndex, @"Index should match the last staged");
    
    CCConcurrentIndexBufferDiscard(IndexBuffer, ReadIndex);
    XCTAssertFalse(CCConcurrentIndexBufferReadAcquire(IndexBuffer, &ReadIndex), @"Should return false no index was staged");
    
    Index = CCConcurrentIndexBufferWriteAcquire(IndexBuffer);
    CCConcurrentIndexBufferDiscard(IndexBuffer, Index);
    XCTAssertFalse(CCConcurrentIndexBufferReadAcquire(IndexBuffer, &ReadIndex), @"Should return false no index was staged");
    
    CCConcurrentIndexBufferDestroy(IndexBuffer);
}

@end
