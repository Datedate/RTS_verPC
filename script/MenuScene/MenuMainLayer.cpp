#include "MenuMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../../resource3.h"
#include "../Core/RenderManager.h"
#include "../Core/ParticleSystem.h"
#include "../Core/GameDataManager.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventManager.h"
#include "../Core/SceneManager.h"
#include "../Core/ScheduleManager.h"
#include "../Core/DebugSystem.h"
#include <iostream>
#include <sstream>

#define PI 3.14159265

MenuMainLayer::MenuMainLayer() {
	m_backGround	= nullptr;
	m_particleField = nullptr;
	m_battleLogo	= nullptr;
	m_tutorialLogo	= nullptr;
	m_deckLogo		= nullptr;
	m_arrow[0]		= nullptr;
	m_arrow[1]		= nullptr;

	m_particleRadius = 50.0f;
	m_particleAngle = 0.0f;
}

bool MenuMainLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}

	m_backGround	= SpriteBase::Create();
	m_backGround2	= SpriteBase::Create();
	m_particleField = SpriteBase::Create();
	m_tutorialLogo  = SpriteBase::Create();
	m_battleLogo	= SpriteBase::Create();
	m_deckLogo		= SpriteBase::Create();
	m_arrow[0]		= SpriteBase::Create();
	m_arrow[1]		= SpriteBase::Create();

	m_backGround->CreateTex("Menu/menuBack.png");
	m_backGround2->CreateTex("Menu/menuBack.png");
	m_particleField->CreateTex("Menu/particleFieldBack.png");
	m_tutorialLogo->CreateTex("Menu/tutorialLogo.png");
	m_battleLogo->CreateTex("Menu/battleLogo.png");
	m_deckLogo->CreateTex("Menu/deckLogo.png");
	m_arrow[0]->CreateTex("Menu/yazirusi.png");
	m_arrow[1]->CreateTex("Menu/yazirusi.png");

	m_backGround->SetEffectID(FXID_EFFECT);
	m_backGround2->SetEffectID(FXID_EFFECT);
	m_particleField->SetEffectID(FXID_EFFECT);
	m_tutorialLogo->SetEffectID(FXID_EFFECT);
	m_battleLogo->SetEffectID(FXID_EFFECT);
	m_deckLogo->SetEffectID(FXID_EFFECT);
	m_arrow[0]->SetEffectID(FXID_EFFECT);
	m_arrow[1]->SetEffectID(FXID_EFFECT);

	float displayWidth  = RenderManager::GetInstance()->GetDisplaySize().width;
	float displayHeight = RenderManager::GetInstance()->GetDisplaySize().height;

	m_backGround->SetSize(displayWidth, displayHeight);
	m_backGround->SetPos(displayWidth / 2.0f, displayHeight / 2.0f);

	m_backGround2->SetSize(displayWidth, displayHeight / 2.0f + 18);
	m_backGround2->SetPos(displayWidth / 2.0f, displayHeight / 2.0f + 200);

	m_particleField->SetSize(displayWidth , 350.0f);
	m_particleField->SetPos(displayWidth / 2.0f, 300.0f);

	m_tutorialLogo->SetSize(420, 150);
	m_tutorialLogo->SetPos(displayWidth / 2.0f, 600);

	m_deckLogo->SetSize(420, 150);
	m_deckLogo->SetPos(displayWidth / 2.0f, 750);

	m_battleLogo->SetSize(420, 150);
	m_battleLogo->SetPos(displayWidth / 2.0f, 900);

	m_arrow[0]->SetSize(50, 50);
	m_arrow[0]->SetPos(displayWidth / 8.0f, 300.0f);
	m_arrow[0]->SetUVScaler(0.25f, 0.5f);

	m_arrow[1]->SetSize(50, 50);
	m_arrow[1]->SetPos((displayWidth / 8.0f)*7.0f, 300.0f);
	m_arrow[1]->SetUVScaler(0.25f, 0.5f);
	m_arrow[1]->SetAngle(180.0f);

	this->AddChild(m_backGround,0);
	this->AddChild(m_backGround2, 3);
	this->AddChild(m_particleField,1);
	this->AddChild(m_tutorialLogo,4);
	this->AddChild(m_battleLogo,5);
	this->AddChild(m_deckLogo,6);
	this->AddChild(m_arrow[0],7);
	this->AddChild(m_arrow[1],8);


	// デッキ　パーティクルの設定
	auto dataMng = GameDataManager::GetInstance();
	dataMng->LoadDeck();
	for (int i = 0;i < DECK_NUM;++i) {
		m_partSysContainer.push_back(ParticleSystem::Create());
		m_partSysContainer[i]->Load(dataMng->GetParticleFilePath(i));
		m_partSysContainer[i]->SetPos(displayWidth / 2.0f, 300.0f);
		m_partSysContainer[i]->SetScale(0.6f, 0.6f);
		this->AddChild(m_partSysContainer[i],2);
	}
	m_id = 0;
	m_partSysContainer[m_id]->StartSimulation();

	// イベント設定
	EventMouseListener* rightButton = EventMouseListener::Create();
	rightButton->m_onMouseDown = [this](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			m_partSysContainer[m_id]->StopSimulation();
			m_id++;
			m_id = m_id % DECK_NUM;
			m_partSysContainer[m_id]->StartSimulation();
		}
	};
	
	EventMouseListener* leftButton = EventMouseListener::Create();
	leftButton->m_onMouseDown = [this](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());

		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			m_partSysContainer[m_id]->StopSimulation();
			m_id--;
			m_id = (m_id + DECK_NUM) % DECK_NUM;
			m_partSysContainer[m_id]->StartSimulation();
		}
	};

	EventMouseListener* tutorialButton = EventMouseListener::Create();
	tutorialButton->m_onMouseDown = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());

		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChengeScene(SCENE::TUTORIAL);
		}
	};

	EventMouseListener* deckButton = EventMouseListener::Create();
	deckButton->m_onMouseDown = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());

		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChengeScene(SCENE::DECK);
		}
	};

	EventMouseListener* lobbyButton = EventMouseListener::Create();
	lobbyButton->m_onMouseDown = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());

		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChengeScene(SCENE::LOBBY);
		}
	};

	EventManager::GetInstance()->AddEvent(rightButton, m_arrow[1]);
	EventManager::GetInstance()->AddEvent(leftButton, m_arrow[0]);
	EventManager::GetInstance()->AddEvent(tutorialButton, m_tutorialLogo);
	EventManager::GetInstance()->AddEvent(deckButton, m_deckLogo);
	EventManager::GetInstance()->AddEvent(lobbyButton, m_battleLogo);

	SET_UPDATE(MenuMainLayer);

	return true;
}

void MenuMainLayer::Update() {
	
	m_particleAngle += 10.0f;
	if (m_particleAngle > 360)
		m_particleAngle = 0.0f;

	float x = cosf(m_particleAngle * (PI / 180.0f)) * m_particleRadius + RenderManager::GetInstance()->GetDisplaySize().width/2.0;
	float y = sinf(m_particleAngle * (PI / 180.0f)) * m_particleRadius + 300.0f;

	std::string buff = "座標 x:";
	buff += std::to_string(x);
	buff += " y:";
	buff += std::to_string(y);
	DebugSystem::GetInstance()->Push(buff,0,0);

	m_partSysContainer[m_id]->SetPos(x, y);
}

void MenuMainLayer::Exit() {
	
	EventManager::GetInstance()->Clear();

	m_backGround->Release();
	m_backGround2->Release();
	m_particleField->Release();
	m_battleLogo->Release();
	m_tutorialLogo->Release();
	m_deckLogo->Release();
	m_arrow[0]->Release();
	m_arrow[1]->Release();

	delete m_backGround;
	m_backGround = nullptr;
	delete m_backGround2;
	m_backGround2 = nullptr;
	delete m_particleField;
	m_particleField = nullptr;
	delete m_battleLogo;
	m_battleLogo = nullptr;
	delete m_tutorialLogo;
	m_tutorialLogo = nullptr;
	delete m_deckLogo;
	m_deckLogo = nullptr;
	delete m_arrow[0];
	delete m_arrow[1];
	m_arrow[0] = nullptr;
	m_arrow[1] = nullptr;

	for (ParticleSystem* pa : m_partSysContainer) {
		pa->StopSimulation();
		pa->Exit();
		delete pa;
	}
	m_partSysContainer.clear();
}

MenuMainLayer::~MenuMainLayer() {
	Exit();
}