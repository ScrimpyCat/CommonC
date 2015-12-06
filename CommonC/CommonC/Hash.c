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

#include "Hash.h"
#include "Extensions.h"

uint32_t CCHashJenkins32(CCData Data)
{
    uint32_t Hash = 0;
    
    size_t Read = 0;
    const size_t PreferredMapSize = CCDataGetPreferredMapSize(Data), Size = CCDataGetSize(Data);
    for (size_t Loop = 0, Count = Size / PreferredMapSize; Loop < Count; Loop++)
    {
        CCBufferMap Map = CCDataMapBuffer(Data, Loop * PreferredMapSize, PreferredMapSize, CCDataHintRead);
        
        for (size_t Index = 0; Index < Map.size; Index++)
        {
            Hash += ((uint8_t*)Map.ptr)[Index];
            Hash += (Hash << 10);
            Hash ^= (Hash >> 6);
        }
        
        CCDataUnmapBuffer(Data, Map);
        
        Read += Map.size;
        if (Map.size != PreferredMapSize) goto Finalizer;
    }
    
    CCBufferMap Map = CCDataMapBuffer(Data, Read, Size - Read, CCDataHintRead);
    
    for (size_t Index = 0; Index < Map.size; Index++)
    {
        Hash += ((uint8_t*)Map.ptr)[Index];
        Hash += (Hash << 10);
        Hash ^= (Hash >> 6);
    }
    
    CCDataUnmapBuffer(Data, Map);
    
Finalizer:
    Hash += (Hash << 3);
    Hash ^= (Hash >> 11);
    Hash += (Hash << 15);
    
    return Hash;
}

static CC_FORCE_INLINE uint32_t CCHashROL32(uint32_t x, uint32_t y)
{
    return ((x << y) | (x >> (32 - y)));
}

uint32_t CCHashMurmur32(CCData Data)
{
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t r1 = 15;
    const uint32_t r2 = 13;
    const uint32_t m = 5;
    const uint32_t n = 0xe6546b64;
    
    uint32_t Seed = 0;
    uint32_t Hash = Seed;
    
    size_t Read = 0;
    size_t PreferredMapSize = (CCDataGetPreferredMapSize(Data) / sizeof(uint32_t)) * sizeof(uint32_t), Size = CCDataGetSize(Data);
    if (!PreferredMapSize) PreferredMapSize = 4;
    
    for (size_t Loop = 0, Count = ((Size / sizeof(uint32_t)) * sizeof(uint32_t)) / PreferredMapSize; Loop < Count; Loop++)
    {
        CCBufferMap Map = CCDataMapBuffer(Data, Loop * PreferredMapSize, PreferredMapSize, CCDataHintRead);
        
        size_t BlockCount = Map.size / sizeof(uint32_t);
        for (size_t Index = 0; Index < BlockCount; Index++)
        {
            uint32_t k = ((uint32_t*)Map.ptr)[Index];
            k *= c1;
            k = CCHashROL32(k, r1);
            k *= c2;
            
            Hash ^= k;
            Hash = CCHashROL32(Hash, r2) * m + n;
        }
        
        size_t Leftover = Map.size - (BlockCount * sizeof(uint32_t));
        if (Leftover)
        {
            const uint8_t *Tail = Map.ptr + (BlockCount * sizeof(uint32_t));
            uint32_t k = 0;
            switch (Leftover)
            {
                case 3:
                    k ^= Tail[2] << 16;
                case 2:
                    k ^= Tail[1] << 8;
                case 1:
                    k ^= Tail[0];
                    
                    k *= c1;
                    k = CCHashROL32(k, r1);
                    k *= c2;
                    
                    Hash ^= k;
                    break;
            }
        }
        
        CCDataUnmapBuffer(Data, Map);
        
        Read += Map.size;
        if (Map.size != PreferredMapSize) goto Finalizer;
    }
    
    CCBufferMap Map = CCDataMapBuffer(Data, Read, Size - Read, CCDataHintRead);
    
    size_t BlockCount = Map.size / sizeof(uint32_t);
    for (size_t Index = 0; Index < BlockCount; Index++)
    {
        uint32_t k = ((uint32_t*)Map.ptr)[Index];
        k *= c1;
        k = CCHashROL32(k, r1);
        k *= c2;
        
        Hash ^= k;
        Hash = CCHashROL32(Hash, r2) * m + n;
    }
    
    size_t Leftover = Map.size - (BlockCount * sizeof(uint32_t));
    if (Leftover)
    {
        const uint8_t *Tail = Map.ptr + (BlockCount * sizeof(uint32_t));
        uint32_t k = 0;
        switch (Leftover)
        {
            case 3:
                k ^= Tail[2] << 16;
            case 2:
                k ^= Tail[1] << 8;
            case 1:
                k ^= Tail[0];
                
                k *= c1;
                k = CCHashROL32(k, r1);
                k *= c2;
                
                Hash ^= k;
                break;
        }
    }
    
    CCDataUnmapBuffer(Data, Map);
    Read += Map.size;
    
Finalizer:
    Hash ^= Read;
    Hash ^= (Hash >> 16);
    Hash *= 0x85ebca6b;
    Hash ^= (Hash >> 13);
    Hash *= 0xc2b2ae35;
    Hash ^= (Hash >> 16);
    
    return Hash;
}
