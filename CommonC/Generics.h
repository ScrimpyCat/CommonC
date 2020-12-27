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

#ifndef CommonC_Generics_h
#define CommonC_Generics_h

#include <CommonC/Hacks.h>

#define CC_GENERIC_EVALUATE(val, ...) _Generic((1? (val) : (val)), __VA_ARGS__)

#define CC_GENERIC_INDEXED_TYPE(name, index) name##index

#define CC_GENERIC_INDEXED_TYPE_LIST(name, count) CC_REPEAT(0, count, CC_GENERIC_INDEXED_TYPE, name)

#define CC_GENERIC_TYPE_MATCH(type, _, fun) type: fun(type)

#define CC_GENERIC_CONSUME(...) __VA_ARGS__

#define CC_GENERIC_1(generic, types, ...) CC_GENERIC_1_(generic, types, CC_VA_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)
#define CC_GENERIC_1_(...) CC_GENERIC_1__(__VA_ARGS__)
#define CC_GENERIC_1__(generic, types, n, ...) CC_GENERIC_1___(generic, types, CC_GENERIC_1_##n, __VA_ARGS__)
#define CC_GENERIC_1___(generic, types, x, ...) x(generic, types, __VA_ARGS__)

#define CC_GENERIC_N_n(generic, types, args, ...) CC_GENERIC_EVALUATE(__VA_ARGS__, CC_MAP_WITH(CC_GENERIC_TYPE_MATCH, generic, CC_GENERIC_CONSUME types)) args

#define CC_GENERIC_1_n(generic, types, x, ...) CC_GENERIC_N_n(generic, types, (__VA_ARGS__), x)
#define CC_GENERIC_1_1(generic, types, x) CC_GENERIC_1_n(generic, types, x, x)
#define CC_GENERIC_1_2(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_3(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_4(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_5(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_6(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_7(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_8(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_9(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_10(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_11(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_12(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_13(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_14(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_15(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_16(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_17(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_18(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)
#define CC_GENERIC_1_19(generic, types, x, ...) CC_GENERIC_1_n(generic, types, x, x, __VA_ARGS__)

#endif
