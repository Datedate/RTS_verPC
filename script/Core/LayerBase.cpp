#include "LayerBase.h"
#include "SpriteBase.h"
#include "RenderManager.h"
#include "ParticleSystem.h"

bool LayerBase::Init() {
	m_objType = ObjectType::LAYER;
	RenderManager::GetInstance()->PushLayer(this);
	return true;
}

void LayerBase::RemoveAllChildren() {
	if (m_children.empty()) return;

	for (auto Obj = m_children.begin(); Obj != m_children.end();++Obj) {
		(*Obj)->RemoveAllChildren();
	}
}

void LayerBase::RemoveChild(std::string _name) {
	if (m_children.empty()) return;

	for (auto Obj = m_children.begin();Obj != m_children.end();++Obj) {
		if ((*Obj)->GetName() == _name) {
			(*Obj)->RemoveAllChildren();
		}
	}
}

void LayerBase::AddChild(SpriteBase* _sprite) {
	Object::AddChild(_sprite);
	m_isChildChange = true;
}

void LayerBase::AddChild(ParticleSystem* _particle) {
	Object::AddChild(_particle);
	m_isChildChange = true;
}

void LayerBase::SortChildren() {
	if (!m_isChildChange) return;
	// TODO : 子供（スプライトをオーダー順に並び変える）
	
	m_isChildChange = false;
}

void LayerBase::PushSpriteToRenderer() {
	if (m_children.empty()) return;
	// レイヤーに結びついてるスプライトを描画管理クラスのコンテナに格納
	for (auto sprite = m_children.begin();sprite != m_children.end();++sprite) {
		if ((*sprite)->GetType() == Object::ObjectType::SPRITE) {
			SpriteBase* sp = static_cast<SpriteBase*>(*sprite);
			RenderManager::GetInstance()->PushSprite(sp);
		}
		else if((*sprite)->GetType() == Object::ObjectType::PARTICLE){
			ParticleSystem* p = static_cast<ParticleSystem*>(*sprite);
			p->PushParticle();
		}
	}
}

void LayerBase::SetSize(Size _size) {
	m_size = _size;
}

std::vector<Object*> LayerBase::GetSpriteContainer()const {
	return m_children;
}