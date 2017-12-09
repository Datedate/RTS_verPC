#include "ScheduleManager.h"
#include "ScheduleInfo.h"

bool ScheduleManager::Init() {
	return true;
}
void ScheduleManager::Exit() {

}

void ScheduleManager::AllUpdate() {

}
void ScheduleManager::SetUpdate(Object* _obj) {

}
void ScheduleManager::ScheduleUpdate(ScheduleInfo* _scheduleInfo) {

}
void ScheduleManager::ScheduleUpdateOnce(ScheduleInfo* _scheduleInfo) {

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