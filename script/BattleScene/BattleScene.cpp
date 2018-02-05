#include "BattleScene.h"

BattleScene::BattleScene() {

}

bool BattleScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	return true;
}

void BattleScene::Exit() {
	//	m_mainLayer->Release();
	//	delete m_mainLayer;
}

BattleScene::~BattleScene() {

}