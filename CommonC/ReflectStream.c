/*
 *  Copyright (c) 2024, Stefan Johnson
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

#include "ReflectStream.h"
#include "Platform.h"
#include "Swap.h"


void CCReflectStreamRLEWriteFlush(CCReflectStreamRLE *Stream)
{
    if (Stream->repeat.count)
    {
        size_t Count = Stream->repeat.count - 1;
        
        Stream->repeat.count = 0;
        
#if CC_HARDWARE_ENDIAN_BIG
        CCSwap(&Count, sizeof(size_t));
#endif
        
        Stream->into.write(Stream->into.stream, &Count, Stream->repeat.size);
    }
}

static inline void CCReflectStreamRLEWriteByte(CCReflectStreamRLE *Stream, uint8_t Byte)
{
    if (CCBitsGet(Stream->repeat.mask, Byte))
    {
        Stream->repeat.value = Byte;
        Stream->repeat.count++;
    }
    
    Stream->into.write(Stream->into.stream, &Byte, sizeof(uint8_t));
}

void CCReflectStreamRLEWrite(CCReflectStreamRLE *Stream, const void *Data, size_t Size)
{
    const size_t Max = 1ULL << (size_t)(8 * Stream->repeat.size);
    
    for (size_t Loop = 0; Loop < Size; Loop++)
    {
        const uint8_t Byte = ((const uint8_t*)Data)[Loop];
        
        if (Stream->repeat.count)
        {
            if (Byte != Stream->repeat.value)
            {
                CCReflectStreamRLEWriteFlush(Stream);
                CCReflectStreamRLEWriteByte(Stream, Byte);
            }
            
            else if (++Stream->repeat.count == Max)
            {
                CCReflectStreamRLEWriteFlush(Stream);
            }
        }
        
        else CCReflectStreamRLEWriteByte(Stream, Byte);
    }
}

void CCReflectStreamRLEWriteContinue(CCReflectStreamRLE *Stream, const void *Data, size_t Size)
{
    if (Stream->repeat.count)
    {
        const size_t Max = 1ULL << (size_t)(8 * Stream->repeat.size);
        
        for (size_t Loop = 0; Loop < Size; Loop++)
        {
            if (((const uint8_t*)Data)[Loop] != Stream->repeat.value)
            {
                CCReflectStreamRLEWriteFlush(Stream);
                Stream->into.write(Stream->into.stream, &((const uint8_t*)Data)[Loop], Size - Loop);
                
                break;
            }
            
            else if (++Stream->repeat.count == Max)
            {
                CCReflectStreamRLEWriteFlush(Stream);
            }
        }
        
        return;
    }
    
    Stream->into.write(Stream->into.stream, Data, Size);
}

void CCReflectStreamRLERead(CCReflectStreamRLE *Stream, void *Data, size_t Size)
{
    for (size_t Loop = 0; Loop < Size; Loop++)
    {
        if (Stream->repeat.count)
        {
            ((uint8_t*)Data)[Loop] = Stream->repeat.value;
            
            Stream->repeat.count--;
        }
        
        else
        {
            uint8_t Byte;
            Stream->into.read(Stream->into.stream, &Byte, sizeof(uint8_t));
            
            ((uint8_t*)Data)[Loop] = Byte;
            
            if (CCBitsGet(Stream->repeat.mask, Byte))
            {
                Stream->repeat.value = Byte;
                
                Stream->into.read(Stream->into.stream, &Stream->repeat.count, Stream->repeat.size);
                
#if CC_HARDWARE_ENDIAN_BIG
                CCSwap(&Stream->repeat.count, sizeof(size_t));
#endif
            }
        }
    }
}

void CCReflectStreamRLEReadContinue(CCReflectStreamRLE *Stream, void *Data, size_t Size)
{
    if (Stream->repeat.count)
    {
        for (size_t Loop = 0; Loop < Size; Loop++)
        {
            if (Stream->repeat.count)
            {
                ((uint8_t*)Data)[Loop] = Stream->repeat.value;
                
                Stream->repeat.count--;
            }
            
            else
            {
                Stream->into.read(Stream->into.stream, (uint8_t*)Data + Loop, Size - Loop);
                
                break;
            }
        }
        
        return;
    }
    
    Stream->into.read(Stream->into.stream, Data, Size);
}
