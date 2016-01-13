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

#include "CCString.h"
#include "MemoryAllocation.h"
#include "Logging.h"
#include "Assertion.h"
#include <string.h>
#include <wchar.h>
#include "CCStringEnumerator.h"

typedef struct {
    CCStringHint hint;
    uint32_t hash;
    size_t size;
    size_t length;
    char *string;
    char characters[];
} CCStringInfo;

_Static_assert(sizeof(CCStringInfo) == (sizeof(CC_STRING_HEADER) + sizeof(CCStringHint) - 1), "Need to update CC_STRING padding");
_Static_assert(sizeof(CCStringInfo) == (sizeof(CC_STRING_HEADER_CCStringEncodingASCII) - 1), "Need to update CC_STRING padding");
_Static_assert(sizeof(CCStringInfo) == (sizeof(CC_STRING_HEADER_CCStringEncodingUTF8) - 1), "Need to update CC_STRING padding");
_Static_assert(offsetof(CCStringInfo, hint) == 0, "Need to update CC_STRING padding");

enum {
    CCStringMarkConstant = 0x80000000,
    CCStringMarkHash = 0x40000000,
    CCStringMarkSize = 0x20000000,
    CCStringMarkLength = 0x10000000,
};

enum {
    CCStringTaggedMask = 3
};

static size_t CCStringGetLengthUTF8(const char *String);
static CCChar CCStringGetCharacterUTF8(const char *String, size_t *Size);
static size_t CCStringGetPreviousCodepointUTF8(const char *String, size_t Index);

static CC_FORCE_INLINE _Bool CCStringIsTagged(CCString String)
{
    return String & CCStringTaggedMask;
}

static CC_FORCE_INLINE char *CCStringGetCharacters(CCStringInfo *String)
{
    return String->string ? String->string : String->characters;
}

static CCStringMap Map127[127] = { //ASCII set, missing DEL character
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126
};

static CCStringMap Map63[63] = { //ASCII set 0, [-+/*() !=<>.], [a-z], [A-G], I, [N-P], [R-T]
    0,
    '-', '+', '/', '*', '(', ')', ' ', '!', '=', '<', '>', '.',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'I', 'N', 'O', 'P', 'R', 'S', 'T'
};

static CCStringMap Map31[31] = { //ASCII set 0, -, !, `, &, [a-z]
    0,
    '-', '!', '`', '&',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

static struct {
    CCStringEncoding encoding;
    const CCStringMap *map;
} Maps[3] = {
    { CCStringEncodingASCII, Map127 },
    { CCStringEncodingASCII, Map63 },
    { CCStringEncodingASCII, Map31 }
};

void CCStringRegisterMap(CCStringEncoding Encoding, const CCStringMap *Map, CCStringMapSet Set)
{
    Set--;
    
    if (Map)
    {
        Maps[Set].map = Map;
        Maps[Set].encoding = Encoding;
    }
    
    else
    {
        Maps[Set].map = (const CCStringMap*[3]){ Map127, Map63, Map31 }[Set];
        Maps[Set].encoding = CCStringEncodingASCII;
    }
}

static _Bool CCStringCharacterInMap(CCChar Character, const CCStringMap *Map, size_t MapSize, size_t *Index)
{
    //TODO: Could easily be vectorized or pre-compute the ranges and so just check those
    for (size_t Loop = 0; Loop < MapSize; Loop++)
    {
        if (Map[Loop] == Character)
        {
            *Index = Loop;
            return TRUE;
        }
    }
    
    return FALSE;
}

static inline const CCStringMap *CCStringTaggedMap(CCStringMapSet Set)
{
    return Maps[Set - 1].map;
}

static inline size_t CCStringTaggedBitSize(CCStringMapSet Set)
{
    return 8 - Set;
}

static inline size_t CCStringTaggedMapSize(CCStringMapSet Set)
{
    return (size_t[3]){ 127, 63, 31 }[Set - 1];
}

static CCString CCStringCreateTaggedFromMapSet(CCStringMapSet Set, const char *String, size_t Length, CCStringEncoding Encoding)
{
    CCString Map = Set;
    const CCStringMap *Lookup = CCStringTaggedMap(Set);
    const size_t Bits = CCStringTaggedBitSize(Set);
    const size_t MapSize = CCStringTaggedMapSize(Set);
    
    if (Encoding == CCStringEncodingASCII)
    {
        for (size_t Loop = 0; Loop < Length; Loop++)
        {
            size_t Index;
            if (CCStringCharacterInMap(String[Loop], Lookup, MapSize, &Index))
            {
                Map |= (Index << (Bits * Loop)) << 2;
            }
            
            else
            {
                Map = 0;
                break;
            }
        }
    }
    
    else if (Encoding == CCStringEncodingUTF8)
    {
        for (size_t Loop = 0, Count = 0; Loop < Length; )
        {
            size_t Size;
            CCChar c = CCStringGetCharacterUTF8(String + Loop, &Size);
            
            size_t Index;
            if ((Count <= (sizeof(CCString) * 8) / Bits) && (CCStringCharacterInMap(c, Lookup, MapSize, &Index)))
            {
                Map |= (Index << (Bits * Count++)) << 2;
                Loop += Size;
            }
            
            else
            {
                Map = 0;
                break;
            }
        }
    }
    
    return Map;
}

static inline size_t CCStringTaggedCharacterMax(CCStringMapSet Set)
{
#if CC_HARDWARE_PTR_64
    static const size_t MaxSize[3] = { 8, 10, 12 };
#elif CC_HARDWARE_PTR_32
    static const size_t MaxSize[3] = { 4, 5, 6 };
#else
#error Unknown pointer size
#endif
    
    return MaxSize[Set - 1];
}

static CCString CCStringCreateTagged(const char *String, size_t Length, CCStringEncoding Encoding)
{
    const size_t Factor = Encoding == CCStringEncodingUTF8 ? 4 : 1;
    for (int Loop = CCStringMapSet31; Loop > 0; Loop--)
    {
        if (Length <= (CCStringTaggedCharacterMax(Loop) * Factor))
        {
            CCString Map = CCStringCreateTaggedFromMapSet(Loop, String, Length, Encoding);
            if (Map) return Map;
        }
    }
    
    return 0;
}

CCString CCStringCreate(CCAllocatorType Allocator, CCStringHint Hint, const char *String)
{
    CCAssertLog(String, "String must not be null");
    
#if CC_DEBUG
    //log map of current character usage
#endif
    
    const size_t Size = strlen(String);
    
    CCString TaggedStr = CCStringCreateTagged(String, Size, Hint & CCStringHintEncodingMask);
    if (TaggedStr) return TaggedStr;
    
    
    CCStringInfo *Str = CCMalloc(CC_ALIGNED_ALLOCATOR(2)/*Allocator*/, sizeof(CCStringInfo) + (Hint & CCStringHintCopy ? Size + 1 : 0), NULL, CC_DEFAULT_ERROR_CALLBACK); //TODO: Allow aligned allocator to use a specified allocator
    
    *Str = (CCStringInfo){
        .hint = Hint | CCStringMarkSize,
        .hash = 0,
        .size = Size,
        .length = 0,
        .string = NULL
    };
    
    if ((Hint & CCStringHintEncodingMask) == CCStringEncodingASCII)
    {
        Str->hint |= CCStringMarkLength;
        Str->length = Size;
    }
    
    if (Hint & CCStringHintCopy) memcpy(Str->characters, String, Size + 1);
    else Str->string = (char*)String;
    
    return (CCString)Str;
}

void CCStringDestroy(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (!CCStringIsTagged(String))
    {
        if ((((CCStringInfo*)String)->string) && ((CCStringInfo*)String)->hint & CCStringHintFree)
        {
            CC_SAFE_Free(((CCStringInfo*)String)->string);
        }
        
        if (!(((CCStringInfo*)String)->hint & CCStringMarkConstant))
        {
            CCFree((CCStringInfo*)String);
        }
    }
}

CCStringEncoding CCStringGetEncoding(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (CCStringIsTagged(String)) return Maps[(String & CCStringTaggedMask) - 1].encoding;
    else return ((CCStringInfo*)String)->hint & CCStringHintEncodingMask;
}

static inline size_t CCCharSize(CCChar c)
{
    if (c == 0) return 0;
    else if (c < 0x80) return 1;
    else if (c < 0x800) return 2;
    else if (c < 0x10000) return 3;
    
    return 4;
}

size_t CCStringGetSize(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (CCStringIsTagged(String))
    {
        CCStringMapSet Set = String & CCStringTaggedMask;
        String >>= 2;
        
        size_t Size = 0;
        const size_t MapSize = CCStringTaggedMapSize(Set);
        const size_t Bits = CCStringTaggedBitSize(Set);
        const CCStringMap *Map = CCStringTaggedMap(Set);
        for (size_t Loop = 0, Count = CCStringTaggedCharacterMax(Set); Loop < Count; Loop++)
        {
            Size += CCCharSize(Map[(String >> (Bits * Loop)) & MapSize]);
        }
        
        return Size;
    }
    
    else
    {
        if (!(((CCStringInfo*)String)->hint & CCStringMarkSize))
        {
            ((CCStringInfo*)String)->size = strlen(CCStringGetCharacters((CCStringInfo*)String));
            ((CCStringInfo*)String)->hint |= CCStringMarkSize;
        }
        
        return ((CCStringInfo*)String)->size;
    }
}

size_t CCStringGetLength(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (CCStringIsTagged(String))
    {
        CCStringMapSet Set = String & CCStringTaggedMask;
        String >>= 2;
        
        size_t Length = 0;
        const size_t MapSize = CCStringTaggedMapSize(Set);
        const size_t Bits = CCStringTaggedBitSize(Set);
        const CCStringMap *Map = CCStringTaggedMap(Set);
        for (size_t Loop = 0, Count = CCStringTaggedCharacterMax(Set); (Loop < Count) && (CCCharSize(Map[(String >> (Bits * Loop)) & MapSize])); Loop++)
        {
            Length++;
        }
        
        return Length;
    }
    
    else
    {
        if (!(((CCStringInfo*)String)->hint & CCStringMarkLength))
        {
            if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingASCII)
            {
                ((CCStringInfo*)String)->length = CCStringGetSize(String);
                ((CCStringInfo*)String)->hint |= CCStringMarkLength;
            }
            
            else if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingUTF8)
            {
                ((CCStringInfo*)String)->length = CCStringGetLengthUTF8(CCStringGetCharacters((CCStringInfo*)String));
                ((CCStringInfo*)String)->hint |= CCStringMarkLength;
            }
        }
        
        return ((CCStringInfo*)String)->length;
    }
}

uint32_t CCStringGetHash(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    return 0;
}

static inline CCChar CCStringTaggedCharacterAtIndex(CCString String, size_t Index)
{
    const CCStringMapSet Set = String & CCStringTaggedMask;
    const size_t MapSize = CCStringTaggedMapSize(Set);
    const size_t Bits = CCStringTaggedBitSize(Set);
    const CCStringMap *Map = CCStringTaggedMap(Set);
    size_t Max = CCStringTaggedCharacterMax(Set);
    
    return Index < Max ? Map[(String >> (Bits * Index) >> 2) & MapSize] : 0;
}

CCChar CCStringGetCharacterAtIndex(CCString String, size_t Index)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Index < CCStringGetLength(String), "Index must not exceed string length");
    
    if (CCStringIsTagged(String))
    {
        return CCStringTaggedCharacterAtIndex(String, Index);
    }
    
    else
    {
        CCChar c = 0;
        if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingASCII)
        {
            c = CCStringGetCharacters((CCStringInfo*)String)[Index];
        }
        
        else if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingUTF8)
        {
            CCEnumerator Enumerator;
            CCStringGetEnumerator(String, &Enumerator);
            
            c = CCStringEnumeratorGetCurrent(&Enumerator);
            while (Index--) c = CCStringEnumeratorNext(&Enumerator);
        }
        
        return c;
    }
}

_Bool CCStringEqual(CCString String1, CCString String2)
{
    CCAssertLog(String1 && String2, "Strings must not be null");
    
    _Bool Equal = String1 == String2;
    if ((!Equal) &&
        (CCStringGetSize(String1) == CCStringGetSize(String2)) &&
        (CCStringGetLength(String1) == CCStringGetLength(String2)) &&
        (CCStringGetHash(String1) == CCStringGetHash(String2)))
    {
        if ((CCStringIsTagged(String1)) || (CCStringIsTagged(String2)))
        {
        }
        
        else Equal = !strcmp(CCStringGetCharacters((CCStringInfo*)String1), CCStringGetCharacters((CCStringInfo*)String2));
    }
    
    return Equal;
}

void CCStringGetEnumerator(CCString String, CCEnumerator *Enumerator)
{
    CCAssertLog(String, "String must not be null");
    
    if (CCStringIsTagged(String))
    {
        Enumerator->state.type = CCEnumeratorFormatInternal;
    }
    
    else
    {
        if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingASCII)
        {
            Enumerator->state.type = CCEnumeratorFormatBatch;
        }
        
        else if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingUTF8)
        {
            Enumerator->state.type = CCEnumeratorFormatInternal;
        }
    }
    
    Enumerator->ref = (CCStringInfo*)String;
    CCStringEnumerator(String, &Enumerator->state, CCStringEnumeratorActionHead);
}

CCChar CCStringEnumerator(CCString String, CCEnumeratorState *Enumerator, CCStringEnumeratorAction Action)
{
    if (CCStringIsTagged(String))
    {
        switch (Action)
        {
            case CCStringEnumeratorActionHead:
                Enumerator->internal.extra[0] = 0; //index
                Enumerator->internal.extra[1] = CCStringTaggedCharacterAtIndex(String, Enumerator->internal.extra[0]); //current CCChar
                break;
                
            case CCStringEnumeratorActionTail:
                Enumerator->internal.extra[0] = CCStringGetLength(String) - 1; //index
                Enumerator->internal.extra[1] = CCStringTaggedCharacterAtIndex(String, Enumerator->internal.extra[0]); //current CCChar
                break;
                
            case CCStringEnumeratorActionNext:
            {
                if (Enumerator->internal.extra[0] >= (CCStringGetLength(String) - 1))
                {
                    Enumerator->internal.extra[0] = SIZE_MAX;
                    Enumerator->internal.extra[1] = 0;
                    
                    return 0;
                }
                
                Enumerator->internal.extra[1] = CCStringTaggedCharacterAtIndex(String, ++Enumerator->internal.extra[0]); //current CCChar
                break;
            }
                
            case CCStringEnumeratorActionPrevious:
            {
                if (!Enumerator->internal.extra[0])
                {
                    Enumerator->internal.extra[0] = SIZE_MAX;
                    Enumerator->internal.extra[1] = 0;
                    
                    return 0;
                }
                
                Enumerator->internal.extra[1] = CCStringTaggedCharacterAtIndex(String, --Enumerator->internal.extra[0]); //current CCChar
                break;
            }
                
            default:
                break;
        }
        
        return (CCChar)Enumerator->internal.extra[1];
    }
    
    else
    {
        if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingASCII)
        {
            switch (Action)
            {
                case CCStringEnumeratorActionHead:
                    Enumerator->batch.ptr = CCStringGetCharacters((CCStringInfo*)String);
                    Enumerator->batch.index = 0;
                    Enumerator->batch.count = CCStringGetLength(String);
                    Enumerator->batch.stride = 1;
                    break;
                    
                case CCStringEnumeratorActionTail:
                    Enumerator->batch.ptr = CCStringGetCharacters((CCStringInfo*)String);
                    Enumerator->batch.count = CCStringGetLength(String);
                    Enumerator->batch.index = Enumerator->batch.count - 1;
                    Enumerator->batch.stride = 1;
                    break;
                    
                case CCStringEnumeratorActionNext:
                case CCStringEnumeratorActionPrevious:
                    Enumerator->batch.count = 0;
                    Enumerator->batch.index = SIZE_MAX;
                    break;
                    
                default:
                    break;
            }
            
            return *(char*)(Enumerator->batch.ptr + (Enumerator->batch.index * Enumerator->batch.stride));
        }
        
        else if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingUTF8)
        {
            switch (Action)
            {
                case CCStringEnumeratorActionHead:
                {
                    size_t Size = 0;
                    Enumerator->internal.ptr = CCStringGetCharacters((CCStringInfo*)String);
                    Enumerator->internal.extra[0] = 0; //index
                    Enumerator->internal.extra[1] = CCStringGetCharacterUTF8(Enumerator->internal.ptr, &Size); //current CCChar
                    Enumerator->internal.extra[2] = Size; //next codepoint
                    Enumerator->internal.extra[3] = CCStringEnumeratorActionNext;
                    break;
                }
                    
                case CCStringEnumeratorActionTail:
                {
                    size_t Size = 0;
                    Enumerator->internal.ptr = CCStringGetCharacters((CCStringInfo*)String);
                    Enumerator->internal.extra[0] = CCStringGetLength(String) - 1; //index
                    Enumerator->internal.extra[2] = CCStringGetPreviousCodepointUTF8(Enumerator->internal.ptr, CCStringGetSize(String) - 1); //next codepoint
                    Enumerator->internal.extra[1] = CCStringGetCharacterUTF8(Enumerator->internal.ptr + Enumerator->internal.extra[2], &Size); //current CCChar
                    Enumerator->internal.extra[3] = CCStringEnumeratorActionPrevious;
                    break;
                }
                    
                case CCStringEnumeratorActionNext:
                {
                    if (Enumerator->internal.extra[0] >= (CCStringGetLength(String) - 1))
                    {
                        Enumerator->internal.extra[0] = SIZE_MAX;
                        Enumerator->internal.extra[1] = 0;
                        
                        return 0;
                    }
                    
                    if (Enumerator->internal.extra[3] == CCStringEnumeratorActionPrevious)
                    {
                        Enumerator->internal.extra[3] = CCStringEnumeratorActionNext;
                        CCStringEnumerator(String, Enumerator, Action);
                        Enumerator->internal.extra[0]--;
                    }
                    
                    size_t Size = 0;
                    Enumerator->internal.extra[0]++;
                    Enumerator->internal.extra[1] = CCStringGetCharacterUTF8(Enumerator->internal.ptr + Enumerator->internal.extra[2], &Size);
                    Enumerator->internal.extra[2] += Size;
                    break;
                }
                    
                case CCStringEnumeratorActionPrevious:
                {
                    if (!Enumerator->internal.extra[0])
                    {
                        Enumerator->internal.extra[0] = SIZE_MAX;
                        Enumerator->internal.extra[1] = 0;
                        
                        return 0;
                    }
                    
                    if (Enumerator->internal.extra[3] == CCStringEnumeratorActionNext)
                    {
                        Enumerator->internal.extra[3] = CCStringEnumeratorActionPrevious;
                        CCStringEnumerator(String, Enumerator, Action);
                        Enumerator->internal.extra[0]++;
                    }
                    
                    size_t Size = 0;
                    Enumerator->internal.extra[0]--;
                    Enumerator->internal.extra[2] = CCStringGetPreviousCodepointUTF8(Enumerator->internal.ptr, Enumerator->internal.extra[2] - 1);
                    Enumerator->internal.extra[1] = CCStringGetCharacterUTF8(Enumerator->internal.ptr + Enumerator->internal.extra[2], &Size);
                    break;
                }
                    
                default:
                    break;
            }
            
            return (CCChar)Enumerator->internal.extra[1];
        }
    }
    
    return 0;
}

static size_t CCStringGetLengthUTF8(const char *String)
{
    mbstate_t State = {0};
    size_t Length = 0;
    
    while (*String)
    {
        const size_t Len = mbrlen(String, MB_CUR_MAX, &State);
        CCAssertLog((Len != (size_t)-1) || (Len != (size_t)-2), "String must be valid UTF-8");
        
        String += Len;
        Length++;
    }
    
    return Length;
}

//From http://clang.llvm.org/doxygen/ConvertUTF_8c_source.html
#define UNI_SUR_HIGH_START  UINT32_C(0xd800)
#define UNI_SUR_HIGH_END    UINT32_C(0xdbff)
#define UNI_SUR_LOW_START   UINT32_C(0xdc00)
#define UNI_SUR_LOW_END     UINT32_C(0xdfff)

#define UNI_MAX_LEGAL_UTF32 UINT32_C(0x10ffff)

static const char CCStringTrailingBytesUTF8[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

static const uint32_t CCStringOffsetsUTF8[6] = { 0, 0x3080, 0xe2080, 0x03c82080, 0xfa082080, 0x82082080 };

static CCChar CCStringGetCharacterUTF8(const char *String, size_t *Size)
{
    CCChar c = 0;
    int Extra = CCStringTrailingBytesUTF8[(uint8_t)*String];
    
    if (Size) *Size = Extra + 1;
    
    const int Offset = CCStringOffsetsUTF8[Extra];
    for ( ; Extra; Extra--) c = (c + (uint8_t)*String++) << 6;
    c = (c + (uint8_t)*String++) - Offset;
    
    CCAssertLog(c <= UNI_MAX_LEGAL_UTF32, "Character must not exceed valid UTF-32");
    CCAssertLog((c < UNI_SUR_HIGH_START) || (c > UNI_SUR_LOW_END), "Character must not be an UTF-16 surrogate value");
    
    return c; //big-endian UTF-32
}

static size_t CCStringGetPreviousCodepointUTF8(const char *String, size_t Index)
{
    while ((Index) && ((String[Index] & 0xC0) == 0x80)) Index--;
    
    return Index;
}
