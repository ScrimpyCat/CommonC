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

#ifndef CommonC_FileHandle_h
#define CommonC_FileHandle_h

#include <CommonC/Path.h>
#include <CommonC/FileSystem.h>


typedef enum {
    FSHandleTypeRead,
    FSHandleTypeWrite,
    FSHandleTypeUpdate
} FSHandleType;

typedef struct {
    FSHandleType type;
    FSPath path;
    void *handle;
} FSHandleInfo, *FSHandle;

typedef enum {
    FSBehaviourDefault,
    FSBehaviourPreserveOffset = (0 << 0),
    FSBehaviourUpdateOffset = (1 << 0),
    FSBehaviourOffsettingMask = (1 << 0),
    
    //Reading
    
    //Writing
    FSWritingBehaviourOverwrite = (0 << 16),
    FSWritingBehaviourInsert = (1 << 16),
    FSWritingBehaviourDestructiveMask = (1 << 16),
    
    FSBehaviourMask        = 0x0000ff,
    FSReadingBehaviourMask = 0x00ff00,
    FSWritingBehaviourMask = 0xff0000
} FSBehaviour;


/*!
 * @brief Open a file handle to a file at path.
 * @param Path The path of the file.
 * @param Type The type of file handle.
 * @param Handle A pointer to the write out the handle. If the operation was successful, then
 *        the file handle must be closed when finished.
 *
 * @return FSOperationSuccess if it successfully opens a file handle to the file. Otherwise
 *         the type of failure.
 */
FSOperation FSHandleOpen(FSPath CC_COPY(Path), FSHandleType Type, FSHandle * CC_NEW Handle);

/*!
 * @brief Close a file handle.
 * @param Handle The file handle.
 * @return FSOperationSuccess if it successfully closes the file handle. Otherwise the type 
 *         of failure.
 */
FSOperation FSHandleClose(FSHandle CC_DESTROY(Handle));

/*!
 * @brief Block until all operations on the file have finished.
 * @param Handle The file handle.
 * @return FSOperationSuccess if it successfully synchronizes the file handle. Otherwise the
 *         type of failure.
 */
FSOperation FSHandleSync(FSHandle Handle);

/*!
 * @brief Read the data from the file.
 * @param Handle The file handle.
 * @param Count A pointer to the amount of data to be read, and sets it to the amount of data
 *        actually read.
 *
 * @param Data A pointer to where the read data should be stored. Must be at least size of Count.
 * @param Behaviour The behaviour of the operation.
 * @return FSOperationSuccess if it successfully reads from the file handle. Otherwise the
 *         type of failure.
 */
FSOperation FSHandleRead(FSHandle Handle, size_t *Count, void *Data, FSBehaviour Behaviour);

/*!
 * @brief Read the data at an offset from the file.
 * @param Handle The file handle.
 * @param Offset The offset to begin reading from.
 * @param Count A pointer to the amount of data to be read, and sets it to the amount of data
 *        actually read.
 *
 * @param Data A pointer to where the read data should be stored. Must be at least size of Count.
 * @param Behaviour The behaviour of the operation.
 * @return FSOperationSuccess if it successfully reads from the file handle. Otherwise the
 *         type of failure.
 */
FSOperation FSHandleReadFromOffset(FSHandle Handle, size_t Offset, size_t *Count, void *Data, FSBehaviour Behaviour);

/*!
 * @brief Write the data to the file.
 * @param Handle The file handle.
 * @param Count The amount of data to be written.
 * @param Data The data to be written. Must be at least size of Count.
 * @param Behaviour The behaviour of the operation.
 * @return FSOperationSuccess if it successfully write to the file handle. Otherwise the
 *         type of failure.
 */
FSOperation FSHandleWrite(FSHandle Handle, size_t Count, const void *Data, FSBehaviour Behaviour);

/*!
 * @brief Write the data at an offset in the file.
 * @param Handle The file handle.
 * @param Offset The offset to begin reading from.
 * @param Count The amount of data to be written.
 * @param Data The data to be written. Must be at least size of Count.
 * @param Behaviour The behaviour of the operation.
 * @return FSOperationSuccess if it successfully write to the file handle. Otherwise the
 *         type of failure.
 */
FSOperation FSHandleWriteFromOffset(FSHandle Handle, size_t Offset, size_t Count, const void *Data, FSBehaviour Behaviour);

/*!
 * @brief Remove data from the file.
 * @param Handle The file handle.
 * @param Count The amount of data to be removed. Passing SIZE_MAX will ensure all data is removed.
 * @param Behaviour The behaviour of the operation.
 * @return FSOperationSuccess if it successfully removes the data from to the file handle. 
 *         Otherwise the type of failure.
 */
FSOperation FSHandleRemove(FSHandle Handle, size_t Count, FSBehaviour Behaviour);

/*!
 * @brief Remove data from an offset in the file.
 * @param Handle The file handle.
 * @param Count The amount of data to be removed. Passing SIZE_MAX will ensure all data is removed.
 * @param Behaviour The behaviour of the operation.
 * @return FSOperationSuccess if it successfully removes the data from to the file handle.
 *         Otherwise the type of failure.
 */
FSOperation FSHandleRemoveFromOffset(FSHandle Handle, size_t Offset, size_t Count, FSBehaviour Behaviour);

/*!
 * @brief Get the current offset in the file.
 * @param Handle The file handle.
 * @return The offset.
 */
size_t FSHandleGetOffset(FSHandle Handle);

/*!
 * @brief Set the current offset in the file.
 * @param Handle The file handle.
 * @return FSOperationSuccess if it successfully sets the offset. Otherwise the type of failure.
 */
FSOperation FSHandleSetOffset(FSHandle Handle, size_t Offset);

#if CC_PLATFORM_POSIX_COMPLIANT
/*!
 * @brief Get the POSIX file descriptor for the file.
 * @warning This function is only available on POSIX compliant systems. Check CC_PLATFORM_POSIX_COMPLIANT
 *          for POSIX compliancy.
 *
 * @param Handle The file handle.
 * @return The POSIX file descriptor, or -1 if an error occurred.
 */
int FSHandleGetFileDescriptor(FSHandle Handle);
#endif

#endif
