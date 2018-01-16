#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include <vector>
#include "picojson.h"
#include "../Core/Object.h"
#include "ParticleParam.h"
#include "Rectangle.h"

using namespace picojson;

class SpriteBase;
class Particle;

class ParticleSystem : public Object
{
public:
	ParticleSystem() {};
	~ParticleSystem() {};
	bool Init();
	CREATE_FUNC(ParticleSystem);
	void Load(std::string _path);
	void PushParticle();
	void Update();
	void StartSimulation();
	void StopSimulation();
private:
	void LoadParam(_ParamMode* param, std::string _name, object _obj);
	void LoadColor(_ColorMode* color, std::string _name, object _obj);
	void LoadShapeParam(object _obj);
	void Clear();
	void Generate();	// �p�[�e�B�N������
	void OneTimeParticleCreate(int num);	// ��b�Ԃɉ��̃p�[�e�B�N���𔭐������邩
	void CalcTimer();	// �V���~���[�V�����o�ߎ���
	void ParticleCreate();		// �p�[�e�B�N�����q�����
	void ParticleInitVector(Particle* pa);
	//void ParticleCreate(float x, float y);
private:
	_ParticleMainModule		m_main;
	_ParticleEmissionModule m_emission;
	_ParticleShape			m_shape;

	std::vector<Particle*> m_particleContainer;
	bool					m_simulationFlag;
	
	int						m_timer;
	Size					m_displaysize;
	Vector2					m_centerPos;
};


#endif