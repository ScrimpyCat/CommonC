/*
 *  Copyright (c) 2021, Stefan Johnson
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

#include <CommonC/Template.h>

#define CCMemoryRead_T(tx, ty) CC_TEMPLATE_REF(CCMemoryRead, void, tx, size_t, size_t, size_t, ty)
#define CCMemoryReadSwap_T(tx, ty) CC_TEMPLATE_REF(CCMemoryReadSwap, void, tx, size_t, size_t, size_t, ty)
#define CCMemoryReadBig_T(tx, ty) CC_TEMPLATE_REF(CCMemoryReadBig, void, tx, size_t, size_t, size_t, ty)
#define CCMemoryReadLittle_T(tx, ty) CC_TEMPLATE_REF(CCMemoryReadLittle, void, tx, size_t, size_t, size_t, ty)

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryRead, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadSwap, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadBig, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer));
CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadLittle, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer));

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryRead, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    const size_t ValueSize = sizeof(*Buffer);
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        ((uint8_t*)Buffer)[(Loop % ValueSize) + ((Loop / ValueSize) * ValueSize)] = ((uint8_t*)Memory)[(Offset + Loop) % Size];
    }
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryRead, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    CCMemoryRead_T(PTYPE(void *), Ty)(Memory, Size, Offset, Count, Buffer);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadSwap, (const PTYPE(void *)  Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    const size_t ValueSize = sizeof(*Buffer);
    
    for (size_t Loop = 0; Loop < Count; Loop++)
    {
        ((uint8_t*)Buffer)[(ValueSize - 1) - (Loop % ValueSize) + ((Loop / ValueSize) * ValueSize)] = ((uint8_t*)Memory)[(Offset + Loop) % Size];
    }
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadSwap, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    CCMemoryReadSwap_T(PTYPE(void *), Ty)(Memory, Size, Offset, Count, Buffer);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadBig, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
#if CC_HARDWARE_ENDIAN_BIG
    CCMemoryRead_T(PTYPE(void *), Ty)(Memory, Size, Offset, Count, Buffer);
#else
    CCMemoryReadSwap_T(PTYPE(void *), Ty)(Memory, Size, Offset, Count, Buffer);
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadBig, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
#if CC_HARDWARE_ENDIAN_BIG
    CCMemoryRead_T(Tx, Ty)(Memory, Size, Offset, Count, Buffer);
#else
    CCMemoryReadSwap_T(Tx, Ty)(Memory, Size, Offset, Count, Buffer);
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadLittle, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
#if CC_HARDWARE_ENDIAN_LITTLE
    CCMemoryRead_T(PTYPE(void *), Ty)(Memory, Size, Offset, Count, Buffer);
#else
    CCMemoryReadSwap_T(PTYPE(void *), Ty)(Memory, Size, Offset, Count, Buffer);
#endif
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadLittle, (const Tx Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
#if CC_HARDWARE_ENDIAN_LITTLE
    CCMemoryRead_T(Tx, Ty)(Memory, Size, Offset, Count, Buffer);
#else
    CCMemoryReadSwap_T(Tx, Ty)(Memory, Size, Offset, Count, Buffer);
#endif
}
