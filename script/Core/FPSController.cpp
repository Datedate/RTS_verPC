#include "FPSController.h"

FPSContoller::FPSContoller()
{
	m_fps = 60.0f;
}

FPSContoller::~FPSContoller()
{
}

bool FPSContoller::FpsControlCheck() {
	auto beginTime = std::chrono::steady_clock::now();

	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(beginTime - m_lastTime);

	if (elapsedTime.count() >= 1000000.0f / m_fps) {
		m_lastTime = std::chrono::steady_clock::now();
		return true;
	}
	return false;
}