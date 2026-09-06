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

static void Sha1HashA(size_t Size, uint32_t *Result)
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
    Sha1HashA(0, Result);
    XCTAssertEqual(Result[0], 0xda39a3ee,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x5e6b4b0d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x3255bfef,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x95601890,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xafd80709,  @"Calculated the correct hash");
    
    
    /*
     echo -n "aaa" | sha1
     7e240de74fb1ed08fa08d38063f6a6a91462a815
     */
    Sha1HashA(3, Result);
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
    Sha1HashA(55, Result);
    XCTAssertEqual(Result[0], 0xc1c8bbdc,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x22796e28,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xc0e15163,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xd20899b6,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x5621d65a,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*56" | sha1
     c2db330f6083854c99d4b5bfb6e8f29f201be699
     */
    Sha1HashA(56, Result);
    XCTAssertEqual(Result[0], 0xc2db330f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x6083854c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x99d4b5bf,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xb6e8f29f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x201be699,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*57" | sha1
     f08f24908d682555111be7ff6f004e78283d989a
     */
    Sha1HashA(57, Result);
    XCTAssertEqual(Result[0], 0xf08f2490,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x8d682555,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x111be7ff,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x6f004e78,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x283d989a,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*58" | sha1
     5ee0f8895f4e1aae6a6661de5c432e34188a5a2d
     */
    Sha1HashA(58, Result);
    XCTAssertEqual(Result[0], 0x5ee0f889,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x5f4e1aae,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x6a6661de,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x5c432e34,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x188a5a2d,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*59" | sha1
     dbc8b8f59ff85a2b1448ed873484b14bf0507246
     */
    Sha1HashA(59, Result);
    XCTAssertEqual(Result[0], 0xdbc8b8f5,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x9ff85a2b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x1448ed87,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x3484b14b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xf0507246,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*60" | sha1
     13d956033d9af449bfe2c4ef78c17c20469c4bf1
     */
    Sha1HashA(60, Result);
    XCTAssertEqual(Result[0], 0x13d95603,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x3d9af449,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xbfe2c4ef,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x78c17c20,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x469c4bf1,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*61" | sha1
     aeab141db28af3353283b5ccb2a322df0b9b5f56
     */
    Sha1HashA(61, Result);
    XCTAssertEqual(Result[0], 0xaeab141d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xb28af335,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x3283b5cc,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xb2a322df,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x0b9b5f56,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*62" | sha1
     67b4b3923fa178d788a9611b76446c96431071f2
     */
    Sha1HashA(62, Result);
    XCTAssertEqual(Result[0], 0x67b4b392,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x3fa178d7,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x88a9611b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x76446c96,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x431071f2,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*63" | sha1
     03f09f5b158a7a8cdad920bddc29b81c18a551f5
     */
    Sha1HashA(63, Result);
    XCTAssertEqual(Result[0], 0x03f09f5b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x158a7a8c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xdad920bd,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xdc29b81c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x18a551f5,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*64" | sha1
     0098ba824b5c16427bd7a1122a5a442a25ec644d
     */
    Sha1HashA(64, Result);
    XCTAssertEqual(Result[0], 0x0098ba82,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x4b5c1642,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x7bd7a112,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x2a5a442a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x25ec644d,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*65" | sha1
     11655326c708d70319be2610e8a57d9a5b959d3b
     */
    Sha1HashA(65, Result);
    XCTAssertEqual(Result[0], 0x11655326,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xc708d703,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x19be2610,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xe8a57d9a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x5b959d3b,  @"Calculated the correct hash");
}

static void Sha256HashA(size_t Size, uint32_t *Result)
{
    CCCryptoSha256State State = CCCryptoSha256StateInit();
    const CCCryptoSha256Constants Constants = CCCryptoSha256ConstantsInit();
    
    uint8_t Data[64 * 3];
    
    memset(Data, 0, sizeof(Data));
    
    memset(Data, 0x61, Size);
    
    size_t Blocks = CCCryptoSha256Prepare(Data, Size);
    
    for (size_t Loop = 0; Loop < Blocks; Loop++)
    {
        State = CCCryptoSha256Process(State, Data + (Loop * 64), Constants);
    }
    
    CCCryptoSha256Store(State, Result);
    
    uint32_t Hash[8];
    CCCryptoSha256Store(CCCryptoSha256(Data, Size), Hash);
    
    XCTAssertEqual(Result[0], Hash[0],  @"Calculated the same hash");
    XCTAssertEqual(Result[1], Hash[1],  @"Calculated the same hash");
    XCTAssertEqual(Result[2], Hash[2],  @"Calculated the same hash");
    XCTAssertEqual(Result[3], Hash[3],  @"Calculated the same hash");
    XCTAssertEqual(Result[4], Hash[4],  @"Calculated the same hash");
    XCTAssertEqual(Result[5], Hash[5],  @"Calculated the same hash");
    XCTAssertEqual(Result[6], Hash[6],  @"Calculated the same hash");
    XCTAssertEqual(Result[7], Hash[7],  @"Calculated the same hash");
}

-(void) testSha256
{
    uint32_t Result[8];
    
    /*
     echo -n "" | sha256
     e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
     */
    Sha256HashA(0, Result);
    XCTAssertEqual(Result[0], 0xe3b0c442,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x98fc1c14,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x9afbf4c8,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x996fb924,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x27ae41e4,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x649b934c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0xa495991b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x7852b855,  @"Calculated the correct hash");
    
    
    /*
     echo -n "aaa" | sha256
     9834876dcfb05cb167a5c24953eba58c4ac89b1adf57f28f2f9d09af107ee8f0
     */
    Sha256HashA(3, Result);
    XCTAssertEqual(Result[0], 0x9834876d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xcfb05cb1,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x67a5c249,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x53eba58c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x4ac89b1a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xdf57f28f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x2f9d09af,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x107ee8f0,  @"Calculated the correct hash");
    
    CCCryptoSha256Store(CCCryptoSha256("aaa", 3), Result);
    XCTAssertEqual(Result[0], 0x9834876d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xcfb05cb1,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x67a5c249,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x53eba58c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x4ac89b1a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xdf57f28f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x2f9d09af,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x107ee8f0,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*55" | sha256
     9f4390f8d30c2dd92ec9f095b65e2b9ae9b0a925a5258e241c9f1e910f734318
     */
    Sha256HashA(55, Result);
    XCTAssertEqual(Result[0], 0x9f4390f8,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xd30c2dd9,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x2ec9f095,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xb65e2b9a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xe9b0a925,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xa5258e24,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x1c9f1e91,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x0f734318,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*56" | sha256
     b35439a4ac6f0948b6d6f9e3c6af0f5f590ce20f1bde7090ef7970686ec6738a
     */
    Sha256HashA(56, Result);
    XCTAssertEqual(Result[0], 0xb35439a4,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xac6f0948,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xb6d6f9e3,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xc6af0f5f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x590ce20f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x1bde7090,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0xef797068,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x6ec6738a,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*57" | sha256
     f13b2d724659eb3bf47f2dd6af1accc87b81f09f59f2b75e5c0bed6589dfe8c6
     */
    Sha256HashA(57, Result);
    XCTAssertEqual(Result[0], 0xf13b2d72,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x4659eb3b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xf47f2dd6,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xaf1accc8,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x7b81f09f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x59f2b75e,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x5c0bed65,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x89dfe8c6,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*58" | sha256
     d5c039b748aa64665782974ec3dc3025c042edf54dcdc2b5de31385b094cb678
     */
    Sha256HashA(58, Result);
    XCTAssertEqual(Result[0], 0xd5c039b7,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x48aa6466,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x5782974e,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xc3dc3025,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xc042edf5,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x4dcdc2b5,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0xde31385b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x094cb678,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*59" | sha256
     111bb261277afd65f0744b247cd3e47d386d71563d0ed995517807d5ebd4fba3
     */
    Sha256HashA(59, Result);
    XCTAssertEqual(Result[0], 0x111bb261,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x277afd65,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xf0744b24,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x7cd3e47d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x386d7156,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x3d0ed995,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x517807d5,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0xebd4fba3,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*60" | sha256
     11ee391211c6256460b6ed375957fadd8061cafbb31daf967db875aebd5aaad4
     */
    Sha256HashA(60, Result);
    XCTAssertEqual(Result[0], 0x11ee3912,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x11c62564,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x60b6ed37,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x5957fadd,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x8061cafb,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xb31daf96,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x7db875ae,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0xbd5aaad4,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*61" | sha256
     35d5fc17cfbbadd00f5e710ada39f194c5ad7c766ad67072245f1fad45f0f530
     */
    Sha256HashA(61, Result);
    XCTAssertEqual(Result[0], 0x35d5fc17,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xcfbbadd0,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x0f5e710a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xda39f194,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xc5ad7c76,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x6ad67072,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x245f1fad,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x45f0f530,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*62" | sha256
     f506898cc7c2e092f9eb9fadae7ba50383f5b46a2a4fe5597dbb553a78981268
     */
    Sha256HashA(62, Result);
    XCTAssertEqual(Result[0], 0xf506898c,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0xc7c2e092,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xf9eb9fad,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xae7ba503,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x83f5b46a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0x2a4fe559,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x7dbb553a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x78981268,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*63" | sha256
     7d3e74a05d7db15bce4ad9ec0658ea98e3f06eeecf16b4c6fff2da457ddc2f34
     */
    Sha256HashA(63, Result);
    XCTAssertEqual(Result[0], 0x7d3e74a0,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x5d7db15b,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xce4ad9ec,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0x0658ea98,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xe3f06eee,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xcf16b4c6,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0xfff2da45,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x7ddc2f34,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*64" | sha256
     ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb
     */
    Sha256HashA(64, Result);
    XCTAssertEqual(Result[0], 0xffe054fe,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x7ae0cb6d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0xc65c3af9,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xb61d5209,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0xf439851d,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xb43d0ba5,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x997337df,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x154668eb,  @"Calculated the correct hash");
    
    
    /*
     ruby -e "print 'a'*65" | sha256
     635361c48bb9eab14198e76ea8ab7f1a41685d6ad62aa9146d301d4f17eb0ae0
     */
    Sha256HashA(65, Result);
    XCTAssertEqual(Result[0], 0x635361c4,  @"Calculated the correct hash");
    XCTAssertEqual(Result[1], 0x8bb9eab1,  @"Calculated the correct hash");
    XCTAssertEqual(Result[2], 0x4198e76e,  @"Calculated the correct hash");
    XCTAssertEqual(Result[3], 0xa8ab7f1a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[4], 0x41685d6a,  @"Calculated the correct hash");
    XCTAssertEqual(Result[5], 0xd62aa914,  @"Calculated the correct hash");
    XCTAssertEqual(Result[6], 0x6d301d4f,  @"Calculated the correct hash");
    XCTAssertEqual(Result[7], 0x17eb0ae0,  @"Calculated the correct hash");
}

-(void) testAes128KeyExpansion
{
    uint32_t ExpectedKeys128[10][4] = {
        { CC_MAP(CC_BIG_32, 0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605) },
        { CC_MAP(CC_BIG_32, 0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f) },
        { CC_MAP(CC_BIG_32, 0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b) },
        { CC_MAP(CC_BIG_32, 0xef44a541, 0xa8525b7f, 0xb671253b, 0xdb0bad00) },
        { CC_MAP(CC_BIG_32, 0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc) },
        { CC_MAP(CC_BIG_32, 0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd) },
        { CC_MAP(CC_BIG_32, 0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f) },
        { CC_MAP(CC_BIG_32, 0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f) },
        { CC_MAP(CC_BIG_32, 0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e) },
        { CC_MAP(CC_BIG_32, 0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6) }
    };
    
    CCSimd_u8x16 Key = CCSimdLoad_u8x16((uint8_t[16]){ 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c });
    
    for (size_t Loop = 0; Loop < 10; Loop++)
    {
        Key = CCCryptoAes128KeyExpandRound(Key, Loop);
        
        uint32_t Result[4];
        CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(Key));
        
        XCTAssertEqual(Result[0], ExpectedKeys128[Loop][0], @"Should be the correct expanded word");
        XCTAssertEqual(Result[1], ExpectedKeys128[Loop][1], @"Should be the correct expanded word");
        XCTAssertEqual(Result[2], ExpectedKeys128[Loop][2], @"Should be the correct expanded word");
        XCTAssertEqual(Result[3], ExpectedKeys128[Loop][3], @"Should be the correct expanded word");
    }
    
    
    
    Key = CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f });
    
    CCSimd_u8x16 ExpandedKey[11];
    CCCryptoAes128KeyExpand(Key, ExpandedKey);
    
    uint32_t ExpectedExpandedKeys128[11][4] = {
        { CC_MAP(CC_BIG_32, 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f) },
        { CC_MAP(CC_BIG_32, 0xd6aa74fd, 0xd2af72fa, 0xdaa678f1, 0xd6ab76fe) },
        { CC_MAP(CC_BIG_32, 0xb692cf0b, 0x643dbdf1, 0xbe9bc500, 0x6830b3fe) },
        { CC_MAP(CC_BIG_32, 0xb6ff744e, 0xd2c2c9bf, 0x6c590cbf, 0x0469bf41) },
        { CC_MAP(CC_BIG_32, 0x47f7f7bc, 0x95353e03, 0xf96c32bc, 0xfd058dfd) },
        { CC_MAP(CC_BIG_32, 0x3caaa3e8, 0xa99f9deb, 0x50f3af57, 0xadf622aa) },
        { CC_MAP(CC_BIG_32, 0x5e390f7d, 0xf7a69296, 0xa7553dc1, 0x0aa31f6b) },
        { CC_MAP(CC_BIG_32, 0x14f9701a, 0xe35fe28c, 0x440adf4d, 0x4ea9c026) },
        { CC_MAP(CC_BIG_32, 0x47438735, 0xa41c65b9, 0xe016baf4, 0xaebf7ad2) },
        { CC_MAP(CC_BIG_32, 0x549932d1, 0xf0855768, 0x1093ed9c, 0xbe2c974e) },
        { CC_MAP(CC_BIG_32, 0x13111d7f, 0xe3944a17, 0xf307a78b, 0x4d2b30c5) }
    };
    
    for (size_t Loop = 0; Loop < 11; Loop++)
    {
        uint32_t Result[4];
        CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(ExpandedKey[Loop]));
        
        XCTAssertEqual(Result[0], ExpectedExpandedKeys128[Loop][0], @"Should be the correct expanded word");
        XCTAssertEqual(Result[1], ExpectedExpandedKeys128[Loop][1], @"Should be the correct expanded word");
        XCTAssertEqual(Result[2], ExpectedExpandedKeys128[Loop][2], @"Should be the correct expanded word");
        XCTAssertEqual(Result[3], ExpectedExpandedKeys128[Loop][3], @"Should be the correct expanded word");
    }
}

-(void) testAes192KeyExpansion
{
    uint32_t ExpectedKeys192[16][4] = {
        { CC_MAP(CC_BIG_32, 0xfe0c91f7, 0x2402f5a5, 0xec12068e, 0x6c827f6b) }, { CC_MAP(CC_BIG_32, 0x0e7a95b9, 0x5c56fec2) },
        { CC_MAP(CC_BIG_32, 0x4db7b4bd, 0x69b54118, 0x85a74796, 0xe92538fd) }, { CC_MAP(CC_BIG_32, 0xe75fad44, 0xbb095386) },
        { CC_MAP(CC_BIG_32, 0x485af057, 0x21efb14f, 0xa448f6d9, 0x4d6dce24) }, { CC_MAP(CC_BIG_32, 0xaa326360, 0x113b30e6) },
        { CC_MAP(CC_BIG_32, 0xa25e7ed5, 0x83b1cf9a, 0x27f93943, 0x6a94f767) }, { CC_MAP(CC_BIG_32, 0xc0a69407, 0xd19da4e1) },
        { CC_MAP(CC_BIG_32, 0xec1786eb, 0x6fa64971, 0x485f7032, 0x22cb8755) }, { CC_MAP(CC_BIG_32, 0xe26d1352, 0x33f0b7b3) },
        { CC_MAP(CC_BIG_32, 0x40beeb28, 0x2f18a259, 0x6747d26b, 0x458c553e) }, { CC_MAP(CC_BIG_32, 0xa7e1466c, 0x9411f1df) },
        { CC_MAP(CC_BIG_32, 0x821f750a, 0xad07d753, 0xca400538, 0x8fcc5006) }, { CC_MAP(CC_BIG_32, 0x282d166a, 0xbc3ce7b5) },
        { CC_MAP(CC_BIG_32, 0xe98ba06f, 0x448c773c, 0x8ecc7204, 0x01002202) }, {}
    };
    
    CCSimd_u8x16x2 Key = {
        CCSimdLoad_u8x16((uint8_t[16]){ 0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5 }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b })
    };
    
    for (size_t Loop = 0; Loop < 8; Loop++)
    {
        Key = CCCryptoAes192KeyExpandRound(Key, Loop);
        
        uint32_t Result[4];
        CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]));
        
        XCTAssertEqual(Result[0], ExpectedKeys192[(Loop * 2)][0], @"Should be the correct expanded word");
        XCTAssertEqual(Result[1], ExpectedKeys192[(Loop * 2)][1], @"Should be the correct expanded word");
        XCTAssertEqual(Result[2], ExpectedKeys192[(Loop * 2)][2], @"Should be the correct expanded word");
        XCTAssertEqual(Result[3], ExpectedKeys192[(Loop * 2)][3], @"Should be the correct expanded word");
        
        if (Loop < 7)
        {
            CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]));
            
            XCTAssertEqual(Result[0], ExpectedKeys192[(Loop * 2) + 1][0], @"Should be the correct expanded word");
            XCTAssertEqual(Result[1], ExpectedKeys192[(Loop * 2) + 1][1], @"Should be the correct expanded word");
        }
    }
    
    
    
    Key.v[0] = CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f });
    Key.v[1] = CCSimdLoad_u8x16((uint8_t[16]){ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 });
    
    CCSimd_u8x16 ExpandedKey[13];
    CCCryptoAes192KeyExpand(Key, ExpandedKey);
    
    uint32_t ExpectedExpandedKeys192[13][4] = {
        { CC_MAP(CC_BIG_32, 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f) },
        { CC_MAP(CC_BIG_32, 0x10111213, 0x14151617, 0x5846f2f9, 0x5c43f4fe) },
        { CC_MAP(CC_BIG_32, 0x544afef5, 0x5847f0fa, 0x4856e2e9, 0x5c43f4fe) },
        { CC_MAP(CC_BIG_32, 0x40f949b3, 0x1cbabd4d, 0x48f043b8, 0x10b7b342) },
        { CC_MAP(CC_BIG_32, 0x58e151ab, 0x04a2a555, 0x7effb541, 0x6245080c) },
        { CC_MAP(CC_BIG_32, 0x2ab54bb4, 0x3a02f8f6, 0x62e3a95d, 0x66410c08) },
        { CC_MAP(CC_BIG_32, 0xf5018572, 0x97448d7e, 0xbdf1c6ca, 0x87f33e3c) },
        { CC_MAP(CC_BIG_32, 0xe5109761, 0x83519b69, 0x34157c9e, 0xa351f1e0) },
        { CC_MAP(CC_BIG_32, 0x1ea0372a, 0x99530916, 0x7c439e77, 0xff12051e) },
        { CC_MAP(CC_BIG_32, 0xdd7e0e88, 0x7e2fff68, 0x608fc842, 0xf9dcc154) },
        { CC_MAP(CC_BIG_32, 0x859f5f23, 0x7a8d5a3d, 0xc0c02952, 0xbeefd63a) },
        { CC_MAP(CC_BIG_32, 0xde601e78, 0x27bcdf2c, 0xa223800f, 0xd8aeda32) },
        { CC_MAP(CC_BIG_32, 0xa4970a33, 0x1a78dc09, 0xc418c271, 0xe3a41d5d) }
    };
    
    for (size_t Loop = 0; Loop < 13; Loop++)
    {
        uint32_t Result[4];
        CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(ExpandedKey[Loop]));
        
        XCTAssertEqual(Result[0], ExpectedExpandedKeys192[Loop][0], @"Should be the correct expanded word");
        XCTAssertEqual(Result[1], ExpectedExpandedKeys192[Loop][1], @"Should be the correct expanded word");
        XCTAssertEqual(Result[2], ExpectedExpandedKeys192[Loop][2], @"Should be the correct expanded word");
        XCTAssertEqual(Result[3], ExpectedExpandedKeys192[Loop][3], @"Should be the correct expanded word");
    }
}

-(void) testAes256KeyExpansion
{
    uint32_t ExpectedKeys256[13][4] = {
        { CC_MAP(CC_BIG_32, 0x9ba35411, 0x8e6925af, 0xa51a8b5f, 0x2067fcde) }, { CC_MAP(CC_BIG_32, 0xa8b09c1a, 0x93d194cd, 0xbe49846e, 0xb75d5b9a) },
        { CC_MAP(CC_BIG_32, 0xd59aecb8, 0x5bf3c917, 0xfee94248, 0xde8ebe96) }, { CC_MAP(CC_BIG_32, 0xb5a9328a, 0x2678a647, 0x98312229, 0x2f6c79b3) },
        { CC_MAP(CC_BIG_32, 0x812c81ad, 0xdadf48ba, 0x24360af2, 0xfab8b464) }, { CC_MAP(CC_BIG_32, 0x98c5bfc9, 0xbebd198e, 0x268c3ba7, 0x09e04214) },
        { CC_MAP(CC_BIG_32, 0x68007bac, 0xb2df3316, 0x96e939e4, 0x6c518d80) }, { CC_MAP(CC_BIG_32, 0xc814e204, 0x76a9fb8a, 0x5025c02d, 0x59c58239) },
        { CC_MAP(CC_BIG_32, 0xde136967, 0x6ccc5a71, 0xfa256395, 0x9674ee15) }, { CC_MAP(CC_BIG_32, 0x5886ca5d, 0x2e2f31d7, 0x7e0af1fa, 0x27cf73c3) },
        { CC_MAP(CC_BIG_32, 0x749c47ab, 0x18501dda, 0xe2757e4f, 0x7401905a) }, { CC_MAP(CC_BIG_32, 0xcafaaae3, 0xe4d59b34, 0x9adf6ace, 0xbd10190d) },
        { CC_MAP(CC_BIG_32, 0xfe4890d1, 0xe6188d0b, 0x046df344, 0x706c631e) },
    };
    
    CCSimd_u8x16x2 Key = {
        CCSimdLoad_u8x16((uint8_t[16]){ 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81 }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 })
    };
    
    for (size_t Loop = 0; Loop < 7; Loop++)
    {
        Key = CCCryptoAes256KeyExpandRound(Key, Loop);
        
        uint32_t Result[4];
        CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]));
        
        XCTAssertEqual(Result[0], ExpectedKeys256[(Loop * 2)][0], @"Should be the correct expanded word");
        XCTAssertEqual(Result[1], ExpectedKeys256[(Loop * 2)][1], @"Should be the correct expanded word");
        XCTAssertEqual(Result[2], ExpectedKeys256[(Loop * 2)][2], @"Should be the correct expanded word");
        XCTAssertEqual(Result[3], ExpectedKeys256[(Loop * 2)][3], @"Should be the correct expanded word");
        
        if (Loop < 6)
        {
            CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]));
            
            XCTAssertEqual(Result[0], ExpectedKeys256[(Loop * 2) + 1][0], @"Should be the correct expanded word");
            XCTAssertEqual(Result[1], ExpectedKeys256[(Loop * 2) + 1][1], @"Should be the correct expanded word");
            XCTAssertEqual(Result[2], ExpectedKeys256[(Loop * 2) + 1][2], @"Should be the correct expanded word");
            XCTAssertEqual(Result[3], ExpectedKeys256[(Loop * 2) + 1][3], @"Should be the correct expanded word");
        }
    }
    
    
    
    Key.v[0] = CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f });
    Key.v[1] = CCSimdLoad_u8x16((uint8_t[16]){ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f });
    
    CCSimd_u8x16 ExpandedKey[15];
    CCCryptoAes256KeyExpand(Key, ExpandedKey);
    
    uint32_t ExpectedExpandedKeys256[15][4] = {
        { CC_MAP(CC_BIG_32, 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f) },
        { CC_MAP(CC_BIG_32, 0x10111213, 0x14151617, 0x18191a1b, 0x1c1d1e1f) },
        { CC_MAP(CC_BIG_32, 0xa573c29f, 0xa176c498, 0xa97fce93, 0xa572c09c) },
        { CC_MAP(CC_BIG_32, 0x1651a8cd, 0x0244beda, 0x1a5da4c1, 0x0640bade) },
        { CC_MAP(CC_BIG_32, 0xae87dff0, 0x0ff11b68, 0xa68ed5fb, 0x03fc1567) },
        { CC_MAP(CC_BIG_32, 0x6de1f148, 0x6fa54f92, 0x75f8eb53, 0x73b8518d) },
        { CC_MAP(CC_BIG_32, 0xc656827f, 0xc9a79917, 0x6f294cec, 0x6cd5598b) },
        { CC_MAP(CC_BIG_32, 0x3de23a75, 0x524775e7, 0x27bf9eb4, 0x5407cf39) },
        { CC_MAP(CC_BIG_32, 0x0bdc905f, 0xc27b0948, 0xad5245a4, 0xc1871c2f) },
        { CC_MAP(CC_BIG_32, 0x45f5a660, 0x17b2d387, 0x300d4d33, 0x640a820a) },
        { CC_MAP(CC_BIG_32, 0x7ccff71c, 0xbeb4fe54, 0x13e6bbf0, 0xd261a7df) },
        { CC_MAP(CC_BIG_32, 0xf01afafe, 0xe7a82979, 0xd7a5644a, 0xb3afe640) },
        { CC_MAP(CC_BIG_32, 0x2541fe71, 0x9bf50025, 0x8813bbd5, 0x5a721c0a) },
        { CC_MAP(CC_BIG_32, 0x4e5a6699, 0xa9f24fe0, 0x7e572baa, 0xcdf8cdea) },
        { CC_MAP(CC_BIG_32, 0x24fc79cc, 0xbf0979e9, 0x371ac23c, 0x6d68de36) }
    };
    
    for (size_t Loop = 0; Loop < 15; Loop++)
    {
        uint32_t Result[4];
        CCSimdStore_u32x4(Result, CCSimd_u32x4_Reinterpret_u8x16(ExpandedKey[Loop]));
        
        XCTAssertEqual(Result[0], ExpectedExpandedKeys256[Loop][0], @"Should be the correct expanded word");
        XCTAssertEqual(Result[1], ExpectedExpandedKeys256[Loop][1], @"Should be the correct expanded word");
        XCTAssertEqual(Result[2], ExpectedExpandedKeys256[Loop][2], @"Should be the correct expanded word");
        XCTAssertEqual(Result[3], ExpectedExpandedKeys256[Loop][3], @"Should be the correct expanded word");
    }
}

-(void) testAes128
{    
    CCSimd_u8x16 Data = CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff });
    CCSimd_u8x16 Key = CCSimdLoad_u8x16((uint8_t[16]){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    
    CCSimd_u8x16 ExpandedKey[11];
    CCCryptoAes128KeyExpand(Key, ExpandedKey);
    
    CCSimd_u8x16 CipherText = CCCryptoAes128Encrypt(Data, ExpandedKey);
    
    uint8_t Expected[16] = { 0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a };
    uint8_t Result[16];
    CCSimdStore_u8x16(Result, CipherText);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    CCSimd_u8x16 PlainText = CCCryptoAes128Decrypt(CipherText, ExpandedKey);
    
    CCSimdStore_u8x16(Result, PlainText);
    CCSimdStore_u8x16(Expected, Data);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    
    
    Data = CCSimdLoad_u8x16((uint8_t[16]){ 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 });
    Key = CCSimdLoad_u8x16((uint8_t[16]){ 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c });
    
    CCCryptoAes128KeyExpand(Key, ExpandedKey);
    
    CipherText = CCCryptoAes128Encrypt(Data, ExpandedKey);
    
    memcpy(Expected, (uint8_t[16]){ 0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32 }, 16);
    CCSimdStore_u8x16(Result, CipherText);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    PlainText = CCCryptoAes128Decrypt(CipherText, ExpandedKey);
    
    CCSimdStore_u8x16(Result, PlainText);
    CCSimdStore_u8x16(Expected, Data);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
}

-(void) testAes192
{
    CCSimd_u8x16 Data = CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff });
    CCSimd_u8x16x2 Key = {
        CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 })
    };
    
    CCSimd_u8x16 ExpandedKey[13];
    CCCryptoAes192KeyExpand(Key, ExpandedKey);
    
    CCSimd_u8x16 CipherText = CCCryptoAes192Encrypt(Data, ExpandedKey);
    
    uint8_t Expected[16] = { 0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0, 0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91 };
    uint8_t Result[16];
    CCSimdStore_u8x16(Result, CipherText);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    CCSimd_u8x16 PlainText = CCCryptoAes192Decrypt(CipherText, ExpandedKey);
    
    CCSimdStore_u8x16(Result, PlainText);
    CCSimdStore_u8x16(Expected, Data);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    
    
    Data = CCSimdLoad_u8x16((uint8_t[16]){ 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 });
    Key.v[0] = CCSimdLoad_u8x16((uint8_t[16]){ 0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5 });
    Key.v[1] = CCSimdLoad_u8x16((uint8_t[16]){ 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b });
    
    CCCryptoAes192KeyExpand(Key, ExpandedKey);
    
    CipherText = CCCryptoAes192Encrypt(Data, ExpandedKey);
    
    memcpy(Expected, (uint8_t[16]){ 0x58, 0x5e, 0x9f, 0xb6, 0xc2, 0x72, 0x2b, 0x9a, 0xf4, 0xf4, 0x92, 0xc1, 0x2b, 0xb0, 0x24, 0xc1 }, 16);
    CCSimdStore_u8x16(Result, CipherText);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    PlainText = CCCryptoAes192Decrypt(CipherText, ExpandedKey);
    
    CCSimdStore_u8x16(Result, PlainText);
    CCSimdStore_u8x16(Expected, Data);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
}

-(void) testAes256
{
    CCSimd_u8x16 Data = CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff });
    CCSimd_u8x16x2 Key = {
        CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f })
    };
    
    CCSimd_u8x16 ExpandedKey[15];
    CCCryptoAes256KeyExpand(Key, ExpandedKey);
    
    CCSimd_u8x16 CipherText = CCCryptoAes256Encrypt(Data, ExpandedKey);
    
    uint8_t Expected[16] = { 0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89 };
    uint8_t Result[16];
    CCSimdStore_u8x16(Result, CipherText);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    CCSimd_u8x16 PlainText = CCCryptoAes256Decrypt(CipherText, ExpandedKey);
    
    CCSimdStore_u8x16(Result, PlainText);
    CCSimdStore_u8x16(Expected, Data);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    
    
    Data = CCSimdLoad_u8x16((uint8_t[16]){ 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 });
    Key.v[0] = CCSimdLoad_u8x16((uint8_t[16]){ 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81 });
    Key.v[1] = CCSimdLoad_u8x16((uint8_t[16]){ 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 });
    
    CCCryptoAes256KeyExpand(Key, ExpandedKey);
    
    CipherText = CCCryptoAes256Encrypt(Data, ExpandedKey);
    
    memcpy(Expected, (uint8_t[16]){ 0x30, 0x21, 0x61, 0x3a, 0x97, 0x3e, 0x58, 0x2f, 0x4a, 0x29, 0x23, 0x41, 0x37, 0xae, 0xc4, 0x94 }, 16);
    CCSimdStore_u8x16(Result, CipherText);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
    
    PlainText = CCCryptoAes256Decrypt(CipherText, ExpandedKey);
    
    CCSimdStore_u8x16(Result, PlainText);
    CCSimdStore_u8x16(Expected, Data);
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct cipher text");
    }
}

@end
