#include "ParticleSystem.h"
#include "RenderManager.h"
#include "ScheduleInfo.h"
#include "ScheduleManager.h"
#include "Particle.h"
#include "../../resource3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <random>

bool ParticleSystem::Init() {
	if (!Object::Init()) {
		return false;
	}
	m_objType = ObjectType::PARTICLE;
	m_simulationFlag = false;
	m_updateFlag     = false;
	m_displaysize = RenderManager::GetInstance()->GetDisplaySize();
	m_centerPos.Set(Vector2(m_displaysize.width / 2.0f, m_displaysize.height / 2.0f));
	m_scale.x = 1.0f;
	m_scale.y = 1.0f;
	srand((unsigned int)time(NULL));

	return true;
}

void ParticleSystem::Load(std::string _path) {
	std::ifstream		filestr;
	std::stringstream	strstr;

	filestr.open(_path, std::ios::binary);
	if (!filestr.is_open()) {
		MessageBox(NULL, "ParticleSystem::Load ファイルオープン失敗", "", 0);
		return;
	}
	strstr << filestr.rdbuf();
	filestr.close();

	value val;
	strstr >> val;
	std::string err = get_last_error();
	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	// メインモジュール
	{
		object& main		= val.get<object>()["main"].get<object>();
		m_main.duration		= static_cast<float>(main["duration"].get<double>());
		m_main.loop			= main["loop"].get<bool>();
		m_main.prewarm		= main["prewarm"].get<bool>();
		LoadParam(&m_main.startDelay, "startDelay", main);
		LoadParam(&m_main.startLifeTime, "startLifeTime", main);
		LoadParam(&m_main.startSpeed, "startSpeed", main);
		LoadParam(&m_main.startSize, "startSize", main);
		LoadParam(&m_main.startRotation, "startRotation", main);
		m_main.randomizeRotationDirection = static_cast<float>(main["randomizeRotationDirection"].get<double>());
		LoadColor(&m_main.startColor, "startColor", main);
		LoadParam(&m_main.gravityModifier, "gravityModifier", main);
		m_main.simulationSpeed	= static_cast<float>(main["simulationSpeed"].get<double>());
		m_main.maxParticles		= static_cast<int>(main["maxParticles"].get<double>());
		m_main.randSeed			= main["randSeed"].get<bool>();
	}
	// エミッション
	{
		object& emission = val.get<object>()["emission"].get<object>();
		LoadParam(&m_emission.rateOverTime, "rateOverTime", emission);
		array& bursts = emission["bursts"].get<array>();
		_Burst burst;
		for (int i = 0;i < bursts.size();++i) {
			object& data = bursts[i].get<object>();
			burst.minCount	= static_cast<int>(data["minCount"].get<double>());
			burst.maxCount	= static_cast<int>(data["maxCount"].get<double>());
			burst.time		= static_cast<float>(data["time"].get<double>());
			m_emission.burst.push_back(burst);
		}
	}
	// シェイプ
	{
		object& shape				= val.get<object>()["shape"].get<object>();
		LoadShapeParam(shape);
	}

	SetCircleMode();
}

void ParticleSystem::LoadParam(_ParamMode* _param, std::string _name, object _obj) {
	object& param = _obj[_name].get<object>();
	_param->constantMin = static_cast<float>(param["constant"].get<double>());
	_param->constantMax = static_cast<float>(param["constantTwo"].get<double>());

	object& curve = param["curve"].get<object>();
	_param->curveMin.keyLength = static_cast<int>(curve["keyLength"].get<double>());
	if (_param->curveMin.keyLength != 0) {
		_KeyInfo key;
		array& keydata = curve["keys"].get<array>();
		for (int i = 0;i < _param->curveMin.keyLength; ++i) {
			object& data = keydata[i].get<object>();
			key.inTangent = static_cast<float>(data["inTangent"].get<double>());
			key.outTangent = static_cast<float>(data["outTangent"].get<double>());
			key.time = static_cast<float>(data["time"].get<double>());
			key.value = static_cast<float>(data["value"].get<double>());
			_param->curveMin.keys.push_back(key);
		}
	}

	object& curveTwo = param["curveTwo"].get<object>();
	_param->curveMax.keyLength = static_cast<int>(curveTwo["keyLength"].get<double>());
	if (_param->curveMax.keyLength != 0) {
		_KeyInfo key;
		array& keydata = curveTwo["keys"].get<array>();
		for (int i = 0; i < _param->curveMax.keyLength; ++i)
		{
			object& data = keydata[i].get<object>();
			key.inTangent = static_cast<float>(data["inTangent"].get<double>());
			key.outTangent = static_cast<float>(data["outTangent"].get<double>());
			key.time = static_cast<float>(data["time"].get<double>());
			key.value = static_cast<float>(data["value"].get<double>());
			_param->curveMax.keys.push_back(key);
		}
	}
}

void ParticleSystem::LoadColor(_ColorMode* _color, std::string _name, object _obj) {
	object& color = _obj[_name].get<object>();
	
	object& colorMin = color["colorMin"].get<object>();
	_color->colorMin.r = static_cast<float>(colorMin["r"].get<double>());
	_color->colorMin.g = static_cast<float>(colorMin["g"].get<double>());
	_color->colorMin.b = static_cast<float>(colorMin["b"].get<double>());
	_color->colorMin.a = static_cast<float>(colorMin["a"].get<double>());

	object& colorMax = color["colorMax"].get<object>();
	_color->colorMax.r = static_cast<float>(colorMax["r"].get<double>());
	_color->colorMax.g = static_cast<float>(colorMax["g"].get<double>());
	_color->colorMax.b = static_cast<float>(colorMax["b"].get<double>());
	_color->colorMax.a = static_cast<float>(colorMax["a"].get<double>());

}

void ParticleSystem::LoadShapeParam(object _obj) {
	object& shapeKind = _obj["shape"].get<object>();


	m_shape.radius				 = static_cast<float>(_obj["radius"].get<double>());
	m_shape.alignToDirection	 = _obj["alignToDirection"].get<bool>();
	m_shape.randomizeDirection	 = static_cast<float>(_obj["randomizeDirection"].get<double>());
	m_shape.spherizeDirection	 = static_cast<float>(_obj["spherizeDirection"].get<double>());

	if (shapeKind["sphere"].get<bool>()) {
		m_shape.emitFromShell = _obj["emitFromShell"].get<bool>();
	}
	else if (shapeKind["hemiSphere"].get<bool>()) {
		m_shape.emitFromShell = _obj["emitFromShell"].get<bool>();
	}
	else if (shapeKind["circle"].get<bool>()) {
		// circleパラメータセット
		object& arcParam = _obj["arc"].get<object>();
		m_shape.circleParam.random		= arcParam["random"].get<bool>();
		m_shape.circleParam.loop		= arcParam["loop"].get<bool>();
		m_shape.circleParam.pingpong	= arcParam["pingpong"].get<bool>();
		m_shape.circleParam.burstSpeed	= arcParam["burstSpeed"].get<bool>();
		m_shape.circleParam.arc			= static_cast<float>(arcParam["arc"].get<double>());
		m_shape.circleParam.arcSpread	= static_cast<float>(arcParam["arcSpread"].get<double>());
		LoadParam(&m_shape.circleParam.arcSpeed, "arcSpeed", arcParam);
	}
}

void ParticleSystem::SetCircleMode() {
	// Todo:
	m_circleMode.SetArc(m_shape.circleParam.arc);
	if (m_shape.circleParam.random) {
		m_circleMode.Init(MODE::RANDOM);
	}
	else if (m_shape.circleParam.loop) {
		m_circleMode.Init(MODE::LOOP);
		m_circleMode.SetInterval(m_shape.circleParam.arcSpread);
		m_circleMode.SetSpeed(m_shape.circleParam.arcSpeed.constantMax);
	}
	else if (m_shape.circleParam.pingpong) {
		m_circleMode.Init(MODE::PINGPONG);
		m_circleMode.SetInterval(m_shape.circleParam.arcSpread);
		m_circleMode.SetSpeed(m_shape.circleParam.arcSpeed.constantMax);
	}
	else if (m_shape.circleParam.burstSpeed) {
	}
}

void ParticleSystem::PushParticle() {
	//if (!m_simulationFlag) return;

	auto itr = m_particleContainer.begin();
	for (;itr != m_particleContainer.end();) {
		if ((*itr)->GetLife() >= 0.0f) {
			RenderManager::GetInstance()->PushSprite(*itr);
			itr++;
		}
		else {
			(*itr)->Exit();
			delete (*itr);
			itr = m_particleContainer.erase(itr);
		}
	}
}

void ParticleSystem::Update() {
	if (!m_simulationFlag) return;

	auto itr = m_particleContainer.begin();
	for (;itr != m_particleContainer.end();itr++) {
		(*itr)->Update();
	}

	for (int i = 0;i < m_emission.rateOverTime.constantMax / 60+1 ;i++) {
		Generate();
		m_circleMode.AddAngle();
	}
	//Generate();
	//m_circleMode.AddAngle();
	//Generate();
	//m_circleMode.AddAngle();
}

void ParticleSystem::StartSimulation() {
	if (m_simulationFlag) return;
	Clear();
	m_simulationFlag = true;
	if (!m_updateFlag) {
		SET_UPDATE(ParticleSystem);
		m_updateFlag = true;
	}
}

void ParticleSystem::StopSimulation() {
	m_simulationFlag = false;
	m_particleContainer.clear();
}

bool ParticleSystem::isSimulation()const{
	return m_simulationFlag;
}

void ParticleSystem::SetScale(float x, float y) {
	m_scale.x = x;
	m_scale.y = y;
}

void ParticleSystem::SetPos(float x, float y) {
	m_centerPos.x = x;
	m_centerPos.y = y;
}

void ParticleSystem::Clear() {
	//ScheduleManager::GetInstance()->ReleaseScheduleOnce(ParticleSystem::CalcTimer);
}

// パーティクル発生
void ParticleSystem::Generate() {
	if (m_circleMode.IsCreate()) {
		ParticleCreate();
	}
}

// 粒子一つ生成
void ParticleSystem::ParticleCreate() {
	
		Particle* pa = Particle::Create();
		pa->CreateTex("Particle/tama_01.png");
		pa->SetColor(m_main.startColor.colorMin.r,
			m_main.startColor.colorMax.g,
			m_main.startColor.colorMax.b,
			m_main.startColor.colorMax.a);
		pa->SetAlpha(0.6f);
		pa->SetPos(m_centerPos.x,m_centerPos.y);
		pa->SetEffectID(FXID_EFFECT);
		pa->SetGravity(m_main.gravityModifier.constantMax);
		ParticleInitVector(pa);
		m_particleContainer.push_back(pa);
}

// パーティクル発生時の粒子の設定
void ParticleSystem::ParticleInitVector(Particle* pa) {
	
	if (m_shape.circleParam.random) {
		ParticleInitVectorRandom(pa);
	}
	else if (m_shape.circleParam.loop) {
		ParticleInitVectorLoop(pa);
	}
	else if (m_shape.circleParam.pingpong) {
		ParticleInitVectorPingPong(pa);
	}
	else if (m_shape.circleParam.burstSpeed) {
		ParticleInitVectorBurstSpeed(pa);
	}

	// 共通設定
	pa->SetSpeed(m_main.startSpeed.constantMax);
	pa->CalcDirection();
	pa->SetLife(m_main.startLifeTime.constantMax);
	pa->SetScale(m_scale.x, m_scale.y);
	pa->Scale(1.0f, 1.0f);
}

// Randomモードのパーティクル発生時の粒子の設定
void ParticleSystem::ParticleInitVectorRandom(Particle* pa) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> rand360(0, m_shape.circleParam.arc);

	pa->SetAngle(rand360(mt));
}

// Loopモード時のパーティクル発生時の粒子の設定
void ParticleSystem::ParticleInitVectorLoop(Particle* pa) {
	pa->SetAngle(m_circleMode.GetAngle());
}

// PingPongモードのパーティクル発生時の粒子の設定
void ParticleSystem::ParticleInitVectorPingPong(Particle* pa) {
	pa->SetAngle(m_circleMode.GetAngle());
}

// BurstSpeedモードのパーティクル発生時の粒子の設定
void ParticleSystem::ParticleInitVectorBurstSpeed(Particle* pa) {
	// Todo:

}

ParticleSystem::~ParticleSystem() {
	for (auto itr = m_particleContainer.begin();
		      itr != m_particleContainer.end();itr++) {
		if ((*itr) != nullptr) {
			delete (*itr);
		}
	}

	m_particleContainer.clear();
}