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
#import "Portability.h"
#import <CommonC/Platform.h>
#import <CommonC/Types.h>

#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#import <dlfcn.h>
#endif

GLenum CCGLEnumRemap(GLenum Value, CCGLEnumMapping *Mapping, size_t MapTableSize)
{
    for (size_t Loop = 0; Loop < MapTableSize; Loop++)
    {
        if (Value == Mapping[Loop].from) return Mapping[Loop].to;
    }
    
    return Value;
}

void *CCGLFunction(const char *Name)
{
    void *Func = NULL;
    
#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
    Func = dlsym(RTLD_NEXT, Name);
#endif
    
    return Func;
}

_Bool CCGLFunctionBatch(const char * const *Names, size_t Count, void **Functions, _Bool StopOnFailure)
{
#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
    void *ImageGL = RTLD_NEXT;
    
    _Bool Found = TRUE;
    if (StopOnFailure)
    {
        for (size_t Loop = 0; Loop < Count; Loop++) if (!(Found &= (Functions[Loop] = dlsym(ImageGL, Names[Loop])) != NULL)) break;
    }
    
    else for (size_t Loop = 0; Loop < Count; Loop++) Found &= (Functions[Loop] = dlsym(ImageGL, Names[Loop])) != NULL;
    
    return Found;
#else
    return FALSE;
#endif
}

_Bool CCGLFunctionBatchPtr(const char * const *Names, size_t Count, void ***Functions, _Bool StopOnFailure)
{
#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
    void *ImageGL = RTLD_NEXT;
    
    _Bool Found = TRUE;
    if (StopOnFailure)
    {
        for (size_t Loop = 0; Loop < Count; Loop++) if (!(Found &= (*Functions[Loop] = dlsym(ImageGL, Names[Loop])) != NULL)) break;
    }
    
    else for (size_t Loop = 0; Loop < Count; Loop++) Found &= (*Functions[Loop] = dlsym(ImageGL, Names[Loop])) != NULL;
    
    return Found;
#else
    return FALSE;
#endif
}
