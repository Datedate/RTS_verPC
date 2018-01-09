#include "ParticleOperationUILayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventManager.h"
#include "../Core/ShaderManager.h"
#include "../../resource3.h"
bool ParticleOperationUILayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}
	/*
	m_reloadFlag = false; m_startFlag = false; m_stopFlag = false;

	m_reloadButton = SpriteBase::Create();
	m_reloadButton->Trans(500, 200);
	m_reloadButton->SetEffectID(FXID_EFFECT);
	this->AddChild(m_reloadButton);

	
	EventMouseListener* listener = EventMouseListener::Create();
	listener->m_onMouseDown = [](EventMouseInfo* _eventMouse) {
		SpriteBase* target = static_cast<SpriteBase*>(_eventMouse->GetTarget());
		if(target->InRange(_eventMouse->GetPosition().x,_eventMouse->GetPosition().y))
			
	}
	*/

	return true;
}