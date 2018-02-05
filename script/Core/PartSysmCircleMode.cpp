#include "PartSysmCircleMode.h"

void PartSysmCircleMode::SetArc(float _arc) {
	m_arc = _arc;
}
void PartSysmCircleMode::Init(MODE mode) {
	m_mode = mode;
}
void PartSysmCircleMode::SetInterval(float val) {
	// ‚O`‚P‚Ü‚Å‚Ì’l‚ª—ˆ‚é 
	m_intervalAngle = val * 3600;
	if (m_intervalAngle == 0) {
		m_intervalAngle = 1;
	}
}

void PartSysmCircleMode::SetSpeed(float speed) {
	m_arcSpeed = speed * 36;
}

void PartSysmCircleMode::AddAngle() {
	m_nowAngle += m_arcSpeed;
	if (m_nowAngle > m_arc * 10) {
		if (m_mode == MODE::LOOP) {
			m_nowAngle -= m_arc * 10;
		}
		else if (m_mode == MODE::PINGPONG) {
			m_arcSpeed *= -1;
		}
	}

	if (m_nowAngle < 0) {
		m_arcSpeed *= -1;
	}
}

bool PartSysmCircleMode::IsCreate() {
	if (m_intervalAngle == 0) {
		return true;
	}

	int angle = m_nowAngle * 1000;
	int angleinterval = m_intervalAngle * 1000;
	if (angle % angleinterval == 0)
		return true;
	return false;
}
float PartSysmCircleMode::GetAngle()const {
	return m_nowAngle/10.0f;
}
