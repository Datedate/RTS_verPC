#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "SingletonTemplate.h"
#include "Rectangle.h"

enum SCENE {
	NONE,
	TITLE,
	MENU,
	TUTORIAL,
	DECK,
	LOBBY,
	BATTLE,
	DEBUG,
	NUM
};

class SceneBase;

class SceneManager:public SingletonTemplate<SceneManager>
{
public:
	friend SingletonTemplate<SceneManager>;

	void Init(float _sizeWidth, float _sizeHeight);
	void Update();
	void Exit();
	void ChengeScene(SCENE );
private:
	void NextScene();
	SceneManager();
	~SceneManager();
private:
	SceneBase*				m_currentscene;
	SCENE					m_next;
};

#endif

