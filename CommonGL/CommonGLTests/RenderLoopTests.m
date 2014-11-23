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

@interface RenderLoopTests : XCTestCase <CCRenderLoop>

@end

@implementation RenderLoopTests
{
    CCGLContext ctx;
    CCRenderLoop renderLoop;
    
    size_t index;
}

-(void) setUp
{
    [super setUp];
    
    CGLPixelFormatObj PixelFormat;
    CGLChoosePixelFormat((CGLPixelFormatAttribute[]){
        kCGLPFAAllRenderers,
#ifdef CC_OPENGL_MODERN
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_GL4_Core,
#elif defined(CC_OPENGL_LEGACY)
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_Legacy,
#endif
        0
    }, &PixelFormat, &(GLint){0});
    
    CGLCreateContext(PixelFormat, NULL, &ctx);
    CGLDestroyPixelFormat(PixelFormat);
    
    index = 0;
    renderLoop = CCRenderLoopCreate(self, ctx);
}

-(void) tearDown
{
    CCRenderLoopDestroy(renderLoop);
    
    CCGLContextSetCurrent(NULL);
    CGLDestroyContext(ctx);
    ctx = NULL;
    
    [super tearDown];
}

-(void) renderLoop: (CCRenderLoop)renderLoop
{
    index++;
}

-(void) testLoop
{
    const size_t PrevIndex = index;
    [NSThread sleepForTimeInterval: 1.0];
    XCTAssertNotEqual(PrevIndex, index, @"Should be continually calling renderLoop:");
}

-(void) testStop
{
    CCRenderLoopStop(renderLoop);
    
    const size_t PrevIndex = index;
    [NSThread sleepForTimeInterval: 1.0];
    XCTAssertEqual(PrevIndex, index, @"Should not be calling renderLoop: whilst stopped");
}

-(void) testIsRunning
{
    XCTAssertTrue(CCRenderLoopIsRunning(renderLoop), @"Should be running when created");
    
    CCRenderLoopStop(renderLoop);
    XCTAssertFalse(CCRenderLoopIsRunning(renderLoop), @"Should not be running after stopped");
    
    CCRenderLoopStart(renderLoop);
    XCTAssertTrue(CCRenderLoopIsRunning(renderLoop), @"Should be running after started again");
}

@end
