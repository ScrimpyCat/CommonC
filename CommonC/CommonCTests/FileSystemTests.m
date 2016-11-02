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
#import "FileSystem.h"
#import "Path.h"
#import "FileHandle.h"

@interface FileSystemTests : XCTestCase

@end

@implementation FileSystemTests
{
    FSPath testFolder;
}

-(void) setUp
{
    [super setUp];
    
    testFolder = FSPathCreate("commonc-framework/");
    FSManagerRemove(testFolder);
    FSManagerCreate(testFolder, FALSE);
}

-(void) tearDown
{
    [super tearDown];
    
    FSManagerRemove(testFolder);
    
    FSPathDestroy(testFolder);
}

-(void) testCurrentPath
{
    XCTAssertTrue(!strcmp(FSPathGetPathString(FSPathCurrent()), "//Macintosh HD/private/tmp/"), @"Correctly picks up current directory");
}

-(void) testCreation
{
    FSPath File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "123"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertNotEqual(FSManagerCreate(File, FALSE), FSOperationSuccess, @"Intermediate directories should not exist");
    XCTAssertFalse(FSManagerExists(File), @"File should not exist");
    
    XCTAssertEqual(FSManagerCreate(File, TRUE), FSOperationSuccess, @"Intermediate directories should be created as well");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    FSPathDestroy(File);
    
    
    File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertEqual(FSManagerCreate(File, FALSE), FSOperationSuccess, @"Intermediate directories already exist");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    FSPathDestroy(File);
}

-(void) testRemoval
{
    FSPath File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "123"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertNotEqual(FSManagerCreate(File, FALSE), FSOperationSuccess, @"Intermediate directories should not exist");
    XCTAssertFalse(FSManagerExists(File), @"File should not exist");
    
    XCTAssertEqual(FSManagerCreate(File, TRUE), FSOperationSuccess, @"Intermediate directories should be created as well");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    XCTAssertEqual(FSManagerRemove(File), FSOperationSuccess, @"Should remove the file");
    XCTAssertFalse(FSManagerExists(File), @"File should no longer exist");

    
    FSPathDestroy(File);
    
    
    File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertEqual(FSManagerCreate(File, FALSE), FSOperationSuccess, @"Intermediate directories already exist");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    XCTAssertEqual(FSManagerRemove(testFolder), FSOperationSuccess, @"Should remove all files/directories");
    XCTAssertFalse(FSManagerExists(File), @"File should no longer exist");
    
    FSPathDestroy(File);
}

-(void) testMoving
{
    FSPath File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "123"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    FSPath Destination = FSPathCopy(testFolder);
    FSPathAppendComponent(Destination, FSPathComponentCreate(FSPathComponentTypeDirectory, "destination"));
    FSPathAppendComponent(Destination, FSPathComponentCreate(FSPathComponentTypeFile, "test1"));
    FSPathAppendComponent(Destination, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertEqual(FSManagerCreate(File, TRUE), FSOperationSuccess, @"Intermediate directories should be created as well");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    XCTAssertNotEqual(FSManagerMove(File, Destination), FSOperationSuccess, @"Should not move file due to destination not existing");
    XCTAssertTrue(FSManagerExists(File), @"File should still exist");
    
    FSPath Folder = FSPathCopy(Destination);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    XCTAssertEqual(FSManagerCreate(Folder, FALSE), FSOperationSuccess, @"Should create directory");
    FSPathDestroy(Folder);
    
    XCTAssertEqual(FSManagerMove(File, Destination), FSOperationSuccess, @"Should move the file");
    XCTAssertFalse(FSManagerExists(File), @"File should no longer exist");
    XCTAssertTrue(FSManagerExists(Destination), @"File should exist");
    
    XCTAssertEqual(FSManagerCreate(File, FALSE), FSOperationSuccess, @"Original directories should still exist");
    
    Folder = FSPathCopy(File);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    
    FSPathInsertComponentAtIndex(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "destination"), FSPathGetComponentCount(File) - 4);
    
    FSPathDestroy(Destination);
    Destination = FSPathCopy(File);
    FSPathRemoveComponentLast(Destination);
    FSPathRemoveComponentLast(Destination);
    FSPathRemoveComponentLast(Destination);
    
    XCTAssertEqual(FSManagerMove(Folder, Destination), FSOperationSuccess, @"Should move the file");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    FSPathDestroy(Folder);
    
    FSPathDestroy(File);
    FSPathDestroy(Destination);
}

-(void) testCopying
{
    FSPath File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "123"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    FSPath Destination = FSPathCopy(testFolder);
    FSPathAppendComponent(Destination, FSPathComponentCreate(FSPathComponentTypeDirectory, "destination"));
    FSPathAppendComponent(Destination, FSPathComponentCreate(FSPathComponentTypeFile, "test1"));
    FSPathAppendComponent(Destination, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertEqual(FSManagerCreate(File, TRUE), FSOperationSuccess, @"Intermediate directories should be created as well");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    XCTAssertNotEqual(FSManagerCopy(File, Destination), FSOperationSuccess, @"Should not move file due to destination not existing");
    XCTAssertTrue(FSManagerExists(File), @"File should still exist");
    
    FSPath Folder = FSPathCopy(Destination);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    XCTAssertEqual(FSManagerCreate(Folder, FALSE), FSOperationSuccess, @"Should create directory");
    FSPathDestroy(Folder);
    
    XCTAssertEqual(FSManagerCopy(File, Destination), FSOperationSuccess, @"Should move the file");
    XCTAssertTrue(FSManagerExists(File), @"File should still exist");
    XCTAssertTrue(FSManagerExists(Destination), @"File should exist");
    
    XCTAssertEqual(FSManagerCreate(File, FALSE), FSOperationSuccess, @"Original directories should still exist");
    
    Folder = FSPathCopy(File);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    
    FSPath Original = FSPathCopy(File);
    FSPathInsertComponentAtIndex(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "destination"), FSPathGetComponentCount(File) - 4);
    
    FSPathDestroy(Destination);
    Destination = FSPathCopy(File);
    FSPathRemoveComponentLast(Destination);
    FSPathRemoveComponentLast(Destination);
    FSPathRemoveComponentLast(Destination);
    
    XCTAssertEqual(FSManagerCopy(Folder, Destination), FSOperationSuccess, @"Should move the file");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    XCTAssertTrue(FSManagerExists(Original), @"File should still exist");
    FSPathDestroy(Folder);
    FSPathDestroy(Original);
    
    FSPathDestroy(File);
    FSPathDestroy(Destination);
}

-(void) testRenaming
{
    FSPath File = FSPathCopy(testFolder);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "example"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "123"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    XCTAssertEqual(FSManagerCreate(File, TRUE), FSOperationSuccess, @"Intermediate directories should be created as well");
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    XCTAssertEqual(FSManagerRename(File, "blah.png"), FSOperationSuccess, @"Should rename the file");
    XCTAssertFalse(FSManagerExists(File), @"File should not exist");
    
    FSPathRemoveComponentLast(File);
    FSPathRemoveComponentLast(File);
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeFile, "blah"));
    FSPathAppendComponent(File, FSPathComponentCreate(FSPathComponentTypeExtension, "png"));
    
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    FSPath Folder = FSPathCopy(File);
    FSPathRemoveComponentLast(Folder);
    FSPathRemoveComponentLast(Folder);
    
    XCTAssertEqual(FSManagerRename(Folder, "stuff"), FSOperationSuccess, @"Should rename the folder");
    XCTAssertFalse(FSManagerExists(Folder), @"Folder should not exist");
    XCTAssertFalse(FSManagerExists(File), @"File should not exist");
    
    FSPathInsertComponentAtIndex(File, FSPathComponentCreate(FSPathComponentTypeDirectory, "stuff"), FSPathGetComponentCount(File) - 3);
    FSPathRemoveComponentIndex(File, FSPathGetComponentCount(File) - 3);
    XCTAssertTrue(FSManagerExists(File), @"File should exist");
    
    FSPathDestroy(Folder);
    FSPathDestroy(File);
}

@end
