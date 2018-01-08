#include "SceneBase.h"
#include "RenderManager.h"
#include "LayerBase.h"
bool SceneBase::Init() {
	m_objType = ObjectType::SCENE;
	m_size = RenderManager::GetInstance()->GetDisplaySize();
	m_debugFlag = false;
	return true;
}

void SceneBase::AddChild(LayerBase* _child, unsigned int _order) {
	Object::AddChild(_child,_order);

	_child->SetSize(m_size);

}

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

void SceneBase::OnDebugMode() {
	m_debugFlag = true;
}
void SceneBase::OffDebugMode() {
	m_debugFlag = false;
}