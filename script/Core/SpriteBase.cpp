#include "SpriteBase.h"
#include "RenderManager.h"

SpriteBase::SpriteBase() {
}
SpriteBase::SpriteBase(std::string _name) {
	auto device = RenderManager::GetInstance()->GetDevice();
	if (FAILED((D3DXCreateTextureFromFile(device, _name.c_str(), &m_tex))) ){
		MessageBox(NULL, "Failed : load Texture", _name.c_str() , MB_OK);
	}
}
SpriteBase::~SpriteBase() {

}

SpriteBase*	SpriteBase::Create() {
	SpriteBase* ptr = new SpriteBase();
	if (ptr && ptr->Init()) {
		return ptr;
	}
	else {
		delete ptr;
		ptr = nullptr;
		return 	nullptr;
	}
}

SpriteBase*	SpriteBase::Create(std::string _name) {
	SpriteBase* ptr = new SpriteBase(_name);
	if (ptr && ptr->Init()) {
		return ptr;
	}
	else {
		delete ptr;
		ptr = nullptr;
		return 	nullptr;
	}
}

bool SpriteBase::Init() {
	m_rect = Rect(0, 0, 100, 100);
	m_tu = m_tv = 0.0f;
	m_tuWidth = m_tvHeight = 1.0f;
	m_tex = NULL;
	m_drawFlag = true;

	return true;
}

void SpriteBase::Update() {
	
}

void SpriteBase::SetDrawFlag(bool _flag) {
	m_drawFlag = _flag;
}

bool SpriteBase::IsDrawFlag() {
	return m_drawFlag;
}

float SpriteBase::getMinTU() {
	return m_tu;
}
float SpriteBase::getMinTV() {
	return m_tv;
}
float SpriteBase::getMaxTU() {
	return m_tu + m_tuWidth;
}
float SpriteBase::getMaxTV() {
	return m_tv + m_tvHeight;
}

void SpriteBase::Draw() {
	auto Render = RenderManager::GetInstance();
	Render->PushDraw(this);
}