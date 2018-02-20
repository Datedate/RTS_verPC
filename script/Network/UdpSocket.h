#ifndef _UDP_SOCKET__H__
#define _UDP_SOCKET__H__

#include "wsock32error.h"
//#include <WinSock2.h>
//#pragma comment (lib, "wsock32.lib")

#define DEFAULT_PORT 2222

class UdpSocket
{
public:
	UdpSocket();
	~UdpSocket();
	bool Create();
	void Open(int _port);
	void Open(const char* _ip , int _port);
	void SetData(sockaddr_in _myAddr, sockaddr_in _destinationAddr);
	bool Bind();
	int Send(void* _data,int _size);
	bool Receive(void* _data , int _size);
	void Close();

	sockaddr_in GetMyAddr() const;
	sockaddr_in GetDestinationAddr() const;
private:
	SOCKET	m_sock;					// ソケット
	sockaddr_in	m_myAddr;			// 自分のアドレス
	sockaddr_in m_destinationAddr;	// 相手のアドレス
};

#endif
