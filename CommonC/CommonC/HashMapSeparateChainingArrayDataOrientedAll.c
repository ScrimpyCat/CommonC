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

#include "CCHashMapSeparateChainingArrayDataOrientedAll.h"
#include "HashMap.h"
#include "MemoryAllocation.h"
#include "Array.h"
#include "BitTricks.h"
#include "Logging.h"


typedef struct {
    CCArray hashes;
    CCArray keys;
    CCArray values;
} CCHashMapSeparateChainingArrayDataOrientedAllInternal;

static void *CCHashMapSeparateChainingArrayDataOrientedAllConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount);
static void CCHashMapSeparateChainingArrayDataOrientedAllDestructor(CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal);
static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllFindKey(CCHashMap Map, void *Key);
static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllEntryForKey(CCHashMap Map, void *Key, _Bool *Created);
static void *CCHashMapSeparateChainingArrayDataOrientedAllGetEntry(CCHashMap Map, CCHashMapEntry Entry);
static void CCHashMapSeparateChainingArrayDataOrientedAllSetEntry(CCHashMap Map, CCHashMapEntry Entry, void *Value);
static void CCHashMapSeparateChainingArrayDataOrientedAllRemoveEntry(CCHashMap Map, CCHashMapEntry Entry);
static void *CCHashMapSeparateChainingArrayDataOrientedAllGetValue(CCHashMap Map, void *Key);
static void CCHashMapSeparateChainingArrayDataOrientedAllSetValue(CCHashMap Map, void *Key, void *Value);
static void CCHashMapSeparateChainingArrayDataOrientedAllRemoveValue(CCHashMap Map, void *Key);


const CCHashMapInterface CCHashMapSeparateChainingArrayDataOrientedAllInterface = {
    .create = CCHashMapSeparateChainingArrayDataOrientedAllConstructor,
    .destroy = (CCHashMapDestructorCallback)CCHashMapSeparateChainingArrayDataOrientedAllDestructor,
    .findKey = CCHashMapSeparateChainingArrayDataOrientedAllFindKey,
    .entryForKey = CCHashMapSeparateChainingArrayDataOrientedAllEntryForKey,
    .getEntry = CCHashMapSeparateChainingArrayDataOrientedAllGetEntry,
    .setEntry = CCHashMapSeparateChainingArrayDataOrientedAllSetEntry,
    .removeEntry = CCHashMapSeparateChainingArrayDataOrientedAllRemoveEntry,
    .optional = {
        .getValue = CCHashMapSeparateChainingArrayDataOrientedAllGetValue,
        .setValue = CCHashMapSeparateChainingArrayDataOrientedAllSetValue,
        .removeValue = CCHashMapSeparateChainingArrayDataOrientedAllRemoveValue
    }
};

const CCHashMapInterface * const CCHashMapSeparateChainingArrayDataOrientedAll = &CCHashMapSeparateChainingArrayDataOrientedAllInterface;


static void *CCHashMapSeparateChainingArrayDataOrientedAllConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount)
{
    CCHashMapSeparateChainingArrayDataOrientedAllInternal *Map = CCMalloc(Allocator, sizeof(CCHashMapSeparateChainingArrayDataOrientedAllInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Map)
    {
        *Map = (CCHashMapSeparateChainingArrayDataOrientedAllInternal){
            .hashes = NULL,
            .keys = NULL,
            .values = NULL
        };
    }
    
    return Map;
}

static void CCHashMapSeparateChainingArrayDataOrientedAllBucketDestroy(CCArray Buckets)
{
    for (size_t Loop = 0, Count = CCArrayGetCount(Buckets); Loop < Count; Loop++)
    {
        CCArray Bkt = *(CCArray*)CCArrayGetElementAtIndex(Buckets, Loop);
        if (Bkt) CCArrayDestroy(Bkt);
    }
    
    CCArrayDestroy(Buckets);
}

static void CCHashMapSeparateChainingArrayDataOrientedAllDestructor(CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal)
{
    if (Internal->hashes) CCHashMapSeparateChainingArrayDataOrientedAllBucketDestroy(Internal->hashes);
    if (Internal->keys) CCHashMapSeparateChainingArrayDataOrientedAllBucketDestroy(Internal->keys);
    if (Internal->values) CCHashMapSeparateChainingArrayDataOrientedAllBucketDestroy(Internal->values);
}

static _Bool CCHashMapSeparateChainingArrayDataOrientedAllGetKey(CCHashMap Map, void *Key, uintmax_t *HashValue, size_t *BucketIndex, size_t *ItemIndex)
{
    const uintmax_t Hash = CCHashMapGetKeyHash(Map, Key);
    const size_t Index = Hash % Map->bucketCount;
    
    if (HashValue) *HashValue = Hash;
    *BucketIndex = Index;
    
    const CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
    
    if (Internal->hashes)
    {
        CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Index);
        if (HashBucket)
        {
            for (size_t Loop = 0, Count = CCArrayGetCount(HashBucket); Loop < Count; Loop++)
            {
                const uintmax_t EntryHash = *(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop);
                if (Hash == EntryHash)
                {
                    const void *EntryKey = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->keys, Index), Loop);
                    if (Map->compareKeys)
                    {
                        if (Map->compareKeys(Key, EntryKey) == CCComparisonResultEqual)
                        {
                            *ItemIndex = Loop;
                            return TRUE;
                        }
                    }
                    
                    else if (!memcmp(Key, EntryKey, Map->keySize))
                    {
                        *ItemIndex = Loop;
                        return TRUE;
                    }
                }
            }
        }
    }
    
    else if (Internal->keys)
    {
        CCArray KeyBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->keys, Index);
        if (KeyBucket)
        {
            for (size_t Loop = 0, Count = CCArrayGetCount(KeyBucket); Loop < Count; Loop++)
            {
                const void *EntryKey = CCArrayGetElementAtIndex(KeyBucket, Loop);
                if (Map->compareKeys)
                {
                    if (Map->compareKeys(Key, EntryKey) == CCComparisonResultEqual)
                    {
                        *ItemIndex = Loop;
                        return TRUE;
                    }
                }
                
                else if (!memcmp(Key, EntryKey, Map->keySize))
                {
                    *ItemIndex = Loop;
                    return TRUE;
                }
            }
        }
    }
    
    return FALSE;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllIndexToEntry(CCHashMap Map, size_t BucketIndex, size_t ItemIndex)
{
    const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
    const uintmax_t ItemMask = ~BucketMask;
    
    if ((ItemIndex & ItemMask) == ItemIndex)
    {
        return (ItemIndex << CCBitCountSet(BucketMask)) | (BucketIndex + 1);
    }
    
    CC_LOG_WARNING("HashMap bucket size (%zu, %zu) exceeds representable threshold for an entry reference", Map->bucketCount, CCArrayGetCount(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex)));
    
    return 0;
}

static _Bool CCHashMapSeparateChainingArrayDataOrientedAllEntryToIndex(CCHashMap Map, CCHashMapEntry Entry, size_t *BucketIndex, size_t *ItemIndex)
{
    if (Entry)
    {
        const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
        const uintmax_t ItemMask = ~BucketMask;
        
        *BucketIndex = (Entry & BucketMask) - 1;
        *ItemIndex = (Entry >> CCBitCountSet(BucketMask)) & ItemMask;
        
        return TRUE;
    }
    
    return FALSE;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllFindKey(CCHashMap Map, void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (CCHashMapSeparateChainingArrayDataOrientedAllGetKey(Map, Key, NULL, &BucketIndex, &ItemIndex))
    {
        return CCHashMapSeparateChainingArrayDataOrientedAllIndexToEntry(Map, BucketIndex, ItemIndex);
    }
    
    return 0;
}

static size_t CCHashMapSeparateChainingArrayDataOrientedAllAddValue(CCHashMap Map, size_t BucketIndex, uintmax_t Hash, void *Key, void *Value)
{
    CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
    
    //hash
    if (Map->getHash)
    {
        if (!Internal->hashes)
        {
            Internal->hashes = CCArrayCreate(Map->allocator, sizeof(CCArray), Map->bucketCount);
            for (size_t Loop = 0; Loop < Map->bucketCount; Loop++) CCArrayAppendElement(Internal->hashes, &(CCArray){ NULL });
        }
        
        CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, BucketIndex);
        if (!HashBucket)
        {
            HashBucket = CCArrayCreate(Map->allocator, sizeof(uintmax_t), 1);
            CCArrayReplaceElementAtIndex(Internal->hashes, BucketIndex, &HashBucket);
        }
        
        CCArrayAppendElement(HashBucket, &Hash);
    }
    
    //key
    if (!Internal->keys)
    {
        Internal->keys = CCArrayCreate(Map->allocator, sizeof(CCArray), Map->bucketCount);
        for (size_t Loop = 0; Loop < Map->bucketCount; Loop++) CCArrayAppendElement(Internal->keys, &(CCArray){ NULL });
    }
    
    CCArray KeyBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->keys, BucketIndex);
    if (!KeyBucket)
    {
        KeyBucket = CCArrayCreate(Map->allocator, Map->keySize, 1);
        CCArrayReplaceElementAtIndex(Internal->keys, BucketIndex, &KeyBucket);
    }
    
    CCArrayAppendElement(KeyBucket, Key);
    
    //value
    if (!Internal->values)
    {
        Internal->values = CCArrayCreate(Map->allocator, sizeof(CCArray), Map->bucketCount);
        for (size_t Loop = 0; Loop < Map->bucketCount; Loop++) CCArrayAppendElement(Internal->values, &(CCArray){ NULL });
    }
    
    CCArray ValueBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->values, BucketIndex);
    if (!ValueBucket)
    {
        ValueBucket = CCArrayCreate(Map->allocator, Map->valueSize, 1);
        CCArrayReplaceElementAtIndex(Internal->values, BucketIndex, &ValueBucket);
    }
    
    return CCArrayAppendElement(ValueBucket, Value);
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllEntryForKey(CCHashMap Map, void *Key, _Bool *Created)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (CCHashMapSeparateChainingArrayDataOrientedAllGetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        if (Created) *Created = FALSE;
        return CCHashMapSeparateChainingArrayDataOrientedAllIndexToEntry(Map, BucketIndex, ItemIndex);
    }
    
    else
    {
        if (Created) *Created = TRUE;
        return CCHashMapSeparateChainingArrayDataOrientedAllIndexToEntry(Map, BucketIndex, CCHashMapSeparateChainingArrayDataOrientedAllAddValue(Map, BucketIndex, Hash, Key, NULL));
    }
}

static void *CCHashMapSeparateChainingArrayDataOrientedAllGetEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (CCHashMapSeparateChainingArrayDataOrientedAllEntryToIndex(Map, Entry, &BucketIndex, &ItemIndex)) Value = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex), ItemIndex);
    
    return Value;
}

static void CCHashMapSeparateChainingArrayDataOrientedAllSetEntry(CCHashMap Map, CCHashMapEntry Entry, void *Value)
{
    size_t BucketIndex, ItemIndex;
    if (CCHashMapSeparateChainingArrayDataOrientedAllEntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        CCArrayReplaceElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex), ItemIndex, Value);
    }
}

static void CCHashMapSeparateChainingArrayDataOrientedAllRemoveEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    //TODO: implement
}

static void *CCHashMapSeparateChainingArrayDataOrientedAllGetValue(CCHashMap Map, void *Key)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (CCHashMapSeparateChainingArrayDataOrientedAllGetKey(Map, Key, NULL, &BucketIndex, &ItemIndex)) Value = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex), ItemIndex);
    
    return Value;
}

static void CCHashMapSeparateChainingArrayDataOrientedAllSetValue(CCHashMap Map, void *Key, void *Value)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (CCHashMapSeparateChainingArrayDataOrientedAllGetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        CCArrayReplaceElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex), ItemIndex, Value);
    }
    
    else
    {
        CCHashMapSeparateChainingArrayDataOrientedAllAddValue(Map, BucketIndex, Hash, Key, Value);
    }
}

static void CCHashMapSeparateChainingArrayDataOrientedAllRemoveValue(CCHashMap Map, void *Key)
{
    //TODO: implement
}
