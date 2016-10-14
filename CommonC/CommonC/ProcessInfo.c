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

#include "ProcessInfo.h"
#include "File.h"
#include <string.h>
#include <ctype.h>

#if CC_PLATFORM_OS_X //|| CC_PLATFORM_IOS
#define CC_USE_LIBPROC 1
#include <libproc.h>
#include <mach/mach.h>
#endif


const char *CCProcessCurrentPath(void)
{
#if CC_USE_LIBPROC
    
    static char ProcName[PROC_PIDPATHINFO_MAXSIZE] = { 0 };
    if (ProcName[0] == 0)
    {
        if (!proc_pidpath((pid_t)CCProcessCurrent(), ProcName, sizeof(ProcName))) return NULL;
    }
    
    return ProcName;
    
#else
    return NULL;
#endif
}

const char *CCProcessCurrentName(void)
{
    static const char *Name = NULL;
    if (Name == NULL)
    {
        const char *Path = CCProcessCurrentPath();
        if (Path)
        {
#if CC_PLATFORM_POSIX_COMPLIANT
            size_t ComponentLength;
            const char *LastComponent = CCLastComponent(Path, &ComponentLength, '/');
            if (LastComponent)
            {
                if (ComponentLength == 0) Name = LastComponent;
                else if (ComponentLength < CC_PATH_NAME_LENGTH_MAX)
                {
                    static char CopiedName[CC_PATH_NAME_LENGTH_MAX] = { 0 };
                    strncpy(CopiedName, LastComponent, ComponentLength);
                    Name = CopiedName;
                }
            }
#endif
        }
    }
    
    return Name;
}

const char *CCProcessCurrentStrippedName(void)
{
    static char Name[CC_PATH_NAME_LENGTH_MAX] = { 0 };
    if (Name[0] == 0)
    {
        const char *OriginalName = CCProcessCurrentName();
        if (OriginalName)
        {
            size_t NameLength = 0;
            for ( ; *OriginalName; OriginalName++) if (isalnum(*OriginalName)) Name[NameLength++] = *OriginalName;
            Name[NameLength] = 0;
        }
    }
    
    return Name;
}

CCPid CCProcessCurrent(void)
{
#if CC_PLATFORM_POSIX_COMPLIANT
    return (uintptr_t)getpid();
#endif
    return 0;
}

const char *CCHostCurrentName(void)
{
#if CC_PLATFORM_POSIX_COMPLIANT
    
#if HOST_NAME_MAX
    static char HostName[HOST_NAME_MAX + 1] = { 0 };
#elif _POSIX_HOST_NAME_MAX
    static char HostName[_POSIX_HOST_NAME_MAX + 1] = { 0 };
#else
    static char HostName[256] = { 0 };
#endif
    if (HostName[0] == 0)
    {
        if (gethostname(HostName, sizeof(HostName))) return NULL;
    }
    
    return HostName;
    
#else
    return NULL;
#endif
}
