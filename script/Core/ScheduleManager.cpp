#include "ScheduleManager.h"
#include "ScheduleInfo.h"
#include "SceneBase.h"
#include "LayerBase.h"
#include "SpriteBase.h"

bool ScheduleManager::Init() {
	return true;
}
void ScheduleManager::Exit() {

}

void ScheduleManager::AllUpdate() {
	{
		auto itr = m_scheduleOnceContainer.begin();
		for (;itr != m_scheduleOnceContainer.end();++itr) {
			(*itr)->Exec();
		}
	}

	{
		auto itr = m_scheduleContainer.begin();
		for (;itr != m_scheduleContainer.end();++itr) {
			(*itr)->Exec();
		}
	}

	{
		auto itr = m_updaterContainer.begin();
		for (;itr != m_updaterContainer.end();++itr) {
			(*itr)->Exec();
		}
	}
}


void ScheduleManager::SetUpdate(const std::function<void()>& _update) {
	auto info = new ScheduleInfo(_update);
	m_updaterContainer.push_back(info);
}
void ScheduleManager::ScheduleUpdate(ScheduleInfo* _scheduleInfo) {
	m_scheduleContainer.push_back(_scheduleInfo);
}
void ScheduleManager::ScheduleUpdateOnce(Object* _target,ScheduleInfo* _scheduleInfo) {
	_scheduleInfo->SetOnce();
	m_scheduleOnceContainer.push_back(_scheduleInfo);
}

void ScheduleManager::ReleaseSchedule(std::function<void()> _callback) {

}
void ScheduleManager::ReleaseScheduleOnce(std::function<void()> _callback) {

}

unsigned int ScheduleManager::PauseSchedule(std::function<void()> _callback) {
	return 0;
}
unsigned int ScheduleManager::PauseScheduleOnce(std::function<void()> _callback) {
	return 0;
}

void ScheduleManager::ReStartSchedule(unsigned int _id) {

}

void ScheduleManager::ReleaseAll() {
	{
		auto itr = m_scheduleOnceContainer.begin();
		for (;itr != m_scheduleOnceContainer.end();++itr) {
			(*itr)->Destroy();
			delete (*itr);
		}
		m_scheduleOnceContainer.clear();
	}

	{
		auto itr = m_scheduleContainer.begin();
		for (;itr != m_scheduleContainer.end();++itr) {
			(*itr)->Destroy();
			delete (*itr);
		}
		m_scheduleContainer.clear();
	}

	{
		auto itr = m_updaterContainer.begin();
		for (;itr != m_updaterContainer.end();++itr) {
			(*itr)->Destroy();
			delete (*itr);
		}
		m_updaterContainer.clear();
	}
}