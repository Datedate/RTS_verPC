#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include <functional>
#include "ConfigSystem.h"
#include <string>

class EventInfo;
class Object;

class EventListenerBase
{
public:
	enum class EVENT_ID {
		MOUSE_ID,
		KEYBOARD_ID,
		COLLISION_ID,
		CUSTOM_ID
	};
public:
	EventListenerBase();
	~EventListenerBase();
	virtual EventListenerBase*	Clone() = 0;

	bool Init(EVENT_ID _id, const std::string& _evnetName, const std::function<void(EventInfo*)>& callback);

	void SetEnabled(bool enabled) { m_isEnabled = enabled; }
	bool IsEnabled() const { return m_isEnabled; }
	void SetTarget(Object* _target);
	Object* GetTarget()const;
protected:
	void SetPaused(bool paused);
	bool IsPaused() const;
	void SetRegistered(bool registered);
	bool IsRegistered() const;
	EVENT_ID GetID() const;
	const std::string& GetEventName() const;
	void SetPriority(int _priority);
	int GetdPriority() const;

	friend class EventManager;

	// ÉÅÉìÉoïœêî
	std::function<void(EventInfo*)> m_onEvent;
	EVENT_ID						m_eventId;                             
	std::string						m_eventName;
	bool							m_isRegistered;                     
	int								m_priority;   
	bool						    m_paused;          
	bool							m_isEnabled;
	Object*							m_target;
};

#endif