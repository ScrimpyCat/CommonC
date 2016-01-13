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

#include <CommonC/Enumerator.h>
#include <CommonC/CCString.h>
#include <CommonC/Extensions.h>

static CC_FORCE_INLINE size_t CCStringEnumeratorGetIndex(CCEnumerator *Enumerator)
{
    switch (Enumerator->state.type)
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
    switch (Enumerator->state.type)
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
    switch (Enumerator->state.type)
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
    switch (Enumerator->state.type)
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
