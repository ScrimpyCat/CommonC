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

#ifndef CommonC_DictionaryEnumerator_h
#define CommonC_DictionaryEnumerator_h

#include <CommonC/Enumerator.h>
#include <CommonC/Dictionary.h>
#include <CommonC/Extensions.h>


/*!
 * @define CC_DICTIONARY_CURRENT_KEY_ENUMERATOR
 * @abstract Convenient macro to reference the key enumerator of the current CC_DICTIONARY_FOREACH* blocks.
 */
#define CC_DICTIONARY_CURRENT_KEY_ENUMERATOR CC_PRIV_hash_map_key_enumerator___

/*!
 * @define CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR
 * @abstract Convenient macro to reference the value enumerator of the current CC_DICTIONARY_FOREACH* blocks.
 */
#define CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR CC_PRIV_hash_map_value_enumerator___

/*!
 * @define CC_DICTIONARY_FOREACH_KEY
 * @abstract Convenient macro to iterate through each key in a dictionary.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @param type The type of the key.
 * @param key The name for the key variable.
 * @param map The map to iterate through.
 */
#define CC_DICTIONARY_FOREACH_KEY(type, key, map) \
for (CCEnumerator CC_DICTIONARY_CURRENT_KEY_ENUMERATOR, CC_PRIV_loop_once__ = { .option = 2 }; CC_PRIV_loop_once__.option; CCDictionaryGetKeyEnumerator(map, &CC_DICTIONARY_CURRENT_KEY_ENUMERATOR), CC_PRIV_loop_once__.option--) \
if (CC_PRIV_loop_once__.option == 1) \
for (type *CC_PRIV_##key##__ = CCDictionaryEnumeratorGetCurrent(&CC_DICTIONARY_CURRENT_KEY_ENUMERATOR), key = CC_PRIV_##key##__ ? *CC_PRIV_##key##__ : (type){ 0 }; CC_PRIV_##key##__; CC_PRIV_##key##__ = CCDictionaryEnumeratorNext(&CC_DICTIONARY_CURRENT_KEY_ENUMERATOR), key = CC_PRIV_##key##__ ? *CC_PRIV_##key##__ : (type){ 0 })

/*!
 * @define CC_DICTIONARY_FOREACH_VALUE
 * @abstract Convenient macro to iterate through each value in a dictionary.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @param type The type of the value.
 * @param value The name for the value variable.
 * @param map The map to iterate through.
 */
#define CC_DICTIONARY_FOREACH_VALUE(type, value, map) \
for (CCEnumerator CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR, CC_PRIV_loop_once__ = { .option = 2 }; CC_PRIV_loop_once__.option; CCDictionaryGetValueEnumerator(map, &CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR), CC_PRIV_loop_once__.option--) \
if (CC_PRIV_loop_once__.option == 1) \
for (type *CC_PRIV_##value##__ = CCDictionaryEnumeratorGetCurrent(&CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR), value = CC_PRIV_##value##__ ? *CC_PRIV_##value##__ : (type){ 0 }; CC_PRIV_##value##__; CC_PRIV_##value##__ = CCDictionaryEnumeratorNext(&CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR), value = CC_PRIV_##value##__ ? *CC_PRIV_##value##__ : (type){ 0 })

/*!
 * @define CC_DICTIONARY_FOREACH_KEY_PTR
 * @abstract Convenient macro to iterate through each pointer key in a collection.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @param type The type of the key. Note: The key will be a pointer to this type.
 * @param key The name for the key variable.
 * @param map The map to iterate through.
 */
#define CC_DICTIONARY_FOREACH_KEY_PTR(type, key, map) \
for (CCEnumerator CC_DICTIONARY_CURRENT_KEY_ENUMERATOR, CC_PRIV_loop_once__ = { .option = 2 }; CC_PRIV_loop_once__.option; CCDictionaryGetKeyEnumerator(map, &CC_DICTIONARY_CURRENT_KEY_ENUMERATOR), CC_PRIV_loop_once__.option--) \
if (CC_PRIV_loop_once__.option == 1) \
for (type *key = CCDictionaryEnumeratorGetCurrent(&CC_DICTIONARY_CURRENT_KEY_ENUMERATOR); key; key = CCDictionaryEnumeratorNext(&CC_DICTIONARY_CURRENT_KEY_ENUMERATOR))

/*!
 * @define CC_DICTIONARY_FOREACH_VALUE_PTR
 * @abstract Convenient macro to iterate through each pointer value in a collection.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @param type The type of the value. Note: The value will be a pointer to this type.
 * @param value The name for the value variable.
 * @param map The map to iterate through.
 */
#define CC_DICTIONARY_FOREACH_VALUE_PTR(type, value, map) \
for (CCEnumerator CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR, CC_PRIV_loop_once__ = { .option = 2 }; CC_PRIV_loop_once__.option; CCDictionaryGetValueEnumerator(map, &CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR), CC_PRIV_loop_once__.option--) \
if (CC_PRIV_loop_once__.option == 1) \
for (type *value = CCDictionaryEnumeratorGetCurrent(&CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR); value; value = CCDictionaryEnumeratorNext(&CC_DICTIONARY_CURRENT_VALUE_ENUMERATOR))

/*!
 * @brief Get the type of dictionary enumerator.
 * @param Enumerator The enumerator to get the type of.
 * @return The type indicating whether it is key enumerator, or a value enumerator.
 */
static CC_FORCE_INLINE CCDictionaryEnumeratorType CCDictionaryEnumeratorGetType(CCEnumerator *Enumerator);

/*!
 * @brief Get a reference to the current entry in the enumerator.
 * @param Enumerator The enumerator to get the reference to.
 * @return The entry reference to the current key/value.
 */
static CC_FORCE_INLINE CCDictionaryEntry CCDictionaryEnumeratorGetEntry(CCEnumerator *Enumerator);

/*!
 * @brief Get the current key/value in the enumerator.
 * @param Enumerator The enumerator to get the key/value from.
 * @return The current key/value.
 */
static CC_FORCE_INLINE void *CCDictionaryEnumeratorGetCurrent(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the head.
 * @param Enumerator The enumerator to point to the head.
 * @return The current key/value.
 */
static CC_FORCE_INLINE void *CCDictionaryEnumeratorGetHead(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the tail.
 * @param Enumerator The enumerator to point to the tail.
 * @return The current key/value.
 */
static CC_FORCE_INLINE void *CCDictionaryEnumeratorGetTail(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the next position.
 * @description Once the enumerator has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerator The enumerator to point to the next element.
 * @return The current key/value or NULL if it has reached the end.
 */
static CC_FORCE_INLINE void *CCDictionaryEnumeratorNext(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the previous position.
 * @description Once the enumerator has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerator The enumerator to point to the previous element.
 * @return The current key/value or NULL if it has reached the end.
 */
static CC_FORCE_INLINE void *CCDictionaryEnumeratorPrevious(CCEnumerator *Enumerator);


#pragma mark -

static CC_FORCE_INLINE CCDictionaryEnumeratorType CCDictionaryEnumeratorGetType(CCEnumerator *Enumerator)
{
    return Enumerator->option & CCDictionaryEnumeratorTypeMask;
}

static CC_FORCE_INLINE CCDictionaryEntry CCDictionaryEnumeratorGetEntry(CCEnumerator *Enumerator)
{
    return ((CCDictionary)Enumerator->ref)->interface->enumeratorReference(((CCDictionary)Enumerator->ref)->internal, &Enumerator->state, CCDictionaryEnumeratorGetType(Enumerator));
}

static CC_FORCE_INLINE void *CCDictionaryEnumeratorGetCurrent(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatInternal:
            return ((CCDictionary)Enumerator->ref)->interface->enumerator(((CCDictionary)Enumerator->ref)->internal, &Enumerator->state, CCDictionaryEnumeratorActionCurrent, CCDictionaryEnumeratorGetType(Enumerator));
            
        case CCEnumeratorFormatFixedBatch:
            return Enumerator->state.fixedBatch.count ? Enumerator->state.fixedBatch.ptr[Enumerator->state.fixedBatch.index] : NULL;
            
        case CCEnumeratorFormatBatch:
            return Enumerator->state.batch.count ? Enumerator->state.batch.ptr + (Enumerator->state.batch.index * Enumerator->state.batch.stride) : NULL;
            
        case CCEnumeratorFormatCircular:
            return Enumerator->state.circular.count ? Enumerator->state.circular.ptr + ((Enumerator->state.circular.index % Enumerator->state.circular.max) * Enumerator->state.circular.stride) : NULL;
    }
    
    return NULL;
}

static CC_FORCE_INLINE void *CCDictionaryEnumeratorGetHead(CCEnumerator *Enumerator)
{
    return ((CCDictionary)Enumerator->ref)->interface->enumerator(((CCDictionary)Enumerator->ref)->internal, &Enumerator->state, CCDictionaryEnumeratorActionHead, CCDictionaryEnumeratorGetType(Enumerator));
}

static CC_FORCE_INLINE void *CCDictionaryEnumeratorGetTail(CCEnumerator *Enumerator)
{
    return ((CCDictionary)Enumerator->ref)->interface->enumerator(((CCDictionary)Enumerator->ref)->internal, &Enumerator->state, CCDictionaryEnumeratorActionTail, CCDictionaryEnumeratorGetType(Enumerator));
}

static CC_FORCE_INLINE void *CCDictionaryEnumeratorNext(CCEnumerator *Enumerator)
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
            
        case CCEnumeratorFormatCircular:
            if (Enumerator->state.circular.count == 0) return NULL;
            else if ((Enumerator->state.circular.index + 1) < (Enumerator->state.circular.count + Enumerator->state.circular.start)) return Enumerator->state.circular.ptr + ((++Enumerator->state.circular.index % Enumerator->state.circular.max) * Enumerator->state.circular.stride);
            break;
            
        default:
            break;
    }
    
    return ((CCDictionary)Enumerator->ref)->interface->enumerator(((CCDictionary)Enumerator->ref)->internal, &Enumerator->state, CCDictionaryEnumeratorActionNext, CCDictionaryEnumeratorGetType(Enumerator));
}

static CC_FORCE_INLINE void *CCDictionaryEnumeratorPrevious(CCEnumerator *Enumerator)
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
            
        case CCEnumeratorFormatCircular:
            if (Enumerator->state.circular.count == 0) return NULL;
            else if (Enumerator->state.circular.index > Enumerator->state.circular.start) return Enumerator->state.circular.ptr + ((--Enumerator->state.circular.index % Enumerator->state.circular.max) * Enumerator->state.circular.stride);
            break;
            
        default:
            break;
    }
    
    return ((CCDictionary)Enumerator->ref)->interface->enumerator(((CCDictionary)Enumerator->ref)->internal, &Enumerator->state, CCDictionaryEnumeratorActionPrevious, CCDictionaryEnumeratorGetType(Enumerator));
}

#endif
