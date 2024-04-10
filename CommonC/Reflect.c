/*
 *  Copyright (c) 2023, Stefan Johnson
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

#include "Reflect.h"
#include "Assertion_Private.h"
#include "Dictionary.h"
#include "Array.h"
#include "ReflectedTypes.h"

size_t CCReflectTypeSize(CCReflectType Type)
{
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
            return sizeof(void*);
            
        case CCReflectTypeInteger:
            return ((const CCReflectInteger*)Type)->size;
            
        case CCReflectTypeFloat:
            return ((const CCReflectFloat*)Type)->size;
            
        case CCReflectTypeStruct:
            return ((const CCReflectStruct*)Type)->size;
            
        case CCReflectTypeOpaque:
            return ((const CCReflectOpaque*)Type)->size;
            
        case CCReflectTypeArray:
            return CCReflectTypeSize(((const CCReflectArray*)Type)->type) * ((const CCReflectArray*)Type)->count;
            
        case CCReflectTypeValidator:
            return CCReflectTypeSize(((const CCReflectValidator*)Type)->type);
            
        case CCReflectTypeEnumerable:
            return sizeof(CCEnumerable);
    }
    
    CCAssertLog(0, "Unsupported reflection type");
}

CCReflectType CCReflectValidate(const CCReflectValidator *Validator, void *Data, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCReflectType BaseType = Validator->type;
    
    if (*(CCReflectTypeID*)BaseType == CCReflectTypeValidator)
    {
        BaseType = CCReflectValidate(BaseType, Data, Zone, Allocator);
    }
    
    if (Validator->validate(BaseType, Data, Validator))
    {
        if (Validator->success.type)
        {
            CCReflectCopy(Validator->success.type, Data, Validator->success.data, Zone, Allocator, CCReflectAssignmentCopy, TRUE);
            BaseType = Validator->success.type;
        }
    }
    
    else if (Validator->failure.type)
    {
        CCReflectCopy(Validator->failure.type, Data, Validator->failure.data, Zone, Allocator, CCReflectAssignmentCopy, TRUE);
        BaseType = Validator->failure.type;
    }
    
    return BaseType;
}

#pragma mark - Copy

void CCReflectTransferHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args)
{
    CCReflectCopy(Type, Args->dest, Data, Args->zone, Args->allocator, CCReflectAssignmentTransfer, Args->validate);
}

void CCReflectShareHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args)
{
    CCReflectCopy(Type, Args->dest, Data, Args->zone, Args->allocator, CCReflectAssignmentShare, Args->validate);
}

void CCReflectCopyHandler(CCReflectType Type, const void *Data, CCReflectCopyHandlerArgs *Args)
{
    CCReflectCopy(Type, Args->dest, Data, Args->zone, Args->allocator, CCReflectAssignmentCopy, Args->validate);
}

void CCReflectCopy(CCReflectType Type, void *Data, const void *Source, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectAssignment Assignment, _Bool Validate)
{
    CCAssertLog(Type, "Type must not be null");
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog(Source, "Write must not be null");
    
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
            *(void**)Data = *(void**)Source;
            
            _Static_assert(CCReflectAssignmentTransfer == 0, "Expects transfer to be 0");
            
            if (Assignment)
            {
                switch (((const CCReflectPointer*)Type)->ownership)
                {
                    case CCReflectOwnershipWeak:
                        break;
                        
                    case CCReflectOwnershipRetain:
                        if (Assignment == CCReflectAssignmentShare)
                        {
                            CCRetain(*(void**)Data);
                            
                            break;
                        }
                        
                    case CCReflectOwnershipTransfer:
                    {
                        CCAllocatorType DataAllocator = Allocator;
                        
                        if (((const CCReflectPointer*)Type)->storage == CCReflectStorageDynamic)
                        {
                            if (((const CCReflectDynamicPointer*)Type)->allocator.allocator != CC_NULL_ALLOCATOR.allocator) DataAllocator = ((const CCReflectDynamicPointer*)Type)->allocator;
                        }
                        
                        void *Ptr = CCMalloc(Allocator, CCReflectTypeSize(((const CCReflectPointer*)Type)->type), NULL, CC_DEFAULT_ERROR_CALLBACK);
                        CCReflectCopy(((const CCReflectPointer*)Type)->type, Ptr, *(void**)Data, Zone, Allocator, Assignment, Validate);
                        
                        *(void**)Data = Ptr;
                        
                        break;
                    }
                }
            }
            break;
            
        case CCReflectTypeInteger:
            memcpy(Data, Source, ((const CCReflectInteger*)Type)->size);
            break;
            
        case CCReflectTypeFloat:
            memcpy(Data, Source, ((const CCReflectFloat*)Type)->size);
            break;
            
        case CCReflectTypeStruct:
            for (size_t Loop = 0, Count = ((const CCReflectStruct*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectCopy(((const CCReflectStruct*)Type)->fields[Loop].type, Data + ((const CCReflectStruct*)Type)->fields[Loop].offset, Source + ((const CCReflectStruct*)Type)->fields[Loop].offset, Zone, Allocator, Assignment, Validate);
            }
            break;
            
        case CCReflectTypeOpaque:
        {
            CCReflectTypeHandler Handler = NULL;
            
            switch (Assignment)
            {
                case CCReflectAssignmentTransfer:
                    Handler = (CCReflectTypeHandler)CCReflectTransferHandler;
                    break;
                    
                case CCReflectAssignmentShare:
                    Handler = (CCReflectTypeHandler)CCReflectShareHandler;
                    break;
                    
                case CCReflectAssignmentCopy:
                    Handler = (CCReflectTypeHandler)CCReflectCopyHandler;
                    break;
            }
            
            ((const CCReflectOpaque*)Type)->map(Type, Source, Data, Handler);
            
            break;
        }
            
        case CCReflectTypeArray:
        {
            CCReflectType ElementType = ((const CCReflectArray*)Type)->type;
            const size_t ElementSize = CCReflectTypeSize(ElementType);
            
            for (size_t Loop = 0, Count = ((const CCReflectArray*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectCopy(ElementType, Data + (ElementSize * Loop), Source + (ElementSize * Loop), Zone, Allocator, Assignment, Validate);
            }
            
            break;
        }
            
        case CCReflectTypeValidator:
            CCReflectCopy(((const CCReflectValidator*)Type)->type, Data, Source, Zone, Allocator, Assignment, Validate);
            if (Validate) CCReflectValidate(Type, Data, Zone, Allocator);
            break;
            
        case CCReflectTypeEnumerable:
        {
            CCEnumerable Enumerable = *(const CCEnumerable*)Data;
            
            CCReflectType ElementType = ((const CCReflectEnumerable*)Type)->type;
            const size_t ElementSize = CCReflectTypeSize(ElementType);
            
            CCMemoryZoneBlock *Block = CCMemoryZoneGetCurrentBlock(Zone);
            ptrdiff_t Offset = CCMemoryZoneBlockGetCurrentOffset(Block);
            
            size_t Count = 0;
            
            for (const void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable), Count++)
            {
                void *DestElement = CCMemoryZoneAllocate(Zone, ElementSize);
                
                CCMemoryZoneSave(Zone);
                CCReflectCopy(Type, DestElement, Element, Zone, Allocator, Assignment, Validate);
                CCMemoryZoneRestore(Zone);
            }
            
            CCMemoryZoneBlockGetEnumerable(Block, Offset, ElementSize, Count, Data);
            
            break;
        }
    }
}

#pragma mark - Binary Serialization

static void CCReflectSerializeBinaryEndianValue(CCReflectEndian SourceEndianness, const void *Data, size_t Size, CCReflectEndian DestinationEndianness, void *Stream, CCReflectStreamWriter Write)
{
#if CC_HARDWARE_ENDIAN_LITTLE
    switch (SourceEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianLittle:
            switch (DestinationEndianness)
            {
                case CCReflectEndianNative:
                case CCReflectEndianLittle:
                    Write(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
            
        case CCReflectEndianBig:
            switch (DestinationEndianness)
            {
                case CCReflectEndianBig:
                    Write(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
    }
#elif CC_HARDWARE_ENDIAN_BIG
    switch (SourceEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianBig:
            switch (DestinationEndianness)
            {
                case CCReflectEndianNative:
                case CCReflectEndianBig:
                    Write(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
            
        case CCReflectEndianLittle:
            switch (DestinationEndianness)
            {
                case CCReflectEndianLittle:
                    Write(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
    }
#else
#error Unknown native endianness
#endif
    
    CCAssertLog(Size <= 64, "Exceeds max supported size");
    
    uint8_t Buffer[64];
    
    for (size_t Loop = 0; Loop < Size; Loop++)
    {
        Buffer[Loop] = ((const uint8_t*)Data)[(Size - Loop) - 1];
    }
    
    Write(Stream, Buffer, Size);
}

static void CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndian SourceEndianness, const void *Data, size_t Size, _Bool Signed, void *Stream, CCReflectStreamWriter Write)
{
    size_t Invert, Start;
    
#if CC_HARDWARE_ENDIAN_LITTLE
    switch (SourceEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianLittle:
            Invert = 1;
            Start = 0;
            break;
            
        case CCReflectEndianBig:
            Invert = -1;
            Start = Size - 1;
            break;
    }
#elif CC_HARDWARE_ENDIAN_BIG
    switch (SourceEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianBig:
            Invert = 1;
            Start = 0;
            break;
            
        case CCReflectEndianLittle:
            Invert = -1;
            Start = Size - 1;
            break;
    }
#else
#error Unknown native endianness
#endif
    
    CCAssertLog(Size <= 64, "Exceeds max supported size");
    
    uint8_t Buffer[64];
    
    memset(Buffer, 0, sizeof(Buffer));
    
    size_t Count = 0;
    
    if (Signed)
    {
        const uint8_t Sign = ((const uint8_t*)Data)[Start + (Invert * (Size - 1))] >> 7;
        
        const uint8_t InvertMultiplier = Sign ? 0xff : 1;
        const uint8_t InvertAdjust = Sign;
        
        Buffer[0] = Sign << 6;
        
        size_t Max = Size - 1;
        
        while (Max && !(uint8_t)((InvertMultiplier * ((const uint8_t*)Data)[Start + (Invert * Max)]) - InvertAdjust)) Max--;
        
        for (size_t Loop = 0; Loop < Max; Loop++, Count++)
        {
            uint8_t Mask = (Count + 1) % 8;
            
            Buffer[Count] |= ((InvertMultiplier * ((const uint8_t*)Data)[Start + (Invert * Loop)]) - InvertAdjust) & (0x7f >> Mask);
            
            const uint8_t Remainder = ((InvertMultiplier * ((const uint8_t*)Data)[Start + (Invert * Loop)]) - InvertAdjust) & ~(0x7f >> Mask);
            
            Buffer[Count] |= 0x80;
            
            Buffer[Count + 1] = Remainder >> 1;
        }
        
        uint8_t Mask = (Count + 1) % 8;
        
        Buffer[Count] |= (((InvertMultiplier * ((const uint8_t*)Data)[Start + (Invert * Max)]) - InvertAdjust) & 0xff) & (0x7f >> Mask);
        
        const uint8_t Remainder = (((InvertMultiplier * ((const uint8_t*)Data)[Start + (Invert * Max)]) - InvertAdjust) & 0xff) & ~(0x7f >> Mask);
        
        if (Remainder)
        {
            Buffer[Count] |= 0x80;
            Buffer[++Count] = Remainder >> 1;
        }
    }
    
    else
    {
        size_t Max = Size - 1;
        
        while (Max && !((const uint8_t*)Data)[Start + (Invert * Max)]) Max--;
        
        for (size_t Loop = 0; Loop < Max; Loop++, Count++)
        {
            uint8_t Mask = Count % 8;
            
            Buffer[Count] |= ((const uint8_t*)Data)[Start + (Invert * Loop)] & (0x7f >> Mask);
            
            const uint8_t Remainder = ((const uint8_t*)Data)[Start + (Invert * Loop)] & ~(0x7f >> Mask);
            
            Buffer[Count] |= 0x80;
            
            Buffer[Count + 1] = Remainder >> 1;
        }
        
        uint8_t Mask = Count % 8;
        
        Buffer[Count] |= ((const uint8_t*)Data)[Start + (Invert * Max)] & (0x7f >> Mask);
        
        const uint8_t Remainder = ((const uint8_t*)Data)[Start + (Invert * Max)] & ~(0x7f >> Mask);
        
        if (Remainder)
        {
            Buffer[Count] |= 0x80;
            Buffer[++Count] = Remainder >> 1;
        }
    }
    
    Write(Stream, Buffer, Count + 1);
}

static void CCReflectSerializeBinaryIntegerValue(CCReflectEndian SourceEndianness, const void *Data, size_t Size, _Bool Signed, _Bool Fixed, size_t PreferVariableLength, CCReflectEndian DestinationEndianness, void *Stream, CCReflectStreamWriter Write)
{
    if ((Size >= PreferVariableLength) || (!Fixed))
    {
        CCReflectSerializeBinaryVariableLengthIntegerValue(SourceEndianness, Data, Size, Signed, Stream, Write);
    }
    
    else
    {
        CCReflectSerializeBinaryEndianValue(SourceEndianness, Data, Size, DestinationEndianness, Stream, Write);
    }
}

static void CCReflectDeserializeBinaryEndianValue(CCReflectEndian DestinationEndianness, void *Data, size_t Size, CCReflectEndian SourceEndianness, void *Stream, CCReflectStreamReader Read)
{
#if CC_HARDWARE_ENDIAN_LITTLE
    switch (SourceEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianLittle:
            switch (DestinationEndianness)
            {
                case CCReflectEndianNative:
                case CCReflectEndianLittle:
                    Read(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
            
        case CCReflectEndianBig:
            switch (DestinationEndianness)
            {
                case CCReflectEndianBig:
                    Read(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
    }
#elif CC_HARDWARE_ENDIAN_BIG
    switch (SourceEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianBig:
            switch (DestinationEndianness)
            {
                case CCReflectEndianNative:
                case CCReflectEndianBig:
                    Read(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
            
        case CCReflectEndianLittle:
            switch (DestinationEndianness)
            {
                case CCReflectEndianLittle:
                    Read(Stream, Data, Size);
                    return;
                    
                default:
                    break;
            }
            break;
    }
#else
#error Unknown native endianness
#endif
    
    CCAssertLog(Size <= 64, "Exceeds max supported size");
    
    uint8_t Buffer[64];
    
    Read(Stream, Buffer, Size);
    
    for (size_t Loop = 0; Loop < Size; Loop++)
    {
        ((uint8_t*)Data)[Loop] = Buffer[(Size - Loop) - 1];
    }
}

static void CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndian DestinationEndianness, void *Data, size_t Size, _Bool Signed, void *Stream, CCReflectStreamReader Read)
{
    size_t Invert, Start;
    
#if CC_HARDWARE_ENDIAN_LITTLE
    switch (DestinationEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianLittle:
            Invert = 1;
            Start = 0;
            break;
            
        case CCReflectEndianBig:
            Invert = -1;
            Start = Size - 1;
            break;
    }
#elif CC_HARDWARE_ENDIAN_BIG
    switch (DestinationEndianness)
    {
        case CCReflectEndianNative:
        case CCReflectEndianBig:
            Invert = 1;
            Start = 0;
            break;
            
        case CCReflectEndianLittle:
            Invert = -1;
            Start = Size - 1;
            break;
    }
#else
#error Unknown native endianness
#endif
    
    memset(Data, 0, Size);
    
    if (Signed)
    {
        uint8_t Buffer[2];
        
        for (size_t Loop = 0, Count = 0; ; Loop++, Count++)
        {
            uint8_t Mask = (Count + 1) % 8, Value;
            
            Read(Stream, &Value, 1);
            
            Buffer[(_Bool)Loop] = Value;
            
            if (Count < Size) ((uint8_t*)Data)[Start + (Invert * Count)] |= Value & (0x7f >> Mask);
            
            const uint8_t Remainder = Value & ~(0x7f >> Mask);
            
            if (Remainder)
            {
                if ((Count - 1) < Size) ((uint8_t*)Data)[Start + (Invert * (Count - 1))] |= Remainder << 1;
                
                if (Remainder & 0x80) continue;
            }
            
            else if (Count >= Size) memset(Data, 0xff, Size);
            
            break;
        }
        
        ((uint8_t*)Data)[Start + (Invert * (Size - 1))] &= 0x7f;
        
        if (Buffer[0] & 0x40)
        {
            for (size_t Loop = 0; Loop < Size; Loop++)
            {
                ((uint8_t*)Data)[Loop] = ~((uint8_t*)Data)[Loop];
            }
        }
    }
    
    else
    {
        for (size_t Loop = 0, Count = 0; ; Loop++, Count++)
        {
            uint8_t Mask = Count % 8, Value;
            
            Read(Stream, &Value, 1);
            
            if (Count < Size) ((uint8_t*)Data)[Start + (Invert * Count)] |= Value & (0x7f >> Mask);
            
            const uint8_t Remainder = Value & ~(0x7f >> Mask);
            
            if (Remainder)
            {
                if ((Count - 1) < Size) ((uint8_t*)Data)[Start + (Invert * (Count - 1))] |= Remainder << 1;
                
                if (Remainder & 0x80) continue;
            }
            
            else if (Count >= Size) memset(Data, 0xff, Size);
            
            break;
        }
    }
}

static void CCReflectDeserializeBinaryIntegerValue(CCReflectEndian DestinationEndianness, void *Data, size_t Size, _Bool Signed, _Bool Fixed, size_t PreferVariableLength, CCReflectEndian SourceEndianness, void *Stream, CCReflectStreamReader Read)
{
    if ((Size >= PreferVariableLength) || (!Fixed))
    {
        CCReflectDeserializeBinaryVariableLengthIntegerValue(DestinationEndianness, Data, Size, Signed, Stream, Read);
    }
    
    else
    {
        CCReflectDeserializeBinaryEndianValue(DestinationEndianness, Data, Size, SourceEndianness, Stream, Read);
    }
}

static void CCReflectSerializeBinaryStringValue(const CCString String, CCReflectEndian DestinationEndianness, void *Stream, CCReflectStreamWriter Write)
{
    const size_t Size = CCStringGetSize(String);
    CCReflectSerializeBinaryEndianValue(CCReflectEndianNative, &Size, sizeof(Size), DestinationEndianness, Stream, Write);
    
    CC_STRING_TEMP_BUFFER(Buffer, String)
    {
        Write(Stream, Buffer, Size);
    }
}

static CC_NEW CCString CCReflectDeserializeBinaryStringValue(CCReflectEndian SourceEndianness, void *Stream, CCReflectStreamReader Read, CCAllocatorType Allocator)
{
    size_t Size;
    CCReflectDeserializeBinaryEndianValue(CCReflectEndianNative, &Size, sizeof(Size), SourceEndianness, Stream, Read);
    
    void *Buffer = CCMalloc(Allocator, Size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    Read(Stream, Buffer, Size);
    
    return CCStringCreateWithSize(Allocator, CCStringEncodingUTF8 | CCStringHintFree, Buffer, Size);
}

static void CCReflectSerializeBinaryTypeData(CCReflectType Type, CCReflectEndian DestinationEndianness, void *Stream, CCReflectStreamWriter Write, CCDictionary Indexes, size_t *Index)
{
    CCDictionarySetValue(Indexes, &Type, Index);
    
    (*Index)++;
    
    const uint8_t ID = *(const CCReflectTypeID*)Type << 4;
    
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
        {
            CCAssertLog(((const CCReflectPointer*)Type)->storage != CCReflectStorageStatic, "Cannot serialize static pointer type");
            
            // [  0:4  ][_:1][storage:1][ownership:2][type:n][allocator:n]
            Write(Stream, &(uint8_t){ ID | (((const CCReflectPointer*)Type)->storage << 2) | ((const CCReflectPointer*)Type)->ownership }, 1);
            
            CCAssertLog(((const CCReflectDynamicPointer*)Type)->allocator.allocator == CC_NULL_ALLOCATOR.allocator, "Cannot serialize dynamic pointer types with custom allocators");
            
            const size_t *TypeIndex = CCDictionaryGetValue(Indexes, &((const CCReflectPointer*)Type)->type);
            
            if (TypeIndex)
            {
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, TypeIndex, sizeof(*TypeIndex), FALSE, Stream, Write);
            }
            
            else
            {
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, Index, sizeof(*Index), FALSE, Stream, Write);
                CCReflectSerializeBinaryTypeData(((const CCReflectPointer*)Type)->type, DestinationEndianness, Stream, Write, Indexes, Index);
            }
            
            break;
        }
            
        case CCReflectTypeInteger:
            // [  1:4  ][sign:1][fixed:1][endian:2][size:n]
            Write(Stream, &(uint8_t){ ID | (((const CCReflectInteger*)Type)->sign << 3) | (((const CCReflectInteger*)Type)->fixed << 2) | ((const CCReflectInteger*)Type)->endian }, 1);
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectInteger*)Type)->size, sizeof(((const CCReflectInteger*)Type)->size), FALSE, Stream, Write);
            break;
            
        case CCReflectTypeFloat:
            // [  2:4  ][_:2][endian:2][size:n]
            Write(Stream, &(uint8_t){ ID | ((const CCReflectFloat*)Type)->endian }, 1);
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectFloat*)Type)->size, sizeof(((const CCReflectFloat*)Type)->size), FALSE, Stream, Write);
            break;
            
        case CCReflectTypeStruct:
            // [  4:4  ][_:4][size:n][count:n][field:n]
            // field: [name:n][offset:n][type:n]
            
            Write(Stream, &ID, 1);
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectStruct*)Type)->size, sizeof(((const CCReflectStruct*)Type)->size), FALSE, Stream, Write);
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectStruct*)Type)->count, sizeof(((const CCReflectStruct*)Type)->count), FALSE, Stream, Write);
            
            for (size_t Loop = 0, Count = ((const CCReflectStruct*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectSerializeBinaryStringValue(((const CCReflectStruct*)Type)->fields[Loop].name, DestinationEndianness, Stream, Write);
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectStruct*)Type)->fields[Loop].offset, sizeof(((const CCReflectStruct*)Type)->fields[Loop].offset), FALSE, Stream, Write);
                
                const size_t *TypeIndex = CCDictionaryGetValue(Indexes, &((const CCReflectStruct*)Type)->fields[Loop].type);
                
                if (TypeIndex)
                {
                    CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, TypeIndex, sizeof(*TypeIndex), FALSE, Stream, Write);
                }
                
                else
                {
                    CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, Index, sizeof(*Index), FALSE, Stream, Write);
                    CCReflectSerializeBinaryTypeData(((const CCReflectStruct*)Type)->fields[Loop].type, DestinationEndianness, Stream, Write, Indexes, Index);
                }
            }
            break;
            
        case CCReflectTypeOpaque:
            CCAssertLog(0, "Cannot serialize opaque type");
            break;
            
        case CCReflectTypeArray:
        {
            // [  6:4  ][_:4][count:n][type:n]
            Write(Stream, &ID, 1);
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectArray*)Type)->count, sizeof(((const CCReflectArray*)Type)->count), FALSE, Stream, Write);
            
            const size_t *TypeIndex = CCDictionaryGetValue(Indexes, &((const CCReflectArray*)Type)->type);
            
            if (TypeIndex)
            {
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, TypeIndex, sizeof(*TypeIndex), FALSE, Stream, Write);
            }
            
            else
            {
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, Index, sizeof(*Index), FALSE, Stream, Write);
                CCReflectSerializeBinaryTypeData(((const CCReflectArray*)Type)->type, DestinationEndianness, Stream, Write, Indexes, Index);
            }
            
            break;
        }
            
        case CCReflectTypeValidator:
            CCAssertLog(0, "Cannot serialize validator type");
            break;
            
        case CCReflectTypeEnumerable:
        {
            // [  8:4  ][_:4][count:n][type:n]
            Write(Stream, &ID, 1);
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectEnumerable*)Type)->count, sizeof(((const CCReflectEnumerable*)Type)->count), FALSE, Stream, Write);
            
            const size_t *TypeIndex = CCDictionaryGetValue(Indexes, &((const CCReflectEnumerable*)Type)->type);
            
            if (TypeIndex)
            {
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, TypeIndex, sizeof(*TypeIndex), FALSE, Stream, Write);
            }
            
            else
            {
                CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, Index, sizeof(*Index), FALSE, Stream, Write);
                CCReflectSerializeBinaryTypeData(((const CCReflectEnumerable*)Type)->type, DestinationEndianness, Stream, Write, Indexes, Index);
            }
            
            break;
        }
    }
}

static void CCReflectSerializeBinaryType(CCReflectType Type, CCReflectEndian DestinationEndianness, void *Stream, CCReflectStreamWriter Write, CCAllocatorType Allocator)
{
    CCDictionary Indexes = CCDictionaryCreate(Allocator, CCDictionaryHintSizeSmall, sizeof(void*), sizeof(size_t), NULL);
    
    CCReflectSerializeBinaryTypeData(Type, DestinationEndianness, Stream, Write, Indexes, &(size_t){ 0 });
    
    CCDictionaryDestroy(Indexes);
}

static CCReflectType CCReflectDeserializeBinaryTypeData(CCMemoryZone Zone, CCReflectEndian SerializedEndianness, void *Stream, CCReflectStreamReader Read, CCArray Types)
{
    uint8_t ID;
    Read(Stream, &ID, 1);
    
    switch (ID >> 4)
    {
        case CCReflectTypePointer:
        {
            // [  0:4  ][_:1][storage:1][ownership:2][type:n][allocator:n]
            CCReflectPointer *Pointer = CCMemoryZoneAllocate(Zone, sizeof(union { CCReflectStaticPointer staticPointer; CCReflectDynamicPointer dynamicPointer; }));
            
            CCArrayAppendElement(Types, &Pointer);
            
            Pointer->id = CCReflectTypePointer;
            Pointer->storage = (ID & 4) >> 2;
            Pointer->ownership = ID & 3;
            
            CCAssertLog(Pointer->storage != CCReflectStorageStatic, "Cannot deserialize static pointer type");
            
            size_t TypeIndex;
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &TypeIndex, sizeof(TypeIndex), FALSE, Stream, Read);
            
            Pointer->type = TypeIndex < CCArrayGetCount(Types) ? *(CCReflectType*)CCArrayGetElementAtIndex(Types, TypeIndex) : CCReflectDeserializeBinaryTypeData(Zone, SerializedEndianness, Stream, Read, Types);
            
            ((CCReflectDynamicPointer*)Pointer)->allocator = CC_NULL_ALLOCATOR;
            
            return Pointer;
        }
            
        case CCReflectTypeInteger:
        {
            // [  1:4  ][sign:1][fixed:1][endian:2][size:n]
            CCReflectInteger *Integer = CCMemoryZoneAllocate(Zone, sizeof(CCReflectInteger));
            
            CCArrayAppendElement(Types, &Integer);
            
            Integer->id = CCReflectTypeInteger;
            Integer->sign = ID & 8;
            Integer->fixed = ID & 4;
            Integer->endian = ID & 3;
            
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Integer->size, sizeof(Integer->size), FALSE, Stream, Read);
            
            return Integer;
        }
            
        case CCReflectTypeFloat:
        {
            // [  2:4  ][_:2][endian:2][size:n]
            CCReflectFloat *Float = CCMemoryZoneAllocate(Zone, sizeof(CCReflectFloat));
            
            CCArrayAppendElement(Types, &Float);
            
            Float->id = CCReflectTypeFloat;
            Float->endian = ID & 3;
            
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Float->size, sizeof(Float->size), FALSE, Stream, Read);
            
            return Float;
        }
            
        case CCReflectTypeStruct:
        {
            // [  4:4  ][_:4][size:n][count:n][field:n]
            // field: [name:n][offset:n][type:n]
            
            size_t Size, Count;
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Size, sizeof(Size), FALSE, Stream, Read);
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Count, sizeof(Count), FALSE, Stream, Read);
            
            CCReflectStruct *Struct = CCMemoryZoneAllocate(Zone, sizeof(CCReflectStruct) + (sizeof(*Struct->fields) * Count));
            
            CCArrayAppendElement(Types, &Struct);
            
            Struct->id = CCReflectTypeStruct;
            Struct->size = Size;
            Struct->count = Count;
            
            for (size_t Loop = 0; Loop < Count; Loop++)
            {
                Struct->fields[Loop].name = CCReflectDeserializeBinaryStringValue(SerializedEndianness, Stream, Read, CC_ZONE_ALLOCATOR(Zone));
                CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Struct->fields[Loop].offset, sizeof(Struct->fields[Loop].offset), FALSE, Stream, Read);
                
                size_t TypeIndex;
                CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &TypeIndex, sizeof(TypeIndex), FALSE, Stream, Read);
                
                Struct->fields[Loop].type = TypeIndex < CCArrayGetCount(Types) ? *(CCReflectType*)CCArrayGetElementAtIndex(Types, TypeIndex) : CCReflectDeserializeBinaryTypeData(Zone, SerializedEndianness, Stream, Read, Types);
            }
            
            return Struct;
        }
            
        case CCReflectTypeOpaque:
            CCAssertLog(0, "Cannot deserialize opaque type");
            break;
            
        case CCReflectTypeArray:
        {
            // [  6:4  ][_:4][count:n][type:n]
            CCReflectArray *Array = CCMemoryZoneAllocate(Zone, sizeof(CCReflectArray));
            
            CCArrayAppendElement(Types, &Array);
            
            Array->id = CCReflectTypeArray;
            
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Array->count, sizeof(Array->count), FALSE, Stream, Read);
            
            size_t TypeIndex;
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &TypeIndex, sizeof(TypeIndex), FALSE, Stream, Read);
            
            Array->type = TypeIndex < CCArrayGetCount(Types) ? *(CCReflectType*)CCArrayGetElementAtIndex(Types, TypeIndex) : CCReflectDeserializeBinaryTypeData(Zone, SerializedEndianness, Stream, Read, Types);
            
            return Array;
        }
            
        case CCReflectTypeValidator:
            CCAssertLog(0, "Cannot deserialize validator type");
            break;
            
        case CCReflectTypeEnumerable:
        {
            // [  8:4  ][_:4][count:n][type:n]
            CCReflectEnumerable *Enumerable = CCMemoryZoneAllocate(Zone, sizeof(CCReflectArray));
            
            CCArrayAppendElement(Types, &Enumerable);
            
            Enumerable->id = CCReflectTypeEnumerable;
            
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Enumerable->count, sizeof(Enumerable->count), FALSE, Stream, Read);
            
            size_t TypeIndex;
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &TypeIndex, sizeof(TypeIndex), FALSE, Stream, Read);
            
            Enumerable->type = TypeIndex < CCArrayGetCount(Types) ? *(CCReflectType*)CCArrayGetElementAtIndex(Types, TypeIndex) : CCReflectDeserializeBinaryTypeData(Zone, SerializedEndianness, Stream, Read, Types);
            
            return Enumerable;
        }
    }
    
    return NULL;
}

static CCReflectType CCReflectDeserializeBinaryType(CCMemoryZone Zone, CCReflectEndian SerializedEndianness, void *Stream, CCReflectStreamReader Read, CCAllocatorType Allocator)
{
    CCArray Types = CCArrayCreate(Allocator, sizeof(CCReflectType), 32);
    
    CCReflectType Type = CCReflectDeserializeBinaryTypeData(Zone, SerializedEndianness, Stream, Read, Types);
    
    CCArrayDestroy(Types);
    
    return Type;
}

typedef struct {
    CCReflectEndian serializedEndianness;
    size_t preferVariableLength;
    void *stream;
    CCReflectStreamWriter write;
    CCMemoryZone zone;
} CCReflectSerializeBinaryHandlerArgs;

static void CCReflectSerializeBinaryHandler(CCReflectType Type, const void *Data, CCReflectSerializeBinaryHandlerArgs *Args)
{
    CCReflectSerializeBinaryType(Type, Args->serializedEndianness, Args->stream, Args->write, CC_ZONE_ALLOCATOR(Args->zone));
    
    CCReflectSerializeBinary(Type, Data, Args->serializedEndianness, Args->preferVariableLength, Args->stream, Args->write, Args->zone);
}

void CCReflectSerializeBinary(CCReflectType Type, const void *Data, CCReflectEndian SerializedEndianness, size_t PreferVariableLength, void *Stream, CCReflectStreamWriter Write, CCMemoryZone Zone)
{
    CCAssertLog(Type, "Type must not be null");
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog(Write, "Write must not be null");
    
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
            if (((const CCReflectPointer*)Type)->storage == CCReflectStorageDynamic)
            {
                if (*(void**)Data)
                {
                    Write(Stream, &(uint8_t){ 1 }, 1);
                    CCReflectSerializeBinary(((const CCReflectPointer*)Type)->type, *(void**)Data, SerializedEndianness, PreferVariableLength, Stream, Write, Zone);
                }
                
                else Write(Stream, &(uint8_t){ 0 }, 1);
            }
            
            else
            {
                ((const CCReflectStaticPointer*)Type)->map(Type, Data, &(CCReflectSerializeBinaryHandlerArgs){
                    .serializedEndianness = SerializedEndianness,
                    .preferVariableLength = PreferVariableLength,
                    .stream = Stream,
                    .write = Write,
                    .zone = Zone
                }, (CCReflectTypeHandler)CCReflectSerializeBinaryHandler);
            }
            break;
            
        case CCReflectTypeInteger:
            CCReflectSerializeBinaryIntegerValue(((const CCReflectInteger*)Type)->endian, Data, ((const CCReflectInteger*)Type)->size, ((const CCReflectInteger*)Type)->sign, ((const CCReflectInteger*)Type)->fixed, PreferVariableLength, SerializedEndianness, Stream, Write);
            break;
            
        case CCReflectTypeFloat:
            CCReflectSerializeBinaryEndianValue(((const CCReflectFloat*)Type)->endian, Data, ((const CCReflectFloat*)Type)->size, SerializedEndianness, Stream, Write);
            break;
            
        case CCReflectTypeStruct:
            for (size_t Loop = 0, Count = ((const CCReflectStruct*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectSerializeBinary(((const CCReflectStruct*)Type)->fields[Loop].type, Data + ((const CCReflectStruct*)Type)->fields[Loop].offset, SerializedEndianness, PreferVariableLength, Stream, Write, Zone);
            }
            break;
            
        case CCReflectTypeOpaque:
            ((const CCReflectOpaque*)Type)->map(Type, Data, &(CCReflectSerializeBinaryHandlerArgs){
                .serializedEndianness = SerializedEndianness,
                .preferVariableLength = PreferVariableLength,
                .stream = Stream,
                .write = Write,
                .zone = Zone
            }, (CCReflectTypeHandler)CCReflectSerializeBinaryHandler);
            break;
            
        case CCReflectTypeArray:
        {
            CCReflectType ElementType = ((const CCReflectArray*)Type)->type;
            const size_t ElementSize = CCReflectTypeSize(ElementType);
            
            for (size_t Loop = 0, Count = ((const CCReflectArray*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectSerializeBinary(ElementType, Data + (ElementSize * Loop), SerializedEndianness, PreferVariableLength, Stream, Write, Zone);
            }
            
            break;
        }
            
        case CCReflectTypeValidator:
            CCReflectSerializeBinary(((const CCReflectValidator*)Type)->type, Data, SerializedEndianness, PreferVariableLength, Stream, Write, Zone);
            break;
            
        case CCReflectTypeEnumerable:
        {
            CCReflectSerializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &((const CCReflectEnumerable*)Type)->count, sizeof(((const CCReflectEnumerable*)Type)->count), FALSE, Stream, Write);
            
            if (((const CCReflectEnumerable*)Type)->count == SIZE_MAX)
            {
                CCEnumerable Enumerable = *(const CCEnumerable*)Data;
                
                CCReflectType ElementType = ((const CCReflectEnumerable*)Type)->type;
                
                for (const void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable))
                {
                    Write(Stream, &(uint8_t){ 1 }, 1);
                    
                    CCReflectSerializeBinary(ElementType, Element, SerializedEndianness, PreferVariableLength, Stream, Write, Zone);
                }
                
                Write(Stream, &(uint8_t){ 0 }, 1);
            }
            
            else
            {
                CCEnumerable Enumerable = *(const CCEnumerable*)Data;
                
                CCReflectType ElementType = ((const CCReflectEnumerable*)Type)->type;
                
                for (const void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable))
                {
                    CCReflectSerializeBinary(ElementType, Element, SerializedEndianness, PreferVariableLength, Stream, Write, Zone);
                }
            }
            
            break;
        }
    }
}

typedef struct {
    void *dest;
    CCReflectEndian serializedEndianness;
    void *stream;
    CCReflectStreamReader read;
    CCAllocatorType allocator;
    CCMemoryZone zone;
} CCReflectDeserializeBinaryHandlerArgs;

static void CCReflectDeserializeBinaryHandler(CCReflectType Type, const void *Data, CCReflectDeserializeBinaryHandlerArgs *Args)
{
    CCReflectCopy(Type, Args->dest, Data, Args->zone, Args->allocator, CCReflectAssignmentShare, TRUE);
}

void CCReflectDeserializeBinary(CCReflectType Type, void *Data, CCReflectEndian SerializedEndianness, size_t PreferVariableLength, void *Stream, CCReflectStreamReader Read, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCAssertLog(Type, "Type must not be null");
    CCAssertLog(Data, "Data must not be null");
    CCAssertLog(Read, "Write must not be null");
    
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypePointer:
        {
            if (((const CCReflectPointer*)Type)->storage == CCReflectStorageDynamic)
            {
                uint8_t Exists;
                Read(Stream, &Exists, sizeof(uint8_t));
                
                if (Exists)
                {
                    CCAllocatorType CustomAllocator = ((const CCReflectDynamicPointer*)Type)->allocator;
                    
                    void *Ptr = CCMalloc((CustomAllocator.allocator == CC_NULL_ALLOCATOR.allocator ? Allocator : CustomAllocator), CCReflectTypeSize(((const CCReflectPointer*)Type)->type), NULL, CC_DEFAULT_ERROR_CALLBACK);
                    CCReflectDeserializeBinary(((const CCReflectPointer*)Type)->type, Ptr, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
                    
                    *(void**)Data = Ptr;
                }
                
                else *(void**)Data = NULL;
            }
            
            else
            {
                CCReflectType MappedType = CCReflectDeserializeBinaryType(Zone, SerializedEndianness, Stream, Read, CC_ZONE_ALLOCATOR(Zone));
                void *MappedData = CCMemoryZoneAllocate(Zone, CCReflectTypeSize(MappedType));
                CCReflectDeserializeBinary(MappedType, MappedData, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
                
                ((const CCReflectStaticPointer*)Type)->unmap(MappedType, MappedData, &(CCReflectDeserializeBinaryHandlerArgs){
                    .dest = Data,
                    .serializedEndianness = SerializedEndianness,
                    .stream = Stream,
                    .read = Read,
                    .allocator = Allocator,
                    .zone = Zone
                }, (CCReflectTypeHandler)CCReflectDeserializeBinaryHandler);
            }
            
            break;
        }
            
        case CCReflectTypeInteger:
            CCReflectDeserializeBinaryIntegerValue(((const CCReflectInteger*)Type)->endian, Data, ((const CCReflectInteger*)Type)->size, ((const CCReflectInteger*)Type)->sign, ((const CCReflectInteger*)Type)->fixed, PreferVariableLength, SerializedEndianness, Stream, Read);
            break;
            
        case CCReflectTypeFloat:
            CCReflectDeserializeBinaryEndianValue(((const CCReflectFloat*)Type)->endian, Data, ((const CCReflectFloat*)Type)->size, SerializedEndianness, Stream, Read);
            break;
            
        case CCReflectTypeStruct:
            for (size_t Loop = 0, Count = ((const CCReflectStruct*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectDeserializeBinary(((const CCReflectStruct*)Type)->fields[Loop].type, Data + ((const CCReflectStruct*)Type)->fields[Loop].offset, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
            }
            break;
            
        case CCReflectTypeOpaque:
        {
            CCReflectType MappedType = CCReflectDeserializeBinaryType(Zone, SerializedEndianness, Stream, Read, CC_ZONE_ALLOCATOR(Zone));
            void *MappedData = CCMemoryZoneAllocate(Zone, CCReflectTypeSize(MappedType));
            CCReflectDeserializeBinary(MappedType, MappedData, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
            
            ((const CCReflectOpaque*)Type)->unmap(MappedType, MappedData, &(CCReflectDeserializeBinaryHandlerArgs){
                .dest = Data,
                .serializedEndianness = SerializedEndianness,
                .stream = Stream,
                .read = Read,
                .allocator = Allocator,
                .zone = Zone
            }, (CCReflectTypeHandler)CCReflectDeserializeBinaryHandler);
            
            break;
        }
            
        case CCReflectTypeArray:
        {
            CCReflectType ElementType = ((const CCReflectArray*)Type)->type;
            const size_t ElementSize = CCReflectTypeSize(ElementType);
            
            for (size_t Loop = 0, Count = ((const CCReflectArray*)Type)->count; Loop < Count; Loop++)
            {
                CCReflectDeserializeBinary(ElementType, Data + (ElementSize * Loop), SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
            }
            
            break;
        }
            
        case CCReflectTypeValidator:
            CCReflectDeserializeBinary(((const CCReflectValidator*)Type)->type, Data, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
            CCReflectValidate(Type, Data, Zone, Allocator);
            break;
            
        case CCReflectTypeEnumerable:
        {
            typeof(((CCReflectEnumerable*)Type)->count) Count;
            CCReflectDeserializeBinaryVariableLengthIntegerValue(CCReflectEndianNative, &Count, sizeof(Count), FALSE, Stream, Read);
            
            CCReflectType ElementType = ((const CCReflectEnumerable*)Type)->type;
            const size_t ElementSize = CCReflectTypeSize(ElementType);
            
            CCMemoryZoneBlock *Block = CCMemoryZoneGetCurrentBlock(Zone);
            ptrdiff_t Offset = CCMemoryZoneBlockGetCurrentOffset(Block);
            
            if (Count == SIZE_MAX)
            {
                Count = 0;
                
                uint8_t Exists;
                Read(Stream, &Exists, sizeof(uint8_t));
                
                for ( ; Exists; Count++)
                {
                    void *Element = CCMemoryZoneAllocate(Zone, ElementSize);
                    
                    CCMemoryZoneSave(Zone);
                    CCReflectDeserializeBinary(ElementType, Element, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
                    CCMemoryZoneRestore(Zone);
                    
                    Read(Stream, &Exists, sizeof(uint8_t));
                }
            }
            
            else
            {
                for (size_t Loop = 0; Loop < Count; Loop++)
                {
                    void *Element = CCMemoryZoneAllocate(Zone, ElementSize);
                    
                    CCMemoryZoneSave(Zone);
                    CCReflectDeserializeBinary(ElementType, Element, SerializedEndianness, PreferVariableLength, Stream, Read, Zone, Allocator);
                    CCMemoryZoneRestore(Zone);
                }
            }
            
            CCMemoryZoneBlockGetEnumerable(Block, Offset, ElementSize, Count, Data);
            
            break;
        }
    }
}
