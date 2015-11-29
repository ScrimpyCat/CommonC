/*
 *  Copyright (c) 2015, Stefan Johnson
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

#define CC_DEFAULT_ALLOCATOR CC_ALIGNED_ALLOCATOR(8)

#include "PathComponent.h"
#include "MemoryAllocation.h"
#include "Logging.h"

FSPathComponent FSPathComponentCreate(FSPathComponentType Type, const char *String)
{
    FSPathComponent Component = Type;
    
    if (String)
    {
        char *Str;
        CC_SAFE_Malloc(Str, sizeof(char) * (strlen(String) + 1),
                       CC_LOG_ERROR("Failed to create path component due to allocation failure. Allocation size: %zu", sizeof(char) * (strlen(String) + 1));
                       return (FSPathComponent)FSPathComponentTypeInvalid;
                       );
        
        strcpy(Str, String);
        
        Component |= (FSPathComponent)Str;
    }
    
    return Component;
}

void FSPathComponentDestroy(FSPathComponent Component)
{
    void *Ptr = (void*)FSPathComponentGetString(Component);
    CC_SAFE_Free(Ptr);
}

FSPathComponent FSPathComponentCopy(FSPathComponent Component)
{
    return FSPathComponentCreate(FSPathComponentGetType(Component), FSPathComponentGetString(Component));
}
