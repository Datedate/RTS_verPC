#include "TextureManager.h"
#include "RenderManager.h"

LPDIRECT3DTEXTURE9 TextureManager::CreateTex(std::string _filepath) {
	auto device = RenderManager::GetInstance()->GetDevice();
	std::string filepath = "assets/" + _filepath;
	LPDIRECT3DTEXTURE9 tex;

	auto data = m_texContainer.find(_filepath);
	if (data != m_texContainer.end()) {
		return data->second;
	}
	if (FAILED((D3DXCreateTextureFromFile(device, filepath.c_str(), &tex)))) {
		MessageBox(NULL, "Failed : load Texture", filepath.c_str(), MB_OK);
		return NULL;
	}

	m_texContainer.insert(std::make_pair(_filepath, tex));
	return tex;
}

void TextureManager::PolySize(std::string filepath, float* x, float* y) {
	// テクスチャサイズ取得
	D3DSURFACE_DESC desc;

	auto data = m_texContainer.find(filepath);
	if (data != m_texContainer.end()) {
		if (FAILED(data->second->GetLevelDesc(0, &desc))) {
			MessageBox(NULL, "テクスチャサイズ取得失敗", filepath.c_str(), MB_OK);
			return;
		}
		*x = desc.Width;
		*y = desc.Height;
	}
}

void TextureManager::Release(std::string filepath) {
	auto data = m_texContainer.find(filepath);
	if (data != m_texContainer.end()) {
		if (data->second != NULL)
			data->second->Release();
	}
}

TextureManager::~TextureManager() {
	auto itr = m_texContainer.begin();
	for (;itr != m_texContainer.end();itr++) {
		if ((*itr).second != NULL)
			(*itr).second->Release();
	}
}