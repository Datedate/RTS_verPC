#ifndef _FPS_CONTROLLER_H_
#define _FPS_CONTROLLER_H_

#include <chrono>

class FPSContoller
{
public:
	FPSContoller();
	~FPSContoller();
	bool FpsControlCheck();
private:
	float m_fps;
	std::chrono::steady_clock::time_point m_lastTime;
};



#endif