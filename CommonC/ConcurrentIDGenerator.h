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

#ifndef CommonC_ConcurrentIDGenerator_h
#define CommonC_ConcurrentIDGenerator_h

#include <CommonC/Ownership.h>
#include <CommonC/Allocator.h>
#include <CommonC/ConcurrentIDGeneratorInterface.h>

/*!
 * @brief The concurrent ID generator.
 * @description Allows @b CCRetain.
 */
typedef struct CCConcurrentIDGeneratorInfo *CCConcurrentIDGenerator;


#pragma mark - Creation / Destruction
/*!
 * @brief Create a concurrent ID generator.
 * @param Allocator The allocator to be used for the allocation.
 * @param Count The number of IDs this generator should manage.
 * @param Interface The implementation to be used.
 * @return An ID generator, or NULL on failure. Must be destroyed to free the memory.
 */
CC_NEW CCConcurrentIDGenerator CCConcurrentIDGeneratorCreate(CCAllocatorType Allocator, size_t Count, const CCConcurrentIDGeneratorInterface *Interface);

/*!
 * @brief Destroy an ID generator.
 * @param Generator The ID generator to be destroyed.
 */
void CCConcurrentIDGeneratorDestroy(CCConcurrentIDGenerator CC_DESTROY(Generator));

#pragma mark - Retrieve/Recycle
/*!
 * @brief Obtain an ID from the ID generator.
 * @performance This function will wait until it has assigned an ID.
 * @param Generator The ID generator to get the ID from.
 * @return The ID that has been assigned. This ID must be recycled in order for it to become available
 *         again.
 */
uintptr_t CCConcurrentIDGeneratorAssign(CCConcurrentIDGenerator Generator);

/*!
 * @brief Try obtain an ID from the ID generator.
 * @description This will return if no ID is available.
 * @param Generator The ID generator to get the ID from.
 * @param ID The pointer to where the assigned ID should be stored. This ID must be recycled in order
 *           for it to become available again. This must not be NULL.
 *
 * @return Whether an ID was assigned (TRUE), or not (FALSE).
 */
_Bool CCConcurrentIDGeneratorTryAssign(CCConcurrentIDGenerator Generator, uintptr_t *ID);

/*!
 * @brief Recycle an ID to the ID generator.
 * @performance Wait-free O(1) operation.
 * @param Generator The ID generator to recycle the ID to.
 * @param ID The ID to be recycled.
 */
void CCConcurrentIDGeneratorRecycle(CCConcurrentIDGenerator Generator, uintptr_t ID);

#pragma mark - Info

/*!
 * @brief Get the max ID this generator may assign.
 * @param Generator The ID generator to get the max ID from.
 * @return The max ID that can be assigned.
 */
uintptr_t CCConcurrentIDGeneratorGetMaxID(CCConcurrentIDGenerator Generator);

#endif
