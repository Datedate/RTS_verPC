#pragma once
/**
**   DebugWindow�N���X
**
** @brief �f�o�b�O�p�E�C���h�E�̐����E����
** @details �V���O���g���Ŏ���
**			
*/
#include <iostream>

class DebugWindow
{
public:
	static DebugWindow &GetInstance();		// �C���X�^���X�̎Q��
private:
	DebugWindow() {};
	~DebugWindow() {};
	DebugWindow(const DebugWindow& _debug) {};
	const DebugWindow& operator= (const DebugWindow&) {};
public:
	void Create();
	void Destroy();
private:
	static FILE* fp;
};

