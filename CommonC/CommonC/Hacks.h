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
 For code that is on the more hackish side and waiting for better alternatives to change to. The majority of this is for internal use by the framework to provide
 consistency depending on what functionality is available.
 
 CC_SILENCE_UNUSED_WARNING: Silences the unused value/variable warning where it would otherwise not be appropriate or sometimes even able to use a compiler extension.
 */

#ifndef CommonC_Hacks_h
#define CommonC_Hacks_h

#include <CommonC/Extensions.h>
#include <CommonC/Generics.h>


#define CC_NAME_RETURN_VALUE_FUNCTION_(name) CCGenericReturnValue_##name##_
#define CC_GENERATE_RETURN_VALUE_FUNCTION_(name, type) static CC_FORCE_INLINE type CC_NAME_RETURN_VALUE_FUNCTION_(name)(type val){ return val; }
#define CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(name, type) type: CC_NAME_RETURN_VALUE_FUNCTION_(name)

CC_GENERATE_RETURN_VALUE_FUNCTION_(char, char)
CC_GENERATE_RETURN_VALUE_FUNCTION_(short, short)
CC_GENERATE_RETURN_VALUE_FUNCTION_(int, int)
CC_GENERATE_RETURN_VALUE_FUNCTION_(long, long)
CC_GENERATE_RETURN_VALUE_FUNCTION_(long_long, long long)
CC_GENERATE_RETURN_VALUE_FUNCTION_(float, float)
CC_GENERATE_RETURN_VALUE_FUNCTION_(double, double)
CC_GENERATE_RETURN_VALUE_FUNCTION_(long_double, long double)
CC_GENERATE_RETURN_VALUE_FUNCTION_(void_ptr, void*)

#define CC_SILENCE_UNUSED_WARNING(val) (CC_GENERIC_EVALUATE(val, \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(char, char), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(short, short), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(int, int), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(long, long), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(long_long, long long), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(float, float), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(double, double), \
CC_GENERIC_ATTRIBUTE_RETURN_VALUE_FUNCTION_(long_double, long double), \
default: CC_NAME_RETURN_VALUE_FUNCTION_(void_ptr) \
))(val)


#endif
