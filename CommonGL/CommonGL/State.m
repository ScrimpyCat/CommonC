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
#import "State.h"
#import "Debug.h"
#import "Calling.h"
#import <CommonObjc/GenericContainer.h>
#import <CommonC/MemoryAllocation.h>


CCGLState *CCGLStateForContext(CCGLContext Context)
{
    CCGenericContainer *StateContainer = CCGLContextGetAssociatedObject(Context, &CCGLStateForContext);
    if (!StateContainer)
    {
        CCGLContextLock(Context);
        if (!(StateContainer = CCGLContextGetAssociatedObject(Context, &CCGLStateForContext)))
        {
            CCGLState *State = CCGLStateCreate();
            if (State)
            {
                CCGLStateInitializeWithCurrent(State);
                StateContainer = [CCGenericContainer containerWithData: State OfSize: sizeof(CCGLState) ReleaserBlock: ^(void *Data, size_t Size, bool IsCopied){
                    CCGLStateRelease(Data);
                }];
                CCGLContextSetAssociatedObject(Context, &CCGLStateForContext, StateContainer);
            }
            CCGLContextUnlock(Context);
            
            return State;
        }
        CCGLContextUnlock(Context);
    }
    
    return StateContainer.data;
}

CCGLState *CCGLStateCreate(void)
{
    CCGLState *State;
    CC_SAFE_Malloc(State, sizeof(CCGLState),
                   return NULL;
                   );
    
#if CC_GL_STATE_ENABLED
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA,
        GLint MaxClipDistances;
        glGetIntegerv(GL_MAX_CLIP_DISTANCES, &MaxClipDistances); CC_GL_CHECK();
        CC_SAFE_Malloc(State->enabled.clipDistance, MaxClipDistances * sizeof(typeof(State->enabled.clipDistance)));
    );
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1,
        GLint MaxClipPlanes;
        glGetIntegerv(GL_MAX_CLIP_PLANES, &MaxClipPlanes); CC_GL_CHECK();
        CC_SAFE_Malloc(State->enabled.clipPlane, MaxClipPlanes * sizeof(typeof(State->enabled.clipPlane)));
    );
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1,
        GLint MaxLights;
        glGetIntegerv(GL_MAX_LIGHTS, &MaxLights); CC_GL_CHECK();
        CC_SAFE_Malloc(State->enabled.light, MaxLights * sizeof(typeof(State->enabled.light)));
    );
#endif
    
#if CC_GL_STATE_TEXTURE && !CC_GL_STATE_TEXTURE_MAX
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA,
        GLint MaxTextures;
        CC_GL_VERSION_ACTIVE(1_1, 1_5, 1_0, 1_1, glGetIntegerv(GL_MAX_TEXTURE_UNITS, &MaxTextures); CC_GL_CHECK());
        CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextures); CC_GL_CHECK());
        
        CC_SAFE_Malloc(State->bindTexture, MaxTextures * sizeof(typeof(*State->bindTexture)));
    );
#endif
    
    return State;
}

void CCGLStateRelease(CCGLState *State)
{
#if CC_GL_STATE_ENABLED
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, CC_SAFE_Free(State->enabled.clipDistance));
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, CC_SAFE_Free(State->enabled.clipPlane));
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, CC_SAFE_Free(State->enabled.light));
#endif
    
#if CC_GL_STATE_TEXTURE && !CC_GL_STATE_TEXTURE_MAX
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, CC_SAFE_Free(State->bindTexture));
#endif
    
    CC_SAFE_Free(State);
}

void CCGLStateInitializeWithDefault(CCGLState *State)
{
    CC_GL_SETUP;
    
#if CC_GL_STATE_BLEND
    CC_GL_VERSION_ACTIVE(1_0, 1_3, 1_0, 1_1, State->blendFunc = (typeof(State->blendFunc)){ .src = GL_ONE, .dst = GL_ZERO });
    CC_GL_VERSION_ACTIVE(1_4, NA, 2_0, NA, State->blendFunc = (typeof(State->blendFunc)){ .rgb = { .src = GL_ONE, .dst = GL_ZERO }, .alpha = { .src = GL_ONE, .dst = GL_ZERO } });
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, NA, NA, State->blendEquation = (typeof(State->blendEquation)){ .mode = GL_FUNC_ADD });
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, State->blendEquation = (typeof(State->blendEquation)){ .rgb = { .mode = GL_FUNC_ADD }, .alpha = { .mode = GL_FUNC_ADD } });
#endif
    
#if CC_GL_STATE_BUFFER
    CC_GL_VERSION_ACTIVE(1_5, NA, 1_0, NA,
        State->bindBuffer = (typeof(State->bindBuffer)){
            ._GL_ARRAY_BUFFER = 0,
            CC_GL_VERSION_ACTIVE(4_2, NA, 3_1, NA, ._GL_ATOMIC_COUNTER_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, ._GL_COPY_READ_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, ._GL_COPY_WRITE_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, ._GL_DISPATCH_INDIRECT_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(4_0, NA, 3_1, NA, ._GL_DRAW_INDIRECT_BUFFER = 0,)
            ._GL_ELEMENT_ARRAY_BUFFER = 0,
            CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, ._GL_PIXEL_PACK_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, ._GL_PIXEL_UNPACK_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(4_4, NA, NA, NA, ._GL_QUERY_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, ._GL_SHADER_STORAGE_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(3_1, NA, NA, NA, ._GL_TEXTURE_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, ._GL_TRANSFORM_FEEDBACK_BUFFER = 0,)
            CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, ._GL_UNIFORM_BUFFER = 0)
        }
    );
#endif
    
#if CC_GL_STATE_COLOUR
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->clearColour = (typeof(State->clearColour)){ .red = 0.0f, .green = 0.0f, .blue = 0.0f, .alpha = 0.0f });
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->colourMask = (typeof(State->colourMask)){ .red = GL_TRUE, .green = GL_TRUE, .blue = GL_TRUE, .alpha = GL_TRUE });
#endif
    
#if CC_GL_STATE_CULL_FACE
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->cullFace.mode = GL_BACK);
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->frontFace.mode = GL_CCW);
#endif
    
#if CC_GL_STATE_DEPTH
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->clearDepth.depth = 1.0f);
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->depthFunc.func = GL_LESS);
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->depthMask.flag = GL_TRUE);
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->depthRange = (typeof(State->depthRange)){ .near = 0.0f, .far = 1.0f });
#endif
    
#if CC_GL_STATE_ENABLED
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA,
        if (State->enabled.clipDistance)
        {
            GLint MaxClipDistances;
            glGetIntegerv(GL_MAX_CLIP_DISTANCES, &MaxClipDistances); CC_GL_CHECK();
            memset(State->enabled.clipDistance, 0, MaxClipDistances * sizeof(typeof(State->enabled.clipDistance)));
        }
        void * const ClipDistance = State->enabled.clipDistance;
    );
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1,
        if (State->enabled.clipPlane)
        {
            GLint MaxClipPlanes;
            glGetIntegerv(GL_MAX_CLIP_PLANES, &MaxClipPlanes); CC_GL_CHECK();
            memset(State->enabled.clipPlane, 0, MaxClipPlanes * sizeof(typeof(State->enabled.clipPlane)));
        }
        void * const ClipPlane = State->enabled.clipPlane;
    );
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1,
        if (State->enabled.light)
        {
            GLint MaxLights;
            glGetIntegerv(GL_MAX_LIGHTS, &MaxLights); CC_GL_CHECK();
            memset(State->enabled.light, 0, MaxLights * sizeof(typeof(State->enabled.light)));
        }
        void * const Light = State->enabled.light;
    );
    
    memset(&State->enabled, 0, sizeof(typeof(State->enabled)));
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_DITHER = TRUE);
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, 1_1, State->enabled._GL_MULTISAMPLE = TRUE);
    
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, State->enabled.clipDistance = ClipDistance);
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled.clipPlane = ClipPlane);
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled.light = Light);
#endif
    
#if CC_GL_STATE_FRAMEBUFFER
#if GL_ARB_framebuffer_object || GL_OES_framebuffer_object
    State->bindFramebuffer = (typeof(State->bindFramebuffer)){ .read = 0, .write = 0 };
#else
    CC_GL_VERSION_ACTIVE(3_0, NA, 2_0, NA, State->bindFramebuffer = (typeof(State->bindFramebuffer)){ .read = 0, .write = 0 });
#endif
#endif
    
#if CC_GL_STATE_SCISSOR
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLint ScissorBox[4];
        glGetIntegerv(GL_SCISSOR_BOX, ScissorBox); CC_GL_CHECK();
        State->scissor = (typeof(State->scissor)){ .x = 0, .y = 0, .width = ScissorBox[2], .height = ScissorBox[3] };
    );
#endif
    
#if CC_GL_STATE_SHADER
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, State->useProgram.program = 0);
#endif
    
#if CC_GL_STATE_STENCIL
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->clearStencil.s = 0);
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, State->stencilFunc = (typeof(State->stencilFunc)){ .func = GL_ALWAYS, .ref = 0, .mask = UINT_MAX });
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, State->stencilFunc = (typeof(State->stencilFunc)){ .front = { .func = GL_ALWAYS, .ref = 0, .mask = UINT_MAX }, .back = { .func = GL_ALWAYS, .ref = 0, .mask = UINT_MAX } });
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, State->stencilMask.mask = UINT_MAX);
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, State->stencilMask = (typeof(State->stencilMask)){ .front = { .mask = UINT_MAX }, .back = { .mask = UINT_MAX } });
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, State->stencilOp = (typeof(State->stencilOp)){ .sfail = GL_KEEP, .dpfail = GL_KEEP, .dppass = GL_KEEP });
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, State->stencilOp = (typeof(State->stencilOp)){ .front = { .sfail = GL_KEEP, .dpfail = GL_KEEP, .dppass = GL_KEEP }, .back = { .sfail = GL_KEEP, .dpfail = GL_KEEP, .dppass = GL_KEEP } });
#endif
    
#if CC_GL_STATE_TEXTURE
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, State->activeTexture.texture = GL_TEXTURE0);
    
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA,
#if CC_GL_STATE_TEXTURE_MAX
        const size_t Count = CC_GL_STATE_TEXTURE_MAX;
#else
        if (State->bindTexture)
        {
            GLint Count;
            CC_GL_VERSION_ACTIVE(1_1, 1_5, 1_0, 1_1, glGetIntegerv(GL_MAX_TEXTURE_UNITS, &Count); CC_GL_CHECK());
            CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Count); CC_GL_CHECK());
#endif
        
        memset(State->bindTexture, 0, Count * sizeof(typeof(*State->bindTexture)));
            
#if !CC_GL_STATE_TEXTURE_MAX
        }
#endif
    );
#endif
    
#if CC_GL_STATE_VERTEX_ARRAY_OBJECT
#if GL_APPLE_vertex_array_object || GL_OES_vertex_array_object
    State->bindVertexArray.array = 0;
#else
    CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, State->bindVertexArray.array = 0);
#endif
#endif
    
#if CC_GL_STATE_VIEWPORT
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLint Viewport[4];
        glGetIntegerv(GL_SCISSOR_BOX, Viewport); CC_GL_CHECK();
        State->viewport = (typeof(State->viewport)){ .x = 0, .y = 0, .width = Viewport[2], .height = Viewport[3] };
    );
#endif
}

void CCGLStateInitializeWithCurrent(CCGLState *State)
{
    CC_GL_SETUP_CONTEXT;
    
#if CC_GL_STATE_BLEND
    CC_GL_VERSION_ACTIVE(1_0, 1_3, 1_0, 1_1,
        glGetIntegerv(GL_BLEND_SRC, (GLint*)&State->blendFunc.src); CC_GL_CHECK();
        glGetIntegerv(GL_BLEND_DST, (GLint*)&State->blendFunc.dst); CC_GL_CHECK();
    );
    CC_GL_VERSION_ACTIVE(1_4, NA, 2_0, NA,
        glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&State->blendFunc.rgb.src); CC_GL_CHECK();
        glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&State->blendFunc.alpha.src); CC_GL_CHECK();
        glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&State->blendFunc.rgb.dst); CC_GL_CHECK();
        glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&State->blendFunc.alpha.dst); CC_GL_CHECK();
    );
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, NA, NA, glGetIntegerv(GL_BLEND_EQUATION, (GLint*)&State->blendEquation.mode); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA,
        glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&State->blendEquation.rgb.mode); CC_GL_CHECK();
        glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&State->blendEquation.alpha.mode); CC_GL_CHECK();
    );
#endif
    
#if CC_GL_STATE_BUFFER
    CC_GL_VERSION_ACTIVE(1_5, NA, 1_0, NA,
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_ARRAY_BUFFER); CC_GL_CHECK();
        CC_GL_VERSION_ACTIVE(4_2, NA, 3_1, NA, glGetIntegerv(GL_ATOMIC_COUNTER_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_ATOMIC_COUNTER_BUFFER); CC_GL_CHECK());
#if GL_COPY_READ_BUFFER_BINDING //bug?
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, glGetIntegerv(GL_COPY_READ_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_COPY_READ_BUFFER); CC_GL_CHECK());
#endif
#if GL_COPY_WRITE_BUFFER_BINDING //bug?
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, glGetIntegerv(GL_COPY_WRITE_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_COPY_WRITE_BUFFER); CC_GL_CHECK());
#endif
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, glGetIntegerv(GL_DISPATCH_INDIRECT_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_DISPATCH_INDIRECT_BUFFER); CC_GL_CHECK());
        CC_GL_VERSION_ACTIVE(4_0, NA, 3_1, NA, glGetIntegerv(GL_DRAW_INDIRECT_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_DRAW_INDIRECT_BUFFER); CC_GL_CHECK());
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_ELEMENT_ARRAY_BUFFER); CC_GL_CHECK();
        CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_PIXEL_PACK_BUFFER); CC_GL_CHECK());
        CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_PIXEL_UNPACK_BUFFER); CC_GL_CHECK());
        CC_GL_VERSION_ACTIVE(4_4, NA, NA, NA, glGetIntegerv(GL_QUERY_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_QUERY_BUFFER); CC_GL_CHECK());
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, glGetIntegerv(GL_SHADER_STORAGE_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_SHADER_STORAGE_BUFFER); CC_GL_CHECK());
#if GL_TEXTURE_BUFFER_BINDING //bug?
        CC_GL_VERSION_ACTIVE(3_1, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_TEXTURE_BUFFER); CC_GL_CHECK());
#endif
        CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, glGetIntegerv(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_TRANSFORM_FEEDBACK_BUFFER); CC_GL_CHECK());
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, (GLint*)&State->bindBuffer._GL_UNIFORM_BUFFER); CC_GL_CHECK());
    );
#endif
    
#if CC_GL_STATE_COLOUR
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLclampf ClearColour[4];
        glGetFloatv(GL_COLOR_CLEAR_VALUE, ClearColour); CC_GL_CHECK();
        State->clearColour = (typeof(State->clearColour)){ .red = ClearColour[0], .green = ClearColour[1], .blue = ClearColour[2], .alpha = ClearColour[3] };
    );
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLboolean ColourMask[4];
        glGetBooleanv(GL_COLOR_WRITEMASK, ColourMask); CC_GL_CHECK();
        State->colourMask = (typeof(State->colourMask)){ .red = ColourMask[0], .green = ColourMask[1], .blue = ColourMask[2], .alpha = ColourMask[3] };
    );
#endif
    
#if CC_GL_STATE_CULL_FACE
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, glGetIntegerv(GL_CULL_FACE_MODE, (GLint*)&State->cullFace.mode); CC_GL_CHECK());
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, glGetIntegerv(GL_FRONT_FACE, (GLint*)&State->frontFace.mode); CC_GL_CHECK());
#endif
    
#if CC_GL_STATE_DEPTH
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, glGetFloatv(GL_DEPTH_CLEAR_VALUE, &State->clearDepth.depth); CC_GL_CHECK());
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, glGetIntegerv(GL_DEPTH_FUNC, (GLint*)&State->depthFunc.func); CC_GL_CHECK());
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, glGetBooleanv(GL_DEPTH_WRITEMASK, &State->depthMask.flag); CC_GL_CHECK());
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLclampf DepthRange[4];
        glGetFloatv(GL_DEPTH_RANGE, DepthRange); CC_GL_CHECK();
        State->depthRange = (typeof(State->depthRange)){ .near = DepthRange[0], .far = DepthRange[1] };
    );
#endif
    
#if CC_GL_STATE_ENABLED
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA,
        if (State->enabled.clipDistance)
        {
            GLint MaxClipDistances;
            glGetIntegerv(GL_MAX_CLIP_DISTANCES, &MaxClipDistances); CC_GL_CHECK();
            for (GLint Loop = 0; Loop < MaxClipDistances; Loop++)
            {
                State->enabled.clipDistance[Loop] = glIsEnabled(GL_CLIP_DISTANCE0 + Loop); CC_GL_CHECK();
            }
        }
    );
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1,
        if (State->enabled.clipPlane)
        {
            GLint MaxClipPlanes;
            glGetIntegerv(GL_MAX_CLIP_PLANES, &MaxClipPlanes); CC_GL_CHECK();
            for (GLint Loop = 0; Loop < MaxClipPlanes; Loop++)
            {
                State->enabled.clipPlane[Loop] = glIsEnabled(GL_CLIP_PLANE0 + Loop); CC_GL_CHECK();
            }
        }
    );
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1,
        if (State->enabled.light)
        {
            GLint MaxLights;
            glGetIntegerv(GL_MAX_LIGHTS, &MaxLights); CC_GL_CHECK();
            for (GLint Loop = 0; Loop < MaxLights; Loop++)
            {
                State->enabled.light[Loop] = glIsEnabled(GL_LIGHT0 + Loop); CC_GL_CHECK();
            }
        }
    );
    
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_ALPHA_TEST = glIsEnabled(GL_ALPHA_TEST); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_AUTO_NORMAL = glIsEnabled(GL_AUTO_NORMAL); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_BLEND = glIsEnabled(GL_BLEND); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, 1_1, State->enabled._GL_COLOR_LOGIC_OP = glIsEnabled(GL_COLOR_LOGIC_OP); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_COLOR_MATERIAL = glIsEnabled(GL_COLOR_MATERIAL); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_COLOR_SUM = glIsEnabled(GL_COLOR_SUM); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_CULL_FACE = glIsEnabled(GL_CULL_FACE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(4_3, NA, NA, NA, State->enabled._GL_DEBUG_OUTPUT = glIsEnabled(GL_DEBUG_OUTPUT); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(4_3, NA, NA, NA, State->enabled._GL_DEBUG_OUTPUT_SYNCHRONOUS = glIsEnabled(GL_DEBUG_OUTPUT_SYNCHRONOUS); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, State->enabled._GL_DEPTH_CLAMP = glIsEnabled(GL_DEPTH_CLAMP); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_DEPTH_TEST = glIsEnabled(GL_DEPTH_TEST); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_DITHER = glIsEnabled(GL_DITHER); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_FOG = glIsEnabled(GL_FOG); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, State->enabled._GL_FRAMEBUFFER_SRGB = glIsEnabled(GL_FRAMEBUFFER_SRGB); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_1, 2_1, NA, NA, State->enabled._GL_INDEX_LOGIC_OP = glIsEnabled(GL_INDEX_LOGIC_OP); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_LIGHTING = glIsEnabled(GL_LIGHTING); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, 1_1, State->enabled._GL_LINE_SMOOTH = glIsEnabled(GL_LINE_SMOOTH); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_LINE_STIPPLE = glIsEnabled(GL_LINE_STIPPLE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_COLOR_4 = glIsEnabled(GL_MAP1_COLOR_4); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_INDEX = glIsEnabled(GL_MAP1_INDEX); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_NORMAL = glIsEnabled(GL_MAP1_NORMAL); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_TEXTURE_COORD_1 = glIsEnabled(GL_MAP1_TEXTURE_COORD_1); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_TEXTURE_COORD_2 = glIsEnabled(GL_MAP1_TEXTURE_COORD_2); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_TEXTURE_COORD_3 = glIsEnabled(GL_MAP1_TEXTURE_COORD_3); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_TEXTURE_COORD_4 = glIsEnabled(GL_MAP1_TEXTURE_COORD_4); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_VERTEX_3 = glIsEnabled(GL_MAP1_VERTEX_3); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP1_VERTEX_4 = glIsEnabled(GL_MAP1_VERTEX_4); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_COLOR_4 = glIsEnabled(GL_MAP2_COLOR_4); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_INDEX = glIsEnabled(GL_MAP2_INDEX); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_NORMAL = glIsEnabled(GL_MAP2_NORMAL); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_TEXTURE_COORD_1 = glIsEnabled(GL_MAP2_TEXTURE_COORD_1); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_TEXTURE_COORD_2 = glIsEnabled(GL_MAP2_TEXTURE_COORD_2); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_TEXTURE_COORD_3 = glIsEnabled(GL_MAP2_TEXTURE_COORD_3); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_TEXTURE_COORD_4 = glIsEnabled(GL_MAP2_TEXTURE_COORD_4); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_VERTEX_3 = glIsEnabled(GL_MAP2_VERTEX_3); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MAP2_VERTEX_4 = glIsEnabled(GL_MAP2_VERTEX_4); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, 1_1, State->enabled._GL_MULTISAMPLE = glIsEnabled(GL_MULTISAMPLE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_NORMALIZE = glIsEnabled(GL_NORMALIZE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_POINT_SMOOTH = glIsEnabled(GL_POINT_SMOOTH); CC_GL_CHECK());
#if GL_POINT_SPRITE_OES
    CC_GL_VERSION_ACTIVE(2_0, 2_1, 1_0, 1_1, State->enabled._GL_POINT_SPRITE = glIsEnabled(GL_POINT_SPRITE_OES); CC_GL_CHECK());
#else
    CC_GL_VERSION_ACTIVE(2_0, 2_1, 1_0, 1_1, State->enabled._GL_POINT_SPRITE = glIsEnabled(GL_POINT_SPRITE); CC_GL_CHECK());
#endif
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, State->enabled._GL_POLYGON_OFFSET_FILL = glIsEnabled(GL_POLYGON_OFFSET_FILL); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, State->enabled._GL_POLYGON_OFFSET_LINE = glIsEnabled(GL_POLYGON_OFFSET_LINE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, State->enabled._GL_POLYGON_OFFSET_POINT = glIsEnabled(GL_POLYGON_OFFSET_POINT); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, NA, NA, State->enabled._GL_POLYGON_SMOOTH = glIsEnabled(GL_POLYGON_SMOOTH); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_POLYGON_STIPPLE = glIsEnabled(GL_POLYGON_STIPPLE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(3_1, NA, NA, NA, State->enabled._GL_PRIMITIVE_RESTART = glIsEnabled(GL_PRIMITIVE_RESTART); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(4_3, NA, 3_0, NA, State->enabled._GL_PRIMITIVE_RESTART_FIXED_INDEX = glIsEnabled(GL_PRIMITIVE_RESTART_FIXED_INDEX); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, State->enabled._GL_PROGRAM_POINT_SIZE = glIsEnabled(GL_PROGRAM_POINT_SIZE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(4_0, NA, 3_0, NA, State->enabled._GL_RASTERIZER_DISCARD = glIsEnabled(GL_RASTERIZER_DISCARD); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_2, 2_1, 1_0, 1_1, State->enabled._GL_RESCALE_NORMAL = glIsEnabled(GL_RESCALE_NORMAL); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, State->enabled._GL_SAMPLE_ALPHA_TO_COVERAGE = glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, 1_1, State->enabled._GL_SAMPLE_ALPHA_TO_ONE = glIsEnabled(GL_SAMPLE_ALPHA_TO_ONE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, State->enabled._GL_SAMPLE_COVERAGE = glIsEnabled(GL_SAMPLE_COVERAGE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(4_0, NA, NA, NA, State->enabled._GL_SAMPLE_SHADING = glIsEnabled(GL_SAMPLE_SHADING); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(4_0, NA, 3_1, NA, State->enabled._GL_SAMPLE_MASK = glIsEnabled(GL_SAMPLE_MASK); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_SCISSOR_TEST = glIsEnabled(GL_SCISSOR_TEST); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, State->enabled._GL_STENCIL_TEST = glIsEnabled(GL_STENCIL_TEST); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_TEXTURE_1D = glIsEnabled(GL_TEXTURE_1D); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, State->enabled._GL_TEXTURE_2D = glIsEnabled(GL_TEXTURE_2D); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_2, 2_1, NA, NA, State->enabled._GL_TEXTURE_3D = glIsEnabled(GL_TEXTURE_3D); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_3, 2_1, NA, NA, State->enabled._GL_TEXTURE_CUBE_MAP = glIsEnabled(GL_TEXTURE_CUBE_MAP); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, State->enabled._GL_TEXTURE_CUBE_MAP_SEAMLESS = glIsEnabled(GL_TEXTURE_CUBE_MAP_SEAMLESS); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_TEXTURE_GEN_Q = glIsEnabled(GL_TEXTURE_GEN_Q); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_TEXTURE_GEN_R = glIsEnabled(GL_TEXTURE_GEN_R); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_TEXTURE_GEN_S = glIsEnabled(GL_TEXTURE_GEN_S); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_TEXTURE_GEN_T = glIsEnabled(GL_TEXTURE_GEN_T); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(2_0, 2_1, NA, NA, State->enabled._GL_VERTEX_PROGRAM_POINT_SIZE = glIsEnabled(GL_VERTEX_PROGRAM_POINT_SIZE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(2_0, 2_1, NA, NA, State->enabled._GL_VERTEX_PROGRAM_TWO_SIDE = glIsEnabled(GL_VERTEX_PROGRAM_TWO_SIDE); CC_GL_CHECK());
    
#if GL_ARB_imaging
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_COLOR_TABLE = glIsEnabled(GL_COLOR_TABLE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_CONVOLUTION_1D = glIsEnabled(GL_CONVOLUTION_1D); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_CONVOLUTION_2D = glIsEnabled(GL_CONVOLUTION_2D); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_HISTOGRAM = glIsEnabled(GL_HISTOGRAM); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_MINMAX = glIsEnabled(GL_MINMAX); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_POST_COLOR_MATRIX_COLOR_TABLE = glIsEnabled(GL_POST_COLOR_MATRIX_COLOR_TABLE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_POST_CONVOLUTION_COLOR_TABLE = glIsEnabled(GL_POST_CONVOLUTION_COLOR_TABLE); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, State->enabled._GL_SEPARABLE_2D = glIsEnabled(GL_SEPARABLE_2D); CC_GL_CHECK());
#endif
    
#if GL_ARB_texture_rectangle
    CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, State->enabled._GL_TEXTURE_RECTANGLE_ARB = glIsEnabled(GL_TEXTURE_RECTANGLE_ARB); CC_GL_CHECK());
#endif
#endif
    
    
#if CC_GL_STATE_FRAMEBUFFER
#if GL_ARB_framebuffer_object || GL_OES_framebuffer_object
#if GL_DRAW_FRAMEBUFFER_BINDING && GL_READ_FRAMEBUFFER_BINDING
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, (GLint*)&State->bindFramebuffer.write); CC_GL_CHECK();
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, (GLint*)&State->bindFramebuffer.read); CC_GL_CHECK();
#else
    GLuint Framebuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&Framebuffer); CC_GL_CHECK();
    State->bindFramebuffer = (typeof(State->bindFramebuffer)){ .read = Framebuffer, .write = Framebuffer };
#endif
#else
    CC_GL_VERSION_ACTIVE(3_0, NA, 2_0, NA,
#if GL_DRAW_FRAMEBUFFER_BINDING && GL_READ_FRAMEBUFFER_BINDING
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, (GLint*)&State->bindFramebuffer.write); CC_GL_CHECK();
        glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, (GLint*)&State->bindFramebuffer.read); CC_GL_CHECK();
#else
        GLuint Framebuffer;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&Framebuffer); CC_GL_CHECK();
        State->bindFramebuffer = (typeof(State->bindFramebuffer)){ .read = Framebuffer, .write = Framebuffer };
#endif
    );
#endif
#endif
    
#if CC_GL_STATE_SCISSOR
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLint ScissorBox[4];
        glGetIntegerv(GL_SCISSOR_BOX, ScissorBox); CC_GL_CHECK();
        State->scissor = (typeof(State->scissor)){ .x = ScissorBox[0], .y = ScissorBox[1], .width = ScissorBox[2], .height = ScissorBox[3] };
    );
#endif
    
#if CC_GL_STATE_SHADER
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&State->useProgram.program); CC_GL_CHECK());
#endif
    
#if CC_GL_STATE_STENCIL
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &State->clearStencil.s); CC_GL_CHECK());
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1,
        glGetIntegerv(GL_STENCIL_FUNC, (GLint*)&State->stencilFunc.func); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_REF, &State->stencilFunc.ref); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint*)&State->stencilFunc.mask); CC_GL_CHECK();
    );
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA,
        glGetIntegerv(GL_STENCIL_FUNC, (GLint*)&State->stencilFunc.front.func); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_REF, &State->stencilFunc.front.ref); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_VALUE_MASK, (GLint*)&State->stencilFunc.front.mask); CC_GL_CHECK();
        
        glGetIntegerv(GL_STENCIL_BACK_FUNC, (GLint*)&State->stencilFunc.back.func); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_BACK_REF, &State->stencilFunc.back.ref); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_BACK_VALUE_MASK, (GLint*)&State->stencilFunc.back.mask); CC_GL_CHECK();
    );
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint*)&State->stencilMask.mask); CC_GL_CHECK());
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA,
        glGetIntegerv(GL_STENCIL_WRITEMASK, (GLint*)&State->stencilMask.front.mask); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_BACK_WRITEMASK, (GLint*)&State->stencilMask.back.mask); CC_GL_CHECK();
    );

    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1,
        glGetIntegerv(GL_STENCIL_FAIL, (GLint*)&State->stencilOp.sfail); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint*)&State->stencilOp.dpfail); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint*)&State->stencilOp.dppass); CC_GL_CHECK();
    );
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA,
        glGetIntegerv(GL_STENCIL_FAIL, (GLint*)&State->stencilOp.front.sfail); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, (GLint*)&State->stencilOp.front.dpfail); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, (GLint*)&State->stencilOp.front.dppass); CC_GL_CHECK();
        
        glGetIntegerv(GL_STENCIL_BACK_FAIL, (GLint*)&State->stencilOp.back.sfail); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, (GLint*)&State->stencilOp.back.dpfail); CC_GL_CHECK();
        glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_PASS, (GLint*)&State->stencilOp.back.dppass); CC_GL_CHECK();
    );
#endif
    
#if CC_GL_STATE_TEXTURE
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&State->activeTexture.texture); CC_GL_CHECK());
    
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA,
#if CC_GL_STATE_TEXTURE_MAX
        const size_t Count = CC_GL_STATE_TEXTURE_MAX;
#else
        if (State->bindTexture)
        {
            GLint Count;
            CC_GL_VERSION_ACTIVE(1_1, 1_5, 1_0, 1_1, glGetIntegerv(GL_MAX_TEXTURE_UNITS, &Count); CC_GL_CHECK());
            CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Count); CC_GL_CHECK());
#endif
        
        for (GLint Loop = 0; Loop < Count; Loop++)
        {
            CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, glActiveTexture((GLenum)(GL_TEXTURE0 + Loop)); CC_GL_CHECK());
#if CC_GL_STATE_TEXTURE_1D
            CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_1D, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_1D); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_2D
            CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_2D); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_3D
            CC_GL_VERSION_ACTIVE(1_1, NA, 3_0, NA, glGetIntegerv(GL_TEXTURE_BINDING_3D, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_3D); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_1D_ARRAY
            CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_1D_ARRAY, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_1D_ARRAY); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_2D_ARRAY
            CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, glGetIntegerv(GL_TEXTURE_BINDING_2D_ARRAY, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_2D_ARRAY); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_RECTANGLE
#if GL_ARB_texture_rectangle
            glGetIntegerv(GL_TEXTURE_BINDING_RECTANGLE_ARB, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_RECTANGLE_ARB); CC_GL_CHECK();
#else
            CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_RECTANGLE, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_RECTANGLE); CC_GL_CHECK());
#endif
#endif
#if CC_GL_STATE_TEXTURE_CUBE_MAP
            CC_GL_VERSION_ACTIVE(1_3, NA, 2_0, NA, glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_CUBE_MAP); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_CUBE_MAP_ARRAY
            CC_GL_VERSION_ACTIVE(4_0, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP_ARRAY, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_CUBE_MAP_ARRAY); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_BUFFER
            CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_BUFFER, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_BUFFER); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE
            CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_2D_MULTISAMPLE, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_2D_MULTISAMPLE); CC_GL_CHECK());
#endif
#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE_ARRAY
            CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, glGetIntegerv(GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, (GLint*)&State->bindTexture[Loop]._GL_TEXTURE_2D_MULTISAMPLE_ARRAY); CC_GL_CHECK());
#endif
        }
        
#if !CC_GL_STATE_TEXTURE_MAX
        }
    
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, glActiveTexture(State->activeTexture.texture); CC_GL_CHECK());
#endif
    );
#endif
    
#if CC_GL_STATE_VERTEX_ARRAY_OBJECT
#if GL_APPLE_vertex_array_object || GL_OES_vertex_array_object
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&State->bindVertexArray.array); CC_GL_CHECK();
#else
    CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&State->bindVertexArray.array); CC_GL_CHECK());
#endif
#endif
    
#if CC_GL_STATE_VIEWPORT
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA,
        GLint Viewport[4];
        glGetIntegerv(GL_VIEWPORT, Viewport); CC_GL_CHECK();
        State->viewport = (typeof(State->viewport)){ .x = Viewport[0], .y = Viewport[1], .width = Viewport[2], .height = Viewport[3] };
    );
#endif
}
