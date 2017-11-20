#pragma once

#include "SceneManager.h"
#include "CGraphics.h"


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
	SceneManager	m_sceneMng;
	CGraphics		m_graphics;
};
