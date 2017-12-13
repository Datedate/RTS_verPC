#include "SceneBase.h"
#include "RenderManager.h"
#include "LayerBase.h"

bool SceneBase::Init() {
	m_size = RenderManager::GetInstance()->GetDisplaySize();
	return true;
}
/*
void SceneBase::AddChild(Object* _child) {
	LayerBase* childLayer = static_cast<LayerBase*>(_child);
	childLayer->SetSize(m_size);

	Object::AddChild(childLayer);
}
*/
void SceneBase::RemoveAllChildren() {
	if (m_children.empty()) return;

	for (auto layer = m_children.begin();layer != m_children.end();++layer) {
		(*layer)->RemoveAllChildren();
	}

	m_children.clear();
}

void SceneBase::RemoveChild(std::string _childname) {
	if (m_children.empty()) return;

	for (auto layer = m_children.begin();layer != m_children.end();++layer) {
		if ((*layer)->GetName() == _childname) {
			(*layer)->RemoveAllChildren();
		}
	}

}