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

const char *CCReflectTypeNameDefaults(CCReflectType Type);

/*!
 * @brief A lookup serializer for some common default types.
 * @description This may be called from within your own lookup to make use of any remaining unmapped indices.
 * @param Type The reflected type to get the lookup for.
 * @param Offset The offset for the unmapped indices.
 * @return The lookup for the type or @b UINT8_MAX if there is none.
 */
uint8_t CCReflectSerializeBinaryTypeLookupDefaults(CCReflectType Type, size_t Offset);

/*!
 * @brief A lookup deserializer for some common default types.
 * @description This may be called from within your own lookup to make use of any remaining unmapped indices.
 * @param Index The index of the type to lookup.
 * @param Zone The memory zone to use for allocations.
 * @param Offset The offset for the unmapped indices.
 * @return The type that is mapped to the given index.
 */
CCReflectType CCReflectDeserializeBinaryTypeLookupDefaults(uint8_t Index, CCMemoryZone Zone, size_t Offset);


#pragma mark - Reflected Types

extern const CCReflectOpaque CC_REFLECT(CCReflectType);

extern const CCReflectInteger CC_REFLECT(CCReflectTypeID);

extern const CCReflectInteger CC_REFLECT(CCReflectStorage);

extern const CCReflectInteger CC_REFLECT(CCReflectOwnership);

extern const CCReflectStruct4 CC_REFLECT(CCReflectPointer);

extern const CCReflectStruct3 CC_REFLECT(CCReflectStaticPointer);

extern const CCReflectStruct3 CC_REFLECT(CCReflectDynamicPointer);

extern const CCReflectInteger CC_REFLECT(CCReflectEndian);

extern const CCReflectStruct5 CC_REFLECT(CCReflectInteger);

extern const CCReflectStruct3 CC_REFLECT(CCReflectFloat);

extern const CCReflectStruct3 CC_REFLECT(CCReflectStructField);

extern const CCReflectStruct4 CC_REFLECT(CCReflectStruct);

extern const CCReflectStruct3 CC_REFLECT(CCReflectArray);

extern const CCReflectStruct3 CC_REFLECT(CCReflectEnumerable);

extern const CCReflectStaticPointer CC_REFLECT(CCReflectTypeMapper);
extern const CCReflectStaticPointer CC_REFLECT(CCReflectTypeUnmapper);

extern CCReflectTypeMapper CCReflectUnmapperMap;
extern CCReflectTypeUnmapper CCReflectUnmapperUnmap;

void CCReflectTypeMapperMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectTypeMapperUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

void CCReflectTypeUnmapperMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectTypeUnmapperUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

#define CC_REFLECT_VALUE_IS_POINTER(value) *(void**)CC_REFLECT_MAP_DATA_ARG == value

#define CC_REFLECT_VALUE_TO_POINTER(type) &CC_REFLECT(type) CC_REFLECT_VALUE_TO_POINTER_
#define CC_REFLECT_VALUE_TO_POINTER_(value) , &(void*){ (void*)value }

extern const CCReflectStruct5 CC_REFLECT(CCReflectOpaque);

extern CCReflectTypeMapper CCReflectOpaqueTypeDescriptorMap;
extern CCReflectTypeUnmapper CCReflectOpaqueTypeDescriptorUnmap;

void CCReflectOpaqueTypeDescriptorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectOpaqueTypeDescriptorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern CCReflectTypeMapper CCReflectStaticPointerTypeDescriptorMap;
extern CCReflectTypeUnmapper CCReflectStaticPointerTypeDescriptorUnmap;

void CCReflectStaticPointerTypeDescriptorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectStaticPointerTypeDescriptorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

#define CC_REFLECT_STATIC_POINTER_IS_TYPE(value) CC_REFLECT_MAP_DATA_ARG == &CC_REFLECT(value)

#define CC_REFLECT_VALUE_TO_STATIC_POINTER(value) &CC_REFLECT(CCReflectStaticPointer), &CC_REFLECT(value)

void CCReflectValidationMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectValidationUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectStaticPointer CC_REFLECT(CCReflectValidation);

extern CCReflectTypeMapper CCReflectValidationMap;
extern CCReflectTypeUnmapper CCReflectValidationUnmap;

extern const CCReflectStruct2 CC_REFLECT(CCReflectValue);
extern const CCReflectStruct5 CC_REFLECT(CCReflectValidator);

#pragma mark - void

extern const CCReflectOpaque CC_REFLECT(void);

#pragma mark - Integer Types

extern const CCReflectInteger CC_REFLECT(_Bool);

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

#define CC_REFLECT_TERMINATED_ARRAY(type, terminator_, maxSize) ((CCReflectTerminatedArray){ .opaque = CC_REFLECT_OPAQUE(maxSize, sizeof(CCReflectTerminatedArray), CCReflectTerminatedArrayMapper, CCReflectTerminatedArrayUnmapper), .elementType = type, .terminator = terminator_ })

void CCReflectTerminatedArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectTerminatedArrayUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


#pragma mark - Big Integers

#include <CommonC/BigInt.h>
#include <CommonC/BigIntFast.h>

extern const CCReflectOpaque CC_REFLECT(CCBigInt);
extern const CCReflectOpaque CC_REFLECT(CCBigIntFast);

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCBigInt, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCBigInt, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCBigInt, retain, dynamic));

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCBigIntFast, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCBigIntFast, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCBigIntFast, retain, dynamic));


#pragma mark - Strings

extern const CCReflectInteger CC_REFLECT(CCChar);

extern const CCReflectOpaque CC_REFLECT(CCString);

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCString, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCString, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCString, retain, dynamic));

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

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCAllocatorType, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCAllocatorType, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCAllocatorType, retain, dynamic));


#pragma mark - MemoryDestructorCallback

extern const CCReflectStaticPointer CC_REFLECT(CCMemoryDestructorCallback);

extern CCReflectTypeMapper CCMemoryDestructorCallbackMap;
extern CCReflectTypeUnmapper CCMemoryDestructorCallbackUnmap;

void CCMemoryDestructorCallbackMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCMemoryDestructorCallbackUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


#pragma mark - CCComparator

extern const CCReflectStaticPointer CC_REFLECT(CCComparator);

extern CCReflectTypeMapper CCComparatorMap;
extern CCReflectTypeUnmapper CCComparatorUnmap;

void CCComparatorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCComparatorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


#pragma mark - Pointer Types

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectType, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectType, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectType, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeID, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeID, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeID, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStorage, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStorage, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStorage, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectOwnership, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectOwnership, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectOwnership, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectPointer, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectPointer, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectPointer, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStaticPointer, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStaticPointer, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStaticPointer, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectDynamicPointer, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectDynamicPointer, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectDynamicPointer, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectEndian, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectEndian, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectEndian, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectInteger, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectInteger, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectInteger, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectFloat, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectFloat, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectFloat, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStructField, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStructField, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStructField, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStruct, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStruct, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectStruct, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectArray, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectArray, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectArray, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeMapper, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeMapper, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeMapper, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeUnmapper, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeUnmapper, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectTypeUnmapper, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectOpaque, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectOpaque, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectOpaque, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectEnumerable, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectEnumerable, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectEnumerable, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValidation, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValidation, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValidation, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValue, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValue, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValue, retain, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValidator, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValidator, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCReflectValidator, retain, dynamic));

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


#pragma mark - Collections

typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
    size_t chunkSize;
} CCReflectCCArray;

#define CC_REFLECT_CCArray(type, allocator_, chunkSize_) ((CCReflectCCArray){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCArray), sizeof(CCReflectCCArray), CCReflectCCArrayMapper, CCReflectCCArrayUnmapper), .elementType = type, .allocator = allocator_, .chunkSize = chunkSize_ })

void CCReflectCCArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCArrayUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
} CCReflectCCLinkedList;

#define CC_REFLECT_CCLinkedList(type, allocator_) ((CCReflectCCLinkedList){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCLinkedList), sizeof(CCReflectCCLinkedList), CCReflectCCLinkedListMapper, CCReflectCCLinkedListUnmapper), .elementType = type, .allocator = allocator_ })

void CCReflectCCLinkedListMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCLinkedListUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
    size_t chunkSize;
    size_t pageSize;
} CCReflectCCList;

#define CC_REFLECT_CCList(type, allocator_, chunkSize_, pageSize_) ((CCReflectCCList){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCList), sizeof(CCReflectCCList), CCReflectCCListMapper, CCReflectCCListUnmapper), .elementType = type, .allocator = allocator_, .chunkSize = chunkSize_, .pageSize = pageSize_ })

void CCReflectCCListMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCListUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
    CCCollectionElementDestructor elementDestructor;
    CCCollectionHint hint;
} CCReflectCCCollection;

#define CC_REFLECT_CCCollection(type, allocator_, hint_, elementDestructor_) ((CCReflectCCCollection){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCCollection), sizeof(CCReflectCCCollection), CCReflectCCCollectionMapper, CCReflectCCCollectionUnmapper), .elementType = type, .allocator = allocator_, .hint = hint_, .elementDestructor = elementDestructor_ })

void CCReflectCCCollectionMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCCollectionUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectInteger CC_REFLECT(CCCollectionHint);

extern const CCReflectStaticPointer CC_REFLECT(CCCollectionElementDestructor);

extern CCReflectTypeMapper CCCollectionElementDestructorMap;
extern CCReflectTypeUnmapper CCCollectionElementDestructorUnmap;

void CCCollectionElementDestructorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCCollectionElementDestructorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


#pragma mark - Maps

#include <CommonC/HashMap.h>

typedef struct {
    CCReflectOpaque opaque;
    CCReflectType keyType;
    CCReflectType valueType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
    size_t bucketCount;
    CCHashMapKeyHasher hasher;
    CCComparator keyComparator;
    const CCHashMapInterface *interface;
} CCReflectCCHashMap;

#define CC_REFLECT_CCHashMap(keyType_, valueType_, allocator_, bucketCount_, hasher_, keyComparator_, interface_) ((CCReflectCCHashMap){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCHashMap), sizeof(CCReflectCCHashMap), CCReflectCCHashMapMapper, CCReflectCCHashMapUnmapper), .keyType = keyType_, .valueType = valueType_, .allocator = allocator_, .bucketCount = bucketCount_, .hasher = hasher_, .keyComparator = keyComparator_, .interface = interface_ })

void CCReflectCCHashMapMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCHashMapUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectStaticPointer CC_REFLECT(CCHashMapKeyHasher);

extern CCReflectTypeMapper CCHashMapKeyHasherMap;
extern CCReflectTypeUnmapper CCHashMapKeyHasherUnmap;

void CCHashMapKeyHasherMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCHashMapKeyHasherUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectStaticPointer CC_REFLECT(PTYPE(CCHashMapInterface, weak, static));

extern CCReflectTypeMapper CCHashMapInterfaceMap;
extern CCReflectTypeUnmapper CCHashMapInterfaceUnmap;

void CCHashMapInterfaceMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCHashMapInterfaceUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


#include <CommonC/Dictionary.h>

typedef struct {
    CCReflectOpaque opaque;
    CCReflectType keyType;
    CCReflectType valueType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
    CCDictionaryHint hint;
    const CCDictionaryCallbacks *callbacks;
} CCReflectCCDictionary;

#define CC_REFLECT_CCDictionary(keyType_, valueType_, allocator_, hint_, callbacks_) ((CCReflectCCDictionary){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCDictionary), sizeof(CCReflectCCDictionary), CCReflectCCDictionaryMapper, CCReflectCCDictionaryUnmapper), .keyType = keyType_, .valueType = valueType_, .allocator = allocator_, .hint = hint_, .callbacks = callbacks_ })

void CCReflectCCDictionaryMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCDictionaryUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectInteger CC_REFLECT(CCDictionaryHint);

extern const CCReflectStaticPointer CC_REFLECT(CCDictionaryKeyHasher);

extern CCReflectTypeMapper CCDictionaryKeyHasherMap;
extern CCReflectTypeUnmapper CCDictionaryKeyHasherUnmap;

void CCDictionaryKeyHasherMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCDictionaryKeyHasherUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectStaticPointer CC_REFLECT(CCDictionaryElementDestructor);

extern CCReflectTypeMapper CCDictionaryElementDestructorMap;
extern CCReflectTypeUnmapper CCDictionaryElementDestructorUnmap;

void CCDictionaryElementDestructorMapDefaults(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCDictionaryElementDestructorUnmapDefaults(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const CCReflectStruct4 CC_REFLECT(CCDictionaryCallbacks);

extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCDictionaryCallbacks, weak, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCDictionaryCallbacks, transfer, dynamic));
extern const CCReflectDynamicPointer CC_REFLECT(PTYPE(CCDictionaryCallbacks, retain, dynamic));


#pragma mark - Queues

typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
} CCReflectCCQueue;

#define CC_REFLECT_CCQueue(type, allocator_) ((CCReflectCCQueue){ .opaque = CC_REFLECT_OPAQUE(sizeof(CCQueue), sizeof(CCReflectCCQueue), CCReflectCCQueueMapper, CCReflectCCQueueUnmapper), .elementType = type, .allocator = allocator_ })

void CCReflectCCQueueMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
void CCReflectCCQueueUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);


#pragma mark - Helpers
/*!
 * @abstract Overrideable macros:
 *           - CC_REFLECT_VALUE_MAP_WITHOUT_NAME
 *           - CC_REFLECT_MAP_DATA_ARG
 *           - CC_REFLECT_UNMAP_DATA_ARG
 *           - CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE
 *           - CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_BASE
 *           - CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE
 *           - CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_BASE
 */

#ifndef CC_REFLECT_VALUE_MAP_WITHOUT_NAME
#define CC_REFLECT_VALUE_MAP_WITHOUT_NAME 1
#endif

#ifndef CC_REFLECT_MAP_DATA_ARG
#define CC_REFLECT_MAP_DATA_ARG Data
#endif

/*!
 * @define CC_REFLECT_VALUE_IS_TYPE
 * @brief Specify that the value is a reflected type.
 */
#define CC_REFLECT_VALUE_IS_TYPE(value) *(CCReflectType*)CC_REFLECT_MAP_DATA_ARG == &CC_REFLECT(value)

/*!
 * @define CC_REFLECT_VALUE_IS_OPAQUE
 * @brief Specify that the value is an opaque value.
 * @note @b CC_REFLECT_VALUE_OPAQUE_MAPPER(value) and @b CC_REFLECT_VALUE_OPAQUE_UNMAPPER(value) should both be defined to return the expected
 *       function name.
 */
#define CC_REFLECT_VALUE_IS_OPAQUE(value) ((*(CCReflectOpaque**)CC_REFLECT_MAP_DATA_ARG)->map == CC_REFLECT_VALUE_OPAQUE_MAPPER(value)) && ((*(CCReflectOpaque**)CC_REFLECT_MAP_DATA_ARG)->unmap == CC_REFLECT_VALUE_OPAQUE_UNMAPPER(value))

#if CC_REFLECT_VALUE_MAP_WITHOUT_NAME
#ifndef CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE
#define CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE uint8_t
#endif

#ifndef CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_BASE
#define CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_BASE 0
#endif

#define CC_REFLECT_MAP_STATELESS_VALUE_HANDLER(value, index) Handler(&CC_REFLECT(CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE), &(CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE){ index + CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_BASE }, Args);
#else
#define CC_REFLECT_MAP_STATELESS_VALUE_HANDLER(value, index) Handler(&CC_REFLECT_ARRAY(&CC_REFLECT(unsigned char), sizeof(#value)), #value, Args);
#endif

/*!
 * @define CC_REFLECT_MAP_STATELESS_VALUE
 * @brief Map a stateless value with the given index and condition.
 * @description A value is stateless if it can be mapped without any associated state.
 * @param type The type of the value.
 * @param index The index to associate with the value of this type.
 * @param condition The condition to check the type with.
 */
#define CC_REFLECT_MAP_STATELESS_VALUE(value, index, condition) \
(condition(value)) \
{ \
    CC_REFLECT_MAP_STATELESS_VALUE_HANDLER(value, index) \
}

/*!
 * @define CC_REFLECT_MAP_STATELESS_VALUES_WHEN
 * @brief Map a series of stateless values when the provided condition is met.
 * @note See @b CC_REFLECT_MAP_STATEFUL_VALUE.
 * @param condition The condition to check the types with.
 */
#define CC_REFLECT_MAP_STATELESS_VALUES_WHEN(condition, ...) CC_SOFT_JOIN(else if, CC_MAP_WITH(CC_REFLECT_MAP_STATELESS_VALUE, condition, __VA_ARGS__))

#define CC_REFLECT_STATEFUL_VALUE_DEFINE_MEMBER(args, index) CC_REFLECT_STATEFUL_VALUE_DEFINE_MEMBER_ args
#define CC_REFLECT_STATEFUL_VALUE_DEFINE_MEMBER_(name, type) CC_TYPE_DECL(type) name;

#define CC_REFLECT_STATEFUL_VALUE_DEFINE_MEMBERS(...) CC_MERGE_MAP(CC_REFLECT_STATEFUL_VALUE_DEFINE_MEMBER, __VA_ARGS__)

#define CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBER(args, index, prefix) CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBER_(prefix, CC_EXPAND args)
#define CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBER_(...) CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBER__(__VA_ARGS__)
#define CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBER__(prefix, name, type) (prefix(name), &CC_REFLECT(type))

#define CC_REFLECT_APPLY_PREFIX_NONE(x) x
#define CC_REFLECT_APPLY_PREFIX_DATA(x) data.x

#define CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBERS(prefix, ...) CC_MAP_WITH(CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBER, prefix, __VA_ARGS__)

#define CC_REFLECT_STATEFUL_VALUE_INIT_MEMBER(args, index, struct) CC_REFLECT_STATEFUL_VALUE_INIT_MEMBER_(index, struct, CC_EXPAND args)
#define CC_REFLECT_STATEFUL_VALUE_INIT_MEMBER_(...) CC_REFLECT_STATEFUL_VALUE_INIT_MEMBER__(__VA_ARGS__)
#define CC_REFLECT_STATEFUL_VALUE_INIT_MEMBER__(index, struct, name, ...) .name = (*(struct**)Data)->name

#define CC_REFLECT_STATEFUL_VALUE_INIT_MEMBERS(struct, ...) CC_MAP_WITH(CC_REFLECT_STATEFUL_VALUE_INIT_MEMBER, struct, __VA_ARGS__)

#if CC_REFLECT_VALUE_MAP_WITHOUT_NAME
#ifndef CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE
#define CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE uint8_t
#endif

#ifndef CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_BASE
#define CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_BASE 0
#endif

#define CC_REFLECT_STATEFUL_VALUE_DEFINE_NAME(type) CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE name;
#define CC_REFLECT_STATEFUL_VALUE_REFLECT_NAME(type) (name, &CC_REFLECT(CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE))
#define CC_REFLECT_STATEFUL_VALUE_INIT_NAME(type, index) index + CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_BASE
#else
#define CC_REFLECT_STATEFUL_VALUE_DEFINE_NAME(type) char name[sizeof(#type)];
#define CC_REFLECT_STATEFUL_VALUE_REFLECT_NAME(type) (name, &CC_REFLECT_ARRAY(&CC_REFLECT(unsigned char), sizeof(#type)))
#define CC_REFLECT_STATEFUL_VALUE_INIT_NAME(type, index) #type
#endif

#define CC_REFLECT_MAP_STATEFUL_VALUE_HANDLER(type, index, ...) \
typedef struct { \
    CC_REFLECT_STATEFUL_VALUE_DEFINE_NAME(type) \
    struct { \
        CC_REFLECT_STATEFUL_VALUE_DEFINE_MEMBERS(__VA_ARGS__) \
    } data; \
} CC_REFLECT_STATEFUL_VALUE_STRUCT_NAME(type); \
Handler(&CC_REFLECT_STRUCT(CC_REFLECT_STATEFUL_VALUE_STRUCT_NAME(type), \
    CC_REFLECT_STATEFUL_VALUE_REFLECT_NAME(type), \
    CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBERS(CC_REFLECT_APPLY_PREFIX_DATA, __VA_ARGS__) \
), &(CC_REFLECT_STATEFUL_VALUE_STRUCT_NAME(type)){ \
    .name = CC_REFLECT_STATEFUL_VALUE_INIT_NAME(type, index), \
    .data = { CC_REFLECT_STATEFUL_VALUE_INIT_MEMBERS(CC_REFLECT_STATEFUL_VALUE_TYPE(type), __VA_ARGS__) } \
}, Args);

/*!
 * @define CC_REFLECT_MAP_STATEFUL_VALUE
 * @brief Map a stateful value with the given index and condition.
 * @description A value is stateful if it needs to be mapped with some associated state.
 * @note @b CC_REFLECT_STATEFUL_VALUE_STRUCT_NAME(type) and @b CC_REFLECT_STATEFUL_VALUE_TYPE(type) should both be defined to return the expected
 *       type names.
 * @param type The type of the value.
 * @param index The index to associate with the value of this type.
 * @param condition The condition to check the type with.
 */
#define CC_REFLECT_MAP_STATEFUL_VALUE(type, index, condition) CC_REFLECT_MAP_STATEFUL_VALUE_(index, condition, CC_EXPAND type)
#define CC_REFLECT_MAP_STATEFUL_VALUE_(...) CC_REFLECT_MAP_STATEFUL_VALUE__(__VA_ARGS__)
#define CC_REFLECT_MAP_STATEFUL_VALUE__(index, condition, type, ...) \
(condition(type)) \
{ \
    CC_REFLECT_MAP_STATEFUL_VALUE_HANDLER(type, index, __VA_ARGS__) \
}

/*!
 * @define CC_REFLECT_MAP_STATEFUL_VALUES_WHEN
 * @brief Map a series of stateful values when the provided condition is met.
 * @note See @b CC_REFLECT_MAP_STATEFUL_VALUE.
 * @param condition The condition to check the types with.
 */
#define CC_REFLECT_MAP_STATEFUL_VALUES_WHEN(condition, ...) CC_SOFT_JOIN(else if, CC_RECURSIVE_0_MAP_WITH(CC_REFLECT_MAP_STATEFUL_VALUE, condition, __VA_ARGS__))


#ifndef CC_REFLECT_UNMAP_DATA_ARG
#define CC_REFLECT_UNMAP_DATA_ARG CC_REFLECT_MAP_DATA_ARG
#endif

#ifndef CC_REFLECT_UNMAP_MAPPED_TYPE_ARG
#define CC_REFLECT_UNMAP_MAPPED_TYPE_ARG MappedType
#endif

#define CC_REFLECT_VALUE_TO_OPAQUE(value) &CC_REFLECT(CCReflectOpaque), &CC_REFLECT(value)

#define CC_REFLECT_STATEFUL_VALUE_GET_FIELD(args, index) CC_REFLECT_STATEFUL_VALUE_GET_FIELD_(index, CC_EXPAND args)
#define CC_REFLECT_STATEFUL_VALUE_GET_FIELD_(...) CC_REFLECT_STATEFUL_VALUE_GET_FIELD__(__VA_ARGS__)
#define CC_REFLECT_STATEFUL_VALUE_GET_FIELD__(index, name, type) *(CC_TYPE_DECL(type)*)(CC_REFLECT_UNMAP_DATA_ARG + ((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[index + 1].offset)

/*!
 * @define CC_REFLECT_VALUE_TO_STRUCT
 * @brief Unmap the value to a struct value.
 * @note @b CC_REFLECT_STATEFUL_VALUE_TYPE_CONSTRUCTOR(type) and @b CC_REFLECT_STATEFUL_VALUE_OPAQUE_FIELD should both be defined to return the expected
 *       type and field names.
 */
#define CC_REFLECT_VALUE_TO_STRUCT(type, ...) \
CC_REFLECT_VALUE_TO_STRUCT_(CC_REFLECT_STRUCT(CC_REFLECT_STATEFUL_VALUE_TYPE(type), \
    (CC_REFLECT_STATEFUL_VALUE_OPAQUE_FIELD.id, &CC_REFLECT(CCReflectTypeID)), \
    (CC_REFLECT_STATEFUL_VALUE_OPAQUE_FIELD.size, &CC_REFLECT(size_t)), \
    (CC_REFLECT_STATEFUL_VALUE_OPAQUE_FIELD.map, &CC_REFLECT(CCReflectTypeMapper)), \
    (CC_REFLECT_STATEFUL_VALUE_OPAQUE_FIELD.unmap, &CC_REFLECT(CCReflectTypeUnmapper)), \
    CC_REFLECT_STATEFUL_VALUE_REFLECT_MEMBERS(CC_REFLECT_APPLY_PREFIX_NONE, __VA_ARGS__) \
), \
CC_REFLECT_STATEFUL_VALUE_TYPE_CONSTRUCTOR(type), \
CC_MAP(CC_REFLECT_STATEFUL_VALUE_GET_FIELD, __VA_ARGS__))
#define CC_REFLECT_VALUE_TO_STRUCT_(...) CC_REFLECT_VALUE_TO_STRUCT__(__VA_ARGS__)
#define CC_REFLECT_VALUE_TO_STRUCT__(struct, constructor, ...) &struct, &constructor(__VA_ARGS__)

/*!
 * @define CC_REFLECT_UNMAP_STATEFUL_VALUE
 * @brief Unmap a stateful value with the given index and converter.
 * @description A value is stateful if it needs to be unmapped with some associated state.
 * @param type The type of the value.
 * @param index The index to associate with the value of this type.
 * @param convert How to convert the value.
 */
#define CC_REFLECT_UNMAP_STATEFUL_VALUE(value, index, convert) CC_REFLECT_UNMAP_STATEFUL_VALUE_(index, convert, CC_EXPAND value)
#define CC_REFLECT_UNMAP_STATEFUL_VALUE_(...) CC_REFLECT_UNMAP_STATEFUL_VALUE__(__VA_ARGS__)

/*!
 * @define CC_REFLECT_UNMAP_STATELESS_VALUE
 * @brief Unmap a stateless value with the given index and converter.
 * @description A value is stateless if it can be unmapped without any associated state.
 * @param type The type of the value.
 * @param index The index to associate with the value of this type.
 * @param convert How to convert the value.
 */

/*!
 * @define CC_REFLECT_UNMAP_STATELESS_VALUES
 * @brief Unmap a series of stateless values with the given converter.
 * @note See @b CC_REFLECT_UNMAP_STATELESS_VALUE.
 * @param convert How to convert the value.
 */

/*!
 * @define CC_REFLECT_UNMAP_STATEFUL_VALUES
 * @brief Unmap a series of stateful values with the given converter.
 * @note See @b CC_REFLECT_UNMAP_STATEFUL_VALUE.
 * @param convert How to convert the value.
 */


#if CC_REFLECT_VALUE_MAP_WITHOUT_NAME
#define CC_REFLECT_UNMAP_STATELESS_VALUE(value, index, convert) \
case index + CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_BASE: \
    Handler(convert(value), Args); \
    return;

#define CC_REFLECT_UNMAP_STATELESS_VALUES(convert, ...) \
(*(const CCReflectTypeID*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG == CCReflectTypeInteger) \
{ \
    if (((const CCReflectInteger*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->size == sizeof(CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE)) \
    { \
        switch (*(CC_REFLECT_MAP_STATELESS_VALUE_MAPPED_INDEX_TYPE*)CC_REFLECT_UNMAP_DATA_ARG) \
        { \
            CC_MERGE_MAP_WITH(CC_REFLECT_UNMAP_STATELESS_VALUE, convert, __VA_ARGS__) \
        } \
    } \
}

#define CC_REFLECT_UNMAP_STATEFUL_VALUE__(index, convert, type_, ...) \
case index + CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_BASE: \
    Handler(convert(type_, __VA_ARGS__), Args); \
    return;

#define CC_REFLECT_UNMAP_STATEFUL_VALUES(convert, ...) \
(*(const CCReflectTypeID*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG == CCReflectTypeStruct) \
{ \
    if (((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->count >= 1) \
    { \
        if (*(const CCReflectTypeID*)((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].type == CCReflectTypeInteger) \
        { \
            if (((const CCReflectInteger*)((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].type)->size == sizeof(CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE)) \
            { \
                switch (*(CC_REFLECT_MAP_STATEFUL_VALUE_MAPPED_INDEX_TYPE*)CC_REFLECT_UNMAP_DATA_ARG) \
                { \
                    CC_MERGE_MAP_WITH(CC_REFLECT_UNMAP_STATEFUL_VALUE, convert, __VA_ARGS__) \
                } \
            } \
        } \
    } \
}
#else
#define CC_REFLECT_UNMAP_STATELESS_VALUE(value, index, convert) \
(!strncmp(CC_REFLECT_UNMAP_DATA_ARG, #value, ((const CCReflectArray*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->count)) \
{ \
    Handler(convert(value), Args); \
    return; \
}

#define CC_REFLECT_UNMAP_STATELESS_VALUES(convert, ...) \
(*(const CCReflectTypeID*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG == CCReflectTypeArray) \
{ \
    if (*(const CCReflectTypeID*)((const CCReflectArray*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->type == CCReflectTypeInteger) \
    { \
        if (((const CCReflectInteger*)((const CCReflectArray*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->type)->size == sizeof(char)) \
        { \
            if CC_SOFT_JOIN(else if, CC_MAP_WITH(CC_REFLECT_UNMAP_STATELESS_VALUE, convert, __VA_ARGS__)) \
        } \
    } \
}

#define CC_REFLECT_UNMAP_STATEFUL_VALUE__(index, convert, type_, ...) \
(!strncmp(CC_REFLECT_UNMAP_DATA_ARG + ((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].offset, #type_, ((const CCReflectArray*)((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].type)->count)) \
{ \
    Handler(convert(type_, __VA_ARGS__), Args); \
    return; \
}

#define CC_REFLECT_UNMAP_STATEFUL_VALUES(convert, ...) \
(*(const CCReflectTypeID*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG == CCReflectTypeStruct) \
{ \
    if (((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->count >= 1) \
    { \
        if (*(const CCReflectTypeID*)((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].type == CCReflectTypeArray) \
        { \
            if (*(const CCReflectTypeID*)((const CCReflectArray*)((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].type)->type == CCReflectTypeInteger) \
            { \
                if (((const CCReflectInteger*)((const CCReflectArray*)((const CCReflectStruct*)CC_REFLECT_UNMAP_MAPPED_TYPE_ARG)->fields[0].type)->type)->size == 1) \
                { \
                    if CC_SOFT_JOIN(else if, CC_RECURSIVE_0_MAP_WITH(CC_REFLECT_UNMAP_STATEFUL_VALUE, convert, __VA_ARGS__)) \
                } \
            } \
        } \
    } \
}
#endif

#endif
