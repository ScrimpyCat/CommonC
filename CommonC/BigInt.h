/*
 *  Copyright (c) 2019, Stefan Johnson
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

#ifndef CommonC_BigInt_h
#define CommonC_BigInt_h

#include <CommonC/Base.h>
#include <CommonC/Platform.h>
#include <CommonC/Generics.h>
#include <CommonC/Maths.h>
#include <CommonC/CCString.h>

/*!
 * @brief The big integer.
 * @description Allows @b CCRetain.
 */
typedef struct CCBigIntInfo *CCBigInt;


#pragma mark - Creation/Destruction
/*!
 * @brief Create a big integer.
 * @param Allocator The allocator to be used for the allocation.
 * @return A big integer set to 0, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCBigInt CCBigIntCreate(CCAllocatorType Allocator);

/*!
 * @brief Destroy a big integer.
 * @param Integer The big integer to be destroyed.
 */
void CCBigIntDestroy(CCBigInt CC_DESTROY(Integer));

#pragma mark - Getter/Setter

/*!
 * @define CCBigIntSet
 * @abstract Generic macro to set the big integer to the given value.
 * @param Integer The big integer to be set.
 * @param Value The value to set the big integer to. The following types are allowed as inputs:
 *
 *        @b CCBigInt - to set the integer to the value represented by another big integer.
 *
 *        @b CCString - a hexadecimal formatted string.
 *
 *        Otherwise will default to an @b int64_t.
 */
#define CCBigIntSet(integer, value) CC_GENERIC_EVALUATE(value, \
CCBigInt: CCBigIntSetBigInt, \
CCString: CCBigIntSetString, \
default: CCBigIntSetInt)(integer, value)

void CCBigIntSetBigInt(CCBigInt Integer, CCBigInt Value);
void CCBigIntSetInt(CCBigInt Integer, int64_t Value);
void CCBigIntSetString(CCBigInt Integer, CCString Value);

#pragma mark - Operations

#endif
