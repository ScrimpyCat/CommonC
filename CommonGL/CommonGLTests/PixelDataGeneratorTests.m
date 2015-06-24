/*
 *  Copyright (c) 2015, Stefan Johnson
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

#import "Default_Private.h"

@import Cocoa;
@import XCTest;
#import "Common.h"

@interface PixelDataGeneratorTests : XCTestCase

@end

@implementation PixelDataGeneratorTests
{
    CCPixelDataGenerator *pixelData;
}

-(void) setUp
{
    [super setUp];
    
    pixelData = [[CCPixelDataGenerator alloc] initWithDataGenerator: ^CCColour(size_t x, size_t y, size_t z){
        return (CCColour){
            .type = (CCColourFormat)CCColourFormatRGBA8Uint,
            .channel = {
                { .type = CCColourFormatChannelRed   | (8 << CCColourFormatChannelBitSize), .u32 = 0 },
                { .type = CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize), .u32 = 0 },
                { .type = CCColourFormatChannelBlue  | (8 << CCColourFormatChannelBitSize), .u32 = 0 },
                { .type = CCColourFormatChannelAlpha | (8 << CCColourFormatChannelBitSize), .u32 = 0 }
            }
        };
    }
                                               AsFormat: CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                                         | ((CCColourFormatChannelRed   | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                                         | ((CCColourFormatChannelGreen | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                                         | ((CCColourFormatChannelBlue  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)];
}

-(void) tearDown
{
    CC_SAFE_Release(pixelData);
    
    [super tearDown];
}

-(void) testSampling
{
    CCColour Pixel = [pixelData colourAtX: 0 Y: 0 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 1 Y: 0 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 2 Y: 0 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 0 Y: 1 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 1 Y: 1 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 2 Y: 1 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
}

@end
