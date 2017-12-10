#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ConfigSystem.h"
#include <vector>
#include <string>

class ScheduleManager;

class Object
{
public:
	Object();
	~Object();
	virtual bool Init();
	static Object* Create();
	void Update();
	virtual void AddChild(Object*);
	virtual void AddChild(Object*, int _zorder);
	virtual void RemoveAllChildren();
	virtual void RemoveChild();
	virtual void RemoveChild(std::string _childname);
	virtual void Release();
	void SetName(std::string _name) { m_name = _name; }
	void SetZOrder(int _z) { m_zorder = _z; }
	void SetVisible(bool _flag) { m_visible = _flag; }
	void Exit();

	Object* GetParent()const;
	bool IsVisible()const;
	std::string GetName()const;
	int GetOrder()const;
protected:
	void SetParent(Object*);
protected:
	std::vector<Object*>	m_children;
	Object*					m_parent;
	bool					m_visible;
	std::string				m_name;
	int						m_zorder;
};

#endif