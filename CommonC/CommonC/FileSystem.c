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

#include "FileSystem.h"
#import "Platform.h"
#import "OrderedCollection.h"
#import "CollectionEnumerator.h"

#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
//SystemPath.m
#elif CC_PLATFORM_UNIX
#error Add support for unix
#elif CC_PLATFORM_WINDOWS
#error Add support for windows
#else
#warning Unsupported platform
#endif

FSOperation FSManagerRename(FSPath Path, const char *Name)
{
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
