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
}