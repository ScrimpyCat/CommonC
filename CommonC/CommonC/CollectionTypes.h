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

#ifndef CommonC_CollectionTypes_h
#define CommonC_CollectionTypes_h

/*!
 * @typedef CCCollectionHint
 * @brief Hints for the indended usage of the collection.
 */
typedef enum {
    ///Mask for hints for a collection.
    CCCollectionHintMask = 0xff,
    ///Collection will involve a lot of enumerations.
    CCCollectionHintHeavyEnumerating = (1 << 0),
    ///Collection will involve a lot of object lookups.
    CCCollectionHintHeavyFinding = (1 << 1),
    ///Collection will involve a lot of inserting.
    CCCollectionHintHeavyInserting = (1 << 2),
    ///Collection will involve a lot of deleting.
    CCCollectionHintHeavyDeleting = (1 << 3),
    ///The number of elements in the collection won't change (unlikely to do any inserting/deleting).
    CCCollectionHintConstantLength = (1 << 4),
    ///The elements won't change (unlikely to do any deleting/replacing).
    CCCollectionHintConstantElements = (1 << 5),
    ///The collection is ordered.
    CCCollectionHintOrdered = (1 << 6),
} CCCollectionHint;

/*!
 * @typedef CCOrderedCollectionHint
 * @brief Hints for the indended usage of the ordered collection.
 * @description Can be combined with CCCollectionHint.
 */
typedef enum {
    ///Mask for hints for a ordered collection.
    CCOrderedCollectionHintMask = 0xff00,
    ///Collection will involve a lot of replacing.
    CCOrderedCollectionHintHeavyReplacing = (1 << 0) | CCCollectionHintOrdered,
    ///Collection will involve a lot of appending.
    CCOrderedCollectionHintHeavyAppending = (1 << 1) | CCCollectionHintOrdered,
    ///Collection will involve a lot of prepending.
    CCOrderedCollectionHintHeavyPrepending = (1 << 2) | CCCollectionHintOrdered,
    ///Collection will involve a lot of sorting.
    CCOrderedCollectionHintHeavySorting = (1 << 3) | CCCollectionHintOrdered,
    ///Collection will involve a lot of inserting.
    CCOrderedCollectionHintHeavyInserting = (1 << 4) | CCCollectionHintHeavyInserting | CCCollectionHintOrdered
} CCOrderedCollectionHint;

/*!
 * @brief The type of action the enumerator callback will need to perform.
 */
typedef enum {
    ///Set the enumerator to the head end of the collection and return the element there.
    CCCollectionEnumeratorActionHead,
    ///Set the enumerator to the tail end of the collection and return the element there.
    CCCollectionEnumeratorActionTail,
    ///Set the enumerator to the next position in the collection, and return the element there.
    CCCollectionEnumeratorActionNext,
    ///Set the enumerator to the previous position in the collection, and return the element there.
    CCCollectionEnumeratorActionPrevious,
    ///Return the element at the current position.
    CCCollectionEnumeratorActionCurrent
} CCCollectionEnumeratorAction;

/*!
 * @brief The collection.
 */
typedef struct CCCollectionInfo *CCCollection;

/*!
 * @brief The ordered collection
 */
typedef CCCollection CCOrderedCollection;

/*!
 * @brief The reference to an entry in the collection.
 */
typedef void *CCCollectionEntry;

#endif
