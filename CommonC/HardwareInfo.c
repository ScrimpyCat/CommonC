/*
 *  Copyright (c) 2025, Stefan Johnson
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

#include "HardwareInfo.h"
#include "Platform.h"
#include "CCString.h"
#include "Assertion.h"

#if CC_PLATFORM_APPLE
#include <mach/mach.h>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <sys/types.h>
#include <sys/sysctl.h>

static void CopyStringFromCFObject(char *Dst, CFTypeRef Src, size_t Size)
{
    if (CFGetTypeID(Src) == CFStringGetTypeID())
    {
        CFStringGetCString(Src, Dst, Size, kCFStringEncodingUTF8);
    }
    
    else if (CFGetTypeID(Src) == CFDataGetTypeID())
    {
        strncpy(Dst, (const char*)CFDataGetBytePtr(Src), Size - 1);
    }
}

static void CopySizeFromCFObject(size_t *Dst, CFTypeRef Src)
{
    if (CFGetTypeID(Src) == CFNumberGetTypeID())
    {
#if SIZE_MAX > UINT32_MAX
        uint64_t Value;
        CFNumberGetValue(Src, kCFNumberSInt64Type, &Value);
#else
        uint32_t Value;
        CFNumberGetValue(Src, kCFNumberSInt32Type, &Value);
#endif
        
        *Dst = Value;
    }
    
    else if (CFGetTypeID(Src) == CFDataGetTypeID())
    {
        switch (CFDataGetLength(Src))
        {
            case sizeof(uint64_t):
                *Dst = *(const uint64_t*)CFDataGetBytePtr(Src);
                break;
                
            case sizeof(uint32_t):
                *Dst = *(const uint32_t*)CFDataGetBytePtr(Src);
                break;
                
            case sizeof(uint16_t):
                *Dst = *(const uint16_t*)CFDataGetBytePtr(Src);
                break;
                
            case sizeof(uint8_t):
                *Dst = *(const uint8_t*)CFDataGetBytePtr(Src);
                break;
        }
    }
}

_Bool CCHardwareGetCPUs(CCHardwareCPU *Processors, size_t *Count)
{
    CCAssertLog(Processors, "Processors must not be null");
    CCAssertLog(Count, "Count must not be null");
    
    if (*Count)
    {
        memset(Processors, 0, sizeof(*Processors) * *Count);
        
        host_basic_info_data_t Info;
        kern_return_t Err = host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&Info, &(mach_msg_type_number_t){ HOST_BASIC_INFO_COUNT });
        
        if (Err != KERN_SUCCESS)
        {
            *Count = 0;
            
            return FALSE;
        }
        
        *Count = 1;
        
        Processors[0].cores.physical = Info.physical_cpu;
        Processors[0].cores.logical = Info.logical_cpu;
        Processors[0].memory = Info.max_mem;
        
        sysctlbyname("machdep.cpu.brand_string", Processors[0].model, &(size_t){ sizeof(Processors[0].model) }, NULL, 0);
    }
    
    return TRUE;
}

_Bool CCHardwareGetGPUs(CCHardwareGPU *Processors, size_t *Count)
{
    CCAssertLog(Processors, "Processors must not be null");
    CCAssertLog(Count, "Count must not be null");
    
    const size_t Max = *Count;
    
    if (Max)
    {
        memset(Processors, 0, sizeof(*Processors) * Max);
        
        size_t GPUCount = 0;
        
#if CC_PLATFORM_APPLE_VERSION_MIN_REQUIRED(CC_PLATFORM_MAC_12_0, CC_PLATFORM_IOS_15_0)
        mach_port_t MainPort;
        
        if (CC_AVAILABLE(macOS 12, iOS 15, *)) MainPort = kIOMainPortDefault;
        else MainPort = kIOMasterPortDefault;
#else
        mach_port_t MainPort = kIOMasterPortDefault;
#endif
        
        io_iterator_t Iterator;
        kern_return_t Err = IOServiceGetMatchingServices(MainPort, IOServiceMatching("AppleARMIODevice"), &Iterator);
        
        if ((Err == KERN_SUCCESS) && (Iterator))
        {
            for ( ; ; IOIteratorReset(Iterator))
            {
                for (io_service_t Device; (GPUCount < Max) && (Device = IOIteratorNext(Iterator)); IOObjectRelease(Device))
                {
                    CFTypeRef Value = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("device_type"), kCFAllocatorDefault, kNilOptions);
                    
                    if (Value)
                    {
                        if (CFGetTypeID(Value) == CFDataGetTypeID())
                        {
                            const UInt8 *Name = CFDataGetBytePtr(Value);
                            
                            if (!strcmp((const char*)Name, "sgx"))
                            {
                                io_registry_entry_t Child;
                                IORegistryEntryGetChildEntry(Device, kIOServicePlane, &Child);
                                
                                CFStringRef Model = IORegistryEntrySearchCFProperty(Child, kIOServicePlane, CFSTR("model"), kCFAllocatorDefault, kNilOptions);
                                
                                if (Model)
                                {
                                    CopyStringFromCFObject(Processors[GPUCount].model, Model, sizeof(Processors[0].model));
                                    CFRelease(Model);
                                }
                                
                                
                                CFNumberRef Cores = IORegistryEntrySearchCFProperty(Child, kIOServicePlane, CFSTR("gpu-core-count"), kCFAllocatorDefault, kNilOptions);
                                
                                if (Cores)
                                {
                                    CopySizeFromCFObject(&Processors[GPUCount].cores, Cores);
                                    CFRelease(Cores);
                                }
                                
                                GPUCount++;
                            }
                        }
                        
                        CFRelease(Value);
                    }
                }
                
                if (IOIteratorIsValid(Iterator)) break;
                
                memset(Processors, 0, sizeof(*Processors) * GPUCount);
                
                GPUCount = 0;
            }
        }
        
        
        Err = IOServiceGetMatchingServices(MainPort, IOServiceMatching("IOPCIDevice"), &Iterator);
        
        if ((Err == KERN_SUCCESS) && (Iterator))
        {
            const size_t PrevCount = GPUCount;
            
            for ( ; ; IOIteratorReset(Iterator))
            {
                for (io_service_t Device; (GPUCount < Max) && (Device = IOIteratorNext(Iterator)); IOObjectRelease(Device))
                {
                    CFTypeRef Value = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("IOName"), kCFAllocatorDefault, kNilOptions);
                    
                    if (Value)
                    {
                        if (CFGetTypeID(Value) == CFStringGetTypeID())
                        {
                            if (CFStringCompare(Value, CFSTR("display"), 0) == kCFCompareEqualTo)
                            {
                                CFDataRef Model = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("model"), kCFAllocatorDefault, kNilOptions);
                                
                                if (Model)
                                {
                                    CopyStringFromCFObject(Processors[GPUCount].model, Model, sizeof(Processors[0].model));
                                    CFRelease(Model);
                                    
                                    _Bool MBytes = FALSE;
                                    CFTypeRef VRAM = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("VRAM,totalsize"), kCFAllocatorDefault, kIORegistryIterateRecursively);

                                    if (!VRAM)
                                    {
                                        MBytes = TRUE;
                                        VRAM = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("VRAM,totalMB"), kCFAllocatorDefault, kIORegistryIterateRecursively);
                                    }
                                    
                                    if (VRAM)
                                    {
                                        CopySizeFromCFObject(&Processors[GPUCount].vram, VRAM);
                                        CFRelease(VRAM);
                                        
                                        if (MBytes) Processors[GPUCount].vram *= 1000000;
                                    }
                                    
                                    GPUCount++;
                                }
                            }
                        }
                        
                        CFRelease(Value);
                    }
                }
                
                if (IOIteratorIsValid(Iterator)) break;
                
                memset(Processors + PrevCount, 0, sizeof(*Processors) * (GPUCount - PrevCount));
                
                GPUCount = PrevCount;
            }
        }
        
        *Count = GPUCount;
    }
    
    return TRUE;
}
#else
_Bool CCHardwareGetCPUs(CCHardwareCPU *Processors, size_t *Count)
{
    CCAssertLog(Processors, "Processors must not be null");
    CCAssertLog(Count, "Count must not be null");
    
    *Count = 0;
    
    return FALSE;
}

_Bool CCHardwareGetGPUs(CCHardwareGPU *Processors, size_t *Count)
{
    CCAssertLog(Processors, "Processors must not be null");
    CCAssertLog(Count, "Count must not be null");
    
    *Count = 0;
    
    return FALSE;
}
#endif
