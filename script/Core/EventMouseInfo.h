#ifndef _EVENT_MOUSE_INFO_H_
#define _EVENT_MOUSE_INFO_H_

#include "EventInfo.h"
#include "Rectangle.h"

class EventMouseInfo : public EventInfo
{
public:
	enum class MouseEventType {
		NONE,
		DOWN,
		UP,
		MOVE,
		SCROLL
	};

public:
	EventMouseInfo() {};
	EventMouseInfo(MouseEventType _type);
	~EventMouseInfo() {};
	MouseEventType GetMouseType();
	void SetPosition(float _x,float _y);
	Vector2 GetPosition()const {
		return m_pos;
	}
private:
	MouseEventType	m_mouseTyoe;
	Vector2			m_pos;
};

#endif
