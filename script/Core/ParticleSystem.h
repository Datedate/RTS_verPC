#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

#include <vector>
#include "picojson.h"
#include "../Core/Object.h"

using namespace picojson;

class SpriteBase;

struct _KeyInfo
{
	float inTangent;
	float outTangent;
	float time;
	float value;
};

struct _CurveParam
{
	std::vector<_KeyInfo>	keys;
	int						keyLength;
};

struct _ParamMode
{
	float		constantMin;
	float		constantMax;
	_CurveParam	curveMin;
	_CurveParam curveMax;
};

struct _Color {
	float r;
	float g;
	float b;
	float a;
};

struct _ColorMode {
	_Color colorMin;
	_Color colorMax;
};


struct _ParticleMainModule
{
	float		duration;						// �p�[�e�B�N����������
	bool		loop;							// �p�[�e�B�N���������p�����邩
	bool		prewarm;
	_ParamMode	startDelay;
	_ParamMode	startLifeTime;
	_ParamMode	startSpeed;
	_ParamMode	startSize;
	_ParamMode	startRotation;
	float		randomizeRotationDirection;
	_ColorMode	startColor;
	_ParamMode	gravityModifier;
	float		simulationSpeed;
	int			maxParticles;
	bool		randSeed;
};

struct _Burst {
	int		minCount;
	int		maxCount;
	float	time;
};

struct _ParticleEmissionModule
{
	_ParamMode				rateOverTime;
	std::vector<_Burst>		burst;
};

struct _ShapeKind
{
	bool sphere;
	bool hemisphere;
	bool circle;		// �QD�͂قڂ���
};

struct _ShapeCircleParam
{
	float		arc;
	bool		random;
	bool		loop;
	bool		pingpong;
	bool		burstSpeed;
	float		arcSpread;
	_ParamMode	arcSpeed;
};

struct _ParticleShape
{
	_ShapeKind			shape;
	float				radius;
	_ShapeCircleParam	circleParam;
	bool				emitFromShell;
	bool				alignToDirection;
	float				randomizeDirection;
	float				spherizeDirection;
};



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
	void LoadParam(_ParamMode param, std::string _name, object _obj);
	void LoadColor(_ColorMode color, std::string _name, object _obj);
	void LoadShapeParam(object _obj);
	void CalcTimer();	// �V���~���[�V�����o�ߎ���
	void Clear();
	void Generate();	// �p�[�e�B�N������
	void ParticleCreate();		// �p�[�e�B�N�����q�����
private:
	_ParticleMainModule		m_main;
	_ParticleEmissionModule m_emission;
	_ParticleShape			m_shape;

	std::vector<SpriteBase*> m_particleContainer;
	bool					m_simulationFlag;
	
	int						m_timer;
};


#endif