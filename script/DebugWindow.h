#pragma once
/**
**   DebugWindowクラス
**
** @brief デバッグ用ウインドウの生成・操作
** @details シングルトンで実装
**			
*/
#include <iostream>

class DebugWindow
{
public:
	static DebugWindow &GetInstance();		// インスタンスの参照
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

