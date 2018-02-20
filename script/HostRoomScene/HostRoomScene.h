#ifndef _HOST_ROOM_SCENE_H_
#define _HOST_ROOM_SCENE_H_

#include "../Core/SceneBase.h"

class HostRoomMainLayer;

class HostRoomScene : public SceneBase
{
public:
	HostRoomScene();
	~HostRoomScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(HostRoomScene);
private:
	HostRoomMainLayer* m_mainLayer;
};

#endif