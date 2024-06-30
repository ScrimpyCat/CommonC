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
#include "CCString.h"
#include "Data.h"
#include "Path.h"
#include "Array.h"
#include "LinkedList.h"
#include "List.h"
#include "HashMap.h"
#include "Queue.h"
#include "FileHandle.h"
#include "BigInt.h"
#include "BigIntFast.h"

#pragma mark Destructors

static void CCGenericContainerElementDestructor(void *Container, void **Element);
static void CCStringContainerElementDestructor(void *Container, CCString *Element);
static void CCDataContainerElementDestructor(void *Container, CCData *Element);
static void CCArrayContainerElementDestructor(void *Container, CCArray *Element);
static void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element);
static void CCListContainerElementDestructor(void *Container, CCList *Element);
static void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element);
static void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element);
static void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element);
static void CCQueueContainerElementDestructor(void *Container, CCQueue *Element);
static void FSPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element);
static void FSPathContainerElementDestructor(void *Container, FSPath *Element);
static void FSHandleContainerElementDestructor(void *Container, FSHandle *Element);
static void CCBigIntContainerElementDestructor(void *Container, CCBigInt *Element);
static void CCBigIntFastContainerElementDestructor(void *Container, CCBigIntFast *Element);

#pragma mark Hashers

static uintmax_t CCStringHasher(CCString *Key);
static uintmax_t CCBigIntHasher(CCBigInt *Key);
static uintmax_t CCBigIntFastHasher(CCBigIntFast *Key);
static uintmax_t CCBigIntLowHasher(CCBigInt *Key);
static uintmax_t CCBigIntFastLowHasher(CCBigIntFast *Key);

#pragma mark Comparators

static CCComparisonResult CCStringComparator(CCString *Left, CCString *Right);
static CCComparisonResult CCBigIntComparator(CCBigInt *Left, CCBigInt *Right);
static CCComparisonResult CCBigIntFastComparator(CCBigIntFast *Left, CCBigIntFast *Right);

#pragma mark - Collection Callbacks
#pragma mark Destructors

const CCCollectionElementDestructor CCGenericDestructorForCollection = (CCCollectionElementDestructor)CCGenericContainerElementDestructor;
const CCCollectionElementDestructor CCStringDestructorForCollection = (CCCollectionElementDestructor)CCStringContainerElementDestructor;
const CCCollectionElementDestructor CCDataDestructorForCollection = (CCCollectionElementDestructor)CCDataContainerElementDestructor;
const CCCollectionElementDestructor CCArrayDestructorForCollection = (CCCollectionElementDestructor)CCArrayContainerElementDestructor;
const CCCollectionElementDestructor CCLinkedListDestructorForCollection = (CCCollectionElementDestructor)CCLinkedListContainerElementDestructor;
const CCCollectionElementDestructor CCListDestructorForCollection = (CCCollectionElementDestructor)CCListContainerElementDestructor;
const CCCollectionElementDestructor CCCollectionDestructorForCollection = (CCCollectionElementDestructor)CCCollectionContainerElementDestructor;
const CCCollectionElementDestructor CCHashMapDestructorForCollection = (CCCollectionElementDestructor)CCHashMapContainerElementDestructor;
const CCCollectionElementDestructor CCDictionaryDestructorForCollection = (CCCollectionElementDestructor)CCDictionaryContainerElementDestructor;
const CCCollectionElementDestructor CCQueueDestructorForCollection = (CCCollectionElementDestructor)CCQueueContainerElementDestructor;
const CCCollectionElementDestructor FSPathComponentDestructorForCollection = (CCCollectionElementDestructor)FSPathComponentContainerElementDestructor;
const CCCollectionElementDestructor FSPathDestructorForCollection = (CCCollectionElementDestructor)FSPathContainerElementDestructor;
const CCCollectionElementDestructor FSHandleDestructorForCollection = (CCCollectionElementDestructor)FSHandleContainerElementDestructor;
const CCCollectionElementDestructor CCBigIntDestructorForCollection = (CCCollectionElementDestructor)CCBigIntContainerElementDestructor;
const CCCollectionElementDestructor CCBigIntFastDestructorForCollection = (CCCollectionElementDestructor)CCBigIntFastContainerElementDestructor;

#pragma mark Comparators

const CCComparator CCStringComparatorForCollection = (CCComparator)CCStringComparator;
const CCComparator CCBigIntComparatorForCollection = (CCComparator)CCBigIntComparator;
const CCComparator CCBigIntFastComparatorForCollection = (CCComparator)CCBigIntFastComparator;

#pragma mark - Dictionary Callbacks
#pragma mark Destructors

const CCDictionaryElementDestructor CCGenericDestructorForDictionary = (CCDictionaryElementDestructor)CCGenericContainerElementDestructor;
const CCDictionaryElementDestructor CCStringDestructorForDictionary = (CCDictionaryElementDestructor)CCStringContainerElementDestructor;
const CCDictionaryElementDestructor CCDataDestructorForDictionary = (CCDictionaryElementDestructor)CCDataContainerElementDestructor;
const CCDictionaryElementDestructor CCArrayDestructorForDictionary = (CCDictionaryElementDestructor)CCArrayContainerElementDestructor;
const CCDictionaryElementDestructor CCLinkedListDestructorForDictionary = (CCDictionaryElementDestructor)CCLinkedListContainerElementDestructor;
const CCDictionaryElementDestructor CCListDestructorForDictionary = (CCDictionaryElementDestructor)CCListContainerElementDestructor;
const CCDictionaryElementDestructor CCCollectionDestructorForDictionary = (CCDictionaryElementDestructor)CCCollectionContainerElementDestructor;
const CCDictionaryElementDestructor CCHashMapDestructorForDictionary = (CCDictionaryElementDestructor)CCHashMapContainerElementDestructor;
const CCDictionaryElementDestructor CCDictionaryDestructorForDictionary = (CCDictionaryElementDestructor)CCDictionaryContainerElementDestructor;
const CCDictionaryElementDestructor CCQueueDestructorForDictionary = (CCDictionaryElementDestructor)CCQueueContainerElementDestructor;
const CCDictionaryElementDestructor FSPathComponentDestructorForDictionary = (CCDictionaryElementDestructor)FSPathComponentContainerElementDestructor;
const CCDictionaryElementDestructor FSPathDestructorForDictionary = (CCDictionaryElementDestructor)FSPathContainerElementDestructor;
const CCDictionaryElementDestructor FSHandleDestructorForDictionary = (CCDictionaryElementDestructor)FSHandleContainerElementDestructor;
const CCDictionaryElementDestructor CCBigIntDestructorForDictionary = (CCDictionaryElementDestructor)CCBigIntContainerElementDestructor;
const CCDictionaryElementDestructor CCBigIntFastDestructorForDictionary = (CCDictionaryElementDestructor)CCBigIntFastContainerElementDestructor;

#pragma mark Hashers

const CCDictionaryKeyHasher CCStringHasherForDictionary = (CCDictionaryKeyHasher)CCStringHasher;
const CCDictionaryKeyHasher CCBigIntHasherForDictionary = (CCDictionaryKeyHasher)CCBigIntHasher;
const CCDictionaryKeyHasher CCBigIntFastHasherForDictionary = (CCDictionaryKeyHasher)CCBigIntFastHasher;
const CCDictionaryKeyHasher CCBigIntLowHasherForDictionary = (CCDictionaryKeyHasher)CCBigIntLowHasher;
const CCDictionaryKeyHasher CCBigIntFastLowHasherForDictionary = (CCDictionaryKeyHasher)CCBigIntFastLowHasher;

#pragma mark Comparators

const CCComparator CCStringComparatorForDictionary = (CCComparator)CCStringComparator;
const CCComparator CCBigIntComparatorForDictionary = (CCComparator)CCBigIntComparator;
const CCComparator CCBigIntFastComparatorForDictionary = (CCComparator)CCBigIntFastComparator;

#pragma mark -

static void CCGenericContainerElementDestructor(void *Container, void **Element)
{
    CCFree(*Element);
}

static void CCStringContainerElementDestructor(void *Container, CCString *Element)
{
    CCStringDestroy(*Element);
}

static void CCDataContainerElementDestructor(void *Container, CCData *Element)
{
    CCDataDestroy(*Element);
}

static void CCArrayContainerElementDestructor(void *Container, CCArray *Element)
{
    CCArrayDestroy(*Element);
}

static void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element)
{
    CCLinkedListDestroy(*Element);
}

static void CCListContainerElementDestructor(void *Container, CCList *Element)
{
    CCListDestroy(*Element);
}

static void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element)
{
    CCCollectionDestroy(*Element);
}

static void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element)
{
    CCHashMapDestroy(*Element);
}

static void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element)
{
    CCDictionaryDestroy(*Element);
}

static void CCQueueContainerElementDestructor(void *Container, CCQueue *Element)
{
    CCQueueDestroy(*Element);
}

static void FSPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element)
{
    FSPathComponentDestroy(*Element);
}

static void FSPathContainerElementDestructor(void *Container, FSPath *Element)
{
    FSPathDestroy(*Element);
}

static void FSHandleContainerElementDestructor(void *Container, FSHandle *Element)
{
    FSHandleClose(*Element);
}

static void CCBigIntContainerElementDestructor(void *Container, CCBigInt *Element)
{
    CCBigIntDestroy(*Element);
}

static void CCBigIntFastContainerElementDestructor(void *Container, CCBigIntFast *Element)
{
    CCBigIntFastDestroy(*Element);
}

static uintmax_t CCStringHasher(CCString *Key)
{
    return CCStringGetHash(*Key);
}

static uintmax_t CCBigIntHasher(CCBigInt *Key)
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

static uintmax_t CCBigIntFastHasher(CCBigIntFast *Key)
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

static uintmax_t CCBigIntLowHasher(CCBigInt *Key)
{
    return CCBigIntGetComponent(*Key, 0) | ((uint64_t)CCBigIntGetSign(*Key) << 63);
}

static uintmax_t CCBigIntFastLowHasher(CCBigIntFast *Key)
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

static CCComparisonResult CCStringComparator(CCString *Left, CCString *Right)
{
    return CCStringEqual(*Left, *Right) ? CCComparisonResultEqual : CCComparisonResultInvalid;
}

static CCComparisonResult CCBigIntComparator(CCBigInt *Left, CCBigInt *Right)
{
    return CCBigIntCompare(*Left, *Right);
}

static CCComparisonResult CCBigIntFastComparator(CCBigIntFast *Left, CCBigIntFast *Right)
{
    return CCBigIntFastCompare(*Left, *Right);
}
