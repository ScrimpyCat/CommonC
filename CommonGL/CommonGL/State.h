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

#ifndef CommonGL_State_h
#define CommonGL_State_h

#import <CommonGL/Defined.h>
#import <CommonGL/Version.h>
#import <CommonGL/Context.h>
#import <CommonC/Types.h>


#if CC_GL_STATE_COMPLETE
#define CC_GL_STATE_BLEND 1
#define CC_GL_STATE_BUFFER 1
#define CC_GL_STATE_COLOUR 1
#define CC_GL_STATE_CULL_FACE 1
#define CC_GL_STATE_DEPTH 1
#define CC_GL_STATE_ENABLED 1
#define CC_GL_STATE_FRAMEBUFFER 1
#define CC_GL_STATE_SCISSOR 1
#define CC_GL_STATE_SHADER 1
#define CC_GL_STATE_STENCIL 1
#define CC_GL_STATE_TEXTURE 1
#define CC_GL_STATE_TEXTURE_COMPLETE 1
#define CC_GL_STATE_VERTEX_ARRAY_OBJECT 1
#define CC_GL_STATE_VIEWPORT 1
#endif

#if CC_GL_STATE_TEXTURE_COMPLETE
#define CC_GL_STATE_TEXTURE_1D 1
#define CC_GL_STATE_TEXTURE_2D 1
#define CC_GL_STATE_TEXTURE_3D 1
#define CC_GL_STATE_TEXTURE_1D_ARRAY 1
#define CC_GL_STATE_TEXTURE_2D_ARRAY 1
#define CC_GL_STATE_TEXTURE_RECTANGLE 1
#define CC_GL_STATE_TEXTURE_CUBE_MAP 1
#define CC_GL_STATE_TEXTURE_CUBE_MAP_ARRAY 1
#define CC_GL_STATE_TEXTURE_BUFFER 1
#define CC_GL_STATE_TEXTURE_2D_MULTISAMPLE 1
#define CC_GL_STATE_TEXTURE_2D_MULTISAMPLE_ARRAY 1
#endif

#if !CC_GL_STATE_TEXTURE
#if CC_GL_STATE_TEXTURE_1D \
 || CC_GL_STATE_TEXTURE_2D \
 || CC_GL_STATE_TEXTURE_3D \
 || CC_GL_STATE_TEXTURE_1D_ARRAY \
 || CC_GL_STATE_TEXTURE_2D_ARRAY \
 || CC_GL_STATE_TEXTURE_RECTANGLE \
 || CC_GL_STATE_TEXTURE_CUBE_MAP \
 || CC_GL_STATE_TEXTURE_CUBE_MAP_ARRAY \
 || CC_GL_STATE_TEXTURE_BUFFER \
 || CC_GL_STATE_TEXTURE_2D_MULTISAMPLE \
 || CC_GL_STATE_TEXTURE_2D_MULTISAMPLE_ARRAY
#define CC_GL_STATE_TEXTURE 1
#endif
#endif


//To set a hard limit for the maximum textures that can be bound, define CC_GL_STATE_TEXTURE_MAX



typedef struct {
#if CC_GL_STATE_BLEND
    CC_GL_VERSION_ACTIVE(1_0, 1_3, 1_0, 1_1, struct {
        GLenum src, dst;
    } blendFunc); //glBlendFunc
    CC_GL_VERSION_ACTIVE(1_4, NA, 2_0, NA, struct {
        struct { GLenum src, dst; } rgb, alpha;
    } blendFunc); //glBlendFunc + glBlendFuncSeparate
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, NA, NA, struct {
        GLenum mode;
    } blendEquation); //glBlendEquation
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, struct {
        struct { GLenum mode; } rgb, alpha;
    } blendEquation); //glBlendEquation + glBlendEquationSeparate
#endif
    
#if CC_GL_STATE_BUFFER
    CC_GL_VERSION_ACTIVE(1_5, NA, 1_0, NA, struct {
        GLuint _GL_ARRAY_BUFFER; //GL_ARRAY_BUFFER
        CC_GL_VERSION_ACTIVE(4_2, NA, 3_1, NA, GLuint _GL_ATOMIC_COUNTER_BUFFER); //GL_ATOMIC_COUNTER_BUFFER
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, GLuint _GL_COPY_READ_BUFFER); //GL_COPY_READ_BUFFER
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, GLuint _GL_COPY_WRITE_BUFFER); //GL_COPY_WRITE_BUFFER
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, GLuint _GL_DISPATCH_INDIRECT_BUFFER); //GL_DISPATCH_INDIRECT_BUFFER
        CC_GL_VERSION_ACTIVE(4_0, NA, 3_1, NA, GLuint _GL_DRAW_INDIRECT_BUFFER); //GL_DRAW_INDIRECT_BUFFER
        GLuint _GL_ELEMENT_ARRAY_BUFFER; //GL_ELEMENT_ARRAY_BUFFER
        CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, GLuint _GL_PIXEL_PACK_BUFFER); //GL_PIXEL_PACK_BUFFER
        CC_GL_VERSION_ACTIVE(1_5, NA, 3_0, NA, GLuint _GL_PIXEL_UNPACK_BUFFER); //GL_PIXEL_UNPACK_BUFFER
        CC_GL_VERSION_ACTIVE(4_4, NA, NA, NA, GLuint _GL_QUERY_BUFFER); //GL_QUERY_BUFFER
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_1, NA, GLuint _GL_SHADER_STORAGE_BUFFER); //GL_SHADER_STORAGE_BUFFER
        CC_GL_VERSION_ACTIVE(3_1, NA, NA, NA, GLuint _GL_TEXTURE_BUFFER); //GL_TEXTURE_BUFFER
        CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, GLuint _GL_TRANSFORM_FEEDBACK_BUFFER); //GL_TRANSFORM_FEEDBACK_BUFFER
        CC_GL_VERSION_ACTIVE(3_1, NA, 3_0, NA, GLuint _GL_UNIFORM_BUFFER); //GL_UNIFORM_BUFFER
    } bindBuffer); //glBindBuffer
#endif
    
#if CC_GL_STATE_COLOUR
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLclampf red, green, blue, alpha;
    } clearColour); //glClearColor
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLboolean red, green, blue, alpha;
    } colourMask); //glColorMask
#endif
    
#if CC_GL_STATE_CULL_FACE
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLenum mode;
    } cullFace); //glCullFace
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLenum mode;
    } frontFace); //glFrontFace
#endif
    
#if CC_GL_STATE_DEPTH
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLclampf depth;
    } clearDepth); //glClearDepthf
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLenum func;
    } depthFunc); //glDepthFunc
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLboolean flag;
    } depthMask); //glDepthMask
    
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLclampf near, far;
    } depthRange); //glDepthRangef
#endif
    
#if CC_GL_STATE_ENABLED
    struct {
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, uint8_t *clipDistance); //GL_CLIP_DISTANCEi [GL_MAX_CLIP_DISTANCES]
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t *clipPlane); //GL_CLIP_PLANEi [GL_MAX_CLIP_PLANES]
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t *light); //GL_LIGHTi [GL_MAX_LIGHTS]
        
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_ALPHA_TEST : 1); //GL_ALPHA_TEST
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_AUTO_NORMAL : 1); //GL_AUTO_NORMAL
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, uint8_t _GL_BLEND : 1); //GL_BLEND
        CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, 1_1, uint8_t _GL_COLOR_LOGIC_OP : 1); //GL_COLOR_LOGIC_OP
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_COLOR_MATERIAL : 1); //GL_COLOR_MATERIAL
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_COLOR_SUM : 1); //GL_COLOR_SUM
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, uint8_t _GL_CULL_FACE : 1); //GL_CULL_FACE
        CC_GL_VERSION_ACTIVE(4_3, NA, NA, NA, uint8_t _GL_DEBUG_OUTPUT : 1); //GL_DEBUG_OUTPUT
        CC_GL_VERSION_ACTIVE(4_3, NA, NA, NA, uint8_t _GL_DEBUG_OUTPUT_SYNCHRONOUS : 1); //GL_DEBUG_OUTPUT_SYNCHRONOUS
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, uint8_t _GL_DEPTH_CLAMP : 1); //GL_DEPTH_CLAMP
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, uint8_t _GL_DEPTH_TEST : 1); //GL_DEPTH_TEST
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, uint8_t _GL_DITHER : 1); //GL_DITHER
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_FOG : 1); //GL_FOG
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, uint8_t _GL_FRAMEBUFFER_SRGB : 1); //GL_FRAMEBUFFER_SRGB
        CC_GL_VERSION_ACTIVE(1_1, 2_1, NA, NA, uint8_t _GL_INDEX_LOGIC_OP : 1); //GL_INDEX_LOGIC_OP
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_LIGHTING : 1); //GL_LIGHTING
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, 1_1, uint8_t _GL_LINE_SMOOTH : 1); //GL_LINE_SMOOTH
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_LINE_STIPPLE : 1); //GL_LINE_STIPPLE
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_COLOR_4 : 1); //GL_MAP1_COLOR_4
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_INDEX : 1); //GL_MAP1_INDEX
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_NORMAL : 1); //GL_MAP1_NORMAL
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_TEXTURE_COORD_1 : 1); //GL_MAP1_TEXTURE_COORD_1
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_TEXTURE_COORD_2 : 1); //GL_MAP1_TEXTURE_COORD_2
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_TEXTURE_COORD_3 : 1); //GL_MAP1_TEXTURE_COORD_3
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_TEXTURE_COORD_4 : 1); //GL_MAP1_TEXTURE_COORD_4
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_VERTEX_3 : 1); //GL_MAP1_VERTEX_3
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP1_VERTEX_4 : 1); //GL_MAP1_VERTEX_4
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_COLOR_4 : 1); //GL_MAP2_COLOR_4
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_INDEX : 1); //GL_MAP2_INDEX
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_NORMAL : 1); //GL_MAP2_NORMAL
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_TEXTURE_COORD_1 : 1); //GL_MAP2_TEXTURE_COORD_1
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_TEXTURE_COORD_2 : 1); //GL_MAP2_TEXTURE_COORD_2
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_TEXTURE_COORD_3 : 1); //GL_MAP2_TEXTURE_COORD_3
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_TEXTURE_COORD_4 : 1); //GL_MAP2_TEXTURE_COORD_4
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_VERTEX_3 : 1); //GL_MAP2_VERTEX_3
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MAP2_VERTEX_4 : 1); //GL_MAP2_VERTEX_4
        CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, 1_1, uint8_t _GL_MULTISAMPLE : 1); //GL_MULTISAMPLE
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_NORMALIZE : 1); //GL_NORMALIZE
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_POINT_SMOOTH : 1); //GL_POINT_SMOOTH
        #define _GL_POINT_SPRITE_OES _GL_POINT_SPRITE
        CC_GL_VERSION_ACTIVE(2_0, 2_1, 1_0, 1_1, uint8_t _GL_POINT_SPRITE : 1); //GL_POINT_SPRITE or GL_POINT_SPRITE_OES (GLES)
        CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, uint8_t _GL_POLYGON_OFFSET_FILL : 1); //GL_POLYGON_OFFSET_FILL
        CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, uint8_t _GL_POLYGON_OFFSET_LINE : 1); //GL_POLYGON_OFFSET_LINE
        CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, uint8_t _GL_POLYGON_OFFSET_POINT : 1); //GL_POLYGON_OFFSET_POINT
        CC_GL_VERSION_ACTIVE(1_0, NA, NA, NA, uint8_t _GL_POLYGON_SMOOTH : 1); //GL_POLYGON_SMOOTH
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_POLYGON_STIPPLE : 1); //GL_POLYGON_STIPPLE
        CC_GL_VERSION_ACTIVE(3_1, NA, NA, NA, uint8_t _GL_PRIMITIVE_RESTART : 1); //GL_PRIMITIVE_RESTART
        CC_GL_VERSION_ACTIVE(4_3, NA, 3_0, NA, uint8_t _GL_PRIMITIVE_RESTART_FIXED_INDEX : 1); //GL_PRIMITIVE_RESTART_FIXED_INDEX
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, uint8_t _GL_PROGRAM_POINT_SIZE : 1); //GL_PROGRAM_POINT_SIZE
        CC_GL_VERSION_ACTIVE(4_0, NA, 3_0, NA, uint8_t _GL_RASTERIZER_DISCARD : 1); //GL_RASTERIZER_DISCARD
        CC_GL_VERSION_ACTIVE(1_2, 2_1, 1_0, 1_1, uint8_t _GL_RESCALE_NORMAL : 1); //GL_RESCALE_NORMAL
        CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, uint8_t _GL_SAMPLE_ALPHA_TO_COVERAGE : 1); //GL_SAMPLE_ALPHA_TO_COVERAGE
        CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, 1_1, uint8_t _GL_SAMPLE_ALPHA_TO_ONE : 1); //GL_SAMPLE_ALPHA_TO_ONE
        CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, uint8_t _GL_SAMPLE_COVERAGE : 1); //GL_SAMPLE_COVERAGE
        CC_GL_VERSION_ACTIVE(4_0, NA, NA, NA, uint8_t _GL_SAMPLE_SHADING : 1); //GL_SAMPLE_SHADING
        CC_GL_VERSION_ACTIVE(4_0, NA, 3_1, NA, uint8_t _GL_SAMPLE_MASK : 1); //GL_SAMPLE_MASK
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, uint8_t _GL_SCISSOR_TEST : 1); //GL_SCISSOR_TEST
        CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, uint8_t _GL_STENCIL_TEST : 1); //GL_STENCIL_TEST
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_TEXTURE_1D : 1); //GL_TEXTURE_1D
        CC_GL_VERSION_ACTIVE(1_0, 2_1, 1_0, 1_1, uint8_t _GL_TEXTURE_2D : 1); //GL_TEXTURE_2D
        CC_GL_VERSION_ACTIVE(1_2, 2_1, NA, NA, uint8_t _GL_TEXTURE_3D : 1); //GL_TEXTURE_3D
        CC_GL_VERSION_ACTIVE(1_3, 2_1, NA, NA, uint8_t _GL_TEXTURE_CUBE_MAP : 1); //GL_TEXTURE_CUBE_MAP
        CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, uint8_t _GL_TEXTURE_CUBE_MAP_SEAMLESS : 1); //GL_TEXTURE_CUBE_MAP_SEAMLESS
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_TEXTURE_GEN_Q : 1); //GL_TEXTURE_GEN_Q
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_TEXTURE_GEN_R : 1); //GL_TEXTURE_GEN_R
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_TEXTURE_GEN_S : 1); //GL_TEXTURE_GEN_S
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_TEXTURE_GEN_T : 1); //GL_TEXTURE_GEN_T
        CC_GL_VERSION_ACTIVE(2_0, 2_1, NA, NA, uint8_t _GL_VERTEX_PROGRAM_POINT_SIZE : 1); //GL_VERTEX_PROGRAM_POINT_SIZE
        CC_GL_VERSION_ACTIVE(2_0, 2_1, NA, NA, uint8_t _GL_VERTEX_PROGRAM_TWO_SIDE : 1); //GL_VERTEX_PROGRAM_TWO_SIDE
        
#if GL_ARB_imaging
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_COLOR_TABLE : 1); //GL_COLOR_TABLE
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_CONVOLUTION_1D : 1); //GL_CONVOLUTION_1D
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_CONVOLUTION_2D : 1); //GL_CONVOLUTION_2D
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_HISTOGRAM : 1); //GL_HISTOGRAM
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_MINMAX : 1); //GL_MINMAX
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_POST_COLOR_MATRIX_COLOR_TABLE : 1); //GL_POST_COLOR_MATRIX_COLOR_TABLE
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_POST_CONVOLUTION_COLOR_TABLE : 1); //GL_POST_CONVOLUTION_COLOR_TABLE
        CC_GL_VERSION_ACTIVE(1_0, 2_1, NA, NA, uint8_t _GL_SEPARABLE_2D : 1); //GL_SEPARABLE_2D
#endif
        
#if GL_ARB_texture_rectangle
        CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, uint8_t _GL_TEXTURE_RECTANGLE_ARB : 1); //GL_TEXTURE_RECTANGLE_ARB
#endif
    } enabled;
#endif
    
#if CC_GL_STATE_FRAMEBUFFER //GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER or GL_FRAMEBUFFER
#if GL_ARB_framebuffer_object || GL_OES_framebuffer_object
    struct {
        GLuint read, write;
    } bindFramebuffer; //glBindFramebuffer
#else
    CC_GL_VERSION_ACTIVE(3_0, NA, 2_0, NA, struct {
        GLuint read, write;
    } bindFramebuffer); //glBindFramebuffer
#endif
#endif
    
#if CC_GL_STATE_SCISSOR
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLint x, y;
        GLsizei width, height;
    } scissor); //glScissor
#endif
    
#if CC_GL_STATE_SHADER
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, struct {
        GLuint program;
    } useProgram); //glUseProgram
#endif
    
#if CC_GL_STATE_STENCIL
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLint s;
    } clearStencil); //glClearStencil
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, struct {
        GLenum func;
        GLint ref;
        GLuint mask;
    } stencilFunc); //glStencilFunc
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, struct {
        struct {
            GLenum func;
            GLint ref;
            GLuint mask;
        } front, back;
    } stencilFunc); //glStencilFunc + glStencilFuncSeparate
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, struct {
        GLuint mask;
    } stencilMask); //glStencilMask
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, struct {
        struct { GLuint mask; } front, back;
    } stencilMask); //glStencilMask + glStencilMaskSeparate
    
    CC_GL_VERSION_ACTIVE(1_0, 1_5, 1_0, 1_1, struct {
        GLenum sfail, dpfail, dppass;
    } stencilOp); //glStencilOp
    CC_GL_VERSION_ACTIVE(2_0, NA, 2_0, NA, struct {
        struct { GLenum sfail, dpfail, dppass; } front, back;
    } stencilOp); //glStencilOp + glStencilOpSeparate
#endif
    
#if CC_GL_STATE_TEXTURE
    CC_GL_VERSION_ACTIVE(1_3, NA, 1_0, NA, struct {
        GLenum texture;
    } activeTexture); //glActiveTexture
    
    CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, struct {
#if CC_GL_STATE_TEXTURE_1D
        CC_GL_VERSION_ACTIVE(1_1, NA, NA, NA, GLuint _GL_TEXTURE_1D); //GL_TEXTURE_1D
#endif
#if CC_GL_STATE_TEXTURE_2D
        CC_GL_VERSION_ACTIVE(1_1, NA, 1_0, NA, GLuint _GL_TEXTURE_2D); //GL_TEXTURE_2D
#endif
#if CC_GL_STATE_TEXTURE_3D
        CC_GL_VERSION_ACTIVE(1_1, NA, 3_0, NA, GLuint _GL_TEXTURE_3D); //GL_TEXTURE_3D
#endif
#if CC_GL_STATE_TEXTURE_1D_ARRAY
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, GLuint _GL_TEXTURE_1D_ARRAY); //GL_TEXTURE_1D_ARRAY
#endif
#if CC_GL_STATE_TEXTURE_2D_ARRAY
        CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, GLuint _GL_TEXTURE_2D_ARRAY); //GL_TEXTURE_2D_ARRAY
#endif
#if CC_GL_STATE_TEXTURE_RECTANGLE
#if GL_ARB_texture_rectangle
        GLuint _GL_TEXTURE_RECTANGLE_ARB; //GL_TEXTURE_RECTANGLE_ARB
#else
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, GLuint _GL_TEXTURE_RECTANGLE); //GL_TEXTURE_RECTANGLE
#endif
#endif
#if CC_GL_STATE_TEXTURE_CUBE_MAP
        CC_GL_VERSION_ACTIVE(1_3, NA, 2_0, NA, GLuint _GL_TEXTURE_CUBE_MAP); //GL_TEXTURE_CUBE_MAP
#endif
#if CC_GL_STATE_TEXTURE_CUBE_MAP_ARRAY
        CC_GL_VERSION_ACTIVE(4_0, NA, NA, NA, GLuint _GL_TEXTURE_CUBE_MAP_ARRAY); //GL_TEXTURE_CUBE_MAP_ARRAY
#endif
#if CC_GL_STATE_TEXTURE_BUFFER
        CC_GL_VERSION_ACTIVE(3_0, NA, NA, NA, GLuint _GL_TEXTURE_BUFFER); //GL_TEXTURE_BUFFER
#endif
#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE
        CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, GLuint _GL_TEXTURE_2D_MULTISAMPLE); //GL_TEXTURE_2D_MULTISAMPLE
#endif
#if CC_GL_STATE_TEXTURE_2D_MULTISAMPLE_ARRAY
        CC_GL_VERSION_ACTIVE(3_2, NA, NA, NA, GLuint _GL_TEXTURE_2D_MULTISAMPLE_ARRAY); //GL_TEXTURE_2D_MULTISAMPLE_ARRAY
#endif
    }
#if !CC_GL_STATE_TEXTURE_MAX
    *bindTexture); //[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS]
#else
    bindTexture[CC_GL_STATE_TEXTURE_MAX]);
#endif
#endif
    
#if CC_GL_STATE_VERTEX_ARRAY_OBJECT
#if GL_APPLE_vertex_array_object || GL_OES_vertex_array_object
    struct {
        GLuint array;
    } bindVertexArray; //glBindVertexArray
#else
    CC_GL_VERSION_ACTIVE(3_0, NA, 3_0, NA, struct {
        GLuint array;
    } bindVertexArray); //glBindVertexArray
#endif
#endif
    
#if CC_GL_STATE_VIEWPORT
    CC_GL_VERSION_ACTIVE(1_0, NA, 1_0, NA, struct {
        GLint x, y;
        GLsizei width, height;
    } viewport); //glViewport
#endif
} CCGLState;


CCGLState *CCGLStateForContext(CCGLContext Context);
CCGLState *CCGLStateCreate(void);
void CCGLStateRelease(CCGLState *State);
void CCGLStateInitializeWithDefault(CCGLState *State);
void CCGLStateInitializeWithCurrent(CCGLState *State);

#endif
