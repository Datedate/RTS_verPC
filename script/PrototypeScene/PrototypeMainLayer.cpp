#include "PrototypeMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/RenderManager.h"
bool PrototypeMainLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}

	m_sprite = SpriteBase::Create();
	
	RenderManager::GetInstance()->PushDraw(m_sprite);

	return true;
}