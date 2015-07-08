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


#pragma mark Documentation
/*
 Pre-include options:
 CC_NO_LOG: Disable all logging from macros. Virtually turns them all into a no-op.
 CC_NO_LOG_##tag: Disables logging of a particular tag through its macro usage (turned into no-op).
 { CC_NO_LOG_EMERGENCY, CC_NO_LOG_ALERT, CC_NO_LOG_CRITICAL, CC_NO_LOG_ERROR, CC_NO_LOG_WARNING, CC_NO_LOG_NOTICE, CC_NO_LOG_INFO, CC_NO_LOG_DEBUG }
 
 Options (either pre-include or undef and redefine):
 CC_LOG_OPTION: Specify the logging options for all logging macros.
 CC_LOG_##tag##_OPTION: Specify the logging options for that particular tag through its macro usage. Can be overriden by modifying CC_LOG_OPTION.
 CC_LOG_IDENTIFIER: Specify the identifier for all logging macros unless their specific is set.
 CC_LOG_##tag##_IDENTIFIER: Specify the identifier for that particular tag through its macro usage. Will override CC_LOG_IDENTIFIER when set.
 CC_LOG_FROM_FILE: Specify the file (typically __FILE__) or NULL to avoid adding the file name to the logging message.
 CC_LOG_FROM_FUNCTION: Specify the function (typically __func__) or NULL to avoid adding the function name to the logging message.
 
 Types:
 enum CCLoggingOption - A bit mask indicating what type of logging options should be used.
    CCLogOptionNone - No options. The logger will return, not logging anything.
    CCLogOptionOutputPrint - The logger will print the log message to stderr.
    CCLogOptionOutputFile - The logger will write the log message to the appropriate files.
    CCLogOptionOutputAll - A convenience option, specifies all options to be used.
    CCLogOptionAsync - Writes to file asynchronously.
 
 enum CCLogFilterType - The filter type of the function.
    CCLogFilterInput - Data field is CCLogInputData, return value is ignored. This filter is called at the beginning of CCLogv. The main usage is for having filters that apply to one of the prefixed fields (e.g. shortening the filename). This filter can only affect the current option, otherwise to do more it's suggested to call CCLog again with the modified inputs.
    CCLogFilterSpecifier - Data field is CCLogSpecifierData, return value is the amount to increment the specifier string by (e.g. usually the size of the specifier being matched if it is found). The filter takes affect when formatting the input. The main usage is to create custom (or override) format specifiers.
    CCLogFilterMessage - Data field is CCLogMessageData, return value is ignored. This filter takes affect at the end after the message has been formatted, but prior to logging. The main usage for this is to modify the final message, or to send it to any other loggers.
 
 Functions:
 CCLog() - Logs the message. The logging message formatted output is: "TAG:[file:line]:function: message" where "[file:line]:" and "function:" are optional.
    Return:
    int - A value indicating how many characters of the log message were successfully logged. Expect either 0 (no characters from the message) or 
          N the message's length.
    Arguments:
    CCLoggingOption Option - Options specifying how the logging should be done.
    const char *Tag - The tag part of the log message, it is used to highlight the message (make it easily identifiable at a glance). A tag can be 
                      anything you choose. However if it is one of the CCTag# variables on certain systems it will belong under that group of logging
                      message types. If you use a custom string then it will specify that message log type as Info.
    const char *Identifier - An identifier is another way of possibly grouping log messages. It is suggested to use reverse DNS format (however that 
                             is really only the case when targeting an Apple platform). If supported it will be used as the facility part of a logger,
                             otherwise will simply be a hash tag at the end of the message.
    const char *Filename - The source filename or path. If NULL will drop the "[file:line]:".
    const char *FunctionName - The function name. If NULL will drop the "function:".
    unsigned int Line - The line number in that source.
    const char *FormatString - The main message/format specifier string. It follows printf style format string conversions.
    ... - The arguments referenced through the FormatString.
 CCLogAddFile() - Add a file to log messages to.
    Arguments:
    const char *File - A path and name of the file to be used. If no such file exists it will try create one. If the path does not exist it try will 
                       make one.
 CCLogAddFilter() - Add a filter to be applied to calls made using CCLog/CCLogv. Filters can be used to restructure log messages, add custom format specifiers, pass messages to other systems or other loggers, etc.
    Arguments:
    CCLogFilterType Type - The type of this filter (may be multiple).
    CCLogFilter Filter - The filter (either function or if supported block). See CCLogFilterType definition for filter guidlines.
 
 
 
 Constants:
 CCTagEmergency - The tag to identify with an emergency level log message. It will log: "EMERGENCY".
 CCTagAlert - The tag to identify with an alert level log message. It will log: "ALERT"
 CCTagCritical - The tag to identify with an critical level log message. It will log: "CRITICAL"
 CCTagError - The tag to identify with an error level log message. It will log: "ERROR"
 CCTagWarning - The tag to identify with an warning level log message. It will log: "WARNING"
 CCTagNotice - The tag to identify with an notice level log message. It will log: "NOTICE"
 CCTagInfo - The tag to identify with an info level log message. It will log: "INFO"
 CCTagDebug - The tag to identify with an debug level log message. It will log: "DEBUG"
 */

#pragma mark -

#ifndef CommonC_Logging_h
#define CommonC_Logging_h

#include <CommonC/Extensions.h>
#include <CommonC/Generics.h>
#include <CommonC/Hacks.h>
#include <stdarg.h>


#pragma mark - Constants
extern const char * const CCTagEmergency;
extern const char * const CCTagAlert;
extern const char * const CCTagCritical;
extern const char * const CCTagError;
extern const char * const CCTagWarning;
extern const char * const CCTagNotice;
extern const char * const CCTagInfo;
extern const char * const CCTagDebug;


#pragma mark - Types
typedef enum {
    CCLogOptionNone = 0,
    //Output
    CCLogOptionOutputPrint = (1 << 0),
    CCLogOptionOutputFile = (1 << 1),
    CCLogOptionOutputAll = CCLogOptionOutputPrint | CCLogOptionOutputFile,
    
    //Asynchronous file output
    CCLogOptionAsync = (1 << 8) //Only available when GCD is supported
} CCLoggingOption;

typedef enum {
    CCLogFilterInput = (1 << 0),
    CCLogFilterSpecifier = (1 << 1),
    CCLogFilterMessage = (1 << 2)
} CCLogFilterType;

typedef struct {
    CCLogFilterType filter;
    CCLoggingOption *option;
    const char *tag, *identifier;
    const char *filename, *functionName;
    unsigned int line;
} CCLogData;

typedef struct {
    const char *format;
    va_list *args;
} CCLogInputData;

typedef struct CCLogMessage {
    char * const *message; //the full message
    const size_t *length; //full length of the current message (excluding null terminator)
    int (*write)(const struct CCLogMessage *Msg, const char *String, size_t Length); //returns 0 on success otherwise failure
    int (*remove)(const struct CCLogMessage *Msg, size_t Length); //returns 0 on success otherwise failure
} CCLogMessage;

typedef struct {
    const CCLogMessage *msg;
    const char *specifier;
    va_list *args;
} CCLogSpecifierData;

typedef CCLogMessage CCLogMessageData;

typedef size_t (*CCLogFilter)(const CCLogData *LogData, void *Data);
typedef size_t (*CCLogInputFilter)(const CCLogData *LogData, const CCLogInputData *Data);
typedef size_t (*CCLogSpecifierFilter)(const CCLogData *LogData, const CCLogSpecifierData *Data);
typedef size_t (*CCLogMessageFilter)(const CCLogData *LogData, const CCLogMessageData *Data);


#if __BLOCKS__
typedef size_t (^CCLogFilterBlock)(const CCLogData *LogData, void *Data);
typedef size_t (^CCLogInputFilterBlock)(const CCLogData *LogData, const CCLogInputData *Data);
typedef size_t (^CCLogSpecifierFilterBlock)(const CCLogData *LogData, const CCLogSpecifierData *Data);
typedef size_t (^CCLogMessageFilterBlock)(const CCLogData *LogData, const CCLogMessageData *Data);
#endif


typedef struct {
    struct {
        int flags : 1;
        int width : 1;
        int precision : 1;
        int length : 1;
    } options;
    struct {
        int leftJustified : 1;
        int showPlusSign : 1;
        int spacePrefixed : 1; //ignore if showPlusSign
        int altForm : 1;
        int padWithZeros : 1;
    } flags;
    struct {
        int value;
        int valueInArgs : 1;
    } width;
    struct {
        int value;
        int valueInArgs : 1;
    } precision;
    int length; //either 0, 'hh, 'h, 'l', 'll, 'j', 'z', 't', 'L'
} CCFormatSpecifierInfo;



#pragma mark - Functions
void CCLogAddFile(const char *File);
int CCLogCustom(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char *FormatString, ...);
int CCLog(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char *FormatString, ...) CC_FORMAT_PRINTF(7, 8);
int CCLogv(CCLoggingOption Option, const char *Tag, const char *Identifier, const char * const Filename, const char * const FunctionName, unsigned int Line, const char *FormatString, va_list Args) CC_FORMAT_PRINTF(7, 0);
void CCLogAddFilter(CCLogFilterType Type, CCLogFilter Filter);

#if __BLOCKS__
void CCLogAddFilterBlock(CCLogFilterType Type, CCLogFilterBlock Filter);
#endif

#define CCLogAddFilter(type, filter) CC_GENERIC_EVALUATE(filter, \
CCLogFilter: CCLogAddFilter, \
CCLogSpecifierFilter: CCLogAddFilter, \
CCLogMessageFilter: CCLogAddFilter, \
CC_SUPPORT_BLOCKS(CCLogFilterBlock: CCLogAddFilterBlock,) \
CC_SUPPORT_BLOCKS(CCLogSpecifierFilterBlock: CCLogAddFilterBlock,) \
CC_SUPPORT_BLOCKS(CCLogMessageFilterBlock: CCLogAddFilterBlock,) \
void *: CCLogAddFilter)(type, (void*)filter)



#if CC_NO_LOG
#define CC_LOG_(option, tag, identifier, ...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_CUSTOM_(option, tag, identifier, ...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_(option, tag, identifier, ...) CCLog(option, tag, identifier, CC_LOG_FROM_FILE, CC_LOG_FROM_FUNCTION, __LINE__, __VA_ARGS__)
#define CC_LOG_CUSTOM_(option, tag, identifier, ...) CCLogCustom(option, tag, identifier, CC_LOG_FROM_FILE, CC_LOG_FROM_FUNCTION, __LINE__, __VA_ARGS__)
#endif


#pragma mark - Formatting Helper Function
size_t CCGetFormatSpecifierInfo(const char *Format, CCFormatSpecifierInfo *Info);


#pragma mark - Loggers
#define CC_LOG(tag, ...) CC_LOG_(CC_LOG_OPTION, tag, CC_LOG_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_CUSTOM(tag, ...) CC_LOG_CUSTOM_(CC_LOG_OPTION, tag, CC_LOG_IDENTIFIER, __VA_ARGS__)

#if CC_NO_LOG_EMERGENCY
#define CC_LOG_EMERGENCY(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_EMERGENCY_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_EMERGENCY(...) CC_LOG_(CC_LOG_EMERGENCY_OPTION & CC_LOG_OPTION, CCTagEmergency, CC_LOG_EMERGENCY_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_EMERGENCY_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_EMERGENCY_OPTION & CC_LOG_OPTION, CCTagEmergency, CC_LOG_EMERGENCY_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_ALERT
#define CC_LOG_ALERT(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_ALERT_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_ALERT(...) CC_LOG_(CC_LOG_ALERT_OPTION & CC_LOG_OPTION, CCTagAlert, CC_LOG_ALERT_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_ALERT_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_ALERT_OPTION & CC_LOG_OPTION, CCTagAlert, CC_LOG_ALERT_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_CRITICAL
#define CC_LOG_CRITICAL(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_CRITICAL_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_CRITICAL(...) CC_LOG_(CC_LOG_CRITICAL_OPTION & CC_LOG_OPTION, CCTagCritical, CC_LOG_CRITICAL_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_CRITICAL_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_CRITICAL_OPTION & CC_LOG_OPTION, CCTagCritical, CC_LOG_CRITICAL_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_ERROR
#define CC_LOG_ERROR(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_ERROR_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_ERROR(...) CC_LOG_(CC_LOG_ERROR_OPTION & CC_LOG_OPTION, CCTagError, CC_LOG_ERROR_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_ERROR_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_ERROR_OPTION & CC_LOG_OPTION, CCTagError, CC_LOG_ERROR_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_WARNING
#define CC_LOG_WARNING(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_WARNING_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_WARNING(...) CC_LOG_(CC_LOG_WARNING_OPTION & CC_LOG_OPTION, CCTagWarning, CC_LOG_WARNING_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_WARNING_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_WARNING_OPTION & CC_LOG_OPTION, CCTagWarning, CC_LOG_WARNING_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_NOTICE
#define CC_LOG_NOTICE(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_NOTICE_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_NOTICE(...) CC_LOG_(CC_LOG_NOTICE_OPTION & CC_LOG_OPTION, CCTagNotice, CC_LOG_NOTICE_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_NOTICE_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_NOTICE_OPTION & CC_LOG_OPTION, CCTagNotice, CC_LOG_NOTICE_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_INFO
#define CC_LOG_INFO(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_INFO_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_INFO(...) CC_LOG_(CC_LOG_INFO_OPTION & CC_LOG_OPTION, CCTagInfo, CC_LOG_INFO_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_INFO_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_INFO_OPTION & CC_LOG_OPTION, CCTagInfo, CC_LOG_INFO_IDENTIFIER, __VA_ARGS__)
#endif

#if CC_NO_LOG_DEBUG
#define CC_LOG_DEBUG(...) CC_SILENCE_UNUSED_WARNING(0)
#define CC_LOG_DEBUG_CUSTOM(...) CC_SILENCE_UNUSED_WARNING(0)
#else
#define CC_LOG_DEBUG(...) CC_LOG_(CC_LOG_DEBUG_OPTION & CC_LOG_OPTION, CCTagDebug, CC_LOG_DEBUG_IDENTIFIER, __VA_ARGS__)
#define CC_LOG_DEBUG_CUSTOM(...) CC_LOG_CUSTOM_(CC_LOG_DEBUG_OPTION & CC_LOG_OPTION, CCTagDebug, CC_LOG_DEBUG_IDENTIFIER, __VA_ARGS__)
#endif



#pragma mark - Logging Options
#ifndef CC_LOG_OPTION
#define CC_LOG_OPTION (CCLogOptionOutputAll | CCLogOptionAsync)
#endif

#ifndef CC_LOG_EMERGENCY_OPTION
#define CC_LOG_EMERGENCY_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_ALERT_OPTION
#define CC_LOG_ALERT_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_CRITICAL_OPTION
#define CC_LOG_CRITICAL_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_ERROR_OPTION
#define CC_LOG_ERROR_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_WARNING_OPTION
#define CC_LOG_WARNING_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_NOTICE_OPTION
#define CC_LOG_NOTICE_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_INFO_OPTION
#define CC_LOG_INFO_OPTION CC_LOG_OPTION
#endif

#ifndef CC_LOG_DEBUG_OPTION
#define CC_LOG_DEBUG_OPTION CC_LOG_OPTION
#endif


#pragma mark - Logging Identifiers
#ifndef CC_LOG_IDENTIFIER
#define CC_LOG_IDENTIFIER NULL
#endif

#ifndef CC_LOG_EMERGENCY_IDENTIFIER
#define CC_LOG_EMERGENCY_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_ALERT_IDENTIFIER
#define CC_LOG_ALERT_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_CRITICAL_IDENTIFIER
#define CC_LOG_CRITICAL_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_ERROR_IDENTIFIER
#define CC_LOG_ERROR_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_WARNING_IDENTIFIER
#define CC_LOG_WARNING_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_NOTICE_IDENTIFIER
#define CC_LOG_NOTICE_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_INFO_IDENTIFIER
#define CC_LOG_INFO_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#ifndef CC_LOG_DEBUG_IDENTIFIER
#define CC_LOG_DEBUG_IDENTIFIER CC_LOG_IDENTIFIER
#endif

#pragma mark - Additional Logging Features

#ifndef CC_LOG_FROM_FILE
#define CC_LOG_FROM_FILE __FILE__
#endif

#ifndef CC_LOG_FROM_FUNCTION
#define CC_LOG_FROM_FUNCTION __func__
#endif

#pragma mark -

#endif
