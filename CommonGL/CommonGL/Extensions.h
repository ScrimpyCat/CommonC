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

#ifndef CommonGL_Extensions_h
#define CommonGL_Extensions_h

#import <CommonGL/Defined.h>
#import <CommonGL/Version.h>

#pragma mark - Vertex Array Object
#if GL_APPLE_vertex_array_object
#define CC_GL_SUPPORT_VERTEX_ARRAY_OBJECT 1

#define GL_VERTEX_ARRAY_BINDING GL_VERTEX_ARRAY_BINDING_APPLE

#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#define glIsVertexArray glIsVertexArrayAPPLE

#elif GL_OES_vertex_array_object
#define CC_GL_SUPPORT_VERTEX_ARRAY_OBJECT 1

#define GL_VERTEX_ARRAY_BINDING GL_VERTEX_ARRAY_BINDING_OES

#define glGenVertexArrays glGenVertexArraysOES
#define glBindVertexArray glBindVertexArrayOES
#define glDeleteVertexArrays glDeleteVertexArraysOES
#define glIsVertexArray glIsVertexArrayOES

#elif CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_3_0, CC_OPENGL_ES_VERSION_3_0)
#define CC_GL_SUPPORT_VERTEX_ARRAY_OBJECT 1
#endif

#pragma mark - Debug Label
#if GL_EXT_debug_label
#define CC_GL_SUPPORT_DEBUG_LABEL 1

#if defined(GL_VERTEX_ARRAY_OBJECT_EXT) && defined(GL_VERTEX_ARRAY)
#define CC_GL_FEATURE_DEBUG_LABEL_MAPPING \
(CCGLEnumMapping[1]){ \
    { GL_VERTEX_ARRAY, GL_VERTEX_ARRAY_OBJECT_EXT } \
}
#else
#define CC_GL_FEATURE_DEBUG_LABEL_MAPPING (CCGLEnumMapping[0]){}
#endif


#ifdef GL_BUFFER_OBJECT_EXT
#define GL_BUFFER GL_BUFFER_OBJECT_EXT
#endif

#ifdef GL_SHADER_OBJECT_EXT
#define GL_SHADER GL_SHADER_OBJECT_EXT
#endif

#ifdef GL_PROGRAM_OBJECT_EXT
#define GL_PROGRAM GL_PROGRAM_OBJECT_EXT
#endif

#if defined(GL_VERTEX_ARRAY_OBJECT_EXT) && !defined(GL_VERTEX_ARRAY)
#define GL_VERTEX_ARRAY GL_VERTEX_ARRAY_OBJECT_EXT
#endif

#ifdef GL_QUERY_OBJECT_EXT
#define GL_QUERY GL_QUERY_OBJECT_EXT
#endif

#ifdef GL_PROGRAM_PIPELINE_OBJECT_EXT
#define GL_PROGRAM_PIPELINE GL_PROGRAM_PIPELINE_OBJECT_EXT
#endif

#define CC_GL_FEATURE_DEBUG_LABEL_REMAP(enum) CCGLEnumRemap(enum, CC_GL_FEATURE_DEBUG_LABEL_MAPPING, sizeof(CC_GL_FEATURE_DEBUG_LABEL_MAPPING) / sizeof(CCGLEnumMapping))

#define glObjectLabel glLabelObjectEXT
#define glGetObjectLabel glGetObjectLabelEXT

#elif CC_GL_VERSION_MIN_REQUIRED(CC_OPENGL_VERSION_4_3, CC_OPENGL_ES_VERSION_NA)
#define CC_GL_SUPPORT_DEBUG_LABEL 1
#endif

#pragma mark - Debug Marker
#if GL_EXT_debug_marker
#define CC_GL_SUPPORT_DEBUG_MARKER 1

#define glInsertEventMarker glInsertEventMarkerEXT
#define glPushGroupMarker glPushGroupMarkerEXT
#define glPopGroupMarker glPopGroupMarkerEXT
#endif

#endif
