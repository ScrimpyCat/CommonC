/*
 *  Copyright (c) 2016, Stefan Johnson
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

#include "Dictionary.h"
#include "DictionaryEnumerator.h"
#include "Assertion.h"
#include "MemoryAllocation.h"
#include "LinkedList.h"
#include "BitTricks.h"


typedef struct {
    CCLinkedListNode node;
    const CCDictionaryInterface *interface;
} CCDictionaryInterfaceNode;

typedef struct {
    int allocator;
    CCDictionaryInterfaceNode data;
} CCDictionaryInternalInterfaceNode;


const int CCDictionaryHintWeightMax = 30000; //CCDictionaryHintWeightCreate((UINT_MAX & ~CCDictionaryHintSizeMask) | CCDictionaryHintSizeLarge, UINT_MAX, 0, 0)

int CCDictionaryHintWeightCreate(CCDictionaryHint Hint, CCDictionaryHint FastHints, CCDictionaryHint ModerateHints, CCDictionaryHint SlowHints)
{
    const int Size = (int[]){ 10, 1, 100, 0 }[(Hint & CCDictionaryHintSizeMask) >> 30];
    Hint &= ~CCDictionaryHintSizeMask;
    
    FastHints &= Hint;
    ModerateHints &= Hint;
    SlowHints &= Hint;
    
    return ((int)CCBitCountSet(FastHints) * 10 * Size) + ((int)CCBitCountSet(ModerateHints) * -1 * Size) + ((int)CCBitCountSet(SlowHints) * -100 * Size);
}

const CCDictionaryInterface CCDictionaryHashMapInterface;
static CCDictionaryInternalInterfaceNode InternalInterfaces[] = {
    { .allocator = -1, .data = { .node = { .prev = NULL, .next = NULL }, .interface = &CCDictionaryHashMapInterface } }
};
static CCDictionaryInterfaceNode *Interfaces = (void*)InternalInterfaces + offsetof(CCDictionaryInternalInterfaceNode, data);
void CCDictionaryRegisterInterface(const CCDictionaryInterface *Interface)
{
    CCAssertLog(Interface, "Interface must not be null");
    
    CCLinkedListNode *Node = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(CCDictionaryInterface*), &Interface);
    if (Node)
    {
        if (Interfaces)
        {
            Interfaces = (CCDictionaryInterfaceNode*)CCLinkedListInsert((CCLinkedList)Interfaces, Node);
        }
        
        else Interfaces = (CCDictionaryInterfaceNode*)Node;
    }
    
    else
    {
        CC_LOG_ERROR("Failed to add interface (%p): Failed to allocate memory of size (%zu)", Interface, sizeof(CCDictionaryInterfaceNode));
    }
}

void CCDictionaryDeregisterInterface(const CCDictionaryInterface *Interface)
{
    for (CCLinkedListNode *Node = (CCLinkedListNode*)Interfaces; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        if (((CCDictionaryInterfaceNode*)Node)->interface == Interface)
        {
            if (CCLinkedListIsHead(Node))
            {
                Interfaces = (CCDictionaryInterfaceNode*)CCLinkedListEnumerateNext(Node);
            }
            
            CCLinkedListDestroyNode(Node);
            break;
        }
    }
}

CCDictionary CCDictionaryCreate(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, const CCDictionaryCallbacks *Callbacks)
{
    int Weight = INT_MIN;
    const CCDictionaryInterface *BestInterface = NULL;
    
    for (CCLinkedListNode *Node = (CCLinkedListNode*)Interfaces; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        const int NewWeight = ((CCDictionaryInterfaceNode*)Node)->interface->hintWeight(Hint);
        if (NewWeight > Weight)
        {
            Weight = NewWeight;
            BestInterface = ((CCDictionaryInterfaceNode*)Node)->interface;
        }
    }
    
    return CCDictionaryCreateWithImplementation(Allocator, Hint, KeySize, ValueSize, Callbacks, BestInterface);
}

static void CCDictionaryDestructor(CCDictionary Dictionary)
{
    if ((Dictionary->callbacks.keyDestructor) || (Dictionary->callbacks.valueDestructor))
    {
        CCEnumerator Enumerator;
        CCDictionaryGetKeyEnumerator(Dictionary, &Enumerator);
        
        for (void *Key = CCDictionaryEnumeratorGetCurrent(&Enumerator); Key; Key = CCDictionaryEnumeratorNext(&Enumerator))
        {
            if (Dictionary->callbacks.keyDestructor) Dictionary->callbacks.keyDestructor(Dictionary, Key);
            if (Dictionary->callbacks.valueDestructor)
            {
                CCDictionaryEntry Entry = CCDictionaryEnumeratorGetEntry(&Enumerator);
                if (CCDictionaryEntryIsInitialized(Dictionary, Entry))
                {
                    Dictionary->callbacks.valueDestructor(Dictionary, CCDictionaryGetEntry(Dictionary, Entry));
                }
            }
        }
    }
    
    Dictionary->interface->destroy(Dictionary->internal);
}

CCDictionary CCDictionaryCreateWithImplementation(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, const CCDictionaryCallbacks *Callbacks, const CCDictionaryInterface *Interface)
{
    CCAssertLog(Interface, "Interface must not be null");
    
    CCDictionary Dictionary = CCMalloc(Allocator, sizeof(CCDictionaryInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Dictionary)
    {
        CCDictionaryCallbacks DefaultCallbacks = Callbacks? *Callbacks : (CCDictionaryCallbacks){};
        
        *Dictionary = (CCDictionaryInfo){
            .interface = Interface,
            .allocator = Allocator,
            .callbacks = DefaultCallbacks,
            .keySize = KeySize,
            .valueSize = ValueSize,
            .internal = Interface->create(Allocator, Hint, KeySize, ValueSize, DefaultCallbacks.getHash, DefaultCallbacks.compareKeys)
        };
        
        if (!Dictionary->internal)
        {
            CC_LOG_ERROR("Failed to create dictionary: Implementation failure (%p)", Interface);
            CCFree(Dictionary);
            Dictionary = NULL;
        }
        
        else CCMemorySetDestructor(Dictionary, (CCMemoryDestructorCallback)CCDictionaryDestructor);
    }
    
    else
    {
        CC_LOG_ERROR("Failed to create dictionary: Failed to allocate memory of size (%zu)", sizeof(CCDictionaryInfo));
    }
    
    return Dictionary;
}

void CCDictionaryDestroy(CCDictionary Dictionary)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    CCFree(Dictionary);
}

void CCDictionarySetEntry(CCDictionary Dictionary, CCDictionaryEntry Entry, void *Value)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    if (!Entry) return;
    
    if ((Dictionary->callbacks.valueDestructor) && (CCDictionaryEntryIsInitialized(Dictionary, Entry))) Dictionary->callbacks.valueDestructor(Dictionary, CCDictionaryGetEntry(Dictionary, Entry));
    
    Dictionary->interface->setEntry(Dictionary->internal, Entry, Value, Dictionary->valueSize, Dictionary->allocator);
}

void CCDictionaryRemoveEntry(CCDictionary Dictionary, CCDictionaryEntry Entry)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    if (!Entry) return;
    
    if (Dictionary->callbacks.keyDestructor) Dictionary->callbacks.keyDestructor(Dictionary, CCDictionaryGetKey(Dictionary, Entry));
    if ((Dictionary->callbacks.valueDestructor) && (CCDictionaryEntryIsInitialized(Dictionary, Entry))) Dictionary->callbacks.valueDestructor(Dictionary, CCDictionaryGetEntry(Dictionary, Entry));
    
    Dictionary->interface->removeEntry(Dictionary->internal, Entry, Dictionary->allocator);
}

void CCDictionarySetValue(CCDictionary Dictionary, void *Key, void *Value)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    CCDictionaryEntry Entry = CCDictionaryEntryForKey(Dictionary, Key);
    
    CCAssertLog(Entry, "Implementation must return a valid entry");
    
    CCDictionarySetEntry(Dictionary, Entry, Value);
}

void CCDictionaryRemoveValue(CCDictionary Dictionary, void *Key)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    CCDictionaryEntry Entry = CCDictionaryFindKey(Dictionary, Key);
    CCDictionaryRemoveEntry(Dictionary, Entry);
}

CCDictionaryEntry CCDictionaryEntryForKey(CCDictionary Dictionary, void *Key)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    return Dictionary->interface->entryForKey(Dictionary->internal, Key, Dictionary->keySize, Dictionary->callbacks.getHash, Dictionary->callbacks.compareKeys, Dictionary->allocator);
}

_Bool CCDictionaryEntryIsInitialized(CCDictionary Dictionary, CCDictionaryEntry Entry)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    if (!Entry) return FALSE;
    
    return Dictionary->interface->initialized(Dictionary->internal, Entry);
}

CCDictionaryEntry CCDictionaryFindKey(CCDictionary Dictionary, void *Key)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    return Dictionary->interface->findKey(Dictionary->internal, Key, Dictionary->keySize, Dictionary->callbacks.getHash, Dictionary->callbacks.compareKeys);
}

void *CCDictionaryGetEntry(CCDictionary Dictionary, CCDictionaryEntry Entry)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    if (!Entry) return NULL;
    
    return Dictionary->interface->getEntry(Dictionary->internal, Entry);
}

void *CCDictionaryGetValue(CCDictionary Dictionary, void *Key)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    return CCDictionaryGetEntry(Dictionary, CCDictionaryFindKey(Dictionary, Key));
}

void *CCDictionaryGetKey(CCDictionary Dictionary, CCDictionaryEntry Entry)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    if (!Entry) return NULL;
    
    return Dictionary->interface->getKey(Dictionary->internal, Entry);
}

CCOrderedCollection CCDictionaryGetKeys(CCDictionary Dictionary)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    CCOrderedCollection Keys;
    if (Dictionary->interface->optional.keys) Keys = Dictionary->interface->optional.keys(Dictionary->internal, Dictionary->allocator);
    else
    {
        Keys = CCCollectionCreate(Dictionary->allocator, CCCollectionHintOrdered | CCCollectionHintConstantLength | CCCollectionHintHeavyEnumerating, Dictionary->keySize, NULL);
        
        CCEnumerator Enumerator;
        CCDictionaryGetKeyEnumerator(Dictionary, &Enumerator);
        
        for (void *Key = CCDictionaryEnumeratorGetCurrent(&Enumerator); Key; Key = CCDictionaryEnumeratorNext(&Enumerator))
        {
            CCOrderedCollectionAppendElement(Keys, Key);
        }
    }
    
    return Keys;
}

CCOrderedCollection CCDictionaryGetValues(CCDictionary Dictionary)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    CCOrderedCollection Values;
    if (Dictionary->interface->optional.values) Values = Dictionary->interface->optional.values(Dictionary->internal, Dictionary->allocator);
    else
    {
        Values = CCCollectionCreate(Dictionary->allocator, CCCollectionHintOrdered | CCCollectionHintConstantLength | CCCollectionHintHeavyEnumerating, Dictionary->valueSize, NULL);
        
        CCEnumerator Enumerator;
        CCDictionaryGetValueEnumerator(Dictionary, &Enumerator);
        
        for (void *Value = CCDictionaryEnumeratorGetCurrent(&Enumerator); Value; Value = CCDictionaryEnumeratorNext(&Enumerator))
        {
            CCOrderedCollectionAppendElement(Values, Value);
        }
    }
    
    return Values;
}

void CCDictionaryGetKeyEnumerator(CCDictionary Dictionary, CCEnumerator *Enumerator)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    Dictionary->interface->enumerator(Dictionary->internal, &Enumerator->state, CCDictionaryEnumeratorActionHead, CCDictionaryEnumeratorTypeKey);
    Enumerator->ref = Dictionary;
    Enumerator->option = CCDictionaryEnumeratorTypeKey;
}

void CCDictionaryGetValueEnumerator(CCDictionary Dictionary, CCEnumerator *Enumerator)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    Dictionary->interface->enumerator(Dictionary->internal, &Enumerator->state, CCDictionaryEnumeratorActionHead, CCDictionaryEnumeratorTypeValue);
    Enumerator->ref = Dictionary;
    Enumerator->option = CCDictionaryEnumeratorTypeValue;
}

size_t CCDictionaryGetCount(CCDictionary Dictionary)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    return Dictionary->interface->count(Dictionary->internal);
}

size_t CCDictionaryGetKeySize(CCDictionary Dictionary)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    return Dictionary->keySize;
}

size_t CCDictionaryGetValueSize(CCDictionary Dictionary)
{
    CCAssertLog(Dictionary, "Dictionary must not be null");
    
    return Dictionary->valueSize;
}
