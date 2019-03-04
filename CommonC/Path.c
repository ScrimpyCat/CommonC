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

#include "Path.h"
#include "MemoryAllocation.h"
#include "Logging.h"
#include "Assertion.h"
#include "CollectionEnumerator.h"
#include "TypeCallbacks.h"
#include "Types.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


static void FSPathClearPathStringCache(FSPath Path);

static _Bool FSPathFoundComponentTypeFromInputs(char CurrentCharacter, char FirstCharacter, int SlashCount, int DotCount, int CharacterCount, FSPathComponentType *Type)
{
    switch (FirstCharacter)
    {
        case '/': //volume, root
            if (((!CurrentCharacter) || (CurrentCharacter == '/')) && (SlashCount == 2) && (!DotCount) && (CharacterCount)) //volume
            {
                *Type = FSPathComponentTypeVolume;
                return TRUE;
            }
            
            else if (((!CurrentCharacter) || (CurrentCharacter != '/')) && (SlashCount == 1) && (!DotCount) && (!CharacterCount)) //root
            {
                *Type = FSPathComponentTypeRoot;
                return TRUE;
            }
            break;
            
        case '.': //relative parent directory, extension, file
            if ((SlashCount) && (DotCount == 2) && (!CharacterCount)) //relative parent directory
            {
                *Type = FSPathComponentTypeRelativeParentDirectory;
                return TRUE;
            }
            
            else if (((!CurrentCharacter) || (CurrentCharacter == '.')) && (!SlashCount) && (DotCount == 1) && (CharacterCount)) //extension
            {
                *Type = FSPathComponentTypeExtension;
                return TRUE;
            }
            break;
            
        default: //directory, file
            if ((SlashCount) && (!DotCount) && (CharacterCount)) //directory
            {
                *Type = FSPathComponentTypeDirectory;
                return TRUE;
            }
            
            else if (((!CurrentCharacter) || (CurrentCharacter == '.')) && (!SlashCount) && (!DotCount) && (CharacterCount)) //file
            {
                *Type = FSPathComponentTypeFile;
                return TRUE;
            }
            break;
    }
    
    return FALSE;
}

static char *FSPathCopyString(const char *String, size_t Length)
{
    char *NewString;
    CC_SAFE_Malloc(NewString, sizeof(char) * (Length + 1),
                   CC_LOG_ERROR("Failed to copy path string. Allocation size: %zu", sizeof(char) * (Length + 1));
                   return NULL;
                   );
    
    strncpy(NewString, String, Length);
    NewString[Length] = 0;
    
    return NewString;
}

static FSPathComponent FSPathCreateComponent(FSPathComponentType Type, const char *String, size_t Length)
{
    char *Component = NULL;
    switch (Type)
    {
        case FSPathComponentTypeVolume:
            Component = FSPathCopyString(String + 2, Length - 2);
            break;
            
        case FSPathComponentTypeDirectory:
            Component = FSPathCopyString(String, Length - 1);
            break;
            
        case FSPathComponentTypeFile:
            Component = FSPathCopyString(String, Length);
            break;
            
        case FSPathComponentTypeExtension:
            Component = FSPathCopyString(String + 1, Length - 1);
            break;
            
        default:
            break;
    }
    
    FSPathComponent PathComponent = FSPathComponentCreate(Type, Component);
    if (Component) CC_SAFE_Free(Component);
    
    return PathComponent;
}

CCOrderedCollection FSPathConvertPathToComponents(const char *Path, _Bool CompletePath)
{
    CCOrderedCollection Components = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered, sizeof(FSPathComponent), FSPathComponentDestructorForCollection);
    
    FSPathComponentType Type;
    const char *Start = Path;
    int SlashCount = 0, DotCount = 0, CharacterCount = 0;
    _Bool HasFile = FALSE;
    for (char c; (c = *Path); Path++)
    {
        if (FSPathFoundComponentTypeFromInputs(c, *Start, SlashCount, DotCount, CharacterCount, &Type))
        {
            if (!HasFile)
            {
                if (Type == FSPathComponentTypeFile) HasFile = TRUE;
                else if (Type == FSPathComponentTypeExtension)
                {
                    Type = FSPathComponentTypeFile;
                    HasFile = TRUE;
                }
            }
            
            FSPathComponent Component = FSPathCreateComponent(Type, Start, Path - Start);
            
            CCOrderedCollectionAppendElement(Components, &Component);
            
            Start = Path;
            SlashCount = 0;
            DotCount = 0;
            CharacterCount = 0;
        }
        
        else if ((HasFile) && (c == '/')) //Fixup directories that contain '.'
        {
            for (FSPathComponent *Component; (Component = CCOrderedCollectionGetLastElement(Components)) && ((FSPathComponentGetType(*Component) == FSPathComponentTypeExtension) || (FSPathComponentGetType(*Component) == FSPathComponentTypeFile)); CCOrderedCollectionRemoveLastElement(Components))
            {
                Start -= strlen(FSPathComponentGetString(*Component)) + 1;
            }
            
            FSPathComponent Component = FSPathCreateComponent(FSPathComponentTypeDirectory, Start + 1, Path - Start);
            
            CCOrderedCollectionAppendElement(Components, &Component);
            
            HasFile = FALSE;
            Start = Path + 1;
            SlashCount = 0;
            DotCount = 0;
            CharacterCount = 0;
            continue;
        }
        
        switch (c)
        {
            case '/':
                SlashCount++;
                break;
                
            case '.':
                DotCount++;
                break;
                
            default:
                CharacterCount++;
                break;
        }
    }
    
    
    if (FSPathFoundComponentTypeFromInputs('\0', *Start, SlashCount, DotCount, CharacterCount, &Type))
    {
        CCOrderedCollectionAppendElement(Components, &(FSPathComponent){ FSPathCreateComponent(Type, Start, Path - Start) });
    }
    
    if ((CompletePath) && (CCCollectionGetCount(Components)))
    {
        FSPathComponentType Type = FSPathComponentGetType(*(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Components, 0));
        if ((Type != FSPathComponentTypeVolume) && (Type != FSPathComponentTypeRoot))
        {
            CCOrderedCollectionPrependElement(Components, &(FSPathComponent){ FSPathComponentCreate(FSPathComponentTypeRelativeRoot, NULL) });
        }
    }
    
    return Components;
}

//CCOrderedCollection FSPathConvertSystemPathToComponents(const char *Path, _Bool CompletePath);
//FSPath FSPathCurrent(void);
//CC_NEW FSPath FSPathCreateAppData(const char *AppName);
#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
//SystemPath.m
#elif CC_PLATFORM_UNIX
#error Add support for unix
#elif CC_PLATFORM_WINDOWS
#error Add support for windows
#else
#warning Unsupported platform
#endif

FSPath FSPathCreateFromComponents(CCOrderedCollection Components)
{
    CCAssertLog(Components, "Components must not be null");
    
    FSPath NewPath;
    CC_SAFE_Malloc(NewPath, sizeof(FSPathInfo),
                   CC_LOG_ERROR("Failed to create path due to failing to allocate path. Allocation size: %zu", sizeof(FSPathInfo));
                   return NULL;
                   );
    
    *NewPath = (FSPathInfo){
        .components = Components,
        .completeRep = NULL,
        .filenameRep = NULL,
        .pathRep = NULL
    };
    
    return NewPath;
}

FSPath FSPathCreate(const char *Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    return FSPathCreateFromComponents(FSPathConvertPathToComponents(Path, TRUE));
}

FSPath FSPathCreateFromSystemPath(const char *Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    return FSPathCreateFromComponents(FSPathConvertSystemPathToComponents(Path, TRUE));
}

FSPath FSPathCopy(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollection Components = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered, sizeof(FSPathComponent), FSPathComponentDestructorForCollection);
    
    CC_COLLECTION_FOREACH(FSPathComponent, Element, Path->components)
    {
        CCOrderedCollectionAppendElement(Components, &(FSPathComponent){ FSPathComponentCopy(Element) });
    }
    
    return FSPathCreateFromComponents(Components);
}

void FSPathDestroy(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    CCAssertLog(Path != FSPathCurrent(), "Cannot mutate the current path");
    
    CCCollectionDestroy(Path->components);
    FSPathClearPathStringCache(Path);
    CC_SAFE_Free(Path);
}

static void FSPathMutated(FSPath Path)
{
    CCAssertLog(Path != FSPathCurrent(), "Cannot mutate the current path");
    
    FSPathClearPathStringCache(Path);
}

size_t FSPathGetComponentCount(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    return CCCollectionGetCount(Path->components);
}

FSPathComponent FSPathGetComponentAtIndex(FSPath Path, size_t Index)
{
    CCAssertLog(Path, "Path must not be null");
    
    return *(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Path->components, Index);
}

void FSPathSetComponentAtIndex(FSPath Path, FSPathComponent Component, size_t Index)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollectionReplaceElementAtIndex(Path->components, &Component, Index);
    FSPathMutated(Path);
}

void FSPathInsertComponentAtIndex(FSPath Path, FSPathComponent Component, size_t Index)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollectionInsertElementAtIndex(Path->components, &Component, Index);
    FSPathMutated(Path);
}

void FSPathAppendComponent(FSPath Path, FSPathComponent Component)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollectionAppendElement(Path->components, &Component);
    FSPathMutated(Path);
}

void FSPathPrependComponent(FSPath Path, FSPathComponent Component)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollectionPrependElement(Path->components, &Component);
    FSPathMutated(Path);
}

void FSPathRemoveComponentIndex(FSPath Path, size_t Index)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollectionRemoveElementAtIndex(Path->components, Index);
    FSPathMutated(Path);
}

void FSPathRemoveComponentLast(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    CCOrderedCollectionRemoveLastElement(Path->components);
    FSPathMutated(Path);
}

static void FSPathClearPathStringCache(FSPath Path)
{
    CC_SAFE_Free(Path->completeRep);
    Path->filenameRep = NULL;
    Path->pathRep = NULL;
}

static void FSPathCreatePathStringCache(FSPath Path)
{
    if (Path->completeRep) FSPathClearPathStringCache(Path);
    
    _Bool RequiresVolume = TRUE;
    size_t Length = 0;
    CC_COLLECTION_FOREACH(FSPathComponent, Component, Path->components)
    {
        const char *ComponentString = FSPathComponentGetString(Component);
        if (ComponentString) Length += strlen(ComponentString);
        switch (FSPathComponentGetType(Component))
        {
            case FSPathComponentTypeVolume:
                RequiresVolume = FALSE;
            case FSPathComponentTypeRoot:
                Length += 2;
                break;
                
            case FSPathComponentTypeRelativeRoot:
                RequiresVolume = FALSE;
                Length += strlen(FSPathGetFullPathString(FSPathCurrent()));
                break;
                
            case FSPathComponentTypeDirectory:
            case FSPathComponentTypeExtension:
                Length += 1;
                break;
                
            case FSPathComponentTypeRelativeParentDirectory:
                Length += 3;
                break;
                
            default:
                break;
        }
    }
    
    
    if (Length)
    {
        const char *Volume = NULL;
        if (RequiresVolume)
        {
            Volume = FSPathComponentGetString(FSPathGetVolume(Path));
            Length += 2 + strlen(Volume);
        }
        
        CC_SAFE_Malloc(Path->completeRep, sizeof(char) * (Length + 1),
                       CC_LOG_ERROR("Failed to create path string, due to allocation failure. Allocation size: %zu", sizeof(char) * (Length + 1));
                       return;
                       );
        
        char *Current = Path->completeRep;
        if (Volume)
        {
            Current += sprintf(Current, "//%s", Volume);
        }
        
        CC_COLLECTION_FOREACH(FSPathComponent, Component, Path->components)
        {
            switch (FSPathComponentGetType(Component))
            {
                case FSPathComponentTypeVolume:
                    if (!Path->pathRep) Path->pathRep = Current;
                    Current += sprintf(Current, "//%s", FSPathComponentGetString(Component));
                    break;
                    
                case FSPathComponentTypeRoot:
                    if (!Path->pathRep) Path->pathRep = Current;
                    Current += sprintf(Current, "/");
                    break;
                    
                case FSPathComponentTypeRelativeRoot:
                    Current += sprintf(Current, "%s", FSPathGetFullPathString(FSPathCurrent()));
                    break;
                    
                case FSPathComponentTypeDirectory:
                    if (!Path->pathRep) Path->pathRep = Current;
                    Current += sprintf(Current, "%s/", FSPathComponentGetString(Component));
                    break;
                    
                case FSPathComponentTypeRelativeParentDirectory:
                    if (!Path->pathRep) Path->pathRep = Current;
                    Current += sprintf(Current, "../");
                    break;
                    
                case FSPathComponentTypeFile:
                    if (!Path->filenameRep) Path->filenameRep = Current;
                    Current += sprintf(Current, "%s", FSPathComponentGetString(Component));
                    break;
                    
                case FSPathComponentTypeExtension:
                    if (!Path->filenameRep) Path->filenameRep = Current;
                    Current += sprintf(Current, ".%s", FSPathComponentGetString(Component));
                    break;
                    
                default:
                    break;
            }
        }
        
        if (!Path->pathRep) Path->pathRep = Path->filenameRep;
    }
}

const char *FSPathGetFullPathString(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    if (!Path->completeRep) FSPathCreatePathStringCache(Path);
    
    return Path->completeRep;
}

const char *FSPathGetPathString(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    if (!Path->pathRep) FSPathCreatePathStringCache(Path);
    
    return Path->pathRep;
}

const char *FSPathGetFilenameString(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    if (!Path->filenameRep) FSPathCreatePathStringCache(Path);
    
    return Path->filenameRep;
}

FSPathComponent FSPathGetVolume(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    FSPathComponent Component = *(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Path->components, 0);
    if (FSPathComponentGetType(Component) == FSPathComponentTypeVolume)
    {
        return Component;
    }
    
    else if (Path != FSPathCurrent())
    {
        return FSPathGetVolume(FSPathCurrent());
    }
    
    return (FSPathComponent)FSPathComponentTypeInvalid;
}

_Bool FSPathIsDirectory(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    return !FSPathIsFile(Path);
}

_Bool FSPathIsFile(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    FSPathComponentType Type = CCCollectionGetCount(Path->components) ? FSPathComponentGetType(*(FSPathComponent*)CCCollectionGetElement(Path->components, CCOrderedCollectionGetLastEntry(Path->components))) : FSPathComponentTypeInvalid;
    return (Type == FSPathComponentTypeExtension) || (Type == FSPathComponentTypeFile);
}

_Bool FSPathIsRelativePath(FSPath Path)
{
    CCAssertLog(Path, "Path must not be null");
    
    return CCCollectionGetCount(Path->components) ? FSPathComponentGetType(*(FSPathComponent*)CCOrderedCollectionGetElementAtIndex(Path->components, 0)) == FSPathComponentTypeRelativeRoot : FALSE;
}

_Bool FSPathMatch(FSPath Left, FSPath Right, FSMatch MatchOptions)
{
    CCAssertLog(Left, "Left must not be null");
    CCAssertLog(Right, "Right must not be null");
    
    CCEnumerator LeftEnumerator, RightEnumerator;
    CCCollectionGetEnumerator(Left->components, &LeftEnumerator);
    CCCollectionGetEnumerator(Right->components, &RightEnumerator);
    
    const char Wildcard = (MatchOptions & FSMatchNameOptionWildcardIsLiteral) ? 0 : (((unsigned int)(MatchOptions & FSMatchNameOptionWildcardMask) >> FSMatchNameOptionWildcard) ? ((unsigned int)(MatchOptions & FSMatchNameOptionWildcardMask) >> FSMatchNameOptionWildcard) : '*');
    for (FSPathComponent *LeftComponent = CCCollectionEnumeratorGetTail(&LeftEnumerator), *RightComponent = CCCollectionEnumeratorGetTail(&RightEnumerator); (LeftComponent) && (RightComponent); LeftComponent = CCCollectionEnumeratorPrevious(&LeftEnumerator), RightComponent = CCCollectionEnumeratorPrevious(&RightEnumerator))
    {
        if (FSPathComponentGetType(*LeftComponent) == FSPathComponentGetType(*RightComponent))
        {
            const char *LeftString = FSPathComponentGetString(*LeftComponent), *RightString = FSPathComponentGetString(*RightComponent);
            
            if ((Wildcard) && (((LeftString) && (*LeftString == Wildcard)) || ((RightString) && (*RightString == Wildcard)))) continue;
            
            if (LeftString != RightString)
            {
                if ((LeftString) && (RightString))
                {
                    if (MatchOptions & FSMatchNameOptionCaseSensitive)
                    {
                        if (strcmp(LeftString, RightString)) return FALSE;
                    }
                    
                    else
                    {
                        for ( ; (*LeftString) && (*RightString) && (tolower(*LeftString) == tolower(*RightString)); LeftString++, RightString++);
                        if (*LeftString != *RightString) return FALSE;
                    }
                }
            }
        }
        
        else if ((MatchOptions & FSMatchNameOptionRequireRelativeRoot) ||
                 ((FSPathComponentGetType(*LeftComponent) != FSPathComponentTypeRelativeRoot) &&
                  (FSPathComponentGetType(*RightComponent) != FSPathComponentTypeRelativeRoot))) return FALSE;
    }
    
    return TRUE;
}
