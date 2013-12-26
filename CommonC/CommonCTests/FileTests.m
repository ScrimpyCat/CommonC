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

#import "FileTests.h"
#import "File.h"
#import "Types.h"


#define ANSWER "answer"

static _Bool Working(_Bool ShouldEqual, const char *Str, size_t Length)
{
    if (!Str) return ShouldEqual == FALSE; //true
    else if (ShouldEqual == FALSE) return FALSE; //false
    else
    {
        if (Length == 0) return !strcmp(Str, ANSWER); //true if correct
        else return !strncmp(Str, ANSWER, Length); //true if correct
    }
}

@implementation FileTests

-(void) testCCLastComponent
{
    size_t Length;
    const char *Str;
    
    Str = CCLastComponent(ANSWER, &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%s == %s) (%zu == 0)", Str, ANSWER, Length);
    
    Str = CCLastComponent("/"ANSWER, &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%s == %s) (%zu == 0)", Str, ANSWER, Length);
    
    Str = CCLastComponent("///"ANSWER, &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%s == %s) (%zu == 0)", Str, ANSWER, Length);
    
    Str = CCLastComponent("/first/"ANSWER, &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%s == %s) (%zu == 0)", Str, ANSWER, Length);
    
    Str = CCLastComponent("last/first/"ANSWER, &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%s == %s) (%zu == 0)", Str, ANSWER, Length);
    
    Str = CCLastComponent(ANSWER"/", &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%.*s == %s) (%zu == %zu)", (int)Length, Str, ANSWER, Length, sizeof(ANSWER) - 1);
    
    Str = CCLastComponent(ANSWER"///", &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%.*s == %s) (%zu == %zu)", (int)Length, Str, ANSWER, Length, sizeof(ANSWER) - 1);
    
    Str = CCLastComponent("/////"ANSWER"/////", &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%.*s == %s) (%zu == %zu)", (int)Length, Str, ANSWER, Length, sizeof(ANSWER) - 1);
    
    Str = CCLastComponent("//first///"ANSWER"/////", &Length, '/');
    XCTAssertTrue(Working(TRUE, Str, Length), @"Should return component: (%.*s == %s) (%zu == %zu)", (int)Length, Str, ANSWER, Length, sizeof(ANSWER) - 1);
    
    Str = CCLastComponent("", &Length, '/');
    XCTAssertTrue(Working(FALSE, Str, Length), @"Shouldn't return component: (%p == null)", Str);
    
    Str = CCLastComponent(NULL, &Length, '/');
    XCTAssertTrue(Working(FALSE, Str, Length), @"Shouldn't return component: (%p == null)", Str);
    
    Str = CCLastComponent("//////////", &Length, '/');
    XCTAssertTrue(Working(FALSE, Str, Length), @"Shouldn't return component: (%p == null)", Str);
    
    Str = CCLastComponent("/", &Length, '/');
    XCTAssertTrue(Working(FALSE, Str, Length), @"Shouldn't return component: (%p == null)", Str);
    
    Str = CCLastComponent("\x00"ANSWER, &Length, '/');
    XCTAssertTrue(Working(FALSE, Str, Length), @"Shouldn't return component: (%p == null)", Str);
    
    Str = CCLastComponent(ANSWER + sizeof(ANSWER) - 1, &Length, '/');
    XCTAssertTrue(Working(FALSE, Str, Length), @"Shouldn't return component: (%p == null)", Str);
}

@end
