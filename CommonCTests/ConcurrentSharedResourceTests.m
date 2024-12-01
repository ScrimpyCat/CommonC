/*
 *  Copyright (c) 2024, Stefan Johnson
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
#import "CCString.h"

#define Titem int
#define Tmax 6
#include "ConcurrentSharedResource.h"

static uint64_t ShareCounter = 0;
static int Share(int x)
{
    ShareCounter += (uint64_t)1 << (x * 4);
    
    return x;
}

static uint64_t DestructorCounter = 0;
static void Destructor(int x)
{
    DestructorCounter += (uint64_t)1 << (x * 4);
}

#define Titem int
#define Tmax 3
#define Tshare Share
#define Tdestructor Destructor
#include "ConcurrentSharedResource.h"

#define Titem int
#define Tmax 3
#define Tshare Share
#define Tdestructor Destructor
#define Tunlimited FALSE
#include "ConcurrentSharedResource.h"

@interface ConcurrentSharedResourceTests : XCTestCase
@end

@implementation ConcurrentSharedResourceTests

-(void) testSettingItems
{
    CCConcurrentSharedResource(int, 6, CC_CONCURRENT_SHARED_RESOURCE_DEFAULT_OP, CC_CONCURRENT_SHARED_RESOURCE_DEFAULT_OP, TRUE) I6 = CC_CONCURRENT_SHARED_RESOURCE_INIT;
    
    int Result = CCConcurrentSharedResourceGet(&I6);
    
    XCTAssertEqual(Result, 0, @"Should default to 0");
    
    CCConcurrentSharedResourceSet(&I6, 1);
    
    Result = CCConcurrentSharedResourceGet(&I6);
    
    XCTAssertEqual(Result, 1, @"Should get the current resource");
    
    Result = CCConcurrentSharedResourceGet(&I6);
    
    XCTAssertEqual(Result, 1, @"Should get the current resource");
    
    CCConcurrentSharedResourceSet(&I6, 2);
    CCConcurrentSharedResourceSet(&I6, 3);
    
    Result = CCConcurrentSharedResourceGet(&I6);
    
    XCTAssertEqual(Result, 3, @"Should get the current resource");
    
    Result = CCConcurrentSharedResourceGet(&I6);
    
    XCTAssertEqual(Result, 3, @"Should get the current resource");
    
    for (int Loop = 4; Loop < 10; Loop++)
    {
        CCConcurrentSharedResourceSet(&I6, Loop);
        
        Result = CCConcurrentSharedResourceGet(&I6);
        
        XCTAssertEqual(Result, Loop, @"Should get the current resource");
    }
    
    
    
    CCConcurrentSharedResource(int, 3, Share, Destructor, TRUE) I3a = CC_CONCURRENT_SHARED_RESOURCE_INIT;
    
    Result = CCConcurrentSharedResourceGet(&I3a);
    
    XCTAssertEqual(Result, 0, @"Should default to 0");
    
    CCConcurrentSharedResourceSet(&I3a, 1);
    
    Result = CCConcurrentSharedResourceGet(&I3a);
    
    XCTAssertEqual(Result, 1, @"Should get the current resource");
    
    Result = CCConcurrentSharedResourceGet(&I3a);
    
    XCTAssertEqual(Result, 1, @"Should get the current resource");
    
    CCConcurrentSharedResourceSet(&I3a, 2);
    CCConcurrentSharedResourceSet(&I3a, 3);
    
    Result = CCConcurrentSharedResourceGet(&I3a);
    
    XCTAssertEqual(Result, 3, @"Should get the current resource");
    
    Result = CCConcurrentSharedResourceGet(&I3a);
    
    XCTAssertEqual(Result, 3, @"Should get the current resource");
    
    for (int Loop = 4; Loop < 10; Loop++)
    {
        CCConcurrentSharedResourceSet(&I3a, Loop);
        
        Result = CCConcurrentSharedResourceGet(&I3a);
        
        XCTAssertEqual(Result, Loop, @"Should get the current resource");
    }
    
    XCTAssertEqual(ShareCounter, 0x1111112021, @"Should run the share callback");
    XCTAssertEqual(DestructorCounter, 0x1111113, @"Should run the destructor callback");
    
    atomic_fetch_add(&I3a.nodes[7 % 3].refs, 1);
    
    CCConcurrentSharedResourceSet(&I3a, 10);
    CCConcurrentSharedResourceSet(&I3a, 11);
    CCConcurrentSharedResourceSet(&I3a, 12);
    
    XCTAssertEqual(DestructorCounter, 0x11101111113, @"Should run the destructor callback");
    
    
    
    ShareCounter = 0;
    DestructorCounter = 0;
    CCConcurrentSharedResource(int, 3, Share, Destructor, FALSE) I3b = CC_CONCURRENT_SHARED_RESOURCE_INIT;
    
    Result = CCConcurrentSharedResourceGet(&I3b);
    
    XCTAssertEqual(Result, 0, @"Should default to 0");
    
    CCConcurrentSharedResourceSet(&I3b, 1);
    
    Result = CCConcurrentSharedResourceGet(&I3b);
    
    XCTAssertEqual(Result, 1, @"Should get the current resource");
    
    Result = CCConcurrentSharedResourceGet(&I3b);
    
    XCTAssertEqual(Result, 1, @"Should get the current resource");
    
    CCConcurrentSharedResourceSet(&I3b, 2);
    CCConcurrentSharedResourceSet(&I3b, 3);
    
    Result = CCConcurrentSharedResourceGet(&I3b);
    
    XCTAssertEqual(Result, 3, @"Should get the current resource");
    
    Result = CCConcurrentSharedResourceGet(&I3b);
    
    XCTAssertEqual(Result, 3, @"Should get the current resource");
    
    for (int Loop = 4; Loop < 10; Loop++)
    {
        CCConcurrentSharedResourceSet(&I3b, Loop);
        
        Result = CCConcurrentSharedResourceGet(&I3b);
        
        XCTAssertEqual(Result, Loop, @"Should get the current resource");
    }
    
    XCTAssertEqual(ShareCounter, 0x1111112021, @"Should run the share callback");
    XCTAssertEqual(DestructorCounter, 0x1111113, @"Should run the destructor callback");
    
    atomic_fetch_add(&I3b.nodes[7 % 3].refs, 1);
    
    CCConcurrentSharedResourceSet(&I3b, 10);
    CCConcurrentSharedResourceSet(&I3b, 11);
    CCConcurrentSharedResourceSet(&I3b, 12);
    
    XCTAssertEqual(DestructorCounter, 0x11101111113, @"Should run the destructor callback");
}

@end
