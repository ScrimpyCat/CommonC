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

#include "HashMap.h"
#include "MemoryAllocation.h"


static void CCHashMapDestructor(CCHashMap Ptr)
{
    Ptr->interface->destroy(Ptr->internal);
}

CCHashMap CCHashMapCreate(CCAllocatorType Allocator, size_t KeySize, size_t ValueSize, size_t BucketCount, CCHashMapKeyHasher Hasher, CCComparator KeyComparator, const CCHashMapInterface *Interface)
{
    CCAssertLog(BucketCount >= 1, "BucketCount must be at least 1");
    
    CCHashMap Map = CCMalloc(Allocator, sizeof(CCHashMapInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (Map)
    {
        *Map = (CCHashMapInfo){
            .interface = Interface,
            .allocator = Allocator,
            .getHash = Hasher,
            .compareKeys = KeyComparator,
            .keySize = KeySize,
            .valueSize = ValueSize,
            .bucketCount = BucketCount,
            .internal = Interface->create(Allocator, KeySize, ValueSize, BucketCount)
        };
        
        if (!Map->internal)
        {
            CC_LOG_ERROR("Failed to create hashmap: Implementation failure (%p)", Interface);
            CCFree(Map);
            Map = NULL;
        }
        
        else CCMemorySetDestructor(Map, (CCMemoryDestructorCallback)CCHashMapDestructor);
    }
    
    else
    {
        CC_LOG_ERROR("Failed to create hashmap: Failed to allocate memory of size (%zu)", sizeof(CCHashMapInfo));
    }
    
    return Map;
}

void CCHashMapDestroy(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    CCFree(Map);
}

uintmax_t CCHashMapGetKeyHash(CCHashMap Map, void *Key)
{
    uintmax_t Hash = 0;
    if (Map->getHash)
    {
        Hash = Map->getHash(Key);
    }
    
    else
    {
        if (Map->keySize >= sizeof(uintmax_t))
        {
            Hash = *(uintmax_t*)Key;
        }
        
        else
        {
#if CC_HARDWARE_ENDIAN_LITTLE
            memcpy(&Hash, Key, Map->keySize);
#elif CC_HARDWARE_ENDIAN_BIG
            memcpy(&Hash + (sizeof(uintmax_t) - Map->keySize), Key, Map->keySize);
#else
#warning Unknown endianness, no guarantee of efficient hashing
            memcpy(&Hash, Key, Map->keySize);
#endif
        }
    }
    
    return Hash;
}

CCHashMapEntry CCHashMapFindKey(CCHashMap Map, void *Key)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->interface->findKey(Map, Key);
}

CCHashMapEntry CCHashMapEntryForKey(CCHashMap Map, void *Key, _Bool *Created)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->interface->entryForKey(Map, Key, Created);
}

void *CCHashMapGetKey(CCHashMap Map, CCHashMapEntry Entry)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->interface->getKey(Map, Entry);
}

void *CCHashMapGetEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    CCAssertLog(Map, "Map must not be null");
    
    if (!Entry) return NULL;
    
    return Map->interface->getEntry(Map, Entry);
}

void CCHashMapSetEntry(CCHashMap Map, CCHashMapEntry Entry, void *Value)
{
    CCAssertLog(Map, "Map must not be null");
    
    if (!Entry) return;
    
    Map->interface->setEntry(Map, Entry, Value);
}

void CCHashMapRemoveEntry(CCHashMap Map, CCHashMapEntry Entry)
{
    CCAssertLog(Map, "Map must not be null");
    
    if (!Entry) return;
    
    Map->interface->removeEntry(Map, Entry);
}

void *CCHashMapGetValue(CCHashMap Map, void *Key)
{
    CCAssertLog(Map, "Map must not be null");
    
    if (Map->interface->optional.getValue) return Map->interface->optional.getValue(Map, Key);
    else return CCHashMapGetEntry(Map, CCHashMapFindKey(Map, Key));
}

void CCHashMapSetValue(CCHashMap Map, void *Key, void *Value)
{
    CCAssertLog(Map, "Map must not be null");
    
    if (Map->interface->optional.setValue) Map->interface->optional.setValue(Map, Key, Value);
    else CCHashMapSetEntry(Map, CCHashMapFindKey(Map, Key), Value);
}

void CCHashMapRemoveValue(CCHashMap Map, void *Key)
{
    CCAssertLog(Map, "Map must not be null");
    
    if (Map->interface->optional.removeValue) Map->interface->optional.removeValue(Map, Key);
    else CCHashMapRemoveEntry(Map, CCHashMapFindKey(Map, Key));
}

size_t CCHashMapGetCount(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->interface->count(Map);
}

CCOrderedCollection CCHashMapGetKeys(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->interface->keys(Map);
}

CCOrderedCollection CCHashMapGetValues(CCHashMap Map)
{
    CCAssertLog(Map, "Map must not be null");
    
    return Map->interface->values(Map);
}
