#include "LayerBase.h"

bool LayerBase::Init() {
	return true;
}

void LayerBase::SetSize(Size _size) {
	m_size = _size;
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