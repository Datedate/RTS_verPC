#ifndef _SPRITE_BASE_H_
#define _SPRITE_BASE_H_

#include "Object.h"

MY_NAMESPACE_BEGIN

class SpriteBase:public Object
{
public:
	SpriteBase();
	~SpriteBase();
	bool Init();
private:

};

MY_NAMESPACE_END

#endif
