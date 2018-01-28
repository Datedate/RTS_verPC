#ifndef _PARTICLE_2018_1_12_H_
#define _PARTICLE_2018_1_12_H_

#include "SpriteBase.h"
#include "ParticleParam.h"

class Particle : public SpriteBase
{
public:
	Particle() {};
	~Particle() {};
	CREATE_FUNC(Particle);
	bool Init();
	void SetAngle(float angle);
	void SetDirection(Vector2 vec);
	void SetDirection(float x, float y);
	void SetSpeed(float speed);
	void SetLife(int life);
	void SetGravity(float gravity);

	void SubLife(float sub);
	void CalcDirection();
	int GetLife()const;
	void Update();
	void GravityForce(float*,float*);
private:
	Vector2			m_dir;			// ˆÚ“®•ûŒü
	float 			m_lifeTime;		// Žõ–½ŽžŠÔ
	float			m_speed;		// ‘¬“x
	float			m_an;
	float			m_gravity;
	float			m_time;			// ŽžŠÔŒo‰ß

};


#endif