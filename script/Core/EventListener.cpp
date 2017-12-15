#include "EventListener.h"
#include "Object.h"

EventListenerBase::EventListenerBase()
{}

EventListenerBase::~EventListenerBase()
{}

bool EventListenerBase::Init() {
	m_eventId = EVENT_ID::NO_ID;
	m_eventName = "";
	m_onEvent = nullptr;
	m_isRegistered = false;
	m_paused = true;
	m_isEnabled = true;
	return true;

}
bool EventListenerBase::Init(EVENT_ID _id, const std::string& _eventName, const std::function<void(EventInfo*)>& _callback) {
	m_eventId = _id;
	m_eventName = _eventName;
	m_onEvent = _callback;
	m_isRegistered = false;
	m_paused = true;
	m_isEnabled = true;
	return true;
}
void EventListenerBase::SetStatus(EVENT_ID _id, const std::string& _eventName, const std::function<void(EventInfo*)>& _callback) {
	m_eventId = _id;
	m_eventName = _eventName;
	m_onEvent = _callback;
}
void EventListenerBase::SetTarget(Object* _target) {
	m_target = _target;
}
Object* EventListenerBase::GetTarget()const {
	return m_target;
}
void EventListenerBase::SetPaused(bool _paused) {
	m_paused = _paused;
}
bool EventListenerBase::IsPaused() const{
	return m_paused;
}
void EventListenerBase::SetRegistered(bool _registered) {
	m_isRegistered = _registered;
}
bool EventListenerBase::IsRegistered()const {
	return m_isRegistered;
}
EventListenerBase::EVENT_ID EventListenerBase::GetID() const {
	return m_eventId;
}
const std::string& EventListenerBase::GetEventName() const {
	return m_eventName;
}
void EventListenerBase::SetPriority(int _priority) {
	m_priority = _priority;
}
int EventListenerBase::GetdPriority() const {
	return m_priority;
}