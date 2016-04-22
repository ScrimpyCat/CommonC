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

#ifndef CommonC_FileSystem_h
#define CommonC_FileSystem_h

#include <CommonC/Path.h>

typedef enum {
    FSAccessReadable = (1 << 0),
    FSAccessWritable = (1 << 1),
    FSAccessExecutable = (1 << 2),
    FSAccessDeletable = (1 << 3)
} FSAccess;

typedef enum {
    FSOperationSuccess,
    FSOperationFailure, //generic failure
    FSOperationPathNotExist
} FSOperation;


/*!
 * @brief Check whether the path exists.
 * @param Path The path.
 * @return TRUE if it exists, FALSE if it does not.
 */
_Bool FSManagerExists(FSPath Path);

/*!
 * @brief Get the access rights of a path.
 * @param Path The path.
 * @return The access types.
 */
FSAccess FSManagerGetAccessRights(FSPath Path);

/*!
 * @brief Get the size of a path.
 * @param Path The path.
 * @return The size or 0 if it does not exist.
 */
size_t FSManagerGetSize(FSPath Path);

/*!
 * @brief Get the preferred block size for IO operations on the path.
 * @param Path The path.
 * @return The block size or 0 if it does not exist.
 */
size_t FSManagerGetPreferredIOBlockSize(FSPath Path);

/*!
 * @brief Get a list of all content paths in the specified path.
 * @description Contents are filtered based on matching inputs. The named matching rules are as
 *              follows:
 *
 *              Path component names are matched literally, with wildcard matches denoted by '*'.
 *
 *              The matching behaviour can be overridden by using the FSMatchNameOption* flags.
 *              Where default matching behaviour is a case incensitive whitelist.
 *
 * @param Path The path.
 * @param NamingMatches An array of FSPath's to apply named matching rules on the list, or NULL
 *        for no named matches.
 * @param MatchOptions The options specifying the matching behaviour.
 * @return The list of FSPath's or NULL is there were no paths. Note: Must be destroyed.
 */
CC_NEW CCOrderedCollection FSManagerGetContentsAtPath(FSPath Path, CCCollection NamingMatches, FSMatch MatchOptions);

/*!
 * @brief Create a path and optionally any required intermediate directories.
 * @param Path The path.
 * @param IntermediateDirectories Whether any missing intermediate directories should be created.
 * @return FSOperationSuccess if it successfully creates the path or if the path already exists.
 *         Otherwise the type of failure.
 */
FSOperation FSManagerCreate(FSPath Path, _Bool IntermediateDirectories);

/*!
 * @brief Remove a path.
 * @param Path The path.
 * @return FSOperationSuccess if it successfully removes the path or if the path already did not
 *         exist. Otherwise the type of failure.
 */
FSOperation FSManagerRemove(FSPath Path);

/*!
 * @brief Move a path.
 * @param Path The path.
 * @param Destination The new path it should be moved to.
 * @return FSOperationSuccess if it successfully moves the path to the destination path. Otherwise
 *         the type of failure.
 */
FSOperation FSManagerMove(FSPath Path, FSPath Destination);

/*!
 * @brief Create a path and optionally any required intermediate directories.
 * @param Path The path.
 * @param IntermediateDirectories Whether any missing intermediate directories should be created.
 * @return FSOperationSuccess if it successfully copies the path to the destination path. Otherwise
 *         the type of failure.
 */
FSOperation FSManagerCopy(FSPath Path, FSPath Destination);

/*!
 * @brief Create a path and optionally any required intermediate directories.
 * @param Path The path.
 * @param IntermediateDirectories Whether any missing intermediate directories should be created.
 * @return FSOperationSuccess if it successfully renames the path. Otherwise the type of failure.
 */
FSOperation FSManagerRename(FSPath Path, const char *Name);

#endif
