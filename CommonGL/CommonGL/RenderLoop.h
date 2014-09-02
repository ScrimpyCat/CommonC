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

#ifndef CommonGL_RenderLoop_h
#define CommonGL_RenderLoop_h

#import <CommonC/Platform.h>
#import <CommonGL/Display.h>
#import <CommonGL/Context.h>
#import <CommonGL/RenderTimestamp.h>


#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#import <QuartzCore/QuartzCore.h>

#if CC_PLATFORM_OS_X
typedef CVDisplayLinkRef CCRenderLoop;
#else
typedef CADisplayLink *CCRenderLoop;
#endif

#else
typedef void *CCRenderLoop;
#endif


@protocol CCRenderLoop <NSObject>

-(void) renderLoop: (CCRenderLoop)renderLoop;

@end


CCRenderLoop CCRenderLoopCreate(id<CCRenderLoop> Target, CCGLContext Context);
CCRenderLoop CCRenderLoopCreateForDisplay(CCDisplay Display, id<CCRenderLoop> Target, CCGLContext Context);
void CCRenderLoopStart(CCRenderLoop RenderLoop);
void CCRenderLoopStop(CCRenderLoop RenderLoop);
void CCRenderLoopDestroy(CCRenderLoop RenderLoop);
_Bool CCRenderLoopIsRunning(CCRenderLoop RenderLoop);
CCRenderTimestamp CCRenderLoopTimestamp(CCRenderLoop RenderLoop);

#endif
