#include "DebugWindow.h"
#include <io.h>
#include <Windows.h>
#include <Fcntl.h>

FILE* DebugWindow::fp = nullptr;

DebugWindow& DebugWindow::GetInstance() {
	static DebugWindow *instance = nullptr;
	if (!instance)
		instance = new DebugWindow();
	return *instance;
}

void DebugWindow::Create() {

	// �R���\�[���E�C���h�E����
	::AllocConsole();

	// �W���o�͂̊��蓖��
	freopen_s(&fp, "CON", "w", stdout);
}

void DebugWindow::Destroy() {
	// �E�C���h�E�I��
	fclose(fp);
	::FreeConsole();
}