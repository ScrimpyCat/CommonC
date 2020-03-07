/*
 *  Copyright (c) 2013, Stefan Johnson
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

#ifndef CommonC_Random_h
#define CommonC_Random_h

#include <CommonC/Base.h>
#include <CommonC/Platform.h>
#include <CommonC/Maths.h>
#include <CommonC/Types.h>
#include <CommonC/DataBuffer.h>
#include <CommonC/MemoryAllocation.h>
#include <CommonC/Logging.h>

#if !defined(CC_RANDOM_ARC4) && !defined(CC_RANDOM_STD) && !defined(CC_RANDOM_XORSHIFT) && !defined(CC_RANDOM_XORWOW)

#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS //or BSD
#define CC_RANDOM_ARC4 1
#else
#define CC_RANDOM_STD 1
#endif

#endif


#pragma mark Custom PRNG Implementations
#pragma mark xorshift

typedef uint32_t CCRandomState_xorshift;

/*!
 * @brief Get the next random value using a xorshift PRNG.
 * @param State The current xorshift state.
 * @return A random number.
 */
uint32_t CCRandom_xorshift(CCRandomState_xorshift *State);

/*!
 * @brief Get the maximum value the xorshift PRNG can generate.
 * @return The largest possible number.
 */
uint32_t CCRandomMax_xorshift(void);

/*!
 * @brief Seed the xorshift PRNG.
 * @param State The xorshift state.
 * @param Seed The seed value.
 */
void CCRandomSeed_xorshift(CCRandomState_xorshift *State, uint32_t Seed);

#pragma mark xorwow

typedef struct {
    uint32_t a, b, c, d;
    uint32_t counter;
} CCRandomState_xorwow;

/*!
 * @brief Get the next random value using a xorwow PRNG.
 * @param State The current xorwow state.
 * @return A random number.
 */
uint32_t CCRandom_xorwow(CCRandomState_xorwow *State);

/*!
 * @brief Get the maximum value the xorwow PRNG can generate.
 * @return The largest possible number.
 */
uint32_t CCRandomMax_xorwow(void);

/*!
 * @brief Seed the xorwow PRNG.
 * @param State The xorwow state.
 * @param Seed The seed value.
 */
void CCRandomSeed_xorwow(CCRandomState_xorwow *State, uint32_t Seed);

#pragma mark - Global PRNG

extern CCRandomState_xorshift CCRandomGlobalState_xorshift;
extern CCRandomState_xorwow CCRandomGlobalState_xorwow;

#if CC_RANDOM_XORSHIFT
#define CCRandomState CCRandomGlobalState_xorshift
#define CC_RANDOM_SEED CCRandomSeed_xorshift
#define CC_RANDOM_MAX CCRandomMax_xorshift
#define CC_RANDOM CCRandom_xorshift
#elif CC_RANDOM_XORWOW
#define CCRandomState CCRandomGlobalState_xorwow
#define CC_RANDOM_SEED CCRandomSeed_xorwow
#define CC_RANDOM_MAX CCRandomMax_xorwow
#define CC_RANDOM CCRandom_xorwow
#endif

/*!
 * @brief Get the next random value using the global PRNG.
 * @description The global PRNG implementation can be selected by defining:
 *
 *              - @b CC_RANDOM_ARC4
 *
 *              - @b CC_RANDOM_STD
 *
 *              - @b CC_RANDOM_XORSHIFT
 *
 *              - @b CC_RANDOM_XORWOW
 *
 * @return A random number.
 */
static inline uint32_t CCRandom(void);

/*!
 * @brief Get the maximum value the global PRNG can generate.
 * @description The global PRNG implementation can be selected by defining:
 *
 *              - @b CC_RANDOM_ARC4
 *
 *              - @b CC_RANDOM_STD
 *
 *              - @b CC_RANDOM_XORSHIFT
 *
 *              - @b CC_RANDOM_XORWOW
 *
 * @return The largest possible number.
 */
static inline uint32_t CCRandomMax(void);

/*!
 * @brief Seed the global PRNG.
 * @description The global PRNG implementation can be selected by defining:
 *
 *              - @b CC_RANDOM_ARC4
 *
 *              - @b CC_RANDOM_STD
 *
 *              - @b CC_RANDOM_XORSHIFT
 *
 *              - @b CC_RANDOM_XORWOW
 *
 * @param seed The seed value.
 */
static inline void CCRandomSeed(uint32_t seed);

/*!
 * @brief Get the global PRNG state in a generic data container.
 * @description The global PRNG implementation can be selected by defining:
 *
 *              - @b CC_RANDOM_ARC4
 *
 *              - @b CC_RANDOM_STD
 *
 *              - @b CC_RANDOM_XORSHIFT
 *
 *              - @b CC_RANDOM_XORWOW
 *
 * @return The current global PRNG state. This must be destroyed.
 */
static inline CC_NEW CCData CCRandomGetState(void);

/*!
 * @brief Set the global PRNG state.
 * @description The global PRNG implementation can be selected by defining:
 *
 *              - @b CC_RANDOM_ARC4
 *
 *              - @b CC_RANDOM_STD
 *
 *              - @b CC_RANDOM_XORSHIFT
 *
 *              - @b CC_RANDOM_XORWOW
 *
 * @param State The state data. This is intended to be a result retrieved from
 *        @b CCRandomGetState.
 */
static inline void CCRandomSetState(CCData State);

/*!
 * @brief Get the next random value as a double between 0.0 - 1.0.
 * @note This uses the global PRNG.
 * @return A random number between 0.0 - 1.0.
 */
static inline double CCRandomd(void);

/*!
 * @brief Get the next random value as a float between 0.0f - 1.0f.
 * @note This uses the global PRNG.
 * @return A random number between 0.0f - 1.0f.
 */
static inline float CCRandomf(void);

/*!
 * @brief Get the next random value as an integer between 0 - RAND_MAX.
 * @description This is to replicate behaviour of the standard @b rand function.
 * @note This uses the global PRNG.
 * @return A random number between 0 - RAND_MAX.
 */
static inline int CCRandomi(void);

/*!
 * @brief Get the next random value as a double between the specified range.
 * @note This uses the global PRNG.
 * @param min The minimum value that can be returned.
 * @param max The maximum value that can be returned.
 * @return A random number between defined range.
 */
static inline double CCRandomRanged(double min, double max);

/*!
 * @brief Get the next random value as a float between the specified range.
 * @note This uses the global PRNG.
 * @param min The minimum value that can be returned.
 * @param max The maximum value that can be returned.
 * @return A random number between defined range.
 */
static inline float CCRandomRangef(float min, float max);

/*!
 * @brief Get the next random value as an integer between the specified range.
 * @note This uses the global PRNG.
 * @param min The minimum value that can be returned.
 * @param max The maximum value that can be returned.
 * @return A random number between defined range.
 */
static inline int32_t CCRandomRangei(int32_t min, int32_t max);

/*!
 * @brief Get the next random value as a point in the given rect.
 * @note This uses the global PRNG.
 * @param rect The rect to select a random point from.
 * @return A random point.
 */
static inline CCVector2D CCRandomPointInRect(CCRect rect);

/*!
 * @brief Get the next random value as a point in the given ellipse.
 * @note This uses the global PRNG.
 * @param center The center of the ellipse.
 * @param radius The radius of the ellipse.
 * @return A random point.
 */
static inline CCVector2D CCRandomPointInEllipse(CCVector2D center, CCVector2D radius);

/*!
 * @brief Get the next random value as a point in the given circle.
 * @note This uses the global PRNG.
 * @param center The center of the circle.
 * @param radius The radius of the circle.
 * @return A random point.
 */
static inline CCVector2D CCRandomPointInCircle(CCVector2D center, float radius);

#pragma mark -

static inline uint32_t CCRandom(void) //0 - CCRandomMax()
{
#if CC_RANDOM_ARC4
    return arc4random(); //arc4random range: (2**32)-1
#elif defined(CCRandomState)
    return CC_RANDOM(&CCRandomState);
#else //CC_RANDOM_STD
    return rand();
#endif
}

static inline uint32_t CCRandomMax(void)
{
#if CC_RANDOM_ARC4
    return UINT32_MAX;
#elif defined(CCRandomState)
    return CC_RANDOM_MAX();
#else
    return RAND_MAX;
#endif
}

static inline void CCRandomSeed(uint32_t seed)
{
#if CC_RANDOM_ARC4
    //does not need seeding
#elif defined(CCRandomState)
    CC_RANDOM_SEED(&CCRandomState, seed);
#else
    srand(seed);
#endif
}

#undef CC_RANDOM_SEED
#undef CC_RANDOM_MAX
#undef CC_RANDOM

static inline CC_NEW CCData CCRandomGetState(void)
{
    size_t Size = 0;
    
#if defined(CCRandomState)
    Size = sizeof(CCRandomState);
#endif
    
    void *Buffer;
    CC_SAFE_Malloc(Buffer, Size,
                   CC_LOG_ERROR("Failed to get global random state due to allocation failure. Allocation size (%zu)", Size);
                   return NULL;
                   );
    
#if defined(CCRandomState)
    memcpy(Buffer, &CCRandomState, Size);
#endif
    
    return CCDataBufferCreate(CC_STD_ALLOCATOR, CCDataHintResize | CCDataHintReadWrite | CCDataBufferHintFree, Size, Buffer, NULL, NULL);
}

static inline void CCRandomSetState(CCData State)
{
#if defined(CCRandomState)
    CCDataReadBuffer(State, 0, sizeof(CCRandomState), &CCRandomState);
#endif
}

static inline double CCRandomd(void) //returns a random number between 0.0 - 1.0
{
    return (double)CCRandom() / (double)CCRandomMax();
}

static inline float CCRandomf(void) //returns a random number between 0.0f - 1.0f
{
    return (float)CCRandom() / (float)CCRandomMax();
}

static inline int CCRandomi(void) //returns a random number between 0 - RAND_MAX
{
    return CCRandom() % ((unsigned int)RAND_MAX + 1);
}

static inline double CCRandomRanged(double min, double max)
{
    return CCClampd(CCRandomd() * (max - min) + min, min, max);
}

static inline float CCRandomRangef(float min, float max)
{
    return CCClampf(CCRandomf() * (max - min) + min, min, max);
}

static inline int32_t CCRandomRangei(int32_t min, int32_t max)
{
    const int32_t r = CCRandom();
    return (r % (max - min + 1)) + (r < 0 ? max : min);
}

static inline CCVector2D CCRandomPointInRect(CCRect rect)
{
    return (CCVector2D){ rect.position.x + (CCRandomf() * rect.size.x), rect.position.y + (CCRandomf() * rect.size.y) };
}

static inline CCVector2D CCRandomPointInEllipse(CCVector2D center, CCVector2D radius)
{
    const float r = sqrtf(CCRandomf()), angle = (CC_PI * 2.0f) * CCRandomf();
    return (CCVector2D){ (cosf(angle) * r * radius.x) + center.x, (sinf(angle) * r * radius.y) + center.y };
}

static inline CCVector2D CCRandomPointInCircle(CCVector2D center, float radius)
{
    return CCRandomPointInEllipse(center, (CCVector2D){ radius, radius });
}

#endif
