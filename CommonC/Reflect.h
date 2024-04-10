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

typedef void (*CCReflectTypeHandler)(CCReflectType Type, const void *Data, void *Args);

typedef void (*CCReflectTypeMapper)(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

typedef struct {
    CCReflectTypeID id;
    CCReflectType type;
    enum {
        CCReflectStorageStatic,
        CCReflectStorageDynamic
    } storage;
    enum {
        CCReflectOwnershipWeak,
        CCReflectOwnershipTransfer,
        CCReflectOwnershipRetain
    } ownership;
} CCReflectPointer;

typedef struct {
    CCReflectPointer pointer;
    CCReflectTypeMapper map;
    CCReflectTypeMapper unmap;
} CCReflectStaticPointer;

typedef struct {
    CCReflectPointer pointer;
    /// Set to CC_NULL_ALLOCATOR to use the provided allocator, otherwise set to the allocator that should be used instead.
    CCAllocatorType allocator;
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

#define CCReflectStruct(n) struct { \
    CCReflectTypeID id; \
    size_t size; \
    size_t count; \
    struct { \
        CCString name; \
        size_t offset; \
        CCReflectType type; \
    } fields[n]; \
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
    CCReflectTypeMapper map;
    CCReflectTypeMapper unmap;
} CCReflectOpaque;

#define CC_REFLECT_INTEGER(type, order, ...) ((CCReflectInteger){ .id = CCReflectTypeInteger, .size = sizeof(type), .endian = order, __VA_ARGS__ })
#define CC_REFLECT_SIGNED_INTEGER(type, order, ...) CC_REFLECT_INTEGER(type, order, .sign = TRUE, __VA_ARGS__)
#define CC_REFLECT_UNSIGNED_INTEGER(type, order, ...) CC_REFLECT_INTEGER(type, order, .sign = FALSE, __VA_ARGS__)
#define CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(type, order, ...) CC_REFLECT_SIGNED_INTEGER(type, order, .fixed = TRUE, __VA_ARGS__)
#define CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(type, order, ...) CC_REFLECT_UNSIGNED_INTEGER(type, order, .fixed = TRUE, __VA_ARGS__)

#define CC_REFLECT_FLOAT(type, order, ...) ((CCReflectFloat){ .id = CCReflectTypeFloat, .size = sizeof(type), .endian = order, __VA_ARGS__ })

#define CC_REFLECT_POINTER(type_, storage_, ownership_) ((CCReflectPointer){ .id = CCReflectTypePointer, .type = type_, .storage = storage_, .ownership = ownership_ })
#define CC_REFLECT_STATIC_POINTER(type, ownership, mapper, unmapper) ((CCReflectStaticPointer){ .pointer = CC_REFLECT_POINTER(type, CCReflectStorageStatic, ownership), .map = mapper, .unmap = unmapper })
#define CC_REFLECT_DYNAMIC_POINTER(type, ownership, ...) ((CCReflectDynamicPointer){ .pointer = CC_REFLECT_POINTER(type, CCReflectStorageDynamic, ownership), .allocator = CC_NULL_ALLOCATOR, __VA_ARGS__ })

#define CC_REFLECT_ARRAY(type_, count_) ((CCReflectArray){ .id = CCReflectTypeArray, .type = type_, .count = count_ })

#define CC_REFLECT_ENUMERABLE(type_, ...) ((CCReflectEnumerable){ .id = CCReflectTypeEnumerable, .type = type_, .count = SIZE_MAX, __VA_ARGS__ })

#define CC_REFLECT_OPAQUE(size_, mapper, unmapper) ((CCReflectOpaque){ .id = CCReflectTypeOpaque, .size = size_, .map = mapper, .unmap = unmapper })

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
    CCReflectAssignmentTransfer,
    CCReflectAssignmentShare,
    CCReflectAssignmentCopy
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
    void *dest;
    CCMemoryZone zone;
    CCAllocatorType allocator;
    _Bool validate;
} CCReflectCopyHandlerArgs;

void CCReflectTransferHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args);
void CCReflectShareHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args);
void CCReflectCopyHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args);

#endif
