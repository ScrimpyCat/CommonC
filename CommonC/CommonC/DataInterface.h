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

#ifndef CommonC_DataInterface_h
#define CommonC_DataInterface_h

#include <CommonC/DataTypes.h>
#include <CommonC/Buffer.h>
#include <CommonC/Allocator.h>

#pragma mark - Required Callbacks
/*!
 * @brief A callback to create the internal implementation for the data.
 * @param Allocator The allocator to be used for the creation.
 * @param Hint The hints describing the intended usage of the collection.
 * @param Data The initializaton data.
 * @return The created internal structure.
 */
typedef void *(*CCDataConstructorCallback)(CCAllocatorType Allocator, CCDataHint Hint, void *Data);

/*!
 * @brief A callback to destroy the internal implementation for the data.
 * @param Internal The pointer to the internal of the data.
 */
typedef void (*CCDataDestructorCallback)(void *Internal);

/*!
 * @brief A callback to retrieve the size of the internal data.
 * @param Internal The pointer to the internal of the data.
 * @return The size of the internal data.
 */
typedef size_t (*CCDataGetSizeCallback)(void *Internal);

/*!
 * @brief A callback to map a region of the internal data.
 * @param Internal The pointer to the internal of the data.
 * @param Offset The offset to map from.
 * @param Size The size of the data to be mapped.
 * @param Access The access behaviour for the map.
 * @return The mapped buffer.
 */
typedef CCBufferMap (*CCDataMapBufferCallback)(void *Internal, ptrdiff_t Offset, size_t Size, CCDataHint Access);

/*!
 * @brief A callback to unmap a mapped region of the internal data.
 * @param Internal The pointer to the internal of the data.
 * @param MappedBuffer The mapped buffer.
 */
typedef void (*CCDataUnmapBufferCallback)(void *Internal, CCBufferMap MappedBuffer);


#pragma mark - Optional Callbacks
/*!
 * @brief An optional callback to retrieve the preferred map size for the internal data.
 * @param Internal The pointer to the internal of the data.
 * @return The preferred map size for the internal data.
 */
typedef size_t (*CCDataGetPreferredMapSizeCallback)(void *Internal);

/*!
 * @brief An optional callback to resize the internal data.
 * @param Internal The pointer to the internal of the data.
 * @param Size The new size of the internal data.
 * @return Whether the resize was successful or not.
 */
typedef _Bool (*CCDataResizeCallback)(void *Internal, size_t Size);

/*!
 * @brief An optional callback to retrieve the hash of the internal data.
 * @param Internal The pointer to the internal of the data.
 * @return The hash for the data.
 */
typedef uint32_t (*CCDataGetHashCallback)(void *Internal);

/*!
 * @brief An optional callback to sync operations for the internal data.
 * @param Internal The pointer to the internal of the data.
 */
typedef void (*CCDataSyncCallback)(void *Internal);

/*!
 * @brief An optional callback to invalidate the internal data.
 * @param Internal The pointer to the internal of the data.
 */
typedef void (*CCDataInvalidateCallback)(void *Internal);

/*!
 * @brief An optional callback to retrieve the pointer to the internal buffer.
 * @param Internal The pointer to the internal of the data.
 * @return The internal buffer.
 */
typedef void *(*CCDataGetBufferCallback)(void *Internal);

/*!
 * @brief An optional callback to mark the region of internal buffer that has been modified.
 * @param Internal The pointer to the internal of the data.
 * @param Offset The offset of the modification.
 * @param Size The size of the modification.
 */
typedef void (*CCDataModifiedRangeCallback)(void *Internal, ptrdiff_t Offset, size_t Size);

/*!
 * @brief An optional callback to read the internal data.
 * @param Internal The pointer to the internal of the data.
 * @param Offset The offset to read from.
 * @param Size The size to read.
 * @param Buffer The buffer read data is copied to.
 * @return The amount successfully read.
 */
typedef size_t (*CCDataReadBufferCallback)(void *Internal, ptrdiff_t Offset, size_t Size, void *Buffer);

/*!
 * @brief An optional callback to write the internal data.
 * @param Internal The pointer to the internal of the data.
 * @param Offset The offset to write from.
 * @param Size The size to write.
 * @param Buffer The buffer of data to be written.
 * @return The amount successfully written.
 */
typedef size_t (*CCDataWriteBufferCallback)(void *Internal, ptrdiff_t Offset, size_t Size, const void *Buffer);

/*!
 * @brief An optional callback to copy the internal data to another.
 * @description Both source and destination are of the same type. i.e. Have the same 
 *              @b CCDataInterface.
 *
 * @param SrcInternal The pointer to the internal of the data to copy from.
 * @param SrcOffset The offset of to copy from.
 * @param Size The size of the copy.
 * @param DstInternal The pointer to the internal of the data to copy to.
 * @param DstOffset The offset of to copy to.
 * @return The amount successfully copied.
 */
typedef size_t (*CCDataCopyBufferCallback)(void *SrcInternal, ptrdiff_t SrcOffset, size_t Size, void *DstInternal, ptrdiff_t DstOffset);

/*!
 * @brief An optional callback to fill the internal data.
 * @param Internal The pointer to the internal of the data.
 * @param Offset The offset to fill from.
 * @param Size The size to fill.
 * @param Fill The value to use for the fill.
 * @return The amount successfully filled.
 */
typedef size_t (*CCDataFillBufferCallback)(void *Internal, ptrdiff_t Offset, size_t Size, uint8_t Fill);


#pragma mark -

/*!
 * @brief The interface to the internal implementation.
 * @description Optional interfaces do not need to be implemented and will instead be supported
 *              through reusing the required interfaces.
 */
typedef struct {
    CCDataConstructorCallback create;
    CCDataDestructorCallback destroy;
    CCDataGetSizeCallback size;
    CCDataMapBufferCallback map;
    CCDataUnmapBufferCallback unmap;
    struct {
        CCDataGetPreferredMapSizeCallback preferredMapSize;
        CCDataResizeCallback resize;
        CCDataGetHashCallback hash;
        CCDataSyncCallback sync;
        CCDataInvalidateCallback invalidate;
        CCDataGetBufferCallback buffer;
        CCDataModifiedRangeCallback modifiedBuffer;
        CCDataReadBufferCallback read;
        CCDataWriteBufferCallback write;
        CCDataCopyBufferCallback copy;
        CCDataFillBufferCallback fill;
    } optional;
} CCDataInterface;

#endif
