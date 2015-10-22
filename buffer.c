//*****************************************************************************
//
// buffer.c - Driver for the Buffer module.
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

//*****************************************************************************
//
//! \addtogroup umsg_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "buffer.h"

void populateMsgObject(tMsgObject* msgObj, uint32_t msgID, uint8_t* msgData, uint32_t len)
{
	uint32_t i;

	msgObj->ui32MsgID = msgID;
	for(i = 0; i < len; i++)
	{
		msgObj->pui8MsgData[i] = msgData[i];
	}
}

void initMsgBuffer(tMsgBuffer* msgBuf, tMsgObject* bufData, const uint64_t bufSz)
{
	msgBuf->writeIdx = 0;
	msgBuf->readIdx = 0;
	msgBuf->bufSz = bufSz;
	msgBuf->msgBuf = bufData;
}

void pushMsgToBuf(tMsgObject msg, tMsgBuffer* buf)
{
	// TODO: need logic here to make sure we didn't overwrite unread data
	// TODO!!!

	// push the data into an offset based on the actual size of the buffer
	buf->msgBuf[buf->writeIdx++ % buf->bufSz] = msg;
}

tMsgObject popMsgFromBuf(tMsgBuffer* buf)
{
	// TODO: need logic here to make sure we don't read past current writeIdx (and would be getting stale data)
	// TODO!!!

	// pop data from an offset based on the actual size of the buffer
	return buf->msgBuf[buf->readIdx++ % buf->bufSz];
}

extern uint64_t getBufCount(tMsgBuffer* buf)
{
	// NOTE: overwrite checking logic called for in pushMsgToBuf()
	// NOTE: will allow this to be a straight subtraction, because
	// NOTE: these two indices should never be farther apart than bufSz
	return (buf->writeIdx - buf->readIdx);
}

bool isBufEmpty(tMsgBuffer* buf)
{
	uint64_t tempCount = getBufCount(buf);
	return 0 == tempCount;
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
