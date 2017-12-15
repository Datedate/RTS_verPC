#ifndef __SCHEDULE_MANAGER_H__
#define __SCHEDULE_MANAGER_H__

#include "SingletonTemplate.h"
#include <functional>
#include <vector>
#include "Object.h"

#define SET_UPDATE(__TYPE__)\
ScheduleManager::GetInstance()->SetUpdate(std::bind(&__TYPE__::Update , std::ref(*this)));
#define SET_SCHEDULE_4( _FUNC_ , _NUM_ , _DELTA_ , _DELAY_ , _ORDER_)\
ScheduleManager::GetInstance()->ScheduleUpdate(\
new ScheduleInfo(std::bind(&_FUNC_ , std::ref(*this)),_NUM_,_DELTA_,_DELAY_ ,_ORDER_));
#define SET_SCHEDULE_3( _FUNC_ , _NUM_ , _DELTA_ , _DELAY_ )\
ScheduleManager::GetInstance()->ScheduleUpdate(\
new ScheduleInfo(std::bind(&_FUNC_ , std::ref(*this)),_NUM_,_DELTA_,_DELAY_ ));
#define SET_SCHEDULE_2( _FUNC_ , _NUM_ , _DELTA_ )\
ScheduleManager::GetInstance()->ScheduleUpdate(\
new ScheduleInfo(std::bind(&_FUNC_ , std::ref(*this)),_NUM_,_DELTA_));
#define SET_SCHEDULE_1( _FUNC_ , _NUM_  )\
ScheduleManager::GetInstance()->ScheduleUpdate(\
new ScheduleInfo(std::bind(&_FUNC_ , std::ref(*this)),_NUM_));
#define SET_SCHEDULE( _FUNC_ )\
ScheduleManager::GetInstance()->ScheduleUpdate(\
new ScheduleInfo(std::bind(&_FUNC_ , std::ref(*this))));


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
	void SetUpdate(const std::function<void()>& _update );
	void ScheduleUpdate(ScheduleInfo* _scheduleInfo);
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