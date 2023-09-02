/*
 *  Copyright (c) 2023, Stefan Johnson
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
#import "MemoryZone.h"

@interface MemoryZoneTests : XCTestCase

@end

@implementation MemoryZoneTests

-(void) testAllocating
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 16);
    
    uint64_t *a = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *b = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *c = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    
    *a = 1;
    *b = 2;
    *c = 3;
    
    XCTAssertEqual(*a, 1, @"Should be the correct value");
    XCTAssertEqual(*b, 2, @"Should be the correct value");
    XCTAssertEqual(*c, 3, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, sizeof(uint64_t));
    
    uint64_t *x = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *x = 4;
    
    XCTAssertEqual(*a, 1, @"Should be the correct value");
    XCTAssertEqual(*b, 2, @"Should be the correct value");
    XCTAssertEqual(*c, 4, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, sizeof(uint64_t) * 2);
    
    x = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *x = 5;
    x = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *x = 6;
    
    XCTAssertEqual(*a, 1, @"Should be the correct value");
    XCTAssertEqual(*b, 5, @"Should be the correct value");
    XCTAssertEqual(*x, 6, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    
    x = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *x = 7;
    x = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *x = 8;
    x = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *x = 9;
    
    XCTAssertEqual(*a, 7, @"Should be the correct value");
    XCTAssertEqual(*b, 8, @"Should be the correct value");
    XCTAssertEqual(*x, 9, @"Should be the correct value");
    
    CCMemoryZoneDestroy(Zone);
}

-(void) testRestoringState
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 128);
    
    uint32_t *a = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *b = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *c = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    *a = 1;
    *b = 2;
    *c = 3;
    
    XCTAssertEqual(*a, 1, @"Should be the correct value");
    XCTAssertEqual(*b, 2, @"Should be the correct value");
    XCTAssertEqual(*c, 3, @"Should be the correct value");
    
    CCMemoryZoneRestore(Zone);
    
    uint32_t *x = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    *x = 4;
    
    XCTAssertEqual(*a, 1, @"Should be the correct value");
    XCTAssertEqual(*b, 2, @"Should be the correct value");
    XCTAssertEqual(*c, 3, @"Should be the correct value");
    XCTAssertEqual(*x, 4, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    a = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    CCMemoryZoneSave(Zone);
    b = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    *a = 5;
    *b = 6;
    
    XCTAssertEqual(*a, 5, @"Should be the correct value");
    XCTAssertEqual(*b, 6, @"Should be the correct value");
    
    CCMemoryZoneRestore(Zone);
    CCMemoryZoneAllocate(Zone, sizeof(CCMemoryZoneState));
    x = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    *x = 7;
    
    XCTAssertEqual(*a, 5, @"Should be the correct value");
    XCTAssertEqual(*b, 7, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    CCMemoryZoneSave(Zone);
    a = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    CCMemoryZoneSave(Zone);
    b = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    *a = 8;
    *b = 9;
    
    XCTAssertEqual(*a, 8, @"Should be the correct value");
    XCTAssertEqual(*b, 9, @"Should be the correct value");
    
    CCMemoryZoneRestore(Zone);
    CCMemoryZoneRestore(Zone);
    
    CCMemoryZoneAllocate(Zone, sizeof(CCMemoryZoneState));
    x = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    *x = 10;
    
    XCTAssertEqual(*a, 10, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    CCMemoryZoneSave(Zone);
    a = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    CCMemoryZoneSave(Zone);
    b = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    *a = 11;
    *b = 12;
    
    XCTAssertEqual(*a, 11, @"Should be the correct value");
    XCTAssertEqual(*b, 12, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, sizeof(uint32_t));
    CCMemoryZoneRestore(Zone);
    CCMemoryZoneAllocate(Zone, sizeof(CCMemoryZoneState));
    x = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    *x = 13;
    
    XCTAssertEqual(*a, 11, @"Should be the correct value");
    XCTAssertEqual(*b, 13, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    CCMemoryZoneSave(Zone);
    a = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    CCMemoryZoneSave(Zone);
    b = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    *a = 14;
    *b = 15;
    
    XCTAssertEqual(*a, 14, @"Should be the correct value");
    XCTAssertEqual(*b, 15, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, sizeof(uint32_t) + 1);
    CCMemoryZoneRestore(Zone);
    CCMemoryZoneAllocate(Zone, sizeof(CCMemoryZoneState));
    x = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    *x = 16;
    
    XCTAssertEqual(*a, 16, @"Should be the correct value");
    
    CCMemoryZoneDestroy(Zone);
}

@end