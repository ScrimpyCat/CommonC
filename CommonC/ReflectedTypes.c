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

const char *CCReflectTypeNameDefaults(CCReflectType Type)
{
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
            if (((const CCReflectPointer*)Type)->storage == CCReflectStorageStatic)
            {
                if (Type == &CC_REFLECT(CCReflectTypeMapper)) return "CCReflectTypeMapper";
                else if (Type == &CC_REFLECT(CCReflectTypeUnmapper)) return "CCReflectTypeUnmapper";
                else if (Type == &CC_REFLECT(CCCollectionElementDestructor)) return "CCCollectionElementDestructor";
            }
            break;
            
        case CCReflectTypeInteger:
            if (Type == &CC_REFLECT(CCReflectTypeID)) return "CCReflectTypeID";
            else if (Type == &CC_REFLECT(CCReflectStorage)) return "CCReflectStorage";
            else if (Type == &CC_REFLECT(CCReflectOwnership)) return "CCReflectOwnership";
            else if (Type == &CC_REFLECT(CCReflectEndian)) return "CCReflectEndian";
            else if (Type == &CC_REFLECT(_Bool)) return "_Bool";
            else if (Type == &CC_REFLECT(char)) return "char";
            else if (Type == &CC_REFLECT(short)) return "short";
            else if (Type == &CC_REFLECT(int)) return "int";
            else if (Type == &CC_REFLECT(long)) return "long";
            else if (Type == &CC_REFLECT(long long)) return "long long";
            else if (Type == &CC_REFLECT(unsigned char)) return "unsigned char";
            else if (Type == &CC_REFLECT(unsigned short)) return "unsigned short";
            else if (Type == &CC_REFLECT(unsigned int)) return "unsigned int";
            else if (Type == &CC_REFLECT(unsigned long)) return "unsigned long";
            else if (Type == &CC_REFLECT(unsigned long long)) return "unsigned long long";
            else if (Type == &CC_REFLECT(int8_t)) return "int8_t";
            else if (Type == &CC_REFLECT(int16_t)) return "int16_t";
            else if (Type == &CC_REFLECT(int32_t)) return "int32_t";
            else if (Type == &CC_REFLECT(int64_t)) return "int64_t";
            else if (Type == &CC_REFLECT(uint8_t)) return "uint8_t";
            else if (Type == &CC_REFLECT(uint16_t)) return "uint16_t";
            else if (Type == &CC_REFLECT(uint32_t)) return "uint32_t";
            else if (Type == &CC_REFLECT(uint64_t)) return "uint64_t";
            else if (Type == &CC_REFLECT(ptrdiff_t)) return "ptrdiff_t";
            else if (Type == &CC_REFLECT(intptr_t)) return "intptr_t";
            else if (Type == &CC_REFLECT(uintptr_t)) return "uintptr_t";
            else if (Type == &CC_REFLECT(size_t)) return "size_t";
            else if (Type == &CC_REFLECT(int_fast8_t)) return "int_fast8_t";
            else if (Type == &CC_REFLECT(int_fast16_t)) return "int_fast16_t";
            else if (Type == &CC_REFLECT(int_fast32_t)) return "int_fast32_t";
            else if (Type == &CC_REFLECT(int_fast64_t)) return "int_fast64_t";
            else if (Type == &CC_REFLECT(int_least8_t)) return "int_least8_t";
            else if (Type == &CC_REFLECT(int_least16_t)) return "int_least16_t";
            else if (Type == &CC_REFLECT(int_least32_t)) return "int_least32_t";
            else if (Type == &CC_REFLECT(int_least64_t)) return "int_least64_t";
            else if (Type == &CC_REFLECT(uint_fast8_t)) return "uint_fast8_t";
            else if (Type == &CC_REFLECT(uint_fast16_t)) return "uint_fast16_t";
            else if (Type == &CC_REFLECT(uint_fast32_t)) return "uint_fast32_t";
            else if (Type == &CC_REFLECT(uint_fast64_t)) return "uint_fast64_t";
            else if (Type == &CC_REFLECT(uint_least8_t)) return "uint_least8_t";
            else if (Type == &CC_REFLECT(uint_least16_t)) return "uint_least16_t";
            else if (Type == &CC_REFLECT(uint_least32_t)) return "uint_least32_t";
            else if (Type == &CC_REFLECT(uint_least64_t)) return "uint_least64_t";
            else if (Type == &CC_REFLECT(intmax_t)) return "intmax_t";
            else if (Type == &CC_REFLECT(uintmax_t)) return "uintmax_t";
            else if (Type == &CC_REFLECT(CCCollectionHint)) return "CCCollectionHint";
            break;
            
        case CCReflectTypeFloat:
            if (Type == &CC_REFLECT(float)) return "float";
            else if (Type == &CC_REFLECT(double)) return "double";
            else if (Type == &CC_REFLECT(long double)) return "long double";
            break;
            
        case CCReflectTypeStruct:
            if (Type == &CC_REFLECT(CCReflectPointer)) return "CCReflectPointer";
            else if (Type == &CC_REFLECT(CCReflectStaticPointer)) return "CCReflectStaticPointer";
            else if (Type == &CC_REFLECT(CCReflectDynamicPointer)) return "CCReflectDynamicPointer";
            else if (Type == &CC_REFLECT(CCReflectInteger)) return "CCReflectInteger";
            else if (Type == &CC_REFLECT(CCReflectFloat)) return "CCReflectFloat";
            else if (Type == &CC_REFLECT(CCReflectStructField)) return "CCReflectStructField";
            else if (Type == &CC_REFLECT(CCReflectStruct)) return "CCReflectStruct";
            else if (Type == &CC_REFLECT(CCReflectArray)) return "CCReflectArray";
            else if (Type == &CC_REFLECT(CCReflectOpaque)) return "CCReflectOpaque";
            else if (Type == &CC_REFLECT(CCVector2D)) return "CCVector2D";
            else if (Type == &CC_REFLECT(CCVector2Di)) return "CCVector2Di";
            else if (Type == &CC_REFLECT(CCVector3D)) return "CCVector3D";
            else if (Type == &CC_REFLECT(CCColourRGB)) return "CCColourRGB";
            else if (Type == &CC_REFLECT(CCVector3Di)) return "CCVector3Di";
            else if (Type == &CC_REFLECT(CCColourRGBi)) return "CCColourRGBi";
            else if (Type == &CC_REFLECT(CCVector4D)) return "CCVector4D";
            else if (Type == &CC_REFLECT(CCColourRGBA)) return "CCColourRGBA";
            else if (Type == &CC_REFLECT(CCVector4Di)) return "CCVector4Di";
            else if (Type == &CC_REFLECT(CCColourRGBAi)) return "CCColourRGBAi";
            else if (Type == &CC_REFLECT(CCRect)) return "CCRect";
            else if (Type == &CC_REFLECT(CCMatrix2)) return "CCMatrix2";
            else if (Type == &CC_REFLECT(CCMatrix3)) return "CCMatrix3";
            else if (Type == &CC_REFLECT(CCMatrix4)) return "CCMatrix4";
            else if (Type == &CC_REFLECT(CCDebugAllocatorInfo)) return "CCDebugAllocatorInfo";
            break;
            
        case CCReflectTypeOpaque:
            if (Type == &CC_REFLECT(CCReflectType)) return "CCReflectType";
            else if (Type == &CC_REFLECT(void)) return "void";
            else if (Type == &CC_REFLECT(CCString)) return "CCString";
            else if (Type == &CC_REFLECT(ARRAY(char, v8))) return "char[8]";
            else if (Type == &CC_REFLECT(ARRAY(char, v16))) return "char[16]";
            else if (Type == &CC_REFLECT(ARRAY(char, v32))) return "char[32]";
            else if (Type == &CC_REFLECT(ARRAY(char, v64))) return "char[64]";
            else if (Type == &CC_REFLECT(ARRAY(char, v128))) return "char[128]";
            else if (Type == &CC_REFLECT(ARRAY(char, v256))) return "char[256]";
            else if (Type == &CC_REFLECT(ARRAY(char, v512))) return "char[512]";
            else if (Type == &CC_REFLECT(ARRAY(char, v1024))) return "char[1024]";
            else if (Type == &CC_REFLECT(ARRAY(char, v4096))) return "char[4096]";
            else if (Type == &CC_REFLECT(ARRAY(char, v65536))) return "char[65536]";
            else if (Type == &CC_REFLECT(CCAllocatorType)) return "CCAllocatorType";
            else
            {
                if ((((const CCReflectOpaque*)Type)->map == CCReflectCCArrayMapper) && (((const CCReflectOpaque*)Type)->unmap == CCReflectCCArrayUnmapper)) return "CCArray";
                else if ((((const CCReflectOpaque*)Type)->map == CCReflectCCCollectionMapper) && (((const CCReflectOpaque*)Type)->unmap == CCReflectCCCollectionUnmapper)) return "CCCollection";
            }
            break;
            
        case CCReflectTypeArray:
            break;
            
        case CCReflectTypeValidator:
            break;
            
        case CCReflectTypeEnumerable:
            break;
    }
    
    return NULL;
}

#pragma mark - void

static void VoidTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
}

static void VoidTypeUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
}

const CCReflectOpaque CC_REFLECT(void) = CC_REFLECT_OPAQUE(sizeof(void), sizeof(CCReflectOpaque), VoidTypeMapper, VoidTypeUnmapper);

#pragma mark - Integer Types

#define REFLECT_SIGNED_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_SIGNED_INTEGER(type, CCReflectEndianNative)
#define REFLECT_SIGNED_FIXED_WIDTH_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(type, CCReflectEndianNative)

#define REFLECT_UNSIGNED_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_UNSIGNED_INTEGER(type, CCReflectEndianNative)
#define REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(type) const CCReflectInteger CC_REFLECT(type) = CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(type, CCReflectEndianNative)

REFLECT_UNSIGNED_INTEGER(_Bool);

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

void CCReflectTerminatedArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    const size_t ElementSize = CCReflectTypeSize(((const CCReflectTerminatedArray*)Type)->elementType);
    
    size_t Count = 0;
    while (memcmp(Data + (Count++ * ElementSize), ((const CCReflectTerminatedArray*)Type)->terminator, ElementSize));
    
    Handler(&CC_REFLECT_ARRAY(((const CCReflectTerminatedArray*)Type)->elementType, Count), Data, Args);
}

void CCReflectTerminatedArrayUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    Handler(MappedType, Data, Args);
}

#pragma mark - Strings

static void CCStringMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void CCStringUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectOpaque CC_REFLECT(CCString) = CC_REFLECT_OPAQUE(sizeof(CCString), sizeof(CCReflectOpaque), CCStringMapper, CCStringUnmapper);

static void CCStringMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if (Intent == CCReflectMapIntentTransfer)
    {
        Handler(&CC_REFLECT(PTYPE(void, weak, dynamic)), Data, Args);
    }
    
    else if ((Intent == CCReflectMapIntentShare) || (Intent == CCReflectMapIntentCopy))
    {
        CCString String = CCStringCopy(*(CCString*)Data);
        
        Handler((CCStringIsTagged(String) ? &CC_REFLECT(PTYPE(void, weak, dynamic)) : &CC_REFLECT(PTYPE(void, retain, dynamic))), &String, Args);
        
        CCStringDestroy(String);
    }
    
    else if (Handler == (CCReflectTypeHandler)CCReflectPrintHandler)
    {
        CCReflectPrintIndent(((CCReflectPrintHandlerArgs*)Args)->file, ((CCReflectPrintHandlerArgs*)Args)->indentation, ((CCReflectPrintHandlerArgs*)Args)->indentCount, ((CCReflectPrintHandlerArgs*)Args)->shouldIndent);
        
        if (*(CCString*)Data)
        {
            CC_STRING_TEMP_BUFFER(Buffer, *(CCString*)Data)
            {
                fprintf(((CCReflectPrintHandlerArgs*)Args)->file, "\"%s\"", Buffer);
            }
        }
        
        else
        {
            fprintf(((CCReflectPrintHandlerArgs*)Args)->file, "(CCString)0");
        }
    }
    
    else
    {
        CC_STRING_TEMP_BUFFER(Buffer, *(CCString*)Data)
        {
            const size_t Length = CCStringGetLength(*(CCString*)Data);
            
            Handler(&CC_REFLECT_ARRAY(&CC_REFLECT(unsigned char), Length), Buffer, Args);
        }
    }
}

static void CCStringUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if (*(const CCReflectTypeID*)MappedType == CCReflectTypeArray)
    {
        CCString String = CCStringCreateWithSize(Allocator, CCStringHintCopy | CCStringEncodingUTF8, Data, ((const CCReflectArray*)MappedType)->count);
        
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

static void AllocatorTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void AllocatorTypeUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectOpaque CC_REFLECT(CCAllocatorType) = CC_REFLECT_OPAQUE(sizeof(CCAllocatorType), sizeof(CCReflectOpaque), AllocatorTypeMapper, AllocatorTypeUnmapper);

static void AllocatorTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCReflectStruct2 AllocatorType = CC_REFLECT_STRUCT(CCAllocatorType, (allocator, &CC_REFLECT(int)), (data, CCAllocatorTypeDataFieldType(*(const CCAllocatorType*)Data)));
    
    Handler(&AllocatorType, Data, Args);
}

static void AllocatorTypeUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    Handler(MappedType, Data, Args);
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

static void CCMemoryDestructorCallbackMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void CCMemoryDestructorCallbackUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectStaticPointer CC_REFLECT(CCMemoryDestructorCallback) = CC_REFLECT_STATIC_POINTER(&CC_REFLECT(void), CCReflectOwnershipWeak, CCMemoryDestructorCallbackMapper, CCMemoryDestructorCallbackUnmapper);

CCReflectTypeMapper CCMemoryDestructorCallbackMap = CCMemoryDestructorCallbackMapDefaults;
CCReflectTypeUnmapper CCMemoryDestructorCallbackUnmap = CCMemoryDestructorCallbackUnmapDefaults;

static void CCMemoryDestructorCallbackMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCMemoryDestructorCallbackMap(Type, Data, Args, Handler, Zone, Allocator, Intent);
}

static void CCMemoryDestructorCallbackUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCMemoryDestructorCallbackUnmap(Type, MappedType, Data, Args, Handler, Zone, Allocator);
}

void CCMemoryDestructorCallbackMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCAssertLog(0, "Unknown destructor type");
}

void CCMemoryDestructorCallbackUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCAssertLog(0, "Unknown destructor type");
}


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

REFLECT_DYNAMIC_POINTERS(CCString); // TODO: need destructor

REFLECT_DYNAMIC_POINTERS(CCAllocatorType);

REFLECT_DYNAMIC_POINTERS(CCReflectType);
REFLECT_DYNAMIC_POINTERS(CCReflectTypeID);
REFLECT_DYNAMIC_POINTERS(CCReflectStorage);
REFLECT_DYNAMIC_POINTERS(CCReflectOwnership);
REFLECT_DYNAMIC_POINTERS(CCReflectPointer);
REFLECT_DYNAMIC_POINTERS(CCReflectStaticPointer);
REFLECT_DYNAMIC_POINTERS(CCReflectDynamicPointer);
REFLECT_DYNAMIC_POINTERS(CCReflectEndian);
REFLECT_DYNAMIC_POINTERS(CCReflectInteger);
REFLECT_DYNAMIC_POINTERS(CCReflectFloat);
REFLECT_DYNAMIC_POINTERS(CCReflectStructField);
REFLECT_DYNAMIC_POINTERS(CCReflectStruct);
REFLECT_DYNAMIC_POINTERS(CCReflectArray);
REFLECT_DYNAMIC_POINTERS(CCReflectTypeMapper);
REFLECT_DYNAMIC_POINTERS(CCReflectTypeUnmapper);
REFLECT_DYNAMIC_POINTERS(CCReflectOpaque);
REFLECT_DYNAMIC_POINTERS(CCReflectEnumerable);
REFLECT_DYNAMIC_POINTERS(CCReflectValidation);
REFLECT_DYNAMIC_POINTERS(CCReflectValue);
REFLECT_DYNAMIC_POINTERS(CCReflectValidator);

#pragma mark - Reflected Types

static void ReflectTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void ReflectTypeUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectOpaque CC_REFLECT(CCReflectType) = CC_REFLECT_OPAQUE(sizeof(void*), sizeof(CCReflectOpaque), ReflectTypeMapper, ReflectTypeUnmapper);

const CCReflectInteger CC_REFLECT(CCReflectTypeID) = CC_REFLECT_INTEGER(CCReflectTypeID, CCReflectEndianNative);

const CCReflectInteger CC_REFLECT(CCReflectStorage) = CC_REFLECT_INTEGER(CCReflectStorage, CCReflectEndianNative);

const CCReflectInteger CC_REFLECT(CCReflectOwnership) = CC_REFLECT_INTEGER(CCReflectOwnership, CCReflectEndianNative);

const CCReflectStruct4 CC_REFLECT(CCReflectPointer) = CC_REFLECT_STRUCT(CCReflectPointer,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (type, &CC_REFLECT(CCReflectType)),
    (storage, &CC_REFLECT(CCReflectStorage)),
    (ownership, &CC_REFLECT(CCReflectOwnership))
);

const CCReflectStruct3 CC_REFLECT(CCReflectDynamicPointer) = CC_REFLECT_STRUCT(CCReflectDynamicPointer,
    (pointer, &CC_REFLECT(CCReflectPointer)),
    (allocator, &CC_REFLECT(CCAllocatorType)),
    (destructor, &CC_REFLECT(CCMemoryDestructorCallback))
);

const CCReflectInteger CC_REFLECT(CCReflectEndian) = CC_REFLECT_INTEGER(CCReflectEndian, CCReflectEndianNative);

const CCReflectStruct5 CC_REFLECT(CCReflectInteger) = CC_REFLECT_STRUCT(CCReflectInteger,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (size, &CC_REFLECT(size_t)),
    (endian, &CC_REFLECT(CCReflectEndian)),
    (sign, &CC_REFLECT(_Bool)),
    (fixed, &CC_REFLECT(_Bool))
);

const CCReflectStruct3 CC_REFLECT(CCReflectFloat) = CC_REFLECT_STRUCT(CCReflectFloat,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (size, &CC_REFLECT(size_t)),
    (endian, &CC_REFLECT(CCReflectEndian))
);

const CCReflectStruct3 CC_REFLECT(CCReflectStructField) = CC_REFLECT_STRUCT(CCReflectStructField,
    (name, &CC_REFLECT(CCString)),
    (offset, &CC_REFLECT(size_t)),
    (type, &CC_REFLECT(CCReflectType))
);

const CCReflectStruct4 CC_REFLECT(CCReflectStruct) = CC_REFLECT_STRUCT(CCReflectStruct,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (size, &CC_REFLECT(size_t)),
    (count, &CC_REFLECT(size_t)),
    (fields, &CC_REFLECT_ARRAY(&CC_REFLECT(CCReflectStructField), 0))
);

#define CC_REFLECT_STRUCT_TYPE(count_) \
CC_REFLECT_STRUCT(CCReflectStruct, \
    (id, &CC_REFLECT(CCReflectTypeID)), \
    (size, &CC_REFLECT(size_t)), \
    (count, &CC_REFLECT(size_t)), \
    (fields, &CC_REFLECT_ARRAY(&CC_REFLECT(CCReflectStructField), count_)) \
)

const CCReflectStruct3 CC_REFLECT(CCReflectArray) = CC_REFLECT_STRUCT(CCReflectArray,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (type, &CC_REFLECT(CCReflectType)),
    (count, &CC_REFLECT(size_t))
);

const CCReflectStruct3 CC_REFLECT(CCReflectEnumerable) = CC_REFLECT_STRUCT(CCReflectEnumerable,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (type, &CC_REFLECT(CCReflectType)),
    (count, &CC_REFLECT(size_t))
);

static void MapFunctionMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void MapFunctionUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);
static void UnmapFunctionMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void UnmapFunctionUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectStaticPointer CC_REFLECT(CCReflectTypeMapper) = CC_REFLECT_STATIC_POINTER(&CC_REFLECT(void), CCReflectOwnershipWeak, MapFunctionMapper, MapFunctionUnmapper);
const CCReflectStaticPointer CC_REFLECT(CCReflectTypeUnmapper) = CC_REFLECT_STATIC_POINTER(&CC_REFLECT(void), CCReflectOwnershipWeak, UnmapFunctionMapper, UnmapFunctionUnmapper);

CCReflectTypeMapper CCReflectMapperMap = CCReflectTypeMapperMapDefaults;
CCReflectTypeUnmapper CCReflectMapperUnmap = CCReflectTypeMapperUnmapDefaults;

static void MapFunctionMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCReflectMapperMap(Type, Data, Args, Handler, Zone, Allocator, Intent);
}

static void MapFunctionUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCReflectMapperUnmap(Type, MappedType, Data, Args, Handler, Zone, Allocator);
}

void CCReflectTypeMapperMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_VALUE_IS_POINTER,
        CCStringMapper
    )
    
    else CCAssertLog(0, "Unknown map function");
}

void CCReflectTypeMapperUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{    
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_POINTER(CCReflectTypeMapper),
        CCStringMapper
    )
    
    CCAssertLog(0, "Unknown mapper function");
}

CCReflectTypeMapper CCReflectUnmapperMap = CCReflectTypeUnmapperMapDefaults;
CCReflectTypeUnmapper CCReflectUnmapperUnmap = CCReflectTypeUnmapperUnmapDefaults;

static void UnmapFunctionMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCReflectUnmapperMap(Type, Data, Args, Handler, Zone, Allocator, Intent);
}

static void UnmapFunctionUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCReflectUnmapperUnmap(Type, MappedType, Data, Args, Handler, Zone, Allocator);
}

void CCReflectTypeUnmapperMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_VALUE_IS_POINTER,
        CCStringUnmapper
    )
    
    else CCAssertLog(0, "Unknown unmapper function");
}

void CCReflectTypeUnmapperUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_POINTER(CCReflectTypeUnmapper),
        CCStringUnmapper
    )
    
    CCAssertLog(0, "Unknown unmapper function");
}

const CCReflectStruct5 CC_REFLECT(CCReflectOpaque) = CC_REFLECT_STRUCT(CCReflectOpaque,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (size, &CC_REFLECT(size_t)),
    (typeSize, &CC_REFLECT(size_t)),
    (map, &CC_REFLECT(CCReflectTypeMapper)),
    (unmap, &CC_REFLECT(CCReflectTypeUnmapper))
);

void CCReflectOpaqueTypeDescriptorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
#define CC_REFLECT_VALUE_OPAQUE_MAPPER(value) CCReflect##value##Mapper
#define CC_REFLECT_VALUE_OPAQUE_UNMAPPER(value) CCReflect##value##Unmapper
    
#define CC_REFLECT_STATEFUL_VALUE_STRUCT_NAME(type) CCReflectMapped##type
#define CC_REFLECT_STATEFUL_VALUE_TYPE(type) CCReflect##type
    
#define CC_REFLECT_STATEFUL_VALUE_TYPE_CONSTRUCTOR(type) CC_REFLECT_##type
    
#define CC_REFLECT_STATEFUL_VALUE_OPAQUE_FIELD opaque
    
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_VALUE_IS_TYPE,
        void,
        CCReflectType,
        CCAllocatorType,
        CCString
    )
    
    else if CC_REFLECT_MAP_STATEFUL_VALUES_WHEN(CC_REFLECT_VALUE_IS_OPAQUE,
        (CCCollection, (elementType, CCReflectType), (allocator, CCAllocatorType), (hint, CCCollectionHint), (elementDestructor, CCCollectionElementDestructor))
    )
    
    else CCAssertLog(0, "Unknown opaque type");
}

void CCReflectOpaqueTypeDescriptorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_OPAQUE,
        void,
        CCReflectType,
        CCAllocatorType,
        CCString
    )
        
    else if CC_REFLECT_UNMAP_STATEFUL_VALUES(CC_REFLECT_VALUE_TO_STRUCT,
        (CCCollection, (elementType, CCReflectType), (allocator, CCAllocatorType), (hint, CCCollectionHint), (elementDestructor, CCCollectionElementDestructor))
    )
    
    CCAssertLog(0, "Unknown opaque type");
}

const CCReflectStruct3 CC_REFLECT(CCReflectStaticPointer) = CC_REFLECT_STRUCT(CCReflectStaticPointer,
    (pointer, &CC_REFLECT(CCReflectPointer)),
    (map, &CC_REFLECT(CCReflectTypeMapper)),
    (unmap, &CC_REFLECT(CCReflectTypeUnmapper))
);

CCReflectTypeMapper CCReflectOpaqueTypeDescriptorMap = CCReflectOpaqueTypeDescriptorMapDefaults;
CCReflectTypeUnmapper CCReflectOpaqueTypeDescriptorUnmap = CCReflectOpaqueTypeDescriptorUnmapDefaults;

void CCReflectStaticPointerTypeDescriptorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_STATIC_POINTER_IS_TYPE,
        CCReflectTypeMapper,
        CCReflectTypeUnmapper,
        CCCollectionElementDestructor
    )
    
    else CCAssertLog(0, "Unknown static pointer type");
}

void CCReflectStaticPointerTypeDescriptorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{    
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_STATIC_POINTER,
        CCReflectTypeMapper,
        CCReflectTypeUnmapper,
        CCCollectionElementDestructor
    )
    
    CCAssertLog(0, "Unknown static pointer type");
}

CCReflectTypeMapper CCReflectStaticPointerTypeDescriptorMap = CCReflectStaticPointerTypeDescriptorMapDefaults;
CCReflectTypeUnmapper CCReflectStaticPointerTypeDescriptorUnmap = CCReflectStaticPointerTypeDescriptorUnmapDefaults;

#include "ValidateMinimum.h"

static void ValidationMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void ValidationUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectStaticPointer CC_REFLECT(CCReflectValidation) = CC_REFLECT_STATIC_POINTER(&CC_REFLECT(void), CCReflectOwnershipWeak, ValidationMapper, ValidationUnmapper);

CCReflectTypeMapper CCReflectValidationMap = CCReflectValidationMapDefaults;
CCReflectTypeUnmapper CCReflectValidationUnmap = CCReflectValidationUnmapDefaults;

static void ValidationMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCReflectValidationMap(Type, Data, Args, Handler, Zone, Allocator, Intent);
}

static void ValidationUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCReflectValidationUnmap(Type, MappedType, Data, Args, Handler, Zone, Allocator);
}

void CCReflectValidationMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_VALUE_IS_POINTER,
        CCReflectValidateMinimum
    )
    
    else CCAssertLog(0, "Unknown map function");
}

void CCReflectValidationUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_POINTER(CCReflectValidation),
        CCReflectValidateMinimum
    )
    
    CCAssertLog(0, "Unknown mapper function");
}

const CCReflectStruct2 CC_REFLECT(CCReflectValue) = CC_REFLECT_STRUCT(CCReflectValue,
    (type, &CC_REFLECT(CCReflectType)),
    (data, &CC_REFLECT(PTYPE(void, weak, dynamic)))
);

const CCReflectStruct5 CC_REFLECT(CCReflectValidator) = CC_REFLECT_STRUCT(CCReflectValidator,
    (id, &CC_REFLECT(CCReflectTypeID)),
    (type, &CC_REFLECT(CCReflectType)),
    (validate, &CC_REFLECT(CCReflectValidation)),
    (success, &CC_REFLECT(CCReflectValue)),
    (failure, &CC_REFLECT(CCReflectValue))
);

static void ReflectTypeMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCReflectType DataType = *(CCReflectType*)Data;
    
    switch (*(const CCReflectTypeID*)DataType)
    {
        case CCReflectTypePointer:
            switch (((CCReflectPointer*)DataType)->storage)
            {
                case CCReflectStorageStatic:
                    Handler(&CC_REFLECT(PTYPE(CCReflectStaticPointer, weak, dynamic)), Data, Args);
                    break;
                    
                case CCReflectStorageDynamic:
                    Handler(&CC_REFLECT(PTYPE(CCReflectDynamicPointer, weak, dynamic)), Data, Args);
                    break;
            }
            break;
            
        case CCReflectTypeInteger:
            Handler(&CC_REFLECT(PTYPE(CCReflectInteger, weak, dynamic)), Data, Args);
            break;
            
        case CCReflectTypeFloat:
            Handler(&CC_REFLECT(PTYPE(CCReflectFloat, weak, dynamic)), Data, Args);
            break;
            
        case CCReflectTypeStruct:
            Handler(&CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT_STRUCT_TYPE(((CCReflectStruct*)DataType)->count), CCReflectOwnershipWeak), Data, Args);
            break;
            
        case CCReflectTypeOpaque:
            Handler(&CC_REFLECT(PTYPE(CCReflectOpaque, weak, dynamic)), Data, Args);
            break;
            
        case CCReflectTypeArray:
            Handler(&CC_REFLECT(PTYPE(CCReflectArray, weak, dynamic)), Data, Args);
            break;
            
        case CCReflectTypeValidator:
            Handler(&CC_REFLECT(PTYPE(CCReflectValidator, weak, dynamic)), Data, Args);
            break;
            
        case CCReflectTypeEnumerable:
            Handler(&CC_REFLECT(PTYPE(CCReflectEnumerable, weak, dynamic)), Data, Args);
            break;
    }
}

static void ReflectTypeUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    Handler(MappedType, Data, Args);
}

typedef struct {
    CCMemoryZone zone;
    CCReflectType type;
    void *data;
} CCReflectMapHandlerArgs;

void CCReflectMapHandler(CCReflectType Type, const void *Data, CCReflectMapHandlerArgs *Args)
{
    Args->type = CCMemoryZoneAllocate(Args->zone, sizeof(CCReflectType));
    CCReflectCopy(&CC_REFLECT(CCReflectType), (void*)Args->type, &Type, Args->zone, CC_ZONE_ALLOCATOR(Args->zone), CCReflectAssignmentCopy, FALSE);
    
    Args->data = (void**)Data;
    
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
            if (((CCReflectPointer*)Type)->ownership != CCReflectOwnershipWeak)
            {
                CCRetain(*(void**)Data);
            }
            break;
            
        default:
        {
            const size_t Size = CCReflectTypeSize(Type);
            Args->data = CCMemoryZoneAllocate(Args->zone, Size);
            
            CCReflectCopy(Type, Args->data, Data, Args->zone, CC_ZONE_ALLOCATOR(Args->zone), CCReflectAssignmentCopy, TRUE);
            break;
        }
    }
}

#pragma mark - Collections

#include "Array.h"

void CCReflectCCArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCArray Array;
    
    if ((Intent == CCReflectMapIntentTransfer) || (Intent == CCReflectMapIntentShare) || (!(Array = *(CCArray*)Data)))
    {
        Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), Data, Args);
    }
    
    else
    {
        Handler(&CC_REFLECT_ARRAY(((const CCReflectCCArray*)Type)->elementType, CCArrayGetCount(Array)), CCArrayGetData(Array), Args);
    }
}

void CCReflectCCArrayUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if (*(const CCReflectTypeID*)MappedType == CCReflectTypeArray)
    {
        if (((const CCReflectCCArray*)Type)->allocator.allocator != CC_NULL_ALLOCATOR.allocator) Allocator = ((const CCReflectCCArray*)Type)->allocator;
        
        const size_t ElementSize = CCReflectTypeSize(((const CCReflectCCArray*)Type)->elementType);
        CCArray Array = CCArrayCreate(Allocator, ElementSize, ((const CCReflectCCArray*)Type)->chunkSize);
        
        const size_t Count = ((const CCReflectArray*)MappedType)->count;
        CCArrayAppendElements(Array, Data, Count);
        
        Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), &Array, Args);
        
        CCArrayDestroy(Array);
    }
    
    else
    {
        Handler(MappedType, Data, Args);
    }
}


void CCReflectCCCollectionMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCCollection Collection;
    
    if ((Intent == CCReflectMapIntentTransfer) || (Intent == CCReflectMapIntentShare) || (!(Collection = *(CCCollection*)Data)))
    {
        Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), Data, Args);
    }
    
    else
    {
        CCEnumerable Enumerable;
        CCCollectionGetEnumerable(Collection, &Enumerable);
        
        Handler(&CC_REFLECT_ENUMERABLE(((const CCReflectCCCollection*)Type)->elementType, .count = CCCollectionGetCount(Collection)), &Enumerable, Args);
    }
}

void CCReflectCCCollectionUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if (*(const CCReflectTypeID*)MappedType == CCReflectTypeEnumerable)
    {
        if (((const CCReflectCCCollection*)Type)->allocator.allocator != CC_NULL_ALLOCATOR.allocator) Allocator = ((const CCReflectCCCollection*)Type)->allocator;
        
        const size_t ElementSize = CCReflectTypeSize(((const CCReflectCCCollection*)Type)->elementType);
        CCCollection Collection = CCCollectionCreate(Allocator, ((const CCReflectCCCollection*)Type)->hint, ElementSize, ((const CCReflectCCCollection*)Type)->elementDestructor);
        
        CCEnumerable Enumerable = *(CCEnumerable*)Data;
        
        for (void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable)) CCCollectionInsertElement(Collection, Element);
        
        Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), &Collection, Args);
        
        CCCollectionDestroy(Collection);
    }
    
    else
    {
        Handler(MappedType, Data, Args);
    }
}

#include "TypeCallbacks.h"

const CCReflectInteger CC_REFLECT(CCCollectionHint) = CC_REFLECT_SIGNED_INTEGER(int, CCReflectEndianNative);

static void CCCollectionElementDestructorMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void CCCollectionElementDestructorUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

const CCReflectStaticPointer CC_REFLECT(CCCollectionElementDestructor) = CC_REFLECT_STATIC_POINTER(&CC_REFLECT(void), CCReflectOwnershipWeak, CCCollectionElementDestructorMapper, CCCollectionElementDestructorUnmapper);

CCReflectTypeMapper CCCollectionElementDestructorMap = CCCollectionElementDestructorMapDefaults;
CCReflectTypeUnmapper CCCollectionElementDestructorUnmap = CCCollectionElementDestructorUnmapDefaults;

static void CCCollectionElementDestructorMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCCollectionElementDestructorMap(Type, Data, Args, Handler, Zone, Allocator, Intent);
}

static void CCCollectionElementDestructorUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCCollectionElementDestructorUnmap(Type, MappedType, Data, Args, Handler, Zone, Allocator);
}

void CCCollectionElementDestructorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_VALUE_IS_COLLECTION_ELEMENT_DESTRUCTOR,
        CCGenericDestructorForCollection,
        CCStringDestructorForCollection,
        CCDataDestructorForCollection,
        CCArrayDestructorForCollection,
        CCLinkedListDestructorForCollection,
        CCCollectionDestructorForCollection,
        CCHashMapDestructorForCollection,
        CCDictionaryDestructorForCollection,
        FSPathComponentDestructorForCollection,
        FSPathDestructorForCollection,
        FSHandleDestructorForCollection,
        CCBigIntDestructorForCollection,
        CCBigIntFastDestructorForCollection
    )
    
    else CCAssertLog(0, "Unknown destructor type");
}

void CCCollectionElementDestructorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{    
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_COLLECTION_ELEMENT_DESTRUCTOR,
        CCGenericDestructorForCollection,
        CCStringDestructorForCollection,
        CCDataDestructorForCollection,
        CCArrayDestructorForCollection,
        CCLinkedListDestructorForCollection,
        CCCollectionDestructorForCollection,
        CCHashMapDestructorForCollection,
        CCDictionaryDestructorForCollection,
        FSPathComponentDestructorForCollection,
        FSPathDestructorForCollection,
        FSHandleDestructorForCollection,
        CCBigIntDestructorForCollection,
        CCBigIntFastDestructorForCollection
    )
    
    CCAssertLog(0, "Unknown destructor type");
}
