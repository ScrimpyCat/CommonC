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
#include "OrderedCollection.h"
#include "Assertion.h"


CCCollectionEntry CCOrderedCollectionInsertElementAtIndex(CCOrderedCollection Collection, const void *Element, size_t Index)
{
    CCAssertLog(Collection, "Collection must not be null");
    CCAssertLog(Index <= CCCollectionGetCount(Collection), "Index outside of bounds");
    
    return Collection->interface->optional.ordered->insert(Collection->internal, Element, Index, Collection->allocator, Collection->size);
}

CCCollectionEntry CCOrderedCollectionAppendElement(CCOrderedCollection Collection, const void *Element)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    if (Collection->interface->optional.ordered->optional.append) return Collection->interface->optional.ordered->optional.append(Collection->internal, Element, Collection->allocator, Collection->size);
    else return CCOrderedCollectionInsertElementAtIndex(Collection, Element, CCCollectionGetCount(Collection));
}

CCCollectionEntry CCOrderedCollectionPrependElement(CCOrderedCollection Collection, const void *Element)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    if (Collection->interface->optional.ordered->optional.prepend) return Collection->interface->optional.ordered->optional.prepend(Collection->internal, Element, Collection->allocator, Collection->size);
    else return CCOrderedCollectionInsertElementAtIndex(Collection, Element, 0);
}

CCCollectionEntry CCOrderedCollectionReplaceElementAtIndex(CCOrderedCollection Collection, const void *Element, size_t Index)
{
    CCAssertLog(Collection, "Collection must not be null");
    CCAssertLog(Index < CCCollectionGetCount(Collection), "Index outside of bounds");
    
    if (Collection->interface->optional.ordered->optional.replace)
    {
        if (Collection->destructor)
        {
            Collection->destructor(Collection, CCOrderedCollectionGetElementAtIndex(Collection, Index));
        }
        
        return Collection->interface->optional.ordered->optional.replace(Collection->internal, Element, Index, Collection->allocator, Collection->size);
    }
    
    else
    {
        CCCollectionEntry Entry = CCOrderedCollectionInsertElementAtIndex(Collection, Element, Index);
        CCOrderedCollectionRemoveElementAtIndex(Collection, Index + 1);
        
        return Entry;
    }
}

void CCOrderedCollectionRemoveElementAtIndex(CCOrderedCollection Collection, size_t Index)
{
    CCAssertLog(Collection, "Collection must not be null");
    CCAssertLog(Index < CCCollectionGetCount(Collection), "Index outside of bounds");
    
    if (Collection->interface->optional.ordered->optional.remove)
    {
        if (Collection->destructor)
        {
            Collection->destructor(Collection, CCOrderedCollectionGetElementAtIndex(Collection, Index));
        }
        
        Collection->interface->optional.ordered->optional.remove(Collection->internal, Index, Collection->allocator);
    }
    else CCCollectionRemoveElement(Collection, CCOrderedCollectionGetEntryAtIndex(Collection, Index));
}

void CCOrderedCollectionRemoveLastElement(CCOrderedCollection Collection)
{
    CCAssertLog(Collection, "Collection must not be null");
    CCAssertLog(CCCollectionGetCount(Collection), "Collection must have at least one element");
    
    if (Collection->interface->optional.ordered->optional.removeLast)
    {
        if (Collection->destructor)
        {
            Collection->destructor(Collection, CCOrderedCollectionGetElementAtIndex(Collection, CCCollectionGetCount(Collection) - 1));
        }
        
        Collection->interface->optional.ordered->optional.removeLast(Collection->internal, Collection->allocator);
    }
    else CCOrderedCollectionRemoveElementAtIndex(Collection, CCCollectionGetCount(Collection) - 1);
}

CCCollectionEntry CCOrderedCollectionGetEntryAtIndex(CCOrderedCollection Collection, size_t Index)
{
    CCAssertLog(Collection, "Collection must not be null");
    CCAssertLog(Index < CCCollectionGetCount(Collection), "Index outside of bounds");
    
    return Collection->interface->optional.ordered->entry(Collection->internal, Index);
}

CCCollectionEntry CCOrderedCollectionGetLastEntry(CCOrderedCollection Collection)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    const size_t Count = CCCollectionGetCount(Collection);
    if (!Count) return NULL;
    
    if (Collection->interface->optional.ordered->optional.lastEntry) return Collection->interface->optional.ordered->optional.lastEntry(Collection->internal);
    else return CCOrderedCollectionGetEntryAtIndex(Collection, Count - 1);
}

size_t CCOrderedCollectionGetIndex(CCOrderedCollection Collection, CCCollectionEntry Entry)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    return Collection->interface->optional.ordered->index(Collection->internal, Entry);
}

void *CCOrderedCollectionGetElementAtIndex(CCOrderedCollection Collection, size_t Index)
{
    CCAssertLog(Collection, "Collection must not be null");
    CCAssertLog(Index < CCCollectionGetCount(Collection), "Index outside of bounds");
    
    if (Collection->interface->optional.ordered->optional.element) return Collection->interface->optional.ordered->optional.element(Collection->internal, Index);
    else return CCCollectionGetElement(Collection, CCOrderedCollectionGetEntryAtIndex(Collection, Index));
}

void *CCOrderedCollectionGetLastElement(CCOrderedCollection Collection)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    return CCCollectionGetElement(Collection, CCOrderedCollectionGetLastEntry(Collection));
}
