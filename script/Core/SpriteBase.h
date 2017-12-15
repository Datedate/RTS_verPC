#ifndef _SPRITE_BASE_H_
#define _SPRITE_BASE_H_

#include "Object.h"
#include "Rectangle.h"
#include <string>
#include <d3dx9.h>

class RenderManager;

struct Poly {
	float wid, hei;
	float x, y;
};

struct UV {
	float left;
	float top;
	float wid, hei;
};

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
	void SetEffectID(DWORD _id);
	bool CreateTex(std::string _texName);
	void UVCut(float _left, float _top, float _width, float _height);
	void SetAlpha(float _alpha);
	void Move(float _x, float _y);

	void Trans(float _transX,float _transY);			// ïΩçsà⁄ìÆ
	void Rotation(float _angleZ);						// âÒì]
	void Scale(float _scaleX, float _scaleY);			// ägèk
	void MakeWorldMatrix();

	DWORD GetEffectID()const {
		return m_effectID;
	}
	D3DXMATRIX GetMatrix() const{
		return m_world;
	}
	int* GetColor(){
		return (m_color);
	}
	float GetAlpha()const {
		return m_alpha;
	}
	float getPivotX()const;
	float getPivotY()const;
	UV getUV()const;
	LPDIRECT3DTEXTURE9 GetTexture()const;

private:
	Poly					m_poly;
	UV						m_uv;
	float					m_pivot_x, m_pivot_y;
	int						m_color[4];
	
	LPDIRECT3DTEXTURE9		m_tex;
	bool					m_drawFlag;
	float					m_alpha;
	DWORD					m_effectID;
	
	// åªç›ÇÃépê®
	Vector2					m_pos;
	float					m_angle;
	Size					m_size;

	// çsóÒïœä∑
	D3DXMATRIX				m_world;
	D3DXVECTOR3				m_transAmount;
	D3DXVECTOR3				m_angleAmount;
	D3DXVECTOR3				m_scaleAmount;

	RenderManager*			pRenderMng;
};

#endif
