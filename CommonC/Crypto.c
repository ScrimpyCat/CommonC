/*
 *  Copyright (c) 2026, Stefan Johnson
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

#include "Crypto.h"

CCCryptoSha1State CCCryptoSha1(const void *Data, size_t Size)
{
    CCCryptoSha1State State = CCCryptoSha1StateInit();
    const CCCryptoSha1Constants Constants = CCCryptoSha1ConstantsInit();
    
    const size_t Blocks = Size / 64;
    
    for (size_t Loop = 0; Loop < Blocks; Loop++)
    {
        State = CCCryptoSha1Process(State, Data + (Loop * 64), Constants);
    }
    
    uint8_t Chunk[128] = {0};
    memcpy(Chunk, (const uint8_t*)Data + (Blocks * 64), Size - (Blocks * 64));
    
    size_t RemainingBlocks = CCCryptoSha1Prepare((uint8_t*)Chunk - (Blocks * 64), Size) - Blocks;
    
    for (size_t Loop = 0; Loop < RemainingBlocks; Loop++)
    {
        State = CCCryptoSha1Process(State, Chunk + (Loop * 64), Constants);
    }
    
    return State;
}

CCCryptoSha256State CCCryptoSha256(const void *Data, size_t Size)
{
    CCCryptoSha256State State = CCCryptoSha256StateInit();
    const CCCryptoSha256Constants Constants = CCCryptoSha256ConstantsInit();
    
    const size_t Blocks = Size / 64;
    
    for (size_t Loop = 0; Loop < Blocks; Loop++)
    {
        State = CCCryptoSha256Process(State, Data + (Loop * 64), Constants);
    }
    
    uint8_t Chunk[128] = {0};
    memcpy(Chunk, (const uint8_t*)Data + (Blocks * 64), Size - (Blocks * 64));
    
    size_t RemainingBlocks = CCCryptoSha256Prepare((uint8_t*)Chunk - (Blocks * 64), Size) - Blocks;
    
    for (size_t Loop = 0; Loop < RemainingBlocks; Loop++)
    {
        State = CCCryptoSha256Process(State, Chunk + (Loop * 64), Constants);
    }
    
    return State;
}
