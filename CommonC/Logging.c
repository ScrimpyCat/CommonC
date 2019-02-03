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

#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <wchar.h>
#include "Logging.h"
#include "Assertion.h"
#include "MemoryAllocation.h"
#include "Types.h"
#include "Platform.h"
#include "ProcessInfo.h"
#include "SystemInfo.h"
#include "OrderedCollection.h"
#include "TypeCallbacks.h"
#include "CollectionEnumerator.h"

// Specify which system specific loggers to build with
//#define CC_EXCLUDE_ASL_LOGGER
//#define CC_EXCLUDE_OSL_LOGGER
//#define CC_EXCLUDE_SYSLOG_LOGGER

#if CC_PLATFORM_APPLE

#if !defined(CC_EXCLUDE_ASL_LOGGER) && (!defined(__has_include) || __has_include("asl.h"))
#define CC_ASL_LOGGER 1
#include <asl.h>
#endif

#if CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_10_12, CC_PLATFORM_IOS_10_0)
#if !defined(CC_EXCLUDE_OSL_LOGGER) && (!defined(__has_include) || __has_include("os/log.h"))
#define CC_OSL_LOGGER 1
#include <os/log.h>
#endif
#endif

#if CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_10_6, CC_PLATFORM_IOS_4_0)
#define CC_USE_GCD 1
#include <dispatch/dispatch.h>
#endif

#elif CC_PLATFORM_UNIX
#if !defined(CC_EXCLUDE_SYSLOG_LOGGER)
#define CC_SYSLOG_LOGGER 1
#include <syslog.h>
#endif
#endif

#if CC_PLATFORM_POSIX_COMPLIANT
#include <glob.h>
#include <sys/stat.h>
#include <pthread.h>
#endif

#if CC_PLATFORM_IOS
#include <CoreFoundation/CoreFoundation.h>
#endif

#if __BLOCKS__
#include <Block.h>
#endif

#if CC_PLATFORM_IOS
#define CC_VA_LIST_IS_POINTER 0 //need to get it ourselves
#elif CC_PLATFORM_OS_X
#define CC_VA_LIST_IS_POINTER 1 //implicit
#endif


const char * const CCTagEmergency = "EMERGENCY";
const char * const CCTagAlert = "ALERT";
const char * const CCTagCritical = "CRITICAL";
const char * const CCTagError = "ERROR";
const char * const CCTagWarning = "WARNING";
const char * const CCTagNotice = "NOTICE";
const char * const CCTagInfo = "INFO";
const char * const CCTagDebug = "DEBUG";



#define CC_IDENTIFIER_ "io.scrimpycat.common"
#define CC_FOLDER_ "CommonFramework/"
#define CC_EXTENSION_ ".log"

/// Set whether the default framework log file should be a new file (1) or if it should append onto the current (0)
#define CC_NEW_FRAMEWORK_LOG_FILE 1

static CCOrderedCollection FileList = NULL;

#if CC_USE_GCD
static dispatch_queue_t LogQueue;
#endif

#if CC_ASL_LOGGER
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
static aslclient Client;

static void LogMessageASL(aslmsg Msg)
{
    asl_send(Client, Msg);
    asl_free(Msg);
}
#pragma clang diagnostic pop
#endif

#if CC_OSL_LOGGER
typedef struct {
    os_log_t log;
    os_log_type_t type;
    const char *msg;
    _Bool destroy;
} CCOSLogContext;

static void LogMessageOSL(CCOSLogContext *Ctx)
{
    os_log_with_type(Ctx->log, Ctx->type, "%s", Ctx->msg);
    os_release(Ctx->log);
    
    if (Ctx->destroy)
    {
        CCFree((char*)Ctx->msg);
        CCFree(Ctx);
    }
}
#endif

#pragma mark - Logger Setup
static void Setup(void)
{
#if CC_USE_GCD
    LogQueue = dispatch_queue_create(NULL, DISPATCH_QUEUE_SERIAL);
#endif
    
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
                
                FSPath LogPath = FSPathCreateFromSystemPath(Path);
                
                if (FSManagerCreate(LogPath, FALSE) == FSOperationSuccess)
                {
                    FSHandle Handle;
                    if (FSHandleOpen(LogPath, FSHandleTypeWrite, &Handle) == FSOperationSuccess)
                    {
#if CC_NEW_FRAMEWORK_LOG_FILE
                        FSHandleRemove(Handle, FSManagerGetSize(Handle->path), FSBehaviourPreserveOffset);
#else
                        FSHandleSetOffset(Handle, FSManagerGetSize(Handle->path));
#endif
                        CCLogAddFile(Handle);
                    }
                }
                
                FSPathDestroy(LogPath);
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
    
    CFStringRef Path = CFURLCopyFileSystemPath(PathURL, kCFURLPOSIXPathStyle);
    CFRelease(PathURL);
    if (!Path)
    {
        CC_LOG_ERROR("Failed to create path. Won't be able to record logs locally to app.");
        return;
    }
    
    size_t Size = CFStringGetLength(Path) + 1;
    char *PathStr = NULL;
    CC_TEMP_Malloc(PathStr, sizeof(char) * Size,
                   CC_LOG_ERROR("Failed to create path. Won't be able to record logs locally to app.");
                   CFRelease(Path);
                   return;
                   );
    
    if (CFStringGetCString(Path, PathStr, Size, kCFStringEncodingASCII))
    {
        FSPath LogPath = FSPathCreateFromSystemPath(PathStr);
        
        if (FSManagerCreate(LogPath, FALSE) == FSOperationSuccess)
        {
            FSHandle Handle;
            if (FSHandleOpen(LogPath, FSHandleTypeWrite, &Handle) == FSOperationSuccess)
            {
#if CC_NEW_FRAMEWORK_LOG_FILE
                FSHandleRemove(Handle, FSManagerGetSize(Handle->path), FSBehaviourPreserveOffset);
#else
                FSHandleSetOffset(Handle, FSManagerGetSize(Handle->path));
#endif
                CCLogAddFile(Handle);
            }
        }
        
        FSPathDestroy(LogPath);
    }
    
    CFRelease(Path);
    CC_TEMP_Free(PathStr);
#endif
}

#if CC_ASL_LOGGER
static void ASLSetup(void)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    Client = asl_open(NULL, NULL, 0);
#pragma clang diagnostic pop
}
#endif

#pragma mark - Filters
typedef struct CCFilter {
    void *filter;
    _Bool isBlock;
    struct CCFilter *next;
} CCFilter;

static CCFilter *InputFilters = NULL, *SpecifierFilters = NULL, *MessageFilters = NULL;

#undef CCLogAddFilter
void CCLogAddFilter(CCLogFilterType Type, CCLogFilter Filter)
{
    if (Type & CCLogFilterInput)
    {
        CCFilter *NewFilter;
        CC_SAFE_Malloc(NewFilter, sizeof(CCFilter),
                       //Add error callback?
                       return;
                       );
        
        NewFilter->filter = Filter;
        NewFilter->isBlock = FALSE;
        NewFilter->next = InputFilters;
        InputFilters = NewFilter;
    }
    
    if (Type & CCLogFilterSpecifier)
    {
        CCFilter *NewFilter;
        CC_SAFE_Malloc(NewFilter, sizeof(CCFilter),
                       //Add error callback?
                       return;
                       );
        
        NewFilter->filter = Filter;
        NewFilter->isBlock = FALSE;
        NewFilter->next = SpecifierFilters;
        SpecifierFilters = NewFilter;
    }
    
    if (Type & CCLogFilterMessage)
    {
        CCFilter *NewFilter;
        CC_SAFE_Malloc(NewFilter, sizeof(CCFilter),
                       //Add error callback?
                       return;
                       );
        
        NewFilter->filter = Filter;
        NewFilter->isBlock = FALSE;
        NewFilter->next = MessageFilters;
        MessageFilters = NewFilter;
    }
}

#if __BLOCKS__
void CCLogAddFilterBlock(CCLogFilterType Type, CCLogFilterBlock Filter)
{
    if (Type & CCLogFilterInput)
    {
        CCFilter *NewFilter;
        CC_SAFE_Malloc(NewFilter, sizeof(CCFilter),
                       //Add error callback?
                       return;
                       );
        
        NewFilter->filter = Block_copy(Filter);
        NewFilter->isBlock = TRUE;
        NewFilter->next = InputFilters;
        InputFilters = NewFilter;
    }
    
    if (Type & CCLogFilterSpecifier)
    {
        CCFilter *NewFilter;
        CC_SAFE_Malloc(NewFilter, sizeof(CCFilter),
                       //Add error callback?
                       return;
                       );
        
        NewFilter->filter = Block_copy(Filter);
        NewFilter->isBlock = TRUE;
        NewFilter->next = SpecifierFilters;
        SpecifierFilters = NewFilter;
    }
    
    if (Type & CCLogFilterMessage)
    {
        CCFilter *NewFilter;
        CC_SAFE_Malloc(NewFilter, sizeof(CCFilter),
                       //Add error callback?
                       return;
                       );
        
        NewFilter->filter = Block_copy(Filter);
        NewFilter->isBlock = TRUE;
        NewFilter->next = MessageFilters;
        MessageFilters = NewFilter;
    }
}
#endif

#pragma mark - CCLogMessage functions
#define CC_MESSAGE_BATCH_SIZE 64

typedef struct CCLogMessageBuffer {
    char **message;
    size_t *length;
    int (*write)(const struct CCLogMessage *Msg, const char *String, size_t Length);
    int (*remove)(const struct CCLogMessage *Msg, size_t Length);
    size_t *bufferSize;
} CCLogMessageBuffer;

static int MessageBufferWrite(CCLogMessageBuffer *Msg, const char *String, size_t Length)
{
    if (*Msg->bufferSize - *Msg->length < Length)
    {
        *Msg->bufferSize += CC_MESSAGE_BATCH_SIZE + ((Length / CC_MESSAGE_BATCH_SIZE) * CC_MESSAGE_BATCH_SIZE);
        CC_SAFE_Realloc(*Msg->message, sizeof(char) * (*Msg->bufferSize + 1),
                        return -1;
                        );
    }
    
    strncpy(*Msg->message + *Msg->length, String, Length);
    (*Msg->message)[(*Msg->length += Length)] = 0;
    
    return 0;
}

static int MessageBufferRemove(CCLogMessageBuffer *Msg, size_t Length)
{
    if (Length > *Msg->length) Length = *Msg->length;
    
    (*Msg->message)[(*Msg->length -= Length)] = 0;
    
    return 0;
}

#pragma mark - Logger
int CCLogv(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char *FormatString, va_list Args)
{
    CCLogData LogData = {
        .filter = CCLogFilterInput,
        .option = &Option,
        .tag = Tag,
        .identifier = Identifier,
        .filename = Filename,
        .functionName = FunctionName,
        .line = Line
    };
    
    CCLogInputData InputData = {
        .format = FormatString,
#if CC_VA_LIST_IS_POINTER
        .args = (va_list*)Args
#else
        .args = (va_list*)&Args
#endif
    };
    for (CCFilter *CurrentFilter = InputFilters; CurrentFilter; CurrentFilter = CurrentFilter->next)
    {
#if __BLOCKS__
        if (CurrentFilter->isBlock) ((CCLogInputFilterBlock)CurrentFilter->filter)(&LogData, &InputData);
        else
#endif
            ((CCLogInputFilter)CurrentFilter->filter)(&LogData, &InputData);
    }
    
    
    if (Option == CCLogOptionNone) return 0;
    
    if (!Tag) Tag = CCTagInfo;
    
    size_t MessageSize = 0, Length = strlen(Tag) + 1 //"%s:"
    + (Filename? 1 + strlen(Filename) + 1 + 11 + 2 : 0) //"[%s:%d]:" Approx max number of digits for unsigned int: 10 + 1 (sign) TODO: add a CCNumberOfDigits() function in bit tricks
    + (FunctionName? strlen(FunctionName) + 1 : 0) //"%s:"
    + 2; //" " and null terminator
    char *Message = NULL;
    
    CCLogMessageBuffer MessageBuffer = {
        .message = &Message,
        .length = &Length,
        .write = (int(*)(const CCLogMessage*,const char*,size_t))MessageBufferWrite,
        .remove = (int(*)(const CCLogMessage*,size_t))MessageBufferRemove,
        .bufferSize = &MessageSize
    };
    
    if (SpecifierFilters)
    {
        MessageSize = CC_MESSAGE_BATCH_SIZE + ((Length / CC_MESSAGE_BATCH_SIZE) * CC_MESSAGE_BATCH_SIZE);
        CC_SAFE_Malloc(Message, sizeof(char) * (MessageSize + 1),
                       return -1;
                       );
        
        
        if ((Filename) && (FunctionName)) Length = snprintf(Message, Length, "%s:[%s:%d]:%s: ", Tag, Filename, Line, FunctionName);
        else if (Filename) Length = snprintf(Message, Length, "%s:[%s:%d]: ", Tag, Filename, Line);
        else if (FunctionName) Length = snprintf(Message, Length, "%s:%s: ", Tag, FunctionName);
        else  Length = snprintf(Message, Length, "%s: ", Tag);
        
        
        size_t BufferSize = 0;
        char *Buffer = NULL;
        const char *Specifier = FormatString;
        
        Specifier = strchr(Specifier, '%');
        const ptrdiff_t NextSpecLength = Specifier? (Specifier - FormatString) : strlen(FormatString);
        
        if (NextSpecLength > 0)
        {
            if (MessageSize - Length < NextSpecLength)
            {
                MessageSize += CC_MESSAGE_BATCH_SIZE + ((NextSpecLength / CC_MESSAGE_BATCH_SIZE) * CC_MESSAGE_BATCH_SIZE);
                CC_SAFE_Realloc(Message, sizeof(char) * (MessageSize + 1),
                                CC_SAFE_Free(Message);
                                return -1;
                                );
            }
            
            strncpy(&Message[Length], FormatString, NextSpecLength);
            Length += NextSpecLength;
        }
        
        LogData.filter = CCLogFilterSpecifier;
        while ((FormatString = Specifier))
        {
            CCLogSpecifierData SpecData = {
                .msg = (CCLogMessage*)&MessageBuffer,
                .specifier = Specifier,
#if CC_VA_LIST_IS_POINTER
                .args = (va_list*)Args
#else
                .args = (va_list*)&Args
#endif
            };
            for (CCFilter *CurrentFilter = SpecifierFilters; CurrentFilter && (FormatString == Specifier); CurrentFilter = CurrentFilter->next)
            {
#if __BLOCKS__
                if (CurrentFilter->isBlock) Specifier += ((CCLogSpecifierFilterBlock)CurrentFilter->filter)(&LogData, &SpecData);
                else
#endif
                    Specifier += ((CCLogSpecifierFilter)CurrentFilter->filter)(&LogData, &SpecData);
            }
            
            if (FormatString == Specifier)
            {
                Specifier = strchr(Specifier + 2, '%'); //%%
                const ptrdiff_t NextSpecLength = Specifier? (Specifier - FormatString) : strlen(FormatString);
                
                if (BufferSize < NextSpecLength)
                {
                    CC_SAFE_Realloc(Buffer, sizeof(char) * (NextSpecLength + 1),
                                    CC_SAFE_Free(Buffer);
                                    CC_SAFE_Free(Message);
                                    return -1;
                                    );
                    BufferSize = NextSpecLength;
                }
                
                strncpy(Buffer, FormatString, NextSpecLength);
                Buffer[NextSpecLength] = 0;
                
                va_list ArgsCopy;
                va_copy(ArgsCopy, Args);
                int Len = vsnprintf(NULL, 0, Buffer, ArgsCopy);
                va_end(ArgsCopy);
                
                if (MessageSize - Length < Len)
                {
                    MessageSize += CC_MESSAGE_BATCH_SIZE + ((Len / CC_MESSAGE_BATCH_SIZE) * CC_MESSAGE_BATCH_SIZE);
                    CC_SAFE_Realloc(Message, sizeof(char) * (MessageSize + 1),
                                    CC_SAFE_Free(Buffer);
                                    CC_SAFE_Free(Message);
                                    return -1;
                                    );
                }
                
                va_copy(ArgsCopy, Args);
                vsprintf(&Message[Length], Buffer, ArgsCopy);
                va_end(ArgsCopy);
                Length += Len;
                
                CCFormatSpecifierInfo Info;
                const char ConversionSpecifier = Buffer[CCGetFormatSpecifierInfo(Buffer, &Info)];
                switch (ConversionSpecifier)
                {
                    case 'd':
                    case 'i':
                    case 'o':
                    case 'u':
                    case 'x':
                    case 'X':
                        switch (Info.length)
                        {
                            case 'l':
                                va_arg(Args, unsigned long int);
                                break;
                                
                            case 'll':
                                va_arg(Args, unsigned long long int);
                                break;
                                
                            case 'j':
                                va_arg(Args, uintmax_t);
                                break;
                                
                            case 'z':
                                va_arg(Args, size_t);
                                break;
                                
                            case 't':
                                va_arg(Args, ptrdiff_t);
                                break;
                                
                            default:
                                va_arg(Args, unsigned int);
                                break;
                        }
                        break;
                        
                    case 'f':
                    case 'F':
                    case 'e':
                    case 'E':
                    case 'g':
                    case 'G':
                    case 'a':
                    case 'A':
                        switch (Info.length)
                        {
                            case 'L':
                                va_arg(Args, long double);
                                break;
                                
                            default:
                                va_arg(Args, double);
                                break;
                        }
                        break;
                        
                    case 'c':
                        switch (Info.length)
                        {
                            case 'l':
#if CC_COMPILER_MINGW
                                va_arg(Args, int);
#else
                                va_arg(Args, wint_t);
#endif
                                break;
                                
                            default:
                                va_arg(Args, unsigned int);
                                break;
                        }
                        break;
                        
                    case 's':
                    case 'p':
                    case 'n':
                        va_arg(Args, void *);
                        break;
                }
            }
            
            else
            {
                FormatString = Specifier;
                
                Specifier = strchr(Specifier, '%');
                const ptrdiff_t NextSpecLength = Specifier? (Specifier - FormatString) : strlen(FormatString);
                
                if (NextSpecLength > 0)
                {
                    if (MessageSize - Length < NextSpecLength)
                    {
                        MessageSize += CC_MESSAGE_BATCH_SIZE + ((NextSpecLength / CC_MESSAGE_BATCH_SIZE) * CC_MESSAGE_BATCH_SIZE);
                        CC_SAFE_Realloc(Message, sizeof(char) * (MessageSize + 1),
                                        CC_SAFE_Free(Buffer);
                                        CC_SAFE_Free(Message);
                                        return -1;
                                        );
                    }
                    
                    strncpy(&Message[Length], FormatString, NextSpecLength);
                    Length += NextSpecLength;
                }
            }
        }
        
        CC_SAFE_Free(Buffer);
        Message[Length] = 0;
    }
    
    else
    {
        va_list ArgsCopy;
        va_copy(ArgsCopy, Args);
        const size_t FormatLength = vsnprintf(NULL, 0, FormatString, ArgsCopy);
        va_end(ArgsCopy);
        
        
        CC_SAFE_Malloc(Message, sizeof(char) * (Length + FormatLength),
                       return -1;
                       );
        
        if ((Filename) && (FunctionName)) Length = snprintf(Message, Length, "%s:[%s:%d]:%s: ", Tag, Filename, Line, FunctionName);
        else if (Filename) Length = snprintf(Message, Length, "%s:[%s:%d]: ", Tag, Filename, Line);
        else if (FunctionName) Length = snprintf(Message, Length, "%s:%s: ", Tag, FunctionName);
        else  Length = snprintf(Message, Length, "%s: ", Tag);
        
        Length += vsnprintf(Message + Length, FormatLength + 1, FormatString, Args);
    }
    
    
    LogData.filter = CCLogFilterMessage;
    for (CCFilter *CurrentFilter = MessageFilters; CurrentFilter; CurrentFilter = CurrentFilter->next)
    {
#if __BLOCKS__
        if (CurrentFilter->isBlock) ((CCLogMessageFilterBlock)CurrentFilter->filter)(&LogData, (CCLogMessage*)&MessageBuffer);
        else
#endif
            ((CCLogMessageFilter)CurrentFilter->filter)(&LogData, (CCLogMessage*)&MessageBuffer);
    }
    
    enum {
        CCSystemLoggerPrinted = 0x80000000,
        
        CCSystemLoggerNone = 0,
        CCSystemLoggerASL = 1,
        CCSystemLoggerOSL = 2 | CCSystemLoggerPrinted,
        CCSystemLoggerSyslog = 3
    } Logged = CCSystemLoggerNone;
    
    if (Option & CCLogOptionOutputFile)
    {
#if CC_PLATFORM_POSIX_COMPLIANT
        static pthread_once_t OnceSetup = PTHREAD_ONCE_INIT;
        pthread_once(&OnceSetup, Setup);
#endif
        
#if CC_OSL_LOGGER || CC_ASL_LOGGER
        _Bool FreeIdentifier = FALSE;
        if (!Identifier)
        {
            const char *AppName = CCProcessCurrentStrippedName();
            if (AppName)
            {
                const size_t AppLength = strlen(AppName);
                
                if ((Identifier = CCMalloc(CC_DEFAULT_ALLOCATOR, sizeof(CC_IDENTIFIER_) + (sizeof(char) * AppLength), NULL, CC_DEFAULT_ERROR_CALLBACK)))
                {
                    FreeIdentifier = TRUE;
                    strncpy((char*)Identifier, CC_IDENTIFIER_, sizeof(CC_IDENTIFIER_) - 1);
                    strncpy((char*)(Identifier + sizeof(CC_IDENTIFIER_) - 1), AppName, AppLength);
                }
            }
        }
#endif
        
#if CC_OSL_LOGGER
        if ((!Logged) && (&os_log_create))
        {
            Logged = CCSystemLoggerOSL;
            
            os_log_t Log = Identifier ? os_log_create(Identifier, Tag) : os_retain(OS_LOG_DEFAULT);
            
            os_log_type_t LogType = OS_LOG_TYPE_DEFAULT; //custom
            if (Tag == CCTagEmergency) LogType = OS_LOG_TYPE_FAULT;
            else if (Tag == CCTagAlert) LogType = OS_LOG_TYPE_FAULT;
            else if (Tag == CCTagCritical) LogType = OS_LOG_TYPE_FAULT;
            else if (Tag == CCTagError) LogType = OS_LOG_TYPE_ERROR;
            else if (Tag == CCTagWarning) LogType = OS_LOG_TYPE_ERROR;
            else if (Tag == CCTagNotice) LogType = OS_LOG_TYPE_INFO;
            else if (Tag == CCTagInfo) LogType = OS_LOG_TYPE_INFO;
            else if (Tag == CCTagDebug) LogType = OS_LOG_TYPE_DEBUG;
            
#if CC_USE_GCD
            if (Option & CCLogOptionAsync)
            {
                if (LogQueue)
                {
                    CCOSLogContext *Context;
                    if ((Context = CCMalloc(CC_DEFAULT_ALLOCATOR, sizeof(CCOSLogContext), NULL, CC_DEFAULT_ERROR_CALLBACK)))
                    {
                        *Context = (CCOSLogContext){ .log = Log, .type = LogType, .msg = CCRetain(Message), .destroy = TRUE };
                    }
                    
                    dispatch_async_f(LogQueue, Context, (dispatch_function_t)LogMessageOSL);
                }
            }
            
            else
#endif
                LogMessageOSL(&(CCOSLogContext){ .log = Log, .type = LogType, .msg = Message, .destroy = FALSE });
        }
#endif
        
#if CC_ASL_LOGGER
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        if ((!Logged) && (&asl_new))
        {
#pragma clang diagnostic pop
            Logged = CCSystemLoggerASL;
            
            const char *LogLevelMessage = ASL_STRING_INFO; //CCTagInfo or custom
            if (Tag == CCTagEmergency) LogLevelMessage = ASL_STRING_EMERG;
            else if (Tag == CCTagAlert) LogLevelMessage = ASL_STRING_ALERT;
            else if (Tag == CCTagCritical) LogLevelMessage = ASL_STRING_CRIT;
            else if (Tag == CCTagError) LogLevelMessage = ASL_STRING_ERR;
            else if (Tag == CCTagWarning) LogLevelMessage = ASL_STRING_WARNING;
            else if (Tag == CCTagNotice) LogLevelMessage = ASL_STRING_NOTICE;
            else if (Tag == CCTagDebug) LogLevelMessage = ASL_STRING_DEBUG;
            
            static pthread_once_t Once = PTHREAD_ONCE_INIT;
            pthread_once(&Once, ASLSetup);
            
            
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
            aslmsg Msg = asl_new(ASL_TYPE_MSG);
            asl_set(Msg, ASL_KEY_MSG, Message);
            asl_set(Msg, ASL_KEY_LEVEL, LogLevelMessage);
            if (Identifier) asl_set(Msg, ASL_KEY_FACILITY, Identifier);
#pragma clang diagnostic pop
            
#if CC_USE_GCD
            if (Option & CCLogOptionAsync)
            {
                if (LogQueue) dispatch_async_f(LogQueue, Msg, (dispatch_function_t)LogMessageASL);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
                else asl_free(Msg);
#pragma clang diagnostic pop
            }
            
            else
#endif
                LogMessageASL(Msg);
        }
#elif CC_SYSLOG_LOGGER
        //TODO
#endif
        
#if CC_OSL_LOGGER || CC_ASL_LOGGER
        if (FreeIdentifier) CCFree((char*)Identifier);
#endif
        
        if ((FileList) && (Logged != CCSystemLoggerASL))
        {
            char Timestamp[16];
            strftime(Timestamp, sizeof(Timestamp), "%b %d %T", localtime(&(time_t){ time(NULL) }));
            
            const char *Hostname = CCHostCurrentName(), *ProcName = CCProcessCurrentStrippedName();
            const CCPid Pid = CCProcessCurrent();
            
            const size_t FormattedLength = snprintf(NULL, 0, "%s %s %s[%" PRIuPTR "]: ", Timestamp, Hostname, ProcName, Pid) + Length + 2;
            
            char *FormattedMessage = CCMalloc(CC_DEFAULT_ALLOCATOR, FormattedLength, NULL, CC_DEFAULT_ERROR_CALLBACK);
            if (FormattedMessage)
            {
                snprintf(FormattedMessage, FormattedLength, "%s %s %s[%" PRIuPTR "]: %s\n", Timestamp, Hostname, ProcName, Pid, Message);
                
                CC_COLLECTION_FOREACH(FSHandle, Handle, FileList)
                {
                    FSHandleWrite(Handle, FormattedLength - 1, FormattedMessage, FSBehaviourUpdateOffset);
                }
                
                CC_SAFE_Free(FormattedMessage);
            }
        }
    }
    
    if ((Option & CCLogOptionOutputPrint) && !(Logged & CCSystemLoggerPrinted)) fprintf(stderr, "%s\n", Message);
    
    CC_SAFE_Free(Message);
    
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

int CCLogCustom(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char *FormatString, ...)
{
    va_list Args;
    va_start(Args, FormatString);
    const int Length = CCLogv(Option, Tag, Identifier, Filename, FunctionName, Line, FormatString, Args);
    va_end(Args);
    
    return Length;
}

#pragma mark - Logger Outputs
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

#if CC_ASL_LOGGER
extern int asl_add_output(aslclient asl, int fd, const char *msg_fmt, const char *time_fmt, uint32_t text_encoding) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);
#endif


void CCLogAddFile(FSHandle File)
{
    if (!FileList) FileList = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall | CCCollectionHintHeavyEnumerating | CCCollectionHintConstantLength | CCCollectionHintConstantElements, sizeof(FSHandle), FSHandleDestructorForCollection);
    
    CCOrderedCollectionAppendElement(FileList, &File);
    
#if CC_PLATFORM_POSIX_COMPLIANT
    
#if CC_ASL_LOGGER
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wunreachable-code"
    int Fd = FSHandleGetFileDescriptor(File);
    
#if CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_10_9, CC_PLATFORM_IOS_7_0)
    if (&asl_add_output_file) asl_add_output_file(Client, Fd, ASL_MSG_FMT_BSD, ASL_TIME_FMT_LCL, ASL_FILTER_MASK_UPTO(ASL_LEVEL_DEBUG), ASL_ENCODE_SAFE);
    else
#endif
        if (&asl_add_output) asl_add_output(Client, Fd, ASL_MSG_FMT_BSD, ASL_TIME_FMT_LCL, ASL_ENCODE_SAFE);
#pragma clang diagnostic pop
#elif CC_SYSLOG_LOGGER
    //TODO: use syslog
#endif
    
#endif
}

size_t CCGetFormatSpecifierInfo(const char *Format, CCFormatSpecifierInfo *Info)
{
    memset(Info, 0, sizeof(CCFormatSpecifierInfo));
    
    const char *Start = Format;
    if (*Format != '%') Format--;
    
    int CurrentOption = 0;
    while (*++Format)
    {
        const char c = *Format;
        switch (CurrentOption)
        {
            case 0: //flags
                switch (c)
                {
                    case '-':
                        Info->options.flags = 1;
                        Info->flags.leftJustified = 1;
                        continue;
                    
                    case '+':
                        Info->options.flags = 1;
                        Info->flags.showPlusSign = 1;
                        continue;
                    
                    case ' ':
                        Info->options.flags = 1;
                        Info->flags.spacePrefixed = 1;
                        continue;
                    
                    case '#':
                        Info->options.flags = 1;
                        Info->flags.altForm = 1;
                        continue;
                    
                    case '0':
                        Info->options.flags = 1;
                        Info->flags.padWithZeros = 1;
                        continue;
                }
                
            case 1: //width
                CurrentOption = 1;
                if (isdigit(c))
                {
                    Info->options.width = 1;
                    Info->width.value = (Info->width.value * 10) + (c - '0');
                    break;
                }
                
                else if (c == '*')
                {
                    Info->options.width = 1;
                    Info->width.valueInArgs = 1;
                    CurrentOption = 2;
                    break;
                }
                
            case 2: //precision
                CurrentOption = 2;
                if (c == '.')
                {
                    Info->options.precision = 1;
                    break;
                }
                
                else if (Info->options.precision)
                {
                    if (isdigit(c))
                    {
                        Info->precision.value = (Info->precision.value * 10) + (c - '0');
                        break;
                    }
                    
                    else if (c == '*')
                    {
                        Info->precision.valueInArgs = 1;
                        CurrentOption = 3;
                        break;
                    }
                    
                    else if (c == '-')
                    {
                        Info->options.precision = 0;
                        while (isdigit(*++Format));
                    }
                }
                
            case 3: //length
                CurrentOption = 3;
                switch (c)
                {
                    case 'h':
                        Info->options.length = 1;
                        Info->length = (Info->length << 8) | 'h';
                        continue;
                    
                    case 'l':
                        Info->options.length = 1;
                        Info->length = (Info->length << 8) | 'l';
                        continue;
                    
                    case 'j':
                        Info->options.length = 1;
                        Info->length = 'j';
                        break;
                    
                    case 'z':
                        Info->options.length = 1;
                        Info->length = 'z';
                        break;
                    
                    case 't':
                        Info->options.length = 1;
                        Info->length = 't';
                        break;
                    
                    case 'L':
                        Info->options.length = 1;
                        Info->length = 'L';
                        break;
                    
                    default:
                        return Format - Start;
                }
                return (Format - Start) + 1;
        }
    }
    
    return Format - Start;
}
