/*
 *  Copyright (c) 2023, Stefan Johnson
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

#include "MemoryZone.h"
#include "MemoryAllocation.h"
#include "Logging.h"
#include "Maths.h"

static void CCMemoryZoneDestructor(CCMemoryZone Zone)
{
    for (CCMemoryZoneBlock *Block = Zone->block.next, *NextBlock; Block; Block = NextBlock)
    {
        NextBlock = Block->next;
        CCFree(Block);
    }
}

CCMemoryZone CCMemoryZoneCreate(CCAllocatorType Allocator, size_t BlockSize)
{
    if (BlockSize < sizeof(CCMemoryZoneState)) BlockSize = sizeof(CCMemoryZoneState);
    
    CCMemoryZone Zone = CCMalloc(Allocator, sizeof(CCMemoryZoneHeader) + BlockSize, NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Zone)
    {
        *Zone = (CCMemoryZoneHeader){
            .allocator = Allocator,
            .blockSize = BlockSize,
            .state = NULL,
            .block = {
                .last = &Zone->block,
                .next = NULL,
                .offset = 0
            }
        };
        
        CCMemorySetDestructor(Zone, (CCMemoryDestructorCallback)CCMemoryZoneDestructor);
    }
    
    
    return Zone;
}

void CCMemoryZoneDestroy(CCMemoryZone Zone)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    CCFree(Zone);
}

void *CCMemoryZoneAllocate(CCMemoryZone Zone, size_t Size)
{
    CCAssertLog(Zone, "Zone must not be null");
    CCAssertLog(Size, "Size must not be zero");
    CCAssertLog(Size <= Zone->blockSize, "Size must be less than the block size (%zu)", Zone->blockSize);
    
    CCMemoryZoneBlock *Block = Zone->block.last;
    
    if ((Block->offset + Size) > Zone->blockSize)
    {
        CCMemoryZoneBlock *NewBlock = CCMalloc(Zone->allocator, sizeof(CCMemoryZoneBlock) + Zone->blockSize, NULL, CC_DEFAULT_ERROR_CALLBACK);
        if (!NewBlock)
        {
            CC_LOG_ERROR("Failed to allocate block of size (%zu)", sizeof(CCMemoryZoneBlock) + Zone->blockSize);
            
            return NULL;
        }
        
        *NewBlock = (CCMemoryZoneBlock){
            .prev = Block,
            .next = NULL,
            .offset = 0
        };
        
        Zone->block.last = NewBlock;
        Block->next = NewBlock;
        Block = NewBlock;
    }
    
    void *Ptr = Block->data + Block->offset;
    Block->offset += Size;
    
    if (Zone->state) Zone->state->size += Size;
    
    return Ptr;
}

void CCMemoryZoneDeallocate(CCMemoryZone Zone, size_t Size)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    CCMemoryZoneState *State = Zone->state;
    for (size_t DeallocSize = Size; State; )
    {
        const size_t StateSize = State->size;
        if (StateSize < DeallocSize)
        {
            DeallocSize -= StateSize;
            State = State->prev;
        }
        
        else
        {
            State->size -= DeallocSize;
            break;
        }
    }
    
    Zone->state = State;
    
    CCMemoryZoneBlock *Block = Zone->block.last;
    
    Zone->block.last = &Zone->block;
    
    for (CCMemoryZoneBlock *PrevBlock; ; Block = PrevBlock)
    {
        PrevBlock = Block->prev;
        
        if (Block->offset < Size)
        {
            if (PrevBlock != Block)
            {
                Size -= Block->offset;
                PrevBlock->next = NULL;
                CCFree(Block);
            }
            
            else
            {
                Block->offset = 0;
                break;
            }
        }
        
        else
        {
            Block->offset -= Size;
            break;
        }
    }
    
    Zone->block.last = Block;
}

void CCMemoryZoneSave(CCMemoryZone Zone)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    CCMemoryZoneState *State = CCMemoryZoneAllocate(Zone, sizeof(CCMemoryZoneState));
    
    *State = (CCMemoryZoneState){
        .size = 0,
        .prev = Zone->state
    };
    
    Zone->state = State;
}

void CCMemoryZoneRestore(CCMemoryZone Zone)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    CCMemoryZoneState *State = Zone->state;
    if (State) CCMemoryZoneDeallocate(Zone, State->size + sizeof(CCMemoryZoneState));
}

static void *CCMemoryZoneEnumerableHandler(CCEnumerator *Enumerator, CCEnumerableAction Action)
{
    switch (Action)
    {
        case CCEnumerableActionHead:
            while (CCMemoryZoneEnumerableHandler(Enumerator, CCEnumerableActionPrevious));
            Enumerator->state.batch.index = 0;
            break;
            
        case CCEnumerableActionTail:
            while (CCMemoryZoneEnumerableHandler(Enumerator, CCEnumerableActionNext));
            Enumerator->state.batch.index = Enumerator->state.batch.count - 1;
            break;
            
        case CCEnumerableActionNext:
        {
            if ((Enumerator->state.batch.extra[0] + Enumerator->state.batch.count) == Enumerator->state.batch.extra[1]) return NULL;
            
            CCMemoryZoneBlock *Block = Enumerator->ref;
            
            if ((Block = Block->next))
            {
                Enumerator->state.batch.extra[0] += Enumerator->state.batch.count;
                
                Enumerator->ref = Block;
                
                Enumerator->state.batch.ptr = Block->data;
                Enumerator->state.batch.index = 0;
                
                size_t Count = Block->offset / Enumerator->state.batch.stride;
                const size_t Remainder = Enumerator->state.batch.extra[1] - Enumerator->state.batch.extra[0];
                
                if (Count > Remainder) Count = Remainder;
                
                Enumerator->state.batch.count = Count;
            }
            
            else
            {
                const size_t Count = ((CCMemoryZoneBlock*)Enumerator->ref)->offset / Enumerator->state.batch.stride;

                if (Count == Enumerator->state.batch.count) return NULL;

                Enumerator->state.batch.count = Count;
                Enumerator->state.batch.index++;
            }
            
            break;
        }
            
        case CCEnumerableActionPrevious:
        {
            if (Enumerator->state.batch.extra[0] == 0) return NULL;
            
            CCMemoryZoneBlock *Block = ((CCMemoryZoneBlock*)Enumerator->ref)->prev;
            
            Enumerator->ref = Block;
            
            Enumerator->state.batch.ptr = Block->data;
            Enumerator->state.batch.count = Block->offset / Enumerator->state.batch.stride;
            
            if (Enumerator->state.batch.extra[0] < Enumerator->state.batch.count)
            {
                Enumerator->state.batch.ptr += (Enumerator->state.batch.count - Enumerator->state.batch.extra[0]) * Enumerator->state.batch.stride;
                
                Enumerator->state.batch.count = Enumerator->state.batch.extra[0];
            }
            
            Enumerator->state.batch.index = Enumerator->state.batch.count - 1;
            
            Enumerator->state.batch.extra[0] -= Enumerator->state.batch.count;
            
            break;
        }
            
        default:
            break;
    }
    
    if (Enumerator->state.batch.index >= Enumerator->state.batch.count) return NULL;
    
    return Enumerator->state.batch.ptr + (Enumerator->state.batch.index * Enumerator->state.batch.stride);
}

void CCMemoryZoneBlockGetEnumerable(CCMemoryZoneBlock *ZoneBlock, ptrdiff_t Offset, size_t Stride, size_t Count, CCEnumerable *Enumerable)
{
    CCAssertLog(ZoneBlock, "ZoneBlock must not be null");
    
    size_t Size;
    void *Ptr = CCMemoryZoneBlockGetPointer(&ZoneBlock, &Offset, &Size);
    
    *Enumerable = (CCEnumerable){
        .handler = CCMemoryZoneEnumerableHandler,
        .enumerator = {
            .ref = ZoneBlock,
            .state = {
                .batch = {
                    .ptr = Ptr,
                    .count = CCMin(Size / Stride, Count),
                    .stride = Stride,
                    .index = 0,
                    .extra = { 0, Count }
                },
                .type = CCEnumeratorFormatBatch
            }
        }
    };
}
