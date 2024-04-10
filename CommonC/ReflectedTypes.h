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

#ifndef CommonC_ReflectedTypes_h
#define CommonC_ReflectedTypes_h

#include <CommonC/Reflect.h>

#define CC_TYPE_ARRAY(x, count, ...) ARRAY(x, count)
#define CC_TYPE_0_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_1_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_2_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_3_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_4_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_5_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_6_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_7_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_8_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,
#define CC_TYPE_9_ARRAY(...) CC_TYPE_ARRAY, __VA_ARGS__,

#pragma mark - void

extern const CCReflectOpaque CC_REFLECT(void);


#pragma mark - Integer Types

extern const CCReflectInteger CC_REFLECT(char);
extern const CCReflectInteger CC_REFLECT(short);
extern const CCReflectInteger CC_REFLECT(int);
extern const CCReflectInteger CC_REFLECT(long);
extern const CCReflectInteger CC_REFLECT(long long);

extern const CCReflectInteger CC_REFLECT(unsigned char);
extern const CCReflectInteger CC_REFLECT(unsigned short);
extern const CCReflectInteger CC_REFLECT(unsigned int);
extern const CCReflectInteger CC_REFLECT(unsigned long);
extern const CCReflectInteger CC_REFLECT(unsigned long long);

extern const CCReflectInteger CC_REFLECT(int8_t);
extern const CCReflectInteger CC_REFLECT(int16_t);
extern const CCReflectInteger CC_REFLECT(int32_t);
extern const CCReflectInteger CC_REFLECT(int64_t);

extern const CCReflectInteger CC_REFLECT(uint8_t);
extern const CCReflectInteger CC_REFLECT(uint16_t);
extern const CCReflectInteger CC_REFLECT(uint32_t);
extern const CCReflectInteger CC_REFLECT(uint64_t);

extern const CCReflectInteger CC_REFLECT(ptrdiff_t);
extern const CCReflectInteger CC_REFLECT(intptr_t);
extern const CCReflectInteger CC_REFLECT(uintptr_t);
extern const CCReflectInteger CC_REFLECT(size_t);

extern const CCReflectInteger CC_REFLECT(int_fast8_t);
extern const CCReflectInteger CC_REFLECT(int_fast16_t);
extern const CCReflectInteger CC_REFLECT(int_fast32_t);
extern const CCReflectInteger CC_REFLECT(int_fast64_t);

extern const CCReflectInteger CC_REFLECT(int_least8_t);
extern const CCReflectInteger CC_REFLECT(int_least16_t);
extern const CCReflectInteger CC_REFLECT(int_least32_t);
extern const CCReflectInteger CC_REFLECT(int_least64_t);

extern const CCReflectInteger CC_REFLECT(uint_fast8_t);
extern const CCReflectInteger CC_REFLECT(uint_fast16_t);
extern const CCReflectInteger CC_REFLECT(uint_fast32_t);
extern const CCReflectInteger CC_REFLECT(uint_fast64_t);

extern const CCReflectInteger CC_REFLECT(uint_least8_t);
extern const CCReflectInteger CC_REFLECT(uint_least16_t);
extern const CCReflectInteger CC_REFLECT(uint_least32_t);
extern const CCReflectInteger CC_REFLECT(uint_least64_t);

extern const CCReflectInteger CC_REFLECT(intmax_t);
extern const CCReflectInteger CC_REFLECT(uintmax_t);


#pragma mark - Float Types

extern const CCReflectFloat CC_REFLECT(float);
extern const CCReflectFloat CC_REFLECT(double);
extern const CCReflectFloat CC_REFLECT(long double);


#pragma mark - Vector Types

#include <CommonC/Types.h>

extern const CCReflectStruct2 CC_REFLECT(CCVector2D);

extern const CCReflectStruct2 CC_REFLECT(CCVector2Di);

extern const CCReflectStruct3 CC_REFLECT(CCVector3D);
extern const CCReflectStruct3 CC_REFLECT(CCColourRGB);

extern const CCReflectStruct3 CC_REFLECT(CCVector3Di);
extern const CCReflectStruct3 CC_REFLECT(CCColourRGBi);

extern const CCReflectStruct4 CC_REFLECT(CCVector4D);
extern const CCReflectStruct4 CC_REFLECT(CCColourRGBA);

extern const CCReflectStruct4 CC_REFLECT(CCVector4Di);
extern const CCReflectStruct4 CC_REFLECT(CCColourRGBAi);

extern const CCReflectStruct2 CC_REFLECT(CCRect);

extern const CCReflectStruct2 CC_REFLECT(CCMatrix2);

extern const CCReflectStruct3 CC_REFLECT(CCMatrix3);

extern const CCReflectStruct4 CC_REFLECT(CCMatrix4);


#pragma mark - Arrays

typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
    const void *terminator;
} CCReflectTerminatedArray;

#define CC_REFLECT_TERMINATED_ARRAY(type, terminator_, maxSize) ((CCReflectTerminatedArray){ .opaque = CC_REFLECT_OPAQUE(maxSize, CCReflectTerminatedArrayMapper, CCReflectTerminatedArrayUnmapper), .elementType = type, .terminator = terminator_ })

void CCReflectTerminatedArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);
void CCReflectTerminatedArrayUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);


#pragma mark - Strings

extern const CCReflectOpaque CC_REFLECT(CCString);

extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v8));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v16));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v32));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v64));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v128));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v256));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v512));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v1024));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v4096));
extern const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v65536));


#pragma mark - CCAllocatorType

#include <CommonC/Allocator.h>

extern const CCReflectOpaque CC_REFLECT(CCAllocatorType);

extern const CCReflectStruct2 CC_REFLECT(CCDebugAllocatorInfo);

typedef CCReflectType (*CCAllocatorTypeDataFieldTypeCallback)(CCAllocatorType Allocator);

extern CCAllocatorTypeDataFieldTypeCallback CCAllocatorTypeDataFieldType;


#pragma mark - Pointer Types

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(void, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(void, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(void, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(char, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(char, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(char, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(short, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(short, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(short, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long long, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long long, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long long, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned char, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned char, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned char, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned short, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned short, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned short, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned int, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned int, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned int, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned long, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned long, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned long, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned long long, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned long long, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(unsigned long long, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int8_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int8_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int8_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int16_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int16_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int16_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int32_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int32_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int32_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int64_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int64_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int64_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint8_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint8_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint8_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint16_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint16_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint16_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint32_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint32_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint32_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint64_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint64_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint64_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ptrdiff_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ptrdiff_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ptrdiff_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(intptr_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(intptr_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(intptr_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uintptr_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uintptr_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uintptr_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(size_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(size_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(size_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast8_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast8_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast8_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast16_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast16_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast16_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast32_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast32_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast32_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast64_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast64_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_fast64_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least8_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least8_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least8_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least16_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least16_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least16_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least32_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least32_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least32_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least64_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least64_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(int_least64_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast8_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast8_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast8_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast16_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast16_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast16_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast32_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast32_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast32_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast64_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast64_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_fast64_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least8_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least8_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least8_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least16_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least16_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least16_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least32_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least32_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least32_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least64_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least64_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uint_least64_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(intmax_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(intmax_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(intmax_t, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uintmax_t, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uintmax_t, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(uintmax_t, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(float, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(float, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(float, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(double, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(double, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(double, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long double, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long double, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(long double, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector2D, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector2D, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector2D, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector2Di, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector2Di, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector2Di, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector3D, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector3D, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector3D, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGB, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGB, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGB, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector3Di, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector3Di, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector3Di, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBi, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBi, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBi, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector4D, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector4D, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector4D, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBA, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBA, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBA, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector4Di, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector4Di, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCVector4Di, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBAi, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBAi, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCColourRGBAi, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCRect, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCRect, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCRect, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix2, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix2, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix2, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix3, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix3, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix3, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix4, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix4, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCMatrix4, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v8), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v8), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v8), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v16), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v16), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v16), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v32), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v32), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v32), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v64), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v64), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v64), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v128), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v128), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v128), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v256), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v256), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v256), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v512), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v512), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v512), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v1024), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v1024), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v1024), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v4096), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v4096), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v4096), retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v65536), weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v65536), transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(ARRAY(char, v65536), retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCString, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCString, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCString, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCAllocatorType, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCAllocatorType, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCAllocatorType, retain, dynamic));

#endif
