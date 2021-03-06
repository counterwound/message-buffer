//*****************************************************************************
//
// buffer.h - Defines and Macros for the BUFFER controller.
//
// Copyright (c) 2015 Counterwound Labs, Inc.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
//
//   Neither the name of Counterwound Labs, Inc. nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef _BUFFER_H__
#define _BUFFER_H__

//*****************************************************************************
//
//! \addtogroup buffer_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdint.h>

//*****************************************************************************
//
// Miscellaneous defines for Buffer types
//
//*****************************************************************************
//*****************************************************************************
//
// These are the flags used by the ttMsgObjectMsgObject.ui32Flags value when calling
// the popMsgFromBuf() and pushMsgToBuf() functions.
//
//*****************************************************************************

//
//! This indicates that a message object has no flags set.
//
#define BUF_OBJ_NO_FLAGS        0x00000000

//
//! This indicates that a pop was attempted when the buffer was empty.
//
#define BUF_OBJ_EMPTY_POP		0x00000001

//
//! This indicates a push or pop contained the wrong length for the buffer
//! object data width.  NOT CURRENTLY IMPLEMENTED
//
//#define BUF_OBJ_DIM_ERROR		0x00000002

//
//! This indicates data data was lost during a push.  This occurs if the buffer
//! was full when a push was attempted.  The oldest data is overwritten with
//! new data.
//
#define BUF_OBJ_DATA_LOST       0x00000100

//*****************************************************************************
//
//! The structure used for encapsulating all the items associated with a
//! message object.
//
//*****************************************************************************
typedef struct
{
    //
    //! The message identifier
    //
    uint32_t ui32MsgID;

    //
    //! This is a pointer to the message object's data.
    //
    uint8_t pui8MsgData[8];
}
tMsgObject;

//*****************************************************************************
//
//! The structure to represent and track contents of a buffer of messages
//
//*****************************************************************************
typedef struct
{
	//
	//! The index for the last write to the buffer.
	//
	uint64_t ui64WriteIdx;

	//
	//! The index for the last read in the buffer.
	//
	uint64_t ui64ReadIdx;

	//
	//! This value holds various status flags and settings.
	//
	uint32_t ui32Flags;

	//
	//! This value is the number of tMsgObject's in the the buffer can store.
	//
	uint64_t ui64BufferDepth;

	//
	//! This value is the width in bytes of tMsgObject's.
	//! NOT CURRENTLY IMPLEMENTED
	//
	//uint64_t ui64BufferWidth;

	//
	//! This is a pointer to the buffer object's data.
	//
	tMsgObject* psMessages;
}
tBufObject;

//*****************************************************************************
//
//! Fill data and MsgID, given the raw data
//
//*****************************************************************************
void stageMsgObject(tMsgObject* psMsgObject, uint32_t ui32MsgID,
		uint8_t* pui8MsgData, uint32_t ui32MsgLen);

//*****************************************************************************
//
//! Initialize buffer contents
//
//*****************************************************************************

extern void initMsgBuffer(tBufObject* psBuffer, tMsgObject* psMsgObject, const uint64_t ui64BufferDepth);

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************

extern uint32_t pushMsgToBuf(tBufObject* psBuffer, tMsgObject psMsgObject);
extern uint32_t popMsgFromBuf(tBufObject* psBuffer, tMsgObject* psMsgObject);
extern uint64_t getBufCount(tBufObject* psBuffer);
extern bool isBufEmpty(tBufObject* psBuffer);
extern bool isBufFull(tBufObject* psBuffer);
extern uint32_t getBufStatus(tBufObject* psBuffer);
extern void clearBufStatus(tBufObject* psBuffer);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // _BUFFER_H__
