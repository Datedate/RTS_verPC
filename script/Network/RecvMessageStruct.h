#ifndef _RECV_MESSAGE_STRUCT_H_
#define _RECV_MESSAGE_STRUCT_H_

enum RecvDataMode {
	RECV_CONNECT,
	RECV_NUM_MAX
};

struct RecvMessageInfo
{
	RecvDataMode	header;
	int				seqNo;
};

struct RecvMessageData
{
	union 
	{
		RecvMessageInfo info;
		char data[sizeof(RecvMessageInfo)];
	};
};
#endif