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

#ifndef CC_SIMD_WIDTH
#error "CC_SIMD_WIDTH is not defined"
#endif

#define CC_SIMD_LANES_MAX (CC_SIMD_WIDTH / 8)

#define CC_SIMD_N_2_ELEMENT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _2_ELEMENT_TYPES)
#define CC_SIMD_N_4_ELEMENT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _4_ELEMENT_TYPES)
#define CC_SIMD_N_8_ELEMENT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _8_ELEMENT_TYPES)
#define CC_SIMD_N_16_ELEMENT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _16_ELEMENT_TYPES)
#define CC_SIMD_N_32_ELEMENT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _32_ELEMENT_TYPES)
#define CC_SIMD_N_64_ELEMENT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _64_ELEMENT_TYPES)

#define CC_SIMD_N_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _INTEGER_TYPES)
#define CC_SIMD_N_FLOAT_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _FLOAT_TYPES)

#define CC_SIMD_N_2_ELEMENT_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _2_ELEMENT_INTEGER_TYPES)
#define CC_SIMD_N_4_ELEMENT_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _4_ELEMENT_INTEGER_TYPES)
#define CC_SIMD_N_8_ELEMENT_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _8_ELEMENT_INTEGER_TYPES)
#define CC_SIMD_N_16_ELEMENT_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _16_ELEMENT_INTEGER_TYPES)
#define CC_SIMD_N_32_ELEMENT_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _32_ELEMENT_INTEGER_TYPES)
#define CC_SIMD_N_64_ELEMENT_INTEGER_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _64_ELEMENT_INTEGER_TYPES)

#if CC_SIMD_WIDTH >= 16
#define CC_SIMD_N_INTEGER_8_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _INTEGER_8_TYPES)
#if CC_SIMD_WIDTH >= 32
#define CC_SIMD_N_INTEGER_16_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _INTEGER_16_TYPES)
#if CC_SIMD_WIDTH >= 64
#define CC_SIMD_N_INTEGER_32_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _INTEGER_32_TYPES)
#if CC_SIMD_WIDTH >= 128
#define CC_SIMD_N_INTEGER_64_TYPES CC_CAT(CC_SIMD_, CC_SIMD_WIDTH, _INTEGER_64_TYPES)
#endif
#endif
#endif
#endif

#ifdef CC_SIMD_MISSING_CCSimdZero
#define CC_SIMD_IMPL(base, count, kind) (void){ return CC_SIMD_NAME(CCSimdFill, base, count)(0); }
CC_SIMD_DECL(CCSimdZero, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdZero)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdSetSequence
#if CC_SIMD_LANES_MAX >= 2
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1) \
{ \
    switch ((v1 << 1) | v0) \
    { \
        case 0: return a; \
        case 1: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 0, v); \
        case 2: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 1, v); \
        case 3: return CC_SIMD_NAME(CCSimdFill, base, count)(v); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 4
// FIXME: some interleaves are causing gpr use
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3) \
{ \
    switch ((v3 << 3) | (v2 << 2) | (v1 << 1) | v0) \
    { \
        case 0: return a; \
        case 1: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 0, v); \
        case 2: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 1, v); \
        case 3: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 1, 0, 0); \
        case 4: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 2, v); \
        case 5: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 0, 1, 0); \
        case 6: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 1, 1, 0); \
        case 7: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 1, 1, 0); \
        case 8: return CC_SIMD_NAME(CCSimdSet, base, count)(a, 3, v); \
        case 9: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 0, 0, 1); \
        case 10: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 1, 0, 1); \
        case 11: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 1, 0, 1); \
        case 12: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 0, 1, 1); \
        case 13: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 1, 0, 1, 1); \
        case 14: return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(v), 0, 1, 1, 1); \
        case 15: return CC_SIMD_NAME(CCSimdFill, base, count)(v); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 8
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 0, v); \
    if (v1) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 1, v); \
    if (v2) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 2, v); \
    if (v3) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 3, v); \
    if (v4) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 4, v); \
    if (v5) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 5, v); \
    if (v6) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 6, v); \
    if (v7) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 7, v); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 16
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7, _Bool v8, _Bool v9, _Bool v10, _Bool v11, _Bool v12, _Bool v13, _Bool v14, _Bool v15) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 0, v); \
    if (v1) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 1, v); \
    if (v2) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 2, v); \
    if (v3) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 3, v); \
    if (v4) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 4, v); \
    if (v5) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 5, v); \
    if (v6) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 6, v); \
    if (v7) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 7, v); \
    if (v8) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 8, v); \
    if (v9) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 9, v); \
    if (v10) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 10, v); \
    if (v11) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 11, v); \
    if (v12) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 12, v); \
    if (v13) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 13, v); \
    if (v14) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 14, v); \
    if (v15) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 15, v); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_16_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 32
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7, _Bool v8, _Bool v9, _Bool v10, _Bool v11, _Bool v12, _Bool v13, _Bool v14, _Bool v15, _Bool v16, _Bool v17, _Bool v18, _Bool v19, _Bool v20, _Bool v21, _Bool v22, _Bool v23, _Bool v24, _Bool v25, _Bool v26, _Bool v27, _Bool v28, _Bool v29, _Bool v30, _Bool v31) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 0, v); \
    if (v1) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 1, v); \
    if (v2) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 2, v); \
    if (v3) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 3, v); \
    if (v4) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 4, v); \
    if (v5) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 5, v); \
    if (v6) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 6, v); \
    if (v7) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 7, v); \
    if (v8) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 8, v); \
    if (v9) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 9, v); \
    if (v10) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 10, v); \
    if (v11) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 11, v); \
    if (v12) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 12, v); \
    if (v13) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 13, v); \
    if (v14) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 14, v); \
    if (v15) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 15, v); \
    if (v16) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 16, v); \
    if (v17) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 17, v); \
    if (v18) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 18, v); \
    if (v19) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 19, v); \
    if (v20) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 20, v); \
    if (v21) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 21, v); \
    if (v22) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 22, v); \
    if (v23) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 23, v); \
    if (v24) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 24, v); \
    if (v25) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 25, v); \
    if (v26) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 26, v); \
    if (v27) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 27, v); \
    if (v28) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 28, v); \
    if (v29) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 29, v); \
    if (v30) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 30, v); \
    if (v31) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 31, v); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_32_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 64
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, CC_SIMD_BASE_TYPE(base) v, _Bool v0, _Bool v1, _Bool v2, _Bool v3, _Bool v4, _Bool v5, _Bool v6, _Bool v7, _Bool v8, _Bool v9, _Bool v10, _Bool v11, _Bool v12, _Bool v13, _Bool v14, _Bool v15, _Bool v16, _Bool v17, _Bool v18, _Bool v19, _Bool v20, _Bool v21, _Bool v22, _Bool v23, _Bool v24, _Bool v25, _Bool v26, _Bool v27, _Bool v28, _Bool v29, _Bool v30, _Bool v31, _Bool v32, _Bool v33, _Bool v34, _Bool v35, _Bool v36, _Bool v37, _Bool v38, _Bool v39, _Bool v40, _Bool v41, _Bool v42, _Bool v43, _Bool v44, _Bool v45, _Bool v46, _Bool v47, _Bool v48, _Bool v49, _Bool v50, _Bool v51, _Bool v52, _Bool v53, _Bool v54, _Bool v55, _Bool v56, _Bool v57, _Bool v58, _Bool v59, _Bool v60, _Bool v61, _Bool v62, _Bool v63) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    if (v0) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 0, v); \
    if (v1) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 1, v); \
    if (v2) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 2, v); \
    if (v3) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 3, v); \
    if (v4) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 4, v); \
    if (v5) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 5, v); \
    if (v6) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 6, v); \
    if (v7) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 7, v); \
    if (v8) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 8, v); \
    if (v9) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 9, v); \
    if (v10) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 10, v); \
    if (v11) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 11, v); \
    if (v12) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 12, v); \
    if (v13) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 13, v); \
    if (v14) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 14, v); \
    if (v15) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 15, v); \
    if (v16) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 16, v); \
    if (v17) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 17, v); \
    if (v18) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 18, v); \
    if (v19) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 19, v); \
    if (v20) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 20, v); \
    if (v21) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 21, v); \
    if (v22) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 22, v); \
    if (v23) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 23, v); \
    if (v24) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 24, v); \
    if (v25) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 25, v); \
    if (v26) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 26, v); \
    if (v27) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 27, v); \
    if (v28) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 28, v); \
    if (v29) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 29, v); \
    if (v30) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 30, v); \
    if (v31) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 31, v); \
    if (v32) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 32, v); \
    if (v33) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 33, v); \
    if (v34) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 34, v); \
    if (v35) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 35, v); \
    if (v36) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 36, v); \
    if (v37) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 37, v); \
    if (v38) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 38, v); \
    if (v39) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 39, v); \
    if (v40) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 40, v); \
    if (v41) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 41, v); \
    if (v42) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 42, v); \
    if (v43) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 43, v); \
    if (v44) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 44, v); \
    if (v45) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 45, v); \
    if (v46) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 46, v); \
    if (v47) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 47, v); \
    if (v48) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 48, v); \
    if (v49) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 49, v); \
    if (v50) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 50, v); \
    if (v51) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 51, v); \
    if (v52) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 52, v); \
    if (v53) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 53, v); \
    if (v54) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 54, v); \
    if (v55) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 55, v); \
    if (v56) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 56, v); \
    if (v57) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 57, v); \
    if (v58) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 58, v); \
    if (v59) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 59, v); \
    if (v60) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 60, v); \
    if (v61) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 61, v); \
    if (v62) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 62, v); \
    if (v63) Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, 63, v); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdSetSequence, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_64_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdSetSequence))
#undef CC_SIMD_IMPL
#endif

#endif

#ifdef CC_SIMD_MISSING_CCSimdAndNot
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNot, base, count)(a), b); }
CC_SIMD_DECL(CCSimdAndNot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdAndNot)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateLeft
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    const CC_SIMD_TYPE(base, count) Mask = CC_SIMD_NAME(CCSimdFill, base, count)(CC_SIMD_BITS(base) - 1); \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftLeft, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(b, Mask)), CC_SIMD_NAME(CCSimdShiftRight, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(b), Mask))); \
}
CC_SIMD_DECL(CCSimdRotateLeft, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateLeft)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateLeftN
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    const uint8_t Mask = CC_SIMD_BITS(base) - 1; \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftLeftN, base, count)(a, n & Mask), CC_SIMD_NAME(CCSimdShiftRightN, base, count)(a, -n & Mask)); \
}
CC_SIMD_DECL(CCSimdRotateLeftN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateLeftN)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateRight
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    const CC_SIMD_TYPE(base, count) Mask = CC_SIMD_NAME(CCSimdFill, base, count)(CC_SIMD_BITS(base) - 1); \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftRight, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(b, Mask)), CC_SIMD_NAME(CCSimdShiftLeft, base, count)(a, CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(b), Mask))); \
}
CC_SIMD_DECL(CCSimdRotateRight, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateRight)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdRotateRightN
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const uint8_t n) \
{ \
    const uint8_t Mask = CC_SIMD_BITS(base) - 1; \
    \
    return CC_SIMD_NAME(CCSimdOr, base, count)(CC_SIMD_NAME(CCSimdShiftRightN, base, count)(a, n & Mask), CC_SIMD_NAME(CCSimdShiftLeftN, base, count)(a, -n & Mask)); \
}
CC_SIMD_DECL(CCSimdRotateRightN, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdRotateRightN)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdLowestUnset
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdNot, base, count)(a), CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdFill, base, count)(1))); }
CC_SIMD_DECL(CCSimdLowestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdLowestUnset)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdLowestSet
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a){ return CC_SIMD_NAME(CCSimdAnd, base, count)(a, CC_SIMD_NAME(CCSimdNeg, base, count)(a)); }
CC_SIMD_DECL(CCSimdLowestSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdLowestSet)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdHighestSet
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = CC_SIMD_NAME(CCSimdMask, base, count)(a); \
    \
    return CC_SIMD_NAME(CCSimdXor, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), _, CC_SIMD_NAME(Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), _, CC_SIMD_NAME(Reinterpret, base, count))(Result), 1))); \
}
CC_SIMD_DECL(CCSimdHighestSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdHighestSet)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdNextPow2
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) One = CC_SIMD_NAME(CCSimdFill, base, count)(1); \
    CC_SIMD_TYPE(base, count) Result = CC_SIMD_NAME(CCSimdSub, base, count)(a, One); \
    \
    Result = CC_SIMD_NAME(CCSimdMask, base, count)(Result); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(Result, One); \
}
CC_SIMD_DECL(CCSimdNextPow2, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdNextPow2)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMask
#ifdef CC_SIMD_N_INTEGER_64_TYPES
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 1)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 2)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 4)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 8)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 16)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 16)));  \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_64_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_N_INTEGER_32_TYPES
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 1)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 2)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 4)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 8)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 16)));  \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_32_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_N_INTEGER_16_TYPES
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 1)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 2)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 4)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 8)));  \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_16_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_N_INTEGER_8_TYPES
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 1)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 2)));  \
    Result = CC_SIMD_NAME(CCSimdOr, base, count)(Result, CC_CAT(CC_SIMD_NAME(CCSimd, base, count), CC_SIMD_NAME(_Reinterpret, CC_SIMD_UNSIGNED(base), count))(CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_UNSIGNED(base), count)(CC_CAT(CC_SIMD_NAME(CCSimd, CC_SIMD_UNSIGNED(base), count), CC_SIMD_NAME(_Reinterpret, base, count))(Result), 4)));  \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdMask, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_8_TYPES), CC_SIMD_MISSING_CCSimdMask))
#undef CC_SIMD_IMPL
#endif
#endif

#ifdef CC_SIMD_MISSING_CCSimdMaskLowerPow2
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) Mask = CC_SIMD_NAME(CCSimdMaskCompareNotEqual, base, count)(a, CC_SIMD_NAME(CCSimdZero, base, count)()); \
    const CC_SIMD_TYPE(base, count) Result = CC_SIMD_NAME(CCSimdNot, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(a)); \
    \
    return CC_SIMD_NAME(CCSimdAnd, base, count)(Mask, Result); \
}
CC_SIMD_DECL(CCSimdMaskLowerPow2, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMaskLowerPow2)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMaskHighestUnset
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    return CC_SIMD_NAME(CCSimdXor, base, count)(CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_MAX >> (64 - CC_SIMD_BITS(base))), CC_SIMD_NAME(CCSimdMask, base, count)(a)); \
}
CC_SIMD_DECL(CCSimdMaskHighestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMaskHighestUnset)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCountLowestUnset
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) AllZero = CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdCompareEqual, base, count)(a, CC_SIMD_NAME(CCSimdZero, base, count)()), CC_SIMD_NAME(CCSimdFill, base, count)(CC_SIMD_BITS(base))); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdCountSet, base, count)(CC_SIMD_NAME(CCSimdMaskLowerPow2, base, count)(CC_SIMD_NAME(CCSimdLowestSet, base, count)(a))), AllZero); \
}
CC_SIMD_DECL(CCSimdCountLowestUnset, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdCountLowestUnset)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCountSet
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a) \
{ \
    const CC_SIMD_TYPE(base, count) Mask55 = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x5555555555555555) >> (64 - CC_SIMD_BITS(base))); \
    const CC_SIMD_TYPE(base, count) Mask33 = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x3333333333333333) >> (64 - CC_SIMD_BITS(base))); \
    const CC_SIMD_TYPE(base, count) Mask0f = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x0f0f0f0f0f0f0f0f) >> (64 - CC_SIMD_BITS(base))); \
    const CC_SIMD_TYPE(base, count) Mask01 = CC_SIMD_NAME(CCSimdFill, base, count)(UINT64_C(0x0101010101010101) >> (64 - CC_SIMD_BITS(base))); \
    \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    Result = CC_SIMD_NAME(CCSimdSub, base, count)(Result, CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdShiftRightN, base, count)(Result, 1), Mask55)); \
    Result = CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAnd, base, count)(Result, Mask33), CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdShiftRightN, base, count)(Result, 2), Mask33)); \
    Result = CC_SIMD_NAME(CCSimdAnd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(Result, CC_SIMD_NAME(CCSimdShiftRightN, base, count)(Result, 4)), Mask0f); \
    Result = CC_SIMD_NAME(CCSimdShiftRightN, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(Result, Mask01), CC_SIMD_BITS(base) - 8); \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdCountSet, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdCountSet)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareNotEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareNotEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareNotEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareNotEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareNotEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareLessThan
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareLessThan, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThan))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareLessThan, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareLessThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThan))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareLessThanEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareLessThanEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThanEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareLessThanEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareLessThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareLessThanEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareGreaterThan
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThan, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThan))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThan, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareGreaterThan, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThan))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThanEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdShiftRightN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdShiftLeftN, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareGreaterThanEqual, base, count)(a, b), 25), 2); }
CC_SIMD_DECL(CCSimdCompareGreaterThanEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMaskCompareNotEqual
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNot, base, count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdMaskCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMaskCompareNotEqual))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdNot, CC_SIMD_TO(base, u), count)(CC_SIMD_NAME(CCSimdMaskCompareEqual, base, count)(a, b)); }
CC_SIMD_DECL(CCSimdMaskCompareNotEqual, CC_SIMD_RETURN_TYPE_SIMD_TO(u), CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdMaskCompareNotEqual))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMadd
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), c); }
CC_SIMD_DECL(CCSimdMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMadd)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdNegMadd
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b)), c); }
CC_SIMD_DECL(CCSimdNegMadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdNegMadd)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdMsub
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), c); }
CC_SIMD_DECL(CCSimdMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdMsub)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdNegMsub
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, const CC_SIMD_TYPE(base, count) c){ return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdNeg, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b)), c); }
CC_SIMD_DECL(CCSimdNegMsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdNegMsub)
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdDiv
#if CC_SIMD_COMPATIBILITY
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b) \
{ \
    CC_SIMD_TYPE(base, count) Result = a; \
    \
    for (size_t Loop = 0; Loop < count; Loop++) \
    { \
        Result = CC_SIMD_NAME(CCSimdSet, base, count)(Result, Loop, CC_SIMD_NAME(CCSimdGet, base, count)(a, Loop) / CC_SIMD_NAME(CCSimdGet, base, count)(b, Loop)); \
    } \
    \
    return Result; \
}
CC_SIMD_DECL(CCSimdDiv, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdDiv)
#undef CC_SIMD_IMPL
#endif
#endif

#ifdef CC_SIMD_MISSING_CCSimdMod
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdDiv, base, count)(a, b), b)); }
CC_SIMD_DECL(CCSimdMod, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_INTEGER_TYPES), CC_SIMD_MISSING_CCSimdMod))
#undef CC_SIMD_IMPL

#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b){ return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdMul, base, count)(CC_SIMD_NAME(CCSimdFloor, base, count)(CC_SIMD_NAME(CCSimdDiv, base, count)(a, b)), b)); }
CC_SIMD_DECL(CCSimdMod, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_FLOAT_TYPES), CC_SIMD_MISSING_CCSimdMod))
#undef CC_SIMD_IMPL
#endif

#ifdef CC_SIMD_MISSING_CCSimdHadd
#if CC_SIMD_LANES_MAX >= 2
#define CC_SIMD_HADD_MASK(x0, x1) ((x1) << 2) | (x0)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 <= 3) && (v1 <= 3), "Index masks must not exceed lane count"); \
    \
    switch (CC_SIMD_HADD_MASK(v0, v1)) \
    { \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), 0): \
        case CC_SIMD_HADD_MASK(0, CC_SIMD_LANE_MASK(1)): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(1)): \
        case 0: return a; \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 1); \
            \
        case CC_SIMD_HADD_MASK(0, CC_SIMD_LANE_MASK(0)): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), 0): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0); \
            \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 0, 1); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 0, 1); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
            \
        case CC_SIMD_HADD_MASK(0, CC_SIMD_LANE_MASK(0, 1)): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), 0): \
        case CC_SIMD_HADD_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdAdd, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
#undef CC_SIMD_IMPL
#undef CC_SIMD_HADD_MASK
#endif

#if CC_SIMD_LANES_MAX >= 4
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 | ((v0 << 4) & 16), CC_SIMD_A0 | ((v1 << 4) & 16), CC_SIMD_A0 | ((v2 << 4) & 16), CC_SIMD_A0 | ((v3 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 | ((v0 << 3) & 16), CC_SIMD_A1 | ((v1 << 3) & 16), CC_SIMD_A1 | ((v2 << 3) & 16), CC_SIMD_A1 | ((v3 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 | ((v0 << 2) & 16), CC_SIMD_A2 | ((v1 << 2) & 16), CC_SIMD_A2 | ((v2 << 2) & 16), CC_SIMD_A2 | ((v3 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 | ((v0 << 1) & 16), CC_SIMD_A3 | ((v1 << 1) & 16), CC_SIMD_A3 | ((v2 << 1) & 16), CC_SIMD_A3 | ((v3 << 1) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 8
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 | ((v0 << 4) & 16), CC_SIMD_A0 | ((v1 << 4) & 16), CC_SIMD_A0 | ((v2 << 4) & 16), CC_SIMD_A0 | ((v3 << 4) & 16), CC_SIMD_A0 | ((v4 << 4) & 16), CC_SIMD_A0 | ((v5 << 4) & 16), CC_SIMD_A0 | ((v6 << 4) & 16), CC_SIMD_A0 | ((v7 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 | ((v0 << 3) & 16), CC_SIMD_A1 | ((v1 << 3) & 16), CC_SIMD_A1 | ((v2 << 3) & 16), CC_SIMD_A1 | ((v3 << 3) & 16), CC_SIMD_A1 | ((v4 << 3) & 16), CC_SIMD_A1 | ((v5 << 3) & 16), CC_SIMD_A1 | ((v6 << 3) & 16), CC_SIMD_A1 | ((v7 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 | ((v0 << 2) & 16), CC_SIMD_A2 | ((v1 << 2) & 16), CC_SIMD_A2 | ((v2 << 2) & 16), CC_SIMD_A2 | ((v3 << 2) & 16), CC_SIMD_A2 | ((v4 << 2) & 16), CC_SIMD_A2 | ((v5 << 2) & 16), CC_SIMD_A2 | ((v6 << 2) & 16), CC_SIMD_A2 | ((v7 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 | ((v0 << 1) & 16), CC_SIMD_A3 | ((v1 << 1) & 16), CC_SIMD_A3 | ((v2 << 1) & 16), CC_SIMD_A3 | ((v3 << 1) & 16), CC_SIMD_A3 | ((v4 << 1) & 16), CC_SIMD_A3 | ((v5 << 1) & 16), CC_SIMD_A3 | ((v6 << 1) & 16), CC_SIMD_A3 | ((v7 << 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L4 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A4 | ((v0 << 0) & 16), CC_SIMD_A4 | ((v1 << 0) & 16), CC_SIMD_A4 | ((v2 << 0) & 16), CC_SIMD_A4 | ((v3 << 0) & 16), CC_SIMD_A4 | ((v4 << 0) & 16), CC_SIMD_A4 | ((v5 << 0) & 16), CC_SIMD_A4 | ((v6 << 0) & 16), CC_SIMD_A4 | ((v7 << 0) & 16)); \
    const CC_SIMD_TYPE(base, count) L5 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A5 | ((v0 >> 1) & 16), CC_SIMD_A5 | ((v1 >> 1) & 16), CC_SIMD_A5 | ((v2 >> 1) & 16), CC_SIMD_A5 | ((v3 >> 1) & 16), CC_SIMD_A5 | ((v4 >> 1) & 16), CC_SIMD_A5 | ((v5 >> 1) & 16), CC_SIMD_A5 | ((v6 >> 1) & 16), CC_SIMD_A5 | ((v7 >> 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L6 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A6 | ((v0 >> 2) & 16), CC_SIMD_A6 | ((v1 >> 2) & 16), CC_SIMD_A6 | ((v2 >> 2) & 16), CC_SIMD_A6 | ((v3 >> 2) & 16), CC_SIMD_A6 | ((v4 >> 2) & 16), CC_SIMD_A6 | ((v5 >> 2) & 16), CC_SIMD_A6 | ((v6 >> 2) & 16), CC_SIMD_A6 | ((v7 >> 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L7 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A7 | ((v0 >> 3) & 16), CC_SIMD_A7 | ((v1 >> 3) & 16), CC_SIMD_A7 | ((v2 >> 3) & 16), CC_SIMD_A7 | ((v3 >> 3) & 16), CC_SIMD_A7 | ((v4 >> 3) & 16), CC_SIMD_A7 | ((v5 >> 3) & 16), CC_SIMD_A7 | ((v6 >> 3) & 16), CC_SIMD_A7 | ((v7 >> 3) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)), CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L4, L5), CC_SIMD_NAME(CCSimdAdd, base, count)(L6, L7))); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 16
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7, uint8_t v8, uint8_t v9, uint8_t v10, uint8_t v11, uint8_t v12, uint8_t v13, uint8_t v14, uint8_t v15) \
{ \
    CCAssertLog((v0 <= 0xffff) & (v1 <= 0xffff) & (v2 <= 0xffff) & (v3 <= 0xffff) & (v4 <= 0xffff) & (v5 <= 0xffff) & (v6 <= 0xffff) & (v7 <= 0xffff) & (v8 <= 0xffff) & (v9 <= 0xffff) & (v10 <= 0xffff) & (v11 <= 0xffff) & (v12 <= 0xffff) & (v13 <= 0xffff) & (v14 <= 0xffff) & (v15 <= 0xffff), "Index masks must not exceed lane count"); \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 | ((v0 << 4) & 16), CC_SIMD_A0 | ((v1 << 4) & 16), CC_SIMD_A0 | ((v2 << 4) & 16), CC_SIMD_A0 | ((v3 << 4) & 16), CC_SIMD_A0 | ((v4 << 4) & 16), CC_SIMD_A0 | ((v5 << 4) & 16), CC_SIMD_A0 | ((v6 << 4) & 16), CC_SIMD_A0 | ((v7 << 4) & 16), CC_SIMD_A0 | ((v8 << 4) & 16), CC_SIMD_A0 | ((v9 << 4) & 16), CC_SIMD_A0 | ((v10 << 4) & 16), CC_SIMD_A0 | ((v11 << 4) & 16), CC_SIMD_A0 | ((v12 << 4) & 16), CC_SIMD_A0 | ((v13 << 4) & 16), CC_SIMD_A0 | ((v14 << 4) & 16), CC_SIMD_A0 | ((v15 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 | ((v0 << 3) & 16), CC_SIMD_A1 | ((v1 << 3) & 16), CC_SIMD_A1 | ((v2 << 3) & 16), CC_SIMD_A1 | ((v3 << 3) & 16), CC_SIMD_A1 | ((v4 << 3) & 16), CC_SIMD_A1 | ((v5 << 3) & 16), CC_SIMD_A1 | ((v6 << 3) & 16), CC_SIMD_A1 | ((v7 << 3) & 16), CC_SIMD_A1 | ((v8 << 3) & 16), CC_SIMD_A1 | ((v9 << 3) & 16), CC_SIMD_A1 | ((v10 << 3) & 16), CC_SIMD_A1 | ((v11 << 3) & 16), CC_SIMD_A1 | ((v12 << 3) & 16), CC_SIMD_A1 | ((v13 << 3) & 16), CC_SIMD_A1 | ((v14 << 3) & 16), CC_SIMD_A1 | ((v15 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 | ((v0 << 2) & 16), CC_SIMD_A2 | ((v1 << 2) & 16), CC_SIMD_A2 | ((v2 << 2) & 16), CC_SIMD_A2 | ((v3 << 2) & 16), CC_SIMD_A2 | ((v4 << 2) & 16), CC_SIMD_A2 | ((v5 << 2) & 16), CC_SIMD_A2 | ((v6 << 2) & 16), CC_SIMD_A2 | ((v7 << 2) & 16), CC_SIMD_A2 | ((v8 << 2) & 16), CC_SIMD_A2 | ((v9 << 2) & 16), CC_SIMD_A2 | ((v10 << 2) & 16), CC_SIMD_A2 | ((v11 << 2) & 16), CC_SIMD_A2 | ((v12 << 2) & 16), CC_SIMD_A2 | ((v13 << 2) & 16), CC_SIMD_A2 | ((v14 << 2) & 16), CC_SIMD_A2 | ((v15 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 | ((v0 << 1) & 16), CC_SIMD_A3 | ((v1 << 1) & 16), CC_SIMD_A3 | ((v2 << 1) & 16), CC_SIMD_A3 | ((v3 << 1) & 16), CC_SIMD_A3 | ((v4 << 1) & 16), CC_SIMD_A3 | ((v5 << 1) & 16), CC_SIMD_A3 | ((v6 << 1) & 16), CC_SIMD_A3 | ((v7 << 1) & 16), CC_SIMD_A3 | ((v8 << 1) & 16), CC_SIMD_A3 | ((v9 << 1) & 16), CC_SIMD_A3 | ((v10 << 1) & 16), CC_SIMD_A3 | ((v11 << 1) & 16), CC_SIMD_A3 | ((v12 << 1) & 16), CC_SIMD_A3 | ((v13 << 1) & 16), CC_SIMD_A3 | ((v14 << 1) & 16), CC_SIMD_A3 | ((v15 << 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L4 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A4 | ((v0 << 0) & 16), CC_SIMD_A4 | ((v1 << 0) & 16), CC_SIMD_A4 | ((v2 << 0) & 16), CC_SIMD_A4 | ((v3 << 0) & 16), CC_SIMD_A4 | ((v4 << 0) & 16), CC_SIMD_A4 | ((v5 << 0) & 16), CC_SIMD_A4 | ((v6 << 0) & 16), CC_SIMD_A4 | ((v7 << 0) & 16), CC_SIMD_A4 | ((v8 << 0) & 16), CC_SIMD_A4 | ((v9 << 0) & 16), CC_SIMD_A4 | ((v10 << 0) & 16), CC_SIMD_A4 | ((v11 << 0) & 16), CC_SIMD_A4 | ((v12 << 0) & 16), CC_SIMD_A4 | ((v13 << 0) & 16), CC_SIMD_A4 | ((v14 << 0) & 16), CC_SIMD_A4 | ((v15 << 0) & 16)); \
    const CC_SIMD_TYPE(base, count) L5 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A5 | ((v0 >> 1) & 16), CC_SIMD_A5 | ((v1 >> 1) & 16), CC_SIMD_A5 | ((v2 >> 1) & 16), CC_SIMD_A5 | ((v3 >> 1) & 16), CC_SIMD_A5 | ((v4 >> 1) & 16), CC_SIMD_A5 | ((v5 >> 1) & 16), CC_SIMD_A5 | ((v6 >> 1) & 16), CC_SIMD_A5 | ((v7 >> 1) & 16), CC_SIMD_A5 | ((v8 >> 1) & 16), CC_SIMD_A5 | ((v9 >> 1) & 16), CC_SIMD_A5 | ((v10 >> 1) & 16), CC_SIMD_A5 | ((v11 >> 1) & 16), CC_SIMD_A5 | ((v12 >> 1) & 16), CC_SIMD_A5 | ((v13 >> 1) & 16), CC_SIMD_A5 | ((v14 >> 1) & 16), CC_SIMD_A5 | ((v15 >> 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L6 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A6 | ((v0 >> 2) & 16), CC_SIMD_A6 | ((v1 >> 2) & 16), CC_SIMD_A6 | ((v2 >> 2) & 16), CC_SIMD_A6 | ((v3 >> 2) & 16), CC_SIMD_A6 | ((v4 >> 2) & 16), CC_SIMD_A6 | ((v5 >> 2) & 16), CC_SIMD_A6 | ((v6 >> 2) & 16), CC_SIMD_A6 | ((v7 >> 2) & 16), CC_SIMD_A6 | ((v8 >> 2) & 16), CC_SIMD_A6 | ((v9 >> 2) & 16), CC_SIMD_A6 | ((v10 >> 2) & 16), CC_SIMD_A6 | ((v11 >> 2) & 16), CC_SIMD_A6 | ((v12 >> 2) & 16), CC_SIMD_A6 | ((v13 >> 2) & 16), CC_SIMD_A6 | ((v14 >> 2) & 16), CC_SIMD_A6 | ((v15 >> 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L7 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A7 | ((v0 >> 3) & 16), CC_SIMD_A7 | ((v1 >> 3) & 16), CC_SIMD_A7 | ((v2 >> 3) & 16), CC_SIMD_A7 | ((v3 >> 3) & 16), CC_SIMD_A7 | ((v4 >> 3) & 16), CC_SIMD_A7 | ((v5 >> 3) & 16), CC_SIMD_A7 | ((v6 >> 3) & 16), CC_SIMD_A7 | ((v7 >> 3) & 16), CC_SIMD_A7 | ((v8 >> 3) & 16), CC_SIMD_A7 | ((v9 >> 3) & 16), CC_SIMD_A7 | ((v10 >> 3) & 16), CC_SIMD_A7 | ((v11 >> 3) & 16), CC_SIMD_A7 | ((v12 >> 3) & 16), CC_SIMD_A7 | ((v13 >> 3) & 16), CC_SIMD_A7 | ((v14 >> 3) & 16), CC_SIMD_A7 | ((v15 >> 3) & 16)); \

const CC_SIMD_TYPE(base, count) L8 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A8 | ((v0 >> 4) & 16), CC_SIMD_A8 | ((v1 >> 4) & 16), CC_SIMD_A8 | ((v2 >> 4) & 16), CC_SIMD_A8 | ((v3 >> 4) & 16), CC_SIMD_A8 | ((v4 >> 4) & 16), CC_SIMD_A8 | ((v5 >> 4) & 16), CC_SIMD_A8 | ((v6 >> 4) & 16), CC_SIMD_A8 | ((v7 >> 4) & 16), CC_SIMD_A8 | ((v8 >> 4) & 16), CC_SIMD_A8 | ((v9 >> 4) & 16), CC_SIMD_A8 | ((v10 >> 4) & 16), CC_SIMD_A8 | ((v11 >> 4) & 16), CC_SIMD_A8 | ((v12 >> 4) & 16), CC_SIMD_A8 | ((v13 >> 4) & 16), CC_SIMD_A8 | ((v14 >> 4) & 16), CC_SIMD_A8 | ((v15 >> 4) & 16)); \
const CC_SIMD_TYPE(base, count) L9 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A9 | ((v0 >> 5) & 16), CC_SIMD_A9 | ((v1 >> 5) & 16), CC_SIMD_A9 | ((v2 >> 5) & 16), CC_SIMD_A9 | ((v3 >> 5) & 16), CC_SIMD_A9 | ((v4 >> 5) & 16), CC_SIMD_A9 | ((v5 >> 5) & 16), CC_SIMD_A9 | ((v6 >> 5) & 16), CC_SIMD_A9 | ((v7 >> 5) & 16), CC_SIMD_A9 | ((v8 >> 5) & 16), CC_SIMD_A9 | ((v9 >> 5) & 16), CC_SIMD_A9 | ((v10 >> 5) & 16), CC_SIMD_A9 | ((v11 >> 5) & 16), CC_SIMD_A9 | ((v12 >> 5) & 16), CC_SIMD_A9 | ((v13 >> 5) & 16), CC_SIMD_A9 | ((v14 >> 5) & 16), CC_SIMD_A9 | ((v15 >> 5) & 16)); \
const CC_SIMD_TYPE(base, count) L10 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A10 | ((v0 >> 6) & 16), CC_SIMD_A10 | ((v1 >> 6) & 16), CC_SIMD_A10 | ((v2 >> 6) & 16), CC_SIMD_A10 | ((v3 >> 6) & 16), CC_SIMD_A10 | ((v4 >> 6) & 16), CC_SIMD_A10 | ((v5 >> 6) & 16), CC_SIMD_A10 | ((v6 >> 6) & 16), CC_SIMD_A10 | ((v7 >> 6) & 16), CC_SIMD_A10 | ((v8 >> 6) & 16), CC_SIMD_A10 | ((v9 >> 6) & 16), CC_SIMD_A10 | ((v10 >> 6) & 16), CC_SIMD_A10 | ((v11 >> 6) & 16), CC_SIMD_A10 | ((v12 >> 6) & 16), CC_SIMD_A10 | ((v13 >> 6) & 16), CC_SIMD_A10 | ((v14 >> 6) & 16), CC_SIMD_A10 | ((v15 >> 6) & 16)); \
const CC_SIMD_TYPE(base, count) L11 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, ); \
const CC_SIMD_TYPE(base, count) L12 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, ); \
const CC_SIMD_TYPE(base, count) L13 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, ); \
const CC_SIMD_TYPE(base, count) L14 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, ); \
const CC_SIMD_TYPE(base, count) L15 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, ); \

    \
    return CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)), CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L4, L5), CC_SIMD_NAME(CCSimdAdd, base, count)(L6, L7))); \
}
CC_SIMD_DECL(CCSimdHadd, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_N_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHadd))
#undef CC_SIMD_IMPL
#endif

#endif

#ifdef CC_SIMD_MISSING_CCSimdHsub
#if CC_SIMD_LANES_MAX >= 2
#define CC_SIMD_HSUB_MASK(x0, x1) ((x1) << 2) | (x0)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 <= 3) && (v1 <= 3), "Index masks must not exceed lane count"); \
    \
    switch (CC_SIMD_HSUB_MASK(v0, v1)) \
    { \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), 0): \
        case CC_SIMD_HSUB_MASK(0, CC_SIMD_LANE_MASK(1)): \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(1)): \
        case 0: return a; \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 1); \
            \
        case CC_SIMD_HSUB_MASK(0, CC_SIMD_LANE_MASK(0)): \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), 0): \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0); \
            \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), a), 0, 1); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), a), 0, 1); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdInterleave, base, count)(a, CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)), 1, 0); \
            \
        case CC_SIMD_HSUB_MASK(0, CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0), a); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), 0): return CC_SIMD_NAME(CCSimdSub, base, count)(a, CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 0)); \
        case CC_SIMD_HSUB_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 0, 0), CC_SIMD_NAME(CCSimdSwizzle, base, count)(a, 1, 1)); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHsub))
#undef CC_SIMD_IMPL
#undef CC_SIMD_HSUB_MASK
#endif

#if CC_SIMD_LANES_MAX >= 4
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    const uint8_t AdjustV0 = CCBitCountLowestUnset(v0); \
    const uint8_t AdjustV1 = CCBitCountLowestUnset(v1); \
    const uint8_t AdjustV2 = CCBitCountLowestUnset(v2); \
    const uint8_t AdjustV3 = CCBitCountLowestUnset(v3); \
    \
    v0 >>= AdjustV0; \
    v1 >>= AdjustV1; \
    v2 >>= AdjustV2; \
    v3 >>= AdjustV3; \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A0 + (AdjustV0 * ((v0 >> 0) & 1))) | ((v0 << 4) & 16), (CC_SIMD_A0 + (AdjustV1 * ((v1 >> 0) & 1))) | ((v1 << 4) & 16), (CC_SIMD_A0 + (AdjustV2 * ((v2 >> 0) & 1))) | ((v2 << 4) & 16), (CC_SIMD_A0 + (AdjustV3 * ((v3 >> 0) & 1))) | ((v3 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A1 + (AdjustV0 * ((v0 >> 1) & 1))) | ((v0 << 3) & 16), (CC_SIMD_A1 + (AdjustV1 * ((v1 >> 1) & 1))) | ((v1 << 3) & 16), (CC_SIMD_A1 + (AdjustV2 * ((v2 >> 1) & 1))) | ((v2 << 3) & 16), (CC_SIMD_A1 + (AdjustV3 * ((v3 >> 1) & 1))) | ((v3 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A2 + (AdjustV0 * ((v0 >> 2) & 1))) | ((v0 << 2) & 16), (CC_SIMD_A2 + (AdjustV1 * ((v1 >> 2) & 1))) | ((v1 << 2) & 16), (CC_SIMD_A2 + (AdjustV2 * ((v2 >> 2) & 1))) | ((v2 << 2) & 16), (CC_SIMD_A2 + (AdjustV3 * ((v3 >> 2) & 1))) | ((v3 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, (CC_SIMD_A3 + (AdjustV0 * ((v0 >> 3) & 1))) | ((v0 << 1) & 16), (CC_SIMD_A3 + (AdjustV1 * ((v1 >> 3) & 1))) | ((v1 << 1) & 16), (CC_SIMD_A3 + (AdjustV2 * ((v2 >> 3) & 1))) | ((v2 << 1) & 16), (CC_SIMD_A3 + (AdjustV3 * ((v3 >> 3) & 1))) | ((v3 << 1) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSub, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)); \
}
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHsub))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 8
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    const uint8_t AdjustV0 = CCBitCountLowestUnset(v0); \
    const uint8_t AdjustV1 = CCBitCountLowestUnset(v1); \
    const uint8_t AdjustV2 = CCBitCountLowestUnset(v2); \
    const uint8_t AdjustV3 = CCBitCountLowestUnset(v3); \
    const uint8_t AdjustV4 = CCBitCountLowestUnset(v4); \
    const uint8_t AdjustV5 = CCBitCountLowestUnset(v5); \
    const uint8_t AdjustV6 = CCBitCountLowestUnset(v6); \
    const uint8_t AdjustV7 = CCBitCountLowestUnset(v7); \
    \
    v0 >>= AdjustV0; \
    v1 >>= AdjustV1; \
    v2 >>= AdjustV2; \
    v3 >>= AdjustV3; \
    v4 >>= AdjustV4; \
    v5 >>= AdjustV5; \
    v6 >>= AdjustV6; \
    v7 >>= AdjustV7; \
    \
    const CC_SIMD_TYPE(base, count) Zero = CC_SIMD_NAME(CCSimdZero, base, count)(); \
    \
    const CC_SIMD_TYPE(base, count) L0 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A0 + (AdjustV0 * ((v0 >> 0) & 1)) | ((v0 << 4) & 16), CC_SIMD_A0 + (AdjustV1 * ((v1 >> 0) & 1)) | ((v1 << 4) & 16), CC_SIMD_A0 + (AdjustV2 * ((v2 >> 0) & 1)) | ((v2 << 4) & 16), CC_SIMD_A0 + (AdjustV3 * ((v3 >> 0) & 1)) | ((v3 << 4) & 16), CC_SIMD_A0 + (AdjustV4 * ((v4 >> 0) & 1)) | ((v4 << 4) & 16), CC_SIMD_A0 + (AdjustV5 * ((v5 >> 0) & 1)) | ((v5 << 4) & 16), CC_SIMD_A0 + (AdjustV6 * ((v6 >> 0) & 1)) | ((v6 << 4) & 16), CC_SIMD_A0 + (AdjustV7 * ((v7 >> 0) & 1)) | ((v7 << 4) & 16)); \
    const CC_SIMD_TYPE(base, count) L1 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A1 + (AdjustV0 * ((v0 >> 1) & 1)) | ((v0 << 3) & 16), CC_SIMD_A1 + (AdjustV1 * ((v1 >> 1) & 1)) | ((v1 << 3) & 16), CC_SIMD_A1 + (AdjustV2 * ((v2 >> 1) & 1)) | ((v2 << 3) & 16), CC_SIMD_A1 + (AdjustV3 * ((v3 >> 1) & 1)) | ((v3 << 3) & 16), CC_SIMD_A1 + (AdjustV4 * ((v4 >> 1) & 1)) | ((v4 << 3) & 16), CC_SIMD_A1 + (AdjustV5 * ((v5 >> 1) & 1)) | ((v5 << 3) & 16), CC_SIMD_A1 + (AdjustV6 * ((v6 >> 1) & 1)) | ((v6 << 3) & 16), CC_SIMD_A1 + (AdjustV7 * ((v7 >> 1) & 1)) | ((v7 << 3) & 16)); \
    const CC_SIMD_TYPE(base, count) L2 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A2 + (AdjustV0 * ((v0 >> 2) & 1)) | ((v0 << 2) & 16), CC_SIMD_A2 + (AdjustV1 * ((v1 >> 2) & 1)) | ((v1 << 2) & 16), CC_SIMD_A2 + (AdjustV2 * ((v2 >> 2) & 1)) | ((v2 << 2) & 16), CC_SIMD_A2 + (AdjustV3 * ((v3 >> 2) & 1)) | ((v3 << 2) & 16), CC_SIMD_A2 + (AdjustV4 * ((v4 >> 2) & 1)) | ((v4 << 2) & 16), CC_SIMD_A2 + (AdjustV5 * ((v5 >> 2) & 1)) | ((v5 << 2) & 16), CC_SIMD_A2 + (AdjustV6 * ((v6 >> 2) & 1)) | ((v6 << 2) & 16), CC_SIMD_A2 + (AdjustV7 * ((v7 >> 2) & 1)) | ((v7 << 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L3 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A3 + (AdjustV0 * ((v0 >> 3) & 1)) | ((v0 << 1) & 16), CC_SIMD_A3 + (AdjustV1 * ((v1 >> 3) & 1)) | ((v1 << 1) & 16), CC_SIMD_A3 + (AdjustV2 * ((v2 >> 3) & 1)) | ((v2 << 1) & 16), CC_SIMD_A3 + (AdjustV3 * ((v3 >> 3) & 1)) | ((v3 << 1) & 16), CC_SIMD_A3 + (AdjustV4 * ((v4 >> 3) & 1)) | ((v4 << 1) & 16), CC_SIMD_A3 + (AdjustV5 * ((v5 >> 3) & 1)) | ((v5 << 1) & 16), CC_SIMD_A3 + (AdjustV6 * ((v6 >> 3) & 1)) | ((v6 << 1) & 16), CC_SIMD_A3 + (AdjustV7 * ((v7 >> 3) & 1)) | ((v7 << 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L4 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A4 + (AdjustV0 * ((v0 >> 4) & 1)) | ((v0 << 0) & 16), CC_SIMD_A4 + (AdjustV1 * ((v1 >> 4) & 1)) | ((v1 << 0) & 16), CC_SIMD_A4 + (AdjustV2 * ((v2 >> 4) & 1)) | ((v2 << 0) & 16), CC_SIMD_A4 + (AdjustV3 * ((v3 >> 4) & 1)) | ((v3 << 0) & 16), CC_SIMD_A4 + (AdjustV4 * ((v4 >> 4) & 1)) | ((v4 << 0) & 16), CC_SIMD_A4 + (AdjustV5 * ((v5 >> 4) & 1)) | ((v5 << 0) & 16), CC_SIMD_A4 + (AdjustV6 * ((v6 >> 4) & 1)) | ((v6 << 0) & 16), CC_SIMD_A4 + (AdjustV7 * ((v7 >> 4) & 1)) | ((v7 << 0) & 16)); \
    const CC_SIMD_TYPE(base, count) L5 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A5 + (AdjustV0 * ((v0 >> 5) & 1)) | ((v0 >> 1) & 16), CC_SIMD_A5 + (AdjustV1 * ((v1 >> 5) & 1)) | ((v1 >> 1) & 16), CC_SIMD_A5 + (AdjustV2 * ((v2 >> 5) & 1)) | ((v2 >> 1) & 16), CC_SIMD_A5 + (AdjustV3 * ((v3 >> 5) & 1)) | ((v3 >> 1) & 16), CC_SIMD_A5 + (AdjustV4 * ((v4 >> 5) & 1)) | ((v4 >> 1) & 16), CC_SIMD_A5 + (AdjustV5 * ((v5 >> 5) & 1)) | ((v5 >> 1) & 16), CC_SIMD_A5 + (AdjustV6 * ((v6 >> 5) & 1)) | ((v6 >> 1) & 16), CC_SIMD_A5 + (AdjustV7 * ((v7 >> 5) & 1)) | ((v7 >> 1) & 16)); \
    const CC_SIMD_TYPE(base, count) L6 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A6 + (AdjustV0 * ((v0 >> 6) & 1)) | ((v0 >> 2) & 16), CC_SIMD_A6 + (AdjustV1 * ((v1 >> 6) & 1)) | ((v1 >> 2) & 16), CC_SIMD_A6 + (AdjustV2 * ((v2 >> 6) & 1)) | ((v2 >> 2) & 16), CC_SIMD_A6 + (AdjustV3 * ((v3 >> 6) & 1)) | ((v3 >> 2) & 16), CC_SIMD_A6 + (AdjustV4 * ((v4 >> 6) & 1)) | ((v4 >> 2) & 16), CC_SIMD_A6 + (AdjustV5 * ((v5 >> 6) & 1)) | ((v5 >> 2) & 16), CC_SIMD_A6 + (AdjustV6 * ((v6 >> 6) & 1)) | ((v6 >> 2) & 16), CC_SIMD_A6 + (AdjustV7 * ((v7 >> 6) & 1)) | ((v7 >> 2) & 16)); \
    const CC_SIMD_TYPE(base, count) L7 = CC_SIMD_NAME(CCSimdMerge, base, count)(Zero, a, CC_SIMD_A7 + (AdjustV0 * ((v0 >> 7) & 1)) | ((v0 >> 3) & 16), CC_SIMD_A7 + (AdjustV1 * ((v1 >> 7) & 1)) | ((v1 >> 3) & 16), CC_SIMD_A7 + (AdjustV2 * ((v2 >> 7) & 1)) | ((v2 >> 3) & 16), CC_SIMD_A7 + (AdjustV3 * ((v3 >> 7) & 1)) | ((v3 >> 3) & 16), CC_SIMD_A7 + (AdjustV4 * ((v4 >> 7) & 1)) | ((v4 >> 3) & 16), CC_SIMD_A7 + (AdjustV5 * ((v5 >> 7) & 1)) | ((v5 >> 3) & 16), CC_SIMD_A7 + (AdjustV6 * ((v6 >> 7) & 1)) | ((v6 >> 3) & 16), CC_SIMD_A7 + (AdjustV7 * ((v7 >> 7) & 1)) | ((v7 >> 3) & 16)); \
    \
    return CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSub, base, count)(CC_SIMD_NAME(CCSimdSub, base, count)(L0, L1), CC_SIMD_NAME(CCSimdAdd, base, count)(L2, L3)), CC_SIMD_NAME(CCSimdAdd, base, count)(CC_SIMD_NAME(CCSimdAdd, base, count)(L4, L5), CC_SIMD_NAME(CCSimdAdd, base, count)(L6, L7))); \
}
CC_SIMD_DECL(CCSimdHsub, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdHsub))
#undef CC_SIMD_IMPL
#endif

#endif

#ifdef CC_SIMD_MISSING_CCSimdDot
#if CC_SIMD_LANES_MAX >= 2
#define CC_SIMD_DOT_MASK(x0, x1) ((x1) << 2) | (x0)
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1) \
{ \
    CCAssertLog((v0 <= 3) && (v1 <= 3), "Index masks must not exceed lane count"); \
    \
    switch (CC_SIMD_DOT_MASK(v0, v1)) \
    { \
        case 0: return a; \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), 0, 0); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), 1, 1); \
        case CC_SIMD_DOT_MASK(0, CC_SIMD_LANE_MASK(1)): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), 0): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdMul, base, count)(a, b); \
        case CC_SIMD_DOT_MASK(0, CC_SIMD_LANE_MASK(0)): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), 0): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdSwizzle, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), 1, 0); \
            \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0), CC_SIMD_LANE_MASK(0, 1)); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(1), CC_SIMD_LANE_MASK(0, 1)); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0)); \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(1)); \
            \
        case CC_SIMD_DOT_MASK(0, CC_SIMD_LANE_MASK(0, 1)): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), 0): \
        case CC_SIMD_DOT_MASK(CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)): return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), CC_SIMD_LANE_MASK(0, 1), CC_SIMD_LANE_MASK(0, 1)); \
    } \
    \
    CC_UNREACHABLE(); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_2_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdDot))
#undef CC_SIMD_IMPL
#undef CC_SIMD_DOT_MASK
#endif

#if CC_SIMD_LANES_MAX >= 4
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3) \
{ \
    CCAssertLog((v0 <= 15) && (v1 <= 15) && (v2 <= 15) && (v3 <= 15), "Index masks must not exceed lane count"); \
    \
    return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), v0, v1, v2, v3); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_4_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdDot))
#undef CC_SIMD_IMPL
#endif

#if CC_SIMD_LANES_MAX >= 8
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) b, uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6, uint8_t v7) \
{ \
    CCAssertLog((v0 <= 255) && (v1 <= 255) && (v2 <= 255) && (v3 <= 255) && (v4 <= 255) && (v5 <= 255) && (v6 <= 255) && (v7 <= 255), "Index masks must not exceed lane count"); \
    \
    return CC_SIMD_NAME(CCSimdHadd, base, count)(CC_SIMD_NAME(CCSimdMul, base, count)(a, b), v0, v1, v2, v3, v4, v5, v6, v7); \
}
CC_SIMD_DECL(CCSimdDot, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_TYPE_FILTER((CC_SIMD_64_8_ELEMENT_TYPES), CC_SIMD_MISSING_CCSimdDot))
#undef CC_SIMD_IMPL
#endif

#endif

#ifdef CC_SIMD_MISSING_CCSimdClamp
#define CC_SIMD_IMPL(base, count, kind) (const CC_SIMD_TYPE(base, count) a, const CC_SIMD_TYPE(base, count) min, const CC_SIMD_TYPE(base, count) max){ return CC_SIMD_NAME(CCSimdMin, base, count)(CC_SIMD_NAME(CCSimdMax, base, count)(a, min), max); }
CC_SIMD_DECL(CCSimdClamp, CC_SIMD_RETURN_TYPE_SIMD, CC_SIMD_MISSING_CCSimdClamp)
#undef CC_SIMD_IMPL
#endif

#define T f32
#include <CommonC/SimdFallbackTrig.h>

#define T f64
#include <CommonC/SimdFallbackTrig.h>

#undef CC_SIMD_LANES_MAX

#undef CC_SIMD_N_2_ELEMENT_TYPES
#undef CC_SIMD_N_4_ELEMENT_TYPES
#undef CC_SIMD_N_8_ELEMENT_TYPES
#undef CC_SIMD_N_16_ELEMENT_TYPES
#undef CC_SIMD_N_32_ELEMENT_TYPES
#undef CC_SIMD_N_64_ELEMENT_TYPES

#undef CC_SIMD_N_INTEGER_TYPES
#undef CC_SIMD_N_FLOAT_TYPES

#undef CC_SIMD_N_2_ELEMENT_INTEGER_TYPES
#undef CC_SIMD_N_4_ELEMENT_INTEGER_TYPES
#undef CC_SIMD_N_8_ELEMENT_INTEGER_TYPES
#undef CC_SIMD_N_16_ELEMENT_INTEGER_TYPES
#undef CC_SIMD_N_32_ELEMENT_INTEGER_TYPES
#undef CC_SIMD_N_64_ELEMENT_INTEGER_TYPES

#undef CC_SIMD_N_INTEGER_64_TYPES
#undef CC_SIMD_N_INTEGER_32_TYPES
#undef CC_SIMD_N_INTEGER_16_TYPES
#undef CC_SIMD_N_INTEGER_8_TYPES
