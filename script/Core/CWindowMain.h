#pragma once
#include <Windows.h>
#include "CGame.h"
#include <thread>

//-----------------------------------------------------------------------------
// マクロの定義
//-----------------------------------------------------------------------------
#define		NAME			"win32A"
#define		TITLE			"RTS"
#define		SCREEN_X		656
#define		SCREEN_Y		959
#define		FULLSCREEN		0				// フルスクリーンフラグ

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);			// ウインドウプロシージャ
void CALLBACK TimerProc(UINT, UINT, DWORD dwUser, DWORD, DWORD);

class CWindowMain
{
public:
	CWindowMain() {};
	~CWindowMain() {};
	bool Init(HINSTANCE _hInstance, int _winMode);		// 初期化関数
	bool InitWindow();
	bool InitGame();
	bool InitEvent();
	void InitTimer();
	void Update();										// 更新関数
	void Exit();										// 終了関数
	void GameMain();									// ゲームメイン
	void GameSetEvent();								// イベントシグナル状態
	LRESULT LocalWndProc(HWND, UINT, WPARAM, LPARAM);	// ローカルウインドウプロシージャ
	void LocalTimeProc();
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
private:
	std::thread m_gamethread;
	int m_timerID;					// タイマーID
	HANDLE m_eventHandle;			// 同期する
private:
	CGame m_game;					// ゲームの中枢クラス
};


