#include "UdpSocket.h"

UdpSocket::UdpSocket()
{
	m_sock = INVALID_SOCKET;
}

bool UdpSocket::Create() {
	WSADATA wsaData;

	int sts = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (sts == SOCKET_ERROR) {
		errcom(WSAGetLastError());
		return false;
	}

	m_sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (m_sock == INVALID_SOCKET) {
		MessageBox(NULL, "ソケット作成失敗", "ソケット作成失敗", 0);
		return false;
	}
	return true;
}

bool UdpSocket::Bind() {
	int sts = bind(m_sock, (sockaddr*)&m_myAddr, sizeof(sockaddr));
	if (sts == SOCKET_ERROR) {
		errcom(WSAGetLastError());
		return false;
	}
	return true;
}

void UdpSocket::Open(int _port) {
	m_myAddr.sin_family = AF_INET;
	m_myAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_myAddr.sin_port = htons(_port);
}

void UdpSocket::Open(const char* _ip, int _port) {
	m_myAddr.sin_family = AF_INET;
//	m_myAddr.sin_addr.S_un.S_addr = inet_addr(_ip);
//	InetPton(m_myAddr.sin_family, _ip, &m_myAddr.sin_addr.S_un.S_addr);
	m_myAddr.sin_port = htons(_port);
}

void UdpSocket::SetData(sockaddr_in _myAddr, sockaddr_in _destinationAddr) {
	m_myAddr          = _myAddr;
	m_destinationAddr = _destinationAddr;
}

int UdpSocket::Send(void* _data, int _size) {
	int addrSize = sizeof(sockaddr);
	int sts = sendto(m_sock, (char*)_data, _size, 0, (sockaddr*)&m_destinationAddr, addrSize);

	if (sts == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool UdpSocket::Receive(void* _data, int _size) {
	int addrSize = sizeof(sockaddr);
	int sts = recvfrom(m_sock, (char*)_data, _size, 0, (sockaddr*)&m_destinationAddr, &addrSize);

	if (sts == SOCKET_ERROR) {
		//errcom(WSAGetLastError());
		return false;
	}
	return true;
}

void UdpSocket::Close() {

}

sockaddr_in UdpSocket::GetMyAddr() const {
	return m_myAddr;
}

sockaddr_in UdpSocket::GetDestinationAddr() const {
	return m_destinationAddr;
}

UdpSocket::~UdpSocket()
{
}
