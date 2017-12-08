#include "SpriteBase.h"
#include "RenderManager.h"

const int SpriteBase::VERTEX_NUM = 4;

SpriteBase::SpriteBase() {
	m_tex = nullptr;
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
	m_rect.setRect(0, 0, 100, 100);
	m_tu = m_tv = 0.0f;
	m_tuWidth = m_tvHeight = 1.0f;
	m_tex = NULL;
	m_drawFlag = true;

	m_color[0] = 255.0f;
	m_color[1] = 255.0f;
	m_color[2] = 255.0f;
	m_color[3] = 255.0f;

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
LPDIRECT3DTEXTURE9 SpriteBase::GetTexture()const {
	return m_tex;
}

void SpriteBase::Draw() {
	auto Render = RenderManager::GetInstance();
	Render->PushDraw(this);
}