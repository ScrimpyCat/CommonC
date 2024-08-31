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
#define _XOPEN_SOURCE 500
#define _BSD_SOURCE
#include "FileSystem_Private.h"
#include "Platform.h"
#include "OrderedCollection.h"
#include "CollectionEnumerator.h"
#include "DictionaryEnumerator.h"
#include "DictionaryHashMap.h"
#include "HashMap.h"
#include "HashMapSeparateChainingArray.h"
#include "Assertion.h"
#include "TypeCallbacks.h"
#include "MemoryAllocation.h"
#include "Logging.h"

#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
//SystemPath.m
#elif CC_PLATFORM_UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <ftw.h>
#include <string.h>
#elif CC_PLATFORM_WINDOWS
#error Add support for windows
#else
#warning Unsupported platform
#endif

const char * FSVirtualVolume = "[MEMORY]";

FSOperation FSManagerRename(FSPath Path, const char *Name)
{
    CCAssertLog(Path, "Path must not be null");
    CCAssertLog(Name, "Name must not be null");
    
    FSPath NewPath = FSPathCopy(Path);
    
    //TODO: Create some simple setters to make this easier
    if (FSPathIsFile(Path))
    {
        for (size_t Loop = FSPathGetComponentCount(NewPath); Loop != 0; Loop--)
        {
            const size_t Index = Loop - 1;
            FSPathComponentType Type = FSPathComponentGetType(FSPathGetComponentAtIndex(NewPath, Index));
            if ((Type == FSPathComponentTypeFile) || (Type == FSPathComponentTypeExtension))
            {
                FSPathRemoveComponentIndex(NewPath, Index);
            }
            
            else break;
        }
        
        
        CCOrderedCollection Components = FSPathConvertPathToComponents(Name, FALSE);
        
        CC_COLLECTION_FOREACH(FSPathComponent, Component, Components)
        {
            FSPathAppendComponent(NewPath, FSPathComponentCopy(Component));
        }
        
        CCCollectionDestroy(Components);
    }
    
    else //directory
    {
        FSPathSetComponentAtIndex(NewPath, FSPathComponentCreate(FSPathComponentTypeDirectory, Name), FSPathGetComponentCount(Path) - 1);
    }
    
    FSOperation Success = FSManagerMove(Path, NewPath);
    FSPathDestroy(NewPath);
    
    return Success;
}

#if CC_PLATFORM_UNIX

#pragma mark Path
//CCOrderedCollection FSPathConvertSystemPathToComponents(const char *Path, _Bool CompletePath)
//{
//    CCAssertLog(Path, "Path must not be null");
//    CCAssertLog(0, "Not implemented");
//    
//    return NULL;
//}

//FSPath FSPathCurrent(void)
//{
//    /*
//     Potental issues with threading unless add locks around any FSCurrentPath usage. May be better to just
//     implement FSPathCreateFromCurrent()
//     */
//    static FSPathInfo FSCurrentPath;
//    if (!FSCurrentPath.components)
//    {
//        char Path[PATH_MAX];
//        if (getcwd(Path, sizeof(Path)))
//        {
//            CCOrderedCollection Components = FSPathConvertPathToComponents(Path, FALSE); //TODO: Make it handle it properly //FSPathConvertSystemPathToComponents(Path, FALSE);
//            
//            if ((CCCollectionGetCount(Components) >= 1) && (FSPathComponentGetType(*(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Components, 0)) != FSPathComponentTypeVolume))
//            {
//                NSString *Volume;
//                [[NSURL fileURLWithPath: CurrentPath] getResourceValue: &Volume forKey:NSURLVolumeNameKey error: NULL];
//
//                CCOrderedCollectionPrependElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeVolume, [Volume UTF8String]) });
//            }
//            
//            FSCurrentPath.components = Components;s
//        }
//    }
//    
//    return &FSCurrentPath;
//}

#pragma mark - FileSystem

static const char *FSPathSystemInternalRepresentation(FSPath Path)
{
    CCAssertLog(FSPathComponentGetType(FSPathGetComponentAtIndex(Path, 0)) != FSPathComponentTypeVolume, "Currently does not support resolving volumes");
    
    return FSPathGetPathString(Path); //TODO: Need to handle resolving of volumes
}

_Bool FSManagerExists(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    struct stat Info;
    int Status = stat(FSPathSystemInternalRepresentation(Path), &Info);
    
    return (!Status) && ((_Bool)S_ISDIR(Info.st_mode) == FSPathIsDirectory(Path));
}

FSAccess FSManagerGetAccessRights(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    struct stat Info;
    int Status = stat(FSPathSystemInternalRepresentation(Path), &Info);
    
    return Status ? 0 : ((_Bool)(Info.st_mode & S_IRUSR) * FSAccessReadable)
    | ((_Bool)(Info.st_mode & S_IWUSR) * FSAccessWritable)
    | ((_Bool)(Info.st_mode & S_IXUSR) * FSAccessExecutable)
    | ((_Bool)(Info.st_mode & S_IWUSR) * FSAccessDeletable); //TODO: detect proper file/directory mutability (FSAccessDeletable)
}

size_t FSManagerGetSize(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    struct stat Info;
    int Status = stat(FSPathSystemInternalRepresentation(Path), &Info);
    
    return !Status ? Info.st_size : 0;
}

size_t FSManagerGetPreferredIOBlockSize(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    struct stat Info;
    int Status = stat(FSPathSystemInternalRepresentation(Path), &Info);
    
    return !Status ? Info.st_blksize : 0;
}

static void FSManagerAddContentsInPath(FSPath SystemPath, CCOrderedCollection *List, CCCollection NamingMatches, FSMatch MatchOptions)
{
    DIR *Info = opendir(FSPathSystemInternalRepresentation(SystemPath));
    if (Info)
    {
        for (struct dirent *Entry; (Entry = readdir(Info)); )
        {
            const char *Item = Entry->d_name;
            if ((Item[0] == '.') && ((MatchOptions & FSMatchSkipHidden) || (Item[1] == 0) || ((Item[1] == '.') && (Item[2] == 0)))) continue;
            
            const _Bool IsDir = Entry->d_type == DT_DIR;
            _Bool Match = TRUE;
            
#ifdef _DIRENT_HAVE_D_NAMLEN
            const size_t EntryLength = Entry->d_namlen;
#else
            const size_t EntryLength = strlen(Entry->d_name);
#endif
            
            const size_t SystemPathLength = strlen(FSPathGetPathString(SystemPath));
            char *ItemPath;
            CC_SAFE_Malloc(ItemPath, SystemPathLength + EntryLength + 1,
                           CC_LOG_ERROR("Failed to add path item: \"%s/%s\" due to allocation failure (%zu)", FSPathGetPathString(SystemPath), Item, SystemPathLength + EntryLength + 1);
                           continue;
                           );
            
            strcpy(ItemPath, FSPathGetPathString(SystemPath));
            strcpy(ItemPath + SystemPathLength, Item);
            
            FSPath Path = FSPathCreateFromSystemPath(ItemPath);
            CC_SAFE_Free(ItemPath);
            
            if (NamingMatches)
            {
                CC_COLLECTION_FOREACH(FSPath, PathMatch, NamingMatches)
                {
                    Match = FSPathMatch(Path, PathMatch, MatchOptions);
                    
                    if (Match) break;
                }
            }
            
            _Bool PreservePath = FALSE;
            if ((PreservePath = ((MatchOptions & FSMatchNameBlacklist) ? !Match : Match)))
            {
                if (!(IsDir * (MatchOptions & FSMatchSkipDirectory)) && !(!IsDir * (MatchOptions & FSMatchSkipFile)))
                {
                    if (!*List) *List = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintHeavyEnumerating, sizeof(FSPath), FSPathDestructorForCollection);
                    CCOrderedCollectionAppendElement(*List, &Path);
                }
            }
            
            if ((MatchOptions & FSMatchSearchRecursively))
            {
                if (IsDir) FSManagerAddContentsInPath(Path, List, NamingMatches, MatchOptions);
            }
            
            if (!PreservePath) FSPathDestroy(Path);
        }
        
        closedir(Info);
    }
}

CCOrderedCollection FSManagerGetContentsAtPath(FSPath Path, CCCollection NamingMatches, FSMatch MatchOptions)
{
    CCAssertLog(Path, "Path must not be null");
    CCAssertLog(NamingMatches, "NamingMatches must not be null");
    
    CCOrderedCollection List = NULL;
    
    FSManagerAddContentsInPath(Path, &List, NamingMatches, MatchOptions);
    
    return List;
}

static _Bool FSManagerCreateDirectory(FSPath Path, _Bool IntermediateDirectories)
{
    if (((FSPathGetComponentCount(Path) == 1) && (FSPathComponentGetType(FSPathGetComponentAtIndex(Path, 0)) != FSPathComponentTypeDirectory)) || (FSManagerExists(Path))) return TRUE;
    
    _Bool Success = TRUE;
    if (IntermediateDirectories)
    {
        FSPathComponent Component = FSPathComponentCopy(FSPathGetComponentAtIndex(Path, FSPathGetComponentCount(Path) - 1));

        FSPathRemoveComponentLast(Path);
        Success = FSManagerCreateDirectory(Path, IntermediateDirectories);

        FSPathAppendComponent(Path, Component);
    }
    
    if ((Success) && (!FSPathIsFile(Path))) Success = !mkdir(FSPathSystemInternalRepresentation(Path), S_IRWXU | S_IRGRP | S_IROTH);
    
    return Success;
}

FSOperation FSManagerCreate(FSPath Path, _Bool IntermediateDirectories)
{
    CCAssertLog(Path, "Path must not be null");
    
    if (!FSManagerExists(Path))
    {
        _Bool Success = FALSE;
        
        if (FSPathIsFile(Path))
        {
            FSPath Temp = FSPathCopy(Path);
            Success = FSManagerCreateDirectory(Temp, IntermediateDirectories);
            FSPathDestroy(Temp);
            
            if (Success)
            {
                int fd = creat(FSPathSystemInternalRepresentation(Path), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                if ((Success = (fd != -1))) close(fd);
            }
        }
        
        else
        {
            Success = FSManagerCreateDirectory(Path, IntermediateDirectories);
        }
        
        return Success ? FSOperationSuccess : FSOperationFailure;
    }
    
    return FSOperationSuccess;
}

static int FSManagerRemover(const char *Path, const struct stat *Info, int Flags, struct FTW *Ref)
{
    return remove(Path);
}

static int FSManagerMaxFileDescriptors(void)
{
    const int Max = sysconf(_SC_OPEN_MAX);
    
    return (Max / 100) >= 1 ? 100 : 1;
}

FSOperation FSManagerRemove(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    if (FSManagerExists(Path))
    {
        _Bool Success;
        if (FSPathIsFile(Path)) Success = !remove(FSPathSystemInternalRepresentation(Path));
        else Success = !nftw(FSPathSystemInternalRepresentation(Path), FSManagerRemover, FSManagerMaxFileDescriptors(), FTW_DEPTH);
        
        return Success ? FSOperationSuccess : FSOperationFailure;
    }
    
    return FSOperationSuccess;
}

FSOperation FSManagerMove(FSPath Path, FSPath Destination)
{
    CCAssertLog(Path, "Path must not be null");
    CCAssertLog(Destination, "Destination must not be null");
    
    if (FSManagerExists(Path))
    {
        _Bool Success = !rename(FSPathSystemInternalRepresentation(Path), FSPathSystemInternalRepresentation(Destination));
        
        return Success ? FSOperationSuccess : FSOperationFailure;
    }
    
    return FSOperationPathNotExist;
}

static _Thread_local size_t ChunkSize = 0;
static _Thread_local void *Chunk = NULL;
static FSOperation FSManagerCopyItem(FSPath Path, FSPath Destination)
{
    FSOperation Success;
    if ((Success = FSManagerCreate(Destination, FALSE)) == FSOperationSuccess)
    {
        if ((FSPathIsFile(Path)))
        {
            FSHandle Reader, Writer;
            if ((Success = FSHandleOpen(Path, FSHandleTypeRead, &Reader)) == FSOperationSuccess)
            {
                if ((Success = FSHandleOpen(Destination, FSHandleTypeWrite, &Writer)) == FSOperationSuccess)
                {
                    const size_t BlockSize = FSManagerGetPreferredIOBlockSize(Path);
                    if (ChunkSize < BlockSize)
                    {
                        CC_SAFE_Realloc(Chunk, BlockSize,
                                        FSHandleClose(Writer);
                                        FSHandleClose(Reader);
                                        
                                        return FSOperationFailure;
                                        );
                        
                        ChunkSize = BlockSize;
                    }
                    
                    for (size_t Count = BlockSize; Count; )
                    {
                        Count = BlockSize;
                        if (FSHandleRead(Reader, &Count, Chunk, FSBehaviourUpdateOffset) != FSOperationSuccess)
                        {
                            FSHandleClose(Writer);
                            FSHandleClose(Reader);
                            
                            return FSOperationFailure;
                        }
                        
                        if (FSHandleWrite(Writer, Count, Chunk, FSBehaviourUpdateOffset) != FSOperationSuccess)
                        {
                            FSHandleClose(Writer);
                            FSHandleClose(Reader);
                            
                            return FSOperationFailure;
                        }
                    }
                    
                    FSHandleClose(Writer);
                }
                
                FSHandleClose(Reader);
            }
        }
    }
    
    return Success;
}

static _Thread_local FSPath CopyDestination;
static _Thread_local size_t BaseComponentCount;
static int FSManagerCopier(const char *Path, const struct stat *Info, int Flags, struct FTW *Ref)
{
    FSPath Destination = FSPathCopy(CopyDestination);
    CCOrderedCollection Components = FSPathConvertSystemPathToComponents(Path, TRUE);
    for (size_t Loop = BaseComponentCount, Count = CCCollectionGetCount(Components); Loop < Count; Loop++)
    {
        FSPathAppendComponent(Destination, FSPathComponentCopy(*(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Components, Loop)));
    }
    
    CCCollectionDestroy(Components);
    
    FSPath Original = FSPathCreateFromSystemPath(Path);
    FSOperation Success = FSManagerCopyItem(Original, Destination);
    
    FSPathDestroy(Original);
    FSPathDestroy(Destination);
    
    return Success == FSOperationSuccess ? 0 : -1;
}

FSOperation FSManagerCopy(FSPath Path, FSPath Destination)
{
    CCAssertLog(Path, "Path must not be null");
    CCAssertLog(Destination, "Destination must not be null");
    
    if (FSManagerExists(Path))
    {
        FSOperation Result;
        if (FSPathIsFile(Path)) Result = FSManagerCopyItem(Path, Destination);
        else
        {
            CopyDestination = Destination;
            BaseComponentCount = FSPathGetComponentCount(Path);
            
            _Bool Success = !nftw(FSPathSystemInternalRepresentation(Path), FSManagerCopier, FSManagerMaxFileDescriptors(), 0);
            
            Result = Success ? FSOperationSuccess : FSOperationFailure;
        }
        
        CC_SAFE_Free(Chunk);
        ChunkSize = 0;
        
        return Result;
    }
    
    return FSOperationPathNotExist;
}

#endif

#pragma mark - Virtual

void FSVirtualFileDestructor(FSVirtualFile *File)
{
    CCArrayDestroy(File->contents);
}

static void FSManagerVirtualNodeElementDestructor(CCDictionary Dictionary, FSVirtualNode **Element)
{
    FSVirtualNode *Node = *Element;
    
    CCStringDestroy(Node->name);
    
    if (Node->isDir)
    {
        CCDictionaryDestroy(Node->nodes);
    }
    
    else
    {
        FSVirtualFileDestroy(Node->file);
    }
    
    CCFree(Node);
}

static inline CCDictionary FSManagerVirtualCreateDir(void)
{
    return CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeMedium | CCDictionaryHintHeavyFinding | CCDictionaryHintHeavyInserting, sizeof(CCString), sizeof(FSVirtualNode*), &(CCDictionaryCallbacks){
        .keyDestructor = CCStringDestructorForDictionary,
        .valueDestructor = (CCDictionaryElementDestructor)FSManagerVirtualNodeElementDestructor,
        .getHash = CCStringHasherForDictionary,
        .compareKeys = CCStringComparatorForDictionary
    });
}

FSVirtualNode FSVirtualRoot = {
    .parent = NULL,
    .name = 0,
    .mode = FSAccessReadable | FSAccessWritable | FSAccessExecutable | FSAccessDeletable,
    .isDir = TRUE,
    .nodes = CC_STATIC_DICTIONARY(CCDictionaryHintSizeMedium | CCDictionaryHintHeavyFinding | CCDictionaryHintHeavyInserting, sizeof(CCString), sizeof(FSVirtualNode*), CCStringDestructorForDictionary, (CCDictionaryElementDestructor)FSManagerVirtualNodeElementDestructor, CCStringHasherForDictionary, CCStringComparatorForDictionary)
};

FSVirtualLock FSVirtualVolumeLock = ATOMIC_VAR_INIT(0);

FSVirtualNode *FSManagerVirtualNodeOp(FSPath Path, FSVirtualNode *Dirs[128], size_t *Level, FSVirtualNodeOperation Op, _Bool IntermediateDirectories)
{
    CCAssertLog(*Level < 128, "Exceeds maximum directory depth");
    
    FSVirtualNode FakeNode = { .isDir = TRUE };
    FSVirtualNode *Node = NULL;
    CCString File = 0;
    
    size_t Index = 1, Count = FSPathGetComponentCount(Path);
    CC_COLLECTION_FOREACH(FSPathComponent, Component, Path->components)
    {
        switch (FSPathComponentGetType(Component))
        {
            case FSPathComponentTypeVolume:
                Node = File ? NULL : &FSVirtualRoot;
                break;
                
            case FSPathComponentTypeRoot:
                if (!Node) Node = File ? NULL : &FSVirtualRoot;
                break;
                
            case FSPathComponentTypeRelativeRoot:
                Node = File ? NULL : FSManagerVirtualNodeOp(FSPathCurrent(), Dirs, Level, (Op == FSVirtualNodeOperationCreate ? FSVirtualNodeOperationCreate : FSVirtualNodeOperationNone), IntermediateDirectories);
                break;
                
            case FSPathComponentTypeDirectory:
                if ((Node) && (Node->isDir))
                {
                    if (Node != &FakeNode)
                    {
                        CCString Key = CCStringCreate(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringEncodingUTF8, FSPathComponentGetString(Component));
                        FSVirtualNode **Temp = CCDictionaryGetValue(Node->nodes, &Key);
                        
                        if (Temp)
                        {
                            Node = *Temp;
                            
                            CCStringDestroy(Key);
                        }
                        
                        else if ((Op == FSVirtualNodeOperationCreate) && ((Index == Count) || (IntermediateDirectories)))
                        {
                            FSVirtualNode *NewNode = CCMalloc(CC_STD_ALLOCATOR, sizeof(FSVirtualNode), NULL, CC_DEFAULT_ERROR_CALLBACK);
                            
                            *NewNode = (FSVirtualNode){
                                .parent = Node,
                                .name = CCStringCopy(Key),
                                .mode = FSAccessReadable | FSAccessWritable | FSAccessExecutable | FSAccessDeletable,
                                .isDir = TRUE,
                                .nodes = FSManagerVirtualCreateDir()
                            };
                            
                            CCDictionarySetValue(Node->nodes, &Key, &NewNode);
                            
                            Node = NewNode;
                        }
                        
                        else
                        {
                            Node = &FakeNode;
                            
                            CCStringDestroy(Key);
                        }
                        
                        if (!Node->isDir) Node = NULL;
                    }
                }
                
                else Node = NULL;
                break;
                
            case FSPathComponentTypeRelativeParentDirectory:
                *Level = (*Level > 2 ? *Level - 2 : 0);
                Node = Dirs[*Level];
                break;
                
            case FSPathComponentTypeFile:
                if ((Node) && (Node->isDir) && (Node != &FakeNode) && (!File))
                {
                    File = CCStringCreate(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringEncodingUTF8, FSPathComponentGetString(Component));
                }
                
                else Node = NULL;
                break;
                
            case FSPathComponentTypeExtension:
                if ((Node) && (Node->isDir) && (Node != &FakeNode))
                {
                    CCString Ext = CCStringCreate(CC_STD_ALLOCATOR, CCStringHintCopy | CCStringEncodingUTF8, FSPathComponentGetString(Component));
                    
                    if (File)
                    {
                        CCString Name = CCStringCreateByJoiningStrings((CCString[2]){ File, Ext }, 2, CC_STRING("."));
                        
                        CCStringDestroy(Ext);
                        CCStringDestroy(File);
                        
                        File = Name;
                    }
                    
                    else File = Ext;
                }
                
                else Node = NULL;
                break;
        }
        
        if (!Node) break;
        
        if (Node->isDir) Dirs[(*Level)++] = Node;
        
        Index++;
    }
    
    if (Node == &FakeNode) Node = NULL;
    
    if (File)
    {
        if (Node)
        {
            if (Op == FSVirtualNodeOperationRemove)
            {
                if (Node->mode & FSAccessDeletable)
                {
                    CCDictionaryRemoveValue(Node->nodes, &File);
                    
                    Node = NULL;
                }
                
                CCStringDestroy(File);
            }
            
            else
            {
                FSVirtualNode **Temp = CCDictionaryGetValue(Node->nodes, &File);
                
                if (Temp)
                {
                    Node = *Temp;
                }
                
                else if (Op == FSVirtualNodeOperationCreate)
                {
                    FSVirtualNode *NewNode = CCMalloc(CC_STD_ALLOCATOR, sizeof(FSVirtualNode), NULL, CC_DEFAULT_ERROR_CALLBACK);
                    
                    *NewNode = (FSVirtualNode){
                        .parent = Node,
                        .name = CCStringCopy(File),
                        .isDir = FALSE,
                        .mode = FSAccessReadable | FSAccessWritable | FSAccessDeletable,
                        .file = FSVirtualFileCreate()
                    };
                    
                    CCDictionarySetValue(Node->nodes, &File, &NewNode);
                    
                    Node = NewNode;
                }
                
                else Node = FALSE;
            }
        }
        
        else CCStringDestroy(File);
    }
    
    else if ((Node) && (Op == FSVirtualNodeOperationRemove) && (Node->mode & FSAccessDeletable))
    {
        CCDictionaryRemoveValue(Node->parent->nodes, &Node->name);
        
        Node = NULL;
    }
    
    return Node;
}

FSVirtualNode *FSManagerVirtualNode(FSPath Path)
{
    return FSManagerVirtualNodeOp(Path, (FSVirtualNode*[128]){ &FSVirtualRoot }, &(size_t){ 1 }, FSVirtualNodeOperationNone, FALSE);
}

_Bool FSManagerVirtualExists(FSPath Path)
{
    FSVirtualReadLock(&FSVirtualVolumeLock);
    const _Bool Exist = FSManagerVirtualNode(Path) != NULL;
    FSVirtualReadUnlock(&FSVirtualVolumeLock);
    
    return Exist;
}

FSAccess FSManagerVirtualGetAccessRights(FSPath Path)
{
    FSVirtualReadLock(&FSVirtualVolumeLock);
    FSVirtualNode *Node = FSManagerVirtualNode(Path);
    FSAccess Mode = Node ? Node->mode : 0;
    FSVirtualReadUnlock(&FSVirtualVolumeLock);
    
    return Mode;
}

size_t FSManagerVirtualGetSize(FSPath Path)
{
    size_t Size = 0;
    
    FSVirtualReadLock(&FSVirtualVolumeLock);
    FSVirtualNode *Node = FSManagerVirtualNode(Path);
    
    if (Node)
    {
        if (!Node->isDir)
        {
            FSVirtualFileReadLock(Node->file);
            Size = CCArrayGetCount(Node->file->contents);
            FSVirtualFileReadUnlock(Node->file);
        }
    }
    
    FSVirtualReadUnlock(&FSVirtualVolumeLock);
    
    return Size;
}

size_t FSManagerVirtualGetPreferredIOBlockSize(FSPath Path)
{
    return 4096;
}

static void FSManagerVirtualAddContentsInPath(FSPath SystemPath, CCOrderedCollection *List, CCCollection NamingMatches, FSMatch MatchOptions)
{
    FSVirtualNode *Node = FSManagerVirtualNode(SystemPath);
    
    if (Node)
    {
        if (Node->isDir)
        {
            CC_DICTIONARY_FOREACH_KEY(CCString, Key, Node->nodes)
            {
                _Bool Match = TRUE;
                FSPath Path = FSPathCopy(SystemPath);
                
                FSVirtualNode *Item = *(FSVirtualNode**)CCDictionaryGetValue(Node->nodes, &Key);
                
                CC_STRING_TEMP_BUFFER(Buffer, Key)
                {
                    if (Item->isDir)
                    {
                        FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeDirectory, Buffer));
                    }
                    
                    else
                    {
                        FSPath File = FSPathCreate(Buffer);
                        
                        for (size_t Loop = 1, Count = FSPathGetComponentCount(File); Loop < Count; Loop++)
                        {
                            FSPathAppendComponent(Path, FSPathComponentCopy(FSPathGetComponentAtIndex(File, Loop)));
                        }
                        
                        FSPathDestroy(File);
                    }
                    
                }
                
                if (NamingMatches)
                {
                    CC_COLLECTION_FOREACH(FSPath, PathMatch, NamingMatches)
                    {
                        Match = FSPathMatch(Path, PathMatch, MatchOptions);
                        
                        if (Match) break;
                    }
                }
                
                _Bool DestroyPath = TRUE;
                const _Bool IsDir = Item->isDir;
                
                if ((MatchOptions & FSMatchNameBlacklist) ? !Match : Match)
                {
                    if (!(IsDir * (MatchOptions & FSMatchSkipDirectory)) && !(!IsDir * (MatchOptions & FSMatchSkipFile)))
                    {
                        if (!*List) *List = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintHeavyEnumerating, sizeof(FSPath), FSPathDestructorForCollection);
                        CCOrderedCollectionAppendElement(*List, &Path);
                        
                        DestroyPath = FALSE;
                    }
                }
                
                if ((MatchOptions & FSMatchSearchRecursively))
                {
                    if (IsDir) FSManagerVirtualAddContentsInPath(Path, List, NamingMatches, MatchOptions);
                }
                
                if (DestroyPath) FSPathDestroy(Path);
            }
        }
    }
}

CCOrderedCollection FSManagerVirtualGetContentsAtPath(FSPath Path, CCCollection NamingMatches, FSMatch MatchOptions)
{
    CCOrderedCollection List = NULL;
    
    FSVirtualReadLock(&FSVirtualVolumeLock);
    FSManagerVirtualAddContentsInPath(Path, &List, NamingMatches, MatchOptions);
    FSVirtualReadUnlock(&FSVirtualVolumeLock);
    
    return List;
}

FSOperation FSManagerVirtualCreate(FSPath Path, _Bool IntermediateDirectories)
{
    FSVirtualWriteLock(&FSVirtualVolumeLock);
    FSVirtualNode *Node = FSManagerVirtualNodeOp(Path, (FSVirtualNode*[128]){ &FSVirtualRoot }, &(size_t){ 1 }, FSVirtualNodeOperationCreate, IntermediateDirectories);
    FSVirtualWriteUnlock(&FSVirtualVolumeLock);
    
    return Node != NULL ? FSOperationSuccess : FSOperationFailure;
}

FSOperation FSManagerVirtualRemove(FSPath Path)
{
    FSVirtualWriteLock(&FSVirtualVolumeLock);
    FSOperation Result = FSManagerVirtualNodeOp(Path, (FSVirtualNode*[128]){ &FSVirtualRoot }, &(size_t){ 1 }, FSVirtualNodeOperationRemove, FALSE) == NULL ? FSOperationSuccess : FSOperationFailure;
    FSVirtualWriteUnlock(&FSVirtualVolumeLock);
    
    return Result;
}

FSOperation FSManagerVirtualMove(FSPath Path, FSPath Destination)
{
    FSOperation Result = FSManagerVirtualCopy(Path, Destination);
    
    if (Result == FSOperationSuccess)
    {
        Result = FSManagerVirtualRemove(Path);
    }
    
    return Result;
}

FSOperation FSManagerVirtualCopy(FSPath Path, FSPath Destination)
{
    FSOperation Result = FSOperationFailure;
    
    if (FSManagerExists(Path))
    {
        if (FSPathIsDirectory(Path))
        {
            if (FSOperationSuccess == (Result = FSManagerCreate(Destination, FALSE)))
            {
                CCOrderedCollection(FSPath) Matches = FSManagerGetContentsAtPath(Path, NULL, FSMatchDefault);
                
                CC_COLLECTION_FOREACH(FSPath, Child, Matches)
                {
                    FSPath ChildDestination = FSPathCopy(Destination);
                    const size_t ChildDestEnd = FSPathGetComponentCount(ChildDestination);
                    size_t Count = FSPathGetComponentCount(Child);
                    
                    FSPathComponent Component;
                    
                    do
                    {
                        Component = FSPathGetComponentAtIndex(Child, --Count);
                        FSPathInsertComponentAtIndex(ChildDestination, FSPathComponentCopy(Component), ChildDestEnd);
                        
                        _Static_assert(FSPathComponentTypeFile == 6 &&
                                       FSPathComponentTypeExtension == 7 &&
                                       FSPathComponentTypeMask == 7, "Path component types have changed");
                    } while((Count) && ((Component & FSPathComponentTypeMask) >= FSPathComponentTypeExtension));
                    
                    FSManagerVirtualCopy(Child, ChildDestination);
                    FSPathDestroy(ChildDestination);
                }
                
                CCCollectionDestroy(Matches);
            }
        }
        
        else
        {
            size_t Size = FSManagerGetSize(Path);
            void *Data;
            CC_SAFE_Malloc(Data, Size,
                           CC_LOG_ERROR("Failed to copy file due to memory allocation failure. Allocation size (%zu)", Size);
                           return FSOperationFailure;
                           );
            
            FSHandle Handle;
            if (FSOperationSuccess == FSHandleOpen(Path, FSHandleTypeRead, &Handle))
            {
                if (FSOperationSuccess == FSHandleRead(Handle, &Size, Data, FSBehaviourDefault))
                {
                    if (FSOperationSuccess == FSManagerCreate(Destination, FALSE))
                    {
                        FSHandle DestinationHandle;
                        if (FSOperationSuccess == FSHandleOpen(Destination, FSHandleTypeWrite, &DestinationHandle))
                        {
                            Result = FSHandleWrite(DestinationHandle, Size, Data, FSBehaviourDefault);
                            FSHandleClose(DestinationHandle);
                        }
                    }
                }
                
                FSHandleClose(Handle);
            }
            
            CC_SAFE_Free(Data);
        }
    }
    
    return Result;
}
