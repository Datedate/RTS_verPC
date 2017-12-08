#ifndef _SCHEDULE_INFO_H_
#define _SCHEDULE_INFO_H_

#include <functional>

class ScheduleInfo
{
public:
	ScheduleInfo() {};
	ScheduleInfo(const std::function<void()>& _callback);
	ScheduleInfo(const std::function<void()>& _callback, unsigned int _num);
	ScheduleInfo(const std::function<void()>& _callback, unsigned int _num, float _delta);
	ScheduleInfo(const std::function<void()>& _callback, unsigned int _num, float _delta, float _delay);
	ScheduleInfo(const std::function<void()>& _callback, unsigned int _num, float _delta, float _delay, int _order);
	~ScheduleInfo() {};
	
private:
	std::function<void()>	m_callback;
	unsigned int			m_numExec;
	float					m_deltatimeExec;
	float					m_delaytime;
	int						m_order;
	bool					m_pause;
};

#endif
