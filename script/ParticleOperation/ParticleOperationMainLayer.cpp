#include "ParticleOperationMainLayer.h"
#include "../Core/EventKeyInfo.h"
#include "../Core/EventKeyListener.h"
#include "../Core/EventManager.h"
#include "../Core/ParticleSystem.h"
#include "../Core/InputManager.h"
#include "../Core/TextureManager.h"
#include "../Core/Object.h"
#include "../Core/SceneManager.h"

ParticleOperationMainLayer::ParticleOperationMainLayer() {
	m_particleSystem = nullptr;
}

bool ParticleOperationMainLayer::Init() {
	if (!LayerBase::Init())
		return false;

	m_particleSystem = ParticleSystem::Create();
	m_particleSystem->Load("ParticleData/test.json");
  	EventKeyListener* listener = EventKeyListener::Create();
	listener->m_onKeyDown = [](EventKeyInfo* _eventKey) {
		SceneManager::GetInstance()->ChengeScene(SCENE::DEBUG);
	};

	EventKeyListener* listener2 = EventKeyListener::Create();
	listener2->m_onKeyDown = [](EventKeyInfo* _eventKey) {
		ParticleSystem* target = static_cast<ParticleSystem*>(_eventKey->GetTarget());
		if (target->isSimulation()) {
			target->StopSimulation();
		}
		else {
			target->StartSimulation();
		}
	};

	EventManager::GetInstance()->AddKeyEvent(listener, m_particleSystem, KEY_D);
	EventManager::GetInstance()->AddKeyEvent(listener2, m_particleSystem, KEY_SPACE);

	this->AddChild(m_particleSystem);

	return true;
}

ParticleOperationMainLayer::~ParticleOperationMainLayer() {
	// Todoテクスチャ解放
	//

	delete m_particleSystem;
}