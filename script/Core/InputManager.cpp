#include "InputManager.h"

bool InputManager::Init(HINSTANCE _hInstance, HWND _hwnd) {
	bool    initflag = true;

	if (!m_pDirInput)
	{
		HRESULT hr;
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pDirInput, NULL);
		if (FAILED(hr))
			return false;
	}

	// キーボードの初期化
	if (!InitKeyboard(_hInstance, _hwnd))
		return false;

	// マウスの初期化
	if (!InitMouse(_hInstance, _hwnd))
		return false;

	m_hwnd = _hwnd;

	return true;
}

void InputManager::Update() {
	// キーボードの更新
	UpdateKeyboard();

	// マウスの更新
	UpdateMouse();
}

void InputManager::Exit() {
	// キーボードの終了処理
	ExitKeyboard();

	// マウスの終了処理
	ExitMouse();

	if (m_pDirInput)
	{
		m_pDirInput->Release();
		m_pDirInput = NULL;
	}
}

bool InputManager::InitKeyboard(HINSTANCE _hInstance, HWND _hwnd) {
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = m_pDirInput->CreateDevice(GUID_SysKeyboard, &m_pDirDevKeyboard, NULL);
	if (FAILED(hr) || m_pDirDevKeyboard == NULL)
	{
		MessageBox(_hwnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return false;
	}

	// データフォーマットを設定
	hr = m_pDirDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(_hwnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDirDevKeyboard->SetCooperativeLevel(_hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(_hwnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDirDevKeyboard->Acquire();

	return true;
}

bool InputManager::InitMouse(HINSTANCE _hInstance, HWND _hwnd) {
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = m_pDirInput->CreateDevice(GUID_SysMouse, &m_pDirDevMouse, NULL);
	if (FAILED(hr) || m_pDirDevMouse == NULL)
	{
		MessageBox(_hwnd, "マウスがねぇ！", "警告！", MB_ICONWARNING);
		return false;
	}

	// データフォーマットを設定
	hr = m_pDirDevMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		MessageBox(_hwnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_pDirDevMouse->SetCooperativeLevel(_hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(_hwnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return false;
	}

	// デバイスの設定
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = m_pDirDevMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDirDevMouse->Acquire();

	return true;
}

void InputManager::UpdateKeyboard() {
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, m_keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = m_pDirDevKeyboard->GetDeviceState(sizeof(m_keyState), m_keyState);
	if (SUCCEEDED(hr))
	{
		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			// トリガーとリリースを取得
			m_keyStateTrigg[cnt] = (m_keyState[cnt] ^ keyStateOld[cnt])& m_keyState[cnt];
			m_keyStateRelea[cnt] = (m_keyState[cnt] ^ keyStateOld[cnt])& keyStateOld[cnt];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		hr = m_pDirDevKeyboard->Acquire();
	}
}

void InputManager::UpdateMouse() {
	HRESULT hr;
	DIMOUSESTATE2 mouseStateOld;

	GetCursorPos(&m_mousePos);
	ScreenToClient(m_hwnd, &m_mousePos);

	// 前回のデータを保存
	mouseStateOld = m_mouseState;

	// デバイスからデータを取得
	hr = m_pDirDevMouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState);
	if (SUCCEEDED(hr))
	{ 
		for (int cnt = 0; cnt < 8; cnt++)
		{
			m_mouseStateTrigg.rgbButtons[cnt] = ((mouseStateOld.rgbButtons[cnt] ^ m_mouseState.rgbButtons[cnt]) & m_mouseState.rgbButtons[cnt]);
			m_mouseStateRelea.rgbButtons[cnt] = ((mouseStateOld.rgbButtons[cnt] ^ m_mouseState.rgbButtons[cnt]) & mouseStateOld.rgbButtons[cnt]);
		}
	}
	else
	{
		m_pDirDevMouse->Acquire();
	}

}

void InputManager::ExitKeyboard() {
	if (m_pDirDevKeyboard)
	{
		m_pDirDevKeyboard->Unacquire();

		m_pDirDevKeyboard->Release();
		m_pDirDevKeyboard = NULL;
	}
}

void InputManager::ExitMouse() {
	if (m_pDirDevMouse)
	{
		m_pDirDevMouse->Unacquire();

		m_pDirDevMouse->Release();
		m_pDirDevMouse = NULL;
	}
}


bool InputManager::GetKeyboardPress(int _key) {
	return ((m_keyState[_key] & 0x80) != 0);
}
bool InputManager::GetKeyboardTrigger(int _key) {
	return ((m_keyStateTrigg[_key] & 0x80) != 0);
}
bool InputManager::GetKeyboardRelease(int _key) {
	return ((m_keyStateRelea[_key] & 0x80) != 0);
}

bool InputManager::GetMousePress() {
	return ((m_mouseState.rgbButtons[0] & 0x80) != 0);
}
bool InputManager::GetMouseTrigger() {
	return ((m_mouseStateTrigg.rgbButtons[0] & 0x80) != 0);
}
bool InputManager::GetMouseRelease() {
	return ((m_mouseStateRelea.rgbButtons[0] & 0x80) != 0);
}
long InputManager::GetMouseAxisX() {
	return m_mouseState.lX;
}
long InputManager::GetMouseAxisY() {
	return m_mouseState.lY;
}
long InputManager::GetMouseAxisZ() {
	return m_mouseState.lZ;
}
long InputManager::GetMouseCurrentX() {
	return m_mousePos.x;
}
long InputManager::GetMouseCurrentY() {
	return m_mousePos.y;
}