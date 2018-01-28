#include "Particle.h"

#define PI 3.14159265

bool Particle::Init() {
	SpriteBase::Init();

	m_gravity = 0;
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
	m_dir.x = cosf(m_angle * (PI/180.0f));
	m_dir.y = sinf(m_angle * (PI / 180.0f)) ;
}

void Particle::SetSpeed(float speed) {
	m_speed = speed / 1.25f;
}

void Particle::SetLife(int life) {
	m_lifeTime = life;
}

void Particle::SetGravity(float gravity) {
	m_gravity = gravity;
}

void Particle::SubLife(float sub) {
	m_lifeTime += sub;
}

int Particle::GetLife()const {
	return m_lifeTime;
}

void Particle::Update() {
	float x = m_dir.x * m_speed;
	float y = m_dir.y * m_speed;
	SubLife(-(1.0f / 60.0f));
	GravityForce(&x,&y);
	Trans(x, y);
	
}

void Particle::GravityForce(float* x,float* y) {
	if (m_gravity == 0) return;
	m_time += 0.14f * m_gravity ;

	(*y) = (*y)  - (0.98 * m_time*m_time) / 2.0f;
}