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

@end

@implementation StringTests
{
    char prevLocale[256];
}

-(void) setUp
{
    [super setUp];
    
    sprintf(prevLocale, "%.255s", setlocale(LC_ALL, NULL));
    setlocale(LC_ALL, "en_US.UTF-8");
}

-(void) tearDown
{
    [super tearDown];
    
    setlocale(LC_ALL, prevLocale);
}

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "helLo");
}

-(size_t) size
{
    return 5;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', 'e', 'l', 'L', 'o' }[index];
}

-(void) testSize
{
    CCString String = [self createString];
    
    XCTAssertEqual(CCStringGetSize(String), [self size], @"Should get the correct index");
    
    CCStringDestroy(String);
}

-(void) testLength
{
    CCString String = [self createString];
    
    XCTAssertEqual(CCStringGetLength(String), 5, @"Should get the correct index");
    
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
    
    CCStringDestroy(String);
}

@end


@interface StringUTF8Tests : StringTests
@end

@implementation StringUTF8Tests

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, "h😀lLo");
}

-(size_t) size
{
    return 8;
}

-(CCChar) charAtIndex: (size_t)index
{
    return (CCChar[]){ 'h', L'😀', 'l', 'L', 'o' }[index];
}

@end


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

@end


@interface StringTaggedTests : StringTests

-(CCString) taggedString;

@end

@implementation StringTaggedTests

-(CCString) createString
{
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingASCII, "helLo");
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
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, "helLo");
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
    return CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, "h😀lL😁");
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

@end
