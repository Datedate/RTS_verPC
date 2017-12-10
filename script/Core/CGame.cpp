#include "CGame.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "EventManager.h"
#include "ScheduleManager.h"
#include "FPSController.h"
#include "DebugSystem.h"

CGame::CGame()
{
	
}

CGame::~CGame()
{
}

bool CGame::Init(HWND _hwnd, HINSTANCE _hInstance, bool _fullscreen, int _screenX, int _screenY) {
	m_sceneMng = SceneManager::GetInstance();
	m_renderMng = RenderManager::GetInstance();
	m_eventMng = EventManager::GetInstance();
	m_scheduleMng = ScheduleManager::GetInstance();
	m_debugSysMng = DebugSystem::GetInstance();

	// 入力デバイス初期化
	if (!m_eventMng->Init(_hInstance,_hwnd))
		return false;
	// 描画クラスの初期化
	if (!m_renderMng->Init(_hwnd, _fullscreen, _screenX, _screenY))
		return false;
	// シーンマネージャーの初期化
	m_sceneMng->Init(_screenX,_screenY);
	m_scheduleMng->Init();
	m_debugSysMng->Init();

	return true;
}

void CGame::Exec() {
	// FPS制御
	if (m_fpsCtrl.FpsControlCheck()) {
		m_eventMng->Excute();
		m_sceneMng->Update();
		m_scheduleMng->AllUpdate();
		m_renderMng->Render();
	}
}

void CGame::Exit() {
	m_eventMng->Exit();
	m_renderMng->Exit();
	m_scheduleMng->Exit();
	m_sceneMng->Exit();
}

void CGame::SetEndFlag() {
	m_endFlag = true;
}

bool CGame::IsEnd() {
	return m_endFlag;
}