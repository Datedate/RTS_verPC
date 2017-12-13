#include "PrototypeMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/RenderManager.h"
#include "../Core/ShaderManager.h"
#include "../../resource3.h"

bool PrototypeMainLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}

	m_sprite = SpriteBase::Create();
	m_sprite->CreateTex("particle_01.png");
	//m_sprite->UVCut(0.2, 0.2, 0.7, 0.7);
	//m_sprite->SetAlpha(1);
	m_sprite->Trans(656/2.0f,959/2.0f);
	m_sprite->Scale(10, 10);
	//m_sprite->Rotation(90);

	m_sprite->SetEffectID(FXID_EFFECT);

	return true;
}