#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

#include "Object.h"

MY_NAMESPACE_BEGIN

class SceneBase :public Object
{
public:
	SceneBase() {};
	~SceneBase() {};
	static SceneBase* Create();
};

MY_NAMESPACE_END

#endif

