#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ConfigSystem.h""
#include <vector>
#include <string>

MY_NAMESPACE_BEGIN

class Object
{
public:
	Object();
	~Object();
	virtual bool Init();
	static Object* Create();
	virtual void Update();
	virtual void AddChild(Object*);
	virtual void Release();
	void SetName(std::string _name) { m_name = _name; }
	void SetZOrder(int _z) { m_zorder = _z; }
	void SetVisible(bool _flag) { m_visible = _flag; }
	void Exit();
protected:
	void SetParent(Object*);
protected:
	std::vector<Object*>	m_children;
	Object*					m_parent;
	bool					m_visible;
	std::string				m_name;
	int						m_zorder;
};

MY_NAMESPACE_END

#endif