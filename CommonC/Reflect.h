/*
 *  Copyright (c) 2023, Stefan Johnson
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

#ifndef CommonC_Reflect_h
#define CommonC_Reflect_h

#include <CommonC/Base.h>
#include <CommonC/CCString.h>
#include <CommonC/Allocator.h>
#include <CommonC/MemoryZone.h>
#include <CommonC/Hacks.h>
// TODO: Also handle atomic types (use load/store with relaxed)
typedef enum {
    CCReflectTypePointer,
    CCReflectTypeInteger,
    CCReflectTypeFloat,
    CCReflectTypeStruct,
    CCReflectTypeOpaque,
    CCReflectTypeArray,
    CCReflectTypeValidator,
    CCReflectTypeEnumerable,
} CCReflectTypeID;

typedef const void *CCReflectType;

typedef enum {
    CCReflectMapIntentTransfer,
    CCReflectMapIntentShare,
    CCReflectMapIntentCopy,
    CCReflectMapIntentSerialize,
    CCReflectMapIntentDisplay,
    CCReflectMapIntentInspect
} CCReflectMapIntent;

typedef void (*CCReflectTypeHandler)(CCReflectType Type, const void *Data, void *Args);

typedef void (*CCReflectTypeMapper)(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
typedef void (*CCReflectTypeUnmapper)(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

typedef enum {
    CCReflectStorageStatic,
    CCReflectStorageDynamic
} CCReflectStorage;

typedef enum {
    CCReflectOwnershipWeak,
    CCReflectOwnershipTransfer,
    CCReflectOwnershipRetain
} CCReflectOwnership;

typedef struct {
    CCReflectTypeID id;
    CCReflectType type;
    CCReflectStorage storage;
    CCReflectOwnership ownership;
} CCReflectPointer;

typedef struct {
    CCReflectPointer pointer;
    CCReflectTypeMapper map;
    CCReflectTypeUnmapper unmap;
} CCReflectStaticPointer;

typedef struct {
    CCReflectPointer pointer;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
    CCMemoryDestructorCallback destructor;
} CCReflectDynamicPointer;

typedef enum {
    CCReflectEndianNative,
    CCReflectEndianBig,
    CCReflectEndianLittle
} CCReflectEndian;

typedef struct {
    CCReflectTypeID id;
    size_t size;
    CCReflectEndian endian;
    _Bool sign;
    _Bool fixed;
} CCReflectInteger;

typedef struct {
    CCReflectTypeID id;
    size_t size;
    CCReflectEndian endian;
} CCReflectFloat;

typedef _Bool (*CCReflectValidation)(CCReflectType Type, void *Data, CCReflectType Validator);

typedef struct {
    CCReflectType type;
    const void *data;
} CCReflectValue;

typedef struct {
    CCReflectTypeID id;
    CCReflectType type;
    CCReflectValidation validate;
    CCReflectValue success;
    CCReflectValue failure;
} CCReflectValidator;

typedef struct {
    CCString name;
    size_t offset;
    CCReflectType type;
} CCReflectStructField;

#define CCReflectStruct(n) struct { \
    CCReflectTypeID id; \
    size_t size; \
    size_t count; \
    CCReflectStructField fields[n]; \
}

typedef CCReflectStruct() CCReflectStruct;

#define CC_REFLECT_STRUCT_DEFINE(x, y) typedef CCReflectStruct((x##0) + y) CCReflectStruct##x##y;

CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, ));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 1));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 2));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 3));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 4));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 5));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 6));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 7));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 8));
CC_SOFT_JOIN(;, CC_REPEAT(0, 10, CC_REFLECT_STRUCT_DEFINE, 9));

typedef struct {
    CCReflectTypeID id;
    CCReflectType type;
    size_t count;
} CCReflectArray;

typedef struct {
    CCReflectTypeID id;
    CCReflectType type;
    /// Set to SIZE_MAX for unknown size
    size_t count;
} CCReflectEnumerable;

typedef struct {
    CCReflectTypeID id;
    size_t size;
    size_t typeSize;
    CCReflectTypeMapper map;
    CCReflectTypeUnmapper unmap;
} CCReflectOpaque;

#define CC_REFLECT_INTEGER(type, order, ...) ((CCReflectInteger){ .id = CCReflectTypeInteger, .size = sizeof(type), .endian = order, __VA_ARGS__ })
#define CC_REFLECT_SIGNED_INTEGER(type, order, ...) CC_REFLECT_INTEGER(type, order, .sign = TRUE, __VA_ARGS__)
#define CC_REFLECT_UNSIGNED_INTEGER(type, order, ...) CC_REFLECT_INTEGER(type, order, .sign = FALSE, __VA_ARGS__)
#define CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(type, order, ...) CC_REFLECT_SIGNED_INTEGER(type, order, .fixed = TRUE, __VA_ARGS__)
#define CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(type, order, ...) CC_REFLECT_UNSIGNED_INTEGER(type, order, .fixed = TRUE, __VA_ARGS__)

#define CC_REFLECT_FLOAT(type, order, ...) ((CCReflectFloat){ .id = CCReflectTypeFloat, .size = sizeof(type), .endian = order, __VA_ARGS__ })

#define CC_REFLECT_POINTER(type_, storage_, ownership_) ((CCReflectPointer){ .id = CCReflectTypePointer, .type = type_, .storage = storage_, .ownership = ownership_ })
#define CC_REFLECT_STATIC_POINTER(type, ownership, mapper, unmapper) ((CCReflectStaticPointer){ .pointer = CC_REFLECT_POINTER(type, CCReflectStorageStatic, ownership), .map = mapper, .unmap = unmapper })
#define CC_REFLECT_DYNAMIC_POINTER(type, ownership, ...) ((CCReflectDynamicPointer){ .pointer = CC_REFLECT_POINTER(type, CCReflectStorageDynamic, ownership), CC_OVERRIDE_INIT((.allocator = CC_NULL_ALLOCATOR, .destructor = NULL), ## __VA_ARGS__) })

#define CC_REFLECT_ARRAY(type_, count_) ((CCReflectArray){ .id = CCReflectTypeArray, .type = type_, .count = count_ })

#define CC_REFLECT_ENUMERABLE(type_, ...) ((CCReflectEnumerable){ .id = CCReflectTypeEnumerable, .type = type_, CC_OVERRIDE_INIT((.count = SIZE_MAX), ## __VA_ARGS__) })

#define CC_REFLECT_OPAQUE(size_, typeSize_, mapper, unmapper) ((CCReflectOpaque){ .id = CCReflectTypeOpaque, .size = size_, .typeSize = typeSize_, .map = mapper, .unmap = unmapper })

#define CC_REFLECT_VALUE(type_, data_) ((CCReflectValue){ .type = type_, .data = data_ })

#define CC_REFLECT_RESULT(type, data) CC_REFLECT_VALUE(type, data)

#define CC_REFLECT_RESULT_DEFAULT CC_REFLECT_RESULT(NULL, NULL)

#define CC_REFLECT_VALIDATOR(type_, validate_, success_, failure_) ((CCReflectValidator){ .id = CCReflectTypeValidator, .type = type_, .validate = validate_, .success = success_, .failure = failure_ })

#define CC_REFLECT_STRUCT(type, ...) CC_REFLECT_STRUCT_(type, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_STRUCT_(...) CC_REFLECT_STRUCT__(__VA_ARGS__)
#define CC_REFLECT_STRUCT__(type_, n, ...) \
((CCReflectStruct##n){ \
    .id = CCReflectTypeStruct, \
    .size = sizeof(type_), \
    .count = n, \
    .fields = { \
        CC_MAP_WITH(CC_REFLECT_STRUCT_FIELD, type_, __VA_ARGS__) \
    } \
})

#define CC_REFLECT_STRUCT_FIELD(x, i, struct_) CC_REFLECT_STRUCT_FIELD_(CC_EXPAND x, struct_)
#define CC_REFLECT_STRUCT_FIELD_(...) CC_REFLECT_STRUCT_FIELD__(__VA_ARGS__)
#define CC_REFLECT_STRUCT_FIELD__(field, type_, struct_) { .name = CC_STRING(#field), .offset = offsetof(struct_, field), .type = type_ }

#include <CommonC/Template.h>

#define CC_REFLECT(...) CC_REFLECT_0(__VA_ARGS__)

#define CC_REFLECT_0(...) CC_REFLECT_0_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_1(...) CC_REFLECT_1_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_2(...) CC_REFLECT_2_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_3(...) CC_REFLECT_3_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_4(...) CC_REFLECT_4_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_5(...) CC_REFLECT_5_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_6(...) CC_REFLECT_6_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_7(...) CC_REFLECT_7_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_8(...) CC_REFLECT_8_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_9(...) CC_REFLECT_9_(CC_TYPE(__VA_ARGS__), __VA_ARGS__)
#define CC_REFLECT_0_(...) CC_REFLECT_0__(__VA_ARGS__)
#define CC_REFLECT_1_(...) CC_REFLECT_1__(__VA_ARGS__)
#define CC_REFLECT_2_(...) CC_REFLECT_2__(__VA_ARGS__)
#define CC_REFLECT_3_(...) CC_REFLECT_3__(__VA_ARGS__)
#define CC_REFLECT_4_(...) CC_REFLECT_4__(__VA_ARGS__)
#define CC_REFLECT_5_(...) CC_REFLECT_5__(__VA_ARGS__)
#define CC_REFLECT_6_(...) CC_REFLECT_6__(__VA_ARGS__)
#define CC_REFLECT_7_(...) CC_REFLECT_7__(__VA_ARGS__)
#define CC_REFLECT_8_(...) CC_REFLECT_8__(__VA_ARGS__)
#define CC_REFLECT_9_(...) CC_REFLECT_9__(__VA_ARGS__)
#define CC_REFLECT_0__(type, ...) CC_REFLECT_0___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_1__(type, ...) CC_REFLECT_1___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_2__(type, ...) CC_REFLECT_2___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_3__(type, ...) CC_REFLECT_3___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_4__(type, ...) CC_REFLECT_4___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_5__(type, ...) CC_REFLECT_5___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_6__(type, ...) CC_REFLECT_6___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_7__(type, ...) CC_REFLECT_7___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_8__(type, ...) CC_REFLECT_8___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_9__(type, ...) CC_REFLECT_9___((CCReflectedType_##type), __VA_ARGS__)
#define CC_REFLECT_0___(...) CC_REFLECT_0____(__VA_ARGS__)
#define CC_REFLECT_1___(...) CC_REFLECT_1____(__VA_ARGS__)
#define CC_REFLECT_2___(...) CC_REFLECT_2____(__VA_ARGS__)
#define CC_REFLECT_3___(...) CC_REFLECT_3____(__VA_ARGS__)
#define CC_REFLECT_4___(...) CC_REFLECT_4____(__VA_ARGS__)
#define CC_REFLECT_5___(...) CC_REFLECT_5____(__VA_ARGS__)
#define CC_REFLECT_6___(...) CC_REFLECT_6____(__VA_ARGS__)
#define CC_REFLECT_7___(...) CC_REFLECT_7____(__VA_ARGS__)
#define CC_REFLECT_8___(...) CC_REFLECT_8____(__VA_ARGS__)
#define CC_REFLECT_9___(...) CC_REFLECT_9____(__VA_ARGS__)
#define CC_REFLECT_0____(name, ...) CC_REFLECT_0_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_1____(name, ...) CC_REFLECT_1_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_2____(name, ...) CC_REFLECT_2_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_3____(name, ...) CC_REFLECT_3_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_4____(name, ...) CC_REFLECT_4_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_5____(name, ...) CC_REFLECT_5_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_6____(name, ...) CC_REFLECT_6_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_7____(name, ...) CC_REFLECT_7_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_8____(name, ...) CC_REFLECT_8_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_9____(name, ...) CC_REFLECT_9_____(CC_VA_ARG_COUNT name, CC_EXPAND name, __VA_ARGS__)
#define CC_REFLECT_0_____(...) CC_REFLECT_0______(__VA_ARGS__)
#define CC_REFLECT_1_____(...) CC_REFLECT_1______(__VA_ARGS__)
#define CC_REFLECT_2_____(...) CC_REFLECT_2______(__VA_ARGS__)
#define CC_REFLECT_3_____(...) CC_REFLECT_3______(__VA_ARGS__)
#define CC_REFLECT_4_____(...) CC_REFLECT_4______(__VA_ARGS__)
#define CC_REFLECT_5_____(...) CC_REFLECT_5______(__VA_ARGS__)
#define CC_REFLECT_6_____(...) CC_REFLECT_6______(__VA_ARGS__)
#define CC_REFLECT_7_____(...) CC_REFLECT_7______(__VA_ARGS__)
#define CC_REFLECT_8_____(...) CC_REFLECT_8______(__VA_ARGS__)
#define CC_REFLECT_9_____(...) CC_REFLECT_9______(__VA_ARGS__)
#define CC_REFLECT_0______(n, ...) CC_REFLECT_0_##n(__VA_ARGS__)
#define CC_REFLECT_1______(n, ...) CC_REFLECT_1_##n(__VA_ARGS__)
#define CC_REFLECT_2______(n, ...) CC_REFLECT_2_##n(__VA_ARGS__)
#define CC_REFLECT_3______(n, ...) CC_REFLECT_3_##n(__VA_ARGS__)
#define CC_REFLECT_4______(n, ...) CC_REFLECT_4_##n(__VA_ARGS__)
#define CC_REFLECT_5______(n, ...) CC_REFLECT_5_##n(__VA_ARGS__)
#define CC_REFLECT_6______(n, ...) CC_REFLECT_6_##n(__VA_ARGS__)
#define CC_REFLECT_7______(n, ...) CC_REFLECT_7_##n(__VA_ARGS__)
#define CC_REFLECT_8______(n, ...) CC_REFLECT_8_##n(__VA_ARGS__)
#define CC_REFLECT_9______(n, ...) CC_REFLECT_9_##n(__VA_ARGS__)

#define CC_REFLECT_0_1(name, ...) name
#define CC_REFLECT_1_1(name, ...) name
#define CC_REFLECT_2_1(name, ...) name
#define CC_REFLECT_3_1(name, ...) name
#define CC_REFLECT_4_1(name, ...) name
#define CC_REFLECT_5_1(name, ...) name
#define CC_REFLECT_6_1(name, ...) name
#define CC_REFLECT_7_1(name, ...) name
#define CC_REFLECT_8_1(name, ...) name
#define CC_REFLECT_9_1(name, ...) name
#define CC_REFLECT_0_2(name, fun, ...) CC_REFLECT_0_2_(fun##_0(name, __VA_ARGS__))
#define CC_REFLECT_1_2(name, fun, ...) CC_REFLECT_1_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_2_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_3_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_4_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_5_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_6_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_7_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_8_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_9_2(name, fun, ...) CC_REFLECT_2_2_(fun##_1(name, __VA_ARGS__))
#define CC_REFLECT_0_2_(...) CC_REFLECT_0_2__(__VA_ARGS__)
#define CC_REFLECT_1_2_(...) CC_REFLECT_1_2__(__VA_ARGS__)
#define CC_REFLECT_2_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_3_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_4_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_5_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_6_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_7_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_8_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_9_2_(...) CC_REFLECT_2_2__(__VA_ARGS__)
#define CC_REFLECT_0_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_1_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_2_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_3_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_4_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_5_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_6_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_7_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_8_2__(name, ...) CCReflectedType_##name
#define CC_REFLECT_9_2__(name, ...) CCReflectedType_##name

#define CCReflectedType_TYPE(...) CCReflectedType_##__VA_ARGS__

#define CCReflectedType_PTYPE(...)  __VA_ARGS__, CC_REFLECT_PTYPE

#define CCReflectedType_ARRAY(type, ...) type, CC_REFLECT_ARRAY

#define CC_REFLECT_PTYPE_0(name, ...)  CC_REFLECT_PTYPE_0_(CC_REFLECT_1(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_1(name, ...)  CC_REFLECT_PTYPE_1_(CC_REFLECT_2(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_2(name, ...)  CC_REFLECT_PTYPE_2_(CC_REFLECT_3(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_3(name, ...)  CC_REFLECT_PTYPE_3_(CC_REFLECT_4(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_4(name, ...)  CC_REFLECT_PTYPE_4_(CC_REFLECT_5(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_5(name, ...)  CC_REFLECT_PTYPE_5_(CC_REFLECT_6(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_6(name, ...)  CC_REFLECT_PTYPE_6_(CC_REFLECT_7(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_7(name, ...)  CC_REFLECT_PTYPE_7_(CC_REFLECT_8(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_8(name, ...)  CC_REFLECT_PTYPE_8_(CC_REFLECT_9(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_PTYPE_0_(...) CC_REFLECT_PTYPE_0__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_1_(...) CC_REFLECT_PTYPE_1__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_2_(...) CC_REFLECT_PTYPE_2__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_3_(...) CC_REFLECT_PTYPE_3__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_4_(...) CC_REFLECT_PTYPE_4__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_5_(...) CC_REFLECT_PTYPE_5__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_6_(...) CC_REFLECT_PTYPE_6__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_7_(...) CC_REFLECT_PTYPE_7__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_8_(...) CC_REFLECT_PTYPE_8__(__VA_ARGS__)
#define CC_REFLECT_PTYPE_0__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_1__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_2__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_3__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_4__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_5__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_6__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_7__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name
#define CC_REFLECT_PTYPE_8__(name, type, ownership, storage) ownership##_##storage##_PointerTo_##name

#define CC_REFLECT_EXPAND_PTYPE(type, ownership, storage) type, ownership, storage

#define CC_REFLECT_ARRAY_0(name, ...) CC_REFLECT_ARRAY_0_(CC_REFLECT_1(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_1(name, ...) CC_REFLECT_ARRAY_1_(CC_REFLECT_2(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_2(name, ...) CC_REFLECT_ARRAY_2_(CC_REFLECT_3(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_3(name, ...) CC_REFLECT_ARRAY_3_(CC_REFLECT_4(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_4(name, ...) CC_REFLECT_ARRAY_4_(CC_REFLECT_5(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_5(name, ...) CC_REFLECT_ARRAY_5_(CC_REFLECT_6(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_6(name, ...) CC_REFLECT_ARRAY_6_(CC_REFLECT_7(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_7(name, ...) CC_REFLECT_ARRAY_7_(CC_REFLECT_8(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_8(name, ...) CC_REFLECT_ARRAY_8_(CC_REFLECT_9(name), CC_REFLECT_EXPAND_##__VA_ARGS__)
#define CC_REFLECT_ARRAY_0_(...) CC_REFLECT_ARRAY_0__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_1_(...) CC_REFLECT_ARRAY_1__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_2_(...) CC_REFLECT_ARRAY_2__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_3_(...) CC_REFLECT_ARRAY_3__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_4_(...) CC_REFLECT_ARRAY_4__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_5_(...) CC_REFLECT_ARRAY_5__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_6_(...) CC_REFLECT_ARRAY_6__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_7_(...) CC_REFLECT_ARRAY_7__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_8_(...) CC_REFLECT_ARRAY_8__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_9_(...) CC_REFLECT_ARRAY_9__(__VA_ARGS__)
#define CC_REFLECT_ARRAY_0__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_1__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_2__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_3__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_4__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_5__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_6__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_7__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_8__(name, type, count) ArrayOf_##count##_##name
#define CC_REFLECT_ARRAY_9__(name, type, count) ArrayOf_##count##_##name

#define CC_REFLECT_EXPAND_ARRAY(type, count, ...) type, count

typedef enum {
    CCReflectAssignmentTransfer = CCReflectMapIntentTransfer,
    CCReflectAssignmentShare = CCReflectMapIntentShare,
    CCReflectAssignmentCopy = CCReflectMapIntentCopy
} CCReflectAssignment;

/*!
 * @brief Get the size of a given reflected type.
 * @param Type The reflected type to get the size of.
 * @return The size of the type.
 */
size_t CCReflectTypeSize(CCReflectType Type);

/*!
 * @brief Validate the data conforms to its validated type.
 * @param Validator The validated type for the data.
 * @param Data The data to validate.
 * @param Zone The memory zone to be used for internal allocations.
 * @param Allocator The allocator to be used as the default allocator.
 * @return The base type.
 */
CCReflectType CCReflectValidate(const CCReflectValidator *Validator, void *Data, CCMemoryZone Zone, CCAllocatorType Allocator);

extern const char *(*CCReflectTypeNameCallback)(CCReflectType Type);

/*!
 * @brief Get the type name.
 * @param Type The reflected type to get the name for.
 * @return The type name or NULL if it is not known.
 */
const char *CCReflectTypeName(CCReflectType Type);

/*!
 * @brief Print the type.
 * @param Type The type to be printed.
 */
void CCReflectPrintType(CCReflectType Type);

/*!
 * @brief Print the type.
 * @param File The file to print to.
 * @param Levels The current recursion level.
 * @param Type The reflected type to be printed.
 * @param Indentation The string to be used to indent.
 * @param IndentCount The current number of indentations at this scope.
 * @param ShouldIndent Whether it needs to indent or not.
 */
void CCReflectDetailedPrintType(FILE *File, size_t Levels, CCReflectType Type, const char *Indentation, size_t IndentCount, _Bool *ShouldIndent);

/*!
 * @brief Print the data.
 * @param Type The reflected type of the data to be printed.
 * @param Data The data to be printed.
 */
void CCReflectPrint(CCReflectType Type, const void *Data);

/*!
 * @brief Print the data.
 * @param File The file to print to.
 * @param Levels The current recursion level.
 * @param Type The reflected type of the data to be printed.
 * @param Data The data to be printed.
 * @param MakeCompoundLiteral Whether to print the current block as a compound literal.
 * @param Indentation The string to be used to indent.
 * @param IndentCount The current number of indentations at this scope.
 * @param ShouldIndent Whether it needs to indent or not.
 * @param Zone The memory zone to use for any allocations.
 */
void CCReflectDetailedPrint(FILE *File, size_t Levels, CCReflectType Type, const void *Data, _Bool MakeCompoundLiteral, const char *Indentation, size_t IndentCount, _Bool *ShouldIndent, CCMemoryZone Zone);

/*!
 * @brief Print the indentation.
 * @param File The file to print to.
 * @param Indentation The string to be used to indent.
 * @param IndentCount The current number of indentations at this scope.
 * @param ShouldIndent Whether it needs to indent or not.
 */
void CCReflectPrintIndent(FILE *File, const char *Indentation, size_t IndentCount, _Bool *ShouldIndent);

/*!
 * @brief Copy the data.
 * @param Type The reflected type of the data to be copied.
 * @param Data The destination to copy to.
 * @param Source The source to copy from.
 * @param Zone The memory zone to be used for internal allocations.
 * @param Allocator The allocator to be used as the default allocator.
 * @param Assignment The assignment behaviour.
 * @param Validate Wether the data should be validated or not.
 */
void CCReflectCopy(CCReflectType Type, void *Data, const void *Source, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectAssignment Assignment, _Bool Validate);

typedef void (*CCReflectStreamReader)(void *Stream, void *Data, size_t Size);
typedef void (*CCReflectStreamWriter)(void *Stream, const void *Data, size_t Size);

/*!
 * @brief Serialize the data as binary data.
 * @param Type The reflected type of the data to be serialized.
 * @param Data The data to be serialized.
 * @param SerializedEndianness The endianness of the serialized binary data.
 * @param PreferVariableLength The minimum size of any fixed sized integers that should be stored using the variable length integer format instead.
 * @param Stream The stream to be used for writing the binary data to.
 * @param Write The writer function.
 * @param Zone The memory zone to be used for internal allocations.
 */
void CCReflectSerializeBinary(CCReflectType Type, const void *Data, CCReflectEndian SerializedEndianness, size_t PreferVariableLength, void *Stream, CCReflectStreamWriter Write, CCMemoryZone Zone);

/*!
 * @brief Deserialize the data from binary data.
 * @param Type The reflected type of the data to be deserialized.
 * @param Data A pointer to where to store the deserialized data.
 * @param SerializedEndianness The endianness of the binary data.
 * @param PreferVariableLength The minimum size of any fixed sized integers that are stored using the variable length integer format.
 * @param Stream The stream to be used for reading the binary data from.
 * @param Read The reader function.
 * @param Zone The memory zone to be used for internal allocations.
 * @param Allocator The allocator to be used as the default allocator.
 */
void CCReflectDeserializeBinary(CCReflectType Type, void *Data, CCReflectEndian SerializedEndianness, size_t PreferVariableLength, void *Stream, CCReflectStreamReader Read, CCMemoryZone Zone, CCAllocatorType Allocator);

#pragma mark - Handlers

typedef struct {
    FILE *file;
    size_t levels;
    _Bool makeCompoundLiteral;
    const char *indentation;
    size_t indentCount;
    _Bool *shouldIndent;
    CCMemoryZone zone;
} CCReflectPrintHandlerArgs;

void CCReflectPrintHandler(CCReflectType Type, const void *Data, CCReflectPrintHandlerArgs *Args);

typedef struct {
    CCReflectType type;
    void *dest;
    CCMemoryZone zone;
    CCAllocatorType allocator;
    _Bool validate;
} CCReflectCopyHandlerArgs;

void CCReflectTransferHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args);
void CCReflectShareHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args);
void CCReflectCopyHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args);

#pragma mark -

#define CC_TYPE_CCReflectType(...) CCReflectType
#define CC_TYPE_0_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_1_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_2_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_3_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_4_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_5_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_6_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_7_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_8_CCReflectType CC_TYPE_CCReflectType,
#define CC_TYPE_9_CCReflectType CC_TYPE_CCReflectType,

#define CC_PRESERVE_CC_TYPE_CCReflectType CC_TYPE_CCReflectType

#define CC_TYPE_DECL_CCReflectType(...) CCReflectType, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_1_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_2_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_3_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_4_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_5_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_6_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_7_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_8_CCReflectType CC_TYPE_DECL_CCReflectType,
#define CC_TYPE_DECL_9_CCReflectType CC_TYPE_DECL_CCReflectType,

#define CC_MANGLE_TYPE_0_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_1_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_2_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_3_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_4_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_5_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_6_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_7_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_8_CCReflectType CCReflectType
#define CC_MANGLE_TYPE_9_CCReflectType CCReflectType

#define CC_TYPE_CCReflectTypeID(...) CCReflectTypeID
#define CC_TYPE_0_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_1_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_2_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_3_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_4_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_5_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_6_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_7_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_8_CCReflectTypeID CC_TYPE_CCReflectTypeID,
#define CC_TYPE_9_CCReflectTypeID CC_TYPE_CCReflectTypeID,

#define CC_PRESERVE_CC_TYPE_CCReflectTypeID CC_TYPE_CCReflectTypeID

#define CC_TYPE_DECL_CCReflectTypeID(...) CCReflectTypeID, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_1_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_2_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_3_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_4_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_5_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_6_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_7_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_8_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,
#define CC_TYPE_DECL_9_CCReflectTypeID CC_TYPE_DECL_CCReflectTypeID,

#define CC_MANGLE_TYPE_0_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_1_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_2_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_3_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_4_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_5_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_6_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_7_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_8_CCReflectTypeID CCReflectTypeID
#define CC_MANGLE_TYPE_9_CCReflectTypeID CCReflectTypeID

#define CC_TYPE_CCReflectStorage(...) CCReflectStorage
#define CC_TYPE_0_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_1_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_2_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_3_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_4_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_5_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_6_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_7_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_8_CCReflectStorage CC_TYPE_CCReflectStorage,
#define CC_TYPE_9_CCReflectStorage CC_TYPE_CCReflectStorage,

#define CC_PRESERVE_CC_TYPE_CCReflectStorage CC_TYPE_CCReflectStorage

#define CC_TYPE_DECL_CCReflectStorage(...) CCReflectStorage, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_1_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_2_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_3_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_4_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_5_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_6_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_7_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_8_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,
#define CC_TYPE_DECL_9_CCReflectStorage CC_TYPE_DECL_CCReflectStorage,

#define CC_MANGLE_TYPE_0_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_1_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_2_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_3_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_4_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_5_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_6_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_7_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_8_CCReflectStorage CCReflectStorage
#define CC_MANGLE_TYPE_9_CCReflectStorage CCReflectStorage

#define CC_TYPE_CCReflectOwnership(...) CCReflectOwnership
#define CC_TYPE_0_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_1_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_2_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_3_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_4_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_5_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_6_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_7_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_8_CCReflectOwnership CC_TYPE_CCReflectOwnership,
#define CC_TYPE_9_CCReflectOwnership CC_TYPE_CCReflectOwnership,

#define CC_PRESERVE_CC_TYPE_CCReflectOwnership CC_TYPE_CCReflectOwnership

#define CC_TYPE_DECL_CCReflectOwnership(...) CCReflectOwnership, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_1_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_2_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_3_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_4_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_5_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_6_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_7_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_8_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,
#define CC_TYPE_DECL_9_CCReflectOwnership CC_TYPE_DECL_CCReflectOwnership,

#define CC_MANGLE_TYPE_0_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_1_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_2_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_3_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_4_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_5_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_6_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_7_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_8_CCReflectOwnership CCReflectOwnership
#define CC_MANGLE_TYPE_9_CCReflectOwnership CCReflectOwnership

#define CC_TYPE_CCReflectPointer(...) CCReflectPointer
#define CC_TYPE_0_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_1_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_2_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_3_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_4_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_5_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_6_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_7_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_8_CCReflectPointer CC_TYPE_CCReflectPointer,
#define CC_TYPE_9_CCReflectPointer CC_TYPE_CCReflectPointer,

#define CC_PRESERVE_CC_TYPE_CCReflectPointer CC_TYPE_CCReflectPointer

#define CC_TYPE_DECL_CCReflectPointer(...) CCReflectPointer, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_1_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_2_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_3_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_4_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_5_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_6_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_7_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_8_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,
#define CC_TYPE_DECL_9_CCReflectPointer CC_TYPE_DECL_CCReflectPointer,

#define CC_MANGLE_TYPE_0_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_1_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_2_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_3_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_4_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_5_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_6_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_7_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_8_CCReflectPointer CCReflectPointer
#define CC_MANGLE_TYPE_9_CCReflectPointer CCReflectPointer

#define CC_TYPE_CCReflectDynamicPointer(...) CCReflectDynamicPointer
#define CC_TYPE_0_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_1_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_2_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_3_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_4_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_5_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_6_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_7_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_8_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,
#define CC_TYPE_9_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer,

#define CC_PRESERVE_CC_TYPE_CCReflectDynamicPointer CC_TYPE_CCReflectDynamicPointer

#define CC_TYPE_DECL_CCReflectDynamicPointer(...) CCReflectDynamicPointer, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_1_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_2_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_3_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_4_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_5_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_6_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_7_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_8_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,
#define CC_TYPE_DECL_9_CCReflectDynamicPointer CC_TYPE_DECL_CCReflectDynamicPointer,

#define CC_MANGLE_TYPE_0_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_1_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_2_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_3_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_4_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_5_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_6_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_7_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_8_CCReflectDynamicPointer CCReflectDynamicPointer
#define CC_MANGLE_TYPE_9_CCReflectDynamicPointer CCReflectDynamicPointer

#define CC_TYPE_CCReflectStaticPointer(...) CCReflectStaticPointer
#define CC_TYPE_0_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_1_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_2_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_3_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_4_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_5_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_6_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_7_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_8_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,
#define CC_TYPE_9_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer,

#define CC_PRESERVE_CC_TYPE_CCReflectStaticPointer CC_TYPE_CCReflectStaticPointer

#define CC_TYPE_DECL_CCReflectStaticPointer(...) CCReflectStaticPointer, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_1_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_2_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_3_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_4_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_5_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_6_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_7_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_8_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,
#define CC_TYPE_DECL_9_CCReflectStaticPointer CC_TYPE_DECL_CCReflectStaticPointer,

#define CC_MANGLE_TYPE_0_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_1_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_2_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_3_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_4_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_5_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_6_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_7_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_8_CCReflectStaticPointer CCReflectStaticPointer
#define CC_MANGLE_TYPE_9_CCReflectStaticPointer CCReflectStaticPointer

#define CC_TYPE_CCReflectEndian(...) CCReflectEndian
#define CC_TYPE_0_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_1_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_2_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_3_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_4_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_5_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_6_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_7_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_8_CCReflectEndian CC_TYPE_CCReflectEndian,
#define CC_TYPE_9_CCReflectEndian CC_TYPE_CCReflectEndian,

#define CC_PRESERVE_CC_TYPE_CCReflectEndian CC_TYPE_CCReflectEndian

#define CC_TYPE_DECL_CCReflectEndian(...) CCReflectEndian, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_1_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_2_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_3_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_4_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_5_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_6_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_7_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_8_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,
#define CC_TYPE_DECL_9_CCReflectEndian CC_TYPE_DECL_CCReflectEndian,

#define CC_MANGLE_TYPE_0_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_1_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_2_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_3_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_4_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_5_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_6_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_7_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_8_CCReflectEndian CCReflectEndian
#define CC_MANGLE_TYPE_9_CCReflectEndian CCReflectEndian

#define CC_TYPE_CCReflectInteger(...) CCReflectInteger
#define CC_TYPE_0_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_1_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_2_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_3_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_4_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_5_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_6_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_7_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_8_CCReflectInteger CC_TYPE_CCReflectInteger,
#define CC_TYPE_9_CCReflectInteger CC_TYPE_CCReflectInteger,

#define CC_PRESERVE_CC_TYPE_CCReflectInteger CC_TYPE_CCReflectInteger

#define CC_TYPE_DECL_CCReflectInteger(...) CCReflectInteger, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_1_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_2_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_3_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_4_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_5_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_6_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_7_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_8_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,
#define CC_TYPE_DECL_9_CCReflectInteger CC_TYPE_DECL_CCReflectInteger,

#define CC_MANGLE_TYPE_0_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_1_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_2_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_3_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_4_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_5_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_6_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_7_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_8_CCReflectInteger CCReflectInteger
#define CC_MANGLE_TYPE_9_CCReflectInteger CCReflectInteger

#define CC_TYPE_CCReflectFloat(...) CCReflectFloat
#define CC_TYPE_0_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_1_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_2_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_3_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_4_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_5_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_6_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_7_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_8_CCReflectFloat CC_TYPE_CCReflectFloat,
#define CC_TYPE_9_CCReflectFloat CC_TYPE_CCReflectFloat,

#define CC_PRESERVE_CC_TYPE_CCReflectFloat CC_TYPE_CCReflectFloat

#define CC_TYPE_DECL_CCReflectFloat(...) CCReflectFloat, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_1_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_2_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_3_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_4_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_5_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_6_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_7_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_8_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,
#define CC_TYPE_DECL_9_CCReflectFloat CC_TYPE_DECL_CCReflectFloat,

#define CC_MANGLE_TYPE_0_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_1_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_2_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_3_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_4_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_5_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_6_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_7_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_8_CCReflectFloat CCReflectFloat
#define CC_MANGLE_TYPE_9_CCReflectFloat CCReflectFloat

#define CC_TYPE_CCReflectStructField(...) CCReflectStructField
#define CC_TYPE_0_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_1_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_2_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_3_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_4_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_5_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_6_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_7_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_8_CCReflectStructField CC_TYPE_CCReflectStructField,
#define CC_TYPE_9_CCReflectStructField CC_TYPE_CCReflectStructField,

#define CC_PRESERVE_CC_TYPE_CCReflectStructField CC_TYPE_CCReflectStructField

#define CC_TYPE_DECL_CCReflectStructField(...) CCReflectStructField, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_1_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_2_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_3_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_4_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_5_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_6_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_7_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_8_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,
#define CC_TYPE_DECL_9_CCReflectStructField CC_TYPE_DECL_CCReflectStructField,

#define CC_MANGLE_TYPE_0_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_1_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_2_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_3_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_4_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_5_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_6_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_7_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_8_CCReflectStructField CCReflectStructField
#define CC_MANGLE_TYPE_9_CCReflectStructField CCReflectStructField

#define CC_TYPE_CCReflectStruct(...) CCReflectStruct
#define CC_TYPE_0_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_1_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_2_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_3_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_4_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_5_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_6_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_7_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_8_CCReflectStruct CC_TYPE_CCReflectStruct,
#define CC_TYPE_9_CCReflectStruct CC_TYPE_CCReflectStruct,

#define CC_PRESERVE_CC_TYPE_CCReflectStruct CC_TYPE_CCReflectStruct

#define CC_TYPE_DECL_CCReflectStruct(...) CCReflectStruct, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_1_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_2_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_3_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_4_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_5_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_6_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_7_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_8_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,
#define CC_TYPE_DECL_9_CCReflectStruct CC_TYPE_DECL_CCReflectStruct,

#define CC_MANGLE_TYPE_0_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_1_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_2_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_3_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_4_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_5_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_6_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_7_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_8_CCReflectStruct CCReflectStruct
#define CC_MANGLE_TYPE_9_CCReflectStruct CCReflectStruct

#define CC_TYPE_CCReflectArray(...) CCReflectArray
#define CC_TYPE_0_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_1_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_2_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_3_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_4_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_5_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_6_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_7_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_8_CCReflectArray CC_TYPE_CCReflectArray,
#define CC_TYPE_9_CCReflectArray CC_TYPE_CCReflectArray,

#define CC_PRESERVE_CC_TYPE_CCReflectArray CC_TYPE_CCReflectArray

#define CC_TYPE_DECL_CCReflectArray(...) CCReflectArray, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_1_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_2_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_3_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_4_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_5_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_6_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_7_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_8_CCReflectArray CC_TYPE_DECL_CCReflectArray,
#define CC_TYPE_DECL_9_CCReflectArray CC_TYPE_DECL_CCReflectArray,

#define CC_MANGLE_TYPE_0_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_1_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_2_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_3_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_4_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_5_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_6_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_7_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_8_CCReflectArray CCReflectArray
#define CC_MANGLE_TYPE_9_CCReflectArray CCReflectArray

#define CC_TYPE_CCReflectEnumerable(...) CCReflectEnumerable
#define CC_TYPE_0_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_1_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_2_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_3_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_4_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_5_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_6_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_7_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_8_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,
#define CC_TYPE_9_CCReflectEnumerable CC_TYPE_CCReflectEnumerable,

#define CC_PRESERVE_CC_TYPE_CCReflectEnumerable CC_TYPE_CCReflectEnumerable

#define CC_TYPE_DECL_CCReflectEnumerable(...) CCReflectEnumerable, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_1_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_2_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_3_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_4_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_5_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_6_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_7_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_8_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,
#define CC_TYPE_DECL_9_CCReflectEnumerable CC_TYPE_DECL_CCReflectEnumerable,

#define CC_MANGLE_TYPE_0_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_1_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_2_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_3_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_4_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_5_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_6_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_7_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_8_CCReflectEnumerable CCReflectEnumerable
#define CC_MANGLE_TYPE_9_CCReflectEnumerable CCReflectEnumerable

#define CC_TYPE_CCReflectOpaque(...) CCReflectOpaque
#define CC_TYPE_0_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_1_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_2_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_3_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_4_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_5_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_6_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_7_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_8_CCReflectOpaque CC_TYPE_CCReflectOpaque,
#define CC_TYPE_9_CCReflectOpaque CC_TYPE_CCReflectOpaque,

#define CC_PRESERVE_CC_TYPE_CCReflectOpaque CC_TYPE_CCReflectOpaque

#define CC_TYPE_DECL_CCReflectOpaque(...) CCReflectOpaque, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_1_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_2_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_3_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_4_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_5_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_6_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_7_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_8_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,
#define CC_TYPE_DECL_9_CCReflectOpaque CC_TYPE_DECL_CCReflectOpaque,

#define CC_MANGLE_TYPE_0_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_1_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_2_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_3_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_4_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_5_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_6_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_7_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_8_CCReflectOpaque CCReflectOpaque
#define CC_MANGLE_TYPE_9_CCReflectOpaque CCReflectOpaque

#define CC_TYPE_CCReflectTypeMapper(...) CCReflectTypeMapper
#define CC_TYPE_0_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_1_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_2_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_3_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_4_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_5_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_6_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_7_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_8_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,
#define CC_TYPE_9_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper,

#define CC_PRESERVE_CC_TYPE_CCReflectTypeMapper CC_TYPE_CCReflectTypeMapper

#define CC_TYPE_DECL_CCReflectTypeMapper(...) CCReflectTypeMapper, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_1_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_2_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_3_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_4_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_5_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_6_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_7_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_8_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,
#define CC_TYPE_DECL_9_CCReflectTypeMapper CC_TYPE_DECL_CCReflectTypeMapper,

#define CC_MANGLE_TYPE_0_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_1_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_2_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_3_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_4_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_5_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_6_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_7_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_8_CCReflectTypeMapper CCReflectTypeMapper
#define CC_MANGLE_TYPE_9_CCReflectTypeMapper CCReflectTypeMapper

#define CC_TYPE_CCReflectTypeUnmapper(...) CCReflectTypeUnmapper
#define CC_TYPE_0_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_1_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_2_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_3_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_4_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_5_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_6_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_7_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_8_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,
#define CC_TYPE_9_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper,

#define CC_PRESERVE_CC_TYPE_CCReflectTypeUnmapper CC_TYPE_CCReflectTypeUnmapper

#define CC_TYPE_DECL_CCReflectTypeUnmapper(...) CCReflectTypeUnmapper, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_1_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_2_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_3_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_4_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_5_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_6_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_7_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_8_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,
#define CC_TYPE_DECL_9_CCReflectTypeUnmapper CC_TYPE_DECL_CCReflectTypeUnmapper,

#define CC_MANGLE_TYPE_0_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_1_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_2_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_3_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_4_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_5_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_6_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_7_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_8_CCReflectTypeUnmapper CCReflectTypeUnmapper
#define CC_MANGLE_TYPE_9_CCReflectTypeUnmapper CCReflectTypeUnmapper

#define CC_TYPE_CCReflectValidator(...) CCReflectValidator
#define CC_TYPE_0_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_1_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_2_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_3_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_4_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_5_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_6_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_7_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_8_CCReflectValidator CC_TYPE_CCReflectValidator,
#define CC_TYPE_9_CCReflectValidator CC_TYPE_CCReflectValidator,

#define CC_PRESERVE_CC_TYPE_CCReflectValidator CC_TYPE_CCReflectValidator

#define CC_TYPE_DECL_CCReflectValidator(...) CCReflectValidator, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_1_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_2_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_3_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_4_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_5_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_6_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_7_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_8_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,
#define CC_TYPE_DECL_9_CCReflectValidator CC_TYPE_DECL_CCReflectValidator,

#define CC_MANGLE_TYPE_0_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_1_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_2_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_3_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_4_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_5_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_6_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_7_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_8_CCReflectValidator CCReflectValidator
#define CC_MANGLE_TYPE_9_CCReflectValidator CCReflectValidator

#define CC_TYPE_CCReflectValidation(...) CCReflectValidation
#define CC_TYPE_0_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_1_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_2_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_3_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_4_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_5_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_6_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_7_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_8_CCReflectValidation CC_TYPE_CCReflectValidation,
#define CC_TYPE_9_CCReflectValidation CC_TYPE_CCReflectValidation,

#define CC_PRESERVE_CC_TYPE_CCReflectValidation CC_TYPE_CCReflectValidation

#define CC_TYPE_DECL_CCReflectValidation(...) CCReflectValidation, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_1_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_2_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_3_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_4_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_5_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_6_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_7_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_8_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,
#define CC_TYPE_DECL_9_CCReflectValidation CC_TYPE_DECL_CCReflectValidation,

#define CC_MANGLE_TYPE_0_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_1_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_2_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_3_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_4_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_5_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_6_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_7_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_8_CCReflectValidation CCReflectValidation
#define CC_MANGLE_TYPE_9_CCReflectValidation CCReflectValidation

#define CC_TYPE_CCReflectValue(...) CCReflectValue
#define CC_TYPE_0_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_1_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_2_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_3_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_4_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_5_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_6_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_7_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_8_CCReflectValue CC_TYPE_CCReflectValue,
#define CC_TYPE_9_CCReflectValue CC_TYPE_CCReflectValue,

#define CC_PRESERVE_CC_TYPE_CCReflectValue CC_TYPE_CCReflectValue

#define CC_TYPE_DECL_CCReflectValue(...) CCReflectValue, __VA_ARGS__
#define CC_TYPE_DECL_0_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_1_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_2_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_3_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_4_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_5_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_6_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_7_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_8_CCReflectValue CC_TYPE_DECL_CCReflectValue,
#define CC_TYPE_DECL_9_CCReflectValue CC_TYPE_DECL_CCReflectValue,

#define CC_MANGLE_TYPE_0_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_1_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_2_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_3_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_4_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_5_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_6_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_7_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_8_CCReflectValue CCReflectValue
#define CC_MANGLE_TYPE_9_CCReflectValue CCReflectValue

#endif
