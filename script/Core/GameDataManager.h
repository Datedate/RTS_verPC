#ifndef _GAMEDATA_MANAGER_H_
#define _GAMEDATA_MANAGER_H_

#include "SingletonTemplate.h"
#include <string>

#define DECK_NUM 5

class GameDataManager : public SingletonTemplate<GameDataManager>
{
public:
	friend SingletonTemplate<GameDataManager>;
	
	void LoadDeck();
	std::string GetParticleFilePath(int num);
private:
	GameDataManager();
	~GameDataManager();
private :
	int				m_deckID[DECK_NUM];
	std::string		m_deckFileName[DECK_NUM];
};



#endif