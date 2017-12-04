#ifndef _PROTOTYPE_SCENE_H_
#define _PROTOTYPE_SCENE_H_

#include "../Core/SceneBase.h"

class PrototypeMainLayer;

class PrototypeScene :public SceneBase
{
public:
	PrototypeScene() {};
	~PrototypeScene() {};
	bool Init();
	void Update();
	CREATE_FUNC(PrototypeScene);
private:
	PrototypeMainLayer* m_protoMainLayer;;
};

#endif

