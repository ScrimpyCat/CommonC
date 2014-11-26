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

#import "GenericContainer.h"
#import <CommonC/MemoryAllocation.h>

@implementation CCGenericContainer
{
    _Bool shouldFreeData;
}
@synthesize data, size, releaser;

+(instancetype) containerOfSize: (size_t)theSize
{
    return [self containerOfSize: theSize ReleaserBlock: NULL];
}

+(instancetype) containerOfSize: (size_t)theSize ReleaserBlock: (CCGenericContainerReleaser)theReleaser
{
    return [self containerWithCopiedData: NULL OfSize: theSize ReleaserBlock: theReleaser];
}

+(instancetype) containerWithCopiedData: (const void*)theData OfSize: (size_t)theSize
{
    return [self containerWithCopiedData: theData OfSize: theSize ReleaserBlock: NULL];
}

+(instancetype) containerWithCopiedData: (const void*)theData OfSize: (size_t)theSize ReleaserBlock: (CCGenericContainerReleaser)theReleaser
{
    return [[[self alloc] initWithCopiedData: theData OfSize: theSize ReleaserBlock: theReleaser] autorelease];
}

+(instancetype) containerWithData: (void*)theData OfSize: (size_t)theSize
{
    return [self containerWithData: theData OfSize: theSize ReleaserBlock: NULL];
}

+(instancetype) containerWithData: (void*)theData OfSize: (size_t)theSize ReleaserBlock: (CCGenericContainerReleaser)theReleaser
{
    return [[[self alloc] initWithData: theData OfSize: theSize ReleaserBlock: theReleaser] autorelease];
}

-(instancetype) initWithCopiedData: (const void*)theData OfSize: (size_t)theSize ReleaserBlock: (CCGenericContainerReleaser)theReleaser
{
    if ((self = [super init]))
    {
        void *Data;
        CC_SAFE_Malloc(Data, theSize,
                       [self release];
                       return nil;
                       );
        
        if (theData) memcpy(Data, theData, theSize);
        
        data = Data;
        size = theSize;
        self.releaser = theReleaser;
        shouldFreeData = YES;
    }
    
    return self;
}

-(instancetype) initWithData: (void*)theData OfSize: (size_t)theSize ReleaserBlock: (CCGenericContainerReleaser)theReleaser
{
    if ((self = [super init]))
    {
        data = theData;
        size = theSize;
        self.releaser = theReleaser;
        shouldFreeData = NO;
    }
    
    return self;
}

-(void) dealloc
{
    void *Data = self.data; data = NULL;
    CCGenericContainerReleaser Releaser = self.releaser;
    if (Releaser) Releaser(Data, self.size, shouldFreeData);
    
    if (shouldFreeData) CC_SAFE_Free(Data);
    self.releaser = nil;
    
    [super dealloc];
}

@end
