#include "PrototypeMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/RenderManager.h"
#include "../Core/ShaderManager.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventManager.h"
#include "../Core/ScheduleManager.h"
#include "../../resource3.h"
#include "../Core/ScheduleInfo.h"

bool PrototypeMainLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}
	scaleX = scaleY = 2;

	m_sprite = SpriteBase::Create();
	auto sp = SpriteBase::Create();
	m_sprite->CreateTex("particle_01.png");
	sp->CreateTex("particle_01.png");
	m_sprite->SetName("spriteTest");
	//m_sprite->UVCut(0.2, 0.2, 0.7, 0.7);
	//m_sprite->SetAlpha(1);
	m_sprite->Trans(500,200);
	sp->Trans(500, 400);
	//m_sprite->Scale(1, 1);
	//m_sprite->Rotation(90);
	m_sprite->SetEffectID(FXID_EFFECT);
	sp->SetEffectID(FXID_EFFECT);

	this->AddChild(m_sprite);
	this->AddChild(sp);

	EventMouseListener* listener2 = EventMouseListener::Create();
	listener2->m_onMouseDown = [](EventMouseInfo* _eventMouse) {
		SpriteBase* target = static_cast<SpriteBase*>(_eventMouse->GetTarget());
		target->Move(_eventMouse->GetPosition().x,_eventMouse->GetPosition().y);
	};

	// Update�o�^
	//SET_UPDATE(PrototypeMainLayer);
	
	SET_SCHEDULE_M3(PrototypeMainLayer::Update,4,2,5);

	EventManager::GetInstance()->AddEvent(listener2,m_sprite);
	return true;
}

void PrototypeMainLayer::Update() {
	m_sprite->Scale(scaleX, scaleY);
	scaleX+= 0.5;
	scaleY+= 0.5;
}