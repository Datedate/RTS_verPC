#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "../Core/SceneBase.h"

class MenuMainLayer;

class MenuScene :public SceneBase
{
public:
	MenuScene();
	~MenuScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(MenuScene);
private:
	MenuMainLayer*	m_mainLayer;
};

#endif