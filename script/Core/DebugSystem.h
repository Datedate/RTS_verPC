#ifndef _DEBUG_SYSTEM_H_
#define _DEBUG_SYSTEM_H_

#include <d3dx9.h>
#include <string>
#include <vector>
#include "SingletonTemplate.h"

struct DEBUG_TEXT {
	DEBUG_TEXT(){}
	DEBUG_TEXT(std::string _buf, int _x, int _y
		) {
		buf = _buf; 
		x = _x;
		y = _y;
	}
	std::string buf;
	int x, y;
	int width, height;
};

class DebugSystem : public SingletonTemplate<DebugSystem>
{
public:
	friend SingletonTemplate<DebugSystem>;

	bool Init();
	void Push(const std::string _buf, int x, int y);
	void DebugDrawText() const;
	void Clear();
private:
	DebugSystem() {};
	~DebugSystem() {
		if (m_font != nullptr) {
			m_font->Release();
			m_font = nullptr;
		}
	};
private:
	LPD3DXFONT		m_font;
	std::vector<DEBUG_TEXT> m_bufContainer;
};

#endif
