#ifndef _CLIENT_ROOM_SCENE_H_
#define _CLIENT_ROOM_SCENE_H_

#include "../Core/SceneBase.h"

class ClientRoomMainLayer;

class ClientRoomScene : public SceneBase
{
public:
	ClientRoomScene();
	~ClientRoomScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(ClientRoomScene);
private:
	ClientRoomMainLayer* m_mainLayer;
};

#endif