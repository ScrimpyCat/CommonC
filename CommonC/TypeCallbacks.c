/*
 *  Copyright (c) 2016, Stefan Johnson
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
#include "TypeCallbacks.h"

#pragma mark Destructors

void CCGenericContainerElementDestructor(void *Container, void **Element);
void CCStringContainerElementDestructor(void *Container, CCString *Element);
void CCDataContainerElementDestructor(void *Container, CCData *Element);
void CCArrayContainerElementDestructor(void *Container, CCArray *Element);
void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element);
void CCListContainerElementDestructor(void *Container, CCList *Element);
void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element);
void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element);
void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element);
void CCQueueContainerElementDestructor(void *Container, CCQueue *Element);
void FSPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element);
void FSPathContainerElementDestructor(void *Container, FSPath *Element);
void FSHandleContainerElementDestructor(void *Container, FSHandle *Element);
void CCBigIntContainerElementDestructor(void *Container, CCBigInt *Element);
void CCBigIntFastContainerElementDestructor(void *Container, CCBigIntFast *Element);

#pragma mark Hashers

uintmax_t CCStringHasher(CCString *Key);
uintmax_t CCBigIntHasher(CCBigInt *Key);
uintmax_t CCBigIntFastHasher(CCBigIntFast *Key);
uintmax_t CCBigIntLowHasher(CCBigInt *Key);
uintmax_t CCBigIntFastLowHasher(CCBigIntFast *Key);

#pragma mark Comparators

CCComparisonResult CCStringComparator(CCString *Left, CCString *Right);
CCComparisonResult CCBigIntComparator(CCBigInt *Left, CCBigInt *Right);
CCComparisonResult CCBigIntFastComparator(CCBigIntFast *Left, CCBigIntFast *Right);

#pragma mark -

void CCGenericContainerElementDestructor(void *Container, void **Element)
{
    CCFree(*Element);
}

void CCStringContainerElementDestructor(void *Container, CCString *Element)
{
    CCStringDestroy(*Element);
}

void CCDataContainerElementDestructor(void *Container, CCData *Element)
{
    CCDataDestroy(*Element);
}

void CCArrayContainerElementDestructor(void *Container, CCArray *Element)
{
    CCArrayDestroy(*Element);
}

void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element)
{
    CCLinkedListDestroy(*Element);
}

void CCListContainerElementDestructor(void *Container, CCList *Element)
{
    CCListDestroy(*Element);
}

void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element)
{
    CCCollectionDestroy(*Element);
}

void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element)
{
    CCHashMapDestroy(*Element);
}

void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element)
{
    CCDictionaryDestroy(*Element);
}

void CCQueueContainerElementDestructor(void *Container, CCQueue *Element)
{
    CCQueueDestroy(*Element);
}

void FSPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element)
{
    FSPathComponentDestroy(*Element);
}

void FSPathContainerElementDestructor(void *Container, FSPath *Element)
{
    FSPathDestroy(*Element);
}

void FSHandleContainerElementDestructor(void *Container, FSHandle *Element)
{
    FSHandleClose(*Element);
}

void CCBigIntContainerElementDestructor(void *Container, CCBigInt *Element)
{
    CCBigIntDestroy(*Element);
}

void CCBigIntFastContainerElementDestructor(void *Container, CCBigIntFast *Element)
{
    CCBigIntFastDestroy(*Element);
}

uintmax_t CCStringHasher(CCString *Key)
{
    return CCStringGetHash(*Key);
}

uintmax_t CCBigIntHasher(CCBigInt *Key)
{
    CCEnumerable Enumerable;
    CCListGetEnumerable((*Key)->value, &Enumerable);
    
    uintmax_t Hash = 0;
    for (uint64_t *Component = CCEnumerableGetCurrent(&Enumerable); Component; Component = CCEnumerableNext(&Enumerable))
    {
        Hash ^= *Component;
    }
    
    return Hash | ((uint64_t)CCBigIntGetSign(*Key) << 63);
}

uintmax_t CCBigIntFastHasher(CCBigIntFast *Key)
{
    if (CCBigIntFastIsTaggedValue(*Key))
    {
        const int64_t Value = CCBigIntFastGetTaggedValue(*Key);
        const int64_t Mask = Value >> 63;
        
        const uint64_t Hash = (Value ^ Mask) - Mask;
        
        return Hash | ((uint64_t)CCBigIntFastGetSign(*Key) << 63);
    }
    
    return CCBigIntHasher((CCBigInt*)Key);
}

uintmax_t CCBigIntLowHasher(CCBigInt *Key)
{
    return CCBigIntGetComponent(*Key, 0) | ((uint64_t)CCBigIntGetSign(*Key) << 63);
}

uintmax_t CCBigIntFastLowHasher(CCBigIntFast *Key)
{
    if (CCBigIntFastIsTaggedValue(*Key))
    {
        const int64_t Value = CCBigIntFastGetTaggedValue(*Key);
        const int64_t Mask = Value >> 63;
        
        const uint64_t Hash = (Value ^ Mask) - Mask;
        
        return Hash | ((uint64_t)CCBigIntFastGetSign(*Key) << 63);
    }
    
    return CCBigIntLowHasher((CCBigInt*)Key);
}

CCComparisonResult CCStringComparator(CCString *Left, CCString *Right)
{
    return CCStringEqual(*Left, *Right) ? CCComparisonResultEqual : CCComparisonResultInvalid;
}

CCComparisonResult CCBigIntComparator(CCBigInt *Left, CCBigInt *Right)
{
    return CCBigIntCompare(*Left, *Right);
}

CCComparisonResult CCBigIntFastComparator(CCBigIntFast *Left, CCBigIntFast *Right)
{
    return CCBigIntFastCompare(*Left, *Right);
}
