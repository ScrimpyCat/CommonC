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

#include <CommonC/Base.h>
#include <CommonC/Hacks.h>

#pragma mark Mangling

#define CC_MANGLE_TYPE(x, ...) CC_MANGLE_TYPE_0(x)

#define CC_MANGLE_TYPE_0(x, ...) CC_MANGLE_TYPE_0_(CC_TYPE_0(x))
#define CC_MANGLE_TYPE_1(x, ...) CC_MANGLE_TYPE_1_(CC_TYPE_1(x))
#define CC_MANGLE_TYPE_2(x, ...) CC_MANGLE_TYPE_2_(CC_TYPE_2(x))
#define CC_MANGLE_TYPE_3(x, ...) CC_MANGLE_TYPE_3_(CC_TYPE_3(x))
#define CC_MANGLE_TYPE_4(x, ...) CC_MANGLE_TYPE_4_(CC_TYPE_4(x))
#define CC_MANGLE_TYPE_5(x, ...) CC_MANGLE_TYPE_5_(CC_TYPE_5(x))
#define CC_MANGLE_TYPE_6(x, ...) CC_MANGLE_TYPE_6_(CC_TYPE_6(x))
#define CC_MANGLE_TYPE_7(x, ...) CC_MANGLE_TYPE_7_(CC_TYPE_7(x))
#define CC_MANGLE_TYPE_8(x, ...) CC_MANGLE_TYPE_8_(CC_TYPE_8(x))
#define CC_MANGLE_TYPE_9(x, ...) CC_MANGLE_TYPE_9_(CC_TYPE_9(x))
#define CC_MANGLE_TYPE_0_(x) CC_MANGLE_TYPE_0__(x)
#define CC_MANGLE_TYPE_1_(x) CC_MANGLE_TYPE_1__(x)
#define CC_MANGLE_TYPE_2_(x) CC_MANGLE_TYPE_2__(x)
#define CC_MANGLE_TYPE_3_(x) CC_MANGLE_TYPE_3__(x)
#define CC_MANGLE_TYPE_4_(x) CC_MANGLE_TYPE_4__(x)
#define CC_MANGLE_TYPE_5_(x) CC_MANGLE_TYPE_5__(x)
#define CC_MANGLE_TYPE_6_(x) CC_MANGLE_TYPE_6__(x)
#define CC_MANGLE_TYPE_7_(x) CC_MANGLE_TYPE_7__(x)
#define CC_MANGLE_TYPE_8_(x) CC_MANGLE_TYPE_8__(x)
#define CC_MANGLE_TYPE_9_(x) CC_MANGLE_TYPE_9__(x)
#define CC_MANGLE_TYPE_0__(x, ...) CC_MANGLE_TYPE_0___(CC_MANGLE_TYPE_0_##x)
#define CC_MANGLE_TYPE_1__(x, ...) CC_MANGLE_TYPE_1___(CC_MANGLE_TYPE_1_##x)
#define CC_MANGLE_TYPE_2__(x, ...) CC_MANGLE_TYPE_2___(CC_MANGLE_TYPE_2_##x)
#define CC_MANGLE_TYPE_3__(x, ...) CC_MANGLE_TYPE_3___(CC_MANGLE_TYPE_3_##x)
#define CC_MANGLE_TYPE_4__(x, ...) CC_MANGLE_TYPE_4___(CC_MANGLE_TYPE_4_##x)
#define CC_MANGLE_TYPE_5__(x, ...) CC_MANGLE_TYPE_5___(CC_MANGLE_TYPE_5_##x)
#define CC_MANGLE_TYPE_6__(x, ...) CC_MANGLE_TYPE_6___(CC_MANGLE_TYPE_6_##x)
#define CC_MANGLE_TYPE_7__(x, ...) CC_MANGLE_TYPE_7___(CC_MANGLE_TYPE_7_##x)
#define CC_MANGLE_TYPE_8__(x, ...) CC_MANGLE_TYPE_8___(CC_MANGLE_TYPE_8_##x)
#define CC_MANGLE_TYPE_9__(x, ...) CC_MANGLE_TYPE_9___(CC_MANGLE_TYPE_9_##x)
#define CC_MANGLE_TYPE_0___(x) x
#define CC_MANGLE_TYPE_1___(x) x
#define CC_MANGLE_TYPE_2___(x) x
#define CC_MANGLE_TYPE_3___(x) x
#define CC_MANGLE_TYPE_4___(x) x
#define CC_MANGLE_TYPE_5___(x) x
#define CC_MANGLE_TYPE_6___(x) x
#define CC_MANGLE_TYPE_7___(x) x
#define CC_MANGLE_TYPE_8___(x) x
#define CC_MANGLE_TYPE_9___(x) x

#define CC_MANGLE_TYPE_0_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_1_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_2_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_3_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_4_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_5_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_6_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_7_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_8_TYPE(...) CC_CAT(__VA_ARGS__)
#define CC_MANGLE_TYPE_9_TYPE(...) CC_CAT(__VA_ARGS__)

#define CC_MANGLE_TYPE_0_PTYPE(x, ...) CC_MANGLE_TYPE_0_PTYPE_(CC_MANGLE_TYPE_1(x))
#define CC_MANGLE_TYPE_1_PTYPE(x, ...) CC_MANGLE_TYPE_1_PTYPE_(CC_MANGLE_TYPE_2(x))
#define CC_MANGLE_TYPE_2_PTYPE(x, ...) CC_MANGLE_TYPE_2_PTYPE_(CC_MANGLE_TYPE_3(x))
#define CC_MANGLE_TYPE_3_PTYPE(x, ...) CC_MANGLE_TYPE_3_PTYPE_(CC_MANGLE_TYPE_4(x))
#define CC_MANGLE_TYPE_4_PTYPE(x, ...) CC_MANGLE_TYPE_4_PTYPE_(CC_MANGLE_TYPE_5(x))
#define CC_MANGLE_TYPE_5_PTYPE(x, ...) CC_MANGLE_TYPE_5_PTYPE_(CC_MANGLE_TYPE_6(x))
#define CC_MANGLE_TYPE_6_PTYPE(x, ...) CC_MANGLE_TYPE_6_PTYPE_(CC_MANGLE_TYPE_7(x))
#define CC_MANGLE_TYPE_7_PTYPE(x, ...) CC_MANGLE_TYPE_7_PTYPE_(CC_MANGLE_TYPE_8(x))
#define CC_MANGLE_TYPE_8_PTYPE(x, ...) CC_MANGLE_TYPE_8_PTYPE_(CC_MANGLE_TYPE_9(x))
#define CC_MANGLE_TYPE_9_PTYPE(x, ...) CC_MANGLE_TYPE_9_PTYPE_(CC_MANGLE_TYPE_10(x))
#define CC_MANGLE_TYPE_0_PTYPE_(x) CC_MANGLE_TYPE_0_PTYPE__(x)
#define CC_MANGLE_TYPE_1_PTYPE_(x) CC_MANGLE_TYPE_1_PTYPE__(x)
#define CC_MANGLE_TYPE_2_PTYPE_(x) CC_MANGLE_TYPE_2_PTYPE__(x)
#define CC_MANGLE_TYPE_3_PTYPE_(x) CC_MANGLE_TYPE_3_PTYPE__(x)
#define CC_MANGLE_TYPE_4_PTYPE_(x) CC_MANGLE_TYPE_4_PTYPE__(x)
#define CC_MANGLE_TYPE_5_PTYPE_(x) CC_MANGLE_TYPE_5_PTYPE__(x)
#define CC_MANGLE_TYPE_6_PTYPE_(x) CC_MANGLE_TYPE_6_PTYPE__(x)
#define CC_MANGLE_TYPE_7_PTYPE_(x) CC_MANGLE_TYPE_7_PTYPE__(x)
#define CC_MANGLE_TYPE_8_PTYPE_(x) CC_MANGLE_TYPE_8_PTYPE__(x)
#define CC_MANGLE_TYPE_9_PTYPE_(x) CC_MANGLE_TYPE_9_PTYPE__(x)
#define CC_MANGLE_TYPE_0_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_1_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_2_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_3_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_4_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_5_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_6_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_7_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_8_PTYPE__(x) p##x
#define CC_MANGLE_TYPE_9_PTYPE__(x) p##x

#define CC_MANGLE_TYPE_0_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_0(CC_PRESERVE_TYPE_0(x))
#define CC_MANGLE_TYPE_1_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_1(CC_PRESERVE_TYPE_1(x))
#define CC_MANGLE_TYPE_2_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_2(CC_PRESERVE_TYPE_2(x))
#define CC_MANGLE_TYPE_3_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_3(CC_PRESERVE_TYPE_3(x))
#define CC_MANGLE_TYPE_4_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_4(CC_PRESERVE_TYPE_4(x))
#define CC_MANGLE_TYPE_5_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_5(CC_PRESERVE_TYPE_5(x))
#define CC_MANGLE_TYPE_6_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_6(CC_PRESERVE_TYPE_6(x))
#define CC_MANGLE_TYPE_7_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_7(CC_PRESERVE_TYPE_7(x))
#define CC_MANGLE_TYPE_8_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_8(CC_PRESERVE_TYPE_8(x))
#define CC_MANGLE_TYPE_9_FPTYPE(x, ...) CC_MANGLE_FPTYPE_EXPAND_9(CC_PRESERVE_TYPE_9(x))
#define CC_MANGLE_FPTYPE_EXPAND_0(...) CC_MANGLE_FPTYPE_EXPAND_0_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_1(...) CC_MANGLE_FPTYPE_EXPAND_1_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_2(...) CC_MANGLE_FPTYPE_EXPAND_2_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_3(...) CC_MANGLE_FPTYPE_EXPAND_3_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_4(...) CC_MANGLE_FPTYPE_EXPAND_4_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_5(...) CC_MANGLE_FPTYPE_EXPAND_5_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_6(...) CC_MANGLE_FPTYPE_EXPAND_6_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_7(...) CC_MANGLE_FPTYPE_EXPAND_7_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_8(...) CC_MANGLE_FPTYPE_EXPAND_8_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_9(...) CC_MANGLE_FPTYPE_EXPAND_9_(__VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_0_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_0__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_1_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_1__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_2_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_2__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_3_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_3__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_4_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_4__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_5_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_5__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_6_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_6__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_7_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_7__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_8_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_8__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_9_(r, x, ...) CC_MANGLE_FPTYPE_EXPAND_9__(r, CC_MANGLE_FPTYPE_CONSUME x)
#define CC_MANGLE_FPTYPE_EXPAND_0__(r, ...) CC_MANGLE_FPTYPE_EXPAND_0___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_1__(r, ...) CC_MANGLE_FPTYPE_EXPAND_1___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_2__(r, ...) CC_MANGLE_FPTYPE_EXPAND_2___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_3__(r, ...) CC_MANGLE_FPTYPE_EXPAND_3___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_4__(r, ...) CC_MANGLE_FPTYPE_EXPAND_4___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_5__(r, ...) CC_MANGLE_FPTYPE_EXPAND_5___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_6__(r, ...) CC_MANGLE_FPTYPE_EXPAND_6___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_7__(r, ...) CC_MANGLE_FPTYPE_EXPAND_7___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_8__(r, ...) CC_MANGLE_FPTYPE_EXPAND_8___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_9__(r, ...) CC_MANGLE_FPTYPE_EXPAND_9___(r, __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_0___(r, ...) CC_MANGLE_FPTYPE_EXPAND_0____(CC_MANGLE_TYPE_1(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_0 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_1___(r, ...) CC_MANGLE_FPTYPE_EXPAND_1____(CC_MANGLE_TYPE_2(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_1 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_2___(r, ...) CC_MANGLE_FPTYPE_EXPAND_2____(CC_MANGLE_TYPE_3(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_2 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_3___(r, ...) CC_MANGLE_FPTYPE_EXPAND_3____(CC_MANGLE_TYPE_4(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_3 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_4___(r, ...) CC_MANGLE_FPTYPE_EXPAND_4____(CC_MANGLE_TYPE_5(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_4 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_5___(r, ...) CC_MANGLE_FPTYPE_EXPAND_5____(CC_MANGLE_TYPE_6(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_5 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_6___(r, ...) CC_MANGLE_FPTYPE_EXPAND_6____(CC_MANGLE_TYPE_7(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_6 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_7___(r, ...) CC_MANGLE_FPTYPE_EXPAND_7____(CC_MANGLE_TYPE_8(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_7 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_8___(r, ...) CC_MANGLE_FPTYPE_EXPAND_8____(CC_MANGLE_TYPE_9(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_8 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_9___(r, ...) CC_MANGLE_FPTYPE_EXPAND_9____(CC_MANGLE_TYPE_10(r), CC_VA_ARG_COUNT __VA_ARGS__, CC_MANGLE_TYPE_LIST_9 __VA_ARGS__)
#define CC_MANGLE_FPTYPE_EXPAND_0____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_0_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_1____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_1_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_2____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_2_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_3____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_3_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_4____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_4_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_5____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_5_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_6____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_6_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_7____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_7_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_8____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_8_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_9____(r, n, t) CC_MANGLE_FPTYPE_EXPAND_9_____(r, n, _, t)
#define CC_MANGLE_FPTYPE_EXPAND_0_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_1_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_2_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_3_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_4_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_5_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_6_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_7_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_8_____(r, n, s, t) fp##n##r##s##t
#define CC_MANGLE_FPTYPE_EXPAND_9_____(r, n, s, t) fp##n##r##s##t

#define CC_MANGLE_FPTYPE_CONSUME(x, ...) __VA_ARGS__

#define CC_MANGLE_TYPE_LIST_0(...) CC_JOIN(_, CC_RECURSIVE_0_MAP(CC_MANGLE_TYPE_1, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_1(...) CC_JOIN(_, CC_RECURSIVE_1_MAP(CC_MANGLE_TYPE_2, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_2(...) CC_JOIN(_, CC_RECURSIVE_2_MAP(CC_MANGLE_TYPE_3, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_3(...) CC_JOIN(_, CC_RECURSIVE_3_MAP(CC_MANGLE_TYPE_4, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_4(...) CC_JOIN(_, CC_RECURSIVE_4_MAP(CC_MANGLE_TYPE_5, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_5(...) CC_JOIN(_, CC_RECURSIVE_5_MAP(CC_MANGLE_TYPE_6, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_6(...) CC_JOIN(_, CC_RECURSIVE_6_MAP(CC_MANGLE_TYPE_7, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_7(...) CC_JOIN(_, CC_RECURSIVE_7_MAP(CC_MANGLE_TYPE_8, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_8(...) CC_JOIN(_, CC_RECURSIVE_8_MAP(CC_MANGLE_TYPE_9, __VA_ARGS__))
#define CC_MANGLE_TYPE_LIST_9(...) CC_JOIN(_, CC_RECURSIVE_9_MAP(CC_MANGLE_TYPE_10, __VA_ARGS__))


#pragma mark -
#pragma mark Type Extraction

/*!
 * @define CC_TYPE
 * @brief Get the base type from a given type declaration.
 * @description Custom types will need to provide their own @b CC_TYPE_ defines if they want to be
 *              detected. Otherwise utilise the @b TYPE(x) or @b PTYPE(x) or @b FPTYPE(x) macros in
 *              your declaration.
 */
#define CC_TYPE(x, ...) CC_TYPE_0(x)

/*!
 * @define CC_PRESERVE_TYPE
 * @brief Get the base type from a given type declaration and preserve the trailing tokens in the
 *        expansion.
 *
 * @description Custom types will need to provide their own @b CC_TYPE_ and @b CC_PRESERVE_CC_TYPE_
 *              defines if they want to be detected. Otherwise utilise the @b TYPE(x) or @b PTYPE(x)
 *              or @b FPTYPE(x) macros in your declaration.
 */
#define CC_PRESERVE_TYPE(x, ...) CC_PRESERVE_TYPE_0(x)

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

#define CC_PRESERVE_TYPE_0(x) CC_PRESERVE_TYPE_EXPAND_0(CC_TYPE_0_ x)
#define CC_PRESERVE_TYPE_1(x) CC_PRESERVE_TYPE_EXPAND_1(CC_TYPE_1_ x)
#define CC_PRESERVE_TYPE_2(x) CC_PRESERVE_TYPE_EXPAND_2(CC_TYPE_2_ x)
#define CC_PRESERVE_TYPE_3(x) CC_PRESERVE_TYPE_EXPAND_3(CC_TYPE_3_ x)
#define CC_PRESERVE_TYPE_4(x) CC_PRESERVE_TYPE_EXPAND_4(CC_TYPE_4_ x)
#define CC_PRESERVE_TYPE_5(x) CC_PRESERVE_TYPE_EXPAND_5(CC_TYPE_5_ x)
#define CC_PRESERVE_TYPE_6(x) CC_PRESERVE_TYPE_EXPAND_6(CC_TYPE_6_ x)
#define CC_PRESERVE_TYPE_7(x) CC_PRESERVE_TYPE_EXPAND_7(CC_TYPE_7_ x)
#define CC_PRESERVE_TYPE_8(x) CC_PRESERVE_TYPE_EXPAND_8(CC_TYPE_8_ x)
#define CC_PRESERVE_TYPE_9(x) CC_PRESERVE_TYPE_EXPAND_9(CC_TYPE_9_ x)

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

#define CC_PRESERVE_TYPE_EXPAND_0(x) CC_PRESERVE_TYPE_EXPAND_0_(x)
#define CC_PRESERVE_TYPE_EXPAND_1(x) CC_PRESERVE_TYPE_EXPAND_1_(x)
#define CC_PRESERVE_TYPE_EXPAND_2(x) CC_PRESERVE_TYPE_EXPAND_2_(x)
#define CC_PRESERVE_TYPE_EXPAND_3(x) CC_PRESERVE_TYPE_EXPAND_3_(x)
#define CC_PRESERVE_TYPE_EXPAND_4(x) CC_PRESERVE_TYPE_EXPAND_4_(x)
#define CC_PRESERVE_TYPE_EXPAND_5(x) CC_PRESERVE_TYPE_EXPAND_5_(x)
#define CC_PRESERVE_TYPE_EXPAND_6(x) CC_PRESERVE_TYPE_EXPAND_6_(x)
#define CC_PRESERVE_TYPE_EXPAND_7(x) CC_PRESERVE_TYPE_EXPAND_7_(x)
#define CC_PRESERVE_TYPE_EXPAND_8(x) CC_PRESERVE_TYPE_EXPAND_8_(x)
#define CC_PRESERVE_TYPE_EXPAND_9(x) CC_PRESERVE_TYPE_EXPAND_9_(x)
#define CC_PRESERVE_TYPE_EXPAND_0_(x) CC_PRESERVE_TYPE_EXPAND_0__(CC_TYPE_CONSUME_0_##x)
#define CC_PRESERVE_TYPE_EXPAND_1_(x) CC_PRESERVE_TYPE_EXPAND_1__(CC_TYPE_CONSUME_1_##x)
#define CC_PRESERVE_TYPE_EXPAND_2_(x) CC_PRESERVE_TYPE_EXPAND_2__(CC_TYPE_CONSUME_2_##x)
#define CC_PRESERVE_TYPE_EXPAND_3_(x) CC_PRESERVE_TYPE_EXPAND_3__(CC_TYPE_CONSUME_3_##x)
#define CC_PRESERVE_TYPE_EXPAND_4_(x) CC_PRESERVE_TYPE_EXPAND_4__(CC_TYPE_CONSUME_4_##x)
#define CC_PRESERVE_TYPE_EXPAND_5_(x) CC_PRESERVE_TYPE_EXPAND_5__(CC_TYPE_CONSUME_5_##x)
#define CC_PRESERVE_TYPE_EXPAND_6_(x) CC_PRESERVE_TYPE_EXPAND_6__(CC_TYPE_CONSUME_6_##x)
#define CC_PRESERVE_TYPE_EXPAND_7_(x) CC_PRESERVE_TYPE_EXPAND_7__(CC_TYPE_CONSUME_7_##x)
#define CC_PRESERVE_TYPE_EXPAND_8_(x) CC_PRESERVE_TYPE_EXPAND_8__(CC_TYPE_CONSUME_8_##x)
#define CC_PRESERVE_TYPE_EXPAND_9_(x) CC_PRESERVE_TYPE_EXPAND_9__(CC_TYPE_CONSUME_9_##x)
#define CC_PRESERVE_TYPE_EXPAND_0__(x) CC_PRESERVE_TYPE_EXPAND_0___(x)
#define CC_PRESERVE_TYPE_EXPAND_1__(x) CC_PRESERVE_TYPE_EXPAND_1___(x)
#define CC_PRESERVE_TYPE_EXPAND_2__(x) CC_PRESERVE_TYPE_EXPAND_2___(x)
#define CC_PRESERVE_TYPE_EXPAND_3__(x) CC_PRESERVE_TYPE_EXPAND_3___(x)
#define CC_PRESERVE_TYPE_EXPAND_4__(x) CC_PRESERVE_TYPE_EXPAND_4___(x)
#define CC_PRESERVE_TYPE_EXPAND_5__(x) CC_PRESERVE_TYPE_EXPAND_5___(x)
#define CC_PRESERVE_TYPE_EXPAND_6__(x) CC_PRESERVE_TYPE_EXPAND_6___(x)
#define CC_PRESERVE_TYPE_EXPAND_7__(x) CC_PRESERVE_TYPE_EXPAND_7___(x)
#define CC_PRESERVE_TYPE_EXPAND_8__(x) CC_PRESERVE_TYPE_EXPAND_8___(x)
#define CC_PRESERVE_TYPE_EXPAND_9__(x) CC_PRESERVE_TYPE_EXPAND_9___(x)
#define CC_PRESERVE_TYPE_EXPAND_0___(x) CC_PRESERVE_TYPE_EXPAND_0____(CC_TYPE_0_##x)
#define CC_PRESERVE_TYPE_EXPAND_1___(x) CC_PRESERVE_TYPE_EXPAND_1____(CC_TYPE_1_##x)
#define CC_PRESERVE_TYPE_EXPAND_2___(x) CC_PRESERVE_TYPE_EXPAND_2____(CC_TYPE_2_##x)
#define CC_PRESERVE_TYPE_EXPAND_3___(x) CC_PRESERVE_TYPE_EXPAND_3____(CC_TYPE_3_##x)
#define CC_PRESERVE_TYPE_EXPAND_4___(x) CC_PRESERVE_TYPE_EXPAND_4____(CC_TYPE_4_##x)
#define CC_PRESERVE_TYPE_EXPAND_5___(x) CC_PRESERVE_TYPE_EXPAND_5____(CC_TYPE_5_##x)
#define CC_PRESERVE_TYPE_EXPAND_6___(x) CC_PRESERVE_TYPE_EXPAND_6____(CC_TYPE_6_##x)
#define CC_PRESERVE_TYPE_EXPAND_7___(x) CC_PRESERVE_TYPE_EXPAND_7____(CC_TYPE_7_##x)
#define CC_PRESERVE_TYPE_EXPAND_8___(x) CC_PRESERVE_TYPE_EXPAND_8____(CC_TYPE_8_##x)
#define CC_PRESERVE_TYPE_EXPAND_9___(x) CC_PRESERVE_TYPE_EXPAND_9____(CC_TYPE_9_##x)
#define CC_PRESERVE_TYPE_EXPAND_0____(x) CC_PRESERVE_TYPE_EXPAND_0_____(x)
#define CC_PRESERVE_TYPE_EXPAND_1____(x) CC_PRESERVE_TYPE_EXPAND_1_____(x)
#define CC_PRESERVE_TYPE_EXPAND_2____(x) CC_PRESERVE_TYPE_EXPAND_2_____(x)
#define CC_PRESERVE_TYPE_EXPAND_3____(x) CC_PRESERVE_TYPE_EXPAND_3_____(x)
#define CC_PRESERVE_TYPE_EXPAND_4____(x) CC_PRESERVE_TYPE_EXPAND_4_____(x)
#define CC_PRESERVE_TYPE_EXPAND_5____(x) CC_PRESERVE_TYPE_EXPAND_5_____(x)
#define CC_PRESERVE_TYPE_EXPAND_6____(x) CC_PRESERVE_TYPE_EXPAND_6_____(x)
#define CC_PRESERVE_TYPE_EXPAND_7____(x) CC_PRESERVE_TYPE_EXPAND_7_____(x)
#define CC_PRESERVE_TYPE_EXPAND_8____(x) CC_PRESERVE_TYPE_EXPAND_8_____(x)
#define CC_PRESERVE_TYPE_EXPAND_9____(x) CC_PRESERVE_TYPE_EXPAND_9_____(x)
#define CC_PRESERVE_TYPE_EXPAND_0_____(...) CC_PRESERVE_TYPE_EXPAND_0______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_1_____(...) CC_PRESERVE_TYPE_EXPAND_1______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_2_____(...) CC_PRESERVE_TYPE_EXPAND_2______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_3_____(...) CC_PRESERVE_TYPE_EXPAND_3______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_4_____(...) CC_PRESERVE_TYPE_EXPAND_4______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_5_____(...) CC_PRESERVE_TYPE_EXPAND_5______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_6_____(...) CC_PRESERVE_TYPE_EXPAND_6______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_7_____(...) CC_PRESERVE_TYPE_EXPAND_7______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_8_____(...) CC_PRESERVE_TYPE_EXPAND_8______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_9_____(...) CC_PRESERVE_TYPE_EXPAND_9______(CC_PRESERVE_##__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_0______(...) CC_PRESERVE_TYPE_EXPAND_0_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_1______(...) CC_PRESERVE_TYPE_EXPAND_1_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_2______(...) CC_PRESERVE_TYPE_EXPAND_2_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_3______(...) CC_PRESERVE_TYPE_EXPAND_3_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_4______(...) CC_PRESERVE_TYPE_EXPAND_4_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_5______(...) CC_PRESERVE_TYPE_EXPAND_5_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_6______(...) CC_PRESERVE_TYPE_EXPAND_6_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_7______(...) CC_PRESERVE_TYPE_EXPAND_7_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_8______(...) CC_PRESERVE_TYPE_EXPAND_8_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_9______(...) CC_PRESERVE_TYPE_EXPAND_9_______(__VA_ARGS__)
#define CC_PRESERVE_TYPE_EXPAND_0_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_1_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_2_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_3_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_4_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_5_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_6_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_7_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_8_______(x, ...) x(__VA_ARGS__), __VA_ARGS__
#define CC_PRESERVE_TYPE_EXPAND_9_______(x, ...) x(__VA_ARGS__), __VA_ARGS__

#define CC_PRESERVE_CC_TYPE_0(x) CC_PRESERVE_TYPE_0(x)
#define CC_PRESERVE_CC_TYPE_1(x) CC_PRESERVE_TYPE_1(x)
#define CC_PRESERVE_CC_TYPE_2(x) CC_PRESERVE_TYPE_2(x)
#define CC_PRESERVE_CC_TYPE_3(x) CC_PRESERVE_TYPE_3(x)
#define CC_PRESERVE_CC_TYPE_4(x) CC_PRESERVE_TYPE_4(x)
#define CC_PRESERVE_CC_TYPE_5(x) CC_PRESERVE_TYPE_5(x)
#define CC_PRESERVE_CC_TYPE_6(x) CC_PRESERVE_TYPE_6(x)
#define CC_PRESERVE_CC_TYPE_7(x) CC_PRESERVE_TYPE_7(x)
#define CC_PRESERVE_CC_TYPE_8(x) CC_PRESERVE_TYPE_8(x)
#define CC_PRESERVE_CC_TYPE_9(x) CC_PRESERVE_TYPE_9(x)

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

#define CC_PRESERVE_CC_TYPE_TYPE(x, ...) CC_TYPE_TYPE(x), __VA_ARGS__

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

#define CC_PRESERVE_CC_TYPE_PTYPE(x, ...) CC_TYPE_PTYPE(x), __VA_ARGS__

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

#define CC_PRESERVE_CC_TYPE_FPTYPE(x, ...) CC_TYPE_FPTYPE(x), __VA_ARGS__

//void
#define CC_TYPE_void(...) void
#define CC_TYPE_0_void CC_TYPE_void,
#define CC_TYPE_1_void CC_TYPE_void,
#define CC_TYPE_2_void CC_TYPE_void,
#define CC_TYPE_3_void CC_TYPE_void,
#define CC_TYPE_4_void CC_TYPE_void,
#define CC_TYPE_5_void CC_TYPE_void,
#define CC_TYPE_6_void CC_TYPE_void,
#define CC_TYPE_7_void CC_TYPE_void,
#define CC_TYPE_8_void CC_TYPE_void,
#define CC_TYPE_9_void CC_TYPE_void,

#define CC_PRESERVE_CC_TYPE_void CC_TYPE_void

#define CC_MANGLE_TYPE_0_void V
#define CC_MANGLE_TYPE_1_void V
#define CC_MANGLE_TYPE_2_void V
#define CC_MANGLE_TYPE_3_void V
#define CC_MANGLE_TYPE_4_void V
#define CC_MANGLE_TYPE_5_void V
#define CC_MANGLE_TYPE_6_void V
#define CC_MANGLE_TYPE_7_void V
#define CC_MANGLE_TYPE_8_void V
#define CC_MANGLE_TYPE_9_void V

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

#define CC_PRESERVE_CC_TYPE__Bool CC_TYPE__Bool

#define CC_MANGLE_TYPE_0__Bool B
#define CC_MANGLE_TYPE_1__Bool B
#define CC_MANGLE_TYPE_2__Bool B
#define CC_MANGLE_TYPE_3__Bool B
#define CC_MANGLE_TYPE_4__Bool B
#define CC_MANGLE_TYPE_5__Bool B
#define CC_MANGLE_TYPE_6__Bool B
#define CC_MANGLE_TYPE_7__Bool B
#define CC_MANGLE_TYPE_8__Bool B
#define CC_MANGLE_TYPE_9__Bool B

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

#define CC_PRESERVE_CC_TYPE_bool CC_TYPE_bool

#define CC_MANGLE_TYPE_0_bool B
#define CC_MANGLE_TYPE_1_bool B
#define CC_MANGLE_TYPE_2_bool B
#define CC_MANGLE_TYPE_3_bool B
#define CC_MANGLE_TYPE_4_bool B
#define CC_MANGLE_TYPE_5_bool B
#define CC_MANGLE_TYPE_6_bool B
#define CC_MANGLE_TYPE_7_bool B
#define CC_MANGLE_TYPE_8_bool B
#define CC_MANGLE_TYPE_9_bool B

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

#define CC_PRESERVE_CC_TYPE_char CC_TYPE_char

#if CHAR_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_char I8
#define CC_MANGLE_TYPE_1_char I8
#define CC_MANGLE_TYPE_2_char I8
#define CC_MANGLE_TYPE_3_char I8
#define CC_MANGLE_TYPE_4_char I8
#define CC_MANGLE_TYPE_5_char I8
#define CC_MANGLE_TYPE_6_char I8
#define CC_MANGLE_TYPE_7_char I8
#define CC_MANGLE_TYPE_8_char I8
#define CC_MANGLE_TYPE_9_char I8
#elif CHAR_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_char I16
#define CC_MANGLE_TYPE_1_char I16
#define CC_MANGLE_TYPE_2_char I16
#define CC_MANGLE_TYPE_3_char I16
#define CC_MANGLE_TYPE_4_char I16
#define CC_MANGLE_TYPE_5_char I16
#define CC_MANGLE_TYPE_6_char I16
#define CC_MANGLE_TYPE_7_char I16
#define CC_MANGLE_TYPE_8_char I16
#define CC_MANGLE_TYPE_9_char I16
#elif CHAR_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_char I32
#define CC_MANGLE_TYPE_1_char I32
#define CC_MANGLE_TYPE_2_char I32
#define CC_MANGLE_TYPE_3_char I32
#define CC_MANGLE_TYPE_4_char I32
#define CC_MANGLE_TYPE_5_char I32
#define CC_MANGLE_TYPE_6_char I32
#define CC_MANGLE_TYPE_7_char I32
#define CC_MANGLE_TYPE_8_char I32
#define CC_MANGLE_TYPE_9_char I32
#elif CHAR_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_char I64
#define CC_MANGLE_TYPE_1_char I64
#define CC_MANGLE_TYPE_2_char I64
#define CC_MANGLE_TYPE_3_char I64
#define CC_MANGLE_TYPE_4_char I64
#define CC_MANGLE_TYPE_5_char I64
#define CC_MANGLE_TYPE_6_char I64
#define CC_MANGLE_TYPE_7_char I64
#define CC_MANGLE_TYPE_8_char I64
#define CC_MANGLE_TYPE_9_char I64
#endif

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

#define CC_PRESERVE_CC_TYPE_short CC_TYPE_short

#if SHORT_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_short I8
#define CC_MANGLE_TYPE_1_short I8
#define CC_MANGLE_TYPE_2_short I8
#define CC_MANGLE_TYPE_3_short I8
#define CC_MANGLE_TYPE_4_short I8
#define CC_MANGLE_TYPE_5_short I8
#define CC_MANGLE_TYPE_6_short I8
#define CC_MANGLE_TYPE_7_short I8
#define CC_MANGLE_TYPE_8_short I8
#define CC_MANGLE_TYPE_9_short I8
#elif SHORT_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_short I16
#define CC_MANGLE_TYPE_1_short I16
#define CC_MANGLE_TYPE_2_short I16
#define CC_MANGLE_TYPE_3_short I16
#define CC_MANGLE_TYPE_4_short I16
#define CC_MANGLE_TYPE_5_short I16
#define CC_MANGLE_TYPE_6_short I16
#define CC_MANGLE_TYPE_7_short I16
#define CC_MANGLE_TYPE_8_short I16
#define CC_MANGLE_TYPE_9_short I16
#elif SHORT_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_short I32
#define CC_MANGLE_TYPE_1_short I32
#define CC_MANGLE_TYPE_2_short I32
#define CC_MANGLE_TYPE_3_short I32
#define CC_MANGLE_TYPE_4_short I32
#define CC_MANGLE_TYPE_5_short I32
#define CC_MANGLE_TYPE_6_short I32
#define CC_MANGLE_TYPE_7_short I32
#define CC_MANGLE_TYPE_8_short I32
#define CC_MANGLE_TYPE_9_short I32
#elif SHORT_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_short I64
#define CC_MANGLE_TYPE_1_short I64
#define CC_MANGLE_TYPE_2_short I64
#define CC_MANGLE_TYPE_3_short I64
#define CC_MANGLE_TYPE_4_short I64
#define CC_MANGLE_TYPE_5_short I64
#define CC_MANGLE_TYPE_6_short I64
#define CC_MANGLE_TYPE_7_short I64
#define CC_MANGLE_TYPE_8_short I64
#define CC_MANGLE_TYPE_9_short I64
#endif

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

#define CC_PRESERVE_CC_TYPE_int CC_TYPE_int

#if INT_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_int I8
#define CC_MANGLE_TYPE_1_int I8
#define CC_MANGLE_TYPE_2_int I8
#define CC_MANGLE_TYPE_3_int I8
#define CC_MANGLE_TYPE_4_int I8
#define CC_MANGLE_TYPE_5_int I8
#define CC_MANGLE_TYPE_6_int I8
#define CC_MANGLE_TYPE_7_int I8
#define CC_MANGLE_TYPE_8_int I8
#define CC_MANGLE_TYPE_9_int I8
#elif INT_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_int I16
#define CC_MANGLE_TYPE_1_int I16
#define CC_MANGLE_TYPE_2_int I16
#define CC_MANGLE_TYPE_3_int I16
#define CC_MANGLE_TYPE_4_int I16
#define CC_MANGLE_TYPE_5_int I16
#define CC_MANGLE_TYPE_6_int I16
#define CC_MANGLE_TYPE_7_int I16
#define CC_MANGLE_TYPE_8_int I16
#define CC_MANGLE_TYPE_9_int I16
#elif INT_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_int I32
#define CC_MANGLE_TYPE_1_int I32
#define CC_MANGLE_TYPE_2_int I32
#define CC_MANGLE_TYPE_3_int I32
#define CC_MANGLE_TYPE_4_int I32
#define CC_MANGLE_TYPE_5_int I32
#define CC_MANGLE_TYPE_6_int I32
#define CC_MANGLE_TYPE_7_int I32
#define CC_MANGLE_TYPE_8_int I32
#define CC_MANGLE_TYPE_9_int I32
#elif INT_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_int I64
#define CC_MANGLE_TYPE_1_int I64
#define CC_MANGLE_TYPE_2_int I64
#define CC_MANGLE_TYPE_3_int I64
#define CC_MANGLE_TYPE_4_int I64
#define CC_MANGLE_TYPE_5_int I64
#define CC_MANGLE_TYPE_6_int I64
#define CC_MANGLE_TYPE_7_int I64
#define CC_MANGLE_TYPE_8_int I64
#define CC_MANGLE_TYPE_9_int I64
#endif

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

#define CC_PRESERVE_CC_TYPE_long CC_TYPE_long

#if LONG_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_long I8
#define CC_MANGLE_TYPE_1_long I8
#define CC_MANGLE_TYPE_2_long I8
#define CC_MANGLE_TYPE_3_long I8
#define CC_MANGLE_TYPE_4_long I8
#define CC_MANGLE_TYPE_5_long I8
#define CC_MANGLE_TYPE_6_long I8
#define CC_MANGLE_TYPE_7_long I8
#define CC_MANGLE_TYPE_8_long I8
#define CC_MANGLE_TYPE_9_long I8
#elif LONG_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_long I16
#define CC_MANGLE_TYPE_1_long I16
#define CC_MANGLE_TYPE_2_long I16
#define CC_MANGLE_TYPE_3_long I16
#define CC_MANGLE_TYPE_4_long I16
#define CC_MANGLE_TYPE_5_long I16
#define CC_MANGLE_TYPE_6_long I16
#define CC_MANGLE_TYPE_7_long I16
#define CC_MANGLE_TYPE_8_long I16
#define CC_MANGLE_TYPE_9_long I16
#elif LONG_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_long I32
#define CC_MANGLE_TYPE_1_long I32
#define CC_MANGLE_TYPE_2_long I32
#define CC_MANGLE_TYPE_3_long I32
#define CC_MANGLE_TYPE_4_long I32
#define CC_MANGLE_TYPE_5_long I32
#define CC_MANGLE_TYPE_6_long I32
#define CC_MANGLE_TYPE_7_long I32
#define CC_MANGLE_TYPE_8_long I32
#define CC_MANGLE_TYPE_9_long I32
#elif LONG_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_long I64
#define CC_MANGLE_TYPE_1_long I64
#define CC_MANGLE_TYPE_2_long I64
#define CC_MANGLE_TYPE_3_long I64
#define CC_MANGLE_TYPE_4_long I64
#define CC_MANGLE_TYPE_5_long I64
#define CC_MANGLE_TYPE_6_long I64
#define CC_MANGLE_TYPE_7_long I64
#define CC_MANGLE_TYPE_8_long I64
#define CC_MANGLE_TYPE_9_long I64
#endif

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

#define CC_PRESERVE_CC_TYPE_float CC_TYPE_float

#if FLT_MANT_DIG == 24
#define CC_MANGLE_TYPE_0_float F32
#define CC_MANGLE_TYPE_1_float F32
#define CC_MANGLE_TYPE_2_float F32
#define CC_MANGLE_TYPE_3_float F32
#define CC_MANGLE_TYPE_4_float F32
#define CC_MANGLE_TYPE_5_float F32
#define CC_MANGLE_TYPE_6_float F32
#define CC_MANGLE_TYPE_7_float F32
#define CC_MANGLE_TYPE_8_float F32
#define CC_MANGLE_TYPE_9_float F32
#elif FLT_MANT_DIG == 53
#define CC_MANGLE_TYPE_0_float F64
#define CC_MANGLE_TYPE_1_float F64
#define CC_MANGLE_TYPE_2_float F64
#define CC_MANGLE_TYPE_3_float F64
#define CC_MANGLE_TYPE_4_float F64
#define CC_MANGLE_TYPE_5_float F64
#define CC_MANGLE_TYPE_6_float F64
#define CC_MANGLE_TYPE_7_float F64
#define CC_MANGLE_TYPE_8_float F64
#define CC_MANGLE_TYPE_9_float F64
#endif

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

#define CC_PRESERVE_CC_TYPE_double CC_TYPE_double

#if DBL_MANT_DIG == 24
#define CC_MANGLE_TYPE_0_double F32
#define CC_MANGLE_TYPE_1_double F32
#define CC_MANGLE_TYPE_2_double F32
#define CC_MANGLE_TYPE_3_double F32
#define CC_MANGLE_TYPE_4_double F32
#define CC_MANGLE_TYPE_5_double F32
#define CC_MANGLE_TYPE_6_double F32
#define CC_MANGLE_TYPE_7_double F32
#define CC_MANGLE_TYPE_8_double F32
#define CC_MANGLE_TYPE_9_double F32
#elif DBL_MANT_DIG == 53
#define CC_MANGLE_TYPE_0_double F64
#define CC_MANGLE_TYPE_1_double F64
#define CC_MANGLE_TYPE_2_double F64
#define CC_MANGLE_TYPE_3_double F64
#define CC_MANGLE_TYPE_4_double F64
#define CC_MANGLE_TYPE_5_double F64
#define CC_MANGLE_TYPE_6_double F64
#define CC_MANGLE_TYPE_7_double F64
#define CC_MANGLE_TYPE_8_double F64
#define CC_MANGLE_TYPE_9_double F64
#endif

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

#define CC_PRESERVE_CC_TYPE_int8_t CC_TYPE_int8_t

#define CC_MANGLE_TYPE_0_int8_t I8
#define CC_MANGLE_TYPE_1_int8_t I8
#define CC_MANGLE_TYPE_2_int8_t I8
#define CC_MANGLE_TYPE_3_int8_t I8
#define CC_MANGLE_TYPE_4_int8_t I8
#define CC_MANGLE_TYPE_5_int8_t I8
#define CC_MANGLE_TYPE_6_int8_t I8
#define CC_MANGLE_TYPE_7_int8_t I8
#define CC_MANGLE_TYPE_8_int8_t I8
#define CC_MANGLE_TYPE_9_int8_t I8

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

#define CC_PRESERVE_CC_TYPE_int16_t CC_TYPE_int16_t

#define CC_MANGLE_TYPE_0_int16_t I16
#define CC_MANGLE_TYPE_1_int16_t I16
#define CC_MANGLE_TYPE_2_int16_t I16
#define CC_MANGLE_TYPE_3_int16_t I16
#define CC_MANGLE_TYPE_4_int16_t I16
#define CC_MANGLE_TYPE_5_int16_t I16
#define CC_MANGLE_TYPE_6_int16_t I16
#define CC_MANGLE_TYPE_7_int16_t I16
#define CC_MANGLE_TYPE_8_int16_t I16
#define CC_MANGLE_TYPE_9_int16_t I16

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

#define CC_PRESERVE_CC_TYPE_int32_t CC_TYPE_int32_t

#define CC_MANGLE_TYPE_0_int32_t I32
#define CC_MANGLE_TYPE_1_int32_t I32
#define CC_MANGLE_TYPE_2_int32_t I32
#define CC_MANGLE_TYPE_3_int32_t I32
#define CC_MANGLE_TYPE_4_int32_t I32
#define CC_MANGLE_TYPE_5_int32_t I32
#define CC_MANGLE_TYPE_6_int32_t I32
#define CC_MANGLE_TYPE_7_int32_t I32
#define CC_MANGLE_TYPE_8_int32_t I32
#define CC_MANGLE_TYPE_9_int32_t I32

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

#define CC_PRESERVE_CC_TYPE_int64_t CC_TYPE_int64_t

#define CC_MANGLE_TYPE_0_int64_t I64
#define CC_MANGLE_TYPE_1_int64_t I64
#define CC_MANGLE_TYPE_2_int64_t I64
#define CC_MANGLE_TYPE_3_int64_t I64
#define CC_MANGLE_TYPE_4_int64_t I64
#define CC_MANGLE_TYPE_5_int64_t I64
#define CC_MANGLE_TYPE_6_int64_t I64
#define CC_MANGLE_TYPE_7_int64_t I64
#define CC_MANGLE_TYPE_8_int64_t I64
#define CC_MANGLE_TYPE_9_int64_t I64

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

#define CC_PRESERVE_CC_TYPE_uint8_t CC_TYPE_uint8_t

#define CC_MANGLE_TYPE_0_uint8_t U8
#define CC_MANGLE_TYPE_1_uint8_t U8
#define CC_MANGLE_TYPE_2_uint8_t U8
#define CC_MANGLE_TYPE_3_uint8_t U8
#define CC_MANGLE_TYPE_4_uint8_t U8
#define CC_MANGLE_TYPE_5_uint8_t U8
#define CC_MANGLE_TYPE_6_uint8_t U8
#define CC_MANGLE_TYPE_7_uint8_t U8
#define CC_MANGLE_TYPE_8_uint8_t U8
#define CC_MANGLE_TYPE_9_uint8_t U8

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

#define CC_PRESERVE_CC_TYPE_uint16_t CC_TYPE_uint16_t

#define CC_MANGLE_TYPE_0_uint16_t U16
#define CC_MANGLE_TYPE_1_uint16_t U16
#define CC_MANGLE_TYPE_2_uint16_t U16
#define CC_MANGLE_TYPE_3_uint16_t U16
#define CC_MANGLE_TYPE_4_uint16_t U16
#define CC_MANGLE_TYPE_5_uint16_t U16
#define CC_MANGLE_TYPE_6_uint16_t U16
#define CC_MANGLE_TYPE_7_uint16_t U16
#define CC_MANGLE_TYPE_8_uint16_t U16
#define CC_MANGLE_TYPE_9_uint16_t U16

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

#define CC_PRESERVE_CC_TYPE_uint32_t CC_TYPE_uint32_t

#define CC_MANGLE_TYPE_0_uint32_t U32
#define CC_MANGLE_TYPE_1_uint32_t U32
#define CC_MANGLE_TYPE_2_uint32_t U32
#define CC_MANGLE_TYPE_3_uint32_t U32
#define CC_MANGLE_TYPE_4_uint32_t U32
#define CC_MANGLE_TYPE_5_uint32_t U32
#define CC_MANGLE_TYPE_6_uint32_t U32
#define CC_MANGLE_TYPE_7_uint32_t U32
#define CC_MANGLE_TYPE_8_uint32_t U32
#define CC_MANGLE_TYPE_9_uint32_t U32

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

#define CC_PRESERVE_CC_TYPE_uint64_t CC_TYPE_uint64_t

#define CC_MANGLE_TYPE_0_uint64_t U64
#define CC_MANGLE_TYPE_1_uint64_t U64
#define CC_MANGLE_TYPE_2_uint64_t U64
#define CC_MANGLE_TYPE_3_uint64_t U64
#define CC_MANGLE_TYPE_4_uint64_t U64
#define CC_MANGLE_TYPE_5_uint64_t U64
#define CC_MANGLE_TYPE_6_uint64_t U64
#define CC_MANGLE_TYPE_7_uint64_t U64
#define CC_MANGLE_TYPE_8_uint64_t U64
#define CC_MANGLE_TYPE_9_uint64_t U64

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

#define CC_PRESERVE_CC_TYPE_intmax_t CC_TYPE_intmax_t

#if INTMAX_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_intmax_t I8
#define CC_MANGLE_TYPE_1_intmax_t I8
#define CC_MANGLE_TYPE_2_intmax_t I8
#define CC_MANGLE_TYPE_3_intmax_t I8
#define CC_MANGLE_TYPE_4_intmax_t I8
#define CC_MANGLE_TYPE_5_intmax_t I8
#define CC_MANGLE_TYPE_6_intmax_t I8
#define CC_MANGLE_TYPE_7_intmax_t I8
#define CC_MANGLE_TYPE_8_intmax_t I8
#define CC_MANGLE_TYPE_9_intmax_t I8
#elif INTMAX_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_intmax_t I16
#define CC_MANGLE_TYPE_1_intmax_t I16
#define CC_MANGLE_TYPE_2_intmax_t I16
#define CC_MANGLE_TYPE_3_intmax_t I16
#define CC_MANGLE_TYPE_4_intmax_t I16
#define CC_MANGLE_TYPE_5_intmax_t I16
#define CC_MANGLE_TYPE_6_intmax_t I16
#define CC_MANGLE_TYPE_7_intmax_t I16
#define CC_MANGLE_TYPE_8_intmax_t I16
#define CC_MANGLE_TYPE_9_intmax_t I16
#elif INTMAX_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_intmax_t I32
#define CC_MANGLE_TYPE_1_intmax_t I32
#define CC_MANGLE_TYPE_2_intmax_t I32
#define CC_MANGLE_TYPE_3_intmax_t I32
#define CC_MANGLE_TYPE_4_intmax_t I32
#define CC_MANGLE_TYPE_5_intmax_t I32
#define CC_MANGLE_TYPE_6_intmax_t I32
#define CC_MANGLE_TYPE_7_intmax_t I32
#define CC_MANGLE_TYPE_8_intmax_t I32
#define CC_MANGLE_TYPE_9_intmax_t I32
#elif INTMAX_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_intmax_t I64
#define CC_MANGLE_TYPE_1_intmax_t I64
#define CC_MANGLE_TYPE_2_intmax_t I64
#define CC_MANGLE_TYPE_3_intmax_t I64
#define CC_MANGLE_TYPE_4_intmax_t I64
#define CC_MANGLE_TYPE_5_intmax_t I64
#define CC_MANGLE_TYPE_6_intmax_t I64
#define CC_MANGLE_TYPE_7_intmax_t I64
#define CC_MANGLE_TYPE_8_intmax_t I64
#define CC_MANGLE_TYPE_9_intmax_t I64
#endif

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

#define CC_PRESERVE_CC_TYPE_uintmax_t CC_TYPE_uintmax_t

#if UINTMAX_MAX == UINT8_MAX
#define CC_MANGLE_TYPE_0_uintmax_t U8
#define CC_MANGLE_TYPE_1_uintmax_t U8
#define CC_MANGLE_TYPE_2_uintmax_t U8
#define CC_MANGLE_TYPE_3_uintmax_t U8
#define CC_MANGLE_TYPE_4_uintmax_t U8
#define CC_MANGLE_TYPE_5_uintmax_t U8
#define CC_MANGLE_TYPE_6_uintmax_t U8
#define CC_MANGLE_TYPE_7_uintmax_t U8
#define CC_MANGLE_TYPE_8_uintmax_t U8
#define CC_MANGLE_TYPE_9_uintmax_t U8
#elif UINTMAX_MAX == UINT16_MAX
#define CC_MANGLE_TYPE_0_uintmax_t U16
#define CC_MANGLE_TYPE_1_uintmax_t U16
#define CC_MANGLE_TYPE_2_uintmax_t U16
#define CC_MANGLE_TYPE_3_uintmax_t U16
#define CC_MANGLE_TYPE_4_uintmax_t U16
#define CC_MANGLE_TYPE_5_uintmax_t U16
#define CC_MANGLE_TYPE_6_uintmax_t U16
#define CC_MANGLE_TYPE_7_uintmax_t U16
#define CC_MANGLE_TYPE_8_uintmax_t U16
#define CC_MANGLE_TYPE_9_uintmax_t U16
#elif UINTMAX_MAX == UINT32_MAX
#define CC_MANGLE_TYPE_0_uintmax_t U32
#define CC_MANGLE_TYPE_1_uintmax_t U32
#define CC_MANGLE_TYPE_2_uintmax_t U32
#define CC_MANGLE_TYPE_3_uintmax_t U32
#define CC_MANGLE_TYPE_4_uintmax_t U32
#define CC_MANGLE_TYPE_5_uintmax_t U32
#define CC_MANGLE_TYPE_6_uintmax_t U32
#define CC_MANGLE_TYPE_7_uintmax_t U32
#define CC_MANGLE_TYPE_8_uintmax_t U32
#define CC_MANGLE_TYPE_9_uintmax_t U32
#elif UINTMAX_MAX == UINT64_MAX
#define CC_MANGLE_TYPE_0_uintmax_t U64
#define CC_MANGLE_TYPE_1_uintmax_t U64
#define CC_MANGLE_TYPE_2_uintmax_t U64
#define CC_MANGLE_TYPE_3_uintmax_t U64
#define CC_MANGLE_TYPE_4_uintmax_t U64
#define CC_MANGLE_TYPE_5_uintmax_t U64
#define CC_MANGLE_TYPE_6_uintmax_t U64
#define CC_MANGLE_TYPE_7_uintmax_t U64
#define CC_MANGLE_TYPE_8_uintmax_t U64
#define CC_MANGLE_TYPE_9_uintmax_t U64
#endif

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

#define CC_PRESERVE_CC_TYPE_intptr_t CC_TYPE_intptr_t

#if INTPTR_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_intptr_t I8
#define CC_MANGLE_TYPE_1_intptr_t I8
#define CC_MANGLE_TYPE_2_intptr_t I8
#define CC_MANGLE_TYPE_3_intptr_t I8
#define CC_MANGLE_TYPE_4_intptr_t I8
#define CC_MANGLE_TYPE_5_intptr_t I8
#define CC_MANGLE_TYPE_6_intptr_t I8
#define CC_MANGLE_TYPE_7_intptr_t I8
#define CC_MANGLE_TYPE_8_intptr_t I8
#define CC_MANGLE_TYPE_9_intptr_t I8
#elif INTPTR_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_intptr_t I16
#define CC_MANGLE_TYPE_1_intptr_t I16
#define CC_MANGLE_TYPE_2_intptr_t I16
#define CC_MANGLE_TYPE_3_intptr_t I16
#define CC_MANGLE_TYPE_4_intptr_t I16
#define CC_MANGLE_TYPE_5_intptr_t I16
#define CC_MANGLE_TYPE_6_intptr_t I16
#define CC_MANGLE_TYPE_7_intptr_t I16
#define CC_MANGLE_TYPE_8_intptr_t I16
#define CC_MANGLE_TYPE_9_intptr_t I16
#elif INTPTR_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_intptr_t I32
#define CC_MANGLE_TYPE_1_intptr_t I32
#define CC_MANGLE_TYPE_2_intptr_t I32
#define CC_MANGLE_TYPE_3_intptr_t I32
#define CC_MANGLE_TYPE_4_intptr_t I32
#define CC_MANGLE_TYPE_5_intptr_t I32
#define CC_MANGLE_TYPE_6_intptr_t I32
#define CC_MANGLE_TYPE_7_intptr_t I32
#define CC_MANGLE_TYPE_8_intptr_t I32
#define CC_MANGLE_TYPE_9_intptr_t I32
#elif INTPTR_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_intptr_t I64
#define CC_MANGLE_TYPE_1_intptr_t I64
#define CC_MANGLE_TYPE_2_intptr_t I64
#define CC_MANGLE_TYPE_3_intptr_t I64
#define CC_MANGLE_TYPE_4_intptr_t I64
#define CC_MANGLE_TYPE_5_intptr_t I64
#define CC_MANGLE_TYPE_6_intptr_t I64
#define CC_MANGLE_TYPE_7_intptr_t I64
#define CC_MANGLE_TYPE_8_intptr_t I64
#define CC_MANGLE_TYPE_9_intptr_t I64
#endif

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

#define CC_PRESERVE_CC_TYPE_uintptr_t CC_TYPE_uintptr_t

#if UINTPTR_MAX == UINT8_MAX
#define CC_MANGLE_TYPE_0_uintptr_t U8
#define CC_MANGLE_TYPE_1_uintptr_t U8
#define CC_MANGLE_TYPE_2_uintptr_t U8
#define CC_MANGLE_TYPE_3_uintptr_t U8
#define CC_MANGLE_TYPE_4_uintptr_t U8
#define CC_MANGLE_TYPE_5_uintptr_t U8
#define CC_MANGLE_TYPE_6_uintptr_t U8
#define CC_MANGLE_TYPE_7_uintptr_t U8
#define CC_MANGLE_TYPE_8_uintptr_t U8
#define CC_MANGLE_TYPE_9_uintptr_t U8
#elif UINTPTR_MAX == UINT16_MAX
#define CC_MANGLE_TYPE_0_uintptr_t U16
#define CC_MANGLE_TYPE_1_uintptr_t U16
#define CC_MANGLE_TYPE_2_uintptr_t U16
#define CC_MANGLE_TYPE_3_uintptr_t U16
#define CC_MANGLE_TYPE_4_uintptr_t U16
#define CC_MANGLE_TYPE_5_uintptr_t U16
#define CC_MANGLE_TYPE_6_uintptr_t U16
#define CC_MANGLE_TYPE_7_uintptr_t U16
#define CC_MANGLE_TYPE_8_uintptr_t U16
#define CC_MANGLE_TYPE_9_uintptr_t U16
#elif UINTPTR_MAX == UINT32_MAX
#define CC_MANGLE_TYPE_0_uintptr_t U32
#define CC_MANGLE_TYPE_1_uintptr_t U32
#define CC_MANGLE_TYPE_2_uintptr_t U32
#define CC_MANGLE_TYPE_3_uintptr_t U32
#define CC_MANGLE_TYPE_4_uintptr_t U32
#define CC_MANGLE_TYPE_5_uintptr_t U32
#define CC_MANGLE_TYPE_6_uintptr_t U32
#define CC_MANGLE_TYPE_7_uintptr_t U32
#define CC_MANGLE_TYPE_8_uintptr_t U32
#define CC_MANGLE_TYPE_9_uintptr_t U32
#elif UINTPTR_MAX == UINT64_MAX
#define CC_MANGLE_TYPE_0_uintptr_t U64
#define CC_MANGLE_TYPE_1_uintptr_t U64
#define CC_MANGLE_TYPE_2_uintptr_t U64
#define CC_MANGLE_TYPE_3_uintptr_t U64
#define CC_MANGLE_TYPE_4_uintptr_t U64
#define CC_MANGLE_TYPE_5_uintptr_t U64
#define CC_MANGLE_TYPE_6_uintptr_t U64
#define CC_MANGLE_TYPE_7_uintptr_t U64
#define CC_MANGLE_TYPE_8_uintptr_t U64
#define CC_MANGLE_TYPE_9_uintptr_t U64
#endif

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

#define CC_PRESERVE_CC_TYPE_ptrdiff_t CC_TYPE_ptrdiff_t

#if PTRDIFF_MAX == INT8_MAX
#define CC_MANGLE_TYPE_0_ptrdiff_t I8
#define CC_MANGLE_TYPE_1_ptrdiff_t I8
#define CC_MANGLE_TYPE_2_ptrdiff_t I8
#define CC_MANGLE_TYPE_3_ptrdiff_t I8
#define CC_MANGLE_TYPE_4_ptrdiff_t I8
#define CC_MANGLE_TYPE_5_ptrdiff_t I8
#define CC_MANGLE_TYPE_6_ptrdiff_t I8
#define CC_MANGLE_TYPE_7_ptrdiff_t I8
#define CC_MANGLE_TYPE_8_ptrdiff_t I8
#define CC_MANGLE_TYPE_9_ptrdiff_t I8
#elif PTRDIFF_MAX == INT16_MAX
#define CC_MANGLE_TYPE_0_ptrdiff_t I16
#define CC_MANGLE_TYPE_1_ptrdiff_t I16
#define CC_MANGLE_TYPE_2_ptrdiff_t I16
#define CC_MANGLE_TYPE_3_ptrdiff_t I16
#define CC_MANGLE_TYPE_4_ptrdiff_t I16
#define CC_MANGLE_TYPE_5_ptrdiff_t I16
#define CC_MANGLE_TYPE_6_ptrdiff_t I16
#define CC_MANGLE_TYPE_7_ptrdiff_t I16
#define CC_MANGLE_TYPE_8_ptrdiff_t I16
#define CC_MANGLE_TYPE_9_ptrdiff_t I16
#elif PTRDIFF_MAX == INT32_MAX
#define CC_MANGLE_TYPE_0_ptrdiff_t I32
#define CC_MANGLE_TYPE_1_ptrdiff_t I32
#define CC_MANGLE_TYPE_2_ptrdiff_t I32
#define CC_MANGLE_TYPE_3_ptrdiff_t I32
#define CC_MANGLE_TYPE_4_ptrdiff_t I32
#define CC_MANGLE_TYPE_5_ptrdiff_t I32
#define CC_MANGLE_TYPE_6_ptrdiff_t I32
#define CC_MANGLE_TYPE_7_ptrdiff_t I32
#define CC_MANGLE_TYPE_8_ptrdiff_t I32
#define CC_MANGLE_TYPE_9_ptrdiff_t I32
#elif PTRDIFF_MAX == INT64_MAX
#define CC_MANGLE_TYPE_0_ptrdiff_t I64
#define CC_MANGLE_TYPE_1_ptrdiff_t I64
#define CC_MANGLE_TYPE_2_ptrdiff_t I64
#define CC_MANGLE_TYPE_3_ptrdiff_t I64
#define CC_MANGLE_TYPE_4_ptrdiff_t I64
#define CC_MANGLE_TYPE_5_ptrdiff_t I64
#define CC_MANGLE_TYPE_6_ptrdiff_t I64
#define CC_MANGLE_TYPE_7_ptrdiff_t I64
#define CC_MANGLE_TYPE_8_ptrdiff_t I64
#define CC_MANGLE_TYPE_9_ptrdiff_t I64
#endif

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

#define CC_PRESERVE_CC_TYPE_size_t CC_TYPE_size_t

#if SIZE_MAX == UINT8_MAX
#define CC_MANGLE_TYPE_0_size_t U8
#define CC_MANGLE_TYPE_1_size_t U8
#define CC_MANGLE_TYPE_2_size_t U8
#define CC_MANGLE_TYPE_3_size_t U8
#define CC_MANGLE_TYPE_4_size_t U8
#define CC_MANGLE_TYPE_5_size_t U8
#define CC_MANGLE_TYPE_6_size_t U8
#define CC_MANGLE_TYPE_7_size_t U8
#define CC_MANGLE_TYPE_8_size_t U8
#define CC_MANGLE_TYPE_9_size_t U8
#elif SIZE_MAX == UINT16_MAX
#define CC_MANGLE_TYPE_0_size_t U16
#define CC_MANGLE_TYPE_1_size_t U16
#define CC_MANGLE_TYPE_2_size_t U16
#define CC_MANGLE_TYPE_3_size_t U16
#define CC_MANGLE_TYPE_4_size_t U16
#define CC_MANGLE_TYPE_5_size_t U16
#define CC_MANGLE_TYPE_6_size_t U16
#define CC_MANGLE_TYPE_7_size_t U16
#define CC_MANGLE_TYPE_8_size_t U16
#define CC_MANGLE_TYPE_9_size_t U16
#elif SIZE_MAX == UINT32_MAX
#define CC_MANGLE_TYPE_0_size_t U32
#define CC_MANGLE_TYPE_1_size_t U32
#define CC_MANGLE_TYPE_2_size_t U32
#define CC_MANGLE_TYPE_3_size_t U32
#define CC_MANGLE_TYPE_4_size_t U32
#define CC_MANGLE_TYPE_5_size_t U32
#define CC_MANGLE_TYPE_6_size_t U32
#define CC_MANGLE_TYPE_7_size_t U32
#define CC_MANGLE_TYPE_8_size_t U32
#define CC_MANGLE_TYPE_9_size_t U32
#elif SIZE_MAX == UINT64_MAX
#define CC_MANGLE_TYPE_0_size_t U64
#define CC_MANGLE_TYPE_1_size_t U64
#define CC_MANGLE_TYPE_2_size_t U64
#define CC_MANGLE_TYPE_3_size_t U64
#define CC_MANGLE_TYPE_4_size_t U64
#define CC_MANGLE_TYPE_5_size_t U64
#define CC_MANGLE_TYPE_6_size_t U64
#define CC_MANGLE_TYPE_7_size_t U64
#define CC_MANGLE_TYPE_8_size_t U64
#define CC_MANGLE_TYPE_9_size_t U64
#endif

#endif
