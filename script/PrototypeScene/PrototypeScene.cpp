#include "PrototypeScene.h"
#include "PrototypeMainLayer.h"
#include "Layer_2.h"

bool PrototypeScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_protoMainLayer = PrototypeMainLayer::Create();
	m_protoMainLayer->SetSize(m_size);

	m_layer2 = Layer_2::Create();
	m_layer2->SetSize(m_size);

	this->AddChild(m_protoMainLayer,0);
	this->AddChild(m_layer2, 1);
	
	return true;
}

void PrototypeScene::Update() {

}