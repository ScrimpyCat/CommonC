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
#import "PixelData.h"
#import <CommonObjc/Assertion.h>

@implementation CCPixelData
@synthesize format, planes;

-(CCColour) colourAtX: (size_t)x Y: (size_t)y Z: (size_t)z
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: @"Must override in subclass" userInfo: nil];
}

-(void) getPackedData: (void*)data WithWidth: (size_t)width Height: (size_t)height Depth: (size_t)depth
{
    [self getPackedData: data AsFormat: self.format WithWidth: width Height: height Depth: depth];
}

-(void) getPackedData: (void*)data AsFormat: (CCColourFormat)type WithWidth: (size_t)width Height: (size_t)height Depth: (size_t)depth
{
    CCAssertLog(self.format == type, @"Currently does not support conversions");
    
    for (size_t LoopZ = 0; LoopZ < depth; LoopZ++)
    {
        for (size_t LoopY = 0; LoopY < height; LoopY++)
        {
            for (size_t LoopX = 0; LoopX < width; LoopX++)
            {
                CCColour Pixel = [self colourAtX: LoopX Y: LoopY Z: LoopZ];
                CCAssertLog((Pixel.type & CCColourFormatOptionChannel4), @"Only supports colour formats with 4 channel configuration");
                
                //convert
                
                data += CCColourPackIntoBuffer(Pixel, data);
            }
        }
    }
}

@end
