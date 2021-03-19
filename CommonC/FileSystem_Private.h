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

#define T size_t
#include "Extrema.h"

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

static CC_FORCE_INLINE void FSVirtualFileCreate(CC_NEW FSVirtualFile *File, size_t Count, void *Data);
static CC_FORCE_INLINE void FSVirtualFileDestroy(FSVirtualFile *CC_DESTROY(File));
static CC_FORCE_INLINE void FSVirtualFileReadLock(FSVirtualFile *File);
static CC_FORCE_INLINE void FSVirtualFileReadUnlock(FSVirtualFile *File);
static CC_FORCE_INLINE void FSVirtualFileWriteLock(FSVirtualFile *File);
static CC_FORCE_INLINE void FSVirtualFileWriteUnlock(FSVirtualFile *File);
static CC_FORCE_INLINE void FSVirtualFileRead(FSVirtualFile *File, size_t Offset, size_t *Count, void *Data);

#pragma mark -

static CC_FORCE_INLINE void FSVirtualFileCreate(FSVirtualFile *File, size_t Count, void *Data)
{
    File->refs = ATOMIC_VAR_INIT(0);
    File->contents = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(uint8_t), 128);
    
    if (Count) CCArrayAppendElements(File->contents, Data, Count);
}

static CC_FORCE_INLINE void FSVirtualFileDestroy(FSVirtualFile *File)
{
    CCArrayDestroy(File->contents);
}

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

static CC_FORCE_INLINE void FSVirtualFileRead(FSVirtualFile *File, size_t Offset, size_t *Count, void *Data)
{
    const size_t Size = CCArrayGetCount(File->contents);
    
    if (Offset < Size)
    {
        *Count = CCMin(Size - Offset, *Count);
        memcpy(Data, CCArrayGetData(File->contents) + Offset, *Count);
    }
    
    else *Count = 0;
}

#endif