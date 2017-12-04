#pragma once
#include <Windows.h>
#include "CGame.h"
#include <thread>

//-----------------------------------------------------------------------------
// �}�N���̒�`
//-----------------------------------------------------------------------------
#define		NAME			"win32A"
#define		TITLE			"RTS"
#define		SCREEN_X		656
#define		SCREEN_Y		959
#define		FULLSCREEN		0				// �t���X�N���[���t���O

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);			// �E�C���h�E�v���V�[�W��
void CALLBACK TimerProc(UINT, UINT, DWORD dwUser, DWORD, DWORD);

class CWindowMain
{
public:
	CWindowMain() {};
	~CWindowMain() {};
	bool Init(HINSTANCE _hInstance, int _winMode);		// �������֐�
	bool InitWindow();
	bool InitGame();
	bool InitEvent();
	void InitTimer();
	void Update();										// �X�V�֐�
	void Exit();										// �I���֐�
	void GameMain();									// �Q�[�����C��
	void GameSetEvent();								// �C�x���g�V�O�i�����
	LRESULT LocalWndProc(HWND, UINT, WPARAM, LPARAM);	// ���[�J���E�C���h�E�v���V�[�W��
	void LocalTimeProc();
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
private:
	std::thread m_gamethread;
	int m_timerID;					// �^�C�}�[ID
	HANDLE m_eventHandle;			// ��������
private:
	CGame m_game;					// �Q�[���̒����N���X
};


