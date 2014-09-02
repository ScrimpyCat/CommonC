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

#ifndef CommonGL_Defined_h
#define CommonGL_Defined_h

#if defined(__gl_h_) || defined(__gl3_h_)
#define CC_OPENGL 1
#elif defined(ES1_GL_H_GUARD) || defined(__gl_es20_h_) || defined(__gl_es30_h_)
#define CC_OPENGL_ES 1
#else
#import <CommonC/Platform.h>

#if CC_PLATFORM_OS_X
#define CC_OPENGL 1

#import <OpenGL/OpenGL.h>

#if defined(CC_OPENGL_MODERN)
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
#elif defined(CC_OPENGL_LEGACY)
#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#else
#error Select OpenGL version
#endif

#elif CC_PLATFORM_IOS
#define CC_OPENGL_ES 1

#import <OpenGLES/EAGL.h>

#if defined(CC_OPENGL_ES_MODERN)
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#elif defined(CC_OPENGL_ES_LEGACY)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#warning Not entirely compatible with fixed function pipeline
#else
#error Select OpenGL ES version
#endif

#else
#error Currently not supported
#endif

#endif

#endif
