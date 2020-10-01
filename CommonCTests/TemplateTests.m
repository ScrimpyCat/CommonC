/*
 *  Copyright (c) 2020, Stefan Johnson
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
#import <XCTest/XCTest.h>
#import "Extensions.h"
#import "Hacks.h"
#import "Template.h"

@interface TemplateTests : XCTestCase
@end

@implementation TemplateTests

#define STR(x) STR_(x)
#define STR_(x) [NSString stringWithUTF8String: #x]

-(void) testExtractingTypes
{
#define EXTRACT(...) STR(CC_TYPE(__VA_ARGS__))
    
    XCTAssertEqualObjects(EXTRACT(int), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(int var), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(const int), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(static const int), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(int, float), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(float, int), @"float", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(_Atomic int), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT((int)), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(_Atomic(int)), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(static _Atomic(const int)), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(static (_Atomic(const int))), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(_Alignas(float) int), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(TYPE(foo)), @"TYPE(foo)", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(TYPE(foo) var), @"TYPE(foo)", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(PTYPE(int) *), @"PTYPE(int)", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(FPTYPE(int(*)(int, int))), @"FPTYPE(int(*)(int, int))", @"should have correct value");
}

-(void) testManglingTypes
{
#define MANGLE(...) STR(CC_MANGLE_TYPE(__VA_ARGS__))
    
    XCTAssertEqualObjects(MANGLE(int), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(int var), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(PTYPE(int)), @"pI32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(PTYPE(PTYPE(int))), @"ppI32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(TYPE(int)), @"int", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, float))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(void(*)(void))(*)(int))), @"fp1fp1V_V_I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, FPTYPE(void(*)(void))))), @"fp2I32_I32_fp1V_V", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, FPTYPE(FPTYPE(char(*)(PTYPE(char)*))(*)(void))))), @"fp2I32_I32_fp1fp1I8_pI8_V", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(const int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
}

@end
