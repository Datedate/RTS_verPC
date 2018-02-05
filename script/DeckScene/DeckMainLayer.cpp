#include "DeckMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/RenderManager.h"
#include "../Core/ParticleSystem.h"
#include "../Core/GameDataManager.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventManager.h"
#include "../Core/SceneManager.h"]
#include "../Core/ScheduleManager.h"
#include "../../resource3.h"

DeckMainLayer::DeckMainLayer() {
	m_backGround   = nullptr;
	
	for (SpriteBase* deck : m_deck) {
		deck = nullptr;
	}

	m_paramField   = nullptr;
	m_changeButton = nullptr;
	m_moveButton   = nullptr;

	m_particleContainer.clear();
}

bool DeckMainLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}
	
	// 画像の初期化
	for (int i = 0;i < DECK_NUM;++i) {
		m_deck[i]  = SpriteBase::Create();
		m_deck[i]->CreateTex("Deck/bar2.png");
		m_deck[i]->SetEffectID(FXID_EFFECT);
	}
	m_backGround   = SpriteBase::Create();
	m_paramField   = SpriteBase::Create();
	m_changeButton = SpriteBase::Create();
	m_moveButton   = SpriteBase::Create();
	m_backButton   = SpriteBase::Create();

	m_backGround->CreateTex("Deck/menuBack.png");
	m_paramField->CreateTex("Deck/paramBar.png");
	m_changeButton->CreateTex("Deck/button_template.png");
	m_moveButton->CreateTex("Deck/button_template.png");
	m_backButton->CreateTex("Deck/backButton_02.png");

	m_backGround->SetEffectID(FXID_EFFECT);
	m_paramField->SetEffectID(FXID_EFFECT);
	m_changeButton->SetEffectID(FXID_EFFECT);
	m_moveButton->SetEffectID(FXID_EFFECT);
	m_backButton->SetEffectID(FXID_EFFECT);

	float displayWidth  = RenderManager::GetInstance()->GetDisplaySize().width;
	float displayHeight = RenderManager::GetInstance()->GetDisplaySize().height;

	m_backGround->SetSize(displayWidth, displayHeight);
	m_backGround->SetPos(displayWidth / 2.0f, displayHeight / 2.0f);

	m_paramField->SetSize(displayWidth/2.0f + 100.0f, 200);
	m_paramField->SetPos(displayWidth / 2.0f - 50.0f, displayHeight - 300.0f);

	m_changeButton->SetSize(100, 100);
	m_changeButton->SetPos(displayWidth / 2.0f + 250.0f, displayHeight - 350.0f);

	m_moveButton->SetSize(100, 100);
	m_moveButton->SetPos(displayWidth / 2.0f + 250.0f, displayHeight - 250.0f);

	m_backButton->SetSize(150, 150);
	m_backButton->SetPos(100, displayHeight - 100);
	m_backButton->SetUVScaler(0.5f, 1.0f);


	for (int i = 0;i < DECK_NUM-1;++i) {
		float x = 150 + 350 * (i % 2);
		float y = 150 + 225 * (i / 2);
		std::string deckName = "Deck_";

		m_deck[i]->SetSize(200, 200);
		m_deck[i]->SetPos(x, y);
		
		deckName += std::to_string(i);

		// 名前： "Deck_0 , Deck_1 ..."
		m_deck[i]->SetName(deckName);
		this->AddChild(m_deck[i],10+i);
	}
	m_deck[DECK_NUM - 1]->SetSize(200, 200);
	m_deck[DECK_NUM - 1]->SetPos(displayWidth / 2.0f, 600);
	this->AddChild(m_deck[DECK_NUM - 1],14);

	this->AddChild(m_backGround,   0);
	this->AddChild(m_paramField,   1);
	this->AddChild(m_changeButton, 2);
	this->AddChild(m_moveButton,   3);
	this->AddChild(m_backButton,   4);

	// コトダマの初期化
	auto dataMng = GameDataManager::GetInstance();
	dataMng->LoadDeck();
	for (int i = 0;i < DECK_NUM-1;++i) {
		float x = 150 + 350 * (i % 2);
		float y = 150 + 225 * (i / 2);

		m_particleContainer.push_back(ParticleSystem::Create());
		m_particleContainer[i]->Load(dataMng->GetParticleFilePath(i));
		m_particleContainer[i]->SetPos(x, y);
		m_particleContainer[i]->SetScale(0.5f, 0.5f);
		m_particleContainer[i]->StartSimulation();
		this->AddChild(m_particleContainer[i], 20 + i);
	}
	m_particleContainer.push_back(ParticleSystem::Create());
	m_particleContainer[DECK_NUM - 1]->Load(dataMng->GetParticleFilePath(DECK_NUM - 1));
	m_particleContainer[DECK_NUM - 1]->SetPos(displayWidth/2.0f,580);
	m_particleContainer[DECK_NUM - 1]->SetScale(0.5f, 0.5f);
	m_particleContainer[DECK_NUM - 1]->StartSimulation();
	this->AddChild(m_particleContainer[DECK_NUM - 1],24);

	// 戻るボタンをクリックしたとき
	EventMouseListener* clickBackButton = EventMouseListener::Create();
	clickBackButton->m_onMouseDown = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			target->SetAnimCnt(1);
		}
	};

	// 戻るボタンから離れたとき
	EventMouseListener* releaseBackButton = EventMouseListener::Create();
	releaseBackButton->m_onMouseUp = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		target->SetAnimCnt(0);
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChengeScene(SCENE::MENU);
		}
	};

	EventManager::GetInstance()->AddEvent(clickBackButton , m_backButton);
	EventManager::GetInstance()->AddEvent(releaseBackButton, m_backButton);

	// Todo : それぞれコトダマがクリックされたときパラメータ表示
	EventMouseListener* clickParticleButton[DECK_NUM];
	for (int i = 0;i < DECK_NUM;++i) {
		clickParticleButton[i] = EventMouseListener::Create();
		clickParticleButton[i]->m_onMouseDown = [this](EventMouseInfo* info) {
			auto target = static_cast<SpriteBase*>(info->GetTarget());
			if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
				// Todo:パラメータ表示　もしくは　ＩＤ　セット
				//if(target->GetName() == "Deck_0")
				//else if(target->GetName() == "Deck_1")
				//else if(target->GetName() == "Deck_2")
				//else if (target->GetName() == "Deck_3")
				//else if (target->GetName() == "Deck_4")
			}
		};
		EventManager::GetInstance()->AddEvent(clickParticleButton[i], m_deck[i]);
	}

	// Todo: パーティクル変更ボタンがクリックされたら
	EventMouseListener* clickChangeButton = EventMouseListener::Create();
	clickChangeButton->m_onMouseDown = [](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			// Todo : 変更時処理
		}
	};

	EventManager::GetInstance()->AddEvent(clickChangeButton, m_changeButton);

	SET_UPDATE(DeckMainLayer);

	return true;
}

void DeckMainLayer::Update() {

}

void DeckMainLayer::Exit() {

	// 終了処理

	EventManager::GetInstance()->Clear();

	for (SpriteBase* deck : m_deck) {
		deck->Release();
		delete deck;
	}

	m_backGround->Release();
	m_paramField->Release();
	m_changeButton->Release();
	m_moveButton->Release();

	for (ParticleSystem* pa : m_particleContainer) {
		pa->StopSimulation();
		pa->Exit();
		delete pa;
		pa = nullptr;
	}
}

DeckMainLayer::~DeckMainLayer() {
	Exit();
}