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

#ifndef CommonC_PathComponent_h
#define CommonC_PathComponent_h

#include <stdint.h>
#include <CommonC/Ownership.h>

typedef enum {
    FSPathComponentTypeInvalid,
    FSPathComponentTypeVolume,
    FSPathComponentTypeRoot,
    FSPathComponentTypeRelativeRoot,
    FSPathComponentTypeDirectory,
    FSPathComponentTypeRelativeParentDirectory,
    FSPathComponentTypeFile,
    FSPathComponentTypeExtension,
    FSPathComponentTypeMask = 7
} FSPathComponentType;

typedef uintptr_t FSPathComponent;


/*!
 * @brief Create a path component.
 * @param Type The type of the component.
 * @param String The name of the component. Only used for components of type: FSPathComponentTypeDirectory,
 *        FSPathComponentTypeFile, FSPathComponentTypeExtension. But may be used for other component types.
 *
 * @return The component, or FSPathComponentTypeInvalid on failure. Must be destroyed to free the memory.
 */
CC_NEW FSPathComponent FSPathComponentCreate(FSPathComponentType Type, const char *String);

/*!
 * @brief Destroy a path component.
 * @param Component The component to be destroyed.
 */
void FSPathComponentDestroy(FSPathComponent CC_DESTROY(Component));

/*!
 * @brief Copy a path component.
 * @param Component the component to be copied.
 * @return The component, or FSPathComponentTypeInvalid on failure. Must be destroyed to free the memory.
 */
CC_NEW FSPathComponent FSPathComponentCopy(FSPathComponent Component);

/*!
 * @brief Get the name of a path component.
 * @param Component The path component.
 * @return The string, or NULL if it does not have one.
 */
static inline const char *FSPathComponentGetString(FSPathComponent Component);

/*!
 * @brief Get the type of a path component.
 * @param Component The path component.
 * @return The type.
 */
static inline FSPathComponentType FSPathComponentGetType(FSPathComponent Component);


static inline const char *FSPathComponentGetString(FSPathComponent Component)
{
    return (char*)(Component & ~FSPathComponentTypeMask);
}

static inline FSPathComponentType FSPathComponentGetType(FSPathComponent Component)
{
    return Component & FSPathComponentTypeMask;
}

#endif
