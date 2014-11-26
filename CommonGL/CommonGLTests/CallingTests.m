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

@interface CallingTests : XCTestCase

@end

@implementation CallingTests
{
    CCGLContext ctx, ctx2;
    _Bool finished, finished2;
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
    CGLCreateContext(PixelFormat, NULL, &ctx2);
    CGLDestroyPixelFormat(PixelFormat);
    
    CCGLContextSetCurrent(ctx);
}

-(void) tearDown
{
    CCGLContextSetCurrent(NULL);
    CGLDestroyContext(ctx);
    CGLDestroyContext(ctx2);
    ctx = NULL;
    ctx2 = NULL;
    
    [super tearDown];
}

-(void) testEntryMacroGetsContext
{
    CC_GL_ENTRY;
    
    XCTAssertEqual(CC_GL_CURRENT_CONTEXT, CCGLContextGetCurrent(), @"Should initialize CC_GL_CURRENT_CONTEXT with the current context");
    
    CC_GL_EXIT;
}

-(void) testEntryMacroGetsState
{
    CC_GL_ENTRY;

    XCTAssertEqual(CC_GL_CURRENT_STATE, CCGLStateForContext(CC_GL_CURRENT_CONTEXT), @"Should initialize CC_GL_CURRENT_STATE with state for the current context");
    
    CC_GL_EXIT;
}

-(void) testEntryForContextMacroGetsContext
{
    CC_GL_ENTRY_FOR_CONTEXT(ctx2);
    
    XCTAssertEqual(CC_GL_CURRENT_CONTEXT, ctx2, @"Should initialize CC_GL_CURRENT_CONTEXT to the specified context");
    XCTAssertEqual(CCGLContextGetCurrent(), ctx2, @"Should set the current context to the specified context");
    
    CC_GL_EXIT_FROM_CONTEXT(ctx2);
}

-(void) testEntryForContextMacroGetsState
{
    CC_GL_ENTRY_FOR_CONTEXT(ctx2);
    
    XCTAssertEqual(CC_GL_CURRENT_STATE, CCGLStateForContext(CC_GL_CURRENT_CONTEXT), @"Should initialize CC_GL_CURRENT_STATE with state for the specified context");
    XCTAssertNotEqual(CC_GL_CURRENT_STATE, CCGLStateForContext(ctx), @"Should not be set to the original current context's state");
    
    CC_GL_EXIT_FROM_CONTEXT(ctx2);
}

-(void) testExitForContextRestoresPreviousCurrentContext
{
    CC_GL_ENTRY_FOR_CONTEXT(ctx2);
    CC_GL_EXIT_FROM_CONTEXT(ctx2);
    
    XCTAssertEqual(ctx, CCGLContextGetCurrent(), @"Should be restored back to previous current context");
}

-(void) useMainContext
{
    CCGLContextSetCurrent(ctx);
    CC_GL_ENTRY;
    CC_GL_EXIT;
    
    finished = TRUE;
}

-(void) useCtx
{
    CC_GL_ENTRY_FOR_CONTEXT(ctx);
    CC_GL_EXIT_FROM_CONTEXT(ctx);
    
    finished = TRUE;
}

-(void) useCtx2
{
    CC_GL_ENTRY_FOR_CONTEXT(ctx2);
    CC_GL_EXIT_FROM_CONTEXT(ctx2);
    
    finished2 = TRUE;
}

-(void) testLocks
{
    CC_GL_ENTRY;
    
    [NSThread detachNewThreadSelector: @selector(useMainContext) toTarget: self withObject: nil];
    [NSThread sleepForTimeInterval: 1.0];
    
    XCTAssertFalse(finished, @"The other thread should be locked");
    
    CC_GL_EXIT;
}

-(void) testLocksForSpecifiedContext
{
    CC_GL_ENTRY_FOR_CONTEXT(ctx2);
    
    [NSThread detachNewThreadSelector: @selector(useCtx) toTarget: self withObject: nil];
    [NSThread detachNewThreadSelector: @selector(useCtx2) toTarget: self withObject: nil];
    [NSThread sleepForTimeInterval: 1.0];
    
    XCTAssertTrue(finished, @"The other thread should not be locked as it is a separate context");
    XCTAssertFalse(finished2, @"The other thread should be locked");
    
    CC_GL_EXIT_FROM_CONTEXT(ctx2);
}

@end
