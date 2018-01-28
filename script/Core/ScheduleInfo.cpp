#define _CRT_SECURE_NO_WARNINGS 1
#include "ScheduleInfo.h"
#include "DebugSystem.h"

ScheduleInfo::ScheduleInfo(const std::function<void()>& _callback) {
	Set(_callback, -10, 0, 0, 100);
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
	m_deltatime = _delta;
	m_delaytime = _delay;
	m_order = _order;
	m_pause = false;
	m_isOnce = false;
	m_isfirstflg = true;
}

void ScheduleInfo::FirstCallback() {
	if (m_delaytime == 0)
		m_callback();
	m_deltatimeStart = m_delaytimeStart = std::chrono::steady_clock::now();
	m_isfirstflg = false;
}

void ScheduleInfo::Exec() {
	// 呼び出すコールバック関数がない時処理しない
	if (m_callback == nullptr) return;

	// 初回だけ強制的に呼び出す（m_delayTimeが０の時）
	if (m_isfirstflg) {
		FirstCallback();
	}

	if (m_pause) return;
	if (m_numExec > -5 && m_numExec < 0 ) return;

	auto nowTime = std::chrono::steady_clock::now();

	if (m_delaytime != 0) {
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - m_delaytimeStart);
		//char buf[512] = "";
		//sprintf(buf, "%d", (int)elapsedTime.count()/1000);
		//DebugSystem::GetInstance()->Push(buf, 10, 10);
		if (m_delaytime*1000 > elapsedTime.count())
			return;

	}

	if (m_deltatime != 0) {
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - m_deltatimeStart);
		if (m_deltatime*1000 > elapsedTime.count())
			return;
	}

	m_deltatimeStart = nowTime;
	m_numExec--;
	m_callback();
}

void ScheduleInfo::Destroy() {
	m_callback = nullptr;
}