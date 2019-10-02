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
        
        const size_t Diff = PageSize % ChunkSize;
        if (Diff) List->pageSize += ChunkSize - Diff;
        
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

size_t CCListAppendElements(CCList List, const void *Elements, size_t Count)
{
    CCAssertLog(List, "List must not be null");
    
    CCLinkedListNode *Node = CCLinkedListGetTail(List->list);
    
    for (size_t Loop = 0; Loop < Count; )
    {
        CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Node);
        size_t Available = List->pageSize - CCArrayGetCount(Array), CopyCount = Count - Loop;
        
        if (CopyCount > Available)
        {
            Node = CCLinkedListAppend(Node, CCLinkedListCreateNode(List->allocator, sizeof(CCArray), &(CCArray){ CCArrayCreate(List->allocator, CCArrayGetElementSize(Array), CCArrayGetChunkSize(Array)) }));
            
            if (!Available)
            {
                Available = List->pageSize;
                Array = *(CCArray*)CCLinkedListGetNodeData(Node);
            }
            
            CopyCount = Available;
        }
        
        if (CCArrayAppendElements(Array, Elements + (Loop * CCArrayGetElementSize(Array)), CopyCount) == SIZE_MAX)
        {
            if (Loop)
            {
                const size_t PageIndex = List->count / List->pageSize;
                
                CCLinkedListNode *Page = List->list;
                for (size_t Loop = 0; Loop < PageIndex; Loop++)
                {
                    Page = CCLinkedListEnumerateNext(Page);
                }
                
                CCLinkedListNode *Node = CCLinkedListEnumerateNext(Page);
                if (Node) CCLinkedListDestroy(Node);
                
                const size_t ElementIndex = List->count - (PageIndex * List->pageSize);
                CCArrayRemoveElementsAtIndex(*(CCArray*)CCLinkedListGetNodeData(Page), ElementIndex, List->pageSize - ElementIndex);
            }
            
            return SIZE_MAX;
        }
        
        Loop += CopyCount;
    }
    
    const size_t Index = List->count;
    List->count += Count;
    
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
    
    size_t Result;
    if (ElementIndex == CCArrayGetCount(Array)) Result = CCArrayAppendElement(Array, Element);
    else Result = CCArrayInsertElementAtIndex(Array, ElementIndex, Element);
    
    if (Result == SIZE_MAX)
    {
        CCAssertLog(0, "Need to restore state");
        return SIZE_MAX;
    }
    
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
    
    if (Pages) CCLinkedListDestroy(Pages);
    
    CCArrayRemoveAllElements(*(CCArray*)CCLinkedListGetNodeData(List->list));
    
    List->count = 0;
}
static void *CCListEnumerableHandler(CCEnumerator *Enumerator, CCEnumerableAction Action)
{
    switch (Action)
    {
        case CCEnumerableActionHead:
        {
            CCLinkedList Head = ((CCList)(Enumerator->ref))->list;
            Enumerator->state.batch.extra[0] = (uintptr_t)Head;
            
            CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Head);
            
            Enumerator->state.batch.ptr = CCArrayGetData(Array);
            Enumerator->state.batch.count = CCArrayGetCount(Array);
            Enumerator->state.batch.index = 0;
            break;
        }
            
        case CCEnumerableActionTail:
        {
            CCLinkedList Tail = (CCLinkedList)Enumerator->state.batch.extra[1];
            if (!Tail) Tail = CCLinkedListGetTail((CCLinkedList)Enumerator->state.batch.extra[0]);
            
            Enumerator->state.batch.extra[0] = (uintptr_t)Tail;
            
            if (!Enumerator->state.batch.extra[1]) Enumerator->state.batch.extra[1] = (uintptr_t)Tail;
            
            CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Tail);
            
            Enumerator->state.batch.ptr = CCArrayGetData(Array);
            Enumerator->state.batch.count = CCArrayGetCount(Array);
            Enumerator->state.batch.index = Enumerator->state.batch.count - 1;
            
            return Enumerator->state.batch.count ? (Enumerator->state.batch.ptr + (Enumerator->state.batch.index * Enumerator->state.batch.stride)) : NULL;
        }
            
        case CCEnumerableActionNext:
        {
            CCLinkedList Next = CCLinkedListEnumerateNext((CCLinkedList)Enumerator->state.batch.extra[0]);
            if (Next)
            {
                CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Next);
                Enumerator->state.batch.ptr = CCArrayGetData(Array);
                Enumerator->state.batch.count = CCArrayGetCount(Array);
                Enumerator->state.batch.index = 0;
            }
            
            else
            {
                if (!Enumerator->state.batch.extra[1]) Enumerator->state.batch.extra[1] = Enumerator->state.batch.extra[0];
                
                Enumerator->state.batch.ptr = NULL;
                Enumerator->state.batch.count = 0;
                Enumerator->state.batch.index = 0;
            }
            
            Enumerator->state.batch.extra[0] = (uintptr_t)Next;
            break;
        }
            
        case CCEnumerableActionPrevious:
        {
            CCLinkedList Previous = CCLinkedListEnumeratePrevious((CCLinkedList)Enumerator->state.batch.extra[0]);
            if (Previous)
            {
                CCArray Array = *(CCArray*)CCLinkedListGetNodeData(Previous);
                Enumerator->state.batch.ptr = CCArrayGetData(Array);
                Enumerator->state.batch.count = CCArrayGetCount(Array);
                Enumerator->state.batch.index = Enumerator->state.batch.count - 1;
            }
            
            else
            {
                Enumerator->state.batch.ptr = NULL;
                Enumerator->state.batch.count = 0;
                Enumerator->state.batch.index = 0;
            }
            
            Enumerator->state.batch.extra[0] = (uintptr_t)Previous;
            
            return Enumerator->state.batch.count ? (Enumerator->state.batch.ptr + (Enumerator->state.batch.index * Enumerator->state.batch.stride)) : NULL;
        }
            
        default:
            break;
    }
    
    return Enumerator->state.batch.count ? Enumerator->state.batch.ptr : NULL;
}

void CCListGetEnumerable(CCList List, CCEnumerable *Enumerable)
{
    CCAssertLog(List, "List must not be null");
    
    CCArray Array = *(CCArray*)CCLinkedListGetNodeData(List->list);
    
    *Enumerable = (CCEnumerable){
        .handler = CCListEnumerableHandler,
        .enumerator = {
            .ref = List,
            .state = {
                .batch = {
                    .ptr = CCArrayGetData(Array),
                    .count = CCArrayGetCount(Array),
                    .stride = CCArrayGetElementSize(Array),
                    .index = 0,
                    .extra = { (uintptr_t)List->list, 0 }
                },
                .type = CCEnumeratorFormatBatch
            }
        }
    };
}
