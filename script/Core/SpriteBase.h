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

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

struct VertexInfo
{
	float		x, y, z;						// 座標
	Color		color;
	float		tu, tv;							// テクスチャ値
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
	void SetColor(float r, float g, float b);
	void SetColor(float r, float g, float b, float a);
	void SetAlpha(float _alpha);
	void Move(float _x, float _y);
	bool InRange(float _x, float _y);

	void Trans(float _transX,float _transY);			// 平行移動
	void Rotation(float _angleZ);						// 回転
	void Scale(float _scaleX, float _scaleY);			// 拡縮
	void MakeWorldMatrix();

	DWORD GetEffectID()const {
		return m_effectID;
	}
	D3DXMATRIX GetMatrix() const{
		return m_world;
	}
	Color* GetColor(){
		return (m_color);
	}
	float GetAlpha()const {
		return m_alpha;
	}
	Vector2 GetPos()const {
		return m_pos;
	}
	float getPivotX()const;
	float getPivotY()const;
	UV getUV()const;
	LPDIRECT3DTEXTURE9 GetTexture()const;

protected:
	Poly					m_poly;
	UV						m_uv;
	float					m_pivot_x, m_pivot_y;
	Color					m_color[4];
	
	LPDIRECT3DTEXTURE9		m_tex;
	bool					m_drawFlag;
	float					m_alpha;
	DWORD					m_effectID;
	
	// 現在の姿勢
	Vector2					m_pos;
	float					m_angle;
	Size					m_size;

	// 行列変換
	D3DXMATRIX				m_world;
	D3DXVECTOR3				m_transAmount;
	D3DXVECTOR3				m_angleAmount;
	D3DXVECTOR3				m_scaleAmount;

	RenderManager*			pRenderMng;
};

#endif
