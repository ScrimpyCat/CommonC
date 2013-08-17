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

/*
 Tricks from:
 http://graphics.stanford.edu/~seander/bithacks.html
 http://resnet.uoregon.edu/~gurney_j/jmpc/bitwise.html
 */

#ifndef CommonC_BitTricks_h
#define CommonC_BitTricks_h

#include <CommonC/Extensions.h>
#include <stdint.h>


uint64_t CCLowestUnsetBit(uint64_t x) CC_CONSTANT_FUNCTION; //Finds lowest unset bit (00010110 -> 00000001, 00001000 -> 00000001)
uint64_t CCLowestSetBit(uint64_t x) CC_CONSTANT_FUNCTION; //Finds lowest set bit (00010110 -> 00000010, 00001000 -> 00001000)
uint64_t CCHighestSetBit(uint64_t x) CC_CONSTANT_FUNCTION; //Finds highest set bit (00010110 -> 00010000, 00001000 -> 00001000)
uint64_t CCNextPowerOf2(uint64_t x) CC_CONSTANT_FUNCTION; //Finds the minimum power of 2 value that can hold x (00010110 -> 00100000, 00001000 -> 00001000)
uint64_t CCMaskForValue(uint64_t x) CC_CONSTANT_FUNCTION; //Creates a mask for the entire values range (00010110 -> 00011111, 00001000 -> 00001111)
uint64_t CCMaskForLowerBits2(uint64_t x) CC_CONSTANT_FUNCTION; //Masks the lower bits of a power of 2 value (00010110 -> NA, 00001000 -> 00000111)
uint64_t CCMaskForUnsetValue(uint64_t x) CC_CONSTANT_FUNCTION; //Creates a mask for the entire range of unset bits after the highest set bit (00010110 -> 11100000, 00001000 -> 11110000)
uint64_t CCCountSetBits(uint64_t x) CC_CONSTANT_FUNCTION; //Sums the number of set bits (00010110 -> 00000011, 00001000 -> 00000001)

#endif
