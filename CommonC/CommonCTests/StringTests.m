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

#import <XCTest/XCTest.h>
#import "CCString.h"
#import "CCStringEnumerator.h"

@interface StringTests : XCTestCase

-(CCString) createString;
-(size_t) size;
-(CCChar) charAtIndex: (size_t)index;
-(CCStringEncoding) encoding;
-(uint32_t) getHash;

@end

@implementation StringTests

-(void) setUp
{
    [super setUp];
}

-(void) tearDown
{
    [super tearDown];
}

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], "helLo");
}

-(size_t) size
{
    return 5;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', 'e', 'l', 'L', 'o' }[index];
}

-(CCStringEncoding) encoding
{
    return CCStringEncodingASCII;
}

-(uint32_t) getHash
{
    return 0x78bd1aec;
}

-(void) testBigCreate
{
    CCString String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, "aaaaaaaaaaaaa");
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("aaaaaaaaaaaaa")), @"Should create the correct string");
    
    CCStringDestroy(String);
}

-(void) testTaggedLength
{
    CCStringEncoding Encoding[3];
    const CCStringMap *Maps[3] = {
        CCStringGetMap(CCStringMapSet127, Encoding),
        CCStringGetMap(CCStringMapSet63, &Encoding[1]),
        CCStringGetMap(CCStringMapSet31, &Encoding[2])
    };
    
    CCStringMap NulMap[127] = {0};
    CCStringMap HiLoMap[127] = { //Highest and Lowest bits set
        0, 'a', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '3', 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '2', 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '1'
    };
    
    CCStringRegisterMap(CCStringEncodingUTF8, NulMap, CCStringMapSet31);
    CCStringRegisterMap(CCStringEncodingUTF8, NulMap, CCStringMapSet63);
    CCStringRegisterMap(CCStringEncodingUTF8, HiLoMap, CCStringMapSet127);
    
    for (int Loop = 0; Loop < 12; Loop++)
    {
        CCString String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, &"aaaaaaaaaaaa"[Loop]);
        
        XCTAssertEqual(CCStringGetLength(String), 12 - Loop, @"Should get the correct length");
        
        CCStringDestroy(String);
        
        
        String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, &"111111111111"[Loop]);
        
        XCTAssertEqual(CCStringGetLength(String), 12 - Loop, @"Should get the correct length");
        
        CCStringDestroy(String);
    }
    
    
    CCStringRegisterMap(CCStringEncodingUTF8, NulMap, CCStringMapSet31);
    CCStringRegisterMap(CCStringEncodingUTF8, HiLoMap, CCStringMapSet63);
    CCStringRegisterMap(CCStringEncodingUTF8, NulMap, CCStringMapSet127);
    
    for (int Loop = 0; Loop < 12; Loop++)
    {
        CCString String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, &"aaaaaaaaaaaa"[Loop]);
        
        XCTAssertEqual(CCStringGetLength(String), 12 - Loop, @"Should get the correct length");
        
        CCStringDestroy(String);
        
        
        String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, &"222222222222"[Loop]);
        
        XCTAssertEqual(CCStringGetLength(String), 12 - Loop, @"Should get the correct length");
        
        CCStringDestroy(String);
    }
    
    
    CCStringRegisterMap(CCStringEncodingUTF8, HiLoMap, CCStringMapSet31);
    CCStringRegisterMap(CCStringEncodingUTF8, NulMap, CCStringMapSet63);
    CCStringRegisterMap(CCStringEncodingUTF8, NulMap, CCStringMapSet127);
    
    for (int Loop = 0; Loop < 12; Loop++)
    {
        CCString String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, &"aaaaaaaaaaaa"[Loop]);
        
        XCTAssertEqual(CCStringGetLength(String), 12 - Loop, @"Should get the correct length");
        
        CCStringDestroy(String);
        
        
        String = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, &"333333333333"[Loop]);
        
        XCTAssertEqual(CCStringGetLength(String), 12 - Loop, @"Should get the correct length");
        
        CCStringDestroy(String);
    }
    
    CCStringRegisterMap(Encoding[2], Maps[2], CCStringMapSet31);
    CCStringRegisterMap(Encoding[1], Maps[1], CCStringMapSet63);
    CCStringRegisterMap(Encoding[0], Maps[0], CCStringMapSet127);
}

-(void) testReplacement
{
    CCString String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01a234aa5a"), CC_STRING("a"), 0);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01a234aa5a"), CC_STRING("a"), CC_STRING("bc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01bc234bcbc5bc")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01a234aa5a"), CC_STRING("aa"), CC_STRING("bc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01a234bc5a")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("012345"), CC_STRING("a"), CC_STRING("bc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01😀234😀😀5😀"), CC_STRING("😀"), 0);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01😀234😀😀5😀"), CC_STRING("😀"), CC_STRING("bc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01bc234bcbc5bc")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01😀234😀😀5😀"), CC_STRING("😀😀"), CC_STRING("bc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01😀234bc5😀")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("012345"), CC_STRING("😀"), CC_STRING("bc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("01a234aa5a"), CC_STRING("a"), CC_STRING("😀😀"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01😀😀234😀😀😀😀5😀😀")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    CCString Str = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "01a234aa5a");
    CCString Str2 = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "012345");
    CCString Occurrence = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "a");
    CCString Occurrence2 = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "aa");
    CCString Replacement = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "bc");
    String = CCStringCreateByReplacingOccurrencesOfString(Str, Occurrence, 0);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(Str, Occurrence, Replacement);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01bc234bcbc5bc")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(Str, Occurrence2, Replacement);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("01a234bc5a")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByReplacingOccurrencesOfString(Str2, Occurrence, Replacement);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    CCStringDestroy(Str);
    CCStringDestroy(Str2);
    CCStringDestroy(Occurrence);
    CCStringDestroy(Occurrence2);
    CCStringDestroy(Replacement);
    
    
    Str = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "1 2 3 4 5");
    Occurrence = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, " ");
    String = CCStringCreateByReplacingOccurrencesOfString(Str, Occurrence, 0);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("12345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    CCStringDestroy(Str);
    CCStringDestroy(Occurrence);
    
    
    Str = CCStringCreateByReplacingOccurrencesOfString(CC_STRING("aababaaab"), CC_STRING("aa"), CC_STRING("a"));
    String = CCStringCreateByReplacingOccurrencesOfString(Str, CC_STRING("ab"), CC_STRING("1"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("11a1")), @"Should create the correct string");
    
    CCStringDestroy(String);
    CCStringDestroy(Str);
    
    
    String = CCStringCreateByReplacingOccurrencesOfGroupedStrings(CC_STRING("aababaaab"), (CCString[]){
        CC_STRING("aa"), CC_STRING("ab")
    }, (CCString[]){
        CC_STRING("a"), CC_STRING("1")
    }, 2);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("ab1a1")), @"Should create the correct string");
    
    CCStringDestroy(String);
}

-(void) testRemoval
{
    CCString String = CCStringCreateWithoutRange(CC_STRING("012345"), 0, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(CC_STRING("012345"), 1, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("045")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(CC_STRING("012345"), 3, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(CC_STRING("😀1😀3😀5"), 0, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("3😀5")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(CC_STRING("😀1😀3😀5"), 1, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("😀😀5")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(CC_STRING("😀1😀3😀5"), 3, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("😀1😀")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    CCString Str = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "012345");
    String = CCStringCreateWithoutRange(Str, 0, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(Str, 1, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("045")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(Str, 3, 3);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012")), @"Should create the correct string");
    
    CCStringDestroy(String);
    CCStringDestroy(Str);
    
    
    Str = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "012345");
    String = CCStringCreateWithoutRange(Str, 0, 2);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("2345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(Str, 1, 2);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("0345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithoutRange(Str, 4, 2);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("0123")), @"Should create the correct string");
    
    CCStringDestroy(String);
    CCStringDestroy(Str);
}

-(void) testInsertion
{
    CCString String = CCStringCreateByInsertingString(CC_STRING("012345"), 0, CC_STRING("abc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("abc012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING("012345"), 1, CC_STRING("abc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("0abc12345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING("012345"), 6, CC_STRING("abc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345abc")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING("😀😀😀😀😀😀"), 0, CC_STRING("abc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("abc😀😀😀😀😀😀")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING("😀😀😀😀😀😀"), 1, CC_STRING("abc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("😀abc😀😀😀😀😀")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING("😀😀😀😀😀😀"), 6, CC_STRING("abc"));
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("😀😀😀😀😀😀abc")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    CCString Str = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "012345");
    CCString Insert = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "abc");
    String = CCStringCreateByInsertingString(Str, 0, Insert);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("abc012345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(Str, 1, Insert);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("0abc12345")), @"Should create the correct string");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(Str, 6, Insert);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("012345abc")), @"Should create the correct string");
    
    CCStringDestroy(String);
    CCStringDestroy(Str);
    CCStringDestroy(Insert);
    
    
    String = CCStringCreateByInsertingString(CC_STRING_ENCODING(CCStringEncodingASCII, "12345678901234567890"), 0, CC_STRING_ENCODING(CCStringEncodingASCII, "123"));
    
    XCTAssertEqual(CCStringGetEncoding(String), CCStringEncodingASCII, @"Should use highest encoding");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING_ENCODING(CCStringEncodingASCII, "12345678901234567890"), 0, CC_STRING_ENCODING(CCStringEncodingUTF8, "123"));
    
    XCTAssertEqual(CCStringGetEncoding(String), CCStringEncodingUTF8, @"Should use highest encoding");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING_ENCODING(CCStringEncodingUTF8, "12345678901234567890"), 0, CC_STRING_ENCODING(CCStringEncodingASCII, "123"));
    
    XCTAssertEqual(CCStringGetEncoding(String), CCStringEncodingUTF8, @"Should use highest encoding");
    
    CCStringDestroy(String);
    
    
    String = CCStringCreateByInsertingString(CC_STRING_ENCODING(CCStringEncodingUTF8, "12345678901234567890"), 0, CC_STRING_ENCODING(CCStringEncodingUTF8, "123"));
    
    XCTAssertEqual(CCStringGetEncoding(String), CCStringEncodingUTF8, @"Should use highest encoding");
    
    CCStringDestroy(String);
}

-(void) testFindSubstring
{
    CCString String = [self createString];
    CCString Sub = CCStringCopySubstring(String, 1, 4);
    
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == SIZE_MAX, @"Should not find substring");
    
    CCStringDestroy(Sub);
    
    
    XCTAssertTrue(CCStringFindSubstring(String, 0, CC_STRING("aaaaaaaaaaaaaa")) == SIZE_MAX, @"Should not find substring");
    
    CCStringDestroy(String);
    
    
    String = CC_STRING("abbbbc");
    Sub = CC_STRING("bb");
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == 2, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 3, Sub) == 3, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 4, Sub) == SIZE_MAX, @"Should not find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 5, Sub) == SIZE_MAX, @"Should not find substring");
    
    
    String = CC_STRING("a😀😀😀😀c");
    Sub = CC_STRING("😀😀");
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == 2, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 3, Sub) == 3, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 4, Sub) == SIZE_MAX, @"Should not find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 5, Sub) == SIZE_MAX, @"Should not find substring");
    
    
    String = CC_STRING("a😀😀😀😀c");
    Sub = CC_STRING("😀");
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == 2, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 3, Sub) == 3, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 4, Sub) == 4, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 5, Sub) == SIZE_MAX, @"Should not find substring");
    
    
    String = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "abbbbc");
    Sub = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "bb");
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == 2, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 3, Sub) == 3, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 4, Sub) == SIZE_MAX, @"Should not find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 5, Sub) == SIZE_MAX, @"Should not find substring");
    CCStringDestroy(String);
    CCStringDestroy(Sub);
    
    
    String = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "a😀😀😀😀c");
    Sub = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "😀😀");
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == 2, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 3, Sub) == 3, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 4, Sub) == SIZE_MAX, @"Should not find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 5, Sub) == SIZE_MAX, @"Should not find substring");
    CCStringDestroy(String);
    CCStringDestroy(Sub);
    
    
    String = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "a😀😀😀😀c");
    Sub = CCStringCreate(CC_STD_ALLOCATOR, CCStringEncodingUTF8 | CCStringHintCopy, "😀");
    XCTAssertTrue(CCStringFindSubstring(String, 0, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 1, Sub) == 1, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 2, Sub) == 2, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 3, Sub) == 3, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 4, Sub) == 4, @"Should find substring");
    XCTAssertTrue(CCStringFindSubstring(String, 5, Sub) == SIZE_MAX, @"Should not find substring");
    CCStringDestroy(String);
    CCStringDestroy(Sub);
}

-(void) testCopySubstring
{
    CCString String = [self createString];
    char Buf[[self size] + 1];
    
    *CCStringCopyCharacters(String, 1, 4, Buf) = 0;
    
    CCString Result = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], Buf);
    CCString Sub = CCStringCopySubstring(String, 1, 4);
    
    XCTAssertTrue(CCStringEqual(Sub, Result), @"Should create the correct substring");
    
    CCStringDestroy(Sub);
    CCStringDestroy(Result);
    
    
    
    *CCStringCopyCharacters(String, 0, 2, Buf) = 0;
    
    Result = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], Buf);
    Sub = CCStringCopySubstring(String, 0, 2);
    
    XCTAssertTrue(CCStringEqual(Sub, Result), @"Should create the correct substring");
    
    CCStringDestroy(Sub);
    CCStringDestroy(Result);
    
    CCStringDestroy(String);
}

-(void) testConstantString
{
    XCTAssertFalse(CC_STRING("a") & 3, @"Should not be a tagged pointer");
    XCTAssertFalse(CC_STRING("a") & 3, @"Should not be a tagged pointer");
    XCTAssertFalse(CC_STRING("a") & 3, @"Should not be a tagged pointer");
    XCTAssertFalse(CC_STRING("a") & 3, @"Should not be a tagged pointer");
    XCTAssertFalse(CC_STRING("a") & 3, @"Should not be a tagged pointer");
    XCTAssertFalse(CC_STRING("a") & 3, @"Should not be a tagged pointer");
}

-(void) testCreateWithSize
{
    CCString String = CCStringCreateWithSize(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringEncodingASCII, "abcdef", 4);
    CCString Match = CC_STRING("abcd");
    CCString Copy = CCStringCopy(String);
    
    XCTAssertTrue(CCStringEqual(String, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(String), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(String), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(String), CCStringGetLength(Match), @"Should have the same length");
    
    XCTAssertTrue(CCStringEqual(Copy, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(Copy), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(Copy), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(Copy), CCStringGetLength(Match), @"Should have the same length");
    
    CC_STRING_TEMP_BUFFER(Buffer1, String) XCTAssertEqual(strlen(Buffer1), 4, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer2, Match) XCTAssertEqual(strlen(Buffer2), 4, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer3, Copy) XCTAssertEqual(strlen(Buffer3), 4, @"Should have the same length");
    
    CCStringDestroy(Copy);
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithSize(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "abcdef", 4);
    Copy = CCStringCopy(String);
    
    XCTAssertTrue(CCStringEqual(String, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(String), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(String), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(String), CCStringGetLength(Match), @"Should have the same length");
    
    XCTAssertTrue(CCStringEqual(Copy, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(Copy), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(Copy), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(Copy), CCStringGetLength(Match), @"Should have the same length");
    
    CC_STRING_TEMP_BUFFER(Buffer4, String) XCTAssertEqual(strlen(Buffer4), 4, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer5, Match) XCTAssertEqual(strlen(Buffer5), 4, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer6, Copy) XCTAssertEqual(strlen(Buffer6), 4, @"Should have the same length");
    
    CCStringDestroy(Copy);
    CCStringDestroy(String);
    
    
    
    
    String = CCStringCreateWithSize(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringEncodingASCII, "abcdefghijklmnopqrstuvwxyz", 20);
    Match = CC_STRING("abcdefghijklmnopqrst");
    Copy = CCStringCopy(String);
    
    XCTAssertTrue(CCStringEqual(String, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(String), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(String), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(String), CCStringGetLength(Match), @"Should have the same length");
    
    XCTAssertTrue(CCStringEqual(Copy, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(Copy), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(Copy), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(Copy), CCStringGetLength(Match), @"Should have the same length");
    
    CC_STRING_TEMP_BUFFER(Buffer7, String) XCTAssertEqual(strlen(Buffer7), 20, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer8, Match) XCTAssertEqual(strlen(Buffer8), 20, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer9, Copy) XCTAssertEqual(strlen(Buffer9), 20, @"Should have the same length");
    
    CCStringDestroy(Copy);
    CCStringDestroy(String);
    
    
    String = CCStringCreateWithSize(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "abcdefghijklmnopqrstuvwxyz", 20);
    Copy = CCStringCopy(String);
    
    XCTAssertTrue(CCStringEqual(String, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(String), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(String), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(String), CCStringGetLength(Match), @"Should have the same length");
    
    XCTAssertTrue(CCStringEqual(Copy, Match), @"Should be equal");
    XCTAssertEqual(CCStringGetHash(Copy), CCStringGetHash(Match), @"Should have the same hash");
    XCTAssertEqual(CCStringGetSize(Copy), CCStringGetSize(Match), @"Should have the same size");
    XCTAssertEqual(CCStringGetLength(Copy), CCStringGetLength(Match), @"Should have the same length");
    
    CC_STRING_TEMP_BUFFER(Buffer10, String) XCTAssertEqual(strlen(Buffer10), 20, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer11, Match) XCTAssertEqual(strlen(Buffer11), 20, @"Should have the same length");
    CC_STRING_TEMP_BUFFER(Buffer12, Copy) XCTAssertEqual(strlen(Buffer12), 20, @"Should have the same length");
    
    CCStringDestroy(Copy);
    CCStringDestroy(String);
}

-(void) testHash
{
    CCString String = [self createString];
    
    XCTAssertEqual(CCStringGetHash(String), [self getHash], @"Should get the correct hash");
    
    CCStringDestroy(String);
}

-(void) testCopy
{
    CCString String = [self createString];
    char Buf[[self size] + 1];
    
    *(char*)CCStringCopyCharacters(String, 0, 5, Buf) = 0;
    
    CCString s2 = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], Buf);
    XCTAssertTrue(CCStringEqual(String, s2), @"Should copy the full string");
    CCStringDestroy(s2);
    
    
    CC_STRING_TEMP_BUFFER(buffer, String)
    {
        CCString s2 = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], buffer);
        XCTAssertTrue(CCStringEqual(String, s2), @"Should copy the full string");
        CCStringDestroy(s2);
    }
    
    CCStringDestroy(String);
}

-(void) testSize
{
    CCString String = [self createString];
    
    XCTAssertEqual(CCStringGetSize(String), [self size], @"Should get the correct size");
    
    CCStringDestroy(String);
}

-(void) testLength
{
    CCString String = [self createString];
    
    XCTAssertEqual(CCStringGetLength(String), 5, @"Should get the correct length");
    
    CCStringDestroy(String);
}

-(void) testIndex
{
    CCString String = [self createString];
    
    XCTAssertEqual(CCStringGetCharacterAtIndex(String, 0), [self charAtIndex: 0], @"Should get the correct character");
    XCTAssertEqual(CCStringGetCharacterAtIndex(String, 1), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringGetCharacterAtIndex(String, 2), [self charAtIndex: 2], @"Should get the correct character");
    XCTAssertEqual(CCStringGetCharacterAtIndex(String, 3), [self charAtIndex: 3], @"Should get the correct character");
    XCTAssertEqual(CCStringGetCharacterAtIndex(String, 4), [self charAtIndex: 4], @"Should get the correct character");
    
    CCStringDestroy(String);
}

-(void) testPrefix
{
    CCString String = [self createString];
    
    XCTAssertTrue(CCStringHasPrefix(String, String), @"Should have the prefix");
    XCTAssertTrue(CCStringHasPrefix(String, CC_STRING("h")), @"Should have the prefix");
    XCTAssertFalse(CCStringHasPrefix(String, CC_STRING("H")), @"Should not have the prefix");
    XCTAssertFalse(CCStringHasPrefix(String, CC_STRING("hi")), @"Should not have the prefix");
    
    
    char Buf[[self size] + 1];
    
    *(char*)CCStringCopyCharacters(String, 0, 2, Buf) = 0;
    
    CCString s2 = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], Buf);
    XCTAssertFalse(CCStringEqual(String, s2), @"Should not be equal");
    XCTAssertTrue(CCStringHasPrefix(String, s2), @"Should have the prefix");
    CCStringDestroy(s2);
    
    
    CCStringDestroy(String);
}

-(void) testSuffix
{
    CCString String = [self createString];
    
    XCTAssertTrue(CCStringHasSuffix(String, String), @"Should have the suffix");
    XCTAssertFalse(CCStringHasSuffix(String, CC_STRING("hi")), @"Should not have the suffix");
    
    
    char Buf[[self size] + 1];
    
    *(char*)CCStringCopyCharacters(String, 3, 2, Buf) = 0;
    
    CCString s2 = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], Buf);
    XCTAssertFalse(CCStringEqual(String, s2), @"Should not be equal");
    XCTAssertTrue(CCStringHasSuffix(String, s2), @"Should have the suffix");
    CCStringDestroy(s2);
    
    
    CCStringDestroy(String);
}

-(void) testEquality
{
    CCString s1 = [self createString];
    
    CCString s2 = [self createString];
    XCTAssertTrue(CCStringEqual(s1, s2), @"Should be equal");
    CCStringDestroy(s2);
    
    s2 = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "blah!");
    XCTAssertFalse(CCStringEqual(s1, s2), @"Should not be equal");
    CCStringDestroy(s2);
    
    
    CCStringEncoding Encoding[3];
    const CCStringMap *Maps[3] = {
        CCStringGetMap(CCStringMapSet127, Encoding),
        CCStringGetMap(CCStringMapSet63, &Encoding[1]),
        CCStringGetMap(CCStringMapSet31, &Encoding[2])
    };
    
    CCStringRegisterMap(CCStringEncodingUTF8, (CCStringMap[31]){}, CCStringMapSet31);
    CCStringRegisterMap(CCStringEncodingUTF8, (CCStringMap[63]){}, CCStringMapSet63);
    CCStringRegisterMap(CCStringEncodingUTF8, (CCStringMap[127]){}, CCStringMapSet127);
    
    s2 = [self createString];
    
    CCStringRegisterMap(Encoding[2], Maps[2], CCStringMapSet31);
    CCStringRegisterMap(Encoding[1], Maps[1], CCStringMapSet63);
    CCStringRegisterMap(Encoding[0], Maps[0], CCStringMapSet127);
    
    XCTAssertTrue(CCStringEqual(s1, s2), @"Should be equal");
    CCStringDestroy(s2);
    
    
    CCStringRegisterMap(CCStringEncodingUTF8, (CCStringMap[31]){}, CCStringMapSet31);
    CCStringRegisterMap(CCStringEncodingUTF8, (CCStringMap[63]){}, CCStringMapSet63);
    CCStringRegisterMap(CCStringEncodingUTF8, (CCStringMap[127]){}, CCStringMapSet127);
    
    s2 = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "blah!");
    
    CCStringRegisterMap(Encoding[2], Maps[2], CCStringMapSet31);
    CCStringRegisterMap(Encoding[1], Maps[1], CCStringMapSet63);
    CCStringRegisterMap(Encoding[0], Maps[0], CCStringMapSet127);
    
    XCTAssertFalse(CCStringEqual(s1, s2), @"Should not be equal");
    CCStringDestroy(s2);
    
    
    CCStringDestroy(s1);
}

-(void) testEnumerating
{
    CCString String = [self createString];
    
    CCEnumerator Enumerator;
    CCStringGetEnumerator(String, &Enumerator);
    
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 0, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 0], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorNext(&Enumerator), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 1, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorNext(&Enumerator), [self charAtIndex: 2], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 2, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 2], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorPrevious(&Enumerator), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 1, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetTail(&Enumerator), [self charAtIndex: 4], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 4, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 4], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorPrevious(&Enumerator), [self charAtIndex: 3], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 3, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 3], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorNext(&Enumerator), [self charAtIndex: 4], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 4, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 4], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetHead(&Enumerator), [self charAtIndex: 0], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 0, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 0], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorNext(&Enumerator), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 1, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 1], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorPrevious(&Enumerator), [self charAtIndex: 0], @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), 0, @"Should get the correct index");
    XCTAssertEqual(CCStringEnumeratorGetCurrent(&Enumerator), [self charAtIndex: 0], @"Should get the correct character");
    
    CCStringEnumeratorGetHead(&Enumerator);
    XCTAssertEqual(CCStringEnumeratorPrevious(&Enumerator), 0, @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), SIZE_MAX, @"Should get the correct index");
    CCStringEnumeratorGetTail(&Enumerator);
    XCTAssertEqual(CCStringEnumeratorNext(&Enumerator), 0, @"Should get the correct character");
    XCTAssertEqual(CCStringEnumeratorGetIndex(&Enumerator), SIZE_MAX, @"Should get the correct index");
    
    size_t Index = 0;
    CC_STRING_FOREACH(c, String)
    {
        XCTAssertEqual(c, [self charAtIndex: Index], @"Should get the correct character");
        Index++;
    }
    
    CCStringDestroy(String);
}

@end


@interface StringUTF8Tests : StringTests
@end

@implementation StringUTF8Tests

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], "h😀lLo");
}

-(size_t) size
{
    return 8;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', L'😀', 'l', 'L', 'o' }[index];
}

-(CCStringEncoding) encoding
{
    return CCStringEncodingUTF8;
}

-(uint32_t) getHash
{
    return 0xf27eeece;
}

@end


static uint32_t StringConstantTestsHash = 0xbf59bfa4;
@interface StringConstantTests : StringTests
@end

@implementation StringConstantTests

static CCString StringConstantTestsString = CC_STRING("h😀lL😁");
-(CCString) createString
{
    return StringConstantTestsString;
}

-(size_t) size
{
    return 11;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', L'😀', 'l', 'L', L'😁' }[index];
}

-(CCStringEncoding) encoding
{
    return CCStringEncodingUTF8;
}

-(uint32_t) getHash
{
    return StringConstantTestsHash;
}

@end


@interface StringTaggedTests : StringTests

-(CCString) taggedString;

@end

@implementation StringTaggedTests

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], "helLo");
}

-(size_t) size
{
    return 5;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', 'e', 'l', 'L', 'o' }[index];
}

-(CCString) taggedString
{
    return 0x1be66ccba1;
}

-(CCStringEncoding) encoding
{
    return CCStringEncodingASCII;
}

-(void) testTag
{
    CCString String = [self createString];
    
    XCTAssertTrue(String & 3, @"Should be a tagged string");
    XCTAssertEqual(String, [self taggedString], @"Should equal the string");
    
    CCStringDestroy(String);
}

@end


@interface StringTaggedUTF8Tests : StringTaggedTests
@end

@implementation StringTaggedUTF8Tests

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], "helLo");
}

-(size_t) size
{
    return 5;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', 'e', 'l', 'L', 'o' }[index];
}

-(CCString) taggedString
{
    return 0x1be66ccba1;
}

-(CCStringEncoding) encoding
{
    return CCStringEncodingUTF8;
}

@end


@interface StringTaggedCustomTests : StringTaggedTests
@end

@implementation StringTaggedCustomTests

-(void) setUp
{
    [super setUp];
    
    static CCStringMap Map31[31] = { 0, L'😀', L'😁', 'h', 'l', 'L' };
    CCStringRegisterMap(CCStringEncodingUTF8, Map31, CCStringMapSet31);
}

-(void) tearDown
{
    [super tearDown];
    
    CCStringRegisterMap(0, NULL, CCStringMapSet31);
}

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)[self encoding], "h😀lL😁");
}

-(size_t) size
{
    return 11;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', L'😀', 'l', 'L', L'😁' }[index];
}

-(CCString) taggedString
{
    return 0x8a408f;
}

-(CCStringEncoding) encoding
{
    return CCStringEncodingUTF8;
}

-(uint32_t) getHash
{
    return StringConstantTestsHash;
}

@end
