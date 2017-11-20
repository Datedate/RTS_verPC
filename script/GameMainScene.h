#pragma once

#include "ISceneBase.h"
#include "IGameMainFase.h"
#include "Player.h"
#include <memory>

const int HANDCARD_MAX = 4;
const int PLAYER_NUM = 2;

struct GameMainCommonData {

	Player						player[PLAYER_NUM];			// �v���C���[���
	std::shared_ptr<Card>		handCard[HANDCARD_MAX*2];		// ��D�J�[�h
	int							turn;						// �^�[����
	bool						firstPlayer, nowPlayer;		// ��U�v���C���[,���݃v���C���[�itrue = �v���C���[�P�j
	bool						endFlag;					// �o�g���I���t���O
};

class GameMainScene :public ISceneBase
{
public:
	// ------ �����o�֐��i�I�[�o�[���C�h�j ------
	GameMainScene();
	~GameMainScene();
	void Init();
	SCENE Update();
	void Render();
	void Exit();
private:
	void ReadTexture() {};
private:
	// ------ �����o�ϐ� �i�t�F�C�Y�����j------
	// �֐��|�C���^�i�t�F�C�Y���̍X�V�֐��j
	/*
	FASE (GameMainScene::*PhaseUpdate)();	

	// �t�F�C�Y�X�V�֐��Q
	FASE SetUpdate();
	FASE SelectUpdate();
	FASE ActivateUpdate();
	FASE ResultUpdate();

	// �֐��|�C���^�i�t�F�C�Y���̕`��֐��j
	void (GameMainScene::*PhaseRender)();

	// �t�F�C�Y�`��֐��Q
	void SetDraw();
	void SelectDraw();
	void ActivateDraw();
	void ResultDraw();
	*/

private:
	// ------ �����o�ϐ� ------
	std::shared_ptr<GameMainCommonData>	m_commonData;			// �Q�[�����C���V�[�����̋��ʃf�[�^
	IGameMainFase::FASE					m_fase;					// ���݂̃t�F�[�Y
	std::shared_ptr<IGameMainFase>		m_faseObjPtr;			// �t�F�C�Y�I�u�W�F�N�g
};
