#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "SingletonTemplate.h"
#include "Rectangle.h"

class SceneBase;

class SceneManager:public SingletonTemplate<SceneManager>
{
public:
	friend SingletonTemplate<SceneManager>;

	void Init(float _sizeWidth, float _sizeHeight);
	void Update();
	void Exit();
	void ChengeScene(SceneBase* _scene);
private:
	void NextScene();
	SceneManager();
	~SceneManager();
private:
	SceneBase*				m_currentscene;
	SceneBase*				m_nextscene;
};

#endif

