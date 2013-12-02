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

#define CC_DEFAULT_ERROR_CALLBACK NULL

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Logging.h"
#include "MemoryAllocation.h"
#include "Types.h"
#include "Platform.h"
#include "ProcessInfo.h"
#include "SystemInfo.h"

#if CC_PLATFORM_APPLE
#define CC_ASL_LOGGER 1
#include <asl.h>

#if CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_10_6, CC_PLATFORM_IOS_4_0)
#define CC_USE_GCD 1
#include <dispatch/dispatch.h>
#endif

#elif CC_PLATFORM_UNIX
#define CC_SYSLOG_LOGGER 1
#include <syslog.h>
#endif

#if CC_PLATFORM_POSIX_COMPLIANT
#include <glob.h>
#include <sys/stat.h>
#include <pthread.h>
#endif

#if CC_PLATFORM_IOS
#include <CoreFoundation/CoreFoundation.h>
#endif


const char * const CCTagEmergency = "EMERGENCY";
const char * const CCTagAlert = "ALERT";
const char * const CCTagCritical = "CRITICAL";
const char * const CCTagError = "ERROR";
const char * const CCTagWarning = "WARNING";
const char * const CCTagNotice = "NOTICE";
const char * const CCTagInfo = "INFO";
const char * const CCTagDebug = "DEBUG";



#define CC_IDENTIFIER_ "com.common.framework."
#define CC_FOLDER_ "CommonFramework/"
#define CC_EXTENSION_ ".log"


static aslclient Client;

#if CC_USE_GCD
static dispatch_queue_t LogQueue;
static void LogMessage(aslmsg Msg)
{
    asl_send(Client, Msg);
    asl_free(Msg);
}
#endif


#if CC_ASL_LOGGER
static void ASLSetup(void)
{
#if CC_USE_GCD
    LogQueue = dispatch_queue_create(NULL, DISPATCH_QUEUE_SERIAL);
#endif
    
    Client = asl_open(NULL, NULL, 0);
    
#if CC_PLATFORM_OS_X
    const char *AppName = CCProcessCurrentName();
    if (AppName)
    {
        glob_t Glob;
        if (glob("~/Library/Logs/", GLOB_TILDE, NULL, &Glob) == 0)
        {
            if (Glob.gl_pathc)
            {
                const size_t LogPathLength = strlen(*Glob.gl_pathv);
                
                char Path[LogPathLength + (sizeof(CC_FOLDER_) - 1) + CC_PATH_NAME_LENGTH_MAX + sizeof(CC_EXTENSION_)];
                
                strncpy(Path, *Glob.gl_pathv, LogPathLength);
                strncpy(Path + LogPathLength, CC_FOLDER_, sizeof(CC_FOLDER_));
                
                mkdir(Path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); //assume success (either created or failed because already exists)
                
                const size_t PathTillNameLength = LogPathLength + sizeof(CC_FOLDER_) - 1;
                strncat(Path + PathTillNameLength, AppName, CC_PATH_NAME_LENGTH_MAX);
                strncat(Path + PathTillNameLength, CC_EXTENSION_, sizeof(CC_EXTENSION_) - 1);
                
                CCLogAddFile(Path);
            }
        }
        
        globfree(&Glob);
    }
#elif CC_PLATFORM_IOS
    CFURLRef HomeDir = CFCopyHomeDirectoryURL();
    if (!HomeDir)
    {
        CC_LOG_ERROR("Failed to obtain home directory. Won't be able to record logs locally to app.");
        return;
    }
    
    CFURLRef PathURL = CFURLCreateCopyAppendingPathComponent(kCFAllocatorDefault, HomeDir, CFSTR("Documents/common.log"), FALSE);
    CFRelease(HomeDir);
    if (!PathURL)
    {
        CC_LOG_ERROR("Failed to create path. Won't be able to record logs locally to app.");
        return;
    }
    
    CFStringRef Path = CFURLCopyPath(PathURL);
    CFRelease(PathURL);
    if (!Path)
    {
        CC_LOG_ERROR("Failed to create path. Won't be able to record logs locally to app.");
        return;
    }
    
    size_t Size = CFStringGetLength(Path) + 1;
    char *PathStr;
    CC_TEMP_Malloc(PathStr, sizeof(char) * Size,
                   CC_LOG_ERROR("Failed to create path. Won't be able to record logs locally to app.");
                   CFRelease(Path);
                   return;
                   );
    
    if (CFStringGetCString(Path, PathStr, Size, kCFStringEncodingASCII))
    {
        CCLogAddFile(PathStr);
    }
    
    CFRelease(Path);
    CC_TEMP_Free(PathStr);
#endif
}
#endif

int CCLogv(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char * const FormatString, va_list Args)
{
    if (Option == CCLogOptionNone) return 0;
    
#if CC_ASL_LOGGER
    const char *LogLevelMessage;
#endif
    if (!Tag)
    {
        Tag = CCTagInfo;
#if CC_ASL_LOGGER
        LogLevelMessage = ASL_STRING_INFO;
    }
    
    else
    {
        if (Tag == CCTagEmergency) LogLevelMessage = ASL_STRING_EMERG;
        else if (Tag == CCTagAlert) LogLevelMessage = ASL_STRING_ALERT;
        else if (Tag == CCTagCritical) LogLevelMessage = ASL_STRING_CRIT;
        else if (Tag == CCTagError) LogLevelMessage = ASL_STRING_ERR;
        else if (Tag == CCTagWarning) LogLevelMessage = ASL_STRING_WARNING;
        else if (Tag == CCTagNotice) LogLevelMessage = ASL_STRING_NOTICE;
        else if (Tag == CCTagDebug) LogLevelMessage = ASL_STRING_DEBUG;
        else LogLevelMessage = ASL_STRING_INFO; //CCTagInfo or custom
#endif
    }
    
    va_list ArgsCopy;
    va_copy(ArgsCopy, Args);
    const size_t FormatLength = vsnprintf(NULL, 0, FormatString, ArgsCopy);
    size_t Length = strlen(Tag) + 1 //"%s:"
    + (Filename? 1 + strlen(Filename) + 1 + 11 + 2 : 0) //"[%s:%d]:" Approx max number of digits for unsigned int: 10 + 1 (sign) TODO: add a CCNumberOfDigits() function in bit tricks
    + (FunctionName? strlen(FunctionName) + 1 : 0) //"%s:"
    + 2; //" " and null terminator
    va_end(ArgsCopy);
    
    
    char *Message;
    CC_TEMP_Malloc(Message, Length + FormatLength,
                   return -1;
                   );
    
    if ((Filename) && (FunctionName)) Length = snprintf(Message, Length, "%s:[%s:%d]:%s: ", Tag, Filename, Line, FunctionName);
    else if (Filename) Length = snprintf(Message, Length, "%s:[%s:%d]: ", Tag, Filename, Line);
    else if (FunctionName) Length = snprintf(Message, Length, "%s:%s: ", Tag, FunctionName);
    else  Length = snprintf(Message, Length, "%s: ", Tag);
    
    Length += vsnprintf(Message + Length, FormatLength + 1, FormatString, Args);
    
    if (Option & CCLogOptionOutputFile)
    {
#if CC_ASL_LOGGER
        static pthread_once_t Once = PTHREAD_ONCE_INIT;
        pthread_once(&Once, ASLSetup);
        
        
        aslmsg Msg = asl_new(ASL_TYPE_MSG);
        asl_set(Msg, ASL_KEY_MSG, Message);
        asl_set(Msg, ASL_KEY_LEVEL, LogLevelMessage);
        
        _Bool FreeIdentifier = FALSE;
        if (!Identifier)
        {
            const char *AppName = CCProcessCurrentStrippedName();
            if (AppName)
            {
                const size_t AppLength = strlen(AppName);
                
                if ((Identifier = CCMalloc(CC_DEFAULT_ALLOCATOR, sizeof(CC_IDENTIFIER_) + AppLength, NULL, NULL)))
                {
                    FreeIdentifier = TRUE;
                    strncpy((char*)Identifier, CC_IDENTIFIER_, sizeof(CC_IDENTIFIER_) - 1);
                    strncpy((char*)(Identifier + sizeof(CC_IDENTIFIER_) - 1), AppName, AppLength);
                }
            }
        }
        
        if (Identifier)
        {
            asl_set(Msg, ASL_KEY_FACILITY, Identifier);
            if (FreeIdentifier) CCFree((char*)Identifier);
        }
        
#if CC_USE_GCD
        if (Option & CCLogOptionAsync)
        {
            if (LogQueue) dispatch_async_f(LogQueue, Msg, (dispatch_function_t)LogMessage);
        }
        
        else
#endif
        {
            asl_send(Client, Msg);
            asl_free(Msg);
        }
#elif CC_SYSLOG_LOGGER
        //TODO
#else
        //TODO
#endif
    }
    
    if (Option & CCLogOptionOutputPrint) fprintf(stderr, "%s\n", Message);
    
    CC_TEMP_Free(Message);
    
    return (int)Length;
}

int CCLog(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char * const FormatString, ...)
{
    va_list Args;
    va_start(Args, FormatString);
    const int Length = CCLogv(Option, Tag, Identifier, Filename, FunctionName, Line, FormatString, Args);
    va_end(Args);
    
    return Length;
}

#if CC_ASL_LOGGER && !CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_10_9, CC_PLATFORM_IOS_7_0)
/*
 Private API: Used as we want to avoid the <Level> from being logged (want to use our own).

 Filed a bug report. rdar://14680976
 Viewable: http://openradar.appspot.com/radar?id=5779342353235968
 Resolved: Exposed functionality in Mac OS X 10.9 SDK and iOS 7.0 SDK.
 */

//From: http://www.opensource.apple.com/source/Libc/Libc-825.26/gen/asl_core.h
#define ASL_ENCODE_NONE		0
#define ASL_ENCODE_SAFE		1
#define ASL_ENCODE_ASL		2
#define ASL_ENCODE_XML		3


//From: http://www.opensource.apple.com/source/Libc/Libc-825.26/gen/asl_private.h
#define ASL_MSG_FMT_RAW "raw"
#define ASL_MSG_FMT_STD "std"
#define ASL_MSG_FMT_BSD "bsd"
#define ASL_MSG_FMT_XML "xml"
#define ASL_MSG_FMT_MSG "msg"

#define ASL_TIME_FMT_SEC "sec"
#define ASL_TIME_FMT_UTC "utc"
#define ASL_TIME_FMT_LCL "lcl"
#endif

extern int asl_add_output(aslclient asl, int fd, const char *msg_fmt, const char *time_fmt, uint32_t text_encoding) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);


void CCLogAddFile(const char *File)
{
#if CC_PLATFORM_POSIX_COMPLIANT
    FILE *fp = fopen(File, "a");
    int Fd = fileno(fp);
    
#if CC_ASL_LOGGER
#if CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_10_9, CC_PLATFORM_IOS_7_0)
    if (asl_add_output_file) asl_add_output_file(Client, Fd, ASL_MSG_FMT_BSD, ASL_TIME_FMT_LCL, ASL_FILTER_MASK_UPTO(ASL_LEVEL_DEBUG), ASL_ENCODE_SAFE);
    else
#endif 
        asl_add_output(Client, Fd, ASL_MSG_FMT_BSD, ASL_TIME_FMT_LCL, ASL_ENCODE_SAFE);
#elif CC_SYSLOG_LOGGER
    //TODO: use syslog
#else
    //TODO: create absolute fallback system and just manually write to files
#endif
    
#endif
}
