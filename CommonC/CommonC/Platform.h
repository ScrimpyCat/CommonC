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

#ifndef CommonC_Platform_h
#define CommonC_Platform_h

#if __APPLE__
#define CC_PLATFORM_APPLE 1

#define CC_PLATFORM_MAC_10_0      1000
#define CC_PLATFORM_MAC_10_1      1010
#define CC_PLATFORM_MAC_10_2      1020
#define CC_PLATFORM_MAC_10_3      1030
#define CC_PLATFORM_MAC_10_4      1040
#define CC_PLATFORM_MAC_10_5      1050
#define CC_PLATFORM_MAC_10_6      1060
#define CC_PLATFORM_MAC_10_7      1070
#define CC_PLATFORM_MAC_10_8      1080
#define CC_PLATFORM_MAC_10_9      1090
#define CC_PLATFORM_MAC_NA        9999

#define CC_PLATFORM_IOS_2_0     20000
#define CC_PLATFORM_IOS_2_1     20100
#define CC_PLATFORM_IOS_2_2     20200
#define CC_PLATFORM_IOS_3_0     30000
#define CC_PLATFORM_IOS_3_1     30100
#define CC_PLATFORM_IOS_3_2     30200
#define CC_PLATFORM_IOS_4_0     40000
#define CC_PLATFORM_IOS_4_1     40100
#define CC_PLATFORM_IOS_4_2     40200
#define CC_PLATFORM_IOS_4_3     40300
#define CC_PLATFORM_IOS_5_0     50000
#define CC_PLATFORM_IOS_5_1     50100
#define CC_PLATFORM_IOS_6_0     60000
#define CC_PLATFORM_IOS_6_1     60100
#define CC_PLATFORM_IOS_7_0     70000
#define CC_PLATFORM_IOS_NA      99999

#include <TargetConditionals.h>

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#define CC_PLATFORM_OS_X 1

#ifdef __MAC_OS_X_VERSION_MAX_ALLOWED
#define CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(osx, ios) (__MAC_OS_X_VERSION_MAX_ALLOWED >= (osx))
#else
#define CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(osx, ios) 0
#endif

#elif (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#define CC_PLATFORM_IOS 1

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#define CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(osx, ios) (__IPHONE_OS_VERSION_MAX_ALLOWED >= (ios))
#else
#define CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(osx, ios) 0
#endif

#endif


#elif __unix__

#define CC_PLATFORM_UNIX 1

#else
#if CC_DEBUG
#warning Unknown platform.
#endif
#endif


#if CC_PLATFORM_UNIX || CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#define CC_PLATFORM_POSIX_COMPLIANT 1
#endif


#if __clang__
#define CC_COMPILER_CLANG 1
#elif __GCC__
#define CC_COMPILER_GCC 1
#else
#if CC_DEBUG
#warning Unknown compiler.
#endif
#endif



#if __SSE__
#define CC_HARDWARE_VECTOR_SUPPORT_SSE 1
#if __SSE2__
#define CC_HARDWARE_VECTOR_SUPPORT_SSE2 1
#if __SSE3__
#define CC_HARDWARE_VECTOR_SUPPORT_SSE3 1
#if __SSSE3__
#define CC_HARDWARE_VECTOR_SUPPORT_SSSE3 1
#if __SSE4_1__
#define CC_HARDWARE_VECTOR_SUPPORT_SSE4_1 1
#if __SSE4_2__
#define CC_HARDWARE_VECTOR_SUPPORT_SSE4_2 1
#if __AVX__
#define CC_HARDWARE_VECTOR_SUPPORT_AVX 1
#endif
#endif
#endif
#endif
#endif
#endif
#endif


#if __ARM_NEON__
#define CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON 1
#endif


#endif

