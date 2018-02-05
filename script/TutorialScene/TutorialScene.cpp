#include "TutorialScene.h"

TutorialScene::TutorialScene() {

}

bool TutorialScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	return true;
}

void TutorialScene::Exit() {
	//	m_mainLayer->Release();
	//	delete m_mainLayer;
}

TutorialScene::~TutorialScene() {

}