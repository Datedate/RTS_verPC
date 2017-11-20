#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "SingletonTemplate.h"

#include <memory>
#include <vector>

MY_NAMESPACE_BEGIN

class SceneBase;

class SceneManager:public SingletonTemplate<SceneManager>
{
public:
	friend SingletonTemplate<SceneManager>;

	void InitScene();
	void Update();
	void Exit();
	void ChengeScene(SceneBase* _scene);
	void PushScene(SceneBase* _scene);
	void PopScene();
private:
	void NextScene();
	SceneManager();
	~SceneManager();
private:
	//std::vector<SceneBase*> m_scenes;
	SceneBase*				m_currentscene;
	SceneBase*				m_nextscene;
};

MY_NAMESPACE_END

#endif

