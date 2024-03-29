/*
 *  Copyright (c) 2021, Stefan Johnson
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
#import "MemoryAllocation.h"
#import "Data.h"
#import "DataBuffer.h"

#define Tbuffer PTYPE(uint8_t *)
#include <CommonC/Memory.h>

#define Tbuffer PTYPE(uint16_t *)
#include <CommonC/Memory.h>

#define Tbuffer PTYPE(uint32_t *)
#include <CommonC/Memory.h>

#define CC_GENERIC_PRESERVE_HEADER
#define CC_GENERIC_TEMPLATE <CommonC/DataMemoryTemplate.h>

#define Tmemory CCData
#define Tbuffer PTYPE(uint8_t *)
#include <CommonC/Memory.h>

#define Tmemory CCData
#define Tbuffer PTYPE(uint32_t *)
#include <CommonC/Memory.h>

#undef CC_GENERIC_PRESERVE_HEADER
#undef CC_GENERIC_TEMPLATE

@interface MemoryTemplateTests : XCTestCase

@end

@implementation MemoryTemplateTests

-(void) testRead
{
    uint8_t aIn[3] = { 1, 2, 3 }, aOut[10];
    CCMemoryRead((void*)aIn, sizeof(aIn), 0, sizeof(aOut), aOut);
    XCTAssertEqual(aOut[0], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[5], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[6], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[7], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[8], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[9], 1, @"Should have the correct value");
    
    CCMemoryRead(aIn, sizeof(aIn), 1, sizeof(aOut), aOut);
    XCTAssertEqual(aOut[0], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[5], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[6], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[7], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[8], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[9], 2, @"Should have the correct value");
    
    CCMemoryReadBig(aIn, sizeof(aIn), 1, sizeof(aOut), aOut);
    XCTAssertEqual(aOut[0], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[5], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[6], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[7], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[8], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[9], 2, @"Should have the correct value");
    
    uint16_t bIn[3] = { 0x01f1, 0x02f2, 0x03f3 }, bOut[10];
    CCMemoryRead((void*)bIn, sizeof(bIn), 0, sizeof(bOut), bOut);
    XCTAssertEqual(bOut[0], 0x01f1, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 0x02f2, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 0x03f3, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 0x01f1, @"Should have the correct value");
    XCTAssertEqual(bOut[4], 0x02f2, @"Should have the correct value");
    XCTAssertEqual(bOut[5], 0x03f3, @"Should have the correct value");
    XCTAssertEqual(bOut[6], 0x01f1, @"Should have the correct value");
    XCTAssertEqual(bOut[7], 0x02f2, @"Should have the correct value");
    XCTAssertEqual(bOut[8], 0x03f3, @"Should have the correct value");
    XCTAssertEqual(bOut[9], 0x01f1, @"Should have the correct value");
    
    CCMemoryRead(bIn, sizeof(bIn), 1, sizeof(bOut), bOut);
    XCTAssertEqual(bOut[0], 0xf201, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 0xf302, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 0xf103, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 0xf201, @"Should have the correct value");
    XCTAssertEqual(bOut[4], 0xf302, @"Should have the correct value");
    XCTAssertEqual(bOut[5], 0xf103, @"Should have the correct value");
    XCTAssertEqual(bOut[6], 0xf201, @"Should have the correct value");
    XCTAssertEqual(bOut[7], 0xf302, @"Should have the correct value");
    XCTAssertEqual(bOut[8], 0xf103, @"Should have the correct value");
    XCTAssertEqual(bOut[9], 0xf201, @"Should have the correct value");
    
    CCMemoryReadBig(bIn, sizeof(bIn), 1, sizeof(bOut), bOut);
    XCTAssertEqual(bOut[0], 0x01f2, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 0x02f3, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 0x03f1, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 0x01f2, @"Should have the correct value");
    XCTAssertEqual(bOut[4], 0x02f3, @"Should have the correct value");
    XCTAssertEqual(bOut[5], 0x03f1, @"Should have the correct value");
    XCTAssertEqual(bOut[6], 0x01f2, @"Should have the correct value");
    XCTAssertEqual(bOut[7], 0x02f3, @"Should have the correct value");
    XCTAssertEqual(bOut[8], 0x03f1, @"Should have the correct value");
    XCTAssertEqual(bOut[9], 0x01f2, @"Should have the correct value");
    
    uint32_t cIn[3] = { 0x01f1e1d1, 0x02f2e2d2, 0x03f3e3d3 }, cOut[10];
    CCMemoryRead((void*)cIn, sizeof(cIn), 0, sizeof(cOut), cOut);
    XCTAssertEqual(cOut[0], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 0x01f1e1d1, @"Should have the correct value");
    
    CCMemoryRead(cIn, sizeof(cIn), 1, sizeof(cOut), cOut);
    XCTAssertEqual(cOut[0], 0xd201f1e1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xd302f2e2, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xd103f3e3, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0xd201f1e1, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0xd302f2e2, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 0xd103f3e3, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 0xd201f1e1, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 0xd302f2e2, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 0xd103f3e3, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 0xd201f1e1, @"Should have the correct value");
    
    CCMemoryReadBig(cIn, sizeof(cIn), 1, sizeof(cOut), cOut);
    XCTAssertEqual(cOut[0], 0xe1f101d2, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xe2f202d3, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xe3f303d1, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0xe1f101d2, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0xe2f202d3, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 0xe3f303d1, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 0xe1f101d2, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 0xe2f202d3, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 0xe3f303d1, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 0xe1f101d2, @"Should have the correct value");
    
    CCData Data = CCDataBufferCreate(CC_STD_ALLOCATOR, CCDataHintReadWrite, sizeof(cIn), cIn, NULL, NULL);
    
    CCMemoryRead(Data, CCDataGetSize(Data), 0, sizeof(cOut), cOut);
    XCTAssertEqual(cOut[0], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 0x01f1e1d1, @"Should have the correct value");
    
    CCMemoryRead(Data, sizeof(cIn), 1, sizeof(cOut), cOut);
    XCTAssertEqual(cOut[0], 0xd201f1e1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xd302f2e2, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xd103f3e3, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0xd201f1e1, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0xd302f2e2, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 0xd103f3e3, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 0xd201f1e1, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 0xd302f2e2, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 0xd103f3e3, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 0xd201f1e1, @"Should have the correct value");
    
    CCMemoryReadBig(Data, sizeof(cIn), 1, sizeof(cOut), cOut);
    XCTAssertEqual(cOut[0], 0xe1f101d2, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xe2f202d3, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xe3f303d1, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0xe1f101d2, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0xe2f202d3, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 0xe3f303d1, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 0xe1f101d2, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 0xe2f202d3, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 0xe3f303d1, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 0xe1f101d2, @"Should have the correct value");
    
    CCMemoryRead(Data, CCDataGetSize(Data), 0, sizeof(aOut), aOut);
    XCTAssertEqual(aOut[0], 0xd1, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 0xe1, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 0xf1, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 0x01, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 0xd2, @"Should have the correct value");
    XCTAssertEqual(aOut[5], 0xe2, @"Should have the correct value");
    XCTAssertEqual(aOut[6], 0xf2, @"Should have the correct value");
    XCTAssertEqual(aOut[7], 0x02, @"Should have the correct value");
    XCTAssertEqual(aOut[8], 0xd3, @"Should have the correct value");
    XCTAssertEqual(aOut[9], 0xe3, @"Should have the correct value");
    
    CCMemoryRead(Data, CCDataGetSize(Data), 1, sizeof(aOut), aOut);
    XCTAssertEqual(aOut[0], 0xe1, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 0xf1, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 0x01, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 0xd2, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 0xe2, @"Should have the correct value");
    XCTAssertEqual(aOut[5], 0xf2, @"Should have the correct value");
    XCTAssertEqual(aOut[6], 0x02, @"Should have the correct value");
    XCTAssertEqual(aOut[7], 0xd3, @"Should have the correct value");
    XCTAssertEqual(aOut[8], 0xe3, @"Should have the correct value");
    XCTAssertEqual(aOut[9], 0xf3, @"Should have the correct value");

    CCDataDestroy(Data);
}

-(void) testWrite
{
    uint8_t aIn[3] = { 1, 2, 3 }, aOut[10] = {0};
    CCMemoryWrite((void*)aOut, sizeof(aOut), 0, sizeof(aIn), aIn);
    XCTAssertEqual(aOut[0], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 0, @"Should have the correct value");
    
    CCMemoryWrite(aOut, sizeof(aOut), 1, sizeof(aIn), aIn);
    XCTAssertEqual(aOut[0], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 0, @"Should have the correct value");
    
    CCMemoryWriteBig(aOut, sizeof(aOut), 1, sizeof(aIn), aIn);
    XCTAssertEqual(aOut[0], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 1, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 0, @"Should have the correct value");
    
    CCMemoryWrite(aOut, sizeof(aOut), 1, 11, ((uint8_t[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }));
    XCTAssertEqual(aOut[0], 10, @"Should have the correct value");
    XCTAssertEqual(aOut[1], 11, @"Should have the correct value");
    XCTAssertEqual(aOut[2], 2, @"Should have the correct value");
    XCTAssertEqual(aOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(aOut[4], 4, @"Should have the correct value");
    XCTAssertEqual(aOut[5], 5, @"Should have the correct value");
    XCTAssertEqual(aOut[6], 6, @"Should have the correct value");
    XCTAssertEqual(aOut[7], 7, @"Should have the correct value");
    XCTAssertEqual(aOut[8], 8, @"Should have the correct value");
    XCTAssertEqual(aOut[9], 9, @"Should have the correct value");
    
    uint16_t bIn[3] = { 0x01f1, 0x02f2, 0x03f3 }, bOut[10] = {0};
    CCMemoryWrite((void*)bOut, sizeof(bOut), 0, sizeof(bIn), bIn);
    XCTAssertEqual(bOut[0], 0x01f1, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 0x02f2, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 0x03f3, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 0, @"Should have the correct value");
    
    CCMemoryWrite(bOut, sizeof(bOut), 1, sizeof(bIn), bIn);
    XCTAssertEqual(bOut[0], 0xf1f1, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 0xf201, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 0xf302, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(bOut[4], 0, @"Should have the correct value");
    
    CCMemoryWriteBig(bOut, sizeof(bOut), 1, sizeof(bIn), bIn);
    XCTAssertEqual(bOut[0], 0x01f1, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 0x02f1, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 0x03f2, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 0xf3, @"Should have the correct value");
    XCTAssertEqual(bOut[4], 0, @"Should have the correct value");
    
    CCMemoryWrite(bOut, sizeof(bOut), 2, 22, ((uint16_t[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }));
    XCTAssertEqual(bOut[0], 10, @"Should have the correct value");
    XCTAssertEqual(bOut[1], 11, @"Should have the correct value");
    XCTAssertEqual(bOut[2], 2, @"Should have the correct value");
    XCTAssertEqual(bOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(bOut[4], 4, @"Should have the correct value");
    XCTAssertEqual(bOut[5], 5, @"Should have the correct value");
    XCTAssertEqual(bOut[6], 6, @"Should have the correct value");
    XCTAssertEqual(bOut[7], 7, @"Should have the correct value");
    XCTAssertEqual(bOut[8], 8, @"Should have the correct value");
    XCTAssertEqual(bOut[9], 9, @"Should have the correct value");
    
    uint32_t cIn[3] = { 0x01f1e1d1, 0x02f2e2d2, 0x03f3e3d3 }, cOut[10] = {0};
    CCMemoryWrite((void*)cOut, sizeof(cOut), 0, sizeof(cIn), cIn);
    XCTAssertEqual(cOut[0], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0, @"Should have the correct value");
    
    CCMemoryWrite(cOut, sizeof(cOut), 1, sizeof(cIn), cIn);
    
    XCTAssertEqual(cOut[0], 0xf1e1d1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xf2e2d201, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xf3e3d302, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0, @"Should have the correct value");
    
    CCMemoryWriteBig(cOut, sizeof(cOut), 1, sizeof(cIn), cIn);
    XCTAssertEqual(cOut[0], 0xe1f101d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xe2f202d1, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xe3f303d2, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0xd3, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0, @"Should have the correct value");
    
    CCMemoryWrite(cOut, sizeof(cOut), 4, 44, ((uint32_t[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }));
    XCTAssertEqual(cOut[0], 10, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 11, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 2, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 4, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 5, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 6, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 7, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 8, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 9, @"Should have the correct value");
    
    memset(cOut, 0, sizeof(cOut));
    
    CCData Data = CCDataBufferCreate(CC_STD_ALLOCATOR, CCDataHintReadWrite, sizeof(cOut), cOut, NULL, NULL);
    
    CCMemoryWrite(Data, CCDataGetSize(Data), 0, sizeof(cIn), cIn);
    XCTAssertEqual(cOut[0], 0x01f1e1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0x02f2e2d2, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0x03f3e3d3, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0, @"Should have the correct value");
    
    CCMemoryWrite(Data, sizeof(cOut), 1, sizeof(cIn), cIn);
    XCTAssertEqual(cOut[0], 0xf1e1d1d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xf2e2d201, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xf3e3d302, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0, @"Should have the correct value");
    
    CCMemoryWriteBig(Data, sizeof(cOut), 1, sizeof(cIn), cIn);
    XCTAssertEqual(cOut[0], 0xe1f101d1, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0xe2f202d1, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 0xe3f303d2, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 0xd3, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 0, @"Should have the correct value");
    
    cOut[1] = 0;
    
    CCMemoryWrite(Data, CCDataGetSize(Data), 0, sizeof(aIn), aIn);
    XCTAssertEqual(cOut[0], 0xe1030201, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0, @"Should have the correct value");
    
    CCMemoryWrite(Data, CCDataGetSize(Data), 1, sizeof(aIn), aIn);
    XCTAssertEqual(cOut[0], 0x03020101, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 0, @"Should have the correct value");
    
    CCMemoryWrite(Data, CCDataGetSize(Data), 4, 44, ((uint32_t[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }));
    XCTAssertEqual(cOut[0], 10, @"Should have the correct value");
    XCTAssertEqual(cOut[1], 11, @"Should have the correct value");
    XCTAssertEqual(cOut[2], 2, @"Should have the correct value");
    XCTAssertEqual(cOut[3], 3, @"Should have the correct value");
    XCTAssertEqual(cOut[4], 4, @"Should have the correct value");
    XCTAssertEqual(cOut[5], 5, @"Should have the correct value");
    XCTAssertEqual(cOut[6], 6, @"Should have the correct value");
    XCTAssertEqual(cOut[7], 7, @"Should have the correct value");
    XCTAssertEqual(cOut[8], 8, @"Should have the correct value");
    XCTAssertEqual(cOut[9], 9, @"Should have the correct value");
    
    CCDataDestroy(Data);
}

@end
