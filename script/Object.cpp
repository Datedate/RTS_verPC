#include "Object.h"

MY_NAMESPACE_BEGIN

Object::Object() {

}

Object::~Object() {

}

void Object::AddChild(Object* _child) {
	m_children.push_back(_child);
}
Object* Object::Create()
{
	return new Object();
}

void Object::Draw() {

}

MY_NAMESPACE_END