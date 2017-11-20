#pragma once

#include "ISceneBase.h"
#include "IGameMainFase.h"
#include "Player.h"
#include <memory>

const int HANDCARD_MAX = 4;
const int PLAYER_NUM = 2;

struct GameMainCommonData {

	Player						player[PLAYER_NUM];			// プレイヤー情報
	std::shared_ptr<Card>		handCard[HANDCARD_MAX*2];		// 手札カード
	int							turn;						// ターン数
	bool						firstPlayer, nowPlayer;		// 先攻プレイヤー,現在プレイヤー（true = プレイヤー１）
	bool						endFlag;					// バトル終了フラグ
};

class GameMainScene :public ISceneBase
{
public:
	// ------ メンバ関数（オーバーライド） ------
	GameMainScene();
	~GameMainScene();
	void Init();
	SCENE Update();
	void Render();
	void Exit();
private:
	void ReadTexture() {};
private:
	// ------ メンバ変数 （フェイズ処理）------
	// 関数ポインタ（フェイズ毎の更新関数）
	/*
	FASE (GameMainScene::*PhaseUpdate)();	

	// フェイズ更新関数群
	FASE SetUpdate();
	FASE SelectUpdate();
	FASE ActivateUpdate();
	FASE ResultUpdate();

	// 関数ポインタ（フェイズ毎の描画関数）
	void (GameMainScene::*PhaseRender)();

	// フェイズ描画関数群
	void SetDraw();
	void SelectDraw();
	void ActivateDraw();
	void ResultDraw();
	*/

private:
	// ------ メンバ変数 ------
	std::shared_ptr<GameMainCommonData>	m_commonData;			// ゲームメインシーン内の共通データ
	IGameMainFase::FASE					m_fase;					// 現在のフェーズ
	std::shared_ptr<IGameMainFase>		m_faseObjPtr;			// フェイズオブジェクト
};
