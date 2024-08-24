/*
 *  Copyright (c) 2024, Stefan Johnson
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

#ifndef CommonC_ReflectStream_h
#define CommonC_ReflectStream_h

#include <CommonC/Base.h>
#include <CommonC/BitSets.h>
#include <CommonC/Reflect.h>

typedef struct {
    void *stream;
    union {
        CCReflectStreamReader read;
        CCReflectStreamWriter write;
    };
} CCReflectStream;

#pragma mark - RLE

typedef struct {
    CCReflectStream into;
    struct {
        CCBits(uint8_t, 256) mask;
        uint8_t value;
        size_t size;
        size_t count;
    } repeat;
} CCReflectStreamRLE;

#define CC_REFLECT_STREAM_READ_RLE_ZERO_8(stream, reader)  (CCReflectStreamRLE){ .into = { stream, .read = reader }, .repeat = { .mask = { 1 }, .size = 1, .count = 0 } }
#define CC_REFLECT_STREAM_READ_RLE_ZERO_16(stream, reader) (CCReflectStreamRLE){ .into = { stream, .read = reader }, .repeat = { .mask = { 1 }, .size = 2, .count = 0 } }
#define CC_REFLECT_STREAM_READ_RLE_ZERO_24(stream, reader) (CCReflectStreamRLE){ .into = { stream, .read = reader }, .repeat = { .mask = { 1 }, .size = 3, .count = 0 } }
#define CC_REFLECT_STREAM_READ_RLE_ZERO_32(stream, reader) (CCReflectStreamRLE){ .into = { stream, .read = reader }, .repeat = { .mask = { 1 }, .size = 4, .count = 0 } }
#define CC_REFLECT_STREAM_READ_RLE_ZERO_64(stream, reader) (CCReflectStreamRLE){ .into = { stream, .read = reader }, .repeat = { .mask = { 1 }, .size = 8, .count = 0 } }

#define CC_REFLECT_STREAM_WRITE_RLE_ZERO_8(stream, writer)  (CCReflectStreamRLE){ .into = { stream, .write = writer }, .repeat = { .mask = { 1 }, .size = 1, .count = 0 } }
#define CC_REFLECT_STREAM_WRITE_RLE_ZERO_16(stream, writer) (CCReflectStreamRLE){ .into = { stream, .write = writer }, .repeat = { .mask = { 1 }, .size = 2, .count = 0 } }
#define CC_REFLECT_STREAM_WRITE_RLE_ZERO_24(stream, writer) (CCReflectStreamRLE){ .into = { stream, .write = writer }, .repeat = { .mask = { 1 }, .size = 3, .count = 0 } }
#define CC_REFLECT_STREAM_WRITE_RLE_ZERO_32(stream, writer) (CCReflectStreamRLE){ .into = { stream, .write = writer }, .repeat = { .mask = { 1 }, .size = 4, .count = 0 } }
#define CC_REFLECT_STREAM_WRITE_RLE_ZERO_64(stream, writer) (CCReflectStreamRLE){ .into = { stream, .write = writer }, .repeat = { .mask = { 1 }, .size = 8, .count = 0 } }

/*!
 * @brief Read from an RLE stream.
 * @warning The stream config should not be changed unless it followed a @b CCReflectStreamRLEReadContinue, or @b Stream.repeat.count is 0.
 * @note Compatible as a @b CCReflectStreamReader.
 * @param Stream The RLE stream.
 * @param Data The output data.
 * @param Size The size of the data to read.
 */
void CCReflectStreamRLERead(CCReflectStreamRLE *Stream, void *Data, size_t Size);

/*!
 * @brief Continue to read from an RLE stream, but does not start a new RLE.
 * @note Compatible as a @b CCReflectStreamReader.
 * @param Stream The RLE stream.
 * @param Data The output data.
 * @param Size The size of the data to read.
 */
void CCReflectStreamRLEReadContinue(CCReflectStreamRLE *Stream, void *Data, size_t Size);

/*!
 * @brief Write an RLE stream.
 * @warning The stream config should not be changed unless it followed a @b CCReflectStreamRLEWriteContinue, or @b CCReflectStreamRLEWriteFlush, or @b Stream.repeat.count is 0.
 *          If the write is the last call it should be followed by a @b CCReflectStreamRLEWriteFlush to finalise any remaining RLE.
 *
 * @note Compatible as a @b CCReflectStreamWriter.
 * @param Stream The RLE stream.
 * @param Data The input data.
 * @param Size The size of the data.
 */
void CCReflectStreamRLEWrite(CCReflectStreamRLE *Stream, const void *Data, size_t Size);

/*!
 * @brief Continue to write an RLE stream, but does not start a new RLE.
 * @note Compatible as a @b CCReflectStreamWriter.
 * @param Stream The RLE stream.
 * @param Data The input data.
 * @param Size The size of the data.
 */
void CCReflectStreamRLEWriteContinue(CCReflectStreamRLE *Stream, const void *Data, size_t Size);

/*!
 * @brief Flush the current RLE stream.
 * @param Stream The RLE stream.
 */
void CCReflectStreamRLEWriteFlush(CCReflectStreamRLE *Stream);

#endif
