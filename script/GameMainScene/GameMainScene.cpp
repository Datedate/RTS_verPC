#include "GameMainScene.h"
#include "input.h"
#include <time.h>
#include "GameMainSelectFase.h"
#include "GameMainActivateFase.h"
#include "GameMainResultFase.h"

// lua組み込み
#include "../lua/lua.hpp"

GameMainScene::GameMainScene()
{
	Init();
}
GameMainScene::~GameMainScene() = default;

void GameMainScene::Init() {
	srand(unsigned int(time(NULL)));
	m_commonData.reset(new GameMainCommonData());
	// プレイヤーの初期ステータスをセット
	for (int i = 0; i < PLAYER_NUM; ++i) {
		m_commonData->player[i].SetStatsu(CommonData::type[i]);
	}
	// 先攻・後攻をランダムで決定
	m_commonData->player[0].DecisionPlayFirst(static_cast<bool>(rand() % 2));
	m_commonData->player[1].DecisionPlayFirst(!m_commonData->player[0].GetOrder());

	m_commonData->endFlag = false;
	m_commonData->turn = 1;

	// 初期フェイズの設定
	m_faseObjPtr.reset( new GameMainSelectFase(m_commonData) );
	m_faseObjPtr->Init();
	m_fase = IGameMainFase::SELECT;
}


SCENE GameMainScene::Update() {
	// ゲームメイン再読み込み（デバッグ用）
	if (KeyTrigger(KEY_SPACE)) {
		return SCENE::GAME_MAIN;
	}
	// フェイズ更新実行
	if (m_faseObjPtr->Update() == m_fase)
		return SCENE::NOT;

	switch (m_fase)
	{
	case IGameMainFase::SELECT:
		m_faseObjPtr.reset(new GameMainSelectFase(m_commonData));
		m_fase = IGameMainFase::SELECT;
		break;
	case IGameMainFase::ACTIVATE:
		m_faseObjPtr.reset(new GameMainActivateFase(m_commonData));
		m_fase = IGameMainFase::ACTIVATE;
		break;
	case IGameMainFase::RESULT:
		m_faseObjPtr.reset(new GameMainResultFase(m_commonData));
		m_fase = IGameMainFase::RESULT;
		break;
	case IGameMainFase::END:
		return SCENE::RESULT;
		break;
	default:
		break;
	}
	m_faseObjPtr->Init();

	return SCENE::NOT;
}

void GameMainScene::Render() {
	m_faseObjPtr->Draw();
}

/*
GameMainScene::FASE GameMainScene::SetUpdate() {
	//　Todo: Lua組み込み
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	if (luaL_dofile(L, "LuaScript/CardCreate.lua") || lua_pcall(L,0,0,0)) {
		exit(-1);
	}

	// カードを発行しIDを受け取る
	// ID情報からテクスチャパスを受け取り読み込む
	for (int i = 0;i < 2;++i) {
		lua_getglobal(L, "IssueCardID");
		lua_pcall(L, 0, 4, 0);
		// 4枚分のIDを保存
		for (int k = 0; k < HANDCARD_MAX;++k) {
			m_handcard[k].reset(new Card(lua_tointeger(L, 1),k));
		}

		lua_getglobal(L, "IssueCardTexName");
		for (int k = 0; k < HANDCARD_MAX; ++k) {
			lua_pushnumber(L, m_handcard[k]->GetID());
		}
		lua_pcall(L, 4, 4, 0);

		// PLAYER_1_CARD_0	= プレイヤー１の手持ちカード0番目
		for (int k = 0;k < HANDCARD_MAX; ++k) {
			//m_handcardTex.Add(lua_tostring(L, -1), "PLAYER_" + std::to_string(i + 1) + "CARD_" + std::to_string(k));
			m_handcard[k]->SetTexName(lua_tostring(L,-1));
		}
	}

	lua_close(L);
	
	return GameMainScene::FASE::SELECT;
}
// カード選択フェイズ更新関数
GameMainScene::FASE GameMainScene::SelectUpdate() {
	
	if (m_player[m_nowplayer].Update()) {
		// 次フェイズに移行
		m_barOrder.GetAnimation()->AddNum();
		if (m_nowplayer != m_firstplayer) {
			m_nowplayer = m_firstplayer;
			return GameMainScene::FASE::ACTIVATE;
		}
		// 次のプレイヤー
		m_nowplayer = !m_nowplayer;
	}
	m_player[m_nowplayer].CardAnimUpdate();


	return GameMainScene::FASE::SELECT;
}
// カード発動フェイズ更新関数
GameMainScene::FASE GameMainScene::ActivateUpdate() {

	// Todo: Lua組み込み
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	if (luaL_dofile(L, "LuaScript/BattleSystem.lua") || lua_pcall(L, 0, 0, 0)) {
		exit(-1);
	}

	// パラメータをLuaに渡す
	lua_getglobal(L, "InitParam");
	for (int i = 0;i < 2;++i) {
		lua_newtable(L);
		lua_pushnumber(L, m_player[i].GetParam().GetHP());
		lua_setfield(L, -2, "hp");
		lua_pushnumber(L, m_player[i].GetParam().GetATK());
		lua_setfield(L, -2, "atk");
		lua_pushnumber(L, m_player[i].GetParam().GetDEF());
		lua_setfield(L, -2, "def");
	}
	lua_pcall(L, 2, 0, 0);

	// 選択したカードIDをスタックに積む
	lua_getglobal(L, "SetCardData");
	for (int i = 0;i < 2; ++i)
		lua_pushnumber(L, m_player[i].GetCard());
	lua_pcall(L, 2, 0, 0);

	// カード発動
	lua_getglobal(L, "Battle");
	lua_pushnumber(L, (int)m_firstplayer+1);
	lua_pushnumber(L, (int)!m_firstplayer+1);
	lua_pcall(L, 2, 2, 0);

	return GameMainScene::FASE::RESULT;
}
// 結果フェイズ更新関数 
GameMainScene::FASE GameMainScene::ResultUpdate() {
	if (KeyTrigger(KEY_X)) {
		m_firstplayer = !m_firstplayer;
		m_nowplayer = m_firstplayer;
		if (m_endFlag)
			return GameMainScene::FASE::END;
		m_turn++;
		return GameMainScene::FASE::SET;
	}

	return GameMainScene::FASE::RESULT;
}

void GameMainScene::Render() {
	(this->*PhaseRender)();
}
// ===================== 描画関数 =====================
// カードセットフェイズ描画関数
void GameMainScene::SetDraw() {
	m_tex.Set("BackGround");
	m_back.Draw();
}
// カード選択フェイズ描画関数
void GameMainScene::SelectDraw() {
	// 背景描画
	m_tex.Set("BackGround");
	m_back.Draw();
	// 先攻・後攻表示バー描画
	m_tex.Set("Bar");
	m_barOrder.Draw();
	// カード描画
	m_player[m_nowplayer].DrawCard(m_factoryCard.get());
	
	char buf[256];
	sprintf_s(buf,"プレイヤー %d",m_nowplayer+1);
	g_debugFont.DrawTextA(100, 100,buf);
	sprintf_s(buf, "HP  : %f ",m_player[m_nowplayer].GetParam().GetHP());
	g_debugFont.DrawTextA(100, 150, buf);
	sprintf_s(buf, "ATK : %f ", m_player[m_nowplayer].GetParam().GetATK());
	g_debugFont.DrawTextA(100, 200, buf);
	sprintf_s(buf, "DEF : %f ", m_player[m_nowplayer].GetParam().GetDEF());
	g_debugFont.DrawTextA(100, 250, buf);

	sprintf_s(buf, "プレイヤー %d",(!m_nowplayer) +1);
	g_debugFont.DrawTextA(1000, 100, buf);
	sprintf_s(buf, "HP  : %f ", m_player[!m_nowplayer].GetParam().GetHP());
	g_debugFont.DrawTextA(1000, 150, buf);
	sprintf_s(buf, "ATK : %f ", m_player[!m_nowplayer].GetParam().GetATK());
	g_debugFont.DrawTextA(1000, 200, buf);
	sprintf_s(buf, "DEF : %f ", m_player[!m_nowplayer].GetParam().GetDEF());
	g_debugFont.DrawTextA(1000, 250, buf);
}
// カード発動フェイズ描画関数
void GameMainScene::ActivateDraw() {
	m_tex.Set("BackGround");
	m_back.Draw();


}
// 結果フェイズ描画関数 
void GameMainScene::ResultDraw() {
	m_tex.Set("BackGround");
	m_back.Draw();

	char buf[256];
	sprintf_s(buf, "プレイヤー 1");
	g_debugFont.DrawTextA(100, 100, buf);
	sprintf_s(buf, "HP  : %f ", m_player[m_nowplayer].GetParam().GetHP());
	g_debugFont.DrawTextA(100, 150, buf);
	sprintf_s(buf, "ATK : %f ", m_player[m_nowplayer].GetParam().GetATK());
	g_debugFont.DrawTextA(100, 200, buf);
	sprintf_s(buf, "DEF : %f ", m_player[m_nowplayer].GetParam().GetDEF());
	g_debugFont.DrawTextA(100, 250, buf);

	sprintf_s(buf, "プレイヤー 2");
	g_debugFont.DrawTextA(1000, 100, buf);
	sprintf_s(buf, "HP  : %f ", m_player[!m_nowplayer].GetParam().GetHP());
	g_debugFont.DrawTextA(1000, 150, buf);
	sprintf_s(buf, "ATK : %f ", m_player[!m_nowplayer].GetParam().GetATK());
	g_debugFont.DrawTextA(1000, 200, buf);
	sprintf_s(buf, "DEF : %f ", m_player[!m_nowplayer].GetParam().GetDEF());
	g_debugFont.DrawTextA(1000, 250, buf);
}
*/
void GameMainScene::Exit() {
	m_tex.Clear();
}



