#ifndef _CGAME_H_
#define _CGAME_H_

#include "ConfigSystem.h"
#include "FPSController.h"
#include <Windows.h>

class SceneManager;
class RenderManager;
class EventManager;
class AudioManager;
class ScheduleManager;

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
	bool				m_endFlag;

	FPSContoller		m_fpsCtrl;
	SceneManager*		m_sceneMng;
	RenderManager*		m_renderMng;
	EventManager*		m_eventMng;
	AudioManager*		m_audioMng;
	ScheduleManager*	m_scheduleMng;
};

#endif