#ifndef __SHADER_CONTROLER__H__
#define __SHADER_CONTROLER__H__

#include <map>
#include <d3dx9.h>

struct _Shader
{
	_Shader(){}
	_Shader(const char* _entry, const char* _version)
	{
		entry = _entry;
		version = _version;
	}
	LPDIRECT3DVERTEXSHADER9 lpDirVS;
	LPD3DXCONSTANTTABLE		lpConsTblVS;
	LPDIRECT3DPIXELSHADER9  lpDirPS;
	LPD3DXCONSTANTTABLE		lpConsTblPS;
	const char*				entry;
	const char*				version;
};

class ShaderController
{
public:
	ShaderController() {};
	~ShaderController() {};
	void Add(std::string _fileNae);
	void AddVertexShader(std::string _fileName,std::string _entry,std::string _version);
	void AddPixelShader(std::string _fileName, std::string _entry, std::string _version);
	bool AllShaderCompile();
private:
	bool VertexShaderCompile();
	bool PixelShaderCompile();
	bool ShaderCompile(std::string _fileName, const char* _entry,
		const char* _version, LPD3DXBUFFER* _code, LPD3DXCONSTANTTABLE* _tbl);

	std::map<std::string, _Shader*>	m_vertexShaderContainer;
	std::map<std::string, _Shader*>	m_pixelShaderContainer;
};


#endif
