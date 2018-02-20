#include "HostRoomScene.h"
#include "HostRoomMainLayer.h"


HostRoomScene::HostRoomScene()
{
}

bool HostRoomScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_mainLayer = HostRoomMainLayer::Create();

	this->AddChild(m_mainLayer, 0);

	return true;
}

void HostRoomScene::Update() {

}

void HostRoomScene::Exit() {
	m_mainLayer->Release();
	delete m_mainLayer;
}

HostRoomScene::~HostRoomScene()
{
	Exit();
}