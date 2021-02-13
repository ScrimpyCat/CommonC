/*
 *  Copyright (c) 2019, Stefan Johnson
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

#import "DataTests.h"
#import "DataContainer.h"
#import "MemoryAllocation.h"
#import "Array.h"
#import "LinkedList.h"

@interface DataContainerTests : DataTests

@end

@implementation DataContainerTests

-(const CCDataInterface*) interface
{
    return CCDataContainer;
}

-(CCData) createDataOfSize: (size_t)size WithHint: (CCDataHint)hint
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(uint8_t), 4);
    for (size_t Loop = 0; Loop < size; Loop++) CCArrayAppendElement(Array, &(uint8_t){ 0 });
    
    CCData Data = CCDataContainerCreate(CC_STD_ALLOCATOR, hint, sizeof(uint8_t), (CCDataContainerCount)CCArrayGetCount, (CCDataContainerEnumerable)CCArrayGetEnumerable, Array, NULL, NULL);
    CCArrayDestroy(Array);
    
    return Data;
}

-(void) testMisaligned
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(uint32_t), 4);
    for (uint32_t Loop = 1; Loop <= 4; Loop++) CCArrayAppendElement(Array, &(uint32_t){ Loop });
    
    CCData Data = CCDataContainerCreate(CC_STD_ALLOCATOR, CCDataHintReadWrite, sizeof(uint32_t), (CCDataContainerCount)CCArrayGetCount, (CCDataContainerEnumerable)CCArrayGetEnumerable, Array, NULL, NULL);
    
    CCBufferMap Map = CCDataMapBuffer(Data, 1, 9, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 2, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 4, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 3, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 4, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 5, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 5, 5, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 11, 5, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 12, 4, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 1, 9, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xff;
    ((uint8_t*)Map.ptr)[7] = 0xfe;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 0), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 1), 2, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 2), 0xfe, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 3), 4, @"Should have updated the correct value");
    
    Map = CCDataMapBuffer(Data, 5, 9, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xe0;
    ((uint8_t*)Map.ptr)[1] = 0xe1;
    ((uint8_t*)Map.ptr)[2] = 0xe2;
    ((uint8_t*)Map.ptr)[3] = 0xe3;
    ((uint8_t*)Map.ptr)[4] = 0xe4;
    ((uint8_t*)Map.ptr)[5] = 0xe5;
    ((uint8_t*)Map.ptr)[6] = 0xe6;
    ((uint8_t*)Map.ptr)[7] = 0xe7;
    ((uint8_t*)Map.ptr)[8] = 0xe8;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 0), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 1), 0xe2e1e002, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 2), 0xe6e5e4e3, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 3), 0xe8e7, @"Should have updated the correct value");
    
    Map = CCDataMapBuffer(Data, 11, 5, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xd0;
    ((uint8_t*)Map.ptr)[1] = 0xd1;
    ((uint8_t*)Map.ptr)[2] = 0xd2;
    ((uint8_t*)Map.ptr)[3] = 0xd3;
    ((uint8_t*)Map.ptr)[4] = 0xd4;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 0), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 1), 0xe2e1e002, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 2), 0xd0e5e4e3, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 3), 0xd4d3d2d1, @"Should have updated the correct value");
    
    Map = CCDataMapBuffer(Data, 12, 4, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xc0;
    ((uint8_t*)Map.ptr)[2] = 0xc2;
    ((uint8_t*)Map.ptr)[3] = 0xc3;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 0), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 1), 0xe2e1e002, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 2), 0xd0e5e4e3, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, 3), 0xc3c2d2c0, @"Should have updated the correct value");
    
    CCDataDestroy(Data);
    CCArrayDestroy(Array);
    
    
    
    CCLinkedListNode *Node[4] = {
        CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(uint32_t), &(uint32_t){ 1 }),
        CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(uint32_t), &(uint32_t){ 2 }),
        CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(uint32_t), &(uint32_t){ 3 }),
        CCLinkedListCreateNode(CC_STD_ALLOCATOR, sizeof(uint32_t), &(uint32_t){ 4 })
    };
    CCLinkedList List = Node[3];
    List = CCLinkedListPrepend(List, Node[2]);
    List = CCLinkedListPrepend(List, Node[1]);
    List = CCLinkedListPrepend(List, Node[0]);
    
    Data = CCDataContainerCreate(CC_STD_ALLOCATOR, CCDataHintReadWrite, sizeof(uint32_t), NULL, (CCDataContainerEnumerable)CCLinkedListGetEnumerable, List, NULL, NULL);
    
    Map = CCDataMapBuffer(Data, 1, 9, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 2, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 4, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 3, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 4, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 5, 11, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 5, 5, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 11, 5, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 12, 4, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 1, 9, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xff;
    ((uint8_t*)Map.ptr)[7] = 0xfe;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[0]), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[1]), 2, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[2]), 0xfe, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[3]), 4, @"Should have updated the correct value");
    
    Map = CCDataMapBuffer(Data, 5, 9, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xe0;
    ((uint8_t*)Map.ptr)[1] = 0xe1;
    ((uint8_t*)Map.ptr)[2] = 0xe2;
    ((uint8_t*)Map.ptr)[3] = 0xe3;
    ((uint8_t*)Map.ptr)[4] = 0xe4;
    ((uint8_t*)Map.ptr)[5] = 0xe5;
    ((uint8_t*)Map.ptr)[6] = 0xe6;
    ((uint8_t*)Map.ptr)[7] = 0xe7;
    ((uint8_t*)Map.ptr)[8] = 0xe8;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[0]), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[1]), 0xe2e1e002, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[2]), 0xe6e5e4e3, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[3]), 0xe8e7, @"Should have updated the correct value");
    
    Map = CCDataMapBuffer(Data, 11, 5, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xd0;
    ((uint8_t*)Map.ptr)[1] = 0xd1;
    ((uint8_t*)Map.ptr)[2] = 0xd2;
    ((uint8_t*)Map.ptr)[3] = 0xd3;
    ((uint8_t*)Map.ptr)[4] = 0xd4;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[0]), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[1]), 0xe2e1e002, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[2]), 0xd0e5e4e3, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[3]), 0xd4d3d2d1, @"Should have updated the correct value");
    
    Map = CCDataMapBuffer(Data, 12, 4, CCDataHintReadWrite);
    ((uint8_t*)Map.ptr)[0] = 0xc0;
    ((uint8_t*)Map.ptr)[2] = 0xc2;
    ((uint8_t*)Map.ptr)[3] = 0xc3;
    CCDataUnmapBuffer(Data, Map);
    
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[0]), 0xff01, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[1]), 0xe2e1e002, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[2]), 0xd0e5e4e3, @"Should have updated the correct value");
    XCTAssertEqual(*(uint32_t*)CCLinkedListGetNodeData(Node[3]), 0xc3c2d2c0, @"Should have updated the correct value");
    
    CCDataDestroy(Data);
    CCLinkedListDestroy(List);
}

static size_t Count2(const void *Container)
{
    return 2;
}

static size_t Count10(const void *Container)
{
    return 10;
}

-(void) testDifferingSize
{
    CCArray Array = CCArrayCreate(CC_STD_ALLOCATOR, sizeof(uint32_t), 4);
    for (uint32_t Loop = 1; Loop <= 4; Loop++) CCArrayAppendElement(Array, &(uint32_t){ Loop });
    
    CCData Data = CCDataContainerCreate(CC_STD_ALLOCATOR, CCDataHintReadWrite, sizeof(uint32_t), Count2, (CCDataContainerEnumerable)CCArrayGetEnumerable, Array, NULL, NULL);
    
    XCTAssertEqual(CCDataGetSize(Data), 2 * sizeof(uint32_t), @"Should get the correct size");
    
    CCBufferMap Map = CCDataMapBuffer(Data, 2, 5, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 0, CCDataGetSize(Data), CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 1, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    CCDataDestroy(Data);
    Data = CCDataContainerCreate(CC_STD_ALLOCATOR, CCDataHintReadWrite, sizeof(uint32_t), Count10, (CCDataContainerEnumerable)CCArrayGetEnumerable, Array, NULL, NULL);
    
    XCTAssertEqual(CCDataGetSize(Data), 10 * sizeof(uint32_t), @"Should get the correct size");
    
    Map = CCDataMapBuffer(Data, 2, 5, CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 0, CCDataGetSize(Data), CCDataHintRead);
    XCTAssertEqual(((uint8_t*)Map.ptr)[0], 1, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[1], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[2], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[3], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[4], 2, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[5], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[6], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[7], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[8], 3, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[9], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[10], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[11], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[12], 4, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[13], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[14], 0, @"Should retrieve the correct value");
    XCTAssertEqual(((uint8_t*)Map.ptr)[15], 0, @"Should retrieve the correct value");
    CCDataUnmapBuffer(Data, Map);
    
    Map = CCDataMapBuffer(Data, 20, 4, CCDataHintWrite);
    ((uint8_t*)Map.ptr)[0] = 6;
    ((uint8_t*)Map.ptr)[1] = 0;
    ((uint8_t*)Map.ptr)[2] = 0;
    ((uint8_t*)Map.ptr)[3] = 0;
    CCDataUnmapBuffer(Data, Map);
    
    for (size_t Loop = 0, Count = CCArrayGetCount(Array); Loop < Count; Loop++) XCTAssertEqual(*(uint32_t*)CCArrayGetElementAtIndex(Array, Loop), Loop + 1, @"Should remain unchanged");
    
    CCArrayDestroy(Array);
    CCDataDestroy(Data);
}

@end
