#include "LobbyScene.h"
#include "LobbyMainLayer.h"
LobbyScene::LobbyScene() {

}

bool LobbyScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_mainLayer = LobbyMainLayer::Create();

	this->AddChild(m_mainLayer, 0);

	return true;
}

void LobbyScene::Exit() {
	m_mainLayer->Release();
	delete m_mainLayer;
}

LobbyScene::~LobbyScene() {
	Exit();
}