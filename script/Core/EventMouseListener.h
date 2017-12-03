#ifndef _EVENT_MOUSE_LISTENER_H_
#define _EVENT_MOUSE_LISTENER_H_

#include "EventListener.h"

MY_NAMESPACE_BEGIN

class EventMouseInfo;

class EventMouseListener : public EventListenerBase
{
public:
	EventMouseListener() {};
	~EventMouseListener() {};

	static const std::string EVENT_NAME;
	static EventMouseListener* Create();

	EventMouseListener* Clone();

	std::function<void(EventMouseInfo* _event)> m_onMouseDown;
	std::function<void(EventMouseInfo* _event)> m_onMouseUp;
	std::function<void(EventMouseInfo* _event)> m_onMouseMove;
	std::function<void(EventMouseInfo* _event)> m_onMouseScroll;

	bool Init();
};

MY_NAMESPACE_END

#endif