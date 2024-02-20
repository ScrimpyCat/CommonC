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

-(void) testPointerRetrieval
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 16);
    
    uint64_t *a = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *b = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *c = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *d = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *e = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    
    *a = 1;
    *b = 2;
    *c = 3;
    *d = 4;
    *e = 5;
    
    size_t Size;
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 0, &Size), 1, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 1, &Size), 2, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 2, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 3, &Size), 4, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 4, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 5, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 6, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    uint64_t *f = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *f = 6;
    
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 0, &Size), 1, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 1, &Size), 2, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 2, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 3, &Size), 4, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 4, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 5, &Size), 6, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 6, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, 0, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    CCMemoryZoneDestroy(Zone);
    
    
    
    Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 20);
    
    a = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    b = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    c = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    d = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    e = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    
    *a = 1;
    *b = 2;
    *c = 3;
    *d = 4;
    *e = 5;
    
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 0, &Size), 1, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 1, &Size), 2, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 2, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 3, &Size), 4, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 4, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 5, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 6, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    f = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    *f = 6;
    
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 0, &Size), 1, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 1, &Size), 2, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 2, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 3, &Size), 4, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 4, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 5, &Size), 6, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, sizeof(uint64_t) * 6, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    
    XCTAssertEqual(CCMemoryZoneGetPointer(Zone, 0, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    CCMemoryZoneDestroy(Zone);
    
    
    
    Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 16);
    
    a = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    b = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    c = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    d = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    e = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    
    *a = 1;
    *b = 2;
    *c = 3;
    *d = 4;
    *e = 5;
    
    CCMemoryZoneBlock *Block = CCMemoryZoneGetBlock(Zone);
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 0 }, &Size), 1, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 1 }, &Size), 2, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 2 }, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 0 }, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 1 }, &Size), 4, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 2 }, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 0 }, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 1 }, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 0 }, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    ptrdiff_t Offset = 0;
    Block = CCMemoryZoneGetBlock(Zone);
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), 1, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), 2, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), 3, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), 4, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    XCTAssertEqual(*(uint64_t*)CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), 5, @"Should be the correct value");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&Block, &Offset, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    Offset += sizeof(uint64_t);
    
    CCMemoryZoneDeallocate(Zone, SIZE_MAX);
    
    Block = CCMemoryZoneGetBlock(Zone);
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&Block, &(ptrdiff_t){ sizeof(uint64_t) * 0 }, &Size), NULL, @"Should be the correct value");
    XCTAssertEqual(Size, 0, @"Should be the correct value");
    
    CCMemoryZoneDestroy(Zone);
}

-(void) testOffsetRetrieval
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 16);
    
    uint64_t *a = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *b = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *c = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *d = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    uint64_t *e = CCMemoryZoneAllocate(Zone, sizeof(uint64_t));
    
    *a = 1;
    *b = 2;
    *c = 3;
    *d = 4;
    *e = 5;
    
    ptrdiff_t Offset;
    CCMemoryZoneBlock *Block = CCMemoryZoneGetBlockForPointer(Zone, a, &Offset);
    
    size_t Size;
    ptrdiff_t TestOffset = Offset;
    CCMemoryZoneBlock *TestBlock = Block;
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&TestBlock, &TestOffset, &Size), a, @"Should get the correct pointer");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(TestBlock, Block, @"Should be the correct block");
    XCTAssertEqual(TestOffset, Offset, @"Should be the correct offset");
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, b, &Offset);
    TestOffset = Offset;
    TestBlock = Block;
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&TestBlock, &TestOffset, &Size), b, @"Should get the correct pointer");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(TestBlock, Block, @"Should be the correct block");
    XCTAssertEqual(TestOffset, Offset, @"Should be the correct offset");
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, c, &Offset);
    TestOffset = Offset;
    TestBlock = Block;
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&TestBlock, &TestOffset, &Size), c, @"Should get the correct pointer");
    XCTAssertEqual(Size, sizeof(uint64_t) * 2, @"Should be the correct value");
    XCTAssertEqual(TestBlock, Block, @"Should be the correct block");
    XCTAssertEqual(TestOffset, Offset, @"Should be the correct offset");
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, d, &Offset);
    TestOffset = Offset;
    TestBlock = Block;
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&TestBlock, &TestOffset, &Size), d, @"Should get the correct pointer");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(TestBlock, Block, @"Should be the correct block");
    XCTAssertEqual(TestOffset, Offset, @"Should be the correct offset");
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, e, &Offset);
    TestOffset = Offset;
    TestBlock = Block;
    XCTAssertEqual(CCMemoryZoneBlockGetPointer(&TestBlock, &TestOffset, &Size), e, @"Should get the correct pointer");
    XCTAssertEqual(Size, sizeof(uint64_t) * 1, @"Should be the correct value");
    XCTAssertEqual(TestBlock, Block, @"Should be the correct block");
    XCTAssertEqual(TestOffset, Offset, @"Should be the correct offset");
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, e, NULL);
    XCTAssertEqual(TestBlock, Block, @"Should be the correct block");
    
    CCMemoryZoneDestroy(Zone);
}

-(void) testEnumerable
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 16);
    
    uint32_t *x0 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x1 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x2 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x3 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x4 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x5 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x6 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x7 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x8 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x9 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    uint32_t *x10 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    ptrdiff_t Offset;
    CCMemoryZoneBlock *Block = CCMemoryZoneGetBlockForPointer(Zone, x2, &Offset);
    
    CCEnumerable Enumerable2_3;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 2, &Enumerable2_3);
    
    CCEnumerable Enumerable2_8;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 7, &Enumerable2_8);
    
    CCEnumerable Enumerable2_10;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 9, &Enumerable2_10);
    
    CCEnumerable Enumerable2_12;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 11, &Enumerable2_12);
    
    CCEnumerable Enumerable2_Inf;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), SIZE_MAX, &Enumerable2_Inf);
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, x6, &Offset);
    
    CCEnumerable Enumerable6_7;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 2, &Enumerable6_7);
    
    CCEnumerable Enumerable6_Inf;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), SIZE_MAX, &Enumerable6_Inf);
    
    Block = CCMemoryZoneGetBlockForPointer(Zone, x0, &Offset);
    
    CCEnumerable Enumerable0_0;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 1, &Enumerable0_0);
    
    CCEnumerable Enumerable___;
    CCMemoryZoneGetEnumerable(Block, Offset, sizeof(uint32_t), 0, &Enumerable___);
    
    
    //0_0
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable0_0), x0, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable0_0), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable0_0), x0, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable0_0), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable0_0), x0, @"Should get the correct pointer");
    
    
    //___
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable___), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable___), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable___), NULL, @"Should get the correct pointer");
    
    
    //2_3
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable2_3), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_3), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_3), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable2_3), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_3), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_3), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable2_3), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_3), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_3), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_3), x3, @"Should get the correct pointer");
    
    
    //2_8
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable2_8), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable2_8), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable2_8), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_8), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_8), x8, @"Should get the correct pointer");
    
    
    //2_10
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable2_10), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable2_10), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable2_10), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_10), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), x10, @"Should get the correct pointer");
    
    
    //2_12
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable2_12), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable2_12), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable2_12), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_12), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x10, @"Should get the correct pointer");
    
    
    //2_Inf
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable2_Inf), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable2_Inf), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable2_Inf), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x2, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x3, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x4, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x5, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable2_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x10, @"Should get the correct pointer");
    
    
    //6_7
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable6_7), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_7), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_7), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable6_7), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_7), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_7), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable6_7), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_7), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_7), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_7), x7, @"Should get the correct pointer");
    
    
    //6_Inf
    XCTAssertEqual(CCEnumerableGetCurrent(&Enumerable6_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetTail(&Enumerable6_Inf), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), NULL, @"Should get the correct pointer");
    
    XCTAssertEqual(CCEnumerableGetHead(&Enumerable6_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x6, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x7, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x8, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x10, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerablePrevious(&Enumerable6_Inf), x9, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x10, @"Should get the correct pointer");
    
    
    CCEnumerableGetTail(&Enumerable2_10);
    CCEnumerableGetTail(&Enumerable2_12);
    CCEnumerableGetTail(&Enumerable2_Inf);
    CCEnumerableGetTail(&Enumerable6_Inf);
    
    uint32_t *x11 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_10), NULL, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x11, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x11, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x11, @"Should get the correct pointer");
    
    uint32_t *x12 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), x12, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x12, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x12, @"Should get the correct pointer");
    
    uint32_t *x13 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_12), NULL, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x13, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x13, @"Should get the correct pointer");
    
    uint32_t *x14 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x14, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x14, @"Should get the correct pointer");
    
    uint32_t *x15 = CCMemoryZoneAllocate(Zone, sizeof(uint32_t));
    
    XCTAssertEqual(CCEnumerableNext(&Enumerable2_Inf), x15, @"Should get the correct pointer");
    XCTAssertEqual(CCEnumerableNext(&Enumerable6_Inf), x15, @"Should get the correct pointer");
    
    CCMemoryZoneDestroy(Zone);
}

@end
