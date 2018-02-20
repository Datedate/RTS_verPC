#ifndef __WINSOCK32_ERROR_POPUP__
#define __WINSOCK32_ERROR_POPUP__

//#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "wsock32.lib")
//#pragma comment( lib, "ws2_32.lib" )

struct errdata_t{
	int	eno;					// エラーコード
	char* errmsg;				// エラーメッセージ
};

void errcom(int errcode);

#endif

