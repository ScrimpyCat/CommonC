/*
 *  Copyright (c) 2015, Stefan Johnson
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

#define CC_QUICK_COMPILE
#include "FileHandle.h"
#include "Platform.h"
#include "Assertion.h"
#include "MemoryAllocation.h"
#include "Logging.h"

#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
//SystemPath.m
#elif CC_PLATFORM_UNIX
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ftw.h>
#elif CC_PLATFORM_WINDOWS
#error Add support for windows
#else
#warning Unsupported platform
#endif


#if CC_PLATFORM_UNIX

static const char *FSPathSystemInternalRepresentation(FSPath Path)
{
    CCAssertLog(FSPathComponentGetType(FSPathGetComponentAtIndex(Path, 0)) != FSPathComponentTypeVolume, "Currently does not support resolving volumes");
    
    return FSPathGetPathString(Path); //TODO: Need to handle resolving of volumes
}

FSOperation FSHandleOpen(FSPath Path, FSHandleType Type, FSHandle *Handle)
{
    CCAssertLog(Path, "Path must not be null");
    CCAssertLog(Handle, "Handle must not be null");
    
    if (FSManagerExists(Path))
    {
        const char *SystemPath = FSPathSystemInternalRepresentation(Path);
        FILE *File = NULL;
        
        if (Type == FSHandleTypeRead) File = fopen(SystemPath, "r");
        else if (Type == FSHandleTypeWrite) File = fopen(SystemPath, "r+");
        else if (Type == FSHandleTypeUpdate) File = fopen(SystemPath, "r+");
        
        if (!File) return FSOperationFailure;
        
        CC_SAFE_Malloc(*Handle, sizeof(FSHandleInfo),
                       CC_LOG_ERROR("Failed to open file handle due to memory allocation failure. Allocation size (%zu)", sizeof(FSHandleInfo));
                       fclose(File);
                       return FSOperationFailure;
                       );
        
        **Handle = (FSHandleInfo){
            .type = Type,
            .path = FSPathCopy(Path),
            .handle = File
        };
        
        return FSOperationSuccess;
    }
    
    return FSOperationPathNotExist;
}

FSOperation FSHandleClose(FSHandle Handle)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if (!Handle->handle) return FSOperationFailure;
    
    FSPathDestroy(Handle->path);
    
    fclose(Handle->handle);
    
    CC_SAFE_Free(Handle);
    
    return FSOperationSuccess;
}

FSOperation FSHandleSync(FSHandle Handle)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if (!Handle->handle) return FSOperationFailure;
    
#if CC_PLATFORM_POSIX_COMPLIANT
    return !fsync(FSHandleGetFileDescriptor(Handle)) ? FSOperationSuccess : FSOperationFailure;
#else
    return !fflush(Handle->handle) ? FSOperationSuccess : FSOperationFailure;
#endif
}

FSOperation FSHandleRead(FSHandle Handle, size_t *Count, void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Handle, "Handle must not be null");
    CCAssertLog(Count, "Count must not be null");
    CCAssertLog(Data, "Data must not be null");
    
    if ((!Handle->handle) || (Handle->type == FSHandleTypeWrite))
    {
        *Count = 0;
        return FSOperationFailure;
    }
    
    const size_t Offset = FSHandleGetOffset(Handle);
    
    *Count = fread(Data, 1, *Count, Handle->handle);
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, Offset);
    else if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourUpdateOffset) return FSHandleSetOffset(Handle, Offset + *Count);
    
    return FSOperationSuccess;
}

FSOperation FSHandleReadFromOffset(FSHandle Handle, size_t Offset, size_t *Count, void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Handle, "Handle must not be null");
    CCAssertLog(Count, "Count must not be null");
    CCAssertLog(Data, "Data must not be null");
    
    if (!Handle->handle)
    {
        *Count = 0;
        return FSOperationFailure;
    }
    
    const size_t OldOffset = FSHandleGetOffset(Handle);
    
    FSHandleSetOffset(Handle, Offset);
    FSOperation Result = FSHandleRead(Handle, Count, Data, Behaviour);
    
    if ((Result == FSOperationSuccess) && ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset)) return FSHandleSetOffset(Handle, OldOffset);
    
    return Result;
}

FSOperation FSHandleWrite(FSHandle Handle, size_t Count, const void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Handle, "Handle must not be null");
    CCAssertLog(Data, "Data must not be null");
    
    if ((!Handle->handle) || (Handle->type == FSHandleTypeRead)) return FSOperationFailure;
    
    const size_t Offset = FSHandleGetOffset(Handle);
    
    if ((Behaviour & FSWritingBehaviourDestructiveMask) == FSWritingBehaviourOverwrite)
    {
        fwrite(Data, Count, 1, Handle->handle);
    }
    
    else if ((Behaviour & FSWritingBehaviourDestructiveMask) == FSWritingBehaviourInsert)
    {
        if (Handle->type != FSHandleTypeUpdate) return FSOperationFailure;
        
        size_t ChunkSize = FSManagerGetPreferredIOBlockSize(Handle->path);
        if (Count > ChunkSize) ChunkSize = Count;
        
        const size_t Size = FSManagerGetSize(Handle->path) - Offset;
        void *Chunk, *NextChunk;
        CC_SAFE_Malloc(Chunk, ChunkSize,
                       return FSOperationFailure;
                       );
        
        CC_SAFE_Malloc(NextChunk, ChunkSize,
                       CC_SAFE_Free(Chunk);
                       return FSOperationFailure;
                       );
        
        size_t ChunkLength = ChunkSize;
        FSHandleRead(Handle, &ChunkLength, Chunk, FSBehaviourPreserveOffset);
        
        fwrite(Data, Count, 1, Handle->handle);
        
        for (size_t Shifted = 0; Shifted < Size; )
        {
            FSHandleSetOffset(Handle, Offset + Shifted + Count);
            
            size_t NextChunkLength = 0;
            if (Shifted + ChunkLength < Size)
            {
                NextChunkLength = ChunkSize;
                FSHandleRead(Handle, &NextChunkLength, NextChunk, FSBehaviourPreserveOffset);
            }
            
            fwrite(Chunk, ChunkLength, 1, Handle->handle);
            
            Shifted += ChunkLength;
            
            ChunkLength = NextChunkLength;
            
            void *Temp = Chunk;
            Chunk = NextChunk;
            NextChunk = Temp;
        }
        
        CC_SAFE_Free(Chunk);
        CC_SAFE_Free(NextChunk);
    }
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, Offset);
    else if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourUpdateOffset) return FSHandleSetOffset(Handle, Offset + Count);
    
    return FSOperationSuccess;
}

FSOperation FSHandleWriteFromOffset(FSHandle Handle, size_t Offset, size_t Count, const void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Handle, "Handle must not be null");
    CCAssertLog(Data, "Data must not be null");
    
    if (!Handle->handle) return FSOperationFailure;
    
    const size_t OldOffset = FSHandleGetOffset(Handle);
    
    FSHandleSetOffset(Handle, Offset);
    FSOperation Result = FSHandleWrite(Handle, Count, Data, Behaviour);
    
    if ((Result == FSOperationSuccess) && ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset)) return FSHandleSetOffset(Handle, OldOffset);
    
    return Result;
}

FSOperation FSHandleRemove(FSHandle Handle, size_t Count, FSBehaviour Behaviour)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if ((!Handle->handle) || (Handle->type != FSHandleTypeUpdate)) return FSOperationFailure;
    
    const size_t Offset = FSHandleGetOffset(Handle);
    size_t Size = FSManagerGetSize(Handle->path);
    
    if (Offset > Size) return FSOperationSuccess;
    Size -= Offset;
    
    if (Count >= Size)
    {
#if CC_PLATFORM_POSIX_COMPLIANT
        ftruncate(FSHandleGetFileDescriptor(Handle), Offset);
#else
#error Missing support for truncation
#endif
    }
    
    else
    {
        size_t ChunkSize = FSManagerGetPreferredIOBlockSize(Handle->path);
        
        void *Chunk;
        CC_SAFE_Malloc(Chunk, ChunkSize,
                       return FSOperationFailure;
                       );
        
        for (size_t Shifted = 0; Shifted < (Size - Count); )
        {
            size_t ChunkLength = ChunkSize;
            FSHandleSetOffset(Handle, Offset + Shifted + Count);
            FSHandleRead(Handle, &ChunkLength, Chunk, FSBehaviourDefault);
            
            FSHandleSetOffset(Handle, Offset + Shifted);
            FSHandleWrite(Handle, ChunkLength, Chunk, FSBehaviourDefault);
            
            Shifted += ChunkLength;
        }
        
#if CC_PLATFORM_POSIX_COMPLIANT
        ftruncate(FSHandleGetFileDescriptor(Handle), Offset + Size - Count);
#else
#error Missing support for truncation
#endif
        
        CC_SAFE_Free(Chunk);
    }
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, Offset);
    else if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourUpdateOffset) return FSHandleSetOffset(Handle, Offset + Count);
    
    return FSOperationSuccess;
}

FSOperation FSHandleRemoveFromOffset(FSHandle Handle, size_t Offset, size_t Count, FSBehaviour Behaviour)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if (!Handle->handle) return FSOperationFailure;
    
    const size_t OldOffset = FSHandleGetOffset(Handle);
    
    FSHandleSetOffset(Handle, Offset);
    FSOperation Result = FSHandleRemove(Handle, Count, Behaviour);
    
    if ((Result == FSOperationSuccess) && ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset)) return FSHandleSetOffset(Handle, OldOffset);
    
    return Result;
}

size_t FSHandleGetOffset(FSHandle Handle)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if (Handle->handle)
    {
        return ftell(Handle->handle);
    }
    
    return 0;
}

FSOperation FSHandleSetOffset(FSHandle Handle, size_t Offset)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if (!Handle->handle) return FSOperationFailure;
    
    
    return !fseek(Handle->handle, Offset, SEEK_SET) ? FSOperationSuccess : FSOperationFailure;
}

#if CC_PLATFORM_POSIX_COMPLIANT
int FSHandleGetFileDescriptor(FSHandle Handle)
{
    CCAssertLog(Handle, "Handle must not be null");
    
    if (Handle->handle)
    {
        return fileno(Handle->handle);
    }
    
    return -1;
}
#endif

#endif
