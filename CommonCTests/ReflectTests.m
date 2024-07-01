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

#import <XCTest/XCTest.h>
#import "Reflect.h"
#import "Array.h"
#import "ValidateMinimum.h"
#import "ValidateMaximum.h"
#import "ReflectedTypes.h"
#import "TypeCallbacks.h"
#import "CollectionEnumerator.h"
#import "LinkedList.h"
#import "List.h"
#import "Queue.h"
#import "HashMap.h"
#import "HashMapSeparateChainingArray.h"
#import "Dictionary.h"

@interface ReflectTests : XCTestCase

@end

@implementation ReflectTests

typedef size_t DataStream;

DataStream Stream = 0;
uint8_t StreamData[1024];

void StreamWriter(void *Stream, const void *Data, size_t Size)
{
    memcpy(StreamData + *(DataStream*)Stream, Data, Size);
    
    *(DataStream*)Stream += Size;
}

void StreamReader(void *Stream, void *Data, size_t Size)
{
    memcpy(Data, StreamData + *(DataStream*)Stream, Size);
    
    *(DataStream*)Stream += Size;
}

static const CCReflectInteger TestNativeU32 = CC_REFLECT_INTEGER(uint32_t, CCReflectEndianNative, .fixed = TRUE);
static const CCReflectArray TestNativeU32x4 = CC_REFLECT_ARRAY(&TestNativeU32, 4);

typedef struct {
    CCReflectOpaque opaque;
    CCReflectType elementType;
} ReflectOpaqueArray;

static void TestOpaqueArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void TestOpaqueArrayUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

ReflectOpaqueArray TestOpaqueArray = {
    .opaque = CC_REFLECT_OPAQUE(sizeof(CCArray), sizeof(ReflectOpaqueArray), TestOpaqueArrayMapper, TestOpaqueArrayUnmapper),
    .elementType = &TestNativeU32
};

static void TestOpaqueArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    const size_t Count = CCArrayGetCount(*(CCArray*)Data);
    CCReflectArray Array = CC_REFLECT_ARRAY(((const ReflectOpaqueArray*)Type)->elementType, Count);
    
    Handler(&Array, CCArrayGetData(*(CCArray*)Data), Args);
}

static void TestOpaqueArrayUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, CCReflectTypeSize(((const CCReflectArray*)MappedType)->type), 16);
    
    CCArrayAppendElements(Array, Data, ((const CCReflectArray*)MappedType)->count);
    
    Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), &Array, Args);
    
    CCArrayDestroy(Array);
}

struct Foo {
    uint32_t x, y;
    struct Foo *next;
};

static const CCReflectStruct3 TestFoo = CC_REFLECT_STRUCT(struct Foo, (x, &TestNativeU32), (y, &TestNativeU32), (next, &CC_REFLECT_DYNAMIC_POINTER(&TestFoo, CCReflectOwnershipWeak)));

static const uint32_t ConstantZero = 0;
static const uint32_t ConstantOne = 1;
static const uint32_t ConstantTwo = 2;

static void TestStaticPointerMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    uint32_t PortableValue = 0;
    
    if (*(uint32_t**)Data == &ConstantZero) PortableValue = 1;
    else if (*(uint32_t**)Data == &ConstantOne) PortableValue = 2;
    else if (*(uint32_t**)Data == &ConstantTwo) PortableValue = 3;
    
    Handler(&TestNativeU32, &PortableValue, Args);
}

static void TestStaticPointerUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

static const CCReflectStaticPointer TestStaticPointer = CC_REFLECT_STATIC_POINTER(&TestNativeU32, CCReflectOwnershipWeak, TestStaticPointerMapper, TestStaticPointerUnmapper);

static void TestStaticPointerUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    const uint32_t *Ptr = NULL;
    
    switch (*(uint32_t*)Data)
    {
        case 1:
            Ptr = &ConstantZero;
            break;
            
        case 2:
            Ptr = &ConstantOne;
            break;
            
        case 3:
            Ptr = &ConstantTwo;
            break;
    }
    
    Handler(&TestStaticPointer, &Ptr, Args);
}

static void TestOpaqueFooMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void TestOpaqueFooUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

CCReflectOpaque TestOpaqueFoo = CC_REFLECT_OPAQUE(sizeof(struct Foo), sizeof(CCReflectOpaque), TestOpaqueFooMapper, TestOpaqueFooUnmapper);

static void TestOpaqueFooMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    Handler(&TestFoo, &(struct Foo){ .x = 5, .y = *(const uint32_t*)Data, .next = NULL }, Args);
}

static void TestOpaqueFooUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    Handler(&TestNativeU32, &((const struct Foo*)Data)->y, Args);
}

static void TestOpaqueEnumerableMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent);
static void TestOpaqueEnumerableUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator);

CCReflectOpaque TestOpaqueEnumerable = CC_REFLECT_OPAQUE(sizeof(CCArray), sizeof(CCReflectOpaque), TestOpaqueEnumerableMapper, TestOpaqueEnumerableUnmapper);

static void TestOpaqueEnumerableMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    CCEnumerable Enumerable;
    CCArrayGetEnumerable(*(CCArray*)Data, &Enumerable);
    
    Handler(&CC_REFLECT_ENUMERABLE(&TestNativeU32), &Enumerable, Args);
}

static void TestOpaqueEnumerableUnmapper(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    switch (*(const CCReflectTypeID*)MappedType)
    {
        case CCReflectTypeArray:
        {
            CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, CCReflectTypeSize(((const CCReflectArray*)MappedType)->type), 16);
            
            CCArrayAppendElements(Array, Data, ((const CCReflectArray*)MappedType)->count);
            
            Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), &Array, Args);
            
            CCArrayDestroy(Array);
            
            break;
        }
            
        case CCReflectTypeEnumerable:
        {
            CCEnumerable Enumerable = *(const CCEnumerable*)Data;
            
            CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, CCReflectTypeSize(((const CCReflectArray*)MappedType)->type), 16);
            
            for (const void *Element = CCEnumerableGetCurrent(&Enumerable); Element; Element = CCEnumerableNext(&Enumerable))
            {
                CCArrayAppendElement(Array, Element);
            }
            
            Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), &Array, Args);
            
            CCArrayDestroy(Array);
            
            break;
        }
            
        default:
            break;
    }
}

-(void) testExample
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 1024);
    
    uint32_t NativeU32[4] = { 1, 2, 0x2000000, 0x1000000 };
    uint32_t NativeU32Value = 0, NativeU32x4Value[4] = { 0, 0, 0, 0 };
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[3], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[1], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[3], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[0], @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[3], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[1], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[3], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[0], @"should deserialize the value correctly");
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianLittle, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
#elif CC_HARDWARE_ENDIAN_BIG
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32Value, NativeU32[0], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32[2], CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32[2], @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32x4, &NativeU32, CCReflectEndianBig, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32x4, &NativeU32x4Value, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);

    XCTAssertEqual(NativeU32x4Value[0], NativeU32[0], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[1], NativeU32[1], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[2], NativeU32[2], @"should deserialize the value correctly");
    XCTAssertEqual(NativeU32x4Value[3], NativeU32[3], @"should deserialize the value correctly");
#endif
    
    
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(uint32_t), 16), ArrayValue = NULL;
    CCArrayAppendElements(Array, NativeU32, 4);
    
    CCReflectSerializeBinary(&TestOpaqueArray, &Array, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestOpaqueArray, &ArrayValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCArrayGetCount(ArrayValue), CCArrayGetCount(Array), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 0), *(uint32_t*)CCArrayGetElementAtIndex(Array, 0), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 1), *(uint32_t*)CCArrayGetElementAtIndex(Array, 1), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 2), *(uint32_t*)CCArrayGetElementAtIndex(Array, 2), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 3), *(uint32_t*)CCArrayGetElementAtIndex(Array, 3), @"should deserialize the value correctly");
    
    
    CCArrayDestroy(ArrayValue); ArrayValue = NULL;
    
    CCReflectSerializeBinary(&TestOpaqueEnumerable, &Array, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestOpaqueEnumerable, &ArrayValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(CCArrayGetCount(ArrayValue), CCArrayGetCount(Array), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 0), *(uint32_t*)CCArrayGetElementAtIndex(Array, 0), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 1), *(uint32_t*)CCArrayGetElementAtIndex(Array, 1), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 2), *(uint32_t*)CCArrayGetElementAtIndex(Array, 2), @"should deserialize the value correctly");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(ArrayValue, 3), *(uint32_t*)CCArrayGetElementAtIndex(Array, 3), @"should deserialize the value correctly");
    
    CCArrayDestroy(Array);
    CCArrayDestroy(ArrayValue);
    
    
    struct Foo FooA = { .x = 0, .y = 1, .next = NULL };
    struct Foo FooB = { .x = 2, .y = 3, .next = &FooA };
    struct Foo FooC = { .x = 4, .y = 5, .next = &FooB };
    struct Foo FooValue = { .x = 0, .y = 0, .next = NULL };
    
    CCReflectSerializeBinary(&TestFoo, &FooC, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestFoo, &FooValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(FooValue.x, FooC.x, @"should deserialize the value correctly");
    XCTAssertEqual(FooValue.y, FooC.y, @"should deserialize the value correctly");
    XCTAssertNotEqual(FooValue.next, NULL, @"should deserialize the value correctly");
    XCTAssertEqual(FooValue.next->x, FooC.next->x, @"should deserialize the value correctly");
    XCTAssertEqual(FooValue.next->y, FooC.next->y, @"should deserialize the value correctly");
    XCTAssertNotEqual(FooValue.next->next, NULL, @"should deserialize the value correctly");
    XCTAssertEqual(FooValue.next->next->x, FooC.next->next->x, @"should deserialize the value correctly");
    XCTAssertEqual(FooValue.next->next->y, FooC.next->next->y, @"should deserialize the value correctly");
    XCTAssertEqual(FooValue.next->next->next, FooC.next->next->next, @"should deserialize the value correctly");
    
    CCFree(FooValue.next->next);
    CCFree(FooValue.next);
    
    
    const uint32_t *StaticPtr = &ConstantTwo, *StaticPtrValue = NULL;
    
    CCReflectSerializeBinary(&TestStaticPointer, &StaticPtr, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestStaticPointer, &StaticPtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(StaticPtrValue, StaticPtr, @"should deserialize the value correctly");
    
    StaticPtr = NULL;
    
    CCReflectSerializeBinary(&TestStaticPointer, &StaticPtr, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestStaticPointer, &StaticPtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(StaticPtrValue, StaticPtr, @"should deserialize the value correctly");
    
    
    uint32_t OpaqueFoo = 3, OpaqueFooValue = 0;
    
    CCReflectSerializeBinary(&TestOpaqueFoo, &OpaqueFoo, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestOpaqueFoo, &OpaqueFooValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(OpaqueFooValue, OpaqueFoo, @"should deserialize the value correctly");
}

-(void) testIntegerBinaryEncoding
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 1024);
    
    uint32_t NativeU32Value = 0;
    
    for (uint32_t Loop = 1; Loop < 4; Loop++)
    {
        for (uint32_t Loop2 = 0; Loop2 < 255; Loop2++)
        {
            for (uint32_t Loop3 = 0; Loop3 < 255; Loop3++)
            {
                uint32_t Value = (Loop2 << (Loop * 8)) | Loop3;
                
                CCReflectSerializeBinary(&TestNativeU32, &Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
                CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
                
                XCTAssertEqual(NativeU32Value, Value, @"should deserialize the value correctly");
            }
        }
    }
    
    uint32_t NativeU32 = UINT32_MAX;
    
    CCReflectSerializeBinary(&TestNativeU32, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, NativeU32, @"should deserialize the value correctly");
    
    static const CCReflectInteger TestNativeU32Native = CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint32_t, CCReflectEndianNative);
    static const CCReflectInteger TestNativeU32Little = CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint32_t, CCReflectEndianNative);
    static const CCReflectInteger TestNativeU32Big = CC_REFLECT_UNSIGNED_FIXED_WIDTH_INTEGER(uint32_t, CCReflectEndianBig);
    
#if CC_HARDWARE_ENDIAN_LITTLE
    NativeU32 = 255;
    
    CCReflectSerializeBinary(&TestNativeU32Native, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Native, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Native, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Little, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Native, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Big, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32Little, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Little, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Little, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Native, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Little, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Big, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    NativeU32 = 0xff000000;
    
    CCReflectSerializeBinary(&TestNativeU32Big, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Big, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Big, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Little, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Big, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Native, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
#elif CC_HARDWARE_ENDIAN_BIG
    NativeU32 = 255;
    
    CCReflectSerializeBinary(&TestNativeU32Native, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Big, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Native, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Native, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Native, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Little, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeU32Big, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Big, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Big, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Native, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Big, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Little, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    NativeU32 = 0xff000000;
    
    CCReflectSerializeBinary(&TestNativeU32Little, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Little, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Little, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Big, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeU32Little, &NativeU32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeU32Native, &NativeU32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeU32Value, 0xff, @"should deserialize the value correctly");
#endif
    
    
    static const CCReflectInteger TestNativeI32 = CC_REFLECT_INTEGER(uint32_t, CCReflectEndianNative, .fixed = TRUE, .sign = TRUE);
    
    uint32_t NativeI32Value = 0;
    
    for (uint32_t Loop = 1; Loop < 4; Loop++)
    {
        for (uint32_t Loop2 = 0; Loop2 < 255; Loop2++)
        {
            for (uint32_t Loop3 = 0; Loop3 < 255; Loop3++)
            {
                int32_t Value = (Loop2 << (Loop * 8)) | Loop3;
                
                CCReflectSerializeBinary(&TestNativeI32, &Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
                CCReflectDeserializeBinary(&TestNativeI32, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
                
                XCTAssertEqual(NativeI32Value, Value, @"should deserialize the value correctly");
                
                
                Value = -Value;
                
                CCReflectSerializeBinary(&TestNativeI32, &Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
                CCReflectDeserializeBinary(&TestNativeI32, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
                
                XCTAssertEqual(NativeI32Value, Value, @"should deserialize the value correctly");
            }
        }
    }
    
    uint32_t NativeI32 = INT32_MAX;
    
    CCReflectSerializeBinary(&TestNativeI32, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, NativeI32, @"should deserialize the value correctly");
    
    NativeI32 = INT32_MIN;
    
    CCReflectSerializeBinary(&TestNativeI32, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, NativeI32, @"should deserialize the value correctly");
    
    static const CCReflectInteger TestNativeI32Native = CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int32_t, CCReflectEndianNative);
    static const CCReflectInteger TestNativeI32Little = CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int32_t, CCReflectEndianNative);
    static const CCReflectInteger TestNativeI32Big = CC_REFLECT_SIGNED_FIXED_WIDTH_INTEGER(int32_t, CCReflectEndianBig);
    
#if CC_HARDWARE_ENDIAN_LITTLE
    NativeI32 = 255;
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    NativeI32 = 0xff000000;
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
#elif CC_HARDWARE_ENDIAN_BIG
    NativeI32 = 255;
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    
    NativeI32 = 0xff000000;
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Little, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Native, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
    
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Big, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Native, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff000000, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeI32Big, &NativeI32, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeI32Little, &NativeI32Value, CCReflectEndianNative, 0, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(NativeI32Value, 0xff, @"should deserialize the value correctly");
#endif
    
    
    static const CCReflectInteger TestNativeVariableU16 = CC_REFLECT_INTEGER(uint16_t, CCReflectEndianNative);
    static const CCReflectInteger TestNativeVariableU32 = CC_REFLECT_INTEGER(uint32_t, CCReflectEndianNative);
    
    uint16_t U16 = 0;
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 0 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 0, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 1 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 1, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 2 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 2, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 255 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 255, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 0x7fff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 0xffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 0xffff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 0x10000 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 0xffff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 0x1ffffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 0xffff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU32, &(uint32_t){ 0xffffffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU16, &U16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U16, 0xffff, @"should deserialize the value correctly");
    
    uint32_t U32 = 0;
    
    CCReflectSerializeBinary(&TestNativeVariableU16, &(uint16_t){ 0 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU32, &U32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U32, 0, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU16, &(uint16_t){ 1 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU32, &U32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U32, 1, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU16, &(uint16_t){ 2 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU32, &U32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U32, 2, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU16, &(uint16_t){ 255 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU32, &U32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U32, 255, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU16, &(uint16_t){ 0x7fff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU32, &U32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U32, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableU16, &(uint16_t){ 0xffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableU32, &U32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(U32, 0xffff, @"should deserialize the value correctly");
    
    
    static const CCReflectInteger TestNativeVariableI16 = CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    static const CCReflectInteger TestNativeVariableI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    int16_t I16 = 0;
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 0 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 0, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 1 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 1, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 2 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 2, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 255 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 255, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 0x7fff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 0xffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 0x10000 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 0x1ffffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ 0x7fffffff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ -1 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, -1, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ -2 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, -2, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ -255 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, -255, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ INT16_MIN }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, INT16_MIN, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI32, &(int32_t){ INT32_MIN }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI16, &I16, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I16, INT16_MIN, @"should deserialize the value correctly");
    
    int32_t I32 = 0;
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ 0 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, 0, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ 1 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, 1, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ 2 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, 2, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ 255 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, 255, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ 0x7fff }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, 0x7fff, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ -1 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, -1, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ -2 }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, -2, @"should deserialize the value correctly");
    
    CCReflectSerializeBinary(&TestNativeVariableI16, &(int16_t){ INT16_MIN }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&TestNativeVariableI32, &I32, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(I32, INT16_MIN, @"should deserialize the value correctly");
    
    CCMemoryZoneDestroy(Zone);
}

-(void) assertMinimum: (CCReflectValue)minimum Passes: (void**)passes Fails: (void**)fails OfType: (CCReflectType)type
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 32);
    
    static const CCReflectInteger TestBool = CC_REFLECT_INTEGER(_Bool, CCReflectEndianNative);
    CCReflectType Min = &CC_REFLECT_VALIDATE_MINIMUM(type, minimum, CC_REFLECT_RESULT(&TestBool, (&(_Bool){ TRUE })), CC_REFLECT_RESULT(&TestBool, (&(_Bool){ FALSE })));
    
    for (size_t Loop = 0; passes[Loop]; Loop++)
    {
        CCReflectType BaseType = CCReflectValidate(Min, passes[Loop], Zone, CC_STD_ALLOCATOR);
        
        XCTAssertEqual(BaseType, &TestBool, @"should return base type");
        XCTAssertTrue(*(_Bool*)passes[Loop], @"should validate the value correctly");
    }
    
    for (size_t Loop = 0; fails[Loop]; Loop++)
    {
        CCReflectType BaseType = CCReflectValidate(Min, fails[Loop], Zone, CC_STD_ALLOCATOR);
        
        XCTAssertEqual(BaseType, &TestBool, @"should return base type");
        XCTAssertFalse(*(_Bool*)fails[Loop], @"should validate the value correctly");
    }
    
    CCMemoryZoneDestroy(Zone);
}

-(void) assertMaximum: (CCReflectValue)maximum Passes: (void**)passes Fails: (void**)fails OfType: (CCReflectType)type
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 32);
    
    static const CCReflectInteger TestBool = CC_REFLECT_INTEGER(_Bool, CCReflectEndianNative);
    CCReflectType Max = &CC_REFLECT_VALIDATE_MAXIMUM(type, maximum, CC_REFLECT_RESULT(&TestBool, (&(_Bool){ TRUE })), CC_REFLECT_RESULT(&TestBool, (&(_Bool){ FALSE })));
    
    for (size_t Loop = 0; passes[Loop]; Loop++)
    {
        CCReflectType BaseType = CCReflectValidate(Max, passes[Loop], Zone, CC_STD_ALLOCATOR);
        
        XCTAssertEqual(BaseType, &TestBool, @"should return base type");
        XCTAssertTrue(*(_Bool*)passes[Loop], @"should validate the value correctly");
    }
    
    for (size_t Loop = 0; fails[Loop]; Loop++)
    {
        CCReflectType BaseType = CCReflectValidate(Max, fails[Loop], Zone, CC_STD_ALLOCATOR);
        
        XCTAssertEqual(BaseType, &TestBool, @"should return base type");
        XCTAssertFalse(*(_Bool*)fails[Loop], @"should validate the value correctly");
    }
    
    CCMemoryZoneDestroy(Zone);
}

-(void) testValidations
{
    CCReflectType LimitType = &TestNativeU32;
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianLittle);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianBig);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianBig);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianLittle);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x10000 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x10000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    
    LimitType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianNative);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianLittle);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianBig);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianBig);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianLittle);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x0100 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x0001 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x00ff }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x01ff }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x1000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x0001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint32_t){ 0x00ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(uint16_t){ 0x01ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
    
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x000000ff }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000ff }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
    
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0100 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0001 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x00ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x01ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0100 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x00ff }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x01ff }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                 OfType: &TestNativeU32];
    
    
    
    static const CCReflectInteger NativeI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &NativeI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &NativeI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &NativeI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 },  NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    
    
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0 },  &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0 },  &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0100 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0001 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x00ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x01ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x100 }))
                 Passes: (void*[]){ &(int32_t){ 0 },  &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x0001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x00ff }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int16_t){ 0x01ff }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &NativeI32];
    
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    static const CCReflectInteger AliasI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    static const CCReflectInteger AliasI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &AliasI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                 OfType: &AliasI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    static const CCReflectInteger FlippedI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    static const CCReflectInteger FlippedI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x0000007f }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x000000ff }, NULL }
                 OfType: &FlippedI32];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x0000007f }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0x000000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                 OfType: &FlippedI32];
    
    
    
    static const CCReflectInteger NativeI16 = CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    
    LimitType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int16_t){ 0x7f00 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xffffff01 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 0xff00 }, NULL }
                 OfType: &NativeI16];
    
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 0x7f00 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ NULL }
                  Fails: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(int32_t){ 0xffffff01 }))
                 Passes: (void*[]){ &(int16_t){ 0xff00 }, &(int16_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ &(int16_t){ 0 }, &(int16_t){ 1 }, &(int16_t){ 255 }, &(int16_t){ 0x7f00 }, NULL }
                 OfType: &NativeI16];
    
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_FLOAT(float, CCReflectEndianLittle);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_FLOAT(float, CCReflectEndianBig);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(float){ 0.5f }))
                 Passes: (void*[]){ &(double){ 0.5 }, &(double){ 1.0 }, NULL }
                  Fails: (void*[]){ &(double){ -1.0 }, &(double){ 0.0 }, NULL }
                 OfType: &CC_REFLECT_FLOAT(double, CCReflectEndianNative)];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(float){ 0.5f }))
                 Passes: (void*[]){ &(double){ 0.5 }, &(double){ -1.0 }, &(double){ 0.0 }, NULL }
                  Fails: (void*[]){ &(double){ 1.0 }, NULL }
                 OfType: &CC_REFLECT_FLOAT(double, CCReflectEndianNative)];
    
#if CC_HARDWARE_ENDIAN_LITTLE
    LimitType = &CC_REFLECT_FLOAT(float, CCReflectEndianBig);
#elif CC_HARDWARE_ENDIAN_BIG
    LimitType = &CC_REFLECT_FLOAT(float, CCReflectEndianLittle);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(LimitType, (&(float){ 0.5f }))
                 Passes: (void*[]){ &(double){ 0.5 }, &(double){ 1.0 }, NULL }
                  Fails: (void*[]){ &(double){ -1.0 }, &(double){ 0.0 }, NULL }
                 OfType: &CC_REFLECT_FLOAT(double, CCReflectEndianNative)];
    
    [self assertMaximum: CC_REFLECT_VALUE(LimitType, (&(float){ 0.5f }))
                 Passes: (void*[]){ &(double){ 0.5 }, &(double){ -1.0 }, &(double){ 0.0 }, NULL }
                  Fails: (void*[]){ &(double){ 1.0 }, NULL }
                 OfType: &CC_REFLECT_FLOAT(double, CCReflectEndianNative)];
}

static int DestroyedValue = 0;
static void CustomDestructor(void *Ptr)
{
    DestroyedValue += *(int*)Ptr;
}

void MemoryDestructorCallbackMaps(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator, CCReflectMapIntent Intent)
{
    if CC_REFLECT_MAP_STATELESS_VALUES_WHEN(CC_REFLECT_VALUE_IS_POINTER,
        CustomDestructor
    )
    
    else CCMemoryDestructorCallbackMapDefaults(Type, Data, Args, Handler, Zone, Allocator, Intent);
}

void MemoryDestructorCallbackUnmaps(CCReflectType Type, CCReflectType MappedType, const void *Data, void *Args, CCReflectTypeHandler Handler, CCMemoryZone Zone, CCAllocatorType Allocator)
{
    if CC_REFLECT_UNMAP_STATELESS_VALUES(CC_REFLECT_VALUE_TO_POINTER(CCMemoryDestructorCallback),
        CustomDestructor
    )
    
    CCMemoryDestructorCallbackUnmapDefaults(Type, MappedType, Data, Args, Handler, Zone, Allocator);
}

-(void) testTypes
{
    CCMemoryDestructorCallbackMap = MemoryDestructorCallbackMaps;
    CCMemoryDestructorCallbackUnmap = MemoryDestructorCallbackUnmaps;
    
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 1024);
    
    int Value = 3;
    int *PtrValue = CCMalloc(CC_STD_ALLOCATOR, sizeof(Value), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    *PtrValue = Value;
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT(PTYPE(int, retain, dynamic)), &PtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCFree(PtrValue);
    
    CCReflectDeserializeBinary(&CC_REFLECT(PTYPE(int, retain, dynamic)), &PtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    void *Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(*PtrValue, Value, @"should deserialize the value correctly");
    
    CCFree(PtrValue);
    
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(int), CCReflectOwnershipWeak, .allocator = CC_NULL_ALLOCATOR, .destructor = CustomDestructor), &(int*){ &Value }, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCFree(PtrValue);
    
    CCReflectDeserializeBinary(&CC_REFLECT_DYNAMIC_POINTER(&CC_REFLECT(int), CCReflectOwnershipWeak, .allocator = CC_NULL_ALLOCATOR, .destructor = CustomDestructor), &PtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(*PtrValue, Value, @"should deserialize the value correctly");
    XCTAssertEqual(DestroyedValue, 0, @"should deserialize the destructor correctly");
    
    CCFree(PtrValue);
    
    XCTAssertEqual(DestroyedValue, 3, @"should deserialize the destructor correctly");
    
    
    void *Ptr = NULL;
    
    CCReflectSerializeBinary(&CC_REFLECT(PTYPE(void, weak, dynamic)), &Ptr, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&CC_REFLECT(PTYPE(void, weak, dynamic)), &Ptr, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(Ptr, NULL, @"should deserialize the value correctly");
    
    
    char CString[] = "test";
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT(ARRAY(char, v8)), &CString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    memset(CString, 1, sizeof(CString));
    
    CCReflectDeserializeBinary(&CC_REFLECT(ARRAY(char, v8)), &CString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertTrue(!strcmp(CString, "test"), @"should deserialize the value correctly");
    
    
    char *PtrCString = CString;
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT(PTYPE(ARRAY(char, v8), transfer, dynamic)), &PtrCString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    PtrCString = NULL;
    
    CCReflectDeserializeBinary(&CC_REFLECT(PTYPE(ARRAY(char, v8), transfer, dynamic)), &PtrCString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertTrue(!strcmp(PtrCString, "test"), @"should deserialize the value correctly");
    
    CCFree(PtrCString);
    
    
    CCAllocatorType Allocator = CC_ALIGNED_ALLOCATOR(5);
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT(CCAllocatorType), &Allocator, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    Allocator = CC_NULL_ALLOCATOR;
    
    CCReflectDeserializeBinary(&CC_REFLECT(CCAllocatorType), &Allocator, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(Allocator.allocator, (CC_ALIGNED_ALLOCATOR(5).allocator), @"should deserialize the value correctly");
    XCTAssertEqual(*(size_t*)Allocator.data, 5, @"should deserialize the value correctly");
    
    CCFree(Allocator.data);
    
    
    CCString String = CC_STRING("test");
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    String = 0;
    
    CCReflectDeserializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("test")), @"should deserialise the value correctly");
    
    CCStringDestroy(String);
    
    
    String = CC_STRING("a very long string 1234567890");
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    String = 0;
    
    CCReflectDeserializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("a very long string 1234567890")), @"should deserialise the value correctly");
    
    CCStringDestroy(String);
    
    
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(CCString), 4);
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("hello") });
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("world") });
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT_CCArray(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, 4), &Array, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 0));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 1));
    CCArrayDestroy(Array);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCArray(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, 4), &Array, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCArrayGetCount(Array), 2, @"should deserialise the value correctly");
    XCTAssertTrue((CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(Array, 0), CC_STRING("hello")) && CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(Array, 1), CC_STRING("world"))) || (CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(Array, 1), CC_STRING("hello")) && CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(Array, 0), CC_STRING("world"))), @"should deserialise the value correctly");
    
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 0));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 1));
    CCArrayDestroy(Array);
    
    
    
    Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(CCString), 4);
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("hello") });
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("world") });
    CCArray DestArray;
    CCMemoryZoneSave(Zone);
    CCReflectCopy(&CC_REFLECT_CCArray(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, 4), &DestArray, &Array, Zone, CC_STD_ALLOCATOR, CCReflectAssignmentTransfer, TRUE);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCArrayGetCount(DestArray), 2, @"should deserialise the value correctly");
    XCTAssertTrue(CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 0), CC_STRING("hello")), @"should deserialise the value correctly");
    XCTAssertTrue(CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 1), CC_STRING("world")), @"should deserialise the value correctly");
    
    XCTAssertEqual(DestArray, Array, @"should deserialise the value correctly");
    
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(DestArray, 0));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(DestArray, 1));
    CCArrayDestroy(DestArray);
    
    
    
    Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(CCString), 4);
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("hello") });
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("world") });
    DestArray = NULL;
    CCMemoryZoneSave(Zone);
    CCReflectCopy(&CC_REFLECT_CCArray(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, 4), &DestArray, &Array, Zone, CC_STD_ALLOCATOR, CCReflectAssignmentShare, TRUE);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCArrayGetCount(DestArray), 2, @"should deserialise the value correctly");
    XCTAssertTrue(CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 0), CC_STRING("hello")), @"should deserialise the value correctly");
    XCTAssertTrue(CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 1), CC_STRING("world")), @"should deserialise the value correctly");
    
    XCTAssertEqual(DestArray, Array, @"should deserialise the value correctly");
    
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 0));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 1));
    CCArrayDestroy(DestArray);
    CCArrayDestroy(Array);
    
    
    
    Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(CCString), 4);
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("hello") });
    CCArrayAppendElement(Array, &(CCString){ CC_STRING("world") });
    DestArray = NULL;
    CCMemoryZoneSave(Zone);
    CCReflectCopy(&CC_REFLECT_CCArray(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, 4), &DestArray, &Array, Zone, CC_STD_ALLOCATOR, CCReflectAssignmentCopy, TRUE);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCArrayGetCount(DestArray), 2, @"should deserialise the value correctly");
    XCTAssertTrue(CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 0), CC_STRING("hello")), @"should deserialise the value correctly");
    XCTAssertTrue(CCStringEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 1), CC_STRING("world")), @"should deserialise the value correctly");
    
    XCTAssertNotEqual(DestArray, Array, @"should deserialise the value correctly");
    XCTAssertNotEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 0), *(CCString*)CCArrayGetElementAtIndex(Array, 0), @"should deserialise the value correctly");
    XCTAssertNotEqual(*(CCString*)CCArrayGetElementAtIndex(DestArray, 1), *(CCString*)CCArrayGetElementAtIndex(Array, 1), @"should deserialise the value correctly");
    
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 0));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(Array, 1));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(DestArray, 0));
    CCStringDestroy(*(CCString*)CCArrayGetElementAtIndex(DestArray, 1));
    CCArrayDestroy(DestArray);
    CCArrayDestroy(Array);
    
    
    
    CCCollection Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(CCString), CCStringDestructorForCollection);
    
    CCCollectionInsertElement(Collection, &(CCString){ CC_STRING("hello world") });
    CCCollectionInsertElement(Collection, &(CCString){ CC_STRING("foo") });
    CCCollectionInsertElement(Collection, &(CCString){ CC_STRING("one two three four five six") });
    
    CCCollection DestCollection = NULL;
    CCMemoryZoneSave(Zone);
    CCReflectCopy(&CC_REFLECT_CCCollection(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCStringDestructorForCollection), &DestCollection, &Collection, Zone, CC_STD_ALLOCATOR, CCReflectAssignmentCopy, TRUE);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 3, @"should deserialise the value correctly");
    
    
    
    uint8_t Matches = 0;
    CC_COLLECTION_FOREACH(CCString, String, DestCollection)
    {
        if (CCStringEqual(String, CC_STRING("hello world"))) Matches = (Matches & 0xfc) | (((Matches & 3) + 1) & 3);
        if (CCStringEqual(String, CC_STRING("foo"))) Matches = (Matches & 0xf3) | (((((Matches >> 2) & 3) + 1) & 3) << 2);
        if (CCStringEqual(String, CC_STRING("one two three four five six"))) Matches = (Matches & 0xcf) | (((((Matches >> 4) & 3) + 1) & 3) << 4);
    }
    
    XCTAssertEqual(Matches, 0x15, @"should deserialise the values correctly");
    
    CCCollectionDestroy(DestCollection);
    CCCollectionDestroy(Collection);
    
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(CCString), CCStringDestructorForCollection);
    
    CCCollectionInsertElement(Collection, &(CCString){ CC_STRING("hello world") });
    CCCollectionInsertElement(Collection, &(CCString){ CC_STRING("foo") });
    CCCollectionInsertElement(Collection, &(CCString){ CC_STRING("one two three four five six") });
    
    CCMemoryZoneSave(Zone);
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCStringDestructorForCollection), &Collection, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCStringDestructorForCollection), &Collection, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(Collection), 3, @"should deserialise the value correctly");
    
    Matches = 0;
    CC_COLLECTION_FOREACH(CCString, String, Collection)
    {
        if (CCStringEqual(String, CC_STRING("hello world"))) Matches = (Matches & 0xfc) | (((Matches & 3) + 1) & 3);
        if (CCStringEqual(String, CC_STRING("foo"))) Matches = (Matches & 0xf3) | (((((Matches >> 2) & 3) + 1) & 3) << 2);
        if (CCStringEqual(String, CC_STRING("one two three four five six"))) Matches = (Matches & 0xcf) | (((((Matches >> 4) & 3) + 1) & 3) << 4);
    }
    
    XCTAssertEqual(Matches, 0x15, @"should deserialise the values correctly");
    
    CCCollectionDestroy(Collection);
    
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(CCCollection), CCCollectionDestructorForCollection);
    
    CCCollection IntPtrCollection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(int*), CCGenericDestructorForCollection);
    
    int *IntPtr = CCMalloc(CC_STD_ALLOCATOR, sizeof(int), NULL, CC_DEFAULT_ERROR_CALLBACK);
    *IntPtr = 1;
    CCCollectionInsertElement(IntPtrCollection, &IntPtr);
    IntPtr = CCMalloc(CC_STD_ALLOCATOR, sizeof(int), NULL, CC_DEFAULT_ERROR_CALLBACK);
    *IntPtr = 2;
    CCCollectionInsertElement(IntPtrCollection, &IntPtr);
    
    CCCollectionInsertElement(Collection, &IntPtrCollection);
    
    IntPtrCollection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(int*), CCGenericDestructorForCollection);
    
    IntPtr = CCMalloc(CC_STD_ALLOCATOR, sizeof(int), NULL, CC_DEFAULT_ERROR_CALLBACK);
    *IntPtr = 3;
    CCCollectionInsertElement(IntPtrCollection, &IntPtr);
    IntPtr = CCMalloc(CC_STD_ALLOCATOR, sizeof(int), NULL, CC_DEFAULT_ERROR_CALLBACK);
    *IntPtr = 4;
    CCCollectionInsertElement(IntPtrCollection, &IntPtr);
    
    CCCollectionInsertElement(Collection, &IntPtrCollection);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCCollection(&CC_REFLECT(PTYPE(int, retain, dynamic)), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCGenericDestructorForCollection), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCCollectionDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCCollection(&CC_REFLECT(PTYPE(int, retain, dynamic)), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCGenericDestructorForCollection), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCCollectionDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 2, @"should deserialise the value correctly");
    
    Matches = 0;
    
    CC_COLLECTION_FOREACH(CCCollection, IntCollections, DestCollection)
    {
        XCTAssertEqual(CCCollectionGetCount(IntCollections), 2, @"should deserialise the value correctly");
        
        CC_COLLECTION_FOREACH_PTR(void, IntPtr, IntCollections)
        {
            Matches |= 1 << (**(int**)IntPtr - 1);
        }
    }
    
    XCTAssertEqual(Matches, 0xf, @"should deserialise the value correctly");
    
    CCCollectionDestroy(DestCollection);
    
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(CCCollection), CCCollectionDestructorForCollection);
    
    CCCollection StringCollection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(CCString), CCStringDestructorForCollection);
    
    CCCollectionInsertElement(StringCollection, &(CCString){ CC_STRING("one") });
    CCCollectionInsertElement(StringCollection, &(CCString){ CC_STRING("two") });
    CCCollectionInsertElement(StringCollection, &(CCString){ CC_STRING("three is a very very very long string") });
    
    CCCollectionInsertElement(Collection, &StringCollection);
    
    
    StringCollection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, sizeof(CCString), CCStringDestructorForCollection);
    
    CCCollectionInsertElement(StringCollection, &(CCString){ CC_STRING("four") });
    CCCollectionInsertElement(StringCollection, &(CCString){ CC_STRING("five") });
    CCCollectionInsertElement(StringCollection, &(CCString){ CC_STRING("six is a very very very long string") });
    
    CCCollectionInsertElement(Collection, &StringCollection);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCCollection(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCStringDestructorForCollection), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCCollectionDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCCollection(&CC_REFLECT(CCString), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCStringDestructorForCollection), CC_STD_ALLOCATOR, CCCollectionHintSizeSmall, CCCollectionDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 2, @"should deserialise the value correctly");
    
    Matches = 0;
    
    CC_COLLECTION_FOREACH(CCCollection, StrCollections, DestCollection)
    {
        XCTAssertEqual(CCCollectionGetCount(StrCollections), 3, @"should deserialise the value correctly");
        
        CC_COLLECTION_FOREACH(CCString, String, StrCollections)
        {
            if (CCStringEqual(String, CC_STRING("one"))) Matches = (Matches & 0xfc) | (((Matches & 3) + 1) & 3);
            if (CCStringEqual(String, CC_STRING("two"))) Matches = (Matches & 0xf3) | (((((Matches >> 2) & 3) + 1) & 3) << 2);
            if (CCStringEqual(String, CC_STRING("three is a very very very long string"))) Matches = (Matches & 0xcf) | (((((Matches >> 4) & 3) + 1) & 3) << 4);
            
            if (CCStringEqual(String, CC_STRING("four"))) Matches = (Matches & 0xfc) | (((Matches & 3) + 1) & 3);
            if (CCStringEqual(String, CC_STRING("five"))) Matches = (Matches & 0xf3) | (((((Matches >> 2) & 3) + 1) & 3) << 2);
            if (CCStringEqual(String, CC_STRING("six is a very very very long string"))) Matches = (Matches & 0xcf) | (((((Matches >> 4) & 3) + 1) & 3) << 4);
        }
    }
    
    XCTAssertEqual(Matches, 0x2a, @"should deserialise the values correctly");
    
    CCCollectionDestroy(DestCollection);
    
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, sizeof(int), NULL);
    
    CCOrderedCollectionAppendElement(Collection, &(int){ 1 });
    CCOrderedCollectionAppendElement(Collection, &(int){ 2 });
    CCOrderedCollectionAppendElement(Collection, &(int){ 3 });
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT(int), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, NULL), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT(int), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, NULL), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 3, @"should deserialise the value correctly");
    
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(DestCollection, 0), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(DestCollection, 1), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCOrderedCollectionGetElementAtIndex(DestCollection, 2), 3, @"should deserialise the value correctly");
    
    CCCollectionDestroy(DestCollection);
    
    
    
    CCLinkedList LinkedList = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 });
    LinkedList = CCLinkedListPrepend(LinkedList, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    LinkedList = CCLinkedListPrepend(LinkedList, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCLinkedList(&CC_REFLECT(int), CC_STD_ALLOCATOR), &LinkedList, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCLinkedListDestroy(LinkedList);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCLinkedList(&CC_REFLECT(int), CC_STD_ALLOCATOR), &LinkedList, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(*(int*)CCLinkedListGetNodeData(LinkedList), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCLinkedListGetNodeData(LinkedList->next), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCLinkedListGetNodeData(LinkedList->next->next), 3, @"should deserialise the value correctly");
    XCTAssertEqual(LinkedList->next->next->next, NULL, @"should deserialise the value correctly");
    
    CCLinkedListDestroy(LinkedList);
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, sizeof(CCLinkedList), CCLinkedListDestructorForCollection);
    
    LinkedList = CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 });
    LinkedList = CCLinkedListPrepend(LinkedList, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    LinkedList = CCLinkedListPrepend(LinkedList, CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    
    CCOrderedCollectionAppendElement(Collection, &LinkedList);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCLinkedList(&CC_REFLECT(int), CC_STD_ALLOCATOR), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCLinkedListDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCLinkedList(&CC_REFLECT(int), CC_STD_ALLOCATOR), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCLinkedListDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 1, @"should deserialise the value correctly");
    
    LinkedList = *(CCLinkedList*)CCOrderedCollectionGetElementAtIndex(DestCollection, 0);
    
    XCTAssertEqual(*(int*)CCLinkedListGetNodeData(LinkedList), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCLinkedListGetNodeData(LinkedList->next), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCLinkedListGetNodeData(LinkedList->next->next), 3, @"should deserialise the value correctly");
    XCTAssertEqual(LinkedList->next->next->next, NULL, @"should deserialise the value correctly");
    
    CCCollectionDestroy(DestCollection);
    
    
    
    CCList List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 4, 4);
    CCListAppendElement(List, &(int){ 1 });
    CCListAppendElement(List, &(int){ 2 });
    CCListAppendElement(List, &(int){ 3 });
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCList(&CC_REFLECT(int), CC_STD_ALLOCATOR, 4, 4), &List, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCListDestroy(List);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCList(&CC_REFLECT(int), CC_STD_ALLOCATOR, 4, 4), &List, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCListGetCount(List), 3, @"should deserialise the value correctly");
    
    XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 0), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 1), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 2), 3, @"should deserialise the value correctly");
    
    CCListDestroy(List);
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, sizeof(CCList), CCListDestructorForCollection);
    
    List = CCListCreate(CC_STD_ALLOCATOR, sizeof(int), 4, 4);
    CCListAppendElement(List, &(int){ 1 });
    CCListAppendElement(List, &(int){ 2 });
    CCListAppendElement(List, &(int){ 3 });
    
    CCOrderedCollectionAppendElement(Collection, &List);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCList(&CC_REFLECT(int), CC_STD_ALLOCATOR, 4, 4), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCListDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCList(&CC_REFLECT(int), CC_STD_ALLOCATOR, 4, 4), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCListDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 1, @"should deserialise the value correctly");
    
    List = *(CCList*)CCOrderedCollectionGetElementAtIndex(DestCollection, 0);
    
    XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 0), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 1), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCListGetElementAtIndex(List, 2), 3, @"should deserialise the value correctly");
    
    CCCollectionDestroy(DestCollection);
    
    
    
    CCHashMap Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(CCString), sizeof(int), 4, (CCHashMapKeyHasher)CCStringHasherForDictionary, CCStringComparatorForDictionary, CCHashMapSeparateChainingArray);
    
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("one") }, &(int){ 1 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("two") }, &(int){ 2 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("three is a very very long string") }, &(int){ 3 });
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCHashMap(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, 4, (CCHashMapKeyHasher)CCStringHasherForDictionary, CCStringComparatorForDictionary, CCHashMapSeparateChainingArray), &Map, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCHashMapDestroy(Map);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCHashMap(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, 4, (CCHashMapKeyHasher)CCStringHasherForDictionary, CCStringComparatorForDictionary, CCHashMapSeparateChainingArray), &Map, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("one") }), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("two") }), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("three is a very very long string") }), 3, @"should deserialise the value correctly");
    
    CCEnumerable Enumerable;
    CCHashMapGetKeyEnumerable(Map, &Enumerable);
    
    for (CCString *Key = CCEnumerableGetCurrent(&Enumerable); Key; Key = CCEnumerableNext(&Enumerable))
    {
        CCStringDestroy(*Key);
    }
    
    CCHashMapDestroy(Map);
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, sizeof(CCHashMap), CCHashMapDestructorForCollection);
    
    Map = CCHashMapCreate(CC_STD_ALLOCATOR, sizeof(CCString), sizeof(int), 4, (CCHashMapKeyHasher)CCStringHasherForDictionary, CCStringComparatorForDictionary, CCHashMapSeparateChainingArray);
    
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("one") }, &(int){ 1 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("two") }, &(int){ 2 });
    CCHashMapSetValue(Map, &(CCString){ CC_STRING("three is a very very long string") }, &(int){ 3 });
    
    CCOrderedCollectionAppendElement(Collection, &Map);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCHashMap(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, 4, (CCHashMapKeyHasher)CCStringHasherForDictionary, CCStringComparatorForDictionary, CCHashMapSeparateChainingArray), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCHashMapDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCHashMap(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, 4, (CCHashMapKeyHasher)CCStringHasherForDictionary, CCStringComparatorForDictionary, CCHashMapSeparateChainingArray), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCHashMapDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 1, @"should deserialise the value correctly");
    
    Map = *(CCHashMap*)CCOrderedCollectionGetElementAtIndex(DestCollection, 0);
    
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("one") }), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("two") }), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCHashMapGetValue(Map, &(CCString){ CC_STRING("three is a very very long string") }), 3, @"should deserialise the value correctly");
    
    CCHashMapGetKeyEnumerable(Map, &Enumerable);
    
    for (CCString *Key = CCEnumerableGetCurrent(&Enumerable); Key; Key = CCEnumerableNext(&Enumerable))
    {
        CCStringDestroy(*Key);
    }
    
    CCCollectionDestroy(DestCollection);
    
    
    
    CCDictionaryCallbacks Callbacks = {
        .getHash = CCStringHasherForDictionary,
        .compareKeys = CCStringComparatorForDictionary,
        .keyDestructor = CCStringDestructorForDictionary
    };
    
    CCDictionary Dictionary = CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeSmall, sizeof(CCString), sizeof(int), &Callbacks);
    
    CCDictionarySetValue(Dictionary, &(CCString){ CC_STRING("one") }, &(int){ 1 });
    CCDictionarySetValue(Dictionary, &(CCString){ CC_STRING("two") }, &(int){ 2 });
    CCDictionarySetValue(Dictionary, &(CCString){ CC_STRING("three is a very very long string") }, &(int){ 3 });
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCDictionary(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, CCDictionaryHintSizeSmall, &Callbacks), &Dictionary, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCDictionaryDestroy(Dictionary);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCDictionary(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, CCDictionaryHintSizeSmall, &Callbacks), &Dictionary, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dictionary, &(CCString){ CC_STRING("one") }), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dictionary, &(CCString){ CC_STRING("two") }), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dictionary, &(CCString){ CC_STRING("three is a very very long string") }), 3, @"should deserialise the value correctly");
    
    CCDictionaryDestroy(Dictionary);
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, sizeof(CCDictionary), CCDictionaryDestructorForCollection);
    
    Dictionary = CCDictionaryCreate(CC_STD_ALLOCATOR, CCDictionaryHintSizeSmall, sizeof(CCString), sizeof(int), &Callbacks);
    
    CCDictionarySetValue(Dictionary, &(CCString){ CC_STRING("one") }, &(int){ 1 });
    CCDictionarySetValue(Dictionary, &(CCString){ CC_STRING("two") }, &(int){ 2 });
    CCDictionarySetValue(Dictionary, &(CCString){ CC_STRING("three is a very very long string") }, &(int){ 3 });
    
    CCOrderedCollectionAppendElement(Collection, &Dictionary);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCDictionary(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, CCDictionaryHintSizeSmall, &Callbacks), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCDictionaryDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCDictionary(&CC_REFLECT(CCString), &CC_REFLECT(int), CC_STD_ALLOCATOR, CCDictionaryHintSizeSmall, &Callbacks), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCDictionaryDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 1, @"should deserialise the value correctly");
    
    Dictionary = *(CCDictionary*)CCOrderedCollectionGetElementAtIndex(DestCollection, 0);
    
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dictionary, &(CCString){ CC_STRING("one") }), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dictionary, &(CCString){ CC_STRING("two") }), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCDictionaryGetValue(Dictionary, &(CCString){ CC_STRING("three is a very very long string") }), 3, @"should deserialise the value correctly");
    
    CCCollectionDestroy(DestCollection);
    
    
    
    CCQueue Queue = CCQueueCreate(CC_STD_ALLOCATOR);
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCQueue(&CC_REFLECT(int), CC_STD_ALLOCATOR), &Queue, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCQueueDestroy(Queue);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCQueue(&CC_REFLECT(int), CC_STD_ALLOCATOR), &Queue, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    CCQueueNode *Node = CCQueuePeek(Queue);
    XCTAssertEqual(*(int*)CCQueueGetNodeData(Node), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(Node->prev), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(Node->prev->prev), 3, @"should deserialise the value correctly");
    XCTAssertEqual(Node->prev->prev->prev, NULL, @"should deserialise the value correctly");
    
    CCQueueDestroy(Queue);
    
    
    Collection = CCCollectionCreate(CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, sizeof(CCQueue), CCQueueDestructorForCollection);
    
    Queue = CCQueueCreate(CC_STD_ALLOCATOR);
    
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 1 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 2 }));
    CCQueuePush(Queue, CCQueueCreateNode(CC_STD_ALLOCATOR, sizeof(int), &(int){ 3 }));
    
    CCOrderedCollectionAppendElement(Collection, &Queue);
    
    CCMemoryZoneSave(Zone);
    
    CCReflectSerializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCQueue(&CC_REFLECT(int), CC_STD_ALLOCATOR), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCQueueDestructorForCollection), &Collection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamWriter, Zone);
    
    CCCollectionDestroy(Collection);
    
    CCReflectDeserializeBinary(&CC_REFLECT_CCCollection(&CC_REFLECT_CCQueue(&CC_REFLECT(int), CC_STD_ALLOCATOR), CC_STD_ALLOCATOR, CCCollectionHintOrdered | CCCollectionHintSizeSmall, CCQueueDestructorForCollection), &DestCollection, CCReflectEndianNative, 2, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    CCMemoryZoneRestore(Zone);
    
    Memory = CCMemoryZoneAllocate(Zone, 1024);
    memset(Memory, 0, 1024);
    CCMemoryZoneDeallocate(Zone, 1024);
    
    XCTAssertEqual(CCCollectionGetCount(DestCollection), 1, @"should deserialise the value correctly");
    
    Queue = *(CCQueue*)CCOrderedCollectionGetElementAtIndex(DestCollection, 0);
    
    Node = CCQueuePeek(Queue);
    XCTAssertEqual(*(int*)CCQueueGetNodeData(Node), 1, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(Node->prev), 2, @"should deserialise the value correctly");
    XCTAssertEqual(*(int*)CCQueueGetNodeData(Node->prev->prev), 3, @"should deserialise the value correctly");
    XCTAssertEqual(Node->prev->prev->prev, NULL, @"should deserialise the value correctly");
    
    CCCollectionDestroy(DestCollection);
    
    CCMemoryZoneDestroy(Zone);
}

@end
