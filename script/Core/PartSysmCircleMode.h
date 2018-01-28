#ifndef _PARTICLE_SYSTEM_CIRCLE_MODE_H_
#define _PARTICLE_SYSTEM_CIRCLE_MODE_H_

// circleParam�̃��[�h�̐���

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
	// loop �ݒ�
	void Init(MODE mode);

	void SetInterval(float val);	// �p�[�e�B�N�������̊Ԋu
	void SetSpeed(float speed);		// �i�߂�p�x
	void AddAngle();				// �����O�Ɏ��̊p�x��
	bool IsCreate();				// �ݒ肵���p�x���ǂ���1
	float GetAngle()const;


private:
	MODE m_mode;
	float m_arc;
	// loop���[�h
	float m_nowAngle;
	float m_intervalAngle;
	int m_next;
	int m_arcSpeed;						// �~�ʂ̈ړ��X�s�[�h
	// pingpong���[�h
	// BurstSpeed���[�h
};


#endif