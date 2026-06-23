/*
 *  Copyright (c) 2026, Stefan Johnson
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
#import "Crypto.h"

@interface CryptoTests : XCTestCase
@end

@implementation CryptoTests

static void HashA(size_t Size, uint32_t *Result)
{
    CCCryptoSha1State State = CCCryptoSha1StateInit();
    const CCCryptoSha1Constants Constants = CCCryptoSha1ConstantsInit();
    
    uint8_t Data[64 * 3];
    
    memset(Data, 0, sizeof(Data));
    
    memset(Data, 0x61, Size);
    
    size_t Blocks = CCCryptoSha1Prepare(Data, Size);
    
    for (size_t Loop = 0; Loop < Blocks; Loop++)
    {
        State = CCCryptoSha1Process(State, Data + (Loop * 64), Constants);
    }
    
    CCCryptoSha1Store(State, Result);
    
    
    uint32_t Hash[5];
    CCCryptoSha1Store(CCCryptoSha1(Data, Size), Hash);
    
    XCTAssertEqual(Result[0], Hash[0],  @"Calculated the same hash");
    XCTAssertEqual(Result[1], Hash[1],  @"Calculated the same hash");
    XCTAssertEqual(Result[2], Hash[2],  @"Calculated the same hash");
    XCTAssertEqual(Result[3], Hash[3],  @"Calculated the same hash");
    XCTAssertEqual(Result[4], Hash[4],  @"Calculated the same hash");
}

-(void) testSha1
{
    uint32_t Result[5];
    
    /*
     echo -n "" | sha1
     da39a3ee5e6b4b0d3255bfef95601890afd80709
     */
    HashA(0, Result);
    XCTAssertEqual(Result[0], 0xda39a3ee,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x5e6b4b0d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x3255bfef,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x95601890,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xafd80709,  @"Calculated the correct hash");
    
    
    /*
     echo -n "aaa" | sha1
     7e240de74fb1ed08fa08d38063f6a6a91462a815
     */
    HashA(3, Result);
    XCTAssertEqual(Result[0], 0x7e240de7,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x4fb1ed08,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xfa08d380,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x63f6a6a9,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x1462a815,  @"Calculated the correct hash");
    
    CCCryptoSha1Store(CCCryptoSha1("aaa", 3), Result);
    XCTAssertEqual(Result[0], 0x7e240de7,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x4fb1ed08,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xfa08d380,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x63f6a6a9,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x1462a815,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*55" | sha1
     c1c8bbdc22796e28c0e15163d20899b65621d65a
     */
    HashA(55, Result);
    XCTAssertEqual(Result[0], 0xc1c8bbdc,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x22796e28,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xc0e15163,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xd20899b6,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x5621d65a,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*56" | sha1
     c2db330f6083854c99d4b5bfb6e8f29f201be699
     */
    HashA(56, Result);
    XCTAssertEqual(Result[0], 0xc2db330f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x6083854c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x99d4b5bf,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xb6e8f29f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x201be699,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*57" | sha1
     f08f24908d682555111be7ff6f004e78283d989a
     */
    HashA(57, Result);
    XCTAssertEqual(Result[0], 0xf08f2490,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x8d682555,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x111be7ff,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x6f004e78,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x283d989a,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*58" | sha1
     5ee0f8895f4e1aae6a6661de5c432e34188a5a2d
     */
    HashA(58, Result);
    XCTAssertEqual(Result[0], 0x5ee0f889,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x5f4e1aae,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x6a6661de,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x5c432e34,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x188a5a2d,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*59" | sha1
     dbc8b8f59ff85a2b1448ed873484b14bf0507246
     */
    HashA(59, Result);
    XCTAssertEqual(Result[0], 0xdbc8b8f5,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x9ff85a2b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x1448ed87,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x3484b14b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xf0507246,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*60" | sha1
     13d956033d9af449bfe2c4ef78c17c20469c4bf1
     */
    HashA(60, Result);
    XCTAssertEqual(Result[0], 0x13d95603,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x3d9af449,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xbfe2c4ef,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x78c17c20,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x469c4bf1,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*61" | sha1
     aeab141db28af3353283b5ccb2a322df0b9b5f56
     */
    HashA(61, Result);
    XCTAssertEqual(Result[0], 0xaeab141d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xb28af335,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x3283b5cc,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xb2a322df,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x0b9b5f56,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*62" | sha1
     67b4b3923fa178d788a9611b76446c96431071f2
     */
    HashA(62, Result);
    XCTAssertEqual(Result[0], 0x67b4b392,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x3fa178d7,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x88a9611b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x76446c96,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x431071f2,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*63" | sha1
     03f09f5b158a7a8cdad920bddc29b81c18a551f5
     */
    HashA(63, Result);
    XCTAssertEqual(Result[0], 0x03f09f5b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x158a7a8c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xdad920bd,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xdc29b81c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x18a551f5,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*64" | sha1
     0098ba824b5c16427bd7a1122a5a442a25ec644d
     */
    HashA(64, Result);
    XCTAssertEqual(Result[0], 0x0098ba82,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x4b5c1642,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x7bd7a112,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x2a5a442a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x25ec644d,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*65" | sha1
     11655326c708d70319be2610e8a57d9a5b959d3b
     */
    HashA(65, Result);
    XCTAssertEqual(Result[0], 0x11655326,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xc708d703,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x19be2610,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xe8a57d9a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x5b959d3b,  @"Calculated the correct hash");
}

@end
