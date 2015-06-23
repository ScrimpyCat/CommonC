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

#ifndef CommonGL_Colour_h
#define CommonGL_Colour_h

#include <CommonGL/ColourFormat.h>
#include <CommonGL/ColourComponent.h>

typedef struct {
    CCColourFormat type;
    CCColourComponent channel[4];
} CCColour;

#pragma mark -

/*!
 * @brief Packs the pixel colour into the buffer.
 * @discussion Combines all bit planes.
 * @param Colour The pixel colour to be packed into the buffer.
 * @param Data The buffer to store the colour.
 * @return The amount of bytes written to the buffer (bits rounded up to the next byte).
 */
size_t CCColourPackIntoBuffer(CCColour Colour, void *Data);

/*!
 * @brief Packs the pixel colour of a certain plane into the buffer.
 * @param Colour The pixel colour to be packed into the buffer.
 * @param PlanarIndex The plane to be used.
 * @param Data The buffer to store the colour.
 * @return The amount of bytes written to the buffer (bits rounded up to the next byte).
 */
size_t CCColourPackIntoBufferInPlanar(CCColour Colour, unsigned int PlanarIndex, void *Data);

CCColour CCColourUnpackFromBuffer(CCColourFormat ColourFormat, const void *Data[4]);
size_t CCColourGetChannelsInPlanar(CCColour Colour, unsigned int PlanarIndex, CCColourComponent Channels[4]);
size_t CCColourGetComponentChannelIndex(CCColour Colour, CCColourFormat Index);
CCColourComponent CCColourGetComponent(CCColour Colour, CCColourFormat Index);
CCColourComponent CCColourGetComponentWithPrecision(CCColour Colour, CCColourFormat Index, CCColourFormat Type, int Precision);

CCColour CCColourConversion(CCColour Colour, CCColourFormat NewFormat);


#endif
