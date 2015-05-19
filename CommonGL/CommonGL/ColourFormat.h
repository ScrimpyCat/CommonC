/*
 *  Copyright (c) 2014 Stefan Johnson
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

#ifndef CommonGL_ColourFormat_h
#define CommonGL_ColourFormat_h

#if __has_feature(modules)
@import Foundation;
#else
#import <Foundation/Foundation.h>
#endif

#import <CommonGL/Defined.h>


/*
 rrrrrrrr rrrrrrrr rrrrrrrr rrrrrrrr rrrrrrrr ccccccxx ooxxxxpn sssmmmtt
 
 t: Type
 m: Model
 s: Space
 c: Compression
 r: Reserved options
 x: Unused/Reserved for future use
 
 n: Normalized
 p: Premultiplied Alpha
 o: Control option
 
 
 
 Options when using CCColourFormatOptionChannel4
 bbbbbbpp ccbbbbbb ppccbbbb bbppccbb bbbbppcc 00000000 00000000 00000000
 33333333 33222222 22221111 11111100 00000000 xxxxxxxx xxxxxxxx xxxxxxxx
 
 b: bit size (N << CCColourFormatChannelBitSize)
 p: planar index (CCColourFormatChannelPlanarIndexN)
 c: channel (CCColourFormatChannelIndexN)
 0: CCColourFormatChannelOffset0
 1: CCColourFormatChannelOffset1
 2: CCColourFormatChannelOffset2
 3: CCColourFormatChannelOffset3
 */

typedef NS_OPTIONS(uint64_t, CCColourFormat) {
    //Type
    CCColourFormatTypeMask = (3 << 0),
    CCColourFormatTypeUnsignedInteger = (0 << 0),
    CCColourFormatTypeSignedInteger = (1 << 0),
    CCColourFormatTypeFloat = (2 << 0),
    
    //Colour Model
    CCColourFormatModelMask = (7 << 2),
    CCColourFormatModelRGB = (0 << 2), //whether the format is a RGB colour model (e.g. RGB, sRGB, BGR)
    CCColourFormatModelYUV = (1 << 2), //whether the format is a YUV colour model (e.g. Y'CbCr)
    CCColourFormatModelHS = (2 << 2), //whether the format is a HSV/HSL colour model (e.g. HSL, HSV)
    CCColourFormatModelCMYK = (3 << 2), //whether the format is a CMYK colour model (e.g. CMY, CMYK)
    CCColourFormatModelCIE = (4 << 2), //whether the format is a CIE colour model (e.g. CIELAB, CIELUV)
    CCColourFormatModelMonochrome = (5 << 2),
    
    //Colour Space
    CCColourFormatSpaceMask = (7 << 5),
    //RGB Colour Spaces
    CCColourFormatSpaceRGB_RGB =    CCColourFormatModelRGB | (0 << 5),
    CCColourFormatSpaceRGB_sRGB =   CCColourFormatModelRGB | (1 << 5),
    //YUV Colour Spaces
    CCColourFormatSpaceYUV_YpCbCr = CCColourFormatModelYUV | (0 << 5),
    //HSL/HSV Colour Spaces
    CCColourFormatSpaceHS_HSL =    CCColourFormatModelHS | (0 << 5),
    CCColourFormatSpaceHS_HSV =    CCColourFormatModelHS | (1 << 5),
    CCColourFormatSpaceHS_HSB =    CCColourFormatSpaceHS_HSV,
    CCColourFormatSpaceHS_HSI =    CCColourFormatModelHS | (2 << 5), //component average
    CCColourFormatSpaceHS_HSluma = CCColourFormatModelHS | (3 << 5),
    //CMYK Colour Spaces
    //CIE Colour Spaces
    //Monochrome Colour Spaces
    
    //Compression
    CCColourFormatCompressionMask = (63 << 18),
    CCColourFormatCompressionTypeMask = (7 << 18),
    CCColourFormatCompressionOptionMask = (7 << 21),
    CCColourFormatCompressionNone = (0 << 18),
    CCColourFormatCompressionBPTC = (1 << 18),
    CCColourFormatCompressionS3TC = (2 << 18),
    CCColourFormatCompressionPVRTC = (3 << 18),
    //ASTC
    //ETC2
    //S3TC Compression Options
    CCColourFormatCompressionS3TC_DXT1 = CCColourFormatCompressionS3TC | (0 << 21),
    CCColourFormatCompressionS3TC_DXT2 = CCColourFormatCompressionS3TC | (1 << 21),
    CCColourFormatCompressionS3TC_DXT3 = CCColourFormatCompressionS3TC | (2 << 21),
    CCColourFormatCompressionS3TC_DXT4 = CCColourFormatCompressionS3TC | (3 << 21),
    CCColourFormatCompressionS3TC_DXT5 = CCColourFormatCompressionS3TC | (4 << 21),
    //PVRTC Compression Options
    CCColourFormatCompressionPVRTC_2BPP = CCColourFormatCompressionPVRTC | (0 << 21),
    CCColourFormatCompressionPVRTC_4BPP = CCColourFormatCompressionPVRTC | (1 << 21),
    
    //Options
    CCColourFormatNormalized = (1 << 8),
    CCColourFormatPremultipliedAlpha = (1 << 9),
    
    //Control Option
    CCColourFormatOptionMask = (3 << 14),
    CCColourFormatOptionChannel4 = (0 << 14), //whether it uses the 4 channel option/structure
    
    /*
     Four Channel Option Structure
     
     RGB565:
     ((CCColourFormatChannelRed     | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0) |
     ((CCColourFormatChannelGreen   | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1) |
     ((CCColourFormatChannelBlue    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
     
     BGRA32:
     ((CCColourFormatChannelRed     | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2) |
     ((CCColourFormatChannelGreen   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1) |
     ((CCColourFormatChannelBlue    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0) |
     ((CCColourFormatChannelAlpha   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
     
     R8:
     ((CCColourFormatChannelRed     | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
     
     Y'CbCr 8-bit Bi-Planar (Y' 4-bit plane0, CbCr 4-bit(2:2) plane1):
     ((CCColourFormatChannelLuma    | (4 << CCColourFormatChannelBitSize) | CCColourFormatChannelPlanarIndex0) << CCColourFormatChannelOffset0) |
     ((CCColourFormatChannelChromaB | (2 << CCColourFormatChannelBitSize) | CCColourFormatChannelPlanarIndex1) << CCColourFormatChannelOffset1) | //is really Offset0
     ((CCColourFormatChannelChromaR | (2 << CCColourFormatChannelBitSize) | CCColourFormatChannelPlanarIndex1) << CCColourFormatChannelOffset2) | //is really Offset1
     
     
     How planar and offset work:
     Offset is for shifting the used component information into the format value. It doesn't correlate to offset location of the channel. Channel location works
     in increments based on the planar. So if planar 0 is used twice, it will have locations 0 and 1, if planar 1 is used once, it will have loations 0.
     */
    
    CCColourFormatChannelMask = 1023, //Must shift the offset back before using mask
    CCColourFormatChannelOffset0 = 24,
    CCColourFormatChannelOffset1 = 34,
    CCColourFormatChannelOffset2 = 44,
    CCColourFormatChannelOffset3 = 54,
    
    CCColourFormatChannelPlanarIndexMask = (3 << 2),
    CCColourFormatChannelPlanarIndex0 = (0 << 2),
    CCColourFormatChannelPlanarIndex1 = (1 << 2),
    CCColourFormatChannelPlanarIndex2 = (2 << 2),
    CCColourFormatChannelPlanarIndex3 = (3 << 2),
    
    CCColourFormatChannelBitSizeMask = (63 << 4),
    CCColourFormatChannelBitSize = 4,
    
    CCColourFormatChannelIndexMask = (3 << 0),
    CCColourFormatChannelIndex0 = (0 << 0),
    CCColourFormatChannelIndex1 = (1 << 0),
    CCColourFormatChannelIndex2 = (2 << 0),
    CCColourFormatChannelIndex3 = (3 << 0),
    
    CCColourFormatChannelAlpha = CCColourFormatChannelIndex3,
    
    //RGB Channels
    CCColourFormatChannelRed = CCColourFormatChannelIndex0,
    CCColourFormatChannelGreen = CCColourFormatChannelIndex1,
    CCColourFormatChannelBlue = CCColourFormatChannelIndex2,
    
    //YUV Channels
    CCColourFormatChannelLuma = CCColourFormatChannelIndex0,
    CCColourFormatChannelChromaU = CCColourFormatChannelIndex1,
    CCColourFormatChannelChromaB = CCColourFormatChannelChromaU,
    CCColourFormatChannelChromaV = CCColourFormatChannelIndex2,
    CCColourFormatChannelChromaR = CCColourFormatChannelChromaV,
    
    //HSB/HSV Channels
    CCColourFormatChannelHue = CCColourFormatChannelIndex0,
    CCColourFormatChannelSaturation = CCColourFormatChannelIndex1,
    CCColourFormatChannelValue = CCColourFormatChannelIndex2,
    CCColourFormatChannelLightness = CCColourFormatChannelValue,
};

#pragma mark - RGB Colour Formats
typedef NS_OPTIONS(uint64_t, CCColourFormatRGB) {
    //8-bit
    //R8
    CCColourFormatR8Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR8Unorm_sRGB  = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR8Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR8Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelRed | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR8Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelRed | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //G8
    CCColourFormatG8Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG8Unorm_sRGB  = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG8Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG8Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG8Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelGreen | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //B8
    CCColourFormatB8Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB8Unorm_sRGB  = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB8Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB8Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB8Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelBlue | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //A8
    CCColourFormatA8Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelAlpha | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA8Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelAlpha | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA8Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelAlpha | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA8Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelAlpha | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //16-bit
    //R16
    CCColourFormatR16Unorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR16Snorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR16Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelRed | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR16Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelRed | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR16Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelRed | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //G16
    CCColourFormatG16Unorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelGreen | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG16Snorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelGreen | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG16Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelGreen | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG16Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelGreen | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG16Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelGreen | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //B16
    CCColourFormatB16Unorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelBlue | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB16Snorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelBlue | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB16Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelBlue | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB16Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelBlue | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB16Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelBlue | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //A16
    CCColourFormatA16Unorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelAlpha | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA16Snorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelAlpha | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA16Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelAlpha | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA16Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelAlpha | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA16Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelAlpha | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //RG8
    CCColourFormatRG8Unorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG8Unorm_sRGB = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG8Snorm      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG8Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG8Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    
    
    //R5G6B5
    CCColourFormatR5G6B5Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2),
    CCColourFormatR5G6B5Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2),
    CCColourFormatR5G6B5Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2),
    CCColourFormatR5G6B5Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2),
    
    
    //B5G6R5
    CCColourFormatB5G6R5Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB5G6R5Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB5G6R5Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB5G6R5Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (6 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //RGB5A1
    CCColourFormatRGB5A1Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGB5A1Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGB5A1Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGB5A1Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //BGR5A1
    CCColourFormatBGR5A1Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGR5A1Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGR5A1Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGR5A1Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //A1RGB5
    CCColourFormatA1RGB5Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA1RGB5Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA1RGB5Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA1RGB5Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //A1BGR5
    CCColourFormatA1BGR5Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA1BGR5Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA1BGR5Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA1BGR5Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (5 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (1 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //RGBA4
    CCColourFormatRGBA4Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA4Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA4Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA4Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //BGRA4
    CCColourFormatBGRA4Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA4Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA4Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA4Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //ARGB4
    CCColourFormatARGB4Unorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB4Snorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB4Uint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB4Sint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //ABGR4
    CCColourFormatABGR4Unorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR4Snorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR4Uint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR4Sint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (4 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //32-bit
    //R32
    CCColourFormatR32Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelRed | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR32Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelRed | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatR32Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelRed | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //G32
    CCColourFormatG32Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelGreen | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG32Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelGreen | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatG32Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelGreen | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //B32
    CCColourFormatB32Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelBlue | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB32Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelBlue | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatB32Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelBlue | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //A32
    CCColourFormatA32Uint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelAlpha | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA32Sint       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelAlpha | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatA32Float      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelAlpha | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //RG16
    CCColourFormatRG16Unorm     = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG16Snorm     = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                    | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG16Uint      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG16Sint      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG16Float     = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    
    
    //RGBA8
    CCColourFormatRGBA8Unorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA8Unorm_sRGB   = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA8Snorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA8Uint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA8Sint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //BGRA8
    CCColourFormatBGRA8Unorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA8Unorm_sRGB   = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA8Snorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA8Uint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA8Sint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //ARGB8
    CCColourFormatARGB8Unorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB8Unorm_sRGB   = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB8Snorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB8Uint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB8Sint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //ABGR8
    CCColourFormatABGR8Unorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR8Unorm_sRGB   = CCColourFormatSpaceRGB_sRGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR8Snorm        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR8Uint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR8Sint         = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (8 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    //TODO: common 32-bit packed
    
    //64-bit
    //RG32
    CCColourFormatRG32Uint      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                    | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG32Sint      = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                    | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    CCColourFormatRG32Float     = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                    | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                    | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1),
    
    
    //RGBA16
    CCColourFormatRGBA16Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA16Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA16Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA16Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA16Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //BGRA16
    CCColourFormatBGRA16Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA16Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA16Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA16Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA16Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //ARGB16
    CCColourFormatARGB16Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB16Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB16Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB16Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB16Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //ABGR16
    CCColourFormatABGR16Unorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR16Snorm       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger | CCColourFormatNormalized
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR16Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR16Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR16Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (16 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //128-bit
    //RGBA32
    CCColourFormatRGBA32Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA32Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatRGBA32Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //BGRA32
    CCColourFormatBGRA32Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA32Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    CCColourFormatBGRA32Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3),
    
    
    //ARGB32
    CCColourFormatARGB32Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB32Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatARGB32Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    
    
    //ABGR32
    CCColourFormatABGR32Uint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeUnsignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR32Sint        = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeSignedInteger
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
    CCColourFormatABGR32Float       = CCColourFormatSpaceRGB_RGB | CCColourFormatTypeFloat
                                        | ((CCColourFormatChannelRed    | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset3)
                                        | ((CCColourFormatChannelGreen  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset2)
                                        | ((CCColourFormatChannelBlue   | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset1)
                                        | ((CCColourFormatChannelAlpha  | (32 << CCColourFormatChannelBitSize)) << CCColourFormatChannelOffset0),
};

#pragma mark - YUV Colour Formats
//TODO: YUV formats

#pragma mark - HSL/HSV Colour Formats
//TODO: HSL/HSV formats

#pragma mark - CMYK Colour Formats
//TODO: CMYK formats

#pragma mark - CIE Colour Formats
//TODO: CIE formats

#pragma mark - Monochrome Colour Formats
//TODO: Monochrome formats

#pragma mark -

typedef struct {
    CCColourFormat type;
    union {
        float f32;
        double f64;
        
        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;
        
        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
    };
} CCColourComponent;

typedef struct {
    CCColourFormat type;
    CCColourComponent channel[4];
} CCColour;

#pragma mark -


void CCColourFormatChannel4InPlanar(CCColourFormat ColourFormat, unsigned int PlanarIndex, CCColourFormat Channels[4]);
_Bool CCColourFormatGLRepresentation(CCColourFormat ColourFormat, unsigned int PlanarIndex, GLenum *InputType, GLenum *InputFormat, GLenum *InternalFormat);

/*!
 * @brief Packs the pixel colour into the buffer.
 * @param Colour The pixel colour to be packed onto the buffer.
 * @param Data The buffer to store the colour.
 * @return The amount of bytes written to the buffer (bits rounded up to the next byte).
 */
size_t CCColourFormatPackIntoBuffer(CCColour Colour, void *Data);

CCColourComponent CCColourFormatGetComponent(CCColour Colour, CCColourFormat Index);
CCColourComponent CCColourFormatRGBGetComponent(CCColour Colour, CCColourFormat Index, CCColourFormat Type, int Precision);
CCColourComponent CCColourFormatYUVGetComponent(CCColour Colour, CCColourFormat Index, CCColourFormat Type, int Precision);
CCColourComponent CCColourFormatHSGetComponent(CCColour Colour, CCColourFormat Index, CCColourFormat Type, int Precision);

#endif
