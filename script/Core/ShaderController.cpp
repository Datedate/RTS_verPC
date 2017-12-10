#include "ShaderController.h"
#include "RenderManager.h"

void ShaderController::Add(std::string _fileName) {
	AddVertexShader(_fileName, "vs_main", "vs_3_0");
	AddPixelShader(_fileName, "ps_main", "ps_3_0");
}
void ShaderController::AddVertexShader(std::string _fileName, std::string _entry, std::string _version) {
	m_vertexShaderContainer.insert(std::make_pair(_fileName, new _Shader(_entry.c_str(), _version.c_str())));
}
void ShaderController::AddPixelShader(std::string _fileName, std::string _entry, std::string _version) {
	m_pixelShaderContainer.insert(std::make_pair(_fileName, new _Shader(_entry.c_str(), _version.c_str())));
}
bool ShaderController::AllShaderCompile() {
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

bool ShaderController::VertexShaderCompile() {
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

bool ShaderController::PixelShaderCompile() {
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

bool ShaderController::ShaderCompile(std::string _fileName, const char* _entry,
	const char* _version, LPD3DXBUFFER* _code, LPD3DXCONSTANTTABLE* _tbl) {

	LPD3DXBUFFER error = nullptr;
	HRESULT	hr;

	std::string filepath = "shader/" + _fileName + ".fx";

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