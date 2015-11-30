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

#import <Foundation/Foundation.h>
#import "Platform.h"
#import "MemoryAllocation.h"
#import "Logging.h"
#import "OrderedCollection.h"
#import "CollectionEnumerator.h"
#import "Allocator.h"
#import "Assertion.h"
#import "Path.h"
#import "FileHandle.h"
#import "FileSystem.h"


#pragma mark Path
static void FSPathComponentElementDestructor(CCCollection Collection, FSPathComponent *Element)
{
    FSPathComponentDestroy(*Element);
}

CCOrderedCollection FSPathConvertSystemPathToComponents(const char *Path, _Bool CompletePath)
{
    CCOrderedCollection Components = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered, sizeof(FSPathComponent), (CCCollectionElementDestructor)FSPathComponentElementDestructor);
    
#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
    @autoreleasepool {
        NSString *ExpandedPath = [[NSString stringWithUTF8String: Path] stringByExpandingTildeInPath];
        NSURL *URLPath = [NSURL fileURLWithPath: ExpandedPath];
        
        NSNumber *Dir;
        if (![URLPath getResourceValue: &Dir forKey: NSURLIsDirectoryKey error: NULL])
        {
            Dir = @([URLPath.absoluteString hasSuffix: @"/"]);
        }
        
        _Bool VolumeComponent = FALSE, HasRoot = FALSE, IsDir = [Dir boolValue];
        NSUInteger Count = ExpandedPath.pathComponents.count, Index = 0;
        for (NSString *PathComponent in ExpandedPath.pathComponents)
        {
            if ([PathComponent isEqualToString: @"/"])
            {
                HasRoot = TRUE;
                CCOrderedCollectionAppendElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeRoot, NULL) });
            }
            
            else if ((Index == 1) && ([PathComponent isEqualToString: @"Volumes"]))
            {
                VolumeComponent = HasRoot;
            }
            
            else if ((Index == 2) && (VolumeComponent))
            {
                CCOrderedCollectionPrependElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeVolume, [PathComponent UTF8String]) });
            }
            
            else if (((Index + 1) == Count) && (!IsDir))
            {
                //TODO: Change collections so destructors can be temporarily disabled or make a consumable insertion
                CCOrderedCollection FileComponents = FSPathConvertPathToComponents([PathComponent UTF8String], FALSE);
                
                CC_COLLECTION_FOREACH(FSPathComponent, Element, FileComponents)
                {
                    CCOrderedCollectionAppendElement(Components, &(FSPathComponent){ FSPathComponentCopy(Element) });
                }
                
                CCCollectionDestroy(FileComponents);
            }
            
            else
            {
                CCOrderedCollectionAppendElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeDirectory, [PathComponent UTF8String]) });
            }
            
            Index++;
        }
        
        if ((CompletePath) && (!HasRoot))
        {
            CCOrderedCollectionPrependElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeRelativeRoot, NULL) });
        }
    }
#elif CC_PLATFORM_UNIX
#error Add support for unix
#elif CC_PLATFORM_WINDOWS
#error Add support for windows
#else
#warning Unsupported platform
#endif
    
    return Components;
}

FSPath FSPathCurrent(void)
{
    /*
     Potental issues with threading unless add locks around any FSCurrentPath usage. May be better to just
     implement FSPathCreateFromCurrent()
     */
    static FSPathInfo FSCurrentPath;
    if (!FSCurrentPath.components)
    {
        @autoreleasepool {
            NSString *CurrentPath = [NSFileManager defaultManager].currentDirectoryPath;
            CCOrderedCollection Components = FSPathConvertSystemPathToComponents([CurrentPath UTF8String], FALSE);
            
            if ((CCCollectionGetCount(Components) >= 1) && (FSPathComponentGetType(*(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Components, 0)) != FSPathComponentTypeVolume))
            {
                NSString *Volume;
                [[NSURL fileURLWithPath: CurrentPath] getResourceValue: &Volume forKey:NSURLVolumeNameKey error: NULL];
                
                CCOrderedCollectionPrependElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeVolume, [Volume UTF8String]) });
            }
            
            FSCurrentPath.components = Components;
        }
    }
    
    return &FSCurrentPath;
}

#pragma mark - FileSystem

static NSURL *FSPathSystemInternalRepresentation(FSPath Path)
{
    NSURL *SystemPath = nil;
    CC_COLLECTION_FOREACH(FSPathComponent, Component, Path->components)
    {
        switch (FSPathComponentGetType(Component))
        {
            case FSPathComponentTypeVolume:
                SystemPath = [NSURL fileURLWithPath: [NSString stringWithFormat: @"/Volumes/%s/", FSPathComponentGetString(Component)] isDirectory: YES];
                break;
                
            case FSPathComponentTypeRoot:
                if (!SystemPath) SystemPath = [NSURL fileURLWithPath: @"/" isDirectory: YES];
                break;
                
            case FSPathComponentTypeRelativeRoot:
                SystemPath = [NSURL fileURLWithPath: [NSFileManager defaultManager].currentDirectoryPath isDirectory: YES];
                break;
                
            case FSPathComponentTypeDirectory:
                SystemPath = [SystemPath URLByAppendingPathComponent: [NSString stringWithUTF8String: FSPathComponentGetString(Component)] isDirectory: YES];
                break;
                
            case FSPathComponentTypeRelativeParentDirectory:
                SystemPath = SystemPath.URLByDeletingLastPathComponent;
                break;
                
            case FSPathComponentTypeFile:
                SystemPath = [SystemPath URLByAppendingPathComponent: [NSString stringWithUTF8String: FSPathComponentGetString(Component)] isDirectory: NO];
                break;
                
            case FSPathComponentTypeExtension:
                SystemPath = [SystemPath URLByAppendingPathExtension: [NSString stringWithUTF8String: FSPathComponentGetString(Component)]];
                break;
                
            default:
                break;
        }
    }
    
    return SystemPath;
}

_Bool FSManagerExists(FSPath Path)
{
    @autoreleasepool {
        BOOL IsDir;
        _Bool Exists = [[NSFileManager defaultManager] fileExistsAtPath: FSPathSystemInternalRepresentation(Path).path isDirectory: &IsDir];
        
        return (Exists) && (IsDir == FSPathIsDirectory(Path));
    }
}

FSAccess FSManagerGetAccessRights(FSPath Path)
{
    @autoreleasepool {
        NSString *SystemPath = FSPathSystemInternalRepresentation(Path).path;
        NSFileManager *Manager = [NSFileManager defaultManager];
        
        return ((_Bool)[Manager isReadableFileAtPath: SystemPath] * FSAccessReadable)
        | ((_Bool)[Manager isWritableFileAtPath: SystemPath] * FSAccessWritable)
        | ((_Bool)[Manager isExecutableFileAtPath: SystemPath] * FSAccessExecutable)
        | ((_Bool)[Manager isDeletableFileAtPath: SystemPath] * FSAccessDeletable);
    }
}

size_t FSManagerGetSize(FSPath Path)
{
    @autoreleasepool {
        NSNumber *Size;
        [FSPathSystemInternalRepresentation(Path) getResourceValue: &Size forKey: NSURLFileSizeKey error: NULL];
        
        return (size_t)Size.unsignedLongLongValue;
    }
}

size_t FSManagerGetPreferredIOBlockSize(FSPath Path)
{
    @autoreleasepool {
        NSNumber *Size;
        [FSPathSystemInternalRepresentation(Path) getResourceValue: &Size forKey: NSURLPreferredIOBlockSizeKey error: NULL];
        
        return (size_t)Size.unsignedLongLongValue;
    }
}

FSOperation FSManagerCreate(FSPath Path, _Bool IntermediateDirectories)
{
    if (!FSManagerExists(Path))
    {
        @autoreleasepool {
            _Bool Success = FALSE;
            NSURL *SystemPath = FSPathSystemInternalRepresentation(Path);
            
            if (FSPathIsFile(Path))
            {
                Success = [[NSFileManager defaultManager] createDirectoryAtURL: SystemPath.URLByDeletingLastPathComponent
                                                   withIntermediateDirectories: IntermediateDirectories
                                                                    attributes: nil
                                                                         error: NULL];
                
                if (Success)
                {
                    Success = [[NSFileManager defaultManager] createFileAtPath: SystemPath.path
                                                                      contents: nil
                                                                    attributes: nil];
                }
            }
            
            else
            {
                Success = [[NSFileManager defaultManager] createDirectoryAtURL: SystemPath
                                                   withIntermediateDirectories: IntermediateDirectories
                                                                    attributes: nil
                                                                         error: NULL];
            }
            
            return Success ? FSOperationSuccess : FSOperationFailure;
        }
    }
    
    return FSOperationSuccess;
}

FSOperation FSManagerRemove(FSPath Path)
{
    if (FSManagerExists(Path))
    {
        @autoreleasepool {
            _Bool Success = [[NSFileManager defaultManager] removeItemAtURL: FSPathSystemInternalRepresentation(Path) error: NULL];
            
            return Success ? FSOperationSuccess : FSOperationFailure;
        }
    }
    
    return FSOperationSuccess;
}

FSOperation FSManagerMove(FSPath Path, FSPath Destination)
{
    if (FSManagerExists(Path))
    {
        @autoreleasepool {
            _Bool Success = [[NSFileManager defaultManager] moveItemAtURL: FSPathSystemInternalRepresentation(Path)
                                                                    toURL: FSPathSystemInternalRepresentation(Destination)
                                                                    error: NULL];
            
            return Success ? FSOperationSuccess : FSOperationFailure;
        }
    }
    
    return FSOperationPathNotExist;
}

FSOperation FSManagerCopy(FSPath Path, FSPath Destination)
{
    if (FSManagerExists(Path))
    {
        @autoreleasepool {
            _Bool Success = [[NSFileManager defaultManager] copyItemAtURL: FSPathSystemInternalRepresentation(Path)
                                                                    toURL: FSPathSystemInternalRepresentation(Destination)
                                                                    error: NULL];
            
            return Success ? FSOperationSuccess : FSOperationFailure;
        }
    }
    
    return FSOperationPathNotExist;
}

#pragma mark - FileHandle

FSOperation FSHandleOpen(FSPath Path, FSHandleType Type, FSHandle *Handle)
{
    if (FSManagerExists(Path))
    {
        @autoreleasepool {
            NSURL *SystemPath = FSPathSystemInternalRepresentation(Path);
            NSFileHandle *File = nil;
            
            if (Type == FSHandleTypeRead) File = [NSFileHandle fileHandleForReadingFromURL: SystemPath error: NULL];
            else if (Type == FSHandleTypeWrite) File = [NSFileHandle fileHandleForWritingToURL: SystemPath error: NULL];
            else if (Type == FSHandleTypeUpdate) File = [NSFileHandle fileHandleForUpdatingURL: SystemPath error: NULL];
            
            CC_SAFE_Malloc(*Handle, sizeof(FSHandleInfo),
                           CC_LOG_ERROR("Failed to open file handle due to memory allocation failure. Allocation size (%zu)", sizeof(FSHandleInfo));
                           return FSOperationFailure;
                           );
            
            **Handle = (FSHandleInfo){
                .type = Type,
                .path = FSPathCopy(Path),
                .handle = [File retain]
            };
            
            return FSOperationSuccess;
        }
    }
    
    return FSOperationPathNotExist;
}

FSOperation FSHandleClose(FSHandle Handle)
{
    if (!Handle->handle) return FSOperationFailure;
    
    FSPathDestroy(Handle->path);
    
    @autoreleasepool {
        [(NSFileHandle*)Handle->handle closeFile];
        [(NSFileHandle*)Handle->handle release];
    }
    
    return FSOperationSuccess;
}

FSOperation FSHandleSync(FSHandle Handle)
{
    if (!Handle->handle) return FSOperationFailure;
    
    @autoreleasepool {
        [(NSFileHandle*)Handle->handle synchronizeFile];
    }
    
    return FSOperationSuccess;
}

FSOperation FSHandleRead(FSHandle Handle, size_t *Count, void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Count, "Count must not be NULL");
    CCAssertLog(Data, "Data must not be NULL");
    
    if (!Handle->handle)
    {
        *Count = 0;
        return FSOperationFailure;
    }

    const size_t Offset = FSHandleGetOffset(Handle);
    
    @autoreleasepool {
        NSData *ReadData = [(NSFileHandle*)Handle->handle readDataOfLength: *Count];
        [ReadData getBytes: Data length: *Count];
        
        *Count = ReadData.length;
    }
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, Offset);
    else if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourUpdateOffset) return FSHandleSetOffset(Handle, Offset + *Count);
    
    return FSOperationSuccess;
}

FSOperation FSHandleReadFromOffset(FSHandle Handle, size_t Offset, size_t *Count, void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Count, "Count must not be NULL");
    CCAssertLog(Data, "Data must not be NULL");
    
    if (!Handle->handle)
    {
        *Count = 0;
        return FSOperationFailure;
    }
    
    const size_t OldOffset = FSHandleGetOffset(Handle);
    
    FSHandleSetOffset(Handle, Offset);
    FSOperation Result = FSHandleRead(Handle, Count, Data, Behaviour);
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, OldOffset);
    
    return Result;
}

FSOperation FSHandleWrite(FSHandle Handle, size_t Count, const void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Data, "Data must not be NULL");
    
    if (!Handle->handle) return FSOperationFailure;
    
    const size_t Offset = FSHandleGetOffset(Handle);
    
    @autoreleasepool {
        NSData *WriteData = [NSData dataWithBytesNoCopy: (void*)Data length: Count freeWhenDone: NO];
        if ((Behaviour & FSWritingBehaviourDestructiveMask) == FSWritingBehaviourOverwrite)
        {
            [(NSFileHandle*)Handle->handle writeData: WriteData];
        }
        
        else if ((Behaviour & FSWritingBehaviourDestructiveMask) == FSWritingBehaviourInsert)
        {
#if CC_PLATFORM_OS_X
            size_t ChunkSize = FSManagerGetPreferredIOBlockSize(Handle->path);
#elif CC_PLATFORM_IOS
            size_t ChunkSize = 4096;
#endif
            if (Count > ChunkSize) ChunkSize = Count;
            
            const size_t Size = FSManagerGetSize(Handle->path) - Offset;
            NSData *Chunk = [[(NSFileHandle*)Handle->handle readDataOfLength: ChunkSize] retain];
            
            [(NSFileHandle*)Handle->handle seekToFileOffset: Offset];
            [(NSFileHandle*)Handle->handle writeData: WriteData];
            
            for (size_t Shifted = 0; Shifted < Size; )
            {
                @autoreleasepool {
                    NSData *NextChunk = nil;
                    if (Shifted + Chunk.length < Size)
                    {
                        [(NSFileHandle*)Handle->handle seekToFileOffset: Offset + Shifted + Count];
                        NextChunk = [(NSFileHandle*)Handle->handle readDataOfLength: ChunkSize];
                    }
                    
                    [(NSFileHandle*)Handle->handle seekToFileOffset: Offset + Shifted + Count];
                    [(NSFileHandle*)Handle->handle writeData: Chunk];
                    
                    Shifted += Chunk.length;
                    
                    [Chunk release];
                    Chunk = [NextChunk retain];
                }
            }
            
            [Chunk release];
        }
        
    }
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, Offset);
    else if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourUpdateOffset) return FSHandleSetOffset(Handle, Offset + Count);
    
    return FSOperationSuccess;
}

FSOperation FSHandleWriteFromOffset(FSHandle Handle, size_t Offset, size_t Count, const void *Data, FSBehaviour Behaviour)
{
    CCAssertLog(Data, "Data must not be NULL");
    
    if (!Handle->handle) return FSOperationFailure;
    
    const size_t OldOffset = FSHandleGetOffset(Handle);
    
    FSHandleSetOffset(Handle, Offset);
    FSOperation Result = FSHandleWrite(Handle, Count, Data, Behaviour);
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, OldOffset);
    
    return Result;
}

FSOperation FSHandleRemove(FSHandle Handle, size_t Count, FSBehaviour Behaviour)
{
    if (!Handle->handle) return FSOperationFailure;
    
    const size_t Offset = FSHandleGetOffset(Handle);
    const size_t Size = FSManagerGetSize(Handle->path) - Offset;
    
    
    @autoreleasepool {
        if (Count >= Size)
        {
            [(NSFileHandle*)Handle->handle truncateFileAtOffset: Offset];
        }
        
        else
        {
#if CC_PLATFORM_OS_X
            size_t ChunkSize = FSManagerGetPreferredIOBlockSize(Handle->path);
#elif CC_PLATFORM_IOS
            size_t ChunkSize = 4096;
#endif
            
            for (size_t Shifted = 0; Shifted < (Size - Count); )
            {
                @autoreleasepool {
                    [(NSFileHandle*)Handle->handle seekToFileOffset: Offset + Shifted + Count];
                    NSData *Chunk = [(NSFileHandle*)Handle->handle readDataOfLength: ChunkSize];
                    
                    [(NSFileHandle*)Handle->handle seekToFileOffset: Offset + Shifted];
                    [(NSFileHandle*)Handle->handle writeData: Chunk];
                    
                    Shifted += Chunk.length;
                }
            }
            
            [(NSFileHandle*)Handle->handle truncateFileAtOffset: Offset + Size - Count];
        }
        
    }
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, Offset);
    else if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourUpdateOffset) return FSHandleSetOffset(Handle, Offset + Count);
    
    return FSOperationSuccess;
}

FSOperation FSHandleRemoveFromOffset(FSHandle Handle, size_t Offset, size_t Count, FSBehaviour Behaviour)
{
    if (!Handle->handle) return FSOperationFailure;
    
    const size_t OldOffset = FSHandleGetOffset(Handle);
    
    FSHandleSetOffset(Handle, Offset);
    FSOperation Result = FSHandleRemove(Handle, Count, Behaviour);
    
    if ((Behaviour & FSBehaviourOffsettingMask) == FSBehaviourPreserveOffset) return FSHandleSetOffset(Handle, OldOffset);
    
    return Result;
}

size_t FSHandleGetOffset(FSHandle Handle)
{
    if (Handle->handle)
    {
        @autoreleasepool {
            return [(NSFileHandle*)Handle->handle offsetInFile];
        }
    }
    
    return 0;
}

FSOperation FSHandleSetOffset(FSHandle Handle, size_t Offset)
{
    if (!Handle->handle) return FSOperationFailure;
    
    @autoreleasepool {
        [(NSFileHandle*)Handle->handle seekToFileOffset: Offset];
    }
    
    return FSOperationSuccess;
}
