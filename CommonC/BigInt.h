/*
 *  Copyright (c) 2019, Stefan Johnson
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

#ifndef CommonC_BigInt_h
#define CommonC_BigInt_h

#include <CommonC/Base.h>
#include <CommonC/Platform.h>
#include <CommonC/Generics.h>
#include <CommonC/Maths.h>
#include <CommonC/CCString.h>
#include <CommonC/List.h>

typedef struct CCBigIntInfo {
    CCList(uint64_t) value;
    _Bool sign;
} CCBigIntInfo;

/*!
 * @brief The big integer.
 * @description Allows @b CCRetain.
 */
typedef struct CCBigIntInfo *CCBigInt;


#pragma mark - Creation/Destruction
/*!
 * @brief Create a big integer.
 * @param Allocator The allocator to be used for the allocation.
 * @return A big integer set to 0, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCBigInt CCBigIntCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a big integer.
 * @param Integer The big integer to be destroyed.
 */
void CCBigIntDestroy(CCBigInt CC_DESTROY(Integer));

#pragma mark - Query

/*!
 * @brief Get an internal component from the big integer.
 * @param Integer The big integer to get the component of.
 * @param Index The index of the component. The higher the index the more significant the
 *        component is to the overall value. The lower the index the less significant the
 *        component is to the overall value.
 *
 * @return The component value.
 */
static CC_FORCE_INLINE uint64_t CCBigIntGetComponent(CCBigInt Integer, size_t Index);

/*!
 * @brief Get the number of internal components of a big integer.
 * @param Integer The big integer to get the component count of.
 * @return The number of components.
 */
static CC_FORCE_INLINE size_t CCBigIntGetComponentCount(CCBigInt Integer);

/*!
 * @brief Get the sign of a big integer.
 * @param Integer The big integer to get the sign of.
 * @return Whether the sign part of the integer is set or not. If TRUE then the integer is
 *         negative, while if FALSE then the integer is positive.
 */
static CC_FORCE_INLINE _Bool CCBigIntGetSign(CCBigInt Integer);

#pragma mark - Getter/Setter

/*!
 * @define CCBigIntSet
 * @abstract Generic macro to set the big integer to the given value.
 * @param Integer The big integer to be set.
 * @param Value The value to set the big integer to. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to set the integer to the value represented by another big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntSet(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntSetBigInt, \
CCString: CCBigIntSetString, \
default: CCBigIntSetInt)(integer, value)

void CCBigIntSetBigInt(CCBigInt Integer, CCBigInt Value);
void CCBigIntSetInt(CCBigInt Integer, int64_t Value);
void CCBigIntSetString(CCBigInt Integer, CCString Value);

/*!
 * @brief Get a hexadecimal string representation of the big integer.
 * @param Integer The big integer to convert to a string.
 * @return The hexadecimal string. Must be destroyed to free the memory.
 */
CC_NEW CCString CCBigIntGetString(CCBigInt Integer);

#pragma mark - Comparisons

/*!
 * @define CCBigIntCompare
 * @abstract Generic macro to compare a big integer with a value.
 * @param Integer The big integer to compare.
 * @param Value The value to compare to. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to compare an integer to the value represented by another big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 *
 * @return The comparison order.
 */
#define CCBigIntCompare(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntCompareBigInt, \
CCString: CCBigIntCompareString, \
default: CCBigIntCompareInt)(integer, value)

CCComparisonResult CCBigIntCompareBigInt(CCBigInt a, CCBigInt b);
CCComparisonResult CCBigIntCompareInt(CCBigInt a, int64_t b);
CCComparisonResult CCBigIntCompareString(CCBigInt a, CCString b);

#pragma mark - Operations

/*!
 * @define CCBigIntAdd
 * @abstract Generic macro to add value to the big integer.
 * @param Integer The big integer to apply and store the result of the addition.
 * @param Value The value to add to the big integer. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to add an integer to the value represented by another big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntAdd(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntAddBigInt, \
CCString: CCBigIntAddString, \
default: CCBigIntAddInt)(integer, value)

void CCBigIntAddBigInt(CCBigInt Integer, CCBigInt Value);
void CCBigIntAddInt(CCBigInt Integer, int64_t Value);
void CCBigIntAddString(CCBigInt Integer, CCString Value);

/*!
 * @define CCBigIntSub
 * @abstract Generic macro to subtract value from the big integer.
 * @param Integer The big integer to apply and store the result of the subtraction.
 * @param Value The value to subtract from the big integer. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to subtract an integer from the value represented by another big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntSub(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntSubBigInt, \
CCString: CCBigIntSubString, \
default: CCBigIntSubInt)(integer, value)

void CCBigIntSubBigInt(CCBigInt Integer, CCBigInt Value);
void CCBigIntSubInt(CCBigInt Integer, int64_t Value);
void CCBigIntSubString(CCBigInt Integer, CCString Value);

#pragma mark -

static CC_FORCE_INLINE uint64_t CCBigIntGetComponent(CCBigInt Integer, size_t Index)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return *(uint64_t*)CCListGetElementAtIndex(Integer->value, Index);
}

static CC_FORCE_INLINE size_t CCBigIntGetComponentCount(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return CCListGetCount(Integer->value);
}

static CC_FORCE_INLINE _Bool CCBigIntGetSign(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return Integer->sign;
}

#endif
