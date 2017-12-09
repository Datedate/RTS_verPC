#include "EventKeyInfo.h"

EventKeyInfo::EventKeyInfo(EventKeyInfo::KeyEventType _type) {
	m_keyType = _type;
}


EventKeyInfo::KeyEventType EventKeyInfo::GetKeyType() const {
	return m_keyType;
}
void EventKeyInfo::SetKeyState(BYTE* _keyState) {
	m_keyState = _keyState;
}

BYTE* EventKeyInfo::GetKeyState() const{
	return m_keyState;
}