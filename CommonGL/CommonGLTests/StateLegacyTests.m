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

@import Cocoa;
@import OpenGL.GL;
@import XCTest;
#import "Common.h"

@interface State : XCTestCase

@end

@implementation State
{
    CCGLContext ctx;
}

-(void) setUp
{
    [super setUp];
    
    CGLPixelFormatObj PixelFormat;
    CGLChoosePixelFormat((CGLPixelFormatAttribute[]){
        kCGLPFAAllRenderers,
        kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute)kCGLOGLPVersion_Legacy,
        0
    }, &PixelFormat, &(GLint){0});
    
    CGLCreateContext(PixelFormat, NULL, &ctx);
    CGLDestroyPixelFormat(PixelFormat);
    
    CCGLContextSetCurrent(ctx);
}

-(void) tearDown
{
    CCGLContextSetCurrent(NULL);
    CGLDestroyContext(ctx);
    ctx = NULL;
    
    [super tearDown];
}

-(void) testStateBelongingToContext
{
    CGLPixelFormatObj PixelFormat;
    CGLChoosePixelFormat((CGLPixelFormatAttribute[]){0}, &PixelFormat, &(GLint){0});
    
    CCGLContext Other;
    CGLCreateContext(PixelFormat, NULL, &Other);
    CGLDestroyPixelFormat(PixelFormat);
    
    XCTAssertEqual(CCGLStateForContext(ctx), CCGLStateForContext(ctx), @"should return the same state object");
    XCTAssertEqual(CCGLStateForContext(Other), CCGLStateForContext(Other), @"should return the same state object");
    
    XCTAssertNotEqual(CCGLStateForContext(ctx), CCGLStateForContext(Other), @"should each hold their own state object");
    
    CGLDestroyContext(Other);
}

-(void) testBlendState
{
#if CC_GL_STATE_BLEND
    CCGLState *State = CCGLStateForContext(ctx);
    
    glBlendFunc(GL_ONE, GL_ONE); CC_GL_CHECK();
    glBlendEquation(GL_FUNC_ADD); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->blendFunc.rgb.src, GL_ONE, @"RGB blend func src should be GL_ONE");
    XCTAssertEqual(State->blendFunc.rgb.dst, GL_ONE, @"RGB blend func dst should be GL_ONE");
    XCTAssertEqual(State->blendFunc.alpha.src, GL_ONE, @"alpha blend func src should be GL_ONE");
    XCTAssertEqual(State->blendFunc.alpha.dst, GL_ONE, @"alpha blend func dst should be GL_ONE");
    
    XCTAssertEqual(State->blendEquation.rgb.mode, GL_FUNC_ADD, @"RGB blend equation should be GL_FUNC_ADD");
    XCTAssertEqual(State->blendEquation.alpha.mode, GL_FUNC_ADD, @"alpha blend equation should be GL_FUNC_ADD");
    
    
    glBlendFunc(GL_ZERO, GL_ZERO); CC_GL_CHECK();
    glBlendEquation(GL_FUNC_SUBTRACT); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->blendFunc.rgb.src, GL_ZERO, @"RGB blend func src should be GL_ZERO");
    XCTAssertEqual(State->blendFunc.rgb.dst, GL_ZERO, @"RGB blend func dst should be GL_ZERO");
    XCTAssertEqual(State->blendFunc.alpha.src, GL_ZERO, @"alpha blend func src should be GL_ZERO");
    XCTAssertEqual(State->blendFunc.alpha.dst, GL_ZERO, @"alpha blend func dst should be GL_ZERO");
    
    XCTAssertEqual(State->blendEquation.rgb.mode, GL_FUNC_SUBTRACT, @"RGB blend equation should be GL_FUNC_SUBTRACT");
    XCTAssertEqual(State->blendEquation.alpha.mode, GL_FUNC_SUBTRACT, @"alpha blend equation should be GL_FUNC_SUBTRACT");
#endif
}

#define TEST_GL_ENABLE(cap) \
glEnable(cap); CC_GL_CHECK(); \
CCGLStateInitializeWithCurrent(State); \
XCTAssertTrue(State->enabled._##cap, @#cap " should be enabled");

#define TEST_GL_DISABLE(cap) \
glDisable(cap); CC_GL_CHECK(); \
CCGLStateInitializeWithCurrent(State); \
XCTAssertFalse(State->enabled._##cap, @#cap " should be disabled");

-(void) testEnabledState
{
#if CC_GL_STATE_ENABLED
    CCGLState *State = CCGLStateForContext(ctx);
    
    TEST_GL_ENABLE(GL_ALPHA_TEST);
    TEST_GL_ENABLE(GL_AUTO_NORMAL);
    TEST_GL_ENABLE(GL_BLEND);
    TEST_GL_ENABLE(GL_COLOR_LOGIC_OP);
    TEST_GL_ENABLE(GL_COLOR_MATERIAL);
    TEST_GL_ENABLE(GL_COLOR_SUM);
    TEST_GL_ENABLE(GL_CULL_FACE);
    TEST_GL_ENABLE(GL_DEPTH_TEST);
    TEST_GL_ENABLE(GL_DITHER);
    TEST_GL_ENABLE(GL_FOG);
    TEST_GL_ENABLE(GL_INDEX_LOGIC_OP);
    TEST_GL_ENABLE(GL_LIGHTING);
    TEST_GL_ENABLE(GL_LINE_SMOOTH);
    TEST_GL_ENABLE(GL_LINE_STIPPLE);
    TEST_GL_ENABLE(GL_MAP1_COLOR_4);
    TEST_GL_ENABLE(GL_MAP1_INDEX);
    TEST_GL_ENABLE(GL_MAP1_NORMAL);
    TEST_GL_ENABLE(GL_MAP1_TEXTURE_COORD_1);
    TEST_GL_ENABLE(GL_MAP1_TEXTURE_COORD_2);
    TEST_GL_ENABLE(GL_MAP1_TEXTURE_COORD_3);
    TEST_GL_ENABLE(GL_MAP1_TEXTURE_COORD_4);
    TEST_GL_ENABLE(GL_MAP1_VERTEX_3);
    TEST_GL_ENABLE(GL_MAP1_VERTEX_4);
    TEST_GL_ENABLE(GL_MAP2_COLOR_4);
    TEST_GL_ENABLE(GL_MAP2_INDEX);
    TEST_GL_ENABLE(GL_MAP2_NORMAL);
    TEST_GL_ENABLE(GL_MAP2_TEXTURE_COORD_1);
    TEST_GL_ENABLE(GL_MAP2_TEXTURE_COORD_2);
    TEST_GL_ENABLE(GL_MAP2_TEXTURE_COORD_3);
    TEST_GL_ENABLE(GL_MAP2_TEXTURE_COORD_4);
    TEST_GL_ENABLE(GL_MAP2_VERTEX_3);
    TEST_GL_ENABLE(GL_MAP2_VERTEX_4);
    TEST_GL_ENABLE(GL_MULTISAMPLE);
    TEST_GL_ENABLE(GL_NORMALIZE);
    TEST_GL_ENABLE(GL_POINT_SMOOTH);
    TEST_GL_ENABLE(GL_POINT_SPRITE);
    TEST_GL_ENABLE(GL_POLYGON_OFFSET_FILL);
    TEST_GL_ENABLE(GL_POLYGON_OFFSET_LINE);
    TEST_GL_ENABLE(GL_POLYGON_OFFSET_POINT);
    TEST_GL_ENABLE(GL_POLYGON_SMOOTH);
    TEST_GL_ENABLE(GL_POLYGON_STIPPLE);
    TEST_GL_ENABLE(GL_RESCALE_NORMAL);
    TEST_GL_ENABLE(GL_SAMPLE_ALPHA_TO_COVERAGE);
    TEST_GL_ENABLE(GL_SAMPLE_ALPHA_TO_ONE);
    TEST_GL_ENABLE(GL_SAMPLE_COVERAGE);
    TEST_GL_ENABLE(GL_SCISSOR_TEST);
    TEST_GL_ENABLE(GL_STENCIL_TEST);
    TEST_GL_ENABLE(GL_TEXTURE_1D);
    TEST_GL_ENABLE(GL_TEXTURE_2D);
    TEST_GL_ENABLE(GL_TEXTURE_3D);
    TEST_GL_ENABLE(GL_TEXTURE_CUBE_MAP);
    TEST_GL_ENABLE(GL_TEXTURE_GEN_Q);
    TEST_GL_ENABLE(GL_TEXTURE_GEN_R);
    TEST_GL_ENABLE(GL_TEXTURE_GEN_S);
    TEST_GL_ENABLE(GL_TEXTURE_GEN_T);
    TEST_GL_ENABLE(GL_VERTEX_PROGRAM_POINT_SIZE);
    TEST_GL_ENABLE(GL_VERTEX_PROGRAM_TWO_SIDE);
    TEST_GL_ENABLE(GL_COLOR_TABLE);
    TEST_GL_ENABLE(GL_CONVOLUTION_1D);
    TEST_GL_ENABLE(GL_CONVOLUTION_2D);
    TEST_GL_ENABLE(GL_HISTOGRAM);
    TEST_GL_ENABLE(GL_MINMAX);
    TEST_GL_ENABLE(GL_POST_COLOR_MATRIX_COLOR_TABLE);
    TEST_GL_ENABLE(GL_POST_CONVOLUTION_COLOR_TABLE);
    TEST_GL_ENABLE(GL_SEPARABLE_2D);
    TEST_GL_ENABLE(GL_TEXTURE_RECTANGLE_ARB);
#endif
}

-(void) testDisabledState
{
#if CC_GL_STATE_ENABLED
    CCGLState *State = CCGLStateForContext(ctx);
    
    TEST_GL_DISABLE(GL_ALPHA_TEST);
    TEST_GL_DISABLE(GL_AUTO_NORMAL);
    TEST_GL_DISABLE(GL_BLEND);
    TEST_GL_DISABLE(GL_COLOR_LOGIC_OP);
    TEST_GL_DISABLE(GL_COLOR_MATERIAL);
    TEST_GL_DISABLE(GL_COLOR_SUM);
    TEST_GL_DISABLE(GL_CULL_FACE);
    TEST_GL_DISABLE(GL_DEPTH_TEST);
    TEST_GL_DISABLE(GL_DITHER);
    TEST_GL_DISABLE(GL_FOG);
    TEST_GL_DISABLE(GL_INDEX_LOGIC_OP);
    TEST_GL_DISABLE(GL_LIGHTING);
    TEST_GL_DISABLE(GL_LINE_SMOOTH);
    TEST_GL_DISABLE(GL_LINE_STIPPLE);
    TEST_GL_DISABLE(GL_MAP1_COLOR_4);
    TEST_GL_DISABLE(GL_MAP1_INDEX);
    TEST_GL_DISABLE(GL_MAP1_NORMAL);
    TEST_GL_DISABLE(GL_MAP1_TEXTURE_COORD_1);
    TEST_GL_DISABLE(GL_MAP1_TEXTURE_COORD_2);
    TEST_GL_DISABLE(GL_MAP1_TEXTURE_COORD_3);
    TEST_GL_DISABLE(GL_MAP1_TEXTURE_COORD_4);
    TEST_GL_DISABLE(GL_MAP1_VERTEX_3);
    TEST_GL_DISABLE(GL_MAP1_VERTEX_4);
    TEST_GL_DISABLE(GL_MAP2_COLOR_4);
    TEST_GL_DISABLE(GL_MAP2_INDEX);
    TEST_GL_DISABLE(GL_MAP2_NORMAL);
    TEST_GL_DISABLE(GL_MAP2_TEXTURE_COORD_1);
    TEST_GL_DISABLE(GL_MAP2_TEXTURE_COORD_2);
    TEST_GL_DISABLE(GL_MAP2_TEXTURE_COORD_3);
    TEST_GL_DISABLE(GL_MAP2_TEXTURE_COORD_4);
    TEST_GL_DISABLE(GL_MAP2_VERTEX_3);
    TEST_GL_DISABLE(GL_MAP2_VERTEX_4);
    TEST_GL_DISABLE(GL_MULTISAMPLE);
    TEST_GL_DISABLE(GL_NORMALIZE);
    TEST_GL_DISABLE(GL_POINT_SMOOTH);
    TEST_GL_DISABLE(GL_POINT_SPRITE);
    TEST_GL_DISABLE(GL_POLYGON_OFFSET_FILL);
    TEST_GL_DISABLE(GL_POLYGON_OFFSET_LINE);
    TEST_GL_DISABLE(GL_POLYGON_OFFSET_POINT);
    TEST_GL_DISABLE(GL_POLYGON_SMOOTH);
    TEST_GL_DISABLE(GL_POLYGON_STIPPLE);
    TEST_GL_DISABLE(GL_RESCALE_NORMAL);
    TEST_GL_DISABLE(GL_SAMPLE_ALPHA_TO_COVERAGE);
    TEST_GL_DISABLE(GL_SAMPLE_ALPHA_TO_ONE);
    TEST_GL_DISABLE(GL_SAMPLE_COVERAGE);
    TEST_GL_DISABLE(GL_SCISSOR_TEST);
    TEST_GL_DISABLE(GL_STENCIL_TEST);
    TEST_GL_DISABLE(GL_TEXTURE_1D);
    TEST_GL_DISABLE(GL_TEXTURE_2D);
    TEST_GL_DISABLE(GL_TEXTURE_3D);
    TEST_GL_DISABLE(GL_TEXTURE_CUBE_MAP);
    TEST_GL_DISABLE(GL_TEXTURE_GEN_Q);
    TEST_GL_DISABLE(GL_TEXTURE_GEN_R);
    TEST_GL_DISABLE(GL_TEXTURE_GEN_S);
    TEST_GL_DISABLE(GL_TEXTURE_GEN_T);
    TEST_GL_DISABLE(GL_VERTEX_PROGRAM_POINT_SIZE);
    TEST_GL_DISABLE(GL_VERTEX_PROGRAM_TWO_SIDE);
    TEST_GL_DISABLE(GL_COLOR_TABLE);
    TEST_GL_DISABLE(GL_CONVOLUTION_1D);
    TEST_GL_DISABLE(GL_CONVOLUTION_2D);
    TEST_GL_DISABLE(GL_HISTOGRAM);
    TEST_GL_DISABLE(GL_MINMAX);
    TEST_GL_DISABLE(GL_POST_COLOR_MATRIX_COLOR_TABLE);
    TEST_GL_DISABLE(GL_POST_CONVOLUTION_COLOR_TABLE);
    TEST_GL_DISABLE(GL_SEPARABLE_2D);
    TEST_GL_DISABLE(GL_TEXTURE_RECTANGLE_ARB);
#endif
}

@end
