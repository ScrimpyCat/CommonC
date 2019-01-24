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

#include "TypeCallbacks.h"
#include "CCString.h"
#include "Data.h"
#include "Path.h"
#include "Array.h"
#include "LinkedList.h"
#include "HashMap.h"
#include "FileHandle.h"

#pragma mark Destructors

static void CCGenericContainerElementDestructor(void *Container, void **Element);
static void CCStringContainerElementDestructor(void *Container, CCString *Element);
static void CCDataContainerElementDestructor(void *Container, CCData *Element);
static void CCArrayContainerElementDestructor(void *Container, CCArray *Element);
static void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element);
static void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element);
static void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element);
static void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element);
static void CCPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element);
static void CCPathContainerElementDestructor(void *Container, FSPath *Element);
static void CCHandleContainerElementDestructor(void *Container, FSHandle *Element);

#pragma mark Hashers

static uintmax_t CCStringHasher(CCString *Key);

#pragma mark Comparators

static CCComparisonResult CCStringComparator(CCString *Left, CCString *Right);

#pragma mark - Collection Callbacks
#pragma mark Destructors

const CCCollectionElementDestructor CCGenericDestructorForCollection = (CCCollectionElementDestructor)CCGenericContainerElementDestructor;
const CCCollectionElementDestructor CCStringDestructorForCollection = (CCCollectionElementDestructor)CCStringContainerElementDestructor;
const CCCollectionElementDestructor CCDataDestructorForCollection = (CCCollectionElementDestructor)CCDataContainerElementDestructor;
const CCCollectionElementDestructor CCArrayDestructorForCollection = (CCCollectionElementDestructor)CCArrayContainerElementDestructor;
const CCCollectionElementDestructor CCLinkedListDestructorForCollection = (CCCollectionElementDestructor)CCLinkedListContainerElementDestructor;
const CCCollectionElementDestructor CCCollectionDestructorForCollection = (CCCollectionElementDestructor)CCCollectionContainerElementDestructor;
const CCCollectionElementDestructor CCHashMapDestructorForCollection = (CCCollectionElementDestructor)CCHashMapContainerElementDestructor;
const CCCollectionElementDestructor CCDictionaryDestructorForCollection = (CCCollectionElementDestructor)CCDictionaryContainerElementDestructor;
const CCCollectionElementDestructor FSPathComponentDestructorForCollection = (CCCollectionElementDestructor)CCPathComponentContainerElementDestructor;
const CCCollectionElementDestructor FSPathDestructorForCollection = (CCCollectionElementDestructor)CCPathContainerElementDestructor;
const CCCollectionElementDestructor FSHandleDestructorForCollection = (CCCollectionElementDestructor)CCHandleContainerElementDestructor;

#pragma mark Comparators

const CCComparator CCStringComparatorForCollection = (CCComparator)CCStringComparator;

#pragma mark - Dictionary Callbacks
#pragma mark Destructors

const CCDictionaryElementDestructor CCGenericDestructorForDictionary = (CCDictionaryElementDestructor)CCGenericContainerElementDestructor;
const CCDictionaryElementDestructor CCStringDestructorForDictionary = (CCDictionaryElementDestructor)CCStringContainerElementDestructor;
const CCDictionaryElementDestructor CCDataDestructorForDictionary = (CCDictionaryElementDestructor)CCDataContainerElementDestructor;
const CCDictionaryElementDestructor CCArrayDestructorForDictionary = (CCDictionaryElementDestructor)CCArrayContainerElementDestructor;
const CCDictionaryElementDestructor CCLinkedListDestructorForDictionary = (CCDictionaryElementDestructor)CCLinkedListContainerElementDestructor;
const CCDictionaryElementDestructor CCCollectionDestructorForDictionary = (CCDictionaryElementDestructor)CCCollectionContainerElementDestructor;
const CCDictionaryElementDestructor CCHashMapDestructorForDictionary = (CCDictionaryElementDestructor)CCHashMapContainerElementDestructor;
const CCDictionaryElementDestructor CCDictionaryDestructorForDictionary = (CCDictionaryElementDestructor)CCDictionaryContainerElementDestructor;
const CCDictionaryElementDestructor FSPathComponentDestructorForDictionary = (CCDictionaryElementDestructor)CCPathComponentContainerElementDestructor;
const CCDictionaryElementDestructor FSPathDestructorForDictionary = (CCDictionaryElementDestructor)CCPathContainerElementDestructor;
const CCDictionaryElementDestructor FSHandleDestructorForDictionary = (CCDictionaryElementDestructor)CCHandleContainerElementDestructor;

#pragma mark Hashers

const CCDictionaryKeyHasher CCStringHasherForDictionary = (CCDictionaryKeyHasher)CCStringHasher;

#pragma mark Comparators

const CCComparator CCStringComparatorForDictionary = (CCComparator)CCStringComparator;

#pragma mark -

static void CCGenericContainerElementDestructor(void *Container, void **Element)
{
    CCFree(*Element);
}

static void CCStringContainerElementDestructor(void *Container, CCString *Element)
{
    CCStringDestroy(*Element);
}

static void CCDataContainerElementDestructor(void *Container, CCData *Element)
{
    CCDataDestroy(*Element);
}

static void CCArrayContainerElementDestructor(void *Container, CCArray *Element)
{
    CCArrayDestroy(*Element);
}

static void CCLinkedListContainerElementDestructor(void *Container, CCLinkedList *Element)
{
    CCLinkedListDestroy(*Element);
}

static void CCCollectionContainerElementDestructor(void *Container, CCCollection *Element)
{
    CCCollectionDestroy(*Element);
}

static void CCHashMapContainerElementDestructor(void *Container, CCHashMap *Element)
{
    CCHashMapDestroy(*Element);
}

static void CCDictionaryContainerElementDestructor(void *Container, CCDictionary *Element)
{
    CCDictionaryDestroy(*Element);
}

static void CCPathComponentContainerElementDestructor(void *Container, FSPathComponent *Element)
{
    FSPathComponentDestroy(*Element);
}

static void CCPathContainerElementDestructor(void *Container, FSPath *Element)
{
    FSPathDestroy(*Element);
}

static void CCHandleContainerElementDestructor(void *Container, FSHandle *Element)
{
    FSHandleClose(*Element);
}

static uintmax_t CCStringHasher(CCString *Key)
{
    return CCStringGetHash(*Key);
}

static CCComparisonResult CCStringComparator(CCString *Left, CCString *Right)
{
    return CCStringEqual(*Left, *Right) ? CCComparisonResultEqual : CCComparisonResultInvalid;
}
