#ifndef _TUTORIAL_SCENE_H_
#define _TUTORIAL_SCENE_H_

#include "../Core/SceneBase.h"

class TutorialMainLayer;

class TutorialScene :public SceneBase
{
public:
	TutorialScene();
	~TutorialScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(TutorialScene);
private:
	TutorialMainLayer* m_mainLayer;
};

#endif