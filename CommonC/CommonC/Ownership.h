/*
 *  Copyright (c) 2016, Stefan Johnson
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

#ifndef CommonC_Ownership_h
#define CommonC_Ownership_h

/*
 Ownership qualifiers
 
 Used to provide some added context as the expected ownership behaviour.
 
 Note: Looked into using Clang's annotated malloc analyzer, but wasn't able to support some conventions.
       So going with this more simplistic approach.
 
 Variables/Arguments:
    Variables/Arguments being passed a value can indicate their behaviour using: CC_COPY, CC_RETAIN, CC_DESTROY,
    CC_OWN. These macros prefix the name for convenience (so autocompletes should show the indented use), where:
        c = copy
        r = retain
        d = destroy
        o = own
 
    While no qualifier present indicates there is no transfer of ownership, and usage is only temporary.
 
    Onwership differences between these can be grouped into two groups, ownership is transfered, and ownership is
    retained/not transfered.
 
    Copy and retain: imply ownership is retained. So caller keeps its ownership.
    Destroy and own: imply ownership is transfered. So caller loses its ownership.
 
    The next differences are behavioural differences. These make no guarantee about how you can use them if ownership
    is changed, but imply there may be a possibility to. Need to check docs/code to find out.
 
    Copy: Copies the value. Should assume this is a new allocation and new copy of the state.
    Retain: Retains the value. So increments its reference count by 1.
    Destroy: Destroys the value. So usage of the value after the function is called, is not allowed.
    Own: Owns the value. Usage of the value after the function is called is neither allowed nor not allowed. It depends
         on the usage. Documentation should typically clarify if it's safe or not to use.
 
 Returns:
    Function returns can indicate their behaviour using: CC_NEW.
 
    New indicates a transfer of ownership.
    While no qualifier indicates no transfer of ownership.
 
    In other words CC_NEW indicates that the caller is now responsible for the data. While those without imply that the
    caller is not responsible for the data, and the expected usage behaviour is up to what the documentation has said.
 
 e.g.
 CC_NEW void *malloc(size_t size); //Caller is responsible for the returned data.
 void *value(void); //Caller is not responsible for the returned data.
 void copy(void *CC_COPY(ptr)); //Caller and callee are responsible for 'ptr'.
 void retain(void *CC_RETAIN(ptr)); //Caller and callee are responsible for 'ptr'.
 void destroy(void *CC_DESTROY(ptr)); //Caller is no longer responsible for 'ptr'.
 void hold(void *CC_OWN(ptr)); //Caller is no longer responsible for 'ptr'. Callee is responsible for 'ptr'.
 */

#define CC_COPY(x) c_##x ///Copies the value
#define CC_RETAIN(x) r_##x //Retains the value
#define CC_DESTROY(x) d_##x //Destroys the value (usage of the value after the function is not safe)
#define CC_OWN(x) o_##x //Owns the value (non-retain consume); usage of the value after the function is "safe"
#define CC_NEW //Ownership is passed to caller
//No ownership indicates ownership of the value is not passed to the function or returned to the caller

#endif
