/*
 *  Copyright (c) 2015, Stefan Johnson
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
 * @header CCLinkedList
 * CCLinkedList implements a generic doubly linked list. The data a node holds is defined by the user,
 * typically by creating a new structure including the CCLinkedListNode as a the header followed by
 * the data.
 *
 * Nodes and lists are generally interchangeable, meaning most functions can be used with either. The
 * functions also typically adopt the idea of a relative head node. To operate on the true head of the
 * list (unless a function specifies otherwise), the head can be obtained through a call to CCLinkedListGetHead.
 */

#ifndef CommonC_LinkedList_h
#define CommonC_LinkedList_h

#include <stddef.h>
#include <CommonC/Allocator.h>

typedef struct CCLinkedListNode {
    struct CCLinkedListNode *next, *prev;
} CCLinkedListNode, *CCLinkedList;


#pragma mark - Creation / Destruction
/*!
 * @brief Allocate and initialize a new node.
 * @param Allocator The allocator to be used for the allocation.
 * @param Size The size of the data.
 * @param Data The data to initialize the node with. May be NULL.
 * @return A pointer to the created node containing the data (if not NULL), or NULL on failure.
 *         Must be destroyed to free the memory.
 */
CCLinkedListNode *CCLinkedListCreateNode(CCAllocatorType Allocator, size_t Size, const void *Data);

/*!
 * @brief Remove and destroy a node from the list.
 * @param Node The node to be destroyed.
 */
void CCLinkedListDestroyNode(CCLinkedListNode *Node);

/*!
 * @brief Remove and destroy a list.
 * @description Destroys all the nodes in the list from the relative head till the end of the list.
 *              If the list is not the true head, nodes prior to the passed in head (those returned
 *              through CCLinkedListEnumeratePrevious) will not be destroyed.
 *
 * @param List The relative list to be destroyed.
 */
void CCLinkedListDestroy(CCLinkedList List);


#pragma mark - Relative Insertions
/*!
 * @brief Inserts the node into the relative list at a random position.
 * @description If the position the node takes in the list is not important, use this function over
 *              the other combiners.
 *
 * @performance Will be faster or on worst case as slow as CCLinkedListInsertAfter.
 * @param List The relative list to add the node to.
 * @param Node The node to be added to the list.
 * @return The new relative head. Either List or Node.
 */
CCLinkedList CCLinkedListInsert(CCLinkedList List, CCLinkedListNode *Node);

/*!
 * @brief Inserts the node into the position after the first node in the relative list.
 * @performance O(n) where n is either the number of enumerations needed to reach Node's head or on
 *              the worst case Node's full length.
 *              
 *              When Node is a single node: O(1)
 *              When List is at the tail:   O(CCLinkedListGetHead(Node))
 *              Else:                       O(CCLinkedListGetHead(Node) + CCLinkedListGetTail(Node))
 *
 * @param List The relative list to add the node to.
 * @param Node The node to be added to the list.
 * @return The new relative head which is List.
 */
CCLinkedList CCLinkedListInsertAfter(CCLinkedList List, CCLinkedListNode *Node);

/*!
 * @brief Inserts the node into the position before the first node in the relative list.
 * @performance O(n) where n is either the number of enumerations needed to reach Node's head or on
 *              the worst case Node's full length.
 *
 *              When Node is a single node: O(1)
 *              When List is the real head: O(CCLinkedListGetTail(Node))
 *              Else:                       O(CCLinkedListGetHead(Node) + CCLinkedListGetTail(Node))
 *
 * @param List The relative list to add the node to.
 * @param Node The node to be added to the list.
 * @return The new relative head which is Node.
 */
CCLinkedList CCLinkedListInsertBefore(CCLinkedList List, CCLinkedListNode *Node);


#pragma mark - Real Insertions
/*!
 * @brief Adds the node onto the end of the real list.
 * @performance O(n) where n is the number of enumerations needed to reach the end of the list and
 *              the head of the node. If it is possible it is more performant to pass in a List closer
 *              to the end of the entire list.
 *
 *              When Node is a single node: O(CCLinkedListGetTail(List))
 *              When List is at the tail:   O(CCLinkedListGetHead(Node))
 *              Else:                       O(CCLinkedListGetTail(List) + CCLinkedListGetHead(Node))
 *
 * @param List The relative list to add the node to.
 * @param Node The node to be added to the list.
 * @return The new tail which is Node.
 */
CCLinkedList CCLinkedListAppend(CCLinkedList List, CCLinkedListNode *Node);

/*!
 * @brief Adds the node onto the beginning of the real list.
 * @performance O(n) where n is the number of enumerations needed to reach the beginning of the list and
 *              the tail of the node. If it is possible it is more performant to pass in a List closer
 *              to the real head.
 *
 *              When Node is a single node: O(CCLinkedListGetHead(List))
 *              When List is the real head: O(CCLinkedListGetTail(Node))
 *              Else:                       O(CCLinkedListGetHead(List) + CCLinkedListGetTail(Node))
 *
 * @param List The relative list to add the node to.
 * @param Node The node to be added to the list.
 * @return The new head which is Node.
 */
CCLinkedList CCLinkedListPrepend(CCLinkedList List, CCLinkedListNode *Node);


#pragma mark - Removal
/*!
 * @brief Remove the node from the list.
 * @description The node is still available for usage until it is destroyed.
 * @param Node The node to be removed from the list.
 */
void CCLinkedListRemoveNode(CCLinkedListNode *Node);

/*!
 * @brief Remove a list of nodes from a list.
 * @description All the nodes from Start to End. This list will still be available for usage until
 *              it is destroyed.
 *
 * @param Start The beginning node of the list.
 * @param End The ending node of the list.
 */
void CCLinkedListRemove(CCLinkedList Start, CCLinkedList End);


#pragma mark - Enumeration
/*!
 * @brief Enumerate to the next node in the list.
 * @param List The current node in the list to obtain the next from.
 * @return The next node in the list or NULL if there is no more.
 */
static inline CCLinkedListNode *CCLinkedListEnumerateNext(CCLinkedList List);

/*!
 * @brief Enumerate to the previous node in the list.
 * @param List The current node in the list to obtain the previous from.
 * @return The previous node in the list or NULL if there is no more.
 */
static inline CCLinkedListNode *CCLinkedListEnumeratePrevious(CCLinkedList List);


#pragma mark - Query
/*!
 * @brief Check if the list is currently the head.
 * @param List The list to check.
 * @return True if it is the head, otherwise false.
 */
static inline _Bool CCLinkedListIsHead(CCLinkedList List);

/*!
 * @brief Check if the list is currently the tail.
 * @param List The list to check.
 * @return True if it is the tail, otherwise false.
 */
static inline _Bool CCLinkedListIsTail(CCLinkedList List);

/*!
 * @brief Get the head of the list.
 * @performance Slow, should avoid if possible. As it must enumerate through the current node in the
 *              list until it reaches the head. Worst case it is the entire length of the list.
 *
 * @param List The list to get the head of.
 * @return The head node of the list.
 */
static inline CCLinkedList CCLinkedListGetHead(CCLinkedList List);

/*!
 * @brief Get the tail of the list.
 * @performance Slow, should avoid if possible. As it must enumerate through the current node in the
 *              list until it reaches the tail. Worst case it is the entire length of the list.
 *
 * @param List The list to get the tail of.
 * @return The tail node of the list.
 */
static inline CCLinkedList CCLinkedListGetTail(CCLinkedList List);


#pragma mark -
static inline CCLinkedListNode *CCLinkedListEnumerateNext(CCLinkedList List)
{
    return List? List->next : NULL;
}

static inline CCLinkedListNode *CCLinkedListEnumeratePrevious(CCLinkedList List)
{
    return List? List->prev : NULL;
}

static inline _Bool CCLinkedListIsHead(CCLinkedList List)
{
    return List->prev == NULL;
}

static inline _Bool CCLinkedListIsTail(CCLinkedList List)
{
    return List->next == NULL;
}

static inline CCLinkedList CCLinkedListGetHead(CCLinkedList List)
{
    CCLinkedListNode *Head = List;
    while ((List = CCLinkedListEnumeratePrevious(List))) Head = List;
    
    return Head;
}

static inline CCLinkedList CCLinkedListGetTail(CCLinkedList List)
{
    CCLinkedListNode *Tail = List;
    while ((List = CCLinkedListEnumerateNext(List))) Tail = List;
    
    return Tail;
}

#endif
