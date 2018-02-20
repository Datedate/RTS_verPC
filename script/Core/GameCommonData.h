#ifndef _GAME_COMMON_DATA_H_
#define _GAME_COMMON_DATA_H_

#include "../Core/SingletonTemplate.h"

class UdpSocket;

class GameCommonData : public SingletonTemplate<GameCommonData>
{
public:

	friend SingletonTemplate<GameCommonData>;
	void SetConnectData(bool _isFlag, UdpSocket* _sock);
private:
	GameCommonData();
	~GameCommonData();

	bool		m_isHostFlag;
	UdpSocket*  m_udpSocket;
};

#endif