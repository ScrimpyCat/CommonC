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

#import "Default_Private.h"
#import "ColourFormat.h"
#import "Version.h"
#import <CommonC/Types.h>
#import <CommonObjC/Assertion.h>
#import <CommonC/Extensions.h>


static CC_FORCE_INLINE unsigned int CCColourComponentGetBitSize(CCColourComponent Component) CC_CONSTANT_FUNCTION;


//Retrieves channels for the specified plane, and restructures the channel offsets so they're ordered in the plane
void CCColourFormatChannel4InPlanar(CCColourFormat ColourFormat, unsigned int PlanarIndex, CCColourFormat Channels[4])
{
    CCAssertLog((ColourFormat & CCColourFormatOptionMask) == CCColourFormatOptionChannel4, @"Only works on formats that use the channel 4 structure");
    
    const CCColourFormat Offsets[4] = {
        CCColourFormatChannelOffset0,
        CCColourFormatChannelOffset1,
        CCColourFormatChannelOffset2,
        CCColourFormatChannelOffset3
    };
    
    memset(Channels, 0, sizeof(CCColourFormat) * 4);
    
    for (int Loop = 0, Index = 0; Loop < 4; Loop++)
    {
        CCColourFormat Channel = (ColourFormat >> Offsets[Loop]) & CCColourFormatChannelMask;
        if (((Channel & CCColourFormatChannelPlanarIndexMask) == PlanarIndex) && (Channel & CCColourFormatChannelBitSizeMask))
        {
            Channels[Index++] = Channel;
        }
    }
}

_Bool CCColourFormatGLRepresentation(CCColourFormat ColourFormat, unsigned int PlanarIndex, GLenum *InputType, GLenum *InputFormat, GLenum *InternalFormat)
{
    if (InputType) *InputType = 0;
    if (InputFormat) *InputFormat = 0;
    if (InternalFormat) *InternalFormat = 0;
    
    if ((ColourFormat & CCColourFormatModelMask) == CCColourFormatModelRGB)
    {
        const _Bool sRGB = (ColourFormat & CCColourFormatSpaceMask) == CCColourFormatSpaceRGB_sRGB, Normalized = ColourFormat & CCColourFormatNormalized;
#pragma unused(sRGB)
#pragma unused(Normalized)
        CCColourFormat Channels[4];
        
        CCColourFormatChannel4InPlanar(ColourFormat, PlanarIndex, Channels);
        
        int Channel1Size, Channel2Size, Channel3Size, Channel4Size;
        if ((Channel1Size = (Channels[0] & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize))
        {
            /*
             Table as according to GL docs, however spec says something different :/
             Format:
             Version    GL_RED    GL_GREEN     GL_BLUE    GL_ALPHA    GL_RG    GL_RGB    GL_BGR   GL_RGBA    GL_BGRA
             GL 2       x         x            x          x                    x         x        x           x
             GL 3       x                                             x        x         x        x           x
             GL 4       x                                             x        x         x        x           x
             ES 1                                         x                    x                  x
             ES 2                                         x                    x                  x
             ES 3       x                                 x           x        x                  x
             
             Version    GL_COLOR_INDEX    GL_LUMINANCE    GL_LUMINANCE_ALPHA    GL_STENCIL_INDEX     GL_DEPTH_COMPONENT    GL_DEPTH_STENCIL
             GL 2       x                 x               x
             GL 3
             GL 4                                                               x                    x                     x
             ES 1                         x               x
             ES 2                         x               x
             ES 3                         x               x                                          x                     x
             
             Version    GL_RED_INTEGER   GL_RG_INTEGER    GL_RGB_INTEGER   GL_BGR_INTEGER   GL_RGBA_INTEGER   GL_BGRA_INTEGER
             GL 2
             GL 3
             GL 4       x                x                x                x                x                 x
             ES 1
             ES 2
             ES 3       x                x                x                                 x
             
             
             Type:
             Version    GL_BITMAP    GL_UNSIGNED_BYTE    GL_BYTE      GL_UNSIGNED_SHORT    GL_SHORT    GL_UNSIGNED_INT      GL_INT
             GL 2       x            x                   x            x                    x           x                    x
             GL 3                    x                   x            x                    x           x                    x
             GL 4                    x                   x            x                    x           x                    x
             ES 1                    x
             ES 2                    x
             ES 3                    x                   x            x                    x           x                    x
             
             Version    GL_HALF_FLOAT    GL_FLOAT     GL_UNSIGNED_BYTE_3_3_2   GL_UNSIGNED_BYTE_2_3_3_REV
             GL 2                        x            x                        x
             GL 3                        x            x                        x
             GL 4                        x            x                        x
             ES 1
             ES 2
             ES 3       x                x
             
             Version    GL_UNSIGNED_SHORT_5_6_5      GL_UNSIGNED_SHORT_5_6_5_REV     GL_UNSIGNED_SHORT_4_4_4_4    GL_UNSIGNED_SHORT_4_4_4_4_REV
             GL 2       x                            x                               x                            x
             GL 3       x                            x                               x                            x
             GL 4       x                            x                               x                            x
             ES 1       x                                                            x
             ES 2       x                                                            x
             ES 3       x                                                            x
             
             Version    GL_UNSIGNED_SHORT_5_5_5_1    GL_UNSIGNED_SHORT_1_5_5_5_REV    GL_UNSIGNED_INT_8_8_8_8     GL_UNSIGNED_INT_8_8_8_8_REV
             GL 2       x                            x                                x                           x
             GL 3       x                            x                                x                           x
             GL 4       x                            x                                x                           x
             ES 1       x
             ES 2       x
             ES 3       x
             
             Version    GL_UNSIGNED_INT_10_10_10_2    GL_UNSIGNED_INT_2_10_10_10_REV    GL_UNSIGNED_INT_10F_11F_11F_REV
             GL 2       x                             x
             GL 3       x                             x
             GL 4       x                             x
             ES 1
             ES 2
             ES 3                                     x                                 x
             
             Version    GL_UNSIGNED_INT_5_9_9_9_REV     GL_UNSIGNED_INT_24_8     GL_FLOAT_32_UNSIGNED_INT_24_8_REV
             GL 2
             GL 3
             GL 4
             ES 1
             ES 2
             ES 3       x                               x                        x
             */
            
            if (!Channels[1]) //Single Channel
            {
                if ((Channel1Size == 8) || (Channel1Size == 16) || (Channel1Size == 32))
                {
                    
                }
                
                if (InputFormat)
                {
                    switch (Channels[0] & CCColourFormatChannelIndexMask)
                    {
                        CC_GL_VERSION_ACTIVE(1_0, NA, 3_0, NA, case CCColourFormatChannelRed:
                            CC_GL_VERSION_ACTIVE(4_0, NA, 3_0, NA,
                                if (!Normalized) *InputFormat = GL_RED_INTEGER;
                                else
                            );
                            *InputFormat = GL_RED;
                            break;
                        );
                        
                        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, case CCColourFormatChannelGreen:
                            *InputFormat = GL_GREEN;
                            break;
                        );
                        
                        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, case CCColourFormatChannelBlue:
                            *InputFormat = GL_BLUE;
                            break;
                        );
                        
                        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, NA, case CCColourFormatChannelAlpha:
                            *InputFormat = GL_ALPHA;
                            break;
                        );
                    }
                }
            }
            
            else
            {
                
            }
            
            switch (Channels[0] & CCColourFormatChannelIndexMask)
            {
                case CCColourFormatChannelRed:
                    if (Channels[1])
                    break;
                    
                case CCColourFormatChannelGreen:
                    break;
                    
                case CCColourFormatChannelBlue:
                    break;
                    
                case CCColourFormatChannelAlpha:
                    break;
            }
        }
    }
    
    return FALSE;
}

size_t CCColourFormatPackIntoBuffer(CCColour Colour, void *Data)
{
    CCAssertLog((Colour.type & CCColourFormatOptionMask) == CCColourFormatOptionChannel4, @"Only supports colour formats with 4 channel configuration");
    _Static_assert((CCColourFormatChannelBitSizeMask >> CCColourFormatChannelBitSize) <= (sizeof(uint64_t) * 8), "Exceeds limit of packed data");
    
    int ChunkIndex = 0, ChunkSize = 0;
    uint64_t Chunk = 0;
    
    for (int Loop = 0; Loop < 4 && Colour.channel[Loop].type; Loop++)
    {
        const unsigned int Bits = CCColourComponentGetBitSize(Colour.channel[Loop]);
        
        if ((ChunkSize + Bits) > (sizeof(Chunk) * 8))
        {
            const int Remaining = (ChunkSize + Bits) - (sizeof(Chunk) * 8);
            const int Fit = Bits - Remaining;
            
            Chunk |= (Colour.channel[Loop].u64 & CCBitSet(Fit)) << ChunkSize;
            ((typeof(Chunk)*)Data)[ChunkIndex++] = Chunk;
            
            Chunk = (Colour.channel[Loop].u64 >> Fit) & CCBitSet(Remaining);
            ChunkSize = Remaining;
        }
        
        else
        {
            Chunk |= (Colour.channel[Loop].u64 & CCBitSet(Bits)) << ChunkSize;
            ChunkSize += Bits;
        }
    }
    
    const int Count = (ChunkSize + 7) / 8;
    for (int Loop = 0, Loop2 = ChunkIndex * sizeof(Chunk); Loop < Count; Loop++, Loop2++)
    {
        ((uint8_t*)Data)[Loop2] = ((uint8_t*)&Chunk)[Loop];
    }
    
    return (ChunkIndex * sizeof(Chunk)) + Count;
}

CCColourComponent CCColourFormatGetComponent(CCColour Colour, CCColourFormat Index)
{
    CCColourComponent Component = { .type = 0, .u64 = 0 };
    for (int Loop = 0; Loop < 4 && Colour.channel[Loop].type; Loop++)
    {
        if ((Colour.channel[Loop].type & CCColourFormatChannelIndexMask) == Index)
        {
            Component = Colour.channel[Loop];
            break;
        }
    }
    
    return Component;
}

static CC_FORCE_INLINE CC_CONSTANT_FUNCTION unsigned int CCColourComponentGetBitSize(CCColourComponent Component)
{
    return (Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize;
}

#pragma mark - Component Precision Conversions

static uint64_t CCColourFormatComponentPrecisionConversionLinear(uint64_t Value, int OldBitSize, int NewBitSize)
{
    const uint64_t OldSet = CCBitSet(OldBitSize), NewSet = CCBitSet(NewBitSize);
    return (uint64_t)(((double)Value * (double)NewSet + (double)(OldSet >> 1)) / (double)OldSet) - (NewBitSize >= 54 ? 1 : 0);
}

static uint64_t CCColourFormatComponentPrecisionConversionLinearSigned(uint64_t Value, int OldBitSize, int NewBitSize)
{
    const uint64_t OldSet = CCBitSet(OldBitSize), NewSet = CCBitSet(NewBitSize);
    return Value == 0 ? 0 : CCColourFormatComponentPrecisionConversionLinear((Value + (OldSet / 2) + 1) & OldSet, OldBitSize, NewBitSize) - (NewSet / 2) - 1;
}

CCColourComponent CCColourFormatRGBPrecisionConversion(CCColourComponent Component, CCColourFormat OldType, CCColourFormat NewType, int NewPrecision)
{
    if ((OldType == NewType) && (Component.type == NewPrecision)) return Component;
    
    if ((OldType & CCColourFormatTypeMask) == CCColourFormatTypeUnsignedInteger)
    {
        if (((NewType & CCColourFormatTypeMask) == CCColourFormatTypeSignedInteger) || ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeUnsignedInteger))
        {
            Component.u64 = CCColourFormatComponentPrecisionConversionLinear(Component.u64 & (CCBitSet(CCColourComponentGetBitSize(Component))), CCColourComponentGetBitSize(Component), NewPrecision);
            Component.type = (NewPrecision << CCColourFormatChannelBitSize) | (Component.type & CCColourFormatChannelIndexMask);
            
            return Component;
        }
        
        else if ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeFloat)
        {
            CCAssertLog(NewPrecision == 32, "Only supports 32-bit floats");
            
            Component.f32 = (float)(Component.u64 & (CCBitSet(CCColourComponentGetBitSize(Component))));
            
            if ((NewType & CCColourFormatNormalized))
            {
                Component.f32 /= CCBitSet(CCColourComponentGetBitSize(Component));
            }
            
            Component.type = (NewPrecision << CCColourFormatChannelBitSize) | (Component.type & CCColourFormatChannelIndexMask);
            
            return Component;
        }
    }
    
    else if ((OldType & CCColourFormatTypeMask) == CCColourFormatTypeSignedInteger)
    {
        if (((NewType & CCColourFormatTypeMask) == CCColourFormatTypeSignedInteger) || ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeUnsignedInteger))
        {
            Component.u64 = CCColourFormatComponentPrecisionConversionLinearSigned(Component.u64 & (CCBitSet(CCColourComponentGetBitSize(Component))), CCColourComponentGetBitSize(Component), NewPrecision);
            Component.type = (NewPrecision << CCColourFormatChannelBitSize) | (Component.type & CCColourFormatChannelIndexMask);
            
            return Component;
        }
        
        else if ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeFloat)
        {
            CCAssertLog(NewPrecision == 32, "Only supports 32-bit floats");
            
            Component.f32 = (float)((Component.u64 + (CCBitSet(CCColourComponentGetBitSize(Component)) / 2) + 1) & CCBitSet(CCColourComponentGetBitSize(Component)));
            Component.f32 -= (CCBitSet(CCColourComponentGetBitSize(Component)) / 2) + 1;
            
            if ((NewType & CCColourFormatNormalized))
            {
                Component.f32 = fmaxf(Component.f32 / (CCBitSet(CCColourComponentGetBitSize(Component)) / 2), -1.0f);
            }
            
            Component.type = (NewPrecision << CCColourFormatChannelBitSize) | (Component.type & CCColourFormatChannelIndexMask);
            
            return Component;
        }
    }
    
    else if ((OldType & CCColourFormatTypeMask) == CCColourFormatTypeFloat)
    {
        if ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeFloat)
        {
            CCAssertLog(NewPrecision == 32, "Only supports 32-bit floats");
            
            return Component;
        }
    }
    
    return (CCColourComponent){ .type = 0, .u64 = 0 };
}

#pragma mark - Component Getters

CCColourComponent CCColourFormatRGBGetComponent(CCColour Colour, CCColourFormat Index, CCColourFormat Type, int Precision)
{
    CCColourComponent Component = CCColourFormatGetComponent(Colour, Index);
    if (Component.type)
    {
        Component = CCColourFormatRGBPrecisionConversion(Component, Colour.type, Type, Precision);
    }
    
    return Component;
}
