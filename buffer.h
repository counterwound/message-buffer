//*****************************************************************************
//
// buffer.h - Defines and Macros for the BUFFER controller.
//
// Copyright (c) 2015 Sevun Scientific, Inc..  All rights reserved.
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
//   Neither the name of Sevun Scientific, Inc. nor the names of
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

//*****************************************************************************
//
// Miscellaneous defines for Buffer status
//
//*****************************************************************************

//*****************************************************************************
//
// These are the flags used by the tUARTMsgObject.ui32Flags value when calling
// the UARTMessageSet() and UARTMessageGet() functions.
//
//*****************************************************************************

//
//! This indicates that a message object has no flags set.
//
#define BUF_OBJ_NO_FLAGS        0x00000000

//
//! This indicates that data was lost since this message object was last
//! read.
//
#define BUF_OBJ_DATA_LOST       0x00000100

//*****************************************************************************
//
//! The structure used for encapsulating all the items associated with a
//! message object
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
    uint8_t ui8MsgData[8];
}
tMsgObject;

//*****************************************************************************
//
//! The structure used for encapsulating all the items associated with Buffer
//! object
//
//*****************************************************************************
typedef struct
{
    //
    //! The read index
    //
    uint32_t ui32BufRead;

    //
	//! The write index
	//
	uint32_t ui32BufWrite;

	//
	//! This value is the number of message objects in the buffer.
	//
	uint32_t ui32BufLen;

    //
    //! This value holds various status flags and settings specified by
    //! tMsgObject.
    //
    uint32_t ui32Flags;

    //
    //! This is a pointer to the message object's data.
    //
	tMsgObject *sMsgObject;
}
tBufObject;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void BufferPush(tBufObject sBufObject, tMsgObject *sMsgObject);
extern void BufferPull(tBufObject sBufObject, tMsgObject *sMsgObject);
extern bool BufferIsEmpty(tBufObject sBufObject);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // _BUFFER_H__
