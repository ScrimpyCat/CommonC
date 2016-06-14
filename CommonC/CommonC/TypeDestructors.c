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

#include "TypeDestructors.h"
#include "CCString.h"
#include "Data.h"
#include "Path.h"
#include "Array.h"
#include "LinkedList.h"
#include "HashMAp.h"

static void CCStringCollectionElementDestructor(CCCollection Collection, CCString *Element);
static void CCDataCollectionElementDestructor(CCCollection Collection, CCData *Element);
static void CCArrayCollectionElementDestructor(CCCollection Collection, CCArray *Element);
static void CCLinkedListCollectionElementDestructor(CCCollection Collection, CCLinkedList *Element);
static void CCCollectionCollectionElementDestructor(CCCollection Collection, CCCollection *Element);
static void CCHashMapCollectionElementDestructor(CCCollection Collection, CCHashMap *Element);
static void CCPathCollectionElementDestructor(CCCollection Collection, FSPath *Element);

const CCCollectionElementDestructor CCStringDestructorForCollection = (CCCollectionElementDestructor)CCStringCollectionElementDestructor;
const CCCollectionElementDestructor CCDataDestructorForCollection = (CCCollectionElementDestructor)CCDataCollectionElementDestructor;
const CCCollectionElementDestructor CCArrayDestructorForCollection = (CCCollectionElementDestructor)CCArrayCollectionElementDestructor;
const CCCollectionElementDestructor CCLinkedListDestructorForCollection = (CCCollectionElementDestructor)CCLinkedListCollectionElementDestructor;
const CCCollectionElementDestructor CCCollectionDestructorForCollection = (CCCollectionElementDestructor)CCCollectionCollectionElementDestructor;
const CCCollectionElementDestructor CCHashMapDestructorForCollection = (CCCollectionElementDestructor)CCHashMapCollectionElementDestructor;
const CCCollectionElementDestructor FSPathDestructorForCollection = (CCCollectionElementDestructor)CCPathCollectionElementDestructor;


static void CCStringCollectionElementDestructor(CCCollection Collection, CCString *Element)
{
    CCStringDestroy(*Element);
}

static void CCDataCollectionElementDestructor(CCCollection Collection, CCData *Element)
{
    CCDataDestroy(*Element);
}

static void CCArrayCollectionElementDestructor(CCCollection Collection, CCArray *Element)
{
    CCArrayDestroy(*Element);
}

static void CCLinkedListCollectionElementDestructor(CCCollection Collection, CCLinkedList *Element)
{
    CCLinkedListDestroy(*Element);
}

static void CCCollectionCollectionElementDestructor(CCCollection Collection, CCCollection *Element)
{
    CCCollectionDestroy(*Element);
}

static void CCHashMapCollectionElementDestructor(CCCollection Collection, CCHashMap *Element)
{
    CCHashMapDestroy(*Element);
}

static void CCPathCollectionElementDestructor(CCCollection Collection, FSPath *Element)
{
    FSPathDestroy(*Element);
}
