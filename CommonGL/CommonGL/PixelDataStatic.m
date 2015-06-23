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
#import "PixelDataStatic.h"

@interface CCPixelDataStatic ()

@property (retain) CCGenericContainer *buffer1;
@property (retain) CCGenericContainer *buffer2;
@property (retain) CCGenericContainer *buffer3;
@property (retain) CCGenericContainer *buffer4;
@property size_t width;
@property size_t height;
@property size_t depth;
@property CCColourFormat format;

@end

@implementation CCPixelDataStatic
@synthesize format;

-(instancetype) initWithData: (CCGenericContainer*)data AsFormat: (CCColourFormat)colourFormat OfWidth: (size_t)width Height: (size_t)height Depth: (size_t)depth
{
    if ((self = [super init]))
    {
        self.buffer1 = data;
        self.width = width;
        self.height = height;
        self.depth = depth;
        self.format = colourFormat;
    }
    
    return self;
}

-(instancetype) initWithMultiPlanarData: (CCGenericContainer*[4])data AsFormat: (CCColourFormat)colourFormat OfWidth: (size_t)width Height: (size_t)height Depth: (size_t)depth
{
    if ((self = [super init]))
    {
        self.buffer1 = data[0];
        self.buffer2 = data[1];
        self.buffer3 = data[2];
        self.buffer4 = data[3];
        self.width = width;
        self.height = height;
        self.depth = depth;
        self.format = colourFormat;
    }
    
    return self;
}

-(CCColour) colourAtX: (size_t)x Y: (size_t)y Z: (size_t)z
{
    if (![self isInsideBoundsAtX: x Y: y Z: z]) return (CCColour){ .type = 0 }; //Or should we have proper sampling behaviour?
    
    const CCColourFormat Format = self.format;
    
    return CCColourUnpackFromBuffer(Format, (const void*[4]){
        self.buffer1.data + (CCColourFormatSampleSizeForPlanar(Format, CCColourFormatChannelPlanarIndex0) * (x + (self.width * y) + (self.height * z))),
        self.buffer2.data + (CCColourFormatSampleSizeForPlanar(Format, CCColourFormatChannelPlanarIndex1) * (x + (self.width * y) + (self.height * z))),
        self.buffer3.data + (CCColourFormatSampleSizeForPlanar(Format, CCColourFormatChannelPlanarIndex2) * (x + (self.width * y) + (self.height * z))),
        self.buffer4.data + (CCColourFormatSampleSizeForPlanar(Format, CCColourFormatChannelPlanarIndex3) * (x + (self.width * y) + (self.height * z)))
    });
}

-(void) dealloc
{
    self.buffer1 = nil;
    self.buffer2 = nil;
    self.buffer3 = nil;
    self.buffer4 = nil;
    
    [super dealloc];
}

@end
