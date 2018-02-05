#ifndef _BATTLE_SCENE_H_
#define _BATTLE_SCENE_H_

#include "../Core/SceneBase.h"

class BattleMainLayer;

class BattleScene :public SceneBase
{
public:
	BattleScene();
	~BattleScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(BattleScene);
private:
	BattleMainLayer* m_mainLayer;
};

#endif