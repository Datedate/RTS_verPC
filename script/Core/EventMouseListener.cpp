#include "EventMouseListener.h"
#include "EventMouseInfo.h"

MY_NAMESPACE_BEGIN

const std::string EventMouseListener::EVENT_NAME= "Mouse_Name";

EventMouseListener* EventMouseListener::Create()
{
	auto ret = new EventMouseListener();
	ret->Init();
	return ret;
}

EventMouseListener* EventMouseListener::Clone()
{
	auto ret = new EventMouseListener();
	if(ret->Init())
	{

		ret->m_onMouseUp = m_onMouseUp;
		ret->m_onMouseDown = m_onMouseDown;
		ret->m_onMouseMove = m_onMouseMove;
		ret->m_onMouseScroll = m_onMouseScroll;
	}
	else
	{
		delete ret;
		return nullptr;
	}
	return ret;
}

EventMouseListener::EventMouseListener()
	: m_onMouseDown(nullptr)
	, m_onMouseUp(nullptr)
	, m_onMouseMove(nullptr)
	, m_onMouseScroll(nullptr)
{

}

bool EventMouseListener::Init() {
	auto listener = [this](EventInfo* event) {
		auto mouseEvent = static_cast<EventMouseInfo*>(event);
		switch (mouseEvent->GetMouseType())
		{
		case EventMouseInfo::MouseEventType::DOWN:
			if (m_onMouseDown != nullptr)
				m_onMouseDown(mouseEvent);
			break;
		case EventMouseInfo::MouseEventType::UP:
			if (m_onMouseUp != nullptr)
				m_onMouseUp(mouseEvent);
			break;
		case EventMouseInfo::MouseEventType::MOVE:
			if (m_onMouseMove != nullptr)
				m_onMouseMove(mouseEvent);
			break;
		case EventMouseInfo::MouseEventType::SCROLL:
			if (m_onMouseScroll != nullptr)
				m_onMouseScroll(mouseEvent);
			break;
		default:
			break;
		}
	};

	if (EventListenerBase::Init(EVENT_ID::MOUSE_ID, EVENT_NAME, listener))
	{
		return true;
	}

	return false;
}

MY_NAMESPACE_END