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

@interface FileHandleTests : XCTestCase

@end

@implementation FileHandleTests
{
    FSPath path;
}

-(void) setUp
{
    [super setUp];
    
    path = FSPathCreate("commonc-framework/");
    FSManagerRemove(path);
    
    FSPathAppendComponent(path, FSPathComponentCreate(FSPathComponentTypeFile, "test"));
    FSPathAppendComponent(path, FSPathComponentCreate(FSPathComponentTypeExtension, "txt"));
    
    FSManagerCreate(path, TRUE);
    
    FSHandle Handle;
    if (FSHandleOpen(path, FSHandleTypeWrite, &Handle) == FSOperationSuccess)
    {
        uint8_t Values[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        FSHandleWrite(Handle, sizeof(Values), Values, FSBehaviourDefault);
        FSHandleClose(Handle);
    }
}

-(void) tearDown
{
    [super tearDown];
    
    FSPathRemoveComponentLast(path);
    FSPathRemoveComponentLast(path);
    
    FSManagerRemove(path);
    
    FSPathDestroy(path);
}

-(void) testOpeningFile
{
    FSHandle Handle;
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeRead, &Handle), FSOperationSuccess, @"Should open the file");
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
    
    FSPath BadFile = FSPathCopy(path);
    FSPathRemoveComponentLast(BadFile);
    FSPathAppendComponent(BadFile, FSPathComponentCreate(FSPathComponentTypeExtension, "png"));
    XCTAssertNotEqual(FSHandleOpen(BadFile, FSHandleTypeRead, &Handle), FSOperationSuccess, @"Should not be able to open the file");
    FSPathDestroy(BadFile);
}

-(void) testReading
{
    FSHandle Handle;
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeRead, &Handle), FSOperationSuccess, @"Should open the file");
    
    size_t Read = 1;
    uint8_t Value = 0, Values[16];
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 2, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 3, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 3, @"Should read the correct value");
    
    Read = 16;
    XCTAssertEqual(FSHandleRead(Handle, &Read, Values, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 10, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 3, @"Should read the correct value");
    XCTAssertEqual(Values[1], 4, @"Should read the correct value");
    XCTAssertEqual(Values[2], 5, @"Should read the correct value");
    XCTAssertEqual(Values[3], 6, @"Should read the correct value");
    XCTAssertEqual(Values[4], 7, @"Should read the correct value");
    XCTAssertEqual(Values[5], 8, @"Should read the correct value");
    XCTAssertEqual(Values[6], 9, @"Should read the correct value");
    XCTAssertEqual(Values[7], 10, @"Should read the correct value");
    XCTAssertEqual(Values[8], 11, @"Should read the correct value");
    XCTAssertEqual(Values[9], 12, @"Should read the correct value");
    
    Read = 16;
    XCTAssertEqual(FSHandleRead(Handle, &Read, Values, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 10, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 3, @"Should read the correct value");
    XCTAssertEqual(Values[1], 4, @"Should read the correct value");
    XCTAssertEqual(Values[2], 5, @"Should read the correct value");
    XCTAssertEqual(Values[3], 6, @"Should read the correct value");
    XCTAssertEqual(Values[4], 7, @"Should read the correct value");
    XCTAssertEqual(Values[5], 8, @"Should read the correct value");
    XCTAssertEqual(Values[6], 9, @"Should read the correct value");
    XCTAssertEqual(Values[7], 10, @"Should read the correct value");
    XCTAssertEqual(Values[8], 11, @"Should read the correct value");
    XCTAssertEqual(Values[9], 12, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, &Value, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 2, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 5, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 6, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 50, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    XCTAssertNotEqual(FSHandleWriteFromOffset(Handle, 0, 1, &(uint8_t){ 0 }, FSBehaviourDefault), FSOperationSuccess, @"Should not write to the file");
    XCTAssertNotEqual(FSHandleRemoveFromOffset(Handle, 0, 1, FSBehaviourDefault), FSOperationSuccess, @"Should not remove from the file");
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
}

-(void) testUpdating
{
    FSHandle Handle;
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeUpdate, &Handle), FSOperationSuccess, @"Should open the file");
    
    size_t Read = 1;
    uint8_t Value = 0, Values[20];
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 2, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 3, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 3, @"Should read the correct value");
    
    Read = 16;
    XCTAssertEqual(FSHandleRead(Handle, &Read, Values, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 10, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 3, @"Should read the correct value");
    XCTAssertEqual(Values[1], 4, @"Should read the correct value");
    XCTAssertEqual(Values[2], 5, @"Should read the correct value");
    XCTAssertEqual(Values[3], 6, @"Should read the correct value");
    XCTAssertEqual(Values[4], 7, @"Should read the correct value");
    XCTAssertEqual(Values[5], 8, @"Should read the correct value");
    XCTAssertEqual(Values[6], 9, @"Should read the correct value");
    XCTAssertEqual(Values[7], 10, @"Should read the correct value");
    XCTAssertEqual(Values[8], 11, @"Should read the correct value");
    XCTAssertEqual(Values[9], 12, @"Should read the correct value");
    
    Read = 16;
    XCTAssertEqual(FSHandleRead(Handle, &Read, Values, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 10, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 3, @"Should read the correct value");
    XCTAssertEqual(Values[1], 4, @"Should read the correct value");
    XCTAssertEqual(Values[2], 5, @"Should read the correct value");
    XCTAssertEqual(Values[3], 6, @"Should read the correct value");
    XCTAssertEqual(Values[4], 7, @"Should read the correct value");
    XCTAssertEqual(Values[5], 8, @"Should read the correct value");
    XCTAssertEqual(Values[6], 9, @"Should read the correct value");
    XCTAssertEqual(Values[7], 10, @"Should read the correct value");
    XCTAssertEqual(Values[8], 11, @"Should read the correct value");
    XCTAssertEqual(Values[9], 12, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourPreserveOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, &Value, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 1, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 2, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 5, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 1, @"Should read the correct number of bytes");
    XCTAssertEqual(Value, 6, @"Should read the correct value");
    
    Read = 1;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 50, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    XCTAssertEqual(FSHandleSetOffset(Handle, 0), FSOperationSuccess, @"Should set the offset");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 0 }, FSBehaviourDefault), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 10 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 20 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 30 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 16, (uint8_t[16]){ 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWriteFromOffset(Handle, 4, 1, &(uint8_t){ 254 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 255 }, FSBehaviourDefault), FSOperationSuccess, @"Should write to the file");
    
    //10 20 30 40 254 255 70 80 90 100 110 120 130 140 150 160 170 180 190
    Read = 16;
    XCTAssertEqual(FSHandleRead(Handle, &Read, Values, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 14, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 255, @"Should read the correct value");
    XCTAssertEqual(Values[1], 70, @"Should read the correct value");
    XCTAssertEqual(Values[2], 80, @"Should read the correct value");
    XCTAssertEqual(Values[3], 90, @"Should read the correct value");
    XCTAssertEqual(Values[4], 100, @"Should read the correct value");
    XCTAssertEqual(Values[5], 110, @"Should read the correct value");
    XCTAssertEqual(Values[6], 120, @"Should read the correct value");
    XCTAssertEqual(Values[7], 130, @"Should read the correct value");
    XCTAssertEqual(Values[8], 140, @"Should read the correct value");
    XCTAssertEqual(Values[9], 150, @"Should read the correct value");
    XCTAssertEqual(Values[10], 160, @"Should read the correct value");
    XCTAssertEqual(Values[11], 170, @"Should read the correct value");
    XCTAssertEqual(Values[12], 180, @"Should read the correct value");
    XCTAssertEqual(Values[13], 190, @"Should read the correct value");
    
    Read = 5;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 5, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 10, @"Should read the correct value");
    XCTAssertEqual(Values[1], 20, @"Should read the correct value");
    XCTAssertEqual(Values[2], 30, @"Should read the correct value");
    XCTAssertEqual(Values[3], 40, @"Should read the correct value");
    XCTAssertEqual(Values[4], 254, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleWriteFromOffset(Handle, 21, 1, &(uint8_t){ 123 }, FSBehaviourDefault), FSOperationSuccess, @"Should write to the file");
    
    Read = 4;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 18, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 4, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 190, @"Should read the correct value");
    XCTAssertEqual(Values[1], 0, @"Should read the correct value");
    XCTAssertEqual(Values[2], 0, @"Should read the correct value");
    XCTAssertEqual(Values[3], 123, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleSetOffset(Handle, 0), FSOperationSuccess, @"Should set the offset");
    XCTAssertEqual(FSHandleRemove(Handle, 1, FSBehaviourDefault), FSOperationSuccess, @"Should remove from the file");
    XCTAssertEqual(FSHandleRemove(Handle, 1, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should remove from the file");
    XCTAssertEqual(FSHandleRemove(Handle, 2, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should remove from the file");
    XCTAssertEqual(FSHandleRemove(Handle, 1, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should remove from the file");
    
    Read = 20;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 17, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 30, @"Should read the correct value");
    XCTAssertEqual(Values[1], 255, @"Should read the correct value");
    XCTAssertEqual(Values[2], 70, @"Should read the correct value");
    XCTAssertEqual(Values[3], 90, @"Should read the correct value");
    XCTAssertEqual(Values[4], 100, @"Should read the correct value");
    XCTAssertEqual(Values[5], 110, @"Should read the correct value");
    XCTAssertEqual(Values[6], 120, @"Should read the correct value");
    XCTAssertEqual(Values[7], 130, @"Should read the correct value");
    XCTAssertEqual(Values[8], 140, @"Should read the correct value");
    XCTAssertEqual(Values[9], 150, @"Should read the correct value");
    XCTAssertEqual(Values[10], 160, @"Should read the correct value");
    XCTAssertEqual(Values[11], 170, @"Should read the correct value");
    XCTAssertEqual(Values[12], 180, @"Should read the correct value");
    XCTAssertEqual(Values[13], 190, @"Should read the correct value");
    XCTAssertEqual(Values[14], 0, @"Should read the correct value");
    XCTAssertEqual(Values[15], 0, @"Should read the correct value");
    XCTAssertEqual(Values[16], 123, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleRemoveFromOffset(Handle, 16, 2, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should remove from the file");
    XCTAssertEqual(FSHandleRemoveFromOffset(Handle, 20, 2, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should remove from the file");
    
    Read = 20;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 16, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 30, @"Should read the correct value");
    XCTAssertEqual(Values[1], 255, @"Should read the correct value");
    XCTAssertEqual(Values[2], 70, @"Should read the correct value");
    XCTAssertEqual(Values[3], 90, @"Should read the correct value");
    XCTAssertEqual(Values[4], 100, @"Should read the correct value");
    XCTAssertEqual(Values[5], 110, @"Should read the correct value");
    XCTAssertEqual(Values[6], 120, @"Should read the correct value");
    XCTAssertEqual(Values[7], 130, @"Should read the correct value");
    XCTAssertEqual(Values[8], 140, @"Should read the correct value");
    XCTAssertEqual(Values[9], 150, @"Should read the correct value");
    XCTAssertEqual(Values[10], 160, @"Should read the correct value");
    XCTAssertEqual(Values[11], 170, @"Should read the correct value");
    XCTAssertEqual(Values[12], 180, @"Should read the correct value");
    XCTAssertEqual(Values[13], 190, @"Should read the correct value");
    XCTAssertEqual(Values[14], 0, @"Should read the correct value");
    XCTAssertEqual(Values[15], 0, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleSetOffset(Handle, 0), FSOperationSuccess, @"Should set the offset");
    XCTAssertEqual(FSHandleWrite(Handle, 3, (uint8_t[3]){ 1, 2, 3 }, FSBehaviourUpdateOffset | FSWritingBehaviourInsert), FSOperationSuccess, @"Should insert in the file");
    XCTAssertEqual(FSHandleRemove(Handle, 3, FSBehaviourDefault), FSOperationSuccess, @"Should remove from the file");
    XCTAssertEqual(FSHandleWriteFromOffset(Handle, 14, 3, (uint8_t[3]){ 4, 5, 6 }, FSBehaviourUpdateOffset | FSWritingBehaviourInsert), FSOperationSuccess, @"Should insert in the file");
    
    Read = 20;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 0, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 19, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 1, @"Should read the correct value");
    XCTAssertEqual(Values[1], 2, @"Should read the correct value");
    XCTAssertEqual(Values[2], 3, @"Should read the correct value");
    XCTAssertEqual(Values[3], 90, @"Should read the correct value");
    XCTAssertEqual(Values[4], 100, @"Should read the correct value");
    XCTAssertEqual(Values[5], 110, @"Should read the correct value");
    XCTAssertEqual(Values[6], 120, @"Should read the correct value");
    XCTAssertEqual(Values[7], 130, @"Should read the correct value");
    XCTAssertEqual(Values[8], 140, @"Should read the correct value");
    XCTAssertEqual(Values[9], 150, @"Should read the correct value");
    XCTAssertEqual(Values[10], 160, @"Should read the correct value");
    XCTAssertEqual(Values[11], 170, @"Should read the correct value");
    XCTAssertEqual(Values[12], 180, @"Should read the correct value");
    XCTAssertEqual(Values[13], 190, @"Should read the correct value");
    XCTAssertEqual(Values[14], 4, @"Should read the correct value");
    XCTAssertEqual(Values[15], 5, @"Should read the correct value");
    XCTAssertEqual(Values[16], 6, @"Should read the correct value");
    XCTAssertEqual(Values[17], 0, @"Should read the correct value");
    XCTAssertEqual(Values[18], 0, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
}

-(void) testWriting
{
    FSHandle Handle;
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeWrite, &Handle), FSOperationSuccess, @"Should open the file");
    
    size_t Read = 1;
    uint8_t Value = 0, Values[20];
    XCTAssertNotEqual(FSHandleRead(Handle, &Read, &Value, FSBehaviourDefault), FSOperationSuccess, @"Should not read the file");
    XCTAssertEqual(Read, 0, @"Should read the correct number of bytes");
    
    XCTAssertEqual(FSHandleSetOffset(Handle, 0), FSOperationSuccess, @"Should set the offset");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 0 }, FSBehaviourDefault), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 10 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 20 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 30 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 16, (uint8_t[16]){ 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWriteFromOffset(Handle, 4, 1, &(uint8_t){ 254 }, FSBehaviourUpdateOffset), FSOperationSuccess, @"Should write to the file");
    XCTAssertEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 255 }, FSBehaviourDefault), FSOperationSuccess, @"Should write to the file");
    //10 20 30 40 254 255 70 80 90 100 110 120 130 140 150 160 170 180 190
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
    
    
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeRead, &Handle), FSOperationSuccess, @"Should open the file");
    
    Read = 20;
    XCTAssertEqual(FSHandleRead(Handle, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 19, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 10, @"Should read the correct value");
    XCTAssertEqual(Values[1], 20, @"Should read the correct value");
    XCTAssertEqual(Values[2], 30, @"Should read the correct value");
    XCTAssertEqual(Values[3], 40, @"Should read the correct value");
    XCTAssertEqual(Values[4], 254, @"Should read the correct value");
    XCTAssertEqual(Values[5], 255, @"Should read the correct value");
    XCTAssertEqual(Values[6], 70, @"Should read the correct value");
    XCTAssertEqual(Values[7], 80, @"Should read the correct value");
    XCTAssertEqual(Values[8], 90, @"Should read the correct value");
    XCTAssertEqual(Values[9], 100, @"Should read the correct value");
    XCTAssertEqual(Values[10], 110, @"Should read the correct value");
    XCTAssertEqual(Values[11], 120, @"Should read the correct value");
    XCTAssertEqual(Values[12], 130, @"Should read the correct value");
    XCTAssertEqual(Values[13], 140, @"Should read the correct value");
    XCTAssertEqual(Values[14], 150, @"Should read the correct value");
    XCTAssertEqual(Values[15], 160, @"Should read the correct value");
    XCTAssertEqual(Values[16], 170, @"Should read the correct value");
    XCTAssertEqual(Values[17], 180, @"Should read the correct value");
    XCTAssertEqual(Values[18], 190, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
    
    
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeWrite, &Handle), FSOperationSuccess, @"Should open the file");
    
    XCTAssertEqual(FSHandleWriteFromOffset(Handle, 21, 1, &(uint8_t){ 123 }, FSBehaviourDefault), FSOperationSuccess, @"Should write to the file");
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
    
    
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeRead, &Handle), FSOperationSuccess, @"Should open the file");
    
    Read = 4;
    XCTAssertEqual(FSHandleReadFromOffset(Handle, 18, &Read, Values, FSBehaviourDefault), FSOperationSuccess, @"Should read the file");
    XCTAssertEqual(Read, 4, @"Should read the correct number of bytes");
    XCTAssertEqual(Values[0], 190, @"Should read the correct value");
    XCTAssertEqual(Values[1], 0, @"Should read the correct value");
    XCTAssertEqual(Values[2], 0, @"Should read the correct value");
    XCTAssertEqual(Values[3], 123, @"Should read the correct value");
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
    
    
    XCTAssertEqual(FSHandleOpen(path, FSHandleTypeWrite, &Handle), FSOperationSuccess, @"Should open the file");
    
    XCTAssertNotEqual(FSHandleRemove(Handle, 1, FSBehaviourDefault), FSOperationSuccess, @"Should not remove from the file");
    XCTAssertNotEqual(FSHandleWrite(Handle, 1, &(uint8_t){ 0 }, FSBehaviourDefault | FSWritingBehaviourInsert), FSOperationSuccess, @"Should not insert in the file");
    
    XCTAssertEqual(FSHandleClose(Handle), FSOperationSuccess, @"Should close the file");
}

@end
