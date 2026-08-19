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

#ifndef CommonC_Crypto_h
#define CommonC_Crypto_h

#include <CommonC/Simd.h>
#include <CommonC/Alignment.h>

typedef struct {
#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
    CCSimd_u32x4 c0;
    CCSimd_u32x4 c1;
    CCSimd_u32x4 c2;
    CCSimd_u32x4 c3;
#endif
} CCCryptoSha1Constants;

typedef CCSimd_u32x4x2 CCCryptoSha1State;


typedef struct {
#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
    CCSimd_u32x4 c0;
    CCSimd_u32x4 c1;
    CCSimd_u32x4 c2;
    CCSimd_u32x4 c3;
    CCSimd_u32x4 c4;
    CCSimd_u32x4 c5;
    CCSimd_u32x4 c6;
    CCSimd_u32x4 c7;
    CCSimd_u32x4 c8;
    CCSimd_u32x4 c9;
    CCSimd_u32x4 c10;
    CCSimd_u32x4 c11;
    CCSimd_u32x4 c12;
    CCSimd_u32x4 c13;
    CCSimd_u32x4 c14;
    CCSimd_u32x4 c15;
#endif
} CCCryptoSha256Constants;

typedef CCSimd_u32x4x2 CCCryptoSha256State;

/*!
 * @brief Calculate the SHA1 hash for the provided data.
 * @param Data The data to hash.
 * @param Size The size of the data.
 * @return The SHA1 hash state.
 */
CCCryptoSha1State CCCryptoSha1(const void *Data, size_t Size);

/*!
 * @brief Calculate the SHA256 hash for the provided data.
 * @param Data The data to hash.
 * @param Size The size of the data.
 * @return The SHA256 hash state.
 */
CCCryptoSha256State CCCryptoSha256(const void *Data, size_t Size);

/*!
 * @brief Initialise SHA1 state with default values.
 * @return The SHA1 hash state.
 */
static CC_FORCE_INLINE CCCryptoSha1State CCCryptoSha1StateInit(void);

/*!
 * @brief Initialise SHA1 constants.
 * @return The SHA1 constants.
 */
static CC_FORCE_INLINE CCCryptoSha1Constants CCCryptoSha1ConstantsInit(void);

/*!
 * @brief Prepare the data to be hashed.
 * @description This will modify the data to include the end bit, padding and bit size.
 * @warning Data must be large enough to store this modification.
 * @param Data The data to be prepared.
 * @param Size The size of the data.
 * @return The number of chunks.
 */
static CC_FORCE_INLINE size_t CCCryptoSha1Prepare(void *Data, size_t Size);

/*!
 * @brief Update the hash state by processing the 64-byte chunk of data.
 * @param State The current SHA1 hash state.
 * @param Data The chunk to be processed.
 * @param Constants The SHA1 constants.
 * @return The new hash state.
 */
static CC_FORCE_INLINE CCCryptoSha1State CCCryptoSha1Process(CCCryptoSha1State State, const void *Data, CCCryptoSha1Constants Constants);

/*!
 * @brief Store the SHA1 hash.
 * @param State The current SHA1 hash state to be stored.
 * @param Data A pointer to 5 uint32_t's for where the hash will be stored.
 */
static CC_FORCE_INLINE void CCCryptoSha1Store(CCCryptoSha1State State, uint32_t *Data);

/*!
 * @brief Initialise SHA256 state with default values.
 * @return The SHA256 hash state.
 */
static CC_FORCE_INLINE CCCryptoSha256State CCCryptoSha256StateInit(void);

/*!
 * @brief Initialise SHA256 constants.
 * @return The SHA256 constants.
 */
static CC_FORCE_INLINE CCCryptoSha256Constants CCCryptoSha256ConstantsInit(void);

/*!
 * @brief Prepare the data to be hashed.
 * @description This will modify the data to include the end bit, padding and bit size.
 * @warning Data must be large enough to store this modification.
 * @param Data The data to be prepared.
 * @param Size The size of the data.
 * @return The number of chunks.
 */
static CC_FORCE_INLINE size_t CCCryptoSha256Prepare(void *Data, size_t Size);

/*!
 * @brief Update the hash state by processing the 64-byte chunk of data.
 * @param State The current SHA256 hash state.
 * @param Data The chunk to be processed.
 * @param Constants The SHA256 constants.
 * @return The new hash state.
 */
static CC_FORCE_INLINE CCCryptoSha256State CCCryptoSha256Process(CCCryptoSha256State State, const void *Data, CCCryptoSha256Constants Constants);

/*!
 * @brief Store the SHA256 hash.
 * @param State The current SHA256 hash state to be stored.
 * @param Data A pointer to 8 uint32_t's for where the hash will be stored.
 */
static CC_FORCE_INLINE void CCCryptoSha256Store(CCCryptoSha1State State, uint32_t *Data);

/*!
 * @brief Perform one round of AES-128 key expansion.
 * @param Key The key of the last round or initial key.
 * @param Round The round number.
 * @return The expanded key for the following round.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128KeyExpandRound(CCSimd_u8x16 Key, size_t Round);

/*!
 * @brief Retrieve the AES-128 expanded key.
 * @param Key The initial key.
 * @param ExpandedKey A pointer to store all 11 rounds of the expanded key.
 */
static CC_FORCE_INLINE void CCCryptoAes128KeyExpand(CCSimd_u8x16 Key, CCSimd_u8x16 ExpandedKey[11]);

/*!
 * @brief Encrypt block using AES-128.
 * @param Data The plain text block to be encrypted.
 * @param Key The expanded key for all 11 rounds.
 * @return The cipher text.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128Encrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[11]);

/*!
 * @brief Decrypt block using AES-128.
 * @param Data The cipher text block to be decrypted.
 * @param Key The expanded key for all 11 rounds.
 * @return The plain text.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128Decrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[11]);

#pragma mark -

static CC_FORCE_INLINE CCCryptoSha1State CCCryptoSha1StateInit(void)
{
    return (CCCryptoSha1State){
        .v = {
            CCSimdLoad_u32x4((uint32_t[4]){ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 }),
            CCSimdFill_u32x4(0xc3d2e1f0)
        }
    };
}

static CC_FORCE_INLINE CCCryptoSha1Constants CCCryptoSha1ConstantsInit(void)
{
    return (CCCryptoSha1Constants){
#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
        .c0 = CCSimdFill_u32x4(0x5a827999),
        .c1 = CCSimdFill_u32x4(0x6ed9eba1),
        .c2 = CCSimdFill_u32x4(0x8f1bbcdc),
        .c3 = CCSimdFill_u32x4(0xca62c1d6)
#endif
    };
}

static CC_FORCE_INLINE size_t CCCryptoSha1Prepare(void *Data, size_t Size)
{
    const size_t Base = (Size / 64) * 64;
    size_t Index = Size % 64;
    
    ((uint8_t*)Data)[Size] = 0x80;
    
    Index = ((Index + 9) > 64 ? CC_ALIGN(Size + 64, 64) : CC_ALIGN(Base + Index + 9, 64)) - 8;
    
    uint64_t BitSize = Size * 8;
    ((uint8_t*)Data)[Index + 7] = BitSize & 0xff;
    ((uint8_t*)Data)[Index + 6] = (BitSize >> 8) & 0xff;
    ((uint8_t*)Data)[Index + 5] = (BitSize >> 16) & 0xff;
    ((uint8_t*)Data)[Index + 4] = (BitSize >> 24) & 0xff;
    ((uint8_t*)Data)[Index + 3] = (BitSize >> 32) & 0xff;
    ((uint8_t*)Data)[Index + 2] = (BitSize >> 40) & 0xff;
    ((uint8_t*)Data)[Index + 1] = (BitSize >> 48) & 0xff;
    ((uint8_t*)Data)[Index + 0] = (BitSize >> 56) & 0xff;
    
    return (Index / 64) + 1;
}

static CC_FORCE_INLINE CCCryptoSha1State CCCryptoSha1Process(CCCryptoSha1State State, const void *Data, CCCryptoSha1Constants Constants)
{
#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
    CCSimd_u32x4x4 Msg = {
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 0)),
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 4)),
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 8)),
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 12))
    };
    
    CCSimd_u32x4 Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c0);
    CCSimd_u32x4 Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c0);
    
    uint32_t E0 = CCSimdGet_u32x4(State.v[1], 0), E1;
    
    const CCSimd_u32x4 PrevState = State.v[0];
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1cq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c0);
    Msg.v[0] = vsha1su0q_u32(Msg.v[0], Msg.v[1], Msg.v[2]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1cq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c0);
    Msg.v[0] = vsha1su1q_u32(Msg.v[0], Msg.v[3]);
    Msg.v[1] = vsha1su0q_u32(Msg.v[1], Msg.v[2], Msg.v[3]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1cq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c0);
    Msg.v[1] = vsha1su1q_u32(Msg.v[1], Msg.v[0]);
    Msg.v[2] = vsha1su0q_u32(Msg.v[2], Msg.v[3], Msg.v[0]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1cq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c1);
    Msg.v[2] = vsha1su1q_u32(Msg.v[2], Msg.v[1]);
    Msg.v[3] = vsha1su0q_u32(Msg.v[3], Msg.v[0], Msg.v[1]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1cq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c1);
    Msg.v[3] = vsha1su1q_u32(Msg.v[3], Msg.v[2]);
    Msg.v[0] = vsha1su0q_u32(Msg.v[0], Msg.v[1], Msg.v[2]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c1);
    Msg.v[0] = vsha1su1q_u32(Msg.v[0], Msg.v[3]);
    Msg.v[1] = vsha1su0q_u32(Msg.v[1], Msg.v[2], Msg.v[3]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c1);
    Msg.v[1] = vsha1su1q_u32(Msg.v[1], Msg.v[0]);
    Msg.v[2] = vsha1su0q_u32(Msg.v[2], Msg.v[3], Msg.v[0]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c1);
    Msg.v[2] = vsha1su1q_u32(Msg.v[2], Msg.v[1]);
    Msg.v[3] = vsha1su0q_u32(Msg.v[3], Msg.v[0], Msg.v[1]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c2);
    Msg.v[3] = vsha1su1q_u32(Msg.v[3], Msg.v[2]);
    Msg.v[0] = vsha1su0q_u32(Msg.v[0], Msg.v[1], Msg.v[2]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c2);
    Msg.v[0] = vsha1su1q_u32(Msg.v[0], Msg.v[3]);
    Msg.v[1] = vsha1su0q_u32(Msg.v[1], Msg.v[2], Msg.v[3]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1mq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c2);
    Msg.v[1] = vsha1su1q_u32(Msg.v[1], Msg.v[0]);
    Msg.v[2] = vsha1su0q_u32(Msg.v[2], Msg.v[3], Msg.v[0]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1mq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c2);
    Msg.v[2] = vsha1su1q_u32(Msg.v[2], Msg.v[1]);
    Msg.v[3] = vsha1su0q_u32(Msg.v[3], Msg.v[0], Msg.v[1]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1mq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c2);
    Msg.v[3] = vsha1su1q_u32(Msg.v[3], Msg.v[2]);
    Msg.v[0] = vsha1su0q_u32(Msg.v[0], Msg.v[1], Msg.v[2]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1mq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c3);
    Msg.v[0] = vsha1su1q_u32(Msg.v[0], Msg.v[3]);
    Msg.v[1] = vsha1su0q_u32(Msg.v[1], Msg.v[2], Msg.v[3]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1mq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c3);
    Msg.v[1] = vsha1su1q_u32(Msg.v[1], Msg.v[0]);
    Msg.v[2] = vsha1su0q_u32(Msg.v[2], Msg.v[3], Msg.v[0]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c3);
    Msg.v[2] = vsha1su1q_u32(Msg.v[2], Msg.v[1]);
    Msg.v[3] = vsha1su0q_u32(Msg.v[3], Msg.v[0], Msg.v[1]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E0, Temp0);
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c3);
    Msg.v[3] = vsha1su1q_u32(Msg.v[3], Msg.v[2]);
    Msg.v[0] = vsha1su0q_u32(Msg.v[0], Msg.v[1], Msg.v[2]);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E1, Temp1);
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c3);
    Msg.v[0] = vsha1su1q_u32(Msg.v[0], Msg.v[3]);
    
    E1 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = vsha1pq_u32(State.v[0], E0, Temp0);
    
    E0 = vsha1h_u32(CCSimdGet_u32x4(State.v[0], 0));
    State.v[0] = CCSimdAdd_u32x4(PrevState, vsha1pq_u32(State.v[0], E1, Temp1));
    
    // TODO: Fix compiler moving to GPR.
    State.v[1] = CCSimdSet_u32x4(State.v[1], 0, CCSimdGet_u32x4(State.v[1], 0) + E0);
    
    return State;
#endif
}

static CC_FORCE_INLINE void CCCryptoSha1Store(CCCryptoSha1State State, uint32_t *Data)
{
    CCSimdStore_u32x4(Data, State.v[0]);
    Data[4] = CCSimdGet_u32x4(State.v[1], 0);
}

static CC_FORCE_INLINE CCCryptoSha256State CCCryptoSha256StateInit(void)
{
    return (CCCryptoSha256State){
        .v = {
            CCSimdLoad_u32x4((uint32_t[4]){ 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a }),
            CCSimdLoad_u32x4((uint32_t[4]){ 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 }),
        }
    };
}

static CC_FORCE_INLINE CCCryptoSha256Constants CCCryptoSha256ConstantsInit(void)
{
    return (CCCryptoSha256Constants){
#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
        .c0 = CCSimdLoad_u32x4((uint32_t[4]){ 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5 }),
        .c1 = CCSimdLoad_u32x4((uint32_t[4]){ 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5 }),
        .c2 = CCSimdLoad_u32x4((uint32_t[4]){ 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3 }),
        .c3 = CCSimdLoad_u32x4((uint32_t[4]){ 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174 }),
        .c4 = CCSimdLoad_u32x4((uint32_t[4]){ 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc }),
        .c5 = CCSimdLoad_u32x4((uint32_t[4]){ 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da }),
        .c6 = CCSimdLoad_u32x4((uint32_t[4]){ 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7 }),
        .c7 = CCSimdLoad_u32x4((uint32_t[4]){ 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967 }),
        .c8 = CCSimdLoad_u32x4((uint32_t[4]){ 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13 }),
        .c9 = CCSimdLoad_u32x4((uint32_t[4]){ 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85 }),
        .c10 = CCSimdLoad_u32x4((uint32_t[4]){ 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3 }),
        .c11 = CCSimdLoad_u32x4((uint32_t[4]){ 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070 }),
        .c12 = CCSimdLoad_u32x4((uint32_t[4]){ 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5 }),
        .c13 = CCSimdLoad_u32x4((uint32_t[4]){ 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3 }),
        .c14 = CCSimdLoad_u32x4((uint32_t[4]){ 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208 }),
        .c15 = CCSimdLoad_u32x4((uint32_t[4]){ 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 })
#endif
    };
}

static CC_FORCE_INLINE size_t CCCryptoSha256Prepare(void *Data, size_t Size)
{
    return CCCryptoSha1Prepare(Data, Size);
}

static CC_FORCE_INLINE CCCryptoSha256State CCCryptoSha256Process(CCCryptoSha256State State, const void *Data, CCCryptoSha256Constants Constants)
{
#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
    CCSimd_u32x4x4 Msg = {
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 0)),
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 4)),
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 8)),
        CCSimdReverse_u32x4(CCSimdLoad_u32x4(((uint32_t*)Data) + 12))
    };
    
    CCSimd_u32x4 Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c0), Temp1, Temp2;
    
    const CCCryptoSha256State PrevState = State;
    
    Msg.v[0] = vsha256su0q_u32(Msg.v[0], Msg.v[1]);
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c1);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    Msg.v[0] = vsha256su1q_u32(Msg.v[0], Msg.v[2], Msg.v[3]);
    
    Msg.v[1] = vsha256su0q_u32(Msg.v[1], Msg.v[2]);
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c2);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    Msg.v[1] = vsha256su1q_u32(Msg.v[1], Msg.v[3], Msg.v[0]);
    
    Msg.v[2] = vsha256su0q_u32(Msg.v[2], Msg.v[3]);
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c3);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    Msg.v[2] = vsha256su1q_u32(Msg.v[2], Msg.v[0], Msg.v[1]);
    
    Msg.v[3] = vsha256su0q_u32(Msg.v[3], Msg.v[0]);
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c4);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    Msg.v[3] = vsha256su1q_u32(Msg.v[3], Msg.v[1], Msg.v[2]);
    
    Msg.v[0] = vsha256su0q_u32(Msg.v[0], Msg.v[1]);
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c5);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    Msg.v[0] = vsha256su1q_u32(Msg.v[0], Msg.v[2], Msg.v[3]);
    
    Msg.v[1] = vsha256su0q_u32(Msg.v[1], Msg.v[2]);
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c6);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    Msg.v[1] = vsha256su1q_u32(Msg.v[1], Msg.v[3], Msg.v[0]);
    
    Msg.v[2] = vsha256su0q_u32(Msg.v[2], Msg.v[3]);
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c7);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    Msg.v[2] = vsha256su1q_u32(Msg.v[2], Msg.v[0], Msg.v[1]);
    
    Msg.v[3] = vsha256su0q_u32(Msg.v[3], Msg.v[0]);
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c8);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    Msg.v[3] = vsha256su1q_u32(Msg.v[3], Msg.v[1], Msg.v[2]);
    
    Msg.v[0] = vsha256su0q_u32(Msg.v[0], Msg.v[1]);
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c9);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    Msg.v[0] = vsha256su1q_u32(Msg.v[0], Msg.v[2], Msg.v[3]);
    
    Msg.v[1] = vsha256su0q_u32(Msg.v[1], Msg.v[2]);
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c10);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    Msg.v[1] = vsha256su1q_u32(Msg.v[1], Msg.v[3], Msg.v[0]);
    
    Msg.v[2] = vsha256su0q_u32(Msg.v[2], Msg.v[3]);
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c11);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    Msg.v[2] = vsha256su1q_u32(Msg.v[2], Msg.v[0], Msg.v[1]);
    
    Msg.v[3] = vsha256su0q_u32(Msg.v[3], Msg.v[0]);
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[0], Constants.c12);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    Msg.v[3] = vsha256su1q_u32(Msg.v[3], Msg.v[1], Msg.v[2]);
    
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[1], Constants.c13);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    
    Temp2 = State.v[0];
    Temp0 = CCSimdAdd_u32x4(Msg.v[2], Constants.c14);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    
    Temp2 = State.v[0];
    Temp1 = CCSimdAdd_u32x4(Msg.v[3], Constants.c15);
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp0);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp0);
    
    Temp2 = State.v[0];
    State.v[0] = vsha256hq_u32(State.v[0], State.v[1], Temp1);
    State.v[1] = vsha256h2q_u32(State.v[1], Temp2, Temp1);
    
    State.v[0] = CCSimdAdd_u32x4(PrevState.v[0], State.v[0]);
    State.v[1] = CCSimdAdd_u32x4(PrevState.v[1], State.v[1]);
    
    return State;
#endif
}

static CC_FORCE_INLINE void CCCryptoSha256Store(CCCryptoSha256State State, uint32_t *Data)
{
    CCSimdStore_u32x4(Data, State.v[0]);
    CCSimdStore_u32x4(Data + 4, State.v[1]);
}

static uint8_t CCCryptoAesKeySBox[] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,
};

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128KeyExpandRound(CCSimd_u8x16 Key, size_t Round)
{
    //rot word
    CCSimd_u8x16 Temp = CCSimdSwizzle_u8x16(Key,
                                            (1 + (4 * 0)), (2 + (4 * 0)), (3 + (4 * 0)), (0 + (4 * 0)),
                                            (1 + (4 * 1)), (2 + (4 * 1)), (3 + (4 * 1)), (0 + (4 * 1)),
                                            (1 + (4 * 2)), (2 + (4 * 2)), (3 + (4 * 2)), (0 + (4 * 2)),
                                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)));
    
    // s-box
//    uint8_t v[16];
//    CCSimdStore_u8x16(v, Key);
//    for (size_t Loop = 0; Loop < 16; Loop++)
//    {
//        v[Loop] = CCCryptoAesKeySBox[v[Loop]];
//    }
//    CCSimd_u8x16 vk = CCSimdLoad_u8x16(v);
    
    Temp = vaeseq_u8(Temp, CCSimdZero_u8x16());
    Temp = CCSimdSwizzle_u8x16(Temp,
                               (0 + (4 * 3)), (1 + (4 * 2)), (2 + (4 * 1)), (3 + (4 * 0)),
                               (0 + (4 * 3)), (1 + (4 * 2)), (2 + (4 * 1)), (3 + (4 * 0)),
                               (0 + (4 * 3)), (1 + (4 * 2)), (2 + (4 * 1)), (3 + (4 * 0)),
                               (0 + (4 * 3)), (1 + (4 * 2)), (2 + (4 * 1)), (3 + (4 * 0)));
    
    //Rcon
    uint8_t CCCryptoAesKeyExpansionRoundConstants[10][16] = {
        0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
        0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
        0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00,
        0x36, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
    };
    
    CCSimd_u8x16 Rcon = CCSimdLoad_u8x16(CCCryptoAesKeyExpansionRoundConstants[Round]);
    Temp = CCSimdXor_u8x16(Temp, Rcon);
    
    CCSimd_u32x4 Mask = CCSimdLoad_u32x4((uint32_t[4]){ 0, 0xffffffff, 0xffffffff, 0xffffffff });
    
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1, w^k2, w^k3
    
    Key = CCSimd_u8x16_Reinterpret_u32x4(CCSimdAnd_u8x16(Mask, CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key), 3, 0, 1, 2)));
    Mask = CCSimdAnd_u8x16(Mask, CCSimdSwizzle_u32x4(Mask, 3, 0, 1, 2));
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1^k0, w^k2^k1, w^k3^k2
    
    Key = CCSimd_u8x16_Reinterpret_u32x4(CCSimdAnd_u8x16(Mask, CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key), 3, 0, 1, 2)));
    Mask = CCSimdAnd_u8x16(Mask, CCSimdSwizzle_u32x4(Mask, 3, 0, 1, 2));
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1
    
    Key = CCSimd_u8x16_Reinterpret_u32x4(CCSimdAnd_u8x16(Mask, CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key), 3, 0, 1, 2)));
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1^k0
    
    return Temp;
}

static CC_FORCE_INLINE void CCCryptoAes128KeyExpand(CCSimd_u8x16 Key, CCSimd_u8x16 ExpandedKey[11])
{
    for (size_t Loop = 0; Loop < 10; Loop++)
    {
        ExpandedKey[Loop] = Key;
        Key = CCCryptoAes128KeyExpandRound(Key, Loop);
    }
    
    ExpandedKey[10] = Key;
}

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128Encrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[11])
{
    for (size_t Loop = 0; Loop < 9; Loop++)
    {
        Data = vaeseq_u8(Data, Key[Loop]);
        Data = vaesmcq_u8(Data);
    }
    
    Data = vaeseq_u8(Data, Key[9]);
    
    return CCSimdXor_u8x16(Data, Key[10]);
}

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128Decrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[11])
{
    Data = vaesdq_u8(Data, Key[10]);
    
    for (size_t Loop = 0; Loop < 9; Loop++)
    {
        Data = vaesimcq_u8(Data);
        
        Data = vaesdq_u8(Data, vaesimcq_u8(Key[9 - Loop]));
    }
    
    Data = CCSimdXor_u8x16(Data, Key[0]);
    
    return Data;
}

#endif
