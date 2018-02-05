#ifndef _LOBBY_SCENE_H_
#define _LOBBY_SCENE_H_

#include "../Core/SceneBase.h"

class LobbyMainLayer;

class LobbyScene :public SceneBase
{
public:
	LobbyScene();
	~LobbyScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(LobbyScene);
private:
	LobbyMainLayer* m_mainLayer;
};

#endif