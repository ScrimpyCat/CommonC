/*
 *  Copyright (c) 2024, Stefan Johnson
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

#define Titem int
#include "ConcurrentSwapBuffer.h"

#define Titem float
#include "ConcurrentSwapBuffer.h"

@interface ConcurrentSwapBufferTests : XCTestCase

@end

@implementation ConcurrentSwapBufferTests

-(void) testSwappingBuffers
{
    CCConcurrentSwapBuffer(int) Swap = CC_CONCURRENT_SWAP_BUFFER_INIT;
    
    memset(Swap.buffer, 0, sizeof(int) * 3);
    
    int *Future = CCConcurrentSwapBufferGetFuture(&Swap);
    
    *Future = 1;
    
    Future = CCConcurrentSwapBufferGetFuture(&Swap);
    
    *Future = 2;
    
    CCConcurrentSwapBufferApply(&Swap);
    
    Future = CCConcurrentSwapBufferGetFuture(&Swap);
    
    *Future = 3;
    
    const int *Read = CCConcurrentSwapBufferRead(&Swap);
    
    XCTAssertEqual(*Read, 2, @"Shouold get the correct buffer");
    
    Read = CCConcurrentSwapBufferRead(&Swap);
    
    XCTAssertEqual(*Read, 2, @"Shouold get the correct buffer");
    
    CCConcurrentSwapBufferApply(&Swap);
    
    Read = CCConcurrentSwapBufferRead(&Swap);
    
    XCTAssertEqual(*Read, 3, @"Shouold get the correct buffer");
    
    
    
    CCConcurrentSwapBuffer(float) SwapF = CC_CONCURRENT_SWAP_BUFFER_INIT;
    
    memset(SwapF.buffer, 0, sizeof(float) * 3);
    
    float *FutureF = CCConcurrentSwapBufferGetFuture(&SwapF);
    
    *FutureF = 1.0f;
    
    FutureF = CCConcurrentSwapBufferGetFuture(&SwapF);
    
    *FutureF = 2.0f;
    
    CCConcurrentSwapBufferApply(&SwapF);
    
    FutureF = CCConcurrentSwapBufferGetFuture(&SwapF);
    
    *FutureF = 3.0f;
    
    const float *ReadF = CCConcurrentSwapBufferRead(&SwapF);
    
    XCTAssertEqual(*ReadF, 2.0f, @"Shouold get the correct buffer");
    
    ReadF = CCConcurrentSwapBufferRead(&SwapF);
    
    XCTAssertEqual(*ReadF, 2.0f, @"Shouold get the correct buffer");
    
    CCConcurrentSwapBufferApply(&SwapF);
    
    ReadF = CCConcurrentSwapBufferRead(&SwapF);
    
    XCTAssertEqual(*ReadF, 3.0f, @"Shouold get the correct buffer");
}

@end
