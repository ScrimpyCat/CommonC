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

#include "Collection.h"
#include "CollectionEnumerator.h"
#include "MemoryAllocation.h"
#include "Logging.h"
#include "Assertion.h"
#include "Types.h"
#include "BitTricks.h"
#include "LinkedList.h"
#include "CollectionArray.h"
#include "CollectionList.h"


typedef struct {
    CCLinkedListNode node;
    const CCCollectionInterface *interface;
} CCCollectionInterfaceNode;

typedef struct {
    int allocator;
    CCCollectionInterfaceNode data;
} CCCollectionInternalInterfaceNode;


const int CCCollectionHintWeightMax = 30000; //CCCollectionHintWeightCreate((UINT_MAX & ~CCCollectionHintSizeMask) | CCCollectionHintSizeLarge, UINT_MAX, 0, 0)

int CCCollectionHintWeightCreate(CCCollectionHint Hint, CCCollectionHint FastHints, CCCollectionHint ModerateHints, CCCollectionHint SlowHints)
{
    const int Size = (int[]){ 10, 1, 100, 0 }[(Hint & CCCollectionHintSizeMask) >> 30];
    Hint &= ~CCCollectionHintSizeMask;
    
    FastHints &= Hint;
    ModerateHints &= Hint;
    SlowHints &= Hint;
    
    return ((int)CCBitCountSet(FastHints) * 10 * Size) + ((int)CCBitCountSet(ModerateHints) * -1 * Size) + ((int)CCBitCountSet(SlowHints) * -100 * Size);
}

const CCCollectionInterface CCCollectionArrayInterface, CCCollectionListInterface;
static CCCollectionInternalInterfaceNode InternalInterfaces[] = {
    { .allocator = -1, .data = { .node = { .prev = NULL, .next = (void*)(InternalInterfaces + 1) + offsetof(CCCollectionInternalInterfaceNode, data) }, .interface = &CCCollectionArrayInterface } },
    { .allocator = -1, .data = { .node = { .prev = (void*)InternalInterfaces + offsetof(CCCollectionInternalInterfaceNode, data), .next = NULL }, .interface = &CCCollectionListInterface } }
};
static CCCollectionInterfaceNode *Interfaces = (void*)InternalInterfaces + offsetof(CCCollectionInternalInterfaceNode, data);
void CCCollectionRegisterInterface(const CCCollectionInterface *Interface)
{
    CCAssertLog(Interface, "Interface must not be null");
    
    CCLinkedListNode *Node = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(CCCollectionInterface*), &Interface);
    if (Node)
    {
        if (Interfaces)
        {
            Interfaces = (CCCollectionInterfaceNode*)CCLinkedListInsert((CCLinkedList)Interfaces, Node);
        }
        
        else Interfaces = (CCCollectionInterfaceNode*)Node;
    }
    
    else
    {
        CC_LOG_ERROR("Failed to add interface (%p): Failed to allocate memory of size (%zu)", Interface, sizeof(CCCollectionInterfaceNode));
    }
}

void CCCollectionDeregisterInterface(const CCCollectionInterface *Interface)
{
    for (CCLinkedListNode *Node = (CCLinkedListNode*)Interfaces; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        if (((CCCollectionInterfaceNode*)Node)->interface == Interface)
        {
            if (CCLinkedListIsHead(Node))
            {
                Interfaces = (CCCollectionInterfaceNode*)CCLinkedListEnumerateNext(Node);
            }
            
            CCLinkedListDestroyNode(Node);
            break;
        }
    }
}

CCCollection CCCollectionCreate(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize, CCCollectionElementDestructor Destructor)
{
    int Weight = INT_MIN;
    const CCCollectionInterface *BestInterface = NULL;
    
    for (CCLinkedListNode *Node = (CCLinkedListNode*)Interfaces; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        const int NewWeight = ((CCCollectionInterfaceNode*)Node)->interface->hintWeight(Hint);
        if (NewWeight > Weight)
        {
            Weight = NewWeight;
            BestInterface = ((CCCollectionInterfaceNode*)Node)->interface;
        }
    }
    
    return CCCollectionCreateWithImplementation(Allocator, Hint, ElementSize, Destructor, BestInterface);
}

CCCollection CCCollectionCreateWithImplementation(CCAllocatorType Allocator, CCCollectionHint Hint, size_t ElementSize, CCCollectionElementDestructor Destructor, const CCCollectionInterface *Interface)
{
    CCAssertLog(Interface, "Interface must not be null");
    CCAssertLog(!(Hint & CCCollectionHintOrdered) || Interface->optional.ordered, "Interface must implement an ordered collection when creating an ordered collection");
    
    CCCollection Collection = CCMalloc(Allocator, sizeof(CCCollectionInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Collection)
    {
        *Collection = (CCCollectionInfo){
            .interface = Interface,
            .allocator = Allocator,
            .destructor = Destructor,
            .size = ElementSize,
            .internal = Interface->create(Allocator, Hint, ElementSize)
        };
        
        if (!Collection->internal)
        {
            CC_LOG_ERROR("Failed to create collection: Implementation failure (%p)", Interface);
            CCFree(Collection);
            Collection = NULL;
        }
    }
    
    else
    {
        CC_LOG_ERROR("Failed to create collection: Failed to allocate memory of size (%zu)", sizeof(CCCollectionInfo));
    }
    
    return Collection;
}

void CCCollectionDestroy(CCCollection Collection)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    if (Collection->destructor)
    {
        CCEnumerator Enumerator;
        CCCollectionGetEnumerator(Collection, &Enumerator);
        
        void *Element = CCCollectionEnumeratorGetCurrent(&Enumerator);
        do
        {
            Collection->destructor(Collection, Element);
        } while ((Element = CCCollectionEnumeratorNext(&Enumerator)));
    }
    
    Collection->interface->destroy(Collection->internal);
}

CCCollectionEntry CCCollectionInsertElement(CCCollection Collection, const void *Element)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    return Collection->interface->insert(Collection->internal, Element, Collection->allocator, Collection->size);
}

void CCCollectionRemoveElement(CCCollection Collection, CCCollectionEntry Entry)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    if (!Entry) return;
    
    if (Collection->destructor)
    {
        Collection->destructor(Collection, CCCollectionGetElement(Collection, Entry));
    }
    
    Collection->interface->remove(Collection->internal, Entry, Collection->allocator);
}

void *CCCollectionGetElement(CCCollection Collection, CCCollectionEntry Entry)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    return Entry ? Collection->interface->element(Collection->internal, Entry) : NULL;
}

size_t CCCollectionGetCount(CCCollection Collection)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    return Collection->interface->count(Collection->internal);
}

size_t CCCollectionGetElementSize(CCCollection Collection)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    return Collection->size;
}

CCCollectionEntry CCCollectionFindElement(CCCollection Collection, const void *Element, CCComparator Comparator)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    CCCollectionEntry Found = NULL;
    if (Collection->interface->optional.find)
    {
        Found = Collection->interface->optional.find(Collection->internal, Element, Comparator, Collection->size);
    }
    
    else
    {
        CCEnumerator Enumerator;
        CCCollectionGetEnumerator(Collection, &Enumerator);
        
        void *E = CCCollectionEnumeratorGetCurrent(&Enumerator);
        if (Comparator)
        {
            do
            {
                if (Comparator(E, Element) == CCComparisonResultEqual)
                {
                    Found = CCCollectionEnumeratorGetEntry(&Enumerator);
                    break;
                }
            } while ((E = CCCollectionEnumeratorNext(&Enumerator)));
        }
        
        else
        {
            do
            {
                if (!memcmp(E, Element, Collection->size))
                {
                    Found = CCCollectionEnumeratorGetEntry(&Enumerator);
                    break;
                }
            } while ((E = CCCollectionEnumeratorNext(&Enumerator)));
        }
    }
    
    return Found;
}

void CCCollectionGetEnumerator(CCCollection Collection, CCEnumerator *Enumerator)
{
    CCAssertLog(Collection, "Collection must not be null");
    
    Collection->interface->enumerator(Collection->internal, &Enumerator->state, CCCollectionEnumeratorActionHead);
    Enumerator->ref = Collection;
}
