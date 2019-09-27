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

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import "BigInt.h"

@interface BigIntTests : XCTestCase

@end

@implementation BigIntTests

-(void) setUp
{
    [super setUp];
}

-(void) tearDown
{
    [super tearDown];
}

-(void) testSetters
{
    CCBigInt Integer = CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntSet(Integer, CC_STRING("0x10f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x10f, @"Should contain the correct component value");
    
    CCString Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000000010f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x1011121314151617, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10111213141516118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x101112131415161, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x010111213141516118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x1011121314151618191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x10111213141516, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x001011121314151618191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x101112131415118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x1011121314151, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000101112131415118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10111213141518191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x101112131415, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000010111213141518191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x1011121314118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x10111213141, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000001011121314118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x101112131418191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x1011121314, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000101112131418191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10111213118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x101112131, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000010111213118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x1011121318191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x10111213, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000001011121318191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x101112118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x1011121, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000101112118191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10111218191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 4, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0x101112, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0x18191a1b1c1d1e1f, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0x2021222324252627, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x28292a2b2c2d2e2f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000010111218191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    CCBigIntDestroy(Integer);
}

@end
