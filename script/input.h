//=============================================================================
//
// 入力処理 [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#define KeyPress GetKeyboardPress
#define KeyTrigger GetKeyboardTrigger
#define KeyRepeat GetKeyboardRepeat
#define KeyRelease GetKeyboardRelease

// DirectX用
#define KEY_X	  DIK_X
#define KEY_C     DIK_C
#define KEY_Z     DIK_Z
#define KEY_SPACE DIK_SPACE
#define KEY_UP    DIK_UP
#define KEY_DOWN  DIK_DOWN
#define KEY_RIGHT DIK_RIGHT
#define KEY_LEFT  DIK_LEFT

#define KEY_UP_FLAG    1<<0
#define KEY_DOWN_FLAG  1<<1
#define KEY_RIGHT_FLAG 1<<2
#define KEY_LEFT_FLAG  1<<3


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int key);
bool GetKeyboardTrigger(int key);
bool GetKeyboardRepeat(int key);
bool GetKeyboardRelease(int key);

bool GetMouseLeftPress(void);
bool GetMouseLeftTrigger(void);
bool GetMouseRightPress(void);
bool GetMouseRightTrigger(void);
bool GetMouseCenterPress(void);
bool GetMouseCenterTrigger(void);
long GetMouseAxisX(void);
long GetMouseAxisY(void);
long GetMouseAxisZ(void);
long GetMouseX(void);
long GetMouseY(void);

#endif