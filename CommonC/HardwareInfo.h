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

#ifndef CommonC_HardwareInfo_h
#define CommonC_HardwareInfo_h

#include <CommonC/Base.h>

typedef struct {
    /// The model name of the CPU. Empty if one could not be found.
    char model[256];
    struct {
        /// The number of available physical cores. Zero if it could not be found.
        size_t physical;
        /// The number of available logical cores. Zero if it could not be found.
        size_t logical;
    } cores;
    /// The maximum amount of memory available to the CPU. Zero if it could not be found.
    size_t memory;
} CCHardwareCPU;

typedef struct {
    /// The model name of the GPU. Empty if one could not be found.
    char model[256];
    /// The number of available cores. Zero if it could not be found.
    size_t cores;
    /// The maximum amount of VRAM available to the GPU. Zero if it could not be found.
    size_t vram;
} CCHardwareGPU;

/*!
 * @brief Get information on the available CPUs.
 * @param Processors A pointer to where to store the CPU information.
 * @param Count A pointer to the number of CPUs that can be stored. This will also be set to the number actually
 *              found.
 *
 * @return Whether or not the information was successfully retrieved.
 */
_Bool CCHardwareGetCPUs(CCHardwareCPU *Processors, size_t *Count);

/*!
 * @brief Get information on the available GPUs.
 * @param Processors A pointer to where to store the GPU information.
 * @param Count A pointer to the number of GPUs that can be stored. This will also be set to the number actually
 *              found.
 *
 * @return Whether or not the information was successfully retrieved.
 */
_Bool CCHardwareGetGPUs(CCHardwareGPU *Processors, size_t *Count);

#endif
