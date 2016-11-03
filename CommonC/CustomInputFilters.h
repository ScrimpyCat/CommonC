/*
 *  Copyright (c) 2014, Stefan Johnson
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


#pragma mark Documentation
/*
 Some useful custom input filters. These are not added by default and must manually be added.
 
 CCFileFilterInput: Adds a simple filename filter. It uses the current list of paths added to CCFileFilterInputAddPath to filter the current filename.
                    One thing to watchout for is that this is a very naive filter, it simply takes the first match and removes that part. If you happen
                    to have two paths that would both be true for the current filename, after the first one removes its portion the other one may no
                    longer be true and so won't remove its portion. The order of precedence for these paths is in the reverse order they were added.
                    So the last filter added has precedence over all previously added paths.
 */

#pragma mark -

#ifndef CommonC_CustomInputFilters_h
#define CommonC_CustomInputFilters_h

#include <CommonC/Logging.h>


#pragma mark - Functions
void CCFileFilterInputAddPath(const char *Path);
size_t CCFileFilterInput(const CCLogData *LogData, const CCLogInputData *Data); //Strips the filename path for filepaths added using CCFileFilterInputAddPath()

#endif
