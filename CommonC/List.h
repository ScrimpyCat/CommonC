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

/*!
 * @header CCList
 * CCList implements a linked list of arrays.
 *
 * The intended use case is when you desire to have spatial locality of elements,
 * but may need the list to grow indefinitely (and wish to avoid more expensive
 * copies as the list gets bigger). It provides an interface comparable to @b CCArray.
 */

#ifndef CommonC_List_h
#define CommonC_List_h

#include <CommonC/Base.h>
#include <CommonC/Allocator.h>
#include <CommonC/Assertion.h>
#include <CommonC/Array.h>
#include <CommonC/LinkedList.h>

typedef struct CCListInfo {
    size_t count;
    size_t pageSize;
    CCLinkedList(CCArray) list;
    CCLinkedList(CCArray) last;
    CCAllocatorType allocator;
} CCListInfo;

/*!
 * @brief The list.
 * @description Allows @b CCRetain.
 */
typedef struct CCListInfo *CCList;

CC_CONTAINER_DECLARE_PRESET_1(CCList);

/*!
 * @define CC_LIST_DECLARE
 * @abstract Convenient macro to define a @b CCList type that can be referenced by @b CCList.
 * @param element The element type.
 */
#define CC_LIST_DECLARE(element) CC_CONTAINER_DECLARE(CCList, element)

/*!
 * @define CC_LIST
 * @abstract Convenient macro to define an explicitly typed @b CCList.
 * @param element The element type.
 */
#define CC_LIST(element) CC_CONTAINER(CCList, element)

/*!
 * @define CCList
 * @abstract Convenient macro to define an explicitly typed @b CCList.
 * @description In the case that this macro is conflicting with the standalone @b CCList type, simply
 *              undefine it and redefine it back to @b CC_LIST.
 *
 * @param element The element type.
 */
#define CCList(element) CC_LIST(element)


#pragma mark - Creation/Destruction
/*!
 * @brief Create a list.
 * @param Allocator The allocator to be used for the allocation.
 * @param ElementSize The size of the data elements.
 * @param ChunkSize The number of elements to fit with each allocation. Must be at least 1.
 * @param PageSize The maximum size of a single page. Must be at least 1. It will be rounded up
 *        so it is divisible by the @b chunkSize.
 *
 * @return An empty list, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCList CCListCreate(CCAllocatorType Allocator, size_t ElementSize, size_t ChunkSize, size_t PageSize);

/*!
 * @brief Destroy an list.
 * @param List The list to be destroyed.
 */
void CCListDestroy(CCList CC_DESTROY(List));

/*!
 * @define CC_STATIC_LIST
 * @abstract Convenient macro to create a temporary (allocation free) @b CCList.
 * @discussion If used globally the list will last for the life of the program, however if used within
 *             a function it will last for the entirety of the local scope.
 *
 * @param allocator The allocator to be used for future allocations.
 * @param pageSize The maximum size of a single page. Must be at least 1. It will be rounded up
 *        so it is divisible by the @b chunkSize.
 *
 * @param count The number of elements in the data ptr.
 * @param ptr The pointer to the data allocation. Must not be NULL. The allocation is a list of arrays of
 *        pageSize elements, or fewer for the tail array.
 */
#define CC_STATIC_LIST(allocator, pageSize, count, ptr) CC_LIST_CREATE(allocator, pageSize, count, ptr)

/*!
 * @define CC_CONST_ARRAY
 * @abstract Convenient macro to create a temporary constant (allocation free) @b CCList.
 * @discussion If used globally the list will last for the life of the program, however if used within
 *             a function it will last for the entirety of the local scope.
 *
 * @param allocator The allocator to be used for future allocations.
 * @param pageSize The maximum size of a single page. Must be at least 1. It will be rounded up
 *        so it is divisible by the @b chunkSize.
 *
 * @param count The number of elements in the data ptr.
 * @param ptr The pointer to the data allocation. Must not be NULL. The allocation is a list of arrays of
 *        pageSize elements, or fewer for the tail array.
 */
#define CC_CONST_LIST(allocator, pageSize, count, ptr) CC_LIST_CREATE(allocator, pageSize, count, ptr, const)

#define CC_LIST_CREATE(allocator_, pageSize_, elementCount, ptr, ...) \
((CCList)&(__VA_ARGS__ struct { \
    CCAllocatorHeader header; \
    CCListInfo info; \
}){ \
    .header = CC_ALLOCATOR_HEADER_INIT(CC_NULL_ALLOCATOR.allocator), \
    .info = { \
        .count = elementCount, \
        .pageSize = ((pageSize_ % (*(CCArray*)((CCLinkedListNodeData*)ptr)->data)->chunkSize) ? pageSize_ + ((*(CCArray*)((CCLinkedListNodeData*)ptr)->data)->chunkSize - (pageSize_ % (*(CCArray*)((CCLinkedListNodeData*)ptr)->data)->chunkSize)) : pageSize_), \
        .list = ptr, \
        .last = NULL, \
        .allocator = allocator_ \
    } \
}.info)


#pragma mark - Insertions/Deletions
/*!
 * @brief Appends the element to the end of the list.
 * @description Increases the list's count by 1.
 * @warning The size of element must be the same size as specified in the list creation.
 * @param List The list to append the element to.
 * @param Element The pointer to the element to be copied to the end of the list. If NULL it
 *        will create an uninitialized element.
 *
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCListAppendElement(CCList List, const void *Element);

/*!
 * @brief Appends the elements to the end of the list.
 * @description Increases the list's count by the number of elements.
 * @warning The size of the elements must be the same size as specified in the list creation.
 * @param List The list to append the elements to.
 * @param Elements The pointer to the elements to be copied to the end of the list. If NULL it
 *        will create an uninitialized element.
 *
 * @param Count The number of elements to be appended. Must not be 0.
 * @return The index the first element was added or SIZE_MAX on failure.
 */
size_t CCListAppendElements(CCList List, const void *Elements, size_t Count);

/*!
 * @brief Replace element at index with new element.
 * @warning The size of element must be the same size as specified in the list creation. And the
 *          Index must not be out of bounds.
 *
 * @param List The list to replace an element of.
 * @param Index The position of the element to be replaced.
 * @param Element The replacement element. If NULL the operation does nothing.
 */
void CCListReplaceElementAtIndex(CCList List, size_t Index, const void *Element);

/*!
 * @brief Insert an element at a given index into the list.
 * @description Increases the list's count by 1.
 * @performance The further away from the end of the list the index is, the slower it is. It has
 *              a worst case of O(n+p) (where p is the number of pages).
 *
 * @warning The size of element must be the same size as specified in the list creation. And the
 *          Index must not be out of bounds
 *
 * @param List The list to insert the element into.
 * @param Index The position in the list for the element to be inserted.
 * @param Element The pointer to the element to be copied to the give position in the list. If NULL
 *        it will create an uninitialized element.
 *
 * @return The index the element was added or SIZE_MAX on failure.
 */
size_t CCListInsertElementAtIndex(CCList List, size_t Index, const void *Element);

/*!
 * @brief Removes an element at a given index from the list.
 * @description Decreases the list's count by 1.
 * @performance The further away from the end of the list the index is, the slower it is. It has
 *              a worst case of O(n+p) (where p is the number of pages).
 *
 * @warning Index must not be out of bounds
 * @param List The list to remove an element from.
 * @param Index The position in the list for the element to be removed from.
 */
void CCListRemoveElementAtIndex(CCList List, size_t Index);

/*!
 * @brief Removes all elements from the list.
 * @description Sets the list's count to 0.
 * @param List The list to remove all elements from.
 */
void CCListRemoveAllElements(CCList List);


#pragma mark - Query Info
/*!
 * @brief Get the current number of elements in the list.
 * @param List The list to get the count of.
 * @return The number of elements.
 */
static inline size_t CCListGetCount(CCList List);

/*!
 * @brief Get the element size of the list.
 * @param List The list to get the element size of.
 * @return The size of elements.
 */
static inline size_t CCListGetElementSize(CCList List);

/*!
 * @brief Get the element at index.
 * @warning Index must not be out of bounds.
 * @param List The list to get the element of.
 * @param Index The index of the element.
 * @return The pointer to the element.
 */
static inline void *CCListGetElementAtIndex(CCList List, size_t Index);

/*!
 * @brief Get the chunk size of the list.
 * @param List The list to get the chunk size of.
 * @return The chunk size of the list.
 */
static inline size_t CCListGetChunkSize(CCList List);

/*!
 * @brief Get the page size of the list.
 * @param List The list to get the page size of.
 * @return The page size of the list.
 */
static inline size_t CCListGetPageSize(CCList List);

/*!
 * @brief Get an enumerable for the list.
 * @param List The list to obtain an enumerable for.
 * @param Enumerable A pointer to the enumerable to use.
 */
void CCListGetEnumerable(CCList List, CCEnumerable *Enumerable);


#pragma mark -
static inline size_t CCListGetCount(CCList List)
{
    CCAssertLog(List, "List must not be null");
    
    return List->count;
}

static inline size_t CCListGetElementSize(CCList List)
{
    CCAssertLog(List, "List must not be null");
    
    return CCArrayGetElementSize(*(CCArray*)CCLinkedListGetNodeData(List->list));
}

static inline CCLinkedListNode *CCListGetPage(CCList List, size_t PageIndex)
{
    const size_t MaxPageIndex = (List->count - 1) / List->pageSize;
    
    CCLinkedListNode *Page = List->list;
    
    if ((List->last) && (PageIndex > (MaxPageIndex - PageIndex)))
    {
        Page = List->last;
        
        for (size_t Loop = MaxPageIndex; Loop > PageIndex; Loop--)
        {
            Page = CCLinkedListEnumeratePrevious(Page);
        }
    }
    
    else
    {
        for (size_t Loop = 0; Loop < PageIndex; Loop++)
        {
            Page = CCLinkedListEnumerateNext(Page);
        }
    }
    
    return Page;
}

static inline void *CCListGetElementAtIndex(CCList List, size_t Index)
{
    CCAssertLog(List, "List must not be null");
    CCAssertLog(CCListGetCount(List) > Index, "Index must not be out of bounds");
    
    const size_t PageIndex = Index / List->pageSize;
    const size_t ElementIndex = Index - (PageIndex * List->pageSize);
    
    CCLinkedListNode *Page = CCListGetPage(List, PageIndex);
    
    return CCArrayGetElementAtIndex(*(CCArray*)CCLinkedListGetNodeData(Page), ElementIndex);
}

static inline size_t CCListGetChunkSize(CCList List)
{
    CCAssertLog(List, "List must not be null");
    
    return CCArrayGetChunkSize(*(CCArray*)CCLinkedListGetNodeData(List->list));
}

static inline size_t CCListGetPageSize(CCList List)
{
    CCAssertLog(List, "List must not be null");
    
    return List->pageSize;
}

#endif
