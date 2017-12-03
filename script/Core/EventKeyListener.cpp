#include "EventKeyListener.h"
#include "EventKeyInfo.h"

MY_NAMESPACE_BEGIN

const std::string EventKeyListener::EVENT_NAME = "Keyboard_Name";

EventKeyListener* EventKeyListener::Create()
{
	auto ret = new EventKeyListener();
	ret->Init();
	return ret;
}

EventKeyListener* EventKeyListener::Clone()
{
	auto ret = new EventKeyListener();
	if (ret->Init())
	{
		ret->m_onKeyDown = m_onKeyDown;
		ret->m_onKeyUp = m_onKeyUp;
		ret->m_onKeyPress = m_onKeyPress;
	}
	else
	{
		delete ret;
		return nullptr;
	}
	return ret;
}

EventKeyListener::EventKeyListener()
	: m_onKeyDown(nullptr)
	, m_onKeyUp(nullptr)
	, m_onKeyPress(nullptr)
{

}

bool EventKeyListener::Init() {
	auto listener = [this](EventInfo* event) {
		auto keyboardEvent = static_cast<EventKeyInfo*>(event);
		switch (keyboardEvent->GetKeyType())
		{
		case EventKeyInfo::KeyEventType::DOWN:
			if (m_onKeyDown != nullptr)
				m_onKeyDown(keyboardEvent);
			break;
		case EventKeyInfo::KeyEventType::UP:
			if (m_onKeyUp != nullptr)
				m_onKeyUp(keyboardEvent);
			break;
		case EventKeyInfo::KeyEventType::PRESS:
			if (m_onKeyPress != nullptr)
				m_onKeyPress(keyboardEvent);
			break;
		default:
			break;
		}
	};

	if (EventListenerBase::Init(EVENT_ID::KEYBOARD_ID, EVENT_NAME, listener))
	{
		return true;
	}

	return false;
}

MY_NAMESPACE_END