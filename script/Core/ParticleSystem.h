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
	void Generate();	// パーティクル発生
	void OneTimeParticleCreate(int num);	// 一秒間に何個のパーティクルを発生させるか
	void CalcTimer();	// シュミレーション経過時間
	void ParticleCreate();		// パーティクル粒子一つ生成
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