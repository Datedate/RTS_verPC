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

	// コンソールウインドウ生成
	::AllocConsole();

	// 標準出力の割り当て
	freopen_s(&fp, "CON", "w", stdout);
}

void DebugWindow::Destroy() {
	// ウインドウ終了
	fclose(fp);
	::FreeConsole();
}