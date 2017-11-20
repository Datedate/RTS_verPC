#ifndef _CGAME_H_
#define _CGAME_H_

#include "ConfigSystem.h"

MY_NAMESPACE_BEGIN

class SceneManager;
class RenderManager;

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(HWND _hwnd,HINSTANCE _hInstance, bool _fullscreen,int _screenX,int _screenY);
	void Exec();
	void Exit();
	void SetEndFlag();
	bool IsEnd();
private:
	bool			m_endFlag;
	SceneManager*	m_sceneMng;
	RenderManager*	m_renderMng;
};

MY_NAMESPACE_END

#endif