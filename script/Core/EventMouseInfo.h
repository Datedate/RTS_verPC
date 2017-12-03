#ifndef _EVENT_MOUSE_INFO_H_
#define _EVENT_MOUSE_INFO_H_

#include "EventInfo.h"
#include "Rectangle.h"

MY_NAMESPACE_BEGIN

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
private:
	MouseEventType	m_mouseTyoe;
	Vector2			m_pos;
};

MY_NAMESPACE_END
#endif
