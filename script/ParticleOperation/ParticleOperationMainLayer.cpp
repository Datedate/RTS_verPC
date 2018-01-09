#include "ParticleOperationMainLayer.h"
#include "../Core/EventKeyInfo.h"
#include "../Core/EventKeyListener.h"
#include "../Core/EventManager.h"
#include "../Core/ParticleSystem.h"
bool ParticleOperationMainLayer::Init() {
	if (!LayerBase::Init())
		return false;

	m_particleSystem = ParticleSystem::Create();
	m_particleSystem->Load("ParticleData/test.json");
	this->AddChild(m_particleSystem);

	return true;
}