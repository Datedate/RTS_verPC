#include "SceneManager.h"
#include "../PrototypeScene/PrototypeScene.h"
#include "../ParticleOperation/ParticleOperationScene.h"
#include "ScheduleManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(float _sizeWidth,float _sizeHeight) {		
	m_currentscene = ParticleOperationScene::Create();
}

void SceneManager::Update() {
	// �V�[���J��
	NextScene();
}

void SceneManager::Exit() {
	// �V�[���I��
	if (m_nextscene != nullptr) {
		m_nextscene->Release();
		m_nextscene = nullptr;
	}
	if (m_currentscene != nullptr) {
		m_currentscene->Release();
		m_currentscene = nullptr;
	}
}

void SceneManager::ChengeScene(SceneBase* _scene) {
	// �t�F�[�h
	m_nextscene = _scene;
}


void SceneManager::NextScene() {
	if (m_nextscene != nullptr) {
		// �V�[�����ɃZ�b�g�����X�P�W���[�������
		ScheduleManager::GetInstance()->ReleaseAll();

		delete m_currentscene;
		m_currentscene = m_nextscene;
		m_nextscene = nullptr;
	}
}