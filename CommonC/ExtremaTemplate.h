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

#include <CommonC/Template.h>

#define CCMin_T(t) CC_TEMPLATE_REF(CCMin, t, t, t)
#define CCMax_T(t) CC_TEMPLATE_REF(CCMax, t, t, t)
#define CCClamp_T(t) CC_TEMPLATE_REF(CCClamp, t, t, t)

CC_TEMPLATE(static CC_FORCE_INLINE T, CCMin, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE T, CCMax, (const T a, const T b));
CC_TEMPLATE(static CC_FORCE_INLINE T, CCClamp, (const T Val, const T Min, const T Max));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE T, CCMin, (const T a, const T b))
{
    return a < b ? a : b;
}

CC_TEMPLATE(static CC_FORCE_INLINE T, CCMax, (const T a, const T b))
{
    return a > b ? a : b;
}

CC_TEMPLATE(static CC_FORCE_INLINE T, CCClamp, (const T Val, const T Min, const T Max))
{
    return CCMin_T(T)(CCMax_T(T)(Val, Min), Max);
}
