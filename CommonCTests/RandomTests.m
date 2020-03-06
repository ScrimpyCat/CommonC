/*
 *  Copyright (c) 2020, Stefan Johnson
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
#define CC_RANDOM_XORSHIFT 1
#import "Random.h"

@interface RandomTests : XCTestCase

@end

@implementation RandomTests

-(void) testGlobalState
{
    uint32_t Values[4];
    
    Values[0] = CCRandom();
    Values[1] = CCRandom();
    
    typeof(CCRandomState) State = CCRandomState;
    Values[2] = CCRandom();
    Values[3] = CCRandom();
    
    XCTAssertEqual(Values[0], 270369, @"Should be reproducible");
    XCTAssertEqual(Values[1], 67634689, @"Should be reproducible");
    XCTAssertEqual(Values[2], 2647435461, @"Should be reproducible");
    XCTAssertEqual(Values[3], 307599695, @"Should be reproducible");
    
    CCRandomState = State;
    
    XCTAssertEqual(Values[2], CCRandom(), @"Should return to earlier stage");
    XCTAssertEqual(Values[3], CCRandom(), @"Should return to earlier stage");
    
    
    CCRandomSeed(3);
    Values[0] = CCRandom();
    Values[1] = CCRandom();
    
    State = CCRandomState;
    Values[2] = CCRandom();
    Values[3] = CCRandom();
    
    XCTAssertEqual(Values[0], 811107, @"Should be reproducible");
    XCTAssertEqual(Values[1], 201886211, @"Should be reproducible");
    XCTAssertEqual(Values[2], 3025432647, @"Should be reproducible");
    XCTAssertEqual(Values[3], 1909268553, @"Should be reproducible");
    
    CCRandomState = State;
    
    XCTAssertEqual(Values[2], CCRandom(), @"Should return to earlier stage");
    XCTAssertEqual(Values[3], CCRandom(), @"Should return to earlier stage");
    
    
    CCRandomSeed(0);
    
    XCTAssertEqual(CCRandom(), 270369, @"Should be reproducible");
    XCTAssertEqual(CCRandom(), 67634689, @"Should be reproducible");
    XCTAssertEqual(CCRandom(), 2647435461, @"Should be reproducible");
    XCTAssertEqual(CCRandom(), 307599695, @"Should be reproducible");
    
    CCRandomState = State;
    CCData Data = CCRandomGetState();
    
    XCTAssertEqual(Values[2], CCRandom(), @"Should return to earlier stage");
    XCTAssertEqual(Values[3], CCRandom(), @"Should return to earlier stage");
    
    CCRandomSetState(Data);
    
    XCTAssertEqual(Values[2], CCRandom(), @"Should return to earlier stage");
    XCTAssertEqual(Values[3], CCRandom(), @"Should return to earlier stage");
    
    CCDataDestroy(Data);
}

@end
