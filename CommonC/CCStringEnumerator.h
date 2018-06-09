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

#ifndef CommonC_CCStringEnumerator_h
#define CommonC_CCStringEnumerator_h

#include <CommonC/Base.h>
#include <CommonC/Enumerator.h>
#include <CommonC/CCString.h>
#include <CommonC/Extensions.h>


/*!
 * @define CC_STRING_CURRENT_ENUMERATOR
 * @abstract Convenient macro to reference the enumerator of the current CC_STRING_FOREACH block.
 */
#define CC_STRING_CURRENT_ENUMERATOR CC_PRIV_string_enumerator___

/*!
 * @define CC_STRING_FOREACH
 * @abstract Convenient macro to iterate through each character in a string.
 * @discussion Behaves like a for loop expression, where it should either be followed by parantheses or a
 *             single line statement.
 *
 * @warning Scoping rules apply, to avoid unintended problems with nested foreach loops either change
 *          CC_STRING_CURRENT_ENUMERATOR, or enclosed it in a braces.
 *
 * @param character The name for the character variable. Will be declared as type @b CCChar.
 * @param string The string to iterate through.
 */
#define CC_STRING_FOREACH(character, string) \
CCEnumerator CC_STRING_CURRENT_ENUMERATOR; \
CCStringGetEnumerator(string, &CC_STRING_CURRENT_ENUMERATOR); \
\
for (CCChar character = CCStringEnumeratorGetCurrent(&CC_STRING_CURRENT_ENUMERATOR); character; character = CCStringEnumeratorNext(&CC_STRING_CURRENT_ENUMERATOR))


/*!
 * @brief Get the current index in the enumerator.
 * @param Enumerator The enumerator to get the reference to.
 * @return The index to the current character. Will return SIZE_MAX on invalid position.
 */
static CC_FORCE_INLINE size_t CCStringEnumeratorGetIndex(CCEnumerator *Enumerator);

/*!
 * @brief Get the current character in the enumerator.
 * @param Enumerator The enumerator to get the character from.
 * @return The current character.
 */
static CC_FORCE_INLINE CCChar CCStringEnumeratorGetCurrent(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the head.
 * @param Enumerator The enumerator to point to the head.
 * @return The current character.
 */
static CC_FORCE_INLINE CCChar CCStringEnumeratorGetHead(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the tail.
 * @param Enumerator The enumerator to point to the tail.
 * @return The current character.
 */
static CC_FORCE_INLINE CCChar CCStringEnumeratorGetTail(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the next position.
 * @description Once the enumerator has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerator The enumerator to point to the next character.
 * @return The current character or 0 if it has reached the end.
 */
static CC_FORCE_INLINE CCChar CCStringEnumeratorNext(CCEnumerator *Enumerator);

/*!
 * @brief Set the enumerator to the previous position.
 * @description Once the enumerator has reached the end, further usage is undefined. To
 *              correctly use it again its position must be set again.
 *
 * @param Enumerator The enumerator to point to the previous character.
 * @return The current character or 0 if it has reached the end.
 */
static CC_FORCE_INLINE CCChar CCStringEnumeratorPrevious(CCEnumerator *Enumerator);


#pragma mark -

static CC_FORCE_INLINE size_t CCStringEnumeratorGetIndex(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatInternal:
            return Enumerator->state.internal.extra[0];
            
        case CCEnumeratorFormatBatch:
            return Enumerator->state.batch.index;
            
        default:
            break;
    }
    
    return SIZE_MAX;
}

static CC_FORCE_INLINE CCChar CCStringEnumeratorGetCurrent(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatInternal:
            return (CCChar)Enumerator->state.internal.extra[1];
            
        case CCEnumeratorFormatBatch:
            return Enumerator->state.batch.count ? *(char*)(Enumerator->state.batch.ptr + (Enumerator->state.batch.index * Enumerator->state.batch.stride)) : 0;
            
        default:
            break;
    }
    
    return 0;
}

static CC_FORCE_INLINE CCChar CCStringEnumeratorGetHead(CCEnumerator *Enumerator)
{
    return CCStringEnumerator((CCString)Enumerator->ref, &Enumerator->state, CCStringEnumeratorActionHead);
}

static CC_FORCE_INLINE CCChar CCStringEnumeratorGetTail(CCEnumerator *Enumerator)
{
    return CCStringEnumerator((CCString)Enumerator->ref, &Enumerator->state, CCStringEnumeratorActionTail);
}

static CC_FORCE_INLINE CCChar CCStringEnumeratorNext(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatBatch:
            if (Enumerator->state.batch.count == 0) return 0;
            else if (Enumerator->state.batch.index + 1 < Enumerator->state.batch.count) return *(char*)(Enumerator->state.batch.ptr + (++Enumerator->state.batch.index * Enumerator->state.batch.stride));
            break;
            
        default:
            break;
    }
    
    return CCStringEnumerator((CCString)Enumerator->ref, &Enumerator->state, CCStringEnumeratorActionNext);
}

static CC_FORCE_INLINE CCChar CCStringEnumeratorPrevious(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type & CCEnumeratorFormatMask)
    {
        case CCEnumeratorFormatBatch:
            if (Enumerator->state.batch.count == 0) return 0;
            else if (Enumerator->state.batch.index > 0) return *(char*)(Enumerator->state.batch.ptr + (--Enumerator->state.batch.index * Enumerator->state.batch.stride));
            break;
            
        default:
            break;
    }
    
    return CCStringEnumerator((CCString)Enumerator->ref, &Enumerator->state, CCStringEnumeratorActionPrevious);
}

#endif
