#ifndef _PARTICLE_SYSTEM_CIRCLE_MODE_H_
#define _PARTICLE_SYSTEM_CIRCLE_MODE_H_

// circleParamのモードの制御

enum MODE
{
	RANDOM,
	LOOP,
	PINGPONG,
	BIRSTSPEED
};

class PartSysmCircleMode
{
public:
	PartSysmCircleMode() {};
	~PartSysmCircleMode() {};
	void SetArc(float _arc);
	// loop 設定
	void Init(MODE mode);

	void SetInterval(float val);	// パーティクル生成の間隔
	void SetSpeed(float speed);		// 進める角度
	void AddAngle();				// 生成前に次の角度へ
	bool IsCreate();				// 設定した角度かどうか1
	float GetAngle()const;


private:
	MODE m_mode;
	float m_arc;
	// loopモード
	float m_nowAngle;
	float m_intervalAngle;
	int m_next;
	int m_arcSpeed;						// 円弧の移動スピード
	// pingpongモード
	// BurstSpeedモード
};


#endif