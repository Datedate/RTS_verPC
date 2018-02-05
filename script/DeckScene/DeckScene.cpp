#include "DeckScene.h"
#include "DeckMainLayer.h"

DeckScene::DeckScene() {

}

bool DeckScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_mainLayer = DeckMainLayer::Create();

	return true;
}

void DeckScene::Exit() {
	m_mainLayer->Release();
	delete m_mainLayer;
}

DeckScene::~DeckScene() {
	Exit();
}