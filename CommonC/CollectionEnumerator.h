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

#ifndef CommonC_CollectionEnumerator_h
#define CommonC_CollectionEnumerator_h

#include <CommonC/Enumerator.h>
#include <CommonC/Collection.h>
#include <CommonC/Extensions.h>


/*!
 * @define CC_COLLECTION_CURRENT_ENUMERATOR
 * @abstract Convenient macro to reference the enumerator of the current CC_COLLECTION_FOREACH block.
 */
#define CC_COLLECTION_CURRENT_ENUMERATOR CC_PRIV_enumerator___

/*!
 * @define CC_COLLECTION_FOREACH
 * @abstract Convenient macro to iterate through each element in a collection.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @warning Scoping rules apply, to avoid unintended problems with nested foreach loops either change
 *          CC_COLLECTION_CURRENT_ENUMERATOR, or enclosed it in a braces.
 *
 * @param type The type of the element.
 * @param element The name for the element variable.
 * @param collection The collection to iterate through.
 */
#define CC_COLLECTION_FOREACH(type, element, collection) \
CCEnumerator CC_COLLECTION_CURRENT_ENUMERATOR; \
CCCollectionGetEnumerator(collection, &CC_COLLECTION_CURRENT_ENUMERATOR); \
\
for (type *CC_PRIV_##element##__ = CCCollectionEnumeratorGetCurrent(&CC_COLLECTION_CURRENT_ENUMERATOR), element = CC_PRIV_##element##__ ? *CC_PRIV_##element##__ : (type){ 0 }; CC_PRIV_##element##__; CC_PRIV_##element##__ = CCCollectionEnumeratorNext(&CC_COLLECTION_CURRENT_ENUMERATOR), element = CC_PRIV_##element##__ ? *CC_PRIV_##element##__ : (type){ 0 })

/*!
 * @define CC_COLLECTION_FOREACH_PTR
 * @abstract Convenient macro to iterate through each pointer element in a collection.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @warning Scoping rules apply, to avoid unintended problems with nested foreach loops either change
 *          CC_COLLECTION_CURRENT_ENUMERATOR, or enclosed it in a braces.
 *
 * @param type The type of the element. Note: The element will be a pointer to this type.
 * @param element The name for the element variable.
 * @param collection The collection to iterate through.
 */
#define CC_COLLECTION_FOREACH_PTR(type, element, collection) \
CCEnumerator CC_COLLECTION_CURRENT_ENUMERATOR; \
CCCollectionGetEnumerator(collection, &CC_COLLECTION_CURRENT_ENUMERATOR); \
\
for (type *element = CCCollectionEnumeratorGetCurrent(&CC_COLLECTION_CURRENT_ENUMERATOR); element; element = CCCollectionEnumeratorNext(&CC_COLLECTION_CURRENT_ENUMERATOR))

/*!
 * @brief Get a reference to the current entry in the enumerator.
 * @param Enumerator The enumerator to get the reference to.
 * @return The entry reference to the current element.
 */
static CC_FORCE_INLINE CCCollectionEntry CCCollectionEnumeratorGetEntry(CCEnumerator *Enumerator);

/*!
 * @brief Get the current element in the enumerator.
 * @param Enumerator The enumerator to get the element from.
 * @return The current element.
 */
static CC_FORCE_INLINE void *CCCollectionEnumeratorGetCurrent(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the head.
 * @param Enumerator The enumerator to point to the head.
 * @return The current element.
 */
static CC_FORCE_INLINE void *CCCollectionEnumeratorGetHead(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the tail.
 * @param Enumerator The enumerator to point to the tail.
 * @return The current element.
 */
static CC_FORCE_INLINE void *CCCollectionEnumeratorGetTail(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the next position.
 * @description Once the enumerator has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerator The enumerator to point to the next element.
 * @return The current element or NULL if it has reached the end.
 */
static CC_FORCE_INLINE void *CCCollectionEnumeratorNext(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the previous position.
 * @description Once the enumerator has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerator The enumerator to point to the previous element.
 * @return The current element or NULL if it has reached the end.
 */
static CC_FORCE_INLINE void *CCCollectionEnumeratorPrevious(CCEnumerator *Enumerator);


#pragma mark -

static CC_FORCE_INLINE CCCollectionEntry CCCollectionEnumeratorGetEntry(CCEnumerator *Enumerator)
{
    return ((CCCollection)Enumerator->ref)->interface->enumeratorReference(((CCCollection)Enumerator->ref)->internal, &Enumerator->state);
}

static CC_FORCE_INLINE void *CCCollectionEnumeratorGetCurrent(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatInternal:
            return ((CCCollection)Enumerator->ref)->interface->enumerator(((CCCollection)Enumerator->ref)->internal, &Enumerator->state, CCCollectionEnumeratorActionCurrent);
            
        case CCEnumeratorFormatFixedBatch:
            return Enumerator->state.fixedBatch.count ? Enumerator->state.fixedBatch.ptr[Enumerator->state.fixedBatch.index] : NULL;
            
        case CCEnumeratorFormatBatch:
            return Enumerator->state.batch.count ? Enumerator->state.batch.ptr + (Enumerator->state.batch.index * Enumerator->state.batch.stride) : NULL;
    }
    
    return NULL;
}

static CC_FORCE_INLINE void *CCCollectionEnumeratorGetHead(CCEnumerator *Enumerator)
{
    return ((CCCollection)Enumerator->ref)->interface->enumerator(((CCCollection)Enumerator->ref)->internal, &Enumerator->state, CCCollectionEnumeratorActionHead);
}

static inline void *CCCollectionEnumeratorGetTail(CCEnumerator *Enumerator)
{
    return ((CCCollection)Enumerator->ref)->interface->enumerator(((CCCollection)Enumerator->ref)->internal, &Enumerator->state, CCCollectionEnumeratorActionTail);
}

static CC_FORCE_INLINE void *CCCollectionEnumeratorNext(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatFixedBatch:
            if (Enumerator->state.fixedBatch.count == 0) return NULL;
            else if (Enumerator->state.fixedBatch.index + 1 < Enumerator->state.fixedBatch.count) return Enumerator->state.fixedBatch.ptr[++Enumerator->state.fixedBatch.index];
            break;
            
        case CCEnumeratorFormatBatch:
            if (Enumerator->state.batch.count == 0) return NULL;
            else if (Enumerator->state.batch.index + 1 < Enumerator->state.batch.count) return Enumerator->state.batch.ptr + (++Enumerator->state.batch.index * Enumerator->state.batch.stride);
            break;
            
        default:
            break;
    }
    
    return ((CCCollection)Enumerator->ref)->interface->enumerator(((CCCollection)Enumerator->ref)->internal, &Enumerator->state, CCCollectionEnumeratorActionNext);
}

static CC_FORCE_INLINE void *CCCollectionEnumeratorPrevious(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatFixedBatch:
            if (Enumerator->state.fixedBatch.count == 0) return NULL;
            else if (Enumerator->state.fixedBatch.index > 0) return Enumerator->state.fixedBatch.ptr[--Enumerator->state.fixedBatch.index];
            break;
            
        case CCEnumeratorFormatBatch:
            if (Enumerator->state.batch.count == 0) return NULL;
            else if (Enumerator->state.batch.index > 0) return Enumerator->state.batch.ptr + (--Enumerator->state.batch.index * Enumerator->state.batch.stride);
            break;
            
        default:
            break;
    }
    
    return ((CCCollection)Enumerator->ref)->interface->enumerator(((CCCollection)Enumerator->ref)->internal, &Enumerator->state, CCCollectionEnumeratorActionPrevious);
}

#endif
