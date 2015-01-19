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

#include "LinkedList.h"


typedef struct {
    CCLinkedListNode node;
    uint8_t data[];
} CCLinkedListNodeData;

CCLinkedListNode *CCLinkedListCreateNode(CCAllocatorType Allocator, size_t Size, void *Data)
{
    CCLinkedListNode *List = CCMalloc(Allocator, sizeof(CCLinkedListNode) + Size, NULL, CC_DEFAULT_ERROR_CALLBACK);
    
    if (List)
    {
        List->next = NULL;
        List->prev = NULL;
        if (Data) memcpy(((CCLinkedListNodeData*)List)->data, Data, Size);
    }
    
    return List;
}

void CCLinkedListDestroyNode(CCLinkedListNode *Node)
{
    CCAssertLog(Node, "Node must not be null");
    
    CCLinkedListRemoveNode(Node);
    CCFree(Node);
}

void CCLinkedListDestroy(CCLinkedList List)
{
    CCAssertLog(List, "List must not be null");
    
    CCLinkedListNode *N;
    while ((N = List))
    {
        List = CCLinkedListEnumerateNext(List);
        CCLinkedListDestroyNode(N);
    }
}

CCLinkedList CCLinkedListInsert(CCLinkedList List, CCLinkedListNode *Node)
{
    CCAssertLog(List && Node, "List and node must not be null");
    
    CCLinkedList Head = NULL;
    if ((!List->prev) && (!Node->next))
    {
        List->prev = Node;
        Node->next = List;
        Head = Node;
    }
    
    else if ((!List->next) && (!Node->prev))
    {
        List->next = Node;
        Node->prev = List;
        Head = List;
    }
    
    else if (!List->prev) Head = CCLinkedListInsertBefore(List, Node);
    else if (!List->next) Head = CCLinkedListInsertAfter(List, Node);
    else Head = CCLinkedListInsertAfter(List, Node);
    
    return Head;
}

CCLinkedList CCLinkedListInsertAfter(CCLinkedList List, CCLinkedListNode *Node)
{
    CCAssertLog(List && Node, "List and node must not be null");
    
    if (!List->next)
    {
        CCLinkedListNode *Head = CCLinkedListGetHead(Node);
        List->next = Head;
        Head->prev = List;
    }
    
    else
    {
        CCLinkedListNode *Head = CCLinkedListGetHead(Node), *Tail = CCLinkedListGetTail(Node);
        CCLinkedListNode *Next = List->next;
        
        List->next = Head;
        Next->prev = Tail;
        
        Head->prev = List;
        Tail->next = Next;
    }
    
    return List;
}

CCLinkedList CCLinkedListInsertBefore(CCLinkedList List, CCLinkedListNode *Node)
{
    CCAssertLog(List && Node, "List and node must not be null");
    
    if (!List->prev)
    {
        CCLinkedListNode *Tail = CCLinkedListGetTail(Node);
        List->prev = Tail;
        Tail->next = Node;
    }
    
    else
    {
        CCLinkedListNode *Head = CCLinkedListGetHead(Node), *Tail = CCLinkedListGetTail(Node);
        CCLinkedListNode *Prev = List->prev;
        
        List->prev = Tail;
        Prev->next = Head;
        
        Head->prev = Prev;
        Tail->next = List;
    }
    
    return Node;
}

CCLinkedList CCLinkedListAppend(CCLinkedList List, CCLinkedListNode *Node)
{
    CCAssertLog(List && Node, "List and node must not be null");
    
    CCLinkedListNode *Last = CCLinkedListGetTail(List);
    
    if (!Node->prev)
    {
        Last->next = Node;
        Node->prev = Last;
    }
    
    else CCLinkedListPrepend(Node, Last);
    
    return Node;
}

CCLinkedList CCLinkedListPrepend(CCLinkedList List, CCLinkedListNode *Node)
{
    CCAssertLog(List && Node, "List and node must not be null");
    
    CCLinkedListNode *Head = CCLinkedListGetHead(List);
    
    if (!Node->next)
    {
        Head->prev = Node;
        Node->next = Head;
    }
    
    else CCLinkedListAppend(Node, Head);
    
    return Node;
}

void CCLinkedListRemoveNode(CCLinkedListNode *Node)
{
    CCAssertLog(Node, "Node must not be null");
    
    if (Node->prev) Node->prev->next = Node->next;
    if (Node->next) Node->next->prev = Node->prev;
    
    Node->prev = NULL;
    Node->next = NULL;
}

void CCLinkedListRemove(CCLinkedList Start, CCLinkedList End)
{
    CCAssertLog(Start && End, "Nodes must not be null");
    
    if (Start->prev) Start->prev->next = End->next;
    if (End->next) End->next->prev = Start->prev;
    
    Start->prev = NULL;
    End->next = NULL;
}
