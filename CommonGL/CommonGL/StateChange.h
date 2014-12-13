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
if (CC_GL_CURRENT_STATE->bindBuffer._##target != (buffer)) \
{ \
    CC_GL_CURRENT_STATE->bindBuffer._##target = (buffer); \
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



#if CC_GL_STATE_DEPTH
#define CC_GL_CLEAR_DEPTH(d) \
if (CC_GL_CURRENT_STATE->clearDepth.depth != (d)) \
{ \
    CC_GL_CURRENT_STATE->clearDepth.depth = (d); \
    glClearDepth(d); CC_GL_CHECK(); \
}

#define CC_GL_DEPTH_FUNC(f) \
if (CC_GL_CURRENT_STATE->depthFunc.func != (f)) \
{ \
    CC_GL_CURRENT_STATE->depthFunc.func = (f); \
    glDepthFunc(f); CC_GL_CHECK(); \
}

#define CC_GL_DEPTH_MASK(f) \
if (CC_GL_CURRENT_STATE->depthMask.flag != (f)) \
{ \
    CC_GL_CURRENT_STATE->depthMask.flag = (f); \
    glDepthMask(f); CC_GL_CHECK(); \
}

#define CC_GL_DEPTH_RANGE(n, f) \
if ((CC_GL_CURRENT_STATE->depthRange.near != (n)) || \
    (CC_GL_CURRENT_STATE->depthRange.far != (f))) \
{ \
    CC_GL_CURRENT_STATE->depthRange.near = (n); \
    CC_GL_CURRENT_STATE->depthRange.far = (f); \
    glDepthRange((n), (f)); CC_GL_CHECK(); \
}

#else
#define CC_GL_CLEAR_DEPTH(d) glClearDepth(d); CC_GL_CHECK()
#define CC_GL_DEPTH_FUNC(f) glDepthFunc(f); CC_GL_CHECK()
#define CC_GL_DEPTH_MASK(f) glDepthMask(f); CC_GL_CHECK()
#define CC_GL_DEPTH_RANGE(n, f) glDepthRange((n), (f)); CC_GL_CHECK()
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



#if CC_GL_STATE_FRAMEBUFFER
#if GL_DRAW_FRAMEBUFFER && GL_READ_FRAMEBUFFER
#define CC_GL_BIND_FRAMEBUFFER_TARGET_GL_READ_FRAMEBUFFER(framebuffer) \
if (CC_GL_CURRENT_STATE->bindFramebuffer.read != (framebuffer)) \
{ \
    CC_GL_CURRENT_STATE->bindFramebuffer.read = (framebuffer); \
    glBindFramebuffer(GL_READ_FRAMEBUFFER, (framebuffer)); CC_GL_CHECK(); \
}

#define CC_GL_BIND_FRAMEBUFFER_TARGET_GL_DRAW_FRAMEBUFFER(framebuffer) \
if (CC_GL_CURRENT_STATE->bindFramebuffer.write != (framebuffer)) \
{ \
    CC_GL_CURRENT_STATE->bindFramebuffer.write = (framebuffer); \
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, (framebuffer)); CC_GL_CHECK(); \
}

#define CC_GL_BIND_FRAMEBUFFER_TARGET_GL_FRAMEBUFFER(framebuffer) \
if ((CC_GL_CURRENT_STATE->bindFramebuffer.read != (framebuffer)) || (CC_GL_CURRENT_STATE->bindFramebuffer.write != (framebuffer))) \
{ \
    CC_GL_CURRENT_STATE->bindFramebuffer.read = (framebuffer); \
    CC_GL_CURRENT_STATE->bindFramebuffer.write = (framebuffer); \
    glBindFramebuffer(GL_FRAMEBUFFER, (framebuffer)); CC_GL_CHECK(); \
}

#define CC_GL_BIND_FRAMEBUFFER_TARGET(target, framebuffer) \
switch (target) \
{ \
    case GL_READ_FRAMEBUFFER: \
        CC_GL_BIND_FRAMEBUFFER_TARGET_GL_READ_FRAMEBUFFER(framebuffer); \
        break; \
 \
    case GL_DRAW_FRAMEBUFFER: \
        CC_GL_BIND_FRAMEBUFFER_TARGET_GL_DRAW_FRAMEBUFFER(framebuffer); \
        break; \
 \
    default: \
        CC_GL_BIND_FRAMEBUFFER_TARGET_GL_FRAMEBUFFER(framebuffer); \
        break; \
}

#define CC_GL_BIND_FRAMEBUFFER(target, framebuffer) CC_GL_BIND_FRAMEBUFFER_TARGET_##target(framebuffer)

#else
#define CC_GL_BIND_FRAMEBUFFER(target, framebuffer) \
if ((CC_GL_CURRENT_STATE->bindFramebuffer.read != (framebuffer)) || (CC_GL_CURRENT_STATE->bindFramebuffer.write != (framebuffer))) \
{ \
    CC_GL_CURRENT_STATE->bindFramebuffer.read = (framebuffer); \
    CC_GL_CURRENT_STATE->bindFramebuffer.write = (framebuffer); \
    glBindFramebuffer(GL_FRAMEBUFFER, (framebuffer)); CC_GL_CHECK(); \
}

#endif

#else
#define CC_GL_BIND_FRAMEBUFFER(target, framebuffer) glBindFramebuffer((target), (framebuffer)); CC_GL_CHECK()
#define CC_GL_BIND_FRAMEBUFFER_TARGET(target, framebuffer) glBindFramebuffer((target), (framebuffer)); CC_GL_CHECK()
#endif



#if CC_GL_STATE_SCISSOR
#define CC_GL_SCISSOR(posx, posy, sizew, sizeh) \
if ((CC_GL_CURRENT_STATE->scissor.x != (posx)) || \
    (CC_GL_CURRENT_STATE->scissor.y != (posy)) || \
    (CC_GL_CURRENT_STATE->scissor.width != (sizew)) || \
    (CC_GL_CURRENT_STATE->scissor.height != (sizeh))) \
{ \
    CC_GL_CURRENT_STATE->scissor.x = (posx); \
    CC_GL_CURRENT_STATE->scissor.y = (posy); \
    CC_GL_CURRENT_STATE->scissor.width = (sizew); \
    CC_GL_CURRENT_STATE->scissor.height = (sizeh); \
    glScissor((posx), (posy), (sizew), (sizeh)); CC_GL_CHECK(); \
}

#else
#define CC_GL_SCISSOR(x, y, width, height) glScissor((x), (y), (width), (height)); CC_GL_CHECK()
#endif



#if CC_GL_STATE_SHADER
#define CC_GL_USE_PROGRAM(prog) \
if (CC_GL_CURRENT_STATE->useProgram.program != (prog)) \
{ \
    CC_GL_CURRENT_STATE->useProgram.program = (prog); \
    glUseProgram(prog); CC_GL_CHECK(); \
}

#else
#define CC_GL_USE_PROGRAM(prog) glUseProgram(prog); CC_GL_CHECK()
#endif



#if CC_GL_STATE_STENCIL
#define CC_GL_CLEAR_STENCIL(v) \
if (CC_GL_CURRENT_STATE->clearStencil.s != (v)) \
{ \
    CC_GL_CURRENT_STATE->clearStencil.s = (v); \
    glClearStencil(v); CC_GL_CHECK(); \
}

#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_0, CC_OPENGL_ES_VERSION_1_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_1_5, CC_OPENGL_ES_VERSION_1_1)
#define CC_GL_STENCIL_FUNC(f, r, m) \
if ((CC_GL_CURRENT_STATE->stencilFunc.func != (f)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.ref != (r)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.mask != (m))) \
{ \
    CC_GL_CURRENT_STATE->stencilFunc.func = (f); \
    CC_GL_CURRENT_STATE->stencilFunc.ref = (r); \
    CC_GL_CURRENT_STATE->stencilFunc.mask = (m); \
    glStencilFunc((f), (r), (m)); CC_GL_CHECK(); \
}

#else
#define CC_GL_STENCIL_FUNC(f, r, m) \
if ((CC_GL_CURRENT_STATE->stencilFunc.front.func != (f)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.front.ref != (r)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.front.mask != (m)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.back.func != (f)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.back.ref != (r)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.back.mask != (m))) \
{ \
    CC_GL_CURRENT_STATE->stencilFunc.front.func = (f); \
    CC_GL_CURRENT_STATE->stencilFunc.front.ref = (r); \
    CC_GL_CURRENT_STATE->stencilFunc.front.mask = (m); \
    CC_GL_CURRENT_STATE->stencilFunc.back.func = (f); \
    CC_GL_CURRENT_STATE->stencilFunc.back.ref = (r); \
    CC_GL_CURRENT_STATE->stencilFunc.back.mask = (m); \
    glStencilFunc((f), (r), (m)); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_FUNC_SEPARATE_FACE_GL_FRONT_AND_BACK(f, r, m) CC_GL_STENCIL_FUNC(f, r, m)

#define CC_GL_STENCIL_FUNC_SEPARATE_FACE_GL_FRONT(f, r, m) \
if ((CC_GL_CURRENT_STATE->stencilFunc.front.func != (f)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.front.ref != (r)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.front.mask != (m))) \
{ \
    CC_GL_CURRENT_STATE->stencilFunc.front.func = (f); \
    CC_GL_CURRENT_STATE->stencilFunc.front.ref = (r); \
    CC_GL_CURRENT_STATE->stencilFunc.front.mask = (m); \
    glStencilFuncSeparate(GL_FRONT, (f), (r), (m)); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_FUNC_SEPARATE_FACE_GL_BACK(f, r, m) \
if ((CC_GL_CURRENT_STATE->stencilFunc.back.func != (f)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.back.ref != (r)) || \
    (CC_GL_CURRENT_STATE->stencilFunc.back.mask != (m))) \
{ \
    CC_GL_CURRENT_STATE->stencilFunc.back.func = (f); \
    CC_GL_CURRENT_STATE->stencilFunc.back.ref = (r); \
    CC_GL_CURRENT_STATE->stencilFunc.back.mask = (m); \
    glStencilFuncSeparate(GL_BACK, (f), (r), (m)); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_FUNC_SEPARATE(face, f, r, m) CC_GL_STENCIL_FUNC_SEPARATE_FACE_##face(f, r, m)

#define CC_GL_STENCIL_FUNC_SEPARATE_FACE(face, f, r, m) \
switch (face) \
{ \
    case GL_FRONT: \
        CC_GL_STENCIL_FUNC_SEPARATE_FACE_GL_FRONT(f, r, m); \
        break; \
 \
    case GL_BACK: \
        CC_GL_STENCIL_FUNC_SEPARATE_FACE_GL_BACK(f, r, m); \
        break; \
 \
    default: \
        CC_GL_STENCIL_FUNC_SEPARATE_FACE_GL_FRONT_AND_BACK(f, r, m); \
        break; \
}

#endif

#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_0, CC_OPENGL_ES_VERSION_1_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_1_5, CC_OPENGL_ES_VERSION_1_1)
#define CC_GL_STENCIL_MASK(m) \
if (CC_GL_CURRENT_STATE->stencilMask.mask != (m)) \
{ \
    CC_GL_CURRENT_STATE->stencilMask.mask = (m); \
    glStencilMask(m); CC_GL_CHECK(); \
}

#else
#define CC_GL_STENCIL_MASK(m) \
if ((CC_GL_CURRENT_STATE->stencilMask.front.mask != (m)) || \
    (CC_GL_CURRENT_STATE->stencilMask.back.mask != (m))) \
{ \
    CC_GL_CURRENT_STATE->stencilMask.front.mask = (m); \
    CC_GL_CURRENT_STATE->stencilMask.back.mask = (m); \
    glStencilMask(m); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_MASK_SEPARATE_FACE_GL_FRONT_AND_BACK(m) CC_GL_STENCIL_MASK(m)

#define CC_GL_STENCIL_MASK_SEPARATE_FACE_GL_FRONT(m) \
if (CC_GL_CURRENT_STATE->stencilMask.front.mask != (m)) \
{ \
    CC_GL_CURRENT_STATE->stencilMask.front.mask = (m); \
    glStencilMaskSeparate(GL_FRONT, m); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_MASK_SEPARATE_FACE_GL_BACK(m) \
if (CC_GL_CURRENT_STATE->stencilMask.back.mask != (m)) \
{ \
    CC_GL_CURRENT_STATE->stencilMask.back.mask = (m); \
    glStencilMaskSeparate(GL_BACK, m); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_MASK_SEPARATE(face, m) CC_GL_STENCIL_MASK_SEPARATE_FACE_##face(m)

#define CC_GL_STENCIL_MASK_SEPARATE_FACE(face, m) \
switch (face) \
{ \
    case GL_FRONT: \
        CC_GL_STENCIL_MASK_SEPARATE_FACE_GL_FRONT(m); \
        break; \
    \
    case GL_BACK: \
        CC_GL_STENCIL_MASK_SEPARATE_FACE_GL_BACK(m); \
        break; \
    \
    default: \
        CC_GL_STENCIL_MASK_SEPARATE_FACE_GL_FRONT_AND_BACK(m); \
        break; \
}

#endif

#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_1_0, CC_OPENGL_ES_VERSION_1_0) && CC_GL_VERSION_MAX_SUPPORTED(CC_OPENGL_VERSION_1_5, CC_OPENGL_ES_VERSION_1_1)
#define CC_GL_STENCIL_OP(fail, zfail, zpass) \
if ((CC_GL_CURRENT_STATE->stencilOp.sfail != (fail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.dpfail != (zfail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.dppass != (zpass))) \
{ \
    CC_GL_CURRENT_STATE->stencilOp.sfail = (fail); \
    CC_GL_CURRENT_STATE->stencilOp.dpfail = (zfail); \
    CC_GL_CURRENT_STATE->stencilOp.dppass = (zpass); \
    glStencilOp((fail), (zfail), (zpass)); CC_GL_CHECK(); \
}

#else
#define CC_GL_STENCIL_OP(fail, zfail, zpass) \
if ((CC_GL_CURRENT_STATE->stencilOp.front.sfail != (fail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.front.dpfail != (zfail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.front.dppass != (zpass)) || \
    (CC_GL_CURRENT_STATE->stencilOp.back.sfail != (fail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.back.dpfail != (zfail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.back.dppass != (zpass))) \
{ \
    CC_GL_CURRENT_STATE->stencilOp.front.sfail = (fail); \
    CC_GL_CURRENT_STATE->stencilOp.front.dpfail = (zfail); \
    CC_GL_CURRENT_STATE->stencilOp.front.dppass = (zpass); \
    CC_GL_CURRENT_STATE->stencilOp.back.sfail = (fail); \
    CC_GL_CURRENT_STATE->stencilOp.back.dpfail = (zfail); \
    CC_GL_CURRENT_STATE->stencilOp.back.dppass = (zpass); \
    glStencilOp((fail), (zfail), (zpass)); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_OP_SEPARATE_FACE_GL_FRONT_AND_BACK(fail, zfail, zpass) CC_GL_STENCIL_OP(fail, zfail, zpass)

#define CC_GL_STENCIL_OP_SEPARATE_FACE_GL_FRONT(fail, zfail, zpass) \
if ((CC_GL_CURRENT_STATE->stencilOp.front.sfail != (fail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.front.dpfail != (zfail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.front.dppass != (zpass))) \
{ \
    CC_GL_CURRENT_STATE->stencilOp.front.sfail = (fail); \
    CC_GL_CURRENT_STATE->stencilOp.front.dpfail = (zfail); \
    CC_GL_CURRENT_STATE->stencilOp.front.dppass = (zpass); \
    glStencilOpSeparate(GL_FRONT, (fail), (zfail), (zpass)); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_OP_SEPARATE_FACE_GL_BACK(fail, zfail, zpass) \
if ((CC_GL_CURRENT_STATE->stencilOp.back.sfail != (fail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.back.dpfail != (zfail)) || \
    (CC_GL_CURRENT_STATE->stencilOp.back.dppass != (zpass))) \
{ \
    CC_GL_CURRENT_STATE->stencilOp.back.sfail = (fail); \
    CC_GL_CURRENT_STATE->stencilOp.back.dpfail = (zfail); \
    CC_GL_CURRENT_STATE->stencilOp.back.dppass = (zpass); \
    glStencilOpSeparate(GL_BACK, (fail), (zfail), (zpass)); CC_GL_CHECK(); \
}

#define CC_GL_STENCIL_OP_SEPARATE(face, fail, zfail, zpass) CC_GL_STENCIL_OP_SEPARATE_FACE_##face(fail, zfail, zpass)

#define CC_GL_STENCIL_OP_SEPARATE_FACE(face, fail, zfail, zpass) \
switch (face) \
{ \
    case GL_FRONT: \
        CC_GL_STENCIL_OP_SEPARATE_FACE_GL_FRONT(fail, zfail, zpass); \
        break; \
\
    case GL_BACK: \
        CC_GL_STENCIL_OP_SEPARATE_FACE_GL_BACK(fail, zfail, zpass); \
        break; \
\
    default: \
        CC_GL_STENCIL_OP_SEPARATE_FACE_GL_FRONT_AND_BACK(fail, zfail, zpass); \
        break; \
}

#endif

#else
#define CC_GL_CLEAR_STENCIL(v) glClearStencil(v); CC_GL_CHECK()
#define CC_GL_STENCIL_FUNC(f, r, m) glStencilFunc((f), (r), (m)); CC_GL_CHECK()
#define CC_GL_STENCIL_MASK(m) glStencilMask(m); CC_GL_CHECK()
#define CC_GL_STENCIL_OP(fail, zfail, zpass) glStencilOp((fail), (zfail), (zpass)); CC_GL_CHECK()

#if CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_2_0, CC_OPENGL_ES_VERSION_2_0)
#define CC_GL_STENCIL_FUNC_SEPARATE(face, f, r, m) glStencilFuncSeparate((face), (f), (r), (m)); CC_GL_CHECK()
#define CC_GL_STENCIL_MASK_SEPARATE(face, m) glStencilMaskSeparate((face), (m)); CC_GL_CHECK()
#define CC_GL_STENCIL_OP_SEPARATE(face, fail, zfail, zpass) glStencilOpSeparate((face), (fail), (zfail), (zpass)); CC_GL_CHECK()
#endif

#endif



#if CC_GL_STATE_TEXTURE
#define CC_GL_ACTIVE_TEXTURE(t) \
if (CC_GL_CURRENT_STATE->activeTexture.texture != (t)) \
{ \
    CC_GL_CURRENT_STATE->activeTexture.texture = (t); \
    glActiveTexture(t); CC_GL_CHECK(); \
}

#define CC_GL_BIND_TEXTURE(target, t) \
if (CC_GL_CURRENT_STATE->bindTexture[CC_GL_CURRENT_STATE->activeTexture.texture - GL_TEXTURE0]._##target != (t)) \
{ \
    CC_GL_CURRENT_STATE->bindTexture[CC_GL_CURRENT_STATE->activeTexture.texture - GL_TEXTURE0]._##target = (t); \
    glBindTexture((target), (t)); CC_GL_CHECK(); \
}

#if CC_GL_STATE_TEXTURE_1D
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_1D(t) CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, case GL_TEXTURE_1D: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_1D, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_1D(t)
#endif

#if CC_GL_STATE_TEXTURE_2D
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D(t) CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, case GL_TEXTURE_2D: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_2D, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D(t)
#endif

#if CC_GL_STATE_TEXTURE_3D
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_3D(t) CC_GL_VERSION_ACTIVE(1_1, NA, 3_0, NA, case GL_TEXTURE_3D: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_3D, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_3D(t)
#endif

#if CC_GL_STATE_TEXTURE_1D_ARRAY
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_1D_ARRAY(t) CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, case GL_TEXTURE_1D_ARRAY: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_1D_ARRAY, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_1D_ARRAY(t)
#endif

#if CC_GL_STATE_TEXTURE_2D_ARRAY
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_ARRAY(t) CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, case GL_TEXTURE_2D_ARRAY: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_2D_ARRAY, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_ARRAY(t)
#endif

#if CC_GL_STATE_TEXTURE_RECTANGLE
#if GL_ARB_texture_rectangle
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_RECTANGLE(t) CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, case GL_TEXTURE_RECTANGLE: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_RECTANGLE, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_RECTANGLE(t) CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, case GL_TEXTURE_RECTANGLE: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_RECTANGLE, t); \
    break; \
)
#endif
#endif
#ifndef CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_RECTANGLE
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_RECTANGLE(t)
#endif

#if CC_GL_STATE_TEXTURE_CUBE_MAP
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_CUBE_MAP(t) CC_GL_VERSION_ACTIVE(1_3, NA, 2_0, NA, case GL_TEXTURE_CUBE_MAP: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_CUBE_MAP, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_CUBE_MAP(t)
#endif

#if CC_GL_STATE_TEXTURE_CUBE_MAP_ARRAY
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_CUBE_MAP_ARRAY(t) CC_GL_VERSION_ACTIVE(4_0, NA, NA, NA, case GL_TEXTURE_CUBE_MAP_ARRAY: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_CUBE_MAP_ARRAY, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_CUBE_MAP_ARRAY(t)
#endif

#if CC_GL_STATE_TEXTURE_BUFFER
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_BUFFER(t) CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, case GL_TEXTURE_BUFFER: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_BUFFER, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_BUFFER(t)
#endif

#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_MULTISAMPLE(t) CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, case GL_TEXTURE_2D_MULTISAMPLE: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_2D_MULTISAMPLE, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_MULTISAMPLE(t)
#endif

#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE_ARRAY
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_MULTISAMPLE_ARRAY(t) CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, case GL_TEXTURE_2D_MULTISAMPLE_ARRAY: \
    CC_GL_BIND_TEXTURE(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, t); \
    break; \
)
#else
#define CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_MULTISAMPLE_ARRAY(t)
#endif

#define CC_GL_BIND_TEXTURE_TARGET(target, t) \
switch(target) \
{ \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_1D(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_3D(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_1D_ARRAY(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_ARRAY(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_CUBE_MAP(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_CUBE_MAP_ARRAY(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_BUFFER(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_MULTISAMPLE(t) \
    CC_GL_BIND_TEXTURE_TARGET_GL_TEXTURE_2D_MULTISAMPLE_ARRAY(t) \
}


#else
#define CC_GL_ACTIVE_TEXTURE(texture) glActiveTexture(texture); CC_GL_CHECK()
#define CC_GL_BIND_TEXTURE(target, texture) glBindTexture((target), (texture)); CC_GL_CHECK()
#endif



#if GL_APPLE_vertex_array_object || GL_OES_vertex_array_object || CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_3_0, CC_OPENGL_ES_VERSION_3_0)
#if CC_GL_STATE_VERTEX_ARRAY_OBJECT
#define CC_GL_BIND_VERTEX_ARRAY(vao) \
if (CC_GL_CURRENT_STATE->bindVertexArray.array != (vao)) \
{ \
    CC_GL_CURRENT_STATE->bindVertexArray.array = (vao); \
    glBindVertexArray(vao); CC_GL_CHECK(); \
}

#else
#define CC_GL_BIND_VERTEX_ARRAY(vao) glBindVertexArray(vao); CC_GL_CHECK()
#endif
#endif



#if CC_GL_STATE_VIEWPORT
#define CC_GL_VIEWPORT(posx, posy, sizew, sizeh) \
if ((CC_GL_CURRENT_STATE->viewport.x != (posx)) || \
    (CC_GL_CURRENT_STATE->viewport.y != (posy)) || \
    (CC_GL_CURRENT_STATE->viewport.width != (sizew)) || \
    (CC_GL_CURRENT_STATE->viewport.height != (sizeh))) \
{ \
    CC_GL_CURRENT_STATE->viewport.x = (posx); \
    CC_GL_CURRENT_STATE->viewport.y = (posy); \
    CC_GL_CURRENT_STATE->viewport.width = (sizew); \
    CC_GL_CURRENT_STATE->viewport.height = (sizeh); \
    glViewport((posx), (posy), (sizew), (sizeh)); CC_GL_CHECK(); \
}

#else
#define CC_GL_VIEWPORT(x, y, width, height) glViewport((x), (y), (width), (height)); CC_GL_CHECK()
#endif


#endif
