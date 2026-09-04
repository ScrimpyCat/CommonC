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

#ifndef CommonC_Order_h
#define CommonC_Order_h

#include <CommonC/Platform.h>
#include <CommonC/Hacks.h>

#define CC_BYTE(x, i) (((x) >> ((i) * 8)) & 0xff)

#define CC_SHIFT_BYTE(x, n, i) CC_BYTE(x, i) << (((n) * 8) - (((i) * 8) + 8))

#define CC_SWAP(x, n) CC_SOFT_JOIN(|, CC_REPEAT(0, n, CC_SHIFT_BYTE, x, n))

#if CC_HARDWARE_ENDIAN_BIG
#define CC_BIG(x, n) (x)
#define CC_LITTLE(x, n) CC_SWAP(x, n)
#elif CC_HARDWARE_ENDIAN_LITTLE
#define CC_BIG(x, n) CC_SWAP(x, n)
#define CC_LITTLE(x, n) (x)
#else
#warning Unknown endianness
#endif

#define CC_BIG_8(x, ...)  CC_BIG(x, 1)
#define CC_BIG_16(x, ...) CC_BIG(x, 2)
#define CC_BIG_32(x, ...) CC_BIG(x, 4)
#define CC_BIG_64(x, ...) CC_BIG(x, 8)

#define CC_LITTLE_8(x, ...)  CC_LITTLE(x, 1)
#define CC_LITTLE_16(x, ...) CC_LITTLE(x, 2)
#define CC_LITTLE_32(x, ...) CC_LITTLE(x, 4)
#define CC_LITTLE_64(x, ...) CC_LITTLE(x, 8)

#endif
