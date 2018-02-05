#ifndef _TITLE_LAYER_H_
#define _TITLE_LAYER_H_

#include "../Core/LayerBase.h"

class SpriteBase;

class TitleLayer : public LayerBase
{
public:
	TitleLayer();
	~TitleLayer();
	bool Init();
	void Exit();
	CREATE_FUNC(TitleLayer);
	void CalcTimer();
private:
	SpriteBase* m_backGround;
	SpriteBase* m_titleLogo;
	SpriteBase* m_clickMessage;
};
#endif