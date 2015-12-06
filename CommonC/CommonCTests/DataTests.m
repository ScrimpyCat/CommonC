/*
 *  Copyright (c) 2015, Stefan Johnson
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

#import "DataTests.h"
#import "MemoryAllocation.h"
#import "Data.h"


static void *TestConstructorCallback(CCAllocatorType Allocator, CCDataHint Hint, size_t *Data)
{
    size_t *Ptr = CCMalloc(Allocator, *Data + sizeof(size_t), NULL, CC_DEFAULT_ERROR_CALLBACK);
    *Ptr = *Data;
    
    return Ptr;
}

static void TestDestructorCallback(void *Internal)
{
    CCFree(Internal);
}

static size_t TestGetSizeCallback(void *Internal)
{
    return *(size_t*)Internal;
}

CCBufferMap TestMapBufferCallback(void *Internal, ptrdiff_t Offset, size_t Size, CCDataHint Access)
{
    CCBufferMap Map = (CCBufferMap){
        .ptr = CCMalloc(CC_STD_ALLOCATOR, Size, NULL, CC_DEFAULT_ERROR_CALLBACK),
        .offset = Offset,
        .size = Size,
        .hint = Access
    };
    
    if (Access & CCDataHintRead) memcpy(Map.ptr, Internal + sizeof(size_t) + Offset, Size);

    return Map;
}

static void TestUnmapBufferCallback(void *Internal, CCBufferMap Map)
{
    if (Map.hint & CCDataHintWrite)
    {
        memcpy(Internal + sizeof(size_t) + Map.offset, Map.ptr, Map.size);
    }
    
    CCFree(Map.ptr);
}

static CCDataHint TestGetHint(void *Internal)
{
    return CCDataHintReadWrite;
}



static CCDataInterface TestDataInternal = {
    .create = (CCDataConstructorCallback)TestConstructorCallback,
    .destroy = TestDestructorCallback,
    .hints = TestGetHint,
    .size = TestGetSizeCallback,
    .map = TestMapBufferCallback,
    .unmap = TestUnmapBufferCallback
};


static size_t TestGetPreferredMapSizeCallback(void *Internal)
{
    return 5;
}

static CCDataInterface TestDataInternalSmallBlock = {
    .create = (CCDataConstructorCallback)TestConstructorCallback,
    .destroy = TestDestructorCallback,
    .hints = TestGetHint,
    .size = TestGetSizeCallback,
    .map = TestMapBufferCallback,
    .unmap = TestUnmapBufferCallback,
    .optional = {
        .preferredMapSize = TestGetPreferredMapSizeCallback
    }
};

@implementation DataTests
@synthesize interface;

-(CCData) createDataOfSize: (size_t)size WithHint: (CCDataHint)hint
{
    return CCDataCreate(CC_STD_ALLOCATOR, hint, &size, NULL, NULL, self.interface);
}

-(void) setUp
{
    [super setUp];
    self.interface = &TestDataInternal;
}

-(void) tearDown
{
    [super tearDown];
}

-(void) testSize
{
    CCData Data = [self createDataOfSize: 1 WithHint: 0];
    XCTAssertEqual(CCDataGetSize(Data), 1, @"Should have correct size");
    CCDataDestroy(Data);
    
    Data = [self createDataOfSize: 100 WithHint: 0];
    XCTAssertEqual(CCDataGetSize(Data), 100, @"Should have correct size");
    CCDataDestroy(Data);
}

-(void) testReadWrite
{
    CCData Data = [self createDataOfSize: sizeof(uint8_t) * 4 WithHint: CCDataHintReadWrite];
    
    uint8_t Buffer[4];
    XCTAssertEqual(CCDataWriteBuffer(Data, 0, sizeof(uint8_t) * 4, (uint8_t[4]){ 1, 2, 3, 4 }), 4, @"Should have written the correct number of bytes");
    XCTAssertEqual(CCDataReadBuffer(Data, 1, sizeof(uint8_t) * 2, Buffer), 2, @"Should have read the correct number of bytes");
    XCTAssertEqual(Buffer[0], 2, @"Should have the correct value");
    XCTAssertEqual(Buffer[1], 3, @"Should have the correct value");
    
    
    XCTAssertEqual(CCDataWriteBuffer(Data, 1, sizeof(uint8_t) * 2, (uint8_t[2]){ 50, 51 }), 2, @"Should have written the correct number of bytes");
    XCTAssertEqual(CCDataReadBuffer(Data, 0, sizeof(uint8_t) * 4, Buffer), 4, @"Should have read the correct number of bytes");
    XCTAssertEqual(Buffer[0], 1, @"Should have the correct value");
    XCTAssertEqual(Buffer[1], 50, @"Should have the correct value");
    XCTAssertEqual(Buffer[2], 51, @"Should have the correct value");
    XCTAssertEqual(Buffer[3], 4, @"Should have the correct value");
    
    CCDataDestroy(Data);
}

-(void) testHash
{
    CCData Data = [self createDataOfSize: sizeof(uint8_t) * 10 WithHint: CCDataHintReadWrite];
    
    CCDataWriteBuffer(Data, 0, sizeof(uint8_t) * 10, (uint8_t[10]){ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    
    XCTAssertEqual(CCDataGetHash(Data), 1305033930, @"Should have the correct hash");
    XCTAssertEqual(CCDataGetHash(Data), 1305033930, @"Should have the correct hash");
    
    CCDataWriteBuffer(Data, 1, sizeof(uint8_t), &(uint8_t){ 1 });
    
    XCTAssertEqual(CCDataGetHash(Data), 1915273679, @"Should have the correct hash");
    
    
    CCData Data2 = [self createDataOfSize: sizeof(uint8_t) * 10 WithHint: CCDataHintReadWrite];
    
    CCDataCopyBuffer(Data, 0, sizeof(uint8_t) * 10, Data2, 0);
    XCTAssertEqual(CCDataGetHash(Data2), CCDataGetHash(Data), @"Should have the correct hash");
    
    
    CCDataDestroy(Data2);
    CCDataDestroy(Data);
}

@end


@interface DataSmallBlockTests : DataTests
@end

@implementation DataSmallBlockTests

-(const CCDataInterface*) interface
{
    return &TestDataInternalSmallBlock;
}

@end

