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
 Some useful custom format specifier filters. These are not added by default and must manually be added.
 
 CCBinaryFormatSpecifier: Adds the specifier "%B", which will display the binary form of the integer. The format will display the full number of bits for the
                          specified length modifier. If the alternate form is used ('#' flag is present), it will display only up to the highest set bit.
 */

#pragma mark -

#ifndef CommonC_CustomFormatSpecifiers_h
#define CommonC_CustomFormatSpecifiers_h

#include <CommonC/Base.h>
#include <CommonC/Logging.h>


#pragma mark - Functions
size_t CCBinaryFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data); //"%B" : Follows standard for options usage.
size_t CCArrayFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data); //"%[count{separator}]format_specifier" : Count can either be a value or * (size_t value in arg), separator is optional can be the text or * (char * value in arg), and then the standard format specifier
size_t CCDeletionFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data); //"%{count}DEL" : Deletes one character from the current buffer, or n characters if the optional count value is used or * (size_t value in arg)
size_t CCStringFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data); //%S : Prints a string of CCString type.
size_t CCCharFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data); //%C : Prints a character of CCChar type.

#endif
