#ifndef _SPRITE_BASE_H_
#define _SPRITE_BASE_H_

#include "Object.h"
#include "Rectangle.h"
#include <string>
#include <d3dx9.h>

class SpriteBase:public Object
{
public:
	static const int VERTEX_NUM;
	static SpriteBase* Create();
	static SpriteBase* Create(std::string _name);
	SpriteBase();
	SpriteBase(std::string _name);
	~SpriteBase();
	bool Init();
	void Update();
	void SetDrawFlag(bool _flag);
	bool IsDrawFlag();
	Rect GetRectangle()const {
		return m_rect;
	}
	int* GetColor(){
		return (m_color);
	}
	float getMinTU();
	float getMinTV();
	float getMaxTU();
	float getMaxTV();

	LPDIRECT3DTEXTURE9 GetTexture()const;
private:
	void Draw();

	Rect	m_rect;
	float	m_tu, m_tv;
	float	m_tuWidth, m_tvHeight;
	int		m_color[4];
	LPDIRECT3DTEXTURE9		m_tex;
	bool	m_drawFlag;
};

#endif
