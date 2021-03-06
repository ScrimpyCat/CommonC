/*
 *  Copyright (c) 2015, Stefan Johnson
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

#ifndef CommonC_Comparator_h
#define CommonC_Comparator_h

#include <CommonC/Extensions.h>

/*!
 * @brief The order result of two values.
 */
typedef CC_ENUM(CCComparisonResult, int8_t) {
    ///Left is smaller than Right
    CCComparisonResultAscending = -1,
    ///Left and Right are the same
    CCComparisonResultEqual,
    ///Left is bigger than Right
    CCComparisonResultDescending,
    ///A comparison between left and right is not valid
    CCComparisonResultInvalid
};

/*!
 * @brief Generic comparator function.
 */
typedef CCComparisonResult (*CCComparator)(const void *left, const void *right);

/*!
 * @brief Flip the order of a comparison result.
 * @description @b CCComparisonResultAscending becomes @b CCComparisonResultDescending and vice
 *              versa. @b CCComparisonResultEqual and @b CCComparisonResultInvalid remain the
 *              same.
 *
 * @param Order The comparison order to be flipped.
 * @return The flipped order.
 */
static CC_FORCE_INLINE CCComparisonResult CCComparisonResultFlipOrder(CCComparisonResult Order);

#pragma mark -

static CC_FORCE_INLINE CCComparisonResult CCComparisonResultFlipOrder(CCComparisonResult Order)
{
    if (CC_UNLIKELY(Order == CCComparisonResultInvalid)) return Order;
    
    _Static_assert((CCComparisonResultAscending == -1) && (CCComparisonResultDescending == 1) && (CCComparisonResultEqual == 0), "Expects these exact values");
    
    return -Order;
}

#endif
