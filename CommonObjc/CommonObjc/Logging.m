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

#import "Logging.h"
#undef CCLog

static size_t ObjectSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
    if (!strncmp(Data->specifier, "%@", 2))
    {
        NSString *Description = [va_arg(*Data->args, id) description];
        Data->msg->write(Data->msg, [Description UTF8String], [Description length]);
        
        return 2;
    }
    
    return 0;
}

static _Bool FilterAdded = FALSE;
CC_CONSTRUCTOR static void AddObjectSpecifier(void)
{
    if (!FilterAdded)
    {
        CCLogAddFilter(CCLogFilterSpecifier, ObjectSpecifier);
        FilterAdded = TRUE;
    }
}

int CCLogObjc(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, NSString * const FormatString, ...)
{
    if (!FilterAdded) AddObjectSpecifier();
    
    va_list Args;
    va_start(Args, FormatString);
    
    int Ret = CCLogv(Option, Tag, Identifier, Filename, FunctionName, Line, [FormatString UTF8String], Args);
    va_end(Args);
    
    return Ret;
}

int CCLogObjcCustom(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, NSString * const FormatString, ...)
{
    if (!FilterAdded) AddObjectSpecifier();
    
    va_list Args;
    va_start(Args, FormatString);
    
    int Ret = CCLogv(Option, Tag, Identifier, Filename, FunctionName, Line, [FormatString UTF8String], Args);
    va_end(Args);
    
    return Ret;
}
