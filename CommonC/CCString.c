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

#define CC_QUICK_COMPILE
#include "CCString.h"
#include "MemoryAllocation.h"
#include "Logging.h"
#include "Assertion.h"
#include <string.h>
#include "CCStringEnumerator.h"
#include "BitTricks.h"
#include "CollectionEnumerator.h"
#include "TypeCallbacks.h"

/* 
 CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0 makes the guarantee that a nul char will be represented by 0 in the tagged strings.
 This allows for more efficient checks, if it's not possible to guarantee this, it should be disabled (comment out or
 set to 0).
 */
#ifndef CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0
#define CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0 1
#endif

/*
 CC_STRING_TAGGED_HASH_CACHE allows for the hashes of tagged strings to be cached.
 */
#ifndef CC_STRING_TAGGED_HASH_CACHE
#define CC_STRING_TAGGED_HASH_CACHE 1
#endif

#if CC_STRING_TAGGED_HASH_CACHE
#include "Dictionary.h"

#if defined(__has_include)

#if __has_include(<stdatomic.h>)
#define CC_STRING_USING_STDATOMIC 1
#include <stdatomic.h>
#elif CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#define CC_STRING_USING_OSATOMIC 1
#include <libkern/OSAtomic.h>
#else
#undef CC_STRING_TAGGED_HASH_CACHE
#define CC_STRING_TAGGED_HASH_CACHE 0
#endif

#elif CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#define CC_STRING_USING_OSATOMIC 1
#include <libkern/OSAtomic.h>
#else
#define CC_STRING_USING_STDATOMIC 1
#include <stdatomic.h>
#endif
#endif

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

CC_FLAG_ENUM(uint32_t) {
    CCStringMarkConstant = 0x80000000,
    CCStringMarkHash = 0x40000000,
    CCStringMarkSize = 0x20000000,
    CCStringMarkLength = 0x10000000,
    CCStringMarkUnsafeBuffer = 0x8000000
};

enum {
    CCStringTaggedMask = 3
};

static size_t CCStringGetLengthUTF8(const char *String);
static CCChar CCStringGetCharacterUTF8(const char *String, size_t *Size);
static size_t CCStringGetPreviousCodepointUTF8(const char *String, size_t Index);
static size_t CCStringCopyCharacterUTF8(char *String, CCChar c);

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

static CCStringMap Map31[31] = { //ASCII set 0, -, !, @, &, [a-z]
    0,
    '-', '!', '@', '&',
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
#if CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0
    CCAssertLog(!Map || Map[0] == 0, "CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0 is enabled so maps must use 0 as the first character");
#endif
    
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

const CCStringMap *CCStringGetMap(CCStringMapSet Set, CCStringEncoding *Encoding)
{
    Set--;
    if (Encoding) *Encoding = Maps[Set].encoding;
    
    return Maps[Set].map;
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
    return 127 >> (Set - 1); //127, 63, 31
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
            if ((Count < ((sizeof(CCString) * 8) - 2) / Bits) && (CCStringCharacterInMap(c, Lookup, MapSize, &Index)))
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

static void CCStringDestructor(CCStringInfo *String)
{
    if ((String->string) && (String->hint & CCStringHintFree))
    {
        CC_SAFE_Free(((CCStringInfo*)String)->string);
    }
}

static inline size_t CCCharSize(CCChar c)
{
    if (c == 0) return 0;
    else if (c < 0x80) return 1;
    else if (c < 0x800) return 2;
    else if (c < 0x10000) return 3;
    
    return 4;
}

CCString CCStringCreateWithCharacter(CCAllocatorType Allocator, CCChar Character)
{
    for (int Loop = CCStringMapSet31; Loop > 0; Loop--)
    {
        size_t Index;
        if (CCStringCharacterInMap(Character, CCStringTaggedMap(Loop), CCStringTaggedMapSize(Loop), &Index))
        {
            return Loop | (Index << 2);
        }
    }
    
    size_t Size = CCCharSize(Character);
    CCStringInfo *Str = CCMalloc(CC_ALIGNED_ALLOCATOR(4)/*Allocator*/, sizeof(CCStringInfo) + (Size + 1), NULL, CC_DEFAULT_ERROR_CALLBACK); //TODO: Allow aligned allocator to use a specified allocator
    if (Str)
    {
        CCMemorySetDestructor(Str, (CCMemoryDestructorCallback)CCStringDestructor);
        
        CCStringEncoding Encoding = Size > 1 ? CCStringEncodingUTF8 : CCStringEncodingASCII;
        *Str = (CCStringInfo){
            .hint = Encoding | CCStringMarkSize | CCStringMarkLength,
            .hash = 0,
            .size = Size,
            .length = Size > 0,
            .string = NULL
        };
        
        
        if (Encoding == CCStringEncodingUTF8)
        {
            Str->characters[CCStringCopyCharacterUTF8(Str->characters, Character)] = 0;
        }
        
        else
        {
            Str->characters[0] = Character;
            Str->characters[1] = 0;
        }
    }
    
    else CC_LOG_ERROR("Failed to create string due to allocation failure. Allocation size (%zu)", sizeof(CCStringInfo) + (Size + 1));
    
    return (CCString)Str;
}

static CCString CCStringCreateFromString(CCAllocatorType Allocator, CCStringHint Hint, const char *String, size_t Size, _Bool SameLength)
{
    CCAssertLog(!(Hint & (CCStringMarkHash | CCStringMarkSize | CCStringMarkLength | CCStringMarkUnsafeBuffer)), "Must not use private hints");
    
    CCString TaggedStr = CCStringCreateTagged(String, Size, Hint & CCStringHintEncodingMask);
    if (TaggedStr)
    {
        if ((Hint & CCStringHintCopy) == CCStringHintFree) CCFree((char*)String);
        return TaggedStr;
    }
    
    
    CCStringInfo *Str = CCMalloc(CC_ALIGNED_ALLOCATOR(4)/*Allocator*/, sizeof(CCStringInfo) + ((Hint & CCStringHintCopy) == CCStringHintCopy ? Size + 1 : 0), NULL, CC_DEFAULT_ERROR_CALLBACK); //TODO: Allow aligned allocator to use a specified allocator
    if (Str)
    {
        CCMemorySetDestructor(Str, (CCMemoryDestructorCallback)CCStringDestructor);
        
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
        
        if ((Hint & CCStringHintCopy) == CCStringHintCopy)
        {
            strncpy(Str->characters, String, Size);
            Str->characters[Size] = 0;
        }
        
        else
        {
            Str->string = (char*)String;
            if ((!SameLength) && (Size != strlen(String))) Str->hint |= CCStringMarkUnsafeBuffer;
        }
    }
    
    else CC_LOG_ERROR("Failed to create string due to allocation failure. Allocation size (%zu)", sizeof(CCStringInfo) + ((Hint & CCStringHintCopy) == CCStringHintCopy ? Size + 1 : 0));
    
    return (CCString)Str;
}

CCString CCStringCreate(CCAllocatorType Allocator, CCStringHint Hint, const char *String)
{
    CCAssertLog(String, "String must not be null");
    
    return CCStringCreateFromString(Allocator, Hint, String, strlen(String), TRUE);
}

CCString CCStringCreateWithSize(CCAllocatorType Allocator, CCStringHint Hint, const char *String, size_t Size)
{
    CCAssertLog(String, "String must not be null");
    
    return CCStringCreateFromString(Allocator, Hint, String, Size, FALSE);
}

CCString CCStringCreateByInsertingString(CCString String, size_t Index, CCString Insert)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Insert, "Insert must not be null");
    CCAssertLog(Index <= CCStringGetLength(String), "Index must not be out of bounds + 1");
    
    const size_t StringLength = CCStringGetLength(String), InsertLength = CCStringGetLength(Insert);
    
    if ((CCStringIsTagged(String)) && (CCStringIsTagged(Insert)) && ((String & CCStringTaggedMask) == (Insert & CCStringTaggedMask)))
    {
        const CCStringMapSet Set = String & CCStringTaggedMask;
        if ((StringLength + InsertLength) < CCStringTaggedCharacterMax(Set))
        {
            const size_t Bits = CCStringTaggedBitSize(Set);
            
            String >>= 2;
            
            CCString NewString = Set;
            
            size_t Length = Index;
            if (Length) NewString |= (String & (UINTPTR_MAX >> ((sizeof(CCString) * 8) - (Length * Bits)))) << 2;
            
            NewString |= ((Insert >> 2) << (Length * Bits)) << 2;
            
            Length = StringLength - Index;
            if (Index < StringLength) NewString |= ((String & ((UINTPTR_MAX >> ((sizeof(CCString) * 8) - (Length * Bits))) << (Index * Bits))) << (InsertLength * Bits)) << 2;
            
            return NewString;
        }
    }
    
    char *NewString;
    CC_SAFE_Malloc(NewString, CCStringGetSize(String) + CCStringGetSize(Insert) + 1,
                   CC_LOG_ERROR("Failed to create string due to allocation failure. Allocation size (%zu)", CCStringGetSize(String) + CCStringGetSize(Insert) + 1);
                   return 0;
                   );
    
    char *Buffer = CCStringCopyCharacters(String, 0, Index, NewString);
    Buffer = CCStringCopyCharacters(Insert, 0, InsertLength, Buffer);
    
    if (Index < StringLength) Buffer = CCStringCopyCharacters(String, Index, StringLength - Index, Buffer);
    
    *Buffer = 0;
    
    return CCStringCreate(CC_STD_ALLOCATOR, CCStringHintFree | (CCStringGetEncoding(String) == CCStringEncodingUTF8 ? CCStringEncodingUTF8 : CCStringGetEncoding(Insert)), NewString);
}

CCString CCStringCreateWithoutRange(CCString String, size_t Offset, size_t Length)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Offset + Length <= CCStringGetLength(String), "Offset and size must not be out of bounds");
    
    if (!Length) return CCStringCopy(String);
    
    const size_t StringLength = CCStringGetLength(String);
    if (Offset + Length == StringLength) return CCStringCopySubstring(String, 0, Offset);
    
    if (CCStringIsTagged(String))
    {
        const CCStringMapSet Set = String & CCStringTaggedMask;
        const size_t Bits = CCStringTaggedBitSize(Set);
        
        String >>= 2;
        
        CCString NewString = Set;
        if (Offset) NewString |= (String & ((UINTPTR_MAX >> ((sizeof(CCString) * 8) - (Offset * Bits))))) << 2;
        NewString |= (((String & ((UINTPTR_MAX >> ((sizeof(CCString) * 8) - ((StringLength - (Length + Offset)) * Bits))) << ((Length + Offset) * Bits))) >> (Length * Bits)) << 2);
        
        return NewString;
    }
    
    char *NewString;
    CC_SAFE_Malloc(NewString, (CCStringGetSize(String) - Length) + 1,
                   CC_LOG_ERROR("Failed to create string due to allocation failure. Allocation size (%zu)", (CCStringGetSize(String) - Length) + 1);
                   return 0;
                   );
    
    char *Buffer = CCStringCopyCharacters(String, 0, Offset, NewString);
    
    Buffer = CCStringCopyCharacters(String, Offset + Length, StringLength - (Offset + Length), Buffer);
    
    *Buffer = 0;
    
    return CCStringCreate(CC_STD_ALLOCATOR, CCStringHintFree | CCStringGetEncoding(String), NewString);
}

CCString CCStringCreateByReplacingOccurrencesOfString(CCString String, CCString Occurrence, CCString Replacement)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Occurrence, "Occurrence must not be null");
    
    size_t Index = CCStringFindSubstring(String, 0, Occurrence);
    if (Index == SIZE_MAX) return CCStringCopy(String);
    //TODO: Optimize for non-tagged use case, only need one allocation as it can then mutate that same allocation
    const size_t OccurrenceLength = CCStringGetLength(Occurrence);
    size_t ReplacementLength = 0;
    
    CCString NewString = CCStringCreateWithoutRange(String, Index, OccurrenceLength);
    
    if (Replacement)
    {
        CCString Temp = CCStringCreateByInsertingString(NewString, Index, Replacement);
        CCStringDestroy(NewString);
        NewString = Temp;
        
        ReplacementLength = CCStringGetLength(Replacement);
    }
    
    for (size_t StringLength = CCStringGetLength(NewString); ((Index + ReplacementLength) < StringLength) && ((Index = CCStringFindSubstring(NewString, Index + ReplacementLength, Occurrence)) != SIZE_MAX); StringLength = (StringLength - OccurrenceLength) + ReplacementLength)
    {
        CCString Temp = CCStringCreateWithoutRange(NewString, Index, OccurrenceLength);
        CCStringDestroy(NewString);
        NewString = Temp;
        
        if (Replacement)
        {
            Temp = CCStringCreateByInsertingString(NewString, Index, Replacement);
            CCStringDestroy(NewString);
            NewString = Temp;
        }
    }
    
    return NewString;
}

static size_t CCStringFindClosestSubstring(CCString String, size_t Index, CCString *Substrings, size_t Count, size_t *Found)
{
    size_t SmallestIndex = SIZE_MAX;
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        size_t TempIndex = CCStringFindSubstring(String, Index, Substrings[Loop]);
        if (TempIndex < SmallestIndex)
        {
            SmallestIndex = TempIndex;
            *Found = Loop;
        }
    }
    
    return SmallestIndex;
}

CCString CCStringCreateByReplacingOccurrencesOfGroupedStrings(CCString String, CCString *Occurrences, CCString *Replacements, size_t Count)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Occurrences, "Occurrence must not be null");
    CCAssertLog(Replacements, "Replacements must not be null");
    
    size_t Found;
    size_t Index = CCStringFindClosestSubstring(String, 0, Occurrences, Count, &Found);
    if (Index == SIZE_MAX) return CCStringCopy(String);
    //TODO: Optimize for non-tagged use case, only need one allocation as it can then mutate that same allocation
    size_t ReplacementLength = 0;
    
    CCString NewString = CCStringCreateWithoutRange(String, Index, CCStringGetLength(Occurrences[Found]));
    
    if (Replacements[Found])
    {
        CCString Temp = CCStringCreateByInsertingString(NewString, Index, Replacements[Found]);
        CCStringDestroy(NewString);
        NewString = Temp;
        
        ReplacementLength = CCStringGetLength(Replacements[Found]);
    }
    
    for (size_t StringLength = CCStringGetLength(NewString); ((Index + ReplacementLength) < StringLength) && ((Index = CCStringFindClosestSubstring(NewString, Index + ReplacementLength, Occurrences, Count, &Found)) != SIZE_MAX); StringLength = CCStringGetLength(NewString))
    {
        CCString Temp = CCStringCreateWithoutRange(NewString, Index, CCStringGetLength(Occurrences[Found]));
        CCStringDestroy(NewString);
        NewString = Temp;
        
        if (Replacements[Found])
        {
            Temp = CCStringCreateByInsertingString(NewString, Index, Replacements[Found]);
            CCStringDestroy(NewString);
            NewString = Temp;
            
            ReplacementLength = CCStringGetLength(Replacements[Found]);
        }
        
        else ReplacementLength = 0;
    }
    
    return NewString;
}

static size_t CCStringFindClosestSubstringFromCollection(CCString String, size_t Index, CCOrderedCollection Substrings, CCCollectionEntry *Found)
{
    size_t SmallestIndex = SIZE_MAX;
    CC_COLLECTION_FOREACH(CCString, Substring, Substrings)
    {
        size_t TempIndex = CCStringFindSubstring(String, Index, Substring);
        if (TempIndex < SmallestIndex)
        {
            SmallestIndex = TempIndex;
            *Found = CCCollectionEnumeratorGetEntry(&CC_COLLECTION_CURRENT_ENUMERATOR);
        }
    }
    
    return SmallestIndex;
}

CCString CCStringCreateByReplacingOccurrencesOfGroupedEntries(CCString String, CCOrderedCollection Occurrences, CCOrderedCollection Replacements)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Occurrences, "Occurrence must not be null");
    CCAssertLog(Replacements, "Replacements must not be null");
    CCAssertLog(CCCollectionGetCount(Occurrences) == CCCollectionGetCount(Replacements), "Occurrences and replacements must be the same size");
    
    CCCollectionEntry Found;
    size_t Index = CCStringFindClosestSubstringFromCollection(String, 0, Occurrences, &Found);
    if (Index == SIZE_MAX) return CCStringCopy(String);
    //TODO: Optimize for non-tagged use case, only need one allocation as it can then mutate that same allocation
    size_t ReplacementLength = 0;
    
    CCString NewString = CCStringCreateWithoutRange(String, Index, CCStringGetLength(*(CCString*)CCCollectionGetElement(Occurrences, Found)));
    
    CCString Replacement = *(CCString*)CCOrderedCollectionGetElementAtIndex(Replacements, CCOrderedCollectionGetIndex(Occurrences, Found));
    if (Replacement)
    {
        CCString Temp = CCStringCreateByInsertingString(NewString, Index, Replacement);
        CCStringDestroy(NewString);
        NewString = Temp;
        
        ReplacementLength = CCStringGetLength(Replacement);
    }
    
    for (size_t StringLength = CCStringGetLength(NewString); ((Index + ReplacementLength) < StringLength) && ((Index = CCStringFindClosestSubstringFromCollection(NewString, Index + ReplacementLength, Occurrences, &Found)) != SIZE_MAX); StringLength = CCStringGetLength(NewString))
    {
        CCString Temp = CCStringCreateWithoutRange(NewString, Index, CCStringGetLength(*(CCString*)CCCollectionGetElement(Occurrences, Found)));
        CCStringDestroy(NewString);
        NewString = Temp;
        
        Replacement = *(CCString*)CCOrderedCollectionGetElementAtIndex(Replacements, CCOrderedCollectionGetIndex(Occurrences, Found));
        if (Replacement)
        {
            Temp = CCStringCreateByInsertingString(NewString, Index, Replacement);
            CCStringDestroy(NewString);
            NewString = Temp;
            
            ReplacementLength = CCStringGetLength(Replacement);
        }
        
        else ReplacementLength = 0;
    }
    
    return NewString;
}

CCString CCStringCreateByJoiningStrings(CCString *Strings, size_t Count, CCString Separator)
{
    CCAssertLog(Strings, "Strings must not be null");
    
    //TODO: Optimize for non-tagged use case, only need one allocation as it can then mutate that same allocation
    CCString NewString = 0;
    if (Count > 0)
    {
        NewString = CCStringCopy(Strings[0]);
        if (!Separator)
        {
            for (size_t Loop = 1; Loop < Count; Loop++)
            {
                CCString Temp = CCStringCreateByInsertingString(NewString, CCStringGetLength(NewString), Strings[Loop]);
                CCStringDestroy(NewString);
                NewString = Temp;
            }
        }
        
        else
        {
            for (size_t Loop = 1; Loop < Count; Loop++)
            {
                CCString Temp = CCStringCreateByInsertingString(NewString, CCStringGetLength(NewString), Separator);
                CCStringDestroy(NewString);
                NewString = Temp;
                
                Temp = CCStringCreateByInsertingString(NewString, CCStringGetLength(NewString), Strings[Loop]);
                CCStringDestroy(NewString);
                NewString = Temp;
            }
        }
    }
    
    return NewString ? NewString : CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "");
}

CCString CCStringCreateByJoiningEntries(CCOrderedCollection Strings, CCString Separator)
{
    CCAssertLog(Strings, "Strings must not be null");
    
    //TODO: Optimize for non-tagged use case, only need one allocation as it can then mutate that same allocation
    CCString NewString = 0;
    
    CCEnumerator Enumerator;
    CCCollectionGetEnumerator(Strings, &Enumerator);
    
    CCString *String = CCCollectionEnumeratorGetCurrent(&Enumerator);
    if (String)
    {
        NewString = CCStringCopy(*String);
        if (!Separator)
        {
            while ((String = CCCollectionEnumeratorNext(&Enumerator)))
            {
                CCString Temp = CCStringCreateByInsertingString(NewString, CCStringGetLength(NewString), *String);
                CCStringDestroy(NewString);
                NewString = Temp;
            }
        }
        
        else
        {
            while ((String = CCCollectionEnumeratorNext(&Enumerator)))
            {
                CCString Temp = CCStringCreateByInsertingString(NewString, CCStringGetLength(NewString), Separator);
                CCStringDestroy(NewString);
                NewString = Temp;
                
                Temp = CCStringCreateByInsertingString(NewString, CCStringGetLength(NewString), *String);
                CCStringDestroy(NewString);
                NewString = Temp;
            }
        }
    }
    
    return NewString ? NewString : CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "");
}

CCOrderedCollection CCStringCreateBySeparatingOccurrencesOfString(CCString String, CCString Occurrence)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Occurrence, "Occurrence must not be null");
    
    CCOrderedCollection SeparatedStrings = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered, sizeof(CCString), CCStringDestructorForCollection);
    
    size_t Index = CCStringFindSubstring(String, 0, Occurrence);
    if (Index == SIZE_MAX)
    {
        CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopy(String) });
        return SeparatedStrings;
    }
    
    const size_t OccurrenceLength = CCStringGetLength(Occurrence);
    CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, 0, Index) });;
    
    size_t Offset = (Index += OccurrenceLength);
    for ( ; (Index = CCStringFindSubstring(String, Index, Occurrence)) != SIZE_MAX; Offset = (Index += OccurrenceLength))
    {
        CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, Offset, Index - Offset) });
    }
    
    CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, Offset, CCStringGetLength(String) - Offset) });
    
    return SeparatedStrings;
}

CCOrderedCollection CCStringCreateBySeparatingOccurrencesOfGroupedStrings(CCString String, CCString *Occurrences, size_t Count)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Occurrences, "Occurrence must not be null");
    
    CCOrderedCollection SeparatedStrings = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered, sizeof(CCString), CCStringDestructorForCollection);
    
    size_t Found;
    size_t Index = CCStringFindClosestSubstring(String, 0, Occurrences, Count, &Found);
    if (Index == SIZE_MAX)
    {
        CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopy(String) });
        return SeparatedStrings;
    }
    
    CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, 0, Index) });;
    
    size_t Offset = (Index += CCStringGetLength(Occurrences[Found]));
    for ( ; (Index = CCStringFindClosestSubstring(String, Index, Occurrences, Count, &Found)) != SIZE_MAX; Offset = (Index += CCStringGetLength(Occurrences[Found])))
    {
        CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, Offset, Index - Offset) });
    }
    
    CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, Offset, CCStringGetLength(String) - Offset) });
    
    return SeparatedStrings;
}

CCOrderedCollection CCStringCreateBySeparatingOccurrencesOfGroupedEntries(CCString String, CCOrderedCollection Occurrences)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Occurrences, "Occurrence must not be null");
    
    CCOrderedCollection SeparatedStrings = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered, sizeof(CCString), CCStringDestructorForCollection);
    
    CCCollectionEntry Found;
    size_t Index = CCStringFindClosestSubstringFromCollection(String, 0, Occurrences, &Found);
    if (Index == SIZE_MAX)
    {
        CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopy(String) });
        return SeparatedStrings;
    }
    
    CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, 0, Index) });;
    
    size_t Offset = (Index += CCStringGetLength(*(CCString*)CCCollectionGetElement(Occurrences, Found)));
    for ( ; (Index = CCStringFindClosestSubstringFromCollection(String, Index, Occurrences, &Found)) != SIZE_MAX; Offset = (Index += CCStringGetLength(*(CCString*)CCCollectionGetElement(Occurrences, Found))))
    {
        CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, Offset, Index - Offset) });
    }
    
    CCOrderedCollectionAppendElement(SeparatedStrings, &(CCString){ CCStringCopySubstring(String, Offset, CCStringGetLength(String) - Offset) });
    
    return SeparatedStrings;
}

CCString CCStringCopy(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (CCStringIsTagged(String)) return String;
    
    if (((CCStringInfo*)String)->hint & CCStringHintFree) return (CCString)CCRetain((CCStringInfo*)String);
    
    return CCStringCreateWithSize(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringGetEncoding(String), CCStringGetCharacters((CCStringInfo*)String), CCStringGetSize(String));
}

CCString CCStringCopySubstring(CCString String, size_t Offset, size_t Length)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Offset + Length <= CCStringGetLength(String), "Offset and size must not be out of bounds");
    
    if (CCStringIsTagged(String))
    {
        const CCStringMapSet Set = String & CCStringTaggedMask;
        const size_t Bits = CCStringTaggedBitSize(Set);
        
        return (Length ? ((((String >> 2) & ((UINTPTR_MAX >> ((sizeof(CCString) * 8) - (Length * Bits))) << (Offset * Bits))) >> (Offset * Bits)) << 2) : 0) | Set;
    }
    
    const char *Buffer = CCStringGetBuffer(String);
    if ((Buffer) && (CCStringGetEncoding(String) == CCStringEncodingASCII))
    {
        return CCStringCreateWithSize(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringGetEncoding(String), Buffer + Offset, Length);
    }
    
    else
    {
        char *Copy;
        CC_SAFE_Malloc(Copy, CCStringGetSize(String) + 1,
                       CC_LOG_ERROR("Failed to copy substring due to allocation failure. Allocation size (%zu)", CCStringGetSize(String) + 1);
                       return 0;
                       );
        
        *CCStringCopyCharacters(String, Offset, Length, Copy) = 0;
        
        return CCStringCreate(CC_STD_ALLOCATOR, CCStringHintFree | CCStringGetEncoding(String), Copy);
    }
}

void CCStringDestroy(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (!CCStringIsTagged(String))
    {
        if (!(((CCStringInfo*)String)->hint & CCStringMarkConstant))
        {
            CCFree((CCStringInfo*)String);
        }
    }
}

const char *CCStringGetBuffer(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    return CCStringIsTagged(String) || (((CCStringInfo*)String)->hint & CCStringMarkUnsafeBuffer) ? NULL : CCStringGetCharacters((CCStringInfo*)String);
}

char *CCStringCopyCharacters(CCString String, size_t Offset, size_t Length, char *Buffer)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Buffer, "Buffer must not be null");
    CCAssertLog(Offset + Length <= CCStringGetLength(String), "Offset and size must not be out of bounds");
    
    if (CCStringIsTagged(String))
    {
        CCEnumerator Enumerator;
        CCStringGetEnumerator(String, &Enumerator);
        
        for (size_t Loop = 0; Loop < Offset; Loop++) CCStringEnumeratorNext(&Enumerator);
        
        size_t Index = 0, Loop = 0;
        for (CCChar c = CCStringEnumeratorGetCurrent(&Enumerator); (Loop < Length) && (c) && (CCStringEnumeratorGetIndex(&Enumerator) != SIZE_MAX); c = CCStringEnumeratorNext(&Enumerator), Loop++)
        {
            Index += CCStringCopyCharacterUTF8(Buffer + Index, c);
        }
        
        Length = Index;
    }
    
    else
    {
        if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingASCII)
        {
            strncpy(Buffer, CCStringGetCharacters((CCStringInfo*)String) + Offset, Length);
        }
        
        else if ((((CCStringInfo*)String)->hint & CCStringHintEncodingMask) == CCStringEncodingUTF8)
        {
            CCEnumerator Enumerator;
            CCStringGetEnumerator(String, &Enumerator);
            
            for (size_t Loop = 0; Loop < Offset; Loop++) CCStringEnumeratorNext(&Enumerator);
            
            if (CCStringGetSize(String) - Offset == Length) strncpy(Buffer, CCStringGetCharacters((CCStringInfo*)String) + Offset, Length);
            else
            {
                size_t Index = 0, Loop = 0;
                for (CCChar c = CCStringEnumeratorGetCurrent(&Enumerator); (Loop < Length) && (c) && (CCStringEnumeratorGetIndex(&Enumerator) != SIZE_MAX); c = CCStringEnumeratorNext(&Enumerator), Loop++)
                {
                    Index += CCStringCopyCharacterUTF8(Buffer + Index, c);
                }
                
                Length = Index;
            }
        }
    }
    
    return Buffer + Length;
}

CCStringEncoding CCStringGetEncoding(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
    if (CCStringIsTagged(String)) return Maps[(String & CCStringTaggedMask) - 1].encoding;
    else return ((CCStringInfo*)String)->hint & CCStringHintEncodingMask;
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
        
        size_t Length = 0;
#if CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0
        /*
         TODO: Future optimization could be to cache the length into the tagged string.
         
         64bit CCStringMapSet127: 6 bits unused
         32bit CCStringMapSet127: 2 bits unused
         
         64bit CCStringMapSet63: 2 bits unused
         32bit CCStringMapSet63: 0 bits unused
         
         64bit CCStringMapSet31: 2 bits unused
         32bit CCStringMapSet31: 0 bits unused
         
         64bit: 4 bits (max: 15) is all that would be needed to store length for all variants.
         32bit: 3 bits (max: 7) is all that would be needed to store length for all variants.
         
         Only one with enough space to spare is 64bit CCStringMapSet127. One approach could be to just store
         the length in the high bits anyway. Then if it reaches second highest allowed character it would
         disable it.
         
         So check would instead be check if length bits are set. If they are set check if preceeding character is
         set, if it's set then that means the length bits are actually a character and max length is used. If they
         are not set then that means the length bits are a length value. If the length bits are 0 (not set), then 
         the length has to be max - 1 (second longest).
         
         So highest char bits can be used to store length or character. Depending on current length. Would have to
         make sure to clear those bits on string manipulations (CopySubstring, Create*).
         */
        switch (Set)
        {
            case CCStringMapSet127: //7
#if CC_HARDWARE_PTR_64
                if (String & 0x3ffffffc0000000) //5 - 8
                {
                    if (String & 0x3fff00000000000) //7 - 8
                    {
                        Length = (String & 0x3f8000000000000) ? 8 : 7;
                    }
                    
                    else //0xfffc0000000 //5 - 6
                    {
                        Length = (String & 0xfe000000000) ? 6 : 5;
                    }
                } else
#endif
#if CC_HARDWARE_PTR_64 || CC_HARDWARE_PTR_32
                if (String & 0x3ffffffc) //1 - 4
                {
                    if (String & 0x3fff0000) //3 - 4
                    {
                        Length = (String & 0x3f800000) ? 4 : 3;
                    }
                    
                    else //0xfffc //1 - 2
                    {
                        Length = (String & 0xfe00) ? 2 : 1;
                    }
                }
#else
#error Unknown pointer size
#endif
                break;
                
            case CCStringMapSet63: //6
#if CC_HARDWARE_PTR_64
                if (String & 0x3fffffff00000000) //6 - 10
                {
                    if (String & 0x3ffc000000000000) //9 - 10
                    {
                        Length = (String & 0x3f00000000000000) ? 10 : 9;
                    }
                    
                    else if (String & 0x3ffc000000000) //7 - 8
                    {
                        Length = (String & 0x3f00000000000) ? 8 : 7;
                    }
                    
                    else Length = 6; //0x3f00000000 //6
                } else
#endif
#if CC_HARDWARE_PTR_64 || CC_HARDWARE_PTR_32
                if (String & 0xfffffffc) //1 - 5
                {
                    if (String & 0xfff00000) //4 - 5
                    {
                        Length = (String & 0xfc000000) ? 5 : 4;
                    }
                    
                    else if (String & 0xfff00) //2 - 3
                    {
                        Length = (String & 0xfc000) ? 3 : 2;
                    }
                    
                    else Length = 1; //0xfc //1
                }
#else
#error Unknown pointer size
#endif
                break;
                
            case CCStringMapSet31: //5
#if CC_HARDWARE_PTR_64
                if (String & 0x3fffffff00000000) //6 - 12
                {
                    if (String & 0x3fff800000000000) //10 - 12
                    {
                        if (String & 0x3ff0000000000000) //11 - 12
                        {
                            Length = (String & 0x3e00000000000000) ? 12 : 11;
                        }
                        
                        else Length = 10; //0xF800000000000
                    }
                    
                    else if (String & 0x7fff00000000) //7 - 9
                    {
                        if (String & 0x7fe000000000) //8 - 9
                        {
                            Length = (String & 0x7c0000000000) ? 9 : 8;
                        }
                        
                        else Length = 7; //0x1F00000000
                    }
                } else
#endif
#if CC_HARDWARE_PTR_64 || CC_HARDWARE_PTR_32
                if (String & 0xfffffffc) //1 - 6
                {
                    if (String & 0xfffe0000) //4 - 6
                    {
                        if (String & 0xffc00000) //5 - 6
                        {
                            Length = (String & 0xf8000000) ? 6 : 5;
                        }
                        
                        else Length = 4; //0x3e0000
                    }
                    
                    else if (String & 0x1fffc) //1 - 3
                    {
                        if (String & 0x1ff80) //2 - 3
                        {
                            Length = (String & 0x1f000) ? 3 : 2;
                        }
                        
                        else Length = 1; //0x7c
                    }
                }
#else
#error Unknown pointer size
#endif
                break;
        }
#else
        String >>= 2;
        
        const size_t Bits = CCStringTaggedBitSize(Set);
        const size_t MapSize = CCStringTaggedMapSize(Set);
        const CCStringMap *Map = CCStringTaggedMap(Set);
        for (size_t Loop = 0, Count = CCStringTaggedCharacterMax(Set); (Loop < Count) && (CCCharSize(Map[(String >> (Bits * Loop)) & MapSize])); Loop++)
        {
            Length++;
        }
#endif
        
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

#if CC_STRING_TAGGED_HASH_CACHE
static CCDictionary(CCString, uint32_t) TaggedHashCache = NULL;

#if CC_STRING_USING_STDATOMIC
static _Atomic(int32_t) HashCacheLock = 0;
#else
static int32_t HashCacheLock = 0;
#endif
#endif

uint32_t CCStringGetHash(CCString String)
{
    CCAssertLog(String, "String must not be null");
    
#if CC_STRING_TAGGED_HASH_CACHE
    _Bool StoreCompute = FALSE;
#endif
    if ((!CCStringIsTagged(String)) && (((CCStringInfo*)String)->hint & CCStringMarkHash)) return ((CCStringInfo*)String)->hash;
#if CC_STRING_TAGGED_HASH_CACHE
    else if (CCStringIsTagged(String))
    {
        if (TaggedHashCache)
        {
            int32_t Expected = HashCacheLock;
            if (Expected >= 0)
            {
#if CC_STRING_USING_STDATOMIC
                Expected = atomic_fetch_add_explicit(&HashCacheLock, 1, memory_order_acquire);
#elif CC_STRING_USING_OSATOMIC
                Expected = OSAtomicIncrement32Barrier(&HashCacheLock);
#endif
                if (Expected >= 0)
                {
                    uint32_t *Hash = CCDictionaryGetValue(TaggedHashCache, &String);
                    
#if CC_STRING_USING_STDATOMIC
                    atomic_fetch_sub_explicit(&HashCacheLock, 1, memory_order_release);
#elif CC_STRING_USING_OSATOMIC
                    OSAtomicDecrement32(&HashCacheLock);
#endif
                    
                    if (Hash) return *Hash;
                    
                    StoreCompute = TRUE;
                }
                
                else
                {
#if CC_STRING_USING_STDATOMIC
                    atomic_fetch_sub_explicit(&HashCacheLock, 1, memory_order_release);
#elif CC_STRING_USING_OSATOMIC
                    OSAtomicDecrement32(&HashCacheLock);
#endif
                    StoreCompute = FALSE;
                }
            }
        }
        
        else StoreCompute = TRUE;
    }
#endif
    
    uint32_t Hash = 0;
    
    CCEnumerator Enumerator;
    CCStringGetEnumerator(String, &Enumerator);
    
    for (CCChar c = CCStringEnumeratorGetCurrent(&Enumerator); (c) && (CCStringEnumeratorGetIndex(&Enumerator) != SIZE_MAX); c = CCStringEnumeratorNext(&Enumerator))
    {
        char Buffer[4];
        size_t Size = CCStringCopyCharacterUTF8(Buffer, c);
        
        for (size_t Loop = 0; Loop < Size; Loop++)
        {
            Hash += Buffer[Loop];
            Hash += (Hash << 10);
            Hash ^= (Hash >> 6);
        }
    }
    
    Hash += (Hash << 3);
    Hash ^= (Hash >> 11);
    Hash += (Hash << 15);
    
    if (!CCStringIsTagged(String))
    {
        ((CCStringInfo*)String)->hash = Hash;
        ((CCStringInfo*)String)->hint |= CCStringMarkHash;
    }
    
#if CC_STRING_TAGGED_HASH_CACHE
    else if (StoreCompute)
    {
#if CC_STRING_USING_STDATOMIC
        if (atomic_compare_exchange_weak_explicit(&HashCacheLock, &(int32_t){ 0 }, INT32_MIN, memory_order_acq_rel, memory_order_relaxed))
#elif CC_STRING_USING_OSATOMIC
        if (OSAtomicCompareAndSwap32Barrier(0, INT32_MIN, &HashCacheLock))
#endif
        {
            if (!TaggedHashCache) TaggedHashCache = CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeMedium | CCDictionaryHintHeavyFinding | CCDictionaryHintHeavyInserting, sizeof(CCString), sizeof(uint32_t), NULL);
            
            CCDictionarySetValue(TaggedHashCache, &String, &Hash);
            
#if CC_STRING_USING_STDATOMIC
            while (!atomic_compare_exchange_weak_explicit(&HashCacheLock, &(int32_t){ INT32_MIN }, 0, memory_order_acq_rel, memory_order_relaxed));
#elif CC_STRING_USING_OSATOMIC
            OSMemoryBarrier();
            while (!OSAtomicCompareAndSwap32(INT32_MIN, 0, &HashCacheLock));
#endif
        }
    }
#endif
    
    return Hash;
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

size_t CCStringFindSubstring(CCString String, size_t Index, CCString Substring)
{
    CCAssertLog(String && Substring, "Strings must not be null");
    CCAssertLog(Index <= CCStringGetLength(String), "Index must not exceed string length");
    
    const size_t StringLength = CCStringGetLength(String), SubstringLength = CCStringGetLength(Substring);
    if ((StringLength) && ((StringLength - Index) >= SubstringLength))
    {
        if ((CCStringIsTagged(String)) && (CCStringIsTagged(Substring)) && ((String & CCStringTaggedMask) == (Substring & CCStringTaggedMask)))
        {
            const CCStringMapSet Set = String & CCStringTaggedMask;
            const size_t Bits = CCStringTaggedBitSize(Set);
            const size_t SubstringMax = CCStringTaggedCharacterMax(Set) - SubstringLength;
            
            String >>= 2;
            Substring = (Substring >> 2) << (Bits * Index);
            CCString Mask = (UINTPTR_MAX >> ((sizeof(CCString) * 8) - (SubstringLength * Bits))) << (Bits * Index);
            
            for (size_t Loop = 0; (Index < StringLength) && (Loop < SubstringMax); Loop++, Index++, String >>= Bits)
            {
                if ((String & Mask) == Substring) return Index;
            }
        }
        
        else
        {
            for ( ; ((StringLength - Index) >= SubstringLength) && (Index < StringLength); Index++)
            {
                for (size_t Loop = Index, Loop2 = 0; (Loop2 < SubstringLength) && (CCStringGetCharacterAtIndex(String, Loop) == CCStringGetCharacterAtIndex(Substring, Loop2)); Loop++, Loop2++)
                {
                    if ((Loop2 + 1) == SubstringLength) return Index;
                }
            }
        }
    }
    
    return SIZE_MAX;
}

_Bool CCStringEqual(CCString String1, CCString String2)
{
    CCAssertLog(String1 && String2, "Strings must not be null");
    
    size_t Size;
    _Bool Equal = String1 == String2;
    if (!Equal)
    {
        if ((CCStringIsTagged(String1)) && (CCStringIsTagged(String2)) && ((String1 & CCStringTaggedMask) == (String2 & CCStringTaggedMask))) return FALSE;
        
        if (((Size = CCStringGetSize(String1)) == CCStringGetSize(String2)) &&
            (CCStringGetLength(String1) == CCStringGetLength(String2)) &&
            (CCStringGetHash(String1) == CCStringGetHash(String2)))
        {
            if ((CCStringIsTagged(String1)) || (CCStringIsTagged(String2)))
            {
                CCEnumerator Enumerator1, Enumerator2;
                CCStringGetEnumerator(String1, &Enumerator1);
                CCStringGetEnumerator(String2, &Enumerator2);
                
                if (CCStringEnumeratorGetCurrent(&Enumerator1) == CCStringEnumeratorGetCurrent(&Enumerator2))
                {
                    for (CCChar c = 0; ((c = CCStringEnumeratorNext(&Enumerator1)) == CCStringEnumeratorNext(&Enumerator2)) && (c); );
                    
                    Equal = CCStringEnumeratorGetIndex(&Enumerator1) == SIZE_MAX;
                }
            }
            
            else Equal = !strncmp(CCStringGetCharacters((CCStringInfo*)String1), CCStringGetCharacters((CCStringInfo*)String2), Size);
        }
    }
    
    return Equal;
}

_Bool CCStringHasPrefix(CCString String, CCString Prefix)
{
    _Bool Equal = CCStringEqual(String, Prefix);
    if (!Equal)
    {
#if CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0
        if ((CCStringIsTagged(String)) && (CCStringIsTagged(Prefix)) && ((String & CCStringTaggedMask) == (Prefix & CCStringTaggedMask)))
        {
            size_t PrefixLength = CCStringGetLength(Prefix);
            const size_t Bits = CCStringTaggedBitSize(String & CCStringTaggedMask);
            const CCString Mask = (UINTPTR_MAX >> ((sizeof(CCString) * 8) - (PrefixLength * Bits))) << 2;
            
            return (String & Mask) == (Prefix & Mask);
        }
#endif
        
        CCEnumerator Enumerator1, Enumerator2;
        CCStringGetEnumerator(String, &Enumerator1);
        CCStringGetEnumerator(Prefix, &Enumerator2);
        
        if (CCStringEnumeratorGetCurrent(&Enumerator1) == CCStringEnumeratorGetCurrent(&Enumerator2))
        {
            for (CCChar c = 0; ((c = CCStringEnumeratorNext(&Enumerator1)) == CCStringEnumeratorNext(&Enumerator2)) && (c); );
            
            Equal = CCStringEnumeratorGetIndex(&Enumerator2) == SIZE_MAX;
        }
    }
    
    return Equal;
}

_Bool CCStringHasSuffix(CCString String, CCString Suffix)
{
    _Bool Equal = CCStringEqual(String, Suffix);
    if (!Equal)
    {
#if CC_STRING_TAGGED_NUL_CHAR_ALWAYS_0
        if ((CCStringIsTagged(String)) && (CCStringIsTagged(Suffix)) && ((String & CCStringTaggedMask) == (Suffix & CCStringTaggedMask)))
        {
            size_t SuffixLength = CCStringGetLength(Suffix), StringLength = CCStringGetLength(String);
            const size_t Bits = CCStringTaggedBitSize(String & CCStringTaggedMask);
            const CCString Mask = (UINTPTR_MAX >> ((sizeof(CCString) * 8) - (SuffixLength * Bits))) << 2;
            
            return ((String >> ((StringLength - SuffixLength) * Bits)) & Mask) == (Suffix & Mask);
        }
#endif
        
        CCEnumerator Enumerator1, Enumerator2;
        CCStringGetEnumerator(String, &Enumerator1);
        CCStringGetEnumerator(Suffix, &Enumerator2);
        
        if (CCStringEnumeratorGetTail(&Enumerator1) == CCStringEnumeratorGetTail(&Enumerator2))
        {
            for (CCChar c = 0; ((c = CCStringEnumeratorPrevious(&Enumerator1)) == CCStringEnumeratorPrevious(&Enumerator2)) && (c); );
            
            Equal = CCStringEnumeratorGetIndex(&Enumerator2) == SIZE_MAX;
        }
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
                if ((Enumerator->internal.extra[0] + 1) >= CCStringGetLength(String))
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
                    if ((Enumerator->internal.extra[0] + 1) >= CCStringGetLength(String))
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
    size_t Length = 0;
    
    for (size_t Size = 0; CCStringGetCharacterUTF8(String, &Size); Length++, String += Size);
    
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

static const char CCStringFirstByteMarkUTF8[7] = { 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc };

static size_t CCStringCopyCharacterUTF8(char *String, CCChar c)
{
    size_t Size = CCCharSize(c);
    
    switch (Size)
    {
        case 4:
            String[3] = (c | 0x80) & 0xbf;
            c >>= 6;
        case 3:
            String[2] = (c | 0x80) & 0xbf;
            c >>= 6;
        case 2:
            String[1] = (c | 0x80) & 0xbf;
            c >>= 6;
        case 1:
            String[0] = (c | CCStringFirstByteMarkUTF8[Size]);
    }
    
    return Size;
}
