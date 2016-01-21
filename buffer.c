//*****************************************************************************
//
// buffer.c - Driver for the Buffer module.
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

//*****************************************************************************
//
//! \addtogroup umsg_api
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "buffer.h"

void stageMsgObject(tMsgObject* psMsgObject, uint32_t ui32MsgID, uint8_t* pui8MsgData, uint32_t ui32MsgLen)
{
	uint32_t uIdx;

	psMsgObject->ui32MsgID = ui32MsgID;
	for(uIdx = 0; uIdx < ui32MsgLen; uIdx++)
	{
		psMsgObject->pui8MsgData[uIdx] = pui8MsgData[uIdx];
	}
}

void initMsgBuffer(tBufObject* psBuffer, tMsgObject* psMessages, const uint64_t ui64BufferDepth)
{
	psBuffer->ui64WriteIdx = 0;
	psBuffer->ui64ReadIdx = 0;
	psBuffer->ui64BufferDepth = ui64BufferDepth;
	psBuffer->ui32Flags = BUF_OBJ_NO_FLAGS;
	psBuffer->psMessages = psMessages;
}

uint32_t pushMsgToBuf(tBufObject* psBuffer, tMsgObject psMsgObject)
{
	if(isBufFull(psBuffer))
	{
		// drop oldest sample by advancing read pointer...
		psBuffer->ui64ReadIdx++;

		// then, set status to overflow, in case the caller cares about this condition
		psBuffer->ui32Flags |= BUF_OBJ_DATA_LOST;
	}

	// push the data into an offset based on the actual size of the buffer
	psBuffer->psMessages[psBuffer->ui64WriteIdx % psBuffer->ui64BufferDepth] = psMsgObject;
	psBuffer->ui64WriteIdx++;
	
	if(psBuffer->ui32Flags & BUF_OBJ_EMPTY_POP)
	{
		// if the error bit for popping an empty buffer
		// was previously set, it shouldn't be any more,
		// because we just pushed a message.  since that
		// succeeded, we know that the buffer is not
		// empty now.
		psBuffer->ui32Flags &= ~(BUF_OBJ_EMPTY_POP);
	}

	return getBufStatus(psBuffer);
}

uint32_t popMsgFromBuf(tBufObject* psBuffer, tMsgObject* psMsgObject)
{
	if(isBufEmpty(psBuffer))
	{
		// nothing to drop, so just set status...
		psBuffer->ui32Flags |= BUF_OBJ_EMPTY_POP;

		// then, return empty message object
		stageMsgObject(psMsgObject, 0x00, 0x00, 0);
		return psBuffer->ui32Flags;
	}
	
	// pop data from an offset based on the actual size of the psBufferfer
	*psMsgObject = psBuffer->psMessages[psBuffer->ui64ReadIdx++ % psBuffer->ui64BufferDepth];
	
	if((psBuffer->ui32Flags & BUF_OBJ_DATA_LOST) && !(isBufFull(psBuffer)))
	{
		// if the error bit for pushing to a full
		// buffer was previously set, popping one
		// *might* have corrected that condition.
		// we can surmise here that if the buffer
		// is not full, then data will not be lost
		// on the next push, so we will just count on
		// that condition being tracked by the caller
		// when it occurs in push operations
		psBuffer->ui32Flags &= ~(BUF_OBJ_DATA_LOST);
	}

	return getBufStatus(psBuffer);
}

extern uint64_t getBufCount(tBufObject* psBuffer)
{
	return (psBuffer->ui64WriteIdx - psBuffer->ui64ReadIdx);
}

bool isBufEmpty(tBufObject* psBuffer)
{
	return (0 == getBufCount(psBuffer));
}

bool isBufFull(tBufObject* psBuffer)
{
	return (getBufCount(psBuffer) >= psBuffer->ui64BufferDepth);
}

uint32_t getBufStatus(tBufObject* psBuffer)
{
	return psBuffer->ui32Flags;
}

void clearBufStatus(tBufObject* psBuffer)
{
	psBuffer->ui32Flags = BUF_OBJ_NO_FLAGS;
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
