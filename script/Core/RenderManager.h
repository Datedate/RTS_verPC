#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "SingletonTemplate.h"
#include <d3dx9.h>
#include <vector>
#include "ConfigSystem.h"

class SpriteBase;

struct VertexInfo
{
	float x, y, z;
	float tu, tv;
};

class RenderManager:public SingletonTemplate<RenderManager>
{
public:
	friend SingletonTemplate<RenderManager>;

	bool Init(HWND, bool, int, int);
	void Render();
	void Exit();

	LPDIRECT3DDEVICE9 GetDevice() {
		return m_lpd3ddevice;
	}

	void PushDraw(SpriteBase* _sprite) {
		m_drawList.push_back(_sprite);
	}
private:
	RenderManager();
	~RenderManager();
	void CleanUp();
	void InStreamVertex();
private:
	LPDIRECT3D9					m_lpd3d;			// DIRECT3D8オブジェクト
	LPDIRECT3DDEVICE9			m_lpd3ddevice;		// DIRECT3DDEVICE8オブジェクト
	D3DPRESENT_PARAMETERS		m_d3dpp;			// プレゼンテーションパラメータ
	D3DDISPLAYMODE				m_disp;				// ディスプレイモード
	int							m_adapter;			// ディスプレイアダプタ番号
	int							m_width;			// バックバッファＸサイズ
	int							m_height;			// バックバッファＹサイズ
	std::vector<SpriteBase*>	m_drawList;
	D3DXMATRIX					m_projection2D;		// 
};

#endif