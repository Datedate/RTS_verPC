#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "../Core/SceneBase.h"

class TitleLayer;

class TitleScene:public SceneBase
{
public:
	TitleScene() ;
	~TitleScene();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(TitleScene);
private:
	TitleLayer* m_mainLayer;
};

#endif