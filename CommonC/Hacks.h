/*
 *  Copyright (c) 2013, Stefan Johnson
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

/*
 For code that is on the more hackish side and waiting for better alternatives to change to. The majority of this is for internal use by the framework to provide
 consistency depending on what functionality is available.
 
 CC_SILENCE_UNUSED_WARNING: Silences the unused value/variable warning where it would otherwise not be appropriate or sometimes even able to use a compiler extension.
 CC_VA_ARG_COUNT: Get the argument count for __VA_ARGS__.
 CC_TYPE_PRESETS: Repeat the input for the non-spaced types and types defined by this library.
 CC_CUSTOM_TYPES: Intended to be defined by users of the library to easily include any custom types in the type preset definition.
 CC_CUSTOM_TYPES_: Intended to be defined by users of the library to easily include any custom types in the type preset definition.
 */

#ifndef CommonC_Hacks_h
#define CommonC_Hacks_h

#include <CommonC/Extensions.h>
#include <CommonC/Generics.h>


#define CC_NAME_RETURN_VALUE_FUNCTION_(name) CCGenericReturnValue_##name##_
#define CC_GENERATE_RETURN_VALUE_FUNCTION_(name, type) static CC_FORCE_INLINE type CC_NAME_RETURN_VALUE_FUNCTION_(name)(type val){ return val; }
#define CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(name, type) type: CC_NAME_RETURN_VALUE_FUNCTION_(name)

CC_GENERATE_RETURN_VALUE_FUNCTION_(char, char)
CC_GENERATE_RETURN_VALUE_FUNCTION_(short, short)
CC_GENERATE_RETURN_VALUE_FUNCTION_(int, int)
CC_GENERATE_RETURN_VALUE_FUNCTION_(long, long)
CC_GENERATE_RETURN_VALUE_FUNCTION_(long_long, long long)
CC_GENERATE_RETURN_VALUE_FUNCTION_(float, float)
CC_GENERATE_RETURN_VALUE_FUNCTION_(double, double)
CC_GENERATE_RETURN_VALUE_FUNCTION_(long_double, long double)
CC_GENERATE_RETURN_VALUE_FUNCTION_(void_ptr, void*)

#define CC_SILENCE_UNUSED_WARNING(val) (CC_GENERIC_EVALUATE(val, \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(char, char), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(short, short), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(int, int), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(long, long), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(long_long, long long), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(float, float), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(double, double), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(long_double, long double), \
default: CC_NAME_RETURN_VALUE_FUNCTION_(void_ptr) \
))(val)

#define CC_VA_ARG_COUNT(...) CC_VA_ARG_COUNT_(0, ## __VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define CC_VA_ARG_COUNT_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, count, ...) count

#define CC_VA_CALL(fun, ...) CC_VA_CALL_(CC_VA_ARG_COUNT(__VA_ARGS__), fun, __VA_ARGS__)
#define CC_VA_CALL_(n, ...) CC_VA_CALL__(n, __VA_ARGS__)
#define CC_VA_CALL__(n, fun, ...) CC_VA_CALL___(fun##n, __VA_ARGS__)
#define CC_VA_CALL___(fun, ...) fun(__VA_ARGS__)

#ifndef CC_CUSTOM_TYPES
#define CC_CUSTOM_TYPES(func, ...)
#endif

#ifndef CC_CUSTOM_TYPES_
#define CC_CUSTOM_TYPES_(func, ...)
#endif

#define CC_TYPE_PRESETS(func, ...) \
func(__VA_ARGS__, _Bool); \
func(__VA_ARGS__, char); \
func(__VA_ARGS__, short); \
func(__VA_ARGS__, int); \
func(__VA_ARGS__, long); \
func(__VA_ARGS__, float); \
func(__VA_ARGS__, double); \
func(__VA_ARGS__, int8_t); \
func(__VA_ARGS__, int16_t); \
func(__VA_ARGS__, int32_t); \
func(__VA_ARGS__, int64_t); \
func(__VA_ARGS__, uint8_t); \
func(__VA_ARGS__, uint16_t); \
func(__VA_ARGS__, uint32_t); \
func(__VA_ARGS__, uint64_t); \
func(__VA_ARGS__, intmax_t); \
func(__VA_ARGS__, uintmax_t); \
func(__VA_ARGS__, intptr_t); \
func(__VA_ARGS__, uintptr_t); \
func(__VA_ARGS__, ptrdiff_t); \
func(__VA_ARGS__, size_t); \
func(__VA_ARGS__, CCConcurrentIDGenerator); \
func(__VA_ARGS__, CCConcurrentBuffer); \
func(__VA_ARGS__, CCConcurrentIndexBuffer); \
func(__VA_ARGS__, CCTask); \
func(__VA_ARGS__, CCTaskQueue); \
func(__VA_ARGS__, CCConcurrentGarbageCollector); \
func(__VA_ARGS__, CCQueue); \
func(__VA_ARGS__, CCConcurrentQueue); \
func(__VA_ARGS__, CCHashMap); \
func(__VA_ARGS__, CCHashMapEntry); \
func(__VA_ARGS__, CCDictionary); \
func(__VA_ARGS__, CCDictionaryEntry); \
func(__VA_ARGS__, CCDictionaryHint); \
func(__VA_ARGS__, CCString); \
func(__VA_ARGS__, CCChar); \
func(__VA_ARGS__, CCStringEncoding); \
func(__VA_ARGS__, CCStringHint); \
func(__VA_ARGS__, CCBufferMap); \
func(__VA_ARGS__, CCData); \
func(__VA_ARGS__, CCDataHint); \
func(__VA_ARGS__, CCDataBufferHint); \
func(__VA_ARGS__, CCLinkedListNode); \
func(__VA_ARGS__, CCLinkedList); \
func(__VA_ARGS__, CCLinkedListNodeData); \
func(__VA_ARGS__, CCArray); \
func(__VA_ARGS__, CCList); \
func(__VA_ARGS__, CCConcurrentArray); \
func(__VA_ARGS__, CCConcurrentIndexMap); \
func(__VA_ARGS__, CCEnumerator); \
func(__VA_ARGS__, CCComparisonResult); \
func(__VA_ARGS__, CCCollection); \
func(__VA_ARGS__, CCOrderedCollection); \
func(__VA_ARGS__, CCCollectionHint); \
func(__VA_ARGS__, CCOrderedCollectionHint); \
func(__VA_ARGS__, CCCollectionEntry); \
func(__VA_ARGS__, CCBigInt); \
func(__VA_ARGS__, CCPid); \
func(__VA_ARGS__, FSPathComponent); \
func(__VA_ARGS__, FSPath); \
func(__VA_ARGS__, FSHandle); \
func(__VA_ARGS__, CCVector2D); \
func(__VA_ARGS__, CCVector3D); \
func(__VA_ARGS__, CCVector4D); \
func(__VA_ARGS__, CCVector2Di); \
func(__VA_ARGS__, CCVector3Di); \
func(__VA_ARGS__, CCVector4Di); \
func(__VA_ARGS__, CCColourRGB); \
func(__VA_ARGS__, CCColourRGBi); \
func(__VA_ARGS__, CCColourRGBA); \
func(__VA_ARGS__, CCColourRGBAi); \
func(__VA_ARGS__, CCRect); \
func(__VA_ARGS__, CCMatrix2); \
func(__VA_ARGS__, CCMatrix3); \
func(__VA_ARGS__, CCMatrix4); \
func(__VA_ARGS__, CCVector); \
func(__VA_ARGS__, CCAllocatorType); \
CC_CUSTOM_TYPES(func, __VA_ARGS__);

#define CC_TYPE_PRESETS_(func, ...) \
func(__VA_ARGS__, _Bool); \
func(__VA_ARGS__, char); \
func(__VA_ARGS__, short); \
func(__VA_ARGS__, int); \
func(__VA_ARGS__, long); \
func(__VA_ARGS__, float); \
func(__VA_ARGS__, double); \
func(__VA_ARGS__, int8_t); \
func(__VA_ARGS__, int16_t); \
func(__VA_ARGS__, int32_t); \
func(__VA_ARGS__, int64_t); \
func(__VA_ARGS__, uint8_t); \
func(__VA_ARGS__, uint16_t); \
func(__VA_ARGS__, uint32_t); \
func(__VA_ARGS__, uint64_t); \
func(__VA_ARGS__, intmax_t); \
func(__VA_ARGS__, uintmax_t); \
func(__VA_ARGS__, intptr_t); \
func(__VA_ARGS__, uintptr_t); \
func(__VA_ARGS__, ptrdiff_t); \
func(__VA_ARGS__, size_t); \
func(__VA_ARGS__, CCConcurrentIDGenerator); \
func(__VA_ARGS__, CCConcurrentBuffer); \
func(__VA_ARGS__, CCConcurrentIndexBuffer); \
func(__VA_ARGS__, CCTask); \
func(__VA_ARGS__, CCTaskQueue); \
func(__VA_ARGS__, CCConcurrentGarbageCollector); \
func(__VA_ARGS__, CCQueue); \
func(__VA_ARGS__, CCConcurrentQueue); \
func(__VA_ARGS__, CCHashMap); \
func(__VA_ARGS__, CCHashMapEntry); \
func(__VA_ARGS__, CCDictionary); \
func(__VA_ARGS__, CCDictionaryEntry); \
func(__VA_ARGS__, CCDictionaryHint); \
func(__VA_ARGS__, CCString); \
func(__VA_ARGS__, CCChar); \
func(__VA_ARGS__, CCStringEncoding); \
func(__VA_ARGS__, CCStringHint); \
func(__VA_ARGS__, CCBufferMap); \
func(__VA_ARGS__, CCData); \
func(__VA_ARGS__, CCDataHint); \
func(__VA_ARGS__, CCDataBufferHint); \
func(__VA_ARGS__, CCLinkedListNode); \
func(__VA_ARGS__, CCLinkedList); \
func(__VA_ARGS__, CCLinkedListNodeData); \
func(__VA_ARGS__, CCArray); \
func(__VA_ARGS__, CCList); \
func(__VA_ARGS__, CCConcurrentArray); \
func(__VA_ARGS__, CCConcurrentIndexMap); \
func(__VA_ARGS__, CCEnumerator); \
func(__VA_ARGS__, CCComparisonResult); \
func(__VA_ARGS__, CCCollection); \
func(__VA_ARGS__, CCOrderedCollection); \
func(__VA_ARGS__, CCCollectionHint); \
func(__VA_ARGS__, CCOrderedCollectionHint); \
func(__VA_ARGS__, CCCollectionEntry); \
func(__VA_ARGS__, CCBigInt); \
func(__VA_ARGS__, CCPid); \
func(__VA_ARGS__, FSPathComponent); \
func(__VA_ARGS__, FSPath); \
func(__VA_ARGS__, FSHandle); \
func(__VA_ARGS__, CCVector2D); \
func(__VA_ARGS__, CCVector3D); \
func(__VA_ARGS__, CCVector4D); \
func(__VA_ARGS__, CCVector2Di); \
func(__VA_ARGS__, CCVector3Di); \
func(__VA_ARGS__, CCVector4Di); \
func(__VA_ARGS__, CCColourRGB); \
func(__VA_ARGS__, CCColourRGBi); \
func(__VA_ARGS__, CCColourRGBA); \
func(__VA_ARGS__, CCColourRGBAi); \
func(__VA_ARGS__, CCRect); \
func(__VA_ARGS__, CCMatrix2); \
func(__VA_ARGS__, CCMatrix3); \
func(__VA_ARGS__, CCMatrix4); \
func(__VA_ARGS__, CCVector); \
func(__VA_ARGS__, CCAllocatorType); \
CC_CUSTOM_TYPES_(func, __VA_ARGS__);

#define CC_INC(n) CC_INC_##n
#define CC_INC_0 1
#define CC_INC_1 2
#define CC_INC_2 3
#define CC_INC_3 4
#define CC_INC_4 5
#define CC_INC_5 6
#define CC_INC_6 7
#define CC_INC_7 8
#define CC_INC_8 9
#define CC_INC_9 10
#define CC_INC_10 11
#define CC_INC_11 12
#define CC_INC_12 13
#define CC_INC_13 14
#define CC_INC_14 15
#define CC_INC_15 16
#define CC_INC_16 17
#define CC_INC_17 18
#define CC_INC_18 19
#define CC_INC_19 20
#define CC_INC_20 21
#define CC_INC_21 22
#define CC_INC_22 23
#define CC_INC_23 24
#define CC_INC_24 25
#define CC_INC_25 26
#define CC_INC_26 27
#define CC_INC_27 28
#define CC_INC_28 29
#define CC_INC_29 30
#define CC_INC_30 31
#define CC_INC_31 32
#define CC_INC_32 33
#define CC_INC_33 34
#define CC_INC_34 35
#define CC_INC_35 36
#define CC_INC_36 37
#define CC_INC_37 38
#define CC_INC_38 39
#define CC_INC_39 40
#define CC_INC_40 41
#define CC_INC_41 42
#define CC_INC_42 43
#define CC_INC_43 44
#define CC_INC_44 45
#define CC_INC_45 46
#define CC_INC_46 47
#define CC_INC_47 48
#define CC_INC_48 49
#define CC_INC_49 50
#define CC_INC_50 51
#define CC_INC_51 52
#define CC_INC_52 53
#define CC_INC_53 54
#define CC_INC_54 55
#define CC_INC_55 56
#define CC_INC_56 57
#define CC_INC_57 58
#define CC_INC_58 59
#define CC_INC_59 60
#define CC_INC_60 61
#define CC_INC_61 62
#define CC_INC_62 63
#define CC_INC_63 64
#define CC_INC_64 65
#define CC_INC_65 66
#define CC_INC_66 67
#define CC_INC_67 68
#define CC_INC_68 69

#define CC_REPEAT(index, count, fun, ...) CC_REPEAT_##count(index, fun, __VA_ARGS__)
#define CC_REPEAT_0(index, fun, ...)
#define CC_REPEAT_1(index, fun, ...) fun(__VA_ARGS__, index)
#define CC_REPEAT_2(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_1(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_3(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_2(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_4(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_3(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_5(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_4(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_6(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_5(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_7(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_6(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_8(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_7(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_9(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_8(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_10(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_9(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_11(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_10(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_12(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_11(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_13(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_12(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_14(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_13(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_15(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_14(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_16(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_15(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_17(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_16(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_18(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_17(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_19(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_18(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_20(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_19(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_21(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_20(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_22(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_21(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_23(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_22(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_24(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_23(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_25(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_24(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_26(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_25(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_27(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_26(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_28(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_27(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_29(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_28(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_30(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_29(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_31(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_30(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_32(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_31(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_33(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_32(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_34(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_33(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_35(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_34(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_36(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_35(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_37(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_36(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_38(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_37(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_39(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_38(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_40(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_39(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_41(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_40(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_42(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_41(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_43(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_42(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_44(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_43(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_45(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_44(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_46(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_45(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_47(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_46(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_48(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_47(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_49(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_48(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_50(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_49(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_51(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_50(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_52(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_51(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_53(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_52(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_54(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_53(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_55(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_54(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_56(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_55(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_57(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_56(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_58(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_57(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_59(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_58(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_60(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_59(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_61(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_60(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_62(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_61(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_63(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_62(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_64(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_63(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_65(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_64(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_66(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_65(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_67(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_66(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_68(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_67(CC_INC(index), fun, __VA_ARGS__)
#define CC_REPEAT_69(index, fun, ...) fun(__VA_ARGS__, index), CC_REPEAT_68(CC_INC(index), fun, __VA_ARGS__)

#define CC_RESERVED_BIT(name, index) name##Reserved##index = (1ULL << index)

#define CC_RESERVED_BITS(name, index, count) CC_REPEAT(index, count, CC_RESERVED_BIT, name)

#define CC_GET(index, ...) CC_GET_(CC_GET_##index, __VA_ARGS__)
#define CC_GET_(get, ...) get(__VA_ARGS__)

#define CC_GET_0(x0, ...) x0
#define CC_GET_1(x0, x1, ...) x1
#define CC_GET_2(x0, x1, x2, ...) x2
#define CC_GET_3(x0, x1, x2, x3, ...) x3
#define CC_GET_4(x0, x1, x2, x3, x4, ...) x4
#define CC_GET_5(x0, x1, x2, x3, x4, x5, ...) x5
#define CC_GET_6(x0, x1, x2, x3, x4, x5, x6, ...) x6
#define CC_GET_7(x0, x1, x2, x3, x4, x5, x6, x7, ...) x7
#define CC_GET_8(x0, x1, x2, x3, x4, x5, x6, x7, x8, ...) x8
#define CC_GET_9(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, ...) x9
#define CC_GET_10(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, ...) x10
#define CC_GET_11(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, ...) x11
#define CC_GET_12(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, ...) x12
#define CC_GET_13(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, ...) x13
#define CC_GET_14(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, ...) x14
#define CC_GET_15(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, ...) x15
#define CC_GET_16(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, ...) x16
#define CC_GET_17(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, ...) x17
#define CC_GET_18(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, ...) x18
#define CC_GET_19(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, ...) x19
#define CC_GET_20(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, ...) x20

#define CC_MAP(fun, ...) CC_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_MAP_(fun, n, ...) CC_MAP__(fun, n, __VA_ARGS__)
#define CC_MAP__(fun, n, ...) CC_MAP___(fun, CC_MAP_##n, __VA_ARGS__)
#define CC_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)

#define CC_MAP_0(fun)
#define CC_MAP_1(fun, x0) fun(x0, 0)
#define CC_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)

#define CC_MAP_WITH(fun, x, ...) CC_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_MAP_WITH_(fun, x, n, ...) CC_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_MAP_WITH__(fun, x, n, ...) CC_MAP_WITH___(fun, x, CC_MAP_WITH_##n, __VA_ARGS__)
#define CC_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)

#define CC_MAP_WITH_0(fun, x)
#define CC_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)

#define CC_MERGE_MAP(fun, ...) CC_MERGE_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_MERGE_MAP_(fun, n, ...) CC_MERGE_MAP__(fun, n, __VA_ARGS__)
#define CC_MERGE_MAP__(fun, n, ...) CC_MERGE_MAP___(fun, CC_MERGE_MAP_##n, __VA_ARGS__)
#define CC_MERGE_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)

#define CC_MERGE_MAP_0(fun)
#define CC_MERGE_MAP_1(fun, x0) fun(x0, 0)
#define CC_MERGE_MAP_2(fun, x0, x1) fun(x0, 0) fun(x1, 1)
#define CC_MERGE_MAP_3(fun, x0, x1, x2) fun(x0, 0) fun(x1, 1) fun(x2, 2)
#define CC_MERGE_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3)
#define CC_MERGE_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4)
#define CC_MERGE_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5)
#define CC_MERGE_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6)
#define CC_MERGE_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7)
#define CC_MERGE_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8)
#define CC_MERGE_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9)
#define CC_MERGE_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10)
#define CC_MERGE_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11)
#define CC_MERGE_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12)
#define CC_MERGE_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13)
#define CC_MERGE_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13) fun(x14, 14)
#define CC_MERGE_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13) fun(x14, 14) fun(x15, 15)
#define CC_MERGE_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13) fun(x14, 14) fun(x15, 15) fun(x16, 16)
#define CC_MERGE_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13) fun(x14, 14) fun(x15, 15) fun(x16, 16) fun(x17, 17)
#define CC_MERGE_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13) fun(x14, 14) fun(x15, 15) fun(x16, 16) fun(x17, 17) fun(x18, 18)
#define CC_MERGE_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0) fun(x1, 1) fun(x2, 2) fun(x3, 3) fun(x4, 4) fun(x5, 5) fun(x6, 6) fun(x7, 7) fun(x8, 8) fun(x9, 9) fun(x10, 10) fun(x11, 11) fun(x12, 12) fun(x13, 13) fun(x14, 14) fun(x15, 15) fun(x16, 16) fun(x17, 17) fun(x18, 18) fun(x19, 19)

#define CC_MERGE_MAP_WITH(fun, x, ...) CC_MERGE_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_MERGE_MAP_WITH_(fun, x, n, ...) CC_MERGE_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_MERGE_MAP_WITH__(fun, x, n, ...) CC_MERGE_MAP_WITH___(fun, x, CC_MERGE_MAP_WITH_##n, __VA_ARGS__)
#define CC_MERGE_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)

#define CC_MERGE_MAP_WITH_0(fun, x)
#define CC_MERGE_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_MERGE_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x) fun(x1, 1, x)
#define CC_MERGE_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x)
#define CC_MERGE_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x)
#define CC_MERGE_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x)
#define CC_MERGE_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x)
#define CC_MERGE_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x)
#define CC_MERGE_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x)
#define CC_MERGE_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x)
#define CC_MERGE_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x)
#define CC_MERGE_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x)
#define CC_MERGE_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x)
#define CC_MERGE_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x)
#define CC_MERGE_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x)
#define CC_MERGE_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x) fun(x14, 14, x)
#define CC_MERGE_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x) fun(x14, 14, x) fun(x15, 15, x)
#define CC_MERGE_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x) fun(x14, 14, x) fun(x15, 15, x) fun(x16, 16, x)
#define CC_MERGE_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x) fun(x14, 14, x) fun(x15, 15, x) fun(x16, 16, x) fun(x17, 17, x)
#define CC_MERGE_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x) fun(x14, 14, x) fun(x15, 15, x) fun(x16, 16, x) fun(x17, 17, x) fun(x18, 18, x)
#define CC_MERGE_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x) fun(x1, 1, x) fun(x2, 2, x) fun(x3, 3, x) fun(x4, 4, x) fun(x5, 5, x) fun(x6, 6, x) fun(x7, 7, x) fun(x8, 8, x) fun(x9, 9, x) fun(x10, 10, x) fun(x11, 11, x) fun(x12, 12, x) fun(x13, 13, x) fun(x14, 14, x) fun(x15, 15, x) fun(x16, 16, x) fun(x17, 17, x) fun(x18, 18, x) fun(x19, 19, x)

#define CC_CAT(...) CC_CAT_(CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_CAT_(n, ...) CC_CAT__(n, __VA_ARGS__)
#define CC_CAT__(n, ...) CC_CAT___(CC_CAT_##n, __VA_ARGS__)
#define CC_CAT___(cat, ...) cat(__VA_ARGS__)

#define CC_CAT_0()
#define CC_CAT_1(x0) x0
#define CC_CAT_2(x0, x1) x0##x1
#define CC_CAT_3(x0, x1, x2) x0##x1##x2
#define CC_CAT_4(x0, x1, x2, x3) x0##x1##x2##x3
#define CC_CAT_5(x0, x1, x2, x3, x4) x0##x1##x2##x3##x4
#define CC_CAT_6(x0, x1, x2, x3, x4, x5) x0##x1##x2##x3##x4##x5
#define CC_CAT_7(x0, x1, x2, x3, x4, x5, x6) x0##x1##x2##x3##x4##x5##x6
#define CC_CAT_8(x0, x1, x2, x3, x4, x5, x6, x7) x0##x1##x2##x3##x4##x5##x6##x7
#define CC_CAT_9(x0, x1, x2, x3, x4, x5, x6, x7, x8) x0##x1##x2##x3##x4##x5##x6##x7##x8
#define CC_CAT_10(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9
#define CC_CAT_11(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10
#define CC_CAT_12(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11
#define CC_CAT_13(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12
#define CC_CAT_14(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13
#define CC_CAT_15(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13##x14
#define CC_CAT_16(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13##x14##x15
#define CC_CAT_17(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13##x14##x15##x16
#define CC_CAT_18(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13##x14##x15##x16##x17
#define CC_CAT_19(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13##x14##x15##x16##x17##x18
#define CC_CAT_20(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) x0##x1##x2##x3##x4##x5##x6##x7##x8##x9##x10##x11##x12##x13##x14##x15##x16##x17##x18##x19

#define CC_JOIN(sep, ...) CC_JOIN_(CC_VA_ARG_COUNT(__VA_ARGS__), sep, __VA_ARGS__)
#define CC_JOIN_(n, ...) CC_JOIN__(n, __VA_ARGS__)
#define CC_JOIN__(n, ...) CC_JOIN___(CC_JOIN_##n, __VA_ARGS__)
#define CC_JOIN___(join, ...) join(__VA_ARGS__)

#define CC_JOIN_0(sep)
#define CC_JOIN_1(sep, x0) x0
#define CC_JOIN_2(sep, x0, x1) x0##sep##x1
#define CC_JOIN_3(sep, x0, x1, x2) x0##sep##x1##sep##x2
#define CC_JOIN_4(sep, x0, x1, x2, x3) x0##sep##x1##sep##x2##sep##x3
#define CC_JOIN_5(sep, x0, x1, x2, x3, x4) x0##sep##x1##sep##x2##sep##x3##sep##x4
#define CC_JOIN_6(sep, x0, x1, x2, x3, x4, x5) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5
#define CC_JOIN_7(sep, x0, x1, x2, x3, x4, x5, x6) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6
#define CC_JOIN_8(sep, x0, x1, x2, x3, x4, x5, x6, x7) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7
#define CC_JOIN_9(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8
#define CC_JOIN_10(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9
#define CC_JOIN_11(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10
#define CC_JOIN_12(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11
#define CC_JOIN_13(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12
#define CC_JOIN_14(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13
#define CC_JOIN_15(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13##sep##x14
#define CC_JOIN_16(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13##sep##x14##sep##x15
#define CC_JOIN_17(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13##sep##x14##sep##x15##sep##x16
#define CC_JOIN_18(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13##sep##x14##sep##x15##sep##x16##sep##x17
#define CC_JOIN_19(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13##sep##x14##sep##x15##sep##x16##sep##x17##sep##x18
#define CC_JOIN_20(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) x0##sep##x1##sep##x2##sep##x3##sep##x4##sep##x5##sep##x6##sep##x7##sep##x8##sep##x9##sep##x10##sep##x11##sep##x12##sep##x13##sep##x14##sep##x15##sep##x16##sep##x17##sep##x18##sep##x19

#define CC_SOFT_JOIN(sep, ...) CC_SOFT_JOIN_(CC_VA_ARG_COUNT(__VA_ARGS__), sep, __VA_ARGS__)
#define CC_SOFT_JOIN_(n, ...) CC_SOFT_JOIN__(n, __VA_ARGS__)
#define CC_SOFT_JOIN__(n, ...) CC_SOFT_JOIN___(CC_SOFT_JOIN_##n, __VA_ARGS__)
#define CC_SOFT_JOIN___(join, ...) join(__VA_ARGS__)

#define CC_SOFT_JOIN_0(sep)
#define CC_SOFT_JOIN_1(sep, x0) x0
#define CC_SOFT_JOIN_2(sep, x0, x1) x0 sep x1
#define CC_SOFT_JOIN_3(sep, x0, x1, x2) x0 sep x1 sep x2
#define CC_SOFT_JOIN_4(sep, x0, x1, x2, x3) x0 sep x1 sep x2 sep x3
#define CC_SOFT_JOIN_5(sep, x0, x1, x2, x3, x4) x0 sep x1 sep x2 sep x3 sep x4
#define CC_SOFT_JOIN_6(sep, x0, x1, x2, x3, x4, x5) x0 sep x1 sep x2 sep x3 sep x4 sep x5
#define CC_SOFT_JOIN_7(sep, x0, x1, x2, x3, x4, x5, x6) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6
#define CC_SOFT_JOIN_8(sep, x0, x1, x2, x3, x4, x5, x6, x7) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7
#define CC_SOFT_JOIN_9(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8
#define CC_SOFT_JOIN_10(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9
#define CC_SOFT_JOIN_11(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10
#define CC_SOFT_JOIN_12(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11
#define CC_SOFT_JOIN_13(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12
#define CC_SOFT_JOIN_14(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13
#define CC_SOFT_JOIN_15(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13 sep x14
#define CC_SOFT_JOIN_16(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13 sep x14 sep x15
#define CC_SOFT_JOIN_17(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13 sep x14 sep x15 sep x16
#define CC_SOFT_JOIN_18(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13 sep x14 sep x15 sep x16 sep x17
#define CC_SOFT_JOIN_19(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13 sep x14 sep x15 sep x16 sep x17 sep x18
#define CC_SOFT_JOIN_20(sep, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) x0 sep x1 sep x2 sep x3 sep x4 sep x5 sep x6 sep x7 sep x8 sep x9 sep x10 sep x11 sep x12 sep x13 sep x14 sep x15 sep x16 sep x17 sep x18 sep x19

#define CC_RECURSIVE_0_MAP(fun, ...) CC_RECURSIVE_0_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_1_MAP(fun, ...) CC_RECURSIVE_1_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_2_MAP(fun, ...) CC_RECURSIVE_2_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_3_MAP(fun, ...) CC_RECURSIVE_3_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_4_MAP(fun, ...) CC_RECURSIVE_4_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_5_MAP(fun, ...) CC_RECURSIVE_5_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_6_MAP(fun, ...) CC_RECURSIVE_6_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_7_MAP(fun, ...) CC_RECURSIVE_7_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_8_MAP(fun, ...) CC_RECURSIVE_8_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_9_MAP(fun, ...) CC_RECURSIVE_9_MAP_(fun, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_0_MAP_(fun, n, ...) CC_RECURSIVE_0_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_1_MAP_(fun, n, ...) CC_RECURSIVE_1_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_2_MAP_(fun, n, ...) CC_RECURSIVE_2_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_3_MAP_(fun, n, ...) CC_RECURSIVE_3_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_4_MAP_(fun, n, ...) CC_RECURSIVE_4_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_5_MAP_(fun, n, ...) CC_RECURSIVE_5_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_6_MAP_(fun, n, ...) CC_RECURSIVE_6_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_7_MAP_(fun, n, ...) CC_RECURSIVE_7_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_8_MAP_(fun, n, ...) CC_RECURSIVE_8_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_9_MAP_(fun, n, ...) CC_RECURSIVE_9_MAP__(fun, n, __VA_ARGS__)
#define CC_RECURSIVE_0_MAP__(fun, n, ...) CC_RECURSIVE_0_MAP___(fun, CC_RECURSIVE_0_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_1_MAP__(fun, n, ...) CC_RECURSIVE_1_MAP___(fun, CC_RECURSIVE_1_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_2_MAP__(fun, n, ...) CC_RECURSIVE_2_MAP___(fun, CC_RECURSIVE_2_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_3_MAP__(fun, n, ...) CC_RECURSIVE_3_MAP___(fun, CC_RECURSIVE_3_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_4_MAP__(fun, n, ...) CC_RECURSIVE_4_MAP___(fun, CC_RECURSIVE_4_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_5_MAP__(fun, n, ...) CC_RECURSIVE_5_MAP___(fun, CC_RECURSIVE_5_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_6_MAP__(fun, n, ...) CC_RECURSIVE_6_MAP___(fun, CC_RECURSIVE_6_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_7_MAP__(fun, n, ...) CC_RECURSIVE_7_MAP___(fun, CC_RECURSIVE_7_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_8_MAP__(fun, n, ...) CC_RECURSIVE_8_MAP___(fun, CC_RECURSIVE_8_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_9_MAP__(fun, n, ...) CC_RECURSIVE_9_MAP___(fun, CC_RECURSIVE_9_MAP_##n, __VA_ARGS__)
#define CC_RECURSIVE_0_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_1_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_2_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_3_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_4_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_5_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_6_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_7_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_8_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)
#define CC_RECURSIVE_9_MAP___(fun, apply, ...) apply(fun, __VA_ARGS__)

#define CC_RECURSIVE_0_MAP_0(fun, ...)
#define CC_RECURSIVE_1_MAP_0(fun, ...)
#define CC_RECURSIVE_2_MAP_0(fun, ...)
#define CC_RECURSIVE_3_MAP_0(fun, ...)
#define CC_RECURSIVE_4_MAP_0(fun, ...)
#define CC_RECURSIVE_5_MAP_0(fun, ...)
#define CC_RECURSIVE_6_MAP_0(fun, ...)
#define CC_RECURSIVE_7_MAP_0(fun, ...)
#define CC_RECURSIVE_8_MAP_0(fun, ...)
#define CC_RECURSIVE_9_MAP_0(fun, ...)
#define CC_RECURSIVE_0_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_1_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_2_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_3_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_4_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_5_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_6_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_7_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_8_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_9_MAP_1(fun, x0) fun(x0, 0)
#define CC_RECURSIVE_0_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_1_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_2_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_3_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_4_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_5_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_6_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_7_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_8_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_9_MAP_2(fun, x0, x1) fun(x0, 0), fun(x1, 1)
#define CC_RECURSIVE_0_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_1_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_2_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_3_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_4_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_5_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_6_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_7_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_8_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_9_MAP_3(fun, x0, x1, x2) fun(x0, 0), fun(x1, 1), fun(x2, 2)
#define CC_RECURSIVE_0_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_1_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_2_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_3_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_4_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_5_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_6_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_7_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_8_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_9_MAP_4(fun, x0, x1, x2, x3) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3)
#define CC_RECURSIVE_0_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_1_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_2_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_3_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_4_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_5_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_6_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_7_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_8_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_9_MAP_5(fun, x0, x1, x2, x3, x4) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4)
#define CC_RECURSIVE_0_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_1_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_2_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_3_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_4_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_5_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_6_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_7_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_8_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_9_MAP_6(fun, x0, x1, x2, x3, x4, x5) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5)
#define CC_RECURSIVE_0_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_1_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_2_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_3_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_4_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_5_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_6_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_7_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_8_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_9_MAP_7(fun, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6)
#define CC_RECURSIVE_0_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_1_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_2_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_3_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_4_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_5_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_6_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_7_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_8_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_9_MAP_8(fun, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7)
#define CC_RECURSIVE_0_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_1_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_2_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_3_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_4_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_5_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_6_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_7_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_8_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_9_MAP_9(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8)
#define CC_RECURSIVE_0_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_1_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_2_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_3_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_4_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_5_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_6_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_7_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_8_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_9_MAP_10(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9)
#define CC_RECURSIVE_0_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_1_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_2_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_3_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_4_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_5_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_6_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_7_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_8_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_9_MAP_11(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10)
#define CC_RECURSIVE_0_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_1_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_2_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_3_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_4_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_5_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_6_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_7_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_8_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_9_MAP_12(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11)
#define CC_RECURSIVE_0_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_1_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_2_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_3_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_4_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_5_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_6_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_7_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_8_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_9_MAP_13(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12)
#define CC_RECURSIVE_0_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_1_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_2_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_3_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_4_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_5_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_6_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_7_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_8_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_9_MAP_14(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13)
#define CC_RECURSIVE_0_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_1_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_2_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_3_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_4_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_5_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_6_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_7_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_8_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_9_MAP_15(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14)
#define CC_RECURSIVE_0_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_1_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_2_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_3_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_4_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_5_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_6_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_7_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_8_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_9_MAP_16(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15)
#define CC_RECURSIVE_0_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_1_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_2_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_3_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_4_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_5_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_6_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_7_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_8_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_9_MAP_17(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16)
#define CC_RECURSIVE_0_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_1_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_2_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_3_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_4_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_5_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_6_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_7_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_8_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_9_MAP_18(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17)
#define CC_RECURSIVE_0_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_1_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_2_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_3_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_4_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_5_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_6_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_7_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_8_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_9_MAP_19(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18)
#define CC_RECURSIVE_0_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_1_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_2_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_3_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_4_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_5_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_6_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_7_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_8_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)
#define CC_RECURSIVE_9_MAP_20(fun, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0), fun(x1, 1), fun(x2, 2), fun(x3, 3), fun(x4, 4), fun(x5, 5), fun(x6, 6), fun(x7, 7), fun(x8, 8), fun(x9, 9), fun(x10, 10), fun(x11, 11), fun(x12, 12), fun(x13, 13), fun(x14, 14), fun(x15, 15), fun(x16, 16), fun(x17, 17), fun(x18, 18), fun(x19, 19)

#define CC_RECURSIVE_0_MAP_WITH(fun, x, ...) CC_RECURSIVE_0_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_1_MAP_WITH(fun, x, ...) CC_RECURSIVE_1_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_2_MAP_WITH(fun, x, ...) CC_RECURSIVE_2_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_3_MAP_WITH(fun, x, ...) CC_RECURSIVE_3_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_4_MAP_WITH(fun, x, ...) CC_RECURSIVE_4_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_5_MAP_WITH(fun, x, ...) CC_RECURSIVE_5_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_6_MAP_WITH(fun, x, ...) CC_RECURSIVE_6_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_7_MAP_WITH(fun, x, ...) CC_RECURSIVE_7_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_8_MAP_WITH(fun, x, ...) CC_RECURSIVE_8_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_9_MAP_WITH(fun, x, ...) CC_RECURSIVE_9_MAP_WITH_(fun, x, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_RECURSIVE_0_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_0_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_1_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_1_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_2_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_2_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_3_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_3_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_4_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_4_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_5_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_5_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_6_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_6_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_7_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_7_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_8_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_8_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_9_MAP_WITH_(fun, x, n, ...) CC_RECURSIVE_9_MAP_WITH__(fun, x, n, __VA_ARGS__)
#define CC_RECURSIVE_0_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_0_MAP_WITH___(fun, x, CC_RECURSIVE_0_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_1_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_1_MAP_WITH___(fun, x, CC_RECURSIVE_1_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_2_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_2_MAP_WITH___(fun, x, CC_RECURSIVE_2_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_3_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_3_MAP_WITH___(fun, x, CC_RECURSIVE_3_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_4_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_4_MAP_WITH___(fun, x, CC_RECURSIVE_4_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_5_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_5_MAP_WITH___(fun, x, CC_RECURSIVE_5_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_6_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_6_MAP_WITH___(fun, x, CC_RECURSIVE_6_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_7_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_7_MAP_WITH___(fun, x, CC_RECURSIVE_7_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_8_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_8_MAP_WITH___(fun, x, CC_RECURSIVE_8_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_9_MAP_WITH__(fun, x, n, ...) CC_RECURSIVE_9_MAP_WITH___(fun, x, CC_RECURSIVE_9_MAP_WITH_##n, __VA_ARGS__)
#define CC_RECURSIVE_0_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_1_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_2_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_3_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_4_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_5_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_6_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_7_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_8_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)
#define CC_RECURSIVE_9_MAP_WITH___(fun, x, apply, ...) apply(fun, x, __VA_ARGS__)

#define CC_RECURSIVE_0_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_1_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_2_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_3_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_4_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_5_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_6_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_7_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_8_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_9_MAP_WITH_0(fun, x, ...)
#define CC_RECURSIVE_0_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_1_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_2_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_3_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_4_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_5_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_6_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_7_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_8_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_9_MAP_WITH_1(fun, x, x0) fun(x0, 0, x)
#define CC_RECURSIVE_0_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_1_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_2_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_3_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_4_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_5_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_6_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_7_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_8_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_9_MAP_WITH_2(fun, x, x0, x1) fun(x0, 0, x), fun(x1, 1, x)
#define CC_RECURSIVE_0_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_1_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_2_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_3_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_4_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_5_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_6_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_7_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_8_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_9_MAP_WITH_3(fun, x, x0, x1, x2) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x)
#define CC_RECURSIVE_0_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_1_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_2_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_3_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_4_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_5_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_6_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_7_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_8_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_9_MAP_WITH_4(fun, x, x0, x1, x2, x3) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x)
#define CC_RECURSIVE_0_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_1_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_2_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_3_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_4_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_5_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_6_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_7_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_8_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_9_MAP_WITH_5(fun, x, x0, x1, x2, x3, x4) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x)
#define CC_RECURSIVE_0_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_1_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_2_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_3_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_4_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_5_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_6_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_7_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_8_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_9_MAP_WITH_6(fun, x, x0, x1, x2, x3, x4, x5) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x)
#define CC_RECURSIVE_0_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_1_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_2_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_3_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_4_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_5_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_6_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_7_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_8_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_9_MAP_WITH_7(fun, x, x0, x1, x2, x3, x4, x5, x6) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x)
#define CC_RECURSIVE_0_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_1_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_2_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_3_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_4_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_5_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_6_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_7_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_8_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_9_MAP_WITH_8(fun, x, x0, x1, x2, x3, x4, x5, x6, x7) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x)
#define CC_RECURSIVE_0_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_1_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_2_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_3_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_4_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_5_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_6_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_7_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_8_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_9_MAP_WITH_9(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x)
#define CC_RECURSIVE_0_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_1_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_2_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_3_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_4_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_5_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_6_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_7_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_8_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_9_MAP_WITH_10(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x)
#define CC_RECURSIVE_0_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_1_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_2_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_3_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_4_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_5_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_6_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_7_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_8_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_9_MAP_WITH_11(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x)
#define CC_RECURSIVE_0_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_1_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_2_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_3_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_4_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_5_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_6_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_7_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_8_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_9_MAP_WITH_12(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x)
#define CC_RECURSIVE_0_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_1_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_2_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_3_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_4_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_5_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_6_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_7_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_8_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_9_MAP_WITH_13(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x)
#define CC_RECURSIVE_0_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_1_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_2_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_3_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_4_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_5_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_6_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_7_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_8_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_9_MAP_WITH_14(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x)
#define CC_RECURSIVE_0_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_1_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_2_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_3_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_4_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_5_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_6_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_7_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_8_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_9_MAP_WITH_15(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x)
#define CC_RECURSIVE_0_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_1_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_2_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_3_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_4_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_5_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_6_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_7_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_8_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_9_MAP_WITH_16(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x)
#define CC_RECURSIVE_0_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_1_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_2_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_3_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_4_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_5_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_6_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_7_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_8_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_9_MAP_WITH_17(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x)
#define CC_RECURSIVE_0_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_1_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_2_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_3_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_4_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_5_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_6_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_7_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_8_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_9_MAP_WITH_18(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x)
#define CC_RECURSIVE_0_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_1_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_2_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_3_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_4_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_5_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_6_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_7_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_8_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_9_MAP_WITH_19(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x)
#define CC_RECURSIVE_0_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_1_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_2_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_3_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_4_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_5_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_6_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_7_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_8_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)
#define CC_RECURSIVE_9_MAP_WITH_20(fun, x, x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) fun(x0, 0, x), fun(x1, 1, x), fun(x2, 2, x), fun(x3, 3, x), fun(x4, 4, x), fun(x5, 5, x), fun(x6, 6, x), fun(x7, 7, x), fun(x8, 8, x), fun(x9, 9, x), fun(x10, 10, x), fun(x11, 11, x), fun(x12, 12, x), fun(x13, 13, x), fun(x14, 14, x), fun(x15, 15, x), fun(x16, 16, x), fun(x17, 17, x), fun(x18, 18, x), fun(x19, 19, x)

#define CC_VA_ARG_LAST(...) CC_VA_ARG_LAST_(CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_VA_ARG_LAST_(n, ...) CC_VA_ARG_LAST__(n, __VA_ARGS__)
#define CC_VA_ARG_LAST__(n, ...) CC_VA_ARG_LAST___(CC_VA_ARG_LAST_##n, __VA_ARGS__)
#define CC_VA_ARG_LAST___(last, ...) last(__VA_ARGS__)

#define CC_VA_ARG_LAST_0()
#define CC_VA_ARG_LAST_1(x0) x0
#define CC_VA_ARG_LAST_2(x0, x1) x1
#define CC_VA_ARG_LAST_3(x0, x1, x2) x2
#define CC_VA_ARG_LAST_4(x0, x1, x2, x3) x3
#define CC_VA_ARG_LAST_5(x0, x1, x2, x3, x4) x4
#define CC_VA_ARG_LAST_6(x0, x1, x2, x3, x4, x5) x5
#define CC_VA_ARG_LAST_7(x0, x1, x2, x3, x4, x5, x6) x6
#define CC_VA_ARG_LAST_8(x0, x1, x2, x3, x4, x5, x6, x7) x7
#define CC_VA_ARG_LAST_9(x0, x1, x2, x3, x4, x5, x6, x7, x8) x8
#define CC_VA_ARG_LAST_10(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9) x9
#define CC_VA_ARG_LAST_11(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) x10
#define CC_VA_ARG_LAST_12(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11) x11
#define CC_VA_ARG_LAST_13(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12) x12
#define CC_VA_ARG_LAST_14(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13) x13
#define CC_VA_ARG_LAST_15(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14) x14
#define CC_VA_ARG_LAST_16(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15) x15
#define CC_VA_ARG_LAST_17(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16) x16
#define CC_VA_ARG_LAST_18(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17) x17
#define CC_VA_ARG_LAST_19(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18) x18
#define CC_VA_ARG_LAST_20(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19) x19

#define CC_EXPAND(...) __VA_ARGS__

#pragma mark - Unique Sort

//TODO: Add more compiler friendly unique sort when constexpr is added in C23
#ifndef CC_UNIQUE_SORT_MAX
#define CC_UNIQUE_SORT_MAX 3
#endif

#ifndef CC_UNIQUE_SORT_MAX_SET_OF_64
#define CC_UNIQUE_SORT_MAX_SET_OF_64 2
#endif

#define CC_UNIQUE_SORT(...) CC_UNIQUE_SORT_(CC_VA_ARG_COUNT(__VA_ARGS__), CC_UNIQUE_SORT_MAX_SET_OF_64, __VA_ARGS__)
#define CC_UNIQUE_SORT_(max, range, ...) CC_UNIQUE_SORT__(max, CC_MAP_WITH(CC_UNIQUE_SORT_SETS, (__VA_ARGS__), CC_REPEAT(0, range, CC_UNIQUE_SORT_SET_SIZE)))
#define CC_UNIQUE_SORT__(...) CC_UNIQUE_SORT___(__VA_ARGS__)
#define CC_UNIQUE_SORT___(max, ...) CC_REPEAT(0, max, CC_UNIQUE_SORT_SORTER, (__VA_ARGS__))

#define CC_UNIQUE_SORT_SORTER(args, n) CC_UNIQUE_SORT_SORTER_(n, CC_EXPAND args)
#define CC_UNIQUE_SORT_SORTER_(...) CC_UNIQUE_SORT_SORTER__(__VA_ARGS__)
#define CC_UNIQUE_SORT_SORTER__(n, ...) CC_SOFT_JOIN(|, CC_MAP_WITH(CC_UNIQUE_SORT_GET, (n, (CC_MAP(CC_UNIQUE_SORT_BIT_COUNT_, __VA_ARGS__))), __VA_ARGS__))

#define CC_UNIQUE_SORT_BIT_COUNT_(x, _) CC_UNIQUE_SORT_BIT_COUNT__ x
#define CC_UNIQUE_SORT_BIT_COUNT__(x, _, b) CC_UNIQUE_SORT_BIT_COUNT(b)

#define CC_UNIQUE_SORT_SET_SIZE(_, n) (64 * (n))

#define CC_UNIQUE_SORT_SETS(n, i, args) CC_UNIQUE_SORT_SETS_(n, i, CC_EXPAND args)
#define CC_UNIQUE_SORT_SETS_(n, i, ...) CC_UNIQUE_SORT_SETS__(n, i,  __VA_ARGS__)
#define CC_UNIQUE_SORT_SETS__(n, i, ...) (n, i, CC_MERGE_MAP_WITH(CC_UNIQUE_SORT_SET_COMBINE, n, __VA_ARGS__) 0)

#define CC_UNIQUE_SORT_SET_COMBINE(x, _, off) CC_UNIQUE_SORT_SET_BIT(x, _, off) |

#define CC_UNIQUE_SORT_SET_BIT(x, _, off) (((x) - (off)) > 63 ? 0 : (((x) < (off) ? 0ULL : 1ULL) << (((x) < (off) ? 0 : ((x) - (off))) & 63)))

#define CC_UNIQUE_SORT_BIT_COUNT(x) ((((((((x) - (((x) >> 1) & 0x5555555555555555)) & 0x3333333333333333) + ((((x) - (((x) >> 1) & 0x5555555555555555)) >> 2) & 0x3333333333333333)) + (((((x) - (((x) >> 1) & 0x5555555555555555)) & 0x3333333333333333) + ((((x) - (((x) >> 1) & 0x5555555555555555)) >> 2) & 0x3333333333333333)) >> 4)) & 0x0f0f0f0f0f0f0f0f) * 0x0101010101010101) >> 56)

#define CC_UNIQUE_SORT_BIT_INDEX(x) ((((x) & 0xAAAAAAAAAAAAAAAA) ?  1 : 0) | (((x) & 0xCCCCCCCCCCCCCCCC) ?  2 : 0) | (((x) & 0xF0F0F0F0F0F0F0F0) ?  4 : 0) | (((x) & 0xFF00FF00FF00FF00) ?  8 : 0) | (((x) & 0xFFFF0000FFFF0000) ?  16 : 0) | (((x) & 0xFFFFFFFF00000000) ?  32 : 0))

#define CC_UNIQUE_SORT_LOW_SET(x)  ((x) & -(x))

#define CC_UNIQUE_SORT_MASK_LOWER_2(x) ((x)? ~-(x) : 0)

#define CC_UNIQUE_SORT_MASK(x) CC_UNIQUE_SORT_MASK_LOWER_2(x << 1)

#define CC_UNIQUE_SORT_MASK_0(set) CC_UNIQUE_SORT_LOW_SET(set)
#define CC_UNIQUE_SORT_MASK_1(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_0(set)))
#define CC_UNIQUE_SORT_MASK_2(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_1(set)))
#define CC_UNIQUE_SORT_MASK_3(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_2(set)))
#define CC_UNIQUE_SORT_MASK_4(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_3(set)))
#define CC_UNIQUE_SORT_MASK_5(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_4(set)))
#define CC_UNIQUE_SORT_MASK_6(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_5(set)))
#define CC_UNIQUE_SORT_MASK_7(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_6(set)))
#define CC_UNIQUE_SORT_MASK_8(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_7(set)))
#define CC_UNIQUE_SORT_MASK_9(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_8(set)))
#define CC_UNIQUE_SORT_MASK_10(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_9(set)))
#define CC_UNIQUE_SORT_MASK_11(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_10(set)))
#define CC_UNIQUE_SORT_MASK_12(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_11(set)))
#define CC_UNIQUE_SORT_MASK_13(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_12(set)))
#define CC_UNIQUE_SORT_MASK_14(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_13(set)))
#define CC_UNIQUE_SORT_MASK_15(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_14(set)))
#define CC_UNIQUE_SORT_MASK_16(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_15(set)))
#define CC_UNIQUE_SORT_MASK_17(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_16(set)))
#define CC_UNIQUE_SORT_MASK_18(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_17(set)))
#define CC_UNIQUE_SORT_MASK_19(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_18(set)))
#define CC_UNIQUE_SORT_MASK_20(set) CC_UNIQUE_SORT_LOW_SET((set) & ~CC_UNIQUE_SORT_MASK(CC_UNIQUE_SORT_MASK_19(set)))

#define CC_UNIQUE_SORT_SUM(n, c) CC_UNIQUE_SORT_SUM_(CC_UNIQUE_SORT_SUM_##n, CC_EXPAND c)
#define CC_UNIQUE_SORT_SUM_(sum, ...) CC_UNIQUE_SORT_SUM__(sum, __VA_ARGS__)
#define CC_UNIQUE_SORT_SUM__(sum, ...) sum(__VA_ARGS__)

#define CC_UNIQUE_SORT_SUM_0(x0, ...) (0, (x0))
#define CC_UNIQUE_SORT_SUM_1(x0, x1, ...) ((x0), ((x0) + (x1)))
#define CC_UNIQUE_SORT_SUM_2(x0, x1, x2, ...) (((x0) + (x1)), ((x0) + (x1) + (x2)))
#define CC_UNIQUE_SORT_SUM_3(x0, x1, x2, x3, ...) (((x0) + (x1) + (x2)), ((x0) + (x1) + (x2) + (x3)))
#define CC_UNIQUE_SORT_SUM_4(x0, x1, x2, x3, x4, ...) (((x0) + (x1) + (x2) + (x3)), ((x0) + (x1) + (x2) + (x3) + (x4)))
#define CC_UNIQUE_SORT_SUM_5(x0, x1, x2, x3, x4, x5, ...) (((x0) + (x1) + (x2) + (x3) + (x4)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5)))
#define CC_UNIQUE_SORT_SUM_6(x0, x1, x2, x3, x4, x5, x6, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6)))
#define CC_UNIQUE_SORT_SUM_7(x0, x1, x2, x3, x4, x5, x6, x7, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7)))
#define CC_UNIQUE_SORT_SUM_8(x0, x1, x2, x3, x4, x5, x6, x7, x8, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8)))
#define CC_UNIQUE_SORT_SUM_9(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9)))
#define CC_UNIQUE_SORT_SUM_10(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10)))
#define CC_UNIQUE_SORT_SUM_11(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11)))
#define CC_UNIQUE_SORT_SUM_12(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12)))
#define CC_UNIQUE_SORT_SUM_13(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13)))
#define CC_UNIQUE_SORT_SUM_14(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14)))
#define CC_UNIQUE_SORT_SUM_15(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15)))
#define CC_UNIQUE_SORT_SUM_16(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16)))
#define CC_UNIQUE_SORT_SUM_17(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17)))
#define CC_UNIQUE_SORT_SUM_18(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17) + (x18)))
#define CC_UNIQUE_SORT_SUM_19(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17) + (x18)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17) + (x18) + (x19)))
#define CC_UNIQUE_SORT_SUM_20(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, ...) (((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17) + (x18) + (x19)), ((x0) + (x1) + (x2) + (x3) + (x4) + (x5) + (x6) + (x7) + (x8) + (x9) + (x10) + (x11) + (x12) + (x13) + (x14) + (x15) + (x16) + (x17) + (x18) + (x19) + (x20)))

#define CC_UNIQUE_SORT_GET(set, _, args) CC_UNIQUE_SORT_GET_(CC_EXPAND args, CC_EXPAND set)
#define CC_UNIQUE_SORT_GET_(...) CC_UNIQUE_SORT_GET__(__VA_ARGS__)
#define CC_UNIQUE_SORT_GET__(i, c, n, si, set) CC_UNIQUE_SORT_GET___(i, n, si, set, CC_UNIQUE_SORT_SUM(si, c))
#define CC_UNIQUE_SORT_GET___(i, n, si, set, sum) CC_UNIQUE_SORT_GET____(i, n, si, set, CC_EXPAND sum)
#define CC_UNIQUE_SORT_GET____(...) CC_UNIQUE_SORT_GET_____(__VA_ARGS__)
#define CC_UNIQUE_SORT_GET_____(i, n, si, set, min, max) ((((i) >= (min)) && ((i) < (max))) ? (CC_UNIQUE_SORT_GET_n(set, (i) - (min)) + (n)) : 0)

#define CC_UNIQUE_SORT_GET_n(set, n) CC_UNIQUE_SORT_GET_n_(CC_UNIQUE_SORT_MAX, set, n)
#define CC_UNIQUE_SORT_GET_n_(max, set, n) CC_UNIQUE_SORT_GET_n__(max, set, n)
#define CC_UNIQUE_SORT_GET_n__(max, set, n) CC_UNIQUE_SORT_GET_##max(set, n)

#define CC_UNIQUE_SORT_GET_0(set, n) ((n) == 0 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_0(set)) : 0)
#define CC_UNIQUE_SORT_GET_1(set, n) ((n) == 1 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_1(set)) : CC_UNIQUE_SORT_GET_0(set, n))
#define CC_UNIQUE_SORT_GET_2(set, n) ((n) == 2 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_2(set)) : CC_UNIQUE_SORT_GET_1(set, n))
#define CC_UNIQUE_SORT_GET_3(set, n) ((n) == 3 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_3(set)) : CC_UNIQUE_SORT_GET_2(set, n))
#define CC_UNIQUE_SORT_GET_4(set, n) ((n) == 4 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_4(set)) : CC_UNIQUE_SORT_GET_3(set, n))
#define CC_UNIQUE_SORT_GET_5(set, n) ((n) == 5 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_5(set)) : CC_UNIQUE_SORT_GET_4(set, n))
#define CC_UNIQUE_SORT_GET_6(set, n) ((n) == 6 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_6(set)) : CC_UNIQUE_SORT_GET_5(set, n))
#define CC_UNIQUE_SORT_GET_7(set, n) ((n) == 7 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_7(set)) : CC_UNIQUE_SORT_GET_6(set, n))
#define CC_UNIQUE_SORT_GET_8(set, n) ((n) == 8 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_8(set)) : CC_UNIQUE_SORT_GET_7(set, n))
#define CC_UNIQUE_SORT_GET_9(set, n) ((n) == 9 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_9(set)) : CC_UNIQUE_SORT_GET_8(set, n))
#define CC_UNIQUE_SORT_GET_10(set, n) ((n) == 10 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_10(set)) : CC_UNIQUE_SORT_GET_9(set, n))
#define CC_UNIQUE_SORT_GET_11(set, n) ((n) == 11 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_11(set)) : CC_UNIQUE_SORT_GET_10(set, n))
#define CC_UNIQUE_SORT_GET_12(set, n) ((n) == 12 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_12(set)) : CC_UNIQUE_SORT_GET_11(set, n))
#define CC_UNIQUE_SORT_GET_13(set, n) ((n) == 13 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_13(set)) : CC_UNIQUE_SORT_GET_12(set, n))
#define CC_UNIQUE_SORT_GET_14(set, n) ((n) == 14 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_14(set)) : CC_UNIQUE_SORT_GET_13(set, n))
#define CC_UNIQUE_SORT_GET_15(set, n) ((n) == 15 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_15(set)) : CC_UNIQUE_SORT_GET_14(set, n))
#define CC_UNIQUE_SORT_GET_16(set, n) ((n) == 16 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_16(set)) : CC_UNIQUE_SORT_GET_15(set, n))
#define CC_UNIQUE_SORT_GET_17(set, n) ((n) == 17 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_17(set)) : CC_UNIQUE_SORT_GET_16(set, n))
#define CC_UNIQUE_SORT_GET_18(set, n) ((n) == 18 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_18(set)) : CC_UNIQUE_SORT_GET_17(set, n))
#define CC_UNIQUE_SORT_GET_19(set, n) ((n) == 19 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_19(set)) : CC_UNIQUE_SORT_GET_18(set, n))
#define CC_UNIQUE_SORT_GET_20(set, n) ((n) == 20 ? CC_UNIQUE_SORT_BIT_INDEX(CC_UNIQUE_SORT_MASK_20(set)) : CC_UNIQUE_SORT_GET_19(set, n))

#endif
