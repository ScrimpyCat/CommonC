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

#ifndef CommonC_Data_h
#define CommonC_Data_h

#include <CommonC/Base.h>
#include <CommonC/Container.h>
#include <CommonC/Allocator.h>
#include <CommonC/DataTypes.h>
#include <CommonC/DataInterface.h>
#include <CommonC/Buffer.h>


CC_CONTAINER_DECLARE_PRESET_1(CCData);

/*!
 * @define CC_DATA_DECLARE
 * @abstract Convenient macro to define a @b CCData type that can be referenced by @b CCData.
 * @param data The data type.
 */
#define CC_DATA_DECLARE(data) CC_CONTAINER_DECLARE(CCData, data)

/*!
 * @define CC_DATA
 * @abstract Convenient macro to define an explicitly typed @b CCData.
 * @param data The data type.
 */
#define CC_DATA(data) CC_CONTAINER(CCData, data)

/*!
 * @define CCData
 * @abstract Convenient macro to define an explicitly typed @b CCData.
 * @description In the case that this macro is conflicting with the standalone @b CCData type, simply
 *              undefine it and redefine it back to @b CC_DATA.
 *
 * @param data The data type.
 */
#define CCData(data) CC_DATA(data)

/*!
 * @brief A callback to handle custom destruction of a data buffer.
 * @param Data The data container.
 */
typedef void (*CCDataBufferDestructor)(CCData Data);

/*!
 * @brief A callback to handle custom hashing of a data buffer.
 * @param Data The data container.
 */
typedef uint32_t (*CCDataBufferHash)(CCData Data);


typedef struct CCDataInfo {
    const CCDataInterface *interface;
    CCAllocatorType allocator;
    CCDataBufferDestructor destructor;
    CCDataBufferHash hasher;
    uint32_t hash;
    void *internal;
    _Bool mutated;
} CCDataInfo;

#pragma mark - Creation/Destruction

/*!
 * @brief Create a data container with the specified implementation.
 * @param Allocator The allocator to be used for the allocations.
 * @param Hint The hints for the intended usage of this data container.
 * @param Data The initialization data for the specified implementation.
 * @param Hash An optional hashing function to be performed instead of the default for the internal
 *        implementation.
 *
 * @param Destructor An optional destructor to perform any custom cleanup on destroy.
 * @param Interface The interface to the internal implementation to be used.
 * @return An empty data container, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCData CCDataCreate(CCAllocatorType Allocator, CCDataHint Hint, void *Data, CCDataBufferHash Hash, CCDataBufferDestructor Destructor, const CCDataInterface *Interface);

/*!
 * @brief Destroy a data container.
 * @param Data The data container to be destroyed.
 */
void CCDataDestroy(CCData CC_DESTROY(Data));

/*!
 * @brief Get the hints for the data container.
 * @param Data The data container to retrieve the hints for.
 * @return The hints.
 */
CCDataHint CCDataGetHints(CCData Data);

/*!
 * @brief Get the preferred mapping size of the data container.
 * @param Data The data container to retrieve the size for.
 * @return The preferred map size of the data.
 */
size_t CCDataGetPreferredMapSize(CCData Data);

/*!
 * @brief Get the size of the data container.
 * @param Data The data container to retrieve the size for.
 * @return The size of the data.
 */
size_t CCDataGetSize(CCData Data);

/*!
 * @brief Resize the data container.
 * @description Only allowed on data containers
 * @param Data The data container to retrieve the size for.
 * @param Size The new size of the data.
 * @return Whether the resize was successful or not.
 */
_Bool CCDataSetSize(CCData Data, size_t Size);

/*!
 * @brief Get the hash of the data container.
 * @param Data The data container to retrieve the hash for.
 * @return The hash of the data.
 */
uint32_t CCDataGetHash(CCData Data);

/*!
 * @brief Block until all operations on the data have finished and so it is in the same state
 *        as its internal data.
 *
 * @param Data The data container to retrieve the hash for.
 */
void CCDataSync(CCData Data);

/*!
 * @brief Invaliate the internal storage, replacing it with a new buffer.
 * @param Data The data container to be invalidated.
 */
void CCDataInvalidate(CCData Data);

/*!
 * @brief Purge the cached memory.
 * @param Data The data container to be purged.
 */
void CCDataPurge(CCData Data);

/*!
 * @brief Get the internal buffer for the data if available.
 * @description All writes to the buffer need to be marked using @b CCDataModifiedRange.
 * @warning If the data container was created as readonly, then writing to the buffer is undefined.
 * @param Data The data container to retrieve the internal buffer to.
 * @return The pointer to the data, or NULL if it cannot access the internal buffer (use one of the
 *         read or write functions, or the mapping function).
 */
void *CCDataGetBuffer(CCData Data);

/*!
 * @brief Mark the region of the @b CCDataGetBuffer that was modified.
 * @param Data The data container the buffer belongs to.
 * @param Offset The starting point of the modification.
 * @param Size The size of the modified region.
 */
void CCDataModifiedRange(CCData Data, ptrdiff_t Offset, size_t Size);

/*!
 * @brief Map a region of the buffer for reading/writing.
 * @warning Must be unmapped using @b CCDataUnmapBuffer once finished, at which point the buffer is
 *          invalidated. Any further access is undefined.
 *
 * @param Data The data container to map the buffer for.
 * @param Offset The starting point to map.
 * @param Size The size of the mapped region.
 * @param Access The type of access for the mapped buffer. The default allows for either @b CCDataHintRead,
 *        @b CCDataHintWrite, @b CCDataHintReadWrite.
 *
 * @return The mapped buffer.
 */
CCBufferMap CCDataMapBuffer(CCData Data, ptrdiff_t Offset, size_t Size, CCDataHint Access);

/*!
 * @brief Unmap a mapped buffer.
 * @param Data The data container the mapped buffer belongs to.
 */
void CCDataUnmapBuffer(CCData Data, CCBufferMap MappedBuffer);

/*!
 * @brief Read the data from the region of the data container.
 * @param Data The data container to read.
 * @param Offset The starting point to read from.
 * @param Size The size of the data to be read.
 * @param Buffer The buffer where the data should be copied to.
 * @return The amount successfully read.
 */
size_t CCDataReadBuffer(CCData Data, ptrdiff_t Offset, size_t Size, void *Buffer);

/*!
 * @brief Write the data from the region of the data container.
 * @param Data The data container to be written.
 * @param Offset The starting point to write to.
 * @param Size The size of the data to write.
 * @param Buffer The buffer where the data should be copied to.
 * @return The amount successfully written.
 */
size_t CCDataWriteBuffer(CCData Data, ptrdiff_t Offset, size_t Size, const void *Buffer);

/*!
 * @brief Copy the data from the region of the data container to the region of another data container.
 * @param SrcData The data container to copy.
 * @param SrcOffset The starting point to copy from.
 * @param Size The size of the data to copy. .
 * @param DstData The data container where the data should be copied to.
 * @param DstOffset The starting point to copy to.
 * @return The amount successfully copied.
 */
size_t CCDataCopyBuffer(CCData SrcData, ptrdiff_t SrcOffset, size_t Size, CCData DstData, ptrdiff_t DstOffset);

/*!
 * @brief Fill the data from the region of the data container.
 * @param Data The data container to be filled.
 * @param Offset The starting point to fill from.
 * @param Size The size of the data to fill.
 * @param Fill The value to fill the region with.
 * @return The amount successfully filled.
 */
size_t CCDataFillBuffer(CCData Data, ptrdiff_t Offset, size_t Size, uint8_t Fill);

#endif
