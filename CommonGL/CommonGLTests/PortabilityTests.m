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

@interface PortabilityTests : XCTestCase

@end

@implementation PortabilityTests
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

-(void) testRemap
{
    CCGLEnumMapping Mapping[2] = {
        { 1, 10 }, { 2, 20 }
    };
    
    XCTAssertEqual(CCGLEnumRemap(0, Mapping, 2), 0, @"Values that aren't remapped in the mapping struct should be returned unchanged");
    XCTAssertEqual(CCGLEnumRemap(1, Mapping, 2), 10, @"Values that are remapped in the mapping struct should return changed");
    XCTAssertEqual(CCGLEnumRemap(2, Mapping, 2), 20, @"Values that are remapped in the mapping struct should return changed");
}

-(void) testFunctionLookup
{
    void *Func = CCGLFunction("glEnable"), *GLFunc = glEnable;
    XCTAssertEqual(Func, GLFunc, @"Should return the pointer to glEnable");
    
    Func = CCGLFunction("");
    XCTAssertEqual(Func, NULL, @"When GL function does not exist it should return NULL");
    
    void *Funcs[3], *GLFuncs[3] = { glEnable, glDisable, glGetError };
    CCGLFunctionBatch((const char*[]){
        "glEnable",
        "glDisable",
        "glGetError"
    }, 3, Funcs, NO);
    
    XCTAssertEqual(Funcs[0], GLFuncs[0], @"Should return the pointer to glEnable and at the index it is requested at");
    XCTAssertEqual(Funcs[1], GLFuncs[1], @"Should return the pointer to glDisable and at the index it is requested at");
    XCTAssertEqual(Funcs[2], GLFuncs[2], @"Should return the pointer to glGetError and at the index it is requested at");
    
    
    Funcs[0] = NULL; Funcs[1] = NULL; Funcs[2] = NULL;
    CCGLFunctionBatch((const char*[]){
        "glEnable",
        "",
        "glGetError"
    }, 3, Funcs, NO);
    
    XCTAssertEqual(Funcs[0], GLFuncs[0], @"Should return the pointer to glEnable and at the index it is requested at");
    XCTAssertEqual(Funcs[1], NULL, @"Should return the null because the function does not exist");
    XCTAssertEqual(Funcs[2], GLFuncs[2], @"Should not stop and still return the pointer to glGetError and at the index it is requested at");
    
    
    Funcs[0] = NULL; Funcs[1] = NULL; Funcs[2] = NULL;
    CCGLFunctionBatch((const char*[]){
        "glEnable",
        "",
        "glGetError"
    }, 3, Funcs, YES);
    
    XCTAssertEqual(Funcs[0], GLFuncs[0], @"Should return the pointer to glEnable and at the index it is requested at");
    XCTAssertEqual(Funcs[1], NULL, @"Should return the null because the function does not exist");
    XCTAssertEqual(Funcs[2], NULL, @"Should stop when reaches first non-existent function");
    
    
    void *GLFuncEnable, *GLFuncDisable, *GLFuncGetError;
    void **Funcs2[3] = {
        &GLFuncEnable,
        &GLFuncDisable,
        &GLFuncGetError
    };
    
    CCGLFunctionBatchPtr((const char*[]){
        "glEnable",
        "glDisable",
        "glGetError"
    }, 3, Funcs2, NO);
    
    XCTAssertEqual(GLFuncEnable, GLFuncs[0], @"Should return the pointer to glEnable and at the index it is requested at");
    XCTAssertEqual(GLFuncDisable, GLFuncs[1], @"Should return the pointer to glDisable and at the index it is requested at");
    XCTAssertEqual(GLFuncGetError, GLFuncs[2], @"Should return the pointer to glGetError and at the index it is requested at");
    
    
    GLFuncEnable = NULL, GLFuncDisable = NULL, GLFuncGetError = NULL;
    CCGLFunctionBatchPtr((const char*[]){
        "glEnable",
        "",
        "glGetError"
    }, 3, Funcs2, NO);
    
    XCTAssertEqual(GLFuncEnable, GLFuncs[0], @"Should return the pointer to glEnable and at the index it is requested at");
    XCTAssertEqual(GLFuncDisable, NULL, @"Should return the null because the function does not exist");
    XCTAssertEqual(GLFuncGetError, GLFuncs[2], @"Should not stop and still return the pointer to glGetError and at the index it is requested at");
    

    GLFuncEnable = NULL, GLFuncDisable = NULL, GLFuncGetError = NULL;
    CCGLFunctionBatchPtr((const char*[]){
        "glEnable",
        "",
        "glGetError"
    }, 3, Funcs2, YES);
    
    XCTAssertEqual(GLFuncEnable, GLFuncs[0], @"Should return the pointer to glEnable and at the index it is requested at");
    XCTAssertEqual(GLFuncDisable, NULL, @"Should return the null because the function does not exist");
    XCTAssertEqual(GLFuncGetError, NULL, @"Should stop when reaches first non-existent function");

}

@end
