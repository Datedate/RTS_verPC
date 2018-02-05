#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "SingletonTemplate.h"
#include <d3dx9.h>
#include <map>
#include <string>

class TextureManager : public SingletonTemplate<TextureManager>
{
public:
	friend SingletonTemplate<TextureManager>;

	LPDIRECT3DTEXTURE9 CreateTex(std::string _filepath);
	void PolySize(std::string filepath, float* x, float* y);
	void Release(std::string filepath);
private:
	TextureManager() {};
	~TextureManager();
private:
	std::map<std::string , LPDIRECT3DTEXTURE9>	m_texContainer;
};

#endif