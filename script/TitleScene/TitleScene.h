#pragma once

#include "ISceneBase.h"

class TitleScene:public ISceneBase
{
public:
	TitleScene() {};
	~TitleScene() {};
	void Init();
	void Update();
	void Render();
	void Exit();
};

