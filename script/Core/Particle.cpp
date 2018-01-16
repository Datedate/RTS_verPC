#include "Particle.h"

#define PI 3.14159265

bool Particle::Init() {
	SpriteBase::Init();
	return true;
}

void Particle::SetAngle(float angle) {
	m_angle = angle;
}

void Particle::SetDirection(Vector2 vec) {
	m_dir.x = vec.x;
	m_dir.y = vec.y;
}

void Particle::SetDirection(float x, float y) {

	m_dir.x = x;
	m_dir.y = y;
}

void Particle::CalcDirection() {
	m_dir.x = cosf(m_angle * (PI/180.0f)) * m_speed;
	m_dir.y = sinf(m_angle * (PI / 180.0f)) * m_speed;
}

void Particle::SetSpeed(float speed) {
	m_speed = speed;
}

void Particle::SetLife(int life) {
	m_lifeTime = life;
}

void Particle::SubLife(int sub) {
	m_lifeTime += sub;
}

int Particle::GetLife()const {
	return m_lifeTime;
}

void Particle::Update() {
	Trans(m_dir.x, m_dir.y);
}
