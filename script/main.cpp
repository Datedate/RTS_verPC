#include "CWindowMain.h"

//-----------------------------------------------------------------------------
// リンクライブラリの設定
//-----------------------------------------------------------------------------
#pragma comment(lib, "d3d9.lib")			// リンク対象ライブラリにd3d9.libを追加
#pragma comment(lib, "d3dx9.lib")			// リンク対象ライブラリにd3dx9.libを追加
#pragma comment(lib, "winmm.lib")			// リンク対象ライブラリにwinmm.libを追加

//==============================================================================
//!	@fn		WinMain
//!	@brief	エントリポイント
//!	@param	インスタンスハンドル
//!	@param	意味なし
//!	@param	起動時の引数文字列
//!	@param	ウインドウ表示モード
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//!	@note	
//==============================================================================
int APIENTRY WinMain(HINSTANCE 	hInstance, 		// アプリケーションのハンドル
	HINSTANCE 	hPrevInstance,	// 今のWindowsバージョンでは使われない
	LPSTR 		lpszArgs, 		// 起動時の引数（文字列）
	int 		_winMode)		// ウインドウ表示モード
{
	CWindowMain m_winMain;

	if (!m_winMain.Init(hInstance, _winMode)) {
		MessageBox(NULL, TEXT("error init"),
			TEXT("初期化失敗"), MB_OK);
	}
	m_winMain.Update();
}

//******************************************************************************
//	End of file.
//******************************************************************************