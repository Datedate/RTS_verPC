#ifndef _SEND_MESSAGE_STRUCT_H_
#define _SEND_MESSAGE_STRUCT_H_

enum SendDataMode {
	SEND_CONNECT,
	SEND_NUM_MAX
};

struct SendMessageInfo
{
	SendDataMode	header;
	int				seqNo;
};

struct SendMessageData
{
	union
	{
		SendMessageInfo info;
		char data[sizeof(SendMessageInfo)];
	};
};

#endif
