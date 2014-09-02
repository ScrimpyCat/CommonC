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

#ifndef CommonGL_Debug_h
#define CommonGL_Debug_h

#import <CommonC/Extensions.h>
#import <CommonGL/Defined.h>
#import <CommonGL/Extensions.h>
#import <CommonC/Logging.h>
#import <CommonC/DebugTypes.h>

@class NSString;

typedef struct {
    CCFunctionIndicator indicator;
    const char *info;
    const char *filename, *functionName;
    int line;
    GLenum error;
} CCFunctionDataGLError;


const char *CCGLErrorString(GLenum ErrorType);
void *CCGLErrorCheck(GLenum ErrorType, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallback ErrorCallback);
NSString *CCGLGetObjectLabel(GLenum type, GLuint object);


#if CC_NO_GL_DEBUG
#define CC_NO_GL_ERROR 1
#define CC_NO_GL_MARKER 1
#define CC_NO_GL_LABEL 1
#endif


#ifndef CC_GL_DEFAULT_ERROR_CALLBACK
#define CC_GL_DEFAULT_ERROR_CALLBACK CC_DEFAULT_ERROR_CALLBACK
#endif

#if CC_NO_GL_ERROR
#define CC_GL_CHECK()
#else
#define CC_GL_CHECK() CCGLErrorCheck(glGetError(), __FILE__, __func__, __LINE__, NULL, CC_GL_DEFAULT_ERROR_CALLBACK)
#endif

#if CC_NO_GL_MARKER || !CC_GL_SUPPORT_DEBUG_MARKER
#define CC_GL_INSERT_GROUP_MARKER(marker)
#define CC_GL_PUSH_GROUP_MARKER(marker)
#define CC_GL_POP_GROUP_MARKER()
#else
#define CC_GL_INSERT_GROUP_MARKER(marker) glInsertEventMarker(0, marker); CC_GL_CHECK();
#define CC_GL_PUSH_GROUP_MARKER(marker) glPushGroupMarker(0, marker); CC_GL_CHECK();
#define CC_GL_POP_GROUP_MARKER() glPopGroupMarker(); CC_GL_CHECK();
#endif

#if CC_NO_GL_LABEL || !CC_GL_SUPPORT_DEBUG_LABEL
#define CC_GL_LABEL_OBJECT(type, object, label)
#define CC_GL_GET_OBJECT_LABEL(type, object)
#else
#define CC_GL_LABEL_OBJECT(type, object, label) glObjectLabel(CC_GL_FEATURE_DEBUG_LABEL_REMAP(type), object, 0, label); CC_GL_CHECK();
#define CC_GL_GET_OBJECT_LABEL(type, object) CCGLGetObjectLabel(CC_GL_FEATURE_DEBUG_LABEL_REMAP(type), object);
#endif

#endif
