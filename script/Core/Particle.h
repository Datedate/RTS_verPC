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
	void SetScale(float x, float y);

	void SubLife(float sub);
	void CalcDirection();
	int GetLife()const;
	void Update();
	void GravityForce(float*,float*);
private:
	Vector2			m_dir;			// 移動方向
	float 			m_lifeTime;		// 寿命時間
	float			m_speed;		// 速度
	float			m_an;
	float			m_gravity;
	float			m_time;			// 時間経過
	float			m_scaleX;		// パーティクル自体の大きさ
	float			m_scaleY;		// パーティクル自体の大きさ
};


#endif