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

#ifndef CommonC_BigIntFast_h
#define CommonC_BigIntFast_h

#include <CommonC/BigInt.h>

#define CC_BIG_INT_FAST_TAGGED_MASK 1

#define CC_BIG_INT_FAST_TAGGED_MAX ((int64_t)(UINTPTR_MAX >> 2))
#define CC_BIG_INT_FAST_TAGGED_MIN ((int64_t)(-CC_BIG_INT_FAST_TAGGED_MAX - 1))

#define CC_BIG_INT_FAST_ASSERT_CONSTANT(n, ...) _Static_assert((n <= CC_BIG_INT_FAST_TAGGED_MAX) && (n >= CC_BIG_INT_FAST_TAGGED_MIN), "" __VA_ARGS__)

#define CC_BIG_INT_FAST_CONSTANT(n) ((CCBigIntFast)(((uintptr_t)(n) << 1) | CC_BIG_INT_FAST_TAGGED_MASK))
#define CC_BIG_INT_FAST_0   CC_BIG_INT_FAST_CONSTANT(0)
#define CC_BIG_INT_FAST_1   CC_BIG_INT_FAST_CONSTANT(1)
#define CC_BIG_INT_FAST_2   CC_BIG_INT_FAST_CONSTANT(2)
#define CC_BIG_INT_FAST_3   CC_BIG_INT_FAST_CONSTANT(3)
#define CC_BIG_INT_FAST_4   CC_BIG_INT_FAST_CONSTANT(4)
#define CC_BIG_INT_FAST_5   CC_BIG_INT_FAST_CONSTANT(5)
#define CC_BIG_INT_FAST_6   CC_BIG_INT_FAST_CONSTANT(6)
#define CC_BIG_INT_FAST_7   CC_BIG_INT_FAST_CONSTANT(7)
#define CC_BIG_INT_FAST_8   CC_BIG_INT_FAST_CONSTANT(8)
#define CC_BIG_INT_FAST_9   CC_BIG_INT_FAST_CONSTANT(9)
#define CC_BIG_INT_FAST_10  CC_BIG_INT_FAST_CONSTANT(10)
#define CC_BIG_INT_FAST_11  CC_BIG_INT_FAST_CONSTANT(11)
#define CC_BIG_INT_FAST_12  CC_BIG_INT_FAST_CONSTANT(12)
#define CC_BIG_INT_FAST_13  CC_BIG_INT_FAST_CONSTANT(13)
#define CC_BIG_INT_FAST_14  CC_BIG_INT_FAST_CONSTANT(14)
#define CC_BIG_INT_FAST_15  CC_BIG_INT_FAST_CONSTANT(15)
#define CC_BIG_INT_FAST_16  CC_BIG_INT_FAST_CONSTANT(16)
#define CC_BIG_INT_FAST_32  CC_BIG_INT_FAST_CONSTANT(32)
#define CC_BIG_INT_FAST_64  CC_BIG_INT_FAST_CONSTANT(64)
#define CC_BIG_INT_FAST_128 CC_BIG_INT_FAST_CONSTANT(128)
#define CC_BIG_INT_FAST_256 CC_BIG_INT_FAST_CONSTANT(256)

#define CC_BIG_INT_FAST_NEGATIVE_1   CC_BIG_INT_FAST_CONSTANT(-1)
#define CC_BIG_INT_FAST_NEGATIVE_2   CC_BIG_INT_FAST_CONSTANT(-2)
#define CC_BIG_INT_FAST_NEGATIVE_3   CC_BIG_INT_FAST_CONSTANT(-3)
#define CC_BIG_INT_FAST_NEGATIVE_4   CC_BIG_INT_FAST_CONSTANT(-4)
#define CC_BIG_INT_FAST_NEGATIVE_5   CC_BIG_INT_FAST_CONSTANT(-5)
#define CC_BIG_INT_FAST_NEGATIVE_6   CC_BIG_INT_FAST_CONSTANT(-6)
#define CC_BIG_INT_FAST_NEGATIVE_7   CC_BIG_INT_FAST_CONSTANT(-7)
#define CC_BIG_INT_FAST_NEGATIVE_8   CC_BIG_INT_FAST_CONSTANT(-8)
#define CC_BIG_INT_FAST_NEGATIVE_9   CC_BIG_INT_FAST_CONSTANT(-9)
#define CC_BIG_INT_FAST_NEGATIVE_10  CC_BIG_INT_FAST_CONSTANT(-10)
#define CC_BIG_INT_FAST_NEGATIVE_11  CC_BIG_INT_FAST_CONSTANT(-11)
#define CC_BIG_INT_FAST_NEGATIVE_12  CC_BIG_INT_FAST_CONSTANT(-12)
#define CC_BIG_INT_FAST_NEGATIVE_13  CC_BIG_INT_FAST_CONSTANT(-13)
#define CC_BIG_INT_FAST_NEGATIVE_14  CC_BIG_INT_FAST_CONSTANT(-14)
#define CC_BIG_INT_FAST_NEGATIVE_15  CC_BIG_INT_FAST_CONSTANT(-15)
#define CC_BIG_INT_FAST_NEGATIVE_16  CC_BIG_INT_FAST_CONSTANT(-16)
#define CC_BIG_INT_FAST_NEGATIVE_32  CC_BIG_INT_FAST_CONSTANT(-32)
#define CC_BIG_INT_FAST_NEGATIVE_64  CC_BIG_INT_FAST_CONSTANT(-64)
#define CC_BIG_INT_FAST_NEGATIVE_128 CC_BIG_INT_FAST_CONSTANT(-128)
#define CC_BIG_INT_FAST_NEGATIVE_256 CC_BIG_INT_FAST_CONSTANT(-256)

CC_BIG_INT_FAST_ASSERT_CONSTANT(256);
CC_BIG_INT_FAST_ASSERT_CONSTANT(-256);

#pragma mark - Creation/Destruction
/*!
 * @brief Create a fast big integer.
 * @param Allocator The allocator to be used for the allocation.
 * @return A fast big integer set to 0, or NULL on failure. Must be destroyed to free the memory.
 */
static inline CC_NEW CCBigIntFast CCBigIntFastCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a fast big integer.
 * @param Integer The big integer to be destroyed.
 */
static inline void CCBigIntFastDestroy(CCBigIntFast CC_DESTROY(Integer));

/*!
 * @brief Copy a fast big integer.
 * @param Integer The big integer to be copied.
 */
static inline CC_NEW CCBigIntFast CCBigIntFastCopy(CCBigIntFast Integer);

#pragma mark - Query

static inline _Bool CCBigIntFastIsTaggedValue(CCBigIntFast Integer);
static inline int64_t CCBigIntFastGetTaggedValue(CCBigIntFast Integer);
static inline CCBigIntFast CCBigIntFastTaggedValue(int64_t Value);

/*!
 * @brief Get the sign of a fast big integer.
 * @param Integer The big integer to get the sign of.
 * @return Whether the sign part of the integer is set or not. If TRUE then the integer is
 *         negative, while if FALSE then the integer is positive.
 */
static inline _Bool CCBigIntFastGetSign(CCBigIntFast Integer);

#pragma mark - Getter/Setter

/*!
 * @define CCBigIntFastSet
 * @abstract Generic macro to set the fast big integer to the given value.
 * @param Integer The big integer to be set.
 * @param Value The value to set the big integer to. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to set the integer to the value represented by another big integer.
 *
 *        @b CCBigIntFast - to set the integer to the value represented by another fast big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntFastSet(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntFastSetBigInt, \
CCBigIntFast: CCBigIntFastSetBigIntFast, \
CCString: CCBigIntFastSetString, \
default: CCBigIntFastSetInt)(integer, value)

static inline void CCBigIntFastSetBigInt(CCBigIntFast *Integer, CCBigInt Value);
static inline void CCBigIntFastSetBigIntFast(CCBigIntFast *Integer, CCBigIntFast Value);
static inline void CCBigIntFastSetInt(CCBigIntFast *Integer, int64_t Value);
static inline void CCBigIntFastSetString(CCBigIntFast *Integer, CCString Value);

/*!
 * @brief Convert a fast big integer to an ordinary big integer.
 * @note Modifying the result may modify the source integer.
 * @param Integer The fast big integer to convert to a big integer.
 * @return The big integer. Must be destroyed to free the memory.
 */
static inline CC_NEW CCBigInt CCBigIntFastGetBigInt(CCBigIntFast Integer);

/*!
 * @brief Get a hexadecimal string representation of the fast big integer.
 * @param Integer The big integer to convert to a string.
 * @return The hexadecimal string. Must be destroyed to free the memory.
 */
static inline CC_NEW CCString CCBigIntFastGetString(CCBigIntFast Integer);

#pragma mark - Comparisons

/*!
 * @define CCBigIntFastCompare
 * @abstract Generic macro to compare a big integer with a value.
 * @param integer The big integer to compare.
 * @param value The value to compare to. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to compare an integer to the value represented by another big integer.
 *
 *        @b CCBigIntFast - to compare an integer to the value represented by another fast big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 *
 * @return The comparison order.
 */
#define CCBigIntFastCompare(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntFastCompareBigInt, \
CCBigIntFast: CCBigIntFastCompareBigIntFast, \
CCString: CCBigIntFastCompareString, \
default: CCBigIntFastCompareInt)(integer, value)

static inline CCComparisonResult CCBigIntFastCompareBigInt(CCBigIntFast a, CCBigInt b);
static inline CCComparisonResult CCBigIntFastCompareBigIntFast(CCBigIntFast a, CCBigIntFast b);
static inline CCComparisonResult CCBigIntFastCompareInt(CCBigIntFast a, int64_t b);
static inline CCComparisonResult CCBigIntFastCompareString(CCBigIntFast a, CCString b);

/*!
 * @define CCBigIntFastCompareEqual
 * @abstract Generic macro to check whether a big integer is equal to the value.
 * @param a The big integer to compare.
 * @param b The value to compare to. See inputs allowed by @b CCBigIntCompare
 * @return Whether a and b are equal.
 */
#define CCBigIntFastCompareEqual(a, b) (CCBigIntFastCompare(a, b) == CCComparisonResultEqual)

/*!
 * @define CCBigIntFastCompareLessThan
 * @abstract Generic macro to check whether a big integer is less than the value.
 * @param a The big integer to compare.
 * @param b The value to compare to. See inputs allowed by @b CCBigIntCompare
 * @return Whether a is less than b.
 */
#define CCBigIntFastCompareLessThan(a, b) (CCBigIntFastCompare(a, b) == CCComparisonResultAscending)

/*!
 * @define CCBigIntFastCompareLessThanEqual
 * @abstract Generic macro to check whether a big integer is equal or less than the value.
 * @param a The big integer to compare.
 * @param b The value to compare to. See inputs allowed by @b CCBigIntCompare
 * @return Whether a is less than or equal to b.
 */
#define CCBigIntFastCompareLessThanEqual(a, b) (CCBigIntFastCompare(a, b) != CCComparisonResultDescending)

/*!
 * @define CCBigIntFastCompareGreaterThan
 * @abstract Generic macro to check whether a big integer is greater than the value.
 * @param a The big integer to compare.
 * @param b The value to compare to. See inputs allowed by @b CCBigIntCompare
 * @return Whether a is greater than b.
 */
#define CCBigIntFastCompareGreaterThan(a, b) (CCBigIntFastCompare(a, b) == CCComparisonResultDescending)

/*!
 * @define CCBigIntFastCompareGreaterThanEqual
 * @abstract Generic macro to check whether a big integer is equal or greather than the value.
 * @param a The big integer to compare.
 * @param b The value to compare to. See inputs allowed by @b CCBigIntCompare
 * @return Whether a is greater than or equal to b.
 */
#define CCBigIntFastCompareGreaterThanEqual(a, b) (CCBigIntFastCompare(a, b) != CCComparisonResultAscending)

#pragma mark - Operations

/*!
 * @define CCBigIntFastAdd
 * @abstract Generic macro to add value to the big integer.
 * @param Integer The big integer to apply and store the result of the addition.
 * @param Value The value to add to the big integer. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to add an integer to the value represented by another big integer.
 *
 *        @b CCBigIntFast - to add an integer to the value represented by another fast big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntFastAdd(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntFastAddBigInt, \
CCBigIntFast: CCBigIntFastAddBigIntFast, \
CCString: CCBigIntFastAddString, \
default: CCBigIntFastAddInt)(integer, value)

static inline void CCBigIntFastAddBigInt(CCBigIntFast *Integer, CCBigInt Value);
static inline void CCBigIntFastAddBigIntFast(CCBigIntFast *Integer, CCBigIntFast Value);
static inline void CCBigIntFastAddInt(CCBigIntFast *Integer, int64_t Value);
static inline void CCBigIntFastAddString(CCBigIntFast *Integer, CCString Value);

/*!
 * @define CCBigIntFastSub
 * @abstract Generic macro to subtract value from the big integer.
 * @param Integer The big integer to apply and store the result of the subtraction.
 * @param Value The value to subtract from the big integer. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to subtract an integer from the value represented by another big integer.
 *
 *        @b CCBigIntFast - to subtract an integer from the value represented by another fast big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntFastSub(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntFastSubBigInt, \
CCBigIntFast: CCBigIntFastSubBigIntFast, \
CCString: CCBigIntFastSubString, \
default: CCBigIntFastSubInt)(integer, value)

static inline void CCBigIntFastSubBigInt(CCBigIntFast *Integer, CCBigInt Value);
static inline void CCBigIntFastSubBigIntFast(CCBigIntFast *Integer, CCBigIntFast Value);
static inline void CCBigIntFastSubInt(CCBigIntFast *Integer, int64_t Value);
static inline void CCBigIntFastSubString(CCBigIntFast *Integer, CCString Value);

#pragma mark -
static inline CCBigIntFast CCBigIntFastCreate(CCAllocatorType Allocator)
{
    return CC_BIG_INT_FAST_0;
}

static inline void CCBigIntFastDestroy(CCBigIntFast Integer)
{
    if (!CCBigIntFastIsTaggedValue(Integer)) CCBigIntDestroy((CCBigInt)Integer);
}

static inline CCBigIntFast CCBigIntFastCopy(CCBigIntFast Integer)
{
    if (!CCBigIntFastIsTaggedValue(Integer))
    {
        CCBigInt Value = CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet(Value, Integer);
        return (CCBigIntFast)Value;
    }
    
    return Integer;
}

static inline _Bool CCBigIntFastIsTaggedValue(CCBigIntFast Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return (uintptr_t)Integer & CC_BIG_INT_FAST_TAGGED_MASK;
}

static inline int64_t CCBigIntFastGetTaggedValue(CCBigIntFast Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(CCBigIntFastIsTaggedValue(Integer), "Integer must be a tagged variant");
    
    return (intptr_t)Integer >> 1;
}

static inline CCBigIntFast CCBigIntFastTaggedValue(int64_t Value)
{
    CCAssertLog((Value <= CC_BIG_INT_FAST_TAGGED_MAX) && (Value >= CC_BIG_INT_FAST_TAGGED_MIN), "Integer must not be null");
    
    return (CCBigIntFast)(((uintptr_t)Value << 1) | CC_BIG_INT_FAST_TAGGED_MASK);
}

static inline _Bool CCBigIntFastGetSign(CCBigIntFast Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return CCBigIntFastIsTaggedValue(Integer) ? (CCBigIntFastGetTaggedValue(Integer) < 0) : CCBigIntGetSign((CCBigInt)Integer);
}

static inline void CCBigIntFastSetBigInt(CCBigIntFast *Integer, CCBigInt Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntGetComponentCount(Value) == 1)
    {
        const uint64_t Component = CCBigIntGetComponent(Value, 0);
        if ((Component & ~INT64_MAX) == 0)
        {
            const int64_t IntegerValue = CCBigIntGetSign(Value) ? -Component : Component;
            
            if ((IntegerValue <= CC_BIG_INT_FAST_TAGGED_MAX) || (IntegerValue >= CC_BIG_INT_FAST_TAGGED_MIN))
            {
                CCBigIntFastDestroy(*Integer);
                *Integer = CCBigIntFastTaggedValue(IntegerValue);
                
                return;
            }
        }
    }
    
    if (CCBigIntFastIsTaggedValue(*Integer)) *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntSet((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastSetBigIntFast(CCBigIntFast *Integer, CCBigIntFast Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(Value))
    {
        CCBigIntFastDestroy(*Integer);
        *Integer = Value;
    }
    
    else CCBigIntFastSet(Integer, (CCBigInt)Value);
}

static inline void CCBigIntFastSetInt(CCBigIntFast *Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    
    if ((Value <= CC_BIG_INT_FAST_TAGGED_MAX) || (Value >= CC_BIG_INT_FAST_TAGGED_MIN))
    {
        CCBigIntFastDestroy(*Integer);
        *Integer = CCBigIntFastTaggedValue(Value);
        
        return;
    }
    
    else if (CCBigIntFastIsTaggedValue(*Integer)) *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntSet((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastSetString(CCBigIntFast *Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    
    if (CCBigIntFastIsTaggedValue(*Integer)) *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
    
    CCBigIntSet((CCBigInt)*Integer, Value);
}

static inline CCBigInt CCBigIntFastGetBigInt(CCBigIntFast Integer)
{
    if (CCBigIntFastIsTaggedValue(Integer))
    {
        CCBigInt Value = CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet(Value, Integer);
        
        return Value;
    }
    
    return CCRetain(Integer);
}

static inline CCString CCBigIntFastGetString(CCBigIntFast Integer)
{
    if (CCBigIntFastIsTaggedValue(Integer))
    {
        CCBigInt Temp = CCBigIntFastGetBigInt(Integer);
        CCString String = CCBigIntGetString((CCBigInt)Temp);
        CCBigIntDestroy(Temp);
        
        return String;
    }
    
    else return CCBigIntGetString((CCBigInt)Integer);
}

static inline CCComparisonResult CCBigIntFastCompareBigInt(CCBigIntFast a, CCBigInt b)
{
    return CCComparisonResultFlipOrder(CCBigIntCompare(b, a));
}

static inline CCComparisonResult CCBigIntFastCompareBigIntFast(CCBigIntFast a, CCBigIntFast b)
{
    if (CCBigIntFastIsTaggedValue(a))
    {
        const int64_t ValueA = CCBigIntFastGetTaggedValue(a);
        
        if (CCBigIntFastIsTaggedValue(b))
        {
            const int64_t ValueB = CCBigIntFastGetTaggedValue(b);
            
            return ValueA < ValueB ? CCComparisonResultAscending : (ValueA > ValueB ? CCComparisonResultDescending : CCComparisonResultEqual);
        }
        
        return CCComparisonResultFlipOrder(CCBigIntCompare((CCBigInt)b, ValueA));
    }
    
    return CCBigIntCompare((CCBigInt)a, b);
}

static inline CCComparisonResult CCBigIntFastCompareInt(CCBigIntFast a, int64_t b)
{
    if (CCBigIntFastIsTaggedValue(a))
    {
        const int64_t Value = CCBigIntFastGetTaggedValue(a);
        
        return Value < b ? CCComparisonResultAscending : (Value > b ? CCComparisonResultDescending : CCComparisonResultEqual);
    }
    
    return CCBigIntCompare((CCBigInt)a, b);
}

static inline CCComparisonResult CCBigIntFastCompareString(CCBigIntFast a, CCString b)
{
    if (CCBigIntFastIsTaggedValue(a))
    {
        const int64_t ValueA = CCBigIntFastGetTaggedValue(a);
        CCBigInt ValueB = CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet(ValueB, b);
        const CCComparisonResult Result = CCComparisonResultFlipOrder(CCBigIntCompare(ValueB, ValueA));
        CCBigIntDestroy(ValueB);
        
        return Result;
    }
    
    return CCBigIntCompare((CCBigInt)a, b);
}

static inline void CCBigIntFastAddBigInt(CCBigIntFast *Integer, CCBigInt Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(*Integer))
    {
        if (CCBigIntGetComponentCount(Value) == 1)
        {
            const uint64_t Component = CCBigIntGetComponent(Value, 0);
            if ((Component & ~INT64_MAX) == 0)
            {
                CCBigIntFastAdd(Integer, CCBigIntGetSign(Value) ? -Component : Component);
                return;
            }
        }
        
        const int64_t IntegerValue = CCBigIntFastGetTaggedValue(*Integer);
        
        *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet((CCBigInt)*Integer, IntegerValue);
    }
    
    CCBigIntAdd((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastAddBigIntFast(CCBigIntFast *Integer, CCBigIntFast Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(Value)) CCBigIntFastAdd(Integer, CCBigIntFastGetTaggedValue(*Integer));
    else CCBigIntFastAdd(Integer, (CCBigInt)Value);
}

static inline void CCBigIntFastAddInt(CCBigIntFast *Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    
    if (CCBigIntFastIsTaggedValue(*Integer))
    {
        const int64_t IntegerValue = CCBigIntFastGetTaggedValue(*Integer);
        
        if (((Value > 0) && (IntegerValue > (INT64_MAX - Value))) || ((Value < 0) && (IntegerValue < (INT64_MIN - Value))))
        {
            *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
            CCBigIntSet((CCBigInt)*Integer, IntegerValue);
        }
        
        else
        {
            const int64_t Result = IntegerValue + Value;
            
            if ((Result <= CC_BIG_INT_FAST_TAGGED_MAX) || (Result >= CC_BIG_INT_FAST_TAGGED_MIN))
            {
                *Integer = CCBigIntFastTaggedValue(Result);
            }
            
            else
            {
                *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
                CCBigIntSet((CCBigInt)*Integer, Result);
            }
            
            return;
        }
    }
    
    CCBigIntAdd((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastAddString(CCBigIntFast *Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    
    if (CCBigIntFastIsTaggedValue(*Integer))
    {
        CCBigInt ValueB = CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet(ValueB, Value);
        CCBigIntFastAdd(Integer, ValueB);
        CCBigIntDestroy(ValueB);
    }
    
    else CCBigIntAdd((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastSubBigInt(CCBigIntFast *Integer, CCBigInt Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(*Integer))
    {
        if (CCBigIntGetComponentCount(Value) == 1)
        {
            const uint64_t Component = CCBigIntGetComponent(Value, 0);
            if ((Component & ~INT64_MAX) == 0)
            {
                CCBigIntFastSub(Integer, CCBigIntGetSign(Value) ? -Component : Component);
                return;
            }
        }
        
        const int64_t IntegerValue = CCBigIntFastGetTaggedValue(*Integer);
        
        *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet((CCBigInt)*Integer, IntegerValue);
    }
    
    CCBigIntSub((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastSubBigIntFast(CCBigIntFast *Integer, CCBigIntFast Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(Value)) CCBigIntFastSub(Integer, CCBigIntFastGetTaggedValue(*Integer));
    else CCBigIntFastSub(Integer, (CCBigInt)Value);
}

static inline void CCBigIntFastSubInt(CCBigIntFast *Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    
    if (CCBigIntFastIsTaggedValue(*Integer))
    {
        const int64_t IntegerValue = CCBigIntFastGetTaggedValue(*Integer);
        
        if (((Value < 0) && (IntegerValue > (INT64_MAX + Value))) || ((Value > 0) && (IntegerValue < (INT64_MIN + Value))))
        {
            *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
            CCBigIntSet((CCBigInt)*Integer, IntegerValue);
        }
        
        else
        {
            const int64_t Result = IntegerValue - Value;
            
            if ((Result <= CC_BIG_INT_FAST_TAGGED_MAX) || (Result >= CC_BIG_INT_FAST_TAGGED_MIN))
            {
                *Integer = CCBigIntFastTaggedValue(Result);
            }
            
            else
            {
                *Integer = (CCBigIntFast)CCBigIntCreate(CC_STD_ALLOCATOR);
                CCBigIntSet((CCBigInt)*Integer, Result);
            }
            
            return;
        }
    }
    
    CCBigIntSub((CCBigInt)*Integer, Value);
}

static inline void CCBigIntFastSubString(CCBigIntFast *Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(*Integer, "Integer must not point to null");
    
    if (CCBigIntFastIsTaggedValue(*Integer))
    {
        CCBigInt ValueB = CCBigIntCreate(CC_STD_ALLOCATOR);
        CCBigIntSet(ValueB, Value);
        CCBigIntFastSub(Integer, ValueB);
        CCBigIntDestroy(ValueB);
    }
    
    else CCBigIntSub((CCBigInt)*Integer, Value);
}

#pragma mark -

#define CC_TYPE_CCBigIntFast(...) CCBigIntFast
#define CC_TYPE_0_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_1_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_2_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_3_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_4_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_5_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_6_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_7_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_8_CCBigIntFast CC_TYPE_CCBigIntFast,
#define CC_TYPE_9_CCBigIntFast CC_TYPE_CCBigIntFast,

#define CC_PRESERVE_CC_TYPE_CCBigIntFast CC_TYPE_CCBigIntFast

#define CC_TYPE_DECL_CCBigIntFast(...) CCBigIntFast, __VA_ARGS__
#define CC_TYPE_DECL_0_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_1_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_2_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_3_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_4_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_5_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_6_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_7_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_8_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,
#define CC_TYPE_DECL_9_CCBigIntFast CC_TYPE_DECL_CCBigIntFast,

#define CC_MANGLE_TYPE_0_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_1_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_2_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_3_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_4_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_5_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_6_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_7_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_8_CCBigIntFast CCBigIntFast
#define CC_MANGLE_TYPE_9_CCBigIntFast CCBigIntFast

#endif
