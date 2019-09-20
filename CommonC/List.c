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

#define CC_QUICK_COMPILE
#include "List.h"
#include "MemoryAllocation.h"

static void CCListDestructor(CCList Ptr)
{
    for (CCLinkedListNode *Node = Ptr->list; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        CCArrayDestroy(*(CCArray*)CCLinkedListGetNodeData(Node));
    }
    
    CCLinkedListDestroy(Ptr->list);
}

CCList CCListCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, size_t PageSize)
{
    CCAssertLog(ChunkSize >= 1, "ChunkSize must be at least 1");
    CCAssertLog(PageSize >= 1, "PageSize must be at least 1");
    
    CCList List = CCMalloc(Allocator, sizeof(CCListInfo), NULL, CC_DEFAULT_ERROR_CALLBACK);
    if (List)
    {
        *List = (CCListInfo){
            .count = 0,
            .pageSize = PageSize,
            .list = CCLinkedListCreateNode(Allocator, sizeof(CCArray), &(CCArray){ CCArrayCreate(Allocator, ElementSize, ChunkSize) }),
            .allocator = Allocator
        };
        
        CCMemorySetDestructor(List, (CCMemoryDestructorCallback)CCListDestructor);
    }
    
    
    return List;
}

void CCListDestroy(CCList List)
{
    CCAssertLog(List, "List must not be null");
    
    CCFree(List);
}

size_t CCListAppendElement(CCList List, const void *Element)
{
    CCAssertLog(List, "List must not be null");
    
    CCLinkedListNode *Node = CCLinkedListGetTail(List->list);
    CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Node);
    
    if (CCArrayGetCount(Array) == List->pageSize)
    {
        Array = CCArrayCreate(List->allocator, CCArrayGetElementSize(Array), CCArrayGetChunkSize(Array));
        CCLinkedListAppend(Node, CCLinkedListCreateNode(List->allocator, sizeof(CCArray), &Array));
    }
    
    size_t Index = CCArrayAppendElement(Array, Element);
    if (Index != SIZE_MAX) Index = List->count++;
    
    return Index;
}

void CCListReplaceElementAtIndex(CCList List, size_t Index, const void *Element)
{
    CCAssertLog(List, "List must not be null");
    CCAssertLog(List->count > Index, "Index must not be out of bounds");
    
    const size_t PageIndex = Index / List->pageSize;
    const size_t ElementIndex = Index - (PageIndex * List->pageSize);
    
    CCLinkedListNode *Page = List->list;
    for (size_t Loop = 0; Loop < PageIndex; Loop++)
    {
        Page = CCLinkedListEnumerateNext(Page);
    }
    
    CCArrayReplaceElementAtIndex(*(CCArray*)CCLinkedListGetNodeData(Page), ElementIndex, Element);
}

size_t CCListInsertElementAtIndex(CCList List, size_t Index, const void *Element)
{
    CCAssertLog(List, "List must not be null");
    CCAssertLog(List->count > Index, "Index must not be out of bounds");
    
    const size_t PageIndex = Index / List->pageSize;
    const size_t ElementIndex = Index - (PageIndex * List->pageSize);
    
    CCLinkedListNode *Page = List->list;
    for (size_t Loop = 0; Loop < PageIndex; Loop++)
    {
        Page = CCLinkedListEnumerateNext(Page);
    }
    
    CCLinkedListNode *Node = CCLinkedListGetTail(Page), *Tail;
    CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Node);
    if (CCArrayGetCount(Array) == List->pageSize)
    {
        CCArray NextArray = CCArrayCreate(List->allocator, CCArrayGetElementSize(Array), CCArrayGetChunkSize(Array));
        CCLinkedListAppend(Node, Tail = CCLinkedListCreateNode(List->allocator, sizeof(CCArray), &NextArray));
    }
    
    else
    {
        Tail = Node;
        Node = CCLinkedListEnumeratePrevious(Tail);
    }
    
    for ( ; (Tail != Page); Tail = Node, Node = CCLinkedListEnumeratePrevious(Node))
    {
        CCArray Src = *(CCArray*)CCLinkedListGetNodeData(Node), Dst = *(CCArray*)CCLinkedListGetNodeData(Tail);
        const void *LastElement = CCArrayGetElementAtIndex(Src, List->pageSize - 1);
        
        if (CCArrayGetCount(Dst)) CCArrayInsertElementAtIndex(Dst, 0, LastElement);
        else CCArrayAppendElement(Dst, LastElement);
        
        CCArrayRemoveElementAtIndex(Src, List->pageSize - 1);
    }
    
    Array = *(CCArray*)CCLinkedListGetNodeData(Page);
    
    if (ElementIndex == CCArrayGetCount(Array)) CCArrayAppendElement(Array, Element);
    else if (CCArrayInsertElementAtIndex(Array, ElementIndex, Element) == SIZE_MAX) return SIZE_MAX;
    
    List->count++;
    
    return Index;
}

void CCListRemoveElementAtIndex(CCList List, size_t Index)
{
    CCAssertLog(List, "List must not be null");
    CCAssertLog(List->count > Index, "Index must not be out of bounds");
    
    const size_t PageIndex = Index / List->pageSize;
    const size_t ElementIndex = Index - (PageIndex * List->pageSize);
    
    CCLinkedListNode *Page = List->list;
    for (size_t Loop = 0; Loop < PageIndex; Loop++)
    {
        Page = CCLinkedListEnumerateNext(Page);
    }
    
    CCArrayRemoveElementAtIndex(*(CCArray*)CCLinkedListGetNodeData(Page), ElementIndex);
    
    for (CCLinkedListNode *Node = CCLinkedListEnumerateNext(Page); Node; Node = CCLinkedListEnumerateNext(Node))
    {
        CCArrayAppendElement(*(CCArray*)CCLinkedListGetNodeData(Page), CCArrayGetElementAtIndex(*(CCArray*)CCLinkedListGetNodeData(Node), 0));
        CCArrayRemoveElementAtIndex(*(CCArray*)CCLinkedListGetNodeData(Node), 0);
        
        Page = Node;
    }
    
    List->count--;
}

void CCListRemoveAllElements(CCList List)
{
    CCAssertLog(List, "List must not be null");
    
    CCLinkedList Pages = CCLinkedListEnumerateNext(List->list);
    for (CCLinkedListNode *Node = Pages; Node; Node = CCLinkedListEnumerateNext(Node))
    {
        CCArrayDestroy(*(CCArray*)CCLinkedListGetNodeData(Node));
    }
    
    CCLinkedListDestroy(Pages);
    
    CCArrayRemoveAllElements(*(CCArray*)CCLinkedListGetNodeData(List->list));
    
    List->count = 0;
}