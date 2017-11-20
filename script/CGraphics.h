#pragma once

#include <d3dx9.h>

class CGraphics
{
public:
	CGraphics(){
		m_lpd3d = NULL;
		m_lpd3ddevice = NULL;
		m_adapter = 0;
		m_width = 0;
		m_height = 0;
	}
	~CGraphics() {};
	bool Init(HWND, bool, int, int);
	void Exit();
private:
	LPDIRECT3D9					m_lpd3d;			// DIRECT3D8�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_lpd3ddevice;		// DIRECT3DDEVICE8�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS		m_d3dpp;			// �v���[���e�[�V�����p�����[�^
	D3DDISPLAYMODE				m_disp;				// �f�B�X�v���C���[�h
	int							m_adapter;			// �f�B�X�v���C�A�_�v�^�ԍ�
	int							m_width;			// �o�b�N�o�b�t�@�w�T�C�Y
	int							m_height;			// �o�b�N�o�b�t�@�x�T�C�Y
};


