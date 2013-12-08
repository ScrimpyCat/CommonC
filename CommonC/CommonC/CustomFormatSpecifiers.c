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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include "CustomFormatSpecifiers.h"
#include "BitTricks.h"

size_t CCBinaryFormatSpecifier(const CCLogData *LogData, const CCLogSpecifierData *Data)
{
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
                    uint64_t HighestSetBitIndex = CCCountSetBits(CCMaskForValue(CCHighestSetBit(Value)));
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
}

