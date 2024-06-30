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

#pragma mark - Collection Callbacks

extern const CCCollectionElementDestructor CCGenericDestructorForCollection;
extern const CCCollectionElementDestructor CCStringDestructorForCollection;
extern const CCCollectionElementDestructor CCDataDestructorForCollection;
extern const CCCollectionElementDestructor CCArrayDestructorForCollection;
extern const CCCollectionElementDestructor CCLinkedListDestructorForCollection;
extern const CCCollectionElementDestructor CCListDestructorForCollection;
extern const CCCollectionElementDestructor CCCollectionDestructorForCollection;
extern const CCCollectionElementDestructor CCHashMapDestructorForCollection;
extern const CCCollectionElementDestructor CCDictionaryDestructorForCollection;
extern const CCCollectionElementDestructor CCQueueDestructorForCollection;
extern const CCCollectionElementDestructor FSPathComponentDestructorForCollection;
extern const CCCollectionElementDestructor FSPathDestructorForCollection;
extern const CCCollectionElementDestructor FSHandleDestructorForCollection;
extern const CCCollectionElementDestructor CCBigIntDestructorForCollection;
extern const CCCollectionElementDestructor CCBigIntFastDestructorForCollection;

extern const CCComparator CCStringComparatorForCollection;
extern const CCComparator CCBigIntComparatorForCollection;
extern const CCComparator CCBigIntFastComparatorForCollection;

#pragma mark - Dictionary Callbacks

extern const CCDictionaryElementDestructor CCGenericDestructorForDictionary;
extern const CCDictionaryElementDestructor CCStringDestructorForDictionary;
extern const CCDictionaryElementDestructor CCDataDestructorForDictionary;
extern const CCDictionaryElementDestructor CCArrayDestructorForDictionary;
extern const CCDictionaryElementDestructor CCLinkedListDestructorForDictionary;
extern const CCDictionaryElementDestructor CCListDestructorForDictionary;
extern const CCDictionaryElementDestructor CCCollectionDestructorForDictionary;
extern const CCDictionaryElementDestructor CCHashMapDestructorForDictionary;
extern const CCDictionaryElementDestructor CCDictionaryDestructorForDictionary;
extern const CCDictionaryElementDestructor CCQueueDestructorForDictionary;
extern const CCDictionaryElementDestructor FSPathComponentDestructorForDictionary;
extern const CCDictionaryElementDestructor FSPathDestructorForDictionary;
extern const CCDictionaryElementDestructor FSHandleDestructorForDictionary;
extern const CCDictionaryElementDestructor CCBigIntDestructorForDictionary;
extern const CCDictionaryElementDestructor CCBigIntFastDestructorForDictionary;

extern const CCDictionaryKeyHasher CCStringHasherForDictionary;
extern const CCDictionaryKeyHasher CCBigIntHasherForDictionary;
extern const CCDictionaryKeyHasher CCBigIntFastHasherForDictionary;
extern const CCDictionaryKeyHasher CCBigIntLowHasherForDictionary;
extern const CCDictionaryKeyHasher CCBigIntFastLowHasherForDictionary;

extern const CCComparator CCStringComparatorForDictionary;
extern const CCComparator CCBigIntComparatorForDictionary;
extern const CCComparator CCBigIntFastComparatorForDictionary;

#endif
