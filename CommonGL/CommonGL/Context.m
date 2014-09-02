/*
 *  Copyright (c) 2011, 2013, Stefan Johnson
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

#import "Default_Private.h"
#import "Context.h"
#import <CommonC/Types.h>
#import <Foundation/Foundation.h>

#if CC_PLATFORM_IOS
#import <objc/runtime.h>
#import <CommonObjc/Assertion.h>

static uint8_t LockKey;
#endif

CCGLContext CCGLContextGetCurrent(void)
{
#if CC_PLATFORM_OS_X
    return CGLGetCurrentContext();
#elif CC_PLATFORM_IOS
    return [EAGLContext currentContext];
#else
    return NULL;
#endif
}

_Bool CCGLContextSetCurrent(CCGLContext Context)
{
#if CC_PLATFORM_OS_X
    return CGLSetCurrentContext(Context) == kCGLNoError;
#elif CC_PLATFORM_IOS
    return [EAGLContext setCurrentContext: Context];
#else
    return FALSE;
#endif
}

_Bool CCGLContextTryLock(CCGLContext Context)
{
#if CC_PLATFORM_OS_X
    CCGLContextLock(Context);
    return TRUE;
#elif CC_PLATFORM_IOS
    NSRecursiveLock *Lock = objc_getAssociatedObject(Context, &LockKey);
    if (!Lock)
    {
        CCGLContextLock(Context);
        return TRUE;
    }
    
    else [Lock tryLock];
#else
    return FALSE;
#endif
}

void CCGLContextLock(CCGLContext Context)
{
#if CC_PLATFORM_OS_X
    CGLLockContext(Context);
#elif CC_PLATFORM_IOS
    NSRecursiveLock *Lock = objc_getAssociatedObject(Context, &LockKey);
    if (!Lock)
    {
        static volatile OSSpinLock CreateLock = OS_SPINLOCK_INIT;
        OSSpinLockLock(&CreateLock);
        
        if (!(Lock = objc_getAssociatedObject(Context, &LockKey)))
        {
            Lock = [[NSRecursiveLock new] autorelease];
            objc_setAssociatedObject(Context, &LockKey, Lock, OBJC_ASSOCIATION_RETAIN);
        }
        
        OSSpinLockUnlock(&CreateLock);
    }
    
    [Lock lock];
#endif
}

void CCGLContextUnlock(CCGLContext Context)
{
#if CC_PLATFORM_OS_X
    CGLUnlockContext(Context);
#elif CC_PLATFORM_IOS
    NSRecursiveLock *Lock = objc_getAssociatedObject(Context, &LockKey);
    CCAssertLog(Lock, @"Attempting to unlock a non-existent lock in GL context: %@", Context);
    [Lock unlock];
#endif
}

static CC_NO_INLINE NSMapTable *ContextGetAssociatedObjectTable(CCGLContext Context)
{
    NSMapTable *AssociatedObjectTable = nil;
    
#if CC_PLATFORM_OS_X
    _Bool CreatedNewTable = FALSE;
    static NSMapTable *ContextAssociatedTables = nil;
    if (!ContextAssociatedTables)
    {
        static volatile OSSpinLock CreateLock = OS_SPINLOCK_INIT;
        OSSpinLockLock(&CreateLock);
        
        if (!ContextAssociatedTables)
        {
            ContextAssociatedTables = [[NSMapTable alloc] initWithKeyOptions: NSPointerFunctionsOpaqueMemory | NSPointerFunctionsOpaquePersonality valueOptions: NSPointerFunctionsStrongMemory | NSPointerFunctionsObjectPointerPersonality capacity: 1];
            CreatedNewTable = TRUE;
        }
        
        OSSpinLockUnlock(&CreateLock);
    }
    
    if ((CreatedNewTable) || !(AssociatedObjectTable = [ContextAssociatedTables objectForKey: (id)Context]))
    {
        AssociatedObjectTable = [NSMapTable mapTableWithKeyOptions: NSPointerFunctionsOpaqueMemory | NSPointerFunctionsOpaquePersonality valueOptions: NSPointerFunctionsStrongMemory | NSPointerFunctionsObjectPointerPersonality];
        [ContextAssociatedTables setObject: AssociatedObjectTable forKey: (id)Context];
    }
#elif CC_PLATFORM_IOS
    if (!(AssociatedObjectTable = objc_getAssociatedObject(Context, &ContextGetAssociatedObjectTable)))
    {
        AssociatedObjectTable = [NSMapTable mapTableWithKeyOptions: NSPointerFunctionsOpaqueMemory | NSPointerFunctionsOpaquePersonality valueOptions: NSPointerFunctionsStrongMemory | NSPointerFunctionsObjectPointerPersonality];
        objc_setAssociatedObject(Context, &ContextGetAssociatedObjectTable, AssociatedObjectTable, OBJC_ASSOCIATION_RETAIN);
    }
#endif
    
    return AssociatedObjectTable;
}

id CCGLContextGetAssociatedObject(CCGLContext Context, void *Key)
{
    id Object = nil;
    CCGLContextLock(Context);
    Object = [ContextGetAssociatedObjectTable(Context) objectForKey: Key];
    CCGLContextUnlock(Context);
    
    return Object;
}

void CCGLContextSetAssociatedObject(CCGLContext Context, void *Key, id Object)
{
    CCGLContextLock(Context);
    [ContextGetAssociatedObjectTable(Context) setObject: Object forKey: Key];
    CCGLContextUnlock(Context);
}
