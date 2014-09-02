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

#import "Default_Private.h"
#import "Debug.h"
#import "Defined.h"
#import "Version.h"
#import "Calling.h"
#import <CommonC/Assertion.h>
#import <CommonC/MemoryAllocation.h>
#import <Foundation/Foundation.h>

static const char * const ErrorString[] = {
    "GL_INVALID_ENUM",
    "GL_INVALID_VALUE",
    "GL_INVALID_OPERATION",
    "GL_STACK_OVERFLOW",
    "GL_STACK_UNDERFLOW",
    "GL_OUT_OF_MEMORY",
    "GL_INVALID_FRAMEBUFFER_OPERATION_EXT"
};

const char *CCGLErrorString(GLenum ErrorType)
{
    CCAssertLog((ErrorType == GL_NO_ERROR)
                || (ErrorType == GL_INVALID_ENUM)
                || (ErrorType == GL_INVALID_VALUE)
                || (ErrorType == GL_INVALID_OPERATION)
#if GL_STACK_OVERFLOW
                || (ErrorType == GL_STACK_OVERFLOW)
#endif
#if GL_STACK_UNDERFLOW
                || (ErrorType == GL_STACK_UNDERFLOW)
#endif
                || (ErrorType == GL_OUT_OF_MEMORY)
#if GL_INVALID_FRAMEBUFFER_OPERATION_EXT
                || (ErrorType == GL_INVALID_FRAMEBUFFER_OPERATION_EXT)
#endif
                , "ErrorType should be a valid GL error.");
    
    return ErrorType == GL_NO_ERROR ? "GL_NO_ERROR" : ErrorString[ErrorType - GL_INVALID_ENUM];
}

void *CCGLErrorCheck(GLenum ErrorType, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallback ErrorCallback)
{
    if (ErrorType != GL_NO_ERROR)
    {
        if (ErrorCallback) return ErrorCallback((CCFunctionData*)&(CCFunctionDataGLError){
            .indicator = CCGLErrorCheck,
            .info = CCGLErrorString(ErrorType),
            .filename = Filename,
            .functionName = FunctionName,
            .line = Line,
            .error = ErrorType
        }, CallbackData);
    }
    
    return NULL;
}

NSString *CCGLGetObjectLabel(GLenum type, GLuint object)
{
    CC_GL_SETUP;
    
#if CC_GL_SUPPORT_DEBUG_LABEL
    if (!glGetObjectLabel) return nil;
    
    GLsizei Length;
    glGetObjectLabel(type, object, 0, &Length, NULL); CC_GL_CHECK();
    
    char *Label = NULL;
    CC_TEMP_Malloc(Label, Length + 1,
                   return nil;
                   );
    
    glGetObjectLabel(type, object, Length + 1, NULL, Label); CC_GL_CHECK();
    NSString *ObjectLabel = [NSString stringWithUTF8String: Label];
    CC_TEMP_Free(Label);
    
    return ObjectLabel;
#else
    return nil;
#endif
}
