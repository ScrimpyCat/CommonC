/*
 *  Copyright (c) 2025, Stefan Johnson
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

#ifndef CommonC_Decimal_h
#define CommonC_Decimal_h

#include <CommonC/Base.h>
#include <CommonC/Extensions.h>

typedef struct {
    uint64_t coef;
    int64_t exp;
} CCDecimal;

static inline uint64_t CCDecimalMultiplyU64(uint64_t Value, CCDecimal Decimal)
{
    uint64_t Lo = (Value & 0xffffffff) * Decimal.coef;
    uint64_t Hi = (Value >> 32) * Decimal.coef;
    
    uint64_t Result;
    
    if (Decimal.exp >= 0)
    {
        while (Decimal.exp--)
        {
            Lo *= 10;
            Hi *= 10;
        }
        
        if (Hi > 0xffffffff) Result = UINT64_MAX;
        else Result = Lo + (Hi << 32);
    }
    
    else
    {
        uint64_t Remainder = 0, Carry = 0;
        
        while (Decimal.exp++)
        {
            Remainder += (Hi % 10) << 32;
            
            Carry = ((Remainder % 10) + (Lo % 10) + Carry) >= 10;
            
            Remainder /= 10;
            
            Lo /= 10;
            Hi /= 10;
        }
        
        Result = Lo + Remainder + (Hi << 32) + Carry;
    }
    
    return Result;
}

#endif
