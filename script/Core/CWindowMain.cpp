#include "CWindowMain.h"
#include <thread>

//==============================================================================
//!	@fn		WindowProc
//!	@brief	�E�C���h�E�v���V�[�W��
//!	@param	�E�C���h�E�n���h��
//!	@param	���b�Z�[�W
//!	@param	W�p�����[�^
//!	@param	L�p�����[�^
//!	@retval	�I����
//==============================================================================
LRESULT CALLBACK MainWndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {	
	CWindowMain* pThisPtr = (CWindowMain*)GetWindowLong(_hWnd, GWL_USERDATA);
	if (pThisPtr)
		return (pThisPtr->LocalWndProc(_hWnd, _msg, _wParam, _lParam));
	else
		return (DefWindowProc(_hWnd, _msg, _wParam, _lParam));
}

//==============================================================================
//!	@fn		TimerProc
//!	@brief	�P�U�������ɃC�x���g�I�u�W�F�N�g���Z�b�g����
//!	@param	�^�C�}�h�c
//!	@param	���g�p
//!	@param	���g�p
//!	@param	���g�p
//!	@param	���g�p
//!	@retval	�Ȃ�
//==============================================================================


void CALLBACK TimerProc(UINT, UINT, DWORD dwUser, DWORD, DWORD)
{
	reinterpret_cast<CWindowMain*>(dwUser)->LocalTimeProc();
}


// �������֐�
bool CWindowMain::Init(HINSTANCE hInstance, int _winMode) {
	
	m_hInstance = hInstance;

	// �E�C���h�E����
	if (!InitWindow()) return FALSE;

	// �E�C���h�E��\������
	ShowWindow(m_hWnd, _winMode);
	UpdateWindow(m_hWnd);

	// ���������i�Q�[���N���X�A�C�x���g�����A�^�C�}�[�Z�b�g�j
	if (!InitGame()) {
		m_game.Exit();
		return FALSE;
	}
	if (!InitEvent()) return FALSE;
	InitTimer();

	// �Q�[�����C���֐��X���b�h�N��
	m_gamethread = std::thread(&CWindowMain::GameMain, this);
	return true;
}

bool CWindowMain::InitWindow() {
	WNDCLASSEX		wcex;						// �E�C���h�E�N���X�\����
	int				width = SCREEN_X;			// �E�C���h�E�̕� �v�Z�p���[�N
	int				height = SCREEN_Y;			// �E�C���h�E�̍��� �v�Z�p���[�N

	wcex.hInstance = m_hInstance;			// �C���X�^���X�l�̃Z�b�g
	wcex.lpszClassName = NAME;					// �N���X��
	wcex.lpfnWndProc = (WNDPROC)MainWndProc;		// �E�C���h�E���b�Z�[�W�֐�
	wcex.style = 0;					// �E�C���h�E�X�^�C��
	wcex.cbSize = sizeof(WNDCLASSEX);	// �\���̂̃T�C�Y
	wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ���[�W�A�C�R��
	wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// �X���[���A�C�R��
	wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// �J�[�\���X�^�C��
	wcex.lpszMenuName = 0; 					// ���j���[�Ȃ�
	wcex.cbClsExtra = 0;					// �G�L�X�g���Ȃ�
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// �w�i�F��

	if (!RegisterClassEx(&wcex)) return FALSE;	// �E�C���h�E�N���X�̓o�^

	if (FULLSCREEN) {
		m_hWnd = CreateWindow(
			NAME,							// �E�B���h�E�N���X�̖��O
			TITLE,							// �^�C�g��
			WS_VISIBLE | WS_POPUP,			// �E�B���h�E�X�^�C��
			0, 0,							// �E�B���h�E�ʒu �c, ��
			SCREEN_X, SCREEN_Y,				// �E�B���h�E�T�C�Y
			NULL,							// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,					// ���j���[�Ȃ�
			m_hInstance,						// �C���X�^���X�n���h��
			(LPVOID)NULL);					// �ǉ������Ȃ�
	}
	else {
		RECT	rWindow, rClient;

		m_hWnd = CreateWindow(
			NAME,							// �E�B���h�E�N���X�̖��O
			TITLE,							// �^�C�g��
			WS_CAPTION | WS_SYSMENU,		// �E�B���h�E�X�^�C��
			0, 0,							// �E�B���h�E�ʒu �c, ��(���ƂŒ����Ɉړ������܂�)
			SCREEN_X, SCREEN_Y,				// �E�B���h�E�T�C�Y
			HWND_DESKTOP,					// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,					// ���j���[�Ȃ�
			m_hInstance,						// �C���X�^���X�n���h��
			(LPVOID)NULL);					// �ǉ������Ȃ�

											// �E�C���h�E�T�C�Y���Čv�Z�iMetrics�����ł́A�t���[���f�U�C���ŃN���C�A���g�̈�T�C�Y���ς���Ă��܂��̂Łj
		GetWindowRect(m_hWnd, &rWindow);
		GetClientRect(m_hWnd, &rClient);
		width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + SCREEN_X;
		height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + SCREEN_Y;
		SetWindowPos(
			m_hWnd,
			NULL,
			GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
			width - 1,
			height - 1,
			SWP_NOZORDER);
	}
	SetWindowLong(m_hWnd, GWLP_USERDATA, (LONG)this);
	if (!m_hWnd) {
		return false;
	}
	return true;
}

bool CWindowMain::InitGame() {
	if (!m_game.Init(m_hWnd, m_hInstance, FULLSCREEN , SCREEN_X, SCREEN_Y)) {
		MessageBox(m_hWnd, "ERROR!", "GameInit Error", MB_OK);
		return false;
	}
	return true;
}

bool CWindowMain::InitEvent() {
	// �C�x���g�n���h������
	m_eventHandle = CreateEvent(NULL, false, false, NULL);
	if (m_eventHandle == NULL) {
		MessageBox(m_hWnd, "ERROR!!", "CreateEvent �G���[", MB_OK);
		return false;
	}
	return true;
}

void CWindowMain::InitTimer() {
	// �C�x���g�^�C�}�[���Z�b�g����
	timeBeginPeriod(1);			// �^�C�}�̕���\�͂��P�����ɂ���
								// 16ms���Ƀ����o�̃R�[���o�b�N�֐����Ă΂��
								// �^�C�}�[�R�[���o�b�N�֐����Ń����o�֐����g�p���邽��
								// ���C���^�[�v���b�g�L���X�g�Ŏ����̃|�C���^���^�C�}�[�R�[���o�b�N�֐��ɓn���Ă��܂��B
	m_timerID = timeSetEvent(16, 1, TimerProc, reinterpret_cast<DWORD>(this), TIME_PERIODIC);
}

// �X�V�֐�
void CWindowMain::Update() {
	MSG msg;

	while (1) {	// ���b�Z�[�W����[�v
		if (!GetMessage(&msg, NULL, 0, 0)) {	// ���b�Z�[�W���擾
			break;
		}
		else {
			TranslateMessage(&msg); 			// �������b�Z�[�W�ւ̃R���o�[�g�j
			DispatchMessage(&msg); 				// ���b�Z�[�W��WndProc�֑���
		}
	}
}

// �I���֐�
void CWindowMain::Exit() {
	m_game.SetEndFlag();
	m_gamethread.join();

	if (m_timerID) timeKillEvent(m_timerID);	// �}���`���f�B�A�^�C�}�̏I��
	timeEndPeriod(1);							// �^�C�}�̕���\�͂��Ƃɖ߂�

	m_game.Exit();
}

// ���[�J���E�C���h�E�v���V�[�W��
LRESULT CWindowMain::LocalWndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {
	switch (_msg)
	{
	case WM_KEYDOWN:
		if (_wParam == VK_ESCAPE) {
			Exit();
			PostQuitMessage(0);
		}
		break;
	case WM_DESTROY:
		Exit();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
		break;
	}
	return 0;
}

void CWindowMain::LocalTimeProc() {
	GameSetEvent();
}


void CWindowMain::GameMain() {
	while (1) {
		/*
		DWORD sts = WaitForSingleObject(m_eventHandle, 1000);	// �C�x���g�t���O���Z�b�g�����̂�҂i1000ms�Ń^�C���A�E�g�j
		if (sts == WAIT_FAILED) {
			break;
		}
		else if (sts == WAIT_TIMEOUT) {
			if (m_game.IsEnd()) {
				break;
			}
			continue;
		}
		*/
		m_game.Exec();
	}

	m_game.SetEndFlag();
}

void CWindowMain::GameSetEvent() {
	if (!m_game.IsEnd()) {
		SetEvent(m_eventHandle);
	}
}
