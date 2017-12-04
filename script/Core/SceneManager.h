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
	void PushScene(SceneBase* _scene);
	void PopScene();
	Size GetDisplaySize()const;
private:
	void NextScene();
	SceneManager();
	~SceneManager();
private:
	//std::vector<SceneBase*> m_scenes;
	SceneBase*				m_currentscene;
	SceneBase*				m_nextscene;
	Size					m_displaySize;
};

#endif

