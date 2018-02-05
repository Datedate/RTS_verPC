#ifndef _PARTICLE_OPERATION_MAIN_LAYER_H_
#define _PARTICLE_OPERATION_MAIN_LAYER_H_

#include "../Core/LayerBase.h"

class ParticleSystem;

class ParticleOperationMainLayer : public LayerBase
{
public:
	ParticleOperationMainLayer();
	~ParticleOperationMainLayer();

	bool Init();
	CREATE_FUNC(ParticleOperationMainLayer);
	void Update();
private:
	ParticleSystem*	m_particleSystem;
};

#endif
