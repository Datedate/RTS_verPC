#ifndef _LOBBY_MAIN_LAYER_H_
#define _LOBBY_MAIN_LAYER_H_

#include "../Core/LayerBase.h"

class SpriteBase;

class LobbyMainLayer : public LayerBase
{
public:
	LobbyMainLayer();
	~LobbyMainLayer();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(LobbyMainLayer);
private:

};

#endif