/*
 *  Copyright (c) 2011, 2013, Stefan Johnson
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

#ifndef CommonGL_Calling_h
#define CommonGL_Calling_h

#import <CommonC/Platform.h>
#import <CommonGL/Context.h>


#if CC_PLATFORM_OS_X && CC_GL_FAST_CALLING
//avoid repeated context and renderer lookups
#import <CommonGL/Version.h>

#if CC_OPENGL_LEGACY
#define CGL_MACRO_CACHE_RENDERER
#define CGL_MACRO_CONTEXT CC_GL_CURRENT_CONTEXT
#define CGL_MACRO_RENDERER CC_GL_PRIV_renderer___
#include <OpenGL/CGLMacro.h>

#define CC_GL_SETUP CGL_MACRO_DECLARE_VARIABLES()
#define CC_GL_SETUP_DECLARES_CONTEXT 1
#endif

#endif


#ifndef CC_GL_SETUP
#define CC_GL_SETUP
#endif


#define CC_GL_CURRENT_CONTEXT CC_GL_PRIV_context___


#if CC_GL_SETUP_DECLARES_CONTEXT

#define CC_GL_ENTRY \
CC_GL_SETUP; \
CCGLContextLock(CC_GL_PRIV_context___)

#else

#define CC_GL_ENTRY \
CCGLContext CC_GL_CURRENT_CONTEXT = CCGLContextGetCurrent() \
CC_GL_SETUP; \
CCGLContextLock(CC_GL_CURRENT_CONTEXT)

#endif


#define CC_GL_EXIT CCGLContextUnlock(CC_GL_CURRENT_CONTEXT)

#define CC_GL_ENTRY_FOR_CONTEXT(ctx) \
CCGLContext CC_GL_PRIV_prev_context___ = CCGLContextGetCurrent(); \
CCGLContextSetCurrent(ctx); \
CC_GL_ENTRY

#define CC_GL_EXIT_FROM_CONTEXT(ctx) \
CC_GL_EXIT; \
CCGLContextSetCurrent(CC_GL_PRIV_prev_context___)

#endif
