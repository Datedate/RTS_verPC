#include "CWindowMain.h"

//-----------------------------------------------------------------------------
// �����N���C�u�����̐ݒ�
//-----------------------------------------------------------------------------
#pragma comment(lib, "d3d9.lib")			// �����N�Ώۃ��C�u������d3d9.lib��ǉ�
#pragma comment(lib, "d3dx9.lib")			// �����N�Ώۃ��C�u������d3dx9.lib��ǉ�
#pragma comment(lib, "winmm.lib")			// �����N�Ώۃ��C�u������winmm.lib��ǉ�

//==============================================================================
//!	@fn		WinMain
//!	@brief	�G���g���|�C���g
//!	@param	�C���X�^���X�n���h��
//!	@param	�Ӗ��Ȃ�
//!	@param	�N�����̈���������
//!	@param	�E�C���h�E�\�����[�h
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//!	@note	
//==============================================================================
int APIENTRY WinMain(HINSTANCE 	hInstance, 		// �A�v���P�[�V�����̃n���h��
	HINSTANCE 	hPrevInstance,	// ����Windows�o�[�W�����ł͎g���Ȃ�
	LPSTR 		lpszArgs, 		// �N�����̈����i������j
	int 		_winMode)		// �E�C���h�E�\�����[�h
{
	CWindowMain m_winMain;

	if (!m_winMain.Init(hInstance, _winMode)) {
		MessageBox(NULL, TEXT("error init"),
			TEXT("���������s"), MB_OK);
	}
	m_winMain.Update();
}

//******************************************************************************
//	End of file.
//******************************************************************************