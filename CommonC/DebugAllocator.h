/*
 *  Copyright (c) 2018, Stefan Johnson
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

#ifndef CommonC_DebugAllocator_h
#define CommonC_DebugAllocator_h

typedef struct {
    const char *file;
    int line;
} CCDebugAllocatorInfo;

void CCDebugAllocatorTrack(void *Ptr, CCDebugAllocatorInfo Info);
void CCDebugAllocatorTrackReplaced(void *OldPtr, void *NewPtr, CCDebugAllocatorInfo Info);
void CCDebugAllocatorUntrack(void *Ptr);
_Bool CCDebugAllocatorIsTracking(void *Ptr);
void CCDebugAllocatorPrint(void);

#define CC_TYPE_CCDebugAllocatorInfo(...) CCDebugAllocatorInfo
#define CC_TYPE_0_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_1_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_2_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_3_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_4_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_5_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_6_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_7_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_8_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,
#define CC_TYPE_9_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo,

#define CC_PRESERVE_CC_TYPE_CCDebugAllocatorInfo CC_TYPE_CCDebugAllocatorInfo

#define CC_TYPE_DECL_CCDebugAllocatorInfo(...) CCDebugAllocatorInfo, __VA_ARGS__
#define CC_TYPE_DECL_0_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_1_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_2_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_3_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_4_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_5_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_6_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_7_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_8_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,
#define CC_TYPE_DECL_9_CCDebugAllocatorInfo CC_TYPE_DECL_CCDebugAllocatorInfo,

#define CC_MANGLE_TYPE_0_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_1_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_2_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_3_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_4_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_5_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_6_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_7_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_8_CCDebugAllocatorInfo CCDebugAllocatorInfo
#define CC_MANGLE_TYPE_9_CCDebugAllocatorInfo CCDebugAllocatorInfo

#endif
