/*
 *  Copyright (c) 2013, Stefan Johnson
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

#include "File.h"
#include <stdio.h>
#include <string.h>
#include "Platform.h"
#include "Types.h"

#if CC_PLATFORM_POSIX_COMPLIANT
#include <sys/stat.h>
#endif


const char *CCLastComponent(const char *Path, size_t *Length, char Separator)
{
    /*
     Doesn't attempt to achieve any validity in the path, simply finds the last component following these rules:
     Path structure: /blah/last (where "last" is the last component if the Separator is '/')
     
     If it can locate a last component with great flexibility (e.g "////last////", "last", "/////last", etc. will all show "last" as the last component) the last
     component. Then it will return the starting point of it, and if it has a fixed length (won't end with a null terminator because there's '/') it will set the
     length to that value. Otherwise length will be set to 0 to indicate till null terminator.
     
     If it cannot locate a last component that is because it is either a NULL pointer, points to a null terminator, or only contains '/' then it returns NULL.
     */
    
    if (!Path) return NULL;
    
    *Length = 0;
    
    const char *LastComponent = strrchr(Path, Separator);
    if (!LastComponent) return *Path != 0 ? Path : NULL;
    else if (LastComponent[1] != 0) return LastComponent + 1;
    
    while ((--LastComponent > Path) && (*LastComponent == Separator));
    
    const char *End = LastComponent;
    
    while ((--LastComponent > Path) && (*LastComponent != Separator));
    
    if (LastComponent < Path) return NULL;
    
    
    *Length = End - (LastComponent == Path? LastComponent - 1 : LastComponent++);
    
    return LastComponent;
}
