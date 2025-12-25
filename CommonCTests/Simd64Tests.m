/*
 *  Copyright (c) 2025, Stefan Johnson
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

#define CC_SIMD_COMPATIBILITY 1
#import "Simd.h"

@interface Simd64Tests : XCTestCase
@end

@implementation Simd64Tests

-(void) testLoadStore
{
    int8_t Result_s8[8];
    CCSimd_s8x8 Vec_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    CCSimdStore_s8x8(Result_s8, Vec_s8x8);
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 5, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 7, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 1), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 2), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 3), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 4), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 5), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 6), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 7), 7, @"should contain the correct value");
    
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 0, 8);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 1, 9);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 2, 10);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 3, 11);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 4, 12);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 5, 13);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 6, 14);
    Vec_s8x8 = CCSimdSet_s8x8(Vec_s8x8, 7, 15);
    
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 1), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 3), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 4), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 5), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 6), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Vec_s8x8, 7), 15, @"should contain the correct value");
    
    CCSimd_s8x8x2 Poly_s8x8x2 = CCSimdInterleaveLoad_s8x8x2((int8_t[16]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 2), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 3), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 4), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 5), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 6), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[0], 7), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 2), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 3), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 4), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 5), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 6), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x2.v[1], 7), 15, @"should contain the correct value");
    
    Poly_s8x8x2.v[0] = CCSimdLoad_s8x8((int8_t[8]){ 10, 12, 14, 16, 18, 20, 22, 24 });
    Poly_s8x8x2.v[1] = CCSimdLoad_s8x8((int8_t[8]){ 11, 13, 15, 17, 19, 21, 23, 25 });
    int8_t Result2_s8[16];
    
    CCSimdInterleaveStore_s8x8x2(Result2_s8, Poly_s8x8x2);
    XCTAssertEqual(Result2_s8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result2_s8[15], 25, @"should contain the correct value");
    
    CCSimd_s8x8x3 Poly_s8x8x3 = CCSimdInterleaveLoad_s8x8x3((int8_t[24]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 });
    
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 2), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 3), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 4), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 5), 15, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 6), 18, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[0], 7), 21, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 2), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 3), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 4), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 5), 16, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 6), 19, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[1], 7), 22, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 3), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 4), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 5), 17, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 6), 20, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x3.v[2], 7), 23, @"should contain the correct value");
    
    Poly_s8x8x3.v[0] = CCSimdLoad_s8x8((int8_t[8]){ 10, 13, 16, 19, 22, 25, 28, 31 });
    Poly_s8x8x3.v[1] = CCSimdLoad_s8x8((int8_t[8]){ 11, 14, 17, 20, 23, 26, 29, 32 });
    Poly_s8x8x3.v[2] = CCSimdLoad_s8x8((int8_t[8]){ 12, 15, 18, 21, 24, 27, 30, 33 });
    int8_t Result3_s8[24];
    
    CCSimdInterleaveStore_s8x8x3(Result3_s8, Poly_s8x8x3);
    XCTAssertEqual(Result3_s8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[15], 25, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[16], 26, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[17], 27, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[18], 28, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[19], 29, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[20], 30, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[21], 31, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[22], 32, @"should contain the correct value");
    XCTAssertEqual(Result3_s8[23], 33, @"should contain the correct value");
    
    CCSimd_s8x8x4 Poly_s8x8x4 = CCSimdInterleaveLoad_s8x8x4((int8_t[32]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 });
    
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 3), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 4), 16, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 5), 20, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 6), 24, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[0], 7), 28, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 2), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 3), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 4), 17, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 5), 21, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 6), 25, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[1], 7), 29, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 3), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 4), 18, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 5), 22, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 6), 26, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[2], 7), 30, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 1), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 2), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 3), 15, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 4), 19, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 5), 23, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 6), 27, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s8x8(Poly_s8x8x4.v[3], 7), 31, @"should contain the correct value");
    
    Poly_s8x8x4.v[0] = CCSimdLoad_s8x8((int8_t[8]){ 10, 14, 18, 22, 26, 30, 34, 38 });
    Poly_s8x8x4.v[1] = CCSimdLoad_s8x8((int8_t[8]){ 11, 15, 19, 23, 27, 31, 35, 39 });
    Poly_s8x8x4.v[2] = CCSimdLoad_s8x8((int8_t[8]){ 12, 16, 20, 24, 28, 32, 36, 40 });
    Poly_s8x8x4.v[3] = CCSimdLoad_s8x8((int8_t[8]){ 13, 17, 21, 25, 29, 33, 37, 41 });
    int8_t Result4_s8[32];
    
    CCSimdInterleaveStore_s8x8x4(Result4_s8, Poly_s8x8x4);
    XCTAssertEqual(Result4_s8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[15], 25, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[16], 26, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[17], 27, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[18], 28, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[19], 29, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[20], 30, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[21], 31, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[22], 32, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[23], 33, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[24], 34, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[25], 35, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[26], 36, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[27], 37, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[28], 38, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[29], 39, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[30], 40, @"should contain the correct value");
    XCTAssertEqual(Result4_s8[31], 41, @"should contain the correct value");
    
    
    uint8_t Result_u8[8];
    CCSimd_u8x8 Vec_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    CCSimdStore_u8x8(Result_u8, Vec_u8x8);
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 7, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 1), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 2), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 3), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 4), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 5), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 6), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 7), 7, @"should contain the correct value");
    
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 0, 8);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 1, 9);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 2, 10);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 3, 11);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 4, 12);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 5, 13);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 6, 14);
    Vec_u8x8 = CCSimdSet_u8x8(Vec_u8x8, 7, 15);
    
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 1), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 3), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 4), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 5), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 6), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Vec_u8x8, 7), 15, @"should contain the correct value");
    
    CCSimd_u8x8x2 Poly_u8x8x2 = CCSimdInterleaveLoad_u8x8x2((uint8_t[16]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 2), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 3), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 4), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 5), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 6), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[0], 7), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 2), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 3), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 4), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 5), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 6), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x2.v[1], 7), 15, @"should contain the correct value");
    
    Poly_u8x8x2.v[0] = CCSimdLoad_u8x8((uint8_t[8]){ 10, 12, 14, 16, 18, 20, 22, 24 });
    Poly_u8x8x2.v[1] = CCSimdLoad_u8x8((uint8_t[8]){ 11, 13, 15, 17, 19, 21, 23, 25 });
    uint8_t Result2_u8[16];
    
    CCSimdInterleaveStore_u8x8x2(Result2_u8, Poly_u8x8x2);
    XCTAssertEqual(Result2_u8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result2_u8[15], 25, @"should contain the correct value");
    
    CCSimd_u8x8x3 Poly_u8x8x3 = CCSimdInterleaveLoad_u8x8x3((uint8_t[24]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 });
    
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 2), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 3), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 4), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 5), 15, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 6), 18, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[0], 7), 21, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 2), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 3), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 4), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 5), 16, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 6), 19, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[1], 7), 22, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 3), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 4), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 5), 17, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 6), 20, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x3.v[2], 7), 23, @"should contain the correct value");
    
    Poly_u8x8x3.v[0] = CCSimdLoad_u8x8((uint8_t[8]){ 10, 13, 16, 19, 22, 25, 28, 31 });
    Poly_u8x8x3.v[1] = CCSimdLoad_u8x8((uint8_t[8]){ 11, 14, 17, 20, 23, 26, 29, 32 });
    Poly_u8x8x3.v[2] = CCSimdLoad_u8x8((uint8_t[8]){ 12, 15, 18, 21, 24, 27, 30, 33 });
    uint8_t Result3_u8[24];
    
    CCSimdInterleaveStore_u8x8x3(Result3_u8, Poly_u8x8x3);
    XCTAssertEqual(Result3_u8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[15], 25, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[16], 26, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[17], 27, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[18], 28, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[19], 29, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[20], 30, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[21], 31, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[22], 32, @"should contain the correct value");
    XCTAssertEqual(Result3_u8[23], 33, @"should contain the correct value");
    
    CCSimd_u8x8x4 Poly_u8x8x4 = CCSimdInterleaveLoad_u8x8x4((uint8_t[32]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 });
    
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 3), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 4), 16, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 5), 20, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 6), 24, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[0], 7), 28, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 2), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 3), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 4), 17, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 5), 21, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 6), 25, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[1], 7), 29, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 3), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 4), 18, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 5), 22, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 6), 26, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[2], 7), 30, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 1), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 2), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 3), 15, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 4), 19, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 5), 23, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 6), 27, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u8x8(Poly_u8x8x4.v[3], 7), 31, @"should contain the correct value");
    
    Poly_u8x8x4.v[0] = CCSimdLoad_u8x8((uint8_t[8]){ 10, 14, 18, 22, 26, 30, 34, 38 });
    Poly_u8x8x4.v[1] = CCSimdLoad_u8x8((uint8_t[8]){ 11, 15, 19, 23, 27, 31, 35, 39 });
    Poly_u8x8x4.v[2] = CCSimdLoad_u8x8((uint8_t[8]){ 12, 16, 20, 24, 28, 32, 36, 40 });
    Poly_u8x8x4.v[3] = CCSimdLoad_u8x8((uint8_t[8]){ 13, 17, 21, 25, 29, 33, 37, 41 });
    uint8_t Result4_u8[32];
    
    CCSimdInterleaveStore_u8x8x4(Result4_u8, Poly_u8x8x4);
    XCTAssertEqual(Result4_u8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[15], 25, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[16], 26, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[17], 27, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[18], 28, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[19], 29, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[20], 30, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[21], 31, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[22], 32, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[23], 33, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[24], 34, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[25], 35, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[26], 36, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[27], 37, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[28], 38, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[29], 39, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[30], 40, @"should contain the correct value");
    XCTAssertEqual(Result4_u8[31], 41, @"should contain the correct value");
    
    
    int16_t Result_s16[4];
    CCSimd_s16x4 Vec_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 0, 1, 2, 3 });
    
    CCSimdStore_s16x4(Result_s16, Vec_s16x4);
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 3, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 1), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 2), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 3), 3, @"should contain the correct value");
    
    Vec_s16x4 = CCSimdSet_s16x4(Vec_s16x4, 0, 8);
    Vec_s16x4 = CCSimdSet_s16x4(Vec_s16x4, 1, 9);
    Vec_s16x4 = CCSimdSet_s16x4(Vec_s16x4, 2, 10);
    Vec_s16x4 = CCSimdSet_s16x4(Vec_s16x4, 3, 11);
    
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 1), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Vec_s16x4, 3), 11, @"should contain the correct value");
    
    CCSimd_s16x4x2 Poly_s16x4x2 = CCSimdInterleaveLoad_s16x4x2((int16_t[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[0], 2), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[0], 3), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[1], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[1], 2), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x2.v[1], 3), 7, @"should contain the correct value");
    
    Poly_s16x4x2.v[0] = CCSimdLoad_s16x4((int16_t[4]){ 10, 12, 14, 16 });
    Poly_s16x4x2.v[1] = CCSimdLoad_s16x4((int16_t[4]){ 11, 13, 15, 17 });
    int16_t Result2_s16[8];
    
    CCSimdInterleaveStore_s16x4x2(Result2_s16, Poly_s16x4x2);
    XCTAssertEqual(Result2_s16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result2_s16[7], 17, @"should contain the correct value");
    
    CCSimd_s16x4x3 Poly_s16x4x3 = CCSimdInterleaveLoad_s16x4x3((int16_t[12]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
    
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[0], 2), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[0], 3), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[1], 2), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[1], 3), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[2], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[2], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x3.v[2], 3), 11, @"should contain the correct value");
    
    Poly_s16x4x3.v[0] = CCSimdLoad_s16x4((int16_t[4]){ 10, 13, 16, 19 });
    Poly_s16x4x3.v[1] = CCSimdLoad_s16x4((int16_t[4]){ 11, 14, 17, 20 });
    Poly_s16x4x3.v[2] = CCSimdLoad_s16x4((int16_t[4]){ 12, 15, 18, 21 });
    int16_t Result3_s16[12];
    
    CCSimdInterleaveStore_s16x4x3(Result3_s16, Poly_s16x4x3);
    XCTAssertEqual(Result3_s16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result3_s16[11], 21, @"should contain the correct value");
    
    CCSimd_s16x4x4 Poly_s16x4x4 = CCSimdInterleaveLoad_s16x4x4((int16_t[16]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[0], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[0], 3), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[1], 2), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[1], 3), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[2], 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[2], 3), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[3], 1), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[3], 2), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s16x4(Poly_s16x4x4.v[3], 3), 15, @"should contain the correct value");
    
    Poly_s16x4x4.v[0] = CCSimdLoad_s16x4((int16_t[4]){ 10, 14, 18, 22 });
    Poly_s16x4x4.v[1] = CCSimdLoad_s16x4((int16_t[4]){ 11, 15, 19, 23 });
    Poly_s16x4x4.v[2] = CCSimdLoad_s16x4((int16_t[4]){ 12, 16, 20, 24 });
    Poly_s16x4x4.v[3] = CCSimdLoad_s16x4((int16_t[4]){ 13, 17, 21, 25 });
    int16_t Result4_s16[16];
    
    CCSimdInterleaveStore_s16x4x4(Result4_s16, Poly_s16x4x4);
    XCTAssertEqual(Result4_s16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result4_s16[15], 25, @"should contain the correct value");
    
    
    uint16_t Result_u16[4];
    CCSimd_u16x4 Vec_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 0, 1, 2, 3 });
    
    CCSimdStore_u16x4(Result_u16, Vec_u16x4);
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 3, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 1), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 2), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 3), 3, @"should contain the correct value");
    
    Vec_u16x4 = CCSimdSet_u16x4(Vec_u16x4, 0, 8);
    Vec_u16x4 = CCSimdSet_u16x4(Vec_u16x4, 1, 9);
    Vec_u16x4 = CCSimdSet_u16x4(Vec_u16x4, 2, 10);
    Vec_u16x4 = CCSimdSet_u16x4(Vec_u16x4, 3, 11);
    
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 1), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Vec_u16x4, 3), 11, @"should contain the correct value");
    
    CCSimd_u16x4x2 Poly_u16x4x2 = CCSimdInterleaveLoad_u16x4x2((uint16_t[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[0], 2), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[0], 3), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[1], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[1], 2), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x2.v[1], 3), 7, @"should contain the correct value");
    
    Poly_u16x4x2.v[0] = CCSimdLoad_u16x4((uint16_t[4]){ 10, 12, 14, 16 });
    Poly_u16x4x2.v[1] = CCSimdLoad_u16x4((uint16_t[4]){ 11, 13, 15, 17 });
    uint16_t Result2_u16[8];
    
    CCSimdInterleaveStore_u16x4x2(Result2_u16, Poly_u16x4x2);
    XCTAssertEqual(Result2_u16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result2_u16[7], 17, @"should contain the correct value");
    
    CCSimd_u16x4x3 Poly_u16x4x3 = CCSimdInterleaveLoad_u16x4x3((uint16_t[12]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
    
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[0], 2), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[0], 3), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[1], 2), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[1], 3), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[2], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[2], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x3.v[2], 3), 11, @"should contain the correct value");
    
    Poly_u16x4x3.v[0] = CCSimdLoad_u16x4((uint16_t[4]){ 10, 13, 16, 19 });
    Poly_u16x4x3.v[1] = CCSimdLoad_u16x4((uint16_t[4]){ 11, 14, 17, 20 });
    Poly_u16x4x3.v[2] = CCSimdLoad_u16x4((uint16_t[4]){ 12, 15, 18, 21 });
    uint16_t Result3_u16[12];
    
    CCSimdInterleaveStore_u16x4x3(Result3_u16, Poly_u16x4x3);
    XCTAssertEqual(Result3_u16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result3_u16[11], 21, @"should contain the correct value");
    
    CCSimd_u16x4x4 Poly_u16x4x4 = CCSimdInterleaveLoad_u16x4x4((uint16_t[16]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[0], 2), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[0], 3), 12, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[1], 2), 9, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[1], 3), 13, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[2], 2), 10, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[2], 3), 14, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[3], 1), 7, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[3], 2), 11, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u16x4(Poly_u16x4x4.v[3], 3), 15, @"should contain the correct value");
    
    Poly_u16x4x4.v[0] = CCSimdLoad_u16x4((uint16_t[4]){ 10, 14, 18, 22 });
    Poly_u16x4x4.v[1] = CCSimdLoad_u16x4((uint16_t[4]){ 11, 15, 19, 23 });
    Poly_u16x4x4.v[2] = CCSimdLoad_u16x4((uint16_t[4]){ 12, 16, 20, 24 });
    Poly_u16x4x4.v[3] = CCSimdLoad_u16x4((uint16_t[4]){ 13, 17, 21, 25 });
    uint16_t Result4_u16[16];
    
    CCSimdInterleaveStore_u16x4x4(Result4_u16, Poly_u16x4x4);
    XCTAssertEqual(Result4_u16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[7], 17, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[8], 18, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[9], 19, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[10], 20, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[11], 21, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[12], 22, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[13], 23, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[14], 24, @"should contain the correct value");
    XCTAssertEqual(Result4_u16[15], 25, @"should contain the correct value");
    
    
    int32_t Result_s32[2];
    CCSimd_s32x2 Vec_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 0, 1 });
    
    CCSimdStore_s32x2(Result_s32, Vec_s32x2);
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_s32x2(Vec_s32x2, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Vec_s32x2, 1), 1, @"should contain the correct value");
    
    Vec_s32x2 = CCSimdSet_s32x2(Vec_s32x2, 0, 8);
    Vec_s32x2 = CCSimdSet_s32x2(Vec_s32x2, 1, 9);
    
    XCTAssertEqual(CCSimdGet_s32x2(Vec_s32x2, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Vec_s32x2, 1), 9, @"should contain the correct value");
    
    CCSimd_s32x2x2 Poly_s32x2x2 = CCSimdInterleaveLoad_s32x2x2((int32_t[4]){ 0, 1, 2, 3 });
    
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x2.v[1], 1), 3, @"should contain the correct value");
    
    Poly_s32x2x2.v[0] = CCSimdLoad_s32x2((int32_t[2]){ 10, 12 });
    Poly_s32x2x2.v[1] = CCSimdLoad_s32x2((int32_t[2]){ 11, 13 });
    int32_t Result2_s32[4];
    
    CCSimdInterleaveStore_s32x2x2(Result2_s32, Poly_s32x2x2);
    XCTAssertEqual(Result2_s32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_s32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_s32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_s32[3], 13, @"should contain the correct value");
    
    CCSimd_s32x2x3 Poly_s32x2x3 = CCSimdInterleaveLoad_s32x2x3((int32_t[6]){ 0, 1, 2, 3, 4, 5 });
    
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x3.v[2], 1), 5, @"should contain the correct value");
    
    Poly_s32x2x3.v[0] = CCSimdLoad_s32x2((int32_t[2]){ 10, 13 });
    Poly_s32x2x3.v[1] = CCSimdLoad_s32x2((int32_t[2]){ 11, 14 });
    Poly_s32x2x3.v[2] = CCSimdLoad_s32x2((int32_t[2]){ 12, 15 });
    int32_t Result3_s32[6];
    
    CCSimdInterleaveStore_s32x2x3(Result3_s32, Poly_s32x2x3);
    XCTAssertEqual(Result3_s32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_s32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_s32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_s32[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_s32[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_s32[5], 15, @"should contain the correct value");
    
    CCSimd_s32x2x4 Poly_s32x2x4 = CCSimdInterleaveLoad_s32x2x4((int32_t[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_s32x2(Poly_s32x2x4.v[3], 1), 7, @"should contain the correct value");
    
    Poly_s32x2x4.v[0] = CCSimdLoad_s32x2((int32_t[2]){ 10, 14 });
    Poly_s32x2x4.v[1] = CCSimdLoad_s32x2((int32_t[2]){ 11, 15 });
    Poly_s32x2x4.v[2] = CCSimdLoad_s32x2((int32_t[2]){ 12, 16 });
    Poly_s32x2x4.v[3] = CCSimdLoad_s32x2((int32_t[2]){ 13, 17 });
    int32_t Result4_s32[8];
    
    CCSimdInterleaveStore_s32x2x4(Result4_s32, Poly_s32x2x4);
    XCTAssertEqual(Result4_s32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_s32[7], 17, @"should contain the correct value");
    
    
    uint32_t Result_u32[2];
    CCSimd_u32x2 Vec_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 0, 1 });
    
    CCSimdStore_u32x2(Result_u32, Vec_u32x2);
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_u32x2(Vec_u32x2, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Vec_u32x2, 1), 1, @"should contain the correct value");
    
    Vec_u32x2 = CCSimdSet_u32x2(Vec_u32x2, 0, 8);
    Vec_u32x2 = CCSimdSet_u32x2(Vec_u32x2, 1, 9);
    
    XCTAssertEqual(CCSimdGet_u32x2(Vec_u32x2, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Vec_u32x2, 1), 9, @"should contain the correct value");
    
    CCSimd_u32x2x2 Poly_u32x2x2 = CCSimdInterleaveLoad_u32x2x2((uint32_t[4]){ 0, 1, 2, 3 });
    
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x2.v[1], 1), 3, @"should contain the correct value");
    
    Poly_u32x2x2.v[0] = CCSimdLoad_u32x2((uint32_t[2]){ 10, 12 });
    Poly_u32x2x2.v[1] = CCSimdLoad_u32x2((uint32_t[2]){ 11, 13 });
    uint32_t Result2_u32[4];
    
    CCSimdInterleaveStore_u32x2x2(Result2_u32, Poly_u32x2x2);
    XCTAssertEqual(Result2_u32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_u32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_u32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_u32[3], 13, @"should contain the correct value");
    
    CCSimd_u32x2x3 Poly_u32x2x3 = CCSimdInterleaveLoad_u32x2x3((uint32_t[6]){ 0, 1, 2, 3, 4, 5 });
    
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x3.v[2], 1), 5, @"should contain the correct value");
    
    Poly_u32x2x3.v[0] = CCSimdLoad_u32x2((uint32_t[2]){ 10, 13 });
    Poly_u32x2x3.v[1] = CCSimdLoad_u32x2((uint32_t[2]){ 11, 14 });
    Poly_u32x2x3.v[2] = CCSimdLoad_u32x2((uint32_t[2]){ 12, 15 });
    uint32_t Result3_u32[6];
    
    CCSimdInterleaveStore_u32x2x3(Result3_u32, Poly_u32x2x3);
    XCTAssertEqual(Result3_u32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_u32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_u32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_u32[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_u32[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_u32[5], 15, @"should contain the correct value");
    
    CCSimd_u32x2x4 Poly_u32x2x4 = CCSimdInterleaveLoad_u32x2x4((uint32_t[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_u32x2(Poly_u32x2x4.v[3], 1), 7, @"should contain the correct value");
    
    Poly_u32x2x4.v[0] = CCSimdLoad_u32x2((uint32_t[2]){ 10, 14 });
    Poly_u32x2x4.v[1] = CCSimdLoad_u32x2((uint32_t[2]){ 11, 15 });
    Poly_u32x2x4.v[2] = CCSimdLoad_u32x2((uint32_t[2]){ 12, 16 });
    Poly_u32x2x4.v[3] = CCSimdLoad_u32x2((uint32_t[2]){ 13, 17 });
    uint32_t Result4_u32[8];
    
    CCSimdInterleaveStore_u32x2x4(Result4_u32, Poly_u32x2x4);
    XCTAssertEqual(Result4_u32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_u32[7], 17, @"should contain the correct value");
    
    
    float Result_f32[2];
    CCSimd_f32x2 Vec_f32x2 = CCSimdLoad_f32x2((float[2]){ 0, 1 });
    
    CCSimdStore_f32x2(Result_f32, Vec_f32x2);
    XCTAssertEqual(Result_f32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 1, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdGet_f32x2(Vec_f32x2, 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Vec_f32x2, 1), 1, @"should contain the correct value");
    
    Vec_f32x2 = CCSimdSet_f32x2(Vec_f32x2, 0, 8);
    Vec_f32x2 = CCSimdSet_f32x2(Vec_f32x2, 1, 9);
    
    XCTAssertEqual(CCSimdGet_f32x2(Vec_f32x2, 0), 8, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Vec_f32x2, 1), 9, @"should contain the correct value");
    
    CCSimd_f32x2x2 Poly_f32x2x2 = CCSimdInterleaveLoad_f32x2x2((float[4]){ 0, 1, 2, 3 });
    
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x2.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x2.v[0], 1), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x2.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x2.v[1], 1), 3, @"should contain the correct value");
    
    Poly_f32x2x2.v[0] = CCSimdLoad_f32x2((float[2]){ 10, 12 });
    Poly_f32x2x2.v[1] = CCSimdLoad_f32x2((float[2]){ 11, 13 });
    float Result2_f32[4];
    
    CCSimdInterleaveStore_f32x2x2(Result2_f32, Poly_f32x2x2);
    XCTAssertEqual(Result2_f32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result2_f32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result2_f32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result2_f32[3], 13, @"should contain the correct value");
    
    CCSimd_f32x2x3 Poly_f32x2x3 = CCSimdInterleaveLoad_f32x2x3((float[6]){ 0, 1, 2, 3, 4, 5 });
    
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x3.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x3.v[0], 1), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x3.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x3.v[1], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x3.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x3.v[2], 1), 5, @"should contain the correct value");
    
    Poly_f32x2x3.v[0] = CCSimdLoad_f32x2((float[2]){ 10, 13 });
    Poly_f32x2x3.v[1] = CCSimdLoad_f32x2((float[2]){ 11, 14 });
    Poly_f32x2x3.v[2] = CCSimdLoad_f32x2((float[2]){ 12, 15 });
    float Result3_f32[6];
    
    CCSimdInterleaveStore_f32x2x3(Result3_f32, Poly_f32x2x3);
    XCTAssertEqual(Result3_f32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result3_f32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result3_f32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result3_f32[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result3_f32[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result3_f32[5], 15, @"should contain the correct value");
    
    CCSimd_f32x2x4 Poly_f32x2x4 = CCSimdInterleaveLoad_f32x2x4((float[8]){ 0, 1, 2, 3, 4, 5, 6, 7 });
    
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[0], 0), 0, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[0], 1), 4, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[1], 0), 1, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[1], 1), 5, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[2], 0), 2, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[2], 1), 6, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[3], 0), 3, @"should contain the correct value");
    XCTAssertEqual(CCSimdGet_f32x2(Poly_f32x2x4.v[3], 1), 7, @"should contain the correct value");
    
    Poly_f32x2x4.v[0] = CCSimdLoad_f32x2((float[2]){ 10, 14 });
    Poly_f32x2x4.v[1] = CCSimdLoad_f32x2((float[2]){ 11, 15 });
    Poly_f32x2x4.v[2] = CCSimdLoad_f32x2((float[2]){ 12, 16 });
    Poly_f32x2x4.v[3] = CCSimdLoad_f32x2((float[2]){ 13, 17 });
    float Result4_f32[8];
    
    CCSimdInterleaveStore_f32x2x4(Result4_f32, Poly_f32x2x4);
    XCTAssertEqual(Result4_f32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[1], 11, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[2], 12, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[4], 14, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[6], 16, @"should contain the correct value");
    XCTAssertEqual(Result4_f32[7], 17, @"should contain the correct value");
}

-(void) testTrigonometry
{
#define DEGREES_TO_RADIANS(x) ((x) * M_PI / 180.0f)
    
    for (size_t Loop = 0; Loop < 72; Loop += 2)
    {
        const float Values[2] = { DEGREES_TO_RADIANS(Loop * 15), DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdSin_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], sinf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], sinf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 72; Loop += 2)
    {
        const float Values[2] = { -DEGREES_TO_RADIANS(Loop * 15), -DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdSin_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], sinf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], sinf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 12; Loop += 2)
    {
        const float Values[2] = { DEGREES_TO_RADIANS(Loop * 15), DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPosPiRadSin_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], sinf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], sinf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 72; Loop += 2)
    {
        const float Values[2] = { DEGREES_TO_RADIANS(Loop * 15), DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPosSin_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], sinf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], sinf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 12; Loop += 2)
    {
        const float Values[2] = { DEGREES_TO_RADIANS(Loop * 15), DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPiRadSin_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], sinf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], sinf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 12; Loop += 2)
    {
        const float Values[2] = { -DEGREES_TO_RADIANS(Loop * 15), -DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPiRadSin_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], sinf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], sinf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", sinf(Values[1]), Result[1]);
    }
    
    
    
    for (size_t Loop = 0; Loop < 72; Loop += 2)
    {
        const float Values[2] = { DEGREES_TO_RADIANS(Loop * 15), DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdCos_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], cosf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], cosf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 72; Loop += 2)
    {
        const float Values[2] = { -DEGREES_TO_RADIANS(Loop * 15), -DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdCos_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], cosf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], cosf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 6; Loop += 2)
    {
        const float Values[2] = { DEGREES_TO_RADIANS(Loop * 15), DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdHalfPiRadCos_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], cosf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], cosf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[1]), Result[1]);
    }
    
    for (size_t Loop = 0; Loop < 6; Loop += 2)
    {
        const float Values[2] = { -DEGREES_TO_RADIANS(Loop * 15), -DEGREES_TO_RADIANS(Loop * 15 + 15) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdHalfPiRadCos_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue(CCFloatEqualAbsolute(Result[0], cosf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[0]), Result[0]);
        XCTAssertTrue(CCFloatEqualAbsolute(Result[1], cosf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", cosf(Values[1]), Result[1]);
    }
}

-(void) testBitwiseOperations
{
    int8_t Result_s8[8];
    const CCSimd_s8x8 VecA_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 10, 11, 12, 13, 14, 15, 16, 17 });
    const CCSimd_s8x8 VecB_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 2, 4, 1, 3, 1, 2, 3, 4 });
    const CCSimd_s8x8 VecC_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 5, 6, 7, 8, 5, 6, 7, 8 });
    const CCSimd_s8x8 VecD_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ -128, -64, -104, -8, -40, -3, -2, -1 });
    
    CCSimdStore_s8x8(Result_s8, CCSimdNot_s8x8(VecA_s8x8));
    XCTAssertEqual(Result_s8[0], (int8_t)-11, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], (int8_t)-12, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], (int8_t)-13, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], (int8_t)-14, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], (int8_t)-15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], (int8_t)-16, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], (int8_t)-17, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], (int8_t)-18, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdNot_s32x2(VecB_s8x8));
    XCTAssertEqual(Result_s8[0], (int8_t)-3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], (int8_t)-5, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], (int8_t)-2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], (int8_t)-4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], (int8_t)-2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], (int8_t)-3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], (int8_t)-4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], (int8_t)-5, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdNot_s32x2(VecC_s8x8));
    XCTAssertEqual(Result_s8[0], (int8_t)-6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], (int8_t)-7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], (int8_t)-8, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], (int8_t)-9, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], (int8_t)-6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], (int8_t)-7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], (int8_t)-8, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], (int8_t)-9, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdNot_s32x2(VecD_s8x8));
    XCTAssertEqual(Result_s8[0], 127, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 63, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 103, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 39, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdAnd_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdAnd_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdAnd_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdOr_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 19, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 21, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdOr_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 23, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 25, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdOr_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 11, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 5, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 12, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdXor_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 14, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 19, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 21, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdXor_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 11, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 5, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 11, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 9, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 23, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 25, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdXor_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 11, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 12, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftLeft_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], -80, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 104, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 28, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 60, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], -128, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 16, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftLeft_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], -64, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], -64, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], -64, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftLeft_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], -128, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 32, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], -128, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], -128, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftLeftN_s8x8(VecA_s8x8, 3));
    XCTAssertEqual(Result_s8[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 88, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 96, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 104, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 112, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 120, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], -128, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], -120, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftLeftN_s8x8(VecB_s8x8, 2));
    XCTAssertEqual(Result_s8[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 16, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 12, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 12, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 16, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftLeftN_s8x8(VecC_s8x8, 1));
    XCTAssertEqual(Result_s8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 12, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 14, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 16, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 12, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 14, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 16, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRight_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRight_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRight_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRight_s8x8(VecD_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], -4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], -2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], -1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRightN_s8x8(VecA_s8x8, 3));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 2, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRightN_s8x8(VecB_s8x8, 2));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRightN_s8x8(VecC_s8x8, 1));
    XCTAssertEqual(Result_s8[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 4, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdShiftRightN_s8x8(VecD_s8x8, 7));
    XCTAssertEqual(Result_s8[0], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], -1, @"should contain the correct value");
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const int8_t Values[8] = { 1, 0xfe, 0x84, 0x42, 0xc0, 0x40, 0x7f, 0xbc };
        int8_t Result[8];
        
        CCSimdStore_s8x8(Result, CCSimdShiftLeftN_s8x8(CCSimdLoad_s8x8(Values), Loop));
        
        XCTAssertEqual(Result[0], (int8_t)(Values[0] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int8_t)(Values[1] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[2], (int8_t)(Values[2] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[3], (int8_t)(Values[3] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[4], (int8_t)(Values[4] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[5], (int8_t)(Values[5] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[6], (int8_t)(Values[6] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[7], (int8_t)(Values[7] << Loop), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const int8_t Values[8] = { 0xff, 0xef, 0x84, 0x42, 0xc0, 0x40, 0x7f, 0xbc };
        int8_t Result[8];
        
        CCSimdStore_s8x8(Result, CCSimdShiftRightN_s8x8(CCSimdLoad_s8x8(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[4], Values[4] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[5], Values[5] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[6], Values[6] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[7], Values[7] >> Loop, @"should contain the correct value");
    }
    
    
    uint8_t Result_u8[8];
    const CCSimd_u8x8 VecA_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 10, 11, 12, 13, 14, 15, 16, 17 });
    const CCSimd_u8x8 VecB_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 2, 4, 1, 3, 1, 2, 3, 4 });
    const CCSimd_u8x8 VecC_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 5, 6, 7, 8, 5, 6, 7, 8 });
    const CCSimd_u8x8 VecD_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ -128, -64, -104, -8, -40, -3, -2, -1 });
    
    CCSimdStore_u8x8(Result_u8, CCSimdNot_u8x8(VecA_u8x8));
    XCTAssertEqual(Result_u8[0], (uint8_t)-11, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], (uint8_t)-12, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], (uint8_t)-13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], (uint8_t)-14, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], (uint8_t)-15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], (uint8_t)-16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], (uint8_t)-17, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], (uint8_t)-18, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdNot_s32x2(VecB_u8x8));
    XCTAssertEqual(Result_u8[0], (uint8_t)-3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], (uint8_t)-5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], (uint8_t)-2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], (uint8_t)-4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], (uint8_t)-2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], (uint8_t)-3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], (uint8_t)-4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], (uint8_t)-5, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdNot_s32x2(VecC_u8x8));
    XCTAssertEqual(Result_u8[0], (uint8_t)-6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], (uint8_t)-7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], (uint8_t)-8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], (uint8_t)-9, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], (uint8_t)-6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], (uint8_t)-7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], (uint8_t)-8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], (uint8_t)-9, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdNot_s32x2(VecD_u8x8));
    XCTAssertEqual(Result_u8[0], 127, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 63, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 103, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 39, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdAnd_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdAnd_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdAnd_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdOr_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 19, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 21, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdOr_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 23, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 25, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdOr_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 11, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 12, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdXor_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 14, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 19, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 21, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdXor_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 11, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 11, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 9, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 23, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 25, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdXor_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 11, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 12, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftLeft_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 176, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 104, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 28, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 60, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 16, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftLeft_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 192, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 192, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 192, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftLeft_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftLeftN_u8x8(VecA_u8x8, 3));
    XCTAssertEqual(Result_u8[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 88, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 96, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 104, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 112, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 120, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 136, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftLeftN_u8x8(VecB_u8x8, 2));
    XCTAssertEqual(Result_u8[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 12, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 12, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 16, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftLeftN_u8x8(VecC_u8x8, 1));
    XCTAssertEqual(Result_u8[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 12, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 14, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 12, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 14, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 16, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRight_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRight_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRight_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRight_u8x8(VecD_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRightN_u8x8(VecA_u8x8, 3));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 2, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRightN_u8x8(VecB_u8x8, 2));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRightN_u8x8(VecC_u8x8, 1));
    XCTAssertEqual(Result_u8[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 4, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdShiftRightN_u8x8(VecD_u8x8, 7));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateLeft_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 176, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 104, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 28, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 60, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 17, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateLeft_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 65, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 194, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 193, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 195, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 17, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateLeft_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 129, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 4, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateLeftN_u8x8(VecA_u8x8, 6));
    XCTAssertEqual(Result_u8[0], 130, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 194, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 67, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 131, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 195, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 68, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateLeftN_u8x8(VecB_u8x8, 12));
    XCTAssertEqual(Result_u8[0], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 48, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 48, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 64, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateLeftN_u8x8(VecC_u8x8, 8));
    XCTAssertEqual(Result_u8[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 8, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateRight_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 130, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 176, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 161, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 195, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 17, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateRight_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 44, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 112, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 60, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 17, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateRight_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 4, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateRightN_u8x8(VecA_u8x8, 6));
    XCTAssertEqual(Result_u8[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 44, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 48, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 52, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 56, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 60, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 68, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateRightN_u8x8(VecB_u8x8, 12));
    XCTAssertEqual(Result_u8[0], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 48, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 48, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 64, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdRotateRightN_u8x8(VecC_u8x8, 8));
    XCTAssertEqual(Result_u8[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 8, @"should contain the correct value");
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint8_t Values[8] = { 1, 0xfe, 0x84, 0x42, 0xc0, 0x40, 0x7f, 0xbc };
        uint8_t Result[8];
        
        CCSimdStore_u8x8(Result, CCSimdShiftLeftN_u8x8(CCSimdLoad_u8x8(Values), Loop));
        
        XCTAssertEqual(Result[0], (uint8_t)(Values[0] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[1], (uint8_t)(Values[1] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[2], (uint8_t)(Values[2] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[3], (uint8_t)(Values[3] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[4], (uint8_t)(Values[4] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[5], (uint8_t)(Values[5] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[6], (uint8_t)(Values[6] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[7], (uint8_t)(Values[7] << Loop), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint8_t Values[8] = { 0xff, 0xef, 0x84, 0x42, 0xc0, 0x40, 0x7f, 0xbc };
        uint8_t Result[8];
        
        CCSimdStore_u8x8(Result, CCSimdShiftRightN_u8x8(CCSimdLoad_u8x8(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[4], Values[4] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[5], Values[5] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[6], Values[6] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[7], Values[7] >> Loop, @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint8_t Values[8] = { 1, 0xfe, 0x84, 0x42, 0xc0, 0x40, 0x7f, 0xbc };
        uint8_t Result[8];
        
        CCSimdStore_u8x8(Result, CCSimdRotateLeftN_u8x8(CCSimdLoad_u8x8(Values), Loop));
        
        XCTAssertEqual(Result[0], (uint8_t)(Values[0] << Loop) | (Values[0] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[1], (uint8_t)(Values[1] << Loop) | (Values[1] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[2], (uint8_t)(Values[2] << Loop) | (Values[2] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[3], (uint8_t)(Values[3] << Loop) | (Values[3] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[4], (uint8_t)(Values[4] << Loop) | (Values[4] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[5], (uint8_t)(Values[5] << Loop) | (Values[5] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[6], (uint8_t)(Values[6] << Loop) | (Values[6] >> (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[7], (uint8_t)(Values[7] << Loop) | (Values[7] >> (-Loop & 7)), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint8_t Values[8] = { 1, 0xfe, 0x84, 0x42, 0xc0, 0x40, 0x7f, 0xbc };
        uint8_t Result[8];
        
        CCSimdStore_u8x8(Result, CCSimdRotateRightN_u8x8(CCSimdLoad_u8x8(Values), Loop));
        
        XCTAssertEqual(Result[0], (Values[0] >> Loop) | (uint8_t)(Values[0] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[1], (Values[1] >> Loop) | (uint8_t)(Values[1] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[2], (Values[2] >> Loop) | (uint8_t)(Values[2] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[3], (Values[3] >> Loop) | (uint8_t)(Values[3] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[4], (Values[4] >> Loop) | (uint8_t)(Values[4] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[5], (Values[5] >> Loop) | (uint8_t)(Values[5] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[6], (Values[6] >> Loop) | (uint8_t)(Values[6] << (-Loop & 7)), @"should contain the correct value");
        XCTAssertEqual(Result[7], (Values[7] >> Loop) | (uint8_t)(Values[7] << (-Loop & 7)), @"should contain the correct value");
    }
    
    
    int16_t Result_s16[4];
    const CCSimd_s16x4 VecA_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 10, 11, 12, 13 });
    const CCSimd_s16x4 VecB_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 2, 4, 1, 3 });
    const CCSimd_s16x4 VecC_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 5, 6, 7, 8 });
    const CCSimd_s16x4 VecD_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ -32768, -16384, -6272, -2048 });
    
    CCSimdStore_s16x4(Result_s16, CCSimdNot_s16x4(VecA_s16x4));
    XCTAssertEqual(Result_s16[0], (int16_t)-11, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], (int16_t)-12, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], (int16_t)-13, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], (int16_t)-14, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdNot_s32x2(VecB_s16x4));
    XCTAssertEqual(Result_s16[0], (int16_t)-3, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], (int16_t)-5, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], (int16_t)-2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], (int16_t)-4, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdNot_s32x2(VecC_s16x4));
    XCTAssertEqual(Result_s16[0], (int16_t)-6, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], (int16_t)-7, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], (int16_t)-8, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], (int16_t)-9, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdNot_s32x2(VecD_s16x4));
    XCTAssertEqual(Result_s16[0], 32767, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 16383, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 6271, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 2047, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdAnd_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdAnd_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 8, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdAnd_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdOr_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 15, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdOr_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 13, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdOr_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 11, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdXor_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 14, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdXor_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 13, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 11, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 5, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdXor_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 11, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftLeft_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 176, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 104, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftLeft_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 320, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 704, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1536, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 3328, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftLeft_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 256, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 128, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 768, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftLeftN_s16x4(VecA_s16x4, 3));
    XCTAssertEqual(Result_s16[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 88, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 96, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 104, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftLeftN_s16x4(VecB_s16x4, 2));
    XCTAssertEqual(Result_s16[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 16, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 12, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftLeftN_s16x4(VecC_s16x4, 1));
    XCTAssertEqual(Result_s16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 12, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 14, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 16, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRight_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRight_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRight_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRight_s16x4(VecD_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], -1024, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], -256, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], -49, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], -8, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRightN_s16x4(VecA_s16x4, 3));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRightN_s16x4(VecB_s16x4, 2));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRightN_s16x4(VecC_s16x4, 1));
    XCTAssertEqual(Result_s16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 4, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdShiftRightN_s16x4(VecD_s16x4, 14));
    XCTAssertEqual(Result_s16[0], -2, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], -1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], -1, @"should contain the correct value");
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        const int16_t Values[4] = { 1, 0xfffe, 0x8842, 0x842 };
        int16_t Result[4];
        
        CCSimdStore_s16x4(Result, CCSimdShiftLeftN_s16x4(CCSimdLoad_s16x4(Values), Loop));
        
        XCTAssertEqual(Result[0], (int16_t)(Values[0] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int16_t)(Values[1] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[2], (int16_t)(Values[2] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[3], (int16_t)(Values[3] << Loop), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        const int16_t Values[4] = { 0xffff, 0xefff, 0x8842, 0x842 };
        int16_t Result[4];
        
        CCSimdStore_s16x4(Result, CCSimdShiftRightN_s16x4(CCSimdLoad_s16x4(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] >> Loop, @"should contain the correct value");
    }
    
    
    uint16_t Result_u16[4];
    const CCSimd_u16x4 VecA_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 10, 11, 12, 13 });
    const CCSimd_u16x4 VecB_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 2, 4, 1, 3 });
    const CCSimd_u16x4 VecC_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 5, 6, 7, 8 });
    const CCSimd_u16x4 VecD_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ -32768, -16384, -6272, -2048 });
    
    CCSimdStore_u16x4(Result_u16, CCSimdNot_u16x4(VecA_u16x4));
    XCTAssertEqual(Result_u16[0], (uint16_t)-11, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], (uint16_t)-12, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], (uint16_t)-13, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], (uint16_t)-14, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdNot_s32x2(VecB_u16x4));
    XCTAssertEqual(Result_u16[0], (uint16_t)-3, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], (uint16_t)-5, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], (uint16_t)-2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], (uint16_t)-4, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdNot_s32x2(VecC_u16x4));
    XCTAssertEqual(Result_u16[0], (uint16_t)-6, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], (uint16_t)-7, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], (uint16_t)-8, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], (uint16_t)-9, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdNot_s32x2(VecD_u16x4));
    XCTAssertEqual(Result_u16[0], 32767, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 16383, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 6271, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 2047, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdAnd_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdAnd_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 8, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdAnd_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdOr_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 15, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdOr_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 13, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdOr_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 11, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdXor_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 14, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdXor_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 11, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 5, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdXor_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 11, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftLeft_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 176, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 104, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftLeft_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 320, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 704, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1536, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 3328, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftLeft_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 256, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 128, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 768, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftLeftN_u16x4(VecA_u16x4, 3));
    XCTAssertEqual(Result_u16[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 88, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 96, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 104, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftLeftN_u16x4(VecB_u16x4, 2));
    XCTAssertEqual(Result_u16[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 12, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftLeftN_u16x4(VecC_u16x4, 1));
    XCTAssertEqual(Result_u16[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 12, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 14, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 16, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRight_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRight_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRight_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRight_u16x4(VecD_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 1024, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 768, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 463, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 248, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRightN_u16x4(VecA_u16x4, 3));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRightN_u16x4(VecB_u16x4, 2));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRightN_u16x4(VecC_u16x4, 1));
    XCTAssertEqual(Result_u16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 4, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdShiftRightN_u16x4(VecD_u16x4, 14));
    XCTAssertEqual(Result_u16[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 3, @"should contain the correct value");
    
    const CCSimd_u16x4 VecE_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 13, 14, 15, 16 });
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateLeft_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 176, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 104, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateLeft_u16x4(VecA_u16x4, VecE_u16x4));
    XCTAssertEqual(Result_u16[0], 16385, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 49154, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 13, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateLeft_u16x4(VecB_u16x4, VecE_u16x4));
    XCTAssertEqual(Result_u16[0], 16384, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 32768, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 3, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateLeftN_u16x4(VecA_u16x4, 14));
    XCTAssertEqual(Result_u16[0], 32770, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 49154, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 3, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 16387, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateLeftN_u16x4(VecB_u16x4, 20));
    XCTAssertEqual(Result_u16[0], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 48, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateLeftN_u16x4(VecE_u16x4, 16));
    XCTAssertEqual(Result_u16[0], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 14, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 16, "should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateRight_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 32770, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 45056, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 6, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 40961, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateRight_u16x4(VecA_u16x4, VecE_u16x4));
    XCTAssertEqual(Result_u16[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 44, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 24, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 13, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateRight_u16x4(VecB_u16x4, VecE_u16x4));
    XCTAssertEqual(Result_u16[0], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 16, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 3, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateRightN_u16x4(VecA_u16x4, 14));
    XCTAssertEqual(Result_u16[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 44, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 48, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 52, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateRightN_u16x4(VecB_u16x4, 20));
    XCTAssertEqual(Result_u16[0], 8192, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 16384, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 4096, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 12288, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdRotateRightN_u16x4(VecE_u16x4, 16));
    XCTAssertEqual(Result_u16[0], 13, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 14, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 16, @"should contain the correct value");
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        const uint16_t Values[4] = { 1, 0xfffe, 0x8842, 0x842 };
        uint16_t Result[4];
        
        CCSimdStore_u16x4(Result, CCSimdShiftLeftN_u16x4(CCSimdLoad_u16x4(Values), Loop));
        
        XCTAssertEqual(Result[0], (uint16_t)(Values[0] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[1], (uint16_t)(Values[1] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[2], (uint16_t)(Values[2] << Loop), @"should contain the correct value");
        XCTAssertEqual(Result[3], (uint16_t)(Values[3] << Loop), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        const uint16_t Values[4] = { 0xffff, 0xefff, 0x8842, 0x842 };
        uint16_t Result[4];
        
        CCSimdStore_u16x4(Result, CCSimdShiftRightN_u16x4(CCSimdLoad_u16x4(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] >> Loop, @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint16_t Values[4] = { 1, 0xfffe, 0x8842, 0x842 };
        uint16_t Result[4];
        
        CCSimdStore_u16x4(Result, CCSimdRotateLeftN_u16x4(CCSimdLoad_u16x4(Values), Loop));
        
        XCTAssertEqual(Result[0], (uint16_t)(Values[0] << Loop) | (Values[0] >> (-Loop & 15)), @"should contain the correct value");
        XCTAssertEqual(Result[1], (uint16_t)(Values[1] << Loop) | (Values[1] >> (-Loop & 15)), @"should contain the correct value");
        XCTAssertEqual(Result[2], (uint16_t)(Values[2] << Loop) | (Values[2] >> (-Loop & 15)), @"should contain the correct value");
        XCTAssertEqual(Result[3], (uint16_t)(Values[3] << Loop) | (Values[3] >> (-Loop & 15)), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint16_t Values[4] = { 1, 0xfffe, 0x8842, 0x842 };
        uint16_t Result[4];
        
        CCSimdStore_u16x4(Result, CCSimdRotateRightN_u16x4(CCSimdLoad_u16x4(Values), Loop));
        
        XCTAssertEqual(Result[0], (Values[0] >> Loop) | (uint16_t)(Values[0] << (-Loop & 15)), @"should contain the correct value");
        XCTAssertEqual(Result[1], (Values[1] >> Loop) | (uint16_t)(Values[1] << (-Loop & 15)), @"should contain the correct value");
        XCTAssertEqual(Result[2], (Values[2] >> Loop) | (uint16_t)(Values[2] << (-Loop & 15)), @"should contain the correct value");
        XCTAssertEqual(Result[3], (Values[3] >> Loop) | (uint16_t)(Values[3] << (-Loop & 15)), @"should contain the correct value");
    }
    
    
    int32_t Result_s32[2];
    const CCSimd_s32x2 VecA_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 10, 11 });
    const CCSimd_s32x2 VecB_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 2, 4 });
    const CCSimd_s32x2 VecC_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 5, 6 });
    const CCSimd_s32x2 VecD_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ -32768, -49152 });
    
    CCSimdStore_s32x2(Result_s32, CCSimdNot_s32x2(VecA_s32x2));
    XCTAssertEqual(Result_s32[0], -11, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -12, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdNot_s32x2(VecB_s32x2));
    XCTAssertEqual(Result_s32[0], -3, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -5, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdNot_s32x2(VecC_s32x2));
    XCTAssertEqual(Result_s32[0], -6, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -7, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdAnd_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdAnd_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 2, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdAnd_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 4, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdOr_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 15, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdOr_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 15, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdOr_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 6, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdXor_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 15, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdXor_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 13, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdXor_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 2, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftLeft_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 176, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftLeft_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 320, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 704, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftLeft_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 256, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftLeftN_s32x2(VecA_s32x2, 3));
    XCTAssertEqual(Result_s32[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 88, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftLeftN_s32x2(VecB_s32x2, 2));
    XCTAssertEqual(Result_s32[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 16, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftLeftN_s32x2(VecC_s32x2, 1));
    XCTAssertEqual(Result_s32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 12, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRight_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRight_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRight_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRight_s32x2(VecD_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], -1024, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -768, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRightN_s32x2(VecA_s32x2, 3));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRightN_s32x2(VecB_s32x2, 2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRightN_s32x2(VecC_s32x2, 1));
    XCTAssertEqual(Result_s32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 3, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdShiftRightN_s32x2(VecD_s32x2, 14));
    XCTAssertEqual(Result_s32[0], -2, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -3, @"should contain the correct value");
    
    for (size_t Loop = 0; Loop < 32; Loop++)
    {
        const int32_t Values[2] = { 1, 0xfffffffe };
        int32_t Result[2];
        
        CCSimdStore_s32x2(Result, CCSimdShiftLeftN_s32x2(CCSimdLoad_s32x2(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] << Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] << Loop, @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 32; Loop++)
    {
        const int32_t Values[2] = { 0xffffffff, 0xefffffff };
        int32_t Result[2];
        
        CCSimdStore_s32x2(Result, CCSimdShiftRightN_s32x2(CCSimdLoad_s32x2(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] >> Loop, @"should contain the correct value");
    }
    
    
    uint32_t Result_u32[2];
    const CCSimd_u32x2 VecA_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 10, 11 });
    const CCSimd_u32x2 VecB_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 2, 4 });
    const CCSimd_u32x2 VecC_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 5, 6 });
    const CCSimd_u32x2 VecD_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ -32768, -49152 });
    
    CCSimdStore_u32x2(Result_u32, CCSimdNot_u32x2(VecA_u32x2));
    XCTAssertEqual(Result_u32[0], -11, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], -12, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdNot_s32x2(VecB_u32x2));
    XCTAssertEqual(Result_u32[0], -3, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], -5, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdNot_s32x2(VecC_u32x2));
    XCTAssertEqual(Result_u32[0], -6, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], -7, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdAnd_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdAnd_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 2, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdAnd_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 4, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdOr_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 15, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdOr_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 15, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdOr_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 6, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdXor_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 15, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdXor_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 13, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdXor_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 7, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 2, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftLeft_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 176, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftLeft_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 320, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 704, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftLeft_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 64, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 256, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftLeftN_u32x2(VecA_u32x2, 3));
    XCTAssertEqual(Result_u32[0], 80, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 88, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftLeftN_u32x2(VecB_u32x2, 2));
    XCTAssertEqual(Result_u32[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 16, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftLeftN_u32x2(VecC_u32x2, 1));
    XCTAssertEqual(Result_u32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 12, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRight_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRight_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRight_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRight_u32x2(VecD_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 134216704, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 67108096, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRightN_u32x2(VecA_u32x2, 3));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRightN_u32x2(VecB_u32x2, 2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRightN_u32x2(VecC_u32x2, 1));
    XCTAssertEqual(Result_u32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 3, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdShiftRightN_u32x2(VecD_u32x2, 14));
    XCTAssertEqual(Result_u32[0], 262142, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 262141, @"should contain the correct value");
    
    const CCSimd_u32x2 VecE_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 31, 32 });
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateLeft_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 176, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateLeft_u32x2(VecA_u32x2, VecE_u32x2));
    XCTAssertEqual(Result_u32[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 11, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateLeft_u32x2(VecB_u32x2, VecE_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 4, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateLeftN_u32x2(VecA_u32x2, 30));
    XCTAssertEqual(Result_u32[0], 2147483650, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 3221225474, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateLeftN_u32x2(VecB_u32x2, 36));
    XCTAssertEqual(Result_u32[0], 32, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 64, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateLeftN_u32x2(VecE_u32x2, 32));
    XCTAssertEqual(Result_u32[0], 31, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 32, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateRight_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 2147483650, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 2952790016, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateRight_u32x2(VecA_u32x2, VecE_u32x2));
    XCTAssertEqual(Result_u32[0], 20, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 11, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateRight_u32x2(VecB_u32x2, VecE_u32x2));
    XCTAssertEqual(Result_u32[0], 4, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 4, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateRightN_u32x2(VecA_u32x2, 30));
    XCTAssertEqual(Result_u32[0], 40, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 44, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateRightN_u32x2(VecB_u32x2, 36));
    XCTAssertEqual(Result_u32[0], 536870912, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1073741824, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdRotateRightN_u32x2(VecE_u32x2, 32));
    XCTAssertEqual(Result_u32[0], 31, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 32, @"should contain the correct value");
    
    for (size_t Loop = 0; Loop < 32; Loop++)
    {
        const uint32_t Values[2] = { 1, 0xfffffffe };
        uint32_t Result[2];
        
        CCSimdStore_u32x2(Result, CCSimdShiftLeftN_u32x2(CCSimdLoad_u32x2(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] << Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] << Loop, @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 32; Loop++)
    {
        const uint32_t Values[2] = { 0xffffffff, 0xefffffff };
        uint32_t Result[2];
        
        CCSimdStore_u32x2(Result, CCSimdShiftRightN_u32x2(CCSimdLoad_u32x2(Values), Loop));
        
        XCTAssertEqual(Result[0], Values[0] >> Loop, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] >> Loop, @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint32_t Values[4] = { 1, 0xfffffffe };
        uint32_t Result[4];
        
        CCSimdStore_u32x2(Result, CCSimdRotateLeftN_u32x2(CCSimdLoad_u32x2(Values), Loop));
        
        XCTAssertEqual(Result[0], (uint32_t)(Values[0] << Loop) | (Values[0] >> (-Loop & 31)), @"should contain the correct value");
        XCTAssertEqual(Result[1], (uint32_t)(Values[1] << Loop) | (Values[1] >> (-Loop & 31)), @"should contain the correct value");
    }
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const uint32_t Values[4] = { 1, 0xfffffffe };
        uint32_t Result[4];
        
        CCSimdStore_u32x2(Result, CCSimdRotateRightN_u32x2(CCSimdLoad_u32x2(Values), Loop));
        
        XCTAssertEqual(Result[0], (Values[0] >> Loop) | (uint32_t)(Values[0] << (-Loop & 31)), @"should contain the correct value");
        XCTAssertEqual(Result[1], (Values[1] >> Loop) | (uint32_t)(Values[1] << (-Loop & 31)), @"should contain the correct value");
    }
}

-(void) testBitMaths
{
    for (size_t Loop = 0; Loop < 7; Loop++)
    {
        const int8_t Values[8] = { 1 << Loop, (1 << Loop) + 1, (1 << Loop) + 3, (1 << Loop) + 240, (1 << Loop) + 5, (1 << Loop) + 6, (1 << Loop) + 7, (1 << Loop) + 9 };
        int8_t Result[8];
        
        CCSimdStore_s8x8(Result, CCSimdLowestUnset_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], CCBitLowestUnset(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestUnset(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestUnset(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestUnset(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitLowestUnset(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitLowestUnset(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitLowestUnset(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitLowestUnset(Values[7]), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdLowestSet_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], CCBitLowestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestSet(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitLowestSet(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitLowestSet(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitLowestSet(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitLowestSet(Values[7]), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdHighestSet_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], (int8_t)CCBitHighestSet(*(uint8_t*)&Values[7]), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdNextPow2_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], (int8_t)(CCBitNextPowerOf2(Values[0]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int8_t)(CCBitNextPowerOf2(Values[1]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[2], (int8_t)(CCBitNextPowerOf2(Values[2]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[3], (int8_t)(CCBitNextPowerOf2(Values[3]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[4], (int8_t)(CCBitNextPowerOf2(Values[4]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[5], (int8_t)(CCBitNextPowerOf2(Values[5]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[6], (int8_t)(CCBitNextPowerOf2(Values[6]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[7], (int8_t)(CCBitNextPowerOf2(Values[7]) & UINT8_MAX), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdMask_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForValue(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForValue(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitMaskForValue(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitMaskForValue(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitMaskForValue(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitMaskForValue(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitMaskForValue(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitMaskForValue(Values[7]), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdMaskLowerPow2_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForLowerPowerOf2(Values[0]), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdMaskHighestUnset_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[0]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[1], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[1]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[2], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[2]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[3], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[3]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[4], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[4]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[5], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[5]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[6], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[6]) & UINT8_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[7], *(int8_t*)&(uint8_t){ CCBitMaskForUnsetValue(Values[7]) & UINT8_MAX }, @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdCountLowestUnset_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], Values[0] ? CCBitCountLowestUnset(Values[0]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] ? CCBitCountLowestUnset(Values[1]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] ? CCBitCountLowestUnset(Values[2]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] ? CCBitCountLowestUnset(Values[3]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[4], Values[4] ? CCBitCountLowestUnset(Values[4]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[5], Values[5] ? CCBitCountLowestUnset(Values[5]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[6], Values[6] ? CCBitCountLowestUnset(Values[6]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[7], Values[7] ? CCBitCountLowestUnset(Values[7]) : 8, @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdCountHighestUnset_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(CCBitMaskForUnsetValue(Values[0]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(CCBitMaskForUnsetValue(Values[1]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(CCBitMaskForUnsetValue(Values[2]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(CCBitMaskForUnsetValue(Values[3]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitCountSet(CCBitMaskForUnsetValue(Values[4]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitCountSet(CCBitMaskForUnsetValue(Values[5]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitCountSet(CCBitMaskForUnsetValue(Values[6]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitCountSet(CCBitMaskForUnsetValue(Values[7]) & UINT8_MAX), @"should contain the correct value");
        
        CCSimdStore_s8x8(Result, CCSimdCountSet_s8x8(CCSimdLoad_s8x8(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(*(uint8_t*)&Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(*(uint8_t*)&Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(*(uint8_t*)&Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(*(uint8_t*)&Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitCountSet(*(uint8_t*)&Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitCountSet(*(uint8_t*)&Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitCountSet(*(uint8_t*)&Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitCountSet(*(uint8_t*)&Values[7]), @"should contain the correct value");
    }
    
    
    for (size_t Loop = 0; Loop < 7; Loop++)
    {
        const uint8_t Values[8] = { 1 << Loop, (1 << Loop) + 1, (1 << Loop) + 3, (1 << Loop) + 240, (1 << Loop) + 5, (1 << Loop) + 6, (1 << Loop) + 7, (1 << Loop) + 9 };
        uint8_t Result[8];
        
        CCSimdStore_u8x8(Result, CCSimdLowestUnset_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitLowestUnset(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestUnset(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestUnset(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestUnset(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitLowestUnset(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitLowestUnset(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitLowestUnset(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitLowestUnset(Values[7]), @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdLowestSet_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitLowestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestSet(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitLowestSet(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitLowestSet(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitLowestSet(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitLowestSet(Values[7]), @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdHighestSet_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitHighestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitHighestSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitHighestSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitHighestSet(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitHighestSet(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitHighestSet(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitHighestSet(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitHighestSet(Values[7]), @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdNextPow2_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitNextPowerOf2(Values[0]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitNextPowerOf2(Values[1]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitNextPowerOf2(Values[2]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitNextPowerOf2(Values[3]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitNextPowerOf2(Values[4]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitNextPowerOf2(Values[5]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitNextPowerOf2(Values[6]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitNextPowerOf2(Values[7]) & UINT8_MAX, @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdMask_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForValue(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForValue(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitMaskForValue(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitMaskForValue(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitMaskForValue(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitMaskForValue(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitMaskForValue(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitMaskForValue(Values[7]), @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdMaskLowerPow2_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForLowerPowerOf2(Values[0]), @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdMaskHighestUnset_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForUnsetValue(Values[0]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForUnsetValue(Values[1]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitMaskForUnsetValue(Values[2]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitMaskForUnsetValue(Values[3]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitMaskForUnsetValue(Values[4]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitMaskForUnsetValue(Values[5]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitMaskForUnsetValue(Values[6]) & UINT8_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitMaskForUnsetValue(Values[7]) & UINT8_MAX, @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdCountLowestUnset_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], Values[0] ? CCBitCountLowestUnset(Values[0]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] ? CCBitCountLowestUnset(Values[1]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] ? CCBitCountLowestUnset(Values[2]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] ? CCBitCountLowestUnset(Values[3]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[4], Values[4] ? CCBitCountLowestUnset(Values[4]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[5], Values[5] ? CCBitCountLowestUnset(Values[5]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[6], Values[6] ? CCBitCountLowestUnset(Values[6]) : 8, @"should contain the correct value");
        XCTAssertEqual(Result[7], Values[7] ? CCBitCountLowestUnset(Values[7]) : 8, @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdCountHighestUnset_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(CCBitMaskForUnsetValue(Values[0]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(CCBitMaskForUnsetValue(Values[1]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(CCBitMaskForUnsetValue(Values[2]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(CCBitMaskForUnsetValue(Values[3]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitCountSet(CCBitMaskForUnsetValue(Values[4]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitCountSet(CCBitMaskForUnsetValue(Values[5]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitCountSet(CCBitMaskForUnsetValue(Values[6]) & UINT8_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitCountSet(CCBitMaskForUnsetValue(Values[7]) & UINT8_MAX), @"should contain the correct value");
        
        CCSimdStore_u8x8(Result, CCSimdCountSet_u8x8(CCSimdLoad_u8x8(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(Values[3]), @"should contain the correct value");
        XCTAssertEqual(Result[4], CCBitCountSet(Values[4]), @"should contain the correct value");
        XCTAssertEqual(Result[5], CCBitCountSet(Values[5]), @"should contain the correct value");
        XCTAssertEqual(Result[6], CCBitCountSet(Values[6]), @"should contain the correct value");
        XCTAssertEqual(Result[7], CCBitCountSet(Values[7]), @"should contain the correct value");
    }
    
    
    for (size_t Loop = 0; Loop < 15; Loop++)
    {
        const int16_t Values[4] = { 1 << Loop, (1 << Loop) + 1, (1 << Loop) + 3, (1 << Loop) + 240 };
        int16_t Result[4];
        
        CCSimdStore_s16x4(Result, CCSimdLowestUnset_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], CCBitLowestUnset(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestUnset(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestUnset(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestUnset(Values[3]), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdLowestSet_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], CCBitLowestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestSet(Values[3]), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdHighestSet_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], (int16_t)CCBitHighestSet(*(uint16_t*)&Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int16_t)CCBitHighestSet(*(uint16_t*)&Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], (int16_t)CCBitHighestSet(*(uint16_t*)&Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], (int16_t)CCBitHighestSet(*(uint16_t*)&Values[3]), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdNextPow2_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], (int16_t)(CCBitNextPowerOf2(Values[0]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int16_t)(CCBitNextPowerOf2(Values[1]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[2], (int16_t)(CCBitNextPowerOf2(Values[2]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[3], (int16_t)(CCBitNextPowerOf2(Values[3]) & UINT16_MAX), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdMask_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForValue(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForValue(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitMaskForValue(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitMaskForValue(Values[3]), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdMaskLowerPow2_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForLowerPowerOf2(Values[0]), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdMaskHighestUnset_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], *(int16_t*)&(uint16_t){ CCBitMaskForUnsetValue(Values[0]) & UINT16_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[1], *(int16_t*)&(uint16_t){ CCBitMaskForUnsetValue(Values[1]) & UINT16_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[2], *(int16_t*)&(uint16_t){ CCBitMaskForUnsetValue(Values[2]) & UINT16_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[3], *(int16_t*)&(uint16_t){ CCBitMaskForUnsetValue(Values[3]) & UINT16_MAX }, @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdCountLowestUnset_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], Values[0] ? CCBitCountLowestUnset(Values[0]) : 16, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] ? CCBitCountLowestUnset(Values[1]) : 16, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] ? CCBitCountLowestUnset(Values[2]) : 16, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] ? CCBitCountLowestUnset(Values[3]) : 16, @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdCountHighestUnset_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(CCBitMaskForUnsetValue(Values[0]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(CCBitMaskForUnsetValue(Values[1]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(CCBitMaskForUnsetValue(Values[2]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(CCBitMaskForUnsetValue(Values[3]) & UINT16_MAX), @"should contain the correct value");
        
        CCSimdStore_s16x4(Result, CCSimdCountSet_s16x4(CCSimdLoad_s16x4(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(*(uint16_t*)&Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(*(uint16_t*)&Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(*(uint16_t*)&Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(*(uint16_t*)&Values[3]), @"should contain the correct value");
    }
    
    
    for (size_t Loop = 0; Loop < 15; Loop++)
    {
        const uint16_t Values[4] = { 1 << Loop, (1 << Loop) + 1, (1 << Loop) + 3, (1 << Loop) + 240 };
        uint16_t Result[4];
        
        CCSimdStore_u16x4(Result, CCSimdLowestUnset_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitLowestUnset(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestUnset(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestUnset(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestUnset(Values[3]), @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdLowestSet_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitLowestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitLowestSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitLowestSet(Values[3]), @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdHighestSet_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitHighestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitHighestSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitHighestSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitHighestSet(Values[3]), @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdNextPow2_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitNextPowerOf2(Values[0]) & UINT16_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitNextPowerOf2(Values[1]) & UINT16_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitNextPowerOf2(Values[2]) & UINT16_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitNextPowerOf2(Values[3]) & UINT16_MAX, @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdMask_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForValue(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForValue(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitMaskForValue(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitMaskForValue(Values[3]), @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdMaskLowerPow2_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForLowerPowerOf2(Values[0]), @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdMaskHighestUnset_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForUnsetValue(Values[0]) & UINT16_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForUnsetValue(Values[1]) & UINT16_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitMaskForUnsetValue(Values[2]) & UINT16_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitMaskForUnsetValue(Values[3]) & UINT16_MAX, @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdCountLowestUnset_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], Values[0] ? CCBitCountLowestUnset(Values[0]) : 16, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] ? CCBitCountLowestUnset(Values[1]) : 16, @"should contain the correct value");
        XCTAssertEqual(Result[2], Values[2] ? CCBitCountLowestUnset(Values[2]) : 16, @"should contain the correct value");
        XCTAssertEqual(Result[3], Values[3] ? CCBitCountLowestUnset(Values[3]) : 16, @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdCountHighestUnset_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(CCBitMaskForUnsetValue(Values[0]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(CCBitMaskForUnsetValue(Values[1]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(CCBitMaskForUnsetValue(Values[2]) & UINT16_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(CCBitMaskForUnsetValue(Values[3]) & UINT16_MAX), @"should contain the correct value");
        
        CCSimdStore_u16x4(Result, CCSimdCountSet_u16x4(CCSimdLoad_u16x4(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(Values[1]), @"should contain the correct value");
        XCTAssertEqual(Result[2], CCBitCountSet(Values[2]), @"should contain the correct value");
        XCTAssertEqual(Result[3], CCBitCountSet(Values[3]), @"should contain the correct value");
    }
    
    
    for (size_t Loop = 0; Loop < 31; Loop++)
    {
        const int32_t Values[2] = { 1 << Loop, (1 << Loop) + 1 };
        int32_t Result[2];
        
        CCSimdStore_s32x2(Result, CCSimdLowestUnset_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], CCBitLowestUnset(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestUnset(Values[1]), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdLowestSet_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], CCBitLowestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestSet(Values[1]), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdHighestSet_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], (int32_t)CCBitHighestSet(*(uint32_t*)&Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int32_t)CCBitHighestSet(*(uint32_t*)&Values[1]), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdNextPow2_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], (int32_t)(CCBitNextPowerOf2(Values[0]) & UINT32_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], (int32_t)(CCBitNextPowerOf2(Values[1]) & UINT32_MAX), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdMask_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForValue(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForValue(Values[1]), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdMaskLowerPow2_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForLowerPowerOf2(Values[0]), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdMaskHighestUnset_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], *(int32_t*)&(uint32_t){ CCBitMaskForUnsetValue(Values[0]) & UINT32_MAX }, @"should contain the correct value");
        XCTAssertEqual(Result[1], *(int32_t*)&(uint32_t){ CCBitMaskForUnsetValue(Values[1]) & UINT32_MAX }, @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdCountLowestUnset_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], Values[0] ? CCBitCountLowestUnset(Values[0]) : 32, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] ? CCBitCountLowestUnset(Values[1]) : 32, @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdCountHighestUnset_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(CCBitMaskForUnsetValue(Values[0]) & UINT32_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(CCBitMaskForUnsetValue(Values[1]) & UINT32_MAX), @"should contain the correct value");
        
        CCSimdStore_s32x2(Result, CCSimdCountSet_s32x2(CCSimdLoad_s32x2(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(*(uint32_t*)&Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(*(uint32_t*)&Values[1]), @"should contain the correct value");
    }
    
    
    for (size_t Loop = 0; Loop < 31; Loop++)
    {
        const uint32_t Values[2] = { 1 << Loop, (1 << Loop) + 1 };
        uint32_t Result[2];
        
        CCSimdStore_u32x2(Result, CCSimdLowestUnset_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitLowestUnset(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestUnset(Values[1]), @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdLowestSet_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitLowestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitLowestSet(Values[1]), @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdHighestSet_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitHighestSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitHighestSet(Values[1]), @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdNextPow2_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitNextPowerOf2(Values[0]) & UINT32_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitNextPowerOf2(Values[1]) & UINT32_MAX, @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdMask_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForValue(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForValue(Values[1]), @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdMaskLowerPow2_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForLowerPowerOf2(Values[0]), @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdMaskHighestUnset_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitMaskForUnsetValue(Values[0]) & UINT32_MAX, @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitMaskForUnsetValue(Values[1]) & UINT32_MAX, @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdCountLowestUnset_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], Values[0] ? CCBitCountLowestUnset(Values[0]) : 32, @"should contain the correct value");
        XCTAssertEqual(Result[1], Values[1] ? CCBitCountLowestUnset(Values[1]) : 32, @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdCountHighestUnset_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(CCBitMaskForUnsetValue(Values[0]) & UINT32_MAX), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(CCBitMaskForUnsetValue(Values[1]) & UINT32_MAX), @"should contain the correct value");
        
        CCSimdStore_u32x2(Result, CCSimdCountSet_u32x2(CCSimdLoad_u32x2(Values)));
        XCTAssertEqual(Result[0], CCBitCountSet(Values[0]), @"should contain the correct value");
        XCTAssertEqual(Result[1], CCBitCountSet(Values[1]), @"should contain the correct value");
    }
}

-(void) testComparisons
{
    int8_t Result_s8[8];
    const CCSimd_s8x8 VecA_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 0, 1, 0, 1, 0, 1, 0, 1 });
    const CCSimd_s8x8 VecB_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 0, -1, 0, -1, 0, -1, 0, -1 });
    const CCSimd_s8x8 VecC_s8x8 = CCSimdLoad_s8x8((int8_t[8]){ 1, 1, 1, 1, 1, 1, 1, 1 });
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual((uint8_t)Result_s8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareEqual_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareNotEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareNotEqual_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual((uint8_t)Result_s8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareEqual_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareEqual_s8x8(VecC_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareNotEqual_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual((uint8_t)Result_s8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareNotEqual_s8x8(VecC_s8x8, VecB_s8x8));
    XCTAssertEqual((uint8_t)Result_s8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareEqual_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareEqual_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareEqual_s8x8(VecC_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareNotEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareNotEqual_s8x8(VecA_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareNotEqual_s8x8(VecB_s8x8, VecC_s8x8));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareNotEqual_s8x8(VecC_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareLessThan_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareLessThanEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual((uint8_t)Result_s8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareGreaterThan_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdMaskCompareGreaterThanEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual((uint8_t)Result_s8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual((uint8_t)Result_s8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareLessThan_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareLessThanEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 0, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareGreaterThan_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    CCSimdStore_s8x8(Result_s8, CCSimdCompareGreaterThanEqual_s8x8(VecA_s8x8, VecB_s8x8));
    XCTAssertEqual(Result_s8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s8[7], 1, @"should contain the correct value");
    
    
    uint8_t Result_u8[8];
    const CCSimd_u8x8 VecA_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 0, 1, 0, 1, 0, 1, 0, 1 });
    const CCSimd_u8x8 VecB_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 0, -1, 0, -1, 0, -1, 0, -1 });
    const CCSimd_u8x8 VecC_u8x8 = CCSimdLoad_u8x8((uint8_t[8]){ 1, 1, 1, 1, 1, 1, 1, 1 });
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareEqual_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareNotEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareNotEqual_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareEqual_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareEqual_u8x8(VecC_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareNotEqual_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareNotEqual_u8x8(VecC_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareEqual_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareEqual_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareEqual_u8x8(VecC_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareNotEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareNotEqual_u8x8(VecA_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareNotEqual_u8x8(VecB_u8x8, VecC_u8x8));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareNotEqual_u8x8(VecC_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareLessThan_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareLessThanEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0xff, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareGreaterThan_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdMaskCompareGreaterThanEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0xff, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareLessThan_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareLessThanEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 1, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareGreaterThan_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    CCSimdStore_u8x8(Result_u8, CCSimdCompareGreaterThanEqual_u8x8(VecA_u8x8, VecB_u8x8));
    XCTAssertEqual(Result_u8[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[3], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[4], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[5], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u8[6], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u8[7], 0, @"should contain the correct value");
    
    
    int16_t Result_s16[4];
    const CCSimd_s16x4 VecA_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 0, 1, 0, 1 });
    const CCSimd_s16x4 VecB_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 0, -1, 0, -1 });
    const CCSimd_s16x4 VecC_s16x4 = CCSimdLoad_s16x4((int16_t[4]){ 1, 1, 1, 1 });
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual((uint16_t)Result_s16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareEqual_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareNotEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareNotEqual_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual((uint16_t)Result_s16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareEqual_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareEqual_s16x4(VecC_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareNotEqual_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual((uint16_t)Result_s16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareNotEqual_s16x4(VecC_s16x4, VecB_s16x4));
    XCTAssertEqual((uint16_t)Result_s16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareEqual_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareEqual_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareEqual_s16x4(VecC_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareNotEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareNotEqual_s16x4(VecA_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareNotEqual_s16x4(VecB_s16x4, VecC_s16x4));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareNotEqual_s16x4(VecC_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareLessThan_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareLessThanEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual((uint16_t)Result_s16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareGreaterThan_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdMaskCompareGreaterThanEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual((uint16_t)Result_s16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual((uint16_t)Result_s16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareLessThan_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareLessThanEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 0, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareGreaterThan_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    CCSimdStore_s16x4(Result_s16, CCSimdCompareGreaterThanEqual_s16x4(VecA_s16x4, VecB_s16x4));
    XCTAssertEqual(Result_s16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s16[3], 1, @"should contain the correct value");
    
    
    uint16_t Result_u16[4];
    const CCSimd_u16x4 VecA_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 0, 1, 0, 1 });
    const CCSimd_u16x4 VecB_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 0, -1, 0, -1 });
    const CCSimd_u16x4 VecC_u16x4 = CCSimdLoad_u16x4((uint16_t[4]){ 1, 1, 1, 1 });
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareEqual_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareNotEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareNotEqual_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareEqual_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareEqual_u16x4(VecC_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareNotEqual_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareNotEqual_u16x4(VecC_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareEqual_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareEqual_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareEqual_u16x4(VecC_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareNotEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareNotEqual_u16x4(VecA_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareNotEqual_u16x4(VecB_u16x4, VecC_u16x4));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareNotEqual_u16x4(VecC_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareLessThan_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareLessThanEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0xffff, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareGreaterThan_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdMaskCompareGreaterThanEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0xffff, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareLessThan_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareLessThanEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 1, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareGreaterThan_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    CCSimdStore_u16x4(Result_u16, CCSimdCompareGreaterThanEqual_u16x4(VecA_u16x4, VecB_u16x4));
    XCTAssertEqual(Result_u16[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[1], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u16[2], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u16[3], 0, @"should contain the correct value");
    
    
    int32_t Result_s32[2];
    const CCSimd_s32x2 VecA_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 0, 1 });
    const CCSimd_s32x2 VecB_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 0, -1 });
    const CCSimd_s32x2 VecC_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 1, 1 });
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareEqual_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareNotEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareNotEqual_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareEqual_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareEqual_s32x2(VecC_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareNotEqual_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareNotEqual_s32x2(VecC_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareEqual_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareEqual_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareEqual_s32x2(VecC_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareNotEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareNotEqual_s32x2(VecA_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareNotEqual_s32x2(VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareNotEqual_s32x2(VecC_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareLessThan_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareLessThanEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareGreaterThan_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMaskCompareGreaterThanEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareLessThan_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareLessThanEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 0, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareGreaterThan_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdCompareGreaterThanEqual_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 1, @"should contain the correct value");
    
    
    uint32_t Result_u32[2];
    const CCSimd_u32x2 VecA_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 0, 1 });
    const CCSimd_u32x2 VecB_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 0, -1 });
    const CCSimd_u32x2 VecC_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 1, 1 });
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareNotEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareNotEqual_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_u32x2(VecC_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareNotEqual_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareNotEqual_u32x2(VecC_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareEqual_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareEqual_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareEqual_u32x2(VecC_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareNotEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareNotEqual_u32x2(VecA_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareNotEqual_u32x2(VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareNotEqual_u32x2(VecC_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareLessThan_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareLessThanEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareGreaterThan_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareGreaterThanEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareLessThan_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareLessThanEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 1, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareGreaterThan_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdCompareGreaterThanEqual_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 1, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    
    float Result_f32[2];
    const CCSimd_f32x2 VecA_f32x2 = CCSimdLoad_f32x2((float[2]){ 0, 1.0f });
    const CCSimd_f32x2 VecB_f32x2 = CCSimdLoad_f32x2((float[2]){ 0, -1.0f });
    const CCSimd_f32x2 VecC_f32x2 = CCSimdLoad_f32x2((float[2]){ 1.0f, 1.0f });
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_u32[0], 0xffffffff, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_f32x2(VecA_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0xffffffff, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_f32x2(VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_u32x2(Result_u32, CCSimdMaskCompareEqual_f32x2(VecC_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 0, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCompareEqual_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 1.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 0, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCompareEqual_f32x2(VecA_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 1.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCompareEqual_f32x2(VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 0, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCompareEqual_f32x2(VecC_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 0, @"should contain the correct value");
}

-(void) testMathFunctions
{
    const float Values[2] = { -2.0f, -5.0f };
    float Result[2];
    
    CCSimdStore_f32x2(Result, CCSimdExp_f32x2(CCSimdLoad_f32x2(Values)));
    
    XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], expf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", expf(Values[0]), Result[0]);
    XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], expf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", expf(Values[1]), Result[1]);
    
    for (size_t Loop = 0; Loop < 44; Loop += 2)
    {
        const float Values[2] = { 0.000000000001f * powf(2.0f, Loop), 0.0000000000015f * powf(2.0f, Loop) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdExp_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], expf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", expf(Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], expf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", expf(Values[1]), Result[1]);
    }
    
    
    CCSimdStore_f32x2(Result, CCSimdExp2_f32x2(CCSimdLoad_f32x2(Values)));
    
    XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], exp2f(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", exp2f(Values[0]), Result[0]);
    XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], exp2f(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", exp2f(Values[1]), Result[1]);
    
    for (size_t Loop = 0; Loop < 44; Loop += 2)
    {
        const float Values[2] = { 0.000000000001f * powf(2.0f, Loop), 0.0000000000015f * powf(2.0f, Loop) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdExp2_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], exp2f(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", exp2f(Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], exp2f(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", exp2f(Values[1]), Result[1]);
    }
    
    
    for (size_t Loop = 0; Loop < 44; Loop += 2)
    {
        const float Values[2] = { 0.000000000001f * powf(2.0f, Loop), 0.0000000000015f * powf(2.0f, Loop) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdLog_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], logf(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", logf(Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], logf(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", logf(Values[1]), Result[1]);
    }
    
    
    for (size_t Loop = 0; Loop < 44; Loop += 2)
    {
        const float Values[2] = { 0.000000000001f * powf(2.0f, Loop), 0.0000000000015f * powf(2.0f, Loop) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdLog2_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], log2f(Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", log2f(Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], log2f(Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", log2f(Values[1]), Result[1]);
    }
    
    
    CCSimdStore_f32x2(Result, CCSimdPow_f32x2(CCSimdFill_f32x2(2.0f), CCSimdLoad_f32x2(Values)));
    
    XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], powf(2.0f, Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(2.0f, Values[0]), Result[0]);
    XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], powf(2.0f, Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(2.0f, Values[1]), Result[1]);
    
    for (size_t Loop = 0; Loop < 44; Loop += 2)
    {
        const float Values[2] = { 0.000000000001f * powf(2.0f, Loop), 0.0000000000015f * powf(2.0f, Loop) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPow_f32x2(CCSimdFill_f32x2(2.0f), CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], powf(2.0f, Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(2.0f, Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], powf(2.0f, Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(2.0f, Values[1]), Result[1]);
    }
    
    
    CCSimdStore_f32x2(Result, CCSimdPow_f32x2(CCSimdFill_f32x2(5.5f), CCSimdLoad_f32x2(Values)));
    
    XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], powf(5.5f, Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(5.5f, Values[0]), Result[0]);
    XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], powf(5.5f, Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(5.5f, Values[1]), Result[1]);
    
    for (size_t Loop = 0; Loop < 42; Loop += 2)
    {
        const float Values[2] = { 0.000000000001f * powf(2.0f, Loop), 0.0000000000015f * powf(2.0f, Loop) };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPow_f32x2(CCSimdFill_f32x2(5.5f), CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], powf(5.5f, Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(5.5f, Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], powf(5.5f, Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(5.5f, Values[1]), Result[1]);
    }
    
    
    for (size_t Loop = 0; Loop < 44; Loop += 2)
    {
        const float Values[2] = { Loop, Loop + 1 };
        float Result[2];
        
        CCSimdStore_f32x2(Result, CCSimdPow2_f32x2(CCSimdLoad_f32x2(Values)));
        
        XCTAssertTrue((isinf(Result[0]) && isinf(Values[0])) || CCFloatEqualAbsolute(Result[0], powf(2.0f, Values[0]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(2.0f, Values[0]), Result[0]);
        XCTAssertTrue((isinf(Result[1]) && isinf(Values[1])) || CCFloatEqualAbsolute(Result[1], powf(2.0f, Values[1]), 0.01f), @"should contain the correct value (approx: %f) instead got: %f", powf(2.0f, Values[1]), Result[1]);
    }
}

-(void) testArithmetic
{
    int32_t Result_s32[2];
    const CCSimd_s32x2 VecA_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 10, 11 });
    const CCSimd_s32x2 VecB_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 2, 4 });
    const CCSimd_s32x2 VecC_s32x2 = CCSimdLoad_s32x2((int32_t[2]){ 5, 6 });
    
    CCSimdStore_s32x2(Result_s32, CCSimdAdd_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 12, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 15, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdSub_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 7, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMul_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 20, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 44, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMadd_s32x2(VecA_s32x2, VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 25, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 50, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMsub_s32x2(VecA_s32x2, VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 38, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdNegMadd_s32x2(VecA_s32x2, VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], -15, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -38, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdNegMsub_s32x2(VecA_s32x2, VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], -25, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -50, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdDiv_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 2, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMod_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 3, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdSum_s32x2(VecA_s32x2), 21, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdNeg_s32x2(VecA_s32x2));
    XCTAssertEqual(Result_s32[0], -10, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], -11, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMin_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 4, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdMax_s32x2(VecA_s32x2, VecB_s32x2));
    XCTAssertEqual(Result_s32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 11, @"should contain the correct value");
    
    CCSimdStore_s32x2(Result_s32, CCSimdClamp_s32x2(VecA_s32x2, VecB_s32x2, VecC_s32x2));
    XCTAssertEqual(Result_s32[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_s32[1], 6, @"should contain the correct value");
    
    
    uint32_t Result_u32[2];
    const CCSimd_u32x2 VecA_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 10, 11 });
    const CCSimd_u32x2 VecB_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 2, 4 });
    const CCSimd_u32x2 VecC_u32x2 = CCSimdLoad_u32x2((uint32_t[2]){ 5, 6 });

    CCSimdStore_u32x2(Result_u32, CCSimdAdd_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 12, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 15, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdSub_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 8, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 7, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdMul_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 20, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 44, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdMadd_u32x2(VecA_u32x2, VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 25, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 50, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdMsub_u32x2(VecA_u32x2, VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 15, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 38, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdNegMadd_u32x2(VecA_u32x2, VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], -15, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], -38, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdNegMsub_u32x2(VecA_u32x2, VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], -25, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], -50, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdDiv_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 2, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdMod_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 0, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 3, @"should contain the correct value");

    XCTAssertEqual(CCSimdSum_u32x2(VecA_u32x2), 21, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdNeg_u32x2(VecA_u32x2));
    XCTAssertEqual(Result_u32[0], -10, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], -11, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdMin_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 2, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 4, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdMax_u32x2(VecA_u32x2, VecB_u32x2));
    XCTAssertEqual(Result_u32[0], 10, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 11, @"should contain the correct value");

    CCSimdStore_u32x2(Result_u32, CCSimdClamp_u32x2(VecA_u32x2, VecB_u32x2, VecC_u32x2));
    XCTAssertEqual(Result_u32[0], 5, @"should contain the correct value");
    XCTAssertEqual(Result_u32[1], 6, @"should contain the correct value");
    
    
    float Result_f32[2];
    const CCSimd_f32x2 VecA_f32x2 = CCSimdLoad_f32x2((float[2]){ 10.0f, 11.0f });
    const CCSimd_f32x2 VecB_f32x2 = CCSimdLoad_f32x2((float[2]){ 2.0f, 4.0f });
    const CCSimd_f32x2 VecC_f32x2 = CCSimdLoad_f32x2((float[2]){ 5.0f, 6.0f });
    
    CCSimdStore_f32x2(Result_f32, CCSimdAdd_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 12.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 15.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdSub_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 8.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 7.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdMul_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 20.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 44.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdMadd_f32x2(VecA_f32x2, VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], 25.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 50.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdMsub_f32x2(VecA_f32x2, VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], 15.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 38.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdNegMadd_f32x2(VecA_f32x2, VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], -15.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -38.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdNegMsub_f32x2(VecA_f32x2, VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], -25.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -50.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdDiv_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 5.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 2.75f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdMod_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 0.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 3.0f, @"should contain the correct value");
    
    XCTAssertEqual(CCSimdSum_f32x2(VecA_f32x2), 21.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdNeg_f32x2(VecA_f32x2));
    XCTAssertEqual(Result_f32[0], -10, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -11, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdMin_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 2.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 4.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdMax_f32x2(VecA_f32x2, VecB_f32x2));
    XCTAssertEqual(Result_f32[0], 10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 11.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdClamp_f32x2(VecA_f32x2, VecB_f32x2, VecC_f32x2));
    XCTAssertEqual(Result_f32[0], 5.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 6.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdSqrt_f32x2(VecA_f32x2));
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[0], sqrtf(10.0f), 0.01f), @"should contain the correct value");
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[1], sqrtf(11.0f), 0.01f), @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdInvSqrt_f32x2(VecA_f32x2));
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[0], 1.0f / sqrtf(10.0f), 0.01f), @"should contain the correct value");
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[1], 1.0f / sqrtf(11.0f), 0.01f), @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCbrt_f32x2(VecA_f32x2));
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[0], cbrtf(10.0f), 0.01f), @"should contain the correct value");
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[1], cbrtf(11.0f), 0.01f), @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdInvCbrt_f32x2(VecA_f32x2));
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[0], 1.0f / cbrtf(10.0f), 0.01f), @"should contain the correct value");
    XCTAssertTrue(CCFloatEqualAbsolute(Result_f32[1], 1.0f / cbrtf(11.0f), 0.01f), @"should contain the correct value");
    
    const CCSimd_f32x2 VecPos_f32x2 = CCSimdLoad_f32x2((float[2]){ 10.5f, 11.5f });
    
    CCSimdStore_f32x2(Result_f32, CCSimdRoundNearestAway_f32x2(VecPos_f32x2));
    XCTAssertEqual(Result_f32[0], 11.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 12.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdRoundNearestEven_f32x2(VecPos_f32x2));
    XCTAssertEqual(Result_f32[0], 10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 12.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdRoundZero_f32x2(VecPos_f32x2));
    XCTAssertEqual(Result_f32[0], 10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 11.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdFloor_f32x2(VecPos_f32x2));
    XCTAssertEqual(Result_f32[0], 10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 11.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCeil_f32x2(VecPos_f32x2));
    XCTAssertEqual(Result_f32[0], 11.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], 12.0f, @"should contain the correct value");
    
    const CCSimd_f32x2 VecNeg_f32x2 = CCSimdLoad_f32x2((float[2]){ -10.5f, -11.5f });
    
    CCSimdStore_f32x2(Result_f32, CCSimdRoundNearestAway_f32x2(VecNeg_f32x2));
    XCTAssertEqual(Result_f32[0], -11.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -12.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdRoundNearestEven_f32x2(VecNeg_f32x2));
    XCTAssertEqual(Result_f32[0], -10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -12.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdRoundZero_f32x2(VecNeg_f32x2));
    XCTAssertEqual(Result_f32[0], -10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -11.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdFloor_f32x2(VecNeg_f32x2));
    XCTAssertEqual(Result_f32[0], -11.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -12.0f, @"should contain the correct value");
    
    CCSimdStore_f32x2(Result_f32, CCSimdCeil_f32x2(VecNeg_f32x2));
    XCTAssertEqual(Result_f32[0], -10.0f, @"should contain the correct value");
    XCTAssertEqual(Result_f32[1], -11.0f, @"should contain the correct value");
}

-(void) testMaskedArithmetic
{
    const uint8_t Masks[256] = {
        0,
        CC_SIMD_LANE_MASK(0),
        CC_SIMD_LANE_MASK(1),
        CC_SIMD_LANE_MASK(0, 1),
        CC_SIMD_LANE_MASK(2),
        CC_SIMD_LANE_MASK(0, 2),
        CC_SIMD_LANE_MASK(1, 2),
        CC_SIMD_LANE_MASK(0, 1, 2),
        CC_SIMD_LANE_MASK(3),
        CC_SIMD_LANE_MASK(0, 3),
        CC_SIMD_LANE_MASK(1, 3),
        CC_SIMD_LANE_MASK(2, 3),
        CC_SIMD_LANE_MASK(0, 1, 3),
        CC_SIMD_LANE_MASK(0, 2, 3),
        CC_SIMD_LANE_MASK(1, 2, 3),
        CC_SIMD_LANE_MASK(0, 1, 2, 3),
        CC_SIMD_LANE_MASK(4),
        CC_SIMD_LANE_MASK(0, 4),
        CC_SIMD_LANE_MASK(1, 4),
        CC_SIMD_LANE_MASK(2, 4),
        CC_SIMD_LANE_MASK(3, 4),
        CC_SIMD_LANE_MASK(0, 1, 4),
        CC_SIMD_LANE_MASK(0, 2, 4),
        CC_SIMD_LANE_MASK(0, 3, 4),
        CC_SIMD_LANE_MASK(1, 2, 4),
        CC_SIMD_LANE_MASK(1, 3, 4),
        CC_SIMD_LANE_MASK(2, 3, 4),
        CC_SIMD_LANE_MASK(0, 1, 2, 4),
        CC_SIMD_LANE_MASK(0, 1, 3, 4),
        CC_SIMD_LANE_MASK(0, 2, 3, 4),
        CC_SIMD_LANE_MASK(1, 2, 3, 4),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4),
        CC_SIMD_LANE_MASK(5),
        CC_SIMD_LANE_MASK(0, 5),
        CC_SIMD_LANE_MASK(1, 5),
        CC_SIMD_LANE_MASK(2, 5),
        CC_SIMD_LANE_MASK(3, 5),
        CC_SIMD_LANE_MASK(4, 5),
        CC_SIMD_LANE_MASK(0, 1, 5),
        CC_SIMD_LANE_MASK(0, 2, 5),
        CC_SIMD_LANE_MASK(0, 3, 5),
        CC_SIMD_LANE_MASK(0, 4, 5),
        CC_SIMD_LANE_MASK(1, 2, 5),
        CC_SIMD_LANE_MASK(1, 3, 5),
        CC_SIMD_LANE_MASK(1, 4, 5),
        CC_SIMD_LANE_MASK(2, 3, 5),
        CC_SIMD_LANE_MASK(2, 4, 5),
        CC_SIMD_LANE_MASK(3, 4, 5),
        CC_SIMD_LANE_MASK(0, 1, 2, 5),
        CC_SIMD_LANE_MASK(0, 1, 3, 5),
        CC_SIMD_LANE_MASK(0, 1, 4, 5),
        CC_SIMD_LANE_MASK(0, 2, 3, 5),
        CC_SIMD_LANE_MASK(0, 2, 4, 5),
        CC_SIMD_LANE_MASK(0, 3, 4, 5),
        CC_SIMD_LANE_MASK(1, 2, 3, 5),
        CC_SIMD_LANE_MASK(1, 2, 4, 5),
        CC_SIMD_LANE_MASK(1, 3, 4, 5),
        CC_SIMD_LANE_MASK(2, 3, 4, 5),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 5),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 5),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 5),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 5),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 5),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5),
        CC_SIMD_LANE_MASK(6),
        CC_SIMD_LANE_MASK(0, 6),
        CC_SIMD_LANE_MASK(1, 6),
        CC_SIMD_LANE_MASK(2, 6),
        CC_SIMD_LANE_MASK(3, 6),
        CC_SIMD_LANE_MASK(4, 6),
        CC_SIMD_LANE_MASK(5, 6),
        CC_SIMD_LANE_MASK(0, 1, 6),
        CC_SIMD_LANE_MASK(0, 2, 6),
        CC_SIMD_LANE_MASK(0, 3, 6),
        CC_SIMD_LANE_MASK(0, 4, 6),
        CC_SIMD_LANE_MASK(0, 5, 6),
        CC_SIMD_LANE_MASK(1, 2, 6),
        CC_SIMD_LANE_MASK(1, 3, 6),
        CC_SIMD_LANE_MASK(1, 4, 6),
        CC_SIMD_LANE_MASK(1, 5, 6),
        CC_SIMD_LANE_MASK(2, 3, 6),
        CC_SIMD_LANE_MASK(2, 4, 6),
        CC_SIMD_LANE_MASK(2, 5, 6),
        CC_SIMD_LANE_MASK(3, 4, 6),
        CC_SIMD_LANE_MASK(3, 5, 6),
        CC_SIMD_LANE_MASK(4, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 6),
        CC_SIMD_LANE_MASK(0, 1, 3, 6),
        CC_SIMD_LANE_MASK(0, 1, 4, 6),
        CC_SIMD_LANE_MASK(0, 1, 5, 6),
        CC_SIMD_LANE_MASK(0, 2, 3, 6),
        CC_SIMD_LANE_MASK(0, 2, 4, 6),
        CC_SIMD_LANE_MASK(0, 2, 5, 6),
        CC_SIMD_LANE_MASK(0, 3, 4, 6),
        CC_SIMD_LANE_MASK(0, 3, 5, 6),
        CC_SIMD_LANE_MASK(0, 4, 5, 6),
        CC_SIMD_LANE_MASK(1, 2, 3, 6),
        CC_SIMD_LANE_MASK(1, 2, 4, 6),
        CC_SIMD_LANE_MASK(1, 2, 5, 6),
        CC_SIMD_LANE_MASK(1, 3, 4, 6),
        CC_SIMD_LANE_MASK(1, 3, 5, 6),
        CC_SIMD_LANE_MASK(1, 4, 5, 6),
        CC_SIMD_LANE_MASK(2, 3, 4, 6),
        CC_SIMD_LANE_MASK(2, 3, 5, 6),
        CC_SIMD_LANE_MASK(2, 4, 5, 6),
        CC_SIMD_LANE_MASK(3, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 6),
        CC_SIMD_LANE_MASK(0, 1, 3, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 6),
        CC_SIMD_LANE_MASK(0, 2, 3, 5, 6),
        CC_SIMD_LANE_MASK(0, 2, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 6),
        CC_SIMD_LANE_MASK(1, 2, 3, 5, 6),
        CC_SIMD_LANE_MASK(1, 2, 4, 5, 6),
        CC_SIMD_LANE_MASK(1, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(2, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6),
        CC_SIMD_LANE_MASK(7),
        CC_SIMD_LANE_MASK(0, 7),
        CC_SIMD_LANE_MASK(1, 7),
        CC_SIMD_LANE_MASK(2, 7),
        CC_SIMD_LANE_MASK(3, 7),
        CC_SIMD_LANE_MASK(4, 7),
        CC_SIMD_LANE_MASK(5, 7),
        CC_SIMD_LANE_MASK(6, 7),
        CC_SIMD_LANE_MASK(0, 1, 7),
        CC_SIMD_LANE_MASK(0, 2, 7),
        CC_SIMD_LANE_MASK(0, 3, 7),
        CC_SIMD_LANE_MASK(0, 4, 7),
        CC_SIMD_LANE_MASK(0, 5, 7),
        CC_SIMD_LANE_MASK(0, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 7),
        CC_SIMD_LANE_MASK(1, 3, 7),
        CC_SIMD_LANE_MASK(1, 4, 7),
        CC_SIMD_LANE_MASK(1, 5, 7),
        CC_SIMD_LANE_MASK(1, 6, 7),
        CC_SIMD_LANE_MASK(2, 3, 7),
        CC_SIMD_LANE_MASK(2, 4, 7),
        CC_SIMD_LANE_MASK(2, 5, 7),
        CC_SIMD_LANE_MASK(2, 6, 7),
        CC_SIMD_LANE_MASK(3, 4, 7),
        CC_SIMD_LANE_MASK(3, 5, 7),
        CC_SIMD_LANE_MASK(3, 6, 7),
        CC_SIMD_LANE_MASK(4, 5, 7),
        CC_SIMD_LANE_MASK(4, 6, 7),
        CC_SIMD_LANE_MASK(5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 7),
        CC_SIMD_LANE_MASK(0, 1, 4, 7),
        CC_SIMD_LANE_MASK(0, 1, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 7),
        CC_SIMD_LANE_MASK(0, 2, 4, 7),
        CC_SIMD_LANE_MASK(0, 2, 5, 7),
        CC_SIMD_LANE_MASK(0, 2, 6, 7),
        CC_SIMD_LANE_MASK(0, 3, 4, 7),
        CC_SIMD_LANE_MASK(0, 3, 5, 7),
        CC_SIMD_LANE_MASK(0, 3, 6, 7),
        CC_SIMD_LANE_MASK(0, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 7),
        CC_SIMD_LANE_MASK(1, 2, 4, 7),
        CC_SIMD_LANE_MASK(1, 2, 5, 7),
        CC_SIMD_LANE_MASK(1, 2, 6, 7),
        CC_SIMD_LANE_MASK(1, 3, 4, 7),
        CC_SIMD_LANE_MASK(1, 3, 5, 7),
        CC_SIMD_LANE_MASK(1, 3, 6, 7),
        CC_SIMD_LANE_MASK(1, 4, 5, 7),
        CC_SIMD_LANE_MASK(1, 4, 6, 7),
        CC_SIMD_LANE_MASK(1, 5, 6, 7),
        CC_SIMD_LANE_MASK(2, 3, 4, 7),
        CC_SIMD_LANE_MASK(2, 3, 5, 7),
        CC_SIMD_LANE_MASK(2, 3, 6, 7),
        CC_SIMD_LANE_MASK(2, 4, 5, 7),
        CC_SIMD_LANE_MASK(2, 4, 6, 7),
        CC_SIMD_LANE_MASK(2, 5, 6, 7),
        CC_SIMD_LANE_MASK(3, 4, 5, 7),
        CC_SIMD_LANE_MASK(3, 4, 6, 7),
        CC_SIMD_LANE_MASK(3, 5, 6, 7),
        CC_SIMD_LANE_MASK(4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 5, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 2, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 5, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 4, 5, 7),
        CC_SIMD_LANE_MASK(1, 2, 4, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(1, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(1, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(2, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(2, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(2, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(2, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(2, 3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 2, 3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(1, 2, 3, 4, 5, 6, 7),
        CC_SIMD_LANE_MASK(0, 1, 2, 3, 4, 5, 6, 7)
    };
    
    
    const int8_t A_s8[8] = { 2, 4, 6, 8, 10, 12, 14, 16 };
    const int8_t B_s8[8] = { 10, 11, 12, 13, 14, 15, 16 };
    const CCSimd_s8x8 VecA_s8x8 = CCSimdLoad_s8x8(A_s8);
    const CCSimd_s8x8 VecB_s8x8 = CCSimdLoad_s8x8(B_s8);
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const size_t Count7 = (((256 << 7) | (0xff ^ 128)) >> Loop) & 257;
        const size_t Count6 = (((256 << 6) | (0xff ^ 64)) >> Loop) & 257;
        const size_t Count5 = (((256 << 5) | (0xff ^ 32)) >> Loop) & 257;
        const size_t Count4 = (((256 << 4) | (0xff ^ 16)) >> Loop) & 257;
        const size_t Count3 = (((256 << 3) | (0xff ^ 8)) >> Loop) & 257;
        const size_t Count2 = (((256 << 2) | (0xff ^ 4)) >> Loop) & 257;
        const size_t Count1 = (((256 << 1) | (0xff ^ 2)) >> Loop) & 257;
        const size_t Count0 = (((256 << 0) | (0xff ^ 1)) >> Loop) & 257;
        
        for (size_t V7 = 0; V7 < Count7; V7++)
        {
            for (size_t V6 = 0; V6 < Count6; V6++)
            {
                for (size_t V5 = 0; V5 < Count5; V5++)
                {
                    for (size_t V4 = 0; V4 < Count4; V4++)
                    {
                        for (size_t V3 = 0; V3 < Count3; V3++)
                        {
                            for (size_t V2 = 0; V2 < Count2; V2++)
                            {
                                for (size_t V1 = 0; V1 < Count1; V1++)
                                {
                                    for (size_t V0 = 0; V0 < Count0; V0++)
                                    {
                                        int8_t Result[8];
                                        CCSimdStore_s8x8(Result, CCSimdHadd_s8x8(VecA_s8x8, Masks[V0], Masks[V1], Masks[V2], Masks[V3], Masks[V4], Masks[V5], Masks[V6], Masks[V7]));
                                        
                                        if (Masks[V0])
                                        {
                                            XCTAssertEqual(Result[0],
                                                           (Masks[V0] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V0] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V0] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V0] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V0] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V0] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V0] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V0] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V1])
                                        {
                                            XCTAssertEqual(Result[1],
                                                           (Masks[V1] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V1] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V1] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V1] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V1] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V1] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V1] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V1] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V2])
                                        {
                                            XCTAssertEqual(Result[2],
                                                           (Masks[V2] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V2] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V2] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V2] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V2] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V2] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V2] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V2] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V3])
                                        {
                                            XCTAssertEqual(Result[3],
                                                           (Masks[V3] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V3] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V3] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V3] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V3] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V3] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V3] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V3] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V4])
                                        {
                                            XCTAssertEqual(Result[4],
                                                           (Masks[V4] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V4] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V4] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V4] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V4] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V4] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V4] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V4] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V5])
                                        {
                                            XCTAssertEqual(Result[5],
                                                           (Masks[V5] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V5] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V5] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V5] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V5] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V5] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V5] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V5] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V6])
                                        {
                                            XCTAssertEqual(Result[6],
                                                           (Masks[V6] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V6] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V6] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V6] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V6] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V6] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V6] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V6] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V7])
                                        {
                                            XCTAssertEqual(Result[7],
                                                           (Masks[V7] & (1 << 0) ? A_s8[0] : 0) +
                                                           (Masks[V7] & (1 << 1) ? A_s8[1] : 0) +
                                                           (Masks[V7] & (1 << 2) ? A_s8[2] : 0) +
                                                           (Masks[V7] & (1 << 3) ? A_s8[3] : 0) +
                                                           (Masks[V7] & (1 << 4) ? A_s8[4] : 0) +
                                                           (Masks[V7] & (1 << 5) ? A_s8[5] : 0) +
                                                           (Masks[V7] & (1 << 6) ? A_s8[6] : 0) +
                                                           (Masks[V7] & (1 << 7) ? A_s8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        
                                        CCSimdStore_s8x8(Result, CCSimdHsub_s8x8(VecA_s8x8, Masks[V0], Masks[V1], Masks[V2], Masks[V3], Masks[V4], Masks[V5], Masks[V6], Masks[V7]));
                                        
                                        if (Masks[V0])
                                        {
                                            XCTAssertEqual(Result[0], -(
                                                               (Masks[V0] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V0] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V0] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V0] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V0] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V0] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V0] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V0] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V0]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V1])
                                        {
                                            XCTAssertEqual(Result[1], -(
                                                               (Masks[V1] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V1] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V1] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V1] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V1] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V1] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V1] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V1] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V1]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V2])
                                        {
                                            XCTAssertEqual(Result[2], -(
                                                               (Masks[V2] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V2] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V2] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V2] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V2] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V2] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V2] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V2] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V2]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V2])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V3])
                                        {
                                            XCTAssertEqual(Result[3], -(
                                                               (Masks[V3] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V3] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V3] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V3] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V3] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V3] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V3] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V3] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V3]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V3])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V4])
                                        {
                                            XCTAssertEqual(Result[4], -(
                                                               (Masks[V4] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V4] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V4] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V4] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V4] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V4] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V4] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V4] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V4]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V4])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V5])
                                        {
                                            XCTAssertEqual(Result[5], -(
                                                               (Masks[V5] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V5] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V5] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V5] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V5] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V5] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V5] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V5] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V5]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V5])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V6])
                                        {
                                            XCTAssertEqual(Result[6], -(
                                                               (Masks[V6] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V6] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V6] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V6] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V6] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V6] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V6] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V6] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V6]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V6])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V7])
                                        {
                                            XCTAssertEqual(Result[7], -(
                                                               (Masks[V7] & (1 << 0) ? A_s8[0] : 0) +
                                                               (Masks[V7] & (1 << 1) ? A_s8[1] : 0) +
                                                               (Masks[V7] & (1 << 2) ? A_s8[2] : 0) +
                                                               (Masks[V7] & (1 << 3) ? A_s8[3] : 0) +
                                                               (Masks[V7] & (1 << 4) ? A_s8[4] : 0) +
                                                               (Masks[V7] & (1 << 5) ? A_s8[5] : 0) +
                                                               (Masks[V7] & (1 << 6) ? A_s8[6] : 0) +
                                                               (Masks[V7] & (1 << 7) ? A_s8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V7]) < 8 ? A_s8[CCBitCountLowestUnset(Masks[V7])] : 0) * 2)
                                                            ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        
                                        CCSimdStore_s8x8(Result, CCSimdDot_s8x8(VecA_s8x8, VecB_s8x8, Masks[V0], Masks[V1], Masks[V2], Masks[V3], Masks[V4], Masks[V5], Masks[V6], Masks[V7]));
                                        
                                        if (Masks[V0])
                                        {
                                            XCTAssertEqual(Result[0], (int8_t)(
                                                               (Masks[V0] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V0] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V0] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V0] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V0] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V0] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V0] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V0] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V1])
                                        {
                                            XCTAssertEqual(Result[1], (int8_t)(
                                                               (Masks[V1] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V1] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V1] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V1] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V1] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V1] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V1] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V1] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V2])
                                        {
                                            XCTAssertEqual(Result[2], (int8_t)(
                                                               (Masks[V2] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V2] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V2] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V2] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V2] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V2] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V2] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V2] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V3])
                                        {
                                            XCTAssertEqual(Result[3], (int8_t)(
                                                               (Masks[V3] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V3] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V3] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V3] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V3] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V3] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V3] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V3] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V4])
                                        {
                                            XCTAssertEqual(Result[4], (int8_t)(
                                                               (Masks[V4] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V4] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V4] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V4] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V4] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V4] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V4] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V4] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V5])
                                        {
                                            XCTAssertEqual(Result[5], (int8_t)(
                                                               (Masks[V5] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V5] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V5] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V5] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V5] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V5] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V5] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V5] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V6])
                                        {
                                            XCTAssertEqual(Result[6], (int8_t)(
                                                               (Masks[V6] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V6] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V6] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V6] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V6] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V6] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V6] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V6] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V7])
                                        {
                                            XCTAssertEqual(Result[7], (int8_t)(
                                                               (Masks[V7] & (1 << 0) ? (A_s8[0] * B_s8[0]) : 0) +
                                                               (Masks[V7] & (1 << 1) ? (A_s8[1] * B_s8[1]) : 0) +
                                                               (Masks[V7] & (1 << 2) ? (A_s8[2] * B_s8[2]) : 0) +
                                                               (Masks[V7] & (1 << 3) ? (A_s8[3] * B_s8[3]) : 0) +
                                                               (Masks[V7] & (1 << 4) ? (A_s8[4] * B_s8[4]) : 0) +
                                                               (Masks[V7] & (1 << 5) ? (A_s8[5] * B_s8[5]) : 0) +
                                                               (Masks[V7] & (1 << 6) ? (A_s8[6] * B_s8[6]) : 0) +
                                                               (Masks[V7] & (1 << 7) ? (A_s8[7] * B_s8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const uint8_t A_u8[8] = { 2, 4, 6, 8, 10, 12, 14, 16 };
    const uint8_t B_u8[8] = { 10, 11, 12, 13, 14, 15, 16 };
    const CCSimd_u8x8 VecA_u8x8 = CCSimdLoad_u8x8(A_u8);
    const CCSimd_u8x8 VecB_u8x8 = CCSimdLoad_u8x8(B_u8);
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        const size_t Count7 = (((256 << 7) | (0xff ^ 128)) >> Loop) & 257;
        const size_t Count6 = (((256 << 6) | (0xff ^ 64)) >> Loop) & 257;
        const size_t Count5 = (((256 << 5) | (0xff ^ 32)) >> Loop) & 257;
        const size_t Count4 = (((256 << 4) | (0xff ^ 16)) >> Loop) & 257;
        const size_t Count3 = (((256 << 3) | (0xff ^ 8)) >> Loop) & 257;
        const size_t Count2 = (((256 << 2) | (0xff ^ 4)) >> Loop) & 257;
        const size_t Count1 = (((256 << 1) | (0xff ^ 2)) >> Loop) & 257;
        const size_t Count0 = (((256 << 0) | (0xff ^ 1)) >> Loop) & 257;
        
        for (size_t V7 = 0; V7 < Count7; V7++)
        {
            for (size_t V6 = 0; V6 < Count6; V6++)
            {
                for (size_t V5 = 0; V5 < Count5; V5++)
                {
                    for (size_t V4 = 0; V4 < Count4; V4++)
                    {
                        for (size_t V3 = 0; V3 < Count3; V3++)
                        {
                            for (size_t V2 = 0; V2 < Count2; V2++)
                            {
                                for (size_t V1 = 0; V1 < Count1; V1++)
                                {
                                    for (size_t V0 = 0; V0 < Count0; V0++)
                                    {
                                        uint8_t Result[8];
                                        CCSimdStore_u8x8(Result, CCSimdHadd_u8x8(VecA_u8x8, Masks[V0], Masks[V1], Masks[V2], Masks[V3], Masks[V4], Masks[V5], Masks[V6], Masks[V7]));
                                        
                                        if (Masks[V0])
                                        {
                                            XCTAssertEqual(Result[0],
                                                           (Masks[V0] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V0] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V0] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V0] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V0] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V0] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V0] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V0] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V1])
                                        {
                                            XCTAssertEqual(Result[1],
                                                           (Masks[V1] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V1] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V1] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V1] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V1] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V1] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V1] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V1] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V2])
                                        {
                                            XCTAssertEqual(Result[2],
                                                           (Masks[V2] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V2] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V2] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V2] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V2] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V2] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V2] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V2] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V3])
                                        {
                                            XCTAssertEqual(Result[3],
                                                           (Masks[V3] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V3] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V3] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V3] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V3] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V3] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V3] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V3] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V4])
                                        {
                                            XCTAssertEqual(Result[4],
                                                           (Masks[V4] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V4] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V4] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V4] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V4] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V4] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V4] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V4] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V5])
                                        {
                                            XCTAssertEqual(Result[5],
                                                           (Masks[V5] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V5] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V5] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V5] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V5] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V5] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V5] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V5] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V6])
                                        {
                                            XCTAssertEqual(Result[6],
                                                           (Masks[V6] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V6] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V6] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V6] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V6] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V6] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V6] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V6] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V7])
                                        {
                                            XCTAssertEqual(Result[7],
                                                           (Masks[V7] & (1 << 0) ? A_u8[0] : 0) +
                                                           (Masks[V7] & (1 << 1) ? A_u8[1] : 0) +
                                                           (Masks[V7] & (1 << 2) ? A_u8[2] : 0) +
                                                           (Masks[V7] & (1 << 3) ? A_u8[3] : 0) +
                                                           (Masks[V7] & (1 << 4) ? A_u8[4] : 0) +
                                                           (Masks[V7] & (1 << 5) ? A_u8[5] : 0) +
                                                           (Masks[V7] & (1 << 6) ? A_u8[6] : 0) +
                                                           (Masks[V7] & (1 << 7) ? A_u8[7] : 0),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        
                                        CCSimdStore_u8x8(Result, CCSimdHsub_u8x8(VecA_u8x8, Masks[V0], Masks[V1], Masks[V2], Masks[V3], Masks[V4], Masks[V5], Masks[V6], Masks[V7]));
                                        
                                        if (Masks[V0])
                                        {
                                            XCTAssertEqual(Result[0], (uint8_t)-(
                                                               (Masks[V0] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V0] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V0] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V0] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V0] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V0] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V0] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V0] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V0]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V1])
                                        {
                                            XCTAssertEqual(Result[1], (uint8_t)-(
                                                               (Masks[V1] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V1] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V1] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V1] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V1] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V1] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V1] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V1] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V1]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V2])
                                        {
                                            XCTAssertEqual(Result[2], (uint8_t)-(
                                                               (Masks[V2] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V2] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V2] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V2] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V2] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V2] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V2] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V2] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V2]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V2])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V3])
                                        {
                                            XCTAssertEqual(Result[3], (uint8_t)-(
                                                               (Masks[V3] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V3] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V3] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V3] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V3] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V3] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V3] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V3] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V3]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V3])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V4])
                                        {
                                            XCTAssertEqual(Result[4], (uint8_t)-(
                                                               (Masks[V4] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V4] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V4] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V4] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V4] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V4] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V4] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V4] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V4]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V4])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V5])
                                        {
                                            XCTAssertEqual(Result[5], (uint8_t)-(
                                                               (Masks[V5] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V5] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V5] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V5] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V5] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V5] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V5] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V5] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V5]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V5])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V6])
                                        {
                                            XCTAssertEqual(Result[6], (uint8_t)-(
                                                               (Masks[V6] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V6] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V6] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V6] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V6] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V6] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V6] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V6] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V6]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V6])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V7])
                                        {
                                            XCTAssertEqual(Result[7], (uint8_t)-(
                                                               (Masks[V7] & (1 << 0) ? A_u8[0] : 0) +
                                                               (Masks[V7] & (1 << 1) ? A_u8[1] : 0) +
                                                               (Masks[V7] & (1 << 2) ? A_u8[2] : 0) +
                                                               (Masks[V7] & (1 << 3) ? A_u8[3] : 0) +
                                                               (Masks[V7] & (1 << 4) ? A_u8[4] : 0) +
                                                               (Masks[V7] & (1 << 5) ? A_u8[5] : 0) +
                                                               (Masks[V7] & (1 << 6) ? A_u8[6] : 0) +
                                                               (Masks[V7] & (1 << 7) ? A_u8[7] : 0) +
                                                               -((CCBitCountLowestUnset(Masks[V7]) < 8 ? A_u8[CCBitCountLowestUnset(Masks[V7])] : 0) * 2)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        
                                        CCSimdStore_u8x8(Result, CCSimdDot_u8x8(VecA_u8x8, VecB_u8x8, Masks[V0], Masks[V1], Masks[V2], Masks[V3], Masks[V4], Masks[V5], Masks[V6], Masks[V7]));
                                        
                                        if (Masks[V0])
                                        {
                                            XCTAssertEqual(Result[0], (uint8_t)(
                                                               (Masks[V0] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V0] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V0] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V0] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V0] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V0] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V0] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V0] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V1])
                                        {
                                            XCTAssertEqual(Result[1], (uint8_t)(
                                                               (Masks[V1] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V1] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V1] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V1] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V1] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V1] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V1] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V1] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V2])
                                        {
                                            XCTAssertEqual(Result[2], (uint8_t)(
                                                               (Masks[V2] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V2] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V2] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V2] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V2] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V2] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V2] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V2] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V3])
                                        {
                                            XCTAssertEqual(Result[3], (uint8_t)(
                                                               (Masks[V3] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V3] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V3] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V3] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V3] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V3] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V3] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V3] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V4])
                                        {
                                            XCTAssertEqual(Result[4], (uint8_t)(
                                                               (Masks[V4] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V4] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V4] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V4] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V4] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V4] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V4] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V4] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V5])
                                        {
                                            XCTAssertEqual(Result[5], (uint8_t)(
                                                               (Masks[V5] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V5] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V5] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V5] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V5] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V5] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V5] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V5] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V6])
                                        {
                                            XCTAssertEqual(Result[6], (uint8_t)(
                                                               (Masks[V6] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V6] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V6] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V6] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V6] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V6] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V6] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V6] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                        
                                        if (Masks[V7])
                                        {
                                            XCTAssertEqual(Result[7], (uint8_t)(
                                                               (Masks[V7] & (1 << 0) ? (A_u8[0] * B_u8[0]) : 0) +
                                                               (Masks[V7] & (1 << 1) ? (A_u8[1] * B_u8[1]) : 0) +
                                                               (Masks[V7] & (1 << 2) ? (A_u8[2] * B_u8[2]) : 0) +
                                                               (Masks[V7] & (1 << 3) ? (A_u8[3] * B_u8[3]) : 0) +
                                                               (Masks[V7] & (1 << 4) ? (A_u8[4] * B_u8[4]) : 0) +
                                                               (Masks[V7] & (1 << 5) ? (A_u8[5] * B_u8[5]) : 0) +
                                                               (Masks[V7] & (1 << 6) ? (A_u8[6] * B_u8[6]) : 0) +
                                                               (Masks[V7] & (1 << 7) ? (A_u8[7] * B_u8[7]) : 0)
                                                           ),
                                                           @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const int16_t A_s16[4] = { 2, 4, 6, 8 };
    const int16_t B_s16[4] = { 10, 11, 12, 13 };
    const CCSimd_s16x4 VecA_s16x4 = CCSimdLoad_s16x4(A_s16);
    const CCSimd_s16x4 VecB_s16x4 = CCSimdLoad_s16x4(B_s16);
    
    for (size_t V3 = 0; V3 < 16; V3++)
    {
        for (size_t V2 = 0; V2 < 16; V2++)
        {
            for (size_t V1 = 0; V1 < 16; V1++)
            {
                for (size_t V0 = 0; V0 < 16; V0++)
                {
                    int16_t Result[4];
                    CCSimdStore_s16x4(Result, CCSimdHadd_s16x4(VecA_s16x4, Masks[V0], Masks[V1], Masks[V2], Masks[V3]));
                    
                    if (Masks[V0])
                    {
                        XCTAssertEqual(Result[0],
                                       (Masks[V0] & (1 << 0) ? A_s16[0] : 0) +
                                       (Masks[V0] & (1 << 1) ? A_s16[1] : 0) +
                                       (Masks[V0] & (1 << 2) ? A_s16[2] : 0) +
                                       (Masks[V0] & (1 << 3) ? A_s16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V1])
                    {
                        XCTAssertEqual(Result[1],
                                       (Masks[V1] & (1 << 0) ? A_s16[0] : 0) +
                                       (Masks[V1] & (1 << 1) ? A_s16[1] : 0) +
                                       (Masks[V1] & (1 << 2) ? A_s16[2] : 0) +
                                       (Masks[V1] & (1 << 3) ? A_s16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V2])
                    {
                        XCTAssertEqual(Result[2],
                                       (Masks[V2] & (1 << 0) ? A_s16[0] : 0) +
                                       (Masks[V2] & (1 << 1) ? A_s16[1] : 0) +
                                       (Masks[V2] & (1 << 2) ? A_s16[2] : 0) +
                                       (Masks[V2] & (1 << 3) ? A_s16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V3])
                    {
                        XCTAssertEqual(Result[3],
                                       (Masks[V3] & (1 << 0) ? A_s16[0] : 0) +
                                       (Masks[V3] & (1 << 1) ? A_s16[1] : 0) +
                                       (Masks[V3] & (1 << 2) ? A_s16[2] : 0) +
                                       (Masks[V3] & (1 << 3) ? A_s16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    
                    CCSimdStore_s16x4(Result, CCSimdHsub_s16x4(VecA_s16x4, Masks[V0], Masks[V1], Masks[V2], Masks[V3]));
                    
                    if (Masks[V0])
                    {
                        XCTAssertEqual(Result[0], -(
                                           (Masks[V0] & (1 << 0) ? A_s16[0] : 0) +
                                           (Masks[V0] & (1 << 1) ? A_s16[1] : 0) +
                                           (Masks[V0] & (1 << 2) ? A_s16[2] : 0) +
                                           (Masks[V0] & (1 << 3) ? A_s16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V0]) < 4 ? A_s16[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V1])
                    {
                        XCTAssertEqual(Result[1], -(
                                           (Masks[V1] & (1 << 0) ? A_s16[0] : 0) +
                                           (Masks[V1] & (1 << 1) ? A_s16[1] : 0) +
                                           (Masks[V1] & (1 << 2) ? A_s16[2] : 0) +
                                           (Masks[V1] & (1 << 3) ? A_s16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V1]) < 4 ? A_s16[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V2])
                    {
                        XCTAssertEqual(Result[2], -(
                                           (Masks[V2] & (1 << 0) ? A_s16[0] : 0) +
                                           (Masks[V2] & (1 << 1) ? A_s16[1] : 0) +
                                           (Masks[V2] & (1 << 2) ? A_s16[2] : 0) +
                                           (Masks[V2] & (1 << 3) ? A_s16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V2]) < 4 ? A_s16[CCBitCountLowestUnset(Masks[V2])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V3])
                    {
                        XCTAssertEqual(Result[3], -(
                                           (Masks[V3] & (1 << 0) ? A_s16[0] : 0) +
                                           (Masks[V3] & (1 << 1) ? A_s16[1] : 0) +
                                           (Masks[V3] & (1 << 2) ? A_s16[2] : 0) +
                                           (Masks[V3] & (1 << 3) ? A_s16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V3]) < 4 ? A_s16[CCBitCountLowestUnset(Masks[V3])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    
                    CCSimdStore_s16x4(Result, CCSimdDot_s16x4(VecA_s16x4, VecB_s16x4, Masks[V0], Masks[V1], Masks[V2], Masks[V3]));
                    
                    if (Masks[V0])
                    {
                        XCTAssertEqual(Result[0],
                                       (Masks[V0] & (1 << 0) ? (A_s16[0] * B_s16[0]) : 0) +
                                       (Masks[V0] & (1 << 1) ? (A_s16[1] * B_s16[1]) : 0) +
                                       (Masks[V0] & (1 << 2) ? (A_s16[2] * B_s16[2]) : 0) +
                                       (Masks[V0] & (1 << 3) ? (A_s16[3] * B_s16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V1])
                    {
                        XCTAssertEqual(Result[1],
                                       (Masks[V1] & (1 << 0) ? (A_s16[0] * B_s16[0]) : 0) +
                                       (Masks[V1] & (1 << 1) ? (A_s16[1] * B_s16[1]) : 0) +
                                       (Masks[V1] & (1 << 2) ? (A_s16[2] * B_s16[2]) : 0) +
                                       (Masks[V1] & (1 << 3) ? (A_s16[3] * B_s16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V2])
                    {
                        XCTAssertEqual(Result[2],
                                       (Masks[V2] & (1 << 0) ? (A_s16[0] * B_s16[0]) : 0) +
                                       (Masks[V2] & (1 << 1) ? (A_s16[1] * B_s16[1]) : 0) +
                                       (Masks[V2] & (1 << 2) ? (A_s16[2] * B_s16[2]) : 0) +
                                       (Masks[V2] & (1 << 3) ? (A_s16[3] * B_s16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V3])
                    {
                        XCTAssertEqual(Result[3],
                                       (Masks[V3] & (1 << 0) ? (A_s16[0] * B_s16[0]) : 0) +
                                       (Masks[V3] & (1 << 1) ? (A_s16[1] * B_s16[1]) : 0) +
                                       (Masks[V3] & (1 << 2) ? (A_s16[2] * B_s16[2]) : 0) +
                                       (Masks[V3] & (1 << 3) ? (A_s16[3] * B_s16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                }
            }
        }
    }
    
    
    const uint16_t A_u16[4] = { 2, 4, 6, 8 };
    const uint16_t B_u16[4] = { 10, 11, 12, 13 };
    const CCSimd_u16x4 VecA_u16x4 = CCSimdLoad_u16x4(A_u16);
    const CCSimd_u16x4 VecB_u16x4 = CCSimdLoad_u16x4(B_u16);
    
    for (size_t V3 = 0; V3 < 16; V3++)
    {
        for (size_t V2 = 0; V2 < 16; V2++)
        {
            for (size_t V1 = 0; V1 < 16; V1++)
            {
                for (size_t V0 = 0; V0 < 16; V0++)
                {
                    uint16_t Result[4];
                    CCSimdStore_u16x4(Result, CCSimdHadd_u16x4(VecA_u16x4, Masks[V0], Masks[V1], Masks[V2], Masks[V3]));
                    
                    if (Masks[V0])
                    {
                        XCTAssertEqual(Result[0],
                                       (Masks[V0] & (1 << 0) ? A_u16[0] : 0) +
                                       (Masks[V0] & (1 << 1) ? A_u16[1] : 0) +
                                       (Masks[V0] & (1 << 2) ? A_u16[2] : 0) +
                                       (Masks[V0] & (1 << 3) ? A_u16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V1])
                    {
                        XCTAssertEqual(Result[1],
                                       (Masks[V1] & (1 << 0) ? A_u16[0] : 0) +
                                       (Masks[V1] & (1 << 1) ? A_u16[1] : 0) +
                                       (Masks[V1] & (1 << 2) ? A_u16[2] : 0) +
                                       (Masks[V1] & (1 << 3) ? A_u16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V2])
                    {
                        XCTAssertEqual(Result[2],
                                       (Masks[V2] & (1 << 0) ? A_u16[0] : 0) +
                                       (Masks[V2] & (1 << 1) ? A_u16[1] : 0) +
                                       (Masks[V2] & (1 << 2) ? A_u16[2] : 0) +
                                       (Masks[V2] & (1 << 3) ? A_u16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V3])
                    {
                        XCTAssertEqual(Result[3],
                                       (Masks[V3] & (1 << 0) ? A_u16[0] : 0) +
                                       (Masks[V3] & (1 << 1) ? A_u16[1] : 0) +
                                       (Masks[V3] & (1 << 2) ? A_u16[2] : 0) +
                                       (Masks[V3] & (1 << 3) ? A_u16[3] : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    
                    CCSimdStore_u16x4(Result, CCSimdHsub_u16x4(VecA_u16x4, Masks[V0], Masks[V1], Masks[V2], Masks[V3]));

                    if (Masks[V0])
                    {
                        XCTAssertEqual(Result[0], (uint16_t)-(
                                           (Masks[V0] & (1 << 0) ? A_u16[0] : 0) +
                                           (Masks[V0] & (1 << 1) ? A_u16[1] : 0) +
                                           (Masks[V0] & (1 << 2) ? A_u16[2] : 0) +
                                           (Masks[V0] & (1 << 3) ? A_u16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V0]) < 4 ? A_u16[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }

                    if (Masks[V1])
                    {
                        XCTAssertEqual(Result[1], (uint16_t)-(
                                           (Masks[V1] & (1 << 0) ? A_u16[0] : 0) +
                                           (Masks[V1] & (1 << 1) ? A_u16[1] : 0) +
                                           (Masks[V1] & (1 << 2) ? A_u16[2] : 0) +
                                           (Masks[V1] & (1 << 3) ? A_u16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V1]) < 4 ? A_u16[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }

                    if (Masks[V2])
                    {
                        XCTAssertEqual(Result[2], (uint16_t)-(
                                           (Masks[V2] & (1 << 0) ? A_u16[0] : 0) +
                                           (Masks[V2] & (1 << 1) ? A_u16[1] : 0) +
                                           (Masks[V2] & (1 << 2) ? A_u16[2] : 0) +
                                           (Masks[V2] & (1 << 3) ? A_u16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V2]) < 4 ? A_u16[CCBitCountLowestUnset(Masks[V2])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }

                    if (Masks[V3])
                    {
                        XCTAssertEqual(Result[3], (uint16_t)-(
                                           (Masks[V3] & (1 << 0) ? A_u16[0] : 0) +
                                           (Masks[V3] & (1 << 1) ? A_u16[1] : 0) +
                                           (Masks[V3] & (1 << 2) ? A_u16[2] : 0) +
                                           (Masks[V3] & (1 << 3) ? A_u16[3] : 0) +
                                           -((CCBitCountLowestUnset(Masks[V3]) < 4 ? A_u16[CCBitCountLowestUnset(Masks[V3])] : 0) * 2)
                                       ),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    
                    CCSimdStore_u16x4(Result, CCSimdDot_u16x4(VecA_u16x4, VecB_u16x4, Masks[V0], Masks[V1], Masks[V2], Masks[V3]));
                    
                    if (Masks[V0])
                    {
                        XCTAssertEqual(Result[0],
                                       (Masks[V0] & (1 << 0) ? (A_u16[0] * B_u16[0]) : 0) +
                                       (Masks[V0] & (1 << 1) ? (A_u16[1] * B_u16[1]) : 0) +
                                       (Masks[V0] & (1 << 2) ? (A_u16[2] * B_u16[2]) : 0) +
                                       (Masks[V0] & (1 << 3) ? (A_u16[3] * B_u16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V1])
                    {
                        XCTAssertEqual(Result[1],
                                       (Masks[V1] & (1 << 0) ? (A_u16[0] * B_u16[0]) : 0) +
                                       (Masks[V1] & (1 << 1) ? (A_u16[1] * B_u16[1]) : 0) +
                                       (Masks[V1] & (1 << 2) ? (A_u16[2] * B_u16[2]) : 0) +
                                       (Masks[V1] & (1 << 3) ? (A_u16[3] * B_u16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V2])
                    {
                        XCTAssertEqual(Result[2],
                                       (Masks[V2] & (1 << 0) ? (A_u16[0] * B_u16[0]) : 0) +
                                       (Masks[V2] & (1 << 1) ? (A_u16[1] * B_u16[1]) : 0) +
                                       (Masks[V2] & (1 << 2) ? (A_u16[2] * B_u16[2]) : 0) +
                                       (Masks[V2] & (1 << 3) ? (A_u16[3] * B_u16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                    
                    if (Masks[V3])
                    {
                        XCTAssertEqual(Result[3],
                                       (Masks[V3] & (1 << 0) ? (A_u16[0] * B_u16[0]) : 0) +
                                       (Masks[V3] & (1 << 1) ? (A_u16[1] * B_u16[1]) : 0) +
                                       (Masks[V3] & (1 << 2) ? (A_u16[2] * B_u16[2]) : 0) +
                                       (Masks[V3] & (1 << 3) ? (A_u16[3] * B_u16[3]) : 0),
                                       @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    }
                }
            }
        }
    }
    
    
    const int32_t A_s32[2] = { 2, 4 };
    const int32_t B_s32[2] = { 10, 11 };
    const CCSimd_s32x2 VecA_s32x2 = CCSimdLoad_s32x2(A_s32);
    const CCSimd_s32x2 VecB_s32x2 = CCSimdLoad_s32x2(B_s32);
    
    for (size_t V1 = 0; V1 < 4; V1++)
    {
        for (size_t V0 = 0; V0 < 4; V0++)
        {
            int32_t Result[2];
            CCSimdStore_s32x2(Result, CCSimdHadd_s32x2(VecA_s32x2, Masks[V0], Masks[V1]));
            
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0],
                               (Masks[V0] & (1 << 0) ? A_s32[0] : 0) +
                               (Masks[V0] & (1 << 1) ? A_s32[1] : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            if (Masks[V1])
            {
                XCTAssertEqual(Result[1],
                               (Masks[V1] & (1 << 0) ? A_s32[0] : 0) +
                               (Masks[V1] & (1 << 1) ? A_s32[1] : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            
            CCSimdStore_s32x2(Result, CCSimdHsub_s32x2(VecA_s32x2, Masks[V0], Masks[V1]));
                        
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0], -(
                                   (Masks[V0] & (1 << 0) ? A_s32[0] : 0) +
                                   (Masks[V0] & (1 << 1) ? A_s32[1] : 0) +
                                   -((CCBitCountLowestUnset(Masks[V0]) < 4 ? A_s32[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                               ),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }

            if (Masks[V1])
            {
                XCTAssertEqual(Result[1], -(
                                   (Masks[V1] & (1 << 0) ? A_s32[0] : 0) +
                                   (Masks[V1] & (1 << 1) ? A_s32[1] : 0) +
                                   -((CCBitCountLowestUnset(Masks[V1]) < 4 ? A_s32[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                               ),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            
            CCSimdStore_s32x2(Result, CCSimdDot_s32x2(VecA_s32x2, VecB_s32x2, Masks[V0], Masks[V1]));
            
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0],
                               (Masks[V0] & (1 << 0) ? (A_s32[0] * B_s32[0]) : 0) +
                               (Masks[V0] & (1 << 1) ? (A_s32[1] * B_s32[1]) : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            if (Masks[V1])
            {
                XCTAssertEqual(Result[1],
                               (Masks[V1] & (1 << 0) ? (A_s32[0] * B_s32[0]) : 0) +
                               (Masks[V1] & (1 << 1) ? (A_s32[1] * B_s32[1]) : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
        }
    }
    
    
    const uint32_t A_u32[2] = { 2, 4 };
    const uint32_t B_u32[2] = { 10, 11 };
    const CCSimd_u32x2 VecA_u32x2 = CCSimdLoad_u32x2(A_u32);
    const CCSimd_u32x2 VecB_u32x2 = CCSimdLoad_u32x2(B_u32);
    
    for (size_t V1 = 0; V1 < 4; V1++)
    {
        for (size_t V0 = 0; V0 < 4; V0++)
        {
            uint32_t Result[2];
            CCSimdStore_u32x2(Result, CCSimdHadd_u32x2(VecA_u32x2, Masks[V0], Masks[V1]));
            
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0],
                               (Masks[V0] & (1 << 0) ? A_u32[0] : 0) +
                               (Masks[V0] & (1 << 1) ? A_u32[1] : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            if (Masks[V1])
            {
                XCTAssertEqual(Result[1],
                               (Masks[V1] & (1 << 0) ? A_u32[0] : 0) +
                               (Masks[V1] & (1 << 1) ? A_u32[1] : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            
            CCSimdStore_u32x2(Result, CCSimdHsub_u32x2(VecA_u32x2, Masks[V0], Masks[V1]));
                        
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0], -(
                                   (Masks[V0] & (1 << 0) ? A_u32[0] : 0) +
                                   (Masks[V0] & (1 << 1) ? A_u32[1] : 0) +
                                   -((CCBitCountLowestUnset(Masks[V0]) < 4 ? A_u32[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                               ),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }

            if (Masks[V1])
            {
                XCTAssertEqual(Result[1], -(
                                   (Masks[V1] & (1 << 0) ? A_u32[0] : 0) +
                                   (Masks[V1] & (1 << 1) ? A_u32[1] : 0) +
                                   -((CCBitCountLowestUnset(Masks[V1]) < 4 ? A_u32[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                               ),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            
            CCSimdStore_u32x2(Result, CCSimdDot_u32x2(VecA_u32x2, VecB_u32x2, Masks[V0], Masks[V1]));
            
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0],
                               (Masks[V0] & (1 << 0) ? (A_u32[0] * B_u32[0]) : 0) +
                               (Masks[V0] & (1 << 1) ? (A_u32[1] * B_u32[1]) : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            if (Masks[V1])
            {
                XCTAssertEqual(Result[1],
                               (Masks[V1] & (1 << 0) ? (A_u32[0] * B_u32[0]) : 0) +
                               (Masks[V1] & (1 << 1) ? (A_u32[1] * B_u32[1]) : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
        }
    }
    
    
    const float A_f32[2] = { 2.0f, 4.0f };
    const float B_f32[2] = { 10.0f, 11.0f };
    const CCSimd_f32x2 VecA_f32x2 = CCSimdLoad_f32x2(A_f32);
    const CCSimd_f32x2 VecB_f32x2 = CCSimdLoad_f32x2(B_f32);
    
    for (size_t V1 = 0; V1 < 4; V1++)
    {
        for (size_t V0 = 0; V0 < 4; V0++)
        {
            float Result[2];
            CCSimdStore_f32x2(Result, CCSimdHadd_f32x2(VecA_f32x2, Masks[V0], Masks[V1]));
            
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0],
                               (Masks[V0] & (1 << 0) ? A_f32[0] : 0) +
                               (Masks[V0] & (1 << 1) ? A_f32[1] : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            if (Masks[V1])
            {
                XCTAssertEqual(Result[1],
                               (Masks[V1] & (1 << 0) ? A_f32[0] : 0) +
                               (Masks[V1] & (1 << 1) ? A_f32[1] : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            
            CCSimdStore_f32x2(Result, CCSimdHsub_f32x2(VecA_f32x2, Masks[V0], Masks[V1]));
                        
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0], -(
                                   (Masks[V0] & (1 << 0) ? A_f32[0] : 0) +
                                   (Masks[V0] & (1 << 1) ? A_f32[1] : 0) +
                                   -((CCBitCountLowestUnset(Masks[V0]) < 4 ? A_f32[CCBitCountLowestUnset(Masks[V0])] : 0) * 2)
                               ),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }

            if (Masks[V1])
            {
                XCTAssertEqual(Result[1], -(
                                   (Masks[V1] & (1 << 0) ? A_f32[0] : 0) +
                                   (Masks[V1] & (1 << 1) ? A_f32[1] : 0) +
                                   -((CCBitCountLowestUnset(Masks[V1]) < 4 ? A_f32[CCBitCountLowestUnset(Masks[V1])] : 0) * 2)
                               ),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            
            CCSimdStore_f32x2(Result, CCSimdDot_f32x2(VecA_f32x2, VecB_f32x2, Masks[V0], Masks[V1]));
            
            if (Masks[V0])
            {
                XCTAssertEqual(Result[0],
                               (Masks[V0] & (1 << 0) ? (A_f32[0] * B_f32[0]) : 0) +
                               (Masks[V0] & (1 << 1) ? (A_f32[1] * B_f32[1]) : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
            
            if (Masks[V1])
            {
                XCTAssertEqual(Result[1],
                               (Masks[V1] & (1 << 0) ? (A_f32[0] * B_f32[0]) : 0) +
                               (Masks[V1] & (1 << 1) ? (A_f32[1] * B_f32[1]) : 0),
                               @"should contain the correct value (%zu %zu)", V0, V1);
            }
        }
    }
}

-(void) testInterleave
{
    const int8_t A_s8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    const int8_t B_s8[8] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    const CCSimd_s8x8 VecA_s8x8 = CCSimdLoad_s8x8(A_s8);
    const CCSimd_s8x8 VecB_s8x8 = CCSimdLoad_s8x8(B_s8);
    
    for (size_t V7 = 0; V7 < 2; V7++)
    {
        for (size_t V6 = 0; V6 < 2; V6++)
        {
            for (size_t V5 = 0; V5 < 2; V5++)
            {
                for (size_t V4 = 0; V4 < 2; V4++)
                {
                    for (size_t V3 = 0; V3 < 2; V3++)
                    {
                        for (size_t V2 = 0; V2 < 2; V2++)
                        {
                            for (size_t V1 = 0; V1 < 2; V1++)
                            {
                                for (size_t V0 = 0; V0 < 2; V0++)
                                {
                                    int8_t Result[8];
                                    CCSimdStore_s8x8(Result, CCSimdInterleave_s8x8(VecA_s8x8, VecB_s8x8, V0, V1, V2, V3, V4, V5, V6, V7));
                                    
                                    XCTAssertEqual(Result[0], (V0 ? B_s8[0] : A_s8[0]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[1], (V1 ? B_s8[1] : A_s8[1]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[2], (V2 ? B_s8[2] : A_s8[2]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[3], (V3 ? B_s8[3] : A_s8[3]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[4], (V4 ? B_s8[4] : A_s8[4]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[5], (V5 ? B_s8[5] : A_s8[5]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[6], (V6 ? B_s8[6] : A_s8[6]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[7], (V7 ? B_s8[7] : A_s8[7]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const uint8_t A_u8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    const uint8_t B_u8[8] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    const CCSimd_u8x8 VecA_u8x8 = CCSimdLoad_u8x8(A_u8);
    const CCSimd_u8x8 VecB_u8x8 = CCSimdLoad_u8x8(B_u8);
    
    for (size_t V7 = 0; V7 < 2; V7++)
    {
        for (size_t V6 = 0; V6 < 2; V6++)
        {
            for (size_t V5 = 0; V5 < 2; V5++)
            {
                for (size_t V4 = 0; V4 < 2; V4++)
                {
                    for (size_t V3 = 0; V3 < 2; V3++)
                    {
                        for (size_t V2 = 0; V2 < 2; V2++)
                        {
                            for (size_t V1 = 0; V1 < 2; V1++)
                            {
                                for (size_t V0 = 0; V0 < 2; V0++)
                                {
                                    uint8_t Result[8];
                                    CCSimdStore_u8x8(Result, CCSimdInterleave_u8x8(VecA_u8x8, VecB_u8x8, V0, V1, V2, V3, V4, V5, V6, V7));
                                    
                                    XCTAssertEqual(Result[0], (V0 ? B_u8[0] : A_u8[0]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[1], (V1 ? B_u8[1] : A_u8[1]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[2], (V2 ? B_u8[2] : A_u8[2]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[3], (V3 ? B_u8[3] : A_u8[3]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[4], (V4 ? B_u8[4] : A_u8[4]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[5], (V5 ? B_u8[5] : A_u8[5]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[6], (V6 ? B_u8[6] : A_u8[6]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[7], (V7 ? B_u8[7] : A_u8[7]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const int16_t A_s16[4] = { 0, 1, 2, 3 };
    const int16_t B_s16[4] = { 10, 11, 12, 13 };
    const CCSimd_s16x4 VecA_s16x4 = CCSimdLoad_s16x4(A_s16);
    const CCSimd_s16x4 VecB_s16x4 = CCSimdLoad_s16x4(B_s16);
    
    for (size_t V3 = 0; V3 < 2; V3++)
    {
        for (size_t V2 = 0; V2 < 2; V2++)
        {
            for (size_t V1 = 0; V1 < 2; V1++)
            {
                for (size_t V0 = 0; V0 < 2; V0++)
                {
                    int16_t Result[4];
                    CCSimdStore_s16x4(Result, CCSimdInterleave_s16x4(VecA_s16x4, VecB_s16x4, V0, V1, V2, V3));
                    
                    XCTAssertEqual(Result[0], (V0 ? B_s16[0] : A_s16[0]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[1], (V1 ? B_s16[1] : A_s16[1]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[2], (V2 ? B_s16[2] : A_s16[2]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[3], (V3 ? B_s16[3] : A_s16[3]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                }
            }
        }
    }
    
    
    const uint16_t A_u16[4] = { 0, 1, 2, 3 };
    const uint16_t B_u16[4] = { 10, 11, 12, 13 };
    const CCSimd_u16x4 VecA_u16x4 = CCSimdLoad_u16x4(A_u16);
    const CCSimd_u16x4 VecB_u16x4 = CCSimdLoad_u16x4(B_u16);
    
    for (size_t V3 = 0; V3 < 2; V3++)
    {
        for (size_t V2 = 0; V2 < 2; V2++)
        {
            for (size_t V1 = 0; V1 < 2; V1++)
            {
                for (size_t V0 = 0; V0 < 2; V0++)
                {
                    uint16_t Result[4];
                    CCSimdStore_u16x4(Result, CCSimdInterleave_u16x4(VecA_u16x4, VecB_u16x4, V0, V1, V2, V3));
                    
                    XCTAssertEqual(Result[0], (V0 ? B_u16[0] : A_u16[0]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[1], (V1 ? B_u16[1] : A_u16[1]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[2], (V2 ? B_u16[2] : A_u16[2]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[3], (V3 ? B_u16[3] : A_u16[3]), @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                }
            }
        }
    }
    
    
    const int32_t A_s32[2] = { 0, 1 };
    const int32_t B_s32[2] = { 10, 11 };
    const CCSimd_s32x2 VecA_s32x2 = CCSimdLoad_s32x2(A_s32);
    const CCSimd_s32x2 VecB_s32x2 = CCSimdLoad_s32x2(B_s32);
    
    for (size_t V1 = 0; V1 < 2; V1++)
    {
        for (size_t V0 = 0; V0 < 2; V0++)
        {
            int32_t Result[2];
            CCSimdStore_s32x2(Result, CCSimdInterleave_s32x2(VecA_s32x2, VecB_s32x2, V0, V1));
            
            XCTAssertEqual(Result[0], (V0 ? B_s32[0] : A_s32[0]), @"should contain the correct value (%zu %zu)", V0, V1);
            XCTAssertEqual(Result[1], (V1 ? B_s32[1] : A_s32[1]), @"should contain the correct value (%zu %zu)", V0, V1);
        }
    }
    
    
    const uint32_t A_u32[2] = { 0, 1 };
    const uint32_t B_u32[2] = { 10, 11 };
    const CCSimd_u32x2 VecA_u32x2 = CCSimdLoad_u32x2(A_u32);
    const CCSimd_u32x2 VecB_u32x2 = CCSimdLoad_u32x2(B_u32);
    
    for (size_t V1 = 0; V1 < 2; V1++)
    {
        for (size_t V0 = 0; V0 < 2; V0++)
        {
            uint32_t Result[2];
            CCSimdStore_u32x2(Result, CCSimdInterleave_u32x2(VecA_u32x2, VecB_u32x2, V0, V1));
            
            XCTAssertEqual(Result[0], (V0 ? B_u32[0] : A_u32[0]), @"should contain the correct value (%zu %zu)", V0, V1);
            XCTAssertEqual(Result[1], (V1 ? B_u32[1] : A_u32[1]), @"should contain the correct value (%zu %zu)", V0, V1);
        }
    }
    
    
    const float A_f32[2] = { 0.0f, 1.0f };
    const float B_f32[2] = { 10.0f, 11.0f };
    const CCSimd_f32x2 VecA_f32x2 = CCSimdLoad_f32x2(A_f32);
    const CCSimd_f32x2 VecB_f32x2 = CCSimdLoad_f32x2(B_f32);
    
    for (size_t V1 = 0; V1 < 2; V1++)
    {
        for (size_t V0 = 0; V0 < 2; V0++)
        {
            float Result[2];
            CCSimdStore_f32x2(Result, CCSimdInterleave_f32x2(VecA_f32x2, VecB_f32x2, V0, V1));
            
            XCTAssertEqual(Result[0], (V0 ? B_f32[0] : A_f32[0]), @"should contain the correct value (%zu %zu)", V0, V1);
            XCTAssertEqual(Result[1], (V1 ? B_f32[1] : A_f32[1]), @"should contain the correct value (%zu %zu)", V0, V1);
        }
    }
}

-(void) testMerge
{
    const int8_t A_s8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    const int8_t B_s8[8] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    const CCSimd_s8x8 VecA_s8x8 = CCSimdLoad_s8x8(A_s8);
    const CCSimd_s8x8 VecB_s8x8 = CCSimdLoad_s8x8(B_s8);
    
    for (size_t Interleave = 0; Interleave < 256; Interleave++)
    {
        for (size_t V7 = 0; V7 < 8; V7++)
        {
            for (size_t V6 = 0; V6 < 8; V6++)
            {
                for (size_t V5 = 0; V5 < 8; V5++)
                {
                    for (size_t V4 = 0; V4 < 8; V4++)
                    {
                        for (size_t V3 = 0; V3 < 8; V3++)
                        {
                            for (size_t V2 = 0; V2 < 8; V2++)
                            {
                                for (size_t V1 = 0; V1 < 8; V1++)
                                {
                                    for (size_t V0 = 0; V0 < 8; V0++)
                                    {
                                        int8_t Result[8];
                                        CCSimdStore_s8x8(Result, CCSimdMerge_s8x8(VecA_s8x8, VecB_s8x8,
                                                                                  ((Interleave & 128) >> 3) | V0,
                                                                                  ((Interleave & 64) >> 2) | V1,
                                                                                  ((Interleave & 32) >> 1) | V2,
                                                                                  (Interleave & 16) | V3,
                                                                                  ((Interleave & 8) << 1) | V4,
                                                                                  ((Interleave & 4) << 2) | V5,
                                                                                  ((Interleave & 2) << 3) | V6,
                                                                                  ((Interleave & 1) << 4) | V7));
                                        
                                        XCTAssertEqual(Result[0], (Interleave & 128 ? B_s8[V0] : A_s8[V0]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[1], (Interleave & 64 ? B_s8[V1] : A_s8[V1]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[2], (Interleave & 32 ? B_s8[V2] : A_s8[V2]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[3], (Interleave & 16 ? B_s8[V3] : A_s8[V3]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[4], (Interleave & 8 ? B_s8[V4] : A_s8[V4]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[5], (Interleave & 4 ? B_s8[V5] : A_s8[V5]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[6], (Interleave & 2 ? B_s8[V6] : A_s8[V6]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[7], (Interleave & 1 ? B_s8[V7] : A_s8[V7]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const uint8_t A_u8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    const uint8_t B_u8[8] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    const CCSimd_u8x8 VecA_u8x8 = CCSimdLoad_u8x8(A_u8);
    const CCSimd_u8x8 VecB_u8x8 = CCSimdLoad_u8x8(B_u8);
    
    for (size_t Interleave = 0; Interleave < 256; Interleave++)
    {
        for (size_t V7 = 0; V7 < 8; V7++)
        {
            for (size_t V6 = 0; V6 < 8; V6++)
            {
                for (size_t V5 = 0; V5 < 8; V5++)
                {
                    for (size_t V4 = 0; V4 < 8; V4++)
                    {
                        for (size_t V3 = 0; V3 < 8; V3++)
                        {
                            for (size_t V2 = 0; V2 < 8; V2++)
                            {
                                for (size_t V1 = 0; V1 < 8; V1++)
                                {
                                    for (size_t V0 = 0; V0 < 8; V0++)
                                    {
                                        uint8_t Result[8];
                                        CCSimdStore_u8x8(Result, CCSimdMerge_u8x8(VecA_u8x8, VecB_u8x8,
                                                                                  ((Interleave & 128) >> 3) | V0,
                                                                                  ((Interleave & 64) >> 2) | V1,
                                                                                  ((Interleave & 32) >> 1) | V2,
                                                                                  (Interleave & 16) | V3,
                                                                                  ((Interleave & 8) << 1) | V4,
                                                                                  ((Interleave & 4) << 2) | V5,
                                                                                  ((Interleave & 2) << 3) | V6,
                                                                                  ((Interleave & 1) << 4) | V7));
                                        
                                        XCTAssertEqual(Result[0], (Interleave & 128 ? B_u8[V0] : A_u8[V0]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[1], (Interleave & 64 ? B_u8[V1] : A_u8[V1]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[2], (Interleave & 32 ? B_u8[V2] : A_u8[V2]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[3], (Interleave & 16 ? B_u8[V3] : A_u8[V3]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[4], (Interleave & 8 ? B_u8[V4] : A_u8[V4]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[5], (Interleave & 4 ? B_u8[V5] : A_u8[V5]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[6], (Interleave & 2 ? B_u8[V6] : A_u8[V6]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                        XCTAssertEqual(Result[7], (Interleave & 1 ? B_u8[V7] : A_u8[V7]), @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7, Interleave);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const int16_t A_s16[4] = { 0, 1, 2, 3 };
    const int16_t B_s16[4] = { 10, 11, 12, 13 };
    const CCSimd_s16x4 VecA_s16x4 = CCSimdLoad_s16x4(A_s16);
    const CCSimd_s16x4 VecB_s16x4 = CCSimdLoad_s16x4(B_s16);
    
    for (size_t Interleave = 0; Interleave < 16; Interleave++)
    {
        for (size_t V3 = 0; V3 < 4; V3++)
        {
            for (size_t V2 = 0; V2 < 4; V2++)
            {
                for (size_t V1 = 0; V1 < 4; V1++)
                {
                    for (size_t V0 = 0; V0 < 4; V0++)
                    {
                        int16_t Result[4];
                        CCSimdStore_s16x4(Result, CCSimdMerge_s16x4(VecA_s16x4, VecB_s16x4, ((Interleave & 8) << 1) | V0, ((Interleave & 4) << 2) | V1, ((Interleave & 2) << 3) | V2, ((Interleave & 1) << 4) | V3));
                        
                        XCTAssertEqual(Result[0], (Interleave & 8 ? B_s16[V0] : A_s16[V0]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                        XCTAssertEqual(Result[1], (Interleave & 4 ? B_s16[V1] : A_s16[V1]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                        XCTAssertEqual(Result[2], (Interleave & 2 ? B_s16[V2] : A_s16[V2]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                        XCTAssertEqual(Result[3], (Interleave & 1 ? B_s16[V3] : A_s16[V3]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                    }
                }
            }
        }
    }
    
    
    const uint16_t A_u16[4] = { 0, 1, 2, 3 };
    const uint16_t B_u16[4] = { 10, 11, 12, 13 };
    const CCSimd_u16x4 VecA_u16x4 = CCSimdLoad_u16x4(A_u16);
    const CCSimd_u16x4 VecB_u16x4 = CCSimdLoad_u16x4(B_u16);
    
    for (size_t Interleave = 0; Interleave < 16; Interleave++)
    {
        for (size_t V3 = 0; V3 < 4; V3++)
        {
            for (size_t V2 = 0; V2 < 4; V2++)
            {
                for (size_t V1 = 0; V1 < 4; V1++)
                {
                    for (size_t V0 = 0; V0 < 4; V0++)
                    {
                        uint16_t Result[4];
                        CCSimdStore_u16x4(Result, CCSimdMerge_u16x4(VecA_u16x4, VecB_u16x4, ((Interleave & 8) << 1) | V0, ((Interleave & 4) << 2) | V1, ((Interleave & 2) << 3) | V2, ((Interleave & 1) << 4) | V3));
                        
                        XCTAssertEqual(Result[0], (Interleave & 8 ? B_u16[V0] : A_u16[V0]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                        XCTAssertEqual(Result[1], (Interleave & 4 ? B_u16[V1] : A_u16[V1]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                        XCTAssertEqual(Result[2], (Interleave & 2 ? B_u16[V2] : A_u16[V2]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                        XCTAssertEqual(Result[3], (Interleave & 1 ? B_u16[V3] : A_u16[V3]), @"should contain the correct value (%zu %zu %zu %zu : %zu)", V0, V1, V2, V3, Interleave);
                    }
                }
            }
        }
    }
    
    
    const int32_t A_s32[2] = { 0, 1 };
    const int32_t B_s32[2] = { 10, 11 };
    const CCSimd_s32x2 VecA_s32x2 = CCSimdLoad_s32x2(A_s32);
    const CCSimd_s32x2 VecB_s32x2 = CCSimdLoad_s32x2(B_s32);
    
    for (size_t Interleave = 0; Interleave < 4; Interleave++)
    {
        for (size_t V1 = 0; V1 < 2; V1++)
        {
            for (size_t V0 = 0; V0 < 2; V0++)
            {
                int32_t Result[2];
                CCSimdStore_s32x2(Result, CCSimdMerge_s32x2(VecA_s32x2, VecB_s32x2, ((Interleave & 2) << 3) | V0, ((Interleave & 1) << 4) | V1));
                
                XCTAssertEqual(Result[0], (Interleave & 2 ? B_s32[V0] : A_s32[V0]), @"should contain the correct value (%zu %zu : %zu)", V0, V1, Interleave);
                XCTAssertEqual(Result[1], (Interleave & 1 ? B_s32[V1] : A_s32[V1]), @"should contain the correct value (%zu %zu : %zu)", V0, V1, Interleave);
            }
        }
    }
    
    
    const uint32_t A_u32[2] = { 0, 1 };
    const uint32_t B_u32[2] = { 10, 11 };
    const CCSimd_u32x2 VecA_u32x2 = CCSimdLoad_u32x2(A_u32);
    const CCSimd_u32x2 VecB_u32x2 = CCSimdLoad_u32x2(B_u32);
    
    for (size_t Interleave = 0; Interleave < 4; Interleave++)
    {
        for (size_t V1 = 0; V1 < 2; V1++)
        {
            for (size_t V0 = 0; V0 < 2; V0++)
            {
                uint32_t Result[2];
                CCSimdStore_u32x2(Result, CCSimdMerge_u32x2(VecA_u32x2, VecB_u32x2, ((Interleave & 2) << 3) | V0, ((Interleave & 1) << 4) | V1));
                
                XCTAssertEqual(Result[0], (Interleave & 2 ? B_u32[V0] : A_u32[V0]), @"should contain the correct value (%zu %zu : %zu)", V0, V1, Interleave);
                XCTAssertEqual(Result[1], (Interleave & 1 ? B_u32[V1] : A_u32[V1]), @"should contain the correct value (%zu %zu : %zu)", V0, V1, Interleave);
            }
        }
    }
    
    
    const float A_f32[2] = { 0.0f, 1.0f };
    const float B_f32[2] = { 10.0f, 11.0f };
    const CCSimd_f32x2 VecA_f32x2 = CCSimdLoad_f32x2(A_f32);
    const CCSimd_f32x2 VecB_f32x2 = CCSimdLoad_f32x2(B_f32);
    
    for (size_t Interleave = 0; Interleave < 4; Interleave++)
    {
        for (size_t V1 = 0; V1 < 2; V1++)
        {
            for (size_t V0 = 0; V0 < 2; V0++)
            {
                float Result[2];
                CCSimdStore_f32x2(Result, CCSimdMerge_f32x2(VecA_f32x2, VecB_f32x2, ((Interleave & 2) << 3) | V0, ((Interleave & 1) << 4) | V1));
                
                XCTAssertEqual(Result[0], (Interleave & 2 ? B_f32[V0] : A_f32[V0]), @"should contain the correct value (%zu %zu : %zu)", V0, V1, Interleave);
                XCTAssertEqual(Result[1], (Interleave & 1 ? B_f32[V1] : A_f32[V1]), @"should contain the correct value (%zu %zu : %zu)", V0, V1, Interleave);
            }
        }
    }
}

-(void) testSwizzle
{
    const int8_t Values_s8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    const CCSimd_s8x8 Vec_s8x8 = CCSimdLoad_s8x8(Values_s8);
    
    for (size_t V7 = 0; V7 < 8; V7++)
    {
        for (size_t V6 = 0; V6 < 8; V6++)
        {
            for (size_t V5 = 0; V5 < 8; V5++)
            {
                for (size_t V4 = 0; V4 < 8; V4++)
                {
                    for (size_t V3 = 0; V3 < 8; V3++)
                    {
                        for (size_t V2 = 0; V2 < 8; V2++)
                        {
                            for (size_t V1 = 0; V1 < 8; V1++)
                            {
                                for (size_t V0 = 0; V0 < 8; V0++)
                                {
                                    int8_t Result[8];
                                    CCSimdStore_s8x8(Result, CCSimdSwizzle_s8x8(Vec_s8x8, V0, V1, V2, V3, V4, V5, V6, V7));
                                    
                                    XCTAssertEqual(Result[0], Values_s8[V0], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[1], Values_s8[V1], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[2], Values_s8[V2], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[3], Values_s8[V3], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[4], Values_s8[V4], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[5], Values_s8[V5], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[6], Values_s8[V6], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[7], Values_s8[V7], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const uint8_t Values_u8[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    const CCSimd_u8x8 Vec_u8x8 = CCSimdLoad_u8x8(Values_u8);
    
    for (size_t V7 = 0; V7 < 8; V7++)
    {
        for (size_t V6 = 0; V6 < 8; V6++)
        {
            for (size_t V5 = 0; V5 < 8; V5++)
            {
                for (size_t V4 = 0; V4 < 8; V4++)
                {
                    for (size_t V3 = 0; V3 < 8; V3++)
                    {
                        for (size_t V2 = 0; V2 < 8; V2++)
                        {
                            for (size_t V1 = 0; V1 < 8; V1++)
                            {
                                for (size_t V0 = 0; V0 < 8; V0++)
                                {
                                    uint8_t Result[8];
                                    CCSimdStore_u8x8(Result, CCSimdSwizzle_u8x8(Vec_u8x8, V0, V1, V2, V3, V4, V5, V6, V7));
                                    
                                    XCTAssertEqual(Result[0], Values_u8[V0], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[1], Values_u8[V1], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[2], Values_u8[V2], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[3], Values_u8[V3], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[4], Values_u8[V4], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[5], Values_u8[V5], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[6], Values_u8[V6], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                    XCTAssertEqual(Result[7], Values_u8[V7], @"should contain the correct value (%zu %zu %zu %zu %zu %zu %zu %zu)", V0, V1, V2, V3, V4, V5, V6, V7);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    const int16_t Values_s16[4] = { 0, 1, 2, 3 };
    const CCSimd_s16x4 Vec_s16x4 = CCSimdLoad_s16x4(Values_s16);
    
    for (size_t V3 = 0; V3 < 4; V3++)
    {
        for (size_t V2 = 0; V2 < 4; V2++)
        {
            for (size_t V1 = 0; V1 < 4; V1++)
            {
                for (size_t V0 = 0; V0 < 4; V0++)
                {
                    int16_t Result[4];
                    CCSimdStore_s16x4(Result, CCSimdSwizzle_s16x4(Vec_s16x4, V0, V1, V2, V3));
                    
                    XCTAssertEqual(Result[0], Values_s16[V0], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[1], Values_s16[V1], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[2], Values_s16[V2], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[3], Values_s16[V3], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                }
            }
        }
    }
    
    
    const uint16_t Values_u16[4] = { 0, 1, 2, 3 };
    const CCSimd_u16x4 Vec_u16x4 = CCSimdLoad_u16x4(Values_u16);
    
    for (size_t V3 = 0; V3 < 4; V3++)
    {
        for (size_t V2 = 0; V2 < 4; V2++)
        {
            for (size_t V1 = 0; V1 < 4; V1++)
            {
                for (size_t V0 = 0; V0 < 4; V0++)
                {
                    uint16_t Result[4];
                    CCSimdStore_u16x4(Result, CCSimdSwizzle_u16x4(Vec_u16x4, V0, V1, V2, V3));
                    
                    XCTAssertEqual(Result[0], Values_u16[V0], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[1], Values_u16[V1], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[2], Values_u16[V2], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                    XCTAssertEqual(Result[3], Values_u16[V3], @"should contain the correct value (%zu %zu %zu %zu)", V0, V1, V2, V3);
                }
            }
        }
    }
    
    
    const int32_t Values_s32[2] = { 0, 1 };
    const CCSimd_s32x2 Vec_s32x2 = CCSimdLoad_s32x2(Values_s32);
    
    for (size_t V1 = 0; V1 < 2; V1++)
    {
        for (size_t V0 = 0; V0 < 2; V0++)
        {
            int32_t Result[2];
            CCSimdStore_s32x2(Result, CCSimdSwizzle_s32x2(Vec_s32x2, V0, V1));
            
            XCTAssertEqual(Result[0], Values_s32[V0], @"should contain the correct value (%zu %zu)", V0, V1);
            XCTAssertEqual(Result[1], Values_s32[V1], @"should contain the correct value (%zu %zu)", V0, V1);
        }
    }
    
    
    const uint32_t Values_u32[2] = { 0, 1 };
    const CCSimd_u32x2 Vec_u32x2 = CCSimdLoad_u32x2(Values_u32);
    
    for (size_t V1 = 0; V1 < 2; V1++)
    {
        for (size_t V0 = 0; V0 < 2; V0++)
        {
            uint32_t Result[2];
            CCSimdStore_u32x2(Result, CCSimdSwizzle_u32x2(Vec_u32x2, V0, V1));
            
            XCTAssertEqual(Result[0], Values_u32[V0], @"should contain the correct value (%zu %zu)", V0, V1);
            XCTAssertEqual(Result[1], Values_u32[V1], @"should contain the correct value (%zu %zu)", V0, V1);
        }
    }
    
    
    const float Values_f32[2] = { 0.0f, 1.0f };
    const CCSimd_f32x2 Vec_f32x2 = CCSimdLoad_f32x2(Values_f32);
    
    for (size_t V1 = 0; V1 < 2; V1++)
    {
        for (size_t V0 = 0; V0 < 2; V0++)
        {
            float Result[2];
            CCSimdStore_f32x2(Result, CCSimdSwizzle_f32x2(Vec_f32x2, V0, V1));
            
            XCTAssertEqual(Result[0], Values_f32[V0], @"should contain the correct value (%zu %zu)", V0, V1);
            XCTAssertEqual(Result[1], Values_f32[V1], @"should contain the correct value (%zu %zu)", V0, V1);
        }
    }
}

@end
