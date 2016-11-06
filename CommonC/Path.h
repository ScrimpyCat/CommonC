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

#ifndef CommonC_Path_h
#define CommonC_Path_h

#include <CommonC/OrderedCollection.h>
#include <CommonC/PathComponent.h>

typedef struct {
    CCOrderedCollection components;
    char *completeRep;
    const char *filenameRep, *pathRep;
} FSPathInfo, *FSPath;

typedef enum {
    /// Default matching behaviour
    FSMatchDefault = 0,
    /// Skip file matches.
    FSMatchSkipFile = (1 << 0),
    /// Skip directory matches.
    FSMatchSkipDirectory = (1 << 1),
    /// Skip hidden file/directory matches.
    FSMatchSkipHidden = (1 << 2),
    /// Search recursively into sub-folders.
    FSMatchSearchRecursively = (1 << 3),
    
    /// Matching names act as a whitelist. Only contents whose name matches are used.
    FSMatchNameWhitelist = (0 << 4),
    /// Matching names act as a blacklist. Only contents whose name do not match are used.
    FSMatchNameBlacklist = (1 << 4),
    /// Matching names are case-insensitive.
    FSMatchNameOptionCaseInsensitive = (0 << 5),
    /// Matching names are case-sensitive.
    FSMatchNameOptionCaseSensitive = (1 << 5),
    /// Matching names use wildcards as a literal character match instead.
    FSMatchNameOptionWildcardIsLiteral = (1 << 6),
    /// Matching names with a relative root must match.
    FSMatchNameOptionRequireRelativeRoot = (1 << 7),
    
    /// Define a custom wildcard ('*' << FSMatchNameOptionWildcard), default is '*'.
    FSMatchNameOptionWildcard = 25,
    FSMatchNameOptionWildcardMask = (127 << FSMatchNameOptionWildcard)
} FSMatch;


/*!
 * @brief Convert an FSPath style path to FSPathComponents.
 * @description 
 *
 *              @b Volumes: Start at the beginning of the path string and are denoted by // followed by the volume name
 *              e.g. "//Macintosh HD", "//C", "//My Drive"
 *
 *              @b Root: Start at the beginning of the path string or directly after a volume is specified, and is denoted
 *              by /
 *
 *              @b Relative root: Any path that does not begin with a volume or a root. e.g. "some/", "some.txt"
 *
 *              @b Directory: Any other component in the path that ends with /
 *
 *              @b Relative parent directory: Any directory component whose name is ..
 *
 *              @b File: Anything else excluding any extensions following
 *
 *              @b Extension: Anything else following a .
 *
 * @param Path The path.
 * @param CompletePath Whether the path should be completed or not if it is not a complete path.
 * @return An ordered collection of FSPathComponents, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCOrderedCollection FSPathConvertPathToComponents(const char *Path, _Bool CompletePath);

/*!
 * @brief Convert the system path to FSPathComponents.
 * @param Path The path.
 * @param CompletePath Whether the path should be completed or not if it is not a complete path.
 * @return An ordered collection of FSPathComponents, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCOrderedCollection FSPathConvertSystemPathToComponents(const char *Path, _Bool CompletePath);

/*!
 * @brief Create a FSPath from an FSPath style path.
 * @see FSPathConvertPathToComponents
 * @param Path The path.
 * @return A path representation of the path, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW FSPath FSPathCreate(const char *Path);

/*!
 * @brief Create a FSPath from a system path.
 * @see FSPathConvertSystemPathToComponents
 * @param Path The path.
 * @return A path representation of the system path, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW FSPath FSPathCreateFromSystemPath(const char *Path);

/*!
 * @brief Copy a path.
 * @param Path The path to be copied.
 * @return A path representation of the path, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW FSPath FSPathCopy(FSPath Path);

/*!
 * @brief Destroy a path.
 * @param Path The path to be destroyed.
 */
void FSPathDestroy(FSPath CC_DESTROY(Path));

/*!
 * @brief Get the current path.
 * @warning Must not mutate or destroy this path.
 * @return A path representation of the current path.
 */
FSPath FSPathCurrent(void);
//void FSPathSetCurrent(FSPath Path);

/*!
 * @brief Get the number of components for the path.
 * @param Path The path.
 * @return A the number of components.
 */
size_t FSPathGetComponentCount(FSPath Path);

/*!
 * @brief Get a component at a given index in the path.
 * @param Path The path.
 * @param Index The index of the component. Must be within bounds.
 * @return The component.
 */
FSPathComponent FSPathGetComponentAtIndex(FSPath Path, size_t Index);

/*!
 * @brief Set the component at a given index in the path to the specified component.
 * @param Path The path.
 * @param Component The component to be added to the path. Ownership of the component is transfered to the path.
 * @param Index The index of the component. Must be within bounds.
 */
void FSPathSetComponentAtIndex(FSPath Path, FSPathComponent CC_OWN(Component), size_t Index);

/*!
 * @brief Insert the component at a given index in the path.
 * @param Path The path.
 * @param Component The component to be added to the path. Ownership of the component is transfered to the path.
 * @param Index The index of the component. Must be within bounds.
 */
void FSPathInsertComponentAtIndex(FSPath Path, FSPathComponent CC_OWN(Component), size_t Index);

/*!
 * @brief Append the component to the end of the path.
 * @param Path The path.
 * @param Component The component to be added to the path. Ownership of the component is transfered to the path.
 */
void FSPathAppendComponent(FSPath Path, FSPathComponent CC_OWN(Component));

/*!
 * @brief Prepend the component to the start of the path.
 * @param Path The path.
 * @param Component The component to be added to the path. Ownership of the component is transfered to the path.
 */
void FSPathPrependComponent(FSPath Path, FSPathComponent CC_OWN(Component));

/*!
 * @brief Remove the component at a given index in the path.
 * @param Path The path.
 * @param Index The index of the component. Must be within bounds.
 */
void FSPathRemoveComponentIndex(FSPath Path, size_t Index);

/*!
 * @brief Remove the last component from the path.
 * @param Path The path.
 */
void FSPathRemoveComponentLast(FSPath Path);

/*!
 * @brief Get the string representation for the full path.
 * @param Path The path.
 * @return The string representation of the full path.
 */
const char *FSPathGetFullPathString(FSPath Path);

/*!
 * @brief Get the string representation for the path.
 * @param Path The path.
 * @return The string representation of the path.
 */
const char *FSPathGetPathString(FSPath Path);

/*!
 * @brief Get the string representation for the filename.
 * @param Path The path.
 * @return The string representation of the filename.
 */
const char *FSPathGetFilenameString(FSPath Path);

/*!
 * @brief Get the volume for the path.
 * @param Path The path.
 * @return The volume component for the path.
 */
FSPathComponent FSPathGetVolume(FSPath Path);

/*!
 * @brief Check whether a path is a directory.
 * @param Path The path.
 * @return TRUE if it represents a directory, FALSE if it does not.
 */
_Bool FSPathIsDirectory(FSPath Path);

/*!
 * @brief Check whether a path is a file.
 * @param Path The path.
 * @return TRUE if it represents a file, FALSE if it does not.
 */
_Bool FSPathIsFile(FSPath Path);

/*!
 * @brief Check whether a path is a relative path.
 * @param Path The path.
 * @return TRUE if it represents a relative path, FALSE if it does not.
 */
_Bool FSPathIsRelativePath(FSPath Path);

/*!
 * @brief Check if the two paths match.
 * @description Using matching options to change matching behaviour.
 * @param Left A path.
 * @param Right A path.
 * @param MatchOptions Matching options to configure the matching behaviour. All options
 *        beginning with FSMatchNameOption are valid. The others have no effect.
 */
_Bool FSPathMatch(FSPath Left, FSPath Right, FSMatch MatchOptions);

#endif
