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

#ifndef CommonC_Vector_h
#define CommonC_Vector_h

#include <CommonC/Vector2D.h>
#include <CommonC/Vector3D.h>
#include <CommonC/Vector4D.h>

#define T CCVector2D
#define CC_NUMERIC_EQUAL CCVector2Equal
#define CC_NUMERIC_LESS_THAN CCVector2LessThan
#define CC_NUMERIC_GREATER_THAN CCVector2GreaterThan
#define CC_NUMERIC_LESS_THAN_EQUAL CCVector2LessThanEqual
#define CC_NUMERIC_GREATER_THAN_EQUAL CCVector2GreaterThanEqual
#define CC_NUMERIC_ADD CCVector2Add
#define CC_NUMERIC_SUB CCVector2Sub
#define CC_NUMERIC_MUL CCVector2Mul
#define CC_NUMERIC_DIV CCVector2Div
#include <CommonC/Numeric.h>

#define T CCVector2D
#define CC_MIN CCVector2Min
#define CC_MAX CCVector2Max
#define CC_CLAMP CCVector2Clamp
#include <CommonC/Extrema.h>

#define T CCVector3D
#define CC_NUMERIC_EQUAL CCVector3Equal
#define CC_NUMERIC_LESS_THAN CCVector3LessThan
#define CC_NUMERIC_GREATER_THAN CCVector3GreaterThan
#define CC_NUMERIC_LESS_THAN_EQUAL CCVector3LessThanEqual
#define CC_NUMERIC_GREATER_THAN_EQUAL CCVector3GreaterThanEqual
#define CC_NUMERIC_ADD CCVector3Add
#define CC_NUMERIC_SUB CCVector3Sub
#define CC_NUMERIC_MUL CCVector3Mul
#define CC_NUMERIC_DIV CCVector3Div
#include <CommonC/Numeric.h>

#define T CCVector3D
#define CC_MIN CCVector3Min
#define CC_MAX CCVector3Max
#define CC_CLAMP CCVector3Clamp
#include <CommonC/Extrema.h>

#define T CCVector4D
#define CC_NUMERIC_EQUAL CCVector4Equal
#define CC_NUMERIC_LESS_THAN CCVector4LessThan
#define CC_NUMERIC_GREATER_THAN CCVector4GreaterThan
#define CC_NUMERIC_LESS_THAN_EQUAL CCVector4LessThanEqual
#define CC_NUMERIC_GREATER_THAN_EQUAL CCVector4GreaterThanEqual
#define CC_NUMERIC_ADD CCVector4Add
#define CC_NUMERIC_SUB CCVector4Sub
#define CC_NUMERIC_MUL CCVector4Mul
#define CC_NUMERIC_DIV CCVector4Div
#include <CommonC/Numeric.h>

#define T CCVector4D
#define CC_MIN CCVector4Min
#define CC_MAX CCVector4Max
#define CC_CLAMP CCVector4Clamp
#include <CommonC/Extrema.h>

#endif
