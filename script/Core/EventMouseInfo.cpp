#include "EventMouseInfo.h"

EventMouseInfo::EventMouseInfo(EventMouseInfo::MouseEventType _type) {
	m_mouseTyoe = _type;
}

EventMouseInfo::MouseEventType EventMouseInfo::GetMouseType() {
	return m_mouseTyoe;
}

void EventMouseInfo::SetPosition(float _x, float _y) {
	m_pos.x = _x;
	// cocos2dx�g�݂��ݗ\��Ȃ̂ł��𔽓]
	m_pos.y = _y;
}