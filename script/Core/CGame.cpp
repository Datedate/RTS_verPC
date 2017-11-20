#include "CGame.h"
#include "input.h"
#include "SceneManager.h"
#include "RenderManager.h"

MY_NAMESPACE_BEGIN

CGame::CGame()
{
	
}

CGame::~CGame()
{
}

bool CGame::Init(HWND _hwnd, HINSTANCE _hInstance, bool _fullscreen, int _screenX, int _screenY) {
	m_sceneMng = SceneManager::GetInstance();
	m_renderMng = RenderManager::GetInstance();

	// ���̓f�o�C�X������
	if (FAILED(InitInput(_hInstance, _hwnd)))
		return FALSE;
	// �`��N���X�̏�����
	if (!m_renderMng->Init(_hwnd, _fullscreen, _screenX, _screenY))
		return FALSE;
	// �V�[���}�l�[�W���[�̏�����
	m_sceneMng->InitScene();
	return true;
}

void CGame::Exec() {
	UpdateInput();
	m_sceneMng->Update();
	m_renderMng->Render();
}

void CGame::Exit() {
	m_sceneMng->Exit();
	m_renderMng->Exit();
	UninitInput();
}

void CGame::SetEndFlag() {
	m_endFlag = true;
}

bool CGame::IsEnd() {
	return m_endFlag;
}

MY_NAMESPACE_END