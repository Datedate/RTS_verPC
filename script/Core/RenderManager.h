#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "SingletonTemplate.h"
#include <d3dx9.h>
#include <vector>
#include "ConfigSystem.h"
#include "Rectangle.h"

class SpriteBase;
class LayerBase;

class RenderManager :public SingletonTemplate<RenderManager>
{
public:
	friend SingletonTemplate<RenderManager>;

	bool Init(HWND, bool, int, int);
	void Render();
	void Exit();

	LPDIRECT3DDEVICE9 GetDevice() {
		return m_lpd3ddevice;
	}

	void PushSprite(SpriteBase* _sprite) {
		m_drawList.push_back(_sprite);
	}
	void PushLayer(LayerBase* _layer) {
		m_layerList.push_back(_layer);
	}

	Size GetDisplaySize()const {
		return m_displaySize;
	}
private:
	RenderManager();
	~RenderManager();

	void VertexFormatSetting();
	void VertexBufferToVRAM();
	void CleanUp();

	void SortLayerInSprite();
	void InStreamVertex();


private:
	LPDIRECT3D9						m_lpd3d;			// DIRECT3D8オブジェクト
	LPDIRECT3DDEVICE9				m_lpd3ddevice;		// DIRECT3DDEVICE8オブジェクト
	LPDIRECT3DVERTEXDECLARATION9	m_lpdecl;			// DIRECT3DVERTEXDECLARATION9オブジェクト（頂点フォーマット設定）
	D3DVERTEXELEMENT9				m_elements[3];		// 頂点フォーマット情報
	D3DPRESENT_PARAMETERS			m_d3dpp;			// プレゼンテーションパラメータ
	D3DDISPLAYMODE					m_disp;				// ディスプレイモード
	int								m_adapter;			// ディスプレイアダプタ番号
	int								m_width;			// バックバッファＸサイズ
	int								m_height;			// バックバッファＹサイズ
	Size							m_displaySize;		// バッファサイズ
	std::vector<SpriteBase*>		m_drawList;			// 描画するスプライトのコンテナ
	std::vector<LayerBase*>			m_layerList;		// レイヤーコンテナ（スプライトを渡す）
	D3DXMATRIX						m_projection2D;		// 2D用射影変換行列 
	LPDIRECT3DVERTEXBUFFER9			m_lpvxBuff;		// 頂点バッファ
};

#endif