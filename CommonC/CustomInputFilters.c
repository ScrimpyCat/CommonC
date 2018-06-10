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

#include <string.h>
#include "Logging_Private.h"
#include "CustomInputFilters.h"
#include "MemoryAllocation.h"

static size_t PathCount = 0;
static struct { char *path; size_t length; } *Paths = NULL;
void CCFileFilterInputAddPath(const char *Path)
{
    CC_SAFE_Realloc(Paths, sizeof(typeof(*Paths)) * ++PathCount,
                    PathCount--;
                    CC_LOG_ERROR("Failed to add path: %s", Path);
                    return;
                    );
    
    const size_t Length = strlen(Path);
    CC_SAFE_Malloc(Paths[PathCount - 1].path, sizeof(char) * (Length + 1),
                   PathCount--;
                   CC_LOG_ERROR("Failed to add path: %s", Path);
                   return;
                   );
    
    strcpy(Paths[PathCount - 1].path, Path);
    Paths[PathCount - 1].length = Length;
}

size_t CCFileFilterInput(const CCLogData *LogData, const CCLogInputData *Data)
{
    for (size_t Loop = 0; Loop < PathCount; Loop++)
    {
        const size_t Index = (PathCount - 1) - Loop;
        const size_t Length = Paths[Index].length;
        if (!strncmp(Paths[Index].path, LogData->filename, Length))
        {
            CCLogv(*LogData->option, LogData->tag, LogData->identifier, LogData->filename + Length, LogData->functionName, LogData->line, Data->format, *Data->args);
            *LogData->option = CCLogOptionNone;
            break;
        }
    }
    
    return 0;
}
