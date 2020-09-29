/*
 *  Copyright (c) 2020, Stefan Johnson
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

#ifndef CommonC_Template_h
#define CommonC_Template_h

/*!
 * @define CC_TYPE
 * @brief Get the base type from a given type declaration.
 * @description Custom types will need to provide their own @b CC_TYPE_ defines if they want to be
 *              detected. Otherwise utilise the @b TYPE(x) or @b PTYPE(x) or @b FPTYPE(x) macros in
 *              your declaration.
 */
#define CC_TYPE(x, ...) CC_TYPE_0(x)

#define CC_TYPE_0(x) CC_TYPE_EXPAND_0(CC_TYPE_0_ x)
#define CC_TYPE_1(x) CC_TYPE_EXPAND_1(CC_TYPE_1_ x)
#define CC_TYPE_2(x) CC_TYPE_EXPAND_2(CC_TYPE_2_ x)
#define CC_TYPE_3(x) CC_TYPE_EXPAND_3(CC_TYPE_3_ x)
#define CC_TYPE_4(x) CC_TYPE_EXPAND_4(CC_TYPE_4_ x)
#define CC_TYPE_5(x) CC_TYPE_EXPAND_5(CC_TYPE_5_ x)
#define CC_TYPE_6(x) CC_TYPE_EXPAND_6(CC_TYPE_6_ x)
#define CC_TYPE_7(x) CC_TYPE_EXPAND_7(CC_TYPE_7_ x)
#define CC_TYPE_8(x) CC_TYPE_EXPAND_8(CC_TYPE_8_ x)
#define CC_TYPE_9(x) CC_TYPE_EXPAND_9(CC_TYPE_9_ x)

#define CC_TYPE_EXPAND_0(x) CC_TYPE_EXPAND_0_(x)
#define CC_TYPE_EXPAND_1(x) CC_TYPE_EXPAND_1_(x)
#define CC_TYPE_EXPAND_2(x) CC_TYPE_EXPAND_2_(x)
#define CC_TYPE_EXPAND_3(x) CC_TYPE_EXPAND_3_(x)
#define CC_TYPE_EXPAND_4(x) CC_TYPE_EXPAND_4_(x)
#define CC_TYPE_EXPAND_5(x) CC_TYPE_EXPAND_5_(x)
#define CC_TYPE_EXPAND_6(x) CC_TYPE_EXPAND_6_(x)
#define CC_TYPE_EXPAND_7(x) CC_TYPE_EXPAND_7_(x)
#define CC_TYPE_EXPAND_8(x) CC_TYPE_EXPAND_8_(x)
#define CC_TYPE_EXPAND_9(x) CC_TYPE_EXPAND_9_(x)
#define CC_TYPE_EXPAND_0_(x) CC_TYPE_EXPAND_0__(CC_TYPE_CONSUME_0_##x)
#define CC_TYPE_EXPAND_1_(x) CC_TYPE_EXPAND_1__(CC_TYPE_CONSUME_1_##x)
#define CC_TYPE_EXPAND_2_(x) CC_TYPE_EXPAND_2__(CC_TYPE_CONSUME_2_##x)
#define CC_TYPE_EXPAND_3_(x) CC_TYPE_EXPAND_3__(CC_TYPE_CONSUME_3_##x)
#define CC_TYPE_EXPAND_4_(x) CC_TYPE_EXPAND_4__(CC_TYPE_CONSUME_4_##x)
#define CC_TYPE_EXPAND_5_(x) CC_TYPE_EXPAND_5__(CC_TYPE_CONSUME_5_##x)
#define CC_TYPE_EXPAND_6_(x) CC_TYPE_EXPAND_6__(CC_TYPE_CONSUME_6_##x)
#define CC_TYPE_EXPAND_7_(x) CC_TYPE_EXPAND_7__(CC_TYPE_CONSUME_7_##x)
#define CC_TYPE_EXPAND_8_(x) CC_TYPE_EXPAND_8__(CC_TYPE_CONSUME_8_##x)
#define CC_TYPE_EXPAND_9_(x) CC_TYPE_EXPAND_9__(CC_TYPE_CONSUME_9_##x)
#define CC_TYPE_EXPAND_0__(x) CC_TYPE_EXPAND_0___(x)
#define CC_TYPE_EXPAND_1__(x) CC_TYPE_EXPAND_1___(x)
#define CC_TYPE_EXPAND_2__(x) CC_TYPE_EXPAND_2___(x)
#define CC_TYPE_EXPAND_3__(x) CC_TYPE_EXPAND_3___(x)
#define CC_TYPE_EXPAND_4__(x) CC_TYPE_EXPAND_4___(x)
#define CC_TYPE_EXPAND_5__(x) CC_TYPE_EXPAND_5___(x)
#define CC_TYPE_EXPAND_6__(x) CC_TYPE_EXPAND_6___(x)
#define CC_TYPE_EXPAND_7__(x) CC_TYPE_EXPAND_7___(x)
#define CC_TYPE_EXPAND_8__(x) CC_TYPE_EXPAND_8___(x)
#define CC_TYPE_EXPAND_9__(x) CC_TYPE_EXPAND_9___(x)
#define CC_TYPE_EXPAND_0___(x) CC_TYPE_EXPAND_0____(CC_TYPE_0_##x)
#define CC_TYPE_EXPAND_1___(x) CC_TYPE_EXPAND_1____(CC_TYPE_1_##x)
#define CC_TYPE_EXPAND_2___(x) CC_TYPE_EXPAND_2____(CC_TYPE_2_##x)
#define CC_TYPE_EXPAND_3___(x) CC_TYPE_EXPAND_3____(CC_TYPE_3_##x)
#define CC_TYPE_EXPAND_4___(x) CC_TYPE_EXPAND_4____(CC_TYPE_4_##x)
#define CC_TYPE_EXPAND_5___(x) CC_TYPE_EXPAND_5____(CC_TYPE_5_##x)
#define CC_TYPE_EXPAND_6___(x) CC_TYPE_EXPAND_6____(CC_TYPE_6_##x)
#define CC_TYPE_EXPAND_7___(x) CC_TYPE_EXPAND_7____(CC_TYPE_7_##x)
#define CC_TYPE_EXPAND_8___(x) CC_TYPE_EXPAND_8____(CC_TYPE_8_##x)
#define CC_TYPE_EXPAND_9___(x) CC_TYPE_EXPAND_9____(CC_TYPE_9_##x)
#define CC_TYPE_EXPAND_0____(x) CC_TYPE_EXPAND_0_____(x)
#define CC_TYPE_EXPAND_1____(x) CC_TYPE_EXPAND_1_____(x)
#define CC_TYPE_EXPAND_2____(x) CC_TYPE_EXPAND_2_____(x)
#define CC_TYPE_EXPAND_3____(x) CC_TYPE_EXPAND_3_____(x)
#define CC_TYPE_EXPAND_4____(x) CC_TYPE_EXPAND_4_____(x)
#define CC_TYPE_EXPAND_5____(x) CC_TYPE_EXPAND_5_____(x)
#define CC_TYPE_EXPAND_6____(x) CC_TYPE_EXPAND_6_____(x)
#define CC_TYPE_EXPAND_7____(x) CC_TYPE_EXPAND_7_____(x)
#define CC_TYPE_EXPAND_8____(x) CC_TYPE_EXPAND_8_____(x)
#define CC_TYPE_EXPAND_9____(x) CC_TYPE_EXPAND_9_____(x)
#define CC_TYPE_EXPAND_0_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_1_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_2_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_3_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_4_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_5_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_6_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_7_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_8_____(x, ...) x(__VA_ARGS__)
#define CC_TYPE_EXPAND_9_____(x, ...) x(__VA_ARGS__)

#define CC_TYPE_CONSUME_0_CC_TYPE_0_
#define CC_TYPE_CONSUME_1_CC_TYPE_1_
#define CC_TYPE_CONSUME_2_CC_TYPE_2_
#define CC_TYPE_CONSUME_3_CC_TYPE_3_
#define CC_TYPE_CONSUME_4_CC_TYPE_4_
#define CC_TYPE_CONSUME_5_CC_TYPE_5_
#define CC_TYPE_CONSUME_6_CC_TYPE_6_
#define CC_TYPE_CONSUME_7_CC_TYPE_7_
#define CC_TYPE_CONSUME_8_CC_TYPE_8_
#define CC_TYPE_CONSUME_9_CC_TYPE_9_

#define CC_TYPE_EXPAND_0__CC_TYPE_0_
#define CC_TYPE_EXPAND_1__CC_TYPE_1_
#define CC_TYPE_EXPAND_2__CC_TYPE_2_
#define CC_TYPE_EXPAND_3__CC_TYPE_3_
#define CC_TYPE_EXPAND_4__CC_TYPE_4_
#define CC_TYPE_EXPAND_5__CC_TYPE_5_
#define CC_TYPE_EXPAND_6__CC_TYPE_6_
#define CC_TYPE_EXPAND_7__CC_TYPE_7_
#define CC_TYPE_EXPAND_8__CC_TYPE_8_
#define CC_TYPE_EXPAND_9__CC_TYPE_9_

//consume paranthesis
#define CC_TYPE_0_(x) CC_TYPE_0_ x
#define CC_TYPE_1_(x) CC_TYPE_1_ x
#define CC_TYPE_2_(x) CC_TYPE_2_ x
#define CC_TYPE_3_(x) CC_TYPE_3_ x
#define CC_TYPE_4_(x) CC_TYPE_4_ x
#define CC_TYPE_5_(x) CC_TYPE_5_ x
#define CC_TYPE_6_(x) CC_TYPE_6_ x
#define CC_TYPE_7_(x) CC_TYPE_7_ x
#define CC_TYPE_8_(x) CC_TYPE_8_ x
#define CC_TYPE_9_(x) CC_TYPE_9_ x

#pragma mark -
#pragma mark Keywords

//const
#define CC_TYPE_0_const CC_TYPE_1,
#define CC_TYPE_1_const CC_TYPE_2,
#define CC_TYPE_2_const CC_TYPE_3,
#define CC_TYPE_3_const CC_TYPE_4,
#define CC_TYPE_4_const CC_TYPE_5,
#define CC_TYPE_5_const CC_TYPE_6,
#define CC_TYPE_6_const CC_TYPE_7,
#define CC_TYPE_7_const CC_TYPE_8,
#define CC_TYPE_8_const CC_TYPE_9,
#define CC_TYPE_9_const CC_TYPE_10,

//volatile
#define CC_TYPE_0_volatile CC_TYPE_1,
#define CC_TYPE_1_volatile CC_TYPE_2,
#define CC_TYPE_2_volatile CC_TYPE_3,
#define CC_TYPE_3_volatile CC_TYPE_4,
#define CC_TYPE_4_volatile CC_TYPE_5,
#define CC_TYPE_5_volatile CC_TYPE_6,
#define CC_TYPE_6_volatile CC_TYPE_7,
#define CC_TYPE_7_volatile CC_TYPE_8,
#define CC_TYPE_8_volatile CC_TYPE_9,
#define CC_TYPE_9_volatile CC_TYPE_10,

//restrict
#define CC_TYPE_0_restrict CC_TYPE_1,
#define CC_TYPE_1_restrict CC_TYPE_2,
#define CC_TYPE_2_restrict CC_TYPE_3,
#define CC_TYPE_3_restrict CC_TYPE_4,
#define CC_TYPE_4_restrict CC_TYPE_5,
#define CC_TYPE_5_restrict CC_TYPE_6,
#define CC_TYPE_6_restrict CC_TYPE_7,
#define CC_TYPE_7_restrict CC_TYPE_8,
#define CC_TYPE_8_restrict CC_TYPE_9,
#define CC_TYPE_9_restrict CC_TYPE_10,

//register
#define CC_TYPE_0_register CC_TYPE_1,
#define CC_TYPE_1_register CC_TYPE_2,
#define CC_TYPE_2_register CC_TYPE_3,
#define CC_TYPE_3_register CC_TYPE_4,
#define CC_TYPE_4_register CC_TYPE_5,
#define CC_TYPE_5_register CC_TYPE_6,
#define CC_TYPE_6_register CC_TYPE_7,
#define CC_TYPE_7_register CC_TYPE_8,
#define CC_TYPE_8_register CC_TYPE_9,
#define CC_TYPE_9_register CC_TYPE_10,

//static
#define CC_TYPE_0_static CC_TYPE_1,
#define CC_TYPE_1_static CC_TYPE_2,
#define CC_TYPE_2_static CC_TYPE_3,
#define CC_TYPE_3_static CC_TYPE_4,
#define CC_TYPE_4_static CC_TYPE_5,
#define CC_TYPE_5_static CC_TYPE_6,
#define CC_TYPE_6_static CC_TYPE_7,
#define CC_TYPE_7_static CC_TYPE_8,
#define CC_TYPE_8_static CC_TYPE_9,
#define CC_TYPE_9_static CC_TYPE_10,

//extern
#define CC_TYPE_0_extern CC_TYPE_1,
#define CC_TYPE_1_extern CC_TYPE_2,
#define CC_TYPE_2_extern CC_TYPE_3,
#define CC_TYPE_3_extern CC_TYPE_4,
#define CC_TYPE_4_extern CC_TYPE_5,
#define CC_TYPE_5_extern CC_TYPE_6,
#define CC_TYPE_6_extern CC_TYPE_7,
#define CC_TYPE_7_extern CC_TYPE_8,
#define CC_TYPE_8_extern CC_TYPE_9,
#define CC_TYPE_9_extern CC_TYPE_10,

//inline
#define CC_TYPE_0_inline CC_TYPE_1,
#define CC_TYPE_1_inline CC_TYPE_2,
#define CC_TYPE_2_inline CC_TYPE_3,
#define CC_TYPE_3_inline CC_TYPE_4,
#define CC_TYPE_4_inline CC_TYPE_5,
#define CC_TYPE_5_inline CC_TYPE_6,
#define CC_TYPE_6_inline CC_TYPE_7,
#define CC_TYPE_7_inline CC_TYPE_8,
#define CC_TYPE_8_inline CC_TYPE_9,
#define CC_TYPE_9_inline CC_TYPE_10,

//_Atomic
#define CC_TYPE_0__Atomic CC_TYPE_1,
#define CC_TYPE_1__Atomic CC_TYPE_2,
#define CC_TYPE_2__Atomic CC_TYPE_3,
#define CC_TYPE_3__Atomic CC_TYPE_4,
#define CC_TYPE_4__Atomic CC_TYPE_5,
#define CC_TYPE_5__Atomic CC_TYPE_6,
#define CC_TYPE_6__Atomic CC_TYPE_7,
#define CC_TYPE_7__Atomic CC_TYPE_8,
#define CC_TYPE_8__Atomic CC_TYPE_9,
#define CC_TYPE_9__Atomic CC_TYPE_10,

//_Alignas
#define CC_TYPE_0__Alignas(x) CC_TYPE_1,
#define CC_TYPE_1__Alignas(x) CC_TYPE_2,
#define CC_TYPE_2__Alignas(x) CC_TYPE_3,
#define CC_TYPE_3__Alignas(x) CC_TYPE_4,
#define CC_TYPE_4__Alignas(x) CC_TYPE_5,
#define CC_TYPE_5__Alignas(x) CC_TYPE_6,
#define CC_TYPE_6__Alignas(x) CC_TYPE_7,
#define CC_TYPE_7__Alignas(x) CC_TYPE_8,
#define CC_TYPE_8__Alignas(x) CC_TYPE_9,
#define CC_TYPE_9__Alignas(x) CC_TYPE_10,

#pragma mark -
#pragma mark Types

//Generic Type
#define CC_TYPE_TYPE(x, ...) TYPE(x)
#define CC_TYPE_0_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_1_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_2_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_3_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_4_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_5_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_6_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_7_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_8_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,
#define CC_TYPE_9_TYPE(...) CC_TYPE_TYPE, __VA_ARGS__,

//Pointer type
#define CC_TYPE_PTYPE(x, ...) PTYPE(x)
#define CC_TYPE_0_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_1_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_2_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_3_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_4_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_5_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_6_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_7_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_8_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,
#define CC_TYPE_9_PTYPE(...) CC_TYPE_PTYPE, __VA_ARGS__,

//Function pointer type
#define CC_TYPE_FPTYPE(x, ...) FPTYPE(x)
#define CC_TYPE_0_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_1_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_2_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_3_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_4_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_5_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_6_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_7_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_8_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,
#define CC_TYPE_9_FPTYPE(...) CC_TYPE_FPTYPE, __VA_ARGS__,

//_Bool
#define CC_TYPE__Bool(...) _Bool
#define CC_TYPE_0__Bool CC_TYPE__Bool,
#define CC_TYPE_1__Bool CC_TYPE__Bool,
#define CC_TYPE_2__Bool CC_TYPE__Bool,
#define CC_TYPE_3__Bool CC_TYPE__Bool,
#define CC_TYPE_4__Bool CC_TYPE__Bool,
#define CC_TYPE_5__Bool CC_TYPE__Bool,
#define CC_TYPE_6__Bool CC_TYPE__Bool,
#define CC_TYPE_7__Bool CC_TYPE__Bool,
#define CC_TYPE_8__Bool CC_TYPE__Bool,
#define CC_TYPE_9__Bool CC_TYPE__Bool,

//bool
#define CC_TYPE_bool(...) bool
#define CC_TYPE_0_bool CC_TYPE_bool,
#define CC_TYPE_1_bool CC_TYPE_bool,
#define CC_TYPE_2_bool CC_TYPE_bool,
#define CC_TYPE_3_bool CC_TYPE_bool,
#define CC_TYPE_4_bool CC_TYPE_bool,
#define CC_TYPE_5_bool CC_TYPE_bool,
#define CC_TYPE_6_bool CC_TYPE_bool,
#define CC_TYPE_7_bool CC_TYPE_bool,
#define CC_TYPE_8_bool CC_TYPE_bool,
#define CC_TYPE_9_bool CC_TYPE_bool,

//char
#define CC_TYPE_char(...) char
#define CC_TYPE_0_char CC_TYPE_char,
#define CC_TYPE_1_char CC_TYPE_char,
#define CC_TYPE_2_char CC_TYPE_char,
#define CC_TYPE_3_char CC_TYPE_char,
#define CC_TYPE_4_char CC_TYPE_char,
#define CC_TYPE_5_char CC_TYPE_char,
#define CC_TYPE_6_char CC_TYPE_char,
#define CC_TYPE_7_char CC_TYPE_char,
#define CC_TYPE_8_char CC_TYPE_char,
#define CC_TYPE_9_char CC_TYPE_char,

//short
#define CC_TYPE_short(...) short
#define CC_TYPE_0_short CC_TYPE_short,
#define CC_TYPE_1_short CC_TYPE_short,
#define CC_TYPE_2_short CC_TYPE_short,
#define CC_TYPE_3_short CC_TYPE_short,
#define CC_TYPE_4_short CC_TYPE_short,
#define CC_TYPE_5_short CC_TYPE_short,
#define CC_TYPE_6_short CC_TYPE_short,
#define CC_TYPE_7_short CC_TYPE_short,
#define CC_TYPE_8_short CC_TYPE_short,
#define CC_TYPE_9_short CC_TYPE_short,

//int
#define CC_TYPE_int(...) int
#define CC_TYPE_0_int CC_TYPE_int,
#define CC_TYPE_1_int CC_TYPE_int,
#define CC_TYPE_2_int CC_TYPE_int,
#define CC_TYPE_3_int CC_TYPE_int,
#define CC_TYPE_4_int CC_TYPE_int,
#define CC_TYPE_5_int CC_TYPE_int,
#define CC_TYPE_6_int CC_TYPE_int,
#define CC_TYPE_7_int CC_TYPE_int,
#define CC_TYPE_8_int CC_TYPE_int,
#define CC_TYPE_9_int CC_TYPE_int,

//long
#define CC_TYPE_long(...) long
#define CC_TYPE_0_long CC_TYPE_long,
#define CC_TYPE_1_long CC_TYPE_long,
#define CC_TYPE_2_long CC_TYPE_long,
#define CC_TYPE_3_long CC_TYPE_long,
#define CC_TYPE_4_long CC_TYPE_long,
#define CC_TYPE_5_long CC_TYPE_long,
#define CC_TYPE_6_long CC_TYPE_long,
#define CC_TYPE_7_long CC_TYPE_long,
#define CC_TYPE_8_long CC_TYPE_long,
#define CC_TYPE_9_long CC_TYPE_long,

//float
#define CC_TYPE_float(...) float
#define CC_TYPE_0_float CC_TYPE_float,
#define CC_TYPE_1_float CC_TYPE_float,
#define CC_TYPE_2_float CC_TYPE_float,
#define CC_TYPE_3_float CC_TYPE_float,
#define CC_TYPE_4_float CC_TYPE_float,
#define CC_TYPE_5_float CC_TYPE_float,
#define CC_TYPE_6_float CC_TYPE_float,
#define CC_TYPE_7_float CC_TYPE_float,
#define CC_TYPE_8_float CC_TYPE_float,
#define CC_TYPE_9_float CC_TYPE_float,

//double
#define CC_TYPE_double(...) double
#define CC_TYPE_0_double CC_TYPE_double,
#define CC_TYPE_1_double CC_TYPE_double,
#define CC_TYPE_2_double CC_TYPE_double,
#define CC_TYPE_3_double CC_TYPE_double,
#define CC_TYPE_4_double CC_TYPE_double,
#define CC_TYPE_5_double CC_TYPE_double,
#define CC_TYPE_6_double CC_TYPE_double,
#define CC_TYPE_7_double CC_TYPE_double,
#define CC_TYPE_8_double CC_TYPE_double,
#define CC_TYPE_9_double CC_TYPE_double,

//int8_t
#define CC_TYPE_int8_t(...) int8_t
#define CC_TYPE_0_int8_t CC_TYPE_int8_t,
#define CC_TYPE_1_int8_t CC_TYPE_int8_t,
#define CC_TYPE_2_int8_t CC_TYPE_int8_t,
#define CC_TYPE_3_int8_t CC_TYPE_int8_t,
#define CC_TYPE_4_int8_t CC_TYPE_int8_t,
#define CC_TYPE_5_int8_t CC_TYPE_int8_t,
#define CC_TYPE_6_int8_t CC_TYPE_int8_t,
#define CC_TYPE_7_int8_t CC_TYPE_int8_t,
#define CC_TYPE_8_int8_t CC_TYPE_int8_t,
#define CC_TYPE_9_int8_t CC_TYPE_int8_t,

//int16_t
#define CC_TYPE_int16_t(...) int16_t
#define CC_TYPE_0_int16_t CC_TYPE_int16_t,
#define CC_TYPE_1_int16_t CC_TYPE_int16_t,
#define CC_TYPE_2_int16_t CC_TYPE_int16_t,
#define CC_TYPE_3_int16_t CC_TYPE_int16_t,
#define CC_TYPE_4_int16_t CC_TYPE_int16_t,
#define CC_TYPE_5_int16_t CC_TYPE_int16_t,
#define CC_TYPE_6_int16_t CC_TYPE_int16_t,
#define CC_TYPE_7_int16_t CC_TYPE_int16_t,
#define CC_TYPE_8_int16_t CC_TYPE_int16_t,
#define CC_TYPE_9_int16_t CC_TYPE_int16_t,

//int32_t
#define CC_TYPE_int32_t(...) int32_t
#define CC_TYPE_0_int32_t CC_TYPE_int32_t,
#define CC_TYPE_1_int32_t CC_TYPE_int32_t,
#define CC_TYPE_2_int32_t CC_TYPE_int32_t,
#define CC_TYPE_3_int32_t CC_TYPE_int32_t,
#define CC_TYPE_4_int32_t CC_TYPE_int32_t,
#define CC_TYPE_5_int32_t CC_TYPE_int32_t,
#define CC_TYPE_6_int32_t CC_TYPE_int32_t,
#define CC_TYPE_7_int32_t CC_TYPE_int32_t,
#define CC_TYPE_8_int32_t CC_TYPE_int32_t,
#define CC_TYPE_9_int32_t CC_TYPE_int32_t,

//int64_t
#define CC_TYPE_int64_t(...) int64_t
#define CC_TYPE_0_int64_t CC_TYPE_int64_t,
#define CC_TYPE_1_int64_t CC_TYPE_int64_t,
#define CC_TYPE_2_int64_t CC_TYPE_int64_t,
#define CC_TYPE_3_int64_t CC_TYPE_int64_t,
#define CC_TYPE_4_int64_t CC_TYPE_int64_t,
#define CC_TYPE_5_int64_t CC_TYPE_int64_t,
#define CC_TYPE_6_int64_t CC_TYPE_int64_t,
#define CC_TYPE_7_int64_t CC_TYPE_int64_t,
#define CC_TYPE_8_int64_t CC_TYPE_int64_t,
#define CC_TYPE_9_int64_t CC_TYPE_int64_t,

//uint8_t
#define CC_TYPE_uint8_t(...) uint8_t
#define CC_TYPE_0_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_1_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_2_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_3_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_4_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_5_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_6_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_7_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_8_uint8_t CC_TYPE_uint8_t,
#define CC_TYPE_9_uint8_t CC_TYPE_uint8_t,

//uint16_t
#define CC_TYPE_uint16_t(...) uint16_t
#define CC_TYPE_0_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_1_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_2_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_3_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_4_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_5_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_6_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_7_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_8_uint16_t CC_TYPE_uint16_t,
#define CC_TYPE_9_uint16_t CC_TYPE_uint16_t,

//uint32_t
#define CC_TYPE_uint32_t(...) uint32_t
#define CC_TYPE_0_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_1_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_2_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_3_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_4_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_5_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_6_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_7_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_8_uint32_t CC_TYPE_uint32_t,
#define CC_TYPE_9_uint32_t CC_TYPE_uint32_t,

//uint64_t
#define CC_TYPE_uint64_t(...) uint64_t
#define CC_TYPE_0_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_1_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_2_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_3_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_4_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_5_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_6_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_7_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_8_uint64_t CC_TYPE_uint64_t,
#define CC_TYPE_9_uint64_t CC_TYPE_uint64_t,

//intmax_t
#define CC_TYPE_intmax_t(...) intmax_t
#define CC_TYPE_0_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_1_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_2_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_3_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_4_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_5_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_6_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_7_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_8_intmax_t CC_TYPE_intmax_t,
#define CC_TYPE_9_intmax_t CC_TYPE_intmax_t,

//uintmax_t
#define CC_TYPE_uintmax_t(...) uintmax_t
#define CC_TYPE_0_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_1_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_2_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_3_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_4_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_5_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_6_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_7_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_8_uintmax_t CC_TYPE_uintmax_t,
#define CC_TYPE_9_uintmax_t CC_TYPE_uintmax_t,

//intptr_t
#define CC_TYPE_intptr_t(...) intptr_t
#define CC_TYPE_0_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_1_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_2_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_3_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_4_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_5_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_6_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_7_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_8_intptr_t CC_TYPE_intptr_t,
#define CC_TYPE_9_intptr_t CC_TYPE_intptr_t,

//uintptr_t
#define CC_TYPE_uintptr_t(...) uintptr_t
#define CC_TYPE_0_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_1_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_2_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_3_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_4_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_5_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_6_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_7_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_8_uintptr_t CC_TYPE_uintptr_t,
#define CC_TYPE_9_uintptr_t CC_TYPE_uintptr_t,

//ptrdiff_t
#define CC_TYPE_ptrdiff_t(...) ptrdiff_t
#define CC_TYPE_0_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_1_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_2_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_3_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_4_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_5_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_6_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_7_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_8_ptrdiff_t CC_TYPE_ptrdiff_t,
#define CC_TYPE_9_ptrdiff_t CC_TYPE_ptrdiff_t,

//size_t
#define CC_TYPE_size_t(...) size_t
#define CC_TYPE_0_size_t CC_TYPE_size_t,
#define CC_TYPE_1_size_t CC_TYPE_size_t,
#define CC_TYPE_2_size_t CC_TYPE_size_t,
#define CC_TYPE_3_size_t CC_TYPE_size_t,
#define CC_TYPE_4_size_t CC_TYPE_size_t,
#define CC_TYPE_5_size_t CC_TYPE_size_t,
#define CC_TYPE_6_size_t CC_TYPE_size_t,
#define CC_TYPE_7_size_t CC_TYPE_size_t,
#define CC_TYPE_8_size_t CC_TYPE_size_t,
#define CC_TYPE_9_size_t CC_TYPE_size_t,

#endif
