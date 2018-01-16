#ifndef _PARTICLE_PARAM_H_
#define _PARTICLE_PARAM_H_

#include <vector>

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
	float		duration;						// パーティクル発生時間
	bool		loop;							// パーティクル発生を継続するか
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
	bool circle;		// ２Dはほぼこれ
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

#endif
