#include "ParticleSystem.h"
#include "RenderManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool ParticleSystem::Init() {
	if (!Object::Init()) {
		return false;
	}
	m_objType = ObjectType::PARTICLE;
	return true;
}

void ParticleSystem::Update() {

}

void ParticleSystem::Load(std::string _path) {
	std::ifstream		filestr;
	std::stringstream	strstr;

	filestr.open(_path, std::ios::binary);
	if (!filestr.is_open()) return;

	strstr << filestr.rdbuf();
	filestr.close();

	value val;
	strstr >> val;
	std::string err = get_last_error();
	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	// ���C�����W���[��
	{
		object& main		= val.get<object>()["main"].get<object>();
		m_main.duration		= static_cast<float>(main["duration"].get<double>());
		m_main.loop			= main["loop"].get<bool>();
		m_main.prewarm		= main["prewarm"].get<bool>();
		LoadParam(m_main.startDelay, "startDelay", main);
		LoadParam(m_main.startLifeTime, "startLifeTime", main);
		LoadParam(m_main.startSpeed, "startSpeed", main);
		LoadParam(m_main.startSize, "startSize", main);
		LoadParam(m_main.startRotation, "startRotation", main);
		m_main.randomizeRotationDirection = static_cast<float>(main["randomizeRotationDirection"].get<double>());
		LoadColor(m_main.startColor, "startColor", main);
		LoadParam(m_main.gravityModifier, "gravityModifier", main);
		m_main.simulationSpeed	= static_cast<float>(main["simulationSpeed"].get<double>());
		m_main.maxParticles		= static_cast<int>(main["maxParticles"].get<double>());
		m_main.randSeed			= main["randSeed"].get<bool>();
	}
	// �G�~�b�V����
	{
		object& emission = val.get<object>()["emission"].get<object>();
		LoadParam(m_emission.rateOverTime, "rateOverTime", emission);
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
	// �V�F�C�v
	{
		object& shape				= val.get<object>()["shape"].get<object>();
		m_shape.radius				= static_cast<float>(shape["radius"].get<double>());
		m_shape.emitFromShell		= shape["emitFromShell"].get<bool>();
		m_shape.alignToDirection	= shape["alignToDirection"].get<bool>();
		m_shape.randomizeDirection  = static_cast<float>(shape["randomizeDirection"].get<double>());
		m_shape.spherizeDirection	= static_cast<float>(shape["spherizeDirection"].get<double>());
	}
}

void ParticleSystem::LoadParam(_ParamMode _param, std::string _name, object _obj) {
	object& param = _obj[_name].get<object>();
	_param.constantMin = static_cast<float>(param["constant"].get<double>());
	_param.constantMax = static_cast<float>(param["constantTwo"].get<double>());

	object& curve = param["curve"].get<object>();
	_param.curveMin.keyLength = static_cast<int>(curve["keyLength"].get<double>());
	if (_param.curveMin.keyLength != 0) {
		_KeyInfo key;
		array& keydata = curve["keys"].get<array>();
		for (int i = 0;i < _param.curveMin.keyLength; ++i) {
			object& data = keydata[i].get<object>();
			key.inTangent = static_cast<float>(data["inTangent"].get<double>());
			key.outTangent = static_cast<float>(data["outTangent"].get<double>());
			key.time = static_cast<float>(data["time"].get<double>());
			key.value = static_cast<float>(data["value"].get<double>());
			_param.curveMin.keys.push_back(key);
		}
	}

	object& curveTwo = param["curveTwo"].get<object>();
	_param.curveMax.keyLength = static_cast<int>(curveTwo["keyLength"].get<double>());
	if (_param.curveMax.keyLength != 0) {
		_KeyInfo key;
		array& keydata = curveTwo["keys"].get<array>();
		for (int i = 0; i < _param.curveMax.keyLength; ++i)
		{
			object& data = keydata[i].get<object>();
			key.inTangent = static_cast<float>(data["inTangent"].get<double>());
			key.outTangent = static_cast<float>(data["outTangent"].get<double>());
			key.time = static_cast<float>(data["time"].get<double>());
			key.value = static_cast<float>(data["value"].get<double>());
			_param.curveMax.keys.push_back(key);
		}
	}
}

void ParticleSystem::LoadColor(_ColorMode _color, std::string _name, object _obj) {
	object& color = _obj[_name].get<object>();
	
	object& colorMin = color["colorMin"].get<object>();
	_color.colorMin.r = static_cast<float>(colorMin["r"].get<double>());
	_color.colorMin.g = static_cast<float>(colorMin["g"].get<double>());
	_color.colorMin.b = static_cast<float>(colorMin["b"].get<double>());
	_color.colorMin.a = static_cast<float>(colorMin["a"].get<double>());

	object& colorMax = color["colorMax"].get<object>();
	_color.colorMax.r = static_cast<float>(colorMax["r"].get<double>());
	_color.colorMax.g = static_cast<float>(colorMax["g"].get<double>());
	_color.colorMax.b = static_cast<float>(colorMax["b"].get<double>());
	_color.colorMax.a = static_cast<float>(colorMax["a"].get<double>());

}

void ParticleSystem::PushParticle() {
	auto itr = m_particle.begin();
	for (;itr != m_particle.end();++itr) {
		RenderManager::GetInstance()->PushSprite(*itr);
	}
}