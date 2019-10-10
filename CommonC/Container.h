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

#ifndef CommonC_Container_h
#define CommonC_Container_h

#include <CommonC/Hacks.h>

#if defined(CC_QUICK_COMPILE) && !defined(CC_CONTAINER_ENABLE)
#define CC_CONTAINER_DECLARE(type, ...)
#define CC_CONTAINER(type, ...) type
#define CC_CONTAINER_DECLARE_PRESET_1(type)
#define CC_CONTAINER_DECLARE_PRESET_2(type)
#else

/*!
 * @define CC_CONTAINER_DECLARE
 * @abstract Convenient macro to define a type that can be referenced by @b CC_CONTAINER.
 * @param type The type of the container.
 * @param va_args The element types inside the container.
 */
#define CC_CONTAINER_DECLARE(type, ...) typedef type CC_CONTAINER(type, __VA_ARGS__)

/*!
 * @define CC_CONTAINER
 * @abstract Define a generic container, explicitly specifying the element types contained.
 * @discussion The generic type will match that defined by @b CC_CONTAINER_DECLARE. To
 *             disable the typing, simply define @b CC_CONTAINER_TYPE_DISABLE (or define it
 *             to 1), and to re-enable it simply undefine it (or set it to 0).
 *
 * @note This has no affect on the code or compilation process, it is purely as a form of
 *       further documenting container types.
 *
 * @param type The type of the container.
 * @param va_args The element types inside the container.
 */
#define CC_CONTAINER(type, ...) CC_CONTAINER_(CC_VA_ARG_COUNT(__VA_ARGS__), type, __VA_ARGS__)

#define CC_CONTAINER_(n, type, ...) CC_CONTAINER__(CC_CONTAINER_TYPE_DISABLE, n)(type, __VA_ARGS__)
#define CC_CONTAINER__(enabled, n) CC_CONTAINER___(enabled)(n)
#define CC_CONTAINER___(enabled) CC_CONTAINER____##enabled
#define CC_CONTAINER____0(n) CC_CONTAINER_##n
#define CC_CONTAINER____1(n) CC_CONTAINER_DISABLED
#define CC_CONTAINER____(n) CC_CONTAINER_DISABLED
#define CC_CONTAINER____CC_CONTAINER_TYPE_DISABLE(n) CC_CONTAINER_##n
#define CC_CONTAINER_DISABLED(type, ...)                type
#define CC_CONTAINER_0(type)                            type
#define CC_CONTAINER_1(type, e1)                        type##_##e1
#define CC_CONTAINER_2(type, e1, e2)                    type##_##e1##_##e2
#define CC_CONTAINER_3(type, e1, e2, e3)                type##_##e1##_##e2##_##e3
#define CC_CONTAINER_4(type, e1, e2, e3, e4)            type##_##e1##_##e2##_##e3##_##e4
#define CC_CONTAINER_5(type, e1, e2, e3, e4, e5)        type##_##e1##_##e2##_##e3##_##e4##_##e5
#define CC_CONTAINER_6(type, e1, e2, e3, e4, e5, e6)    type##_##e1##_##e2##_##e3##_##e4##_##e5##_##e6

#ifdef CC_CONTAINER_DISABLE_PRESETS
#define CC_CONTAINER_DECLARE_PRESET_1(type) CC_CONTAINER_DECLARE_PRESET_##type
#define CC_CONTAINER_DECLARE_PRESET_2(type) CC_CONTAINER_DECLARE_PRESET_##type
#else

/*!
 * @define CC_CONTAINER_DECLARE_PRESET_1
 * @abstract Convenient macro to predefine all the main types as single element types for the container.
 * @param type The type of the container.
 */
#define CC_CONTAINER_DECLARE_PRESET_1(type) CC_TYPE_PRESETS(CC_CONTAINER_DECLARE, type)

/*!
 * @define CC_CONTAINER_DECLARE_PRESET_2
 * @abstract Convenient macro to predefine all the main types as double element types for the container.
 * @param type The type of the container.
 */
#define CC_CONTAINER_DECLARE_PRESET_2(type) CC_TYPE_PRESETS(CC_TYPE_PRESETS_, CC_CONTAINER_DECLARE, type)

#endif

#endif

#endif
