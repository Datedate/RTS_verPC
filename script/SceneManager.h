#pragma once

#include "ISceneBase.h"
#include <memory>
#include <vector>

class SceneManager
{
	enum RENDER_STATE
	{
		NOT,
		NORMAL,
		ALPHA
	};
public:
	SceneManager();
	~SceneManager();
	void InitScene();
	void Update();
	void Render();
	void Exit();
	void ChengeScene(SCENE _scene);
	void PushScene(SCENE _scene);
	void PopScene();
	bool IsScene(SCENE _scene);
private:
	void InitRenderState();
	void NextScene();
	void SetRanderState(RENDER_STATE _state);
	ISceneBase* NewScene(SCENE _scene);
private:
	SCENE					 m_sceneNextType;
	std::vector<ISceneBase*> m_scenes;
	RENDER_STATE			 m_renderState;
};

