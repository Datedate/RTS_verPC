#include "SceneManager.h"
#include "../PrototypeScene/PrototypeScene.h"
#include "../TitleScene/TitleScene.h"
#include "../MenuScene/MenuScene.h"
#include "../TutorialScene/TutorialScene.h"
#include "../DeckScene/DeckScene.h"
#include "../LobbyScene/LobbyScene.h"
#include "../BattleScene/battleScene.h"
#include "../ParticleOperation/ParticleOperationScene.h"
#include "ScheduleManager.h"
#include "RenderManager.h"

#define DEBUG_MODE 0

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(float _sizeWidth,float _sizeHeight) {		
#ifdef DEBUG_MODE 
	m_currentscene = TitleScene::Create();
#else
	m_currentscene = ParticleOperationScene::Create();
#endif
}

void SceneManager::Update() {
	// �V�[���J��
	NextScene();
}

void SceneManager::Exit() {
	// �V�[���I��
	if (m_currentscene != nullptr) {
		m_currentscene->Release();
		m_currentscene = nullptr;
	}
}

void SceneManager::ChengeScene(SCENE s) {
	// �t�F�[�h
	m_next = s;
}


void SceneManager::NextScene() {
	if (m_next != NONE) {
		// �V�[�����ɃZ�b�g�����X�P�W���[�������
		ScheduleManager::GetInstance()->ReleaseAll();
		RenderManager::GetInstance()->ClearCurrentLayer();

		m_currentscene->Exit();
		delete m_currentscene;

		switch (m_next)
		{
		case TITLE:
			m_currentscene = TitleScene::Create();
			break;
		case MENU:
			m_currentscene = MenuScene::Create();
			break;
		case TUTORIAL:
			m_currentscene = TutorialScene::Create();
			break;
		case DECK:
			m_currentscene = DeckScene::Create();
			break;
		case LOBBY:
			m_currentscene = LobbyScene::Create();
			break;
		case BATTLE:
			m_currentscene = BattleScene::Create();
			break;
		case DEBUG:
			m_currentscene = ParticleOperationScene::Create();
			break;
		default:
			break;
		}
		m_next = SCENE::NONE;
	}
}