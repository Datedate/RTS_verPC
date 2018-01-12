#ifndef _PARTICLE_2018_1_12_H_
#define _PARTICLE_2018_1_12_H_

#include "SpriteBase.h"

class Particle : public SpriteBase
{
public:
	Particle();
	~Particle();
	static SpriteBase* Create();
	static SpriteBase* Create();
private:
	Vector2			m_dir;			// ˆÚ“®•ûŒü
	float			m_lifeTime;		// Žõ–½ŽžŠÔ
};


#endif