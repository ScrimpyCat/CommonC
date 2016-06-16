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

#include "HashMapSeparateChainingArray.h"
#include "HashMap.h"
#include "MemoryAllocation.h"
#include "Array.h"
#include "BitTricks.h"
#include "Logging.h"


typedef struct {
    size_t count;
    CCArray buckets;
} CCHashMapSeparateChainingArrayInternal;

static void *CCHashMapSeparateChainingArrayConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount);
static void CCHashMapSeparateChainingArrayDestructor(CCHashMapSeparateChainingArrayInternal *Internal);
static size_t CCHashMapSeparateChainingArrayGetCount(CCHashMap Map);
static _Bool CCHashMapSeparateChainingArrayEntryIsInitialized(CCHashMap Map, CCHashMapEntry Entry);
static CCHashMapEntry CCHashMapSeparateChainingArrayFindKey(CCHashMap Map, void *Key);
static CCHashMapEntry CCHashMapSeparateChainingArrayEntryForKey(CCHashMap Map, void *Key, _Bool *Created);
static void *CCHashMapSeparateChainingArrayGetKey(CCHashMap Map, CCHashMapEntry Entry);
static void *CCHashMapSeparateChainingArrayGetEntry(CCHashMap Map, CCHashMapEntry Entry);
static void CCHashMapSeparateChainingArraySetEntry(CCHashMap Map, CCHashMapEntry Entry, void *Value);
static void CCHashMapSeparateChainingArrayRemoveEntry(CCHashMap Map, CCHashMapEntry Entry);
static void *CCHashMapSeparateChainingArrayGetValue(CCHashMap Map, void *Key);
static void CCHashMapSeparateChainingArraySetValue(CCHashMap Map, void *Key, void *Value);
static void CCHashMapSeparateChainingArrayRemoveValue(CCHashMap Map, void *Key);
static CCOrderedCollection CCHashMapSeparateChainingArrayGetKeys(CCHashMap Map);
static CCOrderedCollection CCHashMapSeparateChainingArrayGetValues(CCHashMap Map);
static void *CCHashMapSeparateChainingArrayEnumerator(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorAction Action, CCHashMapEnumeratorType Type);
static CCHashMapEntry CCHashMapSeparateChainingArrayEnumeratorEntry(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorType Type);


const CCHashMapInterface CCHashMapSeparateChainingArrayInterface = {
    .create = CCHashMapSeparateChainingArrayConstructor,
    .destroy = (CCHashMapDestructorCallback)CCHashMapSeparateChainingArrayDestructor,
    .count = CCHashMapSeparateChainingArrayGetCount,
    .initialized = CCHashMapSeparateChainingArrayEntryIsInitialized,
    .findKey = CCHashMapSeparateChainingArrayFindKey,
    .entryForKey = CCHashMapSeparateChainingArrayEntryForKey,
    .getKey = CCHashMapSeparateChainingArrayGetKey,
    .getEntry = CCHashMapSeparateChainingArrayGetEntry,
    .setEntry = CCHashMapSeparateChainingArraySetEntry,
    .removeEntry = CCHashMapSeparateChainingArrayRemoveEntry,
    .enumerator = CCHashMapSeparateChainingArrayEnumerator,
    .enumeratorReference = CCHashMapSeparateChainingArrayEnumeratorEntry,
    .optional = {
        .rehash = NULL,
        .getValue = CCHashMapSeparateChainingArrayGetValue,
        .setValue = CCHashMapSeparateChainingArraySetValue,
        .removeValue = CCHashMapSeparateChainingArrayRemoveValue,
        .keys = CCHashMapSeparateChainingArrayGetKeys,
        .values = CCHashMapSeparateChainingArrayGetValues
    }
};

const CCHashMapInterface * const CCHashMapSeparateChainingArray = &CCHashMapSeparateChainingArrayInterface;


static CCHashMapEntry IndexToEntry(CCHashMap Map, size_t BucketIndex, size_t ItemIndex)
{
    const uintmax_t BucketMask = CCBitMaskForValue(Map->bucketCount + 1);
    const uintmax_t ItemMask = ~BucketMask, ItemShift = CCBitCountSet(BucketMask);
    
    if ((ItemIndex & (ItemMask >> ItemShift)) == ItemIndex)
    {
        return (ItemIndex << ItemShift) | (BucketIndex + 1);
    }
    
    CC_LOG_WARNING("HashMap bucket size (%zu, %zu) exceeds representable threshold for an entry reference", Map->bucketCount, CCArrayGetCount(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex)));
    
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

static inline uintmax_t *GetItemHash(CCHashMap Map, void *Item)
{
    return Item;
}

static inline void SetItemHash(CCHashMap Map, void *Item, uintmax_t Hash)
{
    *(uintmax_t*)Item = Hash;
}

static inline void *GetItemKey(CCHashMap Map, void *Item)
{
    return Item + sizeof(uintmax_t);
}

static inline void SetItemKey(CCHashMap Map, void *Item, void *Key)
{
    memcpy(Item + sizeof(uintmax_t), Key, Map->keySize);
}

static inline void *GetItemValue(CCHashMap Map, void *Item)
{
    return Item + sizeof(uintmax_t) + Map->keySize;
}

static inline void SetItemValue(CCHashMap Map, void *Item, void *Value)
{
    memcpy(Item + sizeof(uintmax_t) + Map->keySize, Value, Map->valueSize);
}

static size_t AddValue(CCHashMap Map, size_t BucketIndex, uintmax_t Hash, void *Key, void *Value)
{
    CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    Internal->count++;
    
    if (Value) Hash |= HASH_INIT_BIT;
    
    //hash/key/value
    if (!Internal->buckets)
    {
        Internal->buckets = CCArrayCreate(Map->allocator, sizeof(CCArray), Map->bucketCount);
        for (size_t Loop = 0; Loop < Map->bucketCount; Loop++) CCArrayAppendElement(Internal->buckets, &(CCArray){ NULL });
    }
    
    CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, BucketIndex);
    if (!Bucket)
    {
        Bucket = CCArrayCreate(Map->allocator, sizeof(uintmax_t) + Map->keySize + Map->valueSize, 1);
        CCArrayReplaceElementAtIndex(Internal->buckets, BucketIndex, &Bucket);
    }
    
    else
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Bucket); Loop < Count; Loop++)
        {
            void *Item = CCArrayGetElementAtIndex(Bucket, Loop);
            if (HashIsEmpty(*GetItemHash(Map, Item)))
            {
                SetItemHash(Map, Item, Hash);
                SetItemKey(Map, Item, Key);
                if (Value) SetItemValue(Map, Item, Value);
                
                return Loop;
            }
        }
    }
    
    const size_t Index = CCArrayAppendElement(Bucket, NULL);
    void *Item = CCArrayGetElementAtIndex(Bucket, Index);
    SetItemHash(Map, Item, Hash);
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
            CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
            
            uintmax_t *Hash = GetItemHash(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, BucketIndex), ItemIndex));
            
            CCAssertLog(!HashIsEmpty(*Hash), "Hash has been removed");
            
            *Hash |= HASH_EMPTY_BIT;
            *Hash &= ~HASH_INIT_BIT;
            Internal->count--;
        }
    }
}

static _Bool GetKey(CCHashMap Map, void *Key, uintmax_t *HashValue, size_t *BucketIndex, size_t *ItemIndex)
{
    const uintmax_t Hash = CCHashMapGetKeyHash(Map, Key) & HASH_RESERVED_MASK;
    const size_t Index = Hash % Map->bucketCount;
    
    if (HashValue) *HashValue = Hash;
    *BucketIndex = Index;
    
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    
    if (Internal->buckets)
    {
        CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Index);
        if (Bucket)
        {
            for (size_t Loop = 0, Count = CCArrayGetCount(Bucket); Loop < Count; Loop++)
            {
                void *Item = CCArrayGetElementAtIndex(Bucket, Loop);
                const uintmax_t EntryHash = *GetItemHash(Map, Item) & ~HASH_INIT_BIT;
                if (Hash == EntryHash)
                {
                    const void *EntryKey = GetItemKey(Map, Item);
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

static void *CCHashMapSeparateChainingArrayConstructor(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount)
{
    CCHashMapSeparateChainingArrayInternal *Map = CCMalloc(Allocator, sizeof(CCHashMapSeparateChainingArrayInternal), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Map)
    {
        *Map = (CCHashMapSeparateChainingArrayInternal){
            .count = 0,
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

static void CCHashMapSeparateChainingArrayDestructor(CCHashMapSeparateChainingArrayInternal *Internal)
{
    if (Internal->buckets) BucketDestroy(Internal->buckets);
}

static size_t CCHashMapSeparateChainingArrayGetCount(CCHashMap Map)
{
    return ((CCHashMapSeparateChainingArrayInternal*)Map->internal)->count;
}

static _Bool CCHashMapSeparateChainingArrayEntryIsInitialized(CCHashMap Map, CCHashMapEntry Entry)
{
    _Bool Init = FALSE;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        const uintmax_t Hash = *GetItemHash(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex), ItemIndex));
        
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(Hash), "Entry has been removed");
#endif
        
        Init = HashIsInitialized(Hash);
    }
    
    return Init;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayFindKey(CCHashMap Map, void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex))
    {
        return IndexToEntry(Map, BucketIndex, ItemIndex);
    }
    
    return 0;
}

static CCHashMapEntry CCHashMapSeparateChainingArrayEntryForKey(CCHashMap Map, void *Key, _Bool *Created)
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

static void *CCHashMapSeparateChainingArrayGetKey(CCHashMap Map, CCHashMapEntry Entry)
{
    void *Key = NULL;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        void *Item = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex), ItemIndex);
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(*GetItemHash(Map, Item)), "Entry has been removed");
#endif
        
        Key = GetItemKey(Map, Item);
    }
    
    return Key;
}

static void *CCHashMapSeparateChainingArrayGetEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        void *Item = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex), ItemIndex);
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(*GetItemHash(Map, Item)), "Entry has been removed");
#endif
        
        Value = GetItemValue(Map, Item);
    }
    
    return Value;
}

static void CCHashMapSeparateChainingArraySetEntry(CCHashMap Map, CCHashMapEntry Entry, void *Value)
{
    size_t BucketIndex, ItemIndex;
    if (EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex))
    {
        void *Item = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex), ItemIndex);
        uintmax_t *Hash = GetItemHash(Map, Item);
#if !CC_NO_ASSERT
        CCAssertLog(!HashIsEmpty(*Hash), "Entry has been removed");
#endif
        
        *Hash |= HASH_INIT_BIT;
        SetItemValue(Map, Item, Value);
    }
}

static void CCHashMapSeparateChainingArrayRemoveEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    RemoveValue(Map, Entry);
}

static void *CCHashMapSeparateChainingArrayGetValue(CCHashMap Map, void *Key)
{
    void *Value = NULL;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex)) Value = GetItemValue(Map, CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex), ItemIndex));
    
    return Value;
}

static void CCHashMapSeparateChainingArraySetValue(CCHashMap Map, void *Key, void *Value)
{
    uintmax_t Hash;
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, &Hash, &BucketIndex, &ItemIndex))
    {
        void *Item = CCArrayGetElementAtIndex(*(CCArray*)CCArrayGetElementAtIndex(((CCHashMapSeparateChainingArrayInternal*)Map->internal)->buckets, BucketIndex), ItemIndex);
        if (!HashIsInitialized(Hash))
        {
            uintmax_t *Hash = GetItemHash(Map, Item);
            *Hash |= HASH_INIT_BIT;
        }
        
        SetItemValue(Map, Item, Value);
    }
    
    else
    {
        AddValue(Map, BucketIndex, Hash, Key, Value);
    }
}

static void CCHashMapSeparateChainingArrayRemoveValue(CCHashMap Map, void *Key)
{
    size_t BucketIndex, ItemIndex;
    if (GetKey(Map, Key, NULL, &BucketIndex, &ItemIndex)) RemoveValue(Map, IndexToEntry(Map, BucketIndex, ItemIndex));
}

static CCOrderedCollection CCHashMapSeparateChainingArrayGetKeys(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    CCOrderedCollection Keys = CCCollectionCreate(Map->allocator, CCCollectionHintOrdered | CCCollectionHintConstantLength | CCCollectionHintHeavyEnumerating, Map->keySize, NULL);
    
    if (Internal->buckets)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->buckets); Loop < Count; Loop++)
        {
            CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop);
            if (Bucket)
            {
                for (size_t Loop2 = 0, Count2 = CCArrayGetCount(Bucket); Loop2 < Count2; Loop2++)
                {
                    void *Item = CCArrayGetElementAtIndex(Bucket, Loop2);
                    if (!HashIsEmpty(*GetItemHash(Map, Item)))
                    {
                        CCOrderedCollectionAppendElement(Keys, GetItemKey(Map, Item));
                    }
                }
            }
        }
    }
    
    return Keys;
}

static CCOrderedCollection CCHashMapSeparateChainingArrayGetValues(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    CCOrderedCollection Values = CCCollectionCreate(Map->allocator, CCCollectionHintOrdered | CCCollectionHintConstantLength | CCCollectionHintHeavyEnumerating, Map->valueSize, NULL);
    
    if (Internal->buckets)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->buckets); Loop < Count; Loop++)
        {
            CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop);
            if (Bucket)
            {
                for (size_t Loop2 = 0, Count2 = CCArrayGetCount(Bucket); Loop2 < Count2; Loop2++)
                {
                    void *Item = CCArrayGetElementAtIndex(Bucket, Loop2);
                    if (!HashIsEmpty(*GetItemHash(Map, Item)))
                    {
                        CCOrderedCollectionAppendElement(Values, GetItemValue(Map, Item));
                    }
                }
            }
        }
    }
    
    return Values;
}

static CCHashMapEntry GetHeadEntry(CCHashMap Map)
{
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    
    if (Internal->buckets)
    {
        for (size_t Loop = 0, Count = CCArrayGetCount(Internal->buckets); Loop < Count; Loop++)
        {
            CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop);
            if (Bucket)
            {
                for (size_t Loop2 = 0, Count2 = CCArrayGetCount(Bucket); Loop2 < Count2; Loop2++)
                {
                    if (!HashIsEmpty(*GetItemHash(Map, CCArrayGetElementAtIndex(Bucket, Loop2))))
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
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    
    if (Internal->buckets)
    {
        for (size_t Loop = CCArrayGetCount(Internal->buckets); Loop > 0; Loop--)
        {
            CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop - 1);
            if (Bucket)
            {
                for (size_t Loop2 = CCArrayGetCount(Bucket); Loop2 > 0; Loop2--)
                {
                    if (!HashIsEmpty(*GetItemHash(Map, CCArrayGetElementAtIndex(Bucket, Loop2 - 1))))
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
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    
    if (Internal->buckets)
    {
        size_t BucketIndex, ItemIndex;
        EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex);
        
        ItemIndex++;
        
        for (size_t Loop = BucketIndex, Count = CCArrayGetCount(Internal->buckets); Loop < Count; Loop++)
        {
            CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop);
            if (Bucket)
            {
                for (size_t Loop2 = ItemIndex, Count2 = CCArrayGetCount(Bucket); Loop2 < Count2; Loop2++)
                {
                    if (!HashIsEmpty(*GetItemHash(Map, CCArrayGetElementAtIndex(Bucket, Loop2))))
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
    const CCHashMapSeparateChainingArrayInternal *Internal = Map->internal;
    
    if (Internal->buckets)
    {
        size_t BucketIndex, ItemIndex;
        EntryToIndex(Map, Entry, &BucketIndex, &ItemIndex);
        
        ItemIndex++;
        
        for (size_t Loop = BucketIndex + 1; Loop > 0; Loop--)
        {
            CCArray Bucket = *(CCArray*)CCArrayGetElementAtIndex(Internal->buckets, Loop - 1);
            if (Bucket)
            {
                for (size_t Loop2 = ItemIndex ? ItemIndex - 1 : CCArrayGetCount(Bucket); Loop2 > 0; Loop2--)
                {
                    if (!HashIsEmpty(*GetItemHash(Map, CCArrayGetElementAtIndex(Bucket, Loop2 - 1))))
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

static void *CCHashMapSeparateChainingArrayEnumerator(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorAction Action, CCHashMapEnumeratorType Type)
{
    void *(*GetElement)(CCHashMap, CCHashMapEntry) = Type == CCHashMapEnumeratorTypeKey ? CCHashMapSeparateChainingArrayGetKey : CCHashMapSeparateChainingArrayGetEntry;
    
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

static CCHashMapEntry CCHashMapSeparateChainingArrayEnumeratorEntry(CCHashMap Map, CCEnumeratorState *Enumerator, CCHashMapEnumeratorType Type)
{
    return Enumerator->internal.extra[0];
}
