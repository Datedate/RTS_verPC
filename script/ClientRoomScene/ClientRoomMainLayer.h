#ifndef _CLIENT_ROOM_MAIN_LAYER_H_
#define _CLIENT_ROOM_MAIN_LAYER_H_

#include "../Core/LayerBase.h"
//#include <thread>

class SpriteBase;
class UdpSocket;

class ClientRoomMainLayer : public LayerBase
{
public:
	ClientRoomMainLayer();
	~ClientRoomMainLayer();
	bool Init();
	void Update();
	void Exit();
	void ClientRecv();
	CREATE_FUNC(ClientRoomMainLayer);
private:
	SpriteBase* m_backGround;
	SpriteBase* m_headerMessage;
	SpriteBase* m_nameInput;
	SpriteBase* m_matchButton;
	SpriteBase* m_cancelButton;
	UdpSocket*  m_udpSocket;

public:
	//std::thread m_recvThread;
	bool		m_recvThreadFlag;
	bool		m_isnextSceneFlag;
};

#endif