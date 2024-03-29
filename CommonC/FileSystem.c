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
FSVirtualNode FSVirtualRoot = {
    .isDir = TRUE,
    .nodes = NULL
};
FSVirtualLock FSVirtualVolumeLock = ATOMIC_VAR_INIT(0);

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

void FSVirtualFileDestructor(FSVirtualFile *File)
{
    CCArrayDestroy(File->contents);
}

static void FSManagerVirtualNodeElementDestructor(CCDictionary Dictionary, FSVirtualNode *Element)
{
    if (Element->isDir)
    {
        CCDictionaryDestroy(Element->nodes);
    }
    
    else
    {
        FSVirtualFileDestroy(Element->file);
    }
}

static inline CCDictionary FSManagerVirtualCreateDir(void)
{
    return CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeMedium | CCDictionaryHintHeavyFinding | CCDictionaryHintHeavyInserting, sizeof(CCString), sizeof(FSVirtualNode), &(CCDictionaryCallbacks){
        .keyDestructor = CCStringDestructorForDictionary,
        .valueDestructor = (CCDictionaryElementDestructor)FSManagerVirtualNodeElementDestructor,
        .getHash = CCStringHasherForDictionary,
        .compareKeys = CCStringComparatorForDictionary
    });
}

static void FSManagerVirtualInit(void)
{
    static atomic_flag Lock = ATOMIC_FLAG_INIT;
    
    while (!atomic_flag_test_and_set_explicit(&Lock, memory_order_acquire)) CC_SPIN_WAIT();
    
    if (!FSVirtualRoot.nodes)
    {
        FSVirtualRoot.nodes = FSManagerVirtualCreateDir();
    }
    
    atomic_flag_clear_explicit(&Lock, memory_order_release);
}

typedef enum {
    FSVirtualNodeOperationNone,
    FSVirtualNodeOperationCreate,
    FSVirtualNodeOperationRemove
} FSVirtualNodeOperation;

static FSVirtualNode *FSManagerVirtualNodeOp(FSPath Path, FSVirtualNode *Dirs[128], size_t *Level, FSVirtualNodeOperation Op, _Bool IntermediateDirectories)
{
    if (!FSVirtualRoot.nodes) FSManagerVirtualInit();
    
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
                Node = File ? NULL : FSManagerVirtualNodeOp(FSPathCurrent(), Dirs, Level, FSVirtualNodeOperationNone, FALSE);
                break;
                
            case FSPathComponentTypeDirectory:
                if ((Node) && (Node->isDir))
                {
                    const _Bool Create = Op == FSVirtualNodeOperationCreate ? (Index == Count ? TRUE : IntermediateDirectories) : FALSE;
                    
                    CCString Key = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, FSPathComponentGetString(Component));
                    FSVirtualNode *Temp = CCDictionaryGetValue(Node->nodes, &Key);
                    if ((!Temp) && (Create))
                    {
                        CCDictionaryEntry Entry = CCDictionaryEntryForKey(Node->nodes, &Key);
                        CCDictionarySetEntry(Node->nodes, Entry, &(FSVirtualNode){
                            .isDir = TRUE,
                            .nodes = FSManagerVirtualCreateDir()
                        });
                        
                        Temp = CCDictionaryGetEntry(Node->nodes, Entry);
                    }
                    
                    CCStringDestroy(Key);
                    
                    Node = Temp;
                    
                    if (!Node->isDir) Node = NULL;
                }
                
                else Node = NULL;
                break;
                
            case FSPathComponentTypeRelativeParentDirectory:
                Node = Dirs[--(*Level)];
                break;
                
            case FSPathComponentTypeFile:
                if ((Node) && (Node->isDir) && (!File))
                {
                    File = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, FSPathComponentGetString(Component));
                }
                
                else Node = NULL;
                break;
                
            case FSPathComponentTypeExtension:
                if ((Node) && (Node->isDir))
                {
                    CCString Ext = File = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, FSPathComponentGetString(Component));
                    
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
    
    if (File)
    {
        if (Node)
        {
            if (Op == FSVirtualNodeOperationRemove)
            {
                CCDictionaryRemoveValue(Node->nodes, &File);
                Node = NULL;
            }
            
            else
            {
                Node = CCDictionaryGetValue(Node->nodes, &File);
                
                if ((!Node) && (Op == FSVirtualNodeOperationCreate))
                {
                    CCDictionaryEntry Entry = CCDictionaryEntryForKey(Node->nodes, &File);
                    CCDictionarySetEntry(Node->nodes, Entry, &(FSVirtualNode){
                        .isDir = FALSE,
                        .file = FSVirtualFileCreate()
                    });
                    
                    Node = CCDictionaryGetEntry(Node->nodes, Entry);
                }
            }
        }
        
        CCStringDestroy(File);
    }
    
    else if ((Node) && (Op == FSVirtualNodeOperationRemove))
    {
        FSPathComponent Component = FSPathGetComponentAtIndex(Path, Count - 1);
        switch (FSPathComponentGetType(Component))
        {
            case FSPathComponentTypeVolume:
            case FSPathComponentTypeRoot:
            case FSPathComponentTypeRelativeRoot:
            case FSPathComponentTypeRelativeParentDirectory:
                CCDictionaryDestroy(Dirs[*Level - 1]->nodes);
                Dirs[*Level - 1]->nodes = FSManagerVirtualCreateDir();
                break;
                
            case FSPathComponentTypeDirectory:
            {
                CCString Key = CCStringCreate(CC_STD_ALLOCATOR, (CCStringHint)CCStringEncodingUTF8, FSPathComponentGetString(Component));
                CCDictionaryRemoveValue(Dirs[*Level - 1]->nodes, &Key);
                CCStringDestroy(Key);
                break;
            }
                
            default:
                break;
        }
        
        Node = NULL;
    }
    
    return Node;
}

static FSVirtualNode *FSManagerVirtualNode(FSPath Path)
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
    FSManagerVirtualNodeOp(Path, (FSVirtualNode*[128]){ &FSVirtualRoot }, &(size_t){ 1 }, FSVirtualNodeOperationRemove, FALSE);
    FSVirtualWriteUnlock(&FSVirtualVolumeLock);
    
    return FSOperationSuccess;
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
                    const size_t Count = FSPathGetComponentCount(Path);
                    
                    FSPathComponent Component = FSPathGetComponentAtIndex(Path, Count - 1);
                    FSPathAppendComponent(ChildDestination, FSPathComponentCopy(Component));
                    
                    switch (FSPathComponentGetType(Component))
                    {
                        case FSPathComponentTypeFile:
                        case FSPathComponentTypeExtension:
                        {
                            _Static_assert(FSPathComponentTypeFile == 6 &&
                                           FSPathComponentTypeExtension == 7 &&
                                           FSPathComponentTypeMask == 7, "Path component types have changed");
                            
                            for (size_t Loop = 2, ChildDestCount = FSPathGetComponentCount(ChildDestination); (Loop < Count) && ((Component = FSPathGetComponentAtIndex(Path, Count - Loop)) & 6); Loop++)
                            {
                                FSPathInsertComponentAtIndex(ChildDestination, FSPathComponentCopy(Component), ChildDestCount);
                            }
                            break;
                        }
                            
                        default:
                            break;
                    }
                    
                    FSManagerVirtualCopy(Child, Destination);
                    FSPathDestroy(Destination);
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
