#include "ShaderManager.h"
#include "RenderManager.h"
#include "../../resource3.h"

/*
// ==================== ID3DXInclude Openメソッド実装 ====================== 
HRESULT ShaderResourceInclude::Open(D3DXINCLUDE_TYPE IncludeType,	// #includeファイルの所在(D3DXINC_LOACL)
	LPCSTR pFileName,		// #include が指定するファイル名
	LPCVOID pParentData,	// #include ファイルを含むコンテナへのポインタが入る
	LPCVOID *ppData,		// #include ファイルの展開コード文字列へのポインタを返す
	UINT *pBytes) {			// 上の文字列のサイズ

	// 引数のファイル名からリソースIDを探索する
	DWORD id;
	auto shaderMng = ShaderManager::GetInstance();

	if (!shaderMng->GetFromFileNameToID(pFileName, &id)) {
		return D3DXERR_INVALIDDATA;
	}

	// IDに該当するHLSLコードリソースを検索
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(id), RT_RCDATA);
	if (hRsrc == NULL) {
		return D3DXERR_INVALIDDATA;
	}

	// リソースをロード
	HGLOBAL hGlobalRsrc = LoadResource(NULL, hRsrc);
	if (hGlobalRsrc == NULL) {
		return D3DXERR_INVALIDDATA;
	}
	DWORD size = SizeofResource(NULL, hRsrc);	// リソースサイズ取得

	// リソースをロックして文字列を抽出
	*ppData = LockResource(hGlobalRsrc);
	*pBytes = (UINT)size;

	return S_OK;
}
HRESULT ShaderResourceInclude::Close(LPCVOID pData) {
	// ※閉じなくてもいいらしい
}
// ==================== ID3DXInclude Openメソッド実装 ======================
*/

// ==================== ShaderManagerクラス実装部分 ========================
ShaderManager::ShaderManager() {
	auto lpdev = RenderManager::GetInstance()->GetDevice();

	// ここにシェーダーファイル名とリソースIDを結ぶ
	AddEffect(lpdev, "shader.fx", FXID_EFFECT);

}

ShaderManager::~ShaderManager() {
	/*
	if (m_vertexShaderContainer.size() != 0) {
		for (auto itr = m_vertexShaderContainer.begin(); itr != m_vertexShaderContainer.end(); ++itr)
		{
			(*itr).second->Destroy();
			delete (*itr).second;
		}
	}
	m_vertexShaderContainer.clear();
	if (m_pixelShaderContainer.size() != 0) {
		for (auto itr = m_pixelShaderContainer.begin(); itr != m_pixelShaderContainer.end();++itr) {
			(*itr).second->Destroy();
			delete (*itr).second;
		}
	}
	m_pixelShaderContainer.clear();
	*/
	if (m_effectContainer.size() != 0) {
		for (auto itr = m_effectContainer.begin();itr != m_effectContainer.end();++itr) {
			if ((*itr).second != nullptr) {
				(*itr).second->effect->Release();
			}
		}
	}
	m_effectContainer.clear();
	m_effectFileNameIdHash.clear();
}

/*
void ShaderManager::Add(std::string _fileName) {
	AddVertexShader(_fileName, "vs_main", "vs_3_0");
	AddPixelShader(_fileName, "ps_main", "ps_3_0");
}
void ShaderManager::AddVertexShader(std::string _fileName, std::string _entry, std::string _version) {
	m_vertexShaderContainer.insert(std::make_pair(_fileName, new _vertexShaderData(_entry.c_str(), _version.c_str())));
}
void ShaderManager::AddPixelShader(std::string _fileName, std::string _entry, std::string _version) {
	m_pixelShaderContainer.insert(std::make_pair(_fileName, new _pixelShaderData(_entry.c_str(), _version.c_str())));
}
bool ShaderManager::AllShaderCompile() {
	if (!VertexShaderCompile()) {
		MessageBox(nullptr, "Error VertexShaderCompile", "", MB_OK);
		return false;
	}

	if (!PixelShaderCompile()) {
		MessageBox(nullptr, "Error PixelShaderCompile", "", MB_OK);
		return false;
	}
	return true;
}

_vertexShaderData* ShaderManager::GetVertexShaderData(std::string _fileName) const {
	auto target = m_vertexShaderContainer.find(_fileName);
	if (target != m_vertexShaderContainer.end()) {
		return (*target).second;
	}
	return nullptr;
}
_pixelShaderData* ShaderManager::GetPixelShaderData(std::string _fileName) const {
	auto target = m_pixelShaderContainer.find(_fileName);
	if (target != m_pixelShaderContainer.end()) {
		return (*target).second;
	}
	return nullptr;
}
*/

// エフェクトをコンテナに保存
void ShaderManager::AddEffect(LPDIRECT3DDEVICE9 _lpdev, std::string _fileName, DWORD _id) {
	m_effectFileNameIdHash.insert(std::make_pair(_fileName, _id));

	EffectInfo*	effectInfo = new EffectInfo();
	CreateEffectFile(_lpdev, _id,&effectInfo->effect);
	SetEffectInfo(_id, &effectInfo);

	m_effectContainer.insert(std::make_pair(_id, effectInfo));
}
bool ShaderManager::CreateEffectFile(LPDIRECT3DDEVICE9 _lpdev,DWORD _id,LPD3DXEFFECT* _pEffect) {
	HRESULT hr;
	LPD3DXBUFFER error;
	
//	ShaderResourceInclude include;	// ID3DXInclude 実装派生クラス

	// HLSLリソースを読み込む
	hr = D3DXCreateEffectFromResource(
		_lpdev,
		NULL,
		MAKEINTRESOURCE(103),
		NULL,
		//&include,
		NULL,
		0, NULL,
		_pEffect,
		&error
		);


	if (FAILED(hr)) {
		if (error) {
			// コンパイルエラー
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "D3DXCreateEffectFromFile", MB_OK);
		}
		else {
			MessageBox(nullptr, "Error : 読み込み失敗", "D3DXCreateEffectFromFile", MB_OK);
		}

		return false;
	}
	//m_effectContainer.insert(std::make_pair(_id, effectInfo));

	return true;
}

void ShaderManager::SetEffectInfo(DWORD _id, EffectInfo** _ppEffect) {
	// TODO:IDによってIDとセットのエフェクトクラスの派生クラスを生成しセットする
	switch (_id)
	{
	case FXID_EFFECT:
		(*_ppEffect)->matWorld		= "g_MatWorld";
		(*_ppEffect)->matProjection = "g_MatProjection";
		(*_ppEffect)->tech			= "Tech";
		break;
	default:
		break;
	}
}
/*
bool ShaderManager::VertexShaderCompile() {
	auto lpdevice = RenderManager::GetInstance()->GetDevice();

	bool sts;
	LPD3DXBUFFER code;

	auto itr = m_vertexShaderContainer.begin();
	for (;itr != m_vertexShaderContainer.end();++itr) {
		sts = ShaderCompile((*itr).first,
			(*itr).second->entry,
			(*itr).second->version,
			&code,
			&(*itr).second->lpConsTblVS);

		// 頂点シェーダーオブジェクト生成
		HRESULT hr = lpdevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &(*itr).second->lpDirVS);
		if (FAILED(hr)) {
			MessageBox(nullptr, "Error : CreateVertexShader", "", MB_OK);
			return false;
		}
	}

	return true;
}

bool ShaderManager::PixelShaderCompile() {
	auto lpdevice = RenderManager::GetInstance()->GetDevice();

	bool sts;
	LPD3DXBUFFER code;

	auto itr = m_pixelShaderContainer.begin();
	for (;itr != m_pixelShaderContainer.end();++itr) {
		sts = ShaderCompile((*itr).first,
			(*itr).second->entry,
			(*itr).second->version,
			&code,
			&(*itr).second->lpConsTblPS);

		// 頂点シェーダーオブジェクト生成
		HRESULT hr = lpdevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &(*itr).second->lpDirPS);
		if (FAILED(hr)) {
			MessageBox(nullptr, "Error : CreatePixelShader", "", MB_OK);
			return false;
		}
	}

	return true;
}

bool ShaderManager::ShaderCompile(std::string _fileName, const char* _entry,
	const char* _version, LPD3DXBUFFER* _code, LPD3DXCONSTANTTABLE* _tbl) {

	LPD3DXBUFFER error = nullptr;
	HRESULT	hr;

	std::string filepath = "script/shader/" + _fileName + ".fx";

	hr = D3DXCompileShaderFromFile(
		filepath.c_str(),
		nullptr, nullptr,
		_entry, _version, 0,
		_code, &error, _tbl);

	if (FAILED(hr)) {
		if (error) {
			// コンパイルエラー
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			MessageBox(nullptr, "Error : 読み込み失敗", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	return true;
}
*/

bool ShaderManager::GetFromFileNameToID(LPCTSTR _fileName, DWORD* _pID) {
	if (m_effectFileNameIdHash.size() == 0) return false;

	auto target = m_effectFileNameIdHash.find(_fileName);
	if (target != m_effectFileNameIdHash.end()) {
		*_pID = (*target).second;
		return true;
	}
	return false;
}

EffectInfo* ShaderManager::GetEffectInfo(DWORD _id) {
	auto target = m_effectContainer.find(_id);
	if (target != m_effectContainer.end()) {
		return (*target).second;
	}
	return nullptr;
}
// ==================== ShaderManagerクラス実装部分 ========================