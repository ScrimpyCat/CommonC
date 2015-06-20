/*
 *  Copyright (c) 2015 Stefan Johnson
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
#include "ColourComponent.h"
#include <CommonC/Assertion.h>
#include <CommonC/BitTricks.h>

CC_CONSTANT_FUNCTION unsigned int CCColourComponentGetBitSize(CCColourComponent Component)
{
    return (Component.type & CCColourFormatChannelBitSizeMask) >> CCColourFormatChannelBitSize;
}

#pragma mark - Component Precision Conversions

static CC_CONSTANT_FUNCTION uint64_t CCIntegerPrecisionConversionLinear(uint64_t Value, int OldBitSize, int NewBitSize)
{
    const uint64_t OldSet = CCBitSet(OldBitSize), NewSet = CCBitSet(NewBitSize);
    return (uint64_t)(((double)Value * (double)NewSet + (double)(OldSet >> 1)) / (double)OldSet) - (NewBitSize >= 54 ? 1 : 0);
}

static CC_CONSTANT_FUNCTION uint64_t CCIntegerPrecisionConversionLinearSigned(uint64_t Value, int OldBitSize, int NewBitSize)
{
    const uint64_t OldSet = CCBitSet(OldBitSize), NewSet = CCBitSet(NewBitSize);
    return Value == 0 ? 0 : CCIntegerPrecisionConversionLinear((Value + (OldSet / 2) + 1) & OldSet, OldBitSize, NewBitSize) - (NewSet / 2) - 1;
}

CC_CONSTANT_FUNCTION CCColourComponent CCColourComponentLinearPrecisionConversion(CCColourComponent Component, CCColourFormat OldType, CCColourFormat NewType, int NewPrecision)
{
    if ((OldType == NewType) && (Component.type == NewPrecision)) return Component;
    
    if ((OldType & CCColourFormatTypeMask) == CCColourFormatTypeUnsignedInteger)
    {
        if (((NewType & CCColourFormatTypeMask) == CCColourFormatTypeSignedInteger) || ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeUnsignedInteger))
        {
            Component.u64 = CCIntegerPrecisionConversionLinear(Component.u64 & (CCBitSet(CCColourComponentGetBitSize(Component))), CCColourComponentGetBitSize(Component), NewPrecision);
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
            Component.u64 = CCIntegerPrecisionConversionLinearSigned(Component.u64 & (CCBitSet(CCColourComponentGetBitSize(Component))), CCColourComponentGetBitSize(Component), NewPrecision);
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
        
        else if ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeUnsignedInteger)
        {
            const uint64_t NewValueMax = CCBitSet(NewPrecision);
            if ((OldType & CCColourFormatNormalized))
            {
                Component.f32 *= NewValueMax;
            }
            
            Component.u64 = Component.f32 < 0.0f ? 0 : (uint64_t)Component.f32;
            if (Component.u64 > NewValueMax) Component.u64 = NewValueMax;
            
            Component.type = (NewPrecision << CCColourFormatChannelBitSize) | (Component.type & CCColourFormatChannelIndexMask);
            
            return Component;
        }
        
        else if ((NewType & CCColourFormatTypeMask) == CCColourFormatTypeSignedInteger)
        {
            const uint64_t NewValueMax = CCBitSet(NewPrecision);
            if ((OldType & CCColourFormatNormalized))
            {
                Component.f32 *= (NewValueMax / 2) + (Component.f32 < 0 ? 1 : 0);
            }
            
            Component.u64 = (uint64_t)Component.f32 & NewValueMax;
            Component.type = (NewPrecision << CCColourFormatChannelBitSize) | (Component.type & CCColourFormatChannelIndexMask);
            
            return Component;
        }
    }
    
    return (CCColourComponent){ .type = 0, .u64 = 0 };
}
