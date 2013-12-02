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

#include "SystemInfo.h"
#include "Platform.h"
#include "Logging.h"

#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#include <CoreFoundation/CoreFoundation.h>
#if CC_PLATFORM_IOS
#include <objc/objc-runtime.h>
#endif
#endif

void CCSystemVersion(uint32_t *Major, uint32_t *Minor, uint32_t *BugFix)
{
    static uint32_t VersionValues[3] = { UINT32_MAX, 0, 0 };
    if (VersionValues[0] == UINT32_MAX)
    {
#if CC_PLATFORM_OS_X || CC_PLATFORM_IOS
#if CC_PLATFORM_OS_X
        CFURLRef URL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, CFSTR("/System/Library/CoreServices/SystemVersion.plist"), kCFURLPOSIXPathStyle, FALSE);
        if (URL)
        {
            CFReadStreamRef Stream = CFReadStreamCreateWithFile(kCFAllocatorDefault, URL);
            if (Stream)
            {
                CFReadStreamOpen(Stream);
                CFDictionaryRef Plist = (CFDictionaryRef)CFPropertyListCreateWithStream(kCFAllocatorDefault, Stream, 0, kCFPropertyListImmutable, NULL, NULL);
                CFReadStreamClose(Stream);
                if (Plist)
                {
                    CFStringRef ProductVersion = (CFStringRef)CFDictionaryGetValue(Plist, CFSTR("ProductVersion"));
#elif CC_PLATFORM_IOS
                    CFStringRef ProductVersion = (CFStringRef)objc_msgSend(objc_msgSend((id)objc_getClass("UIDevice"), sel_getUid("currentDevice")), sel_getUid("systemVersion"));
#endif
                    if (ProductVersion)
                    {
                        const CFIndex Length = CFStringGetLength(ProductVersion);
                        UniChar Chars[Length];
                        const UniChar *Characters = CFStringGetCharactersPtr(ProductVersion);
                        if (!Characters)
                        {
                            Characters = Chars;
                            CFStringGetCharacters(ProductVersion, CFRangeMake(0, Length), Chars);
                        }
                        
                        
                        uint32_t Values[3] = { 0, 0, 0 };
                        for (CFIndex Loop = 0, Index = 0; Loop < Length; Loop++)
                        {
                            const UniChar c = Characters[Loop];
                            if (c == '.') Index++;
                            else Values[Index] = (Values[Index] * 10) + (c - '0');
                        }
                        
                        VersionValues[2] = Values[2];
                        VersionValues[1] = Values[1];
                        VersionValues[0] = Values[0];
                    }
                    
#if CC_PLATFORM_OS_X
                    CFRelease(Plist);
                }
                
                CFRelease(Stream);
            }
            
            CFRelease(URL);
        }
#endif
#else
#endif
    }
    
    if (Major) *Major = VersionValues[0];
    if (Minor) *Minor = VersionValues[1];
    if (BugFix) *BugFix = VersionValues[2];
}

uint32_t CCSystemVersionLiteral(void)
{
    uint32_t Maj, Min, Bug;
    CCSystemVersion(&Maj, &Min, &Bug);
    
#if CC_PLATFORM_OS_X
    return (Maj * 100) + (Min * 10);
#elif CC_PLATFORM_IOS
    return (Maj * 10000) + (Min * 100);
#else
#endif
}
