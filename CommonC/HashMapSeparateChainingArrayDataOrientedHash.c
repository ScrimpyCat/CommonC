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
#include "HashMapSeparateChainingArrayDataOrientedHash.h"
#include "HashMap.h"
#include "MemoryAllocation.h"
#include "Array.h"
#include "BitTricks.h"
#include "Logging.h"
#include <string.h>


static void *CCHashMapSeparateChainingArrayDataOrientedHashConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount);
static void CCHashMapSeparateChainingArrayDataOrientedHashDestructor(CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal);
static size_t CCHashMapSeparateChainingArrayDataOrientedHashGetCount(CCHashMap Map);
static _Bool CCHashMapSeparateChainingArrayDataOrientedHashEntryIsInitialized(CCHashMap Map, CCHashMapEntry Entry);
static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedHashFindKey(CCHashMap Map, const void *Key);
static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedHashEntryForKey(CCHashMap Map, const void *Key, _Bool *Created);
static void *CCHashMapSeparateChainingArrayDataOrientedHashGetKey(CCHashMap Map, CCHashMapEntry Entry);
static void *CCHashMapSeparateChainingArrayDataOrientedHashGetEntry(CCHashMap Map, CCHashMapEntry Entry);
static void CCHashMapSeparateChainingArrayDataOrientedHashSetEntry(CCHashMap Map, CCHashMapEntry Entry, const void *Value);
static void CCHashMapSeparateChainingArrayDataOrientedHashRemoveEntry(CCHashMap Map, CCHashMapEntry Entry);
static void *CCHashMapSeparateChainingArrayDataOrientedHashGetValue(CCHashMap Map, const void *Key);
static void CCHashMapSeparateChainingArrayDataOrientedHashSetValue(CCHashMap Map, const void *Key, const void *Value);
static void CCHashMapSeparateChainingArrayDataOrientedHashRemoveValue(CCHashMap Map, const void *Key);
static CCOrderedCollection CCHashMapSeparateChainingArrayDataOrientedHashGetKeys(CCHashMap Map);
static CCOrderedCollection CCHashMapSeparateChainingArrayDataOrientedHashGetValues(CCHashMap Map);
static void *CCHashMapSeparateChainingArrayDataOrientedHashEnumerator(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorAction Action, CCHashMapEnumeratorType Type);
static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedHashEnumeratorEntry(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorType Type);


const CCHashMapInterface CCHashMapSeparateChainingArrayDataOrientedHashInterface = {
    .create = CCHashMapSeparateChainingArrayDataOrientedHashConstructor,
    .destroy = (CCHashMapDestructorCallback)CCHashMapSeparateChainingArrayDataOrientedHashDestructor,
    .count = CCHashMapSeparateChainingArrayDataOrientedHashGetCount,
    .initialized = CCHashMapSeparateChainingArrayDataOrientedHashEntryIsInitialized,
    .findKey = CCHashMapSeparateChainingArrayDataOrientedHashFindKey,
    .entryForKey = CCHashMapSeparateChainingArrayDataOrientedHashEntryForKey,
    .getKey = CCHashMapSeparateChainingArrayDataOrientedHashGetKey,
    .getEntry = CCHashMapSeparateChainingArrayDataOrientedHashGetEntry,
    .setEntry = CCHashMapSeparateChainingArrayDataOrientedHashSetEntry,
    .removeEntry = CCHashMapSeparateChainingArrayDataOrientedHashRemoveEntry,
    .enumerator = CCHashMapSeparateChainingArrayDataOrientedHashEnumerator,
    .enumeratorReference = CCHashMapSeparateChainingArrayDataOrientedHashEnumeratorEntry,
    .optional = {
        .rehash = NULL,
        .getValue = CCHashMapSeparateChainingArrayDataOrientedHashGetValue,
        .setValue = CCHashMapSeparateChainingArrayDataOrientedHashSetValue,
        .removeValue = CCHashMapSeparateChainingArrayDataOrientedHashRemoveValue,
        .keys = CCHashMapSeparateChainingArrayDataOrientedHashGetKeys,
        .values = CCHashMapSeparateChainingArrayDataOrientedHashGetValues
    }
};


static CCHashMapEntry IndexToEntry(CCHashMap Map, size_t BucketIndex, size_t ItemIndex)
{
    const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
    const uintmax_t ItemMask = ~BucketMask, ItemShift = CCBitCountSet(BucketMask);
    
    if ((ItemIndex & (ItemMask >> ItemShift)) == ItemIndex)
    {
        return (ItemIndex << ItemShift) | (BucketIndex + 1);
    }
    
    CC_LOG_WARNING("HashMap bucket size (%zu, %zu) exceeds representable threshold for an entry reference", Map->bucketCount, CCArrayGetCount(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->buckets, BucketIndex)));
    
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

#define HASH_RESERVED_MASK (UINTMAX_MAX >> 2)
#define HASH_EMPTY_BIT ~(UINTMAX_MAX >> 1)
#define HASH_INIT_BIT ((~(UINTMAX_MAX >> 1)) >> 1)

static inline _Bool HashIsEmpty(uintmax_t Hash)
{
    return Hash & HASH_EMPTY_BIT;
}

static inline _Bool HashIsInitialized(uintmax_t Hash)
{
    return Hash & HASH_INIT_BIT;
}

static inline void *GetItemKey(CCHashMap Map, void *Item)
{
    return Item;
}

static inline void SetItemKey(CCHashMap Map, void *Item, const void *Key)
{
    memcpy(Item, Key, Map->keySize);
}

static inline void *GetItemValue(CCHashMap Map, void *Item)
{
    return Item + Map->keySize;
}

static inline void SetItemValue(CCHashMap Map, void *Item, const void *Value)
{
    memcpy(Item + Map->keySize, Value, Map->valueSize);
}

static size_t AddValue(CCHashMap Map, size_t BucketIndex, uintmax_t Hash, const void *Key, const void *Value)
{
    CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    Internal->count++;
    
    if (Value) Hash |= HASH_INIT_BIT;
    
    //hash
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
    
    else
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(HashBucket); Loop < Count; Loop++)
        {
            if (HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop)))
            {
                CCArrayReplaceElementAtIndex(HashBucket, Loop, &Hash);
                void *Item = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, BucketIndex), Loop);
                SetItemKey(Map, Item, Key);
                if (Value) SetItemValue(Map, Item, Value);
                
                return Loop;
            }
        }
    }
    
    CCArrayAppendElement(HashBucket, &Hash);
    
    //key/value
    if (!Internal->buckets)
    {
        Internal->buckets = CCArrayCreate(Map->allocator, sizeof(CCArray), Map->bucketCount);
        for (size_t Loop = 0; Loop < Map->bucketCount; Loop++) CCArrayAppendElement(Internal->buckets, &(CCArray){ NULL });
    }
    
    CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, BucketIndex);
    if (!Bucket)
    {
        Bucket = CCArrayCreate(Map->allocator, Map->keySize + Map->valueSize, 1);
        CCArrayReplaceElementAtIndex(Internal->buckets, BucketIndex, &Bucket);
    }
    
    const size_t Index = CCArrayAppendElement(Bucket, NULL);
    void *Item = CCArrayGetElementAtIndex(Bucket, Index);
    SetItemKey(Map, Item, Key);
    if (Value) SetItemValue(Map, Item, Value);
    
    return Index;
}

static void RemoveValue(CCHashMap Map, CCHashMapEntry Entry)
{
    if (Entry)
    {
        size_t BucketIndex, ItemIndex;
        if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
        {
            CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
            
            uintmax_t *Hash = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, BucketIndex), ItemIndex);
            
            CCAssertLog(!HashIsEmpty(*Hash), "Hash has been removed");
            
            *Hash |= HASH_EMPTY_BIT;
            *Hash &= ~HASH_INIT_BIT;
            Internal->count--;
        }
    }
}

static _Bool GetKey(CCHashMap Map, const void *Key, uintmax_t *HashValue, size_t *BucketIndex, size_t *ItemIndex)
{
    const uintmax_t Hash = CCHashMapGetKeyHash(Map, Key) & HASH_RESERVED_MASK;
    const size_t Index = Hash % Map->bucketCount;
    
    if (HashValue) *HashValue = Hash;
    *BucketIndex = Index;
    
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    
    if (Internal->hashes)
    {
        CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Index);
        if (HashBucket)
        {
            for (size_t Loop = 0, Count = CCArrayGetCount(HashBucket); Loop < Count; Loop++)
            {
                const uintmax_t EntryHash = *(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop) & ~HASH_INIT_BIT;
                if (Hash == EntryHash)
                {
                    const void *EntryKey = GetItemKey(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Index), Loop));
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
    
    return FALSE;
}

static void *CCHashMapSeparateChainingArrayDataOrientedHashConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount)
{
    CCHashMapSeparateChainingArrayDataOrientedHashInternal *Map = CCMalloc(Allocator, sizeof(CCHashMapSeparateChainingArrayDataOrientedHashInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Map)
    {
        *Map = (CCHashMapSeparateChainingArrayDataOrientedHashInternal){
            .count = 0,
            .hashes = NULL,
            .buckets = NULL
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

static void CCHashMapSeparateChainingArrayDataOrientedHashDestructor(CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal)
{
    if (Internal->hashes) BucketDestroy(Internal->hashes);
    if (Internal->buckets) BucketDestroy(Internal->buckets);
    
    CC_SAFE_Free(Internal);
}

static size_t CCHashMapSeparateChainingArrayDataOrientedHashGetCount(CCHashMap Map)
{
    return ((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->count;
}

static _Bool CCHashMapSeparateChainingArrayDataOrientedHashEntryIsInitialized(CCHashMap Map, CCHashMapEntry Entry)
{
    _Bool Init = FALSE;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        const uintmax_t Hash = *(uintmax_t*)CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->hashes, BucketIndex), ItemIndex);
        
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(Hash), "Entry has been removed");
#endif
        
        Init = HashIsInitialized(Hash);
    }
    
    return Init;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedHashFindKey(CCHashMap Map, const void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex))
    {
        return IndexToEntry(Map, BucketIndex, ItemIndex);
    }
    
    return 0;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedHashEntryForKey(CCHashMap Map, const void *Key, _Bool *Created)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        if (Created) *Created = FALSE;
        return IndexToEntry(Map, BucketIndex, ItemIndex);
    }
    
    else
    {
        if (Created) *Created = TRUE;
        return IndexToEntry(Map, BucketIndex, AddValue(Map, BucketIndex, Hash, Key, NULL));
    }
}

static void *CCHashMapSeparateChainingArrayDataOrientedHashGetKey(CCHashMap Map, CCHashMapEntry Entry)
{
    void *Key = NULL;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->hashes, BucketIndex), ItemIndex)), "Entry has been removed");
#endif
        
        Key = GetItemKey(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->buckets, BucketIndex), ItemIndex));
    }
    
    return Key;
}

static void *CCHashMapSeparateChainingArrayDataOrientedHashGetEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->hashes, BucketIndex), ItemIndex)), "Entry has been removed");
#endif
        
        Value = GetItemValue(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->buckets, BucketIndex), ItemIndex));
    }
    
    return Value;
}

static void CCHashMapSeparateChainingArrayDataOrientedHashSetEntry(CCHashMap Map, CCHashMapEntry Entry, const void *Value)
{
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        uintmax_t *Hash = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->hashes, BucketIndex), ItemIndex);
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(*Hash), "Entry has been removed");
#endif
        
        *Hash |= HASH_INIT_BIT;
        SetItemValue(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->buckets, BucketIndex), ItemIndex), Value);
    }
}

static void CCHashMapSeparateChainingArrayDataOrientedHashRemoveEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    RemoveValue(Map, Entry);
}

static void *CCHashMapSeparateChainingArrayDataOrientedHashGetValue(CCHashMap Map, const void *Key)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex)) Value = GetItemValue(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->buckets, BucketIndex), ItemIndex));
    
    return Value;
}

static void CCHashMapSeparateChainingArrayDataOrientedHashSetValue(CCHashMap Map, const void *Key, const void *Value)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        if (!HashIsInitialized(Hash))
        {
            uintmax_t *Hash = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->hashes, BucketIndex), ItemIndex);
            *Hash |= HASH_INIT_BIT;
        }
        
        SetItemValue(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayDataOrientedHashInternal*)Map->internal)->buckets, BucketIndex), ItemIndex), Value);
    }
    
    else
    {
        AddValue(Map, BucketIndex, Hash, Key, Value);
    }
}

static void CCHashMapSeparateChainingArrayDataOrientedHashRemoveValue(CCHashMap Map, const void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex)) RemoveValue(Map, IndexToEntry(Map, BucketIndex, ItemIndex));
}

static CCOrderedCollection CCHashMapSeparateChainingArrayDataOrientedHashGetKeys(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    CCOrderedCollection Keys = CCCollectionCreate(Map->allocator, CCCollectionHintOrdered | CCCollectionHintConstantLength | CCCollectionHintHeavyEnumerating, Map->keySize, NULL);
    
    if (Internal->hashes)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->hashes); Loop < Count; Loop++)
        {
            CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Loop);
            if (HashBucket)
            {
                CCArray KeyBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop);
                for (size_t Loop2 = 0, Count2 = CCArrayGetCount(HashBucket); Loop2 < Count2; Loop2++)
                {
                    if (!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop2)))
                    {
                        CCOrderedCollectionAppendElement(Keys, GetItemKey(Map, CCArrayGetElementAtIndex(KeyBucket, Loop2)));
                    }
                }
            }
        }
    }
    
    return Keys;
}

static CCOrderedCollection CCHashMapSeparateChainingArrayDataOrientedHashGetValues(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    CCOrderedCollection Values = CCCollectionCreate(Map->allocator, CCCollectionHintOrdered | CCCollectionHintConstantLength | CCCollectionHintHeavyEnumerating, Map->valueSize, NULL);
    
    if (Internal->hashes)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->hashes); Loop < Count; Loop++)
        {
            CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Loop);
            if (HashBucket)
            {
                CCArray ValueBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop);
                for (size_t Loop2 = 0, Count2 = CCArrayGetCount(HashBucket); Loop2 < Count2; Loop2++)
                {
                    if (!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop2)))
                    {
                        CCOrderedCollectionAppendElement(Values, GetItemValue(Map, CCArrayGetElementAtIndex(ValueBucket, Loop2)));
                    }
                }
            }
        }
    }
    
    return Values;
}

static CCHashMapEntry GetHeadEntry(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    
    if (Internal->hashes)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->hashes); Loop < Count; Loop++)
        {
            CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Loop);
            if (HashBucket)
            {
                for (size_t Loop2 = 0, Count2 = CCArrayGetCount(HashBucket); Loop2 < Count2; Loop2++)
                {
                    if (!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop2)))
                    {
                        return IndexToEntry(Map, Loop, Loop2);
                    }
                }
            }
        }
    }
    
    return 0;
}

static CCHashMapEntry GetTailEntry(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    
    if (Internal->hashes)
    {
        for (size_t Loop = CCArrayGetCount(Internal->hashes); Loop > 0; Loop--)
        {
            CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Loop - 1);
            if (HashBucket)
            {
                for (size_t Loop2 = CCArrayGetCount(HashBucket); Loop2 > 0; Loop2--)
                {
                    if (!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop2 - 1)))
                    {
                        return IndexToEntry(Map, Loop - 1, Loop2 - 1);
                    }
                }
            }
        }
    }
    
    return 0;
}

static CCHashMapEntry GetNextEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    
    if (Internal->hashes)
    {
        size_t BucketIndex, ItemIndex;
        EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex);
        
        ItemIndex++;
        
        for (size_t Loop = BucketIndex, Count = CCArrayGetCount(Internal->hashes); Loop < Count; Loop++)
        {
            CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Loop);
            if (HashBucket)
            {
                for (size_t Loop2 = ItemIndex, Count2 = CCArrayGetCount(HashBucket); Loop2 < Count2; Loop2++)
                {
                    if (!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop2)))
                    {
                        return IndexToEntry(Map, Loop, Loop2);
                    }
                }
                
                ItemIndex = 0;
            }
        }
    }
    
    return 0;
}

static CCHashMapEntry GetPrevEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    const CCHashMapSeparateChainingArrayDataOrientedHashInternal *Internal = Map->internal;
    
    if (Internal->hashes)
    {
        size_t BucketIndex, ItemIndex;
        EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex);
        
        ItemIndex++;
        
        for (size_t Loop = BucketIndex + 1; Loop > 0; Loop--)
        {
            CCArray HashBucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->hashes, Loop - 1);
            if (HashBucket)
            {
                for (size_t Loop2 = ItemIndex ? ItemIndex - 1 : CCArrayGetCount(HashBucket); Loop2 > 0; Loop2--)
                {
                    if (!HashIsEmpty(*(uintmax_t*)CCArrayGetElementAtIndex(HashBucket, Loop2 - 1)))
                    {
                        return IndexToEntry(Map, Loop - 1, Loop2 - 1);
                    }
                }
                
                ItemIndex = 0;
            }
        }
    }
    
    return 0;
}

static void *CCHashMapSeparateChainingArrayDataOrientedHashEnumerator(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorAction Action, CCHashMapEnumeratorType Type)
{
    void *(*GetElement)(CCHashMap, CCHashMapEntry) = Type == CCHashMapEnumeratorTypeKey ? CCHashMapSeparateChainingArrayDataOrientedHashGetKey : CCHashMapSeparateChainingArrayDataOrientedHashGetEntry;
    
    switch (Action)
    {
        case CCCollectionEnumeratorActionHead:
            Enumerator->type = CCEnumeratorFormatInternal;
            Enumerator->internal.extra[0] = GetHeadEntry(Map);
            Enumerator->internal.ptr = GetElement(Map, Enumerator->internal.extra[0]);
            break;
            
        case CCCollectionEnumeratorActionTail:
            Enumerator->type = CCEnumeratorFormatInternal;
            Enumerator->internal.extra[0] = GetTailEntry(Map);
            Enumerator->internal.ptr = GetElement(Map, Enumerator->internal.extra[0]);
            break;
            
        case CCCollectionEnumeratorActionNext:
            Enumerator->internal.extra[0] = GetNextEntry(Map, Enumerator->internal.extra[0]);
            Enumerator->internal.ptr = GetElement(Map, Enumerator->internal.extra[0]);
            break;
            
        case CCCollectionEnumeratorActionPrevious:
            Enumerator->internal.extra[0] = GetPrevEntry(Map, Enumerator->internal.extra[0]);
            Enumerator->internal.ptr = GetElement(Map, Enumerator->internal.extra[0]);
            break;
            
        case CCCollectionEnumeratorActionCurrent:
            break;
    }
    
    return Enumerator->internal.ptr;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayDataOrientedHashEnumeratorEntry(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorType Type)
{
    return Enumerator->internal.extra[0];
}
