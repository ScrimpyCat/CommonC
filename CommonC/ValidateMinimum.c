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

#include "ValidateMinimum.h"
#include "Swap.h"

#if CC_HARDWARE_ENDIAN_LITTLE
#define CC_REFLECT_COMPATIBLE_ENDIAN CCReflectEndianLittle
#define CC_REFLECT_SWAPPED_ENDIAN CCReflectEndianBig
#elif CC_HARDWARE_ENDIAN_BIG
#define CC_REFLECT_COMPATIBLE_ENDIAN CCReflectEndianBig
#define CC_REFLECT_SWAPPED_ENDIAN CCReflectEndianLittle
#else
#error Unknown native endianness
#endif

_Bool CCReflectValidateMinimum(CCReflectType Type, const void *Data, CCReflectType Validator)
{
    CCReflectType ValueType = ((const CCReflectMinimumValidator*)Validator)->min.type;
    const void *Value = ((const CCReflectMinimumValidator*)Validator)->min.data;
    
    switch (*(CCReflectTypeID*)ValueType)
    {
        case CCReflectTypeInteger:
            switch (*(CCReflectTypeID*)Type)
            {
                case CCReflectTypeInteger:
                {
                    size_t InvertA, StartA, SizeA = ((const CCReflectInteger*)Type)->size;
                    size_t InvertB, StartB, SizeB = ((const CCReflectInteger*)ValueType)->size;
                    
                    switch (((const CCReflectInteger*)ValueType)->endian)
                    {
                        case CCReflectEndianNative:
                        case CC_REFLECT_COMPATIBLE_ENDIAN:
                            InvertB = 1;
                            StartB = 0;
                            break;
                            
                        case CC_REFLECT_SWAPPED_ENDIAN:
                            InvertB = -1;
                            StartB = SizeB - 1;
                            break;
                    }
                    
                    switch (((const CCReflectInteger*)Type)->endian)
                    {
                        case CCReflectEndianNative:
                        case CC_REFLECT_COMPATIBLE_ENDIAN:
                            InvertA = 1;
                            StartA = 0;
                            break;
                            
                        case CC_REFLECT_SWAPPED_ENDIAN:
                            InvertA = -1;
                            StartA = SizeA - 1;
                            break;
                    }
                    
                    const _Bool NegA = (((uint8_t*)Data)[StartA + (InvertA * (SizeA - 1))] & 0x80) && ((const CCReflectInteger*)Type)->sign;
                    const _Bool NegB = (((const uint8_t*)Value)[StartB + (InvertB * (SizeB - 1))] & 0x80) && ((const CCReflectInteger*)ValueType)->sign;
                    
                    if (NegA)
                    {
                        if (NegB)
                        {
                            size_t Size = SizeA;
                            
                            if (SizeA > SizeB)
                            {
                                Size = SizeB;
                                
                                for (size_t Loop = SizeA; Loop != SizeB; )
                                {
                                    if (((uint8_t*)Data)[StartA + (InvertA * --Loop)] != 0xff) return FALSE;
                                }
                            }
                            
                            else
                            {
                                for (size_t Loop = SizeB; Loop != SizeA; )
                                {
                                    if (((const uint8_t*)Value)[StartB + (InvertB * --Loop)] != 0xff) return TRUE;
                                }
                            }
                            
                            for (size_t Loop = Size; Loop; )
                            {
                                const uint8_t A = ((uint8_t*)Data)[StartA + (InvertA * --Loop)];
                                const uint8_t B = ((const uint8_t*)Value)[StartB + (InvertB * Loop)];
                                
                                if (A < B) return FALSE;
                                else if (A > B) return TRUE;
                            }
                            
                            return TRUE;
                        }
                        
                        else return FALSE;
                    }
                    
                    else if (NegB)
                    {
                        return TRUE;
                    }
                    
                    else
                    {
                        size_t Size = SizeA;
                        
                        if (SizeA > SizeB)
                        {
                            Size = SizeB;
                            
                            for (size_t Loop = SizeA; Loop != SizeB; )
                            {
                                if (((uint8_t*)Data)[StartA + (InvertA * --Loop)]) return TRUE;
                            }
                        }
                        
                        else
                        {
                            for (size_t Loop = SizeB; Loop != SizeA; )
                            {
                                if (((const uint8_t*)Value)[StartB + (InvertB * --Loop)]) return FALSE;
                            }
                        }
                        
                        for (size_t Loop = Size; Loop; )
                        {
                            const uint8_t A = ((uint8_t*)Data)[StartA + (InvertA * --Loop)];
                            const uint8_t B = ((const uint8_t*)Value)[StartB + (InvertB * Loop)];
                            
                            if (A < B) return FALSE;
                            else if (A > B) return TRUE;
                        }
                        
                        return TRUE;
                    }
                    
                    break;
                }
                    
                default:
                    CCAssertLog(0, "Unsupported value type");
                    break;
            }
            break;
            
        case CCReflectTypeFloat:
            switch (*(CCReflectTypeID*)Type)
            {
                case CCReflectTypeFloat:
                {
                    size_t SizeA = ((const CCReflectFloat*)Type)->size;
                    size_t SizeB = ((const CCReflectFloat*)ValueType)->size;
                    
#define CC_FLOAT_SIZE(a, b) ((a) << 8) + (b)
                    
#define CC_FLOAT_COMPARE(a, b) \
case CC_FLOAT_SIZE(sizeof(a), sizeof(b)): \
{ \
    a A = *(a*)Data; \
    b B = *(const b*)Value; \
    \
    if (((const CCReflectFloat*)Type)->endian == CC_REFLECT_SWAPPED_ENDIAN) CCSwap(&A, SizeA); \
    if (((const CCReflectFloat*)ValueType)->endian == CC_REFLECT_SWAPPED_ENDIAN) CCSwap(&B, SizeB); \
    \
    return A >= B; \
}
                    
                    if ((SizeA <= 0xff) && (SizeB <= 0xff))
                    {
                        switch (CC_FLOAT_SIZE(SizeA, SizeB))
                        {
#if DBL_MANT_DIG != LDBL_MANT_DIG
                            CC_FLOAT_COMPARE(long double, long double)
                            CC_FLOAT_COMPARE(long double, double)
                            CC_FLOAT_COMPARE(long double, float)
                            CC_FLOAT_COMPARE(double, long double)
                            CC_FLOAT_COMPARE(float, long double)
#endif
                            CC_FLOAT_COMPARE(double, double)
                            CC_FLOAT_COMPARE(double, float)
                            CC_FLOAT_COMPARE(float, double)
                            CC_FLOAT_COMPARE(float, float)
                        }
                    }
                    
                    CCAssertLog(0, "Unsupported value type");
                    break;
                }
                    
                default:
                    CCAssertLog(0, "Unsupported value type");
                    break;
            }
            break;
            
        default:
            CCAssertLog(0, "Unknown value type");
            break;
    }
    
    return FALSE;
}

