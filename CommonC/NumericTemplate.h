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

#include <CommonC/Template.h>

#define CCNumericAdd_T(t) CC_TEMPLATE_REF(CCNumericAdd, t, t, t)
#define CCNumericSubtract_T(t) CC_TEMPLATE_REF(CCNumericSubtract, t, t, t)
#define CCNumericMultiply_T(t) CC_TEMPLATE_REF(CCNumericMultiply, t, t, t)
#define CCNumericDivide_T(t) CC_TEMPLATE_REF(CCNumericDivide, t, t, t)

#define CCNumericEqual_T(t) CC_TEMPLATE_REF(CCNumericEqual, _Bool, t, t)
#define CCNumericLessThan_T(t) CC_TEMPLATE_REF(CCNumericLessThan, _Bool, t, t)
#define CCNumericLessThanEqual_T(t) CC_TEMPLATE_REF(CCNumericLessThanEqual, _Bool, t, t)
#define CCNumericGreaterThan_T(t) CC_TEMPLATE_REF(CCNumericGreaterThan, _Bool, t, t)
#define CCNumericGreaterThanEqual_T(t) CC_TEMPLATE_REF(CCNumericGreaterThanEqual, _Bool, t, t)


CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericAdd, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericSubtract, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericMultiply, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericDivide, (const T a, const T b));

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericEqual, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericLessThan, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericLessThanEqual, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericGreaterThan, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericGreaterThanEqual, (const T a, const T b));


#pragma mark -

#ifndef CC_NUMERIC_EQUAL
#define CC_NUMERIC_EQUAL(a, b) ((a) == (b))
#endif

#ifndef CC_NUMERIC_LESS_THAN
#define CC_NUMERIC_LESS_THAN(a, b) ((a) < (b))
#endif

#ifndef CC_NUMERIC_GREATER_THAN
#define CC_NUMERIC_GREATER_THAN(a, b) ((a) > (b))
#endif

#ifndef CC_NUMERIC_LESS_THAN_EQUAL
#define CC_NUMERIC_LESS_THAN_EQUAL(a, b) ((a) <= (b))
#endif

#ifndef CC_NUMERIC_GREATER_THAN_EQUAL
#define CC_NUMERIC_GREATER_THAN_EQUAL(a, b) ((a) >= (b))
#endif

#ifndef CC_NUMERIC_ADD
#define CC_NUMERIC_ADD(a, b) ((a) + (b))
#endif

#ifndef CC_NUMERIC_SUB
#define CC_NUMERIC_SUB(a, b) ((a) - (b))
#endif

#ifndef CC_NUMERIC_MUL
#define CC_NUMERIC_MUL(a, b) ((a) * (b))
#endif

#ifndef CC_NUMERIC_DIV
#define CC_NUMERIC_DIV(a, b) ((a) / (b))
#endif

CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericAdd, (const T a, const T b))
{
    return CC_NUMERIC_ADD(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericSubtract, (const T a, const T b))
{
    return CC_NUMERIC_SUB(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericMultiply, (const T a, const T b))
{
    return CC_NUMERIC_MUL(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE T, CCNumericDivide, (const T a, const T b))
{
    return CC_NUMERIC_DIV(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericEqual, (const T a, const T b))
{
    return CC_NUMERIC_EQUAL(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericLessThan, (const T a, const T b))
{
    return CC_NUMERIC_LESS_THAN(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericLessThanEqual, (const T a, const T b))
{
    return CC_NUMERIC_LESS_THAN_EQUAL(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericGreaterThan, (const T a, const T b))
{
    return CC_NUMERIC_GREATER_THAN(a, b);
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCNumericGreaterThanEqual, (const T a, const T b))
{
    return CC_NUMERIC_GREATER_THAN_EQUAL(a, b);
}

#undef CC_NUMERIC_EQUAL
#undef CC_NUMERIC_LESS_THAN
#undef CC_NUMERIC_GREATER_THAN
#undef CC_NUMERIC_LESS_THAN_EQUAL
#undef CC_NUMERIC_GREATER_THAN_EQUAL
#undef CC_NUMERIC_ADD
#undef CC_NUMERIC_SUB
#undef CC_NUMERIC_MUL
#undef CC_NUMERIC_DIV
