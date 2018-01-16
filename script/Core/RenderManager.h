#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "SingletonTemplate.h"
#include <d3dx9.h>
#include <vector>
#include "ConfigSystem.h"
#include "Rectangle.h"

class SpriteBase;
class LayerBase;

class RenderManager :public SingletonTemplate<RenderManager>
{
public:
	friend SingletonTemplate<RenderManager>;

	bool Init(HWND, bool, int, int);
	void Render();
	void Exit();

	LPDIRECT3DDEVICE9 GetDevice() {
		return m_lpd3ddevice;
	}

	void PushSprite(SpriteBase* _sprite) {
		m_drawList.push_back(_sprite);
	}
	void PushLayer(LayerBase* _layer) {
		m_layerList.push_back(_layer);
	}

	Size GetDisplaySize()const {
		return m_displaySize;
	}
private:
	RenderManager();
	~RenderManager();

	void VertexFormatSetting();
	void VertexBufferToVRAM();
	void CleanUp();

	void SortLayerInSprite();
	void InStreamVertex();


private:
	LPDIRECT3D9						m_lpd3d;			// DIRECT3D8�I�u�W�F�N�g
	LPDIRECT3DDEVICE9				m_lpd3ddevice;		// DIRECT3DDEVICE8�I�u�W�F�N�g
	LPDIRECT3DVERTEXDECLARATION9	m_lpdecl;			// DIRECT3DVERTEXDECLARATION9�I�u�W�F�N�g�i���_�t�H�[�}�b�g�ݒ�j
	D3DVERTEXELEMENT9				m_elements[3];		// ���_�t�H�[�}�b�g���
	D3DPRESENT_PARAMETERS			m_d3dpp;			// �v���[���e�[�V�����p�����[�^
	D3DDISPLAYMODE					m_disp;				// �f�B�X�v���C���[�h
	int								m_adapter;			// �f�B�X�v���C�A�_�v�^�ԍ�
	int								m_width;			// �o�b�N�o�b�t�@�w�T�C�Y
	int								m_height;			// �o�b�N�o�b�t�@�x�T�C�Y
	Size							m_displaySize;		// �o�b�t�@�T�C�Y
	std::vector<SpriteBase*>		m_drawList;			// �`�悷��X�v���C�g�̃R���e�i
	std::vector<LayerBase*>			m_layerList;		// ���C���[�R���e�i�i�X�v���C�g��n���j
	D3DXMATRIX						m_projection2D;		// 2D�p�ˉe�ϊ��s�� 
	LPDIRECT3DVERTEXBUFFER9			m_lpvxBuff;		// ���_�o�b�t�@
};

#endif