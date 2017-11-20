#pragma once
#include <string>
#include <vector>
#include "Image.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void Create(int _num, Vector _pos, Vector _scale);
	void SetLife(int _min, int _max);
	void SetGravity(bool _flag);
	void SetVelocity(float _min,float _max);
	void SetAngle(int _angleMin, int _angleMax);
	// ìôë¨íºê¸â^ìÆ
	void UniformLinearMotion(float _time);
	void PlayBack();
	void Draw();
private:
	std::vector<Image*>		m_particleContainer;
	std::vector<int>		m_lifeContainer;
	std::vector<float>		m_velocity;
	std::vector<float>		m_angle;
	Vector					m_origin,m_scale;
	int						m_max;
	bool					m_useGravityflag;
	int						m_angleMin, m_angleMax;
	int						m_lifeMin, m_lifeMax;
};
