#include "LobbyMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/SceneManager.h"

LobbyMainLayer::LobbyMainLayer()
{
}

bool LobbyMainLayer::Init() {
	if (!(LayerBase::Init())) {
		return false;
	}

	
	return true;
}

void LobbyMainLayer::Update() {

}

void LobbyMainLayer::Exit() {

}

LobbyMainLayer::~LobbyMainLayer()
{
	Exit();
}