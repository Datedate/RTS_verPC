#include "MenuScene.h"
#include "MenuMainLayer.h"

MenuScene::MenuScene() {
	m_mainLayer = nullptr;
}

bool MenuScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_mainLayer = MenuMainLayer::Create();

	this->AddChild(m_mainLayer, 0);

	return true;
}

void MenuScene::Exit() {
	m_mainLayer->Release();
	delete m_mainLayer;
}

MenuScene::~MenuScene() {
	Exit();
}