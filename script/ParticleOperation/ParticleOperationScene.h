#ifndef _PARTICLE_OPERATION_SCENE_H_
#define _PARTICLE_OPERATION_SCENE_H_

#include "../Core/SceneBase.h"

class ParticleOperationMainLayer;
class ParticleOperationUILayer;

class ParticleOperationScene : public SceneBase
{
public:
	ParticleOperationScene() {};
	~ParticleOperationScene() {};
	bool Init();
	void Update();
	CREATE_FUNC(ParticleOperationScene);
private:
	ParticleOperationMainLayer* m_particleMainLayer;
	ParticleOperationUILayer*	m_particleUILayer;
};

#endif