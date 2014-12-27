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
#include "ColourFormat.h"
#import <CommonC/Types.h>
#import <CommonObjC/Assertion.h>


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
