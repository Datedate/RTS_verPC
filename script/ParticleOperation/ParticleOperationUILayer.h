#ifndef _PARTICLE_OPERATION_UI_LAYER_H_
#define _PARTICLE_OPERATION_UI_LAYER_H_

#include "../Core/LayerBase.h"

class ParticleOperationUILayer : public LayerBase
{
public:
	ParticleOperationUILayer() {};
	~ParticleOperationUILayer() {};

	bool Init();
	CREATE_FUNC(ParticleOperationUILayer);
	void Update();
private:
	SpriteBase*	m_reloadButton;
	SpriteBase* m_startButton;
	SpriteBase* m_stopButton;

	bool m_reloadFlag;
	bool m_startFlag;
	bool m_stopFlag;
};

#endif
