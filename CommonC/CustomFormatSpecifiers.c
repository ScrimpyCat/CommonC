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

#include <string.h>
#include <ctype.h>
#include "CustomFormatSpecifiers.h"
#include "BitTricks.h"
#include "MemoryAllocation.h"
#include "CCString.h"

size_t CCBinaryFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
    size_t Length;
    CCFormatSpecifierInfo Info;
    if (Data->specifier[(Length = CCGetFormatSpecifierInfo(Data->specifier, &Info))] == 'B')
    {
        if ((Info.options.width) && (Info.width.valueInArgs)) Info.width.value = va_arg(*Data->args, int);
        if ((Info.options.precision) && (Info.precision.valueInArgs)) Info.precision.value = va_arg(*Data->args, int);
        
        uintmax_t Value;
        size_t Size;
        char Bits[(sizeof(uintmax_t) * 8) + 1];
        switch (Info.length)
        {
            case 'hh':
                Value = va_arg(*Data->args, unsigned int);
                Size = sizeof(unsigned char);
                break;
            
            case 'h':
                Value = va_arg(*Data->args, unsigned int);
                Size = sizeof(unsigned short int);
                break;
            
            case 'l':
                Value = va_arg(*Data->args, unsigned long int);
                Size = sizeof(unsigned long int);
                break;
            
            case 'll':
                Value = va_arg(*Data->args, unsigned long long int);
                Size = sizeof(unsigned long long int);
                break;
            
            case 'j':
                Value = va_arg(*Data->args, uintmax_t);
                Size = sizeof(uintmax_t);
                break;
            
            case 'z':
                Value = va_arg(*Data->args, size_t);
                Size = sizeof(size_t);
                break;
            
            case 't':
                Value = va_arg(*Data->args, ptrdiff_t);
                Size = sizeof(ptrdiff_t);
                break;
            
            default:
                Value = va_arg(*Data->args, unsigned int);
                Size = sizeof(unsigned int);
                break;
        }
        
        size_t Count = Size * 8;
        for (size_t Loop = 0; Loop < Count; Loop++)
        {
            Bits[(Count - Loop) - 1] = ((Value >> Loop) & 1) + '0';
        }
        Bits[Count] = 0;
        
        
        size_t FormattedLength = Count;
        const char *Formatted = Bits;
        if (Info.flags.altForm)
        {
            if (sizeof(uintmax_t) <= sizeof(uint64_t))
            {
                uint64_t HighestSetBitIndex = CCBitCountSet(CCBitMaskForValue(CCBitHighestSet(Value)));
                if (HighestSetBitIndex)
                {
                    Formatted = Bits + (Count - HighestSetBitIndex);
                    FormattedLength = HighestSetBitIndex;
                }
                
                else FormattedLength = 1;
            }
            
            else
            {
                char *HighestSetBit = strchr(Bits, '1');
                if (HighestSetBit)
                {
                    Formatted = HighestSetBit;
                    FormattedLength = Count - (HighestSetBit - Bits);
                }
                
                else FormattedLength = 1;
            }
        }
        
        
        const size_t FormattedLengthAfterPrecision = ((Info.options.precision) && (Info.precision.value > FormattedLength)) ? FormattedLength + (Info.precision.value - FormattedLength) : FormattedLength;
        if ((!Info.flags.leftJustified) && (Info.options.width) && (Info.width.value > FormattedLengthAfterPrecision))
        {
            size_t Width = Info.width.value - FormattedLengthAfterPrecision;
            const char *Padding = Info.flags.padWithZeros? "00000000000000000000" : "                    "; //20 characters
            
            while (Width)
            {
                const size_t WriteSize = Width > 20 ? 20 : Width;
                Data->msg->write(Data->msg, Padding, WriteSize);
                Width -= WriteSize;
            }
        }
        
        if ((Info.options.precision) && (Info.precision.value > FormattedLength))
        {
            size_t Precision = Info.precision.value - FormattedLength;
            const char *Padding = "00000000000000000000"; //20 characters
            
            while (Precision)
            {
                const size_t PrecisionSize = Precision > 20 ? 20 : Precision;
                Data->msg->write(Data->msg, Padding, PrecisionSize);
                Precision -= PrecisionSize;
            }
        }
        
        
        Data->msg->write(Data->msg, Formatted, FormattedLength);
        
        
        if ((Info.flags.leftJustified) && (Info.options.width) && (Info.width.value > FormattedLengthAfterPrecision))
        {
            size_t Width = Info.width.value - FormattedLengthAfterPrecision;
            const char *Padding = "                    "; //20 characters
            
            while (Width)
            {
                const size_t WriteSize = Width > 20 ? 20 : Width;
                Data->msg->write(Data->msg, Padding, WriteSize);
                Width -= WriteSize;
            }
        }
        
        
        return Length + 1;
    }
    
    return 0;
}

size_t CCArrayFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
    if (!strncmp(Data->specifier, "%[", 2))
    {
        size_t ElementCount = 0;
        const char *Format = Data->specifier + 2;
        if (*Format == '*')
        {
            ElementCount = va_arg(*Data->args, size_t);
            Format++;
        }
        
        else if (isdigit(*Format))
        {
            ElementCount = *Format - '0';
            for (char c = *++Format; isdigit(c); c = *++Format) ElementCount = (ElementCount * 10) + (c - '0');
        }
        
        else return 0;
        
        
        size_t SeparatorLength = 2;
        const char *Separator = ", ";
        if (*Format != ']') //custom separator
        {
            if (*Format == '*')
            {
                Separator = va_arg(*Data->args, char *);
                SeparatorLength = strlen(Separator);
                if (*++Format != ']') return 0;
            }
            
            else
            {
                const char *End = strchr(Format, ']');
                if (!End) return 0;
                
                Separator = Format;
                SeparatorLength = End - Format;
                Format += SeparatorLength;
            }
        }
        
        
        CCFormatSpecifierInfo Info;
        size_t Length = CCGetFormatSpecifierInfo(++Format, &Info);
        
        if (ElementCount)
        {
            char *Specifier;
            CC_SAFE_Malloc(Specifier, sizeof(char) * (Length + 3),
                           return 0;
                           );
            
            *Specifier = '%';
            strncpy(Specifier + 1, Format, Length + 1);
            Specifier[Length + 2] = 0;
            
            
#define CC_PRINT_ARRAY(type) \
for (size_t Loop = 0; ; ) \
{ \
    const type Value = ((type*)Ptr)[Loop++]; \
    size_t Len = snprintf(NULL, 0, Specifier, Value); \
    \
    if (Len > FormattedStringLength) \
    { \
        CC_SAFE_Realloc(FormattedString, sizeof(char) * (Len + 1), \
                        Len = FormattedStringLength; \
                        ); \
        FormattedStringLength = Len; \
    } \
    \
    Len = snprintf(FormattedString, FormattedStringLength + 1, Specifier, Value); \
    \
    Data->msg->write(Data->msg, FormattedString, Len); \
    if (Loop >= ElementCount) break; \
    \
    Data->msg->write(Data->msg, Separator, SeparatorLength); \
}
            
            const char ConversionSpecifier = Specifier[Length + 1];
            size_t FormattedStringLength = 0;
            char *FormattedString = NULL;
            const void *Ptr = va_arg(*Data->args, void *);
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
                        case 'hh':
                            CC_PRINT_ARRAY(unsigned char);
                            break;
                            
                        case 'h':
                            CC_PRINT_ARRAY(unsigned short int);
                            break;
                            
                        case 'l':
                            CC_PRINT_ARRAY(unsigned long int);
                            break;
                            
                        case 'll':
                            CC_PRINT_ARRAY(unsigned long long int);
                            break;
                            
                        case 'j':
                            CC_PRINT_ARRAY(uintmax_t);
                            break;
                            
                        case 'z':
                            CC_PRINT_ARRAY(size_t);
                            break;
                            
                        case 't':
                            CC_PRINT_ARRAY(ptrdiff_t);
                            break;
                            
                        default:
                            CC_PRINT_ARRAY(unsigned int);
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
                    //Follows non-standard rule, %f = float, %lf = double, since it is pointer input so there's no promotion so we have to promote it in here
                    switch (Info.length)
                    {
                        case 'l':
                            CC_PRINT_ARRAY(double);
                            break;
                            
                        case 'L':
                            CC_PRINT_ARRAY(long double);
                            break;
                            
                        default:
                            CC_PRINT_ARRAY(float);
                            break;
                    }
                    break;
                    
                case 'c':
                    switch (Info.length)
                    {
                        case 'l':
                            CC_PRINT_ARRAY(wchar_t); //promote to wint_t
                            break;
                            
                        default:
                            CC_PRINT_ARRAY(unsigned char); //promote to int
                            break;
                    }
                    break;
                    
                case 's':
                case 'p':
                    CC_PRINT_ARRAY(void *);
                    break;
            }
            
#undef CC_PRINT_ARRAY
            
            
            CC_SAFE_Free(FormattedString);
            CC_SAFE_Free(Specifier);
        }
        
        return ((Format + Length) - Data->specifier) + 1;
    }
    
    return 0;
}

size_t CCDeletionFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
    if (*Data->specifier == '%')
    {
        const char *Format = Data->specifier + 1;
        size_t Characters = 1;
        
        if (*Format == '*')
        {
            Characters = va_arg(*Data->args, size_t);
            Format++;
        }
        
        else if (isdigit(*Format))
        {
            Characters = *Format - '0';
            for (char c = *++Format; isdigit(c); c = *++Format) Characters = (Characters * 10) + (c - '0');
        }
        
        if (!strncmp(Format, "DEL", 3))
        {
            Data->msg->remove(Data->msg, Characters);
            return (Format - Data->specifier) + 3;
        }
    }
    
    return 0;
}

size_t CCStringFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
    if (!strncmp(Data->specifier, "%S", 2))
    {
        CCString String = va_arg(*Data->args, CCString);
        
        if (String)
        {
            const size_t Size = CCStringGetSize(String);
            const char *Buf = CCStringGetBuffer(String);
            if (Buf)
            {
                Data->msg->write(Data->msg, Buf, Size);
            }
            
            else
            {
                char *Copy;
                CC_TEMP_Malloc(Copy, Size,
                               Data->msg->write(Data->msg, "(write failure)", 15);
                               return 2;
                               );
                
                CCStringCopyCharacters(String, 0, CCStringGetLength(String), Copy);
                Data->msg->write(Data->msg, Copy, Size);
                
                CC_TEMP_Free(Copy);
            }
        }
        
        else
        {
            Data->msg->write(Data->msg, "(null)", 6);
        }
        
        return 2;
    }
    
    return 0;
}

size_t CCCharFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
    if (!strncmp(Data->specifier, "%C", 2))
    {
        CCChar Character = va_arg(*Data->args, CCChar);
        
        const char *Output = "%lc";
        int Len = snprintf(NULL, 0, Output, (wint_t)Character);
        if (Len <= 0)
        {
            Output = "\\%u";
            Len = snprintf(NULL, 0, Output, Character);
        }
        
        char *Buffer;
        CC_TEMP_Malloc(Buffer, Len + 1,
                       Data->msg->write(Data->msg, "(write failure)", 15);
                       return 2;
                       );
        
        Len = snprintf(Buffer, Len + 1, Output, (wint_t)Character);
        Data->msg->write(Data->msg, Buffer, Len);
        
        CC_TEMP_Free(Buffer);
        
        return 2;
    }
    
    return 0;
}
