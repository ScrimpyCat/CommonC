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

#include <CommonC/Generics.h>

#define CCMin(a, b) CCMin_Ref(a, b)(a, b)
#define CCMax(a, b) CCMax_Ref(a, b)(a, b)
#define CCClamp(val, min, max) CCClamp_Ref(val, min, max)(val, min, max)

#define CCMin_Ref(a, b) CC_GENERIC_1(((typeof(a)){0}), CCMin_T, CCMin_T_0)
#define CCMax_Ref(a, b) CC_GENERIC_1(((typeof(a)){0}), CCMax_T, CCMax_T_0)
#define CCClamp_Ref(val, min, max) CC_GENERIC_1(((typeof(val)){0}), CCClamp_T, CCClamp_T_0)

#define CCMin_T_0 CC_GENERIC_INDEXED_TYPE_LIST(CC_EXTREMA_T, CC_EXTREMA_COUNT)
#define CCMax_T_0 CC_GENERIC_INDEXED_TYPE_LIST(CC_EXTREMA_T, CC_EXTREMA_COUNT)
#define CCClamp_T_0 CC_GENERIC_INDEXED_TYPE_LIST(CC_EXTREMA_T, CC_EXTREMA_COUNT)

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_CC_EXTREMA_T0 CC_EXTREMA_T0
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_CC_EXTREMA_T1 CC_EXTREMA_T1
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_CC_EXTREMA_T2 CC_EXTREMA_T2
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_CC_EXTREMA_T3 CC_EXTREMA_T3
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_CC_EXTREMA_T4 CC_EXTREMA_T4
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_CC_EXTREMA_T5 CC_EXTREMA_T5
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_CC_EXTREMA_T6 CC_EXTREMA_T6
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_CC_EXTREMA_T7 CC_EXTREMA_T7
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_CC_EXTREMA_T8 CC_EXTREMA_T8
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_CC_EXTREMA_T9 CC_EXTREMA_T9
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_CC_EXTREMA_T10 CC_EXTREMA_T10
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_CC_EXTREMA_T11 CC_EXTREMA_T11
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_CC_EXTREMA_T12 CC_EXTREMA_T12
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_CC_EXTREMA_T13 CC_EXTREMA_T13
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_CC_EXTREMA_T14 CC_EXTREMA_T14
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_CC_EXTREMA_T15 CC_EXTREMA_T15
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_CC_EXTREMA_T16 CC_EXTREMA_T16
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_CC_EXTREMA_T17 CC_EXTREMA_T17
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_CC_EXTREMA_T18 CC_EXTREMA_T18
#endif

#ifndef CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_CC_EXTREMA_T19 CC_EXTREMA_T19
#endif

#define CC_MANGLE_TYPE_0_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T0 CC_MANGLE_TYPE_CC_EXTREMA_T0
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T1 CC_MANGLE_TYPE_CC_EXTREMA_T1
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T2 CC_MANGLE_TYPE_CC_EXTREMA_T2
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T3 CC_MANGLE_TYPE_CC_EXTREMA_T3
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T4 CC_MANGLE_TYPE_CC_EXTREMA_T4
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T5 CC_MANGLE_TYPE_CC_EXTREMA_T5
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T6 CC_MANGLE_TYPE_CC_EXTREMA_T6
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T7 CC_MANGLE_TYPE_CC_EXTREMA_T7
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T8 CC_MANGLE_TYPE_CC_EXTREMA_T8
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T9 CC_MANGLE_TYPE_CC_EXTREMA_T9
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T10 CC_MANGLE_TYPE_CC_EXTREMA_T10
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T11 CC_MANGLE_TYPE_CC_EXTREMA_T11
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T12 CC_MANGLE_TYPE_CC_EXTREMA_T12
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T13 CC_MANGLE_TYPE_CC_EXTREMA_T13
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T14 CC_MANGLE_TYPE_CC_EXTREMA_T14
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T15 CC_MANGLE_TYPE_CC_EXTREMA_T15
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T16 CC_MANGLE_TYPE_CC_EXTREMA_T16
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T17 CC_MANGLE_TYPE_CC_EXTREMA_T17
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T18 CC_MANGLE_TYPE_CC_EXTREMA_T18
#define CC_MANGLE_TYPE_0_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_1_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_2_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_3_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_4_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_5_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_6_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_7_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_8_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19
#define CC_MANGLE_TYPE_9_CC_EXTREMA_T19 CC_MANGLE_TYPE_CC_EXTREMA_T19

#ifdef CC_EXTREMA_COUNT
#define CC_GENERIC_COUNT CC_EXTREMA_COUNT
#endif

#undef CC_GENERIC_TYPE
#undef CC_GENERIC_TEMPLATE
#define CC_GENERIC_TYPE CC_EXTREMA
#define CC_GENERIC_TEMPLATE <CommonC/ExtremaTemplate.h>
#include <CommonC/Generic.h>

#if CC_GENERIC_COUNT < 1
#undef CC_MANGLE_TYPE_CC_EXTREMA_T0
#endif

#if CC_GENERIC_COUNT < 2
#undef CC_MANGLE_TYPE_CC_EXTREMA_T1
#endif

#if CC_GENERIC_COUNT < 3
#undef CC_MANGLE_TYPE_CC_EXTREMA_T2
#endif

#if CC_GENERIC_COUNT < 4
#undef CC_MANGLE_TYPE_CC_EXTREMA_T3
#endif

#if CC_GENERIC_COUNT < 5
#undef CC_MANGLE_TYPE_CC_EXTREMA_T4
#endif

#if CC_GENERIC_COUNT < 6
#undef CC_MANGLE_TYPE_CC_EXTREMA_T5
#endif

#if CC_GENERIC_COUNT < 7
#undef CC_MANGLE_TYPE_CC_EXTREMA_T6
#endif

#if CC_GENERIC_COUNT < 8
#undef CC_MANGLE_TYPE_CC_EXTREMA_T7
#endif

#if CC_GENERIC_COUNT < 9
#undef CC_MANGLE_TYPE_CC_EXTREMA_T8
#endif

#if CC_GENERIC_COUNT < 10
#undef CC_MANGLE_TYPE_CC_EXTREMA_T9
#endif

#if CC_GENERIC_COUNT < 11
#undef CC_MANGLE_TYPE_CC_EXTREMA_T10
#endif

#if CC_GENERIC_COUNT < 12
#undef CC_MANGLE_TYPE_CC_EXTREMA_T11
#endif

#if CC_GENERIC_COUNT < 13
#undef CC_MANGLE_TYPE_CC_EXTREMA_T12
#endif

#if CC_GENERIC_COUNT < 14
#undef CC_MANGLE_TYPE_CC_EXTREMA_T13
#endif

#if CC_GENERIC_COUNT < 15
#undef CC_MANGLE_TYPE_CC_EXTREMA_T14
#endif

#if CC_GENERIC_COUNT < 16
#undef CC_MANGLE_TYPE_CC_EXTREMA_T15
#endif

#if CC_GENERIC_COUNT < 17
#undef CC_MANGLE_TYPE_CC_EXTREMA_T16
#endif

#if CC_GENERIC_COUNT < 18
#undef CC_MANGLE_TYPE_CC_EXTREMA_T17
#endif

#if CC_GENERIC_COUNT < 19
#undef CC_MANGLE_TYPE_CC_EXTREMA_T18
#endif

#if CC_GENERIC_COUNT < 20
#undef CC_MANGLE_TYPE_CC_EXTREMA_T19
#endif

#undef CC_EXTREMA_COUNT

#if CC_GENERIC_COUNT == 1
#define CC_EXTREMA_COUNT 1
#elif CC_GENERIC_COUNT == 2
#define CC_EXTREMA_COUNT 2
#elif CC_GENERIC_COUNT == 3
#define CC_EXTREMA_COUNT 3
#elif CC_GENERIC_COUNT == 4
#define CC_EXTREMA_COUNT 4
#elif CC_GENERIC_COUNT == 5
#define CC_EXTREMA_COUNT 5
#elif CC_GENERIC_COUNT == 6
#define CC_EXTREMA_COUNT 6
#elif CC_GENERIC_COUNT == 7
#define CC_EXTREMA_COUNT 7
#elif CC_GENERIC_COUNT == 8
#define CC_EXTREMA_COUNT 8
#elif CC_GENERIC_COUNT == 9
#define CC_EXTREMA_COUNT 9
#elif CC_GENERIC_COUNT == 10
#define CC_EXTREMA_COUNT 10
#elif CC_GENERIC_COUNT == 11
#define CC_EXTREMA_COUNT 11
#elif CC_GENERIC_COUNT == 12
#define CC_EXTREMA_COUNT 12
#elif CC_GENERIC_COUNT == 13
#define CC_EXTREMA_COUNT 13
#elif CC_GENERIC_COUNT == 14
#define CC_EXTREMA_COUNT 14
#elif CC_GENERIC_COUNT == 15
#define CC_EXTREMA_COUNT 15
#elif CC_GENERIC_COUNT == 16
#define CC_EXTREMA_COUNT 16
#elif CC_GENERIC_COUNT == 17
#define CC_EXTREMA_COUNT 17
#elif CC_GENERIC_COUNT == 18
#define CC_EXTREMA_COUNT 18
#elif CC_GENERIC_COUNT == 19
#define CC_EXTREMA_COUNT 19
#elif CC_GENERIC_COUNT == 20
#define CC_EXTREMA_COUNT 20
#else
#error Add additional cases
#endif

#undef CC_GENERIC_COUNT

#define CC_TYPE_CC_EXTREMA_T0(...) CC_EXTREMA_T0
#define CC_TYPE_CC_EXTREMA_T1(...) CC_EXTREMA_T1
#define CC_TYPE_CC_EXTREMA_T2(...) CC_EXTREMA_T2
#define CC_TYPE_CC_EXTREMA_T3(...) CC_EXTREMA_T3
#define CC_TYPE_CC_EXTREMA_T4(...) CC_EXTREMA_T4
#define CC_TYPE_CC_EXTREMA_T5(...) CC_EXTREMA_T5
#define CC_TYPE_CC_EXTREMA_T6(...) CC_EXTREMA_T6
#define CC_TYPE_CC_EXTREMA_T7(...) CC_EXTREMA_T7
#define CC_TYPE_CC_EXTREMA_T8(...) CC_EXTREMA_T8
#define CC_TYPE_CC_EXTREMA_T9(...) CC_EXTREMA_T9
#define CC_TYPE_CC_EXTREMA_T10(...) CC_EXTREMA_T10
#define CC_TYPE_CC_EXTREMA_T11(...) CC_EXTREMA_T11
#define CC_TYPE_CC_EXTREMA_T12(...) CC_EXTREMA_T12
#define CC_TYPE_CC_EXTREMA_T13(...) CC_EXTREMA_T13
#define CC_TYPE_CC_EXTREMA_T14(...) CC_EXTREMA_T14
#define CC_TYPE_CC_EXTREMA_T15(...) CC_EXTREMA_T15
#define CC_TYPE_CC_EXTREMA_T16(...) CC_EXTREMA_T16
#define CC_TYPE_CC_EXTREMA_T17(...) CC_EXTREMA_T17
#define CC_TYPE_CC_EXTREMA_T18(...) CC_EXTREMA_T18
#define CC_TYPE_CC_EXTREMA_T19(...) CC_EXTREMA_T19
#define CC_TYPE_0_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_1_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_2_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_3_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_4_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_5_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_6_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_7_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_8_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_9_CC_EXTREMA_T0 CC_TYPE_CC_EXTREMA_T0,
#define CC_TYPE_0_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_1_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_2_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_3_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_4_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_5_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_6_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_7_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_8_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_9_CC_EXTREMA_T1 CC_TYPE_CC_EXTREMA_T1,
#define CC_TYPE_0_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_1_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_2_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_3_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_4_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_5_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_6_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_7_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_8_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_9_CC_EXTREMA_T2 CC_TYPE_CC_EXTREMA_T2,
#define CC_TYPE_0_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_1_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_2_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_3_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_4_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_5_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_6_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_7_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_8_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_9_CC_EXTREMA_T3 CC_TYPE_CC_EXTREMA_T3,
#define CC_TYPE_0_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_1_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_2_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_3_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_4_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_5_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_6_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_7_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_8_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_9_CC_EXTREMA_T4 CC_TYPE_CC_EXTREMA_T4,
#define CC_TYPE_0_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_1_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_2_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_3_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_4_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_5_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_6_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_7_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_8_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_9_CC_EXTREMA_T5 CC_TYPE_CC_EXTREMA_T5,
#define CC_TYPE_0_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_1_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_2_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_3_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_4_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_5_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_6_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_7_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_8_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_9_CC_EXTREMA_T6 CC_TYPE_CC_EXTREMA_T6,
#define CC_TYPE_0_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_1_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_2_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_3_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_4_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_5_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_6_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_7_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_8_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_9_CC_EXTREMA_T7 CC_TYPE_CC_EXTREMA_T7,
#define CC_TYPE_0_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_1_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_2_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_3_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_4_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_5_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_6_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_7_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_8_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_9_CC_EXTREMA_T8 CC_TYPE_CC_EXTREMA_T8,
#define CC_TYPE_0_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_1_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_2_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_3_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_4_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_5_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_6_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_7_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_8_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_9_CC_EXTREMA_T9 CC_TYPE_CC_EXTREMA_T9,
#define CC_TYPE_0_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_1_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_2_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_3_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_4_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_5_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_6_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_7_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_8_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_9_CC_EXTREMA_T10 CC_TYPE_CC_EXTREMA_T10,
#define CC_TYPE_0_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_1_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_2_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_3_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_4_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_5_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_6_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_7_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_8_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_9_CC_EXTREMA_T11 CC_TYPE_CC_EXTREMA_T11,
#define CC_TYPE_0_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_1_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_2_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_3_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_4_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_5_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_6_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_7_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_8_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_9_CC_EXTREMA_T12 CC_TYPE_CC_EXTREMA_T12,
#define CC_TYPE_0_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_1_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_2_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_3_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_4_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_5_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_6_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_7_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_8_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_9_CC_EXTREMA_T13 CC_TYPE_CC_EXTREMA_T13,
#define CC_TYPE_0_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_1_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_2_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_3_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_4_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_5_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_6_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_7_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_8_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_9_CC_EXTREMA_T14 CC_TYPE_CC_EXTREMA_T14,
#define CC_TYPE_0_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_1_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_2_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_3_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_4_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_5_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_6_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_7_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_8_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_9_CC_EXTREMA_T15 CC_TYPE_CC_EXTREMA_T15,
#define CC_TYPE_0_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_1_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_2_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_3_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_4_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_5_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_6_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_7_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_8_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_9_CC_EXTREMA_T16 CC_TYPE_CC_EXTREMA_T16,
#define CC_TYPE_0_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_1_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_2_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_3_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_4_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_5_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_6_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_7_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_8_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_9_CC_EXTREMA_T17 CC_TYPE_CC_EXTREMA_T17,
#define CC_TYPE_0_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_1_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_2_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_3_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_4_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_5_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_6_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_7_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_8_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_9_CC_EXTREMA_T18 CC_TYPE_CC_EXTREMA_T18,
#define CC_TYPE_0_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_1_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_2_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_3_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_4_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_5_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_6_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_7_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_8_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
#define CC_TYPE_9_CC_EXTREMA_T19 CC_TYPE_CC_EXTREMA_T19,
