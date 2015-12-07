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

#include "Data.h"
#include "MemoryAllocation.h"
#include "Logging.h"
#include "Assertion.h"
#include "Hash.h"

CCData CCDataCreate(CCAllocatorType Allocator, CCDataHint Hint, void *InitData, CCDataBufferHash Hash, CCDataBufferDestructor Destructor, const CCDataInterface *Interface)
{
    CCAssertLog(Interface, "Interface must not be null");
    
    CCData Data = CCMalloc(Allocator, sizeof(CCDataInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Data)
    {
        *Data = (CCDataInfo){
            .interface = Interface,
            .allocator = Allocator,
            .destructor = Destructor,
            .hasher = Hash,
            .hash = 0,
            .internal = Interface->create(Allocator, Hint, InitData),
            .mutated = TRUE
        };
        
        if (!Data->internal)
        {
            CC_LOG_ERROR("Failed to create collection: Implementation failure (%p)", Interface);
            CCFree(Data);
            Data = NULL;
        }
    }
    
    else
    {
        CC_LOG_ERROR("Failed to create collection: Failed to allocate memory of size (%zu)", sizeof(CCDataInfo));
    }
    
    return Data;
}


void CCDataDestroy(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    if (Data->destructor) Data->destructor(Data);
    Data->interface->destroy(Data->internal);
    CC_SAFE_Free(Data);
}

CCDataHint CCDataGetHints(CCData Data)
{
    return Data->interface->hints(Data->internal);
}

size_t CCDataGetPreferredMapSize(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    return Data->interface->optional.preferredMapSize ? Data->interface->optional.preferredMapSize(Data->internal) : SIZE_MAX;
}

size_t CCDataGetSize(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    return Data->interface->size(Data->internal);
}

_Bool CCDataSetSize(CCData Data, size_t Size)
{
    CCAssertLog(Data, "Data must not be null");
    
    return Data->interface->optional.resize ? Data->interface->optional.resize(Data->internal, Size) : FALSE;
}

uint32_t CCDataGetHash(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    if (Data->mutated)
    {
        if (Data->hasher) Data->hash = Data->hasher(Data);
        else if (Data->interface->optional.hash) Data->hash = Data->interface->optional.hash(Data->internal);
        else Data->hash = CCHashMurmur32(Data);
        
        Data->mutated = FALSE;
    }
    
    return Data->hash;
}

void CCDataSync(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    if (Data->interface->optional.sync) Data->interface->optional.sync(Data->internal);
    Data->mutated = TRUE;
}

void CCDataInvalidate(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    if (Data->interface->optional.invalidate) Data->interface->optional.invalidate(Data->internal);
    Data->mutated = TRUE;
}

void CCDataPurge(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    if (Data->interface->optional.purge) Data->interface->optional.purge(Data->internal);
}

void *CCDataGetBuffer(CCData Data)
{
    CCAssertLog(Data, "Data must not be null");
    
    return Data->interface->optional.buffer ? Data->interface->optional.buffer(Data->internal) : NULL;
}

void CCDataModifiedRange(CCData Data, ptrdiff_t Offset, size_t Size)
{
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog((Offset + Size) <= CCDataGetSize(Data), "Must not exceed bounds");
    CCAssertLog(CCDataGetHints(Data) & CCDataHintWrite, "Must have write access");
    
    if (Data->interface->optional.modifiedBuffer) Data->interface->optional.modifiedBuffer(Data->internal, Offset, Size);
    Data->mutated = TRUE;
}

CCBufferMap CCDataMapBuffer(CCData Data, ptrdiff_t Offset, size_t Size, CCDataHint Access)
{
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog((Offset + Size) <= CCDataGetSize(Data), "Must not exceed bounds");
    CCAssertLog(!(Access & CCDataHintRead) || (CCDataGetHints(Data) & CCDataHintRead), "Must have read access");
    CCAssertLog(!(Access & CCDataHintWrite) || (CCDataGetHints(Data) & CCDataHintWrite), "Must have write access");
    
    return Data->interface->map(Data->internal, Offset, Size, Access);
}

void CCDataUnmapBuffer(CCData Data, CCBufferMap MappedBuffer)
{
    CCAssertLog(Data, "Data must not be null");
    
    Data->interface->unmap(Data->internal, MappedBuffer);
    Data->mutated = TRUE;
}

size_t CCDataReadBuffer(CCData Data, ptrdiff_t Offset, size_t Size, void *Buffer)
{
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog((Offset + Size) <= CCDataGetSize(Data), "Must not exceed bounds");
    CCAssertLog(CCDataGetHints(Data) & CCDataHintRead, "Must have read access");
    
    size_t Read = 0;
    if (Data->interface->optional.read) Read = Data->interface->optional.read(Data->internal, Offset, Size, Buffer);
    else
    {
        const size_t PreferredMapSize = CCDataGetPreferredMapSize(Data);
        for (size_t Loop = 0, Count = Size / PreferredMapSize; Loop < Count; Loop++)
        {
            CCBufferMap Map = CCDataMapBuffer(Data, Offset + (Loop * PreferredMapSize), PreferredMapSize, CCDataHintRead);
            memcpy(Buffer + (Loop * PreferredMapSize), Map.ptr, Map.size);
            CCDataUnmapBuffer(Data, Map);
            
            Read += Map.size;
            if (Map.size != PreferredMapSize) return Read;
        }
        
        CCBufferMap Map = CCDataMapBuffer(Data, Offset + Read, Size - Read, CCDataHintRead);
        memcpy(Buffer + Read, Map.ptr, Map.size);
        CCDataUnmapBuffer(Data, Map);
        
        Read += Map.size;
    }
    
    return Read;
}

size_t CCDataWriteBuffer(CCData Data, ptrdiff_t Offset, size_t Size, const void *Buffer)
{
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog((Offset + Size) <= CCDataGetSize(Data), "Must not exceed bounds");
    CCAssertLog(CCDataGetHints(Data) & CCDataHintWrite, "Must have write access");
    
    size_t Written = 0;
    if (Data->interface->optional.write) Written = Data->interface->optional.write(Data->internal, Offset, Size, Buffer);
    else
    {
        const size_t PreferredMapSize = CCDataGetPreferredMapSize(Data);
        for (size_t Loop = 0, Count = Size / PreferredMapSize; Loop < Count; Loop++)
        {
            CCBufferMap Map = CCDataMapBuffer(Data, Offset + (Loop * PreferredMapSize), PreferredMapSize, CCDataHintWrite);
            memcpy(Map.ptr, Buffer + (Loop * PreferredMapSize), Map.size);
            CCDataUnmapBuffer(Data, Map);
            
            Written += Map.size;
            if (Map.size != PreferredMapSize) return Written;
        }
        
        CCBufferMap Map = CCDataMapBuffer(Data, Offset + Written, Size - Written, CCDataHintWrite);
        memcpy(Map.ptr, Buffer + Written, Map.size);
        CCDataUnmapBuffer(Data, Map);
        
        Written += Map.size;
    }
    
    Data->mutated = TRUE;
    
    return Written;
}

size_t CCDataCopyBuffer(CCData SrcData, ptrdiff_t SrcOffset, size_t Size, CCData DstData, ptrdiff_t DstOffset)
{
    CCAssertLog(SrcData && DstData, "Source and destination data must not be null");
    CCAssertLog((SrcOffset + Size) <= CCDataGetSize(SrcData), "Must not exceed source bounds");
    CCAssertLog((DstOffset + Size) <= CCDataGetSize(DstData), "Must not exceed destination bounds");
    CCAssertLog(CCDataGetHints(SrcData) & CCDataHintRead, "Must have read access");
    CCAssertLog(CCDataGetHints(DstData) & CCDataHintWrite, "Must have write access");
    
    size_t Copied = 0;
    if ((SrcData->interface == DstData->interface) && (SrcData->interface->optional.copy)) Copied = SrcData->interface->optional.copy(SrcData->internal, SrcOffset, Size, DstData->internal, DstOffset);
    else
    {
        const size_t PreferredMapSize = CCDataGetPreferredMapSize(SrcData);
        for (size_t Loop = 0, Count = Size / PreferredMapSize; Loop < Count; Loop++)
        {
            CCBufferMap SrcMap = CCDataMapBuffer(SrcData, SrcOffset + (Loop * PreferredMapSize), PreferredMapSize, CCDataHintRead);
            CCBufferMap DstMap = CCDataMapBuffer(DstData, DstOffset + (Loop * PreferredMapSize), SrcMap.size, CCDataHintWrite);
            memcpy(DstMap.ptr, SrcMap.ptr, DstMap.size);
            CCDataUnmapBuffer(DstData, DstMap);
            CCDataUnmapBuffer(SrcData, SrcMap);
            
            Copied += DstMap.size;
            if (DstMap.size != PreferredMapSize) return Copied;
        }
        
        CCBufferMap SrcMap = CCDataMapBuffer(SrcData, SrcOffset + Copied, Size - Copied, CCDataHintRead);
        CCBufferMap DstMap = CCDataMapBuffer(DstData, DstOffset + Copied, SrcMap.size, CCDataHintWrite);
        memcpy(DstMap.ptr, SrcMap.ptr, DstMap.size);
        CCDataUnmapBuffer(DstData, DstMap);
        CCDataUnmapBuffer(SrcData, SrcMap);
        
        Copied += DstMap.size;
    }
    
    DstData->mutated = TRUE;
    
    return Copied;
}

size_t CCDataFillBuffer(CCData Data, ptrdiff_t Offset, size_t Size, uint8_t Fill)
{
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog((Offset + Size) <= CCDataGetSize(Data), "Must not exceed bounds");
    CCAssertLog(CCDataGetHints(Data) & CCDataHintWrite, "Must have write access");
    
    size_t Filled = 0;
    if (Data->interface->optional.fill) Filled = Data->interface->optional.fill(Data->internal, Offset, Size, Fill);
    else
    {
        const size_t PreferredMapSize = CCDataGetPreferredMapSize(Data);
        for (size_t Loop = 0, Count = Size / PreferredMapSize; Loop < Count; Loop++)
        {
            CCBufferMap Map = CCDataMapBuffer(Data, Offset + (Loop * PreferredMapSize), PreferredMapSize, CCDataHintWrite);
            memset(Map.ptr, Fill, Map.size);
            CCDataUnmapBuffer(Data, Map);
            
            Filled += Map.size;
            if (Map.size != PreferredMapSize) return Filled;
        }
        
        CCBufferMap Map = CCDataMapBuffer(Data, Offset + Filled, Size - Filled, CCDataHintWrite);
        memset(Map.ptr, Fill, Map.size);
        CCDataUnmapBuffer(Data, Map);
        
        Filled += Map.size;
    }
    
    Data->mutated = TRUE;
    
    return Filled;
}
