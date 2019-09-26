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
        
        CCMemorySetDestructor(Integer, (CCMemoryDestructorCallback)CCBigIntDestructor);
    }
    
    
    return Integer;
}

void CCBigIntDestroy(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    CCFree(Integer);
}

uint64_t CCBigIntGetComponent(CCBigInt Integer, size_t Index)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return *(uint64_t*)CCListGetElementAtIndex(Integer->value, Index);
}

size_t CCBigIntGetComponentCount(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return CCListGetCount(Integer->value);
}

_Bool CCBigIntGetSign(CCBigInt Integer)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    return Integer->sign;
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

void CCBigIntSetInt(CCBigInt Integer, int64_t Value)
{
    CCAssertLog(Integer, "Integer must not be null");
    
    CCListRemoveAllElements(Integer->value);
    
    Integer->sign = Value >> 63;
    
    CCListAppendElement(Integer->value, &(uint64_t){ (Value ^ Integer->sign) - Value });
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
        
        const size_t Leftover = Length % 16;
        if (Leftover)
        {
            CCListAppendElement(Integer->value, &(uint64_t){ CCBigIntParseHex(String, Leftover) });
        }
        
        String += Leftover;
        
        for (size_t Loop = 0; Loop < ElementCount; Loop++, Index--)
        {
            CCListReplaceElementAtIndex(Integer->value, Index, &(uint64_t){ CCBigIntParseHex(String + (Loop * 16), 16) });
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
