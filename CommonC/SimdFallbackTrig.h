/*
 *  Copyright (c) 2026, Stefan Johnson
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

#ifndef T
#error T is not defined
#endif

#define CC_SIMD_T_LANE_COUNT(x) CC_SIMD_TYPE_LANE_COUNT(T, x)

#define CC_SIMD_T CC_SIMD_TYPE(T, CC_SIMD_N_T_LANES)

#define CC_SIMD_U CC_SIMD_TYPE(CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)

#define CC_SIMD_S CC_SIMD_TYPE(CC_SIMD_TO(T, s), CC_SIMD_N_T_LANES)


#define CCSimd_T_Cast_U CC_CAT(CC_SIMD_NAME(CCSimd, T, CC_SIMD_N_T_LANES), CC_SIMD_NAME(_Cast, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES))
#define CCSimd_U_Cast_T CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES), CC_SIMD_NAME(_Cast, T, CC_SIMD_N_T_LANES))
#define CCSimd_S_Cast_T CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_TO(T, s), CC_SIMD_N_T_LANES), CC_SIMD_NAME(_Cast, T, CC_SIMD_N_T_LANES))
#define CCSimd_U_Reinterpret_T CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES), CC_SIMD_NAME(_Reinterpret, T, CC_SIMD_N_T_LANES))
#define CCSimd_T_Reinterpret_U CC_CAT(CC_SIMD_NAME(CCSimd, T, CC_SIMD_N_T_LANES), CC_SIMD_NAME(_Reinterpret, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES))
#define CCSimd_T_Reinterpret_S CC_CAT(CC_SIMD_NAME(CCSimd, T, CC_SIMD_N_T_LANES), CC_SIMD_NAME(_Reinterpret, CC_SIMD_TO(T, s), CC_SIMD_N_T_LANES))
#define CCSimdFill_T CC_SIMD_NAME(CCSimdFill, T, CC_SIMD_N_T_LANES)
#define CCSimdFill_U CC_SIMD_NAME(CCSimdFill, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdFill_S CC_SIMD_NAME(CCSimdFill, CC_SIMD_TO(T, s), CC_SIMD_N_T_LANES)
#define CCSimdZero CC_SIMD_NAME(CCSimdZero, T, CC_SIMD_N_T_LANES)
#define CCSimdAdd_T CC_SIMD_NAME(CCSimdAdd, T, CC_SIMD_N_T_LANES)
#define CCSimdAdd_S CC_SIMD_NAME(CCSimdAdd, CC_SIMD_TO(T, s), CC_SIMD_N_T_LANES)
#define CCSimdSub CC_SIMD_NAME(CCSimdSub, T, CC_SIMD_N_T_LANES)
#define CCSimdMul CC_SIMD_NAME(CCSimdMul, T, CC_SIMD_N_T_LANES)
#define CCSimdDiv CC_SIMD_NAME(CCSimdDiv, T, CC_SIMD_N_T_LANES)
#define CCSimdMod CC_SIMD_NAME(CCSimdMod, T, CC_SIMD_N_T_LANES)
#define CCSimdNeg CC_SIMD_NAME(CCSimdNeg, T, CC_SIMD_N_T_LANES)
#define CCSimdAbs CC_SIMD_NAME(CCSimdAbs, T, CC_SIMD_N_T_LANES)
#define CCSimdFloor CC_SIMD_NAME(CCSimdFloor, T, CC_SIMD_N_T_LANES)
#define CCSimdRoundZero CC_SIMD_NAME(CCSimdRoundZero, T, CC_SIMD_N_T_LANES)
#define CCSimdMadd CC_SIMD_NAME(CCSimdMadd, T, CC_SIMD_N_T_LANES)
#define CCSimdNegMadd CC_SIMD_NAME(CCSimdNegMadd, T, CC_SIMD_N_T_LANES)
#define CCSimdMax CC_SIMD_NAME(CCSimdMax, T, CC_SIMD_N_T_LANES)
#define CCSimdClamp CC_SIMD_NAME(CCSimdClamp, T, CC_SIMD_N_T_LANES)
#define CCSimdAnd CC_SIMD_NAME(CCSimdAnd, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdAndNot CC_SIMD_NAME(CCSimdAndNot, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdOr CC_SIMD_NAME(CCSimdOr, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdXor CC_SIMD_NAME(CCSimdXor, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdShiftLeftN_U CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdShiftLeftN_S CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(T, s), CC_SIMD_N_T_LANES)
#define CCSimdShiftRightN CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(T, u), CC_SIMD_N_T_LANES)
#define CCSimdMaskCompareLessThan_T CC_SIMD_NAME(CCSimdMaskCompareLessThan, T, CC_SIMD_N_T_LANES)
#define CCSimdMaskCompareLessThanEqual_T CC_SIMD_NAME(CCSimdMaskCompareLessThanEqual, T, CC_SIMD_N_T_LANES)
#define CCSimdMaskCompareNotEqual_T CC_SIMD_NAME(CCSimdMaskCompareNotEqual, T, CC_SIMD_N_T_LANES)
#define CCSimdCompareLessThan CC_SIMD_NAME(CCSimdCompareLessThan, T, CC_SIMD_N_T_LANES)

#define CCSimdPosPiRadSin CC_SIMD_NAME(CCSimdPosPiRadSin, T, CC_SIMD_N_T_LANES)
#define CCSimdHalfPiRadCos CC_SIMD_NAME(CCSimdHalfPiRadCos, T, CC_SIMD_N_T_LANES)
#define CCSimdPosSin CC_SIMD_NAME(CCSimdPosSin, T, CC_SIMD_N_T_LANES)
#define CCSimdPiRadSin CC_SIMD_NAME(CCSimdPiRadSin, T, CC_SIMD_N_T_LANES)
#define CCSimdSin CC_SIMD_NAME(CCSimdSin, T, CC_SIMD_N_T_LANES)
#define CCSimdArcSin CC_SIMD_NAME(CCSimdArcSin, T, CC_SIMD_N_T_LANES)
#define CCSimdCos CC_SIMD_NAME(CCSimdCos, T, CC_SIMD_N_T_LANES)
#define CCSimdArcCos CC_SIMD_NAME(CCSimdArcCos, T, CC_SIMD_N_T_LANES)
#define CCSimdTan CC_SIMD_NAME(CCSimdTan, T, CC_SIMD_N_T_LANES)
#define CCSimdQtrPiArcTan CC_SIMD_NAME(CCSimdQtrPiArcTan, T, CC_SIMD_N_T_LANES)
#define CCSimdArcTan CC_SIMD_NAME(CCSimdArcTan, T, CC_SIMD_N_T_LANES)
#define CCSimdArcTan2 CC_SIMD_NAME(CCSimdArcTan2, T, CC_SIMD_N_T_LANES)
#define CCSimdCsc CC_SIMD_NAME(CCSimdCsc, T, CC_SIMD_N_T_LANES)
#define CCSimdSec CC_SIMD_NAME(CCSimdSec, T, CC_SIMD_N_T_LANES)
#define CCSimdCot CC_SIMD_NAME(CCSimdCot, T, CC_SIMD_N_T_LANES)
#define CCSimdLog2 CC_SIMD_NAME(CCSimdLog2, T, CC_SIMD_N_T_LANES)
#define CCSimdLog CC_SIMD_NAME(CCSimdLog, T, CC_SIMD_N_T_LANES)
#define CCSimdPow CC_SIMD_NAME(CCSimdPow, T, CC_SIMD_N_T_LANES)
#define CCSimdPow2 CC_SIMD_NAME(CCSimdPow2, T, CC_SIMD_N_T_LANES)
#define CCSimdExp CC_SIMD_NAME(CCSimdExp, T, CC_SIMD_N_T_LANES)
#define CCSimdExp2 CC_SIMD_NAME(CCSimdExp2, T, CC_SIMD_N_T_LANES)
#define CCSimdCbrt CC_SIMD_NAME(CCSimdCbrt, T, CC_SIMD_N_T_LANES)
#define CCSimdInvCbrt CC_SIMD_NAME(CCSimdInvCbrt, T, CC_SIMD_N_T_LANES)


#ifdef CC_SIMD_MISSING_CCSimdPosPiRadSin
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdPosPiRadSin)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdPosPiRadSin(const CC_SIMD_T a)
{
    const CC_SIMD_T Pi = CCSimdFill_T(CC_PI);
    const CC_SIMD_T M = CCSimdFill_T(4.0);
    const CC_SIMD_T PiSqr5 = CCSimdFill_T(5.0 * CC_PI * CC_PI);
    
    CC_SIMD_T Value = a;
    
    // Bhāskara I's sine approximation
    Value = CCSimdMul(M, CCSimdMul(Value, CCSimdSub(Pi, Value)));
    Value = CCSimdDiv(CCSimdMul(M, Value), CCSimdSub(PiSqr5, Value));
    
    return Value;
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdHalfPiRadCos
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdHalfPiRadCos)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdHalfPiRadCos(const CC_SIMD_T a)
{
#if CC_SIMD_HALF_PI_RAD_COS_ACCURACY == 0
    const CC_SIMD_T M = CCSimdFill_T(4.0);
    const CC_SIMD_T PiSqr = CCSimdFill_T(CC_PI * CC_PI);
    
    CC_SIMD_T Value = a;
    
    // Bhāskara I's cosine approximation
    Value = CCSimdMul(Value, Value);
    Value = CCSimdDiv(CCSimdNegMadd(M, Value, PiSqr), CCSimdAdd_T(PiSqr, Value));
    
    return Value;
#elif CC_SIMD_HALF_PI_RAD_COS_ACCURACY >= 1
    // More accurate but requires more gpr use
    
    // https://math.stackexchange.com/questions/976462/a-1400-years-old-approximation-to-the-sine-function-by-mahabhaskariya-of-bhaskar/4763600#4763600
    // (9): 0.99940323+𝑥^2(−0.49558085+0.036791683𝑥^2)
    
    const CC_SIMD_T X = CCSimdFill_T(0.99940323);
    const CC_SIMD_T Y = CCSimdFill_T(-0.49558085);
    const CC_SIMD_T Z = CCSimdFill_T(0.036791683);
    
    CC_SIMD_T Value = a;
    
    Value = CCSimdMul(Value, Value);
    Value = CCSimdMadd(Value, CCSimdMadd(Value, Z, Y), X);
    
    return Value;
#endif
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdPosSin
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdPosSin)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdPosSin(const CC_SIMD_T a)
{
    const CC_SIMD_T Pi2 = CCSimdFill_T(CC_PI * 2.0);
    const CC_SIMD_T Pi = CCSimdFill_T(CC_PI);
    const CC_SIMD_T NegOne = CCSimdFill_T(-1.0);
    
    CC_SIMD_T Value = a;
    
    CC_SIMD_T Sign = CCSimdFloor(CCSimdDiv(CCSimdMod(Value, Pi2), Pi));
    Sign = CCSimdSub(CCSimdNeg(CCSimdAdd_T(Sign, Sign)), NegOne);
    
    Value = CCSimdMod(Value, Pi);
    
    Value = CCSimdPosPiRadSin(Value);
    
    return CCSimdMul(Value, Sign);
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdPiRadSin
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdPiRadSin)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdPiRadSin(const CC_SIMD_T a)
{
    CC_SIMD_T Value = CCSimdAbs(a);
    
    CC_SIMD_U Sign = CCSimdShiftLeftN_U(CCSimdShiftRightN(CCSimd_U_Reinterpret_T(a), 31), 31);
    
    Value = CCSimdPosPiRadSin(Value);
    
    return CCSimd_T_Reinterpret_U(CCSimdXor(CCSimd_U_Reinterpret_T(Value), Sign));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdSin
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdSin)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdSin(const CC_SIMD_T a)
{
    const CC_SIMD_T Pi2 = CCSimdFill_T(CC_PI * 2.0);
    const CC_SIMD_T Pi = CCSimdFill_T(CC_PI);
    const CC_SIMD_T NegOne = CCSimdFill_T(-1.0);
    
    CC_SIMD_T Value = CCSimdAbs(a);
    
    CC_SIMD_T Sign = CCSimdFloor(CCSimdDiv(CCSimdMod(Value, Pi2), Pi));
    Sign = CCSimdSub(CCSimdNeg(CCSimdAdd_T(Sign, Sign)), NegOne);
    Sign = CCSimd_T_Reinterpret_U(CCSimdXor(CCSimd_U_Reinterpret_T(Sign), CCSimdShiftLeftN_U(CCSimdShiftRightN(CCSimd_U_Reinterpret_T(a), 31), 31)));
    
    Value = CCSimdMod(Value, Pi);
    
    Value = CCSimdPosPiRadSin(Value);
    
    return CCSimdMul(Value, Sign);
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcSin
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdArcSin)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdArcSin(const CC_SIMD_T a)
{
    const CC_SIMD_T HalfPi = CCSimdFill_T(CC_PI / 2.0);
    
#if CC_SIMD_ARCSIN_ACCURACY < 2
    // Based off 4.4.45 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CC_SIMD_T a0 = CCSimdFill_T(1.5707288);
    const CC_SIMD_T a1 = CCSimdFill_T(-0.2121144);
    const CC_SIMD_T a2 = CCSimdFill_T(0.0742610);
    const CC_SIMD_T a3 = CCSimdFill_T(-0.0187293);
#else
    // Based off 4.4.46 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CC_SIMD_T a0 = CCSimdFill_T(1.5707963050);
    const CC_SIMD_T a1 = CCSimdFill_T(-0.2145988016);
    const CC_SIMD_T a2 = CCSimdFill_T(0.0889789874);
    const CC_SIMD_T a3 = CCSimdFill_T(-0.0501743046);
    const CC_SIMD_T a4 = CCSimdFill_T(0.0308918810);
    const CC_SIMD_T a5 = CCSimdFill_T(-0.0170881256);
    const CC_SIMD_T a6 = CCSimdFill_T(0.0066700901);
    const CC_SIMD_T a7 = CCSimdFill_T(-0.0012624911);
#endif
    
    const CC_SIMD_T x1 = a;
    const CC_SIMD_T x2 = CCSimdMul(x1, x1);
    const CC_SIMD_T x3 = CCSimdMul(x1, x2);
#if CC_SIMD_ARCSIN_ACCURACY >= 2
    const CC_SIMD_T x4 = CCSimdMul(x2, x2);
    const CC_SIMD_T x5 = CCSimdMul(x2, x3);
    const CC_SIMD_T x6 = CCSimdMul(x3, x3);
    const CC_SIMD_T x7 = CCSimdMul(x3, x4);
#endif
    
    CC_SIMD_T Result = a0;
    Result = CCSimdMadd(a1, x1, Result);
    Result = CCSimdMadd(a2, x2, Result);
    Result = CCSimdMadd(a3, x3, Result);
#if CC_SIMD_ARCSIN_ACCURACY >= 2
    Result = CCSimdMadd(a4, x4, Result);
    Result = CCSimdMadd(a5, x5, Result);
    Result = CCSimdMadd(a6, x6, Result);
    Result = CCSimdMadd(a7, x7, Result);
#endif
    
    Result = CCSimdMul(CCSimdPow(CCSimdSub(CCSimdFill_T(1.0f), a), CCSimdFill_T(0.5f)), Result);
    
    return CCSimdSub(HalfPi, Result);
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdCos
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdCos)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdCos(const CC_SIMD_T a)
{
    const CC_SIMD_T HalfPi = CCSimdFill_T(CC_PI / 2.0);
    const CC_SIMD_T Pi = CCSimdFill_T(CC_PI);
    const CC_SIMD_T Two = CCSimdFill_T(2.0);
    const CC_SIMD_T NegOne = CCSimdFill_T(-1.0);
    
    CC_SIMD_T Value = CCSimdAdd_T(a, HalfPi);
    
    CC_SIMD_T Sign = CCSimdFloor(CCSimdMod(CCSimdDiv(Value, Pi), Two));
    Sign = CCSimdSub(CCSimdNeg(CCSimdAdd_T(Sign, Sign)), NegOne);
    
    Value = CCSimdSub(CCSimdMod(Value, Pi), HalfPi);
    
    return CCSimdMul(CCSimdHalfPiRadCos(Value), Sign);
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcCos
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdArcCos)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdArcCos(const CC_SIMD_T a)
{
    const CC_SIMD_T HalfPi = CCSimdFill_T(CC_PI / 2.0);
   
    return CCSimdSub(HalfPi, CCSimdArcSin(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdTan
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdTan)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdTan(const CC_SIMD_T a)
{
    return CCSimdDiv(CCSimdSin(a), CCSimdCos(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdQtrPiArcTan
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdQtrPiArcTan)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdQtrPiArcTan(const CC_SIMD_T a)
{
#if CC_SIMD_QTR_PI_ARCTAN_ACCURACY < 2
    // Based off 4.4.48 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CC_SIMD_T One = CCSimdFill_T(1.0);
    const CC_SIMD_T C28 = CCSimdFill_T(0.28);
    
    return CCSimdDiv(a, CCSimdMadd(CCSimdMul(a, a), C28, One));
#else
    // Based off 4.4.47 from Handbook of Mathematical Functions by Milton Abramowitz and Irene Stegun
    const CC_SIMD_T a1 = CCSimdFill_T(0.9998660);
    const CC_SIMD_T a3 = CCSimdFill_T(-0.3302995);
    const CC_SIMD_T a5 = CCSimdFill_T(0.1801410);
    const CC_SIMD_T a7 = CCSimdFill_T(-0.0851330);
    const CC_SIMD_T a9 = CCSimdFill_T(0.0208351);
    
    const CC_SIMD_T x1 = a;
    const CC_SIMD_T x2 = CCSimdMul(x1, x1);
    const CC_SIMD_T x3 = CCSimdMul(x1, x2);
    const CC_SIMD_T x4 = CCSimdMul(x2, x2);
    const CC_SIMD_T x5 = CCSimdMul(x2, x3);
    const CC_SIMD_T x7 = CCSimdMul(x3, x4);
    const CC_SIMD_T x9 = CCSimdMul(x4, x5);
    
    CC_SIMD_T Result = CCSimdMul(a1, x1);
    Result = CCSimdMadd(a3, x3, Result);
    Result = CCSimdMadd(a5, x5, Result);
    Result = CCSimdMadd(a7, x7, Result);
    Result = CCSimdMadd(a9, x9, Result);
    
    return Result;
#endif
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcTan
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdArcTan)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdArcTan(const CC_SIMD_T a)
{
    const CC_SIMD_T One = CCSimdFill_T(1.0);
    const CC_SIMD_T NegOne = CCSimdFill_T(-1.0);
    const CC_SIMD_T HalfPi = CCSimdFill_T(CC_PI / 2.0);
    
    const CC_SIMD_U Sign = CCSimdShiftLeftN_U(CCSimdMaskCompareLessThan_T(a, NegOne), 31);
    const CC_SIMD_U BoundsMask = CCSimdMaskCompareLessThanEqual_T(CCSimd_T_Reinterpret_U(CCSimdXor(Sign, CCSimd_U_Reinterpret_T(a))), One);
    
    CC_SIMD_T Bounds = CCSimd_T_Reinterpret_U(CCSimdAndNot(BoundsMask, CCSimdOr(Sign, CCSimd_U_Reinterpret_T(HalfPi))));
    
    const CC_SIMD_T Radians = CCSimdQtrPiArcTan(CCSimd_T_Reinterpret_U(CCSimdOr(CCSimdAnd(BoundsMask, CCSimd_U_Reinterpret_T(a)), CCSimdAndNot(BoundsMask, CCSimd_U_Reinterpret_T(CCSimdDiv(One, a))))));
    
    return CCSimd_T_Reinterpret_U(CCSimdOr(CCSimdAnd(BoundsMask, CCSimd_U_Reinterpret_T(Radians)), CCSimdAndNot(BoundsMask, CCSimd_U_Reinterpret_T(CCSimdSub(Bounds, Radians)))));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdArcTan2
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdArcTan2)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdArcTan2(const CC_SIMD_T y, const CC_SIMD_T x)
{
    const CC_SIMD_T Zero = CCSimdZero();
    const CC_SIMD_T Pi = CCSimdFill_T(CC_PI);
    const CC_SIMD_T HalfPi = CCSimdFill_T(CC_PI / 2.0);
    
    const CC_SIMD_U MaskX = CCSimdMaskCompareNotEqual_T(x, Zero);
    const CC_SIMD_U MaskY = CCSimdMaskCompareLessThanEqual_T(x, Zero);
#ifdef CC_SIMD_ARCTAN2_PRINCIPAL // (-pi, pi]
    const CC_SIMD_U Sign = CCSimdShiftLeftN_U(CCSimdMaskCompareLessThan_T(y, Zero), 31);
#else // [-pi, pi]
    const CC_SIMD_U Sign = CCSimdShiftLeftN_U(CCSimdShiftRightN(CCSimd_U_Reinterpret_T(y), 31), 31);
#endif
#if defined(CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO) || defined(CC_SIMD_ARCTAN2_UNDEFINED)
    const CC_SIMD_U IsZero = CCSimdOr(MaskX, CCSimdMaskCompareNotEqual(y, Zero));
#endif
#ifdef CC_SIMD_ARCTAN2_UNDEFINED
    const CC_SIMD_T Undefined = CCSimdFill_T(CC_SIMD_ARCTAN2_UNDEFINED);
#endif
        
    const CC_SIMD_T ResultYX = CCSimd_T_Reinterpret_U(CCSimdAnd(CCSimd_U_Reinterpret_T(CCSimdArcTan(CCSimdDiv(y, x))), MaskX));
    const CC_SIMD_T ResultPi = CCSimd_T_Reinterpret_U(CCSimdOr(Sign, CCSimdOr(CCSimdAndNot(MaskX, CCSimd_U_Reinterpret_T(HalfPi)), CCSimdAnd(CCSimdAnd(MaskX, CCSimd_U_Reinterpret_T(Pi)), MaskY))));
    
    CC_SIMD_T Result = CCSimdAdd_T(ResultYX, ResultPi);
    
#ifdef CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO
    return CCSimd_T_Reinterpret_U(CCSimdAnd(IsZero, CCSimd_U_Reinterpret_T(Result)));
#elif defined(CC_SIMD_ARCTAN2_UNDEFINED)
    return CCSimd_T_Reinterpret_U(CCSimdOr(CCSimdAnd(IsZero, CCSimd_U_Reinterpret_T(Result)), CCSimdAndNot(IsZero, CCSimd_U_Reinterpret_T(Undefined))));
#else
    return Result;
#endif
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdCsc
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdCsc)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdCsc(const CC_SIMD_T a)
{
    return CCSimdDiv(CCSimdFill_T(1.0), CCSimdSin(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdSec
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdSec)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdSec(const CC_SIMD_T a)
{
    return CCSimdDiv(CCSimdFill_T(1.0), CCSimdCos(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdCot
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdCot)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdCot(const CC_SIMD_T a)
{
    return CCSimdDiv(CCSimdFill_T(1.0), CCSimdTan(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdLog2
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdLog2)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdLog2(const CC_SIMD_T a)
{
    // Based off Paul Mineiro's fastlog2 from fastapprox v0.3.2: http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    const CC_SIMD_T C0 = CCSimdFill_T(1.1920928955078125e-7);
    const CC_SIMD_T C1 = CCSimdFill_T(124.22551499);
    const CC_SIMD_T C2 = CCSimdFill_T(1.498030302);
    const CC_SIMD_T C3 = CCSimdFill_T(1.72587999);
    const CC_SIMD_T C4 = CCSimdFill_T(0.3520887068);
    const CC_SIMD_U U = CCSimdOr(CCSimdAnd(CCSimd_U_Reinterpret_T(a), CCSimdFill_U(0x7fffff)), CCSimdFill_U(0x3f000000));
    CC_SIMD_T Result = CCSimd_T_Cast_U(CCSimd_U_Reinterpret_T(a));
    
    Result = CCSimdMul(Result, C0);
    
    return CCSimdSub(CCSimdSub(CCSimdSub(Result, C1), CCSimdMul(C2, CCSimd_T_Reinterpret_U(U))), CCSimdDiv(C3, CCSimdAdd_T(C4, CCSimd_T_Reinterpret_U(U))));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdLog
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdLog)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdLog(const CC_SIMD_T a)
{
    // Based off Paul Mineiro's fastlog from fastapprox v0.3.2: http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    return CCSimdMul(CCSimdFill_T(0.69314718), CCSimdLog2(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdPow
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdPow)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdPow(const CC_SIMD_T Base, const CC_SIMD_T Exponent)
{
    return CCSimdExp(CCSimdMul(Exponent, CCSimdLog(Base)));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdPow2
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdPow2)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdPow2(const CC_SIMD_T Exponent)
{
    const CC_SIMD_S ExpBase = CCSimdFill_S(0x7f);
    
    return CCSimd_T_Reinterpret_S(CCSimdShiftLeftN_S(CCSimdAdd_S(CCSimd_S_Cast_T(Exponent), ExpBase), 23));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdExp
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdExp)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdExp(const CC_SIMD_T a)
{
#if CC_SIMD_EXP_ACCURACY < 4
    // Taylor series approximation
    const CC_SIMD_T x0 = CCSimdFill_T(1.0);
    const CC_SIMD_T x1 = a;
    const CC_SIMD_T x2 = CCSimdMul(x1, x1);
    const CC_SIMD_T x3 = CCSimdMul(x1, x2);
    
#if CC_SIMD_EXP_ACCURACY >= 1
    const CC_SIMD_T x4 = CCSimdMul(x2, x2);
    const CC_SIMD_T x5 = CCSimdMul(x2, x3);
#if CC_SIMD_EXP_ACCURACY >= 2
    const CC_SIMD_T x6 = CCSimdMul(x3, x3);
    const CC_SIMD_T x7 = CCSimdMul(x3, x4);
#if CC_SIMD_EXP_ACCURACY >= 3
    const CC_SIMD_T x8 = CCSimdMul(x4, x4);
    const CC_SIMD_T x9 = CCSimdMul(x4, x5);
#endif
#endif
#endif
    
    CC_SIMD_T Result = CCSimdAdd_T(x0, x1);
    Result = CCSimdMadd(x2, CCSimdFill_T(1.0 / 2.0), Result);
    Result = CCSimdMadd(x3, CCSimdFill_T(1.0 / 6.0), Result);
    
#if CC_SIMD_EXP_ACCURACY >= 1
    Result = CCSimdMadd(x4, CCSimdFill_T(1.0 / 24.0), Result);
    Result = CCSimdMadd(x5, CCSimdFill_T(1.0 / 120.0), Result);
#if CC_SIMD_EXP_ACCURACY >= 2
    Result = CCSimdMadd(x6, CCSimdFill_T(1.0 / 720.0), Result);
    Result = CCSimdMadd(x7, CCSimdFill_T(1.0 / 5040.0), Result);
#if CC_SIMD_EXP_ACCURACY >= 3
    Result = CCSimdMadd(x8, CCSimdFill_T(1.0 / 40320.0), Result);
    Result = CCSimdMadd(x9, CCSimdFill_T(1.0 / 362880.0), Result);
#endif
#endif
#endif
    
    return CCSimdMax(Result, CCSimdZero());
#else
    // Based off Julien Pommier's SIMD adaptation of Cephes: http://gruntthepeon.free.fr/ssemath/
    const CC_SIMD_T One = CCSimdFill_T(1.0);
    const CC_SIMD_T Half = CCSimdFill_T(0.5);
    const CC_SIMD_T Min = CCSimdFill_T(-88.3762626647949);
    const CC_SIMD_T Max = CCSimdNeg(Min);
    const CC_SIMD_T Log2e = CCSimdFill_T(1.44269504088896341);
    
    const CC_SIMD_T C1 = CCSimdFill_T(0.693359375);
    const CC_SIMD_T C2 = CCSimdFill_T(-2.12194440e-4);
    
    const CC_SIMD_T P0 = CCSimdFill_T(1.9875691500e-4);
    const CC_SIMD_T P1 = CCSimdFill_T(1.3981999507e-3);
    const CC_SIMD_T P2 = CCSimdFill_T(8.3334519073e-3);
    const CC_SIMD_T P3 = CCSimdFill_T(4.1665795894e-2);
    const CC_SIMD_T P4 = CCSimdFill_T(1.6666665459e-1);
    const CC_SIMD_T P5 = CCSimdFill_T(5.0000001201e-1);
    
    CC_SIMD_T x = CCSimdClamp(a, Min, Max);
    CC_SIMD_T Px = CCSimdFloor(CCSimdMadd(x, Log2e, Half));
    
    x = CCSimdNegMadd(Px, C1, x);
    x = CCSimdNegMadd(Px, C2, x);
    
    CC_SIMD_T xx = CCSimdMul(x, x);
    
    CC_SIMD_T Result = P0;
    Result = CCSimdMadd(Result, x, P1);
    Result = CCSimdMadd(Result, x, P2);
    Result = CCSimdMadd(Result, x, P3);
    Result = CCSimdMadd(Result, x, P4);
    Result = CCSimdMadd(Result, x, P5);
    Result = CCSimdMadd(Result, xx, x);
    Result = CCSimdAdd_T(Result, One);
    
    return CCSimdMul(Result, CCSimdPow2(Px));
#endif
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdExp2
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdExp2)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdExp2(const CC_SIMD_T a)
{
#if CC_SIMD_EXP2_ACCURACY < 2
    // Based off Hao Hao Tan's 3rd-order polynomial approximation: https://gudgud96.github.io/2024/01/02/exp-2/
    const CC_SIMD_T C0 = CCSimdFill_T(0.05700169);
    const CC_SIMD_T C1 = CCSimdFill_T(0.24858144);
    const CC_SIMD_T C2 = CCSimdFill_T(0.69282515);
    const CC_SIMD_T C3 = CCSimdFill_T(0.99916080);
    
    const CC_SIMD_T Fractional = CCSimdSub(a, CCSimdRoundZero(a));
    
    CC_SIMD_T Result = Fractional;
    Result = CCSimdMadd(Result, C0, C1);
    Result = CCSimdMadd(Result, Fractional, C2);
    Result = CCSimdMadd(Result, Fractional, C3);
    
    return CCSimdMul(Result, CCSimdPow2(a));
#else
    // Based off Paul Mineiro's fastpow2 from fastapprox v0.3.2: http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    const CC_SIMD_T Zero = CCSimdZero();
    const CC_SIMD_T Min = CCSimdFill_T(-126.0);
    const CC_SIMD_T C127 = CCSimdFill_T(121.2740575);
    const CC_SIMD_T C27 = CCSimdFill_T(27.7280233);
    const CC_SIMD_T C4 = CCSimdFill_T(4.84252568);
    const CC_SIMD_T C1 = CCSimdFill_T(1.49012907);
    const CC_SIMD_T Base = CCSimdFill_T(0x800000);
    
    const CC_SIMD_T Offset = CCSimdCompareLessThan(a, Zero);
    
    const CC_SIMD_T Mask = CCSimdMaskCompareLessThan_T(a, Min);
    const CC_SIMD_T Clip = CCSimd_T_Reinterpret_U(CCSimdOr(CCSimdAndNot(Mask, CCSimd_U_Reinterpret_T(a)), CCSimdAnd(Mask, CCSimd_U_Reinterpret_T(Min))));
    
    const CC_SIMD_T Z = CCSimdSub(CCSimdAdd_T(Clip, Offset), CCSimdRoundZero(Clip));
    
    CC_SIMD_T Result = CCSimdNegMadd(C1, Z, CCSimdAdd_T(CCSimdAdd_T(Clip, C127), CCSimdDiv(C27, CCSimdSub(C4, Z))));
    
    return CCSimd_T_Reinterpret_U(CCSimd_U_Cast_T(CCSimdMul(Base, Result)));
#endif
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdCbrt
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdCbrt)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdCbrt(const CC_SIMD_T a)
{
    return CCSimdPow(a, CCSimdFill_T(1.0 / 3.0));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#ifdef CC_SIMD_MISSING_CCSimdInvCbrt
#define CC_SIMD_N_T_LANES CC_SIMD_T_LANE_COUNT(CC_SIMD_MISSING_CCSimdInvCbrt)

#if CC_SIMD_TYPE_LANE_COUNT_DEFAULT(CC_SIMD_N_T_LANES, 0)
static CC_FORCE_INLINE CC_SIMD_T CCSimdInvCbrt(const CC_SIMD_T a)
{
    return CCSimdDiv(CCSimdFill_T(1.0), CCSimdCbrt(a));
}
#endif
#undef CC_SIMD_N_T_LANES
#endif

#undef CC_SIMD_T_LANE_COUNT

#undef CC_SIMD_T

#undef CC_SIMD_U

#undef CC_SIMD_S

#undef CCSimd_T_Cast_U
#undef CCSimd_U_Cast_T
#undef CCSimd_S_Cast_T
#undef CCSimd_U_Reinterpret_T
#undef CCSimd_T_Reinterpret_U
#undef CCSimd_T_Reinterpret_S
#undef CCSimdFill_T
#undef CCSimdFill_U
#undef CCSimdFill_S
#undef CCSimdZero
#undef CCSimdAdd_T
#undef CCSimdAdd_S
#undef CCSimdSub
#undef CCSimdMul
#undef CCSimdDiv
#undef CCSimdMod
#undef CCSimdNeg
#undef CCSimdAbs
#undef CCSimdFloor
#undef CCSimdRoundZero
#undef CCSimdMadd
#undef CCSimdNegMadd
#undef CCSimdMax
#undef CCSimdClamp
#undef CCSimdAnd
#undef CCSimdAndNot
#undef CCSimdOr
#undef CCSimdXor
#undef CCSimdShiftLeftN_U
#undef CCSimdShiftLeftN_S
#undef CCSimdShiftRightN
#undef CCSimdMaskCompareLessThan_T
#undef CCSimdMaskCompareLessThanEqual_T
#undef CCSimdMaskCompareNotEqual_T
#undef CCSimdCompareLessThan

#undef CCSimdPosPiRadSin
#undef CCSimdHalfPiRadCos
#undef CCSimdPosSin
#undef CCSimdPiRadSin
#undef CCSimdSin
#undef CCSimdArcSin
#undef CCSimdCos
#undef CCSimdArcCos
#undef CCSimdTan
#undef CCSimdQtrPiArcTan
#undef CCSimdArcTan
#undef CCSimdArcTan2
#undef CCSimdCsc
#undef CCSimdSec
#undef CCSimdCot
#undef CCSimdLog2
#undef CCSimdLog
#undef CCSimdPow
#undef CCSimdPow2
#undef CCSimdExp
#undef CCSimdExp2
#undef CCSimdCbrt
#undef CCSimdInvCbrt


#undef T
