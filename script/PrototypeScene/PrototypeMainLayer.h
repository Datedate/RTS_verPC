#ifndef _PROTOTYPE_MAIN_LAYER_H_
#define _PROTOTYPE_MAIN_LAYER_H_

#include "../Core/LayerBase.h"

class SpriteBase;

class PrototypeMainLayer : public  LayerBase
{
public:
	PrototypeMainLayer::PrototypeMainLayer(){}
	PrototypeMainLayer::~PrototypeMainLayer() {}

	bool Init();
	CREATE_FUNC(PrototypeMainLayer);
private:
	SpriteBase* m_sprite;
	bool		m_fadeFlag;
};

#endif
