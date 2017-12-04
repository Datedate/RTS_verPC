#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "SingletonTemplate.h"
#include <d3dx9.h>
#include <vector>
#include "ConfigSystem.h"

class SpriteBase;

struct VertexInfo
{
	float x, y, z;
	float tu, tv;
};

class RenderManager:public SingletonTemplate<RenderManager>
{
public:
	friend SingletonTemplate<RenderManager>;

	bool Init(HWND, bool, int, int);
	void Render();
	void Exit();

	LPDIRECT3DDEVICE9 GetDevice() {
		return m_lpd3ddevice;
	}

	void PushDraw(SpriteBase* _sprite) {
		m_drawList.push_back(_sprite);
	}
private:
	RenderManager();
	~RenderManager();
	void CleanUp();
	void InStreamVertex();
private:
	LPDIRECT3D9					m_lpd3d;			// DIRECT3D8�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_lpd3ddevice;		// DIRECT3DDEVICE8�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS		m_d3dpp;			// �v���[���e�[�V�����p�����[�^
	D3DDISPLAYMODE				m_disp;				// �f�B�X�v���C���[�h
	int							m_adapter;			// �f�B�X�v���C�A�_�v�^�ԍ�
	int							m_width;			// �o�b�N�o�b�t�@�w�T�C�Y
	int							m_height;			// �o�b�N�o�b�t�@�x�T�C�Y
	std::vector<SpriteBase*>	m_drawList;
	D3DXMATRIX					m_projection2D;		// 
};

#endif