#ifndef _EVENT_INFO_H_
#define _EVENT_INFO_H_

#include "ConfigSystem.h"

MY_NAMESPACE_BEGIN

class Object;

class EventInfo {
public:
	enum class EVENT_TYPE {
		MOUSE,
		KEYBOARD,
		COLLISION,
		CUSTOM
	};

	EventInfo() {}
	EventInfo(EVENT_TYPE _type) {
		m_type = _type;
		m_flag = false;
		m_target = nullptr;
	};
	~EventInfo(){}

	EVENT_TYPE GetType() {
		return m_type;
	}
	void StopEvent() {
		m_flag = true;
	}
	bool isStop() {
		return m_flag;
	}
	Object* GetTarget() {
		return m_target;
	}
	void SetTarget(Object* _target) {
		m_target = _target;
	}
protected:
	

	EVENT_TYPE m_type;
	bool	   m_flag;
	Object*	   m_target;
};

MY_NAMESPACE_END

#endif
