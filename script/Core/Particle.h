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
	void CalcDirection();
	void SetSpeed(float speed);
	void SetLife(int life);

	void SubLife(int sub);
	int GetLife()const;
	void Update();
private:
	Vector2			m_dir;			// ˆÚ“®•ûŒü
	int 			m_lifeTime;		// Žõ–½ŽžŠÔ
	float			m_speed;
	float			m_an;
};


#endif