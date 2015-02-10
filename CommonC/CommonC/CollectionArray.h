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
 * @header CCCollectionArray
 * CCCollectionArray is an interface for an array backed collection implementation. This interface can
 * also be used for ordered collections.
 *
 * For immutable collections, this type is the fastest. For mutable collections, performance may vary.
 *
 * Fast Operations:
 * - Enumerating.
 * - Replacing entries.
 * - Inserting items to the collection. Note: this assumes no copying of contents when reallocating.
 *
 * Slow Operations:
 * - Finding items in the collection.
 *
 *
 * Fast Ordered Operations:
 * - Removing the item at the end of the list.
 * - Index lookup.
 *
 * Slow Ordered Operations:
 * - Prepending items or inserting inside the collection.
 * - Removing items at the beginning of the list or inside the list.
 */
#ifndef CommonC_CollectionArray_h
#define CommonC_CollectionArray_h

#include <CommonC/CollectionInterface.h>

extern const CCCollectionInterface * const CCCollectionArray;

#endif
