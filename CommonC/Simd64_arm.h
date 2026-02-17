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

#ifndef CommonC_Simd64_arm_h
#define CommonC_Simd64_arm_h

#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>


#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) v){ return vdup_n_##base(v); }
CC_SIMD_DECL(CCSimdFill, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) src[count]){ return vld1_##base(src); }
CC_SIMD_DECL(CCSimdLoad, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (CC_SIMD_BASE_TYPE(base) dst[count], const CC_SIMD_TYPE(base, count) src){ vst1_##base(dst, src); }
CC_SIMD_DECL(CCSimdStore, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, n, kind) (const CC_SIMD_BASE_TYPE(base) src[count * n]) \
{ \
    CC_SIMD_INTERNAL_POLY_TYPE(base, count, n) Result = vld##n##_##base((void*)src); \
    return ((CC_SIMD_POLY_TYPE(base, count, n)){ .v = { CC_REPEAT(0, n, CC_SIMD_INTERNAL_POLY_VALUE, Result) } }); \
}
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 2, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 3, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 4, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, n, kind) (CC_SIMD_BASE_TYPE(base) dst[count * n], const CC_SIMD_POLY_TYPE(base, count, n) src) \
{ \
    vst##n##_##base((void*)dst, ((CC_SIMD_INTERNAL_POLY_TYPE(base, count, n)){ .val = { CC_REPEAT(0, n, CC_SIMD_POLY_VALUE, src) } })); \
}
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 2, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 3, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 4, CC_SIMD_RETURN_TYPE(void), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 2, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vget_lane_##base(a, 0); \
        case 1: return vget_lane_##base(a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 4, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vget_lane_##base(a, 0); \
        case 1: return vget_lane_##base(a, 1); \
        case 2: return vget_lane_##base(a, 2); \
        case 3: return vget_lane_##base(a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 8, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vget_lane_##base(a, 0); \
        case 1: return vget_lane_##base(a, 1); \
        case 2: return vget_lane_##base(a, 2); \
        case 3: return vget_lane_##base(a, 3); \
        case 4: return vget_lane_##base(a, 4); \
        case 5: return vget_lane_##base(a, 5); \
        case 6: return vget_lane_##base(a, 6); \
        case 7: return vget_lane_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 2, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vset_lane_##base(v, a, 0); \
        case 1: return vset_lane_##base(v, a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 4, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vset_lane_##base(v, a, 0); \
        case 1: return vset_lane_##base(v, a, 1); \
        case 2: return vset_lane_##base(v, a, 2); \
        case 3: return vset_lane_##base(v, a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 8, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vset_lane_##base(v, a, 0); \
        case 1: return vset_lane_##base(v, a, 1); \
        case 2: return vset_lane_##base(v, a, 2); \
        case 3: return vset_lane_##base(v, a, 3); \
        case 4: return vset_lane_##base(v, a, 4); \
        case 5: return vset_lane_##base(v, a, 5); \
        case 6: return vset_lane_##base(v, a, 6); \
        case 7: return vset_lane_##base(v, a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define vreinterpret_s8_s8(x) (x)
#define vreinterpret_s16_s16(x) (x)
#define vreinterpret_s32_s32(x) (x)
#define vreinterpret_u8_u8(x) (x)
#define vreinterpret_u16_u16(x) (x)
#define vreinterpret_u32_u32(x) (x)
#define vreinterpret_f32_f32(x) (x)

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_s8_##base(a); }
CC_SIMD_DECL(CCSimd_s8x8_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s8x8), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_s16_##base(a); }
CC_SIMD_DECL(CCSimd_s16x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s16x4), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_s32_##base(a); }
CC_SIMD_DECL(CCSimd_s32x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s32x2), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_u8_##base(a); }
CC_SIMD_DECL(CCSimd_u8x8_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u8x8), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_u16_##base(a); }
CC_SIMD_DECL(CCSimd_u16x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u16x4), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_u32_##base(a); }
CC_SIMD_DECL(CCSimd_u32x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u32x2), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpret_f32_##base(a); }
CC_SIMD_DECL(CCSimd_f32x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_f32x2), CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define vcvt_s8_s8(x) (x)
#define vcvt_s8_u8(x) (x)
#define vcvt_u8_s8(x) (x)
#define vcvt_s16_s16(x) (x)
#define vcvt_s16_u16(x) (x)
#define vcvt_u16_s16(x) (x)
#define vcvt_s32_s32(x) (x)
#define vcvt_s32_u32(x) (x)
#define vcvt_u32_s32(x) (x)
#define vcvt_u8_u8(x) (x)
#define vcvt_u8_s8(x) (x)
#define vcvt_s8_u8(x) (x)
#define vcvt_u16_u16(x) (x)
#define vcvt_u16_s16(x) (x)
#define vcvt_s16_u16(x) (x)
#define vcvt_u32_u32(x) (x)
#define vcvt_u32_s32(x) (x)
#define vcvt_s32_u32(x) (x)
#define vcvt_f32_f32(x) (x)

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_s8_##base(a); }
CC_SIMD_DECL(CCSimd_s8x8_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s8x8), CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_s16_##base(a); }
CC_SIMD_DECL(CCSimd_s16x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s16x4), CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_s32_##base(a); }
CC_SIMD_DECL(CCSimd_s32x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s32x2), CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_u8_##base(a); }
CC_SIMD_DECL(CCSimd_u8x8_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u8x8), CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_u16_##base(a); }
CC_SIMD_DECL(CCSimd_u16x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u16x4), CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_u32_##base(a); }
CC_SIMD_DECL(CCSimd_u32x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u32x2), CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvt_f32_##base(a); }
CC_SIMD_DECL(CCSimd_f32x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_f32x2), CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vmvn_##base(a); }
CC_SIMD_DECL(CCSimdNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vand_##base(a, b); }
CC_SIMD_DECL(CCSimdAnd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vorr_##base(a, b); }
CC_SIMD_DECL(CCSimdOr, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vorn_##base(a, b); }
CC_SIMD_DECL(CCSimdOrNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return veor_##base(a, b); }
CC_SIMD_DECL(CCSimdXor, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vshl_##base(a, b); }
CC_SIMD_DECL(CCSimdShiftLeft, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshl_n_##base(a, 1); \
        case 2: return vshl_n_##base(a, 2); \
        case 3: return vshl_n_##base(a, 3); \
        case 4: return vshl_n_##base(a, 4); \
        case 5: return vshl_n_##base(a, 5); \
        case 6: return vshl_n_##base(a, 6); \
        case 7: return vshl_n_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshl_n_##base(a, 1); \
        case 2: return vshl_n_##base(a, 2); \
        case 3: return vshl_n_##base(a, 3); \
        case 4: return vshl_n_##base(a, 4); \
        case 5: return vshl_n_##base(a, 5); \
        case 6: return vshl_n_##base(a, 6); \
        case 7: return vshl_n_##base(a, 7); \
        case 8: return vshl_n_##base(a, 8); \
        case 9: return vshl_n_##base(a, 9); \
        case 10: return vshl_n_##base(a, 10); \
        case 11: return vshl_n_##base(a, 11); \
        case 12: return vshl_n_##base(a, 12); \
        case 13: return vshl_n_##base(a, 13); \
        case 14: return vshl_n_##base(a, 14); \
        case 15: return vshl_n_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshl_n_##base(a, 1); \
        case 2: return vshl_n_##base(a, 2); \
        case 3: return vshl_n_##base(a, 3); \
        case 4: return vshl_n_##base(a, 4); \
        case 5: return vshl_n_##base(a, 5); \
        case 6: return vshl_n_##base(a, 6); \
        case 7: return vshl_n_##base(a, 7); \
        case 8: return vshl_n_##base(a, 8); \
        case 9: return vshl_n_##base(a, 9); \
        case 10: return vshl_n_##base(a, 10); \
        case 11: return vshl_n_##base(a, 11); \
        case 12: return vshl_n_##base(a, 12); \
        case 13: return vshl_n_##base(a, 13); \
        case 14: return vshl_n_##base(a, 14); \
        case 15: return vshl_n_##base(a, 15); \
        case 16: return vshl_n_##base(a, 16); \
        case 17: return vshl_n_##base(a, 17); \
        case 18: return vshl_n_##base(a, 18); \
        case 19: return vshl_n_##base(a, 19); \
        case 20: return vshl_n_##base(a, 20); \
        case 21: return vshl_n_##base(a, 21); \
        case 22: return vshl_n_##base(a, 22); \
        case 23: return vshl_n_##base(a, 23); \
        case 24: return vshl_n_##base(a, 24); \
        case 25: return vshl_n_##base(a, 25); \
        case 26: return vshl_n_##base(a, 26); \
        case 27: return vshl_n_##base(a, 27); \
        case 28: return vshl_n_##base(a, 28); \
        case 29: return vshl_n_##base(a, 29); \
        case 30: return vshl_n_##base(a, 30); \
        case 31: return vshl_n_##base(a, 31); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vshl_##base(a, CC_SIMD_NAME(CCSimdNeg, base, count)(b)); }
CC_SIMD_DECL(CCSimdShiftRight, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshr_n_##base(a, 1); \
        case 2: return vshr_n_##base(a, 2); \
        case 3: return vshr_n_##base(a, 3); \
        case 4: return vshr_n_##base(a, 4); \
        case 5: return vshr_n_##base(a, 5); \
        case 6: return vshr_n_##base(a, 6); \
        case 7: return vshr_n_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshr_n_##base(a, 1); \
        case 2: return vshr_n_##base(a, 2); \
        case 3: return vshr_n_##base(a, 3); \
        case 4: return vshr_n_##base(a, 4); \
        case 5: return vshr_n_##base(a, 5); \
        case 6: return vshr_n_##base(a, 6); \
        case 7: return vshr_n_##base(a, 7); \
        case 8: return vshr_n_##base(a, 8); \
        case 9: return vshr_n_##base(a, 9); \
        case 10: return vshr_n_##base(a, 10); \
        case 11: return vshr_n_##base(a, 11); \
        case 12: return vshr_n_##base(a, 12); \
        case 13: return vshr_n_##base(a, 13); \
        case 14: return vshr_n_##base(a, 14); \
        case 15: return vshr_n_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshr_n_##base(a, 1); \
        case 2: return vshr_n_##base(a, 2); \
        case 3: return vshr_n_##base(a, 3); \
        case 4: return vshr_n_##base(a, 4); \
        case 5: return vshr_n_##base(a, 5); \
        case 6: return vshr_n_##base(a, 6); \
        case 7: return vshr_n_##base(a, 7); \
        case 8: return vshr_n_##base(a, 8); \
        case 9: return vshr_n_##base(a, 9); \
        case 10: return vshr_n_##base(a, 10); \
        case 11: return vshr_n_##base(a, 11); \
        case 12: return vshr_n_##base(a, 12); \
        case 13: return vshr_n_##base(a, 13); \
        case 14: return vshr_n_##base(a, 14); \
        case 15: return vshr_n_##base(a, 15); \
        case 16: return vshr_n_##base(a, 16); \
        case 17: return vshr_n_##base(a, 17); \
        case 18: return vshr_n_##base(a, 18); \
        case 19: return vshr_n_##base(a, 19); \
        case 20: return vshr_n_##base(a, 20); \
        case 21: return vshr_n_##base(a, 21); \
        case 22: return vshr_n_##base(a, 22); \
        case 23: return vshr_n_##base(a, 23); \
        case 24: return vshr_n_##base(a, 24); \
        case 25: return vshr_n_##base(a, 25); \
        case 26: return vshr_n_##base(a, 26); \
        case 27: return vshr_n_##base(a, 27); \
        case 28: return vshr_n_##base(a, 28); \
        case 29: return vshr_n_##base(a, 29); \
        case 30: return vshr_n_##base(a, 30); \
        case 31: return vshr_n_##base(a, 31); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vclz_##base(a); }
CC_SIMD_DECL(CCSimdCountHighestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vceq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vceq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vclt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vclt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcle_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcle_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgt_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcge_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcge_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vadd_##base(a, b); }
CC_SIMD_DECL(CCSimdAdd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vsub_##base(a, b); }
CC_SIMD_DECL(CCSimdSub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmul_##base(a, b); }
CC_SIMD_DECL(CCSimdMul, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfma_##base(c, a, b); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMadd
#define CC_SIMD_MISSING_CCSimdMadd CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfms_##base(c, a, b); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdNegMadd
#define CC_SIMD_MISSING_CCSimdNegMadd CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfma_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMsub
#define CC_SIMD_MISSING_CCSimdMsub CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfms_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdNegMsub
#define CC_SIMD_MISSING_CCSimdNegMsub CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vdiv_##base(a, b); }
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdDiv
#define CC_SIMD_MISSING_CCSimdDiv CC_SIMD_64_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrnda_##base(a); }
CC_SIMD_DECL(CCSimdRoundNearestAway, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndn_##base(a); }
CC_SIMD_DECL(CCSimdRoundNearestEven, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrnd_##base(a); }
CC_SIMD_DECL(CCSimdRoundZero, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndm_##base(a); }
CC_SIMD_DECL(CCSimdFloor, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndp_##base(a); }
CC_SIMD_DECL(CCSimdCeil, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vaddv_##base(a); }
CC_SIMD_DECL(CCSimdSum, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vneg_##base(a); }
CC_SIMD_DECL(CCSimdNeg, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_SIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_CAT(vreinterpret_, base, _, CC_SIMD_SIGNED(base))(CC_CAT(vneg_, CC_SIMD_SIGNED(base))(CC_CAT(vreinterpret_, CC_SIMD_SIGNED(base), _, base)(a))); }
CC_SIMD_DECL(CCSimdNeg, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_UNSIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vabs_##base(a); }
CC_SIMD_DECL(CCSimdAbs, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_SIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return a; }
CC_SIMD_DECL(CCSimdAbs, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_UNSIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmin_##base(a, b); }
CC_SIMD_DECL(CCSimdMin, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmax_##base(a, b); }
CC_SIMD_DECL(CCSimdMax, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vsqrt_##base(a); }
CC_SIMD_DECL(CCSimdSqrt, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrsqrte_##base(a); }
CC_SIMD_DECL(CCSimdInvSqrt, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2), "Indexes must not exceed lane count"); \
    \
    switch ((v0 << 1) | v1) \
    { \
        case 0: return vdup_lane_##base(a, 0); \
        case 1: return a; \
        case 2: return vrev64_##base(a); \
        case 3: return vdup_lane_##base(a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 < 4) && (v1 < 4) && (v2 < 4) && (v3 < 4), "Indexes must not exceed lane count"); \
    \
    switch ((v0 << 6) | (v1 << 4) | (v2 << 2) | v3) \
    { \
        case 0: return vdup_lane_##base(a, 0); \
        case 1: return vzip1_##base(vdup_lane_##base(a, 0), a); \
        case 2: return vuzp1_##base(vdup_lane_##base(a, 0), a); \
        case 3: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 1); \
        case 4: return vzip1_##base(a, vdup_lane_##base(a, 0)); \
        case 5: return vzip1_##base(a, a); \
        case 6: return vext_##base(vdup_lane_##base(a, 0), a, 3); \
        case 7: return vuzp2_##base(vdup_lane_##base(a, 0), a); \
        case 8: return vtrn1_##base(a, vdup_lane_##base(a, 0)); \
        case 9: return vtrn1_##base(a, vzip1_##base(a, a)); \
        case 10: return vtrn1_##base(a, a); \
        case 11: return vcopy_lane_##base(a, 1, a, 0); \
        case 12: return vcopy_lane_##base(vdup_lane_##base(a, 0), 2, a, 3); \
        case 13: return vcopy_lane_##base(vzip1_##base(a, a), 2, a, 3); \
        case 14: return vcopy_lane_##base(vrev32_##base(a), 0, a, 0); \
        case 15: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 2); \
        case 16: return vzip2_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 17: return vreinterpret_##base##_##kind##32(vdup_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0)); \
        case 18: return vcopy_lane_##base(vuzp1_##base(a, a), 1, a, 1); \
        case 19: return vcopy_lane_##base(a, 2, a, 0); \
        case 20: return vzip1_##base(a, vrev32_##base(a)); \
        case 21: return vzip1_##base(a, vdup_lane_##base(a, 1)); \
        case 22: return vzip1_##base(a, vext_##base(a, a, 1)); \
        case 23: return vcopy_lane_##base(a, 2, a, 1); \
        case 24: return vcopy_lane_##base(a, 3, a, 0); \
        case 25: return vcopy_lane_##base(a, 3, a, 1); \
        case 26: return vcopy_lane_##base(a, 3, a, 2); \
        case 27: return a; \
        case 28: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 1)), 0, vreinterpret_##kind##32_##base(a), 0)); \
        case 29: return vcopy_lane_##base(vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1, vreinterpret_##kind##32_##base(a), 0)), 2, a, 3); \
        case 30: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vrev32_##base(a)), 0, vreinterpret_##kind##32_##base(a), 0)); \
        case 31: return vcopy_lane_##base(a, 2, a, 3); \
        case 32: return vuzp1_##base(a, vdup_lane_##base(a, 0)); \
        case 33: return vcopy_lane_##base(vuzp1_##base(a, a), 3, a, 1); \
        case 34: return vuzp1_##base(a, a); \
        case 35: return vzip2_##base(vdup_lane_##base(a, 0), a); \
        case 36: return vcopy_lane_##base(vrev64_##base(a), 0, a, 0); \
        case 37: return vuzp1_##base(a, vdup_lane_##base(a, 1)); \
        case 38: return vzip1_##base(a, vdup_lane_##base(a, 2)); \
        case 39: return vuzp2_##base(vrev32_##base(a), a); \
        case 40: return vuzp1_##base(a, vext_##base(a, a, 2)); \
        case 41: return vcopy_lane_##base(vcopy_lane_##base(a, 1, a, 2), 3, a, 1); \
        case 42: return vuzp1_##base(a, vdup_lane_##base(a, 2)); \
        case 43: return vcopy_lane_##base(a, 1, a, 2); \
        case 44: return vcopy_lane_##base(vext_##base(a, a, 1), 0, a, 0); \
        case 45: return vuzp1_##base(a, vrev64_##base(a)); \
        case 46: return vcopy_lane_##base(vuzp1_##base(a, a), 2, a, 3); \
        case 47: return vuzp1_##base(a, vdup_lane_##base(a, 3)); \
        case 48: return vcopy_lane_##base(vdup_lane_##base(a, 0), 1, a, 3); \
        case 49: return vtrn1_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 50: return vzip1_##base(vdup_lane_##base(a, 0), vrev64_##base(a)); \
        case 51: return vtrn1_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3)); \
        case 52: return vzip1_##base(a, vext_##base(a, a, 3)); \
        case 53: return vcopy_lane_##base(vzip1_##base(a, a), 1, a, 3); \
        case 54: return vzip1_##base(a, vrev64_##base(a)); \
        case 55: return vzip1_##base(a, vdup_lane_##base(a, 3)); \
        case 56: return vext_##base(vrev32_##base(a), a, 1); \
        case 57: return vext_##base(vrev64_##base(a), vrev64_##base(a), 3); \
        case 58: return vcopy_lane_##base(vtrn1_##base(a, a), 1, a, 3); \
        case 59: return vcopy_lane_##base(a, 1, a, 3); \
        case 60: return vzip1_##base(vzip1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 61: return vuzp1_##base(vuzp1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 62: return vzip2_##base(vext_##base(vrev32_##base(a), vrev32_##base(a), 3), vrev32_##base(a)); \
        case 63: return vext_##base(vdup_lane_##base(a, 0), vdup_lane_##base(a, 3), 3); \
        case 64: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 65: return vzip1_##base(vrev32_##base(a), a); \
        case 66: return vcopy_lane_##base(vrev32_##base(a), 2, a, 0); \
        case 67: return vext_##base(vzip1_##base(a, vext_##base(a, a, 3)), vzip1_##base(a, vext_##base(a, a, 3)), 2); \
        case 68: return vext_##base(vrev64_##base(a), vrev32_##base(a), 2); \
        case 69: return vzip1_##base(vdup_lane_##base(a, 1), a); \
        case 70: return vext_##base(vdup_lane_##base(a, 1), a, 3); \
        case 71: return vcopy_lane_##base(vuzp2_##base(a, a), 1, a, 0); \
        case 72: return vrev32_##base(vuzp1_##base(vzip1_##base(a, a), a)); \
        case 73: return vzip1_##base(vext_##base(a, a, 1), a); \
        case 74: return vcopy_lane_##base(vrev32_##base(a), 2, a, 2); \
        case 75: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vrev32_##base(a)), 1, vreinterpret_##kind##32_##base(a), 1)); \
        case 76: return vtrn2_##base(a, vdup_lane_##base(a, 0)); \
        case 77: return vcopy_lane_##base(vrev32_##base(a), 3, a, 1); \
        case 78: return vext_##base(vrev64_##base(a), vrev64_##base(a), 2); \
        case 79: return vcopy_lane_##base(vrev32_##base(a), 3, a, 3); \
        case 80: return vzip2_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 81: return vext_##base(vdup_lane_##base(a, 1), a, 2); \
        case 82: return vuzp1_##base(vdup_lane_##base(a, 1), a); \
        case 83: return vcopy_lane_##base(vtrn2_##base(a, a), 2, a, 0); \
        case 84: return vext_##base(vdup_lane_##base(a, 1), a, 1); \
        case 85: return vdup_lane_##base(a, 1); \
        case 86: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 1); \
        case 87: return vuzp2_##base(vdup_lane_##base(a, 1), a); \
        case 88: return vcopy_lane_##base(vcopy_lane_##base(a, 0, a, 1), 3, a, 0); \
        case 89: return vcopy_lane_##base(vdup_lane_##base(a, 1), 2, a, 2); \
        case 90: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 2); \
        case 91: return vcopy_lane_##base(a, 0, a, 1); \
        case 92: return vcopy_lane_##base(vext_##base(a, a, 1), 1, a, 1); \
        case 93: return vtrn2_##base(a, vdup_lane_##base(a, 1)); \
        case 94: return vcopy_lane_##base(vrev32_##base(a), 1, a, 1); \
        case 95: return vtrn2_##base(a, a); \
        case 96: return vcopy_lane_##base(vext_##base(a, a, 1), 2, a, 0); \
        case 97: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 1)), 1, vreinterpret_##kind##32_##base(a), 0)); \
        case 98: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 99: return vzip2_##base(vrev64_##base(a), a); \
        case 100: return vtrn2_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); \
        case 101: return vcopy_lane_##base(vdup_lane_##base(a, 1), 1, a, 2); \
        case 102: return vtrn1_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2)); \
        case 103: return vzip2_##base(vdup_lane_##base(a, 1), a); \
        case 104: return vcopy_lane_##base(vext_##base(a, a, 1), 2, a, 2); \
        case 105: return vzip1_##base(vext_##base(a, a, 1), vrev32_##base(vext_##base(a, a, 1))); \
        case 106: return vext_##base(vdup_lane_##base(a, 1), vdup_lane_##base(a, 2), 3); \
        case 107: return vzip2_##base(vext_##base(a, a, 3), a); \
        case 108: return vext_##base(a, a, 1); \
        case 109: return vext_##base(a, vrev32_##base(a), 1); \
        case 110: return vext_##base(a, vdup_lane_##base(a, 2), 1); \
        case 111: return vext_##base(a, vdup_lane_##base(a, 3), 1); \
        case 112: return vuzp2_##base(a, vdup_lane_##base(a, 0)); \
        case 113: return vcopy_lane_##base(vext_##base(a, a, 2), 0, a, 1); \
        case 114: return vuzp1_##base(vrev32_##base(a), a); \
        case 115: return vzip2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 116: return vcopy_lane_##base(vuzp2_##base(a, a), 3, a, 0); \
        case 117: return vuzp2_##base(a, vdup_lane_##base(a, 1)); \
        case 118: return vzip1_##base(vdup_lane_##base(a, 1), vrev64_##base(a)); \
        case 119: return vuzp2_##base(a, a); \
        case 120: return vuzp2_##base(a, vrev64_##base(a)); \
        case 121: return vuzp2_##base(a, vuzp1_##base(a, vdup_lane_##base(a, 1))); \
        case 122: return vuzp2_##base(a, vdup_lane_##base(a, 2)); \
        case 123: return vcopy_lane_##base(vuzp2_##base(a, a), 2, a, 2); \
        case 124: return vcopy_lane_##base(vext_##base(a, a, 1), 1, a, 3); \
        case 125: return vuzp2_##base(a, vext_##base(a, a, 2)); \
        case 126: return vcopy_lane_##base(vrev32_##base(a), 1, a, 3); \
        case 127: return vuzp2_##base(a, vdup_lane_##base(a, 3)); \
        case 128: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 129: return vcopy_lane_##base(vext_##base(a, a, 2), 1, a, 0); \
        case 130: return vuzp1_##base(vext_##base(a, a, 2), a); \
        case 131: return vuzp2_##base(vext_##base(a, a, 1), vuzp2_##base(vext_##base(a, a, 1), a)); \
        case 132: return vrev64_##base(vuzp1_##base(vzip1_##base(a, a), a)); \
        case 133: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); \
        case 134: return vext_##base(vdup_lane_##base(a, 2), a, 3); \
        case 135: return vuzp2_##base(vrev64_##base(a), a); \
        case 136: return vuzp2_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 137: return vzip1_##base(vdup_lane_##base(a, 2), a); \
        case 138: return vtrn1_##base(vdup_lane_##base(a, 2), a); \
        case 139: return vcopy_lane_##base(vcopy_lane_##base(a, 0, a, 2), 1, a, 0); \
        case 140: return vzip2_##base(a, vdup_lane_##base(a, 0)); \
        case 141: return vzip1_##base(vext_##base(a, a, 2), a); \
        case 142: return vtrn1_##base(vzip2_##base(a, a), a); \
        case 143: return vuzp2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 144: return vext_##base(vrev64_##base(a), a, 1); \
        case 145: return vext_##base(vrev64_##base(a), vrev32_##base(a), 1); \
        case 146: return vuzp2_##base(vuzp1_##base(a, vext_##base(a, a, 3)), vext_##base(a, a, 3)); \
        case 147: return vext_##base(vrev64_##base(a), vrev64_##base(a), 1); \
        case 148: return vzip2_##base(vext_##base(vrev64_##base(a), vrev64_##base(a), 3), vrev64_##base(a)); \
        case 149: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 3); \
        case 150: return vzip1_##base(vrev32_##base(vext_##base(a, a, 1)), vext_##base(a, a, 1)); \
        case 151: return vcopy_lane_##base(vcopy_lane_##base(a, 0, a, 2), 2, a, 1); \
        case 152: return vzip2_##base(vdup_lane_##base(a, 2), vrev64_##base(a)); \
        case 153: return vtrn1_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1)); \
        case 154: return vcopy_lane_##base(vdup_lane_##base(a, 2), 1, a, 1); \
        case 155: return vcopy_lane_##base(a, 0, a, 2); \
        case 156: return vzip2_##base(a, vrev64_##base(a)); \
        case 157: return vzip2_##base(a, vdup_lane_##base(a, 1)); \
        case 158: return vzip2_##base(a, vext_##base(a, a, 3)); \
        case 159: return vcopy_lane_##base(vzip2_##base(a, a), 1, a, 1); \
        case 160: return vext_##base(vtrn1_##base(a, a), vtrn1_##base(a, a), 2); \
        case 161: return vext_##base(vdup_lane_##base(a, 2), a, 2); \
        case 162: return vuzp1_##base(vdup_lane_##base(a, 2), a); \
        case 163: return vcopy_lane_##base(vzip2_##base(a, a), 2, a, 0); \
        case 164: return vcopy_lane_##base(vrev64_##base(a), 0, a, 2); \
        case 165: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 2); \
        case 166: return vcopy_lane_##base(vdup_lane_##base(a, 2), 2, a, 1); \
        case 167: return vuzp2_##base(vdup_lane_##base(a, 2), a); \
        case 168: return vext_##base(vdup_lane_##base(a, 2), a, 1); \
        case 169: return vext_##base(vdup_lane_##base(a, 2), vdup_lane_##base(a, 1), 1); \
        case 170: return vdup_lane_##base(a, 2); \
        case 171: return vzip2_##base(vdup_lane_##base(a, 2), a); \
        case 172: return vcopy_lane_##base(vext_##base(a, a, 1), 0, a, 2); \
        case 173: return vcopy_lane_##base(vzip2_##base(a, a), 3, a, 1); \
        case 174: return vzip2_##base(a, vdup_lane_##base(a, 2)); \
        case 175: return vzip2_##base(a, a); \
        case 176: return vext_##base(a, vdup_lane_##base(a, 0), 2); \
        case 177: return vext_##base(a, a, 2); \
        case 178: return vcopy_lane_##base(vext_##base(a, a, 2), 3, a, 2); \
        case 179: return vtrn2_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 180: return vext_##base(a, vrev32_##base(a), 2); \
        case 181: return vext_##base(a, vdup_lane_##base(a, 1), 2); \
        case 182: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 3)), 0, vreinterpret_##kind##32_##base(a), 1)); \
        case 183: return vcopy_lane_##base(vuzp2_##base(a, a), 0, a, 2); \
        case 184: return vcopy_lane_##base(vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(a), 0, vreinterpret_##kind##32_##base(a), 1)), 3, a, 0); \
        case 185: return vext_##base(vrev32_##base(a), vrev64_##base(a), 3); \
        case 186: return vext_##base(a, vdup_lane_##base(a, 2), 2); \
        case 187: return vreinterpret_##base##_##kind##32(vdup_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1)); \
        case 188: return vzip2_##base(a, vext_##base(a, a, 1)); \
        case 189: return vcopy_lane_##base(vext_##base(a, a, 2), 2, a, 3); \
        case 190: return vext_##base(a, vrev64_##base(a), 2); \
        case 191: return vext_##base(a, vdup_lane_##base(a, 3), 2); \
        case 192: return vext_##base(a, vdup_lane_##base(a, 0), 3); \
        case 193: return vzip1_##base(vext_##base(a, a, 3), a); \
        case 194: return vcopy_lane_##base(vext_##base(a, a, 3), 2, a, 0); \
        case 195: return vzip1_##base(vext_##base(a, a, 3), vzip1_##base(a, vext_##base(a, a, 3))); \
        case 196: return vtrn1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 197: return vcopy_lane_##base(vzip1_##base(a, a), 0, a, 3); \
        case 198: return vext_##base(a, a, 3); \
        case 199: return vcopy_lane_##base(vext_##base(a, a, 3), 3, a, 3); \
        case 200: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 201: return vzip1_##base(vrev64_##base(a), a); \
        case 202: return vcopy_lane_##base(vext_##base(a, a, 3), 2, a, 2); \
        case 203: return vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(vext_##base(a, a, 3)), 1, vreinterpret_##kind##32_##base(a), 1)); \
        case 204: return vtrn1_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 0)); \
        case 205: return vzip1_##base(vdup_lane_##base(a, 3), a); \
        case 206: return vtrn1_##base(vdup_lane_##base(a, 3), a); \
        case 207: return vcopy_lane_##base(vdup_lane_##base(a, 3), 1, a, 0); \
        case 208: return vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 0)); \
        case 209: return vcopy_lane_##base(vreinterpret_##base##_##kind##32(vcopy_lane_##kind##32(vreinterpret_##kind##32_##base(a), 1, vreinterpret_##kind##32_##base(a), 0)), 0, a, 3); \
        case 210: return vuzp1_##base(vrev64_##base(a), a); \
        case 211: return vext_##base(a, vrev32_##base(a), 3); \
        case 212: return vcopy_lane_##base(vrev64_##base(a), 1, a, 1); \
        case 213: return vext_##base(a, vdup_lane_##base(a, 1), 3); \
        case 214: return vcopy_lane_##base(vext_##base(a, a, 3), 1, a, 1); \
        case 215: return vuzp2_##base(vext_##base(a, a, 2), a); \
        case 216: return vzip2_##base(vrev32_##base(a), vrev64_##base(a)); \
        case 217: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 1)); \
        case 218: return vuzp1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 219: return vcopy_lane_##base(a, 0, a, 3); \
        case 220: return vzip2_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 221: return vuzp1_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 222: return vrev64_##base(vuzp2_##base(vzip2_##base(a, a), a)); \
        case 223: return vtrn2_##base(vdup_lane_##base(a, 3), a); \
        case 224: return vcopy_lane_##base(vrev64_##base(a), 2, a, 0); \
        case 225: return vext_##base(vrev32_##base(a), a, 2); \
        case 226: return vcopy_lane_##base(vuzp1_##base(a, a), 0, a, 3); \
        case 227: return vzip2_##base(vext_##base(a, a, 1), a); \
        case 228: return vrev64_##base(a); \
        case 229: return vcopy_lane_##base(vrev64_##base(a), 3, a, 1); \
        case 230: return vtrn1_##base(vrev64_##base(a), vdup_lane_##base(a, 2)); \
        case 231: return vcopy_lane_##base(vrev64_##base(a), 3, a, 3); \
        case 232: return vcopy_lane_##base(vrev64_##base(a), 2, a, 2); \
        case 233: return vext_##base(a, vuzp2_##base(vuzp1_##base(a, a), a), 3); \
        case 234: return vext_##base(a, vdup_lane_##base(a, 2), 3); \
        case 235: return vzip2_##base(vrev32_##base(a), a); \
        case 236: return vtrn2_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 237: return vrev32_##base(vuzp2_##base(vzip2_##base(a, a), a)); \
        case 238: return vext_##base(vrev32_##base(a), vrev64_##base(a), 2); \
        case 239: return vzip2_##base(vdup_lane_##base(a, 3), a); \
        case 240: return vext_##base(vdup_lane_##base(a, 3), vdup_lane_##base(a, 0), 2); \
        case 241: return vext_##base(vdup_lane_##base(a, 3), a, 2); \
        case 242: return vuzp1_##base(vdup_lane_##base(a, 3), a); \
        case 243: return vcopy_lane_##base(vdup_lane_##base(a, 3), 2, a, 0); \
        case 244: return vcopy_lane_##base(vrev64_##base(a), 1, a, 3); \
        case 245: return vext_##base(vtrn2_##base(a, a), vtrn2_##base(a, a), 2); \
        case 246: return vcopy_lane_##base(vext_##base(a, a, 3), 1, a, 3); \
        case 247: return vuzp2_##base(vdup_lane_##base(a, 3), a); \
        case 248: return vzip2_##base(vrev32_##base(a), vext_##base(a, a, 1)); \
        case 249: return vext_##base(a, vrev64_##base(a), 3); \
        case 250: return vzip1_##base(vrev64_##base(a), vrev64_##base(a)); \
        case 251: return vzip1_##base(vrev64_##base(a), vdup_lane_##base(a, 3)); \
        case 252: return vext_##base(vdup_lane_##base(a, 3), a, 1); \
        case 253: return vtrn1_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 254: return vzip1_##base(vdup_lane_##base(a, 3), vrev64_##base(a)); \
        case 255: return vdup_lane_##base(a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 < 8) && (v1 < 8) && (v2 < 8) && (v3 < 8) && (v4 < 8) && (v5 < 8) && (v6 < 8) && (v7 < 8), "Indexes must not exceed lane count"); \
    \
    return vtbl1_##base(a, CC_SIMD_NAME(CCSimdLoad, base, count)((CC_SIMD_BASE_TYPE(base)[8]){ v0, v1, v2, v3, v4, v5, v6, v7, })); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 1) | v1) \
    { \
        case 0: return a; \
        case 1: return vcopy_lane_##base(a, 1, b, 1); \
        case 2: return vcopy_lane_##base(a, 0, b, 0); \
        case 3: return b; \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 3) | (v1 << 2) | (v2 << 1) | v3) \
    { \
        case 0: return a; \
        case 1: return vcopy_lane_##base(a, 3, b, 3); \
        case 2: return vcopy_lane_##base(a, 2, b, 2); \
        case 3: return vreinterpret_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 2)(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b), 0, 1)); \
        case 4: return vcopy_lane_##base(a, 1, b, 1); \
        case 5: return vtrn2_##base(vrev32_##base(a), b); \
        case 6: return vcopy_lane_##base(vcopy_lane_##base(b, 0, a, 0), 3, a, 3); \
        case 7: return vcopy_lane_##base(b, 0, a, 0); \
        case 8: return vcopy_lane_##base(a, 0, b, 0); \
        case 9: return vcopy_lane_##base(vcopy_lane_##base(a, 0, b, 0), 3, b, 3); \
        case 10: return vtrn2_##base(vrev32_##base(b), a); \
        case 11: return vcopy_lane_##base(b, 1, a, 1); \
        case 12: return vreinterpret_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 2)(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b), 1, 0)); \
        case 13: return vcopy_lane_##base(b, 2, a, 2); \
        case 14: return vcopy_lane_##base(b, 3, a, 3); \
        case 15: return b; \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2) && (v4 < 2) && (v5 < 2) && (v6 < 2) && (v7 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 7) | (v1 << 6) | (v2 << 5) | (v3 << 4) | (v4 << 3) | (v5 << 2) | (v6 << 1) | v7) \
    { \
        case 0: return a; \
        case 1: return vcopy_lane_##base(a, 7, b, 7); \
        case 2: return vcopy_lane_##base(a, 6, b, 6); \
        case 4: return vcopy_lane_##base(a, 5, b, 5); \
        case 8: return vcopy_lane_##base(a, 4, b, 4); \
        case 16: return vcopy_lane_##base(a, 3, b, 3); \
        case 32: return vcopy_lane_##base(a, 2, b, 2); \
        case 64: return vcopy_lane_##base(a, 1, b, 1); \
        case 128: return vcopy_lane_##base(a, 0, b, 0); \
        case 255: return b; \
            \
        case 3: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 0, 0, 1)); \
        case 12: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 0, 1, 0)); \
        case 15: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 0, 1, 1)); \
        case 48: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 0, 0)); \
        case 51: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 0, 1)); \
        case 60: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 1, 0)); \
        case 63: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 0, 1, 1, 1)); \
        case 192: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 0, 0)); \
        case 195: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 0, 1)); \
        case 204: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 1, 0)); \
        case 207: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 0, 1, 1)); \
        case 240: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 1, 0, 0)); \
        case 243: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 1, 0, 1)); \
        case 252: return vreinterpret_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 4)(vreinterpret_##kind##16_##base(a), vreinterpret_##kind##16_##base(b), 1, 1, 1, 0)); \
    } \
    \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = vcopy_lane_##base(Result, 0, b, 0); \
    if (v1) Result = vcopy_lane_##base(Result, 1, b, 1); \
    if (v2) Result = vcopy_lane_##base(Result, 2, b, 2); \
    if (v3) Result = vcopy_lane_##base(Result, 3, b, 3); \
    if (v4) Result = vcopy_lane_##base(Result, 4, b, 4); \
    if (v5) Result = vcopy_lane_##base(Result, 5, b, 5); \
    if (v6) Result = vcopy_lane_##base(Result, 6, b, 6); \
    if (v7) Result = vcopy_lane_##base(Result, 7, b, 7); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_MERGE_MASK(x0, x1) ((x0) << 5) | (x1)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog(((v0 & 0xf) < 2) && ((v1 & 0xf) < 2), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1) & ~0x11), "Indexes must only reference either a or b"); \
    \
    switch (CC_SIMD_MERGE_MASK(v0, v1)) \
    { \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0): return vzip1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1): return vzip2_##base(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0): return vext_##base(a, b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1): return vzip2_##base(a, b); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0): return vzip1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1): return vzip2_##base(CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, 0, 0), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0): return vext_##base(b, a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1): return vzip2_##base(b, a); \
    } \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 1, v1 & 1), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 1, v1 & 1), v0 >> 4, v1 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_MERGE_MASK

#define CC_SIMD_MERGE_MASK(x0, x1, x2, x3) ((x0) << 15) | ((x1) << 10) | ((x2) << 5) | (x3)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog(((v0 & 0xf) < 4) && ((v1 & 0xf) < 4) && ((v2 & 0xf) < 4) && ((v3 & 0xf) < 4), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1 | v2 | v3) & ~0x13), "Indexes must only reference either a or b"); \
    \
    switch (CC_SIMD_MERGE_MASK(v0, v1, v2, v3)) \
    { \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B3): return vreinterpret_##base##_##kind##32(vzip2_s32(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A3): return vreinterpret_##base##_##kind##32(vzip2_s32(vreinterpret_##kind##32_##base(b), vreinterpret_##kind##32_##base(a))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_A1): return vreinterpret_##base##_##kind##32(vzip1_s32(vreinterpret_##kind##32_##base(b), vreinterpret_##kind##32_##base(a))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_B1): return vreinterpret_##base##_##kind##32(vzip1_s32(vreinterpret_##kind##32_##base(a), vreinterpret_##kind##32_##base(b))); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B1): return vzip1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A1): return vzip1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B3): return vzip2_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A3): return vzip2_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B2): return vuzp1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A2): return vuzp1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B3): return vuzp2_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A3): return vuzp2_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B2): return vtrn1_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A2): return vtrn1_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B3): return vtrn2_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A3): return vtrn2_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B0): return vext_##base(a, b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A0): return vext_##base(b, a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B1): return vext_##base(a, b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A1): return vext_##base(b, a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vext_##base(a, b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vext_##base(b, a, 3); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A0): return vrev64_##base(vzip1_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B0): return vrev64_##base(vzip1_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A2): return vrev64_##base(vzip2_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B2): return vrev64_##base(vzip2_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_A0): return vrev64_##base(vuzp1_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_B0): return vrev64_##base(vuzp1_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_A1): return vrev64_##base(vuzp2_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_B1): return vrev64_##base(vuzp2_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A0): return vrev64_##base(vtrn1_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B0): return vrev64_##base(vtrn1_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A1): return vrev64_##base(vtrn2_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B1): return vrev64_##base(vtrn2_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vrev64_##base(vext_##base(a, b, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3): return vrev32_##base(vext_##base(a, b, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vrev64_##base(vext_##base(b, a, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3): return vrev32_##base(vext_##base(b, a, 1)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_A2): return vrev64_##base(vext_##base(a, b, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B0): return vrev32_##base(vext_##base(a, b, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_B2): return vrev64_##base(vext_##base(b, a, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A0): return vrev32_##base(vext_##base(b, a, 2)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A3): return vrev64_##base(vext_##base(a, b, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B1): return vrev32_##base(vext_##base(a, b, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B3): return vrev64_##base(vext_##base(b, a, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A1): return vrev32_##base(vext_##base(b, a, 3)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B1): return vzip1_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B1): return vzip1_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B2): return vzip1_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B0): return vzip1_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B2): return vzip1_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B0): return vzip1_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A2): return vzip1_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A0): return vzip1_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A1): return vzip1_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A1): return vzip1_##base(vrev32_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A2): return vzip1_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A0): return vzip1_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B3): return vzip2_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B3): return vzip2_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B0): return vzip2_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B2): return vzip2_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A0): return vzip2_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A2): return vzip2_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A3): return vzip2_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A3): return vzip2_##base(vrev32_##base(b), a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_B2): return vuzp1_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B2): return vuzp1_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B1): return vuzp1_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B3): return vuzp1_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B1): return vuzp1_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_B3): return vuzp1_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A1): return vuzp1_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A3): return vuzp1_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_A2): return vuzp1_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A2): return vuzp1_##base(vrev32_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A1): return vuzp1_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_A3): return vuzp1_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B3): return vuzp2_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B0): return vuzp2_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_B0): return vuzp2_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B2): return vuzp2_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A0): return vuzp2_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A3): return vuzp2_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_A0): return vuzp2_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A2): return vuzp2_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B2): return vtrn1_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2): return vtrn1_##base(vrev32_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B1): return vtrn1_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B3): return vtrn1_##base(a, vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B1): return vtrn1_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B3): return vtrn1_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A1): return vtrn1_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A3): return vtrn1_##base(b, vrev32_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A2): return vtrn1_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2): return vtrn1_##base(vrev32_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A1): return vtrn1_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A3): return vtrn1_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3): return vtrn2_##base(vrev64_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B0): return vtrn2_##base(a, vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B0): return vtrn2_##base(vrev32_##base(a), vrev64_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B2): return vtrn2_##base(vrev64_##base(a), vrev32_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A0): return vtrn2_##base(b, vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3): return vtrn2_##base(vrev64_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A0): return vtrn2_##base(vrev32_##base(b), vrev64_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A2): return vtrn2_##base(vrev64_##base(b), vrev32_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B0): return vext_##base(vrev64_##base(a), b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B0): return vext_##base(vrev32_##base(a), b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B3): return vext_##base(a, vrev64_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B1): return vext_##base(a, vrev32_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B3): return vext_##base(vrev32_##base(a), vrev64_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B1): return vext_##base(vrev64_##base(a), vrev32_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B1): return vext_##base(vrev32_##base(a), vrev32_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A3): return vext_##base(b, vrev64_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A1): return vext_##base(b, vrev32_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A0): return vext_##base(vrev64_##base(b), a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A0): return vext_##base(vrev32_##base(b), a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A3): return vext_##base(vrev32_##base(b), vrev64_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A1): return vext_##base(vrev64_##base(b), vrev32_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A1): return vext_##base(vrev32_##base(b), vrev32_##base(a), 1); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1): return vext_##base(vrev64_##base(a), b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B1): return vext_##base(vrev32_##base(a), b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B2): return vext_##base(a, vrev64_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B0): return vext_##base(a, vrev32_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B2): return vext_##base(vrev32_##base(a), vrev64_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B0): return vext_##base(vrev64_##base(a), vrev32_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A2): return vext_##base(b, vrev64_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A0): return vext_##base(b, vrev32_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A1): return vext_##base(vrev64_##base(b), a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A1): return vext_##base(vrev32_##base(b), a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A2): return vext_##base(vrev32_##base(b), vrev64_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A0): return vext_##base(vrev64_##base(b), vrev32_##base(a), 2); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vext_##base(vrev64_##base(a), b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vext_##base(vrev32_##base(a), b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vext_##base(a, vrev64_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vext_##base(a, vrev32_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vext_##base(vrev32_##base(a), vrev64_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vext_##base(vrev64_##base(a), vrev32_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vext_##base(vrev32_##base(a), vrev32_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vext_##base(b, vrev64_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vext_##base(b, vrev32_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vext_##base(vrev64_##base(b), a, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vext_##base(vrev32_##base(b), a, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vext_##base(vrev32_##base(b), vrev64_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vext_##base(vrev64_##base(b), vrev32_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vext_##base(vrev32_##base(b), vrev32_##base(a), 3); \
    } \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 3, v1 & 3, v2 & 3, v3 & 3), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 3, v1 & 3, v2 & 3, v3 & 3), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_MERGE_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog(((v0 & 0xf) < 8) && ((v1 & 0xf) < 8) && ((v2 & 0xf) < 8) && ((v3 & 0xf) < 8) && ((v4 & 0xf) < 8) && ((v5 & 0xf) < 8) && ((v6 & 0xf) < 8) && ((v7 & 0xf) < 8), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7) & ~0x17), "Indexes must only reference either a or b"); \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 7, v1 & 7, v2 & 7, v3 & 7, v4 & 7, v5 & 7, v6 & 7, v7 & 7), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 7, v1 & 7, v2 & 7, v3 & 7, v4 & 7, v5 & 7, v6 & 7, v7 & 7), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4, v4 >> 4, v5 >> 4, v6 >> 4, v7 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_64_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#endif

#endif
