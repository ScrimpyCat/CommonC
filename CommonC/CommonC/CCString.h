/*
 *  Copyright (c) 2016, Stefan Johnson
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

#ifndef CommonC_CCString_h
#define CommonC_CCString_h

#include <stdint.h>
#include <CommonC/Allocator.h>
#include <CommonC/Enumerator.h>
#include <CommonC/Platform.h>

#if CC_HARDWARE_PTR_64

#if CC_HARDWARE_ENDIAN_BIG
#define CC_STRING_HEADER "\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define CC_STRING_HEADER_CCStringEncodingASCII CC_STRING_HEADER
#define CC_STRING_HEADER_CCStringEncodingUTF8 "\x80\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#elif CC_HARDWARE_ENDIAN_LITTLE
#define CC_STRING_HEADER "\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define CC_STRING_HEADER_CCStringEncodingASCII CC_STRING_HEADER
#define CC_STRING_HEADER_CCStringEncodingUTF8 "\x01\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#else
#error Unknown endianness
#endif

#elif CC_HARDWARE_PTR_32

#if CC_HARDWARE_ENDIAN_BIG
#define CC_STRING_HEADER "\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define CC_STRING_HEADER_CCStringEncodingASCII CC_STRING_HEADER
#define CC_STRING_HEADER_CCStringEncodingUTF8 "\x80\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#elif
#define CC_STRING_HEADER "\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define CC_STRING_HEADER_CCStringEncodingASCII CC_STRING_HEADER
#define CC_STRING_HEADER_CCStringEncodingUTF8 "\x01\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#endif

#else
#error Unknown pointer size
#endif

#define CC_STRING(string) CC_STRING_ENCODING(CCStringEncodingUTF8, string)
#define CC_STRING_ENCODING(encoding, string) (CCString)((char[]){ CC_STRING_HEADER_##encoding string })

typedef uintptr_t CCString;

typedef uint32_t CCChar;

typedef enum {
    CCStringEncodingASCII,
    CCStringEncodingUTF8
} CCStringEncoding;

typedef enum {
    CCStringMapSet127 = 1,
    CCStringMapSet63,
    CCStringMapSet31
} CCStringMapSet;

typedef enum {
    CCStringHintEncodingMask = 1,
    CCStringHintFree = (1 << 1),
    CCStringHintCopy = (1 << 2) | CCStringHintFree
} CCStringHint;

typedef enum {
    ///Set the enumerator to the head end of the string and return the character there.
    CCStringEnumeratorActionHead,
    ///Set the enumerator to the tail end of the string and return the character there.
    CCStringEnumeratorActionTail,
    ///Set the enumerator to the next position in the string, and return the character there.
    CCStringEnumeratorActionNext,
    ///Set the enumerator to the previous position in the string, and return the character there.
    CCStringEnumeratorActionPrevious,
    ///Return the character at the current position.
    CCStringEnumeratorActionCurrent
} CCStringEnumeratorAction;

typedef CCChar CCStringMap;

void CCStringRegisterMap(CCStringEncoding Encoding, const CCStringMap *Map, CCStringMapSet Set);
CCString CCStringCreate(CCAllocatorType Allocator, CCStringHint Hint, const char *String);
void CCStringDestroy(CCString String);
CCStringEncoding CCStringGetEncoding(CCString String);
size_t CCStringGetSize(CCString String);
size_t CCStringGetLength(CCString String);
uint32_t CCStringGetHash(CCString String);
CCChar CCStringGetCharacterAtIndex(CCString String, size_t Index);
_Bool CCStringEqual(CCString String1, CCString String2);
void CCStringGetEnumerator(CCString String, CCEnumerator *Enumerator);
CCChar CCStringEnumerator(CCString String, CCEnumeratorState *Enumerator, CCStringEnumeratorAction Action);

#endif
