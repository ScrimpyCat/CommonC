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

#ifndef CC_CUSTOM_TYPES
#define CC_CUSTOM_TYPES(func, ...)
#endif

#define CC_TYPE_PRESETS(func, ...) \
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

#endif
