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
#include <CommonC/Assertion.h>

#if CC_MEMORY_COUNT == 0
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx0
#define CC_MANGLE_TYPE_CC_MEMORY_Tx0 CCData
#elif CC_MEMORY_COUNT == 1
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx1
#define CC_MANGLE_TYPE_CC_MEMORY_Tx1 CCData
#elif CC_MEMORY_COUNT == 2
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx2
#define CC_MANGLE_TYPE_CC_MEMORY_Tx2 CCData
#elif CC_MEMORY_COUNT == 3
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx3
#define CC_MANGLE_TYPE_CC_MEMORY_Tx3 CCData
#elif CC_MEMORY_COUNT == 4
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx4
#define CC_MANGLE_TYPE_CC_MEMORY_Tx4 CCData
#elif CC_MEMORY_COUNT == 5
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx5
#define CC_MANGLE_TYPE_CC_MEMORY_Tx5 CCData
#elif CC_MEMORY_COUNT == 6
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx6
#define CC_MANGLE_TYPE_CC_MEMORY_Tx6 CCData
#elif CC_MEMORY_COUNT == 7
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx7
#define CC_MANGLE_TYPE_CC_MEMORY_Tx7 CCData
#elif CC_MEMORY_COUNT == 8
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx8
#define CC_MANGLE_TYPE_CC_MEMORY_Tx8 CCData
#elif CC_MEMORY_COUNT == 9
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx9
#define CC_MANGLE_TYPE_CC_MEMORY_Tx9 CCData
#elif CC_MEMORY_COUNT == 10
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx10
#define CC_MANGLE_TYPE_CC_MEMORY_Tx10 CCData
#elif CC_MEMORY_COUNT == 12
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx11
#define CC_MANGLE_TYPE_CC_MEMORY_Tx11 CCData
#elif CC_MEMORY_COUNT == 13
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx12
#define CC_MANGLE_TYPE_CC_MEMORY_Tx12 CCData
#elif CC_MEMORY_COUNT == 14
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx13
#define CC_MANGLE_TYPE_CC_MEMORY_Tx13 CCData
#elif CC_MEMORY_COUNT == 15
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx14
#define CC_MANGLE_TYPE_CC_MEMORY_Tx14 CCData
#elif CC_MEMORY_COUNT == 16
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx15
#define CC_MANGLE_TYPE_CC_MEMORY_Tx15 CCData
#elif CC_MEMORY_COUNT == 17
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx16
#define CC_MANGLE_TYPE_CC_MEMORY_Tx16 CCData
#elif CC_MEMORY_COUNT == 18
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx17
#define CC_MANGLE_TYPE_CC_MEMORY_Tx17 CCData
#elif CC_MEMORY_COUNT == 19
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx18
#define CC_MANGLE_TYPE_CC_MEMORY_Tx18 CCData
#elif CC_MEMORY_COUNT == 20
#undef CC_MANGLE_TYPE_CC_MEMORY_Tx19
#define CC_MANGLE_TYPE_CC_MEMORY_Tx19 CCData
#else
#error Add additional cases
#endif

#pragma mark -

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryRead, (const CCData Data, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    const size_t BaseOffset = Offset % Size;
    CCBufferMap Map = BaseOffset + Count >= Size ? CCDataMapBuffer(Data, 0, Size, CCDataHintRead) : CCDataMapBuffer(Data, BaseOffset, Size - BaseOffset, CCDataHintRead);
    
    CCMemoryRead(Map.ptr, Size, Offset, Count, Buffer);
    
    CCDataUnmapBuffer(Data, Map);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadSwap, (const CCData Data, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    const size_t BaseOffset = Offset % Size;
    CCBufferMap Map = BaseOffset + Count >= Size ? CCDataMapBuffer(Data, 0, Size, CCDataHintRead) : CCDataMapBuffer(Data, BaseOffset, Size - BaseOffset, CCDataHintRead);
    
    CCMemoryReadSwap(Map.ptr, Size, Offset, Count, Buffer);
    
    CCDataUnmapBuffer(Data, Map);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadBig, (const CCData Data, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    const size_t BaseOffset = Offset % Size;
    CCBufferMap Map = BaseOffset + Count >= Size ? CCDataMapBuffer(Data, 0, Size, CCDataHintRead) : CCDataMapBuffer(Data, BaseOffset, Size - BaseOffset, CCDataHintRead);
    
    CCMemoryReadBig(Map.ptr, Size, Offset, Count, Buffer);
    
    CCDataUnmapBuffer(Data, Map);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadLittle, (const CCData Data, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    const size_t BaseOffset = Offset % Size;
    CCBufferMap Map = BaseOffset + Count >= Size ? CCDataMapBuffer(Data, 0, Size, CCDataHintRead) : CCDataMapBuffer(Data, BaseOffset, Size - BaseOffset, CCDataHintRead);
    
    CCMemoryReadLittle(Map.ptr, Size, Offset, Count, Buffer);
    
    CCDataUnmapBuffer(Data, Map);
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryRead, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    CCAssertLog(0, "Unreachable");
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadSwap, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    CCAssertLog(0, "Unreachable");
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadBig, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    CCAssertLog(0, "Unreachable");
}

CC_TEMPLATE(static CC_FORCE_INLINE void, CCMemoryReadLittle, (const PTYPE(void *) Memory, const size_t Size, const size_t Offset, const size_t Count, Ty Buffer))
{
    CCAssertLog(0, "Unreachable");
}
