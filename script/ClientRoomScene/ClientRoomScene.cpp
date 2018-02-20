#include "ClientRoomScene.h"
#include "ClientRoomMainLayer.h"

ClientRoomScene::ClientRoomScene()
{
}

bool ClientRoomScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_mainLayer = ClientRoomMainLayer::Create();

	this->AddChild(m_mainLayer, 0);

	return true;
}

void ClientRoomScene::Update() {

}

void ClientRoomScene::Exit() {
	m_mainLayer->Release();
	delete m_mainLayer;
}

ClientRoomScene::~ClientRoomScene()
{
	Exit();
}
