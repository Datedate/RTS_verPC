#include "CGame.h"
#include "input.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

bool CGame::Init(HWND _hwnd, HINSTANCE _hInstance, bool _fullscreen, int _screenX, int _screenY) {
	// 入力デバイス初期化
	if (FAILED(InitInput(_hInstance, _hwnd)))
		return FALSE;
	// 描画クラスの初期化
	if (!m_graphics.Init(_hwnd, _fullscreen, _screenX, _screenY))
		return FALSE;
	// シーンマネージャーの初期化
	m_sceneMng.InitScene();
	return true;
}

void CGame::Exec() {
	UpdateInput();
	m_sceneMng.Update();
	m_sceneMng.Render();
}

void CGame::Exit() {
	m_sceneMng.Exit();
	m_graphics.Exit();
	UninitInput();
}

void CGame::SetEndFlag() {
	m_endFlag = true;
}

bool CGame::IsEnd() {
	return m_endFlag;
}
