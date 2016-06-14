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

#import "HashMapTests.h"
#import "HashMap.h"
#import "CCString.h"
#import "CollectionEnumerator.h"
#import "HashMapEnumerator.h"


static uintmax_t StringHasher(CCString *Key)
{
    return CCStringGetHash(*Key);
}

static CCComparisonResult StringComparator(CCString *left, CCString *right)
{
    return CCStringEqual(*left, *right) ? CCComparisonResultEqual : CCComparisonResultInvalid;
}

@implementation HashMapTests

-(void) testCount
{
    if (!self.interface) return;
    
    CCHashMap Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uintmax_t), sizeof(int), 3, NULL, NULL, self.interface);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 0, @"Should not have any entries");
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 100 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 200 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 2, @"Should not have 2 entries");
    
    CCHashMapEntryForKey(Map, &(uintmax_t){ 2 }, NULL);
    CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL);
    CCHashMapEntryForKey(Map, &(uintmax_t){ 4 }, NULL);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should not have 4 entries");
    
    CCHashMapRemoveEntry(Map, CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL));
    
    XCTAssertEqual(CCHashMapGetCount(Map), 3, @"Should not have 3 entries");
    
    CCHashMapEntry Entry = CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should not have 4 entries");
    
    CCHashMapRemoveEntry(Map, Entry);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 3, @"Should not have 3 entries");
    
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 200 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should not have 4 entries");
    
    CCHashMapRemoveValue(Map, &(uintmax_t){ 5 });
    CCHashMapRemoveValue(Map, &(uintmax_t){ 2 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 2, @"Should not have 2 entries");
    
    CCHashMapDestroy(Map);
    
    
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uintmax_t), sizeof(int), 1, NULL, NULL, self.interface);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 0, @"Should not have any entries");
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 100 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 200 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 2, @"Should have 2 entries");
    
    CCHashMapEntryForKey(Map, &(uintmax_t){ 2 }, NULL);
    CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL);
    CCHashMapEntryForKey(Map, &(uintmax_t){ 4 }, NULL);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should have 4 entries");
    
    CCHashMapRemoveEntry(Map, CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL));
    
    XCTAssertEqual(CCHashMapGetCount(Map), 3, @"Should have 3 entries");
    
    Entry = CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should have 4 entries");
    
    CCHashMapRemoveEntry(Map, Entry);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 3, @"Should have 3 entries");
    
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 200 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should have 4 entries");
    
    CCHashMapRemoveValue(Map, &(uintmax_t){ 5 });
    CCHashMapRemoveValue(Map, &(uintmax_t){ 2 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 2, @"Should have 2 entries");
    
    CCHashMapDestroy(Map);
}

-(void) assertKeys: (CCOrderedCollection)keys OfCount: (size_t)count ShouldEqual: (uintmax_t)result
{
    XCTAssertEqual(CCCollectionGetCount(keys), count, @"Should have the correct keys");
    
    uintmax_t Sum = 0;
    CC_COLLECTION_FOREACH(uintmax_t, k, keys) Sum += k;
    
    XCTAssertEqual(Sum, result, @"Should have the correct keys");
    CCCollectionDestroy(keys);
}

-(void) assertKeysInMap: (CCHashMap)map OfCount: (size_t)count ShouldEqual: (uintmax_t)result
{
    [self assertKeys: CCHashMapGetKeys(map) OfCount: count ShouldEqual: result];
    
    size_t Count = 0;
    uintmax_t Sum = 0;
    CC_HASH_MAP_FOREACH_KEY(uintmax_t, k, map)
    {
        Sum += k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
    
    Count = 0;
    Sum = 0;
    
    CCEnumerator Enumerator;
    CCHashMapGetKeyEnumerator(map, &Enumerator);
    
    for (uintmax_t *k = CCHashMapEnumeratorGetTail(&Enumerator); k; k = CCHashMapEnumeratorPrevious(&Enumerator))
    {
        Sum += *k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
}

-(void) assertValues: (CCOrderedCollection)values OfCount: (size_t)count ShouldEqual: (int)result
{
    XCTAssertEqual(CCCollectionGetCount(values), count, @"Should have the correct values");
    
    int Sum = 0;
    CC_COLLECTION_FOREACH(int, k, values) Sum += k;
    
    XCTAssertEqual(Sum, result, @"Should have the correct values");
    CCCollectionDestroy(values);
}

-(void) assertValuesInMap: (CCHashMap)map OfCount: (size_t)count ShouldEqual: (int)result
{
    [self assertValues: CCHashMapGetValues(map) OfCount: count ShouldEqual: result];
    
    size_t Count = 0;
    int Sum = 0;
    CC_HASH_MAP_FOREACH_VALUE(int, k, map)
    {
        Sum += k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
    
    Count = 0;
    Sum = 0;
    
    CCEnumerator Enumerator;
    CCHashMapGetValueEnumerator(map, &Enumerator);
    
    for (int *k = CCHashMapEnumeratorGetTail(&Enumerator); k; k = CCHashMapEnumeratorPrevious(&Enumerator))
    {
        Sum += *k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
}

-(void) assertStoreWithBucketCount: (size_t)bucketCount
{
    CCHashMap Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uintmax_t), sizeof(int), bucketCount, NULL, NULL, self.interface);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 0, @"Should not have any entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 1 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 2 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 5 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    [self assertKeysInMap: Map OfCount: 0 ShouldEqual: 0];
    [self assertValuesInMap: Map OfCount: 0 ShouldEqual: 0];
    
    CCHashMapRemoveValue(Map, &(uintmax_t){ 3 });
    CCHashMapRemoveValue(Map, &(uintmax_t){ 10 });
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 100 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 200 });
    CCHashMapSetValue(Map, &(uintmax_t){ 3 }, &(int){ 300 });
    CCHashMapSetValue(Map, &(uintmax_t){ 4 }, &(int){ 400 });
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 500 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    [self assertKeysInMap: Map OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    [self assertValuesInMap: Map OfCount: 5 ShouldEqual: 100 + 200 + 300 + 400 + 500];
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 101 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 202 });
    CCHashMapSetValue(Map, &(uintmax_t){ 3 }, &(int){ 303 });
    CCHashMapSetValue(Map, &(uintmax_t){ 4 }, &(int){ 404 });
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 3 }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 4 }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    [self assertKeysInMap: Map OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    [self assertValuesInMap: Map OfCount: 5 ShouldEqual: 101 + 202 + 303 + 404 + 505];
    
    CCHashMapRemoveValue(Map, &(uintmax_t){ 3 });
    CCHashMapRemoveValue(Map, &(uintmax_t){ 4 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 3, @"Should have 3 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    [self assertKeysInMap: Map OfCount: 3 ShouldEqual: 1 + 2 + 5];
    [self assertValuesInMap: Map OfCount: 3 ShouldEqual: 101 + 202 + 505];
    
    CCHashMapSetValue(Map, &(uintmax_t){ 3 }, &(int){ 333 });
    CCHashMapSetValue(Map, &(uintmax_t){ 0 }, &(int){ 000 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 3 }), 333, @"Should contain the correct value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 0 }), 000, @"Should contain the correct value for the key");
    
    CCHashMapDestroy(Map);
    
    
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uintmax_t), sizeof(int), bucketCount, NULL, NULL, self.interface);
    
    CCHashMapEntry Entries[] = {
        CCHashMapFindKey(Map, &(uintmax_t){ 0 }),
        CCHashMapEntryForKey(Map, &(uintmax_t){ 1 }, NULL),
        CCHashMapEntryForKey(Map, &(uintmax_t){ 2 }, NULL),
        CCHashMapEntryForKey(Map, &(uintmax_t){ 3 }, NULL),
        CCHashMapEntryForKey(Map, &(uintmax_t){ 4 }, NULL),
        CCHashMapEntryForKey(Map, &(uintmax_t){ 5 }, NULL),
        CCHashMapFindKey(Map, &(uintmax_t){ 6 })
    };
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(CCHashMapGetKey(Map, Entries[0]), NULL, @"Should contain no key");
    XCTAssertEqual(*(uintmax_t*)CCHashMapGetKey(Map, Entries[1]), 1, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCHashMapGetKey(Map, Entries[2]), 2, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCHashMapGetKey(Map, Entries[3]), 3, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCHashMapGetKey(Map, Entries[4]), 4, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCHashMapGetKey(Map, Entries[5]), 5, @"Should contain the correct the key");
    XCTAssertEqual(CCHashMapGetKey(Map, Entries[6]), NULL, @"Should contain no key");
    
    [self assertKeysInMap: Map OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    //values are undefined at this point
    
    CCHashMapSetEntry(Map, Entries[0], &(int){ 0 });
    CCHashMapSetEntry(Map, Entries[1], &(int){ 100 });
    CCHashMapSetEntry(Map, Entries[2], &(int){ 200 });
    CCHashMapSetEntry(Map, Entries[3], &(int){ 300 });
    CCHashMapSetEntry(Map, Entries[4], &(int){ 400 });
    CCHashMapSetEntry(Map, Entries[5], &(int){ 500 });
    CCHashMapSetEntry(Map, Entries[6], &(int){ 600 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uintmax_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    [self assertKeysInMap: Map OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    [self assertValuesInMap: Map OfCount: 5 ShouldEqual: 100 + 200 + 300 + 400 + 500];
    
    CCHashMapSetValue(Map, &(uintmax_t){ 1 }, &(int){ 101 });
    CCHashMapSetValue(Map, &(uintmax_t){ 2 }, &(int){ 202 });
    CCHashMapSetValue(Map, &(uintmax_t){ 3 }, &(int){ 303 });
    CCHashMapSetValue(Map, &(uintmax_t){ 4 }, &(int){ 404 });
    CCHashMapSetValue(Map, &(uintmax_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCHashMapGetEntry(Map, Entries[1]), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetEntry(Map, Entries[2]), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetEntry(Map, Entries[3]), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetEntry(Map, Entries[4]), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetEntry(Map, Entries[5]), 505, @"Should contain the correct value for the key");
    
    CCHashMapRemoveEntry(Map, Entries[3]);
    CCHashMapRemoveEntry(Map, Entries[4]);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 3, @"Should have 3 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    [self assertKeysInMap: Map OfCount: 3 ShouldEqual: 1 + 2 + 5];
    [self assertValuesInMap: Map OfCount: 3 ShouldEqual: 101 + 202 + 505];
    
    CCHashMapSetEntry(Map, Entries[5], &(int){ 555 });
    CCHashMapSetValue(Map, &(uintmax_t){ 0 }, &(int){ 000 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 4, @"Should have 4 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 3 }), NULL, @"Should contain the correct value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 5 }), 555, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uintmax_t){ 0 }), 000, @"Should contain the correct value for the key");
    
    [self assertValuesInMap: Map OfCount: 4 ShouldEqual: 101 + 202 + 555 + 000];
    
    CCHashMapDestroy(Map);
    
    
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(uint8_t), sizeof(int), bucketCount, NULL, NULL, self.interface);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 0, @"Should not have any entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 1 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 2 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 3 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 4 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 5 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    CCHashMapSetValue(Map, &(uint8_t){ 1 }, &(int){ 100 });
    CCHashMapSetValue(Map, &(uint8_t){ 2 }, &(int){ 200 });
    CCHashMapSetValue(Map, &(uint8_t){ 3 }, &(int){ 300 });
    CCHashMapSetValue(Map, &(uint8_t){ 4 }, &(int){ 400 });
    CCHashMapSetValue(Map, &(uint8_t){ 5 }, &(int){ 500 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(uint8_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(uint8_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    CCHashMapSetValue(Map, &(uint8_t){ 1 }, &(int){ 101 });
    CCHashMapSetValue(Map, &(uint8_t){ 2 }, &(int){ 202 });
    CCHashMapSetValue(Map, &(uint8_t){ 3 }, &(int){ 303 });
    CCHashMapSetValue(Map, &(uint8_t){ 4 }, &(int){ 404 });
    CCHashMapSetValue(Map, &(uint8_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 3 }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 4 }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(uint8_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    CCHashMapDestroy(Map);
    
    
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(CCString), sizeof(int), bucketCount, (CCHashMapKeyHasher)StringHasher, (CCComparator)StringComparator, self.interface);
    
    XCTAssertEqual(CCHashMapGetCount(Map), 0, @"Should not have any entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("0") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("6") }), NULL, @"Should not contain a value for the key");
    
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("1") }, &(int){ 100 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("2") }, &(int){ 200 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("3") }, &(int){ 300 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("4") }, &(int){ 400 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("5") }, &(int){ 500 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("0") }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCHashMapGetValue(Map, &(CCString){ CC_STRING("6") }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), 500, @"Should contain the correct value for the key");
    
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("1") }, &(int){ 101 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("2") }, &(int){ 202 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("3") }, &(int){ 303 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("4") }, &(int){ 404 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("5") }, &(int){ 505 });
    
    XCTAssertEqual(CCHashMapGetCount(Map), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("1") }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("2") }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("3") }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("4") }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("5") }), 505, @"Should contain the correct value for the key");
    
    CCHashMapDestroy(Map);
}

-(void) testStoring
{
    if (!self.interface) return;
    
    [self assertStoreWithBucketCount: 1];
    [self assertStoreWithBucketCount: 2];
    [self assertStoreWithBucketCount: 3];
    [self assertStoreWithBucketCount: 5];
    [self assertStoreWithBucketCount: 50];
}

@end
