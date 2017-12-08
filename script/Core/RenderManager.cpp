#include "RenderManager.h"
#include "SpriteBase.h"

RenderManager::RenderManager() {
	m_lpd3d = NULL;
	m_lpd3ddevice = NULL;
	m_adapter = 0;
	m_width = 0;
	m_height = 0;
}

RenderManager::~RenderManager() {
	if (m_lpd3ddevice != NULL) {
		m_lpd3ddevice->Release();
		m_lpd3ddevice = NULL;
	}
	if (m_lpd3d != NULL) {
		m_lpd3d->Release();
		m_lpd3d = NULL;
	}
}

bool RenderManager::Init(HWND hwnd, bool fullscreenflag, int width, int height) {
	HRESULT	hr;

	m_lpd3d = Direct3DCreate9(D3D_SDK_VERSION);	// Direct3D9インターフェース取得
	if (m_lpd3d == NULL)	return false;

	// アダプタの現在のディスプレイモードを取得する
	hr = m_lpd3d->GetAdapterDisplayMode(m_adapter, &m_disp);
	if (hr != D3D_OK)	return false;

	memset(&m_d3dpp, 0, sizeof(m_d3dpp));			// ゼロクリア
	m_d3dpp.BackBufferFormat = m_disp.Format;	// 現在のビット深度
	m_d3dpp.BackBufferWidth = width;			// バックバッファの幅をセット
	m_d3dpp.BackBufferHeight = height;			// バックバッファの高さをセット
	m_d3dpp.BackBufferCount = 1;				// バックバッファの数
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	m_d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	// バックバッファをロック可能にする

	if (fullscreenflag)	m_d3dpp.Windowed = FALSE;	// フルスクリーンモード
	else					m_d3dpp.Windowed = TRUE;	// ウインドウモード

														// Ｚバッファの自動作成（ビット深度24）
	m_d3dpp.EnableAutoDepthStencil = 1;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// VSYNCを待たない

																	// デバイス作成
	hr = m_lpd3d->CreateDevice(m_adapter,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		&m_d3dpp,
		&m_lpd3ddevice);
	if (hr != D3D_OK) {
		hr = m_lpd3d->CreateDevice(m_adapter,
			D3DDEVTYPE_HAL,
			hwnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
			&m_d3dpp,
			&m_lpd3ddevice);
		if (hr != D3D_OK) {
			hr = m_lpd3d->CreateDevice(m_adapter,
				D3DDEVTYPE_REF,
				hwnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
				&m_d3dpp,
				&m_lpd3ddevice);
			if (hr != D3D_OK)		return(false);
		}
	}
	m_height = height;
	m_width = width;


	D3DXMATRIX proj(
		2.0f/width , 0.0f , 0.0f , 0.0f,
		0.0f , 2.0f/height, 0.0f , 0.0f,
		0.0f , 0.0f , 1.0f , 0.0f,
		-1.0f , -1.0f , 0.0f , 1.0f
	);

	m_projection2D = proj;

	m_lpd3ddevice->SetTransform(D3DTS_PROJECTION, &proj);
	// Ｚバッファ有効
	m_lpd3ddevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ライト有効
	m_lpd3ddevice->SetRenderState(D3DRS_LIGHTING, true);
	// カリング無効化
	m_lpd3ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// 環境光セット
	m_lpd3ddevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	//アルファ画像によるブレンド
	//g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_DXGrobj->GetDXDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return true;
}

void RenderManager::Exit() {
	if (m_lpd3ddevice != NULL) {
		m_lpd3ddevice->Release();
		m_lpd3ddevice = NULL;
	}
	if (m_lpd3d != NULL) {
		m_lpd3d->Release();
		m_lpd3d = NULL;
	}
}

void RenderManager::Render() {
	m_lpd3ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	m_lpd3ddevice->BeginScene();

	InStreamVertex();

	m_lpd3ddevice->EndScene();
	m_lpd3ddevice->Present(NULL, NULL, NULL, NULL);
	CleanUp();
}

void RenderManager::CleanUp() {
	//m_drawList.clear();
}

void RenderManager::InStreamVertex() {
	if (m_drawList.empty()) return;
	auto itr = m_drawList.begin();

	m_lpd3ddevice->SetFVF(D3DFVF_XYZ);
	for (;itr != m_drawList.end();++itr) {
		if (!(*itr)->IsDrawFlag()) continue;

		// 描画
		VertexInfo info[4];

		info[0].x = info[1].x = (*itr)->GetRectangle().getMinX();
		info[0].y = info[3].y = (*itr)->GetRectangle().getMinY();
		info[2].x = info[3].x = (*itr)->GetRectangle().getMaxX();
		info[1].y = info[2].y = (*itr)->GetRectangle().getMaxY();
		info[0].z = info[1].z = info[2].z = info[3].z = 0.0f;

//		int* cl = (*itr)->GetColor();
//		info[0].color = D3DCOLOR_ARGB((*cl), (*(cl++)), (*(cl++)), (*(cl++)));
		/*
		if ((*itr)->GetTexture() != nullptr) {
			info[0].tu = info[3].tu = (*itr)->getMinTU();
			info[0].tv = info[1].tv = (*itr)->getMinTV();
			info[1].tu = info[2].tu = (*itr)->getMaxTU();
			info[2].tv = info[3].tv = (*itr)->getMaxTV();
			m_lpd3ddevice->SetTexture(0,(*itr)->GetTexture());
		}
		*/
		m_lpd3ddevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2,info ,sizeof(VertexInfo));
	}
}