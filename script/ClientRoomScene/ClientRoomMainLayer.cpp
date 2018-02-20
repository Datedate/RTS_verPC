#include "ClientRoomMainLayer.h"
#include "../Core/SpriteBase.h"
#include "../Core/SceneManager.h"
#include "../Core/ScheduleManager.h"
#include "../Core/RenderManager.h"
#include "../Core/EventMouseInfo.h"
#include "../Core/EventMouseListener.h"
#include "../Core/EventManager.h"
#include "../../resource3.h"
//#include "../Network/UdpSocket.h"
//#include "../Network/SendMessageStruct.h"
//#include "../Network/RecvMessageStruct.h"

ClientRoomMainLayer::ClientRoomMainLayer()
{
	m_backGround = nullptr;
	m_headerMessage = nullptr;
	m_nameInput = nullptr;
	m_matchButton = nullptr;
	m_cancelButton = nullptr;
	m_recvThreadFlag = false;
	m_isnextSceneFlag = false;
}

bool ClientRoomMainLayer::Init() {
	if (!LayerBase::Init()) {
		return false;
	}

	m_backGround = SpriteBase::Create();
	m_headerMessage = SpriteBase::Create();
	m_nameInput = SpriteBase::Create();
	m_matchButton = SpriteBase::Create();
	m_cancelButton = SpriteBase::Create();

	m_backGround->SetEffectID(FXID_EFFECT);
	m_headerMessage->SetEffectID(FXID_EFFECT);
	m_nameInput->SetEffectID(FXID_EFFECT);
	m_matchButton->SetEffectID(FXID_EFFECT);
	m_cancelButton->SetEffectID(FXID_EFFECT);

	m_backGround->CreateTex("HostRoom/backGround.png");
	m_headerMessage->CreateTex("HostRoom/");
	m_nameInput->CreateTex("HostRoom/");
	m_matchButton->CreateTex("HostRoom/");
	m_cancelButton->CreateTex("HostRoom/");

	float displayWidth = RenderManager::GetInstance()->GetDisplaySize().width;
	float displayHeight = RenderManager::GetInstance()->GetDisplaySize().height;

	m_backGround->SetSize(displayWidth, displayHeight);
	m_headerMessage->SetSize(500, 200);
	m_nameInput->SetSize(400, 200);
	m_matchButton->SetSize(150, 150);
	m_cancelButton->SetSize(150, 150);

	m_backGround->SetPos(displayWidth / 2.0f, displayHeight / 2.0f);
	m_headerMessage->SetPos(displayWidth / 2.0f, 200);
	m_nameInput->SetPos(displayWidth / 2.0f, 350);
	m_matchButton->SetPos(displayWidth / 4.0f, displayHeight / 2.0f + 300);
	m_cancelButton->SetPos(displayWidth - displayWidth / 4.0f, displayHeight / 2.0f + 300);

	this->AddChild(m_backGround, 0);
	this->AddChild(m_headerMessage, 1);
	this->AddChild(m_nameInput, 2);
	this->AddChild(m_matchButton, 3);
	this->AddChild(m_cancelButton, 4);

	// イベント処理
	// マッチングボタン
	EventMouseListener* matchClick = EventMouseListener::Create();
	matchClick->m_onMouseDown = [](EventMouseInfo* _info) {
		auto target = static_cast<SpriteBase*>(_info->GetTarget());
		if (target->InRange(_info->GetPosition().x, _info->GetPosition().y)) {

		}
	};
	matchClick->m_onMouseUp = [this](EventMouseInfo* _info) {
		auto target = static_cast<SpriteBase*>(_info->GetTarget());
		if (target->InRange(_info->GetPosition().x, _info->GetPosition().y)) {

			if (m_recvThreadFlag) {
				// キャンセル
				//if (m_recvThread.joinable()) {
				//	m_recvThread.join();
				//	m_recvThreadFlag = false;
				//}
			}
			else {
				// マッチング
				//m_recvThread = std::thread(&ClientRoomMainLayer::ClientRecv, this);
				//m_recvThreadFlag = true;
			}
		}
	};

	// キャンセルボタン
	EventMouseListener* cancelClick = EventMouseListener::Create();
	cancelClick->m_onMouseDown = [](EventMouseInfo* _info) {
		auto target = static_cast<SpriteBase*>(_info->GetTarget());
		if (target->InRange(_info->GetPosition().x, _info->GetPosition().y)) {

		}
	};
	cancelClick->m_onMouseUp = [](EventMouseInfo* _info) {
		auto target = static_cast<SpriteBase*>(_info->GetTarget());
		if (target->InRange(_info->GetPosition().x, _info->GetPosition().y)) {

		}
	};

	EventManager::GetInstance()->AddEvent(matchClick, m_matchButton);
	EventManager::GetInstance()->AddEvent(cancelClick, m_cancelButton);

	SET_UPDATE(ClientRoomMainLayer);

	return true;
}

void ClientRoomMainLayer::Exit() {
	m_backGround->Release();
	m_headerMessage->Release();
	m_nameInput->Release();
	m_matchButton->Release();
	m_cancelButton->Release();

	delete m_backGround;
	delete m_headerMessage;
	delete m_nameInput;
	delete m_matchButton;
	delete m_cancelButton;

	if (m_recvThreadFlag) {
		//if (m_recvThread.joinable()) {
		//	m_recvThread.join();
		//}
	}

	m_recvThreadFlag = false;
	m_isnextSceneFlag = false;

	EventManager::GetInstance()->Clear();
	ScheduleManager::GetInstance()->ReleaseAll();
}

void ClientRoomMainLayer::Update() {
	if (!m_isnextSceneFlag) {
		SceneManager::GetInstance()->ChangeScene(SCENE::BATTLE);
	}
}

void ClientRoomMainLayer::ClientRecv() {
	/*
	m_udpSocket = new UdpSocket();

	m_udpSocket->Create();
	m_udpSocket->Open(DEFAULT_PORT);
	//m_udpSocket->Bind();

	RecvMessageData recvData;
	recvData.info.header = RecvDataMode::CONNECT;
	SendMessageData sendData;

	// 受信スレッド
	while (m_recvThreadFlag) {
		if (!m_udpSocket->Receive(recvData.data, sizeof(RecvMessageData))) {
			m_recvThreadFlag = false;
			break;
		}
		else {
			switch (recvData.info.header)
			{
			case RecvDataMode::CONNECT:
				sendData.info.header = SendDataMode::CONNECT;
				m_recvThreadFlag = false;
				return;
			default:
				break;
			}
		}
	}
	*/
}


ClientRoomMainLayer::~ClientRoomMainLayer()
{
	Exit();
}
