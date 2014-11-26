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

@interface ContextTests : XCTestCase

@property _Bool containerReleased;

@end

static char Key1, Key2;
@implementation ContextTests
{
    CCGLContext ctx, ctx2;
    CCGenericContainer *object;
}
@synthesize containerReleased;

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
    
    @autoreleasepool {
        object = [CCGenericContainer containerOfSize: 0 ReleaserBlock: ^(void *Data, size_t Size, bool IsCopied){
            self.containerReleased = YES;
        }];
        
        CCGLContextSetAssociatedObject(ctx, &Key1, object);
    }
    
    self.containerReleased = NO;
}

-(void) tearDown
{
    CCGLContextSetCurrent(NULL);
    if (ctx) CCGLContextRelease(ctx);
    CCGLContextRelease(ctx2);
    ctx = NULL;
    ctx2 = NULL;
    
    [super tearDown];
}

-(void) testHoldingAssociatedObjects
{
    XCTAssertEqual(CCGLContextGetAssociatedObject(ctx, &Key1), object, @"Should hold that associated object");
}

-(void) testSettingAssociatedObjects
{
    NSNumber *a = @1, *b = @2, *c = @3;
    
    CCGLContextSetAssociatedObject(ctx, &Key1, a);
    CCGLContextSetAssociatedObject(ctx, &Key2, b);
    CCGLContextSetAssociatedObject(ctx2, &Key1, c);
    
    XCTAssertEqual(CCGLContextGetAssociatedObject(ctx, &Key1), a, @"Should replace the previous associated object with the new one");
    XCTAssertEqual(CCGLContextGetAssociatedObject(ctx, &Key2), b, @"Should hold that associated object");
    XCTAssertEqual(CCGLContextGetAssociatedObject(ctx2, &Key1), c, @"Should hold its own associated objects");
}

-(void) testReleasingAssociatedObjects
{
    CCGLContextRelease(ctx);
    ctx = NULL;
    XCTAssertTrue(self.containerReleased, @"Should release the associated objects on context destroy");
}

-(void) testSettingCurrentContext
{
    CCGLContextSetCurrent(ctx2);
    XCTAssertEqual(CCGLContextGetCurrent(), ctx2, @"Should equal the currently set context");
    
    CCGLContextSetCurrent(ctx);
    XCTAssertEqual(CCGLContextGetCurrent(), ctx, @"Should equal the currently set context");
}

@end
