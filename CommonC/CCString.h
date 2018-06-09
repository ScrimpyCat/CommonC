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

#include <CommonC/Base.h>
#include <CommonC/Allocator.h>
#include <CommonC/Enumerator.h>
#include <CommonC/Platform.h>
#include <CommonC/MemoryAllocation.h>
#include <CommonC/OrderedCollection.h>

#if CC_HARDWARE_PTR_64
#define CC_STRING_HEADER "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#elif CC_HARDWARE_PTR_32
#define CC_STRING_HEADER "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#else
#error Unknown pointer size
#endif

#if CC_HARDWARE_ENDIAN_BIG
#define CC_STRING_HEADER_CCStringEncodingASCII "\x80\x00\x00\x00" CC_STRING_HEADER
#define CC_STRING_HEADER_CCStringEncodingUTF8 "\x80\x00\x00\x01" CC_STRING_HEADER
#elif CC_HARDWARE_ENDIAN_LITTLE
#define CC_STRING_HEADER_CCStringEncodingASCII "\x00\x00\x00\x80" CC_STRING_HEADER
#define CC_STRING_HEADER_CCStringEncodingUTF8 "\x01\x00\x00\x80" CC_STRING_HEADER
#else
#error Unknown endianness
#endif

/*!
 * @define CC_STRING_TEMP_BUFFER
 * @abstract Convenience macro to get a temporary buffer (const char*).
 * @discussion Attempts to retrieve the internal buffer if that fails, will default to copying the string into
 *             temporary storage (as will be a tagged string, so should fit on the stack easily). The scope of
 *             temporary buffer is the next logical scope, where it should either be followed by parantheses or
 *             a single line statement.
 *
 * @warning Scoping rules apply, to avoid unintended problems with nested foreach loops either change the buffer
 *          name, or enclose it in a braces.
 *
 * @param buffer The name for the buffer variable, declared as @b const char*.
 * @param string The string literal to create the string from.
 * @param ... The code to be executed on failure.
 */
#define CC_STRING_TEMP_BUFFER(buffer, string, ...) \
const char *buffer##__CC_PRIV__PRIVCONST_STRING = CCStringGetBuffer(string); \
char *buffer##__CC_PRIV__TEMP_STRING = NULL; \
CC_TEMP_Malloc(buffer##__CC_PRIV__TEMP_STRING, (CCStringGetSize(string) + 1) * (_Bool)buffer##__CC_PRIV__PRIVCONST_STRING, __VA_ARGS__); \
if ((!buffer##__CC_PRIV__PRIVCONST_STRING) && (buffer##__CC_PRIV__TEMP_STRING)) *CCStringCopyCharacters(string, 0, CCStringGetLength(string), buffer##__CC_PRIV__TEMP_STRING) = 0; \
for (const char *buffer = buffer##__CC_PRIV__PRIVCONST_STRING ? buffer##__CC_PRIV__PRIVCONST_STRING : buffer##__CC_PRIV__TEMP_STRING; buffer; buffer = NULL, CC_TEMP_Free(buffer##__CC_PRIV__TEMP_STRING))

/*!
 * @define CC_STRING
 * @abstract Special macro to create a temporary constant (allocation free) UTF-8 string.
 * @discussion If used globally the string will last for the life of the program, however if used within
 *             a function it will last for the entirety of the local scope.
 *
 * @param string The string literal to create the string from.
 */
#define CC_STRING(string) CC_STRING_ENCODING(CCStringEncodingUTF8, string)

/*!
 * @define CC_STRING_ENCODING
 * @abstract Special macro to create a temporary constant (allocation free) string.
 * @discussion If used globally the string will last for the life of the program, however if used within
 *             a function it will last for the entirety of the local scope.
 *
 * @param encoding The encoding of the string.
 * @param string The string literal to create the string from.
 */
#define CC_STRING_ENCODING(encoding, string) (CCString)((struct { _Alignas(4) char s[sizeof(CC_STRING_HEADER_##encoding string)]; }){ CC_STRING_HEADER_##encoding string }.s) //Alignment solution: http://stackoverflow.com/questions/34796571/c-aligning-string-literals-for-a-specific-use-case

/*!
 * @brief The string.
 * @warning Unsafe to call CCRetain, instead use CCStringCopy
 */
typedef uintptr_t CCString;

/*!
 * @brief The UTF-32 character (big-endian).
 */
typedef uint32_t CCChar;

typedef enum {
    CCStringEncodingASCII,
    CCStringEncodingUTF8
} CCStringEncoding;

typedef enum {
    ///A 127 character set, first byte in the set should generally be 0.
    CCStringMapSet127 = 1,
    ///A 63 character set, first byte in the set should generally be 0.
    CCStringMapSet63,
    ///A 31 character set, first byte in the set should generally be 0.
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

/*!
 * @brief Set the character map to be used for the specified map set.
 * @param Encoding The encoding of the map.
 * @param Map The map.
 * @param Set The map set it is to be used for.
 */
void CCStringRegisterMap(CCStringEncoding Encoding, const CCStringMap *Map, CCStringMapSet Set);

/*!
 * @brief Get the character map for the specified map set.
 * @param Set The map set to get the map of.
 * @param Encoding The encoding of the map.
 * @return The map.
 */
const CCStringMap *CCStringGetMap(CCStringMapSet Set, CCStringEncoding *Encoding);

/*!
 * @brief Create a string from a character.
 * @param Allocator The allocator to be used for the allocations.
 * @param Character The character to turn into a string.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateWithCharacter(CCAllocatorType Allocator, CCChar Character);

/*!
 * @brief Create a string.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage and format of the string.
 * @param String The null terminated string to make a CCString representation from.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreate(CCAllocatorType Allocator, CCStringHint Hint, const char *String);

/*!
 * @brief Create a string.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage and format of the string.
 * @param String The null terminated string to make a CCString representation from.
 * @param Size The size of the string to be used.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateWithSize(CCAllocatorType Allocator, CCStringHint Hint, const char *String, size_t Size);

/*!
 * @brief Create a string by inserting a string into a string.
 * @param String The string to insert into.
 * @param Index The index to insert the string.
 * @param Insert The string to insert.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateByInsertingString(CCString String, size_t Index, CCString Insert);

/*!
 * @brief Create a string by removing the characters in range.
 * @param String The string to remove from.
 * @param Offset The offset to start the substring from.
 * @param Length The length of the substring.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateWithoutRange(CCString String, size_t Offset, size_t Length);

/*!
 * @brief Create a string by replacing occurrences of a string with another string.
 * @param String The string to be replaced.
 * @param Occurrence The string to find.
 * @param Replacement The string to be replaced with, or NULL if no characters are to be inserted.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateByReplacingOccurrencesOfString(CCString String, CCString Occurrence, CCString Replacement);

/*!
 * @brief Create a string by replacing occurrences of a strings with other strings.
 * @description Similar to @b CCStringCreateByReplacingOccurrencesOfString with the exception that the
 *              comparisons are grouped. So out of the list of potential occurrences, the closest one is
 *              used, and then skips over the replacement and looks for the next occurrence.
 *
 * @param String The string to be replaced.
 * @param Occurrences The list of strings to find.
 * @param Replacements The list of strings to be replaced with, index of the string should match with the
 *        index of the occurrence. In-place of a string, NULL can be used if no characters are to be
 *        inserted for given occurrence.
 *
 * @param Count The amount of items in the list.
 *
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateByReplacingOccurrencesOfGroupedStrings(CCString String, CCString *Occurrences, CCString *Replacements, size_t Count);

/*!
 * @brief Create a string by replacing occurrences of a strings with other strings.
 * @description Similar to @b CCStringCreateByReplacingOccurrencesOfString with the exception that the
 *              comparisons are grouped. So out of the list of potential occurrences, the closest one is
 *              used, and then skips over the replacement and looks for the next occurrence.
 *
 * @param String The string to be replaced.
 * @param Occurrences The list of strings to find.
 * @param Replacements The list of strings to be replaced with, index of the string should match with the
 *        index of the occurrence. In-place of a string, NULL can be used if no characters are to be
 *        inserted for given occurrence.
 *
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateByReplacingOccurrencesOfGroupedEntries(CCString String, CCOrderedCollection Occurrences, CCOrderedCollection Replacements);

/*!
 * @brief Create a string by concatenating the list of strings, with an optional separator.
 * @param Strings The list of strings to be concatenated.
 * @param Count The amount of strings in the list.
 * @param Separator The string to be included inbetween each concatenated string, or NULL when no
 *        separator should be included.
 *
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateByJoiningStrings(CCString *Strings, size_t Count, CCString Separator);

/*!
 * @brief Create a string by concatenating the list of strings, with an optional separator.
 * @param Strings The list of strings to be concatenated.
 * @param Separator The string to be included inbetween each concatenated string, or NULL when no
 *        separator should be included.
 *
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCreateByJoiningEntries(CCOrderedCollection Strings, CCString Separator);

/*!
 * @brief Create a collection of strings separated by the occurrence of a string.
 * @param String The string to be split up.
 * @param Occurrence The string to find.
 * @return The collection of strings, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCOrderedCollection CCStringCreateBySeparatingOccurrencesOfString(CCString String, CCString Occurrence);

/*!
 * @brief Create a collection of strings separated by the occurrences of strings.
 * @description Similar to @b CCStringCreateBySeparatingOccurrencesOfString with the exception that the
 *              comparisons are grouped. So out of the list of potential occurrences, the closest one is
 *              used, and then skips over to the next chunk and looks for the next occurrence.
 *
 * @param String The string to be split up.
 * @param Occurrences The list of strings to find.
 * @param Count The amount of items in the list.
 * @return The collection of strings, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCOrderedCollection CCStringCreateBySeparatingOccurrencesOfGroupedStrings(CCString String, CCString *Occurrences, size_t Count);

/*!
 * @brief Create a collection of strings separated by the occurrences of strings.
 * @description Similar to @b CCStringCreateBySeparatingOccurrencesOfString with the exception that the
 *              comparisons are grouped. So out of the list of potential occurrences, the closest one is
 *              used, and then skips over the next chunk and looks for the next occurrence.
 *
 * @param String The string to be split up.
 * @param Occurrences The list of strings to find.
 * @return The collection of strings, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCOrderedCollection CCStringCreateBySeparatingOccurrencesOfGroupedEntries(CCString String, CCOrderedCollection Occurrences);

/*!
 * @brief Copy a string.
 * @param String The string to be copied.
 * @return The string, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCopy(CCString String);

/*!
 * @brief Copy a substring.
 * @param String The string to be copied from.
 * @param Offset The offset to start the substring from.
 * @param Length The length of the substring.
 * @return The substring, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCString CCStringCopySubstring(CCString String, size_t Offset, size_t Length);

/*!
 * @brief Destroy the string.
 * @param String The string to be destroyed.
 */
void CCStringDestroy(CCString CC_DESTROY(String));

/*!
 * @brief Get the internal character buffer of a string.
 * @param String The string to get the buffer of.
 * @return The character buffer, or NULL if it cannot retrieve one (instead will have to use
 *         @b CCStringCopyCharacters).
 */
const char *CCStringGetBuffer(CCString String);

/*!
 * @brief Copy the characters from a string into the specified character buffer.
 * @param String The string to get the characters of.
 * @param Offset The index of the character to start copying from.
 * @param Length The amount of characters to be copied.
 * @return The next character in the buffer.
 */
char *CCStringCopyCharacters(CCString String, size_t Offset, size_t Length, char *Buffer);

/*!
 * @brief Get the encoding of a string.
 * @param String The string to get the encoding of.
 * @return The encoding.
 */
CCStringEncoding CCStringGetEncoding(CCString String);

/*!
 * @brief Get the storage size of a string.
 * @param String The string to get the storage size of.
 * @return The size, excludes the null byte.
 */
size_t CCStringGetSize(CCString String);

/*!
 * @brief Get the character length for a string.
 * @param String The string to get the length of.
 * @return The length, excludes null byte.
 */
size_t CCStringGetLength(CCString String);

/*!
 * @brief Get the hash for a string.
 * @param String The string to get the hash of.
 * @return The hash.
 */
uint32_t CCStringGetHash(CCString String);

/*!
 * @brief Get the character in the string.
 * @param String The string to get the character from.
 * @param Index The index of the character.
 * @return The character.
 */
CCChar CCStringGetCharacterAtIndex(CCString String, size_t Index);

/*!
 * @brief Find the substring in the string.
 * @param String The string to find the substring in.
 * @param Index The index to start searching from.
 * @param Substring The substring to find.
 * @return The index of the found string, or SIZE_MAX on failure to find the substring.
 */
size_t CCStringFindSubstring(CCString String, size_t Index, CCString Substring);

/*!
 * @brief Compare if two strings are equal.
 * @param String1 The string to compare.
 * @param String2 The string to compare.
 * @return TRUE if the strings are the same, otherwise FALSE.
 */
_Bool CCStringEqual(CCString String1, CCString String2);

/*!
 * @brief Check if the string contains the prefix.
 * @param String The string to check the prefix of.
 * @param Prefix The prefix.
 * @return TRUE if the string has the prefix, otherwise FALSE.
 */
_Bool CCStringHasPrefix(CCString String, CCString Prefix);

/*!
 * @brief Check if the string contains the suffix.
 * @param String The string to check the suffix of.
 * @param Suffix The suffix.
 * @return TRUE if the string has the suffix, otherwise FALSE.
 */
_Bool CCStringHasSuffix(CCString String, CCString Suffix);

/*!
 * @brief Get the enumerator for a string.
 * @param String The string to get the enumerator for.
 * @param Enumerator The enumerator to be initialized.
 */
void CCStringGetEnumerator(CCString String, CCEnumerator *Enumerator);

///For private use, use CCStringEnumerator* functions instead. Found in @b CCStringEnumerator.h
CCChar CCStringEnumerator(CCString String, CCEnumeratorState *Enumerator, CCStringEnumeratorAction Action);

#endif
