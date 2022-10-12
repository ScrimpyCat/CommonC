/*
 *  Copyright (c) 2022, Stefan Johnson
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
#define T int
#import "ConcurrentPool.h"

@interface ConcurrentPoolTests : XCTestCase
@end

@implementation ConcurrentPoolTests

-(void) testAddingItems
{
#define POOL_MAX 4
    CCConcurrentPool *Pool = CCConcurrentPoolCreate(int, POOL_MAX);
    int *x;
    
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
    
    CCConcurrentPoolPush(Pool, ((int[]){ 1, 2, 3 }), 3, POOL_MAX);
    
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 1, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 2, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 3, @"Should retrieve the correct item");
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
    
    CCConcurrentPoolPush(Pool, ((int[]){ 4, 5 }), 2, POOL_MAX);
    CCConcurrentPoolPush(Pool, ((int[]){ 6, 7 }), 2, POOL_MAX);
    
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 4, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 5, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 6, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 7, @"Should retrieve the correct item");
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
    
    CCConcurrentPoolPush(Pool, ((int[]){ 1, 2, 3, 4 }), 4, POOL_MAX);
    CCConcurrentPoolPush(Pool, ((int[]){ 10, 11 }), 2, POOL_MAX);
    
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 10, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 11, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 3, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 4, @"Should retrieve the correct item");
    
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 10, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 11, @"Should retrieve the correct item");
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
    
    
    CCConcurrentPoolStage Stage = CCConcurrentPoolStageBegin(Pool);
    
    CCConcurrentPoolStagePush(Pool, 20, POOL_MAX, &Stage);
    CCConcurrentPoolStagePush(Pool, 21, POOL_MAX, &Stage);
    
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
    
    CCConcurrentPoolStageCommit(Pool, &Stage);
    
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 20, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 21, @"Should retrieve the correct item");
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
    
    CCConcurrentPoolStagePush(Pool, 30, POOL_MAX, &Stage);
    CCConcurrentPoolStagePush(Pool, 31, POOL_MAX, &Stage);
    
    CCConcurrentPoolStageCommit(Pool, &Stage);
    
    CCConcurrentPoolStagePush(Pool, 32, POOL_MAX, &Stage);
    
    CCConcurrentPoolStageCommit(Pool, &Stage);
    
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 30, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 31, @"Should retrieve the correct item");
    XCTAssertTrue(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should retrieve an item");
    XCTAssertEqual(*x, 32, @"Should retrieve the correct item");
    XCTAssertFalse(CCConcurrentPoolPop_strong(Pool, &x, POOL_MAX), @"Should not retrieve an item");
}

@end
