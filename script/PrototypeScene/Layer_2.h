#ifndef _PROTOTYPE_MAIN_LAYER2_H_
#define _PROTOTYPE_MAIN_LAYER2_H_

#include "../Core/LayerBase.h"

class SpriteBase;

class Layer_2 : public  LayerBase
{
public:
	Layer_2::Layer_2() {}
	Layer_2::~Layer_2() {}

	bool Init();
	CREATE_FUNC(Layer_2);
	void Update();
private:
	SpriteBase* m_sprite;
	bool		m_fadeFlag;
	float		scaleX, scaleY;
};

#endif
