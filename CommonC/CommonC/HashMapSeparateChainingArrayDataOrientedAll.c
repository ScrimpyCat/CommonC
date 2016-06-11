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

#include "HashMapSeparateChainingArrayDataOrientedAll.h"
#include "HashMap.h"
#include "MemoryAllocation.h"
#include "Array.h"
#include "BitTricks.h"
#include "Logging.h"


typedef struct {
    size_t count;
    CCArray hashes;
    CCArray keys;
    CCArray values;
    CCArray available;
} CCHashMapSeparateChainingArrayDataOrientedAllInternal;

static void *CCHashMapSeparateChainingArrayDataOrientedAllConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount);
static void CCHashMapSeparateChainingArrayDataOrientedAllDestructor(CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal);
static size_t CCHashMapSeparateChainingArrayDataOrientedAllGetCount(CCHashMap Map);
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
    .count = CCHashMapSeparateChainingArrayDataOrientedAllGetCount,
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


static CCHashMapEntry IndexToEntry(CCHashMap Map, size_t BucketIndex, size_t ItemIndex)
{
    const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
    const uintmax_t ItemMask = ~BucketMask, ItemShift = CCBitCountSet(BucketMask);
    
    if ((ItemIndex & (ItemMask >> ItemShift)) == ItemIndex)
    {
        return (ItemIndex << ItemShift) | (BucketIndex + 1);
    }
    
    CC_LOG_WARNING("HashMap bucket size (%zu, %zu) exceeds representable threshold for an entry reference", Map->bucketCount, CCArrayGetCount(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex)));
    
    return 0;
}

static _Bool EntryToIndex(CCHashMap Map, CCHashMapEntry Entry, size_t *BucketIndex, size_t *ItemIndex)
{
    if (Entry)
    {
        const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
        const uintmax_t ItemMask = ~BucketMask;
        
        *BucketIndex = (Entry & BucketMask) - 1;
        *ItemIndex = (Entry & ItemMask) >> CCBitCountSet(BucketMask);
        
        return TRUE;
    }
    
    return FALSE;
}

static size_t AddValue(CCHashMap Map, size_t BucketIndex, uintmax_t Hash, void *Key, void *Value)
{
    CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
    Internal->count++;
    
    if (Internal->available)
    {
        const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
        {
            CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
            if ((AvailableEntry) && (BucketIndex == ((AvailableEntry & BucketMask) - 1))) //Replace the remove entry
            {
                if (Loop >= Count - (Count / 4)) CCArrayRemoveElementAtIndex(Internal->available, Loop);
                else CCArrayReplaceElementAtIndex(Internal->available, Loop, &(CCHashMapEntry){ 0 });
                
                const uintmax_t ItemIndex = (AvailableEntry & ~BucketMask) >> CCBitCountSet(BucketMask);
                if (Map->getHash)
                {
                    CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, BucketIndex);
                    CCArrayReplaceElementAtIndex(HashBucket, ItemIndex, &Hash);
                }
                
                CCArray KeyBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->keys, BucketIndex);
                CCArrayReplaceElementAtIndex(KeyBucket, ItemIndex, Key);
                
                CCArray ValueBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->values, BucketIndex);
                CCArrayReplaceElementAtIndex(ValueBucket, ItemIndex, Value);
                
                return ItemIndex;
            }
        }
    }
    
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

static void RemoveValue(CCHashMap Map, CCHashMapEntry Entry)
{
    if (Entry)
    {
        size_t BucketIndex, ItemIndex;
        if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
        {
            CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
            
            if (!Internal->available) Internal->available = CCArrayCreate(Map->allocator, sizeof(CCHashMapEntry), 4);
            
            size_t Reuse = SIZE_MAX;
            for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
            {
                CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
                if (Entry == AvailableEntry) return;
                else if (!AvailableEntry) Reuse = Loop;
            }
            
            if (Reuse != SIZE_MAX) CCArrayReplaceElementAtIndex(Internal->available, Reuse, &Entry);
            else CCArrayAppendElement(Internal->available, &Entry);
            
            Internal->count--;
        }
    }
}

static _Bool GetKey(CCHashMap Map, void *Key, uintmax_t *HashValue, size_t *BucketIndex, size_t *ItemIndex)
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

static void *CCHashMapSeparateChainingArrayDataOrientedAllConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount)
{
    CCHashMapSeparateChainingArrayDataOrientedAllInternal *Map = CCMalloc(Allocator, sizeof(CCHashMapSeparateChainingArrayDataOrientedAllInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Map)
    {
        *Map = (CCHashMapSeparateChainingArrayDataOrientedAllInternal){
            .count = 0,
            .hashes = NULL,
            .keys = NULL,
            .values = NULL,
            .available = NULL
        };
    }
    
    return Map;
}

static void BucketDestroy(CCArray Buckets)
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
    if (Internal->hashes) BucketDestroy(Internal->hashes);
    if (Internal->keys) BucketDestroy(Internal->keys);
    if (Internal->values) BucketDestroy(Internal->values);
}

static size_t CCHashMapSeparateChainingArrayDataOrientedAllGetCount(CCHashMap Map)
{
    return ((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->count;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllFindKey(CCHashMap Map, void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex))
    {
        CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
        const CCHashMapEntry Entry = IndexToEntry(Map, BucketIndex, ItemIndex);
        if (Internal->available)
        {
            for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
            {
                CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
                if (Entry == AvailableEntry) return 0; //Removed entry
            }
        }
        
        return Entry;
    }
    
    return 0;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedAllEntryForKey(CCHashMap Map, void *Key, _Bool *Created)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        if (Created) *Created = FALSE;
        
        CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
        const CCHashMapEntry Entry = IndexToEntry(Map, BucketIndex, ItemIndex);
        if (Internal->available)
        {
            for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
            {
                CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
                if (Entry == AvailableEntry) //Reuse the remove entry
                {
                    if (Loop >= Count - (Count / 4)) CCArrayRemoveElementAtIndex(Internal->available, Loop);
                    else CCArrayReplaceElementAtIndex(Internal->available, Loop, &(CCHashMapEntry){ 0 });
                    
                    Internal->count++;
                    if (Created) *Created = TRUE;
                    break;
                }
            }
        }
        
        return Entry;
    }
    
    else
    {
        if (Created) *Created = TRUE;
        return IndexToEntry(Map, BucketIndex, AddValue(Map, BucketIndex, Hash, Key, NULL));
    }
}

static void *CCHashMapSeparateChainingArrayDataOrientedAllGetEntry(CCHashMap Map, CCHashMapEntry Entry)
{
#if !CC_NO_ASSERT
    CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
    if (Internal->available)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
        {
            CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
            if ((AvailableEntry) && (Entry == AvailableEntry))
            {
                CCAssertLog(0, "Entry was removed");
            }
        }
    }
#endif
    
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex)) Value = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex), ItemIndex);
    
    return Value;
}

static void CCHashMapSeparateChainingArrayDataOrientedAllSetEntry(CCHashMap Map, CCHashMapEntry Entry, void *Value)
{
    CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
    if (Internal->available)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
        {
            CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
            if ((AvailableEntry) && (Entry == AvailableEntry)) //Reuse the remove entry
            {
                if (Loop >= Count - (Count / 4)) CCArrayRemoveElementAtIndex(Internal->available, Loop);
                else CCArrayReplaceElementAtIndex(Internal->available, Loop, &(CCHashMapEntry){ 0 });
                
                const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
                const uintmax_t ItemIndex = (AvailableEntry & ~BucketMask) >> CCBitCountSet(BucketMask);
                
                CCArrayReplaceElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->values, (AvailableEntry & BucketMask)), ItemIndex, Value);
                
                Internal->count++;
                return;
            }
        }
    }
    
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        CCArrayReplaceElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedAllInternal*)Map->internal)->values, BucketIndex), ItemIndex, Value);
    }
}

static void CCHashMapSeparateChainingArrayDataOrientedAllRemoveEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    RemoveValue(Map, Entry);
}

static void *CCHashMapSeparateChainingArrayDataOrientedAllGetValue(CCHashMap Map, void *Key)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex))
    {
        CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
        if (Internal->available)
        {
            const CCHashMapEntry Entry = IndexToEntry(Map, BucketIndex, ItemIndex);
            for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
            {
                CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
                if (Entry == AvailableEntry) return NULL; //Removed entry
            }
        }
        
        Value = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->values, BucketIndex), ItemIndex);
    }
    
    return Value;
}

static void CCHashMapSeparateChainingArrayDataOrientedAllSetValue(CCHashMap Map, void *Key, void *Value)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        CCHashMapSeparateChainingArrayDataOrientedAllInternal *Internal = Map->internal;
        if (Internal->available)
        {
            const CCHashMapEntry Entry = IndexToEntry(Map, BucketIndex, ItemIndex);
            for (size_t Loop = 0, Count = CCArrayGetCount(Internal->available); Loop < Count; Loop++)
            {
                CCHashMapEntry AvailableEntry = *(CCHashMapEntry*)CCArrayGetElementAtIndex(Internal->available, Loop);
                if (Entry == AvailableEntry) //Reuse the remove entry
                {
                    if (Loop >= Count - (Count / 4)) CCArrayRemoveElementAtIndex(Internal->available, Loop);
                    else CCArrayReplaceElementAtIndex(Internal->available, Loop, &(CCHashMapEntry){ 0 });
                    
                    const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
                    const uintmax_t ItemIndex = (AvailableEntry & ~BucketMask) >> CCBitCountSet(BucketMask);
                    
                    CCArrayReplaceElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->values, (AvailableEntry & BucketMask)), ItemIndex, Value);
                    
                    Internal->count++;
                    break;
                }
            }
        }
        
        CCArrayReplaceElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->values, BucketIndex), ItemIndex, Value);
    }
    
    else
    {
        AddValue(Map, BucketIndex, Hash, Key, Value);
    }
}

static void CCHashMapSeparateChainingArrayDataOrientedAllRemoveValue(CCHashMap Map, void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex)) RemoveValue(Map, IndexToEntry(Map, BucketIndex, ItemIndex));
}
