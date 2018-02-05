#include "GameDataManager.h"
#include <fstream>
#include <Windows.h>

GameDataManager::GameDataManager()
{
}

GameDataManager::~GameDataManager()
{
}

void GameDataManager::LoadDeck() {
	// ���[�J���f�[�^�̃f�b�L��ID�擾
	std::ifstream ifs("MyData/DeckID.txt");
	if (ifs.fail()) {
		MessageBox(NULL, "MyData/DeckID.txt�擾�Ɏ��s", "", 0);
		return;
	}

	std::string buff;
	while (std::getline(ifs,buff))
	{
		sscanf_s(buff.data(), "%d,%d,%d,%d,%d"
			, &m_deckID[0], &m_deckID[1], &m_deckID[2], &m_deckID[3], &m_deckID[4]);

	}

	ifs.close();

	std::string path = "ParticleData/particle_";
	
	// ID����p�[�e�B�N���̃f�[�^�p�X���擾
	for (int i = 0;i < DECK_NUM;++i) {
		if (m_deckID[i] / 10 != 0) {
			// ��
			m_deckFileName[i] = path + std::to_string(m_deckID[i]) + ".json";
		}
		else {
			//�ꌅ
			m_deckFileName[i] = path + "0" + std::to_string(m_deckID[i]) + ".json";
		}
	}
}

std::string GameDataManager::GetParticleFilePath(int num) {
	return m_deckFileName[num];
}