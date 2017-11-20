#pragma once

#include "ISceneBase.h"

class ResultScene :public ISceneBase
{
public:
	ResultScene();
	~ResultScene();
	void Init();
	SCENE Update();
	void Render();
	void Exit();
private:
	void ReadTexture();
};
