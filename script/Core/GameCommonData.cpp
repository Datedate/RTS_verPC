#include "GameCommonData.h"
#include "../Network/UdpSocket.h"

GameCommonData::GameCommonData()
{
	m_isHostFlag = false;
	m_udpSocket  = nullptr;
}

void GameCommonData::SetConnectData(bool _isFlag, UdpSocket* _sock) {
	m_isHostFlag = _isFlag;
	m_udpSocket = new UdpSocket();
	m_udpSocket->SetData(_sock->GetMyAddr(),_sock->GetDestinationAddr());
}

GameCommonData::~GameCommonData()
{
}