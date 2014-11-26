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

@interface DebugTests : XCTestCase

@end

@implementation DebugTests
{
    CCGLContext ctx;
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
    
    CCGLContextSetCurrent(ctx);
}

-(void) tearDown
{
    CCGLContextSetCurrent(NULL);
    CCGLContextRelease(ctx);
    ctx = NULL;
    
    [super tearDown];
}

-(void) testObjectLabel
{
#if !CC_NO_GL_LABEL || CC_GL_SUPPORT_DEBUG_LABEL
    GLuint Buffer;
    glGenBuffers(1, &Buffer); CC_GL_CHECK();
    glBindBuffer(GL_ARRAY_BUFFER, Buffer); CC_GL_CHECK();
    
    CC_GL_LABEL_OBJECT(GL_BUFFER, Buffer, "hello");
    
    NSString *Label = CC_GL_GET_OBJECT_LABEL(GL_BUFFER, Buffer);
    XCTAssertEqualObjects(Label, @"hello", @"Should assign the label to the buffer");
    
    glDeleteBuffers(1, &Buffer); CC_GL_CHECK();
#endif
}

-(void) testGLErrorString
{
#define TEST_ERROR_STRING(type) XCTAssertEqualObjects([NSString stringWithUTF8String: CCGLErrorString(type)], @#type, @"glError type " #type " should return the exact string");
    
    TEST_ERROR_STRING(GL_NO_ERROR);
    TEST_ERROR_STRING(GL_INVALID_ENUM);
    TEST_ERROR_STRING(GL_INVALID_VALUE);
    TEST_ERROR_STRING(GL_INVALID_OPERATION);
#if GL_STACK_OVERFLOW
    TEST_ERROR_STRING(GL_STACK_OVERFLOW);
#endif
#if GL_STACK_UNDERFLOW
    TEST_ERROR_STRING(GL_STACK_UNDERFLOW);
#endif
    TEST_ERROR_STRING(GL_OUT_OF_MEMORY);
#if GL_INVALID_FRAMEBUFFER_OPERATION_EXT
    TEST_ERROR_STRING(GL_INVALID_FRAMEBUFFER_OPERATION_EXT);
#endif
}

@end
