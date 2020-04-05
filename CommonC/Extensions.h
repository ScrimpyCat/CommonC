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
 No guarantee to portability with these defines. If unsupported it will just lack that functionality.
 
 Function extensions:
 CC_FORCE_INLINE: Forces the funtion to be inlined
 CC_NO_INLINE: Forces the function not to be inlined
 CC_DEPRECATED: Marks the function as deprecated
 CC_WARN_UNUSED_RESULT: Warn when the return result is unused
 CC_FORMAT_PRINTF(fmt, args): Treats the function usage as if the format and arguments followed that of printf's, and so will give warnings appropriately. fmt = index of the format string, args = the index of the arguments
 CC_FORMAT_SCANF(fmt, args): Treats the function usage as if the format and arguments followed that of scanf's, and so will give warnings appropriately. fmt = index of the format string, args = the index of the arguments
 CC_PURE_FUNCTION: Marks the function as having no side effects. Can help the compiler with optimization.
 CC_CONSTANT_FUNCTION: A more strict version of CC_PURE_FUNCTION, it does not allow pointer arguments or global variable access.
 
 Optional usage:
 CC_SUPPORT_BLOCKS(...): Allows for code specific to blocks to be used.
 */

#ifndef CommonC_Extensions_h
#define CommonC_Extensions_h

#include <CommonC/Platform.h>


#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#ifndef __has_feature
#define __has_feature(x) 0
#endif

#ifndef __has_extension
#define __has_extension(x) __has_feature(x)
#endif

#ifndef __has_c_attribute
#define __has_c_attribute(x) 0
#endif

#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

#if CC_COMPILER_CLANG || CC_COMPILER_GCC
#if __has_attribute(always_inline)
#define CC_FORCE_INLINE inline __attribute__((always_inline))
#endif

#if __has_attribute(noinline)
#define CC_NO_INLINE __attribute__((noinline))
#endif

#if __has_attribute(deprecated)
#define CC_DEPRECATED __attribute__((deprecated))
#endif

#if __has_attribute(warn_unused_result)
#define CC_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#endif

#if __has_attribute(format)
#define CC_FORMAT_PRINTF(fmt, args) __attribute__((format(printf, fmt, args)))
#endif

#if __has_attribute(format)
#define CC_FORMAT_SCANF(fmt, args) __attribute__((format(scanf, fmt, args)))
#endif

#if __has_attribute(pure)
#define CC_PURE_FUNCTION __attribute__((pure))
#endif

#if __has_attribute(const)
#define CC_CONSTANT_FUNCTION __attribute__((const))
#endif

#if __has_builtin(__builtin_expect) || defined(__builtin_expect)
#define CC_LIKELY(e) __builtin_expect(!!(e), 1)
#define CC_UNLIKELY(e) __builtin_expect(!!(e), 0)
#endif

#if __has_attribute(packed)
#define CC_PACKED __attribute__((packed))
#endif

#if __has_attribute(constructor)
#define CC_CONSTRUCTOR __attribute__((constructor))
#endif

#if __has_attribute(destructor)
#define CC_DESTRUCTOR __attribute__((destructor))
#endif

#if __has_attribute(enum_extensibility)
#define CC_OPEN_ENUM __attribute__((enum_extensibility(open)))
#define CC_CLOSED_ENUM __attribute__((enum_extensibility(closed)))
#define CC_OPEN_FLAG_ENUM __attribute__((enum_extensibility(open), flag_enum))
#define CC_CLOSED_FLAG_ENUM __attribute__((enum_extensibility(closed), flag_enum))
#endif
#endif

#ifndef CC_FORCE_INLINE
#define CC_FORCE_INLINE inline
#endif

#ifndef CC_NO_INLINE
#define CC_NO_INLINE
#endif

#ifndef CC_DEPRECATED
#define CC_DEPRECATED
#endif

#ifndef CC_WARN_UNUSED_RESULT
#define CC_WARN_UNUSED_RESULT
#endif

#ifndef CC_FORMAT_PRINTF
#define CC_FORMAT_PRINTF(fmt, args)
#endif

#ifndef CC_FORMAT_SCANF
#define CC_FORMAT_SCANF(fmt, args)
#endif

#ifndef CC_PURE_FUNCTION
#define CC_PURE_FUNCTION
#endif

#ifndef CC_CONSTANT_FUNCTION
#define CC_CONSTANT_FUNCTION
#endif

#ifndef CC_LIKELY
#define CC_LIKELY(e) (!!(e) == 1)
#endif

#ifndef CC_UNLIKELY
#define CC_UNLIKELY(e) (!!(e) == 0)
#endif

#ifndef CC_PACKED
#define CC_PACKED
#endif

#ifndef CC_CONSTRUCTOR
#define CC_CONSTRUCTOR
#endif

#ifndef CC_DESTRUCTOR
#define CC_DESTRUCTOR
#endif

#ifndef CC_OPEN_ENUM
#define CC_OPEN_ENUM
#define CC_CLOSED_ENUM
#define CC_OPEN_FLAG_ENUM
#define CC_CLOSED_FLAG_ENUM
#endif

#if __BLOCKS__
#define CC_SUPPORT_BLOCKS(...) __VA_ARGS__
#else
#define CC_SUPPORT_BLOCKS(...)
#endif


#if __clang_major__ >= 6 && __clang_minor__ >= 1 //or should check? __apple_build_version__ > 6000056
#define CC_NONNULL __nonnull
#define CC_NULLABLE __nullable
#define CC_NULL_UNSPECIFIED __null_unspecified

#define CC_PROPERTY_NONNULL nonnull
#define CC_PROPERTY_NULLABLE nullable
#define CC_PROPERTY_NULL_RESETTABLE null_resettable

#define CC_NOESCAPE __attribute__((noescape))
#else
#define CC_NONNULL
#define CC_NULLABLE
#define CC_NULL_UNSPECIFIED

#define CC_PROPERTY_NONNULL
#define CC_PROPERTY_NULLABLE
#define CC_PROPERTY_NULL_RESETTABLE

#define CC_NOESCAPE
#endif


#if __has_builtin(__builtin_nontemporal_load) || defined(__builtin_nontemporal_load)
#define CC_NON_TEMPORAL_LOAD(addr) __builtin_nontemporal_load(addr)
#else
#define CC_NON_TEMPORAL_LOAD(addr) *(addr)
#endif

#if __has_builtin(__builtin_nontemporal_store) || defined(__builtin_nontemporal_store)
#define CC_NON_TEMPORAL_STORE(value, addr) __builtin_nontemporal_store(value, addr)
#else
#define CC_NON_TEMPORAL_STORE(value, addr) *(addr) = value
#endif

#if __has_builtin(__builtin_available) || defined(__builtin_available)
#if __OBJC__
#define CC_AVAILABLE(...) @available(__VA_ARGS__)
#else
#define CC_AVAILABLE(...) __builtin_available(__VA_ARGS__)
#endif
#else
#define CC_AVAILABLE(...) 0
#endif

#if !defined(CC_DEFAULT_ENUM) && (__has_feature(objc_fixed_enum) || __cplusplus)
#if __cplusplus
#define CC_ENUM_DECLARE_NAMED(name, type, attr) type name; enum attr : type
#else
#define CC_ENUM_DECLARE_NAMED(name, type, attr) enum name : type name; enum attr name : type
#define CC_ENUM_DECLARE_NAMED_IMPLICIT(name, type, attr) type name; enum attr
#endif

#define CC_ENUM_DECLARE_UNNAMED(type, attr) enum attr : type
#else
#ifdef CC_DEFAULT_ENUM
#define CC_ENUM_DECLARE_NAMED(name, type, attr) enum name name; enum attr name
#else
#define CC_ENUM_DECLARE_NAMED(name, type, attr) type name; enum attr
#define CC_ENUM_DECLARE_NAMED_IMPLICIT(name, type, attr) type name; enum attr
#endif

#define CC_ENUM_DECLARE_UNNAMED(type, attr) enum attr
#endif

#define CC_ENUM_DECLARE(_1, _2, name, ...) name

#if defined(CC_DEFAULT_ENUM) && !defined(CC_NO_IMPLICIT_ENUM)
#define CC_NO_IMPLICIT_ENUM
#endif

/*!
 * @define CC_EXTENSIBLE_ENUM
 * @brief Declare an extensible custom width enum.
 * @description This should take the form of @b CC_EXTENSIBLE_ENUM(type) or @b typedef @b CC_EXTENSIBLE_ENUM(name, type).
 *              The custom width can be disabled by defining @b CC_DEFAULT_ENUM. Implicit conversion support can be disabled by
 *              defining @b CC_NO_IMPLICIT_ENUM or when @b CC_DEFAULT_ENUM is used.
 */
#ifdef CC_NO_IMPLICIT_ENUM
#define CC_EXTENSIBLE_ENUM(...) CC_ENUM_DECLARE(__VA_ARGS__, CC_ENUM_DECLARE_NAMED, CC_ENUM_DECLARE_UNNAMED)(__VA_ARGS__, CC_OPEN_ENUM)
#else
#define CC_EXTENSIBLE_ENUM(...) CC_ENUM_DECLARE(__VA_ARGS__, CC_ENUM_DECLARE_NAMED_IMPLICIT, CC_ENUM_DECLARE_UNNAMED)(__VA_ARGS__, CC_OPEN_ENUM)
#endif

/*!
 * @define CC_EXTENSIBLE_FLAG_ENUM
 * @brief Declare an extensible custom width enum.
 * @description This should take the form of @b CC_EXTENSIBLE_FLAG_ENUM(type) or @b typedef @b CC_EXTENSIBLE_FLAG_ENUM(name, type).
 *              The custom width can be disabled by defining @b CC_DEFAULT_ENUM. Implicit conversion support can be disabled by
 *              defining @b CC_NO_IMPLICIT_ENUM or when @b CC_DEFAULT_ENUM is used.
 */
#ifdef CC_NO_IMPLICIT_ENUM
#define CC_EXTENSIBLE_FLAG_ENUM(...) CC_ENUM_DECLARE(__VA_ARGS__, CC_ENUM_DECLARE_NAMED, CC_ENUM_DECLARE_UNNAMED)(__VA_ARGS__, CC_OPEN_FLAG_ENUM)
#else
#define CC_EXTENSIBLE_FLAG_ENUM(...) CC_ENUM_DECLARE(__VA_ARGS__, CC_ENUM_DECLARE_NAMED_IMPLICIT, CC_ENUM_DECLARE_UNNAMED)(__VA_ARGS__, CC_OPEN_FLAG_ENUM)
#endif

/*!
 * @define CC_ENUM
 * @brief Declare a custom width enum.
 * @description This should take the form of @b CC_ENUM(type) or @b typedef @b CC_ENUM(name, type).
 *              The custom width can be disabled by defining @b CC_DEFAULT_ENUM.
 */
#define CC_ENUM(...) CC_ENUM_DECLARE(__VA_ARGS__, CC_ENUM_DECLARE_NAMED, CC_ENUM_DECLARE_UNNAMED)(__VA_ARGS__, CC_CLOSED_ENUM)

/*!
 * @define CC_FLAG_ENUM
 * @brief Declare a custom width flag enum.
 * @description This should take the form of @b CC_FLAG_ENUM(type) or @b typedef @b CC_FLAG_ENUM(name, type).
 *              The custom width can be disabled by defining @b CC_DEFAULT_ENUM.
 */
#define CC_FLAG_ENUM(...) CC_ENUM_DECLARE(__VA_ARGS__, CC_ENUM_DECLARE_NAMED, CC_ENUM_DECLARE_UNNAMED)(__VA_ARGS__, CC_CLOSED_FLAG_ENUM)

/*!
 * @define CC_SPIN_WAIT
 * @brief Attempts to optimize a spin-wait loop (or similarly tightly contested high CPU waste situations).
 * @description PAUSE instruction on X86 architectures supporting SSE2 handles this particular case. ARM
 *              provides the YIELD instruction however the better approach would be to structure a spinlock
 *              using the wait-for-event behaviour (WFE and SEV).
 */
#if CC_HARDWARE_ARCH_X86 || CC_HARDWARE_ARCH_X86_64

#if CC_HARDWARE_VECTOR_SUPPORT_SSE2
#include <emmintrin.h>

#define CC_SPIN_WAIT() _mm_pause()
#endif

#elif CC_HARDWARE_ARCH_ARM || CC_HARDWARE_ARCH_ARM_64

#ifndef __ARM_ACLE
#warning Yield will be a no-op as ACLE intrinsics support not enabled.
#else
#include <arm_acle.h>

#define CC_SPIN_WAIT() __yield()
#endif

#endif

#ifndef CC_SPIN_WAIT
#define CC_SPIN_WAIT()
#endif

#endif
