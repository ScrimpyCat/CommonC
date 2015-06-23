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

@interface PixelDataStaticTests : XCTestCase

@end

@implementation PixelDataStaticTests
{
    CCPixelDataStatic *pixelData;
}

-(void) setUp
{
    [super setUp];
    
    static uint8_t PixelData[6] = { //rgb1
        1, 4, 7, //red, blue, white
        2, 3, 0 //green, yellow, black
    };
    
    CCGenericContainer *Data = [CCGenericContainer containerWithData: PixelData OfSize: 6];
    pixelData = [[CCPixelDataStatic alloc] initWithData: Data
                                               AsFormat: CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                                         | ((CCColourFormatChannelRed   | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                                         | ((CCColourFormatChannelGreen | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                                         | ((CCColourFormatChannelBlue  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                                OfWidth: 3 Height: 2 Depth: 1];
}

-(void) tearDown
{
    CC_SAFE_Release(pixelData);
    
    [super tearDown];
}

-(void) testSampling
{
    CCColour Pixel = [pixelData colourAtX: 0 Y: 0 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 1, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 1 Y: 0 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 1, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 2 Y: 0 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 1, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 1, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 1, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 0 Y: 1 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 1, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 1 Y: 1 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 1, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 1, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 2 Y: 1 Z: 0];
    
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelRed).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelGreen).u8, 0, @"Should contain the correct value");
    XCTAssertEqual(CCColourGetComponent(Pixel, CCColourFormatChannelBlue).u8, 0, @"Should contain the correct value");
    
    
    Pixel = [pixelData colourAtX: 0 Y: 2 Z: 0];
    
    XCTAssertEqual(Pixel.type, 0, @"Should be outside bounds");
}

@end
