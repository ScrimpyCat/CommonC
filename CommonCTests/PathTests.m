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

#import <XCTest/XCTest.h>
#import "Path.h"

@interface PathTests : XCTestCase

@end

@implementation PathTests

-(void) testFormatting
{
    FSPath Path = FSPathCreate("");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 0);
    XCTAssertEqual(FSPathGetPathString(Path), NULL);
    XCTAssertEqual(FSPathGetFullPathString(Path), NULL);
    XCTAssertEqual(FSPathGetFilenameString(Path), NULL);
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeRelativeRoot, NULL));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 1);
    XCTAssertEqual(FSPathGetPathString(Path), NULL);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/");
    XCTAssertEqual(FSPathGetFilenameString(Path), NULL);
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeDirectory, "foo"));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 2);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"foo/");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/foo/");
    XCTAssertEqual(FSPathGetFilenameString(Path), NULL);
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeDirectory, "bar.framework"));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 3);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"foo/bar.framework/");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/foo/bar.framework/");
    XCTAssertEqual(FSPathGetFilenameString(Path), NULL);
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeRelativeParentDirectory, NULL));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 4);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"foo/bar.framework/../");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/foo/bar.framework/../");
    XCTAssertEqual(FSPathGetFilenameString(Path), NULL);
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 5);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"foo/bar.framework/../test");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/foo/bar.framework/../test");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFilenameString(Path)], @"test");
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 6);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"foo/bar.framework/../test.txt");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/foo/bar.framework/../test.txt");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFilenameString(Path)], @"test.txt");
    
    FSPathAppendComponent(Path, FSPathComponentCreate(FSPathComponentTypeExtension, "png"));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 7);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"foo/bar.framework/../test.txt.png");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/private/tmp/foo/bar.framework/../test.txt.png");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFilenameString(Path)], @"test.txt.png");
    
    FSPathSetComponentAtIndex(Path, FSPathComponentCreate(FSPathComponentTypeRoot, NULL), 0);
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 7);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"/foo/bar.framework/../test.txt.png");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Macintosh HD/foo/bar.framework/../test.txt.png");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFilenameString(Path)], @"test.txt.png");
    
    FSPathPrependComponent(Path, FSPathComponentCreate(FSPathComponentTypeVolume, "Test HD"));
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 8);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetPathString(Path)], @"//Test HD/foo/bar.framework/../test.txt.png");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFullPathString(Path)], @"//Test HD/foo/bar.framework/../test.txt.png");
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathGetFilenameString(Path)], @"test.txt.png");
    
    FSPathDestroy(Path);
}

-(void) testCreation
{
    FSPath Path = FSPathCreate("foo/");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 2);
    
    FSPathComponent Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 3);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/test/");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 4);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/../");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 4);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/../test/");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 5);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 4);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/../test");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 5);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 4);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeFile);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/../test.txt");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 6);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 4);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeFile);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    Component = FSPathGetComponentAtIndex(Path, 5);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"txt");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("foo/bar.framework/../test.txt.png");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 7);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 4);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeFile);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    Component = FSPathGetComponentAtIndex(Path, 5);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"txt");
    
    Component = FSPathGetComponentAtIndex(Path, 6);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"png");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("/foo/bar.framework/../test.txt.png");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 7);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 4);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeFile);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    Component = FSPathGetComponentAtIndex(Path, 5);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"txt");
    
    Component = FSPathGetComponentAtIndex(Path, 6);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"png");
    
    FSPathDestroy(Path);
    
    
    Path = FSPathCreate("//Test HD/foo/bar.framework/../test.txt.png");
    
    XCTAssertEqual(FSPathGetComponentCount(Path), 8);
    
    Component = FSPathGetComponentAtIndex(Path, 0);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeVolume);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"Test HD");
    
    Component = FSPathGetComponentAtIndex(Path, 1);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRoot);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 2);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"foo");
    
    Component = FSPathGetComponentAtIndex(Path, 3);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeDirectory);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"bar.framework");
    
    Component = FSPathGetComponentAtIndex(Path, 4);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeRelativeParentDirectory);
    XCTAssertEqual(FSPathComponentGetString(Component), NULL);
    
    Component = FSPathGetComponentAtIndex(Path, 5);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeFile);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"test");
    
    Component = FSPathGetComponentAtIndex(Path, 6);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"txt");
    
    Component = FSPathGetComponentAtIndex(Path, 7);
    XCTAssertEqual(FSPathComponentGetType(Component), FSPathComponentTypeExtension);
    XCTAssertEqualObjects([NSString stringWithUTF8String: FSPathComponentGetString(Component)], @"png");
    
    FSPathDestroy(Path);
}

@end
