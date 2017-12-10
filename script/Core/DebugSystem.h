#ifndef _DEBUG_SYSTEM_H_
#define _DEBUG_SYSTEM_H_

#include <d3dx9.h>
#include "SingletonTemplate.h"

class DebugSystem : public SingletonTemplate<DebugSystem>
{
public:
	friend SingletonTemplate<DebugSystem>;

	bool Init();
	void DebugDrawText(const char* _buf, int x, int y) const;
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
};

#endif
