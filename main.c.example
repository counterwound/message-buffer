#include "buffer.h"
#include <stdlib.h>

#define szBufUart 8

/*
 * main.c
 */
int main(void)
{
	// data for test messages
	tMsgObject testMsg1;
	uint8_t testBuf1[] = {0,1,2,3,4,5,6,7};
	tMsgObject testMsg2;
	uint8_t testBuf2[] = {8,9,10,11,12,13,14,15};

	// data for test buffer
	tMsgObject msgFifoUart[szBufUart];
	tMsgObject poppedMsg;
	tMsgBuffer msgBufUart;
	uint64_t bufCnt;
	bool bufEmpty;

	// test populating two messages
	populateMsgObject(&testMsg1, 0xDEADBEEF, testBuf1, 8);
	populateMsgObject(&testMsg2, 0x600DF00D, testBuf2, 8);
	
	// initialize various buffer variables
	initMsgBuffer(&msgBufUart, msgFifoUart, szBufUart);

	// check if empty (should be) and count (should == 0)
	bufEmpty = isBufEmpty(&msgBufUart);
	bufCnt = getBufCount(&msgBufUart);

	// then push those messages into the buffer
	pushMsgToBuf(testMsg1, &msgBufUart);
	pushMsgToBuf(testMsg2, &msgBufUart);

	// check if empty (should not be) and count (should == 2)
	bufEmpty = isBufEmpty(&msgBufUart);
	bufCnt = getBufCount(&msgBufUart);

	// then pop the first one
	poppedMsg = popMsgFromBuf(&msgBufUart);

	// then check count (should == 1)
	bufCnt = getBufCount(&msgBufUart);

	return 0;
}
