#include "DebugSystem.h"
#include "RenderManager.h"

bool DebugSystem::Init() {
	int			 height = 0;									// �����̍���
	unsigned int width = 10;									// �����̕�
	unsigned int weight = 0;									// �����̑���
	unsigned int mipLevels = 0;									// �~�b�v�}�b�v���x���̐�
	bool		 isItalic = false;								// �C�^���b�N�̂��ۂ� true:�C�^���b�N��
	unsigned long	charSet = SHIFTJIS_CHARSET;					// �����Z�b�g
	unsigned long   qutputPrecision = OUT_DEFAULT_PRECIS;		// ��ɂs�q�t�d�s�x�o�d�̃t�H���g���g��
	unsigned long	quality = PROOF_QUALITY;					// �o�͕i��
	unsigned long   pitchAndFamily = FIXED_PITCH | FF_MODERN;	// �s�b�`�ƃt�@�~���[�C���f�b�N�X
	std::string		fontname = "�l�r�o�S�V�b�N";				// �t�H���g��



	HRESULT hr = D3DXCreateFont(RenderManager::GetInstance()->GetDevice(),
		height, width, weight, mipLevels, isItalic, charSet, qutputPrecision,
		quality, pitchAndFamily, fontname.c_str(), &m_font);

	if (hr == S_OK) {
		return true;
	}
	return false;
}

void DebugSystem::DebugDrawText(const char* _buf, int _x, int _y) const {
	RECT rect = { _x , _y , 0 , 0 };
	// ������̃T�C�Y���v�Z
	m_font->DrawText(NULL, _buf, -1, &rect, DT_CALCRECT, NULL);
	// ������`��i�ԐF�j
	m_font->DrawText(NULL, _buf, -1, &rect, DT_LEFT | DT_BOTTOM, 0xffff0000);
}
