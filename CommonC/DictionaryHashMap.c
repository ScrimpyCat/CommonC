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

#include "DictionaryHashMap.h"
#include "HashMap.h"
#include "HashMapSeparateChainingArray.h"

static int CCDictionaryHashMapHintWeight(CCDictionaryHint Hint);
static void *CCDictionaryHashMapConstructor(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator);
static CCDictionaryEntry CCDictionaryHashMapFindKey(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator);
static CCDictionaryEntry CCDictionaryHashMapEntryForKey(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator);
static void CCDictionaryHashMapSetEntry(CCHashMap Internal, CCDictionaryEntry Entry, void *Value, size_t ValueSize, CCAllocatorType Allocator);
static void CCDictionaryHashMapRemoveEntry(CCHashMap Internal, CCDictionaryEntry Entry, CCAllocatorType Allocator);
static void *CCDictionaryHashMapEnumerator(CCHashMap Internal, CCEnumeratorState *Enumerator, CCDictionaryEnumeratorAction Action, CCDictionaryEnumeratorType Type);
static CCDictionaryEntry CCDictionaryHashMapEnumeratorEntry(CCHashMap Internal, CCEnumeratorState *Enumerator, CCDictionaryEnumeratorType Type);
static void *CCDictionaryHashMapGetValue(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator);
static void CCDictionaryHashMapSetValue(CCHashMap Internal, void *Key, void *Value, size_t KeySize, size_t ValueSize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator);
static void CCDictionaryHashMapRemoveValue(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator);
static CCOrderedCollection CCDictionaryHashMapGetKeys(CCHashMap Internal, CCAllocatorType Allocator);
static CCOrderedCollection CCDictionaryHashMapGetValues(CCHashMap Internal, CCAllocatorType Allocator);


CCDictionaryInterface CCDictionaryHashMapInterface = {
    .hintWeight = CCDictionaryHashMapHintWeight,
    .create = CCDictionaryHashMapConstructor,
    .destroy = (CCDictionaryDestructorCallback)CCHashMapDestroy,
    .count = (CCDictionaryGetCountCallback)CCHashMapGetCount,
    .initialized = (CCDictionaryEntryIsInitializedCallback)CCHashMapEntryIsInitialized,
    .findKey = (CCDictionaryFindKeyCallback)CCDictionaryHashMapFindKey,
    .entryForKey = (CCDictionaryEntryForKeyCallback)CCDictionaryHashMapEntryForKey,
    .getKey = (CCDictionaryGetKeyCallback)CCHashMapGetKey,
    .getEntry = (CCDictionaryGetEntryCallback)CCHashMapGetEntry,
    .setEntry = (CCDictionarySetEntryCallback)CCDictionaryHashMapSetEntry,
    .removeEntry = (CCDictionaryRemoveEntryCallback)CCDictionaryHashMapRemoveEntry,
    .enumerator = NULL,
    .enumeratorReference = NULL,
    .optional = {
        .getValue = (CCDictionaryGetValueCallback)CCDictionaryHashMapGetValue,
        .setValue = (CCDictionarySetValueCallback)CCDictionaryHashMapSetValue,
        .removeValue = (CCDictionaryRemoveValueCallback)CCDictionaryHashMapRemoveValue,
        .keys = (CCDictionaryGetKeysCallback)CCDictionaryHashMapGetKeys,
        .values = (CCDictionaryGetValuesCallback)CCDictionaryHashMapGetValues
    }
};

const CCDictionaryInterface * const CCDictionaryHashMap = &CCDictionaryHashMapInterface;


//Values from http://planetmath.org/sites/default/files/texpdf/33327.pdf or http://planetmath.org/goodhashtableprimes and https://opensource.apple.com/source/CF/CF-1153.18/CFBasicHash.c
static const size_t BucketSizes[40] = {
//    3, 7, 13, 23, 37, 53, 97, 193,
//    389, 769, 1543, 3079, 6151, 12289, 24593, 49157,
//    98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
//    25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741, 3241355263,
//    5244622819, 8485977589, 13730600407, 22216578047, 35947178479, 58163756537, 94110934997, 152274691561
    3, 6, 11, 19, 32, 52, 85, 118,
    155, 237, 390, 672, 1065, 1732, 2795, 4543,
    7391, 12019, 19302, 31324, 50629, 81956, 132580, 214215,
    346784, 561026, 907847, 1468567, 2376414, 3844982, 6221390, 10066379,
    16287773, 26354132, 42641916, 68996399, 111638327, 180634415, 292272755, 472907503
};

static int CCDictionaryHashMapHintWeight(CCDictionaryHint Hint)
{
    return CCDictionaryHintWeightCreate(Hint,
                                        CCDictionaryHintHeavyFinding
                                        | CCDictionaryHintHeavyInserting
                                        | CCDictionaryHintConstantLength
                                        | CCDictionaryHintConstantElements
                                        | CCDictionaryHintHeavyDeleting,
                                        CCDictionaryHintHeavyEnumerating,
                                        0);
}

static void *CCDictionaryHashMapConstructor(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator)
{
    _Static_assert(CCDictionaryEnumeratorActionHead == CCHashMapEnumeratorActionHead &&
                   CCDictionaryEnumeratorActionTail == CCHashMapEnumeratorActionTail &&
                   CCDictionaryEnumeratorActionNext == CCHashMapEnumeratorActionNext &&
                   CCDictionaryEnumeratorActionPrevious == CCHashMapEnumeratorActionPrevious &&
                   CCDictionaryEnumeratorActionCurrent == CCHashMapEnumeratorActionCurrent &&
                   CCDictionaryEnumeratorTypeKey == CCHashMapEnumeratorTypeKey &&
                   CCDictionaryEnumeratorTypeValue == CCHashMapEnumeratorTypeValue, "Must match if we're doing a passthrough");
    
    CCDictionaryHashMapInterface.enumerator = (CCDictionaryEnumeratorCallback)CCHashMapSeparateChainingArray->enumerator;
    CCDictionaryHashMapInterface.enumeratorReference = (CCDictionaryEnumeratorEntryCallback)CCHashMapSeparateChainingArray->enumeratorReference;
    
    size_t BucketCount = 0;
    switch ((Hint & CCDictionaryHintSizeMask))
    {
        case CCDictionaryHintSizeSmall:
            BucketCount = BucketSizes[0];
            break;
            
        case CCDictionaryHintSizeMedium:
            BucketCount = BucketSizes[7];
            break;
            
        case CCDictionaryHintSizeLarge:
            BucketCount = BucketSizes[12];
            break;
    }
    
    return CCHashMapCreate(Allocator, KeySize, ValueSize, BucketCount, Hasher, KeyComparator, CCHashMapSeparateChainingArray);
}

static CCDictionaryEntry CCDictionaryHashMapFindKey(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator)
{
    return CCHashMapFindKey(Internal, Key);
}

static CCDictionaryEntry CCDictionaryHashMapEntryForKey(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator)
{
    if (CCHashMapGetLoadFactor(Internal) >= 0.75f)
    {
        size_t Count = CCHashMapGetBucketCount(Internal);
        for (size_t Loop = 0; Loop < sizeof(BucketSizes) / sizeof(size_t); Loop++)
        {
            if (BucketSizes[Loop] > Count)
            {
                Count = BucketSizes[Loop];
                break;
            }
        }
        
        CCHashMapRehash(Internal, Count);
    }
    
    return CCHashMapEntryForKey(Internal, Key, NULL);
}

static void CCDictionaryHashMapSetEntry(CCHashMap Internal, CCDictionaryEntry Entry, void *Value, size_t ValueSize, CCAllocatorType Allocator)
{
    CCHashMapSetEntry(Internal, Entry, Value);
}

static void CCDictionaryHashMapRemoveEntry(CCHashMap Internal, CCDictionaryEntry Entry, CCAllocatorType Allocator)
{
    CCHashMapRemoveEntry(Internal, Entry);
}

static void *CCDictionaryHashMapGetValue(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator)
{
    return CCHashMapGetValue(Internal, Key);
}

static void CCDictionaryHashMapSetValue(CCHashMap Internal, void *Key, void *Value, size_t KeySize, size_t ValueSize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator)
{
    if (CCHashMapGetLoadFactor(Internal) >= 0.75f)
    {
        size_t Count = CCHashMapGetBucketCount(Internal);
        for (size_t Loop = 0; Loop < sizeof(BucketSizes) / sizeof(size_t); Loop++)
        {
            if (BucketSizes[Loop] > Count)
            {
                Count = BucketSizes[Loop];
                break;
            }
        }
        
        CCHashMapRehash(Internal, Count);
    }
    
    CCHashMapSetValue(Internal, Key, Value);
}

static void CCDictionaryHashMapRemoveValue(CCHashMap Internal, void *Key, size_t KeySize, CCDictionaryKeyHasher Hasher, CCComparator KeyComparator, CCAllocatorType Allocator)
{
    CCHashMapRemoveValue(Internal, Key);
}

static CCOrderedCollection CCDictionaryHashMapGetKeys(CCHashMap Internal, CCAllocatorType Allocator)
{
    return CCHashMapGetKeys(Internal);
}

static CCOrderedCollection CCDictionaryHashMapGetValues(CCHashMap Internal, CCAllocatorType Allocator)
{
    return CCHashMapGetValues(Internal);
}
