/*
 *  Copyright (c) 2014, Stefan Johnson
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

@interface ColourFormatTests : XCTestCase

@end

@implementation ColourFormatTests

-(void) setUp
{
    [super setUp];
}

-(void) tearDown
{
    [super tearDown];
}

-(void) testChannel4InPlanar
{
    CCColourFormat Channels[4];
    CCColourFormatChannel4InPlanar(CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                   | ((CCColourFormatChannelRed  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                   | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
                                   CCColourFormatChannelPlanarIndex0, Channels);
    
    XCTAssertEqual(Channels[0], (CCColourFormatChannelRed  | (8 << CCColourFormatChannelBitSize)), @"Should contain the red channel");
    XCTAssertEqual(Channels[1], (CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)), @"Should contain the blue channel");
    XCTAssertEqual(Channels[2], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[3], 0, @"Should not contain any element");
    
    
    
    CCColourFormatChannel4InPlanar(0, CCColourFormatChannelPlanarIndex0, Channels);
    
    XCTAssertEqual(Channels[0], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[1], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[2], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[3], 0, @"Should not contain any element");
    
    
    
    CCColourFormatChannel4InPlanar(CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                   | ((CCColourFormatChannelRed  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                   | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
                                   CCColourFormatChannelPlanarIndex0, Channels);
    
    XCTAssertEqual(Channels[1], (CCColourFormatChannelRed  | (8 << CCColourFormatChannelBitSize)), @"Should contain the red channel");
    XCTAssertEqual(Channels[0], (CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)), @"Should contain the blue channel");
    XCTAssertEqual(Channels[2], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[3], 0, @"Should not contain any element");
    
    
    
    CCColourFormatChannel4InPlanar(CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                   | ((CCColourFormatChannelRed   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                   | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize) | CCColourFormatChannelPlanarIndex1) << CCColourFormatChannelOffset1)
                                   | ((CCColourFormatChannelBlue  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2),
                                   CCColourFormatChannelPlanarIndex0, Channels);
    
    XCTAssertEqual(Channels[0], (CCColourFormatChannelRed  | (8 << CCColourFormatChannelBitSize)), @"Should contain the red channel");
    XCTAssertEqual(Channels[1], (CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)), @"Should contain the blue channel");
    XCTAssertEqual(Channels[2], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[3], 0, @"Should not contain any element");
    
    
    
    CCColourFormatChannel4InPlanar(CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                   | ((CCColourFormatChannelRed   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                   | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize) | CCColourFormatChannelPlanarIndex1) << CCColourFormatChannelOffset1)
                                   | ((CCColourFormatChannelBlue  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2),
                                   CCColourFormatChannelPlanarIndex1, Channels);
    
    XCTAssertEqual(Channels[0], (CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize) | CCColourFormatChannelPlanarIndex1), @"Should contain the green channel");
    XCTAssertEqual(Channels[1], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[2], 0, @"Should not contain any element");
    XCTAssertEqual(Channels[3], 0, @"Should not contain any element");
}

@end
