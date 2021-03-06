/*
 *  Copyright (c) 2019, Stefan Johnson
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
#import "Container.h"

@interface ContainerTests : XCTestCase

@end

@implementation ContainerTests

CC_CONTAINER_DECLARE(int32_t, int8_t);
CC_CONTAINER_DECLARE(int32_t, int8_t, int16_t);
CC_CONTAINER_DECLARE(int16_t, CC_CONTAINER(int32_t, int8_t));

typedef int8_t int32_t_int16_t;

-(void) testExample
{
    XCTAssertEqual(sizeof(CC_CONTAINER(int32_t, int8_t)), sizeof(int32_t), @"Should be the same size as the original");
    XCTAssertEqual(sizeof(CC_CONTAINER(int32_t, int16_t)), sizeof(int8_t), @"Should be the size of the explicit alias");
#define CC_CONTAINER_TYPE_DISABLE
    XCTAssertEqual(sizeof(CC_CONTAINER(int32_t, int16_t)), sizeof(int32_t), @"Should not reference the alias");
#undef CC_CONTAINER_TYPE_DISABLE
    
    XCTAssertEqual(sizeof(int32_t_int8_t), sizeof(int32_t), @"Should create an alias");
    XCTAssertEqual(sizeof(int32_t_int8_t_int16_t), sizeof(int32_t), @"Should create an alias");
    XCTAssertEqual(sizeof(int16_t_int32_t_int8_t), sizeof(int16_t), @"Should create an alias");
    
    XCTAssertEqual(sizeof(CC_CONTAINER(int16_t, CC_CONTAINER(int32_t, int8_t))), sizeof(int16_t), @"Should handle nesting");
}

@end
