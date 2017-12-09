#include "Object.h"

Object::Object() {

}

Object::~Object() {

}

bool Object::Init() {
	return true;
}

Object* Object::Create()
{
	return new Object();
}

void Object::Update() {
	if (m_children.size() == 0) return;
	
	auto itr = m_children.begin();
	for (;itr != m_children.end();itr++) {
		(*itr)->Update();
	}
}

void Object::AddChild(Object* _child) {
	m_children.push_back(_child);
}

void Object::AddChild(Object* _child, int _zorder) {
	_child->SetZOrder(_zorder);
	AddChild(_child);
}

void Object::RemoveAllChildren() {}
void Object::RemoveChild() {}
void Object::RemoveChild(std::string _childname) {}
void Object::Release() {

}

void Object::SetParent(Object* _parent) {
	m_parent = _parent;
}

void Object::Exit() {
	if (m_children.size() == 0) return;

	auto itr = m_children.begin();
	for (;itr != m_children.end();itr++) {
		(*itr)->Exit();
	}

	Release();
}

Object* Object::GetParent()const {
	if (m_parent == nullptr)
		return nullptr;
	return m_parent;
}

bool Object::IsVisible()const {
	return m_visible;
}

std::string Object::GetName()const {
	return m_name;
}

int Object::GetOrder()const {
	return m_zorder;
}