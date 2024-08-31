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

#ifndef CommonC_TypeDestructors_h
#define CommonC_TypeDestructors_h

#include <CommonC/Collection.h>
#include <CommonC/Dictionary.h>

#include <CommonC/CCString.h>
#include <CommonC/Data.h>
#include <CommonC/Array.h>
#include <CommonC/LinkedList.h>
#include <CommonC/List.h>
#include <CommonC/HashMap.h>
#include <CommonC/Queue.h>
#include <CommonC/PathComponent.h>
#include <CommonC/Path.h>
#include <CommonC/FileHandle.h>
#include <CommonC/BigInt.h>
#include <CommonC/BigIntFast.h>


void CCGenericContainerElementDestructor(void *Container, void **Element);
void CCStringContainerElementDestructor(void *Container, CCString *Element);
void CCDataContainerElementDestructor(void *Container, CCData *Element);
void CCArrayContainerElementDestructor(void *Container, CCArray *Element);
void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element);
void CCListContainerElementDestructor(void *Container, CCList *Element);
void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element);
void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element);
void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element);
void CCQueueContainerElementDestructor(void *Container, CCQueue *Element);
void FSPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element);
void FSPathContainerElementDestructor(void *Container, FSPath *Element);
void FSHandleContainerElementDestructor(void *Container, FSHandle *Element);
void CCBigIntContainerElementDestructor(void *Container, CCBigInt *Element);
void CCBigIntFastContainerElementDestructor(void *Container, CCBigIntFast *Element);

uintmax_t CCStringHasher(CCString *Key);
uintmax_t CCBigIntHasher(CCBigInt *Key);
uintmax_t CCBigIntFastHasher(CCBigIntFast *Key);
uintmax_t CCBigIntLowHasher(CCBigInt *Key);
uintmax_t CCBigIntFastLowHasher(CCBigIntFast *Key);

CCComparisonResult CCStringComparator(CCString *Left, CCString *Right);
CCComparisonResult CCBigIntComparator(CCBigInt *Left, CCBigInt *Right);
CCComparisonResult CCBigIntFastComparator(CCBigIntFast *Left, CCBigIntFast *Right);

#pragma mark - Collection Callbacks

#define CCGenericDestructorForCollection (CCCollectionElementDestructor)CCGenericContainerElementDestructor
#define CCStringDestructorForCollection (CCCollectionElementDestructor)CCStringContainerElementDestructor
#define CCDataDestructorForCollection (CCCollectionElementDestructor)CCDataContainerElementDestructor
#define CCArrayDestructorForCollection (CCCollectionElementDestructor)CCArrayContainerElementDestructor
#define CCLinkedListDestructorForCollection (CCCollectionElementDestructor)CCLinkedListContainerElementDestructor
#define CCListDestructorForCollection (CCCollectionElementDestructor)CCListContainerElementDestructor
#define CCCollectionDestructorForCollection (CCCollectionElementDestructor)CCCollectionContainerElementDestructor
#define CCHashMapDestructorForCollection (CCCollectionElementDestructor)CCHashMapContainerElementDestructor
#define CCDictionaryDestructorForCollection (CCCollectionElementDestructor)CCDictionaryContainerElementDestructor
#define CCQueueDestructorForCollection (CCCollectionElementDestructor)CCQueueContainerElementDestructor
#define FSPathComponentDestructorForCollection (CCCollectionElementDestructor)FSPathComponentContainerElementDestructor
#define FSPathDestructorForCollection (CCCollectionElementDestructor)FSPathContainerElementDestructor
#define FSHandleDestructorForCollection (CCCollectionElementDestructor)FSHandleContainerElementDestructor
#define CCBigIntDestructorForCollection (CCCollectionElementDestructor)CCBigIntContainerElementDestructor
#define CCBigIntFastDestructorForCollection (CCCollectionElementDestructor)CCBigIntFastContainerElementDestructor

#define CCStringComparatorForCollection (CCComparator)CCStringComparator
#define CCBigIntComparatorForCollection (CCComparator)CCBigIntComparator
#define CCBigIntFastComparatorForCollection (CCComparator)CCBigIntFastComparator

#pragma mark - Dictionary Callbacks

#define CCGenericDestructorForDictionary (CCDictionaryElementDestructor)CCGenericContainerElementDestructor
#define CCStringDestructorForDictionary (CCDictionaryElementDestructor)CCStringContainerElementDestructor
#define CCDataDestructorForDictionary (CCDictionaryElementDestructor)CCDataContainerElementDestructor
#define CCArrayDestructorForDictionary (CCDictionaryElementDestructor)CCArrayContainerElementDestructor
#define CCLinkedListDestructorForDictionary (CCDictionaryElementDestructor)CCLinkedListContainerElementDestructor
#define CCListDestructorForDictionary (CCDictionaryElementDestructor)CCListContainerElementDestructor
#define CCCollectionDestructorForDictionary (CCDictionaryElementDestructor)CCCollectionContainerElementDestructor
#define CCHashMapDestructorForDictionary (CCDictionaryElementDestructor)CCHashMapContainerElementDestructor
#define CCDictionaryDestructorForDictionary (CCDictionaryElementDestructor)CCDictionaryContainerElementDestructor
#define CCQueueDestructorForDictionary (CCDictionaryElementDestructor)CCQueueContainerElementDestructor
#define FSPathComponentDestructorForDictionary (CCDictionaryElementDestructor)FSPathComponentContainerElementDestructor
#define FSPathDestructorForDictionary (CCDictionaryElementDestructor)FSPathContainerElementDestructor
#define FSHandleDestructorForDictionary (CCDictionaryElementDestructor)FSHandleContainerElementDestructor
#define CCBigIntDestructorForDictionary (CCDictionaryElementDestructor)CCBigIntContainerElementDestructor
#define CCBigIntFastDestructorForDictionary (CCDictionaryElementDestructor)CCBigIntFastContainerElementDestructor

#define CCStringHasherForDictionary (CCDictionaryKeyHasher)CCStringHasher
#define CCBigIntHasherForDictionary (CCDictionaryKeyHasher)CCBigIntHasher
#define CCBigIntFastHasherForDictionary (CCDictionaryKeyHasher)CCBigIntFastHasher
#define CCBigIntLowHasherForDictionary (CCDictionaryKeyHasher)CCBigIntLowHasher
#define CCBigIntFastLowHasherForDictionary (CCDictionaryKeyHasher)CCBigIntFastLowHasher

#define CCStringComparatorForDictionary (CCComparator)CCStringComparator
#define CCBigIntComparatorForDictionary (CCComparator)CCBigIntComparator
#define CCBigIntFastComparatorForDictionary (CCComparator)CCBigIntFastComparator

#endif
