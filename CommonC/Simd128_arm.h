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

#ifndef CommonC_Simd128_arm_h
#define CommonC_Simd128_arm_h

#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>


#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) v){ return vdupq_n_##base(v); }
CC_SIMD_DECL(CCSimdFill, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_BASE_TYPE(base) src[count]){ return vld1q_##base(src); }
CC_SIMD_DECL(CCSimdLoad, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (CC_SIMD_BASE_TYPE(base) dst[count], const CC_SIMD_TYPE(base, count) src){ vst1q_##base(dst, src); }
CC_SIMD_DECL(CCSimdStore, CC_SIMD_RETURN_TYPE(void), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, n, kind) (const CC_SIMD_BASE_TYPE(base) src[count * n]) \
{ \
    CC_SIMD_INTERNAL_POLY_TYPE(base, count, n) Result = vld##n##q_##base((void*)src); \
    return ((CC_SIMD_POLY_TYPE(base, count, n)){ .v = { CC_REPEAT(0, n, CC_SIMD_INTERNAL_POLY_VALUE, Result) } }); \
}
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 2, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_128_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 3, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_128_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveLoad, 4, CC_SIMD_RETURN_TYPE_SIMD_POLY, CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, n, kind) (CC_SIMD_BASE_TYPE(base) dst[count * n], const CC_SIMD_POLY_TYPE(base, count, n) src) \
{ \
    vst##n##q_##base((void*)dst, ((CC_SIMD_INTERNAL_POLY_TYPE(base, count, n)){ .val = { CC_REPEAT(0, n, CC_SIMD_POLY_VALUE, src) } })); \
}
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 2, CC_SIMD_RETURN_TYPE(void), CC_SIMD_128_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 3, CC_SIMD_RETURN_TYPE(void), CC_SIMD_128_TYPES)
CC_SIMD_POLY_DECL(CCSimdInterleaveStore, 4, CC_SIMD_RETURN_TYPE(void), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 2, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vgetq_lane_##base(a, 0); \
        case 1: return vgetq_lane_##base(a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 4, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vgetq_lane_##base(a, 0); \
        case 1: return vgetq_lane_##base(a, 1); \
        case 2: return vgetq_lane_##base(a, 2); \
        case 3: return vgetq_lane_##base(a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 8, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vgetq_lane_##base(a, 0); \
        case 1: return vgetq_lane_##base(a, 1); \
        case 2: return vgetq_lane_##base(a, 2); \
        case 3: return vgetq_lane_##base(a, 3); \
        case 4: return vgetq_lane_##base(a, 4); \
        case 5: return vgetq_lane_##base(a, 5); \
        case 6: return vgetq_lane_##base(a, 6); \
        case 7: return vgetq_lane_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index) \
{ \
    CCAssertLog(index < 16, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vgetq_lane_##base(a, 0); \
        case 1: return vgetq_lane_##base(a, 1); \
        case 2: return vgetq_lane_##base(a, 2); \
        case 3: return vgetq_lane_##base(a, 3); \
        case 4: return vgetq_lane_##base(a, 4); \
        case 5: return vgetq_lane_##base(a, 5); \
        case 6: return vgetq_lane_##base(a, 6); \
        case 7: return vgetq_lane_##base(a, 7); \
        case 8: return vgetq_lane_##base(a, 8); \
        case 9: return vgetq_lane_##base(a, 9); \
        case 10: return vgetq_lane_##base(a, 10); \
        case 11: return vgetq_lane_##base(a, 11); \
        case 12: return vgetq_lane_##base(a, 12); \
        case 13: return vgetq_lane_##base(a, 13); \
        case 14: return vgetq_lane_##base(a, 14); \
        case 15: return vgetq_lane_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdGet, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 2, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vsetq_lane_##base(v, a, 0); \
        case 1: return vsetq_lane_##base(v, a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 4, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vsetq_lane_##base(v, a, 0); \
        case 1: return vsetq_lane_##base(v, a, 1); \
        case 2: return vsetq_lane_##base(v, a, 2); \
        case 3: return vsetq_lane_##base(v, a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 8, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vsetq_lane_##base(v, a, 0); \
        case 1: return vsetq_lane_##base(v, a, 1); \
        case 2: return vsetq_lane_##base(v, a, 2); \
        case 3: return vsetq_lane_##base(v, a, 3); \
        case 4: return vsetq_lane_##base(v, a, 4); \
        case 5: return vsetq_lane_##base(v, a, 5); \
        case 6: return vsetq_lane_##base(v, a, 6); \
        case 7: return vsetq_lane_##base(v, a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t index, CC_SIMD_BASE_TYPE(base) v) \
{ \
    CCAssertLog(index < 16, "Index must not exceed lane count"); \
    \
    switch (index) \
    { \
        case 0: return vsetq_lane_##base(v, a, 0); \
        case 1: return vsetq_lane_##base(v, a, 1); \
        case 2: return vsetq_lane_##base(v, a, 2); \
        case 3: return vsetq_lane_##base(v, a, 3); \
        case 4: return vsetq_lane_##base(v, a, 4); \
        case 5: return vsetq_lane_##base(v, a, 5); \
        case 6: return vsetq_lane_##base(v, a, 6); \
        case 7: return vsetq_lane_##base(v, a, 7); \
        case 8: return vsetq_lane_##base(v, a, 8); \
        case 9: return vsetq_lane_##base(v, a, 9); \
        case 10: return vsetq_lane_##base(v, a, 10); \
        case 11: return vsetq_lane_##base(v, a, 11); \
        case 12: return vsetq_lane_##base(v, a, 12); \
        case 13: return vsetq_lane_##base(v, a, 13); \
        case 14: return vsetq_lane_##base(v, a, 14); \
        case 15: return vsetq_lane_##base(v, a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define vreinterpretq_s8_s8(x) (x)
#define vreinterpretq_s16_s16(x) (x)
#define vreinterpretq_s32_s32(x) (x)
#define vreinterpretq_s64_s64(x) (x)
#define vreinterpretq_u8_u8(x) (x)
#define vreinterpretq_u16_u16(x) (x)
#define vreinterpretq_u32_u32(x) (x)
#define vreinterpretq_u64_u64(x) (x)
#define vreinterpretq_f32_f32(x) (x)
#define vreinterpretq_f64_f64(x) (x)

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_s8_##base(a); }
CC_SIMD_DECL(CCSimd_s8x16_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s8x16), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_s16_##base(a); }
CC_SIMD_DECL(CCSimd_s16x8_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s16x8), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_s32_##base(a); }
CC_SIMD_DECL(CCSimd_s32x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s32x4), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_s64_##base(a); }
CC_SIMD_DECL(CCSimd_s64x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_s64x2), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_u8_##base(a); }
CC_SIMD_DECL(CCSimd_u8x16_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u8x16), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_u16_##base(a); }
CC_SIMD_DECL(CCSimd_u16x8_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u16x8), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_u32_##base(a); }
CC_SIMD_DECL(CCSimd_u32x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u32x4), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_u64_##base(a); }
CC_SIMD_DECL(CCSimd_u64x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_u64x2), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_f32_##base(a); }
CC_SIMD_DECL(CCSimd_f32x4_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_f32x4), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vreinterpretq_f64_##base(a); }
CC_SIMD_DECL(CCSimd_f64x2_Reinterpret, CC_SIMD_RETURN_TYPE(CCSimd_f64x2), CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define vcvtq_s8_s8(x) (x)
#define vcvtq_s8_u8(x) (x)
#define vcvtq_u8_s8(x) (x)
#define vcvtq_s16_s16(x) (x)
#define vcvtq_s16_u16(x) (x)
#define vcvtq_u16_s16(x) (x)
#define vcvtq_s32_s32(x) (x)
#define vcvtq_s32_u32(x) (x)
#define vcvtq_u32_s32(x) (x)
#define vcvtq_s64_s64(x) (x)
#define vcvtq_s64_u64(x) (x)
#define vcvtq_u64_s64(x) (x)
#define vcvtq_u8_u8(x) (x)
#define vcvtq_u8_s8(x) (x)
#define vcvtq_s8_u8(x) (x)
#define vcvtq_u16_u16(x) (x)
#define vcvtq_u16_s16(x) (x)
#define vcvtq_s16_u16(x) (x)
#define vcvtq_u32_u32(x) (x)
#define vcvtq_u32_s32(x) (x)
#define vcvtq_s32_u32(x) (x)
#define vcvtq_u64_u64(x) (x)
#define vcvtq_u64_s64(x) (x)
#define vcvtq_s64_u64(x) (x)
#define vcvtq_f32_f32(x) (x)
#define vcvtq_f64_f64(x) (x)

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_s8_##base(a); }
CC_SIMD_DECL(CCSimd_s8x16_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s8x16), CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_s16_##base(a); }
CC_SIMD_DECL(CCSimd_s16x8_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s16x8), CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_s32_##base(a); }
CC_SIMD_DECL(CCSimd_s32x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s32x4), CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_s64_##base(a); }
CC_SIMD_DECL(CCSimd_s64x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_s64x2), CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_u8_##base(a); }
CC_SIMD_DECL(CCSimd_u8x16_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u8x16), CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_u16_##base(a); }
CC_SIMD_DECL(CCSimd_u16x8_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u16x8), CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_u32_##base(a); }
CC_SIMD_DECL(CCSimd_u32x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u32x4), CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_u64_##base(a); }
CC_SIMD_DECL(CCSimd_u64x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_u64x2), CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_f32_##base(a); }
CC_SIMD_DECL(CCSimd_f32x4_Cast, CC_SIMD_RETURN_TYPE(CCSimd_f32x4), CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vcvtq_f64_##base(a); }
CC_SIMD_DECL(CCSimd_f64x2_Cast, CC_SIMD_RETURN_TYPE(CCSimd_f64x2), CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vmvnq_##base(a); }
CC_SIMD_DECL(CCSimdNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_128_4_ELEMENT_TYPES, CC_SIMD_128_8_ELEMENT_TYPES, CC_SIMD_128_16_ELEMENT_TYPES), CC_SIMD_128_INTEGER_TYPES))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u8x16)(vmvnq_u8(CC_SIMD_NAME(CCSimd_u8x16_Reinterpret, base, count)(a))); }
CC_SIMD_DECL(CCSimdNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_128_2_ELEMENT_TYPES), CC_SIMD_128_INTEGER_TYPES))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vandq_##base(a, b); }
CC_SIMD_DECL(CCSimdAnd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vorrq_##base(a, b); }
CC_SIMD_DECL(CCSimdOr, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vornq_##base(a, b); }
CC_SIMD_DECL(CCSimdOrNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return veorq_##base(a, b); }
CC_SIMD_DECL(CCSimdXor, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vshlq_##base(a, b); }
CC_SIMD_DECL(CCSimdShiftLeft, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshlq_n_##base(a, 1); \
        case 2: return vshlq_n_##base(a, 2); \
        case 3: return vshlq_n_##base(a, 3); \
        case 4: return vshlq_n_##base(a, 4); \
        case 5: return vshlq_n_##base(a, 5); \
        case 6: return vshlq_n_##base(a, 6); \
        case 7: return vshlq_n_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_16_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshlq_n_##base(a, 1); \
        case 2: return vshlq_n_##base(a, 2); \
        case 3: return vshlq_n_##base(a, 3); \
        case 4: return vshlq_n_##base(a, 4); \
        case 5: return vshlq_n_##base(a, 5); \
        case 6: return vshlq_n_##base(a, 6); \
        case 7: return vshlq_n_##base(a, 7); \
        case 8: return vshlq_n_##base(a, 8); \
        case 9: return vshlq_n_##base(a, 9); \
        case 10: return vshlq_n_##base(a, 10); \
        case 11: return vshlq_n_##base(a, 11); \
        case 12: return vshlq_n_##base(a, 12); \
        case 13: return vshlq_n_##base(a, 13); \
        case 14: return vshlq_n_##base(a, 14); \
        case 15: return vshlq_n_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshlq_n_##base(a, 1); \
        case 2: return vshlq_n_##base(a, 2); \
        case 3: return vshlq_n_##base(a, 3); \
        case 4: return vshlq_n_##base(a, 4); \
        case 5: return vshlq_n_##base(a, 5); \
        case 6: return vshlq_n_##base(a, 6); \
        case 7: return vshlq_n_##base(a, 7); \
        case 8: return vshlq_n_##base(a, 8); \
        case 9: return vshlq_n_##base(a, 9); \
        case 10: return vshlq_n_##base(a, 10); \
        case 11: return vshlq_n_##base(a, 11); \
        case 12: return vshlq_n_##base(a, 12); \
        case 13: return vshlq_n_##base(a, 13); \
        case 14: return vshlq_n_##base(a, 14); \
        case 15: return vshlq_n_##base(a, 15); \
        case 16: return vshlq_n_##base(a, 16); \
        case 17: return vshlq_n_##base(a, 17); \
        case 18: return vshlq_n_##base(a, 18); \
        case 19: return vshlq_n_##base(a, 19); \
        case 20: return vshlq_n_##base(a, 20); \
        case 21: return vshlq_n_##base(a, 21); \
        case 22: return vshlq_n_##base(a, 22); \
        case 23: return vshlq_n_##base(a, 23); \
        case 24: return vshlq_n_##base(a, 24); \
        case 25: return vshlq_n_##base(a, 25); \
        case 26: return vshlq_n_##base(a, 26); \
        case 27: return vshlq_n_##base(a, 27); \
        case 28: return vshlq_n_##base(a, 28); \
        case 29: return vshlq_n_##base(a, 29); \
        case 30: return vshlq_n_##base(a, 30); \
        case 31: return vshlq_n_##base(a, 31); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshlq_n_##base(a, 1); \
        case 2: return vshlq_n_##base(a, 2); \
        case 3: return vshlq_n_##base(a, 3); \
        case 4: return vshlq_n_##base(a, 4); \
        case 5: return vshlq_n_##base(a, 5); \
        case 6: return vshlq_n_##base(a, 6); \
        case 7: return vshlq_n_##base(a, 7); \
        case 8: return vshlq_n_##base(a, 8); \
        case 9: return vshlq_n_##base(a, 9); \
        case 10: return vshlq_n_##base(a, 10); \
        case 11: return vshlq_n_##base(a, 11); \
        case 12: return vshlq_n_##base(a, 12); \
        case 13: return vshlq_n_##base(a, 13); \
        case 14: return vshlq_n_##base(a, 14); \
        case 15: return vshlq_n_##base(a, 15); \
        case 16: return vshlq_n_##base(a, 16); \
        case 17: return vshlq_n_##base(a, 17); \
        case 18: return vshlq_n_##base(a, 18); \
        case 19: return vshlq_n_##base(a, 19); \
        case 20: return vshlq_n_##base(a, 20); \
        case 21: return vshlq_n_##base(a, 21); \
        case 22: return vshlq_n_##base(a, 22); \
        case 23: return vshlq_n_##base(a, 23); \
        case 24: return vshlq_n_##base(a, 24); \
        case 25: return vshlq_n_##base(a, 25); \
        case 26: return vshlq_n_##base(a, 26); \
        case 27: return vshlq_n_##base(a, 27); \
        case 28: return vshlq_n_##base(a, 28); \
        case 29: return vshlq_n_##base(a, 29); \
        case 30: return vshlq_n_##base(a, 30); \
        case 31: return vshlq_n_##base(a, 31); \
        case 32: return vshlq_n_##base(a, 32); \
        case 33: return vshlq_n_##base(a, 33); \
        case 34: return vshlq_n_##base(a, 34); \
        case 35: return vshlq_n_##base(a, 35); \
        case 36: return vshlq_n_##base(a, 36); \
        case 37: return vshlq_n_##base(a, 37); \
        case 38: return vshlq_n_##base(a, 38); \
        case 39: return vshlq_n_##base(a, 39); \
        case 40: return vshlq_n_##base(a, 40); \
        case 41: return vshlq_n_##base(a, 41); \
        case 42: return vshlq_n_##base(a, 42); \
        case 43: return vshlq_n_##base(a, 43); \
        case 44: return vshlq_n_##base(a, 44); \
        case 45: return vshlq_n_##base(a, 45); \
        case 46: return vshlq_n_##base(a, 46); \
        case 47: return vshlq_n_##base(a, 47); \
        case 48: return vshlq_n_##base(a, 48); \
        case 49: return vshlq_n_##base(a, 49); \
        case 50: return vshlq_n_##base(a, 50); \
        case 51: return vshlq_n_##base(a, 51); \
        case 52: return vshlq_n_##base(a, 52); \
        case 53: return vshlq_n_##base(a, 53); \
        case 54: return vshlq_n_##base(a, 54); \
        case 55: return vshlq_n_##base(a, 55); \
        case 56: return vshlq_n_##base(a, 56); \
        case 57: return vshlq_n_##base(a, 57); \
        case 58: return vshlq_n_##base(a, 58); \
        case 59: return vshlq_n_##base(a, 59); \
        case 60: return vshlq_n_##base(a, 60); \
        case 61: return vshlq_n_##base(a, 61); \
        case 62: return vshlq_n_##base(a, 62); \
        case 63: return vshlq_n_##base(a, 63); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vshlq_##base(a, CC_SIMD_NAME(CCSimdNeg, base, count)(b)); }
CC_SIMD_DECL(CCSimdShiftRight, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshrq_n_##base(a, 1); \
        case 2: return vshrq_n_##base(a, 2); \
        case 3: return vshrq_n_##base(a, 3); \
        case 4: return vshrq_n_##base(a, 4); \
        case 5: return vshrq_n_##base(a, 5); \
        case 6: return vshrq_n_##base(a, 6); \
        case 7: return vshrq_n_##base(a, 7); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_16_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshrq_n_##base(a, 1); \
        case 2: return vshrq_n_##base(a, 2); \
        case 3: return vshrq_n_##base(a, 3); \
        case 4: return vshrq_n_##base(a, 4); \
        case 5: return vshrq_n_##base(a, 5); \
        case 6: return vshrq_n_##base(a, 6); \
        case 7: return vshrq_n_##base(a, 7); \
        case 8: return vshrq_n_##base(a, 8); \
        case 9: return vshrq_n_##base(a, 9); \
        case 10: return vshrq_n_##base(a, 10); \
        case 11: return vshrq_n_##base(a, 11); \
        case 12: return vshrq_n_##base(a, 12); \
        case 13: return vshrq_n_##base(a, 13); \
        case 14: return vshrq_n_##base(a, 14); \
        case 15: return vshrq_n_##base(a, 15); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_8_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshrq_n_##base(a, 1); \
        case 2: return vshrq_n_##base(a, 2); \
        case 3: return vshrq_n_##base(a, 3); \
        case 4: return vshrq_n_##base(a, 4); \
        case 5: return vshrq_n_##base(a, 5); \
        case 6: return vshrq_n_##base(a, 6); \
        case 7: return vshrq_n_##base(a, 7); \
        case 8: return vshrq_n_##base(a, 8); \
        case 9: return vshrq_n_##base(a, 9); \
        case 10: return vshrq_n_##base(a, 10); \
        case 11: return vshrq_n_##base(a, 11); \
        case 12: return vshrq_n_##base(a, 12); \
        case 13: return vshrq_n_##base(a, 13); \
        case 14: return vshrq_n_##base(a, 14); \
        case 15: return vshrq_n_##base(a, 15); \
        case 16: return vshrq_n_##base(a, 16); \
        case 17: return vshrq_n_##base(a, 17); \
        case 18: return vshrq_n_##base(a, 18); \
        case 19: return vshrq_n_##base(a, 19); \
        case 20: return vshrq_n_##base(a, 20); \
        case 21: return vshrq_n_##base(a, 21); \
        case 22: return vshrq_n_##base(a, 22); \
        case 23: return vshrq_n_##base(a, 23); \
        case 24: return vshrq_n_##base(a, 24); \
        case 25: return vshrq_n_##base(a, 25); \
        case 26: return vshrq_n_##base(a, 26); \
        case 27: return vshrq_n_##base(a, 27); \
        case 28: return vshrq_n_##base(a, 28); \
        case 29: return vshrq_n_##base(a, 29); \
        case 30: return vshrq_n_##base(a, 30); \
        case 31: return vshrq_n_##base(a, 31); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_4_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    switch (n) \
    { \
        case 0: return a; \
        case 1: return vshrq_n_##base(a, 1); \
        case 2: return vshrq_n_##base(a, 2); \
        case 3: return vshrq_n_##base(a, 3); \
        case 4: return vshrq_n_##base(a, 4); \
        case 5: return vshrq_n_##base(a, 5); \
        case 6: return vshrq_n_##base(a, 6); \
        case 7: return vshrq_n_##base(a, 7); \
        case 8: return vshrq_n_##base(a, 8); \
        case 9: return vshrq_n_##base(a, 9); \
        case 10: return vshrq_n_##base(a, 10); \
        case 11: return vshrq_n_##base(a, 11); \
        case 12: return vshrq_n_##base(a, 12); \
        case 13: return vshrq_n_##base(a, 13); \
        case 14: return vshrq_n_##base(a, 14); \
        case 15: return vshrq_n_##base(a, 15); \
        case 16: return vshrq_n_##base(a, 16); \
        case 17: return vshrq_n_##base(a, 17); \
        case 18: return vshrq_n_##base(a, 18); \
        case 19: return vshrq_n_##base(a, 19); \
        case 20: return vshrq_n_##base(a, 20); \
        case 21: return vshrq_n_##base(a, 21); \
        case 22: return vshrq_n_##base(a, 22); \
        case 23: return vshrq_n_##base(a, 23); \
        case 24: return vshrq_n_##base(a, 24); \
        case 25: return vshrq_n_##base(a, 25); \
        case 26: return vshrq_n_##base(a, 26); \
        case 27: return vshrq_n_##base(a, 27); \
        case 28: return vshrq_n_##base(a, 28); \
        case 29: return vshrq_n_##base(a, 29); \
        case 30: return vshrq_n_##base(a, 30); \
        case 31: return vshrq_n_##base(a, 31); \
        case 32: return vshrq_n_##base(a, 32); \
        case 33: return vshrq_n_##base(a, 33); \
        case 34: return vshrq_n_##base(a, 34); \
        case 35: return vshrq_n_##base(a, 35); \
        case 36: return vshrq_n_##base(a, 36); \
        case 37: return vshrq_n_##base(a, 37); \
        case 38: return vshrq_n_##base(a, 38); \
        case 39: return vshrq_n_##base(a, 39); \
        case 40: return vshrq_n_##base(a, 40); \
        case 41: return vshrq_n_##base(a, 41); \
        case 42: return vshrq_n_##base(a, 42); \
        case 43: return vshrq_n_##base(a, 43); \
        case 44: return vshrq_n_##base(a, 44); \
        case 45: return vshrq_n_##base(a, 45); \
        case 46: return vshrq_n_##base(a, 46); \
        case 47: return vshrq_n_##base(a, 47); \
        case 48: return vshrq_n_##base(a, 48); \
        case 49: return vshrq_n_##base(a, 49); \
        case 50: return vshrq_n_##base(a, 50); \
        case 51: return vshrq_n_##base(a, 51); \
        case 52: return vshrq_n_##base(a, 52); \
        case 53: return vshrq_n_##base(a, 53); \
        case 54: return vshrq_n_##base(a, 54); \
        case 55: return vshrq_n_##base(a, 55); \
        case 56: return vshrq_n_##base(a, 56); \
        case 57: return vshrq_n_##base(a, 57); \
        case 58: return vshrq_n_##base(a, 58); \
        case 59: return vshrq_n_##base(a, 59); \
        case 60: return vshrq_n_##base(a, 60); \
        case 61: return vshrq_n_##base(a, 61); \
        case 62: return vshrq_n_##base(a, 62); \
        case 63: return vshrq_n_##base(a, 63); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdShiftRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_2_ELEMENT_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vclzq_##base(a); }
CC_SIMD_DECL(CCSimdCountHighestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_128_4_ELEMENT_TYPES, CC_SIMD_128_8_ELEMENT_TYPES, CC_SIMD_128_16_ELEMENT_TYPES), CC_SIMD_128_INTEGER_TYPES))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CCSimd_u32x4 Result = CC_SIMD_NAME(CCSimd_u32x4_Reinterpret, base, count)(a); \
    CCSimd_u32x4 Mask = CCSimdSwizzle_u32x4(CCSimdMaskCompareEqual_u32x4(Result, CCSimdZero_s32x4()), 0, 0, 2, 2); \
    \
    Result = CCSimdCountHighestUnset_u32x4(Result); \
    \
    return CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _Reinterpret_u64x2)(CCSimdShiftRightN_u64x2(CCSimd_u64x2_Reinterpret_u32x4(CCSimdAdd_u32x4(Result, CCSimdSwizzle_u32x4(CCSimdAnd_u32x4(Result, Mask), 1, 1, 3, 3))), 32)); \
}
CC_SIMD_DECL(CCSimdCountHighestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_128_2_ELEMENT_TYPES), CC_SIMD_128_INTEGER_TYPES))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vceqq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vceqq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcltq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcltq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcleq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcleq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgtq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgtq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgeq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vcgeq_##base(a, b); }
CC_SIMD_DECL(CCSimdMaskCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vaddq_##base(a, b); }
CC_SIMD_DECL(CCSimdAdd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vsubq_##base(a, b); }
CC_SIMD_DECL(CCSimdSub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

// TODO: implement multiply s/u64
//#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmulq_##base(a, b); }
//CC_SIMD_DECL(CCSimdMul, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_64_TYPES)
//#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmulq_##base(a, b); }
CC_SIMD_DECL(CCSimdMul, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_8_TYPES, CC_SIMD_128_INTEGER_16_TYPES, CC_SIMD_128_INTEGER_32_TYPES, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfmaq_##base(c, a, b); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMadd
#define CC_SIMD_MISSING_CCSimdMadd CC_SIMD_128_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfmsq_##base(c, a, b); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdNegMadd
#define CC_SIMD_MISSING_CCSimdNegMadd CC_SIMD_128_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfmaq_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMsub
#define CC_SIMD_MISSING_CCSimdMsub CC_SIMD_128_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return vfmsq_##base(CC_SIMD_NAME(CCSimdNeg, base, count)(c), a, b); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdNegMsub
#define CC_SIMD_MISSING_CCSimdNegMsub CC_SIMD_128_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vdivq_##base(a, b); }
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdDiv
#define CC_SIMD_MISSING_CCSimdDiv CC_SIMD_128_INTEGER_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndaq_##base(a); }
CC_SIMD_DECL(CCSimdRoundNearestAway, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndnq_##base(a); }
CC_SIMD_DECL(CCSimdRoundNearestEven, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndq_##base(a); }
CC_SIMD_DECL(CCSimdRoundZero, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndmq_##base(a); }
CC_SIMD_DECL(CCSimdFloor, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrndpq_##base(a); }
CC_SIMD_DECL(CCSimdCeil, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vaddvq_##base(a); }
CC_SIMD_DECL(CCSimdSum, CC_SIMD_RETURN_TYPE_BASE, CC_SIMD_128_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vnegq_##base(a); }
CC_SIMD_DECL(CCSimdNeg, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_SIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_CAT(vreinterpretq_, base, _, CC_SIMD_SIGNED(base))(CC_CAT(vnegq_, CC_SIMD_SIGNED(base))(CC_CAT(vreinterpretq_, CC_SIMD_SIGNED(base), _, base)(a))); }
CC_SIMD_DECL(CCSimdNeg, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_UNSIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vabsq_##base(a); }
CC_SIMD_DECL(CCSimdAbs, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_SIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return a; }
CC_SIMD_DECL(CCSimdAbs, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_UNSIGNED_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vminq_##base(a, b); }
CC_SIMD_DECL(CCSimdMin, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_8_TYPES, CC_SIMD_128_INTEGER_16_TYPES, CC_SIMD_128_INTEGER_32_TYPES, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMin
#define CC_SIMD_MISSING_CCSimdMin CC_SIMD_128_INTEGER_64_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return vmaxq_##base(a, b); }
CC_SIMD_DECL(CCSimdMax, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_INTEGER_8_TYPES, CC_SIMD_128_INTEGER_16_TYPES, CC_SIMD_128_INTEGER_32_TYPES, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#undef CC_SIMD_MISSING_CCSimdMax
#define CC_SIMD_MISSING_CCSimdMax CC_SIMD_128_INTEGER_64_TYPES

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vsqrtq_##base(a); }
CC_SIMD_DECL(CCSimdSqrt, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return vrsqrteq_##base(a); }
CC_SIMD_DECL(CCSimdInvSqrt, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_FLOAT_TYPES)
#undef CC_SIMD_IMPL

#define vrev128q_s32(a) vcombine_s64(vrev64_s32(vget_high_s64(a)), vrev64_s32(vget_low_s64(a)))
#define vrev128q_u32(a) vcombine_u64(vrev64_u32(vget_high_u64(a)), vrev64_u32(vget_low_u64(a)))
#define vrev128q_f32(a) vcombine_f64(vrev64_f32(vget_high_f64(a)), vrev64_f32(vget_low_f64(a)))

#define vrev128q_s64(a) vcombine_s64(vget_high_s64(a), vget_low_s64(a))
#define vrev128q_u64(a) vcombine_u64(vget_high_u64(a), vget_low_u64(a))
#define vrev128q_f64(a) vcombine_f64(vget_high_f64(a), vget_low_f64(a))

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2), "Indexes must not exceed lane count"); \
    \
    switch ((v0 << 1) | v1) \
    { \
        case 0: return vdupq_laneq_##base(a, 0); \
        case 1: return a; \
        case 2: return vrev128q_##base(a); \
        case 3: return vdupq_laneq_##base(a, 1); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 < 4) && (v1 < 4) && (v2 < 4) && (v3 < 4), "Indexes must not exceed lane count"); \
    \
    switch ((v0 << 6) | (v1 << 4) | (v2 << 2) | v3) \
    { \
        case 0: return vdupq_laneq_##base(a, 0); \
        case 1: return vzip1q_##base(vdupq_laneq_##base(a, 0), a); \
        case 2: return vuzp1q_##base(vdupq_laneq_##base(a, 0), a); \
        case 3: return vextq_##base(vdupq_laneq_##base(a, 0), vdupq_laneq_##base(a, 3), 1); \
        case 4: return vzip1q_##base(a, vdupq_laneq_##base(a, 0)); \
        case 5: return vzip1q_##base(a, a); \
        case 6: return vextq_##base(vdupq_laneq_##base(a, 0), a, 3); \
        case 7: return vuzp2q_##base(vdupq_laneq_##base(a, 0), a); \
        case 8: return vtrn1q_##base(a, vdupq_laneq_##base(a, 0)); \
        case 9: return vtrn1q_##base(a, vzip1q_##base(a, a)); \
        case 10: return vtrn1q_##base(a, a); \
        case 11: return vcopyq_laneq_##base(a, 1, a, 0); \
        case 12: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 0), 2, a, 3); \
        case 13: return vcopyq_laneq_##base(vzip1q_##base(a, a), 2, a, 3); \
        case 14: return vcopyq_laneq_##base(vrev64q_##base(a), 0, a, 0); \
        case 15: return vextq_##base(vdupq_laneq_##base(a, 0), vdupq_laneq_##base(a, 3), 2); \
        case 16: return vzip2q_##base(vdupq_laneq_##base(a, 0), vrev128q_##base(a)); \
        case 17: return vreinterpretq_##base##_##kind##64(vdupq_laneq_##kind##64(vreinterpretq_##kind##64_##base(a), 0)); \
        case 18: return vcopyq_laneq_##base(vuzp1q_##base(a, a), 1, a, 1); \
        case 19: return vcopyq_laneq_##base(a, 2, a, 0); \
        case 20: return vzip1q_##base(a, vrev64q_##base(a)); \
        case 21: return vzip1q_##base(a, vdupq_laneq_##base(a, 1)); \
        case 22: return vzip1q_##base(a, vextq_##base(a, a, 1)); \
        case 23: return vcopyq_laneq_##base(a, 2, a, 1); \
        case 24: return vcopyq_laneq_##base(a, 3, a, 0); \
        case 25: return vcopyq_laneq_##base(a, 3, a, 1); \
        case 26: return vcopyq_laneq_##base(a, 3, a, 2); \
        case 27: return a; \
        case 28: return vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(vextq_##base(a, a, 1)), 0, vreinterpretq_##kind##64_##base(a), 0)); \
        case 29: return vcopyq_laneq_##base(vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(a), 1, vreinterpretq_##kind##64_##base(a), 0)), 2, a, 3); \
        case 30: return vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(vrev64q_##base(a)), 0, vreinterpretq_##kind##64_##base(a), 0)); \
        case 31: return vcopyq_laneq_##base(a, 2, a, 3); \
        case 32: return vuzp1q_##base(a, vdupq_laneq_##base(a, 0)); \
        case 33: return vcopyq_laneq_##base(vuzp1q_##base(a, a), 3, a, 1); \
        case 34: return vuzp1q_##base(a, a); \
        case 35: return vzip2q_##base(vdupq_laneq_##base(a, 0), a); \
        case 36: return vcopyq_laneq_##base(vrev128q_##base(a), 0, a, 0); \
        case 37: return vuzp1q_##base(a, vdupq_laneq_##base(a, 1)); \
        case 38: return vzip1q_##base(a, vdupq_laneq_##base(a, 2)); \
        case 39: return vuzp2q_##base(vrev64q_##base(a), a); \
        case 40: return vuzp1q_##base(a, vextq_##base(a, a, 2)); \
        case 41: return vcopyq_laneq_##base(vcopyq_laneq_##base(a, 1, a, 2), 3, a, 1); \
        case 42: return vuzp1q_##base(a, vdupq_laneq_##base(a, 2)); \
        case 43: return vcopyq_laneq_##base(a, 1, a, 2); \
        case 44: return vcopyq_laneq_##base(vextq_##base(a, a, 1), 0, a, 0); \
        case 45: return vuzp1q_##base(a, vrev128q_##base(a)); \
        case 46: return vcopyq_laneq_##base(vuzp1q_##base(a, a), 2, a, 3); \
        case 47: return vuzp1q_##base(a, vdupq_laneq_##base(a, 3)); \
        case 48: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 0), 1, a, 3); \
        case 49: return vtrn1q_##base(vdupq_laneq_##base(a, 0), vrev128q_##base(a)); \
        case 50: return vzip1q_##base(vdupq_laneq_##base(a, 0), vrev128q_##base(a)); \
        case 51: return vtrn1q_##base(vdupq_laneq_##base(a, 0), vdupq_laneq_##base(a, 3)); \
        case 52: return vzip1q_##base(a, vextq_##base(a, a, 3)); \
        case 53: return vcopyq_laneq_##base(vzip1q_##base(a, a), 1, a, 3); \
        case 54: return vzip1q_##base(a, vrev128q_##base(a)); \
        case 55: return vzip1q_##base(a, vdupq_laneq_##base(a, 3)); \
        case 56: return vextq_##base(vrev64q_##base(a), a, 1); \
        case 57: return vextq_##base(vrev128q_##base(a), vrev128q_##base(a), 3); \
        case 58: return vcopyq_laneq_##base(vtrn1q_##base(a, a), 1, a, 3); \
        case 59: return vcopyq_laneq_##base(a, 1, a, 3); \
        case 60: return vzip1q_##base(vzip1q_##base(a, vextq_##base(a, a, 3)), vextq_##base(a, a, 3)); \
        case 61: return vuzp1q_##base(vuzp1q_##base(a, vextq_##base(a, a, 3)), vextq_##base(a, a, 3)); \
        case 62: return vzip2q_##base(vextq_##base(vrev64q_##base(a), vrev64q_##base(a), 3), vrev64q_##base(a)); \
        case 63: return vextq_##base(vdupq_laneq_##base(a, 0), vdupq_laneq_##base(a, 3), 3); \
        case 64: return vzip2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 0)); \
        case 65: return vzip1q_##base(vrev64q_##base(a), a); \
        case 66: return vcopyq_laneq_##base(vrev64q_##base(a), 2, a, 0); \
        case 67: return vextq_##base(vzip1q_##base(a, vextq_##base(a, a, 3)), vzip1q_##base(a, vextq_##base(a, a, 3)), 2); \
        case 68: return vextq_##base(vrev128q_##base(a), vrev64q_##base(a), 2); \
        case 69: return vzip1q_##base(vdupq_laneq_##base(a, 1), a); \
        case 70: return vextq_##base(vdupq_laneq_##base(a, 1), a, 3); \
        case 71: return vcopyq_laneq_##base(vuzp2q_##base(a, a), 1, a, 0); \
        case 72: return vrev64q_##base(vuzp1q_##base(vzip1q_##base(a, a), a)); \
        case 73: return vzip1q_##base(vextq_##base(a, a, 1), a); \
        case 74: return vcopyq_laneq_##base(vrev64q_##base(a), 2, a, 2); \
        case 75: return vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(vrev64q_##base(a)), 1, vreinterpretq_##kind##64_##base(a), 1)); \
        case 76: return vtrn2q_##base(a, vdupq_laneq_##base(a, 0)); \
        case 77: return vcopyq_laneq_##base(vrev64q_##base(a), 3, a, 1); \
        case 78: return vextq_##base(vrev128q_##base(a), vrev128q_##base(a), 2); \
        case 79: return vcopyq_laneq_##base(vrev64q_##base(a), 3, a, 3); \
        case 80: return vzip2q_##base(vrev128q_##base(a), vrev128q_##base(a)); \
        case 81: return vextq_##base(vdupq_laneq_##base(a, 1), a, 2); \
        case 82: return vuzp1q_##base(vdupq_laneq_##base(a, 1), a); \
        case 83: return vcopyq_laneq_##base(vtrn2q_##base(a, a), 2, a, 0); \
        case 84: return vextq_##base(vdupq_laneq_##base(a, 1), a, 1); \
        case 85: return vdupq_laneq_##base(a, 1); \
        case 86: return vextq_##base(vdupq_laneq_##base(a, 1), vdupq_laneq_##base(a, 2), 1); \
        case 87: return vuzp2q_##base(vdupq_laneq_##base(a, 1), a); \
        case 88: return vcopyq_laneq_##base(vcopyq_laneq_##base(a, 0, a, 1), 3, a, 0); \
        case 89: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 1), 2, a, 2); \
        case 90: return vextq_##base(vdupq_laneq_##base(a, 1), vdupq_laneq_##base(a, 2), 2); \
        case 91: return vcopyq_laneq_##base(a, 0, a, 1); \
        case 92: return vcopyq_laneq_##base(vextq_##base(a, a, 1), 1, a, 1); \
        case 93: return vtrn2q_##base(a, vdupq_laneq_##base(a, 1)); \
        case 94: return vcopyq_laneq_##base(vrev64q_##base(a), 1, a, 1); \
        case 95: return vtrn2q_##base(a, a); \
        case 96: return vcopyq_laneq_##base(vextq_##base(a, a, 1), 2, a, 0); \
        case 97: return vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(vextq_##base(a, a, 1)), 1, vreinterpretq_##kind##64_##base(a), 0)); \
        case 98: return vzip2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 2)); \
        case 99: return vzip2q_##base(vrev128q_##base(a), a); \
        case 100: return vtrn2q_##base(vdupq_laneq_##base(a, 1), vrev128q_##base(a)); \
        case 101: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 1), 1, a, 2); \
        case 102: return vtrn1q_##base(vdupq_laneq_##base(a, 1), vdupq_laneq_##base(a, 2)); \
        case 103: return vzip2q_##base(vdupq_laneq_##base(a, 1), a); \
        case 104: return vcopyq_laneq_##base(vextq_##base(a, a, 1), 2, a, 2); \
        case 105: return vzip1q_##base(vextq_##base(a, a, 1), vrev64q_##base(vextq_##base(a, a, 1))); \
        case 106: return vextq_##base(vdupq_laneq_##base(a, 1), vdupq_laneq_##base(a, 2), 3); \
        case 107: return vzip2q_##base(vextq_##base(a, a, 3), a); \
        case 108: return vextq_##base(a, a, 1); \
        case 109: return vextq_##base(a, vrev64q_##base(a), 1); \
        case 110: return vextq_##base(a, vdupq_laneq_##base(a, 2), 1); \
        case 111: return vextq_##base(a, vdupq_laneq_##base(a, 3), 1); \
        case 112: return vuzp2q_##base(a, vdupq_laneq_##base(a, 0)); \
        case 113: return vcopyq_laneq_##base(vextq_##base(a, a, 2), 0, a, 1); \
        case 114: return vuzp1q_##base(vrev64q_##base(a), a); \
        case 115: return vzip2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 3)); \
        case 116: return vcopyq_laneq_##base(vuzp2q_##base(a, a), 3, a, 0); \
        case 117: return vuzp2q_##base(a, vdupq_laneq_##base(a, 1)); \
        case 118: return vzip1q_##base(vdupq_laneq_##base(a, 1), vrev128q_##base(a)); \
        case 119: return vuzp2q_##base(a, a); \
        case 120: return vuzp2q_##base(a, vrev128q_##base(a)); \
        case 121: return vuzp2q_##base(a, vuzp1q_##base(a, vdupq_laneq_##base(a, 1))); \
        case 122: return vuzp2q_##base(a, vdupq_laneq_##base(a, 2)); \
        case 123: return vcopyq_laneq_##base(vuzp2q_##base(a, a), 2, a, 2); \
        case 124: return vcopyq_laneq_##base(vextq_##base(a, a, 1), 1, a, 3); \
        case 125: return vuzp2q_##base(a, vextq_##base(a, a, 2)); \
        case 126: return vcopyq_laneq_##base(vrev64q_##base(a), 1, a, 3); \
        case 127: return vuzp2q_##base(a, vdupq_laneq_##base(a, 3)); \
        case 128: return vuzp2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 0)); \
        case 129: return vcopyq_laneq_##base(vextq_##base(a, a, 2), 1, a, 0); \
        case 130: return vuzp1q_##base(vextq_##base(a, a, 2), a); \
        case 131: return vuzp2q_##base(vextq_##base(a, a, 1), vuzp2q_##base(vextq_##base(a, a, 1), a)); \
        case 132: return vrev128q_##base(vuzp1q_##base(vzip1q_##base(a, a), a)); \
        case 133: return vuzp2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 1)); \
        case 134: return vextq_##base(vdupq_laneq_##base(a, 2), a, 3); \
        case 135: return vuzp2q_##base(vrev128q_##base(a), a); \
        case 136: return vuzp2q_##base(vrev128q_##base(a), vrev128q_##base(a)); \
        case 137: return vzip1q_##base(vdupq_laneq_##base(a, 2), a); \
        case 138: return vtrn1q_##base(vdupq_laneq_##base(a, 2), a); \
        case 139: return vcopyq_laneq_##base(vcopyq_laneq_##base(a, 0, a, 2), 1, a, 0); \
        case 140: return vzip2q_##base(a, vdupq_laneq_##base(a, 0)); \
        case 141: return vzip1q_##base(vextq_##base(a, a, 2), a); \
        case 142: return vtrn1q_##base(vzip2q_##base(a, a), a); \
        case 143: return vuzp2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 3)); \
        case 144: return vextq_##base(vrev128q_##base(a), a, 1); \
        case 145: return vextq_##base(vrev128q_##base(a), vrev64q_##base(a), 1); \
        case 146: return vuzp2q_##base(vuzp1q_##base(a, vextq_##base(a, a, 3)), vextq_##base(a, a, 3)); \
        case 147: return vextq_##base(vrev128q_##base(a), vrev128q_##base(a), 1); \
        case 148: return vzip2q_##base(vextq_##base(vrev128q_##base(a), vrev128q_##base(a), 3), vrev128q_##base(a)); \
        case 149: return vextq_##base(vdupq_laneq_##base(a, 2), vdupq_laneq_##base(a, 1), 3); \
        case 150: return vzip1q_##base(vrev64q_##base(vextq_##base(a, a, 1)), vextq_##base(a, a, 1)); \
        case 151: return vcopyq_laneq_##base(vcopyq_laneq_##base(a, 0, a, 2), 2, a, 1); \
        case 152: return vzip2q_##base(vdupq_laneq_##base(a, 2), vrev128q_##base(a)); \
        case 153: return vtrn1q_##base(vdupq_laneq_##base(a, 2), vdupq_laneq_##base(a, 1)); \
        case 154: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 2), 1, a, 1); \
        case 155: return vcopyq_laneq_##base(a, 0, a, 2); \
        case 156: return vzip2q_##base(a, vrev128q_##base(a)); \
        case 157: return vzip2q_##base(a, vdupq_laneq_##base(a, 1)); \
        case 158: return vzip2q_##base(a, vextq_##base(a, a, 3)); \
        case 159: return vcopyq_laneq_##base(vzip2q_##base(a, a), 1, a, 1); \
        case 160: return vextq_##base(vtrn1q_##base(a, a), vtrn1q_##base(a, a), 2); \
        case 161: return vextq_##base(vdupq_laneq_##base(a, 2), a, 2); \
        case 162: return vuzp1q_##base(vdupq_laneq_##base(a, 2), a); \
        case 163: return vcopyq_laneq_##base(vzip2q_##base(a, a), 2, a, 0); \
        case 164: return vcopyq_laneq_##base(vrev128q_##base(a), 0, a, 2); \
        case 165: return vextq_##base(vdupq_laneq_##base(a, 2), vdupq_laneq_##base(a, 1), 2); \
        case 166: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 2), 2, a, 1); \
        case 167: return vuzp2q_##base(vdupq_laneq_##base(a, 2), a); \
        case 168: return vextq_##base(vdupq_laneq_##base(a, 2), a, 1); \
        case 169: return vextq_##base(vdupq_laneq_##base(a, 2), vdupq_laneq_##base(a, 1), 1); \
        case 170: return vdupq_laneq_##base(a, 2); \
        case 171: return vzip2q_##base(vdupq_laneq_##base(a, 2), a); \
        case 172: return vcopyq_laneq_##base(vextq_##base(a, a, 1), 0, a, 2); \
        case 173: return vcopyq_laneq_##base(vzip2q_##base(a, a), 3, a, 1); \
        case 174: return vzip2q_##base(a, vdupq_laneq_##base(a, 2)); \
        case 175: return vzip2q_##base(a, a); \
        case 176: return vextq_##base(a, vdupq_laneq_##base(a, 0), 2); \
        case 177: return vextq_##base(a, a, 2); \
        case 178: return vcopyq_laneq_##base(vextq_##base(a, a, 2), 3, a, 2); \
        case 179: return vtrn2q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 3)); \
        case 180: return vextq_##base(a, vrev64q_##base(a), 2); \
        case 181: return vextq_##base(a, vdupq_laneq_##base(a, 1), 2); \
        case 182: return vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(vextq_##base(a, a, 3)), 0, vreinterpretq_##kind##64_##base(a), 1)); \
        case 183: return vcopyq_laneq_##base(vuzp2q_##base(a, a), 0, a, 2); \
        case 184: return vcopyq_laneq_##base(vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(a), 0, vreinterpretq_##kind##64_##base(a), 1)), 3, a, 0); \
        case 185: return vextq_##base(vrev64q_##base(a), vrev128q_##base(a), 3); \
        case 186: return vextq_##base(a, vdupq_laneq_##base(a, 2), 2); \
        case 187: return vreinterpretq_##base##_##kind##64(vdupq_laneq_##kind##64(vreinterpretq_##kind##64_##base(a), 1)); \
        case 188: return vzip2q_##base(a, vextq_##base(a, a, 1)); \
        case 189: return vcopyq_laneq_##base(vextq_##base(a, a, 2), 2, a, 3); \
        case 190: return vextq_##base(a, vrev128q_##base(a), 2); \
        case 191: return vextq_##base(a, vdupq_laneq_##base(a, 3), 2); \
        case 192: return vextq_##base(a, vdupq_laneq_##base(a, 0), 3); \
        case 193: return vzip1q_##base(vextq_##base(a, a, 3), a); \
        case 194: return vcopyq_laneq_##base(vextq_##base(a, a, 3), 2, a, 0); \
        case 195: return vzip1q_##base(vextq_##base(a, a, 3), vzip1q_##base(a, vextq_##base(a, a, 3))); \
        case 196: return vtrn1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 0)); \
        case 197: return vcopyq_laneq_##base(vzip1q_##base(a, a), 0, a, 3); \
        case 198: return vextq_##base(a, a, 3); \
        case 199: return vcopyq_laneq_##base(vextq_##base(a, a, 3), 3, a, 3); \
        case 200: return vzip1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 0)); \
        case 201: return vzip1q_##base(vrev128q_##base(a), a); \
        case 202: return vcopyq_laneq_##base(vextq_##base(a, a, 3), 2, a, 2); \
        case 203: return vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(vextq_##base(a, a, 3)), 1, vreinterpretq_##kind##64_##base(a), 1)); \
        case 204: return vtrn1q_##base(vdupq_laneq_##base(a, 3), vdupq_laneq_##base(a, 0)); \
        case 205: return vzip1q_##base(vdupq_laneq_##base(a, 3), a); \
        case 206: return vtrn1q_##base(vdupq_laneq_##base(a, 3), a); \
        case 207: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 3), 1, a, 0); \
        case 208: return vuzp1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 0)); \
        case 209: return vcopyq_laneq_##base(vreinterpretq_##base##_##kind##64(vcopyq_laneq_##kind##64(vreinterpretq_##kind##64_##base(a), 1, vreinterpretq_##kind##64_##base(a), 0)), 0, a, 3); \
        case 210: return vuzp1q_##base(vrev128q_##base(a), a); \
        case 211: return vextq_##base(a, vrev64q_##base(a), 3); \
        case 212: return vcopyq_laneq_##base(vrev128q_##base(a), 1, a, 1); \
        case 213: return vextq_##base(a, vdupq_laneq_##base(a, 1), 3); \
        case 214: return vcopyq_laneq_##base(vextq_##base(a, a, 3), 1, a, 1); \
        case 215: return vuzp2q_##base(vextq_##base(a, a, 2), a); \
        case 216: return vzip2q_##base(vrev64q_##base(a), vrev128q_##base(a)); \
        case 217: return vzip1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 1)); \
        case 218: return vuzp1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 2)); \
        case 219: return vcopyq_laneq_##base(a, 0, a, 3); \
        case 220: return vzip2q_##base(vdupq_laneq_##base(a, 3), vrev128q_##base(a)); \
        case 221: return vuzp1q_##base(vrev128q_##base(a), vrev128q_##base(a)); \
        case 222: return vrev128q_##base(vuzp2q_##base(vzip2q_##base(a, a), a)); \
        case 223: return vtrn2q_##base(vdupq_laneq_##base(a, 3), a); \
        case 224: return vcopyq_laneq_##base(vrev128q_##base(a), 2, a, 0); \
        case 225: return vextq_##base(vrev64q_##base(a), a, 2); \
        case 226: return vcopyq_laneq_##base(vuzp1q_##base(a, a), 0, a, 3); \
        case 227: return vzip2q_##base(vextq_##base(a, a, 1), a); \
        case 228: return vrev128q_##base(a); \
        case 229: return vcopyq_laneq_##base(vrev128q_##base(a), 3, a, 1); \
        case 230: return vtrn1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 2)); \
        case 231: return vcopyq_laneq_##base(vrev128q_##base(a), 3, a, 3); \
        case 232: return vcopyq_laneq_##base(vrev128q_##base(a), 2, a, 2); \
        case 233: return vextq_##base(a, vuzp2q_##base(vuzp1q_##base(a, a), a), 3); \
        case 234: return vextq_##base(a, vdupq_laneq_##base(a, 2), 3); \
        case 235: return vzip2q_##base(vrev64q_##base(a), a); \
        case 236: return vtrn2q_##base(vdupq_laneq_##base(a, 3), vrev128q_##base(a)); \
        case 237: return vrev64q_##base(vuzp2q_##base(vzip2q_##base(a, a), a)); \
        case 238: return vextq_##base(vrev64q_##base(a), vrev128q_##base(a), 2); \
        case 239: return vzip2q_##base(vdupq_laneq_##base(a, 3), a); \
        case 240: return vextq_##base(vdupq_laneq_##base(a, 3), vdupq_laneq_##base(a, 0), 2); \
        case 241: return vextq_##base(vdupq_laneq_##base(a, 3), a, 2); \
        case 242: return vuzp1q_##base(vdupq_laneq_##base(a, 3), a); \
        case 243: return vcopyq_laneq_##base(vdupq_laneq_##base(a, 3), 2, a, 0); \
        case 244: return vcopyq_laneq_##base(vrev128q_##base(a), 1, a, 3); \
        case 245: return vextq_##base(vtrn2q_##base(a, a), vtrn2q_##base(a, a), 2); \
        case 246: return vcopyq_laneq_##base(vextq_##base(a, a, 3), 1, a, 3); \
        case 247: return vuzp2q_##base(vdupq_laneq_##base(a, 3), a); \
        case 248: return vzip2q_##base(vrev64q_##base(a), vextq_##base(a, a, 1)); \
        case 249: return vextq_##base(a, vrev128q_##base(a), 3); \
        case 250: return vzip1q_##base(vrev128q_##base(a), vrev128q_##base(a)); \
        case 251: return vzip1q_##base(vrev128q_##base(a), vdupq_laneq_##base(a, 3)); \
        case 252: return vextq_##base(vdupq_laneq_##base(a, 3), a, 1); \
        case 253: return vtrn1q_##base(vdupq_laneq_##base(a, 3), vrev128q_##base(a)); \
        case 254: return vzip1q_##base(vdupq_laneq_##base(a, 3), vrev128q_##base(a)); \
        case 255: return vdupq_laneq_##base(a, 3); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 < 8) && (v1 < 8) && (v2 < 8) && (v3 < 8) && (v4 < 8) && (v5 < 8) && (v6 < 8) && (v7 < 8), "Indexes must not exceed lane count"); \
    \
    return CCSimdSwizzle_u8x16(CC_SIMD_NAME(CCSimd_u8x16_Reinterpret, base, count)(a), v0 * 2, (v0 * 2) + 1, v1 * 2, (v1 * 2) + 1, v2 * 2, (v2 * 2) + 1, v3 * 2, (v3 * 2) + 1, v4 * 2, (v4 * 2) + 1, v5 * 2, (v5 * 2) + 1, v6 * 2, (v6 * 2) + 1, v7 * 2, (v7 * 2) + 1); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15) \
{ \
    CCAssertLog((v0 < 16) && (v1 < 16) && (v2 < 16) && (v3 < 16) && (v4 < 16) && (v5 < 16) && (v6 < 16) && (v7 < 16) && (v8 < 16) && (v9 < 16) && (v10 < 16) && (v11 < 16) && (v12 < 16) && (v13 < 16) && (v14 < 16) && (v15 < 16), "Indexes must not exceed lane count"); \
    \
    return vqtbl1q_##base(a, CC_SIMD_NAME(CCSimdLoad, base, count)((CC_SIMD_BASE_TYPE(base)[16]){ v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15 })); \
}
CC_SIMD_DECL(CCSimdSwizzle, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 1) | v1) \
    { \
        case 0: return a; \
        case 1: return vcopyq_laneq_##base(a, 1, b, 1); \
        case 2: return vcopyq_laneq_##base(a, 0, b, 0); \
        case 3: return b; \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_2_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 3) | (v1 << 2) | (v2 << 1) | v3) \
    { \
        case 0: return a; \
        case 1: return vcopyq_laneq_##base(a, 3, b, 3); \
        case 2: return vcopyq_laneq_##base(a, 2, b, 2); \
        case 3: return vreinterpretq_##base##_##kind##64(CC_SIMD_NAME(CCSimdInterleave, kind##64, 2)(vreinterpretq_##kind##64_##base(a), vreinterpretq_##kind##64_##base(b), 0, 1)); \
        case 4: return vcopyq_laneq_##base(a, 1, b, 1); \
        case 5: return vtrn2q_##base(vrev64q_##base(a), b); \
        case 6: return vcopyq_laneq_##base(vcopyq_laneq_##base(b, 0, a, 0), 3, a, 3); \
        case 7: return vcopyq_laneq_##base(b, 0, a, 0); \
        case 8: return vcopyq_laneq_##base(a, 0, b, 0); \
        case 9: return vcopyq_laneq_##base(vcopyq_laneq_##base(a, 0, b, 0), 3, b, 3); \
        case 10: return vtrn2q_##base(vrev64q_##base(b), a); \
        case 11: return vcopyq_laneq_##base(b, 1, a, 1); \
        case 12: return vreinterpretq_##base##_##kind##64(CC_SIMD_NAME(CCSimdInterleave, kind##64, 2)(vreinterpretq_##kind##64_##base(a), vreinterpretq_##kind##64_##base(b), 1, 0)); \
        case 13: return vcopyq_laneq_##base(b, 2, a, 2); \
        case 14: return vcopyq_laneq_##base(b, 3, a, 3); \
        case 15: return b; \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2) && (v4 < 2) && (v5 < 2) && (v6 < 2) && (v7 < 2), "Indexes must not exceed arg count"); \
    \
    switch ((v0 << 7) | (v1 << 6) | (v2 << 5) | (v3 << 4) | (v4 << 3) | (v5 << 2) | (v6 << 1) | v7) \
    { \
        case 0: return a; \
        case 1: return vcopyq_laneq_##base(a, 7, b, 7); \
        case 2: return vcopyq_laneq_##base(a, 6, b, 6); \
        case 4: return vcopyq_laneq_##base(a, 5, b, 5); \
        case 8: return vcopyq_laneq_##base(a, 4, b, 4); \
        case 16: return vcopyq_laneq_##base(a, 3, b, 3); \
        case 32: return vcopyq_laneq_##base(a, 2, b, 2); \
        case 64: return vcopyq_laneq_##base(a, 1, b, 1); \
        case 128: return vcopyq_laneq_##base(a, 0, b, 0); \
        case 255: return b; \
            \
        case 3: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 0, 0, 1)); \
        case 12: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 0, 1, 0)); \
        case 15: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 0, 1, 1)); \
        case 48: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 1, 0, 0)); \
        case 51: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 1, 0, 1)); \
        case 60: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 1, 1, 0)); \
        case 63: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 0, 1, 1, 1)); \
        case 192: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 0, 0, 0)); \
        case 195: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 0, 0, 1)); \
        case 204: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 0, 1, 0)); \
        case 207: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 0, 1, 1)); \
        case 240: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 1, 0, 0)); \
        case 243: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 1, 0, 1)); \
        case 252: return vreinterpretq_##base##_##kind##32(CC_SIMD_NAME(CCSimdInterleave, kind##32, 4)(vreinterpretq_##kind##32_##base(a), vreinterpretq_##kind##32_##base(b), 1, 1, 1, 0)); \
    } \
    \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = vcopyq_laneq_##base(Result, 0, b, 0); \
    if (v1) Result = vcopyq_laneq_##base(Result, 1, b, 1); \
    if (v2) Result = vcopyq_laneq_##base(Result, 2, b, 2); \
    if (v3) Result = vcopyq_laneq_##base(Result, 3, b, 3); \
    if (v4) Result = vcopyq_laneq_##base(Result, 4, b, 4); \
    if (v5) Result = vcopyq_laneq_##base(Result, 5, b, 5); \
    if (v6) Result = vcopyq_laneq_##base(Result, 6, b, 6); \
    if (v7) Result = vcopyq_laneq_##base(Result, 7, b, 7); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15) \
{ \
    CCAssertLog((v0 < 2) && (v1 < 2) && (v2 < 2) && (v3 < 2) && (v4 < 2) && (v5 < 2) && (v6 < 2) && (v7 < 2) && (v8 < 2) && (v9 < 2) && (v10 < 2) && (v11 < 2) && (v12 < 2) && (v13 < 2) && (v14 < 2) && (v15 < 2), "Indexes must not exceed arg count"); \
    \
    switch (((uint16_t)v0 << 15) | ((uint16_t)v1 << 14) | ((uint16_t)v2 << 13) | ((uint16_t)v3 << 12) | ((uint16_t)v4 << 11) | ((uint16_t)v5 << 10) | ((uint16_t)v6 << 9) | ((uint16_t)v7 << 8) | ((uint16_t)v8 << 7) | ((uint16_t)v9 << 6) | ((uint16_t)v10 << 5) | ((uint16_t)v11 << 4) | ((uint16_t)v12 << 3) | ((uint16_t)v13 << 2) | ((uint16_t)v14 << 1) | (uint16_t)v15) \
    { \
        case 0: return a; \
        case 1: return vcopyq_laneq_##base(a, 15, b, 15); \
        case 2: return vcopyq_laneq_##base(a, 14, b, 14); \
        case 4: return vcopyq_laneq_##base(a, 13, b, 13); \
        case 8: return vcopyq_laneq_##base(a, 12, b, 12); \
        case 16: return vcopyq_laneq_##base(a, 11, b, 11); \
        case 32: return vcopyq_laneq_##base(a, 10, b, 10); \
        case 64: return vcopyq_laneq_##base(a, 9, b, 9); \
        case 128: return vcopyq_laneq_##base(a, 8, b, 8); \
        case 256: return vcopyq_laneq_##base(a, 7, b, 7); \
        case 512: return vcopyq_laneq_##base(a, 6, b, 6); \
        case 1024: return vcopyq_laneq_##base(a, 5, b, 5); \
        case 2048: return vcopyq_laneq_##base(a, 4, b, 4); \
        case 4096: return vcopyq_laneq_##base(a, 3, b, 3); \
        case 8192: return vcopyq_laneq_##base(a, 2, b, 2); \
        case 16384: return vcopyq_laneq_##base(a, 1, b, 1); \
        case 32768: return vcopyq_laneq_##base(a, 0, b, 0); \
        case 65535: return b; \
            \
        case 3: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 0, 0, 1)); \
        case 12: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 0, 1, 0)); \
        case 15: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 0, 1, 1)); \
        case 48: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 1, 0, 0)); \
        case 51: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 1, 0, 1)); \
        case 60: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 1, 1, 0)); \
        case 63: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 0, 1, 1, 1)); \
        case 192: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 0, 0, 0)); \
        case 195: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 0, 0, 1)); \
        case 204: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 0, 1, 0)); \
        case 207: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 0, 1, 1)); \
        case 240: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 1, 0, 0)); \
        case 243: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 1, 0, 1)); \
        case 252: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 1, 1, 0)); \
        case 255: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 0, 1, 1, 1, 1)); \
        case 768: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 0, 0, 0)); \
        case 771: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 0, 0, 1)); \
        case 780: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 0, 1, 0)); \
        case 783: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 0, 1, 1)); \
        case 816: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 1, 0, 0)); \
        case 819: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 1, 0, 1)); \
        case 828: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 1, 1, 0)); \
        case 831: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 0, 1, 1, 1)); \
        case 960: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 0, 0, 0)); \
        case 963: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 0, 0, 1)); \
        case 972: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 0, 1, 0)); \
        case 975: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 0, 1, 1)); \
        case 1008: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 1, 0, 0)); \
        case 1011: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 1, 0, 1)); \
        case 1020: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 1, 1, 0)); \
        case 1023: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 0, 1, 1, 1, 1, 1)); \
        case 3072: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 0, 0, 0)); \
        case 3075: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 0, 0, 1)); \
        case 3084: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 0, 1, 0)); \
        case 3087: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 0, 1, 1)); \
        case 3120: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 1, 0, 0)); \
        case 3123: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 1, 0, 1)); \
        case 3132: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 1, 1, 0)); \
        case 3135: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 0, 1, 1, 1)); \
        case 3264: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 0, 0, 0)); \
        case 3267: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 0, 0, 1)); \
        case 3276: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 0, 1, 0)); \
        case 3279: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 0, 1, 1)); \
        case 3312: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 1, 0, 0)); \
        case 3315: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 1, 0, 1)); \
        case 3324: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 1, 1, 0)); \
        case 3327: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 0, 1, 1, 1, 1)); \
        case 3840: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 0, 0, 0)); \
        case 3843: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 0, 0, 1)); \
        case 3852: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 0, 1, 0)); \
        case 3855: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 0, 1, 1)); \
        case 3888: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 1, 0, 0)); \
        case 3891: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 1, 0, 1)); \
        case 3900: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 1, 1, 0)); \
        case 3903: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 0, 1, 1, 1)); \
        case 4032: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 0, 0, 0)); \
        case 4035: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 0, 0, 1)); \
        case 4044: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 0, 1, 0)); \
        case 4047: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 0, 1, 1)); \
        case 4080: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 1, 0, 0)); \
        case 4083: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 1, 0, 1)); \
        case 4092: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 1, 1, 0)); \
        case 4095: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 0, 1, 1, 1, 1, 1, 1)); \
        case 12288: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 0, 0, 0)); \
        case 12291: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 0, 0, 1)); \
        case 12300: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 0, 1, 0)); \
        case 12303: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 0, 1, 1)); \
        case 12336: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 1, 0, 0)); \
        case 12339: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 1, 0, 1)); \
        case 12348: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 1, 1, 0)); \
        case 12351: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 0, 1, 1, 1)); \
        case 12480: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 0, 0, 0)); \
        case 12483: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 0, 0, 1)); \
        case 12492: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 0, 1, 0)); \
        case 12495: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 0, 1, 1)); \
        case 12528: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 1, 0, 0)); \
        case 12531: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 1, 0, 1)); \
        case 12540: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 1, 1, 0)); \
        case 12543: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 0, 1, 1, 1, 1)); \
        case 13056: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 0, 0, 0)); \
        case 13059: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 0, 0, 1)); \
        case 13068: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 0, 1, 0)); \
        case 13071: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 0, 1, 1)); \
        case 13104: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 1, 0, 0)); \
        case 13107: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 1, 0, 1)); \
        case 13116: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 1, 1, 0)); \
        case 13119: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 0, 1, 1, 1)); \
        case 13248: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 0, 0, 0)); \
        case 13251: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 0, 0, 1)); \
        case 13260: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 0, 1, 0)); \
        case 13263: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 0, 1, 1)); \
        case 13296: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 1, 0, 0)); \
        case 13299: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 1, 0, 1)); \
        case 13308: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 1, 1, 0)); \
        case 13311: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 0, 1, 1, 1, 1, 1)); \
        case 15360: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 0, 0, 0)); \
        case 15363: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 0, 0, 1)); \
        case 15372: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 0, 1, 0)); \
        case 15375: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 0, 1, 1)); \
        case 15408: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 1, 0, 0)); \
        case 15411: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 1, 0, 1)); \
        case 15420: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 1, 1, 0)); \
        case 15423: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 0, 1, 1, 1)); \
        case 15552: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 0, 0, 0)); \
        case 15555: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 0, 0, 1)); \
        case 15564: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 0, 1, 0)); \
        case 15567: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 0, 1, 1)); \
        case 15600: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 1, 0, 0)); \
        case 15603: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 1, 0, 1)); \
        case 15612: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 1, 1, 0)); \
        case 15615: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 0, 1, 1, 1, 1)); \
        case 16128: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 0, 0, 0)); \
        case 16131: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 0, 0, 1)); \
        case 16140: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 0, 1, 0)); \
        case 16143: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 0, 1, 1)); \
        case 16176: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 1, 0, 0)); \
        case 16179: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 1, 0, 1)); \
        case 16188: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 1, 1, 0)); \
        case 16191: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 0, 1, 1, 1)); \
        case 16320: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 0, 0, 0)); \
        case 16323: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 0, 0, 1)); \
        case 16332: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 0, 1, 0)); \
        case 16335: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 0, 1, 1)); \
        case 16368: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 1, 0, 0)); \
        case 16371: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 1, 0, 1)); \
        case 16380: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 1, 1, 0)); \
        case 16383: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 0, 1, 1, 1, 1, 1, 1, 1)); \
        case 49152: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 0, 0, 0)); \
        case 49155: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 0, 0, 1)); \
        case 49164: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 0, 1, 0)); \
        case 49167: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 0, 1, 1)); \
        case 49200: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 1, 0, 0)); \
        case 49203: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 1, 0, 1)); \
        case 49212: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 1, 1, 0)); \
        case 49215: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 0, 1, 1, 1)); \
        case 49344: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 0, 0, 0)); \
        case 49347: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 0, 0, 1)); \
        case 49356: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 0, 1, 0)); \
        case 49359: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 0, 1, 1)); \
        case 49392: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 1, 0, 0)); \
        case 49395: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 1, 0, 1)); \
        case 49404: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 1, 1, 0)); \
        case 49407: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 0, 1, 1, 1, 1)); \
        case 49920: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 0, 0, 0)); \
        case 49923: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 0, 0, 1)); \
        case 49932: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 0, 1, 0)); \
        case 49935: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 0, 1, 1)); \
        case 49968: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 1, 0, 0)); \
        case 49971: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 1, 0, 1)); \
        case 49980: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 1, 1, 0)); \
        case 49983: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 0, 1, 1, 1)); \
        case 50112: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 0, 0, 0)); \
        case 50115: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 0, 0, 1)); \
        case 50124: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 0, 1, 0)); \
        case 50127: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 0, 1, 1)); \
        case 50160: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 1, 0, 0)); \
        case 50163: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 1, 0, 1)); \
        case 50172: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 1, 1, 0)); \
        case 50175: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 0, 1, 1, 1, 1, 1)); \
        case 52224: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 0, 0, 0)); \
        case 52227: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 0, 0, 1)); \
        case 52236: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 0, 1, 0)); \
        case 52239: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 0, 1, 1)); \
        case 52272: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 1, 0, 0)); \
        case 52275: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 1, 0, 1)); \
        case 52284: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 1, 1, 0)); \
        case 52287: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 0, 1, 1, 1)); \
        case 52416: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 0, 0, 0)); \
        case 52419: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 0, 0, 1)); \
        case 52428: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 0, 1, 0)); \
        case 52431: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 0, 1, 1)); \
        case 52464: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 1, 0, 0)); \
        case 52467: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 1, 0, 1)); \
        case 52476: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 1, 1, 0)); \
        case 52479: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 0, 1, 1, 1, 1)); \
        case 52992: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 0, 0, 0)); \
        case 52995: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 0, 0, 1)); \
        case 53004: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 0, 1, 0)); \
        case 53007: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 0, 1, 1)); \
        case 53040: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 1, 0, 0)); \
        case 53043: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 1, 0, 1)); \
        case 53052: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 1, 1, 0)); \
        case 53055: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 0, 1, 1, 1)); \
        case 53184: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 0, 0, 0)); \
        case 53187: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 0, 0, 1)); \
        case 53196: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 0, 1, 0)); \
        case 53199: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 0, 1, 1)); \
        case 53232: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 1, 0, 0)); \
        case 53235: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 1, 0, 1)); \
        case 53244: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 1, 1, 0)); \
        case 53247: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 0, 1, 1, 1, 1, 1, 1)); \
        case 61440: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 0, 0, 0)); \
        case 61443: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 0, 0, 1)); \
        case 61452: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 0, 1, 0)); \
        case 61455: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 0, 1, 1)); \
        case 61488: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 1, 0, 0)); \
        case 61491: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 1, 0, 1)); \
        case 61500: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 1, 1, 0)); \
        case 61503: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 0, 1, 1, 1)); \
        case 61632: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 0, 0, 0)); \
        case 61635: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 0, 0, 1)); \
        case 61644: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 0, 1, 0)); \
        case 61647: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 0, 1, 1)); \
        case 61680: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 1, 0, 0)); \
        case 61683: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 1, 0, 1)); \
        case 61692: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 1, 1, 0)); \
        case 61695: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 0, 1, 1, 1, 1)); \
        case 62208: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 0, 0, 0)); \
        case 62211: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 0, 0, 1)); \
        case 62220: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 0, 1, 0)); \
        case 62223: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 0, 1, 1)); \
        case 62256: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 1, 0, 0)); \
        case 62259: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 1, 0, 1)); \
        case 62268: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 1, 1, 0)); \
        case 62271: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 0, 1, 1, 1)); \
        case 62400: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 0, 0, 0)); \
        case 62403: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 0, 0, 1)); \
        case 62412: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 0, 1, 0)); \
        case 62415: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 0, 1, 1)); \
        case 62448: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 1, 0, 0)); \
        case 62451: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 1, 0, 1)); \
        case 62460: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 1, 1, 0)); \
        case 62463: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 0, 1, 1, 1, 1, 1)); \
        case 64512: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 0, 0, 0)); \
        case 64515: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 0, 0, 1)); \
        case 64524: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 0, 1, 0)); \
        case 64527: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 0, 1, 1)); \
        case 64560: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 1, 0, 0)); \
        case 64563: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 1, 0, 1)); \
        case 64572: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 1, 1, 0)); \
        case 64575: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 0, 1, 1, 1)); \
        case 64704: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 0, 0, 0)); \
        case 64707: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 0, 0, 1)); \
        case 64716: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 0, 1, 0)); \
        case 64719: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 0, 1, 1)); \
        case 64752: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 1, 0, 0)); \
        case 64755: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 1, 0, 1)); \
        case 64764: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 1, 1, 0)); \
        case 64767: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 0, 1, 1, 1, 1)); \
        case 65280: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 0, 0, 0)); \
        case 65283: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 0, 0, 1)); \
        case 65292: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 0, 1, 0)); \
        case 65295: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 0, 1, 1)); \
        case 65328: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 1, 0, 0)); \
        case 65331: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 1, 0, 1)); \
        case 65340: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 1, 1, 0)); \
        case 65343: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 0, 1, 1, 1)); \
        case 65472: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 0, 0, 0)); \
        case 65475: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 0, 0, 1)); \
        case 65484: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 0, 1, 0)); \
        case 65487: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 0, 1, 1)); \
        case 65520: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 1, 0, 0)); \
        case 65523: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 1, 0, 1)); \
        case 65532: return vreinterpretq_##base##_##kind##16(CC_SIMD_NAME(CCSimdInterleave, kind##16, 8)(vreinterpretq_##kind##16_##base(a), vreinterpretq_##kind##16_##base(b), 1, 1, 1, 1, 1, 1, 1, 0)); \
    } \
    \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = vcopyq_laneq_##base(Result, 0, b, 0); \
    if (v1) Result = vcopyq_laneq_##base(Result, 1, b, 1); \
    if (v2) Result = vcopyq_laneq_##base(Result, 2, b, 2); \
    if (v3) Result = vcopyq_laneq_##base(Result, 3, b, 3); \
    if (v4) Result = vcopyq_laneq_##base(Result, 4, b, 4); \
    if (v5) Result = vcopyq_laneq_##base(Result, 5, b, 5); \
    if (v6) Result = vcopyq_laneq_##base(Result, 6, b, 6); \
    if (v7) Result = vcopyq_laneq_##base(Result, 7, b, 7); \
    if (v8) Result = vcopyq_laneq_##base(Result, 8, b, 8); \
    if (v9) Result = vcopyq_laneq_##base(Result, 9, b, 9); \
    if (v10) Result = vcopyq_laneq_##base(Result, 10, b, 10); \
    if (v11) Result = vcopyq_laneq_##base(Result, 11, b, 11); \
    if (v12) Result = vcopyq_laneq_##base(Result, 12, b, 12); \
    if (v13) Result = vcopyq_laneq_##base(Result, 13, b, 13); \
    if (v14) Result = vcopyq_laneq_##base(Result, 14, b, 14); \
    if (v15) Result = vcopyq_laneq_##base(Result, 15, b, 15); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdInterleave, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_MERGE_MASK(x0, x1) ((x0) << 5) | (x1)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog(((v0 & 0xf) < 2) && ((v1 & 0xf) < 2), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1) & ~0x11), "Indexes must only reference either a or b"); \
    \
    switch (CC_SIMD_MERGE_MASK(v0, v1)) \
    { \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0): return vzip1q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1): return vzip2q_##base(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0): return vextq_##base(a, b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1): return vzip2q_##base(a, b); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0): return vzip1q_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1): return vzip2q_##base(CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, 0, 0), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0): return vextq_##base(b, a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1): return vzip2q_##base(b, a); \
    } \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 1, v1 & 1), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 1, v1 & 1), v0 >> 4, v1 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_2_ELEMENT_TYPES)
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
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B3): return vreinterpretq_##base##_##kind##64(vzip2q_s64(vreinterpretq_##kind##64_##base(a), vreinterpretq_##kind##64_##base(b))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A3): return vreinterpretq_##base##_##kind##64(vzip2q_s64(vreinterpretq_##kind##64_##base(b), vreinterpretq_##kind##64_##base(a))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_A1): return vreinterpretq_##base##_##kind##64(vzip1q_s64(vreinterpretq_##kind##64_##base(b), vreinterpretq_##kind##64_##base(a))); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_B1): return vreinterpretq_##base##_##kind##64(vzip1q_s64(vreinterpretq_##kind##64_##base(a), vreinterpretq_##kind##64_##base(b))); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B1): return vzip1q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A1): return vzip1q_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B3): return vzip2q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A3): return vzip2q_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B2): return vuzp1q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A2): return vuzp1q_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B3): return vuzp2q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A3): return vuzp2q_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B2): return vtrn1q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A2): return vtrn1q_##base(b, a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B3): return vtrn2q_##base(a, b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A3): return vtrn2q_##base(b, a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B0): return vextq_##base(a, b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A0): return vextq_##base(b, a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B1): return vextq_##base(a, b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A1): return vextq_##base(b, a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vextq_##base(a, b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vextq_##base(b, a, 3); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A0): return vrev128q_##base(vzip1q_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B0): return vrev128q_##base(vzip1q_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A2): return vrev128q_##base(vzip2q_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B2): return vrev128q_##base(vzip2q_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_A0): return vrev128q_##base(vuzp1q_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_B0): return vrev128q_##base(vuzp1q_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_A1): return vrev128q_##base(vuzp2q_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_B1): return vrev128q_##base(vuzp2q_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A0): return vrev128q_##base(vtrn1q_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B0): return vrev128q_##base(vtrn1q_##base(b, a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A1): return vrev128q_##base(vtrn2q_##base(a, b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B1): return vrev128q_##base(vtrn2q_##base(b, a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vrev128q_##base(vextq_##base(a, b, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3): return vrev64q_##base(vextq_##base(a, b, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vrev128q_##base(vextq_##base(b, a, 1)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3): return vrev64q_##base(vextq_##base(b, a, 1)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_A2): return vrev128q_##base(vextq_##base(a, b, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B0): return vrev64q_##base(vextq_##base(a, b, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_B2): return vrev128q_##base(vextq_##base(b, a, 2)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A0): return vrev64q_##base(vextq_##base(b, a, 2)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A3): return vrev128q_##base(vextq_##base(a, b, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B1): return vrev64q_##base(vextq_##base(a, b, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B3): return vrev128q_##base(vextq_##base(b, a, 3)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A1): return vrev64q_##base(vextq_##base(b, a, 3)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B1): return vzip1q_##base(vrev128q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B1): return vzip1q_##base(vrev64q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B2): return vzip1q_##base(a, vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B0): return vzip1q_##base(a, vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B2): return vzip1q_##base(vrev64q_##base(a), vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B0): return vzip1q_##base(vrev128q_##base(a), vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A2): return vzip1q_##base(b, vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A0): return vzip1q_##base(b, vrev64q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A1): return vzip1q_##base(vrev128q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A1): return vzip1q_##base(vrev64q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A2): return vzip1q_##base(vrev64q_##base(b), vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A0): return vzip1q_##base(vrev128q_##base(b), vrev64q_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B3): return vzip2q_##base(vrev128q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B3): return vzip2q_##base(vrev64q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B0): return vzip2q_##base(a, vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B2): return vzip2q_##base(a, vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A0): return vzip2q_##base(b, vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A2): return vzip2q_##base(b, vrev64q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A3): return vzip2q_##base(vrev128q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A3): return vzip2q_##base(vrev64q_##base(b), a); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_B2): return vuzp1q_##base(vrev128q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_B2): return vuzp1q_##base(vrev64q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B1): return vuzp1q_##base(a, vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B3): return vuzp1q_##base(a, vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B1): return vuzp1q_##base(vrev64q_##base(a), vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_B3): return vuzp1q_##base(vrev128q_##base(a), vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A1): return vuzp1q_##base(b, vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A3): return vuzp1q_##base(b, vrev64q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_A2): return vuzp1q_##base(vrev128q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_A2): return vuzp1q_##base(vrev64q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A1): return vuzp1q_##base(vrev64q_##base(b), vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_A3): return vuzp1q_##base(vrev128q_##base(b), vrev64q_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B3): return vuzp2q_##base(vrev128q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_B0): return vuzp2q_##base(a, vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_B0): return vuzp2q_##base(vrev64q_##base(a), vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B2): return vuzp2q_##base(vrev128q_##base(a), vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_A0): return vuzp2q_##base(b, vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A3): return vuzp2q_##base(vrev128q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_A0): return vuzp2q_##base(vrev64q_##base(b), vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A2): return vuzp2q_##base(vrev128q_##base(b), vrev64q_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B2): return vtrn1q_##base(vrev128q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2): return vtrn1q_##base(vrev64q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2, CC_SIMD_B1): return vtrn1q_##base(a, vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B3): return vtrn1q_##base(a, vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_B1): return vtrn1q_##base(vrev64q_##base(a), vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_A1, CC_SIMD_B3): return vtrn1q_##base(vrev128q_##base(a), vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A3, CC_SIMD_B2, CC_SIMD_A1): return vtrn1q_##base(b, vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A3): return vtrn1q_##base(b, vrev64q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_A2): return vtrn1q_##base(vrev128q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3, CC_SIMD_A2): return vtrn1q_##base(vrev64q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_A1): return vtrn1q_##base(vrev64q_##base(b), vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_B1, CC_SIMD_A3): return vtrn1q_##base(vrev128q_##base(b), vrev64q_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_A0, CC_SIMD_B3): return vtrn2q_##base(vrev128q_##base(a), b); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_B0): return vtrn2q_##base(a, vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B2, CC_SIMD_A2, CC_SIMD_B0): return vtrn2q_##base(vrev64q_##base(a), vrev128q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_B2): return vtrn2q_##base(vrev128q_##base(a), vrev64q_##base(b)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_A0): return vtrn2q_##base(b, vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_B0, CC_SIMD_A3): return vtrn2q_##base(vrev128q_##base(b), a); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A2, CC_SIMD_B2, CC_SIMD_A0): return vtrn2q_##base(vrev64q_##base(b), vrev128q_##base(a)); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_A2): return vtrn2q_##base(vrev128q_##base(b), vrev64q_##base(a)); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B0): return vextq_##base(vrev128q_##base(a), b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B0): return vextq_##base(vrev64q_##base(a), b, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B3): return vextq_##base(a, vrev128q_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B1): return vextq_##base(a, vrev64q_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B3): return vextq_##base(vrev64q_##base(a), vrev128q_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B1): return vextq_##base(vrev128q_##base(a), vrev64q_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B1): return vextq_##base(vrev64q_##base(a), vrev64q_##base(b), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A3): return vextq_##base(b, vrev128q_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A1): return vextq_##base(b, vrev64q_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A0): return vextq_##base(vrev128q_##base(b), a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A0): return vextq_##base(vrev64q_##base(b), a, 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A3): return vextq_##base(vrev64q_##base(b), vrev128q_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A1): return vextq_##base(vrev128q_##base(b), vrev64q_##base(a), 1); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A1): return vextq_##base(vrev64q_##base(b), vrev64q_##base(a), 1); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1): return vextq_##base(vrev128q_##base(a), b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B1): return vextq_##base(vrev64q_##base(a), b, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B2): return vextq_##base(a, vrev128q_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B0): return vextq_##base(a, vrev64q_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B2): return vextq_##base(vrev64q_##base(a), vrev128q_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B0): return vextq_##base(vrev128q_##base(a), vrev64q_##base(b), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A2): return vextq_##base(b, vrev128q_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A0): return vextq_##base(b, vrev64q_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A1): return vextq_##base(vrev128q_##base(b), a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A1): return vextq_##base(vrev64q_##base(b), a, 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A2): return vextq_##base(vrev64q_##base(b), vrev128q_##base(a), 2); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A0): return vextq_##base(vrev128q_##base(b), vrev64q_##base(a), 2); \
            \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vextq_##base(vrev128q_##base(a), b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2): return vextq_##base(vrev64q_##base(a), b, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vextq_##base(a, vrev128q_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A3, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vextq_##base(a, vrev64q_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B3, CC_SIMD_B2, CC_SIMD_B1): return vextq_##base(vrev64q_##base(a), vrev128q_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A0, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vextq_##base(vrev128q_##base(a), vrev64q_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_A2, CC_SIMD_B1, CC_SIMD_B0, CC_SIMD_B3): return vextq_##base(vrev64q_##base(a), vrev64q_##base(b), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vextq_##base(b, vrev128q_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B3, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vextq_##base(b, vrev64q_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vextq_##base(vrev128q_##base(b), a, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A0, CC_SIMD_A1, CC_SIMD_A2): return vextq_##base(vrev64q_##base(b), a, 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A3, CC_SIMD_A2, CC_SIMD_A1): return vextq_##base(vrev64q_##base(b), vrev128q_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B0, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vextq_##base(vrev128q_##base(b), vrev64q_##base(a), 3); \
        case CC_SIMD_MERGE_MASK(CC_SIMD_B2, CC_SIMD_A1, CC_SIMD_A0, CC_SIMD_A3): return vextq_##base(vrev64q_##base(b), vrev64q_##base(a), 3); \
    } \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 3, v1 & 3, v2 & 3, v3 & 3), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 3, v1 & 3, v2 & 3, v3 & 3), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_4_ELEMENT_TYPES)
#undef CC_SIMD_IMPL
#undef CC_SIMD_MERGE_MASK

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog(((v0 & 0xf) < 8) && ((v1 & 0xf) < 8) && ((v2 & 0xf) < 8) && ((v3 & 0xf) < 8) && ((v4 & 0xf) < 8) && ((v5 & 0xf) < 8) && ((v6 & 0xf) < 8) && ((v7 & 0xf) < 8), "Indexes must not exceed lane count"); \
    CCAssertLog(!((v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7) & ~0x17), "Indexes must only reference either a or b"); \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 7, v1 & 7, v2 & 7, v3 & 7, v4 & 7, v5 & 7, v6 & 7, v7 & 7), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 7, v1 & 7, v2 & 7, v3 & 7, v4 & 7, v5 & 7, v6 & 7, v7 & 7), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4, v4 >> 4, v5 >> 4, v6 >> 4, v7 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_8_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15) \
{ \
    CCAssertLog(!((v0 | v1 | v2 | v3 | v4 | v5 | v6 | v7 | v8 | v9 | v10 | v11 | v12 | v13 | v14 | v15) & ~0x1f), "Indexes must only reference either a or b"); \
    \
    return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, v0 & 15, v1 & 15, v2 & 15, v3 & 15, v4 & 15, v5 & 15, v6 & 15, v7 & 15, v8 & 15, v9 & 15, v10 & 15, v11 & 15, v12 & 15, v13 & 15, v14 & 15, v15 & 15), CC_SIMD_NAME(CCSimdSwizzle, base, count)(b, v0 & 15, v1 & 15, v2 & 15, v3 & 15, v4 & 15, v5 & 15, v6 & 15, v7 & 15, v8 & 15, v9 & 15, v10 & 15, v11 & 15, v12 & 15, v13 & 15, v14 & 15, v15 & 15), v0 >> 4, v1 >> 4, v2 >> 4, v3 >> 4, v4 >> 4, v5 >> 4, v6 >> 4, v7 >> 4, v8 >> 4, v9 >> 4, v10 >> 4, v11 >> 4, v12 >> 4, v13 >> 4, v14 >> 4, v15 >> 4); \
}
CC_SIMD_DECL(CCSimdMerge, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_128_16_ELEMENT_TYPES)
#undef CC_SIMD_IMPL

#endif
