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

#include "ReflectedTypes.h"

#pragma mark - void


static void VoidTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
}

static void VoidTypeUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
}

const CCReflectOpaque CC_REFLECT(void) = CC_REFLECT_OPAQUE(sizeof(void), VoidTypeMapper, VoidTypeUnmapper);

#pragma mark - Integer Types

#define REFLECT_SIGNED_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_SIGNED_INTEGER(type, CCReflectEndianNative)
#define REFLECT_SIGNED_FIXED_WIDTH_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(type, CCReflectEndianNative)

#define REFLECT_UNSIGNED_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_UNSIGNED_INTEGER(type, CCReflectEndianNative)
#define REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(type, CCReflectEndianNative)

REFLECT_SIGNED_INTEGER(char);
REFLECT_SIGNED_INTEGER(short);
REFLECT_SIGNED_INTEGER(int);
REFLECT_SIGNED_INTEGER(long);
REFLECT_SIGNED_INTEGER(long long);

REFLECT_UNSIGNED_INTEGER(unsigned char);
REFLECT_UNSIGNED_INTEGER(unsigned short);
REFLECT_UNSIGNED_INTEGER(unsigned int);
REFLECT_UNSIGNED_INTEGER(unsigned long);
REFLECT_UNSIGNED_INTEGER(unsigned long long);

REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int8_t);
REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int16_t);
REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int32_t);
REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int64_t);

REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint8_t);
REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint16_t);
REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint32_t);
REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint64_t);

REFLECT_SIGNED_INTEGER(ptrdiff_t);
REFLECT_SIGNED_INTEGER(intptr_t);
REFLECT_UNSIGNED_INTEGER(uintptr_t);
REFLECT_UNSIGNED_INTEGER(size_t);

REFLECT_SIGNED_INTEGER(int_fast8_t);
REFLECT_SIGNED_INTEGER(int_fast16_t);
REFLECT_SIGNED_INTEGER(int_fast32_t);
REFLECT_SIGNED_INTEGER(int_fast64_t);

REFLECT_SIGNED_INTEGER(int_least8_t);
REFLECT_SIGNED_INTEGER(int_least16_t);
REFLECT_SIGNED_INTEGER(int_least32_t);
REFLECT_SIGNED_INTEGER(int_least64_t);

REFLECT_UNSIGNED_INTEGER(uint_fast8_t);
REFLECT_UNSIGNED_INTEGER(uint_fast16_t);
REFLECT_UNSIGNED_INTEGER(uint_fast32_t);
REFLECT_UNSIGNED_INTEGER(uint_fast64_t);

REFLECT_UNSIGNED_INTEGER(uint_least8_t);
REFLECT_UNSIGNED_INTEGER(uint_least16_t);
REFLECT_UNSIGNED_INTEGER(uint_least32_t);
REFLECT_UNSIGNED_INTEGER(uint_least64_t);

REFLECT_SIGNED_INTEGER(intmax_t);
REFLECT_UNSIGNED_INTEGER(uintmax_t);

#pragma mark - Float Types

#define REFLECT_FLOAT(type) const CCReflectFloat CC_REFLECT(type) = CC_REFLECT_FLOAT(type, CCReflectEndianNative)

REFLECT_FLOAT(float);
REFLECT_FLOAT(double);
REFLECT_FLOAT(long double);

#pragma mark - Vector Types

const CCReflectStruct2 CC_REFLECT(CCVector2D) = CC_REFLECT_STRUCT(CCVector2D, (x, &CC_REFLECT(float)), (y, &CC_REFLECT(float)));

const CCReflectStruct2 CC_REFLECT(CCVector2Di) = CC_REFLECT_STRUCT(CCVector2D, (x, &CC_REFLECT(int32_t)), (y, &CC_REFLECT(int32_t)));

const CCReflectStruct3 CC_REFLECT(CCVector3D) = CC_REFLECT_STRUCT(CCVector3D, (x, &CC_REFLECT(float)), (y, &CC_REFLECT(float)), (z, &CC_REFLECT(float)));
const CCReflectStruct3 CC_REFLECT(CCColourRGB) = CC_REFLECT_STRUCT(CCColourRGB, (r, &CC_REFLECT(float)), (g, &CC_REFLECT(float)), (b, &CC_REFLECT(float)));

const CCReflectStruct3 CC_REFLECT(CCVector3Di) = CC_REFLECT_STRUCT(CCVector3Di, (x, &CC_REFLECT(int32_t)), (y, &CC_REFLECT(int32_t)), (z, &CC_REFLECT(int32_t)));
const CCReflectStruct3 CC_REFLECT(CCColourRGBi) = CC_REFLECT_STRUCT(CCColourRGBi, (r, &CC_REFLECT(int32_t)), (g, &CC_REFLECT(int32_t)), (b, &CC_REFLECT(int32_t)));

const CCReflectStruct4 CC_REFLECT(CCVector4D) = CC_REFLECT_STRUCT(CCVector4D, (x, &CC_REFLECT(float)), (y, &CC_REFLECT(float)), (z, &CC_REFLECT(float)), (w, &CC_REFLECT(float)));
const CCReflectStruct4 CC_REFLECT(CCColourRGBA) = CC_REFLECT_STRUCT(CCColourRGBA, (r, &CC_REFLECT(float)), (g, &CC_REFLECT(float)), (b, &CC_REFLECT(float)), (a, &CC_REFLECT(float)));

const CCReflectStruct4 CC_REFLECT(CCVector4Di) = CC_REFLECT_STRUCT(CCVector4Di, (x, &CC_REFLECT(int32_t)), (y, &CC_REFLECT(int32_t)), (z, &CC_REFLECT(int32_t)), (w, &CC_REFLECT(int32_t)));
const CCReflectStruct4 CC_REFLECT(CCColourRGBAi) = CC_REFLECT_STRUCT(CCColourRGBAi, (r, &CC_REFLECT(int32_t)), (g, &CC_REFLECT(int32_t)), (b, &CC_REFLECT(int32_t)), (a, &CC_REFLECT(int32_t)));

const CCReflectStruct2 CC_REFLECT(CCRect) = CC_REFLECT_STRUCT(CCRect, (position, &CC_REFLECT(CCVector2D)), (size, &CC_REFLECT(CCVector2D)));

const CCReflectStruct2 CC_REFLECT(CCMatrix2) = CC_REFLECT_STRUCT(CCMatrix2, (x, &CC_REFLECT(CCVector2D)), (y, &CC_REFLECT(CCVector2D)));

const CCReflectStruct3 CC_REFLECT(CCMatrix3) = CC_REFLECT_STRUCT(CCMatrix3, (x, &CC_REFLECT(CCVector3D)), (y, &CC_REFLECT(CCVector3D)), (z, &CC_REFLECT(CCVector3D)));

const CCReflectStruct4 CC_REFLECT(CCMatrix4) = CC_REFLECT_STRUCT(CCMatrix4, (x, &CC_REFLECT(CCVector4D)), (y, &CC_REFLECT(CCVector4D)), (z, &CC_REFLECT(CCVector4D)), (w, &CC_REFLECT(CCVector4D)));

#pragma mark - Arrays

void CCReflectTerminatedArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    const size_t ElementSize = CCReflectTypeSize(((const CCReflectTerminatedArray*)Type)->elementType);
    
    size_t Count = 0;
    while (memcmp(Data + (Count++ * ElementSize), ((const CCReflectTerminatedArray*)Type)->terminator, ElementSize));
    
    Handler(&CC_REFLECT_ARRAY(((const CCReflectTerminatedArray*)Type)->elementType, Count), Data, Args);
}

void CCReflectTerminatedArrayUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    Handler(Type, Data, Args);
}

#pragma mark - Strings

static void CCStringMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);
static void CCStringUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

const CCReflectOpaque CC_REFLECT(CCString) = CC_REFLECT_OPAQUE(sizeof(CCString), CCStringMapper, CCStringUnmapper);

static void CCStringMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    if (Handler == (CCReflectTypeHandler)CCReflectTransferHandler)
    {
        Handler(&CC_REFLECT(PTYPE(void, weak, dynamic)), Data, Args);
    }
    
    else if ((Handler == (CCReflectTypeHandler)CCReflectShareHandler) || (Handler == (CCReflectTypeHandler)CCReflectCopyHandler))
    {
        CCString String = CCStringCopy(*(CCString*)Data);
        
        Handler((CCStringIsTagged(String) ? &CC_REFLECT(PTYPE(void, weak, dynamic)) : &CC_REFLECT(PTYPE(void, retain, dynamic))), &String, Args);
        
        CCStringDestroy(String);
    }
    
    else
    {
        CC_STRING_TEMP_BUFFER(Buffer, *(CCString*)Data)
        {
            const size_t Length = CCStringGetLength(*(CCString*)Data);
            
            Handler(&CC_REFLECT_ARRAY(&CC_REFLECT(char), Length), Buffer, Args);
        }
    }
}

static void CCStringUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    if (*(const CCReflectTypeID*)Type == CCReflectTypeArray)
    {
        CCString String = CCStringCreateWithSize(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringEncodingUTF8, Data, ((const CCReflectArray*)Type)->count);
        
        Handler((CCStringIsTagged(String) ? &CC_REFLECT(PTYPE(void, weak, dynamic)) : &CC_REFLECT(PTYPE(void, retain, dynamic))), &String, Args);
        
        CCStringDestroy(String);
    }
    
    else
    {
        Handler(Type, Data, Args);
    }
}

const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v8)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 8);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v16)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 16);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v32)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 32);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v64)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 64);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v128)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 128);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v256)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 256);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v512)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 512);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v1024)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 1024);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v4096)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 4096);
const CCReflectTerminatedArray CC_REFLECT(ARRAY(char, v65536)) = CC_REFLECT_TERMINATED_ARRAY(&CC_REFLECT(char), &(char){ 0 }, sizeof(char) * 65536);

#pragma mark - CCAllocatorType

static void AllocatorTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);
static void AllocatorTypeUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

const CCReflectOpaque CC_REFLECT(CCAllocatorType) = CC_REFLECT_OPAQUE(sizeof(CCAllocatorType), AllocatorTypeMapper, AllocatorTypeUnmapper);

static void AllocatorTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    CCReflectStruct2 AllocatorType = CC_REFLECT_STRUCT(CCAllocatorType, (allocator, &CC_REFLECT(int)), (data, CCAllocatorTypeDataFieldType(*(const CCAllocatorType*)Data)));
    
    Handler(&AllocatorType, Data, Args);
}

static void AllocatorTypeUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    Handler(Type, Data, Args);
}

const CCReflectStruct2 CC_REFLECT(CCDebugAllocatorInfo) = CC_REFLECT_STRUCT(CCDebugAllocatorInfo, (file, &CC_REFLECT(PTYPE(ARRAY(char, v4096), weak, dynamic))), (line, &CC_REFLECT(int)));

static const CCReflectDynamicPointer CCDebugAllocatorDataPtr = CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(CCDebugAllocatorInfo), CCReflectOwnershipWeak);
static const CCReflectDynamicPointer CCAlignedAllocatorDataPtr = CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(size_t), CCReflectOwnershipWeak);

CCReflectType CCAllocatorTypeDataFieldTypeDefaults(CCAllocatorType Allocator)
{
    switch (Allocator.allocator)
    {
        case CC_CUSTOM_ALLOCATOR(NULL, NULL, NULL).allocator:
            CCAssertLog(0, "Unsupported allocator");
            break;
            
        case CC_CALLBACK_ALLOCATOR(NULL).allocator:
            CCAssertLog(0, "Unsupported allocator");
            break;
            
        case CC_ALIGNED_ALLOCATOR(0).allocator:
            return &CCAlignedAllocatorDataPtr;
            
        case CC_DEBUG_ALLOCATOR.allocator:
            return &CCDebugAllocatorDataPtr;
            
        case CC_ZONE_ALLOCATOR(NULL).allocator:
            CCAssertLog(0, "Unsupported allocator");
            break;
    }
    
    return &CC_REFLECT(PTYPE(void, weak, dynamic));
}

CCAllocatorTypeDataFieldTypeCallback CCAllocatorTypeDataFieldType = CCAllocatorTypeDataFieldTypeDefaults;

#pragma mark - Pointer Types

#define REFLECT_DYNAMIC_POINTERS(type) \
const CCReflectDynamicPointer CC_REFLECT(PTYPE(type, weak, dynamic)) = CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(type), CCReflectOwnershipWeak); \
const CCReflectDynamicPointer CC_REFLECT(PTYPE(type, transfer, dynamic)) = CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(type), CCReflectOwnershipTransfer); \
const CCReflectDynamicPointer CC_REFLECT(PTYPE(type, retain, dynamic)) = CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(type), CCReflectOwnershipRetain);

REFLECT_DYNAMIC_POINTERS(void);

REFLECT_DYNAMIC_POINTERS(char);
REFLECT_DYNAMIC_POINTERS(short);
REFLECT_DYNAMIC_POINTERS(int);
REFLECT_DYNAMIC_POINTERS(long);
REFLECT_DYNAMIC_POINTERS(long long);

REFLECT_DYNAMIC_POINTERS(unsigned char);
REFLECT_DYNAMIC_POINTERS(unsigned short);
REFLECT_DYNAMIC_POINTERS(unsigned int);
REFLECT_DYNAMIC_POINTERS(unsigned long);
REFLECT_DYNAMIC_POINTERS(unsigned long long);

REFLECT_DYNAMIC_POINTERS(int8_t);
REFLECT_DYNAMIC_POINTERS(int16_t);
REFLECT_DYNAMIC_POINTERS(int32_t);
REFLECT_DYNAMIC_POINTERS(int64_t);

REFLECT_DYNAMIC_POINTERS(uint8_t);
REFLECT_DYNAMIC_POINTERS(uint16_t);
REFLECT_DYNAMIC_POINTERS(uint32_t);
REFLECT_DYNAMIC_POINTERS(uint64_t);

REFLECT_DYNAMIC_POINTERS(ptrdiff_t);
REFLECT_DYNAMIC_POINTERS(intptr_t);
REFLECT_DYNAMIC_POINTERS(uintptr_t);
REFLECT_DYNAMIC_POINTERS(size_t);

REFLECT_DYNAMIC_POINTERS(int_fast8_t);
REFLECT_DYNAMIC_POINTERS(int_fast16_t);
REFLECT_DYNAMIC_POINTERS(int_fast32_t);
REFLECT_DYNAMIC_POINTERS(int_fast64_t);

REFLECT_DYNAMIC_POINTERS(int_least8_t);
REFLECT_DYNAMIC_POINTERS(int_least16_t);
REFLECT_DYNAMIC_POINTERS(int_least32_t);
REFLECT_DYNAMIC_POINTERS(int_least64_t);

REFLECT_DYNAMIC_POINTERS(uint_fast8_t);
REFLECT_DYNAMIC_POINTERS(uint_fast16_t);
REFLECT_DYNAMIC_POINTERS(uint_fast32_t);
REFLECT_DYNAMIC_POINTERS(uint_fast64_t);

REFLECT_DYNAMIC_POINTERS(uint_least8_t);
REFLECT_DYNAMIC_POINTERS(uint_least16_t);
REFLECT_DYNAMIC_POINTERS(uint_least32_t);
REFLECT_DYNAMIC_POINTERS(uint_least64_t);

REFLECT_DYNAMIC_POINTERS(intmax_t);
REFLECT_DYNAMIC_POINTERS(uintmax_t);

REFLECT_DYNAMIC_POINTERS(float);
REFLECT_DYNAMIC_POINTERS(double);
REFLECT_DYNAMIC_POINTERS(long double);

REFLECT_DYNAMIC_POINTERS(CCVector2D);
REFLECT_DYNAMIC_POINTERS(CCVector2Di);
REFLECT_DYNAMIC_POINTERS(CCVector3D);
REFLECT_DYNAMIC_POINTERS(CCColourRGB);
REFLECT_DYNAMIC_POINTERS(CCVector3Di);
REFLECT_DYNAMIC_POINTERS(CCColourRGBi);
REFLECT_DYNAMIC_POINTERS(CCVector4D);
REFLECT_DYNAMIC_POINTERS(CCColourRGBA);
REFLECT_DYNAMIC_POINTERS(CCVector4Di);
REFLECT_DYNAMIC_POINTERS(CCColourRGBAi);
REFLECT_DYNAMIC_POINTERS(CCRect);
REFLECT_DYNAMIC_POINTERS(CCMatrix2);
REFLECT_DYNAMIC_POINTERS(CCMatrix3);
REFLECT_DYNAMIC_POINTERS(CCMatrix4);

REFLECT_DYNAMIC_POINTERS(ARRAY(char, v8));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v16));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v32));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v64));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v128));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v256));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v512));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v1024));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v4096));
REFLECT_DYNAMIC_POINTERS(ARRAY(char, v65536));

REFLECT_DYNAMIC_POINTERS(CCString);

REFLECT_DYNAMIC_POINTERS(CCAllocatorType);
