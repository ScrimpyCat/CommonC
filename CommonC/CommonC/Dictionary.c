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

//CCDictionary CCDictionaryCreate(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, CCDictionaryCallbacks Callbacks)
//{
//    
//}

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

CCDictionary CCDictionaryCreateWithImplementation(CCAllocatorType Allocator, CCDictionaryHint Hint, size_t KeySize, size_t ValueSize, CCDictionaryCallbacks Callbacks, const CCDictionaryInterface *Interface)
{
    CCAssertLog(Interface, "Interface must not be null");
    
    CCDictionary Dictionary = CCMalloc(Allocator, sizeof(CCDictionaryInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Dictionary)
    {
        *Dictionary = (CCDictionaryInfo){
            .interface = Interface,
            .allocator = Allocator,
            .callbacks = Callbacks,
            .keySize = KeySize,
            .valueSize = ValueSize,
            .internal = Interface->create(Allocator, Hint, KeySize, ValueSize, Callbacks.getHash, Callbacks.compareKeys)
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
    
    Dictionary->interface->enumerator(Dictionary, &Enumerator->state, CCDictionaryEnumeratorActionHead, CCDictionaryEnumeratorTypeValue);
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
