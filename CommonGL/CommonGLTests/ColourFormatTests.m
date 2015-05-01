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

-(void) testPackIntoBuffer
{
    uint8_t Data[64] = {0};
    CCPixel Pixel = {
        .type = (CCColourFormat)CCColourFormatR5G6B5Uint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize), .u8 = 0 },
            [1] = { .type = CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize), .u8 = 1 },
            [2] = { .type = CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize), .u8 = 1 },
            [3] = { .type = 0 }
        }
    };
    
    XCTAssertEqual(CCColourFormatPackIntoBuffer(Pixel, Data), 2, @"Should only write out 2 bytes");
    XCTAssertEqual(*(uint16_t*)Data, 2080, @"Should contain the correct value");
    
    
    Pixel = (CCPixel){
        .type = (CCColourFormat)CCColourFormatR32Uint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed | (32 << CCColourFormatChannelBitSize), .u32 = 0xdeadbeef },
            [1] = { .type = 0 },
            [2] = { .type = 0 },
            [3] = { .type = 0 }
        }
    };
    
    XCTAssertEqual(CCColourFormatPackIntoBuffer(Pixel, Data), 4, @"Should only write out 4 bytes");
    XCTAssertEqual(*(uint32_t*)Data, 0xdeadbeef, @"Should contain the correct value");
    
    
    Pixel = (CCPixel){
        .type = (CCColourFormat)CCColourFormatRGBA8Uint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize), .u8 = 1 },
            [1] = { .type = CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize), .u8 = 2 },
            [2] = { .type = CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize), .u8 = 3 },
            [3] = { .type = CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize), .u8 = 4 }
        }
    };
    
    XCTAssertEqual(CCColourFormatPackIntoBuffer(Pixel, Data), 4, @"Should only write out 4 bytes");
    XCTAssertEqual(((uint8_t*)Data)[0], 1, @"Should contain the correct value");
    XCTAssertEqual(((uint8_t*)Data)[1], 2, @"Should contain the correct value");
    XCTAssertEqual(((uint8_t*)Data)[2], 3, @"Should contain the correct value");
    XCTAssertEqual(((uint8_t*)Data)[3], 4, @"Should contain the correct value");
    
    
    Pixel = (CCPixel){
        .type = (CCColourFormat)CCColourFormatRGBA32Uint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize), .u32 = 0x10000002 },
            [1] = { .type = CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize), .u32 = 0x30000004 },
            [2] = { .type = CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize), .u32 = 0x50000006 },
            [3] = { .type = CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize), .u32 = 0x70000008 }
        }
    };
    
    XCTAssertEqual(CCColourFormatPackIntoBuffer(Pixel, Data), 16, @"Should only write out 16 bytes");
    XCTAssertEqual(((uint32_t*)Data)[0], 0x10000002, @"Should contain the correct value");
    XCTAssertEqual(((uint32_t*)Data)[1], 0x30000004, @"Should contain the correct value");
    XCTAssertEqual(((uint32_t*)Data)[2], 0x50000006, @"Should contain the correct value");
    XCTAssertEqual(((uint32_t*)Data)[3], 0x70000008, @"Should contain the correct value");
    
    
    Pixel = (CCPixel){
        .type = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
        | ((CCColourFormatChannelRed  | (50 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
        | ((CCColourFormatChannelBlue | (50 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (50 << CCColourFormatChannelBitSize), .u64 = 0x3000000000001 },
            [1] = { .type = CCColourFormatChannelBlue   | (50 << CCColourFormatChannelBitSize), .u64 = 0x2000000000003 },
            [2] = { .type = 0 },
            [3] = { .type = 0 }
        }
    };
    
    XCTAssertEqual(CCColourFormatPackIntoBuffer(Pixel, Data), 13, @"Should only write out 13 bytes");
    XCTAssertEqual((((uint64_t*)Data)[0] & 0x3ffffffffffff), 0x3000000000001, @"Should contain the correct value");
    XCTAssertEqual(((((uint64_t*)Data)[0] & 0xfffc000000000000) >> 50) + ((((uint64_t*)Data)[1] & 0xfffffffff) << 14), 0x2000000000003, @"Should contain the correct value");
}

-(void) testGetComponent
{
    CCPixel Pixel = {
        .type = (CCColourFormat)CCColourFormatR5G6B5Uint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize), .u8 = 1 },
            [1] = { .type = CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize), .u8 = 2 },
            [2] = { .type = CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize), .u8 = 3 },
            [3] = { .type = 0 }
        }
    };
    
    CCColour Component = CCColourFormatGetComponent(Pixel, CCColourFormatChannelRed);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelRed, @"Should retrieve the correct component");
    XCTAssertEqual(Component.u8, 1, @"Should retrieve the correct component value");
    
    Component = CCColourFormatGetComponent(Pixel, CCColourFormatChannelGreen);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual(Component.u8, 2, @"Should retrieve the correct component value");
    
    Component = CCColourFormatGetComponent(Pixel, CCColourFormatChannelBlue);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelBlue, @"Should retrieve the correct component");
    XCTAssertEqual(Component.u8, 3, @"Should retrieve the correct component value");
}

-(void) testGetComponentRGB
{
    CCPixel Pixel = {
        .type = (CCColourFormat)CCColourFormatR5G6B5Uint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize), .u8 = 1 },
            [1] = { .type = CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize), .u8 = 63 },
            [2] = { .type = CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize), .u8 = 31 },
            [3] = { .type = 0 }
        }
    };
    
    CCColour Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelRed, CCColourFormatTypeUnsignedInteger, 1);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelRed, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 1, @"Should change the type to the new type");
    XCTAssertEqual(Component.u8, 0, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeUnsignedInteger, 1);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 1, @"Should change the type to the new type");
    XCTAssertEqual(Component.u8, 1, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelBlue, CCColourFormatTypeUnsignedInteger, 6);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelBlue, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 6, @"Should change the type to the new type");
    XCTAssertEqual(Component.u8, 63, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeFloat, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, 63.0f, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeFloat | CCColourFormatNormalized, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, 1.0f, @"Should convert value to the new representation");
    
    Pixel = (CCPixel){
        .type = (CCColourFormat)CCColourFormatRGBA8Sint,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize), .i8 = 0 },
            [1] = { .type = CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize), .i8 = -1 },
            [2] = { .type = CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize), .i8 = 1 },
            [3] = { .type = CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize), .i8 = INT8_MIN }
        }
    };
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelRed, CCColourFormatTypeSignedInteger, 8);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelRed, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 8, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, 0, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeSignedInteger, 8);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 8, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, -1, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelBlue, CCColourFormatTypeSignedInteger, 8);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelBlue, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 8, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, 1, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelAlpha, CCColourFormatTypeSignedInteger, 8);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelAlpha, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 8, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, INT8_MIN, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelRed, CCColourFormatTypeSignedInteger, 16);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelRed, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 16, @"Should change the type to the new type");
    XCTAssertEqual(Component.i16, 0, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeSignedInteger, 16);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 16, @"Should change the type to the new type");
    XCTAssertEqual(Component.i16, -129, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelBlue, CCColourFormatTypeSignedInteger, 16);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelBlue, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 16, @"Should change the type to the new type");
    XCTAssertEqual(Component.i16, 385, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelAlpha, CCColourFormatTypeSignedInteger, 16);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelAlpha, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 16, @"Should change the type to the new type");
    XCTAssertEqual(Component.i16, INT16_MIN, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelRed, CCColourFormatTypeSignedInteger, 7);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelRed, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 7, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, 0, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeSignedInteger, 7);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 7, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, -1, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelBlue, CCColourFormatTypeSignedInteger, 7);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelBlue, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 7, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, 0, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelAlpha, CCColourFormatTypeSignedInteger, 7);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelAlpha, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 7, @"Should change the type to the new type");
    XCTAssertEqual(Component.i8, -64, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelRed, CCColourFormatTypeFloat, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelRed, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, 0.0f, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelGreen, CCColourFormatTypeFloat, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelGreen, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, -1.0f, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelBlue, CCColourFormatTypeFloat, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelBlue, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, 1.0f, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelAlpha, CCColourFormatTypeFloat, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelAlpha, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, (float)INT8_MIN, @"Should convert value to the new representation");
    
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelAlpha, CCColourFormatTypeFloat | CCColourFormatNormalized, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelAlpha, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, -1.0f, @"Should convert value to the new representation");
    
    Pixel.channel[3].i8 = INT8_MAX;
    Component = CCColourFormatRGBGetComponent(Pixel, CCColourFormatChannelAlpha, CCColourFormatTypeFloat | CCColourFormatNormalized, 32);
    XCTAssertEqual(Component.type & CCColourFormatChannelIndexMask, CCColourFormatChannelAlpha, @"Should retrieve the correct component");
    XCTAssertEqual((Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize, 32, @"Should change the type to the new type");
    XCTAssertEqual(Component.f32, 1.0f, @"Should convert value to the new representation");
    
    Pixel = (CCPixel){
        .type = (CCColourFormat)CCColourFormatRGBA32Float,
        .channel = {
            [0] = { .type = CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize), .f32 = 0.5f },
            [1] = { .type = CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize), .f32 = 1.0f },
            [2] = { .type = CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize), .f32 = 10.0f },
            [3] = { .type = CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize), .f32 = 1.0f }
        }
    };
}

@end
