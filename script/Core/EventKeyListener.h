#ifndef _EVENT_KEY_LISTENER_H_
#define _EVENT_KEY_LISTENER_H_

#include "EventListener.h"

MY_NAMESPACE_BEGIN

class EventKeyInfo;

class EventKeyListener : public EventListenerBase
{
public:
	EventKeyListener() {};
	~EventKeyListener() {};

	static const std::string EVENT_NAME;
	static EventKeyListener* Create();

	EventKeyListener* Clone();

	std::function<void(EventKeyInfo* _event)> m_onKeyDown;
	std::function<void(EventKeyInfo* _event)> m_onKeyUp;
	std::function<void(EventKeyInfo* _event)> m_onKeyPress;

	bool Init();
};


MY_NAMESPACE_END

#endif