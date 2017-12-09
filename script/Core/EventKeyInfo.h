#ifndef _EVENT_KEY_INFO_H_
#define _EVENT_KEY_INFO_H_

#include "EventInfo.h"
#include <Windows.h>

class EventKeyInfo : public EventInfo
{
public:
	enum class KeyEventType {
		NONE,
		DOWN,
		UP,
		PRESS,
	};
public:
	EventKeyInfo() {};
	EventKeyInfo(KeyEventType _type);
	~EventKeyInfo() {};
	KeyEventType GetKeyType()const;
	void SetKeyState(BYTE* _keyState);
	BYTE* GetKeyState()const;
private:
	BYTE*			m_keyState;
	KeyEventType	m_keyType;
};


#endif
