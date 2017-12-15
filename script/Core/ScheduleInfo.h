#ifndef _SCHEDULE_INFO_H_
#define _SCHEDULE_INFO_H_

#include <functional>
#include <chrono>

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

//	void Set(const std::function<void()>& _callback);
//	void Set(const std::function<void()>& _callback, unsigned int _num);
//	void Set(const std::function<void()>& _callback, unsigned int _num, float _delta);
//	void Set(const std::function<void()>& _callback, unsigned int _num, float _delta, float _delay);
	void SetFunction(const std::function<void()>& _callback){
		m_callback = _callback;
	}
	void SetNum(int _num) {
		m_numExec = _num;
	}
	void SetDeltaTime(float _delta) {
		m_delaytime = _delta;
	}
	void SetDelay(float _delay) {
		m_delaytime = _delay;
	}
	void SetOrder(int _order) {
		m_order = _order;
	}
	void SetOnce() {
		m_isOnce = true;
	}

	void Exec();
	void Destroy();
private:
	void Set(const std::function<void()>& _callback, unsigned int _num, float _delta, float _delay, int _order);

	std::function<void()>	m_callback;
	unsigned int			m_numExec ;
	float					m_deltatime;
	float					m_delaytime;
	std::chrono::steady_clock::time_point	  m_deltatimeStart;
	std::chrono::steady_clock::time_point	  m_delaytimeStart;
	int						m_order;
	bool					m_pause;
	bool					m_isOnce;
	bool					m_isfirstflg;
};

#endif
