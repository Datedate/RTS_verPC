#include "TitleLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventManager.h"
#include "../Core/SceneManager.h"
#include "../MenuScene/MenuScene.h"
#include "../../resource3.h"
#include "../Core/RenderManager.h"
#include "../Core/ScheduleManager.h"
#include "../Core/ScheduleInfo.h"

TitleLayer::TitleLayer() {
	m_backGround   = nullptr;
	m_titleLogo	   = nullptr;
	m_clickMessage = nullptr;
}

bool TitleLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}

	m_backGround   = SpriteBase::Create();
	m_titleLogo    = SpriteBase::Create();
	m_clickMessage = SpriteBase::Create();

	m_backGround->CreateTex("Title/titleBack_01.png");
	m_titleLogo->CreateTex("Title/titleLogo_01.png");
	m_clickMessage->CreateTex("Title/sart.png");

	m_backGround->SetEffectID(FXID_EFFECT);
	m_titleLogo->SetEffectID(FXID_EFFECT);
	m_clickMessage->SetEffectID(FXID_EFFECT);

	float diplayWidth = RenderManager::GetInstance()->GetDisplaySize().width;
	float displayHeight = RenderManager::GetInstance()->GetDisplaySize().height;
	
	m_backGround->SetSize(diplayWidth,displayHeight);
	m_backGround->SetPos(diplayWidth / 2.0f, displayHeight / 2.0f);
	m_titleLogo->SetSize(640, 150);
	m_titleLogo->SetPos(diplayWidth/2.0f, 400);
	m_clickMessage->SetSize(300, 78);
	m_clickMessage->SetPos(diplayWidth / 2.0f, 800);

	this->AddChild(m_backGround);
	this->AddChild(m_titleLogo);
	this->AddChild(m_clickMessage);

	EventMouseListener* clickListener = EventMouseListener::Create();
	clickListener->m_onMouseDown = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChengeScene(SCENE::MENU);
		}
	};

	EventManager::GetInstance()->AddEvent(clickListener, m_clickMessage);

	// メンバ関数、実行回数、実行間隔（秒）、実行開始時間（秒）
	//SET_SCHEDULE_M3(TitleLayer::CalcTimer, 4, 2, 5);

	return true;
}

void TitleLayer::CalcTimer() {
	// SETSCHEDULE　で設定した情報を基に実行される
}

void TitleLayer::Exit() {
	
	EventManager::GetInstance()->Clear();

	m_backGround->Release();
	m_titleLogo->Release();
	m_clickMessage->Release();

	delete m_backGround;
	delete m_titleLogo;
	delete m_clickMessage;
}

TitleLayer::~TitleLayer() {
	Exit();
}