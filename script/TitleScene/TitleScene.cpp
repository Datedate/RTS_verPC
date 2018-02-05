#include "TitleScene.h"
#include "TitleLayer.h"
TitleScene::TitleScene() {
	m_mainLayer = nullptr;
}

bool TitleScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_mainLayer = TitleLayer::Create();

	this->AddChild(m_mainLayer,0);

	return true;
}

void TitleScene::Update() {

}


void TitleScene::Exit() {
	m_mainLayer->Release();
	delete m_mainLayer;
}

TitleScene::~TitleScene() {
	Exit();
}