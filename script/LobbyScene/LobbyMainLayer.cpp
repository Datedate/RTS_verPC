#include "LobbyMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/SceneManager.h"
#include "../Core/RenderManager.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventManager.h"
#include "../Core/SceneManager.h"
#include "../../resource3.h"
LobbyMainLayer::LobbyMainLayer()
{
	m_hostButton = nullptr;
	m_waitButton = nullptr;
}

bool LobbyMainLayer::Init() {
	if (!(LayerBase::Init())) {
		return false;
	}

	m_backGround = SpriteBase::Create();
	m_hostButton = SpriteBase::Create();
	m_waitButton = SpriteBase::Create();

	m_backGround->CreateTex("Lobby/backGround.png");
	m_hostButton->CreateTex("Lobby/hostButton.png");
	m_waitButton->CreateTex("Lobby/clientButton.png");

	m_hostButton->SetUVScaler(0.5f, 1.0f);
	m_waitButton->SetUVScaler(0.5f, 1.0f);

	m_backGround->SetEffectID(FXID_EFFECT);
	m_hostButton->SetEffectID(FXID_EFFECT);
	m_waitButton->SetEffectID(FXID_EFFECT);

	float displayWidth  = RenderManager::GetInstance()->GetDisplaySize().width;
	float displayHeight = RenderManager::GetInstance()->GetDisplaySize().height;

	m_backGround->SetSize(displayWidth, displayHeight);
	m_hostButton->SetSize(300, 200);
	m_waitButton->SetSize(300, 200);

	m_backGround->SetPos(displayWidth / 2.0f, displayHeight / 2.0f);
	m_hostButton->SetPos(displayWidth / 2.0f, displayHeight / 2.0f - 200);
	m_waitButton->SetPos(displayWidth / 2.0f, displayHeight / 2.0f + 200);

	this->AddChild(m_backGround, 0);
	this->AddChild(m_hostButton, 1);
	this->AddChild(m_waitButton, 2);

	// ホストになるボタン
	EventMouseListener* hostEve = EventMouseListener::Create();
	hostEve->m_onMouseDown = [this](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			m_hostButton->SetAnimCnt(1);
		}
	};
	hostEve->m_onMouseUp = [this](EventMouseInfo* info) {
		m_hostButton->SetAnimCnt(0);

		auto target = static_cast<SpriteBase*>(info->GetTarget());
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChangeScene(SCENE::HOST_ROOM);
		}
	};

	// ホストに接続するボタン
	EventMouseListener* waitEve = EventMouseListener::Create();
	waitEve->m_onMouseDown = [this](EventMouseInfo* info) {
		auto target = static_cast<SpriteBase*>(info->GetTarget());
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			m_waitButton->SetAnimCnt(1);
		}
	};
	waitEve->m_onMouseUp = [this](EventMouseInfo* info) {
		m_waitButton->SetAnimCnt(0);

		auto target = static_cast<SpriteBase*>(info->GetTarget());
		if (target->InRange(info->GetPosition().x, info->GetPosition().y)) {
			SceneManager::GetInstance()->ChangeScene(SCENE::CLIENT_ROOM);
		}
	};

	EventManager::GetInstance()->AddEvent(hostEve, m_hostButton);
	EventManager::GetInstance()->AddEvent(waitEve, m_waitButton);

	return true;
}

void LobbyMainLayer::Update() {

}

void LobbyMainLayer::Exit() {

	EventManager::GetInstance()->Clear();

	m_backGround->Release();
	m_hostButton->Release();
	m_waitButton->Release();

	delete m_backGround;
	delete m_hostButton;
	delete m_waitButton;
}

LobbyMainLayer::~LobbyMainLayer()
{
	Exit();
}