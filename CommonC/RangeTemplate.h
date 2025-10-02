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

#define CCRangeContainsRange_T(t) CC_TEMPLATE_REF(CCRangeContains, _Bool, t, t)
#define CCRangeIntersectRange_T(t) CC_TEMPLATE_REF(CCRangeIntersects, _Bool, t, t)
#define CCRangeGetIntersection_T(t) CC_TEMPLATE_REF(CCRangeGetIntersection, t, t, t)

#undef CCRange

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCRangeContains, (const T Range, const T InnerRange));
CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCRangeIntersects, (const T RangeA, const T RangeB));
CC_TEMPLATE(static CC_FORCE_INLINE T, CCRangeGetIntersection, (const T RangeA, const T RangeB));

#pragma mark -

#ifndef CC_RANGE_VALUE_LESS_THAN
#define CC_RANGE_VALUE_LESS_THAN(a, b) CCNumericLessThan((a), (b))
#endif

#ifndef CC_RANGE_VALUE_GREATER_THAN
#define CC_RANGE_VALUE_GREATER_THAN(a, b) CCNumericGreaterThan((a), (b))
#endif

#ifndef CC_RANGE_VALUE_LESS_THAN_EQUAL
#define CC_RANGE_VALUE_LESS_THAN_EQUAL(a, b) CCNumericLessThanEqual((a), (b))
#endif

#ifndef CC_RANGE_VALUE_GREATER_THAN_EQUAL
#define CC_RANGE_VALUE_GREATER_THAN_EQUAL(a, b) CCNumericGreaterThanEqual((a), (b))
#endif

#ifndef CC_RANGE_VALUE_ADD
#define CC_RANGE_VALUE_ADD(a, b) CCNumericAdd((a), (b))
#endif

#ifndef CC_RANGE_VALUE_SUB
#define CC_RANGE_VALUE_SUB(a, b) CCNumericSubtract((a), (b))
#endif

#ifndef CC_RANGE_VALUE_MAX
#define CC_RANGE_VALUE_MAX(a, b) CCMax((a), (b))
#endif

#ifndef CC_RANGE_VALUE_MIN
#define CC_RANGE_VALUE_MIN(a, b) CCMin((a), (b))
#endif

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCRangeContains, (const T Range, const T InnerRange))
{
    return CC_RANGE_VALUE_LESS_THAN_EQUAL(Range.start, InnerRange.start) && CC_RANGE_VALUE_GREATER_THAN_EQUAL(CC_RANGE_VALUE_ADD(Range.start, Range.length), CC_RANGE_VALUE_ADD(InnerRange.start, InnerRange.length));
}

CC_TEMPLATE(static CC_FORCE_INLINE _Bool, CCRangeIntersects, (const T RangeA, const T RangeB))
{
    return CC_RANGE_VALUE_LESS_THAN_EQUAL(RangeA.start, CC_RANGE_VALUE_ADD(RangeB.start, RangeB.length)) && CC_RANGE_VALUE_GREATER_THAN_EQUAL(CC_RANGE_VALUE_ADD(RangeA.start, RangeA.length), RangeB.start);
}

CC_TEMPLATE(static CC_FORCE_INLINE T, CCRangeGetIntersection, (const T RangeA, const T RangeB))
{
    const Ttype Start = CC_RANGE_VALUE_MAX(RangeA.start, RangeB.start);
    
    return CCRangeMake(Start, CC_RANGE_VALUE_SUB(CC_RANGE_VALUE_MIN(CC_RANGE_VALUE_ADD(RangeA.start, RangeA.length), CC_RANGE_VALUE_ADD(RangeB.start, RangeB.length)), Start));
}

#ifndef CC_RANGE_PRESERVE_IMPS
#undef CC_RANGE_VALUE_LESS_THAN
#undef CC_RANGE_VALUE_GREATER_THAN
#undef CC_RANGE_VALUE_LESS_THAN_EQUAL
#undef CC_RANGE_VALUE_GREATER_THAN_EQUAL
#undef CC_RANGE_VALUE_ADD
#undef CC_RANGE_VALUE_SUB
#undef CC_RANGE_VALUE_MAX
#undef CC_RANGE_VALUE_MIN
#endif

#define CCRange(type) CC_RANGE(type)
