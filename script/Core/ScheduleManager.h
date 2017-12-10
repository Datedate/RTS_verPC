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
	void SetUpdate(Object* );
	void ScheduleUpdate(Object*,ScheduleInfo* _scheduleInfo);
	void ScheduleUpdateOnce(Object*,ScheduleInfo* _scheduleInfo);
	void ReleaseSchedule(std::function<void()> _callback);
	void ReleaseScheduleOnce(std::function<void()> _callback);
	unsigned int PauseSchedule(std::function<void()> _callback);
	unsigned int PauseScheduleOnce(std::function<void()> _callback);
	void ReStartSchedule(unsigned int _id);

	void ReleaseAll();
private:
	std::vector<ScheduleInfo*>	m_updaterContainer;
	std::vector<ScheduleInfo*>	m_scheduleContainer;
	std::vector<ScheduleInfo*>	m_scheduleOnceContainer;
};

#endif