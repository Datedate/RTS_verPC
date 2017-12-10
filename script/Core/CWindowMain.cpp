#include "CWindowMain.h"
#include <thread>

//==============================================================================
//!	@fn		WindowProc
//!	@brief	ウインドウプロシージャ
//!	@param	ウインドウハンドル
//!	@param	メッセージ
//!	@param	Wパラメータ
//!	@param	Lパラメータ
//!	@retval	終了状況
//==============================================================================
LRESULT CALLBACK MainWndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {	
	CWindowMain* pThisPtr = (CWindowMain*)GetWindowLong(_hWnd, GWL_USERDATA);
	if (pThisPtr)
		return (pThisPtr->LocalWndProc(_hWnd, _msg, _wParam, _lParam));
	else
		return (DefWindowProc(_hWnd, _msg, _wParam, _lParam));
}

//==============================================================================
//!	@fn		TimerProc
//!	@brief	１６ｍｓ毎にイベントオブジェクトをセットする
//!	@param	タイマＩＤ
//!	@param	未使用
//!	@param	未使用
//!	@param	未使用
//!	@param	未使用
//!	@retval	なし
//==============================================================================


void CALLBACK TimerProc(UINT, UINT, DWORD dwUser, DWORD, DWORD)
{
	reinterpret_cast<CWindowMain*>(dwUser)->LocalTimeProc();
}


// 初期化関数
bool CWindowMain::Init(HINSTANCE hInstance, int _winMode) {
	
	m_hInstance = hInstance;

	// ウインドウ生成
	if (!InitWindow()) return FALSE;

	// ウインドウを表示する
	ShowWindow(m_hWnd, _winMode);
	UpdateWindow(m_hWnd);

	// 初期処理（ゲームクラス、イベント生成、タイマーセット）
	if (!InitGame()) {
		m_game.Exit();
		return FALSE;
	}
	if (!InitEvent()) return FALSE;
	InitTimer();

	// ゲームメイン関数スレッド起動
	m_gamethread = std::thread(&CWindowMain::GameMain, this);
	return true;
}

bool CWindowMain::InitWindow() {
	WNDCLASSEX		wcex;						// ウインドウクラス構造体
	int				width = SCREEN_X;			// ウインドウの幅 計算用ワーク
	int				height = SCREEN_Y;			// ウインドウの高さ 計算用ワーク

	wcex.hInstance = m_hInstance;			// インスタンス値のセット
	wcex.lpszClassName = NAME;					// クラス名
	wcex.lpfnWndProc = (WNDPROC)MainWndProc;		// ウインドウメッセージ関数
	wcex.style = 0;					// ウインドウスタイル
	wcex.cbSize = sizeof(WNDCLASSEX);	// 構造体のサイズ
	wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ラージアイコン
	wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// スモールアイコン
	wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// カーソルスタイル
	wcex.lpszMenuName = 0; 					// メニューなし
	wcex.cbClsExtra = 0;					// エキストラなし
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// 背景色白

	if (!RegisterClassEx(&wcex)) return FALSE;	// ウインドウクラスの登録

	if (FULLSCREEN) {
		m_hWnd = CreateWindow(
			NAME,							// ウィンドウクラスの名前
			TITLE,							// タイトル
			WS_VISIBLE | WS_POPUP,			// ウィンドウスタイル
			0, 0,							// ウィンドウ位置 縦, 横
			SCREEN_X, SCREEN_Y,				// ウィンドウサイズ
			NULL,							// 親ウィンドウなし
			(HMENU)NULL,					// メニューなし
			m_hInstance,						// インスタンスハンドル
			(LPVOID)NULL);					// 追加引数なし
	}
	else {
		RECT	rWindow, rClient;

		m_hWnd = CreateWindow(
			NAME,							// ウィンドウクラスの名前
			TITLE,							// タイトル
			WS_CAPTION | WS_SYSMENU,		// ウィンドウスタイル
			0, 0,							// ウィンドウ位置 縦, 横(あとで中央に移動させます)
			SCREEN_X, SCREEN_Y,				// ウィンドウサイズ
			HWND_DESKTOP,					// 親ウィンドウなし
			(HMENU)NULL,					// メニューなし
			m_hInstance,						// インスタンスハンドル
			(LPVOID)NULL);					// 追加引数なし

											// ウインドウサイズを再計算（Metricsだけでは、フレームデザインでクライアント領域サイズが変わってしまうので）
		GetWindowRect(m_hWnd, &rWindow);
		GetClientRect(m_hWnd, &rClient);
		width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + SCREEN_X;
		height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + SCREEN_Y;
		SetWindowPos(
			m_hWnd,
			NULL,
			GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
			width - 1,
			height - 1,
			SWP_NOZORDER);
	}
	SetWindowLong(m_hWnd, GWLP_USERDATA, (LONG)this);
	if (!m_hWnd) {
		return false;
	}
	return true;
}

bool CWindowMain::InitGame() {
	if (!m_game.Init(m_hWnd, m_hInstance, FULLSCREEN , SCREEN_X, SCREEN_Y)) {
		MessageBox(m_hWnd, "ERROR!", "GameInit Error", MB_OK);
		return false;
	}
	return true;
}

bool CWindowMain::InitEvent() {
	// イベントハンドル生成
	m_eventHandle = CreateEvent(NULL, false, false, NULL);
	if (m_eventHandle == NULL) {
		MessageBox(m_hWnd, "ERROR!!", "CreateEvent エラー", MB_OK);
		return false;
	}
	return true;
}

void CWindowMain::InitTimer() {
	// イベントタイマーをセットする
	timeBeginPeriod(1);			// タイマの分解能力を１ｍｓにする
								// 16ms毎にメンバのコールバック関数が呼ばれる
								// タイマーコールバック関数内でメンバ関数を使用するため
								// リインタープリットキャストで自分のポインタをタイマーコールバック関数に渡しています。
	m_timerID = timeSetEvent(16, 1, TimerProc, reinterpret_cast<DWORD>(this), TIME_PERIODIC);
}

// 更新関数
void CWindowMain::Update() {
	MSG msg;

	while (1) {	// メッセージ･ループ
		if (!GetMessage(&msg, NULL, 0, 0)) {	// メッセージを取得
			break;
		}
		else {
			TranslateMessage(&msg); 			// 文字メッセージへのコンバート）
			DispatchMessage(&msg); 				// メッセージをWndProcへ送る
		}
	}
}

// 終了関数
void CWindowMain::Exit() {
	m_game.SetEndFlag();
	m_gamethread.join();

	if (m_timerID) timeKillEvent(m_timerID);	// マルチメディアタイマの終了
	timeEndPeriod(1);							// タイマの分解能力もとに戻す

	m_game.Exit();
}

// ローカルウインドウプロシージャ
LRESULT CWindowMain::LocalWndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {
	switch (_msg)
	{
	case WM_KEYDOWN:
		if (_wParam == VK_ESCAPE) {
			Exit();
			PostQuitMessage(0);
		}
		break;
	case WM_DESTROY:
		Exit();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
		break;
	}
	return 0;
}

void CWindowMain::LocalTimeProc() {
	GameSetEvent();
}


void CWindowMain::GameMain() {
	while (1) {
		/*
		DWORD sts = WaitForSingleObject(m_eventHandle, 1000);	// イベントフラグがセットされるのを待つ（1000msでタイムアウト）
		if (sts == WAIT_FAILED) {
			break;
		}
		else if (sts == WAIT_TIMEOUT) {
			if (m_game.IsEnd()) {
				break;
			}
			continue;
		}
		*/
		m_game.Exec();
	}

	m_game.SetEndFlag();
}

void CWindowMain::GameSetEvent() {
	if (!m_game.IsEnd()) {
		SetEvent(m_eventHandle);
	}
}
