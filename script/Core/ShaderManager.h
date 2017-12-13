#ifndef __SHADER_MANAGER__H__
#define __SHADER_MANAGER__H__

#include <map>
#include <d3dx9.h>
#include "SingletonTemplate.h"

/*
// ID3DXInclude インターフェイス派生クラス
class ShaderResourceInclude : public ID3DXInclude{
	HRESULT Open(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes);
	HRESULT Close(LPCVOID pData);
};
*/
// ShaderManagerクラス
struct EffectInfo {
	LPD3DXEFFECT	effect;
	std::string		tech;
	std::string		matWorld;
	std::string     matProjection;
};

class ShaderManager :public SingletonTemplate<ShaderManager>
{
public:
	friend SingletonTemplate<ShaderManager>;

	bool GetFromFileNameToID(LPCTSTR _fileName, DWORD* _pID);
	EffectInfo* GetEffectInfo(DWORD _id);
private:
	ShaderManager();
	~ShaderManager();
	void AddEffect(LPDIRECT3DDEVICE9 _lpdev, std::string _filename, DWORD _id);
	bool CreateEffectFile(LPDIRECT3DDEVICE9 _lpdev, DWORD _id, LPD3DXEFFECT* _pEffect);
	void SetEffectInfo(DWORD _id, EffectInfo** _ppEffectInfo);

	std::map<std::string, DWORD>		m_effectFileNameIdHash;
	std::map<DWORD, EffectInfo*>			m_effectContainer;
};
#endif
