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
#import "ReflectedTypes.h"

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

static void TestOpaqueArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);
static void TestOpaqueArrayUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

ReflectOpaqueArray TestOpaqueArray = {
    .opaque = CC_REFLECT_OPAQUE(sizeof(CCArray), TestOpaqueArrayMapper, TestOpaqueArrayUnmapper),
    .elementType = &TestNativeU32
};

static void TestOpaqueArrayMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    const size_t Count = CCArrayGetCount(*(CCArray*)Data);
    CCReflectArray Array = CC_REFLECT_ARRAY(((const ReflectOpaqueArray*)Type)->elementType, Count);
    
    Handler(&Array, CCArrayGetData(*(CCArray*)Data), Args);
}

static void TestOpaqueArrayUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, CCReflectTypeSize(((const CCReflectArray*)Type)->type), 16);
    
    CCArrayAppendElements(Array, Data, ((const CCReflectArray*)Type)->count);
    
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

static void TestStaticPointerMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    uint32_t PortableValue = 0;
    
    if (*(uint32_t**)Data == &ConstantZero) PortableValue = 1;
    else if (*(uint32_t**)Data == &ConstantOne) PortableValue = 2;
    else if (*(uint32_t**)Data == &ConstantTwo) PortableValue = 3;
    
    Handler(&TestNativeU32, &PortableValue, Args);
}

static void TestStaticPointerUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

static const CCReflectStaticPointer TestStaticPointer = CC_REFLECT_STATIC_POINTER(&TestNativeU32, CCReflectOwnershipWeak, TestStaticPointerMapper, TestStaticPointerUnmapper);

static void TestStaticPointerUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
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

static void TestOpaqueFooMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);
static void TestOpaqueFooUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

CCReflectOpaque TestOpaqueFoo = CC_REFLECT_OPAQUE(sizeof(struct Foo), TestOpaqueFooMapper, TestOpaqueFooUnmapper);

static void TestOpaqueFooMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    Handler(&TestFoo, &(struct Foo){ .x = 5, .y = *(const uint32_t*)Data, .next = NULL }, Args);
}

static void TestOpaqueFooUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    Handler(&TestNativeU32, &((const struct Foo*)Data)->y, Args);
}

static void TestOpaqueEnumerableMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);
static void TestOpaqueEnumerableUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler);

CCReflectOpaque TestOpaqueEnumerable = CC_REFLECT_OPAQUE(sizeof(CCArray), TestOpaqueEnumerableMapper, TestOpaqueEnumerableUnmapper);

static void TestOpaqueEnumerableMapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    CCEnumerable Enumerable;
    CCArrayGetEnumerable(*(CCArray*)Data, &Enumerable);
    
    Handler(&CC_REFLECT_ENUMERABLE(&TestNativeU32), &Enumerable, Args);
}

static void TestOpaqueEnumerableUnmapper(CCReflectType Type, const void *Data, void *Args, CCReflectTypeHandler Handler)
{
    switch (*(const CCReflectTypeID*)Type)
    {
        case CCReflectTypeArray:
        {
            CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, CCReflectTypeSize(((const CCReflectArray*)Type)->type), 16);
            
            CCArrayAppendElements(Array, Data, ((const CCReflectArray*)Type)->count);
            
            Handler(&CC_REFLECT(PTYPE(void, retain, dynamic)), &Array, Args);
            
            CCArrayDestroy(Array);
            
            break;
        }
            
        case CCReflectTypeEnumerable:
        {
            CCEnumerable Enumerable = *(const CCEnumerable*)Data;
            
            CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, CCReflectTypeSize(((const CCReflectArray*)Type)->type), 16);
            
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
    CCReflectType Min = Min = &CC_REFLECT_VALIDATE_MINIMUM(type, minimum, CC_REFLECT_RESULT(&TestBool, (&(_Bool){ TRUE })), CC_REFLECT_RESULT(&TestBool, (&(_Bool){ FALSE })));
    
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

-(void) testValidations
{
    CCReflectType MinType = &TestNativeU32;
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianLittle);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianBig);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianBig);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(uint32_t, CCReflectEndianLittle);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0x10000 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, NULL }
                 OfType: &TestNativeU32];
    
    
    
    MinType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianNative);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];

    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianLittle);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianBig);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianBig);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(uint16_t, CCReflectEndianLittle);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0x0100 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0x0001 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0x00ff }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(uint16_t){ 0x01ff }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    
    
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x010000 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x0100 }))
                 Passes: (void*[]){ &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x0001 }))
                 Passes: (void*[]){ &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x00ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x01ff }))
                 Passes: (void*[]){ &(uint32_t){ 0 }, &(uint32_t){ 1 }, &(uint32_t){ 255 }, &(uint32_t){ 0x7f000000 }, &(uint32_t){ 0xff000000 }, &(uint32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &TestNativeU32];
    
    
    
    static const CCReflectInteger NativeI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x01000000 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x010000 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x000000ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0x010000ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &NativeI32];
    
    
    
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff00 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0xff01 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_INTEGER(int16_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x0100 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x0001 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x00ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int16_t){ 0x01ff }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &NativeI32];
    
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    static const CCReflectInteger AliasI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    static const CCReflectInteger AliasI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#endif
    
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f000000 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &AliasI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f000000 }, &(int32_t){ 0xff000001 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff000000 }, NULL }
                 OfType: &AliasI32];
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    static const CCReflectInteger FlippedI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianBig, .sign = TRUE);
#elif CC_HARDWARE_ENDIAN_BIG
    static const CCReflectInteger FlippedI32 = CC_REFLECT_INTEGER(int32_t, CCReflectEndianLittle, .sign = TRUE);
#endif
    
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x0000007f }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, &(int32_t){ 0x000000ff }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &FlippedI32];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0x01000000 }, &(int32_t){ 0xff000000 }, &(int32_t){ 0x0000007f }, &(int32_t){ 0x010000ff }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0x000000ff }, NULL }
                 OfType: &FlippedI32];
    
    
    
    static const CCReflectInteger NativeI16 = CC_REFLECT_INTEGER(int16_t, CCReflectEndianNative, .sign = TRUE);
    
    MinType = &CC_REFLECT_INTEGER(int32_t, CCReflectEndianNative, .sign = TRUE);
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f00 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff00 }, &(int32_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
     [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 1 }))
                 Passes: (void*[]){ &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f00 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 0xff00 }, &(int32_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 256 }))
                 Passes: (void*[]){ &(int32_t){ 0x7f00 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0xff00 }, &(int32_t){ 0xff01 }, NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000000 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f00 }, &(int32_t){ 0xff00 }, &(int32_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xff000001 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f00 }, &(int32_t){ 0xff00 }, &(int32_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ NULL }
                 OfType: &NativeI16];
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(int32_t){ 0xffffff01 }))
                 Passes: (void*[]){ &(int32_t){ 0 }, &(int32_t){ 1 }, &(int32_t){ 255 }, &(int32_t){ 0x7f00 }, &(int32_t){ 0xff01 }, NULL }
                  Fails: (void*[]){ &(int32_t){ 0xff00 }, NULL }
                 OfType: &NativeI16];
    
    
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_FLOAT(float, CCReflectEndianLittle);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_FLOAT(float, CCReflectEndianBig);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(float){ 0.5f }))
                 Passes: (void*[]){ &(double){ 0.5 }, &(double){ 1.0 }, NULL }
                  Fails: (void*[]){ &(double){ -1.0 }, &(double){ 0.0 }, NULL }
                 OfType: &CC_REFLECT_FLOAT(double, CCReflectEndianNative)];
    
#if CC_HARDWARE_ENDIAN_LITTLE
    MinType = &CC_REFLECT_FLOAT(float, CCReflectEndianBig);
#elif CC_HARDWARE_ENDIAN_BIG
    MinType = &CC_REFLECT_FLOAT(float, CCReflectEndianLittle);
#endif
    
    [self assertMinimum: CC_REFLECT_VALUE(MinType, (&(float){ 0.5f }))
                 Passes: (void*[]){ &(double){ 0.5 }, &(double){ 1.0 }, NULL }
                  Fails: (void*[]){ &(double){ -1.0 }, &(double){ 0.0 }, NULL }
                 OfType: &CC_REFLECT_FLOAT(double, CCReflectEndianNative)];
}

-(void) testTypes
{
    CCMemoryZone Zone = CCMemoryZoneCreate(CC_STD_ALLOCATOR, 1024);
    
    int Value = 3;
    int *PtrValue = CCMalloc(CC_STD_ALLOCATOR, sizeof(Value), NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    *PtrValue = Value;
    
    CCReflectSerializeBinary(&CC_REFLECT(PTYPE(int, retain, dynamic)), &PtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCFree(PtrValue);
    
    CCReflectDeserializeBinary(&CC_REFLECT(PTYPE(int, retain, dynamic)), &PtrValue, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(*PtrValue, Value, @"should deserialize the value correctly");
    
    CCFree(PtrValue);
    
    
    void *Ptr = NULL;
    
    CCReflectSerializeBinary(&CC_REFLECT(PTYPE(void, weak, dynamic)), &Ptr, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    CCReflectDeserializeBinary(&CC_REFLECT(PTYPE(void, weak, dynamic)), &Ptr, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(Ptr, NULL, @"should deserialize the value correctly");
    
    
    char CString[] = "test";
    
    CCReflectSerializeBinary(&CC_REFLECT(ARRAY(char, v8)), &CString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    memset(CString, 1, sizeof(CString));
    
    CCReflectDeserializeBinary(&CC_REFLECT(ARRAY(char, v8)), &CString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertTrue(!strcmp(CString, "test"), @"should deserialize the value correctly");
    
    
    char *PtrCString = CString;
    
    CCReflectSerializeBinary(&CC_REFLECT(PTYPE(ARRAY(char, v8), transfer, dynamic)), &PtrCString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    PtrCString = NULL;
    
    CCReflectDeserializeBinary(&CC_REFLECT(PTYPE(ARRAY(char, v8), transfer, dynamic)), &PtrCString, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertTrue(!strcmp(PtrCString, "test"), @"should deserialize the value correctly");
    
    CCFree(PtrCString);
    
    
    CCAllocatorType Allocator = CC_ALIGNED_ALLOCATOR(5);
    
    CCReflectSerializeBinary(&CC_REFLECT(CCAllocatorType), &Allocator, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    Allocator = CC_NULL_ALLOCATOR;
    
    CCReflectDeserializeBinary(&CC_REFLECT(CCAllocatorType), &Allocator, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertEqual(Allocator.allocator, (CC_ALIGNED_ALLOCATOR(5).allocator), @"should deserialize the value correctly");
    XCTAssertEqual(*(size_t*)Allocator.data, 5, @"should deserialize the value correctly");
    
    
    CCString String = CC_STRING("test");
    
    CCReflectSerializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    String = 0;
    
    CCReflectDeserializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("test")), @"should deserialise the value correctly");
    
    CCStringDestroy(String);
    
    
    String = CC_STRING("a very long string 1234567890");
    
    CCReflectSerializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamWriter, Zone);
    
    String = 0;
    
    CCReflectDeserializeBinary(&CC_REFLECT(CCString), &String, CCReflectEndianNative, SIZE_MAX, &(size_t){ 0 }, StreamReader, Zone, CC_STD_ALLOCATOR);
    
    XCTAssertTrue(CCStringEqual(String, CC_STRING("a very long string 1234567890")), @"should deserialise the value correctly");
    
    CCStringDestroy(String);
    
    
    CCMemoryZoneDestroy(Zone);
}

@end
