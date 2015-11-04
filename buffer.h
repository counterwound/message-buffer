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

#include <stdbool.h>
#include <stdint.h>

#define kBufferOverflow		-11
#define kBufferUnderflow 	-12

//*****************************************************************************
//
//! The structure used for encapsulating all the items associated with a UART
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
    uint8_t pui8MsgData[8];
}
tMsgObject;

//*****************************************************************************
//
//! Fill data and MsgID, given the raw data
//
//*****************************************************************************

void populateMsgObject(tMsgObject* msgObj, uint32_t msgID, uint8_t* msgData, uint32_t len);

//*****************************************************************************
//
//! The structure to represent and track contents of a buffer of messages
//
//*****************************************************************************

typedef struct
{
    uint64_t writeIdx;
    uint64_t readIdx;
    uint64_t bufSz;
    int8_t bufStatus;
    tMsgObject* msgBuf;
}
tMsgBuffer;

//*****************************************************************************
//
//! Initialize buffer contents
//
//*****************************************************************************

extern void initMsgBuffer(tMsgBuffer* msgBuf, tMsgObject* bufData, const uint64_t bufSz);

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************

extern void pushMsgToBuf(tMsgObject msg, tMsgBuffer* buf);
extern tMsgObject popMsgFromBuf(tMsgBuffer* buf);
extern uint64_t getBufCount(tMsgBuffer* buf);
extern bool isBufEmpty(tMsgBuffer* buf);
extern bool isBufFull(tMsgBuffer* buf);
extern int8_t getBufStatus(tMsgBuffer* buf);
extern void clearBufStatus(tMsgBuffer* buf);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // _BUFFER_H__
