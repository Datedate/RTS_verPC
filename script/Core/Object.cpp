#include "Object.h"

MY_NAMESPACE_BEGIN

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
MY_NAMESPACE_END