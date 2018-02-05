#ifndef _DECK_MAIN_LAYER_H_
#define _DECK_MAIN_LAYER_H_

#include "../Core/LayerBase.h"
#include "../Core/GameDataManager.h"

class SpriteBase;
class ParticleSystem;

class DeckMainLayer : public LayerBase
{
public:
	DeckMainLayer();
	~DeckMainLayer();
	bool Init();
	void Update();
	void Exit();
	CREATE_FUNC(DeckMainLayer);
private:
	SpriteBase* m_backGround;
	SpriteBase* m_paramField;
	SpriteBase* m_changeButton;
	SpriteBase* m_moveButton;
	SpriteBase* m_backButton;
public:
	SpriteBase* m_deck[DECK_NUM];
	std::vector<ParticleSystem*> m_particleContainer;

};

#endif