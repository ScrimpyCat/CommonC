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
