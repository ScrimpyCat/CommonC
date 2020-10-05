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

#define STR(...) STR_(__VA_ARGS__)
#define STR_(...) [NSString stringWithUTF8String: #__VA_ARGS__]

-(void) testExtractingTypes
{
#define EXTRACT(...) STR(CC_TYPE(__VA_ARGS__))
    
    XCTAssertEqualObjects(EXTRACT(int), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(int var), @"int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(unsigned), @"unsigned_", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(unsigned int), @"unsigned_int", @"should have correct value");
    XCTAssertEqualObjects(EXTRACT(signed int), @"signed_int", @"should have correct value");
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
    
#define PRESERVE(...) STR(CC_PRESERVE_TYPE(__VA_ARGS__))
    
    XCTAssertEqualObjects(PRESERVE(int), @"int,", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(int var), @"int, var", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(unsigned int), @"unsigned int, , int, int", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(signed int), @"signed int, , int, int", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(const int), @"int, , int", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(static const int), @"int, , int, const int", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(int, float), @"int,", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(float, int), @"float,", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(_Atomic int), @"int, , int", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE((int)), @"int,", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(_Atomic(int)), @"int, , (int)", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(static _Atomic(const int)), @"int, , int, (const int), _Atomic(const int)", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(static (_Atomic(const int))), @"int, , int, (const int), (_Atomic(const int))", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(_Alignas(float) int), @"int, , int", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(TYPE(foo)), @"TYPE(foo), , foo,", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(TYPE(foo) var), @"TYPE(foo), var, foo, var", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(PTYPE(int) *), @"PTYPE(int), *, int, *", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(FPTYPE(int(*)(int, int))), @"FPTYPE(int(*)(int, int)), , int(*)(int, int),", @"should have correct value");
    XCTAssertEqualObjects(PRESERVE(FPTYPE(unsigned int(*)(int, int))), @"FPTYPE(unsigned int(*)(int, int)), , unsigned int(*)(int, int),", @"should have correct value");
}

-(void) testManglingTypes
{
#define MANGLE(...) STR(CC_MANGLE_TYPE(__VA_ARGS__))
    
    XCTAssertEqualObjects(MANGLE(int), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(int var), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned int), @"U32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned), @"U32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned int(*)(void))), @"fp1U32_V", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(PTYPE(int)), @"pI32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(PTYPE(PTYPE(int))), @"ppI32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, float))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(void(*)(void))(*)(int))), @"fp1fp1V_V_I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, FPTYPE(void(*)(void))))), @"fp2I32_I32_fp1V_V", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, FPTYPE(FPTYPE(char(*)(PTYPE(char)*))(*)(void))))), @"fp2I32_I32_fp1fp1I8_pI8_V", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int, FPTYPE(FPTYPE(char(*)(PTYPE(char*)))(*)(void))))), @"fp2I32_I32_fp1fp1I8_pI8_V", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(const int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(const _Alignas(char) int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(const int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(const _Alignas(char) int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(const _Atomic int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned(*)(int a, float b))), @"fp2U32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned(*)(void))(*)(int a, float b))), @"fp2fp1U32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(static _Alignas(int) _Atomic unsigned char v), @"U8", @"should have correct value");
    
    XCTAssertEqualObjects(MANGLE(char), @"I8", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed char), @"I8", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned char), @"U8", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(char(*)(int a, float b))), @"fp2I8_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(char(*)(void))(*)(int a, float b))), @"fp2fp1I8_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(char(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I8_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed char(*)(int a, float b))), @"fp2I8_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed char(*)(void))(*)(int a, float b))), @"fp2fp1I8_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed char(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I8_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned char(*)(int a, float b))), @"fp2U8_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned char(*)(void))(*)(int a, float b))), @"fp2fp1U8_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned char(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U8_V_V_I32_F32", @"should have correct value");
    
    XCTAssertEqualObjects(MANGLE(short), @"I16", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed short), @"I16", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned short), @"U16", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(short(*)(int a, float b))), @"fp2I16_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(short(*)(void))(*)(int a, float b))), @"fp2fp1I16_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(short(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I16_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed short(*)(int a, float b))), @"fp2I16_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed short(*)(void))(*)(int a, float b))), @"fp2fp1I16_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed short(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I16_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned short(*)(int a, float b))), @"fp2U16_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned short(*)(void))(*)(int a, float b))), @"fp2fp1U16_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned short(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U16_V_V_I32_F32", @"should have correct value");
    
    XCTAssertEqualObjects(MANGLE(int), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed int), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned int), @"U32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(int(*)(void))(*)(int a, float b))), @"fp2fp1I32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(int(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed int(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed int(*)(void))(*)(int a, float b))), @"fp2fp1I32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed int(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned int(*)(int a, float b))), @"fp2U32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned int(*)(void))(*)(int a, float b))), @"fp2fp1U32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned int(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U32_V_V_I32_F32", @"should have correct value");
    
#if ULONG_MAX == UINT32_MAX
    XCTAssertEqualObjects(MANGLE(long), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed long), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned long), @"U32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(long(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(long(*)(void))(*)(int a, float b))), @"fp2fp1I32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed long(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed long(*)(void))(*)(int a, float b))), @"fp2fp1I32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned long(*)(int a, float b))), @"fp2U32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned long(*)(void))(*)(int a, float b))), @"fp2fp1U32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U32_V_V_I32_F32", @"should have correct value");
#elif ULONG_MAX == UINT64_MAX
    XCTAssertEqualObjects(MANGLE(long), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed long), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned long), @"U64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(long(*)(int a, float b))), @"fp2I64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(long(*)(void))(*)(int a, float b))), @"fp2fp1I64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I64_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed long(*)(int a, float b))), @"fp2I64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed long(*)(void))(*)(int a, float b))), @"fp2fp1I64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I64_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned long(*)(int a, float b))), @"fp2U64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned long(*)(void))(*)(int a, float b))), @"fp2fp1U64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U64_V_V_I32_F32", @"should have correct value");
#endif
    
#if ULLONG_MAX == UINT32_MAX
    XCTAssertEqualObjects(MANGLE(long long), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed long long), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned long long), @"U32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(long long(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(long long(*)(void))(*)(int a, float b))), @"fp2fp1I32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(long long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed long long(*)(int a, float b))), @"fp2I32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed long long(*)(void))(*)(int a, float b))), @"fp2fp1I32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed long long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned long long(*)(int a, float b))), @"fp2U32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned long long(*)(void))(*)(int a, float b))), @"fp2fp1U32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned long long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U32_V_V_I32_F32", @"should have correct value");
#elif ULLONG_MAX == UINT64_MAX
    XCTAssertEqualObjects(MANGLE(long long), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(signed long long), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(unsigned long long), @"U64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(long long(*)(int a, float b))), @"fp2I64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(long long(*)(void))(*)(int a, float b))), @"fp2fp1I64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(long long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I64_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(signed long long(*)(int a, float b))), @"fp2I64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(signed long long(*)(void))(*)(int a, float b))), @"fp2fp1I64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(signed long long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1I64_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(unsigned long long(*)(int a, float b))), @"fp2U64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(unsigned long long(*)(void))(*)(int a, float b))), @"fp2fp1U64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(unsigned long long(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1U64_V_V_I32_F32", @"should have correct value");
#endif
    
    XCTAssertEqualObjects(MANGLE(float), @"F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(double), @"F64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(long double), @"F80", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(float(*)(int a, float b))), @"fp2F32_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(float(*)(void))(*)(int a, float b))), @"fp2fp1F32_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(float(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1F32_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(double(*)(int a, float b))), @"fp2F64_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(double(*)(void))(*)(int a, float b))), @"fp2fp1F64_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(double(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1F64_V_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(long double(*)(int a, float b))), @"fp2F80_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(long double(*)(void))(*)(int a, float b))), @"fp2fp1F80_V_I32_F32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(FPTYPE(FPTYPE(FPTYPE(long double(*)(void))(*)(void))(*)(int a, float b))), @"fp2fp1fp1F80_V_V_I32_F32", @"should have correct value");
    
    XCTAssertEqualObjects(MANGLE(int8_t), @"I8", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uint8_t), @"U8", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(int16_t), @"I16", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uint16_t), @"U16", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(int32_t), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uint32_t), @"U32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(int64_t), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uint64_t), @"U64", @"should have correct value");
    
#if SIZE_MAX == UINT32_MAX
    XCTAssertEqualObjects(MANGLE(size_t), @"U32", @"should have correct value");
#elif SIZE_MAX == UINT64_MAX
    XCTAssertEqualObjects(MANGLE(size_t), @"U64", @"should have correct value");
#endif
    
#if UINTMAX_MAX == UINT32_MAX
    XCTAssertEqualObjects(MANGLE(intmax_t), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uintmax_t), @"U32", @"should have correct value");
#elif UINTMAX_MAX == UINT64_MAX
    XCTAssertEqualObjects(MANGLE(intmax_t), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uintmax_t), @"U64", @"should have correct value");
#endif
    
#if UINTPTR_MAX == UINT32_MAX
    XCTAssertEqualObjects(MANGLE(intptr_t), @"I32", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uintptr_t), @"U32", @"should have correct value");
#elif UINTPTR_MAX == UINT64_MAX
    XCTAssertEqualObjects(MANGLE(intptr_t), @"I64", @"should have correct value");
    XCTAssertEqualObjects(MANGLE(uintptr_t), @"U64", @"should have correct value");
#endif
    
#if PTRDIFF_MAX == UINT32_MAX
    XCTAssertEqualObjects(MANGLE(ptrdiff_t), @"I32", @"should have correct value");
#elif PTRDIFF_MAX == UINT64_MAX
    XCTAssertEqualObjects(MANGLE(ptrdiff_t), @"I64", @"should have correct value");
#endif
}

@end
