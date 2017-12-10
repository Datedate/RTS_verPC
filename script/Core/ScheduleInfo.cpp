#include "ScheduleInfo.h"

ScheduleInfo::ScheduleInfo(const std::function<void()>& _callback) {
	Set(_callback, 0, 0, 0, 100);
}
ScheduleInfo::ScheduleInfo(const std::function<void()>& _callback , unsigned int _num) {
	Set(_callback, _num, 0, 0, 100);
}
ScheduleInfo::ScheduleInfo(const std::function<void()>& _callback , unsigned int _num, float _delta) {
	Set(_callback, _num, _delta, 0, 100);
}
ScheduleInfo::ScheduleInfo(const std::function<void()>& _callback , unsigned int _num, float _delta, float _delay) {
	Set(_callback, _num, _delta, _delay, 100);
}
ScheduleInfo::ScheduleInfo(const std::function<void()>& _callback ,  unsigned int _num, float _delta, float _delay, int _order) {
	Set(_callback, _num, _delta, _delay, _order);
}

void ScheduleInfo::Set(const std::function<void()>& _callback, unsigned int _num, float _delta, float _delay, int _order) {
	m_callback = _callback;
	m_numExec = _num;
	m_delaytime = _delta;
	m_delaytime = _delay;
	m_order = _order;
	m_pause = false;
	m_isOnce = false;

	m_deltatimeStart = m_delaytimeStart = std::chrono::steady_clock::now();
}

void ScheduleInfo::Exec() {
	if (m_pause) return;
	if (m_callback == nullptr) return;

	auto nowTime = std::chrono::steady_clock::now();

	if (m_delaytime != 0) {
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(nowTime - m_delaytimeStart);
		if (m_delaytime > elapsedTime.count())
			return;
	}

	if (m_deltatimeExec != 0) {
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(nowTime - m_deltatimeStart);
		if (m_deltatimeExec > elapsedTime.count())
			return;
	}
	
	m_deltatimeStart = nowTime;

	m_callback();
}

void ScheduleInfo::Destroy() {
	m_callback = nullptr;
}