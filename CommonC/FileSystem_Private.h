/*
 *  Copyright (c) 2021, Stefan Johnson
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

#ifndef CommonC_FileSystem_Private_h
#define CommonC_FileSystem_Private_h

#include "FileSystem.h"
#include "Array.h"
#include "CCString.h"
#include "Dictionary.h"

// TODO: Convert this to a more optimal structure
typedef struct {
    CCArray(uint8_t) contents;
    _Atomic(uint32_t) refs;
} FSVirtualFile;

#define FS_VIRTUAL_FILE_WRITE_FLAG 0x80000000F

CC_DICTIONARY_DECLARE(CCString, FSVirtualNode);

typedef struct {
    union {
        CCDictionary(CCString, FSVirtualNode) nodes;
        FSVirtualFile file;
    };
    _Bool isDir;
} FSVirtualNode;

typedef struct {
    FSVirtualFile *file;
    size_t offset;
} FSVirtualFileHandle;

#pragma mark -

static CC_FORCE_INLINE void FSVirtualFileReadLock(FSVirtualFile *File)
{
    uint32_t Ref;
    
    do {
        while ((Ref = atomic_load_explicit(&File->refs, memory_order_relaxed)) & FS_VIRTUAL_FILE_WRITE_FLAG) CC_SPIN_WAIT();
    } while (!atomic_compare_exchange_weak_explicit(&File->refs, &Ref, Ref + 1, memory_order_acquire, memory_order_relaxed));
}

static CC_FORCE_INLINE void FSVirtualFileReadUnlock(FSVirtualFile *File)
{
    const uint32_t Ref = atomic_fetch_sub_explicit(&File->refs, 1, memory_order_release);
    
    CCAssertLog(!(Ref & FS_VIRTUAL_FILE_WRITE_FLAG), "Unlocking a write lock");
}

static CC_FORCE_INLINE void FSVirtualFileWriteLock(FSVirtualFile *File)
{
    while (!atomic_compare_exchange_weak_explicit(&File->refs, (&(uint32_t){ 0 }), FS_VIRTUAL_FILE_WRITE_FLAG, memory_order_acquire, memory_order_relaxed));
}

static CC_FORCE_INLINE void FSVirtualFileWriteUnlock(FSVirtualFile *File)
{
    const uint32_t Ref = atomic_fetch_xor_explicit(&File->refs, FS_VIRTUAL_FILE_WRITE_FLAG, memory_order_release);
    
    CCAssertLog(Ref & FS_VIRTUAL_FILE_WRITE_FLAG, "Unlocking a read lock");
}

#endif
