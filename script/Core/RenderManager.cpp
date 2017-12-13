#include "RenderManager.h"
#include "SpriteBase.h"
#include "ShaderManager.h"

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
	m_displaySize = Size(width, height);

	D3DXMATRIX proj(
		2.0f / width, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / height, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f
		);

	m_projection2D = proj;
	// Ｚバッファ有効
	m_lpd3ddevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// ライト有効
	m_lpd3ddevice->SetRenderState(D3DRS_LIGHTING, true);
	// カリング無効化
	m_lpd3ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// 環境光セット
	m_lpd3ddevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	VertexFormatSetting();
	VertexBufferToVRAM();

		return true;
}

void RenderManager::Exit() {
	if (m_lpvxBuff != NULL) {
		m_lpvxBuff->Release();
		m_lpvxBuff = NULL;
	}
	if (m_lpdecl != NULL) {
		m_lpdecl->Release();
		m_lpdecl = NULL;
	}
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

void RenderManager::VertexFormatSetting() {
	m_elements[0] =			// 頂点座標フォーマット
	{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 };
	m_elements[1] =			// 頂点UVフォーマット
	{ 0,sizeof(float) * 3,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_TEXCOORD,0 };
	m_elements[2] = D3DDECL_END();

	// 頂点宣言オブジェクト取得
	m_lpd3ddevice->CreateVertexDeclaration(m_elements, &m_lpdecl);
}

void RenderManager::VertexBufferToVRAM() {
	if (m_lpvxBuff == NULL) {
		float commonVtx[] = {
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 1
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 2
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 3
		};
		m_lpd3ddevice->CreateVertexBuffer(sizeof(commonVtx), 0, 0, D3DPOOL_MANAGED, &m_lpvxBuff, 0);
		float *p = 0;
		if (m_lpvxBuff) {
			m_lpvxBuff->Lock(0, 0, (void**)&p, 0);
			memcpy(p, commonVtx, sizeof(commonVtx));
			m_lpvxBuff->Unlock();
		}
	}
}

void RenderManager::CleanUp() {
	//m_drawList.clear();
}

void RenderManager::InStreamVertex() {
	if (m_drawList.empty()) return;
	auto sprite = m_drawList.begin();
	auto shaderMng = ShaderManager::GetInstance();

	// 頂点バッファ・頂点宣言設定
	m_lpd3ddevice->SetStreamSource(0, m_lpvxBuff, 0, sizeof(float) * 5);
	m_lpd3ddevice->SetVertexDeclaration(m_lpdecl);

	for (;sprite != m_drawList.end();++sprite) {
		SpriteBase* sp = (*sprite);
		if (!sp->IsDrawFlag()) continue;
		sp->MakeWorldMatrix();

		// スプライトが使用するシェーダーを取得
		auto shaderData = shaderMng->GetEffectInfo(sp->GetEffectID());
		if (shaderData == NULL)
			MessageBox(nullptr, "ShaderManager->GetEffectInfo", "NULL来た", MB_OK);

		// テクニックの選択
		shaderData->effect->SetTechnique(shaderData->tech.c_str());
		// 独自シェーダー切り替え
		UINT numPass;
		shaderData->effect->Begin(&numPass, 0);
		shaderData->effect->BeginPass(0);

		shaderData->effect->SetMatrix(shaderData->matProjection.c_str(), &m_projection2D);
		shaderData->effect->SetMatrix(shaderData->matWorld.c_str(), &sp->GetMatrix());
		shaderData->effect->SetTexture("g_Texture", sp->GetTexture());
		shaderData->effect->SetFloat("uv_left"	  , sp->getUV().left);
		shaderData->effect->SetFloat("uv_top"	  , sp->getUV().top);
		shaderData->effect->SetFloat("uv_width"	  , sp->getUV().hei);
		shaderData->effect->SetFloat("uv_height"  , sp->getUV().wid);
		shaderData->effect->SetFloat("alpha"	  , sp->GetAlpha());
		shaderData->effect->SetFloat("pivot_x"	  , sp->getPivotX());
		shaderData->effect->SetFloat("pivot_y"	  , sp->getPivotY());
		shaderData->effect->CommitChanges();
		/*
		// 頂点情報セット
		VertexInfo info[4];

		info[0].x = info[1].x = (*itr)->GetRectangle().getMinX();
		info[0].y = info[3].y = (*itr)->GetRectangle().getMinY();
		info[2].x = info[3].x = (*itr)->GetRectangle().getMaxX();
		info[1].y = info[2].y = (*itr)->GetRectangle().getMaxY();
		info[0].z = info[1].z = info[2].z = info[3].z = 0.0f;

		if ((*itr)->GetTexture() != nullptr) {
			info[0].tu = 0.0f; info[0].tv = 0.0f;
			info[1].tu = 0.0f; info[1].tv = 1.0f;
			info[2].tu = 1.0f; info[2].tv = 1.0f;
			info[3].tu = 1.0f; info[3].tv = 0.0f;
		}

		//m_vertex = info;
		*/
		m_lpd3ddevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0 ,2);

		shaderData->effect->EndPass();
		shaderData->effect->End();
	}
}
