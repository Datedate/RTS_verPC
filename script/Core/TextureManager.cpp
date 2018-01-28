#include "TextureManager.h"
#include "RenderManager.h"

LPDIRECT3DTEXTURE9 TextureManager::CreateTex(std::string _filepath) const{
	auto device = RenderManager::GetInstance()->GetDevice();
	std::string filepath = "assets/" + _filepath;
	LPDIRECT3DTEXTURE9 tex;

	auto data = m_texContainer.find(filepath);
	if (data != m_texContainer.end()) {
		return data->second;
	}
	if (FAILED((D3DXCreateTextureFromFile(device, filepath.c_str(), &tex)))) {
		MessageBox(NULL, "Failed : load Texture", filepath.c_str(), MB_OK);
		return NULL;
	}
	m_texContainer.insert(std::make_pair(filepath, tex));

	// テクスチャサイズ取得
	D3DSURFACE_DESC desc;
	if (FAILED(m_tex->GetLevelDesc(0, &desc))) {
		MessageBox(NULL, "テクスチャサイズ取得失敗", filepath.c_str(), MB_OK);
		return false;
	}

}