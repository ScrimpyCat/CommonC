/*
 *  Copyright (c) 2018, Stefan Johnson
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


#import <XCTest/XCTest.h>
#import "ConcurrentIndexMap.h"
#import "EpochGarbageCollector.h"
#import "LazyGarbageCollector.h"
#import <stdatomic.h>
#import <pthread.h>

@interface ConcurrentIndexMapTests : XCTestCase

@property (readonly) const CCConcurrentGarbageCollectorInterface *gc;

@end

@implementation ConcurrentIndexMapTests

-(const CCConcurrentGarbageCollectorInterface *) gc
{
    return CCEpochGarbageCollector;
}

-(void) testCreation
{
    CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 1, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 0, @"Should be empty");
    XCTAssertEqual(CCConcurrentIndexMapGetElementSize(IndexMap), sizeof(int), @"Should be the size specified on creation");
    
    CCConcurrentIndexMapDestroy(IndexMap);
}

-(void) testAppending
{
    for (size_t ChunkSize = 1; ChunkSize <= 5; ChunkSize++)
    {
        CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), ChunkSize, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
        
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
        
        int Value;
        XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 1, @"Should be the first element");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 2, @"Should be the second element");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 3, @"Should be the third element");
        
        XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
        
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 4 });
        
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 4, @"Should be the fourth element");
        
        CCConcurrentIndexMapDestroy(IndexMap);
    }
}

-(void) testReplacing
{
    for (size_t ChunkSize = 1; ChunkSize <= 5; ChunkSize++)
    {
        CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), ChunkSize, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
        
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
        
        int Value;
        XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 0, &(int){ 10 }, &Value), "Should replace the element");
        XCTAssertEqual(Value, 1, "Should retrieve the previous element");
        XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 1, &(int){ 20 }, &Value), "Should replace the element");
        XCTAssertEqual(Value, 2, "Should retrieve the previous element");
        XCTAssertTrue(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 2, &(int){ 30 }, &Value), "Should replace the element");
        XCTAssertEqual(Value, 3, "Should retrieve the previous element");
        
        XCTAssertFalse(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 3, &(int){ 40 }, &Value), "Should not replace an element that does not exist");
        
        XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 10, @"Should be the first element");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 20, @"Should be the second element");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 30, @"Should be the third element");
        
        XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
        
        CCConcurrentIndexMapDestroy(IndexMap);
    }
}

-(void) testReplacingMatches
{
    for (size_t ChunkSize = 1; ChunkSize <= 5; ChunkSize++)
    {
        CCConcurrentIndexMap IndexMap = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), ChunkSize, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
        
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 1 });
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 2 });
        CCConcurrentIndexMapAppendElement(IndexMap, &(int){ 3 });
        
        XCTAssertTrue(CCConcurrentIndexMapReplaceExactElementAtIndex(IndexMap, 0, &(int){ 10 }, &(int){ 1 }), "Should replace the element");
        XCTAssertFalse(CCConcurrentIndexMapReplaceExactElementAtIndex(IndexMap, 1, &(int){ 20 }, &(int){ 5 }), "Should replace the element");
        XCTAssertFalse(CCConcurrentIndexMapReplaceExactElementAtIndex(IndexMap, 2, &(int){ 30 }, &(int){ 2 }), "Should replace the element");
        
        XCTAssertFalse(CCConcurrentIndexMapReplaceElementAtIndex(IndexMap, 3, &(int){ 40 }, &(int){ 3 }), "Should not replace an element that does not exist");
        
        int Value;
        XCTAssertEqual(CCConcurrentIndexMapGetCount(IndexMap), 3, @"Should contain 3 elements");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 0, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 10, @"Should be the first element");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 1, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 2, @"Should be the second element");
        XCTAssertTrue(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 2, &Value), @"Should have an element at the given index");
        XCTAssertEqual(Value, 3, @"Should be the third element");
        
        XCTAssertFalse(CCConcurrentIndexMapGetElementAtIndex(IndexMap, 3, &Value), @"Should not have an element at the given index");
        
        CCConcurrentIndexMapDestroy(IndexMap);
    }
}

#define ELEMENT_COUNT 1000
#define ELEMENT_INC 1000

static CCConcurrentIndexMap M;
static _Atomic(int) ReplaceCount = ATOMIC_VAR_INIT(0);
static _Atomic(int) CorrectCount = ATOMIC_VAR_INIT(0);
static void *Counters(void *Arg)
{
    size_t Indexes[ELEMENT_COUNT];
    
    for (int Loop = 0; Loop < ELEMENT_COUNT; Loop++)
    {
        Indexes[Loop] = CCConcurrentIndexMapAppendElement(M, &Loop);
    }
    
    int LocalReplaceCount = 0;
    for (int Loop = 0; Loop < ELEMENT_INC; Loop++)
    {
        for (int Loop2 = 0; Loop2 < ELEMENT_COUNT; Loop2++)
        {
            int Element;
            if (CCConcurrentIndexMapGetElementAtIndex(M, Indexes[Loop2], &Element))
            {
                int ReplacedElement;
                if (CCConcurrentIndexMapReplaceElementAtIndex(M, Indexes[Loop2], &(int){ Element + 1 }, &ReplacedElement))
                {
                    LocalReplaceCount++;
                }
            }
        }
    }
    
    int Matches = 0;
    for (int Loop = 0; Loop < ELEMENT_COUNT; Loop++)
    {
        int Element;
        if (CCConcurrentIndexMapGetElementAtIndex(M, Indexes[Loop], &Element))
        {
            if (Element == (ELEMENT_INC + Loop))
            {
                Matches++;
            }
        }
    }
    
    if (Matches == ELEMENT_COUNT) atomic_fetch_add_explicit(&CorrectCount, 1, memory_order_relaxed);
    
    atomic_fetch_add_explicit(&ReplaceCount, LocalReplaceCount, memory_order_relaxed);
    
    return NULL;
}

#define THREAD_COUNT 10

-(void) testMultiThreadedReplacements
{
    atomic_store(&ReplaceCount, 0);
    atomic_store(&CorrectCount, 0);
    M = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 4, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    pthread_t CounterThreads[THREAD_COUNT];
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(CounterThreads + Loop, NULL, Counters, NULL);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(CounterThreads[Loop], NULL);
    }
    
    
    CCConcurrentIndexMapDestroy(M);
    
    XCTAssertEqual(atomic_load(&ReplaceCount), ELEMENT_INC * ELEMENT_COUNT * THREAD_COUNT, @"Should cause this many replacements");
    XCTAssertEqual(atomic_load(&CorrectCount), THREAD_COUNT, @"All threads should end up in the correct state");
}

static CCConcurrentIndexMap M2;
static void *Appenders(void *Arg)
{
    for (int Loop = 0; Loop < ELEMENT_COUNT; Loop++)
    {
        CCConcurrentIndexMapAppendElement(M2, &Loop);
    }
    
    return NULL;
}

static size_t Sum = 0;
static void *Summer(void *Arg)
{
    Sum = 0;
    for (int Loop = 0; Loop < ELEMENT_COUNT * THREAD_COUNT; Loop++)
    {
        int Element;
        while (!CCConcurrentIndexMapGetElementAtIndex(M2, Loop, &Element));
        
        Sum += Element;
    }
    
    return NULL;
}

-(void) testMultiThreadedAppends
{
    M2 = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 4, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    pthread_t AppenderThreads[THREAD_COUNT], SummerThread;
    
    pthread_create(&SummerThread, NULL, Summer, NULL);
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(AppenderThreads + Loop, NULL, Appenders, NULL);
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(AppenderThreads[Loop], NULL);
    }
    
    pthread_join(SummerThread, NULL);
    
    CCConcurrentIndexMapDestroy(M2);
    
    size_t CorrectSum = 0;
    for (int Loop = 0; Loop < ELEMENT_COUNT; Loop++) CorrectSum += Loop;
    
    XCTAssertEqual(Sum, (CorrectSum * THREAD_COUNT), @"Should append all elements");
}

static CCConcurrentIndexMap M3;
static _Atomic(size_t) ReplacerSum = ATOMIC_VAR_INIT(0);
static void *Replacers(void *Arg)
{
    size_t LocalSum = 0;
    for (int Loop = 0; Loop < ELEMENT_INC; Loop++)
    {
        int ReplacedElement;
        if (CCConcurrentIndexMapReplaceElementAtIndex(M3, 0, &(int){ (int)Arg }, &ReplacedElement))
        {
            LocalSum += ReplacedElement;
        }
    }
    
    atomic_fetch_add_explicit(&ReplacerSum, LocalSum, memory_order_relaxed);
    
    return NULL;
}

-(void) testMultiThreadedSingleElementReplacement
{
    atomic_store(&ReplacerSum, 0);
    
    M3 = CCConcurrentIndexMapCreate(CC_STD_ALLOCATOR, sizeof(int), 4, CCConcurrentGarbageCollectorCreate(CC_STD_ALLOCATOR, self.gc));
    
    CCConcurrentIndexMapAppendElement(M3, &(int){ 1 });
    
    pthread_t ReplacerThreads[THREAD_COUNT];
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_create(ReplacerThreads + Loop, NULL, Replacers, (void*)(uintptr_t)(Loop + 1));
    }
    
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        pthread_join(ReplacerThreads[Loop], NULL);
    }
    
    size_t CorrectSum = 1;
    for (int Loop = 0; Loop < THREAD_COUNT; Loop++)
    {
        for (int Loop2 = 0; Loop2 < ELEMENT_INC; Loop2++)
        {
            CorrectSum += (Loop + 1);
        }
    }
    
    int ReplacedElement;
    if (CCConcurrentIndexMapReplaceElementAtIndex(M3, 0, &(int){ 0 }, &ReplacedElement))
    {
        CorrectSum -= ReplacedElement;
    }
    
    CCConcurrentIndexMapDestroy(M3);
    
    XCTAssertEqual(atomic_load(&ReplacerSum), CorrectSum, @"Should cause this many replacements");
}

@end

@interface ConcurrentIndexMapTestsLazyGC : ConcurrentIndexMapTests
@end

@implementation ConcurrentIndexMapTestsLazyGC

-(const CCConcurrentGarbageCollectorInterface *) gc
{
    return CCLazyGarbageCollector;
}

@end
