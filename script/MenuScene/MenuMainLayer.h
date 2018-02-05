#ifndef _MENU_MAIN_LAYER_H_
#define _MENU_MAIN_LAYER_H_

#include "../Core/LayerBase.h"

class SpriteBase;
class ParticleSystem;

class MenuMainLayer : public LayerBase
{
public:
	MenuMainLayer();
	~MenuMainLayer();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(MenuMainLayer);
private:
	SpriteBase* m_backGround;
	SpriteBase* m_backGround2;
	SpriteBase* m_particleField;
	SpriteBase* m_battleLogo;
	SpriteBase* m_tutorialLogo;
	SpriteBase* m_deckLogo;
	SpriteBase* m_arrow[2];

	float		m_particleRadius;
	float		m_particleAngle;

	// イベント処理時に参照するメンバ変数
public:
	std::vector<ParticleSystem*> m_partSysContainer;
	int			m_id;
};

#endif