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
#import "BigIntFast.h"

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
    
    CCBigIntSet(Integer, 0x10f);
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x10f, @"Should contain the correct component value");
    
    CCString Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000000010f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -0x10f);
    
    XCTAssertTrue(CCBigIntGetSign(Integer), @"Should be negative");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x10f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x000000000000010f")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigInt IntegerB = CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntSet(IntegerB, CC_STRING("0x1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
    CCBigIntSet(Integer, IntegerB);
    CCBigIntDestroy(IntegerB);
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 9, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 1), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 2), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 3), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 4), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 5), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 6), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 7), 0, @"Should contain the correct component value");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 8), 0x10000, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10f"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x10f, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
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
    
    
    CCBigIntSet(Integer, CC_STRING("0x000000000000000001"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x1, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x000000000000000000"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x0, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0x0"));
    
    XCTAssertFalse(CCBigIntGetSign(Integer), @"Should be positive");
    XCTAssertEqual(CCBigIntGetComponentCount(Integer), 1, @"Should contain the correct number of components");
    XCTAssertEqual(CCBigIntGetComponent(Integer, 0), 0x0, @"Should contain the correct component value");
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    CCBigIntDestroy(Integer);
}

-(void) testComparison
{
    CCBigInt Integer = CCBigIntCreate(CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, 1);
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, 2);
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, CC_STRING("0x10000000000000000"));
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, CC_STRING("0x10000000000000001"));
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, CC_STRING("0x20000000000000001"));
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, -1);
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultEqual, @"Should be equal");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer, -2);
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultDescending, @"Should be greater than");
    
    
    CCBigIntSet(Integer,  CC_STRING("-0x10000000000000000"));
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultEqual, @"Should be equal");
    
    
    CCBigIntSet(Integer,  CC_STRING("-0x10000000000000001"));
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    
    
    CCBigIntSet(Integer,  CC_STRING("-0x20000000000000000"));
    XCTAssertEqual(CCBigIntCompare(Integer, 0), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x0")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, 1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, -1), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x1")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    XCTAssertEqual(CCBigIntCompare(Integer, CC_STRING("-0x10000000000000000")), CCComparisonResultAscending, @"Should be less than");
    
    XCTAssertTrue(CCBigIntCompareEqual(Integer, CC_STRING("-0x20000000000000000")), @"Should be equal");
    XCTAssertFalse(CCBigIntCompareEqual(Integer, CC_STRING("0x20000000000000000")), @"Should not be equal");
    XCTAssertTrue(CCBigIntCompareLessThan(Integer, CC_STRING("0x20000000000000000")), @"Should be less than");
    XCTAssertFalse(CCBigIntCompareLessThan(Integer, CC_STRING("-0x20000000000000000")), @"Should not be less than");
    XCTAssertTrue(CCBigIntCompareLessThanEqual(Integer, CC_STRING("-0x20000000000000000")), @"Should be less than or equal");
    XCTAssertTrue(CCBigIntCompareLessThanEqual(Integer, CC_STRING("0x20000000000000000")), @"Should be less than or equal");
    XCTAssertFalse(CCBigIntCompareLessThanEqual(Integer, CC_STRING("-0x20000000000000001")), @"Should not be less than or equal");
    XCTAssertTrue(CCBigIntCompareGreaterThan(Integer, CC_STRING("-0x20000000000000001")), @"Should be greater than");
    XCTAssertFalse(CCBigIntCompareGreaterThan(Integer, CC_STRING("-0x20000000000000000")), @"Should not be greater than");
    XCTAssertTrue(CCBigIntCompareGreaterThanEqual(Integer, CC_STRING("-0x20000000000000001")), @"Should be greater than or equal");
    XCTAssertTrue(CCBigIntCompareGreaterThanEqual(Integer, CC_STRING("-0x20000000000000000")), @"Should be greater than or equal");
    XCTAssertFalse(CCBigIntCompareGreaterThanEqual(Integer, CC_STRING("0x20000000000000000")), @"Should not be greater than or equal");
    
    CCBigIntDestroy(Integer);
}

-(void) testAddition
{
    CCBigInt Integer = CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntAdd(Integer, 0);
    
    CCString Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntAdd(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntAdd(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntAdd(Integer, 0xffffffff);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000100000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntAdd(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntAdd(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntAdd(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xfffffffffffffffe"));
    CCBigIntAdd(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xfffffffffffffffe"));
    CCBigIntAdd(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x00000000000000010000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xfffffffffffffffe"));
    CCBigIntAdd(Integer, CC_STRING("0x10000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001fffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10000000000000000"));
    CCBigIntAdd(Integer, CC_STRING("0xfffffffffffffffe"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001fffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntAdd(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntAdd(Integer, CC_STRING("0xffffffffffffffff"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff"));
    CCBigIntAdd(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntAdd(Integer, CC_STRING("-0xffffffffffffffff"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 0);
    CCBigIntAdd(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntAdd(Integer, 0);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 1);
    CCBigIntAdd(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntAdd(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 2);
    CCBigIntAdd(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntAdd(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 3);
    CCBigIntAdd(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntAdd(Integer, 3);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x00000000000000010000000000000000"));
    CCBigIntAdd(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0x00000000000000010000000000000000"));
    CCBigIntAdd(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 2);
    CCBigIntAdd(Integer, CC_STRING("-0x00000000000000010000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntAdd(Integer, CC_STRING("0x00000000000000010000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    CCBigIntAdd(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    CCBigIntAdd(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntAdd(Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntAdd(Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    CCBigIntDestroy(Integer);
}

-(void) testSubtraction
{
    CCBigInt Integer = CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntSub(Integer, 0);
    
    CCString Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSub(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSub(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSub(Integer, 0xffffffff);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000100000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntSub(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSub(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffd")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntSub(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffd")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xfffffffffffffffe"));
    CCBigIntSub(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffc")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xfffffffffffffffe"));
    CCBigIntSub(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffc")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xfffffffffffffffe"));
    CCBigIntSub(Integer, CC_STRING("0x10000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x10000000000000000"));
    CCBigIntSub(Integer, CC_STRING("0xfffffffffffffffe"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntSub(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffe0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntSub(Integer, CC_STRING("0xffffffffffffffff"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff"));
    CCBigIntSub(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntSub(Integer, CC_STRING("-0xffffffffffffffff"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffe0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 0);
    CCBigIntSub(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntSub(Integer, 0);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 1);
    CCBigIntSub(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000003")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntSub(Integer, 1);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000003")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 2);
    CCBigIntSub(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000004")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntSub(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000004")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 3);
    CCBigIntSub(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000005")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntSub(Integer, 3);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000005")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0x00000000000000010000000000000000"));
    CCBigIntSub(Integer, -2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0x00000000000000010000000000000000"));
    CCBigIntSub(Integer, 2);
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x00000000000000010000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, 2);
    CCBigIntSub(Integer, CC_STRING("-0x00000000000000010000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, -2);
    CCBigIntSub(Integer, CC_STRING("0x00000000000000010000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x00000000000000010000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    CCBigIntSub(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001fffffffffffffffe0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    CCBigIntSub(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001fffffffffffffffe0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntSub(Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001fffffffffffffffe0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntSub(Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001fffffffffffffffe0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntSub(Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntSet(Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntSub(Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    CCBigIntDestroy(Integer);
}

-(void) testFastInteger
{
    CCBigIntFast Integer = CCBigIntFastCreate(CC_STD_ALLOCATOR);
    
    CCBigIntFastAdd(&Integer, 0);
    
    CCString Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastAdd(&Integer, 1);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastAdd(&Integer, 1);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastAdd(&Integer, 0xffffffff);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000100000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntFastAdd(&Integer, 1);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastAdd(&Integer, 1);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntFastAdd(&Integer, 2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xfffffffffffffffe"));
    CCBigIntFastAdd(&Integer, 2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x00000000000000010000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("-0xfffffffffffffffe"));
    CCBigIntFastAdd(&Integer, -2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x00000000000000010000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xfffffffffffffffe"));
    CCBigIntFastAdd(&Integer, CC_STRING("0x10000000000000000"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001fffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0x10000000000000000"));
    CCBigIntFastAdd(&Integer, CC_STRING("0xfffffffffffffffe"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001fffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xffffffffffffffff"));
    CCBigIntFastAdd(&Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntFastAdd(&Integer, CC_STRING("0xffffffffffffffff"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("-0xffffffffffffffff"));
    CCBigIntFastAdd(&Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntFastAdd(&Integer, CC_STRING("-0xffffffffffffffff"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x000000000000000100000000000000000000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, 0);
    CCBigIntFastAdd(&Integer, -2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, -2);
    CCBigIntFastAdd(&Integer, 0);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000002")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, 1);
    CCBigIntFastAdd(&Integer, -2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, -2);
    CCBigIntFastAdd(&Integer, 1);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, 2);
    CCBigIntFastAdd(&Integer, -2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, -2);
    CCBigIntFastAdd(&Integer, 2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000000")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, 3);
    CCBigIntFastAdd(&Integer, -2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, -2);
    CCBigIntFastAdd(&Integer, 3);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0x00000000000000010000000000000000"));
    CCBigIntFastAdd(&Integer, -2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("-0x00000000000000010000000000000000"));
    CCBigIntFastAdd(&Integer, 2);
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, 2);
    CCBigIntFastAdd(&Integer, CC_STRING("-0x00000000000000010000000000000000"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, -2);
    CCBigIntFastAdd(&Integer, CC_STRING("0x00000000000000010000000000000000"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0xfffffffffffffffe")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    CCBigIntFastAdd(&Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    CCBigIntFastAdd(&Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("-0xffffffffffffffff0000000000000001"));
    CCBigIntFastAdd(&Integer, CC_STRING("0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("-0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    
    CCBigIntFastSet(&Integer, CC_STRING("0xffffffffffffffff0000000000000001"));
    CCBigIntFastAdd(&Integer, CC_STRING("-0xffffffffffffffff0000000000000000"));
    
    Value = CCBigIntFastGetString(Integer);
    XCTAssertTrue(CCStringEqual(Value, CC_STRING("0x0000000000000001")), @"Should have the correct value instead got: %s", CCStringGetBuffer(Value));
    CCStringDestroy(Value);
    
    CCBigIntFastDestroy(Integer);
}

@end
