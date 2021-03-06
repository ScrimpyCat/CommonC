/*
 *  Copyright (c) 2020, Stefan Johnson
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

#include "Random.h"

CCRandomState_xorshift CCRandomGlobalState_xorshift = 1;

uint32_t CCRandom_xorshift(CCRandomState_xorshift *State)
{
    *State ^= *State << 13;
    *State ^= *State >> 17;
    *State ^= *State << 5;
    
    return *State;
}

uint32_t CCRandomMax_xorshift(void)
{
	return UINT32_MAX;
}

void CCRandomSeed_xorshift(CCRandomState_xorshift *State, uint32_t Seed)
{
    *State = Seed ? Seed : 1;
}

CCRandomState_xorwow CCRandomGlobalState_xorwow = { 270369, 67634689, 2647435461, 307599695, 2398689233 };

uint32_t CCRandom_xorwow(CCRandomState_xorwow *State)
{
    uint32_t t = State->d;
    const uint32_t s = State->a;
    State->d = State->c;
    State->c = State->b;
    State->b = s;
    
    t ^= t >> 2;
    t ^= t << 1;
    t ^= s ^ (s << 4);
    State->a = t;
    
    State->counter += 362437;
    
    return t + State->counter;
}

uint32_t CCRandomMax_xorwow(void)
{
    return UINT32_MAX;
}

void CCRandomSeed_xorwow(CCRandomState_xorwow *State, uint32_t Seed)
{
    CCRandomState_xorshift Xorshift;
    CCRandomSeed_xorshift(&Xorshift, Seed);
    
    *State = (CCRandomState_xorwow){
        .a = CCRandom_xorshift(&Xorshift),
        .b = CCRandom_xorshift(&Xorshift),
        .c = CCRandom_xorshift(&Xorshift),
        .d = CCRandom_xorshift(&Xorshift),
        .counter = CCRandom_xorshift(&Xorshift)
    };
}
