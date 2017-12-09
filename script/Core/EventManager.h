#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include <vector>
#include <string>
#include <Windows.h>
#include "SingletonTemplate.h"

class EventListenerBase;
class InputManager;
class Object;

class EventManager : public SingletonTemplate<EventManager>
{
public:
	

public:
	friend SingletonTemplate<EventManager>;
	bool Init(HINSTANCE _hInstance, HWND _hwnd);
	void Excute();
	void AddEvent(EventListenerBase* _value,Object* _target);
	void Clear();
	void Exit();
private:
	EventManager();
	~EventManager();

	void MouseCallBack(EventListenerBase* _listener);
	void KeyBoardCallBack(EventListenerBase* _listener);

	std::vector<EventListenerBase*> m_eventContainer;
	InputManager*					m_inputMng;
};

#endif
