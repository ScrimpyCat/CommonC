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

-(void) testAesKeyExpansion
{
    uint32_t ExpectedKeys128[10][4] = {
        { 0x17fefaa0, 0xb12c5488, 0x3939a323, 0x05766c2a },
        { 0xf295c2f2, 0x43b9967a, 0x7a803559, 0x7ff65973 },
        { 0x7d47803d, 0x3efe1647, 0x447e231e, 0x3b887a6d },
        { 0x41a544ef, 0x7f5b52a8, 0x3b2571b6, 0x00ad0bdb },
        { 0xf8c6d1d4, 0x879d837c, 0xbcb8f2ca, 0xbc15f911 },
        { 0x7aa3886d, 0xfd3e0b11, 0x4186f9db, 0xfd9300ca },
        { 0x0ef7544e, 0xf3c95f5f, 0xb24fa684, 0x4fdca64e },
        { 0x2173d2ea, 0xd2ba8db5, 0x60f52b31, 0x2f298d7f },
        { 0xf36677ac, 0x21dcfa19, 0x4129d128, 0x6e005c57 },
        { 0xa8f914d0, 0x8925eec9, 0xc80c3fe1, 0xa60c63b6 }
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
    
}

-(void) testAes
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

@end
