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
#import "RenderLoop.h"
#import <CommonC/Types.h>


#if CC_PLATFORM_OS_X
#import <Cocoa/Cocoa.h>

static CVReturn DisplayCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, id<CCRenderLoop> displayLinkContext)
{
    @autoreleasepool {
        [displayLinkContext renderLoop: displayLink];
    }
    
    return kCVReturnSuccess;
}
#endif

CCRenderLoop CCRenderLoopCreate(id<CCRenderLoop> Target, CCGLContext Context)
{
    return CCRenderLoopCreateForDisplay(CCDisplayMain(), Target, Context);
}

CCRenderLoop CCRenderLoopCreateForDisplay(CCDisplay Display, id<CCRenderLoop> Target, CCGLContext Context)
{
    CCRenderLoop RenderLoop = NULL;
    
#if CC_PLATFORM_OS_X
    if (CVDisplayLinkCreateWithActiveCGDisplays(&RenderLoop) == kCVReturnSuccess)
    {
        CVDisplayLinkSetCurrentCGDisplay(RenderLoop, Display);
        CVDisplayLinkSetOutputCallback(RenderLoop, (CVDisplayLinkOutputCallback)DisplayCallback, Target);
        CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(RenderLoop, Context, CGLGetPixelFormat(Context));
        CVDisplayLinkStart(RenderLoop);
    }
#elif CC_PLATFORM_IOS
    RenderLoop = [[Display displayLinkWithTarget: Target selector: @selector(renderLoop:)] retain];
    [RenderLoop addToRunLoop: [NSRunLoop currentRunLoop] forMode: NSDefaultRunLoopMode];
#endif
    
    return RenderLoop;
}

void CCRenderLoopStart(CCRenderLoop RenderLoop)
{
    if (CCRenderLoopIsRunning(RenderLoop)) return;
    
#if CC_PLATFORM_OS_X
    CVDisplayLinkStart(RenderLoop);
#elif CC_PLATFORM_IOS
    RenderLoop.paused = NO;
#endif
}

void CCRenderLoopStop(CCRenderLoop RenderLoop)
{
    if (!CCRenderLoopIsRunning(RenderLoop)) return;
    
#if CC_PLATFORM_OS_X
    CVDisplayLinkStop(RenderLoop);
#elif CC_PLATFORM_IOS
    RenderLoop.paused = YES;
#endif
}

void CCRenderLoopDestroy(CCRenderLoop RenderLoop)
{
    CCRenderLoopStop(RenderLoop);
    
#if CC_PLATFORM_OS_X
    CVDisplayLinkRelease(RenderLoop);
#elif CC_PLATFORM_IOS
    [RenderLoop invalidate];
    [RenderLoop release];
#endif
}

_Bool CCRenderLoopIsRunning(CCRenderLoop RenderLoop)
{
#if CC_PLATFORM_OS_X
    return CVDisplayLinkIsRunning(RenderLoop);
#elif CC_PLATFORM_IOS
    return !RenderLoop.paused;
#else
    return FALSE;
#endif
}

CCRenderTimestamp CCRenderLoopTimestamp(CCRenderLoop RenderLoop)
{
#if CC_PLATFORM_OS_X
    CVTimeStamp Timestamp = { .version = 0 };
    return CVDisplayLinkGetCurrentTime(RenderLoop, &Timestamp) == kCVReturnSuccess ? (CCRenderTimestamp){ .time = Timestamp.videoTime, .scale = Timestamp.videoTimeScale } : CCRenderTimestampZero;
#elif CC_PLATFORM_IOS
    return RenderLoop.timestamp;
#else
    return CCRenderTimestampZero;
#endif
}
