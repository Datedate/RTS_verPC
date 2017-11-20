#pragma once

#include <d3dx9.h>

class CGraphics
{
public:
	CGraphics(){
		m_lpd3d = NULL;
		m_lpd3ddevice = NULL;
		m_adapter = 0;
		m_width = 0;
		m_height = 0;
	}
	~CGraphics() {};
	bool Init(HWND, bool, int, int);
	void Exit();
private:
	LPDIRECT3D9					m_lpd3d;			// DIRECT3D8オブジェクト
	LPDIRECT3DDEVICE9			m_lpd3ddevice;		// DIRECT3DDEVICE8オブジェクト
	D3DPRESENT_PARAMETERS		m_d3dpp;			// プレゼンテーションパラメータ
	D3DDISPLAYMODE				m_disp;				// ディスプレイモード
	int							m_adapter;			// ディスプレイアダプタ番号
	int							m_width;			// バックバッファＸサイズ
	int							m_height;			// バックバッファＹサイズ
};


