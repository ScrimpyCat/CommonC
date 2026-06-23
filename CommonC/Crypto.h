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
    CCSimd_u32x4 zero;
#endif
} CCCryptoSha1Constants;

typedef CCSimd_u32x4x2 CCCryptoSha1State;

/*!
 * @brief Calculate the SHA1 hash for the provided data.
 * @param Data The data to hash.
 * @param Size The size of the data.
 * @return The SHA1 hash state.
 */
static CCCryptoSha1State CCCryptoSha1(const void *Data, size_t Size);

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
        .c3 = CCSimdFill_u32x4(0xca62c1d6),
        .zero = CCSimdZero_u32x4()
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

#endif
