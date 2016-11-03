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

/*!
 * @header CCCollectionFastArray
 * CCCollectionFastArray is an interface for an array backed ordered collection implementation. This interface can
 * only be used for ordered collections. Use cases that rely on persistent @b CCCollectionEntry references will not
 * work. The purpose of this collection is to provide a fast ordered collection implementation. Due to this, the
 * implementation will never be used by the implicit @b CCCollectionCreate function. Instead usage is explicit and
 * therefore must use the @b CCCollectionCreateWithImplementation function.
 *
 * @b CCCollectionEntry are valid only temporarily. If any mutation happens, there is not guarantee they will be valid.
 * As an entry reference is just the current index of the element.
 *
 * For ordered collections, with appending/replacing and collection destruction operations, this type is the fastest.
 *
 * Fast Ordered Operations:
 * - Enumerating
 * - Replacing entries.
 * - Removing the item at the end of the collection.
 * - Removing all items in the collection.
 * - Index lookup.
 * - Destruction of the collection.
 *
 * Slow Ordered Operations:
 * - Prepending items or inserting inside the collection.
 * - Removing items at the beginning of the list or inside the list.
 * - Finding items in the collection.
 */
#ifndef CommonC_CollectionFastArray_h
#define CommonC_CollectionFastArray_h

#include <CommonC/CollectionInterface.h>

extern const CCCollectionInterface * const CCCollectionFastArray;

#endif
