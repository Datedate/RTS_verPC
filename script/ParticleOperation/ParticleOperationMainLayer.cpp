#include "ParticleOperationMainLayer.h"
#include "../Core/EventKeyInfo.h"
#include "../Core/EventKeyListener.h"
#include "../Core/EventManager.h"
#include "../Core/ParticleSystem.h"
#include "../Core/InputManager.h"
bool ParticleOperationMainLayer::Init() {
	if (!LayerBase::Init())
		return false;

	m_particleSystem = ParticleSystem::Create();
	m_particleSystem->Load("ParticleData/test.json");

	EventKeyListener* listener = EventKeyListener::Create();
	listener->m_onKeyDown = [](EventKeyInfo* _eventKey) {
		ParticleSystem* target = static_cast<ParticleSystem*>(_eventKey->GetTarget());
		target->StartSimulation();
	};

	EventManager::GetInstance()->AddKeyEvent(listener, m_particleSystem, KEY_D);
	this->AddChild(m_particleSystem);

	return true;
}