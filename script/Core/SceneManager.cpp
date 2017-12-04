#include "SceneManager.h"
#include "../PrototypeScene/PrototypeScene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(float _sizeWidth,float _sizeHeight) {		
//	m_scenes.push_back(new TitleScene());

	m_currentscene = PrototypeScene::Create();
}

void SceneManager::Update() {
	// シーン遷移
	NextScene();
	// シーン更新
	m_currentscene->Update();
}

void SceneManager::Exit() {
	// シーン終了
	/*
	for (unsigned  int i = 0;i < m_scenes.size();++i) {
		m_scenes[i]->Exit();
	}*/
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
	// フェード
	m_nextscene = _scene;
}

void SceneManager::PushScene(SceneBase* _scene) {
	//if (IsScene(_scene)) return;

	//m_scenes.push_back(NewScene(_scene));
}

void SceneManager::PopScene() {
	/*
	std::vector<ISceneBase*>::iterator itr = m_scenes.begin();
	(*itr)->Exit();
	itr = m_scenes.erase(itr);
	*/
}

Size SceneManager::GetDisplaySize()const {
	return m_displaySize;
}

void SceneManager::NextScene() {
	if (m_nextscene != nullptr) {
		delete m_currentscene;
		m_currentscene = m_nextscene;
		m_nextscene = nullptr;
	}
}