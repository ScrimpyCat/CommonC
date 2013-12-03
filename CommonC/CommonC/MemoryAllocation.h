/*
 *  Copyright (c) 2013, Stefan Johnson
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

#ifndef CommonC_MemoryAllocation_h
#define CommonC_MemoryAllocation_h

#include <CommonC/DebugTypes.h>
#include <CommonC/Allocator.h>
#include <CommonC/Generics.h>
#include <CommonC/Extensions.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
    CCFunctionIndicator indicator;
    const char *info;
    const char *filename, *functionName;
    int line;
    CCAllocatorType type;
    size_t size;
} CCFunctionDataMalloc;

typedef struct {
    CCFunctionIndicator indicator;
    const char *info;
    const char *filename, *functionName;
    int line;
    CCAllocatorType type;
    void *ptr;
    size_t size;
} CCFunctionDataRealloc;



void *CCMalloc(CCAllocatorType Type, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallback ErrorCallback) CC_WARN_UNUSED_RESULT;
void *CCRealloc(CCAllocatorType Type, void *Ptr, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallback ErrorCallback) CC_WARN_UNUSED_RESULT;
void CCFree(void *Ptr);

#if __BLOCKS__
void *CCMallocBlock(CCAllocatorType Type, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallbackBlock ErrorCallback) CC_WARN_UNUSED_RESULT;
void *CCReallocBlock(CCAllocatorType Type, void *Ptr, size_t Size, const char * const Filename, const char * const FunctionName, int Line, void *CallbackData, CCErrorCallbackBlock ErrorCallback) CC_WARN_UNUSED_RESULT;
#endif

#define CCMalloc(type, size, data, callback) CC_GENERIC_EVALUATE(callback, \
CCErrorCallback: CCMalloc, \
CC_SUPPORT_BLOCKS(CCErrorCallbackBlock: CCMallocBlock,) \
void *: CCMalloc)(type, size, __FILE__, __func__, __LINE__, data, callback)

#define CCRealloc(type, ptr, size, data, callback) CC_GENERIC_EVALUATE(callback, \
CCErrorCallback: CCRealloc, \
CC_SUPPORT_BLOCKS(CCErrorCallbackBlock: CCReallocBlock,) \
void *: CCRealloc)(type, ptr, size, __FILE__, __func__, __LINE__, data, callback)

/*
 CCMalloc:
 Allocates memory of size, otherwise calls the callback passed to it (passing the data to the callback) on failure. The callback may return the allocated memory, 
 otherwise return NULL.
 
 CCFree:
 Frees the allocated memory if not NULL, otherwise does nothing.
 */


/*
 CC_SAFE_Malloc:
 A straightforward malloc, offering a template to add behaviour for how it should handle on failure. The behaviour is handled from your function, so after it
 returns from CCMalloc. This is important to note, so the callback passed in to CCMalloc will be executed first before this behaviour.
 
 Free using CC_SAFE_Free().
 
 e.g.
 int Func(void)
 {
    void MyPtr;
    CC_SAFE_Malloc(MyPtr, 1024);
    
    //return from the function
    CC_SAFE_Malloc(MyPtr, 1024, return -1;)
    
    //or try a second time (this behaviour besides the return, may be better handled in the callback passed to CCMalloc)
    CC_SAFE_Malloc(MyPtr, 1024,
        printf("Failed to allocate, attempting to free resources\n");
        MyFreeResources();
        CC_SAFE_Malloc(MyPtr, 1024,
            printf("Failed to allocate after freeing resources\n");
            return -1;
        );
        //Success
    );
    
    //or save and exit (this behaviour may be better handled in the callback passed to CCMalloc)
    CC_SAFE_Malloc(MyPtr, 1024,
        MySaveData();
        exit(-1);
    );
    
    //...
    CC_SAFE_Free(MyPtr);
    return 0;
 }
 */

//CC_SAFE_Malloc(x, size, error)
#define CC_SAFE_Malloc(x, size, ...) \
x = CCMalloc(CC_DEFAULT_ALLOCATOR, size, NULL, CC_DEFAULT_ERROR_CALLBACK); \
if (!x) \
{ \
__VA_ARGS__ \
}
/*
 or
 #define CC_SAFE_Malloc(x, size, ...) x = CCMalloc(size, NULL, CC_DEFAULT_ERROR_CALLBACK); if (!x)
 
 ?
 */

#define CC_SAFE_Realloc(x, size, ...) \
{ \
void *CC_PRIV_temp___ = CCRealloc(CC_DEFAULT_ALLOCATOR, x, size, NULL, CC_DEFAULT_ERROR_CALLBACK); \
if (!CC_PRIV_temp___) \
{ \
__VA_ARGS__ \
} \
else x = CC_PRIV_temp___; \
}

//CC_SAFE_Free(x)
#define CC_SAFE_Free(x) (CCFree(x), x = NULL)



/*
 CC_TEMP_Malloc:
 A temporary malloc (only safe to use in the current scope). It has two possibilities for how it will allocate the data. The first is on the stack, if the size of
 the allocation is not larger than CC_SHOULD_ALLOC_ON_STACK, or if malloc fails and the size is no larger than CC_ALLOC_ON_STACK_MAX, it will allocate on the stack.
 The second is on the heap through malloc, if the size of the allocation is larger than CC_SHOULD_ALLOC_ON_STACK, it will attempt to use malloc.
 
 Free using CC_TEMP_Free(). Should only be used inside the same scope the CC_TEMP_Malloc was called.
 
 CC_TEMP_Malloc cannot be called multiple times in the same scope for the same variable, as this will cause redefinitions.
 */

#define CC_ALLOC_ON_STACK_MAX 256 //If malloc fails it will opt in for stack allocation, it will not allocate any higher than this on the stack
#define CC_SHOULD_ALLOC_ON_STACK 64 //Will opt out of malloc allocation if the size is equal or less than this, and opts for stack allocation.

//The following only allow for x that is alpha-numeric chars only, no array indexing, accessing members of a structure or union, etc.
//CC_TEMP_Malloc(x, size, error)
#define CC_TEMP_Malloc(x, size, ...) /* Only to be used in the same scope as it is allocated, free using CC_TEMP_Free */ \
const size_t x##__CC_PRIV__SIZE = size; \
const _Bool x##__CC_PRIV__NEEDS_FREEING = (x##__CC_PRIV__SIZE <= CC_SHOULD_ALLOC_ON_STACK? 0 : (x = CCMalloc(CC_DEFAULT_ALLOCATOR, size, NULL, CC_DEFAULT_ERROR_CALLBACK))); \
const _Bool x##__CC_PRIV__ALLOC_ON_STACK = (!x##__CC_PRIV__NEEDS_FREEING) && (x##__CC_PRIV__SIZE <= CC_ALLOC_ON_STACK_MAX); \
uint8_t x##__CC_PRIV__BACKUP[x##__CC_PRIV__SIZE * x##__CC_PRIV__ALLOC_ON_STACK]; x = (x##__CC_PRIV__ALLOC_ON_STACK? (void*)x##__CC_PRIV__BACKUP : x); \
if (!x) \
{ \
__VA_ARGS__ \
}


//CC_TEMP_Free(x)
#define CC_TEMP_Free(x) (!x##__CC_PRIV__NEEDS_FREEING?: CCFree(x), x = NULL)


/*
 CC_MUST_Malloc:
 Another form of temporary allocation. It will only execute the passed function pointer or block if it is successful at allocating the memory. This memory should
 not be used outside the scope of the called function (or functions it calls). If the called function
 */

#endif
