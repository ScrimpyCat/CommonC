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

#import "DictionaryTests.h"
#import "Dictionary.h"
#import "CCString.h"
#import "CollectionEnumerator.h"
#import "DictionaryEnumerator.h"


static uintmax_t StringHasher(CCString *Key)
{
    return CCStringGetHash(*Key);
}

static CCComparisonResult StringComparator(CCString *left, CCString *right)
{
    return CCStringEqual(*left, *right) ? CCComparisonResultEqual : CCComparisonResultInvalid;
}

@implementation DictionaryTests

-(void) testCount
{
    if (!self.interface) return;
    
    CCDictionary Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), NULL, self.interface);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 0, @"Should not have any entries");
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 100 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 2 }, &(int){ 200 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 2, @"Should not have 2 entries");
    
    CCDictionaryEntryForKey(Dict, &(uintmax_t){ 2 });
    CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 });
    CCDictionaryEntryForKey(Dict, &(uintmax_t){ 4 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should not have 4 entries");
    
    CCDictionaryRemoveEntry(Dict, CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 }));
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 3, @"Should not have 3 entries");
    
    CCDictionaryEntry Entry = CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should not have 4 entries");
    
    CCDictionaryRemoveEntry(Dict, Entry);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 3, @"Should not have 3 entries");
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 5 }, &(int){ 200 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should not have 4 entries");
    
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 5 });
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 2 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 2, @"Should not have 2 entries");
    
    CCDictionaryDestroy(Dict);
    
    
    
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), NULL, self.interface);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 0, @"Should not have any entries");
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 100 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 2 }, &(int){ 200 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 2, @"Should have 2 entries");
    
    CCDictionaryEntryForKey(Dict, &(uintmax_t){ 2 });
    CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 });
    CCDictionaryEntryForKey(Dict, &(uintmax_t){ 4 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should have 4 entries");
    
    CCDictionaryRemoveEntry(Dict, CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 }));
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 3, @"Should have 3 entries");
    
    Entry = CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should have 4 entries");
    
    CCDictionaryRemoveEntry(Dict, Entry);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 3, @"Should have 3 entries");
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 5 }, &(int){ 200 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should have 4 entries");
    
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 5 });
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 2 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 2, @"Should have 2 entries");
    
    CCDictionaryDestroy(Dict);
}

-(void) assertKeys: (CCOrderedCollection)keys OfCount: (size_t)count ShouldEqual: (uintmax_t)result
{
    XCTAssertEqual(CCCollectionGetCount(keys), count, @"Should have the correct keys");
    
    uintmax_t Sum = 0;
    CC_COLLECTION_FOREACH(uintmax_t, k, keys) Sum += k;
    
    XCTAssertEqual(Sum, result, @"Should have the correct keys");
    CCCollectionDestroy(keys);
}

-(void) assertKeysInDict: (CCDictionary)map OfCount: (size_t)count ShouldEqual: (uintmax_t)result
{
    [self assertKeys: CCDictionaryGetKeys(map) OfCount: count ShouldEqual: result];
    
    size_t Count = 0;
    uintmax_t Sum = 0;
    CC_DICTIONARY_FOREACH_KEY(uintmax_t, k, map)
    {
        Sum += k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
    
    Count = 0;
    Sum = 0;
    
    CCEnumerator Enumerator;
    CCDictionaryGetKeyEnumerator(map, &Enumerator);
    
    for (uintmax_t *k = CCDictionaryEnumeratorGetTail(&Enumerator); k; k = CCDictionaryEnumeratorPrevious(&Enumerator))
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

-(void) assertValuesInDict: (CCDictionary)map OfCount: (size_t)count ShouldEqual: (int)result
{
    [self assertValues: CCDictionaryGetValues(map) OfCount: count ShouldEqual: result];
    
    size_t Count = 0;
    int Sum = 0;
    CC_DICTIONARY_FOREACH_VALUE(int, k, map)
    {
        Sum += k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
    
    Count = 0;
    Sum = 0;
    
    CCEnumerator Enumerator;
    CCDictionaryGetValueEnumerator(map, &Enumerator);
    
    for (int *k = CCDictionaryEnumeratorGetTail(&Enumerator); k; k = CCDictionaryEnumeratorPrevious(&Enumerator))
    {
        Sum += *k;
        Count++;
    }
    
    XCTAssertEqual(Count, count, @"Should have the correct values");
    XCTAssertEqual(Sum, result, @"Should have the correct values");
}

-(void) assertStoreWithBucketCount: (size_t)bucketCount
{
    CCDictionary Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), NULL, self.interface);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 0, @"Should not have any entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    [self assertKeysInDict: Dict OfCount: 0 ShouldEqual: 0];
    [self assertValuesInDict: Dict OfCount: 0 ShouldEqual: 0];
    
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 3 });
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 10 });
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 100 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 2 }, &(int){ 200 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 3 }, &(int){ 300 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 4 }, &(int){ 400 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 5 }, &(int){ 500 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    [self assertKeysInDict: Dict OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    [self assertValuesInDict: Dict OfCount: 5 ShouldEqual: 100 + 200 + 300 + 400 + 500];
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 101 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 2 }, &(int){ 202 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 3 }, &(int){ 303 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 4 }, &(int){ 404 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    [self assertKeysInDict: Dict OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    [self assertValuesInDict: Dict OfCount: 5 ShouldEqual: 101 + 202 + 303 + 404 + 505];
    
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 3 });
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 4 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 3, @"Should have 3 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    [self assertKeysInDict: Dict OfCount: 3 ShouldEqual: 1 + 2 + 5];
    [self assertValuesInDict: Dict OfCount: 3 ShouldEqual: 101 + 202 + 505];
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 3 }, &(int){ 333 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 0 }, &(int){ 000 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), 333, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), 000, @"Should contain the correct value for the key");
    
    [self assertKeysInDict: Dict OfCount: 5 ShouldEqual: 1 + 2 + 3 + 5 + 0];
    [self assertValuesInDict: Dict OfCount: 5 ShouldEqual: 101 + 202 + 333 + 505 + 000];
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), 333, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), 000, @"Should contain the correct value for the key");
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 3 }, &(int){ 300 });
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 1 });
    
    [self assertKeysInDict: Dict OfCount: 4 ShouldEqual: 2 + 3 + 5 + 0];
    [self assertValuesInDict: Dict OfCount: 4 ShouldEqual: 202 + 300 + 505 + 000];
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should have 4 entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), 000, @"Should contain the correct value for the key");
    
    CCDictionaryDestroy(Dict);
    
    
    
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), NULL, self.interface);
    
    CCDictionaryEntry Entries[] = {
        CCDictionaryFindKey(Dict, &(uintmax_t){ 0 }),
        CCDictionaryEntryForKey(Dict, &(uintmax_t){ 1 }),
        CCDictionaryEntryForKey(Dict, &(uintmax_t){ 2 }),
        CCDictionaryEntryForKey(Dict, &(uintmax_t){ 3 }),
        CCDictionaryEntryForKey(Dict, &(uintmax_t){ 4 }),
        CCDictionaryEntryForKey(Dict, &(uintmax_t){ 5 }),
        CCDictionaryFindKey(Dict, &(uintmax_t){ 6 })
    };
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(CCDictionaryGetKey(Dict, Entries[0]), NULL, @"Should contain no key");
    XCTAssertEqual(*(uintmax_t*)CCDictionaryGetKey(Dict, Entries[1]), 1, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCDictionaryGetKey(Dict, Entries[2]), 2, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCDictionaryGetKey(Dict, Entries[3]), 3, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCDictionaryGetKey(Dict, Entries[4]), 4, @"Should contain the correct the key");
    XCTAssertEqual(*(uintmax_t*)CCDictionaryGetKey(Dict, Entries[5]), 5, @"Should contain the correct the key");
    XCTAssertEqual(CCDictionaryGetKey(Dict, Entries[6]), NULL, @"Should contain no key");
    
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[0]), @"Should be uninitialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[1]), @"Should be uninitialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[2]), @"Should be uninitialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[3]), @"Should be uninitialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[4]), @"Should be uninitialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[5]), @"Should be uninitialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[6]), @"Should be uninitialized");
    
    [self assertKeysInDict: Dict OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    //values are undefined at this point
    
    CCDictionarySetEntry(Dict, Entries[0], &(int){ 0 });
    CCDictionarySetEntry(Dict, Entries[1], &(int){ 100 });
    CCDictionarySetEntry(Dict, Entries[2], &(int){ 200 });
    CCDictionarySetEntry(Dict, Entries[3], &(int){ 300 });
    CCDictionarySetEntry(Dict, Entries[4], &(int){ 400 });
    CCDictionarySetEntry(Dict, Entries[5], &(int){ 500 });
    CCDictionarySetEntry(Dict, Entries[6], &(int){ 600 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[0]), @"Should be uninitialized");
    XCTAssertTrue(CCDictionaryEntryIsInitialized(Dict, Entries[1]), @"Should be initialized");
    XCTAssertTrue(CCDictionaryEntryIsInitialized(Dict, Entries[2]), @"Should be initialized");
    XCTAssertTrue(CCDictionaryEntryIsInitialized(Dict, Entries[3]), @"Should be initialized");
    XCTAssertTrue(CCDictionaryEntryIsInitialized(Dict, Entries[4]), @"Should be initialized");
    XCTAssertTrue(CCDictionaryEntryIsInitialized(Dict, Entries[5]), @"Should be initialized");
    XCTAssertFalse(CCDictionaryEntryIsInitialized(Dict, Entries[6]), @"Should be uninitialized");
    
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    [self assertKeysInDict: Dict OfCount: 5 ShouldEqual: 1 + 2 + 3 + 4 + 5];
    [self assertValuesInDict: Dict OfCount: 5 ShouldEqual: 100 + 200 + 300 + 400 + 500];
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 101 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 2 }, &(int){ 202 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 3 }, &(int){ 303 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 4 }, &(int){ 404 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetEntry(Dict, Entries[1]), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetEntry(Dict, Entries[2]), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetEntry(Dict, Entries[3]), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetEntry(Dict, Entries[4]), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetEntry(Dict, Entries[5]), 505, @"Should contain the correct value for the key");
    
    CCDictionaryRemoveEntry(Dict, Entries[3]);
    CCDictionaryRemoveEntry(Dict, Entries[4]);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 3, @"Should have 3 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    [self assertKeysInDict: Dict OfCount: 3 ShouldEqual: 1 + 2 + 5];
    [self assertValuesInDict: Dict OfCount: 3 ShouldEqual: 101 + 202 + 505];
    
    CCDictionarySetEntry(Dict, Entries[5], &(int){ 555 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 0 }, &(int){ 000 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 4, @"Should have 4 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 3 }), NULL, @"Should contain the correct value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uintmax_t){ 4 }), NULL, @"Should have removed the value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 5 }), 555, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uintmax_t){ 0 }), 000, @"Should contain the correct value for the key");
    
    [self assertValuesInDict: Dict OfCount: 4 ShouldEqual: 101 + 202 + 555 + 000];
    
    CCDictionaryDestroy(Dict);
    
    
    
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uint8_t), sizeof(int), NULL, self.interface);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 0, @"Should not have any entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 1 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 2 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 3 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 4 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 5 }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    CCDictionarySetValue(Dict, &(uint8_t){ 1 }, &(int){ 100 });
    CCDictionarySetValue(Dict, &(uint8_t){ 2 }, &(int){ 200 });
    CCDictionarySetValue(Dict, &(uint8_t){ 3 }, &(int){ 300 });
    CCDictionarySetValue(Dict, &(uint8_t){ 4 }, &(int){ 400 });
    CCDictionarySetValue(Dict, &(uint8_t){ 5 }, &(int){ 500 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 0 }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 1 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 2 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 3 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 4 }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 5 }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(uint8_t){ 6 }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 1 }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 2 }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 3 }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 4 }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 5 }), 500, @"Should contain the correct value for the key");
    
    CCDictionarySetValue(Dict, &(uint8_t){ 1 }, &(int){ 101 });
    CCDictionarySetValue(Dict, &(uint8_t){ 2 }, &(int){ 202 });
    CCDictionarySetValue(Dict, &(uint8_t){ 3 }, &(int){ 303 });
    CCDictionarySetValue(Dict, &(uint8_t){ 4 }, &(int){ 404 });
    CCDictionarySetValue(Dict, &(uint8_t){ 5 }, &(int){ 505 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 1 }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 2 }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 3 }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 4 }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(uint8_t){ 5 }), 505, @"Should contain the correct value for the key");
    
    CCDictionaryDestroy(Dict);
    
    
    
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(CCString), sizeof(int), &(CCDictionaryCallbacks){
        .getHash = (CCDictionaryKeyHasher)StringHasher,
        .compareKeys = (CCComparator)StringComparator
    }, self.interface);
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 0, @"Should not have any entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("0") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("1") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("2") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("3") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("4") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("5") }), NULL, @"Should not contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("6") }), NULL, @"Should not contain a value for the key");
    
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("1") }, &(int){ 100 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("2") }, &(int){ 200 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("3") }, &(int){ 300 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("4") }, &(int){ 400 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("5") }, &(int){ 500 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("0") }), NULL, @"Should not contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("1") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("2") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("3") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("4") }), NULL, @"Should contain a value for the key");
    XCTAssertNotEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("5") }), NULL, @"Should contain a value for the key");
    XCTAssertEqual(CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("6") }), NULL, @"Should not contain a value for the key");
    
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("1") }), 100, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("2") }), 200, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("3") }), 300, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("4") }), 400, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("5") }), 500, @"Should contain the correct value for the key");
    
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("1") }, &(int){ 101 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("2") }, &(int){ 202 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("3") }, &(int){ 303 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("4") }, &(int){ 404 });
    CCDictionarySetValue(Dict, &(CCString){ CC_STRING("5") }, &(int){ 505 });
    
    XCTAssertEqual(CCDictionaryGetCount(Dict), 5, @"Should have 5 entries");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("1") }), 101, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("2") }), 202, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("3") }), 303, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("4") }), 404, @"Should contain the correct value for the key");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dict, &(CCString){ CC_STRING("5") }), 505, @"Should contain the correct value for the key");
    
    CCDictionaryDestroy(Dict);
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

static int KeyDestroyCount = 0;
static void TestDictionaryKeyDestructor(CCDictionary Dictionary, void *Element)
{
    KeyDestroyCount++;
}

static int ValueDestroyCount = 0;
static void TestDictionaryValueDestructor(CCDictionary Dictionary, void *Element)
{
    ValueDestroyCount++;
}

-(void) testDestructing
{
    if (!self.interface) return;
    
    CCDictionary Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), &(CCDictionaryCallbacks){
        .keyDestructor = TestDictionaryKeyDestructor,
        .valueDestructor = TestDictionaryValueDestructor
    }, self.interface);
    
    CCDictionaryDestroy(Dict);
    
    XCTAssertEqual(KeyDestroyCount, 0, @"No keys to be destroyed");
    XCTAssertEqual(ValueDestroyCount, 0, @"No values to be destroyed");
    
    
    
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), &(CCDictionaryCallbacks){
        .keyDestructor = TestDictionaryKeyDestructor,
        .valueDestructor = TestDictionaryValueDestructor
    }, self.interface);
    
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 0 });
    
    CCDictionaryDestroy(Dict);
    
    XCTAssertEqual(KeyDestroyCount, 0, @"No keys to be destroyed");
    XCTAssertEqual(ValueDestroyCount, 0, @"No values to be destroyed");
    
    
    
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), &(CCDictionaryCallbacks){
        .keyDestructor = TestDictionaryKeyDestructor,
        .valueDestructor = TestDictionaryValueDestructor
    }, self.interface);
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 0 }, &(int){ 0 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 0 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 0 }, &(int){ 0 });
    
    CCDictionaryDestroy(Dict);
    
    XCTAssertEqual(KeyDestroyCount, 2, @"No keys to be destroyed");
    XCTAssertEqual(ValueDestroyCount, 3, @"No values to be destroyed");
    
    
    
    KeyDestroyCount = 0;
    ValueDestroyCount = 0;
    Dict = CCDictionaryCreateWithImplementation(CC_STD_ALLOCATOR, 0, sizeof(uintmax_t), sizeof(int), &(CCDictionaryCallbacks){
        .keyDestructor = TestDictionaryKeyDestructor,
        .valueDestructor = TestDictionaryValueDestructor
    }, self.interface);
    
    CCDictionarySetValue(Dict, &(uintmax_t){ 0 }, &(int){ 0 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 1 }, &(int){ 0 });
    CCDictionarySetValue(Dict, &(uintmax_t){ 0 }, &(int){ 0 });
    
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 0 });
    CCDictionaryRemoveValue(Dict, &(uintmax_t){ 1 });
    
    CCDictionaryDestroy(Dict);
    
    XCTAssertEqual(KeyDestroyCount, 2, @"No keys to be destroyed");
    XCTAssertEqual(ValueDestroyCount, 3, @"No values to be destroyed");
}

@end
