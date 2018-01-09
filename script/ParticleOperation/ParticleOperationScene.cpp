#include "ParticleOperationScene.h"
#include "ParticleOperationMainLayer.h"
#include "ParticleOperationUILayer.h"

bool ParticleOperationScene::Init() {
	if (!SceneBase::Init()) {
		return false;
	}

	m_particleMainLayer = ParticleOperationMainLayer::Create();
	m_particleMainLayer->SetSize(m_size);

	//m_particleUILayer = ParticleOperationUILayer::Create();
	//m_particleUILayer->SetSize(m_size);

	this->AddChild(m_particleMainLayer, 0);
	//this->AddChild(m_particleUILayer, 1);

	return true;
}

void ParticleOperationScene::Update() {

}