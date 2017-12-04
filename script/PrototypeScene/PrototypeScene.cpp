#include "PrototypeScene.h"
#include "PrototypeMainLayer.h"

bool PrototypeScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_protoMainLayer = PrototypeMainLayer::Create();
	m_protoMainLayer->SetSize(m_size);

	this->AddChild(m_protoMainLayer,0);
	return true;
}

void PrototypeScene::Update() {

}