
#include "InputManager.h"
#include "EventManager.h"
#include "EventListener.h"
#include "EventMouseListener.h"
#include "EventKeyListener.h"
#include "EventMouseInfo.h"
#include "EventKeyInfo.h"

EventManager::EventManager() {}
EventManager::~EventManager() {}

bool EventManager::Init(HINSTANCE _hInstance , HWND _hwnd) {
	m_inputMng = new InputManager();
	if (m_inputMng->Init(_hInstance, _hwnd))
		return true;
	return false;
}

void EventManager::AddEvent(EventListenerBase* _value , Object* _target) {
	_value->SetTarget(_target);
	m_eventContainer.push_back(_value);
}

void EventManager::Excute() {
	if (m_eventContainer.empty()) return;
	
	for (auto itr = m_eventContainer.begin(); itr != m_eventContainer.end(); itr++) {
		switch ((*itr)->GetID())
		{
		case EventListenerBase::EVENT_ID::MOUSE_ID:
			MouseCallBack((*itr));
			break;
		case EventListenerBase::EVENT_ID::KEYBOARD_ID:
			KeyBoardCallBack((*itr));
			break;
		case EventListenerBase::EVENT_ID::COLLISION_ID:
			break;
		case EventListenerBase::EVENT_ID::CUSTOM_ID:
			break;
		default:
			break;
		}
	}
}

void EventManager::MouseCallBack(EventListenerBase* _listener) {
	auto listener = static_cast<EventMouseListener*>(_listener);

	float x = m_inputMng->GetMouseCurrentX();
	float y = m_inputMng->GetMouseCurrentY();

	if (listener->m_onMouseDown != nullptr) {
		if (m_inputMng->GetMouseTrigger()) {
			EventMouseInfo	event(EventMouseInfo::MouseEventType::DOWN);
			event.SetPosition(x, y);
			event.SetTarget(listener->GetTarget());
			listener->m_onMouseDown(&event);
		}
	}
	if (listener->m_onMouseUp != nullptr) {
		if (m_inputMng->GetMouseRelease()) {
			EventMouseInfo	event(EventMouseInfo::MouseEventType::UP);
			event.SetPosition(x, y);
			event.SetTarget(listener->GetTarget());
			listener->m_onMouseUp(&event);
		}		
	}
	if (listener->m_onMouseMove != nullptr) {
		EventMouseInfo	event(EventMouseInfo::MouseEventType::MOVE);
		event.SetPosition(x, y);
		event.SetTarget(listener->GetTarget());
		listener->m_onMouseMove(&event);
	}
	if (listener->m_onMouseScroll != nullptr) {
		EventMouseInfo	event(EventMouseInfo::MouseEventType::SCROLL);
		event.SetPosition(x, y);
		event.SetTarget(listener->GetTarget());
		listener->m_onMouseScroll(&event);
	}
}

void EventManager::KeyBoardCallBack(EventListenerBase* _listener) {
	auto listener = static_cast<EventKeyListener*>(_listener);

	if (listener->m_onKeyDown != nullptr) {
		EventKeyInfo	event(EventKeyInfo::KeyEventType::DOWN);
		event.SetKeyState(m_inputMng->GetKeyStateTrigger());
		event.SetTarget(listener->GetTarget());
		listener->m_onKeyDown(&event);
	}
	if (listener->m_onKeyUp != nullptr) {
		EventKeyInfo	event(EventKeyInfo::KeyEventType::UP);
		event.SetKeyState(m_inputMng->GetKeyStateRelease());
		event.SetTarget(listener->GetTarget());
		listener->m_onKeyUp(&event);
	}
	if (listener->m_onKeyPress != nullptr) {
		EventKeyInfo	event(EventKeyInfo::KeyEventType::PRESS);
		event.SetKeyState(m_inputMng->GetKeyState());
		event.SetTarget(listener->GetTarget());
		listener->m_onKeyPress(&event);
	}
}

void EventManager::Clear() {
	m_eventContainer.clear();
}

void EventManager::Exit() {
	m_inputMng->Exit();
	m_eventContainer.clear();
}
