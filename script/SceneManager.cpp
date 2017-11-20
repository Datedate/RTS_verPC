#include "SceneManager.h"

#include "TitleScene.h"
#include "LoginScene.h"
#include "RankingScene.h"
#include "TypeSelectScene.h"
#include "GameMainScene.h"
#include "ResultScene.h"

#include "RenderDevice.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::InitScene() {		
	InitRenderState();
	m_sceneNextType = SCENE::NOT;
	m_scenes.push_back(new TitleScene());
}

void SceneManager::Update() {
	// �V�[���J��
	NextScene();
	// �V�[���X�V
	for (unsigned int i = 0;i < m_scenes.size();++i) {
		m_sceneNextType = m_scenes[i]->Update();
	}
}

void SceneManager::Render() {
	// �^�[�Q�b�g�o�b�t�@�̃N���A�A�y�o�b�t�@�̃N���A
	RenderDevice::Get()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	RenderDevice::Get()->BeginScene();			// �`��̊J�n���c�h�q�d�b�s�w�ɒʒm
	RenderDevice::Get()->SetFVF(MY_FVF);
	// �V�[���`��
	for (unsigned  int i = 0;i < m_scenes.size();++i) {
		m_scenes[i]->Render();
	}

	RenderDevice::Get()->EndScene();	// �`��̏I����҂�
	RenderDevice::Get()->Present(NULL, NULL, NULL, NULL);	// �o�b�N�o�b�t�@����v���C�}���o�b�t�@�֓]��
}

void SceneManager::Exit() {
	// �V�[���I��
	for (unsigned  int i = 0;i < m_scenes.size();++i) {
		m_scenes[i]->Exit();
	}
}

void SceneManager::ChengeScene(SCENE _scene) {
	// �t�F�[�h
	m_sceneNextType = _scene;
}

void SceneManager::PushScene(SCENE _scene) {
	if (IsScene(_scene)) return;

	m_scenes.push_back(NewScene(_scene));
}

void SceneManager::PopScene() {
	std::vector<ISceneBase*>::iterator itr = m_scenes.begin();
	(*itr)->Exit();
	itr = m_scenes.erase(itr);
}

bool SceneManager::IsScene(SCENE _scene) {
	for (unsigned  int i = 0; i < m_scenes.size(); i++)
	{
		bool flag = m_scenes[i]->GetScene() == _scene ? true : false;
		if (flag) return true;
	}
	return false;
}


void SceneManager::InitRenderState() {
	RenderDevice::Get()->SetRenderState(D3DRS_ZENABLE, TRUE);
	//�����L����
	RenderDevice::Get()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	RenderDevice::Get()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	RenderDevice::Get()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	RenderDevice::Get()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	RenderDevice::Get()->LightEnable(0, FALSE);

	m_renderState = SceneManager::RENDER_STATE::NOT;
}

void SceneManager::NextScene() {
	if (m_sceneNextType != SCENE::NOT) {
		delete m_scenes[0];
		m_scenes[0] = NewScene(m_sceneNextType);
		m_sceneNextType = SCENE::NOT;
	}
}

void SceneManager::SetRanderState(SceneManager::RENDER_STATE _state = NOT) {
	if (m_renderState == _state || _state == SceneManager::RENDER_STATE::NOT) return;

	m_renderState = _state;

	//�����L����
	switch (m_renderState)
	{
	case SceneManager::RENDER_STATE::ALPHA:
		RenderDevice::Get()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		break;
	case SceneManager::RENDER_STATE::NORMAL:
		RenderDevice::Get()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		break;
	default:
		break;
	}
	
}

ISceneBase* SceneManager::NewScene(SCENE _scene) {
	switch (_scene)
	{
	case SCENE::TITLE:
		return new TitleScene();
	case SCENE::LOGIN:
		return new LoginScene();
	case SCENE::RANKING:
		return new RankingScene();
	case SCENE::SELECT:
		return new TypeSelectScene();
	case SCENE::GAME_MAIN:
		return new GameMainScene();
	case SCENE::RESULT:
		return new ResultScene();
	default:
		break;
	}
	return nullptr;
}