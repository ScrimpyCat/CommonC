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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
    }
}

static void TestAes128(CCSimd_u8x16 Data, CCSimd_u8x16 Key, uint8_t Expected[16])
{
    CCSimd_u8x16 ExpandedKey[11];
    CCCryptoAes128KeyExpand(Key, ExpandedKey);
    
    CCSimd_u8x16 CipherText = CCCryptoAes128Encrypt(Data, ExpandedKey);
    
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
    }
}

static void TestAes192(CCSimd_u8x16 Data, CCSimd_u8x16 KeyHi, CCSimd_u8x16 KeyLo, uint8_t Expected[16])
{
    CCSimd_u8x16x2 Key = { KeyHi, KeyLo };
    
    CCSimd_u8x16 ExpandedKey[13];
    CCCryptoAes192KeyExpand(Key, ExpandedKey);
    
    CCSimd_u8x16 CipherText = CCCryptoAes192Encrypt(Data, ExpandedKey);
    
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
    }
}

static void TestAes256(CCSimd_u8x16 Data, CCSimd_u8x16 KeyHi, CCSimd_u8x16 KeyLo, uint8_t Expected[16])
{
    CCSimd_u8x16x2 Key = { KeyHi, KeyLo };
    
    CCSimd_u8x16 ExpandedKey[15];
    CCCryptoAes256KeyExpand(Key, ExpandedKey);
    
    CCSimd_u8x16 CipherText = CCCryptoAes256Encrypt(Data, ExpandedKey);
    
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
        XCTAssertEqual(Result[Loop], Expected[Loop], @"Should be the correct plain text");
    }
}

-(void) testAes
{
    const CCSimd_u8x16 DataZero = CCSimdZero_u8x16();
    const CCSimd_u8x16 DataFF = CCSimdNot_u8x16(CCSimdZero_u8x16());
    const CCSimd_u8x16 DataOnes = CCSimdNeg_u8x16(CCSimdNot_u8x16(CCSimdZero_u8x16()));
    const CCSimd_u8x16 DataLo = CCSimdLoad_u8x16((uint8_t[16]){ 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0 });
    const CCSimd_u8x16 DataHi = CCSimdLoad_u8x16((uint8_t[16]){ 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4 });
    const CCSimd_u8x16 DataABC = CCSimdLoad_u8x16((uint8_t*)"abcdefghijklmnop");
    const CCSimd_u8x16 DataSBoxExhaust[16] = {
        CCSimdLoad_u8x16((uint8_t[16]){ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef }),
        CCSimdLoad_u8x16((uint8_t[16]){ 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff })
    };
    
    const CCSimd_u8x16 Key128Zero = DataZero;
    const CCSimd_u8x16 Key128FF = DataFF;
    const CCSimd_u8x16 Key128Ones = DataOnes;
    const CCSimd_u8x16 Key128Lo = DataLo;
    const CCSimd_u8x16 Key128Hi = DataHi;
    const CCSimd_u8x16 Key128ABC = DataABC;
    CCSimd_u8x16 Key128SBoxExhaust[16];
    
    for (size_t Loop = 0; Loop < 16; Loop++) Key128SBoxExhaust[Loop] = DataSBoxExhaust[Loop];
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     66e94bd4ef8a2c3b884cfa59ca342b2e
     */
    TestAes128(DataZero, Key128Zero, (uint8_t[16]){ 0x66, 0xe9, 0x4b, 0xd4, 0xef, 0x8a, 0x2c, 0x3b, 0x88, 0x4c, 0xfa, 0x59, 0xca, 0x34, 0x2b, 0x2e });
    
    /*
     printf "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     3f5b8cc9ea855a0afa7347d23e8d664e
     */
    TestAes128(DataFF, Key128Zero, (uint8_t[16]){ 0x3f, 0x5b, 0x8c, 0xc9, 0xea, 0x85, 0x5a, 0x0a, 0xfa, 0x73, 0x47, 0xd2, 0x3e, 0x8d, 0x66, 0x4e });
    
    /*
     printf "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     e14d5d0ee27715df08b4152ba23da8e0
     */
    TestAes128(DataOnes, Key128Zero, (uint8_t[16]){ 0xe1, 0x4d, 0x5d, 0x0e, 0xe2, 0x77, 0x15, 0xdf, 0x08, 0xb4, 0x15, 0x2b, 0xa2, 0x3d, 0xa8, 0xe0 });
    
    /*
     printf "\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     ec8ca46e7cd9097485af67ffbc91a023
     */
    TestAes128(DataLo, Key128Zero, (uint8_t[16]){ 0xec, 0x8c, 0xa4, 0x6e, 0x7c, 0xd9, 0x09, 0x74, 0x85, 0xaf, 0x67, 0xff, 0xbc, 0x91, 0xa0, 0x23 });
    
    /*
     printf "\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     bcd272922630e6355b089f1d54268396
     */
    TestAes128(DataHi, Key128Zero, (uint8_t[16]){ 0xbc, 0xd2, 0x72, 0x92, 0x26, 0x30, 0xe6, 0x35, 0x5b, 0x08, 0x9f, 0x1d, 0x54, 0x26, 0x83, 0x96 });
    
    /*
     printf "abcdefghijklmnop" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     c3af71addfe4fcac6941286a76ddedc2
     */
    TestAes128(DataABC, Key128Zero, (uint8_t[16]){ 0xc3, 0xaf, 0x71, 0xad, 0xdf, 0xe4, 0xfc, 0xac, 0x69, 0x41, 0x28, 0x6a, 0x76, 0xdd, 0xed, 0xc2 });
    
    /*
     printf "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     7aca0fd9bcd6ec7c9f97466616e6a282
     */
    TestAes128(DataSBoxExhaust[0], Key128Zero, (uint8_t[16]){ 0x7a, 0xca, 0x0f, 0xd9, 0xbc, 0xd6, 0xec, 0x7c, 0x9f, 0x97, 0x46, 0x66, 0x16, 0xe6, 0xa2, 0x82 });
    
    /*
     printf "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     358d5b59adb65d04107676586f473446
     */
    TestAes128(DataSBoxExhaust[1], Key128Zero, (uint8_t[16]){ 0x35, 0x8d, 0x5b, 0x59, 0xad, 0xb6, 0x5d, 0x04, 0x10, 0x76, 0x76, 0x58, 0x6f, 0x47, 0x34, 0x46 });
    
    /*
     printf "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     7ae4a1a54763eabcc73c42aeca94ed81
     */
    TestAes128(DataSBoxExhaust[2], Key128Zero, (uint8_t[16]){ 0x7a, 0xe4, 0xa1, 0xa5, 0x47, 0x63, 0xea, 0xbc, 0xc7, 0x3c, 0x42, 0xae, 0xca, 0x94, 0xed, 0x81 });
    
    /*
     printf "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     e7204fc0cf7ef9b13a44d549aaac25bf
     */
    TestAes128(DataSBoxExhaust[3], Key128Zero, (uint8_t[16]){ 0xe7, 0x20, 0x4f, 0xc0, 0xcf, 0x7e, 0xf9, 0xb1, 0x3a, 0x44, 0xd5, 0x49, 0xaa, 0xac, 0x25, 0xbf });
    
    /*
     printf "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     21d814c9d8e9c2c027fdb81697e96c3a
     */
    TestAes128(DataSBoxExhaust[4], Key128Zero, (uint8_t[16]){ 0x21, 0xd8, 0x14, 0xc9, 0xd8, 0xe9, 0xc2, 0xc0, 0x27, 0xfd, 0xb8, 0x16, 0x97, 0xe9, 0x6c, 0x3a });
    
    /*
     printf "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     202c11692e65c99bcb7ba90b1b61524a
     */
    TestAes128(DataSBoxExhaust[5], Key128Zero, (uint8_t[16]){ 0x20, 0x2c, 0x11, 0x69, 0x2e, 0x65, 0xc9, 0x9b, 0xcb, 0x7b, 0xa9, 0x0b, 0x1b, 0x61, 0x52, 0x4a });
    
    /*
     printf "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     6bf179c54006c2b2d424c84afbc856bb
     */
    TestAes128(DataSBoxExhaust[6], Key128Zero, (uint8_t[16]){ 0x6b, 0xf1, 0x79, 0xc5, 0x40, 0x06, 0xc2, 0xb2, 0xd4, 0x24, 0xc8, 0x4a, 0xfb, 0xc8, 0x56, 0xbb });
    
    /*
     printf "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     dd7bd3c30b9d03ad43c21e6f290402ba
     */
    TestAes128(DataSBoxExhaust[7], Key128Zero, (uint8_t[16]){ 0xdd, 0x7b, 0xd3, 0xc3, 0x0b, 0x9d, 0x03, 0xad, 0x43, 0xc2, 0x1e, 0x6f, 0x29, 0x04, 0x02, 0xba });
    
    /*
     printf "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     151a9fb0b6acc5976afb5031d1dec841
     */
    TestAes128(DataSBoxExhaust[8], Key128Zero, (uint8_t[16]){ 0x15, 0x1a, 0x9f, 0xb0, 0xb6, 0xac, 0xc5, 0x97, 0x6a, 0xfb, 0x50, 0x31, 0xd1, 0xde, 0xc8, 0x41 });
    
    /*
     printf "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     78f9e03fb1ee4b89fb835d175920ce65
     */
    TestAes128(DataSBoxExhaust[9], Key128Zero, (uint8_t[16]){ 0x78, 0xf9, 0xe0, 0x3f, 0xb1, 0xee, 0x4b, 0x89, 0xfb, 0x83, 0x5d, 0x17, 0x59, 0x20, 0xce, 0x65 });
    
    /*
     printf "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     11d4d0fb8b52063651ac08f1a593e3fa
     */
    TestAes128(DataSBoxExhaust[10], Key128Zero, (uint8_t[16]){ 0x11, 0xd4, 0xd0, 0xfb, 0x8b, 0x52, 0x06, 0x36, 0x51, 0xac, 0x08, 0xf1, 0xa5, 0x93, 0xe3, 0xfa });
    
    /*
     printf "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     b273634fe034b00345acb9673d758389
     */
    TestAes128(DataSBoxExhaust[11], Key128Zero, (uint8_t[16]){ 0xb2, 0x73, 0x63, 0x4f, 0xe0, 0x34, 0xb0, 0x03, 0x45, 0xac, 0xb9, 0x67, 0x3d, 0x75, 0x83, 0x89 });
    
    /*
     printf "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     442fb7268b5f94c8c3f956fee5d24d80
     */
    TestAes128(DataSBoxExhaust[12], Key128Zero, (uint8_t[16]){ 0x44, 0x2f, 0xb7, 0x26, 0x8b, 0x5f, 0x94, 0xc8, 0xc3, 0xf9, 0x56, 0xfe, 0xe5, 0xd2, 0x4d, 0x80 });
    
    /*
     printf "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     982cb02fbb7146f650597b8a666f3c5e
     */
    TestAes128(DataSBoxExhaust[13], Key128Zero, (uint8_t[16]){ 0x98, 0x2c, 0xb0, 0x2f, 0xbb, 0x71, 0x46, 0xf6, 0x50, 0x59, 0x7b, 0x8a, 0x66, 0x6f, 0x3c, 0x5e });
    
    /*
     printf "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     a03f1eba81e0324bba32bd7cd7a7d9aa
     */
    TestAes128(DataSBoxExhaust[14], Key128Zero, (uint8_t[16]){ 0xa0, 0x3f, 0x1e, 0xba, 0x81, 0xe0, 0x32, 0x4b, 0xba, 0x32, 0xbd, 0x7c, 0xd7, 0xa7, 0xd9, 0xaa });
    
    /*
     printf "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff" | openssl enc -aes-128-ecb -K 00000000000000000000000000000000 -nopad | xxd -p
     e1b6293ea19c4eff3d92e23b62c24226
     */
    TestAes128(DataSBoxExhaust[15], Key128Zero, (uint8_t[16]){ 0xe1, 0xb6, 0x29, 0x3e, 0xa1, 0x9c, 0x4e, 0xff, 0x3d, 0x92, 0xe2, 0x3b, 0x62, 0xc2, 0x42, 0x26 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K ffffffffffffffffffffffffffffffff -nopad | xxd -p
     a1f6258c877d5fcd8964484538bfc92c
     */
    TestAes128(DataZero, Key128FF, (uint8_t[16]){ 0xa1, 0xf6, 0x25, 0x8c, 0x87, 0x7d, 0x5f, 0xcd, 0x89, 0x64, 0x48, 0x45, 0x38, 0xbf, 0xc9, 0x2c });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 01010101010101010101010101010101 -nopad | xxd -p
     b6aeaffa752dc08b51639731761aed00
     */
    TestAes128(DataZero, Key128Ones, (uint8_t[16]){ 0xb6, 0xae, 0xaf, 0xfa, 0x75, 0x2d, 0xc0, 0x8b, 0x51, 0x63, 0x97, 0x31, 0x76, 0x1a, 0xed, 0x00 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 01000000020000000300000004000000 -nopad | xxd -p
     80c83679a3b2b14f496486e300b0017f
     */
    TestAes128(DataZero, Key128Lo, (uint8_t[16]){ 0x80, 0xc8, 0x36, 0x79, 0xa3, 0xb2, 0xb1, 0x4f, 0x49, 0x64, 0x86, 0xe3, 0x00, 0xb0, 0x01, 0x7f });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 00000001000000020000000300000004 -nopad | xxd -p
     5cfd714929a749e8cc0e7b382613be23
     */
    TestAes128(DataZero, Key128Hi, (uint8_t[16]){ 0x5c, 0xfd, 0x71, 0x49, 0x29, 0xa7, 0x49, 0xe8, 0xcc, 0x0e, 0x7b, 0x38, 0x26, 0x13, 0xbe, 0x23 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 6162636465666768696a6b6c6d6e6f70 -nopad | xxd -p
     f5657e278d0afad7c848b965898c31df
     */
    TestAes128(DataZero, Key128ABC, (uint8_t[16]){ 0xf5, 0x65, 0x7e, 0x27, 0x8d, 0x0a, 0xfa, 0xd7, 0xc8, 0x48, 0xb9, 0x65, 0x89, 0x8c, 0x31, 0xdf });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 000102030405060708090a0b0c0d0e0f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 0c0d0e0f000102030405060708090a0b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 08090a0b0c0d0e0f0001020304050607 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 0405060708090a0b0c0d0e0f00010203 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 101112131415161718191a1b1c1d1e1f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 1c1d1e1f101112131415161718191a1b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 18191a1b1c1d1e1f1011121314151617 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 1415161718191a1b1c1d1e1f10111213 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 202122232425262728292a2b2c2d2e2f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 2c2d2e2f202122232425262728292a2b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 28292a2b2c2d2e2f2021222324252627 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 2425262728292a2b2c2d2e2f20212223 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 303132333435363738393a3b3c3d3e3f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 3c3d3e3f303132333435363738393a3b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 38393a3b3c3d3e3f3031323334353637 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 3435363738393a3b3c3d3e3f30313233 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 404142434445464748494a4b4c4d4e4f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 4c4d4e4f404142434445464748494a4b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 48494a4b4c4d4e4f4041424344454647 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 4445464748494a4b4c4d4e4f40414243 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 505152535455565758595a5b5c5d5e5f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 5c5d5e5f505152535455565758595a5b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 58595a5b5c5d5e5f5051525354555657 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 5455565758595a5b5c5d5e5f50515253 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 606162636465666768696a6b6c6d6e6f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 6c6d6e6f606162636465666768696a6b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 68696a6b6c6d6e6f6061626364656667 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 6465666768696a6b6c6d6e6f60616263 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 707172737475767778797a7b7c7d7e7f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 7c7d7e7f707172737475767778797a7b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 78797a7b7c7d7e7f7071727374757677 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 7475767778797a7b7c7d7e7f70717273 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 808182838485868788898a8b8c8d8e8f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 8c8d8e8f808182838485868788898a8b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 88898a8b8c8d8e8f8081828384858687 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 8485868788898a8b8c8d8e8f80818283 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 909192939495969798999a9b9c9d9e9f -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 9c9d9e9f909192939495969798999a9b -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 98999a9b9c9d9e9f9091929394959697 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K 9495969798999a9b9c9d9e9f90919293 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K a0a1a2a3a4a5a6a7a8a9aaabacadaeaf -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K acadaeafa0a1a2a3a4a5a6a7a8a9aaab -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K a8a9aaabacadaeafa0a1a2a3a4a5a6a7 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K a4a5a6a7a8a9aaabacadaeafa0a1a2a3 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K b0b1b2b3b4b5b6b7b8b9babbbcbdbebf -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K bcbdbebfb0b1b2b3b4b5b6b7b8b9babb -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K b8b9babbbcbdbebfb0b1b2b3b4b5b6b7 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K b4b5b6b7b8b9babbbcbdbebfb0b1b2b3 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K c0c1c2c3c4c5c6c7c8c9cacbcccdcecf -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K cccdcecfc0c1c2c3c4c5c6c7c8c9cacb -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K c8c9cacbcccdcecfc0c1c2c3c4c5c6c7 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K c4c5c6c7c8c9cacbcccdcecfc0c1c2c3 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K d0d1d2d3d4d5d6d7d8d9dadbdcdddedf -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K dcdddedfd0d1d2d3d4d5d6d7d8d9dadb -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K d8d9dadbdcdddedfd0d1d2d3d4d5d6d7 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K d4d5d6d7d8d9dadbdcdddedfd0d1d2d3 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K e0e1e2e3e4e5e6e7e8e9eaebecedeeef -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K ecedeeefe0e1e2e3e4e5e6e7e8e9eaeb -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K e8e9eaebecedeeefe0e1e2e3e4e5e6e7 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K e4e5e6e7e8e9eaebecedeeefe0e1e2e3 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K fcfdfefff0f1f2f3f4f5f6f7f8f9fafb -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K f8f9fafbfcfdfefff0f1f2f3f4f5f6f7 -nopad | xxd -p >> tests.aes128.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-128-ecb -K f4f5f6f7f8f9fafbfcfdfefff0f1f2f3 -nopad | xxd -p >> tests.aes128.txt
     
     c6a13b37878f5b826f4f8162a1c8d879
     ed2aa3d6bebf2fbe2086eb90f93445e6
     e0006fe0bc2467c27050f4d362485f8b
     c13cf9b79298532b90aff9a8bce79f69
     eda330f90eecd16c003e5fb09bcff358
     45f42e8ae172d8135f8e9f779f1d0b75
     a749f350aa888b8540368c036f80741c
     7f3d1630aeb6de86efed1f5de0c85b29
     ae3a71384013479e5a259218e4df8cbf
     93082c0e1a2a72729a84124f1aba20e9
     84a6b1f986342e3adc2a95a9336b08c7
     e04236c946f2558c82cece1048ab9dbf
     87b514cc01246af8ac95686a46edb60b
     82ef67d88ba65e8033cfdcc1064abe41
     219acb6a6d8c6ceca309fa1fa9814875
     158937f45641b47639c36e7181dac61c
     1899564a9da8de833d25c71739eaadce
     6892e00945f7602fba4c638010bafc23
     cff5681c1d78b75f3523b2164b40eeac
     822ed104ab5848c0544fd21e461c5be2
     2195c4637e1ed75e92bafff38ae3dd67
     1942c21f674fd9d34f8b1fb53d99c62d
     238365be38e006c1265fa542dec1ea07
     dc9fa32edffd9e1fd45724a99c3d2d64
     af1322495504f592b0f247ae53dc7aa8
     89f7f399cd13adff0e49ba29c5b342ed
     90063299247d88bc5f8388d04c41035f
     884a1489c2d22a29bdb77c3e027097f7
     76d0554effd828c702538425786a66c6
     8d26cadf182b550ee8791886d8d43cb3
     31a06a5a1e9a9701567add99e1a0ada1
     026040abbc834d676ae58fb35bc86a31
     a1f0d9d2be280dfd07edbd0fdad067bf
     509b2f713c0943422987f9de3a4be143
     3030614ba4aa86743e21bd6527b32f6f
     b52291064e40c9e4701287b11319c035
     542be8089cae87025fe2f1742aed25f9
     481746d9a533bf53caabd9feb97095c3
     8c94dedaba97c49b006d1925980cf626
     8b1530f290f8ebac6d62b25b52b344d1
     b88291c95b54c76d525f48fb8c317411
     76285081061e56a4d10afa932ca4a23b
     adbf3e718168774c1f082abe19ee4ab5
     95d2a7d124af40642a0fb674ca2567bf
     a56fd8980a6756af442aa59174dc3da8
     120be3e8821fced5f0c9f9b5e36f96fb
     a7655ce86e4c4be9583505a6ae487e66
     9149580bc63130a748e7569c0f9be086
     8576701032353dc30504e1cc611042a9
     81bc707baa1bae1b04dea201db4b0548
     ac5fa50baf15877208fac27667fca765
     d68827c4b59e04fbf6e273eb9659a123
     14470219e2ddc235bbcf57252a375337
     4a3e6396baa62064c2a5f1b1fc580559
     512c0293687e191a3728d7f452a91fa1
     c711717740005e20b831c1dce2b33852
     ddfcfcbe0713919607872e871256f8a6
     bea793ce3c66168f10d22772f35c34ba
     9754b33d1e7d2f2620f60662a5d64909
     fc2e9d4c7aabb936da28dd73738a5cc2
     fdf188a74835a83d8829a62973bbdd03
     a2777526f108da7eca385002b4f2fabd
     805d85901140523cd1f7e11ff5bf9ed0
     0432d83efbe467a507989d3a87b26e15
     */
    uint8_t Key128SBoxExhaustedExpected[64][16] = {
        { 0xc6, 0xa1, 0x3b, 0x37, 0x87, 0x8f, 0x5b, 0x82, 0x6f, 0x4f, 0x81, 0x62, 0xa1, 0xc8, 0xd8, 0x79 },
        { 0xed, 0x2a, 0xa3, 0xd6, 0xbe, 0xbf, 0x2f, 0xbe, 0x20, 0x86, 0xeb, 0x90, 0xf9, 0x34, 0x45, 0xe6 },
        { 0xe0, 0x00, 0x6f, 0xe0, 0xbc, 0x24, 0x67, 0xc2, 0x70, 0x50, 0xf4, 0xd3, 0x62, 0x48, 0x5f, 0x8b },
        { 0xc1, 0x3c, 0xf9, 0xb7, 0x92, 0x98, 0x53, 0x2b, 0x90, 0xaf, 0xf9, 0xa8, 0xbc, 0xe7, 0x9f, 0x69 },
        { 0xed, 0xa3, 0x30, 0xf9, 0x0e, 0xec, 0xd1, 0x6c, 0x00, 0x3e, 0x5f, 0xb0, 0x9b, 0xcf, 0xf3, 0x58 },
        { 0x45, 0xf4, 0x2e, 0x8a, 0xe1, 0x72, 0xd8, 0x13, 0x5f, 0x8e, 0x9f, 0x77, 0x9f, 0x1d, 0x0b, 0x75 },
        { 0xa7, 0x49, 0xf3, 0x50, 0xaa, 0x88, 0x8b, 0x85, 0x40, 0x36, 0x8c, 0x03, 0x6f, 0x80, 0x74, 0x1c },
        { 0x7f, 0x3d, 0x16, 0x30, 0xae, 0xb6, 0xde, 0x86, 0xef, 0xed, 0x1f, 0x5d, 0xe0, 0xc8, 0x5b, 0x29 },
        { 0xae, 0x3a, 0x71, 0x38, 0x40, 0x13, 0x47, 0x9e, 0x5a, 0x25, 0x92, 0x18, 0xe4, 0xdf, 0x8c, 0xbf },
        { 0x93, 0x08, 0x2c, 0x0e, 0x1a, 0x2a, 0x72, 0x72, 0x9a, 0x84, 0x12, 0x4f, 0x1a, 0xba, 0x20, 0xe9 },
        { 0x84, 0xa6, 0xb1, 0xf9, 0x86, 0x34, 0x2e, 0x3a, 0xdc, 0x2a, 0x95, 0xa9, 0x33, 0x6b, 0x08, 0xc7 },
        { 0xe0, 0x42, 0x36, 0xc9, 0x46, 0xf2, 0x55, 0x8c, 0x82, 0xce, 0xce, 0x10, 0x48, 0xab, 0x9d, 0xbf },
        { 0x87, 0xb5, 0x14, 0xcc, 0x01, 0x24, 0x6a, 0xf8, 0xac, 0x95, 0x68, 0x6a, 0x46, 0xed, 0xb6, 0x0b },
        { 0x82, 0xef, 0x67, 0xd8, 0x8b, 0xa6, 0x5e, 0x80, 0x33, 0xcf, 0xdc, 0xc1, 0x06, 0x4a, 0xbe, 0x41 },
        { 0x21, 0x9a, 0xcb, 0x6a, 0x6d, 0x8c, 0x6c, 0xec, 0xa3, 0x09, 0xfa, 0x1f, 0xa9, 0x81, 0x48, 0x75 },
        { 0x15, 0x89, 0x37, 0xf4, 0x56, 0x41, 0xb4, 0x76, 0x39, 0xc3, 0x6e, 0x71, 0x81, 0xda, 0xc6, 0x1c },
        { 0x18, 0x99, 0x56, 0x4a, 0x9d, 0xa8, 0xde, 0x83, 0x3d, 0x25, 0xc7, 0x17, 0x39, 0xea, 0xad, 0xce },
        { 0x68, 0x92, 0xe0, 0x09, 0x45, 0xf7, 0x60, 0x2f, 0xba, 0x4c, 0x63, 0x80, 0x10, 0xba, 0xfc, 0x23 },
        { 0xcf, 0xf5, 0x68, 0x1c, 0x1d, 0x78, 0xb7, 0x5f, 0x35, 0x23, 0xb2, 0x16, 0x4b, 0x40, 0xee, 0xac },
        { 0x82, 0x2e, 0xd1, 0x04, 0xab, 0x58, 0x48, 0xc0, 0x54, 0x4f, 0xd2, 0x1e, 0x46, 0x1c, 0x5b, 0xe2 },
        { 0x21, 0x95, 0xc4, 0x63, 0x7e, 0x1e, 0xd7, 0x5e, 0x92, 0xba, 0xff, 0xf3, 0x8a, 0xe3, 0xdd, 0x67 },
        { 0x19, 0x42, 0xc2, 0x1f, 0x67, 0x4f, 0xd9, 0xd3, 0x4f, 0x8b, 0x1f, 0xb5, 0x3d, 0x99, 0xc6, 0x2d },
        { 0x23, 0x83, 0x65, 0xbe, 0x38, 0xe0, 0x06, 0xc1, 0x26, 0x5f, 0xa5, 0x42, 0xde, 0xc1, 0xea, 0x07 },
        { 0xdc, 0x9f, 0xa3, 0x2e, 0xdf, 0xfd, 0x9e, 0x1f, 0xd4, 0x57, 0x24, 0xa9, 0x9c, 0x3d, 0x2d, 0x64 },
        { 0xaf, 0x13, 0x22, 0x49, 0x55, 0x04, 0xf5, 0x92, 0xb0, 0xf2, 0x47, 0xae, 0x53, 0xdc, 0x7a, 0xa8 },
        { 0x89, 0xf7, 0xf3, 0x99, 0xcd, 0x13, 0xad, 0xff, 0x0e, 0x49, 0xba, 0x29, 0xc5, 0xb3, 0x42, 0xed },
        { 0x90, 0x06, 0x32, 0x99, 0x24, 0x7d, 0x88, 0xbc, 0x5f, 0x83, 0x88, 0xd0, 0x4c, 0x41, 0x03, 0x5f },
        { 0x88, 0x4a, 0x14, 0x89, 0xc2, 0xd2, 0x2a, 0x29, 0xbd, 0xb7, 0x7c, 0x3e, 0x02, 0x70, 0x97, 0xf7 },
        { 0x76, 0xd0, 0x55, 0x4e, 0xff, 0xd8, 0x28, 0xc7, 0x02, 0x53, 0x84, 0x25, 0x78, 0x6a, 0x66, 0xc6 },
        { 0x8d, 0x26, 0xca, 0xdf, 0x18, 0x2b, 0x55, 0x0e, 0xe8, 0x79, 0x18, 0x86, 0xd8, 0xd4, 0x3c, 0xb3 },
        { 0x31, 0xa0, 0x6a, 0x5a, 0x1e, 0x9a, 0x97, 0x01, 0x56, 0x7a, 0xdd, 0x99, 0xe1, 0xa0, 0xad, 0xa1 },
        { 0x02, 0x60, 0x40, 0xab, 0xbc, 0x83, 0x4d, 0x67, 0x6a, 0xe5, 0x8f, 0xb3, 0x5b, 0xc8, 0x6a, 0x31 },
        { 0xa1, 0xf0, 0xd9, 0xd2, 0xbe, 0x28, 0x0d, 0xfd, 0x07, 0xed, 0xbd, 0x0f, 0xda, 0xd0, 0x67, 0xbf },
        { 0x50, 0x9b, 0x2f, 0x71, 0x3c, 0x09, 0x43, 0x42, 0x29, 0x87, 0xf9, 0xde, 0x3a, 0x4b, 0xe1, 0x43 },
        { 0x30, 0x30, 0x61, 0x4b, 0xa4, 0xaa, 0x86, 0x74, 0x3e, 0x21, 0xbd, 0x65, 0x27, 0xb3, 0x2f, 0x6f },
        { 0xb5, 0x22, 0x91, 0x06, 0x4e, 0x40, 0xc9, 0xe4, 0x70, 0x12, 0x87, 0xb1, 0x13, 0x19, 0xc0, 0x35 },
        { 0x54, 0x2b, 0xe8, 0x08, 0x9c, 0xae, 0x87, 0x02, 0x5f, 0xe2, 0xf1, 0x74, 0x2a, 0xed, 0x25, 0xf9 },
        { 0x48, 0x17, 0x46, 0xd9, 0xa5, 0x33, 0xbf, 0x53, 0xca, 0xab, 0xd9, 0xfe, 0xb9, 0x70, 0x95, 0xc3 },
        { 0x8c, 0x94, 0xde, 0xda, 0xba, 0x97, 0xc4, 0x9b, 0x00, 0x6d, 0x19, 0x25, 0x98, 0x0c, 0xf6, 0x26 },
        { 0x8b, 0x15, 0x30, 0xf2, 0x90, 0xf8, 0xeb, 0xac, 0x6d, 0x62, 0xb2, 0x5b, 0x52, 0xb3, 0x44, 0xd1 },
        { 0xb8, 0x82, 0x91, 0xc9, 0x5b, 0x54, 0xc7, 0x6d, 0x52, 0x5f, 0x48, 0xfb, 0x8c, 0x31, 0x74, 0x11 },
        { 0x76, 0x28, 0x50, 0x81, 0x06, 0x1e, 0x56, 0xa4, 0xd1, 0x0a, 0xfa, 0x93, 0x2c, 0xa4, 0xa2, 0x3b },
        { 0xad, 0xbf, 0x3e, 0x71, 0x81, 0x68, 0x77, 0x4c, 0x1f, 0x08, 0x2a, 0xbe, 0x19, 0xee, 0x4a, 0xb5 },
        { 0x95, 0xd2, 0xa7, 0xd1, 0x24, 0xaf, 0x40, 0x64, 0x2a, 0x0f, 0xb6, 0x74, 0xca, 0x25, 0x67, 0xbf },
        { 0xa5, 0x6f, 0xd8, 0x98, 0x0a, 0x67, 0x56, 0xaf, 0x44, 0x2a, 0xa5, 0x91, 0x74, 0xdc, 0x3d, 0xa8 },
        { 0x12, 0x0b, 0xe3, 0xe8, 0x82, 0x1f, 0xce, 0xd5, 0xf0, 0xc9, 0xf9, 0xb5, 0xe3, 0x6f, 0x96, 0xfb },
        { 0xa7, 0x65, 0x5c, 0xe8, 0x6e, 0x4c, 0x4b, 0xe9, 0x58, 0x35, 0x05, 0xa6, 0xae, 0x48, 0x7e, 0x66 },
        { 0x91, 0x49, 0x58, 0x0b, 0xc6, 0x31, 0x30, 0xa7, 0x48, 0xe7, 0x56, 0x9c, 0x0f, 0x9b, 0xe0, 0x86 },
        { 0x85, 0x76, 0x70, 0x10, 0x32, 0x35, 0x3d, 0xc3, 0x05, 0x04, 0xe1, 0xcc, 0x61, 0x10, 0x42, 0xa9 },
        { 0x81, 0xbc, 0x70, 0x7b, 0xaa, 0x1b, 0xae, 0x1b, 0x04, 0xde, 0xa2, 0x01, 0xdb, 0x4b, 0x05, 0x48 },
        { 0xac, 0x5f, 0xa5, 0x0b, 0xaf, 0x15, 0x87, 0x72, 0x08, 0xfa, 0xc2, 0x76, 0x67, 0xfc, 0xa7, 0x65 },
        { 0xd6, 0x88, 0x27, 0xc4, 0xb5, 0x9e, 0x04, 0xfb, 0xf6, 0xe2, 0x73, 0xeb, 0x96, 0x59, 0xa1, 0x23 },
        { 0x14, 0x47, 0x02, 0x19, 0xe2, 0xdd, 0xc2, 0x35, 0xbb, 0xcf, 0x57, 0x25, 0x2a, 0x37, 0x53, 0x37 },
        { 0x4a, 0x3e, 0x63, 0x96, 0xba, 0xa6, 0x20, 0x64, 0xc2, 0xa5, 0xf1, 0xb1, 0xfc, 0x58, 0x05, 0x59 },
        { 0x51, 0x2c, 0x02, 0x93, 0x68, 0x7e, 0x19, 0x1a, 0x37, 0x28, 0xd7, 0xf4, 0x52, 0xa9, 0x1f, 0xa1 },
        { 0xc7, 0x11, 0x71, 0x77, 0x40, 0x00, 0x5e, 0x20, 0xb8, 0x31, 0xc1, 0xdc, 0xe2, 0xb3, 0x38, 0x52 },
        { 0xdd, 0xfc, 0xfc, 0xbe, 0x07, 0x13, 0x91, 0x96, 0x07, 0x87, 0x2e, 0x87, 0x12, 0x56, 0xf8, 0xa6 },
        { 0xbe, 0xa7, 0x93, 0xce, 0x3c, 0x66, 0x16, 0x8f, 0x10, 0xd2, 0x27, 0x72, 0xf3, 0x5c, 0x34, 0xba },
        { 0x97, 0x54, 0xb3, 0x3d, 0x1e, 0x7d, 0x2f, 0x26, 0x20, 0xf6, 0x06, 0x62, 0xa5, 0xd6, 0x49, 0x09 },
        { 0xfc, 0x2e, 0x9d, 0x4c, 0x7a, 0xab, 0xb9, 0x36, 0xda, 0x28, 0xdd, 0x73, 0x73, 0x8a, 0x5c, 0xc2 },
        { 0xfd, 0xf1, 0x88, 0xa7, 0x48, 0x35, 0xa8, 0x3d, 0x88, 0x29, 0xa6, 0x29, 0x73, 0xbb, 0xdd, 0x03 },
        { 0xa2, 0x77, 0x75, 0x26, 0xf1, 0x08, 0xda, 0x7e, 0xca, 0x38, 0x50, 0x02, 0xb4, 0xf2, 0xfa, 0xbd },
        { 0x80, 0x5d, 0x85, 0x90, 0x11, 0x40, 0x52, 0x3c, 0xd1, 0xf7, 0xe1, 0x1f, 0xf5, 0xbf, 0x9e, 0xd0 },
        { 0x04, 0x32, 0xd8, 0x3e, 0xfb, 0xe4, 0x67, 0xa5, 0x07, 0x98, 0x9d, 0x3a, 0x87, 0xb2, 0x6e, 0x15 }
    };
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        for (size_t Loop2 = 0; Loop2 < 4; Loop2++)
        {
            TestAes128(DataZero, Key128SBoxExhaust[Loop], Key128SBoxExhaustedExpected[(Loop * 4) + Loop2]);
            
            Key128SBoxExhaust[Loop] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key128SBoxExhaust[Loop]), 3, 0, 1, 2));
        }
    }
    
    
    
    const CCSimd_u8x16 KeyLo2 = CCSimdLoad_u8x16((uint8_t[16]){ 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0 });
    const CCSimd_u8x16 KeyHi2 = CCSimdLoad_u8x16((uint8_t[16]){ 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8 });
    const CCSimd_u8x16 KeyABC2 = CCSimdLoad_u8x16((uint8_t*)"ABCDEFGHIJKLMNOP");
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     aae06992acbf52a3e8f4a96ec9300bd7
     */
    TestAes192(DataZero, Key128Zero, Key128Zero, (uint8_t[16]){ 0xaa, 0xe0, 0x69, 0x92, 0xac, 0xbf, 0x52, 0xa3, 0xe8, 0xf4, 0xa9, 0x6e, 0xc9, 0x30, 0x0b, 0xd7 });
    
    /*
     printf "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     b13db4da1f718bc6904797c82bcf2d32
     */
    TestAes192(DataFF, Key128Zero, Key128Zero, (uint8_t[16]){ 0xb1, 0x3d, 0xb4, 0xda, 0x1f, 0x71, 0x8b, 0xc6, 0x90, 0x47, 0x97, 0xc8, 0x2b, 0xcf, 0x2d, 0x32 });
    
    /*
     printf "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     cf1ece3c44b078fb27cb0a3e071b0820
     */
    TestAes192(DataOnes, Key128Zero, Key128Zero, (uint8_t[16]){ 0xcf, 0x1e, 0xce, 0x3c, 0x44, 0xb0, 0x78, 0xfb, 0x27, 0xcb, 0x0a, 0x3e, 0x07, 0x1b, 0x08, 0x20 });
    
    /*
     printf "\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     84976aca993ea2e20d02ddec11f4068d
     */
    TestAes192(DataLo, Key128Zero, Key128Zero, (uint8_t[16]){ 0x84, 0x97, 0x6a, 0xca, 0x99, 0x3e, 0xa2, 0xe2, 0x0d, 0x02, 0xdd, 0xec, 0x11, 0xf4, 0x06, 0x8d });
    
    /*
     printf "\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     40d71a755486773b23906f00bc04416d
     */
    TestAes192(DataHi, Key128Zero, Key128Zero, (uint8_t[16]){ 0x40, 0xd7, 0x1a, 0x75, 0x54, 0x86, 0x77, 0x3b, 0x23, 0x90, 0x6f, 0x00, 0xbc, 0x04, 0x41, 0x6d });
    
    /*
     printf "abcdefghijklmnop" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     ec6374e75e004afc29beafbfb25c057d
     */
    TestAes192(DataABC, Key128Zero, Key128Zero, (uint8_t[16]){ 0xec, 0x63, 0x74, 0xe7, 0x5e, 0x00, 0x4a, 0xfc, 0x29, 0xbe, 0xaf, 0xbf, 0xb2, 0x5c, 0x05, 0x7d });
    
    /*
     printf "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     b81a664950008f91323ed53bd3309329
     */
    TestAes192(DataSBoxExhaust[0], Key128Zero, Key128Zero, (uint8_t[16]){ 0xb8, 0x1a, 0x66, 0x49, 0x50, 0x00, 0x8f, 0x91, 0x32, 0x3e, 0xd5, 0x3b, 0xd3, 0x30, 0x93, 0x29 });
    
    /*
     printf "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     ebc90ebde38c04156f83a9f851ee8477
     */
    TestAes192(DataSBoxExhaust[1], Key128Zero, Key128Zero, (uint8_t[16]){ 0xeb, 0xc9, 0x0e, 0xbd, 0xe3, 0x8c, 0x04, 0x15, 0x6f, 0x83, 0xa9, 0xf8, 0x51, 0xee, 0x84, 0x77 });
    
    /*
     printf "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     52620abdb160a866f2e4b86add3b2676
     */
    TestAes192(DataSBoxExhaust[2], Key128Zero, Key128Zero, (uint8_t[16]){ 0x52, 0x62, 0x0a, 0xbd, 0xb1, 0x60, 0xa8, 0x66, 0xf2, 0xe4, 0xb8, 0x6a, 0xdd, 0x3b, 0x26, 0x76 });
    
    /*
     printf "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     8581e4c24b9d82daf1546d402d0c4637
     */
    TestAes192(DataSBoxExhaust[3], Key128Zero, Key128Zero, (uint8_t[16]){ 0x85, 0x81, 0xe4, 0xc2, 0x4b, 0x9d, 0x82, 0xda, 0xf1, 0x54, 0x6d, 0x40, 0x2d, 0x0c, 0x46, 0x37 });
    
    /*
     printf "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     518d597b8f228e59db9eea8efe841a4a
     */
    TestAes192(DataSBoxExhaust[4], Key128Zero, Key128Zero, (uint8_t[16]){ 0x51, 0x8d, 0x59, 0x7b, 0x8f, 0x22, 0x8e, 0x59, 0xdb, 0x9e, 0xea, 0x8e, 0xfe, 0x84, 0x1a, 0x4a });
    
    /*
     printf "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     c763aa3fec304505314bb32c0f15d348
     */
    TestAes192(DataSBoxExhaust[5], Key128Zero, Key128Zero, (uint8_t[16]){ 0xc7, 0x63, 0xaa, 0x3f, 0xec, 0x30, 0x45, 0x05, 0x31, 0x4b, 0xb3, 0x2c, 0x0f, 0x15, 0xd3, 0x48 });
    
    /*
     printf "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     2a31697f0f477c4e980ae033e8536547
     */
    TestAes192(DataSBoxExhaust[6], Key128Zero, Key128Zero, (uint8_t[16]){ 0x2a, 0x31, 0x69, 0x7f, 0x0f, 0x47, 0x7c, 0x4e, 0x98, 0x0a, 0xe0, 0x33, 0xe8, 0x53, 0x65, 0x47 });
    
    /*
     printf "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     e80a8e1066cf37af84e55610e12fcb47
     */
    TestAes192(DataSBoxExhaust[7], Key128Zero, Key128Zero, (uint8_t[16]){ 0xe8, 0x0a, 0x8e, 0x10, 0x66, 0xcf, 0x37, 0xaf, 0x84, 0xe5, 0x56, 0x10, 0xe1, 0x2f, 0xcb, 0x47 });
    
    /*
     printf "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     06f25d302b6d8b24b98f7dee55c422fe
     */
    TestAes192(DataSBoxExhaust[8], Key128Zero, Key128Zero, (uint8_t[16]){ 0x06, 0xf2, 0x5d, 0x30, 0x2b, 0x6d, 0x8b, 0x24, 0xb9, 0x8f, 0x7d, 0xee, 0x55, 0xc4, 0x22, 0xfe });
    
    /*
     printf "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     9ef6f9acd1ff976033f9322ecf6b18cc
     */
    TestAes192(DataSBoxExhaust[9], Key128Zero, Key128Zero, (uint8_t[16]){ 0x9e, 0xf6, 0xf9, 0xac, 0xd1, 0xff, 0x97, 0x60, 0x33, 0xf9, 0x32, 0x2e, 0xcf, 0x6b, 0x18, 0xcc });
    
    /*
     printf "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     59760caab4196e2fc3b3001aafd785c5
     */
    TestAes192(DataSBoxExhaust[10], Key128Zero, Key128Zero, (uint8_t[16]){ 0x59, 0x76, 0x0c, 0xaa, 0xb4, 0x19, 0x6e, 0x2f, 0xc3, 0xb3, 0x00, 0x1a, 0xaf, 0xd7, 0x85, 0xc5 });
    
    /*
     printf "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     b711aea271e61aa43eb801106a9a6e32
     */
    TestAes192(DataSBoxExhaust[11], Key128Zero, Key128Zero, (uint8_t[16]){ 0xb7, 0x11, 0xae, 0xa2, 0x71, 0xe6, 0x1a, 0xa4, 0x3e, 0xb8, 0x01, 0x10, 0x6a, 0x9a, 0x6e, 0x32 });
    
    /*
     printf "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     319a4aff154e9e1fbf8d4f3d9466604f
     */
    TestAes192(DataSBoxExhaust[12], Key128Zero, Key128Zero, (uint8_t[16]){ 0x31, 0x9a, 0x4a, 0xff, 0x15, 0x4e, 0x9e, 0x1f, 0xbf, 0x8d, 0x4f, 0x3d, 0x94, 0x66, 0x60, 0x4f });
    
    /*
     printf "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     6816f443080aecece540798a8f4acace
     */
    TestAes192(DataSBoxExhaust[13], Key128Zero, Key128Zero, (uint8_t[16]){ 0x68, 0x16, 0xf4, 0x43, 0x08, 0x0a, 0xec, 0xec, 0xe5, 0x40, 0x79, 0x8a, 0x8f, 0x4a, 0xca, 0xce });
    
    /*
     printf "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     92c09b8e704f4b8c9503dfb94ad2d738
     */
    TestAes192(DataSBoxExhaust[14], Key128Zero, Key128Zero, (uint8_t[16]){ 0x92, 0xc0, 0x9b, 0x8e, 0x70, 0x4f, 0x4b, 0x8c, 0x95, 0x03, 0xdf, 0xb9, 0x4a, 0xd2, 0xd7, 0x38 });
    
    /*
     printf "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff" | openssl enc -aes-192-ecb -K 000000000000000000000000000000000000000000000000 -nopad | xxd -p
     7330a44a4d776c483b23c6cb101031b7
     */
    TestAes192(DataSBoxExhaust[15], Key128Zero, Key128Zero, (uint8_t[16]){ 0x73, 0x30, 0xa4, 0x4a, 0x4d, 0x77, 0x6c, 0x48, 0x3b, 0x23, 0xc6, 0xcb, 0x10, 0x10, 0x31, 0xb7 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K ffffffffffffffffffffffffffffffffffffffffffffffff -nopad | xxd -p
     dd8a493514231cbf56eccee4c40889fb
     */
    TestAes192(DataZero, Key128FF, Key128FF, (uint8_t[16]){ 0xdd, 0x8a, 0x49, 0x35, 0x14, 0x23, 0x1c, 0xbf, 0x56, 0xec, 0xce, 0xe4, 0xc4, 0x08, 0x89, 0xfb });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 010101010101010101010101010101010101010101010101 -nopad | xxd -p
     5f88ef3fbdebf2e4e2666512d3bcb70f
     */
    TestAes192(DataZero, Key128Ones, Key128Ones, (uint8_t[16]){ 0x5f, 0x88, 0xef, 0x3f, 0xbd, 0xeb, 0xf2, 0xe4, 0xe2, 0x66, 0x65, 0x12, 0xd3, 0xbc, 0xb7, 0x0f });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 010000000200000003000000040000000500000006000000 -nopad | xxd -p
     60c7529b191c6eb1664eaf48fef0d705
     */
    TestAes192(DataZero, Key128Lo, KeyLo2, (uint8_t[16]){ 0x60, 0xc7, 0x52, 0x9b, 0x19, 0x1c, 0x6e, 0xb1, 0x66, 0x4e, 0xaf, 0x48, 0xfe, 0xf0, 0xd7, 0x05 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 000000010000000200000003000000040000000500000006 -nopad | xxd -p
     7e16ab7e3ef59ee422ca1a1a84ae913d
     */
    TestAes192(DataZero, Key128Hi, KeyHi2, (uint8_t[16]){ 0x7e, 0x16, 0xab, 0x7e, 0x3e, 0xf5, 0x9e, 0xe4, 0x22, 0xca, 0x1a, 0x1a, 0x84, 0xae, 0x91, 0x3d });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 6162636465666768696a6b6c6d6e6f704142434445464748 -nopad | xxd -p
     9efe11e54b6e4d2de3c8df56ef080939
     */
    TestAes192(DataZero, Key128ABC, KeyABC2, (uint8_t[16]){ 0x9e, 0xfe, 0x11, 0xe5, 0x4b, 0x6e, 0x4d, 0x2d, 0xe3, 0xc8, 0xdf, 0x56, 0xef, 0x08, 0x09, 0x39 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 000102030405060708090a0b0c0d0e0f0001020304050607 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 0c0d0e0f000102030405060708090a0b0c0d0e0f00010203 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 08090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 0405060708090a0b0c0d0e0f000102030405060708090a0b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 101112131415161718191a1b1c1d1e1f1011121314151617 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 1c1d1e1f101112131415161718191a1b1c1d1e1f10111213 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 18191a1b1c1d1e1f101112131415161718191a1b1c1d1e1f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 1415161718191a1b1c1d1e1f101112131415161718191a1b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 202122232425262728292a2b2c2d2e2f2021222324252627 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 2c2d2e2f202122232425262728292a2b2c2d2e2f20212223 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 28292a2b2c2d2e2f202122232425262728292a2b2c2d2e2f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 2425262728292a2b2c2d2e2f202122232425262728292a2b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 303132333435363738393a3b3c3d3e3f3031323334353637 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 3c3d3e3f303132333435363738393a3b3c3d3e3f30313233 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 38393a3b3c3d3e3f303132333435363738393a3b3c3d3e3f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 3435363738393a3b3c3d3e3f303132333435363738393a3b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 404142434445464748494a4b4c4d4e4f4041424344454647 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 4c4d4e4f404142434445464748494a4b4c4d4e4f40414243 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 48494a4b4c4d4e4f404142434445464748494a4b4c4d4e4f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 4445464748494a4b4c4d4e4f404142434445464748494a4b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 505152535455565758595a5b5c5d5e5f5051525354555657 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 5c5d5e5f505152535455565758595a5b5c5d5e5f50515253 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 58595a5b5c5d5e5f505152535455565758595a5b5c5d5e5f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 5455565758595a5b5c5d5e5f505152535455565758595a5b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 606162636465666768696a6b6c6d6e6f6061626364656667 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 6c6d6e6f606162636465666768696a6b6c6d6e6f60616263 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 68696a6b6c6d6e6f606162636465666768696a6b6c6d6e6f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 6465666768696a6b6c6d6e6f606162636465666768696a6b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 707172737475767778797a7b7c7d7e7f7071727374757677 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 7c7d7e7f707172737475767778797a7b7c7d7e7f70717273 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 78797a7b7c7d7e7f707172737475767778797a7b7c7d7e7f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 7475767778797a7b7c7d7e7f707172737475767778797a7b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 808182838485868788898a8b8c8d8e8f8081828384858687 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 8c8d8e8f808182838485868788898a8b8c8d8e8f80818283 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 88898a8b8c8d8e8f808182838485868788898a8b8c8d8e8f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 8485868788898a8b8c8d8e8f808182838485868788898a8b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 909192939495969798999a9b9c9d9e9f9091929394959697 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 9c9d9e9f909192939495969798999a9b9c9d9e9f90919293 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 98999a9b9c9d9e9f909192939495969798999a9b9c9d9e9f -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K 9495969798999a9b9c9d9e9f909192939495969798999a9b -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K a0a1a2a3a4a5a6a7a8a9aaabacadaeafa0a1a2a3a4a5a6a7 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K acadaeafa0a1a2a3a4a5a6a7a8a9aaabacadaeafa0a1a2a3 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K a8a9aaabacadaeafa0a1a2a3a4a5a6a7a8a9aaabacadaeaf -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K a4a5a6a7a8a9aaabacadaeafa0a1a2a3a4a5a6a7a8a9aaab -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K b0b1b2b3b4b5b6b7b8b9babbbcbdbebfb0b1b2b3b4b5b6b7 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K bcbdbebfb0b1b2b3b4b5b6b7b8b9babbbcbdbebfb0b1b2b3 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K b8b9babbbcbdbebfb0b1b2b3b4b5b6b7b8b9babbbcbdbebf -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K b4b5b6b7b8b9babbbcbdbebfb0b1b2b3b4b5b6b7b8b9babb -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K c0c1c2c3c4c5c6c7c8c9cacbcccdcecfc0c1c2c3c4c5c6c7 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K cccdcecfc0c1c2c3c4c5c6c7c8c9cacbcccdcecfc0c1c2c3 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K c8c9cacbcccdcecfc0c1c2c3c4c5c6c7c8c9cacbcccdcecf -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K c4c5c6c7c8c9cacbcccdcecfc0c1c2c3c4c5c6c7c8c9cacb -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K d0d1d2d3d4d5d6d7d8d9dadbdcdddedfd0d1d2d3d4d5d6d7 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K dcdddedfd0d1d2d3d4d5d6d7d8d9dadbdcdddedfd0d1d2d3 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K d8d9dadbdcdddedfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K d4d5d6d7d8d9dadbdcdddedfd0d1d2d3d4d5d6d7d8d9dadb -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K e0e1e2e3e4e5e6e7e8e9eaebecedeeefe0e1e2e3e4e5e6e7 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K ecedeeefe0e1e2e3e4e5e6e7e8e9eaebecedeeefe0e1e2e3 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K e8e9eaebecedeeefe0e1e2e3e4e5e6e7e8e9eaebecedeeef -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K e4e5e6e7e8e9eaebecedeeefe0e1e2e3e4e5e6e7e8e9eaeb -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K f0f1f2f3f4f5f6f7f8f9fafbfcfdfefff0f1f2f3f4f5f6f7 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K fcfdfefff0f1f2f3f4f5f6f7f8f9fafbfcfdfefff0f1f2f3 -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K f8f9fafbfcfdfefff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff -nopad | xxd -p >> tests.aes192.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-192-ecb -K f4f5f6f7f8f9fafbfcfdfefff0f1f2f3f4f5f6f7f8f9fafb -nopad | xxd -p >> tests.aes192.txt
     
     36d12ad8bf3b067f104d7c4706a9bf9d
     b0670b4491b75035e1abc078c34a2e07
     9de85e9eb92d5e557177d07776be3f9a
     a407954bfa330c964aac9cd4a4254024
     4923d3b1cdefcd23246635f97ae1f94e
     cc8d9a08e2fb2b2dba5f759f24588af0
     1467502422e5778b633c280b66382410
     581041533b58147223420959f0693fb6
     f00f8f21a985af5676bbf87f006885d1
     c13570b559487d9a9930e5243841b066
     32f8cc8282ea9cf8a562965c74fcf7d1
     f2a8151b58ca58d3d8f7ffcc13106d18
     0654ed9642a8ae604c84fbf724ed17bd
     b87eb879b371dfd51b6794ba987b0ef0
     43c8327bf304f14205fb76c0a25f3813
     626c9d3e87d51770db7ceb4534a0f1e9
     e520ef2e09f393d62d85f42e65161037
     15f0df76d20cb0694dbfdf947e540be3
     8c9bf74b2e5bc81ca489a61a15e10eae
     eefec794f4bf46c98b4ecebc029dc8ef
     c473a3b8a6c18df2ac337ac7d65c307a
     7d12c3c653343de5de8b76ea59d4bbf7
     e67139e3273e685c49340bae42a4ca20
     bd4957231923d4a4dcfa74f19981c3de
     702830174c7092a471fab3f2178324bf
     344b066264a83299dc72667784be7700
     8f86af4604d282a78c56eeed2048a30b
     f345129fd96c61c74016816f15553de6
     19d97d7efdc93c0c6a50e8cabbea32de
     bdb9a4f8b995fd63c007fa1364512db9
     e480cbf5f6e27f15c580be759896bf42
     6f4efd119151da3ca9828079eea8034a
     342a32dd6b69687df277091f3c6aa845
     7fc74679015e8435dc24cfda52ab5359
     b59244bbd18e3a76c1f4d9cc2d78dcdc
     5c045c3ceddf9afd69aebb2a29ad700d
     70582909b53748f2e7f9c81544dd6885
     217748566faa5b6e9c2ec1bb0212cfc2
     16fa1010ce5a24bdb5bca7dd24a7541f
     9353330383e0b98e06417d3be6479ac8
     5621c66ce285b58f4106ee0006c622c3
     5f616ccf5ed4c3bba6c8cc808427f30b
     7773622201765b8db9df962477b3654e
     25566015fdf9b9214bb1362247741b40
     3d1aee21ac3a21689203d7ab9bc560f4
     7776621520996314726672550ff684e4
     640031c9f79529fb3904edacb842cb99
     5af4cc9559039aa43b4a8d1992f408f3
     c679c0b1161028d99b25048ebc116c6d
     b31bcc3943808d863d2895547c3cec41
     f3ca88a13adfd31b2c12694ecf6ea641
     78d30e4abbe9018acf25ecbf8d54ff44
     b09c071dfe68da467607489ef2508869
     619dbbc8c8a6466a57b3296a965821d5
     f943fd3e2327ae677ff110d852176f62
     12ad8712a77900b220a2f6353db5765b
     11d9697ecdb87dab281655c454c8f097
     343179e6a315e6e31df9340a1b0d2c75
     c04cbb51ec54e7048451ffff172b0d60
     686d2b43e52dba1718c12cda8ecb0121
     ed2c2bdcb477eee4ac62625b8dc42d57
     1e9e333f60dd8280bc11e4032487d913
     a0b555a0c68f25d3b04d1289efeaf29c
     82e96316a764dccff79cf6a9e87b3d1b
     */
    uint8_t Key192SBoxExhaustedExpected[64][16] = {
        { 0x36, 0xd1, 0x2a, 0xd8, 0xbf, 0x3b, 0x06, 0x7f, 0x10, 0x4d, 0x7c, 0x47, 0x06, 0xa9, 0xbf, 0x9d },
        { 0xb0, 0x67, 0x0b, 0x44, 0x91, 0xb7, 0x50, 0x35, 0xe1, 0xab, 0xc0, 0x78, 0xc3, 0x4a, 0x2e, 0x07 },
        { 0x9d, 0xe8, 0x5e, 0x9e, 0xb9, 0x2d, 0x5e, 0x55, 0x71, 0x77, 0xd0, 0x77, 0x76, 0xbe, 0x3f, 0x9a },
        { 0xa4, 0x07, 0x95, 0x4b, 0xfa, 0x33, 0x0c, 0x96, 0x4a, 0xac, 0x9c, 0xd4, 0xa4, 0x25, 0x40, 0x24 },
        { 0x49, 0x23, 0xd3, 0xb1, 0xcd, 0xef, 0xcd, 0x23, 0x24, 0x66, 0x35, 0xf9, 0x7a, 0xe1, 0xf9, 0x4e },
        { 0xcc, 0x8d, 0x9a, 0x08, 0xe2, 0xfb, 0x2b, 0x2d, 0xba, 0x5f, 0x75, 0x9f, 0x24, 0x58, 0x8a, 0xf0 },
        { 0x14, 0x67, 0x50, 0x24, 0x22, 0xe5, 0x77, 0x8b, 0x63, 0x3c, 0x28, 0x0b, 0x66, 0x38, 0x24, 0x10 },
        { 0x58, 0x10, 0x41, 0x53, 0x3b, 0x58, 0x14, 0x72, 0x23, 0x42, 0x09, 0x59, 0xf0, 0x69, 0x3f, 0xb6 },
        { 0xf0, 0x0f, 0x8f, 0x21, 0xa9, 0x85, 0xaf, 0x56, 0x76, 0xbb, 0xf8, 0x7f, 0x00, 0x68, 0x85, 0xd1 },
        { 0xc1, 0x35, 0x70, 0xb5, 0x59, 0x48, 0x7d, 0x9a, 0x99, 0x30, 0xe5, 0x24, 0x38, 0x41, 0xb0, 0x66 },
        { 0x32, 0xf8, 0xcc, 0x82, 0x82, 0xea, 0x9c, 0xf8, 0xa5, 0x62, 0x96, 0x5c, 0x74, 0xfc, 0xf7, 0xd1 },
        { 0xf2, 0xa8, 0x15, 0x1b, 0x58, 0xca, 0x58, 0xd3, 0xd8, 0xf7, 0xff, 0xcc, 0x13, 0x10, 0x6d, 0x18 },
        { 0x06, 0x54, 0xed, 0x96, 0x42, 0xa8, 0xae, 0x60, 0x4c, 0x84, 0xfb, 0xf7, 0x24, 0xed, 0x17, 0xbd },
        { 0xb8, 0x7e, 0xb8, 0x79, 0xb3, 0x71, 0xdf, 0xd5, 0x1b, 0x67, 0x94, 0xba, 0x98, 0x7b, 0x0e, 0xf0 },
        { 0x43, 0xc8, 0x32, 0x7b, 0xf3, 0x04, 0xf1, 0x42, 0x05, 0xfb, 0x76, 0xc0, 0xa2, 0x5f, 0x38, 0x13 },
        { 0x62, 0x6c, 0x9d, 0x3e, 0x87, 0xd5, 0x17, 0x70, 0xdb, 0x7c, 0xeb, 0x45, 0x34, 0xa0, 0xf1, 0xe9 },
        { 0xe5, 0x20, 0xef, 0x2e, 0x09, 0xf3, 0x93, 0xd6, 0x2d, 0x85, 0xf4, 0x2e, 0x65, 0x16, 0x10, 0x37 },
        { 0x15, 0xf0, 0xdf, 0x76, 0xd2, 0x0c, 0xb0, 0x69, 0x4d, 0xbf, 0xdf, 0x94, 0x7e, 0x54, 0x0b, 0xe3 },
        { 0x8c, 0x9b, 0xf7, 0x4b, 0x2e, 0x5b, 0xc8, 0x1c, 0xa4, 0x89, 0xa6, 0x1a, 0x15, 0xe1, 0x0e, 0xae },
        { 0xee, 0xfe, 0xc7, 0x94, 0xf4, 0xbf, 0x46, 0xc9, 0x8b, 0x4e, 0xce, 0xbc, 0x02, 0x9d, 0xc8, 0xef },
        { 0xc4, 0x73, 0xa3, 0xb8, 0xa6, 0xc1, 0x8d, 0xf2, 0xac, 0x33, 0x7a, 0xc7, 0xd6, 0x5c, 0x30, 0x7a },
        { 0x7d, 0x12, 0xc3, 0xc6, 0x53, 0x34, 0x3d, 0xe5, 0xde, 0x8b, 0x76, 0xea, 0x59, 0xd4, 0xbb, 0xf7 },
        { 0xe6, 0x71, 0x39, 0xe3, 0x27, 0x3e, 0x68, 0x5c, 0x49, 0x34, 0x0b, 0xae, 0x42, 0xa4, 0xca, 0x20 },
        { 0xbd, 0x49, 0x57, 0x23, 0x19, 0x23, 0xd4, 0xa4, 0xdc, 0xfa, 0x74, 0xf1, 0x99, 0x81, 0xc3, 0xde },
        { 0x70, 0x28, 0x30, 0x17, 0x4c, 0x70, 0x92, 0xa4, 0x71, 0xfa, 0xb3, 0xf2, 0x17, 0x83, 0x24, 0xbf },
        { 0x34, 0x4b, 0x06, 0x62, 0x64, 0xa8, 0x32, 0x99, 0xdc, 0x72, 0x66, 0x77, 0x84, 0xbe, 0x77, 0x00 },
        { 0x8f, 0x86, 0xaf, 0x46, 0x04, 0xd2, 0x82, 0xa7, 0x8c, 0x56, 0xee, 0xed, 0x20, 0x48, 0xa3, 0x0b },
        { 0xf3, 0x45, 0x12, 0x9f, 0xd9, 0x6c, 0x61, 0xc7, 0x40, 0x16, 0x81, 0x6f, 0x15, 0x55, 0x3d, 0xe6 },
        { 0x19, 0xd9, 0x7d, 0x7e, 0xfd, 0xc9, 0x3c, 0x0c, 0x6a, 0x50, 0xe8, 0xca, 0xbb, 0xea, 0x32, 0xde },
        { 0xbd, 0xb9, 0xa4, 0xf8, 0xb9, 0x95, 0xfd, 0x63, 0xc0, 0x07, 0xfa, 0x13, 0x64, 0x51, 0x2d, 0xb9 },
        { 0xe4, 0x80, 0xcb, 0xf5, 0xf6, 0xe2, 0x7f, 0x15, 0xc5, 0x80, 0xbe, 0x75, 0x98, 0x96, 0xbf, 0x42 },
        { 0x6f, 0x4e, 0xfd, 0x11, 0x91, 0x51, 0xda, 0x3c, 0xa9, 0x82, 0x80, 0x79, 0xee, 0xa8, 0x03, 0x4a },
        { 0x34, 0x2a, 0x32, 0xdd, 0x6b, 0x69, 0x68, 0x7d, 0xf2, 0x77, 0x09, 0x1f, 0x3c, 0x6a, 0xa8, 0x45 },
        { 0x7f, 0xc7, 0x46, 0x79, 0x01, 0x5e, 0x84, 0x35, 0xdc, 0x24, 0xcf, 0xda, 0x52, 0xab, 0x53, 0x59 },
        { 0xb5, 0x92, 0x44, 0xbb, 0xd1, 0x8e, 0x3a, 0x76, 0xc1, 0xf4, 0xd9, 0xcc, 0x2d, 0x78, 0xdc, 0xdc },
        { 0x5c, 0x04, 0x5c, 0x3c, 0xed, 0xdf, 0x9a, 0xfd, 0x69, 0xae, 0xbb, 0x2a, 0x29, 0xad, 0x70, 0x0d },
        { 0x70, 0x58, 0x29, 0x09, 0xb5, 0x37, 0x48, 0xf2, 0xe7, 0xf9, 0xc8, 0x15, 0x44, 0xdd, 0x68, 0x85 },
        { 0x21, 0x77, 0x48, 0x56, 0x6f, 0xaa, 0x5b, 0x6e, 0x9c, 0x2e, 0xc1, 0xbb, 0x02, 0x12, 0xcf, 0xc2 },
        { 0x16, 0xfa, 0x10, 0x10, 0xce, 0x5a, 0x24, 0xbd, 0xb5, 0xbc, 0xa7, 0xdd, 0x24, 0xa7, 0x54, 0x1f },
        { 0x93, 0x53, 0x33, 0x03, 0x83, 0xe0, 0xb9, 0x8e, 0x06, 0x41, 0x7d, 0x3b, 0xe6, 0x47, 0x9a, 0xc8 },
        { 0x56, 0x21, 0xc6, 0x6c, 0xe2, 0x85, 0xb5, 0x8f, 0x41, 0x06, 0xee, 0x00, 0x06, 0xc6, 0x22, 0xc3 },
        { 0x5f, 0x61, 0x6c, 0xcf, 0x5e, 0xd4, 0xc3, 0xbb, 0xa6, 0xc8, 0xcc, 0x80, 0x84, 0x27, 0xf3, 0x0b },
        { 0x77, 0x73, 0x62, 0x22, 0x01, 0x76, 0x5b, 0x8d, 0xb9, 0xdf, 0x96, 0x24, 0x77, 0xb3, 0x65, 0x4e },
        { 0x25, 0x56, 0x60, 0x15, 0xfd, 0xf9, 0xb9, 0x21, 0x4b, 0xb1, 0x36, 0x22, 0x47, 0x74, 0x1b, 0x40 },
        { 0x3d, 0x1a, 0xee, 0x21, 0xac, 0x3a, 0x21, 0x68, 0x92, 0x03, 0xd7, 0xab, 0x9b, 0xc5, 0x60, 0xf4 },
        { 0x77, 0x76, 0x62, 0x15, 0x20, 0x99, 0x63, 0x14, 0x72, 0x66, 0x72, 0x55, 0x0f, 0xf6, 0x84, 0xe4 },
        { 0x64, 0x00, 0x31, 0xc9, 0xf7, 0x95, 0x29, 0xfb, 0x39, 0x04, 0xed, 0xac, 0xb8, 0x42, 0xcb, 0x99 },
        { 0x5a, 0xf4, 0xcc, 0x95, 0x59, 0x03, 0x9a, 0xa4, 0x3b, 0x4a, 0x8d, 0x19, 0x92, 0xf4, 0x08, 0xf3 },
        { 0xc6, 0x79, 0xc0, 0xb1, 0x16, 0x10, 0x28, 0xd9, 0x9b, 0x25, 0x04, 0x8e, 0xbc, 0x11, 0x6c, 0x6d },
        { 0xb3, 0x1b, 0xcc, 0x39, 0x43, 0x80, 0x8d, 0x86, 0x3d, 0x28, 0x95, 0x54, 0x7c, 0x3c, 0xec, 0x41 },
        { 0xf3, 0xca, 0x88, 0xa1, 0x3a, 0xdf, 0xd3, 0x1b, 0x2c, 0x12, 0x69, 0x4e, 0xcf, 0x6e, 0xa6, 0x41 },
        { 0x78, 0xd3, 0x0e, 0x4a, 0xbb, 0xe9, 0x01, 0x8a, 0xcf, 0x25, 0xec, 0xbf, 0x8d, 0x54, 0xff, 0x44 },
        { 0xb0, 0x9c, 0x07, 0x1d, 0xfe, 0x68, 0xda, 0x46, 0x76, 0x07, 0x48, 0x9e, 0xf2, 0x50, 0x88, 0x69 },
        { 0x61, 0x9d, 0xbb, 0xc8, 0xc8, 0xa6, 0x46, 0x6a, 0x57, 0xb3, 0x29, 0x6a, 0x96, 0x58, 0x21, 0xd5 },
        { 0xf9, 0x43, 0xfd, 0x3e, 0x23, 0x27, 0xae, 0x67, 0x7f, 0xf1, 0x10, 0xd8, 0x52, 0x17, 0x6f, 0x62 },
        { 0x12, 0xad, 0x87, 0x12, 0xa7, 0x79, 0x00, 0xb2, 0x20, 0xa2, 0xf6, 0x35, 0x3d, 0xb5, 0x76, 0x5b },
        { 0x11, 0xd9, 0x69, 0x7e, 0xcd, 0xb8, 0x7d, 0xab, 0x28, 0x16, 0x55, 0xc4, 0x54, 0xc8, 0xf0, 0x97 },
        { 0x34, 0x31, 0x79, 0xe6, 0xa3, 0x15, 0xe6, 0xe3, 0x1d, 0xf9, 0x34, 0x0a, 0x1b, 0x0d, 0x2c, 0x75 },
        { 0xc0, 0x4c, 0xbb, 0x51, 0xec, 0x54, 0xe7, 0x04, 0x84, 0x51, 0xff, 0xff, 0x17, 0x2b, 0x0d, 0x60 },
        { 0x68, 0x6d, 0x2b, 0x43, 0xe5, 0x2d, 0xba, 0x17, 0x18, 0xc1, 0x2c, 0xda, 0x8e, 0xcb, 0x01, 0x21 },
        { 0xed, 0x2c, 0x2b, 0xdc, 0xb4, 0x77, 0xee, 0xe4, 0xac, 0x62, 0x62, 0x5b, 0x8d, 0xc4, 0x2d, 0x57 },
        { 0x1e, 0x9e, 0x33, 0x3f, 0x60, 0xdd, 0x82, 0x80, 0xbc, 0x11, 0xe4, 0x03, 0x24, 0x87, 0xd9, 0x13 },
        { 0xa0, 0xb5, 0x55, 0xa0, 0xc6, 0x8f, 0x25, 0xd3, 0xb0, 0x4d, 0x12, 0x89, 0xef, 0xea, 0xf2, 0x9c },
        { 0x82, 0xe9, 0x63, 0x16, 0xa7, 0x64, 0xdc, 0xcf, 0xf7, 0x9c, 0xf6, 0xa9, 0xe8, 0x7b, 0x3d, 0x1b }
    };
    
    for (size_t Loop = 0; Loop < 16; Loop++)
    {
        for (size_t Loop2 = 0; Loop2 < 4; Loop2++)
        {
            TestAes192(DataZero, Key128SBoxExhaust[Loop], Key128SBoxExhaust[Loop], Key192SBoxExhaustedExpected[(Loop * 4) + Loop2]);
            
            Key128SBoxExhaust[Loop] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key128SBoxExhaust[Loop]), 3, 0, 1, 2));
        }
    }
    
    
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     dc95c078a2408989ad48a21492842087
     */
    TestAes256(DataZero, Key128Zero, Key128Zero, (uint8_t[16]){ 0xdc, 0x95, 0xc0, 0x78, 0xa2, 0x40, 0x89, 0x89, 0xad, 0x48, 0xa2, 0x14, 0x92, 0x84, 0x20, 0x87 });
    
    /*
     printf "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     acdace8078a32b1a182bfa4987ca1347
     */
    TestAes256(DataFF, Key128Zero, Key128Zero, (uint8_t[16]){ 0xac, 0xda, 0xce, 0x80, 0x78, 0xa3, 0x2b, 0x1a, 0x18, 0x2b, 0xfa, 0x49, 0x87, 0xca, 0x13, 0x47 });
    
    /*
     printf "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     7bc3026cd737103e62902bcd18fb0163
     */
    TestAes256(DataOnes, Key128Zero, Key128Zero, (uint8_t[16]){ 0x7b, 0xc3, 0x02, 0x6c, 0xd7, 0x37, 0x10, 0x3e, 0x62, 0x90, 0x2b, 0xcd, 0x18, 0xfb, 0x01, 0x63 });
    
    /*
     printf "\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     c9be575aa3eb199ad2411ceccb4561e8
     */
    TestAes256(DataLo, Key128Zero, Key128Zero, (uint8_t[16]){ 0xc9, 0xbe, 0x57, 0x5a, 0xa3, 0xeb, 0x19, 0x9a, 0xd2, 0x41, 0x1c, 0xec, 0xcb, 0x45, 0x61, 0xe8 });
    
    /*
     printf "\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     b2dbbad6b928e9917053988b9a605dc4
     */
    TestAes256(DataHi, Key128Zero, Key128Zero, (uint8_t[16]){ 0xb2, 0xdb, 0xba, 0xd6, 0xb9, 0x28, 0xe9, 0x91, 0x70, 0x53, 0x98, 0x8b, 0x9a, 0x60, 0x5d, 0xc4 });
    
    /*
     printf "abcdefghijklmnop" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     ac9c9eb761551ffb7d78d88b5e233014
     */
    TestAes256(DataABC, Key128Zero, Key128Zero, (uint8_t[16]){ 0xac, 0x9c, 0x9e, 0xb7, 0x61, 0x55, 0x1f, 0xfb, 0x7d, 0x78, 0xd8, 0x8b, 0x5e, 0x23, 0x30, 0x14 });
    
    /*
     printf "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     b65d30030c88b44c975a343f93fb3c09
     */
    TestAes256(DataSBoxExhaust[0], Key128Zero, Key128Zero, (uint8_t[16]){ 0xb6, 0x5d, 0x30, 0x03, 0x0c, 0x88, 0xb4, 0x4c, 0x97, 0x5a, 0x34, 0x3f, 0x93, 0xfb, 0x3c, 0x09 });
    
    /*
     printf "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     61006666010c43379ede85048213921f
     */
    TestAes256(DataSBoxExhaust[1], Key128Zero, Key128Zero, (uint8_t[16]){ 0x61, 0x00, 0x66, 0x66, 0x01, 0x0c, 0x43, 0x37, 0x9e, 0xde, 0x85, 0x04, 0x82, 0x13, 0x92, 0x1f });
    
    /*
     printf "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     ab987da5c8880ac61ce7d1069041bb96
     */
    TestAes256(DataSBoxExhaust[2], Key128Zero, Key128Zero, (uint8_t[16]){ 0xab, 0x98, 0x7d, 0xa5, 0xc8, 0x88, 0x0a, 0xc6, 0x1c, 0xe7, 0xd1, 0x06, 0x90, 0x41, 0xbb, 0x96 });
    
    /*
     printf "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     c53684da13c67ee7b7cb68795eecace8
     */
    TestAes256(DataSBoxExhaust[3], Key128Zero, Key128Zero, (uint8_t[16]){ 0xc5, 0x36, 0x84, 0xda, 0x13, 0xc6, 0x7e, 0xe7, 0xb7, 0xcb, 0x68, 0x79, 0x5e, 0xec, 0xac, 0xe8 });
    
    /*
     printf "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     7695c5abe906dbbb744ca0826e601dff
     */
    TestAes256(DataSBoxExhaust[4], Key128Zero, Key128Zero, (uint8_t[16]){ 0x76, 0x95, 0xc5, 0xab, 0xe9, 0x06, 0xdb, 0xbb, 0x74, 0x4c, 0xa0, 0x82, 0x6e, 0x60, 0x1d, 0xff });
    
    /*
     printf "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     c9634706ffe044b671e4a5254da22ebb
     */
    TestAes256(DataSBoxExhaust[5], Key128Zero, Key128Zero, (uint8_t[16]){ 0xc9, 0x63, 0x47, 0x06, 0xff, 0xe0, 0x44, 0xb6, 0x71, 0xe4, 0xa5, 0x25, 0x4d, 0xa2, 0x2e, 0xbb });
    
    /*
     printf "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     4484f15086be0881abf4339e593563e2
     */
    TestAes256(DataSBoxExhaust[6], Key128Zero, Key128Zero, (uint8_t[16]){ 0x44, 0x84, 0xf1, 0x50, 0x86, 0xbe, 0x08, 0x81, 0xab, 0xf4, 0x33, 0x9e, 0x59, 0x35, 0x63, 0xe2 });
    
    /*
     printf "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     4a0d5ff8f317f1431d8d6b160e6b7e25
     */
    TestAes256(DataSBoxExhaust[7], Key128Zero, Key128Zero, (uint8_t[16]){ 0x4a, 0x0d, 0x5f, 0xf8, 0xf3, 0x17, 0xf1, 0x43, 0x1d, 0x8d, 0x6b, 0x16, 0x0e, 0x6b, 0x7e, 0x25 });
    
    /*
     printf "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     83769a1f948672b53fbec891e2944550
     */
    TestAes256(DataSBoxExhaust[8], Key128Zero, Key128Zero, (uint8_t[16]){ 0x83, 0x76, 0x9a, 0x1f, 0x94, 0x86, 0x72, 0xb5, 0x3f, 0xbe, 0xc8, 0x91, 0xe2, 0x94, 0x45, 0x50 });
    
    /*
     printf "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     718d3b8da34177d68723e8f7b79f9b75
     */
    TestAes256(DataSBoxExhaust[9], Key128Zero, Key128Zero, (uint8_t[16]){ 0x71, 0x8d, 0x3b, 0x8d, 0xa3, 0x41, 0x77, 0xd6, 0x87, 0x23, 0xe8, 0xf7, 0xb7, 0x9f, 0x9b, 0x75 });
    
    /*
     printf "\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     b83eb6b287c1ab54aa236e80e9bf36a8
     */
    TestAes256(DataSBoxExhaust[10], Key128Zero, Key128Zero, (uint8_t[16]){ 0xb8, 0x3e, 0xb6, 0xb2, 0x87, 0xc1, 0xab, 0x54, 0xaa, 0x23, 0x6e, 0x80, 0xe9, 0xbf, 0x36, 0xa8 });
    
    /*
     printf "\xb0\xb1\xb2\xb3\xb4\xb5\xb6\xb7\xb8\xb9\xba\xbb\xbc\xbd\xbe\xbf" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     5c330bdeee24dd54fda0f5ebd9f4f4d8
     */
    TestAes256(DataSBoxExhaust[11], Key128Zero, Key128Zero, (uint8_t[16]){ 0x5c, 0x33, 0x0b, 0xde, 0xee, 0x24, 0xdd, 0x54, 0xfd, 0xa0, 0xf5, 0xeb, 0xd9, 0xf4, 0xf4, 0xd8 });
    
    /*
     printf "\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     0f8132f23570279debb7618f56728846
     */
    TestAes256(DataSBoxExhaust[12], Key128Zero, Key128Zero, (uint8_t[16]){ 0x0f, 0x81, 0x32, 0xf2, 0x35, 0x70, 0x27, 0x9d, 0xeb, 0xb7, 0x61, 0x8f, 0x56, 0x72, 0x88, 0x46 });
    
    /*
     printf "\xd0\xd1\xd2\xd3\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xdd\xde\xdf" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     5f938110d216e80b01c8df2b23930d0d
     */
    TestAes256(DataSBoxExhaust[13], Key128Zero, Key128Zero, (uint8_t[16]){ 0x5f, 0x93, 0x81, 0x10, 0xd2, 0x16, 0xe8, 0x0b, 0x01, 0xc8, 0xdf, 0x2b, 0x23, 0x93, 0x0d, 0x0d });
    
    /*
     printf "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee\xef" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     213c5eacb8c2c28aab973875a00af4b2
     */
    TestAes256(DataSBoxExhaust[14], Key128Zero, Key128Zero, (uint8_t[16]){ 0x21, 0x3c, 0x5e, 0xac, 0xb8, 0xc2, 0xc2, 0x8a, 0xab, 0x97, 0x38, 0x75, 0xa0, 0x0a, 0xf4, 0xb2 });
    
    /*
     printf "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff" | openssl enc -aes-256-ecb -K 0000000000000000000000000000000000000000000000000000000000000000 -nopad | xxd -p
     ec7789725ea154175da09e02415b9f97
     */
    TestAes256(DataSBoxExhaust[15], Key128Zero, Key128Zero, (uint8_t[16]){ 0xec, 0x77, 0x89, 0x72, 0x5e, 0xa1, 0x54, 0x17, 0x5d, 0xa0, 0x9e, 0x02, 0x41, 0x5b, 0x9f, 0x97 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff -nopad | xxd -p
     4bf85f1b5d54adbc307b0a048389adcb
     */
    TestAes256(DataZero, Key128FF, Key128FF, (uint8_t[16]){ 0x4b, 0xf8, 0x5f, 0x1b, 0x5d, 0x54, 0xad, 0xbc, 0x30, 0x7b, 0x0a, 0x04, 0x83, 0x89, 0xad, 0xcb });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 0101010101010101010101010101010101010101010101010101010101010101 -nopad | xxd -p
     7298caa565031eadc6ce23d23ea66378
     */
    TestAes256(DataZero, Key128Ones, Key128Ones, (uint8_t[16]){ 0x72, 0x98, 0xca, 0xa5, 0x65, 0x03, 0x1e, 0xad, 0xc6, 0xce, 0x23, 0xd2, 0x3e, 0xa6, 0x63, 0x78 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 0100000002000000030000000400000005000000060000000700000008000000 -nopad | xxd -p
     fd0749bcb1ed27845c40bac57455afe3
     */
    TestAes256(DataZero, Key128Lo, KeyLo2, (uint8_t[16]){ 0xfd, 0x07, 0x49, 0xbc, 0xb1, 0xed, 0x27, 0x84, 0x5c, 0x40, 0xba, 0xc5, 0x74, 0x55, 0xaf, 0xe3 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 0000000100000002000000030000000400000005000000060000000700000008 -nopad | xxd -p
     b27d23168dfea46e73b40990d8e7f559
     */
    TestAes256(DataZero, Key128Hi, KeyHi2, (uint8_t[16]){ 0xb2, 0x7d, 0x23, 0x16, 0x8d, 0xfe, 0xa4, 0x6e, 0x73, 0xb4, 0x09, 0x90, 0xd8, 0xe7, 0xf5, 0x59 });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 6162636465666768696a6b6c6d6e6f704142434445464748494a4b4c4d4e4f50 -nopad | xxd -p
     bf9b3a4373451d5ad375a069ac40874d
     */
    TestAes256(DataZero, Key128ABC, KeyABC2, (uint8_t[16]){ 0xbf, 0x9b, 0x3a, 0x43, 0x73, 0x45, 0x1d, 0x5a, 0xd3, 0x75, 0xa0, 0x69, 0xac, 0x40, 0x87, 0x4d });
    
    /*
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 0c0d0e0f000102030405060708090a0b0c0d0e0f000102030405060708090a0b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 08090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f0001020304050607 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 0405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f00010203 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 101112131415161718191a1b1c1d1e1f101112131415161718191a1b1c1d1e1f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 1c1d1e1f101112131415161718191a1b1c1d1e1f101112131415161718191a1b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 18191a1b1c1d1e1f101112131415161718191a1b1c1d1e1f1011121314151617 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 1415161718191a1b1c1d1e1f101112131415161718191a1b1c1d1e1f10111213 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 202122232425262728292a2b2c2d2e2f202122232425262728292a2b2c2d2e2f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 2c2d2e2f202122232425262728292a2b2c2d2e2f202122232425262728292a2b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 28292a2b2c2d2e2f202122232425262728292a2b2c2d2e2f2021222324252627 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 2425262728292a2b2c2d2e2f202122232425262728292a2b2c2d2e2f20212223 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 303132333435363738393a3b3c3d3e3f303132333435363738393a3b3c3d3e3f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 3c3d3e3f303132333435363738393a3b3c3d3e3f303132333435363738393a3b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 38393a3b3c3d3e3f303132333435363738393a3b3c3d3e3f3031323334353637 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 3435363738393a3b3c3d3e3f303132333435363738393a3b3c3d3e3f30313233 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 404142434445464748494a4b4c4d4e4f404142434445464748494a4b4c4d4e4f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 4c4d4e4f404142434445464748494a4b4c4d4e4f404142434445464748494a4b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 48494a4b4c4d4e4f404142434445464748494a4b4c4d4e4f4041424344454647 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 4445464748494a4b4c4d4e4f404142434445464748494a4b4c4d4e4f40414243 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 505152535455565758595a5b5c5d5e5f505152535455565758595a5b5c5d5e5f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 5c5d5e5f505152535455565758595a5b5c5d5e5f505152535455565758595a5b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 58595a5b5c5d5e5f505152535455565758595a5b5c5d5e5f5051525354555657 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 5455565758595a5b5c5d5e5f505152535455565758595a5b5c5d5e5f50515253 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 606162636465666768696a6b6c6d6e6f606162636465666768696a6b6c6d6e6f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 6c6d6e6f606162636465666768696a6b6c6d6e6f606162636465666768696a6b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 68696a6b6c6d6e6f606162636465666768696a6b6c6d6e6f6061626364656667 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 6465666768696a6b6c6d6e6f606162636465666768696a6b6c6d6e6f60616263 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 707172737475767778797a7b7c7d7e7f707172737475767778797a7b7c7d7e7f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 7c7d7e7f707172737475767778797a7b7c7d7e7f707172737475767778797a7b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 78797a7b7c7d7e7f707172737475767778797a7b7c7d7e7f7071727374757677 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 7475767778797a7b7c7d7e7f707172737475767778797a7b7c7d7e7f70717273 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 808182838485868788898a8b8c8d8e8f808182838485868788898a8b8c8d8e8f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 8c8d8e8f808182838485868788898a8b8c8d8e8f808182838485868788898a8b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 88898a8b8c8d8e8f808182838485868788898a8b8c8d8e8f8081828384858687 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 8485868788898a8b8c8d8e8f808182838485868788898a8b8c8d8e8f80818283 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 909192939495969798999a9b9c9d9e9f909192939495969798999a9b9c9d9e9f -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 9c9d9e9f909192939495969798999a9b9c9d9e9f909192939495969798999a9b -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 98999a9b9c9d9e9f909192939495969798999a9b9c9d9e9f9091929394959697 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K 9495969798999a9b9c9d9e9f909192939495969798999a9b9c9d9e9f90919293 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K a0a1a2a3a4a5a6a7a8a9aaabacadaeafa0a1a2a3a4a5a6a7a8a9aaabacadaeaf -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K acadaeafa0a1a2a3a4a5a6a7a8a9aaabacadaeafa0a1a2a3a4a5a6a7a8a9aaab -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K a8a9aaabacadaeafa0a1a2a3a4a5a6a7a8a9aaabacadaeafa0a1a2a3a4a5a6a7 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K a4a5a6a7a8a9aaabacadaeafa0a1a2a3a4a5a6a7a8a9aaabacadaeafa0a1a2a3 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K b0b1b2b3b4b5b6b7b8b9babbbcbdbebfb0b1b2b3b4b5b6b7b8b9babbbcbdbebf -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K bcbdbebfb0b1b2b3b4b5b6b7b8b9babbbcbdbebfb0b1b2b3b4b5b6b7b8b9babb -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K b8b9babbbcbdbebfb0b1b2b3b4b5b6b7b8b9babbbcbdbebfb0b1b2b3b4b5b6b7 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K b4b5b6b7b8b9babbbcbdbebfb0b1b2b3b4b5b6b7b8b9babbbcbdbebfb0b1b2b3 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K c0c1c2c3c4c5c6c7c8c9cacbcccdcecfc0c1c2c3c4c5c6c7c8c9cacbcccdcecf -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K cccdcecfc0c1c2c3c4c5c6c7c8c9cacbcccdcecfc0c1c2c3c4c5c6c7c8c9cacb -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K c8c9cacbcccdcecfc0c1c2c3c4c5c6c7c8c9cacbcccdcecfc0c1c2c3c4c5c6c7 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K c4c5c6c7c8c9cacbcccdcecfc0c1c2c3c4c5c6c7c8c9cacbcccdcecfc0c1c2c3 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K d0d1d2d3d4d5d6d7d8d9dadbdcdddedfd0d1d2d3d4d5d6d7d8d9dadbdcdddedf -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K dcdddedfd0d1d2d3d4d5d6d7d8d9dadbdcdddedfd0d1d2d3d4d5d6d7d8d9dadb -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K d8d9dadbdcdddedfd0d1d2d3d4d5d6d7d8d9dadbdcdddedfd0d1d2d3d4d5d6d7 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K d4d5d6d7d8d9dadbdcdddedfd0d1d2d3d4d5d6d7d8d9dadbdcdddedfd0d1d2d3 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K e0e1e2e3e4e5e6e7e8e9eaebecedeeefe0e1e2e3e4e5e6e7e8e9eaebecedeeef -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K ecedeeefe0e1e2e3e4e5e6e7e8e9eaebecedeeefe0e1e2e3e4e5e6e7e8e9eaeb -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K e8e9eaebecedeeefe0e1e2e3e4e5e6e7e8e9eaebecedeeefe0e1e2e3e4e5e6e7 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K e4e5e6e7e8e9eaebecedeeefe0e1e2e3e4e5e6e7e8e9eaebecedeeefe0e1e2e3 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K f0f1f2f3f4f5f6f7f8f9fafbfcfdfefff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K fcfdfefff0f1f2f3f4f5f6f7f8f9fafbfcfdfefff0f1f2f3f4f5f6f7f8f9fafb -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K f8f9fafbfcfdfefff0f1f2f3f4f5f6f7f8f9fafbfcfdfefff0f1f2f3f4f5f6f7 -nopad | xxd -p >> tests.aes256.txt
     printf "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" | openssl enc -aes-256-ecb -K f4f5f6f7f8f9fafbfcfdfefff0f1f2f3f4f5f6f7f8f9fafbfcfdfefff0f1f2f3 -nopad | xxd -p >> tests.aes256.txt

     7c6c258ccc6a400efacc631452a75a25
     8aa893a1a1aee45014697657dca7c07c
     13dabdef0a01ba09abb7cfb846afe46e
     28bafe05a636c4bdb6d7e4aef99c0e79
     64220e5eb003f51f163c1734a5316860
     ef280d74ed18d6b9bc52e6004ddca23d
     04ce06f7f7be08cb0f72bc1f81fe1603
     36fbc94b08a3dfcda99327e9955deaf6
     a1244fec40b4a12d4ae6f07469bbd5b6
     65e15b3f6802543f44018c41a2d17d9f
     27290515a5f6215f36d6963110f51148
     1108a87c3461fafd33da458c00525bf8
     f8c375e7d6f73ebce36e77046a376585
     dae6b6326d1d068910539a878076cf88
     7c9648f4d54ed012bc534a911053961c
     f630d46e8e107be18af9933ca5a03ff3
     53d35458250b1ef0c935c4b929387bf9
     2522ec4c0b73a39b491fe5f30a70a975
     2dd0a7f417054d365500955a76c0793e
     fbbc7b5e59ec9adda8d4c2f0a926f8f6
     d2a57bb2d1471deef5de64360185429f
     9fb343ddd97d08bcdb18dfa3b59911fe
     01dfc94cbda0ca00d214163f789aa3b2
     3cb3efd85afcdeae39efd00cfb65a8e5
     840c9bf21a1162867e778f42b67b98af
     b29913e592fcfe7552e2d9e90a081093
     170cee8b23eaa6e5012dc8b8cd0f8a27
     d6f7e3c1934a83bfb96faffa34d1ddf8
     3d0384ac6bbcd1e52786eb388b8253ed
     3ec0749d82e8fd277529acdb92739052
     76f04ea627bde0cf76da2cb3e5577fde
     3e34fa0e6b37ec226f411beac6dca754
     056b305d20d93420b49fafd45187c394
     875e76e0971929cedc4a40b5d3a2a18f
     97b96500e56609e5486a758ab0a5874d
     020cfe12820b42be88c8c3368dafe422
     4833f002a2dd4696486f6f091b6cc23e
     7dabb7a2b39a0c16b35f3f019b76ef42
     b8efbd9a55db43843845cd12f2a2fe3b
     dd97a2007fb680fce887dcadf0fcaa7d
     445a2d2f9572dfb1425f0ae57e7147d1
     8e75abbabae7a83fea4c425290e77d0b
     0f7f7d9e7f12ef68fc3b4e0aaff9d4a4
     bf2a5db38db443cd534ad9191f156431
     9e3c1461e1fce77b52962eead295f15f
     9c4d073faa4f02f22348ed6b01ce7d46
     a0a348d6d6fff7476842e0b40608729a
     dfe703506f980758570cf8fe289a907d
     495940dd946ec868f6526fefb7cc763c
     cf25c5468b18aa29ed6ac4513c1834d6
     d40d4f03b32e9a649b4eaf9c80a2daac
     a668b6c6e4dede3bfdbcd3ba03eb8d54
     5f28e7e09c37f4ff842c20e7ea39b0e9
     f2993e16dee223f1b62a73c3bd361249
     183b53432cd23a1b584af02f95b68ce9
     fde6caa13f6274570663bd0a73e4c1d4
     c3b382c86405d9354ad40d33a3fdbefd
     bd3d07ce78ce3163c105f424241361a1
     05d3267714a686cd82b91f68b4bc08e6
     3ae3b5e77bd5d55ead437840eda24879
     ca26f44d4f402c9aca5705129f302bbb
     6052501e9e20e6ba77ade2936dd92132
     fea84efdc157167dda2c167ab673490e
     265390dd7947def19d7a3cad281781cb
     */
    uint8_t Key256SBoxExhaustedExpected[64][16] = {
        { 0x7c, 0x6c, 0x25, 0x8c, 0xcc, 0x6a, 0x40, 0x0e, 0xfa, 0xcc, 0x63, 0x14, 0x52, 0xa7, 0x5a, 0x25 },
        { 0x8a, 0xa8, 0x93, 0xa1, 0xa1, 0xae, 0xe4, 0x50, 0x14, 0x69, 0x76, 0x57, 0xdc, 0xa7, 0xc0, 0x7c },
        { 0x13, 0xda, 0xbd, 0xef, 0x0a, 0x01, 0xba, 0x09, 0xab, 0xb7, 0xcf, 0xb8, 0x46, 0xaf, 0xe4, 0x6e },
        { 0x28, 0xba, 0xfe, 0x05, 0xa6, 0x36, 0xc4, 0xbd, 0xb6, 0xd7, 0xe4, 0xae, 0xf9, 0x9c, 0x0e, 0x79 },
        { 0x64, 0x22, 0x0e, 0x5e, 0xb0, 0x03, 0xf5, 0x1f, 0x16, 0x3c, 0x17, 0x34, 0xa5, 0x31, 0x68, 0x60 },
        { 0xef, 0x28, 0x0d, 0x74, 0xed, 0x18, 0xd6, 0xb9, 0xbc, 0x52, 0xe6, 0x00, 0x4d, 0xdc, 0xa2, 0x3d },
        { 0x04, 0xce, 0x06, 0xf7, 0xf7, 0xbe, 0x08, 0xcb, 0x0f, 0x72, 0xbc, 0x1f, 0x81, 0xfe, 0x16, 0x03 },
        { 0x36, 0xfb, 0xc9, 0x4b, 0x08, 0xa3, 0xdf, 0xcd, 0xa9, 0x93, 0x27, 0xe9, 0x95, 0x5d, 0xea, 0xf6 },
        { 0xa1, 0x24, 0x4f, 0xec, 0x40, 0xb4, 0xa1, 0x2d, 0x4a, 0xe6, 0xf0, 0x74, 0x69, 0xbb, 0xd5, 0xb6 },
        { 0x65, 0xe1, 0x5b, 0x3f, 0x68, 0x02, 0x54, 0x3f, 0x44, 0x01, 0x8c, 0x41, 0xa2, 0xd1, 0x7d, 0x9f },
        { 0x27, 0x29, 0x05, 0x15, 0xa5, 0xf6, 0x21, 0x5f, 0x36, 0xd6, 0x96, 0x31, 0x10, 0xf5, 0x11, 0x48 },
        { 0x11, 0x08, 0xa8, 0x7c, 0x34, 0x61, 0xfa, 0xfd, 0x33, 0xda, 0x45, 0x8c, 0x00, 0x52, 0x5b, 0xf8 },
        { 0xf8, 0xc3, 0x75, 0xe7, 0xd6, 0xf7, 0x3e, 0xbc, 0xe3, 0x6e, 0x77, 0x04, 0x6a, 0x37, 0x65, 0x85 },
        { 0xda, 0xe6, 0xb6, 0x32, 0x6d, 0x1d, 0x06, 0x89, 0x10, 0x53, 0x9a, 0x87, 0x80, 0x76, 0xcf, 0x88 },
        { 0x7c, 0x96, 0x48, 0xf4, 0xd5, 0x4e, 0xd0, 0x12, 0xbc, 0x53, 0x4a, 0x91, 0x10, 0x53, 0x96, 0x1c },
        { 0xf6, 0x30, 0xd4, 0x6e, 0x8e, 0x10, 0x7b, 0xe1, 0x8a, 0xf9, 0x93, 0x3c, 0xa5, 0xa0, 0x3f, 0xf3 },
        { 0x53, 0xd3, 0x54, 0x58, 0x25, 0x0b, 0x1e, 0xf0, 0xc9, 0x35, 0xc4, 0xb9, 0x29, 0x38, 0x7b, 0xf9 },
        { 0x25, 0x22, 0xec, 0x4c, 0x0b, 0x73, 0xa3, 0x9b, 0x49, 0x1f, 0xe5, 0xf3, 0x0a, 0x70, 0xa9, 0x75 },
        { 0x2d, 0xd0, 0xa7, 0xf4, 0x17, 0x05, 0x4d, 0x36, 0x55, 0x00, 0x95, 0x5a, 0x76, 0xc0, 0x79, 0x3e },
        { 0xfb, 0xbc, 0x7b, 0x5e, 0x59, 0xec, 0x9a, 0xdd, 0xa8, 0xd4, 0xc2, 0xf0, 0xa9, 0x26, 0xf8, 0xf6 },
        { 0xd2, 0xa5, 0x7b, 0xb2, 0xd1, 0x47, 0x1d, 0xee, 0xf5, 0xde, 0x64, 0x36, 0x01, 0x85, 0x42, 0x9f },
        { 0x9f, 0xb3, 0x43, 0xdd, 0xd9, 0x7d, 0x08, 0xbc, 0xdb, 0x18, 0xdf, 0xa3, 0xb5, 0x99, 0x11, 0xfe },
        { 0x01, 0xdf, 0xc9, 0x4c, 0xbd, 0xa0, 0xca, 0x00, 0xd2, 0x14, 0x16, 0x3f, 0x78, 0x9a, 0xa3, 0xb2 },
        { 0x3c, 0xb3, 0xef, 0xd8, 0x5a, 0xfc, 0xde, 0xae, 0x39, 0xef, 0xd0, 0x0c, 0xfb, 0x65, 0xa8, 0xe5 },
        { 0x84, 0x0c, 0x9b, 0xf2, 0x1a, 0x11, 0x62, 0x86, 0x7e, 0x77, 0x8f, 0x42, 0xb6, 0x7b, 0x98, 0xaf },
        { 0xb2, 0x99, 0x13, 0xe5, 0x92, 0xfc, 0xfe, 0x75, 0x52, 0xe2, 0xd9, 0xe9, 0x0a, 0x08, 0x10, 0x93 },
        { 0x17, 0x0c, 0xee, 0x8b, 0x23, 0xea, 0xa6, 0xe5, 0x01, 0x2d, 0xc8, 0xb8, 0xcd, 0x0f, 0x8a, 0x27 },
        { 0xd6, 0xf7, 0xe3, 0xc1, 0x93, 0x4a, 0x83, 0xbf, 0xb9, 0x6f, 0xaf, 0xfa, 0x34, 0xd1, 0xdd, 0xf8 },
        { 0x3d, 0x03, 0x84, 0xac, 0x6b, 0xbc, 0xd1, 0xe5, 0x27, 0x86, 0xeb, 0x38, 0x8b, 0x82, 0x53, 0xed },
        { 0x3e, 0xc0, 0x74, 0x9d, 0x82, 0xe8, 0xfd, 0x27, 0x75, 0x29, 0xac, 0xdb, 0x92, 0x73, 0x90, 0x52 },
        { 0x76, 0xf0, 0x4e, 0xa6, 0x27, 0xbd, 0xe0, 0xcf, 0x76, 0xda, 0x2c, 0xb3, 0xe5, 0x57, 0x7f, 0xde },
        { 0x3e, 0x34, 0xfa, 0x0e, 0x6b, 0x37, 0xec, 0x22, 0x6f, 0x41, 0x1b, 0xea, 0xc6, 0xdc, 0xa7, 0x54 },
        { 0x05, 0x6b, 0x30, 0x5d, 0x20, 0xd9, 0x34, 0x20, 0xb4, 0x9f, 0xaf, 0xd4, 0x51, 0x87, 0xc3, 0x94 },
        { 0x87, 0x5e, 0x76, 0xe0, 0x97, 0x19, 0x29, 0xce, 0xdc, 0x4a, 0x40, 0xb5, 0xd3, 0xa2, 0xa1, 0x8f },
        { 0x97, 0xb9, 0x65, 0x00, 0xe5, 0x66, 0x09, 0xe5, 0x48, 0x6a, 0x75, 0x8a, 0xb0, 0xa5, 0x87, 0x4d },
        { 0x02, 0x0c, 0xfe, 0x12, 0x82, 0x0b, 0x42, 0xbe, 0x88, 0xc8, 0xc3, 0x36, 0x8d, 0xaf, 0xe4, 0x22 },
        { 0x48, 0x33, 0xf0, 0x02, 0xa2, 0xdd, 0x46, 0x96, 0x48, 0x6f, 0x6f, 0x09, 0x1b, 0x6c, 0xc2, 0x3e },
        { 0x7d, 0xab, 0xb7, 0xa2, 0xb3, 0x9a, 0x0c, 0x16, 0xb3, 0x5f, 0x3f, 0x01, 0x9b, 0x76, 0xef, 0x42 },
        { 0xb8, 0xef, 0xbd, 0x9a, 0x55, 0xdb, 0x43, 0x84, 0x38, 0x45, 0xcd, 0x12, 0xf2, 0xa2, 0xfe, 0x3b },
        { 0xdd, 0x97, 0xa2, 0x00, 0x7f, 0xb6, 0x80, 0xfc, 0xe8, 0x87, 0xdc, 0xad, 0xf0, 0xfc, 0xaa, 0x7d },
        { 0x44, 0x5a, 0x2d, 0x2f, 0x95, 0x72, 0xdf, 0xb1, 0x42, 0x5f, 0x0a, 0xe5, 0x7e, 0x71, 0x47, 0xd1 },
        { 0x8e, 0x75, 0xab, 0xba, 0xba, 0xe7, 0xa8, 0x3f, 0xea, 0x4c, 0x42, 0x52, 0x90, 0xe7, 0x7d, 0x0b },
        { 0x0f, 0x7f, 0x7d, 0x9e, 0x7f, 0x12, 0xef, 0x68, 0xfc, 0x3b, 0x4e, 0x0a, 0xaf, 0xf9, 0xd4, 0xa4 },
        { 0xbf, 0x2a, 0x5d, 0xb3, 0x8d, 0xb4, 0x43, 0xcd, 0x53, 0x4a, 0xd9, 0x19, 0x1f, 0x15, 0x64, 0x31 },
        { 0x9e, 0x3c, 0x14, 0x61, 0xe1, 0xfc, 0xe7, 0x7b, 0x52, 0x96, 0x2e, 0xea, 0xd2, 0x95, 0xf1, 0x5f },
        { 0x9c, 0x4d, 0x07, 0x3f, 0xaa, 0x4f, 0x02, 0xf2, 0x23, 0x48, 0xed, 0x6b, 0x01, 0xce, 0x7d, 0x46 },
        { 0xa0, 0xa3, 0x48, 0xd6, 0xd6, 0xff, 0xf7, 0x47, 0x68, 0x42, 0xe0, 0xb4, 0x06, 0x08, 0x72, 0x9a },
        { 0xdf, 0xe7, 0x03, 0x50, 0x6f, 0x98, 0x07, 0x58, 0x57, 0x0c, 0xf8, 0xfe, 0x28, 0x9a, 0x90, 0x7d },
        { 0x49, 0x59, 0x40, 0xdd, 0x94, 0x6e, 0xc8, 0x68, 0xf6, 0x52, 0x6f, 0xef, 0xb7, 0xcc, 0x76, 0x3c },
        { 0xcf, 0x25, 0xc5, 0x46, 0x8b, 0x18, 0xaa, 0x29, 0xed, 0x6a, 0xc4, 0x51, 0x3c, 0x18, 0x34, 0xd6 },
        { 0xd4, 0x0d, 0x4f, 0x03, 0xb3, 0x2e, 0x9a, 0x64, 0x9b, 0x4e, 0xaf, 0x9c, 0x80, 0xa2, 0xda, 0xac },
        { 0xa6, 0x68, 0xb6, 0xc6, 0xe4, 0xde, 0xde, 0x3b, 0xfd, 0xbc, 0xd3, 0xba, 0x03, 0xeb, 0x8d, 0x54 },
        { 0x5f, 0x28, 0xe7, 0xe0, 0x9c, 0x37, 0xf4, 0xff, 0x84, 0x2c, 0x20, 0xe7, 0xea, 0x39, 0xb0, 0xe9 },
        { 0xf2, 0x99, 0x3e, 0x16, 0xde, 0xe2, 0x23, 0xf1, 0xb6, 0x2a, 0x73, 0xc3, 0xbd, 0x36, 0x12, 0x49 },
        { 0x18, 0x3b, 0x53, 0x43, 0x2c, 0xd2, 0x3a, 0x1b, 0x58, 0x4a, 0xf0, 0x2f, 0x95, 0xb6, 0x8c, 0xe9 },
        { 0xfd, 0xe6, 0xca, 0xa1, 0x3f, 0x62, 0x74, 0x57, 0x06, 0x63, 0xbd, 0x0a, 0x73, 0xe4, 0xc1, 0xd4 },
        { 0xc3, 0xb3, 0x82, 0xc8, 0x64, 0x05, 0xd9, 0x35, 0x4a, 0xd4, 0x0d, 0x33, 0xa3, 0xfd, 0xbe, 0xfd },
        { 0xbd, 0x3d, 0x07, 0xce, 0x78, 0xce, 0x31, 0x63, 0xc1, 0x05, 0xf4, 0x24, 0x24, 0x13, 0x61, 0xa1 },
        { 0x05, 0xd3, 0x26, 0x77, 0x14, 0xa6, 0x86, 0xcd, 0x82, 0xb9, 0x1f, 0x68, 0xb4, 0xbc, 0x08, 0xe6 },
        { 0x3a, 0xe3, 0xb5, 0xe7, 0x7b, 0xd5, 0xd5, 0x5e, 0xad, 0x43, 0x78, 0x40, 0xed, 0xa2, 0x48, 0x79 },
        { 0xca, 0x26, 0xf4, 0x4d, 0x4f, 0x40, 0x2c, 0x9a, 0xca, 0x57, 0x05, 0x12, 0x9f, 0x30, 0x2b, 0xbb },
        { 0x60, 0x52, 0x50, 0x1e, 0x9e, 0x20, 0xe6, 0xba, 0x77, 0xad, 0xe2, 0x93, 0x6d, 0xd9, 0x21, 0x32 },
        { 0xfe, 0xa8, 0x4e, 0xfd, 0xc1, 0x57, 0x16, 0x7d, 0xda, 0x2c, 0x16, 0x7a, 0xb6, 0x73, 0x49, 0x0e },
        { 0x26, 0x53, 0x90, 0xdd, 0x79, 0x47, 0xde, 0xf1, 0x9d, 0x7a, 0x3c, 0xad, 0x28, 0x17, 0x81, 0xcb }
    };
    
    for (size_t Loop = 9; Loop < 16; Loop++)
    {
        for (size_t Loop2 = 0; Loop2 < 4; Loop2++)
        {
            TestAes256(DataZero, Key128SBoxExhaust[Loop], Key128SBoxExhaust[Loop], Key256SBoxExhaustedExpected[(Loop * 4) + Loop2]);
            
            Key128SBoxExhaust[Loop] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key128SBoxExhaust[Loop]), 3, 0, 1, 2));
        }
    }
}

@end
