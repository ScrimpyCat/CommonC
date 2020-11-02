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

#define CC_QUICK_COMPILE
#include "BigInt.h"
#include "BigIntFast.h"
#include "List.h"


static void CCBigIntDestructor(CCBigInt Ptr)
{
    CCListDestroy(Ptr->value);
}

CCBigInt CCBigIntCreate(CCAllocatorType Allocator)
{
    CCBigInt Integer = CCMalloc(Allocator, sizeof(CCBigIntInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Integer)
    {
        *Integer = (CCBigIntInfo){
            .sign = FALSE,
            .value = CCListCreate(Allocator, sizeof(uint64_t), 4, 16)
        };
        
        CCListAppendElement(Integer->value, &(uint64_t){ 0 });
        
        CCMemorySetDestructor(Integer, (CCMemoryDestructorCallback)CCBigIntDestructor);
    }
    
    
    return Integer;
}

void CCBigIntDestroy(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCFree(Integer);
}

void CCBigIntSetBigInt(CCBigInt Integer, CCBigInt Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(Value, "Value must not be null");
    
    Integer->sign = Value->sign;

    CCListRemoveAllElements(Integer->value);
    
    for (CCLinkedListNode *Node = Value->value->list; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Node);
        CCListAppendElements(Integer->value, CCArrayGetElementAtIndex(Array, 0), CCArrayGetCount(Array));
    }
}

void CCBigIntSetBigIntFast(CCBigInt Integer, CCBigIntFast Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(Value)) CCBigIntSet(Integer, CCBigIntFastGetTaggedValue(Value));
    else CCBigIntSet(Integer, (CCBigInt)Value);
}

void CCBigIntSetInt(CCBigInt Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CCListRemoveAllElements(Integer->value);
    
    const int64_t Mask = Value >> 63;
    
    Integer->sign = Mask;
    
    CCListAppendElement(Integer->value, &(uint64_t){ (Value ^ Mask) - Mask });
}

static uint64_t CCBigIntParseHex(const char *String, size_t Length)
{
    uint64_t Value = 0;
    for (size_t Loop = 0; Loop < Length; Loop++)
    {
        const char Chr = String[Loop];
        
        uint64_t Bits = 0;
        if ((Chr >= '0') && (Chr <= '9')) Bits = Chr - '0';
        else if ((Chr >= 'a') && (Chr <= 'f')) Bits = Chr - 'a' + 10;
        else if ((Chr >= 'A') && (Chr <= 'F')) Bits = Chr - 'A' + 10;
        else return Value;
        
        Value |= (Bits << ((Length - Loop - 1) * 4));
    }
    
    return Value;
}

static void CCBigIntParse(CCBigInt Integer, const char *String, size_t Length)
{
    CCAssertLog(String, "String must not be null");
    CCAssertLog(Length, "Length must not be 0");
    
    CCListRemoveAllElements(Integer->value);
    
    if (*String == '-')
    {
        Integer->sign = TRUE;
        String++;
        Length--;
    }
    
    else Integer->sign = FALSE;
    
    if ((Length > 2) && (String[0] == '0') && (String[1] == 'x'))
    {
        String += 2;
        Length -= 2;
        
        size_t Index = 0;
        const size_t ElementCount = Length / 16;
        for (size_t Loop = 0; Loop < ElementCount; Loop++)
        {
            Index = CCListAppendElement(Integer->value, &(uint64_t){ 0 });
        }
        
        _Bool NonZero = FALSE;
        const size_t Leftover = Length % 16;
        if (Leftover)
        {
            const uint64_t Value = CCBigIntParseHex(String, Leftover);
            if (Value)
            {
                CCListAppendElement(Integer->value, &Value);
                NonZero = TRUE;
            }
        }
        
        String += Leftover;
        
        size_t Loop = 0;
        for ( ; (!NonZero) && (Loop < ElementCount); Loop++, Index--)
        {
            const uint64_t Value = CCBigIntParseHex(String + (Loop * 16), 16);
            if (Value)
            {
                CCListReplaceElementAtIndex(Integer->value, Index, &Value);
                NonZero = TRUE;
            }
            
            else CCListRemoveElementAtIndex(Integer->value, Index);
        }
        
        for ( ; Loop < ElementCount; Loop++, Index--)
        {
            CCListReplaceElementAtIndex(Integer->value, Index, &(uint64_t){ CCBigIntParseHex(String + (Loop * 16), 16) });
        }
        
        if (!NonZero)
        {
            CCListAppendElement(Integer->value, &(uint64_t){ 0 });
            Integer->sign = FALSE;
        }
    }
    
    else CCAssertLog(0, "Unsupported big integer format");
}

void CCBigIntSetString(CCBigInt Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CC_STRING_TEMP_BUFFER(Buffer, Value)
    {
        CCBigIntParse(Integer, Buffer, CCStringGetSize(Value));
    }
}

CCString CCBigIntGetString(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    const size_t Count = CCListGetCount(Integer->value);
    
    char *String;
    CC_SAFE_Malloc(String, sizeof(char) * ((Count * 16) + 4),
                   return 0;
                   );
    
    size_t Index = 0;
    if (Integer->sign) String[Index++] = '-';
    String[Index++] = '0';
    String[Index++] = 'x';
    
    const char * const Hex = "0123456789abcdef";
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        const uint64_t Value = *(uint64_t*)CCListGetElementAtIndex(Integer->value, Count - Loop - 1);
        
        for (size_t Loop2 = 0; Loop2 < 16; Loop2++)
        {
            String[Index++] = Hex[(Value >> (60 - (Loop2 * 4))) & 0xf];
        }
    }
    
    String[Index] = 0;
    
    return CCStringCreateWithSize(CC_STD_ALLOCATOR, CCStringEncodingASCII | CCStringHintFree, String, Index);
}

static CCComparisonResult CCBigIntCompareComponents(CCBigInt a, size_t CountA, CCBigInt b, size_t CountB)
{
    if (CountA == CountB)
    {
        CCEnumerable EnumerableA, EnumerableB;
        CCListGetEnumerable(a->value, &EnumerableA);
        CCListGetEnumerable(b->value, &EnumerableB);
        
        for (const uint64_t *ComponentA = CCEnumerableGetTail(&EnumerableA), *ComponentB = CCEnumerableGetTail(&EnumerableB); ComponentA; ComponentA = CCEnumerablePrevious(&EnumerableA), ComponentB = CCEnumerablePrevious(&EnumerableB))
        {
            if (*ComponentA != *ComponentB)
            {
                return *ComponentA < *ComponentB ? CCComparisonResultAscending : CCComparisonResultDescending;
            }
        }
        
        return CCComparisonResultEqual;
    }
    
    return CountA < CountB ? CCComparisonResultAscending : CCComparisonResultDescending;
}

CCComparisonResult CCBigIntCompareBigInt(CCBigInt a, CCBigInt b)
{
    CCAssertLog(a, "a must not be null");
    CCAssertLog(b, "b must not be null");
    
    if (a == b) return CCComparisonResultEqual;
    
    if (a->sign != b->sign) return a->sign ? CCComparisonResultAscending : CCComparisonResultDescending;
    
    const CCComparisonResult Result = CCBigIntCompareComponents(a, CCListGetCount(a->value), b, CCListGetCount(b->value));
    
    return a->sign ? CCComparisonResultFlipOrder(Result) : Result;
}

CCComparisonResult CCBigIntCompareBigIntFast(CCBigInt a, CCBigIntFast b)
{
    if (CCBigIntFastIsTaggedValue(b)) return CCBigIntCompare(a, CCBigIntFastGetTaggedValue(b));
    
    return CCBigIntCompare(a, (CCBigInt)b);
}

CCComparisonResult CCBigIntCompareInt(CCBigInt Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CCBigInt IntegerB = CCBigIntCreate(CC_STD_ALLOCATOR);
    CCBigIntSet(IntegerB, Value);
    const CCComparisonResult Result = CCBigIntCompare(Integer, IntegerB);
    CCBigIntDestroy(IntegerB);
    
    return Result;
}

CCComparisonResult CCBigIntCompareString(CCBigInt Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CCBigInt IntegerB = CCBigIntCreate(CC_STD_ALLOCATOR);
    CCBigIntSet(IntegerB, Value);
    const CCComparisonResult Result = CCBigIntCompare(Integer, IntegerB);
    CCBigIntDestroy(IntegerB);
    
    return Result;
}

static void CCBigIntApplyAdd(CCBigInt Integer, CCEnumerable *Values)
{
    const uint64_t *Value = CCEnumerableGetCurrent(Values);
    uint64_t Carry = 0;
    
    CCEnumerable Enumerable;
    CCListGetEnumerable(Integer->value, &Enumerable);
    
    for (uint64_t *Component = CCEnumerableGetCurrent(&Enumerable); (Carry || Value) && Component; Component = CCEnumerableNext(&Enumerable), Value = CCEnumerableNext(Values))
    {
        const uint64_t Result = *Component + (Value ? *Value : 0) + Carry;
        Carry = (Result <= *Component) && ((Value ? *Value : 0) | Carry);
        *Component = Result;
    }
    
    for ( ; Value; Value = CCEnumerableNext(Values))
    {
        const uint64_t Result = *Value + Carry;
        Carry = (Result < *Value);
        CCListAppendElement(Integer->value, &Result);
    }
    
    if (Carry) CCListAppendElement(Integer->value, &Carry);
}

static void CCBigIntApplySub(CCBigInt Integer, CCEnumerable *Values)
{
    const uint64_t *Value = CCEnumerableGetCurrent(Values);
    uint64_t Carry = 0;
    
    CCEnumerable Enumerable;
    CCListGetEnumerable(Integer->value, &Enumerable);
    
    size_t LastNonZero = 0, Index = 0;
    for (uint64_t *Component = CCEnumerableGetCurrent(&Enumerable); (Carry || Value) && Component; Component = CCEnumerableNext(&Enumerable), Value = CCEnumerableNext(Values))
    {
        uint64_t Result = Value ? *Value : 0;
        const _Bool NextCarry = (*Component < Result) || (*Component < (Result + Carry)) || ((Carry) && (Result == UINT64_MAX));
        *Component = *Component - (Result + Carry);
        Carry = NextCarry;
        
        if (*Component) LastNonZero = Index;
        
        Index++;
    }
    
    CCAssertLog(!Value, "Values must not exceed size of Integer");
    
    for (size_t Loop = LastNonZero + 1, Count = CCListGetCount(Integer->value); Loop < Count; Loop++)
    {
        CCListRemoveElementAtIndex(Integer->value, Count - Loop);
    }
    
    if (Carry)
    {
        Integer->sign = !Integer->sign;
        uint64_t *Value = CCListGetElementAtIndex(Integer->value, 0);
        
        const int64_t Mask = *(int64_t*)Value >> 63;
        *Value = (*(int64_t*)Value ^ Mask) - Mask;
    }
}

void CCBigIntAddBigInt(CCBigInt Integer, CCBigInt Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(Value, "Value must not be null");
    
    CCEnumerable Enumerable;
    CCListGetEnumerable(Value->value, &Enumerable);
    
    if (Integer->sign == Value->sign) CCBigIntApplyAdd(Integer, &Enumerable);
    else if (CCBigIntCompareComponents(Integer, CCListGetCount(Integer->value), Value, CCListGetCount(Value->value)) != CCComparisonResultAscending) CCBigIntApplySub(Integer, &Enumerable);
    else
    {
        const _Bool OriginalSign = Integer->sign;
        CCList OriginalValue = Integer->value;
        CCListGetEnumerable(OriginalValue, &Enumerable);
        
        Integer->value = CCListCreate(CC_STD_ALLOCATOR, sizeof(uint64_t), 4, 16);
        CCBigIntSet(Integer, Value);
        
        CCBigIntApplySub(Integer, &Enumerable);
        CCListDestroy(OriginalValue);
        
        Integer->sign = !OriginalSign;
    }
}

void CCBigIntAddBigIntFast(CCBigInt Integer, CCBigIntFast Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(Value)) CCBigIntAdd(Integer, CCBigIntFastGetTaggedValue(Value));
    else CCBigIntAdd(Integer, (CCBigInt)Value);
}

void CCBigIntAddInt(CCBigInt Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    const int64_t Mask = Value >> 63;
    uint64_t AbsValue = (Value ^ Mask) - Mask;
    
    CCEnumerable Enumerable = CCEnumerableCreate(&AbsValue, sizeof(typeof(AbsValue)), 1);
    
    if (Integer->sign == (_Bool)Mask) CCBigIntApplyAdd(Integer, &Enumerable);
    else CCBigIntApplySub(Integer, &Enumerable);
}

void CCBigIntAddString(CCBigInt Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CCBigInt Source = CCBigIntCreate(CC_STD_ALLOCATOR);
    CCBigIntSet(Source, Value);
    CCBigIntAdd(Integer, Source);
    CCBigIntDestroy(Source);
}

void CCBigIntSubBigInt(CCBigInt Integer, CCBigInt Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(Value, "Value must not be null");
    
    CCEnumerable Enumerable;
    CCListGetEnumerable(Value->value, &Enumerable);
    
    if (Integer->sign != Value->sign) CCBigIntApplyAdd(Integer, &Enumerable);
    else if (CCBigIntCompareComponents(Integer, CCListGetCount(Integer->value), Value, CCListGetCount(Value->value)) != CCComparisonResultAscending) CCBigIntApplySub(Integer, &Enumerable);
    else
    {
        const _Bool OriginalSign = Integer->sign;
        CCList OriginalValue = Integer->value;
        CCListGetEnumerable(OriginalValue, &Enumerable);
        
        Integer->value = CCListCreate(CC_STD_ALLOCATOR, sizeof(uint64_t), 4, 16);
        CCBigIntSet(Integer, Value);
        
        CCBigIntApplySub(Integer, &Enumerable);
        CCListDestroy(OriginalValue);
        
        Integer->sign = !OriginalSign;
    }
}

void CCBigIntSubBigIntFast(CCBigInt Integer, CCBigIntFast Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCAssertLog(Value, "Value must not be null");
    
    if (CCBigIntFastIsTaggedValue(Value)) CCBigIntSub(Integer, CCBigIntFastGetTaggedValue(Value));
    else CCBigIntSub(Integer, (CCBigInt)Value);
}

void CCBigIntSubInt(CCBigInt Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    const int64_t Mask = Value >> 63;
    uint64_t AbsValue = (Value ^ Mask) - Mask;
    
    CCEnumerable Enumerable = CCEnumerableCreate(&AbsValue, sizeof(typeof(AbsValue)), 1);
    
    if (Integer->sign != (_Bool)Mask) CCBigIntApplyAdd(Integer, &Enumerable);
    else CCBigIntApplySub(Integer, &Enumerable);
}

void CCBigIntSubString(CCBigInt Integer, CCString Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CCBigInt Source = CCBigIntCreate(CC_STD_ALLOCATOR);
    CCBigIntSet(Source, Value);
    CCBigIntSub(Integer, Source);
    CCBigIntDestroy(Source);
}
