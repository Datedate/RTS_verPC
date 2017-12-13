#include "SpriteBase.h"
#include "RenderManager.h"

const int SpriteBase::VERTEX_NUM = 4;

SpriteBase::SpriteBase() {
	// �|���S��
	m_poly.x = 0.0f;
	m_poly.y = 0.0f;
	m_poly.wid = 1.0f;
	m_poly.hei = 1.0f;
	// UV
	m_uv.left = 0.0f;
	m_uv.top = 0.0f;
	m_uv.wid = 1.0f;
	m_uv.hei = 1.0f;
	// �s��v�Z���̌��_�܂ł̋���
	m_pivot_x = 0.5f;
	m_pivot_y = 0.5f;

	// �J���[�l
	m_color[0] = 255.0f;
	m_color[1] = 255.0f;
	m_color[2] = 255.0f;
	m_color[3] = 255.0f;

	// ���݂̎p��
	m_pos.x		  = m_poly.x;
	m_pos.y		  = m_poly.y;
	m_angle		  = 0.0f;
	m_size.width  = m_poly.wid;
	m_size.height = m_poly.hei;
	// �ω���
	m_transAmount = { 0,0,0 };
	m_angleAmount = { 0,0,0 };
	m_scaleAmount = { 1,1,1 };

	D3DXMatrixIdentity(&m_world);
	
	m_drawFlag = true;
	m_alpha = 1.0f;
	m_tex = NULL;
}
SpriteBase::SpriteBase(std::string _name) {
	SpriteBase::SpriteBase();
	
	CreateTex(_name);
}
SpriteBase::~SpriteBase() {

}

SpriteBase*	SpriteBase::Create() {
	SpriteBase* ptr = new SpriteBase();
	if (ptr && ptr->Init()) {
		return ptr;
	}
	else {
		delete ptr;
		ptr = nullptr;
		return 	nullptr;
	}
}

SpriteBase*	SpriteBase::Create(std::string _name) {
	SpriteBase* ptr = new SpriteBase(_name);
	if (ptr && ptr->Init()) {
		return ptr;
	}
	else {
		delete ptr;
		ptr = nullptr;
		return 	nullptr;
	}
}

bool SpriteBase::Init() {
	pRenderMng = RenderManager::GetInstance();
	pRenderMng->PushDraw(this);
	return true;
}

void SpriteBase::Update() {
	
}

void SpriteBase::SetDrawFlag(bool _flag) {
	m_drawFlag = _flag;
}

bool SpriteBase::IsDrawFlag() {
	return m_drawFlag;
}

void SpriteBase::SetEffectID(DWORD _id) {
	m_effectID = _id;
}

bool SpriteBase::CreateTex(std::string _texName) {
	auto device = pRenderMng->GetDevice();
	std::string filepath = "assets/" + _texName;
	if (FAILED((D3DXCreateTextureFromFile(device, filepath.c_str(), &m_tex)))) {
		MessageBox(NULL, "Failed : load Texture", filepath.c_str(), MB_OK);
		return false;
	}

	// �e�N�X�`���T�C�Y�擾
	D3DSURFACE_DESC desc;
	if (FAILED(m_tex->GetLevelDesc(0, &desc))) {
		MessageBox(NULL, "�e�N�X�`���T�C�Y�擾���s", filepath.c_str(), MB_OK);
		return false;
	}
	m_poly.wid = desc.Width;
	m_poly.hei = desc.Height;

	return true;
}

void SpriteBase::UVCut(float _left, float _top, float _width, float _height) {
	m_uv.left = _left;
	m_uv.top  = _top;
	m_uv.wid  = _width;
	m_uv.hei  = _height;
}
void SpriteBase::SetAlpha(float _alpha) {
	m_alpha = _alpha;
}

void SpriteBase::Trans(float _transX, float _transY) {
	m_transAmount.x = _transX;
	m_transAmount.y = _transY;
	m_transAmount.z = 0.0f;
}
void SpriteBase::Rotation(float _angleZ) {
	m_angleAmount.x = 0;
	m_angleAmount.y = 0;
	m_angleAmount.z = _angleZ;
}
void SpriteBase::Scale(float _scaleX, float _scaleY) {
	m_scaleAmount.x = _scaleX;
	m_scaleAmount.y = _scaleY;
	m_scaleAmount.z = 1.0f;
}
void SpriteBase::MakeWorldMatrix() {
	D3DXMATRIX matx, maty,matz,matrotation, mattrans , matscale;

	// �ω��ʂ����݂̎p���ɔ��f
	m_transAmount.x += m_pos.x; m_transAmount.y += m_pos.y;
	m_angleAmount.z += m_angle;
	m_scaleAmount.x += m_size.width - 1; m_scaleAmount.y += m_size.height - 1;

	D3DXMatrixScaling(&m_world , m_poly.wid , m_poly.hei , 1.0f);						// �|���S���T�C�Y�ɒ���				
	D3DXMatrixScaling(&matscale, m_scaleAmount.x, m_scaleAmount.y, m_scaleAmount.z);	// �g��k���s��𐶐�
	
	D3DXMatrixRotationX(&matx, D3DX_PI*m_angleAmount.x / 180.0f);						// X����]�s��𐶐�
	D3DXMatrixRotationY(&maty, D3DX_PI*m_angleAmount.y / 180.0f);						// Y����]�s��𐶐�
	D3DXMatrixRotationZ(&matz, D3DX_PI*m_angleAmount.z / 180.0f);						// Z����]�s��𐶐�
	matrotation = matx * maty * matz;													// ��]�s�񍇐�

	D3DXMatrixTranslation(&mattrans, m_transAmount.x, m_transAmount.y,m_transAmount.z);	// ���s�ړ��s��𐶐�

	m_world *= matscale * matrotation * mattrans ;								// �e�s�񍇐�
	
	// �ω��ʏ�����
	m_pos.x		  = m_transAmount.x; m_pos.y = m_transAmount.y;
	m_angle		  = m_angleAmount.z;
	m_size.width  = m_scaleAmount.x; m_size.height = m_scaleAmount.y;
	
	m_transAmount = { 0,0,0 }; m_angleAmount = { 0,0,0 }; m_scaleAmount = { 1,1,1 };
}


float SpriteBase::getPivotX() const {
	return m_pivot_x;
}
float SpriteBase::getPivotY() const {
	return m_pivot_y;
}
UV SpriteBase::getUV() const {
	return m_uv;
}
/*
float SpriteBase::getMinTV() const  {
	return m_tv;
}
float SpriteBase::getWidthUV() const  {
	return m_tuWidth;
}
float SpriteBase::getHeightUV() const  {
	return m_tvHeight;
}
*/
LPDIRECT3DTEXTURE9 SpriteBase::GetTexture()const {
	return m_tex;
}
void SpriteBase::Draw() {
	auto Render = RenderManager::GetInstance();
	Render->PushDraw(this);
}