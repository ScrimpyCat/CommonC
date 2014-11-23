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
#ifndef CC_OPENGL_LEGACY
#warning "Will not run test. Must set the framework's GL version to legacy to run this test."
#else

@import Cocoa;
@import OpenGL.GL;
@import XCTest;
#import "Common.h"

@interface StateLegacyTests : XCTestCase

@end

@implementation StateLegacyTests
{
    CCGLContext ctx;
}

-(void) setUp
{
    [super setUp];
    
    CGLPixelFormatObj PixelFormat;
    CGLChoosePixelFormat((CGLPixelFormatAttribute[]){
        kCGLPFAAllRenderers,
        kCGLPFAStencilSize, 1,
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

-(void) testBufferState
{
#if CC_GL_STATE_BUFFER
#define TEST_BUFFER_TARGET(target) { target, &State->bindBuffer._##target, #target }
    CCGLState *State = CCGLStateForContext(ctx);
    
    const struct {
        GLenum target;
        const GLenum *state;
        char *name;
    } BufferTargets[] = {
        TEST_BUFFER_TARGET(GL_ARRAY_BUFFER),
        CC_GL_VERSION_ACTIVE(4_2, NA, 3_1, NA, TEST_BUFFER_TARGET(GL_ATOMIC_COUNTER_BUFFER),)
#if GL_COPY_READ_BUFFER_BINDING
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, TEST_BUFFER_TARGET(GL_COPY_READ_BUFFER),)
#endif
#if GL_COPY_WRITE_BUFFER_BINDING
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, TEST_BUFFER_TARGET(GL_COPY_WRITE_BUFFER),)
#endif
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, TEST_BUFFER_TARGET(GL_DISPATCH_INDIRECT_BUFFER),)
        CC_GL_VERSION_ACTIVE(4_0, NA, 3_1, NA, TEST_BUFFER_TARGET(GL_DRAW_INDIRECT_BUFFER),)
        TEST_BUFFER_TARGET(GL_ELEMENT_ARRAY_BUFFER),
        CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, TEST_BUFFER_TARGET(GL_PIXEL_PACK_BUFFER),)
        CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, TEST_BUFFER_TARGET(GL_PIXEL_UNPACK_BUFFER),)
        CC_GL_VERSION_ACTIVE(4_4, NA, NA, NA, TEST_BUFFER_TARGET(GL_QUERY_BUFFER),)
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, TEST_BUFFER_TARGET(GL_SHADER_STORAGE_BUFFER),)
#if GL_TEXTURE_BUFFER_BINDING
        CC_GL_VERSION_ACTIVE(3_1, NA, NA, NA, TEST_BUFFER_TARGET(GL_TEXTURE_BUFFER),)
#endif
        CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, TEST_BUFFER_TARGET(GL_TRANSFORM_FEEDBACK_BUFFER),)
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, TEST_BUFFER_TARGET(GL_UNIFORM_BUFFER),)
    };
    const size_t Count = sizeof(BufferTargets) / sizeof(typeof(*BufferTargets));
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        glBindBuffer(BufferTargets[Loop].target, 0); CC_GL_CHECK();
    }
    
    CCGLStateInitializeWithCurrent(State);
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        XCTAssertEqual(*BufferTargets[Loop].state, 0, @"%s should be %u", BufferTargets[Loop].name, 0);
    }
    
    
    GLuint Buffers[Count];
    
    glGenBuffers(Count, Buffers); CC_GL_CHECK();
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        glBindBuffer(BufferTargets[Loop].target, Buffers[Loop]); CC_GL_CHECK();
    }
    
    CCGLStateInitializeWithCurrent(State);
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        XCTAssertEqual(*BufferTargets[Loop].state, Buffers[Loop], @"%s should be %u", BufferTargets[Loop].name, Buffers[Loop]);
    }
    
    glDeleteBuffers(Count, Buffers); CC_GL_CHECK();
#endif
}

-(void) testColourState
{
#if CC_GL_STATE_COLOUR
    CCGLState *State = CCGLStateForContext(ctx);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); CC_GL_CHECK();
    glColorMask(FALSE, FALSE, FALSE, FALSE); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->clearColour.red, 0.0f, @"should be 0.0");
    XCTAssertEqual(State->clearColour.green, 0.0f, @"should be 0.0");
    XCTAssertEqual(State->clearColour.blue, 0.0f, @"should be 0.0");
    XCTAssertEqual(State->clearColour.alpha, 0.0f, @"should be 0.0");
    XCTAssertFalse(State->colourMask.red, @"should be false");
    XCTAssertFalse(State->colourMask.green, @"should be false");
    XCTAssertFalse(State->colourMask.blue, @"should be false");
    XCTAssertFalse(State->colourMask.alpha, @"should be false");
    
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); CC_GL_CHECK();
    glColorMask(TRUE, TRUE, TRUE, TRUE); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->clearColour.red, 1.0f, @"should be 1.0");
    XCTAssertEqual(State->clearColour.green, 1.0f, @"should be 1.0");
    XCTAssertEqual(State->clearColour.blue, 1.0f, @"should be 1.0");
    XCTAssertEqual(State->clearColour.alpha, 1.0f, @"should be 1.0");
    XCTAssertTrue(State->colourMask.red, @"should be true");
    XCTAssertTrue(State->colourMask.green, @"should be true");
    XCTAssertTrue(State->colourMask.blue, @"should be true");
    XCTAssertTrue(State->colourMask.alpha, @"should be true");
#endif
}

-(void) testCullFaceState
{
#if CC_GL_STATE_CULL_FACE
    CCGLState *State = CCGLStateForContext(ctx);
    
    glCullFace(GL_FRONT); CC_GL_CHECK();
    glFrontFace(GL_CW); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->cullFace.mode, GL_FRONT, @"should be GL_FRONT");
    XCTAssertEqual(State->frontFace.mode, GL_CW, @"should be GL_CW");
    
    
    glCullFace(GL_BACK); CC_GL_CHECK();
    glFrontFace(GL_CCW); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->cullFace.mode, GL_BACK, @"should be GL_BACK");
    XCTAssertEqual(State->frontFace.mode, GL_CCW, @"should be GL_CCW");
#endif
}

-(void) testDepthState
{
#if CC_GL_STATE_DEPTH
    CCGLState *State = CCGLStateForContext(ctx);
    
    glClearDepth(0.0f); CC_GL_CHECK();
    glDepthFunc(GL_NEVER); CC_GL_CHECK();
    glDepthMask(FALSE); CC_GL_CHECK();
    glDepthRange(0.0f, 0.0f); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->clearDepth.depth, 0.0f, @"should be 0.0");
    XCTAssertEqual(State->depthFunc.func, GL_NEVER, @"should be GL_NEVER");
    XCTAssertFalse(State->depthMask.flag, @"should be false");
    XCTAssertEqual(State->depthRange.near, 0.0f, @"should be 0.0");
    XCTAssertEqual(State->depthRange.far, 0.0f, @"should be 0.0");
    
    
    glClearDepth(1.0f); CC_GL_CHECK();
    glDepthFunc(GL_ALWAYS); CC_GL_CHECK();
    glDepthMask(TRUE); CC_GL_CHECK();
    glDepthRange(1.0f, 1.0f); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->clearDepth.depth, 1.0f, @"should be 1.0");
    XCTAssertEqual(State->depthFunc.func, GL_ALWAYS, @"should be GL_ALWAYS");
    XCTAssertTrue(State->depthMask.flag, @"should be true");
    XCTAssertEqual(State->depthRange.near, 1.0f, @"should be 1.0");
    XCTAssertEqual(State->depthRange.far, 1.0f, @"should be 1.0");
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

-(void) testFramebufferState
{
#if CC_GL_STATE_FRAMEBUFFER
    CCGLState *State = CCGLStateForContext(ctx);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->bindFramebuffer.read, 0, @"should be 0");
    XCTAssertEqual(State->bindFramebuffer.write, 0, @"should be 0");
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, 1); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->bindFramebuffer.read, 1, @"should be 1");
    XCTAssertEqual(State->bindFramebuffer.write, 1, @"should be 1");
#endif
}

-(void) testScissorState
{
#if CC_GL_STATE_SCISSOR
    CCGLState *State = CCGLStateForContext(ctx);
    
    glScissor(0, 0, 0, 0); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->scissor.x, 0, @"should be 0");
    XCTAssertEqual(State->scissor.y, 0, @"should be 0");
    XCTAssertEqual(State->scissor.width, 0, @"should be 0");
    XCTAssertEqual(State->scissor.height, 0, @"should be 0");
    
    
    glScissor(1, 2, 3, 4); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->scissor.x, 1, @"should be 1");
    XCTAssertEqual(State->scissor.y, 2, @"should be 2");
    XCTAssertEqual(State->scissor.width, 3, @"should be 3");
    XCTAssertEqual(State->scissor.height, 4, @"should be 4");
#endif
}

-(void) testShaderState
{
#if CC_GL_STATE_SHADER
    CCGLState *State = CCGLStateForContext(ctx);
    
    glUseProgram(0); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->useProgram.program, 0, @"should be 0");
    
    
    //todo: create valid program so this will pass (just leave it till shader class is added so this very simple)
    glUseProgram(1); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->useProgram.program, 1, @"should be 1");
#endif
}

-(void) testStencilState
{
#if CC_GL_STATE_STENCIL
    CCGLState *State = CCGLStateForContext(ctx);
    
    glClearStencil(0); CC_GL_CHECK();
    glStencilFunc(GL_NEVER, 0, 0); CC_GL_CHECK();
    glStencilMask(0); CC_GL_CHECK();
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->clearStencil.s, 0, @"should be 0");
    XCTAssertEqual(State->stencilFunc.front.func, GL_NEVER, @"should be GL_NEVER");
    XCTAssertEqual(State->stencilFunc.front.ref, 0, @"should be 0");
    XCTAssertEqual(State->stencilFunc.front.mask, 0, @"should be 0");
    XCTAssertEqual(State->stencilFunc.back.func, GL_NEVER, @"should be GL_NEVER");
    XCTAssertEqual(State->stencilFunc.back.ref, 0, @"should be 0");
    XCTAssertEqual(State->stencilFunc.back.mask, 0, @"should be 0");
    XCTAssertEqual(State->stencilMask.front.mask, 0, @"should be 0");
    XCTAssertEqual(State->stencilMask.back.mask, 0, @"should be 0");
    XCTAssertEqual(State->stencilOp.front.sfail, GL_KEEP, @"should be GL_KEEP");
    XCTAssertEqual(State->stencilOp.front.dpfail, GL_KEEP, @"should be GL_KEEP");
    XCTAssertEqual(State->stencilOp.front.dppass, GL_KEEP, @"should be GL_KEEP");
    XCTAssertEqual(State->stencilOp.back.sfail, GL_KEEP, @"should be GL_KEEP");
    XCTAssertEqual(State->stencilOp.back.dpfail, GL_KEEP, @"should be GL_KEEP");
    XCTAssertEqual(State->stencilOp.back.dppass, GL_KEEP, @"should be GL_KEEP");
    
    
    glClearStencil(1); CC_GL_CHECK();
    glStencilFunc(GL_ALWAYS, 1, 1); CC_GL_CHECK();
    glStencilMask(1); CC_GL_CHECK();
    glStencilOp(GL_ZERO, GL_INCR, GL_DECR); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->clearStencil.s, 1, @"should be 1");
    XCTAssertEqual(State->stencilFunc.front.func, GL_ALWAYS, @"should be GL_ALWAYS");
    XCTAssertEqual(State->stencilFunc.front.ref, 1, @"should be 1");
    XCTAssertEqual(State->stencilFunc.front.mask, 1, @"should be 1");
    XCTAssertEqual(State->stencilFunc.back.func, GL_ALWAYS, @"should be GL_ALWAYS");
    XCTAssertEqual(State->stencilFunc.back.ref, 1, @"should be 1");
    XCTAssertEqual(State->stencilFunc.back.mask, 1, @"should be 1");
    XCTAssertEqual(State->stencilMask.front.mask, 1, @"should be 1");
    XCTAssertEqual(State->stencilMask.back.mask, 1, @"should be 1");
    XCTAssertEqual(State->stencilOp.front.sfail, GL_ZERO, @"should be GL_ZERO");
    XCTAssertEqual(State->stencilOp.front.dpfail, GL_INCR, @"should be GL_INCR");
    XCTAssertEqual(State->stencilOp.front.dppass, GL_DECR, @"should be GL_DECR");
    XCTAssertEqual(State->stencilOp.back.sfail, GL_ZERO, @"should be GL_ZERO");
    XCTAssertEqual(State->stencilOp.back.dpfail, GL_INCR, @"should be GL_INCR");
    XCTAssertEqual(State->stencilOp.back.dppass, GL_DECR, @"should be GL_DECR");
    
    
    glStencilFuncSeparate(GL_FRONT, GL_LESS, 0, 1); CC_GL_CHECK();
    glStencilMaskSeparate(GL_FRONT, 0); CC_GL_CHECK();
    glStencilOpSeparate(GL_FRONT, GL_INCR, GL_INCR, GL_INCR); CC_GL_CHECK();
    glStencilFuncSeparate(GL_BACK, GL_GREATER, 1, 0); CC_GL_CHECK();
    glStencilMaskSeparate(GL_BACK, 1); CC_GL_CHECK();
    glStencilOpSeparate(GL_BACK, GL_DECR, GL_DECR, GL_DECR); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->stencilFunc.front.func, GL_LESS, @"should be GL_LESS");
    XCTAssertEqual(State->stencilFunc.front.ref, 0, @"should be 0");
    XCTAssertEqual(State->stencilFunc.front.mask, 1, @"should be 1");
    XCTAssertEqual(State->stencilFunc.back.func, GL_GREATER, @"should be GL_GREATER");
    XCTAssertEqual(State->stencilFunc.back.ref, 1, @"should be 1");
    XCTAssertEqual(State->stencilFunc.back.mask, 0, @"should be 0");
    XCTAssertEqual(State->stencilMask.front.mask, 0, @"should be 0");
    XCTAssertEqual(State->stencilMask.back.mask, 1, @"should be 1");
    XCTAssertEqual(State->stencilOp.front.sfail, GL_INCR, @"should be GL_INCR");
    XCTAssertEqual(State->stencilOp.front.dpfail, GL_INCR, @"should be GL_INCR");
    XCTAssertEqual(State->stencilOp.front.dppass, GL_INCR, @"should be GL_INCR");
    XCTAssertEqual(State->stencilOp.back.sfail, GL_DECR, @"should be GL_DECR");
    XCTAssertEqual(State->stencilOp.back.dpfail, GL_DECR, @"should be GL_DECR");
    XCTAssertEqual(State->stencilOp.back.dppass, GL_DECR, @"should be GL_DECR");
#endif
}

-(void) testTextureState
{
#if CC_GL_STATE_TEXTURE
#define TEST_TEXTURE_TARGET(target, index) { target, &State->bindTexture[index]._##target, #target }
    CCGLState *State = CCGLStateForContext(ctx);
    
    GLint Max;
#if !CC_GL_STATE_TEXTURE_MAX
    CC_GL_VERSION_ACTIVE(1_1, 1_5, 1_0, 1_1, glGetIntegerv(GL_MAX_TEXTURE_UNITS, &Max); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Max); CC_GL_CHECK());
#else
    Max = CC_GL_STATE_TEXTURE_MAX;
#endif
    
    for (size_t Active = 0; Active < Max; Active++)
    {
        const struct {
            GLenum target;
            const GLenum *state;
            char *name;
        } TextureTargets[] = {
#if CC_GL_STATE_TEXTURE_1D
            CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_1D, Active),)
#endif
#if CC_GL_STATE_TEXTURE_2D
            CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_2D, Active),)
#endif
#if CC_GL_STATE_TEXTURE_3D
            CC_GL_VERSION_ACTIVE(1_1, NA, 3_0, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_3D, Active),)
#endif
#if CC_GL_STATE_TEXTURE_1D_ARRAY
            CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_1D_ARRAY, Active),)
#endif
#if CC_GL_STATE_TEXTURE_2D_ARRAY
            CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_2D_ARRAY, Active),)
#endif
#if CC_GL_STATE_TEXTURE_RECTANGLE
#if GL_ARB_texture_rectangle
            TEST_TEXTURE_TARGET(GL_TEXTURE_RECTANGLE_ARB, Active),
#else
            CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_RECTANGLE, Active),)
#endif
#endif
#if CC_GL_STATE_TEXTURE_CUBE_MAP
            CC_GL_VERSION_ACTIVE(1_3, NA, 2_0, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_CUBE_MAP, Active),)
#endif
#if CC_GL_STATE_TEXTURE_CUBE_MAP_ARRAY
            CC_GL_VERSION_ACTIVE(4_0, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_CUBE_MAP_ARRAY, Active),)
#endif
#if CC_GL_STATE_TEXTURE_BUFFER
            CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_BUFFER, Active),)
#endif
#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE
            CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_2D_MULTISAMPLE, Active),)
#endif
#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE_ARRAY
            CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, TEST_TEXTURE_TARGET(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, Active),)
#endif
        };
        const size_t Count = sizeof(TextureTargets) / sizeof(typeof(*TextureTargets));
        
        glActiveTexture((GLenum)(GL_TEXTURE0 + Active)); CC_GL_CHECK();
        for (size_t Loop = 0; Loop < Count; Loop++)
        {
            glBindTexture(TextureTargets[Loop].target, 0); CC_GL_CHECK();
        }
        
        CCGLStateInitializeWithCurrent(State);
        
        XCTAssertEqual(State->activeTexture.texture, (GLenum)(GL_TEXTURE0 + Active), @"should be GL_TEXTURE%zu", Active);
        for (size_t Loop = 0; Loop < Count; Loop++)
        {
            XCTAssertEqual(*TextureTargets[Loop].state, 0, @"%s (in GL_TEXTURE%zu) should be %u", TextureTargets[Loop].name, Active, 0);
        }
        
        
        GLuint Textures[Count];
        
        glGenTextures(Count, Textures); CC_GL_CHECK();
        
        for (size_t Loop = 0; Loop < Count; Loop++)
        {
            glBindTexture(TextureTargets[Loop].target, Textures[Loop]); CC_GL_CHECK();
        }
        glActiveTexture(GL_TEXTURE0); CC_GL_CHECK();
        
        CCGLStateInitializeWithCurrent(State);
        
        XCTAssertEqual(State->activeTexture.texture, GL_TEXTURE0, @"should be GL_TEXTURE0");
        for (size_t Loop = 0; Loop < Count; Loop++)
        {
            XCTAssertEqual(*TextureTargets[Loop].state, Textures[Loop], @"%s (in GL_TEXTURE%zu) should be %u", TextureTargets[Loop].name, Active, Textures[Loop]);
        }
        
        glDeleteBuffers(Count, Textures); CC_GL_CHECK();
    }
#endif
}

-(void) testVertexArrayObjectState
{
#if CC_GL_STATE_VERTEX_ARRAY_OBJECT
    CCGLState *State = CCGLStateForContext(ctx);
    
    glBindVertexArray(0); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->bindVertexArray.array, 0, @"should be 0");
    
    
    GLuint vao;
    glGenVertexArrays(1, &vao); CC_GL_CHECK();
    glBindVertexArray(vao); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->bindVertexArray.array, vao, @"should be %u", vao);
    
    glDeleteVertexArrays(1, &vao); CC_GL_CHECK();
#endif
}

-(void) testViewportState
{
#if CC_GL_STATE_VIEWPORT
    CCGLState *State = CCGLStateForContext(ctx);
    
    glViewport(0, 0, 0, 0); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->viewport.x, 0, @"should be 0");
    XCTAssertEqual(State->viewport.y, 0, @"should be 0");
    XCTAssertEqual(State->viewport.width, 0, @"should be 0");
    XCTAssertEqual(State->viewport.height, 0, @"should be 0");
    
    
    glViewport(1, 2, 3, 4); CC_GL_CHECK();
    
    CCGLStateInitializeWithCurrent(State);
    
    XCTAssertEqual(State->viewport.x, 1, @"should be 1");
    XCTAssertEqual(State->viewport.y, 2, @"should be 2");
    XCTAssertEqual(State->viewport.width, 3, @"should be 3");
    XCTAssertEqual(State->viewport.height, 4, @"should be 4");
#endif
}

@end

#endif
