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

#ifndef CommonGL_StateChange_h
#define CommonGL_StateChange_h

#import <CommonGL/Defined.h>
#import <CommonGL/Version.h>
#import <CommonGL/SelectedState.h>
#import <CommonGL/State.h>
#import <CommonGL/Calling.h>



#if CC_GL_STATE_BLEND
#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_0, CC_OPENGL_ES_VERSION_1_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_1_3, CC_OPENGL_ES_VERSION_1_1)
#define CC_GL_BLEND_FUNC(sfactor, dfactor) \
if ((CC_GL_CURRENT_STATE->blendFunc.src != (sfactor)) || \
    (CC_GL_CURRENT_STATE->blendFunc.dst != (dfactor))) \
{ \
    CC_GL_CURRENT_STATE->blendFunc.src = (sfactor); \
    CC_GL_CURRENT_STATE->blendFunc.dst = (dfactor); \
    glBlendFunc((sfactor), (dfactor)); CC_GL_CHECK(); \
}

#elif CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_4, CC_OPENGL_ES_VERSION_2_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_NA, CC_OPENGL_ES_VERSION_NA)
#define CC_GL_BLEND_FUNC(sfactor, dfactor) \
if ((CC_GL_CURRENT_STATE->blendFunc.rgb.src != (sfactor)) || \
    (CC_GL_CURRENT_STATE->blendFunc.rgb.dst != (dfactor)) || \
    (CC_GL_CURRENT_STATE->blendFunc.alpha.src != (sfactor)) || \
    (CC_GL_CURRENT_STATE->blendFunc.alpha.dst != (dfactor))) \
{ \
    CC_GL_CURRENT_STATE->blendFunc.rgb.src = (sfactor); \
    CC_GL_CURRENT_STATE->blendFunc.rgb.dst = (dfactor); \
    CC_GL_CURRENT_STATE->blendFunc.alpha.src = (sfactor); \
    CC_GL_CURRENT_STATE->blendFunc.alpha.dst = (dfactor); \
    glBlendFunc((sfactor), (dfactor)); CC_GL_CHECK(); \
}

#define CC_GL_BLEND_FUNC_SEPARATE(srcRGB, dstRGB, srcAlpha, dstAlpha) \
if ((CC_GL_CURRENT_STATE->blendFunc.rgb.src != (srcRGB)) || \
    (CC_GL_CURRENT_STATE->blendFunc.rgb.dst != (dstRGB)) || \
    (CC_GL_CURRENT_STATE->blendFunc.alpha.src != (srcAlpha)) || \
    (CC_GL_CURRENT_STATE->blendFunc.alpha.dst != (dstAlpha))) \
{ \
    CC_GL_CURRENT_STATE->blendFunc.rgb.src = (srcRGB); \
    CC_GL_CURRENT_STATE->blendFunc.rgb.dst = (dstRGB); \
    CC_GL_CURRENT_STATE->blendFunc.alpha.src = (srcAlpha); \
    CC_GL_CURRENT_STATE->blendFunc.alpha.dst = (dstAlpha); \
    glBlendFuncSeparate((srcRGB), (dstRGB), (srcAlpha), (dstAlpha)); CC_GL_CHECK(); \
}
#endif


#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_0, CC_OPENGL_ES_VERSION_NA) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_1_5, CC_OPENGL_ES_VERSION_NA)
#define CC_GL_BLEND_EQUATION(eq) \
if (CC_GL_CURRENT_STATE->blendEquation.mode != (eq)) \
{ \
    CC_GL_CURRENT_STATE->blendEquation.mode = (eq); \
    glBlendEquation(eq); CC_GL_CHECK(); \
}

#elif CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_2_0, CC_OPENGL_ES_VERSION_2_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_NA, CC_OPENGL_ES_VERSION_NA)
#define CC_GL_BLEND_EQUATION(eq) \
if ((CC_GL_CURRENT_STATE->blendEquation.rgb.mode != (eq)) || \
    (CC_GL_CURRENT_STATE->blendEquation.alpha.mode != (eq))) \
{ \
    CC_GL_CURRENT_STATE->blendEquation.rgb.mode = (eq); \
    CC_GL_CURRENT_STATE->blendEquation.alpha.mode = (eq); \
    glBlendEquation(eq); CC_GL_CHECK(); \
}

#define CC_GL_BLEND_EQUATION_SEPARATE(modeRGB, modeAlpha) \
if ((CC_GL_CURRENT_STATE->blendEquation.rgb.mode != (modeRGB)) || \
    (CC_GL_CURRENT_STATE->blendEquation.alpha.mode != (modeAlpha))) \
{ \
    CC_GL_CURRENT_STATE->blendEquation.rgb.mode = (modeRGB); \
    CC_GL_CURRENT_STATE->blendEquation.alpha.mode = (modeAlpha); \
    glBlendEquationSeparate((modeRGB), (modeAlpha)); CC_GL_CHECK(); \
}

#endif

#else
#define CC_GL_BLEND_FUNC(src, dst) glBlendFunc((src), (dst)); CC_GL_CHECK()
#define CC_GL_BLEND_FUNC_SEPARATE(srcRGB, dstRGB, srcAlpha, dstAlpha) glBlendFuncSeparate((srcRGB), (dstRGB), (srcAlpha), (dstAlpha)); CC_GL_CHECK()
#define CC_GL_BLEND_EQUATION(mode) glBlendEquation(mode); CC_GL_CHECK()
#define CC_GL_BLEND_EQUATION_SEPARATE(modeRGB, modeAlpha) glBlendEquationSeparate((modeRGB), (modeAlpha)); CC_GL_CHECK()
#endif



#if CC_GL_STATE_BUFFER
#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_5, CC_OPENGL_ES_VERSION_1_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_NA, CC_OPENGL_ES_VERSION_NA)

#define CC_GL_BIND_BUFFER(target, buffer) \
if (CC_GL_CURRENT_STATE->bindBuffer._##target != buffer) \
{ \
    CC_GL_CURRENT_STATE->bindBuffer._##target = buffer; \
    glBindBuffer((target), (buffer)); CC_GL_CHECK(); \
}

#endif

#else
#define CC_GL_BIND_BUFFER(target, buffer) glBindBuffer((target), (buffer)); CC_GL_CHECK()
#endif



#if CC_GL_STATE_COLOUR
#define CC_GL_CLEAR_COLOR(r, g, b, a) \
if ((CC_GL_CURRENT_STATE->clearColour.red != (r)) || \
    (CC_GL_CURRENT_STATE->clearColour.green != (g)) || \
    (CC_GL_CURRENT_STATE->clearColour.blue != (b)) || \
    (CC_GL_CURRENT_STATE->clearColour.alpha != (a))) \
{ \
    CC_GL_CURRENT_STATE->clearColour.red = (r); \
    CC_GL_CURRENT_STATE->clearColour.green = (g); \
    CC_GL_CURRENT_STATE->clearColour.blue = (b); \
    CC_GL_CURRENT_STATE->clearColour.alpha = (a); \
    glClearColor((r), (g), (b), (a)); CC_GL_CHECK(); \
}

#define CC_GL_COLOR_MASK(r, g, b, a) \
if ((CC_GL_CURRENT_STATE->colourMask.red != (r)) || \
    (CC_GL_CURRENT_STATE->colourMask.green != (g)) || \
    (CC_GL_CURRENT_STATE->colourMask.blue != (b)) || \
    (CC_GL_CURRENT_STATE->colourMask.alpha != (a))) \
{ \
    CC_GL_CURRENT_STATE->colourMask.red = (r); \
    CC_GL_CURRENT_STATE->colourMask.green = (g); \
    CC_GL_CURRENT_STATE->colourMask.blue = (b); \
    CC_GL_CURRENT_STATE->colourMask.alpha = (a); \
    glColorMask((r), (g), (b), (a)); CC_GL_CHECK(); \
}

#else
#define CC_GL_CLEAR_COLOR(r, g, b, a) glClearColor((r), (g), (b), (a)); CC_GL_CHECK()
#define CC_GL_COLOR_MASK(r, g, b, a) glColorMask((r), (g), (b), (a)); CC_GL_CHECK()
#endif



#if CC_GL_STATE_CULL_FACE
#define CC_GL_CULL_FACE(m) \
if (CC_GL_CURRENT_STATE->cullFace.mode != (m)) \
{ \
    CC_GL_CURRENT_STATE->cullFace.mode = (m); \
    glCullFace(m); CC_GL_CHECK(); \
}

#define CC_GL_FRONT_FACE(m) \
if (CC_GL_CURRENT_STATE->frontFace.mode != (m)) \
{ \
    CC_GL_CURRENT_STATE->frontFace.mode = (m); \
    glFrontFace(m); CC_GL_CHECK(); \
}

#else
#define CC_GL_CULL_FACE(mode) glCullFace(mode); CC_GL_CHECK()
#define CC_GL_FRONT_FACE(mode) glFrontFace(mode); CC_GL_CHECK()
#endif



#if CC_GL_STATE_ENABLED
#define CC_GL_ENABLE(type) \
if (!CC_GL_CURRENT_STATE->enabled._##type) \
{ \
    CC_GL_CURRENT_STATE->enabled._##type = TRUE; \
    glEnable(type); CC_GL_CHECK(); \
}

#define CC_GL_DISABLE(type) \
if (CC_GL_CURRENT_STATE->enabled._##type) \
{ \
    CC_GL_CURRENT_STATE->enabled._##type = FALSE; \
    glDisable(type); CC_GL_CHECK(); \
}
#else
#define CC_GL_ENABLE(type) glEnable(type); CC_GL_CHECK()
#define CC_GL_DISABLE(type) glDisable(type); CC_GL_CHECK()
#endif





#endif
