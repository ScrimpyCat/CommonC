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

#ifndef CommonC_MemoryZone_h
#define CommonC_MemoryZone_h

#include <CommonC/Base.h>
#include <CommonC/Platform.h>
#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>
#include <CommonC/Assertion.h>

typedef struct CCMemoryZoneState {
    size_t size;
    struct CCMemoryZoneState *prev;
} CCMemoryZoneState;

typedef struct CCMemoryZoneBlock {
    union {
        struct CCMemoryZoneBlock *prev;
        struct CCMemoryZoneBlock *last;
    };
    struct CCMemoryZoneBlock *next;
    ptrdiff_t offset;
    uint8_t data[];
} CCMemoryZoneBlock;

typedef struct {
    CCAllocatorType allocator;
    size_t blockSize;
    CCMemoryZoneState *state;
    CCMemoryZoneBlock block;
} CCMemoryZoneHeader;

/*!
 * @brief The memory zone.
 * @description Allows @b CCRetain.
 */
typedef CCMemoryZoneHeader *CCMemoryZone;

/*!
 * @brief Create a memory zone.
 * @param Allocator The allocator to be used for the allocation.
 * @param BlockSize The size of each block. If the block size is smaller than the size of CCMemoryZoneState, then it will be increased up to that size.
 * @return A memory zone, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCMemoryZone CCMemoryZoneCreate(CCAllocatorType Allocator, size_t BlockSize);

/*!
 * @brief Destroy a memory zone.
 * @note All allocations will be freed.
 * @param Zone The memory zone to be destroyed.
 */
void CCMemoryZoneDestroy(CCMemoryZone CC_DESTROY(Zone));

/*!
 * @brief Allocate some memory from the memory zone.
 * @param Zone The memory zone to suballocate in.
 * @param Size The size of the allocation. The size must be smaller than the block size.
 * @return A pointer to the memory, or NULL on failure.
 */
void *CCMemoryZoneAllocate(CCMemoryZone Zone, size_t Size);

/*!
 * @brief Deallocate some memory from the memory zone.
 * @description Deallocations release memory from the most recent allocations.
 * @note If the deallocation size exceeds the current saved state (if there is one), then that state is destroyed (restoring will restore one before it
 *       if there is one).
 *
 * @param Zone The memory zone to deallocate in.
 * @param Size The size of the deallocation. Can pass in SIZE_MAX to deallocate all of the memory in the zone.
 */
void CCMemoryZoneDeallocate(CCMemoryZone Zone, size_t Size);

/*!
 * @brief Save the current allocation state for the zone so it can be restored to later.
 * @param Zone The memory zone to save the current state for.
 */
void CCMemoryZoneSave(CCMemoryZone Zone);

/*!
 * @brief Restore the previous allocation state for the zone.
 * @description All memory in the current state will be deallocated. If no state is currently saved then no deallocation occurs.
 * @param Zone The memory zone to restore the previous state for.
 */
void CCMemoryZoneRestore(CCMemoryZone Zone);

/*!
 * @brief Get the block size for the memory zone.
 * @param Zone The memory zone to retrieve the block size for.
 * @return The block size of the memory zone.
 */
static CC_FORCE_INLINE size_t CCMemoryZoneGetBlockSize(CCMemoryZone Zone);

/*!
 * @brief Get the first block for the memory zone.
 * @param Zone The memory zone to retrieve the block for.
 * @return The first block of the memory zone.
 */
static CC_FORCE_INLINE CCMemoryZoneBlock *CCMemoryZoneGetBlock(CCMemoryZone Zone);

/*!
 * @brief Get the pointer at the given offset for the memory zone.
 * @param Zone The memory zone to retrieve the pointer for.
 * @param Offset The offset of the allocated memory.
 * @param Size A pointer to where to store the size of the memory that can be read from that pointer (not necessarily the size of the remaining allocation).
 * @return The pointer to the memory, or NULL when there is none.
 */
static CC_FORCE_INLINE void *CCMemoryZoneGetPointer(CCMemoryZone Zone, ptrdiff_t Offset, size_t *Size);

/*!
 * @brief Get the pointer at the given offset relative to the provided block.
 * @description This variant can provide faster lookup than @b CCMemoryZoneGetPointer, so it should be preferenced when you'll be
 *              iterating through the memory zone and can keep a reference to the current block.
 *
 * @param ZoneBlock A pointer to the memory zone block pointer. This will be set to the block that contains the pointer.
 * @param RelativeOffset A pointer to the offset of the allocated memory relative to the ZoneBlock. This will be set to the offset in the block the pointer was found.
 * @param Size A pointer to where to store the size of the memory that can be read from that pointer (not necessarily the size of the remaining allocation).
 * @return The pointer to the memory, or NULL when there is none.
 */
static CC_FORCE_INLINE void *CCMemoryZoneBlockGetPointer(CCMemoryZoneBlock **ZoneBlock, ptrdiff_t *RelativeOffset, size_t *Size);

/*!
 * @brief Get the block that contains the given pointer in the memory zone.
 * @param Zone The memory zone to retrieve the block for.
 * @param Ptr The pointer to find the block of
 * @param Offset A pointer to where the offset that the pointer is at should be set. May be NULL.
 * @return The block in the memory zone that contains the pointer, or NULL if there is none.
 */
static CC_FORCE_INLINE CCMemoryZoneBlock *CCMemoryZoneGetBlockForPointer(CCMemoryZone Zone, const void *Ptr, ptrdiff_t *Offset);

#pragma mark -

static CC_FORCE_INLINE size_t CCMemoryZoneGetBlockSize(CCMemoryZone Zone)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    return Zone->blockSize;
}

static CC_FORCE_INLINE CCMemoryZoneBlock *CCMemoryZoneGetBlock(CCMemoryZone Zone)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    return &Zone->block;
}

static CC_FORCE_INLINE void *CCMemoryZoneGetPointer(CCMemoryZone Zone, ptrdiff_t Offset, size_t *Size)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    return CCMemoryZoneBlockGetPointer(&(CCMemoryZoneBlock*){ &Zone->block }, &Offset, Size);
}

static CC_FORCE_INLINE void *CCMemoryZoneBlockGetPointer(CCMemoryZoneBlock **ZoneBlock, ptrdiff_t *RelativeOffset, size_t *Size)
{
    CCAssertLog(ZoneBlock, "ZoneBlock must not be null");
    CCAssertLog(RelativeOffset, "Offset must not be null");
    
    ptrdiff_t Offset = *RelativeOffset;
    
    for (CCMemoryZoneBlock *Block = *ZoneBlock; Block; Block = Block->next)
    {
        if (Offset < Block->offset)
        {
            if (Size) *Size = Block->offset - Offset;
            
            *ZoneBlock = Block;
            *RelativeOffset = Offset;
            
            return Block->data + Offset;
        }
        
        else
        {
            Offset -= Block->offset;
        }
    }
    
    if (Size) *Size = 0;
    
    *ZoneBlock = NULL;
    *RelativeOffset = 0;
    
    return NULL;
}

static CC_FORCE_INLINE CCMemoryZoneBlock *CCMemoryZoneGetBlockForPointer(CCMemoryZone Zone, const void *Ptr, ptrdiff_t *Offset)
{
    CCAssertLog(Zone, "Zone must not be null");
    
    for (CCMemoryZoneBlock *Block = &Zone->block; Block; Block = Block->next)
    {
        if ((Ptr >= (void*)Block->data) && (Ptr < (void*)(Block->data + Block->offset)))
        {
            if (Offset) *Offset = (ptrdiff_t)Ptr - (ptrdiff_t)Block->data;
            
            return Block;
        }
    }
    
    return NULL;
}

#endif
