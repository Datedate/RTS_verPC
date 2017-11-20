#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

#include "Object.h"

MY_NAMESPACE_BEGIN

enum SCENE
{
	AWAKE_LOGO,
	TITLE,
	LOBBY,
	DECK_CONFIRM,
	ROOM_SELECT,
	GAME_MAIN,
	RESULT,
	RANKING,
	COUNT_MAX
};

class SceneBase :public Object
{
public:
	SceneBase() {};
	~SceneBase() {};
	static SceneBase* Create();

};

MY_NAMESPACE_END

#endif

