#ifndef _DECK_SCENE_H_
#define _DECK_SCENE_H_

#include "../Core/SceneBase.h"

class DeckMainLayer;

class DeckScene :public SceneBase
{
public:
	DeckScene();
	~DeckScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(DeckScene);
private:
	DeckMainLayer* m_mainLayer;
};

#endif