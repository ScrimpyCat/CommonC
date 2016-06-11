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
#import "HashMap.h"
#import "HashMapSeparateChainingArrayDataOrientedAll.h"
#import "CCString.h"

@interface HashMapTests : XCTestCase

-(const CCHashMapInterface*) interface;

@end

static uintmax_t StringHasher(CCString *Key)
{
    return CCStringGetHash(*Key);
}

static CCComparisonResult StringComparator(CCString *left, CCString *right)
{
    return CCStringEqual(*left, *right) ? CCComparisonResultEqual : CCComparisonResultInvalid ;
}

@implementation HashMapTests

-(const CCHashMapInterface*) interface
{
    return CCHashMapSeparateChainingArrayDataOrientedAll;
}

-(void) testStoring
{
    CCHashMap Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uintmax_t), sizeof(int), 3, NULL, NULL, [self interface]);
    
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 1 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 2 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 5 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 100 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 200 });
    CCHashMapSetValue(Map, &(uintmax_t){ 3 }, &(int){ 300 });
    CCHashMapSetValue(Map, &(uintmax_t){ 4 }, &(int){ 400 });
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 500 });
    
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 101 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 202 });
    CCHashMapSetValue(Map, &(uintmax_t){ 3 }, &(int){ 303 });
    CCHashMapSetValue(Map, &(uintmax_t){ 4 }, &(int){ 404 });
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 3 }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 4 }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    CCHashMapDestroy(Map);
    
    
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uint8_t), sizeof(int), 3, NULL, NULL, [self interface]);
    
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 1 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 2 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 3 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 4 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 5 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    CCHashMapSetValue(Map, &(uint8_t){ 1 }, &(int){ 100 });
    CCHashMapSetValue(Map, &(uint8_t){ 2 }, &(int){ 200 });
    CCHashMapSetValue(Map, &(uint8_t){ 3 }, &(int){ 300 });
    CCHashMapSetValue(Map, &(uint8_t){ 4 }, &(int){ 400 });
    CCHashMapSetValue(Map, &(uint8_t){ 5 }, &(int){ 500 });
    
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    CCHashMapSetValue(Map, &(uint8_t){ 1 }, &(int){ 101 });
    CCHashMapSetValue(Map, &(uint8_t){ 2 }, &(int){ 202 });
    CCHashMapSetValue(Map, &(uint8_t){ 3 }, &(int){ 303 });
    CCHashMapSetValue(Map, &(uint8_t){ 4 }, &(int){ 404 });
    CCHashMapSetValue(Map, &(uint8_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 3 }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 4 }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    CCHashMapDestroy(Map);
    
    
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(CCString), sizeof(int), 3, (CCHashMapKeyHasher)StringHasher, (CCComparator)StringComparator, [self interface]);
    
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("0") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("6") }), NULL, @"Should not contain a value for the key");
    
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("1") }, &(int){ 100 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("2") }, &(int){ 200 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("3") }, &(int){ 300 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("4") }, &(int){ 400 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("5") }, &(int){ 500 });
    
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("0") }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("6") }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), 500, @"Should contain the correct value for the key");
    
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("1") }, &(int){ 101 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("2") }, &(int){ 202 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("3") }, &(int){ 303 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("4") }, &(int){ 404 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("5") }, &(int){ 505 });
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), 505, @"Should contain the correct value for the key");
    
    CCHashMapDestroy(Map);
}

@end
