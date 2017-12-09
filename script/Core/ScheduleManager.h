#ifndef __SCHEDULE_MANAGER_H__
#define __SCHEDULE_MANAGER_H__

#include "SingletonTemplate.h"
#include <functional>
#include <vector>

class Object;
class ScheduleInfo;

class ScheduleManager : public SingletonTemplate<ScheduleManager>
{
public:
	friend SingletonTemplate<ScheduleManager>;
private:
	ScheduleManager() {};
	~ScheduleManager() {};

public:
	bool Init();
	void Exit();
	void AllUpdate();
	void SetUpdate(Object* _obj);
	void ScheduleUpdate(ScheduleInfo* _scheduleInfo);
	void ScheduleUpdateOnce(ScheduleInfo* _scheduleInfo);
	void ReleaseSchedule(std::function<void()> _callback);
	void ReleaseScheduleOnce(std::function<void()> _callback);
	unsigned int PauseSchedule(std::function<void()> _callback);
	unsigned int PauseScheduleOnce(std::function<void()> _callback);
	void ReStartSchedule(unsigned int _id);
private:
	std::vector<ScheduleInfo*>	m_scheduleContainer;
	std::vector<ScheduleInfo*>	m_scheduleOnceContainer;
};

#endif