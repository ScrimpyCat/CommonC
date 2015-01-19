//
//  CallbackAllocator.h
//  CommonC
//
//  Created by Stefan Johnson on 20/01/2015.
//  Copyright (c) 2015 Stefan Johnson. All rights reserved.
//

#ifndef CommonC_CallbackAllocator_h
#define CommonC_CallbackAllocator_h

#include <stddef.h>

typedef enum {
    CCCallbackAllocatorEventAllocatePre,
    CCCallbackAllocatorEventAllocatePost,
    CCCallbackAllocatorEventReallocatePre,
    CCCallbackAllocatorEventReallocatePost,
    CCCallbackAllocatorEventDeallocatePre
} CCCallbackAllocatorEvent;

typedef void (*CCCallbackAllocatorFunction)(CCCallbackAllocatorEvent Event, void *Ptr, size_t *Size);

#endif
