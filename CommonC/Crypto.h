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
#include <CommonC/Order.h>

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

/*!
 * @brief Perform one round of AES-192 key expansion.
 * @param Key The key of the last round or initial key.
 * @param Round The round number.
 * @return The expanded key for the following round.
 */
static CC_FORCE_INLINE CCSimd_u8x16x2 CCCryptoAes192KeyExpandRound(CCSimd_u8x16x2 Key, size_t Round);

/*!
 * @brief Retrieve the AES-192 expanded key.
 * @param Key The initial key.
 * @param ExpandedKey A pointer to store all 13 rounds of the expanded key.
 */
static CC_FORCE_INLINE void CCCryptoAes192KeyExpand(CCSimd_u8x16x2 Key, CCSimd_u8x16 ExpandedKey[13]);

/*!
 * @brief Encrypt block using AES-192.
 * @param Data The plain text block to be encrypted.
 * @param Key The expanded key for all 13 rounds.
 * @return The cipher text.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes192Encrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[13]);

/*!
 * @brief Decrypt block using AES-192.
 * @param Data The cipher text block to be decrypted.
 * @param Key The expanded key for all 13 rounds.
 * @return The plain text.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes192Decrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[13]);

/*!
 * @brief Perform one round of AES-256 key expansion.
 * @param Key The key of the last round or initial key.
 * @param Round The round number.
 * @return The expanded key for the following round.
 */
static CC_FORCE_INLINE CCSimd_u8x16x2 CCCryptoAes256KeyExpandRound(CCSimd_u8x16x2 Key, size_t Round);

/*!
 * @brief Retrieve the AES-256 expanded key.
 * @param Key The initial key.
 * @param ExpandedKey A pointer to store all 15 rounds of the expanded key.
 */
static CC_FORCE_INLINE void CCCryptoAes256KeyExpand(CCSimd_u8x16x2 Key, CCSimd_u8x16 ExpandedKey[15]);

/*!
 * @brief Encrypt block using AES-256.
 * @param Data The plain text block to be encrypted.
 * @param Key The expanded key for all 15 rounds.
 * @return The cipher text.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes192Encrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[15]);

/*!
 * @brief Decrypt block using AES-256.
 * @param Data The cipher text block to be decrypted.
 * @param Key The expanded key for all 15 rounds.
 * @return The plain text.
 */
static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes256Decrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[15]);

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

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAesKeyExpansionRoundConstant(size_t Round)
{
    const uint32_t RC[51] = {
        CC_MAP(CC_LITTLE_32,
               0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
               0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72,
               0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74,
               0xe8, 0xcb, 0x8d
        )
    };
    
    return CCSimd_u8x16_Reinterpret_u32x4(CCSimdFill_u32x4(RC[Round % 51]));
}

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes128KeyExpandRound(CCSimd_u8x16 Key, size_t Round)
{
    //rot word
    CCSimd_u8x16 Temp = CCSimdSwizzle_u8x16(Key,
                                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)),
                                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)),
                                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)),
                                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)));
    
    //s-box
    Temp = vaeseq_u8(Temp, CCSimdZero_u8x16());
    
    //Rcon
    Temp = CCSimdXor_u8x16(Temp, CCCryptoAesKeyExpansionRoundConstant(Round));
    
    const CCSimd_u32x4 Zero = CCSimdZero_u32x4();
        
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1, w^k2, w^k3
    
    Key = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u32x4(Zero, CCSimd_u32x4_Reinterpret_u8x16(Key), CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2));
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1^k0, w^k2^k1, w^k3^k2
    
    Key = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key), 0, 0, 1, 2));
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1
    
    Key = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key), 0, 0, 1, 2));
    Temp = CCSimdXor_u8x16(Temp, Key); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1^k0
    
    return Temp;
}

static CC_FORCE_INLINE CCSimd_u8x16x2 CCCryptoAes192KeyExpandRound(CCSimd_u8x16x2 Key, size_t Round)
{
    //rot word
    CCSimd_u8x16x2 Temp = {
        Key.v[0],
        CCSimdSwizzle_u8x16(Key.v[1],
                            (1 + (4 * 1)), (2 + (4 * 1)), (3 + (4 * 1)), (0 + (4 * 1)),
                            (1 + (4 * 1)), (2 + (4 * 1)), (3 + (4 * 1)), (0 + (4 * 1)),
                            (1 + (4 * 1)), (2 + (4 * 1)), (3 + (4 * 1)), (0 + (4 * 1)),
                            (1 + (4 * 1)), (2 + (4 * 1)), (3 + (4 * 1)), (0 + (4 * 1)))
    };
    
    //s-box
    Temp.v[1] = vaeseq_u8(Temp.v[1], CCSimdZero_u8x16());
    
    //Rcon
    Temp.v[1] = CCSimdXor_u8x16(Temp.v[1], CCCryptoAesKeyExpansionRoundConstant(Round));
    
    const CCSimd_u32x4 Zero = CCSimdZero_u32x4();
    
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[1], Key.v[0]); //w^k0, w^k1, w^k2, w^k3
    
    Key.v[0] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u32x4(Zero, CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2));
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[0], Key.v[0]); //w^k0, w^k1^k0, w^k2^k1, w^k3^k2
    
    Key.v[0] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), 0, 0, 1, 2));
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[0], Key.v[0]); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1
    
    Key.v[0] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), 0, 0, 1, 2));
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[0], Key.v[0]); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1^k0
    
    CCSimd_u32x4 Temp3 = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Temp.v[0]), 3, 3, 3, 3));
    Temp.v[1] = CCSimdXor_u8x16(Temp3, Key.v[1]); //w^k3^k2^k1^k0^k4, w^k3^k2^k1^k0^k5
    Temp3 = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u32x4(Zero, CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]), CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2));
    Temp.v[1] = CCSimdXor_u8x16(Temp3, Temp.v[1]); //w^k3^k2^k1^k0^k4, w^k3^k2^k1^k0^k5^k4
    
    return Temp;
}

static CC_FORCE_INLINE CCSimd_u8x16x2 CCCryptoAes256KeyExpandRound(CCSimd_u8x16x2 Key, size_t Round)
{
    //rot word
    CCSimd_u8x16x2 Temp = {
        Key.v[0],
        CCSimdSwizzle_u8x16(Key.v[1],
                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)),
                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)),
                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)),
                            (1 + (4 * 3)), (2 + (4 * 3)), (3 + (4 * 3)), (0 + (4 * 3)))
    };
    
    //s-box
    Temp.v[1] = vaeseq_u8(Temp.v[1], CCSimdZero_u8x16());
    
    //Rcon
    Temp.v[1] = CCSimdXor_u8x16(Temp.v[1], CCCryptoAesKeyExpansionRoundConstant(Round));
    
    const CCSimd_u32x4 Zero = CCSimdZero_u32x4();
    
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[1], Key.v[0]); //w^k0, w^k1, w^k2, w^k3
    Temp.v[1] = Key.v[1]; //k4, k5, k6, k7
    
    Key.v[0] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u32x4(Zero, CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2));
    Key.v[1] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u32x4(Zero, CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]), CC_SIMD_A0, CC_SIMD_B0, CC_SIMD_B1, CC_SIMD_B2));
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[0], Key.v[0]); //w^k0, w^k1^k0, w^k2^k1, w^k3^k2
    Temp.v[1] = CCSimdXor_u8x16(Temp.v[1], Key.v[1]); //k4, k5^k4, k6^k5, k7^k6
    
    Key.v[0] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), 0, 0, 1, 2));
    Key.v[1] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]), 0, 0, 1, 2));
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[0], Key.v[0]); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1
    Temp.v[1] = CCSimdXor_u8x16(Temp.v[1], Key.v[1]); //k4, k5^k4, k6^k5^k4, k7^k6^k5
    
    Key.v[0] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), 0, 0, 1, 2));
    Key.v[1] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]), 0, 0, 1, 2));
    Temp.v[0] = CCSimdXor_u8x16(Temp.v[0], Key.v[0]); //w^k0, w^k1^k0, w^k2^k1^k0, w^k3^k2^k1^k0
    Temp.v[1] = CCSimdXor_u8x16(Temp.v[1], Key.v[1]); //k4, k5^k4, k6^k5^k4, k7^k6^k5^k4
    
    CCSimd_u32x4 Temp3 = CCSimd_u8x16_Reinterpret_u32x4(CCSimdSwizzle_u32x4(CCSimd_u32x4_Reinterpret_u8x16(Temp.v[0]), 3, 3, 3, 3));
    Temp3 = vaeseq_u8(Temp3, CCSimdZero_u8x16()); //s-box
    Temp.v[1] = CCSimdXor_u8x16(Temp3, Temp.v[1]); //k4^w, k5^k4^w, k6^k5^k4^w, k7^k6^k5^k4^w
    
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

static CC_FORCE_INLINE void CCCryptoAes192KeyExpand(CCSimd_u8x16x2 Key, CCSimd_u8x16 ExpandedKey[13])
{
    for (size_t Loop = 0, Round = 0; Loop < 12; Loop += 3)
    {
        ExpandedKey[Loop] = Key.v[0];
        const CCSimd_u8x16 Temp = Key.v[1];
        Key = CCCryptoAes192KeyExpandRound(Key, Round++);
        
        ExpandedKey[Loop + 1] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u64x2(CCSimd_u32x4_Reinterpret_u8x16(Temp), CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), CC_SIMD_A0, CC_SIMD_B0));
        
        ExpandedKey[Loop + 2] = CCSimd_u8x16_Reinterpret_u32x4(CCSimdMerge_u64x2(CCSimd_u32x4_Reinterpret_u8x16(Key.v[0]), CCSimd_u32x4_Reinterpret_u8x16(Key.v[1]), CC_SIMD_A1, CC_SIMD_B0));
        Key = CCCryptoAes192KeyExpandRound(Key, Round++);
    }
    
    ExpandedKey[12] = Key.v[0];
}

static CC_FORCE_INLINE void CCCryptoAes256KeyExpand(CCSimd_u8x16x2 Key, CCSimd_u8x16 ExpandedKey[15])
{
    for (size_t Loop = 0, Round = 0; Loop < 13; Loop += 2)
    {
        ExpandedKey[Loop] = Key.v[0];
        ExpandedKey[Loop + 1] = Key.v[1];
        
        Key = CCCryptoAes256KeyExpandRound(Key, Round++);
    }
    
    ExpandedKey[14] = Key.v[0];
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

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes192Encrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[13])
{
    for (size_t Loop = 0; Loop < 11; Loop++)
    {
        Data = vaeseq_u8(Data, Key[Loop]);
        Data = vaesmcq_u8(Data);
    }
    
    Data = vaeseq_u8(Data, Key[11]);
    
    return CCSimdXor_u8x16(Data, Key[12]);
}

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes256Encrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[15])
{
    for (size_t Loop = 0; Loop < 13; Loop++)
    {
        Data = vaeseq_u8(Data, Key[Loop]);
        Data = vaesmcq_u8(Data);
    }
    
    Data = vaeseq_u8(Data, Key[13]);
    
    return CCSimdXor_u8x16(Data, Key[14]);
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

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes192Decrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[13])
{
    Data = vaesdq_u8(Data, Key[12]);
    
    for (size_t Loop = 0; Loop < 11; Loop++)
    {
        Data = vaesimcq_u8(Data);
        
        Data = vaesdq_u8(Data, vaesimcq_u8(Key[11 - Loop]));
    }
    
    Data = CCSimdXor_u8x16(Data, Key[0]);
    
    return Data;
}

static CC_FORCE_INLINE CCSimd_u8x16 CCCryptoAes256Decrypt(CCSimd_u8x16 Data, CCSimd_u8x16 Key[15])
{
    Data = vaesdq_u8(Data, Key[14]);
    
    for (size_t Loop = 0; Loop < 13; Loop++)
    {
        Data = vaesimcq_u8(Data);
        
        Data = vaesdq_u8(Data, vaesimcq_u8(Key[13 - Loop]));
    }
    
    Data = CCSimdXor_u8x16(Data, Key[0]);
    
    return Data;
}

static CC_FORCE_INLINE uint64_t CCCryptoKeccakRoundConstant(size_t Round, size_t LaneSize)
{
    const uint64_t RC[256] = {
        0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
        0x000000000000808B, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
        0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
        0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
        0x8000000000008002, 0x8000000000000080, 0x000000000000800A, 0x800000008000000A,
        0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
        0x8000000080008082, 0x800000008000800A, 0x8000000000000003, 0x8000000080000009,
        0x8000000000008082, 0x0000000000008009, 0x8000000000000080, 0x0000000000008083,
        0x8000000000000081, 0x0000000000000001, 0x000000000000800B, 0x8000000080008001,
        0x0000000000000080, 0x8000000000008000, 0x8000000080008001, 0x0000000000000009,
        0x800000008000808B, 0x0000000000000081, 0x8000000000000082, 0x000000008000008B,
        0x8000000080008009, 0x8000000080000000, 0x0000000080000080, 0x0000000080008003,
        0x8000000080008082, 0x8000000080008083, 0x8000000080000088, 0x0000000000008089,
        0x0000000000008009, 0x8000000000000009, 0x0000000080008008, 0x0000000080008001,
        0x800000000000008A, 0x800000000000000B, 0x0000000000000089, 0x0000000080000002,
        0x800000000000800B, 0x000000008000800B, 0x000000000000808B, 0x0000000080000088,
        0x800000000000800A, 0x0000000080000089, 0x8000000000000001, 0x8000000000008088,
        0x8000000000000081, 0x0000000000000088, 0x0000000080008080, 0x0000000000000081,
        0x800000000000000B, 0x0000000000000000, 0x0000000000000089, 0x000000008000008B,
        0x8000000080008080, 0x800000000000008B, 0x8000000000008000, 0x8000000080008088,
        0x0000000080000082, 0x000000000000000B, 0x800000000000000A, 0x0000000000008082,
        0x8000000000008003, 0x800000000000808B, 0x800000008000000B, 0x800000008000008A,
        0x0000000080000081, 0x0000000080000081, 0x0000000080000008, 0x0000000000000083,
        0x8000000080008003, 0x0000000080008088, 0x8000000080000088, 0x0000000000008000,
        0x0000000080008082, 0x0000000080008089, 0x8000000080008083, 0x8000000080000001,
        0x0000000080008002, 0x8000000080000089, 0x0000000000000082, 0x8000000080000008,
        0x8000000000000089, 0x8000000080000008, 0x8000000000000000, 0x8000000000000083,
        0x0000000080008080, 0x0000000000000008, 0x8000000080000080, 0x8000000080008080,
        0x8000000000000002, 0x800000008000808B, 0x0000000000000008, 0x8000000080000009,
        0x800000000000800B, 0x0000000080008082, 0x0000000080008000, 0x8000000000008008,
        0x0000000000008081, 0x8000000080008089, 0x0000000080008089, 0x800000008000800A,
        0x800000000000008A, 0x8000000000000082, 0x0000000080000002, 0x8000000000008082,
        0x0000000000008080, 0x800000008000000B, 0x8000000080000003, 0x000000000000000A,
        0x8000000000008001, 0x8000000080000083, 0x8000000000008083, 0x000000000000008B,
        0x000000000000800A, 0x8000000080000083, 0x800000000000800A, 0x0000000080000000,
        0x800000008000008A, 0x0000000080000008, 0x000000000000000A, 0x8000000000008088,
        0x8000000000000008, 0x0000000080000003, 0x8000000000000000, 0x800000000000000A,
        0x000000000000800B, 0x8000000080008088, 0x000000008000000B, 0x0000000080000080,
        0x000000008000808A, 0x8000000000008009, 0x0000000000000003, 0x0000000080000003,
        0x8000000000000089, 0x8000000080000081, 0x800000008000008B, 0x0000000080008003,
        0x800000008000800B, 0x8000000000008008, 0x0000000000008008, 0x8000000000008002,
        0x8000000000000009, 0x0000000080008081, 0x000000000000808A, 0x000000008000800A,
        0x0000000000000080, 0x8000000000008089, 0x800000000000808A, 0x8000000080008089,
        0x0000000080008000, 0x8000000000008081, 0x000000008000800A, 0x0000000000000009,
        0x8000000080008002, 0x000000008000000A, 0x0000000080008002, 0x8000000080000000,
        0x0000000080000009, 0x0000000000008088, 0x0000000000000002, 0x0000000080008008,
        0x0000000080008088, 0x8000000080000001, 0x000000008000808B, 0x8000000000000002,
        0x8000000080008002, 0x0000000080000083, 0x0000000000008089, 0x0000000000008080,
        0x8000000080000082, 0x8000000000000088, 0x800000008000808A, 0x000000000000808A,
        0x0000000080008083, 0x000000008000000B, 0x0000000080000009, 0x0000000000008001,
        0x0000000080000089, 0x8000000000000088, 0x8000000080008003, 0x0000000080008001,
        0x8000000000000003, 0x8000000080000080, 0x8000000080008009, 0x8000000080000089,
        0x000000000000000B, 0x8000000000000083, 0x0000000080008009, 0x0000000080000083,
        0x0000000000008000, 0x000000008000800B, 0x0000000000008002, 0x0000000000000003,
        0x000000008000008A, 0x8000000080000002, 0x0000000000008001, 0x0000000080000000,
        0x8000000080000003, 0x0000000000000083, 0x800000008000808A, 0x0000000000008003,
        0x0000000000008008, 0x800000000000808B, 0x8000000080000082, 0x8000000000000001,
        0x8000000000008001, 0x800000008000000A, 0x8000000080008008, 0x800000008000800B,
        0x8000000000008081, 0x0000000080008083, 0x0000000080000082, 0x0000000000000082,
        0x8000000080000081, 0x8000000080000002, 0x0000000000008088, 0x000000000000008B,
        0x0000000000008083, 0x8000000000000008, 0x000000008000008A, 0x800000008000008B,
        0x000000008000808A, 0x8000000000008080, 0x0000000080000088, 0x8000000000008083,
        0x0000000000000002, 0x0000000080008081, 0x0000000000008003, 0x0000000000008081,
        0x8000000080008000, 0x0000000000008002, 0x000000000000008A, 0x0000000000000001
    };
    
    return RC[Round & 0xff] & (UINT64_MAX >> (64 - LaneSize));
}

typedef struct {
    CCSimd_u64x2 lanes[3][5];
} CCCryptoKeccak1600State;

static CC_FORCE_INLINE CCCryptoKeccak1600State CCCryptoKeccak1600PermutationRound(CCCryptoKeccak1600State State, size_t Round)
{
    /*
     State:
     (0 1) (0 1) (0 1) (0 1) (0 1)
     (2 3) (2 3) (2 3) (2 3) (2 3)
     (4 _) (4 _) (4 _) (4 _) (4 _)
     */
    
    CCSimd_u64x2 C[3];
    // θ step
    // θ: C[x] = a[x, 0]
    // θ: C[x] = C[x] XOR a[x, y]
    for (size_t X = 0; X < 3; X++)
    {
        C[X] = veor3q_u64(veor3q_u64(State.lanes[X][0], State.lanes[X][1], State.lanes[X][2]), State.lanes[X][3], State.lanes[X][4]);
    }
    
    /*
     C:
     (0 1)
     (2 3)
     (4 _)
     */
    
    // θ: D[x] = C[x−1] XOR ROT(C[x + 1], 1)
    // θ: A[x, y] = a[x, y] XOR D[x]
    CCSimd_u64x2 D[3];
    
    D[0] = vrax1q_u64(CCSimdMerge_u64x2(C[2], C[0], CC_SIMD_A0, CC_SIMD_B0), CCSimdMerge_u64x2(C[0], C[1], CC_SIMD_A1, CC_SIMD_B0)); // ((4 1) (0 2))
    D[1] = vrax1q_u64(CCSimdMerge_u64x2(C[0], C[1], CC_SIMD_A1, CC_SIMD_B0), CCSimdMerge_u64x2(C[1], C[2], CC_SIMD_A1, CC_SIMD_B0)); // ((1 3) (2 4))
    D[2] = vrax1q_u64(CCSimdSwizzle_u64x2(C[1], 1, 0), C[0]); // ((3 0) (___))
    
#define ROT_OFFSET(i) (((i) * ((i) + 1)) / 2) % 64
#define RHO_MAT(x, y) (((2 * (x)) + (3 * (y))) % 5)][y
    
    CCSimd_u64x2 B[5][5];
    
    B[RHO_MAT(0, 0)] = CCSimdXor_u64x2(State.lanes[0][0], D[0]);
    B[RHO_MAT(0, 1)] = vxarq_u64(State.lanes[0][1], D[0], 64 - ROT_OFFSET(8));
    B[RHO_MAT(0, 2)] = vxarq_u64(State.lanes[0][2], D[0], 64 - ROT_OFFSET(2));
    B[RHO_MAT(0, 3)] = vxarq_u64(State.lanes[0][3], D[0], 64 - ROT_OFFSET(14));
    B[RHO_MAT(0, 4)] = vxarq_u64(State.lanes[0][4], D[0], 64 - ROT_OFFSET(20));
    B[RHO_MAT(1, 0)] = vxarq_u64(State.lanes[0][0], D[0], 64 - ROT_OFFSET(1));
    B[RHO_MAT(1, 1)] = vxarq_u64(State.lanes[0][1], D[0], 64 - ROT_OFFSET(24));
    B[RHO_MAT(1, 2)] = vxarq_u64(State.lanes[0][2], D[0], 64 - ROT_OFFSET(4));
    B[RHO_MAT(1, 3)] = vxarq_u64(State.lanes[0][3], D[0], 64 - ROT_OFFSET(9));
    B[RHO_MAT(1, 4)] = vxarq_u64(State.lanes[0][4], D[0], 64 - ROT_OFFSET(11));
    B[RHO_MAT(2, 0)] = vxarq_u64(State.lanes[1][0], D[1], 64 - ROT_OFFSET(19));
    B[RHO_MAT(2, 1)] = vxarq_u64(State.lanes[1][1], D[1], 64 - ROT_OFFSET(3));
    B[RHO_MAT(2, 2)] = vxarq_u64(State.lanes[1][2], D[1], 64 - ROT_OFFSET(18));
    B[RHO_MAT(2, 3)] = vxarq_u64(State.lanes[1][3], D[1], 64 - ROT_OFFSET(5));
    B[RHO_MAT(2, 4)] = vxarq_u64(State.lanes[1][4], D[1], 64 - ROT_OFFSET(22));
    B[RHO_MAT(3, 0)] = vxarq_u64(State.lanes[1][0], D[1], 64 - ROT_OFFSET(7));
    B[RHO_MAT(3, 1)] = vxarq_u64(State.lanes[1][1], D[1], 64 - ROT_OFFSET(10));
    B[RHO_MAT(3, 2)] = vxarq_u64(State.lanes[1][2], D[1], 64 - ROT_OFFSET(17));
    B[RHO_MAT(3, 3)] = vxarq_u64(State.lanes[1][3], D[1], 64 - ROT_OFFSET(6));
    B[RHO_MAT(3, 4)] = vxarq_u64(State.lanes[1][4], D[1], 64 - ROT_OFFSET(15));
    B[RHO_MAT(4, 0)] = vxarq_u64(State.lanes[2][0], D[2], 64 - ROT_OFFSET(13));
    B[RHO_MAT(4, 1)] = vxarq_u64(State.lanes[2][1], D[2], 64 - ROT_OFFSET(23));
    B[RHO_MAT(4, 2)] = vxarq_u64(State.lanes[2][2], D[2], 64 - ROT_OFFSET(21));
    B[RHO_MAT(4, 3)] = vxarq_u64(State.lanes[2][3], D[2], 64 - ROT_OFFSET(16));
    B[RHO_MAT(4, 4)] = vxarq_u64(State.lanes[2][4], D[2], 64 - ROT_OFFSET(12));

#undef ROT_OFFSET
#undef RHO_MAT
    
    // χ step
#define LANE(y, x) ((((10 << ((y * 3) % 5)) | (10 >> ((y * 2) % 5))) >> (4 - x)) & 1) // sampling pattern for B
    for (size_t X = 0; X < 2; X++)
    {
        for (size_t Y = 0; Y < 5; Y++)
        {
            size_t X1 = X * 2, X2 = (X * 2) + 1;
            CCSimd_u64x2 B0 = CCSimdMerge_u64x2(B[Y][X1], B[Y][X2], CC_SIMD_A0 + LANE(Y, X1), CC_SIMD_B0 + LANE(Y, X2));
            
            X1 = (X1 + 1) % 5;
            X2 = (X2 + 1) % 5;
            CCSimd_u64x2 B1 = CCSimdMerge_u64x2(B[Y][X1], B[Y][X2], CC_SIMD_A0 + LANE(Y, X1), CC_SIMD_B0 + LANE(Y, X2));
            
            X1 = (X1 + 1) % 5;
            X2 = (X2 + 1) % 5;
            CCSimd_u64x2 B2 = CCSimdMerge_u64x2(B[Y][X1], B[Y][X2], CC_SIMD_A0 + LANE(Y, X1), CC_SIMD_B0 + LANE(Y, X2));
            
            State.lanes[X][Y] = vbcaxq_u64(B0, B2, B1);
        }
    }
    
    for (size_t X = 2, Y = 0; Y < 5; Y++)
    {
        size_t X1 = X * 2;
        CCSimd_u64x2 B0 = CCSimdSwizzle_u64x2(B[Y][X1], LANE(Y, X1), 1);
        
        X1 = (X1 + 1) % 5;
        CCSimd_u64x2 B1 = CCSimdSwizzle_u64x2(B[Y][X1], LANE(Y, X1), 1);
        
        X1 = (X1 + 1) % 5;
        CCSimd_u64x2 B2 = CCSimdSwizzle_u64x2(B[Y][X1], LANE(Y, X1), 1);
        
        State.lanes[X][Y] = vbcaxq_u64(B0, B2, B1);
    }
#undef LANE
    
    // ι step
    State.lanes[0][0] = CCSimdXor_u64x2(State.lanes[0][0], CCSimdLoad_u64x2((uint64_t[2]){ CCCryptoKeccakRoundConstant(Round, 64), 0 }));
    
    return State;
}

typedef struct {
    CCSimd_u64x2 lanes[5][5];
} CCCryptoKeccak1600Parallel2State;

static CC_FORCE_INLINE CCCryptoKeccak1600Parallel2State CCCryptoKeccak1600Parallel2PermutationRound(CCCryptoKeccak1600Parallel2State State, size_t Round)
{
    CCSimd_u64x2 C[5];
    // θ step
    // θ: C[x] = a[x, 0]
    // θ: C[x] = C[x] XOR a[x, y]
    for (size_t X = 0; X < 5; X++)
    {
        C[X] = veor3q_u64(veor3q_u64(State.lanes[X][0], State.lanes[X][1], State.lanes[X][2]), State.lanes[X][3], State.lanes[X][4]);
    }
    
    // θ: D[x] = C[x−1] XOR ROT(C[x + 1], 1)
    CCSimd_u64x2 D[5];
    
    for (size_t X = 0; X < 5; X++)
    {
        D[X] = vrax1q_u64(C[((X + 5) - 1) % 5], C[(X + 1) % 5]);
    }
    
    // θ: A[x, y] = a[x, y] XOR D[x]
    // ρ and π steps
#define ROT_OFFSET(i) (((i) * ((i) + 1)) / 2) % 64
#define RHO_MAT(x, y) (((2 * (x)) + (3 * (y))) % 5)][y
    
    CCSimd_u64x2 B[5][5];
    
    B[RHO_MAT(0, 0)] = CCSimdXor_u64x2(State.lanes[0][0], D[0]);
    B[RHO_MAT(0, 1)] = vxarq_u64(State.lanes[0][1], D[0], 64 - ROT_OFFSET(8));
    B[RHO_MAT(0, 2)] = vxarq_u64(State.lanes[0][2], D[0], 64 - ROT_OFFSET(2));
    B[RHO_MAT(0, 3)] = vxarq_u64(State.lanes[0][3], D[0], 64 - ROT_OFFSET(14));
    B[RHO_MAT(0, 4)] = vxarq_u64(State.lanes[0][4], D[0], 64 - ROT_OFFSET(20));
    B[RHO_MAT(1, 0)] = vxarq_u64(State.lanes[1][0], D[1], 64 - ROT_OFFSET(1));
    B[RHO_MAT(1, 1)] = vxarq_u64(State.lanes[1][1], D[1], 64 - ROT_OFFSET(24));
    B[RHO_MAT(1, 2)] = vxarq_u64(State.lanes[1][2], D[1], 64 - ROT_OFFSET(4));
    B[RHO_MAT(1, 3)] = vxarq_u64(State.lanes[1][3], D[1], 64 - ROT_OFFSET(9));
    B[RHO_MAT(1, 4)] = vxarq_u64(State.lanes[1][4], D[1], 64 - ROT_OFFSET(11));
    B[RHO_MAT(2, 0)] = vxarq_u64(State.lanes[2][0], D[2], 64 - ROT_OFFSET(19));
    B[RHO_MAT(2, 1)] = vxarq_u64(State.lanes[2][1], D[2], 64 - ROT_OFFSET(3));
    B[RHO_MAT(2, 2)] = vxarq_u64(State.lanes[2][2], D[2], 64 - ROT_OFFSET(18));
    B[RHO_MAT(2, 3)] = vxarq_u64(State.lanes[2][3], D[2], 64 - ROT_OFFSET(5));
    B[RHO_MAT(2, 4)] = vxarq_u64(State.lanes[2][4], D[2], 64 - ROT_OFFSET(22));
    B[RHO_MAT(3, 0)] = vxarq_u64(State.lanes[3][0], D[3], 64 - ROT_OFFSET(7));
    B[RHO_MAT(3, 1)] = vxarq_u64(State.lanes[3][1], D[3], 64 - ROT_OFFSET(10));
    B[RHO_MAT(3, 2)] = vxarq_u64(State.lanes[3][2], D[3], 64 - ROT_OFFSET(17));
    B[RHO_MAT(3, 3)] = vxarq_u64(State.lanes[3][3], D[3], 64 - ROT_OFFSET(6));
    B[RHO_MAT(3, 4)] = vxarq_u64(State.lanes[3][4], D[3], 64 - ROT_OFFSET(15));
    B[RHO_MAT(4, 0)] = vxarq_u64(State.lanes[4][0], D[4], 64 - ROT_OFFSET(13));
    B[RHO_MAT(4, 1)] = vxarq_u64(State.lanes[4][1], D[4], 64 - ROT_OFFSET(23));
    B[RHO_MAT(4, 2)] = vxarq_u64(State.lanes[4][2], D[4], 64 - ROT_OFFSET(21));
    B[RHO_MAT(4, 3)] = vxarq_u64(State.lanes[4][3], D[4], 64 - ROT_OFFSET(16));
    B[RHO_MAT(4, 4)] = vxarq_u64(State.lanes[4][4], D[4], 64 - ROT_OFFSET(12));
    
#undef ROT_OFFSET
#undef RHO_MAT
    
    // χ step
    for (size_t X = 0; X < 5; X++)
    {
        for (size_t Y = 0; Y < 5; Y++)
        {
            State.lanes[X][Y] = vbcaxq_u64(B[Y][X], B[Y][(X + 2) % 5], B[Y][(X + 1) % 5]);
        }
    }
    
    // ι step
    State.lanes[0][0] = CCSimdXor_u64x2(State.lanes[0][0], CCSimdFill_u64x2(CCCryptoKeccakRoundConstant(Round, 64)));
    
    return State;
}

#endif
