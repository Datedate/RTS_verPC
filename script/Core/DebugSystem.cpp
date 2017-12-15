#include "DebugSystem.h"
#include "RenderManager.h"

bool DebugSystem::Init() {
	int			 height = 0;									// 文字の高さ
	unsigned int width = 10;									// 文字の幅
	unsigned int weight = 0;									// 文字の太さ
	unsigned int mipLevels = 0;									// ミップマップレベルの数
	bool		 isItalic = false;								// イタリック体か否か true:イタリック体
	unsigned long	charSet = SHIFTJIS_CHARSET;					// 文字セット
	unsigned long   qutputPrecision = OUT_DEFAULT_PRECIS;		// 常にＴＲＵＥＴＹＰＥのフォントを使う
	unsigned long	quality = PROOF_QUALITY;					// 出力品質
	unsigned long   pitchAndFamily = FIXED_PITCH | FF_MODERN;	// ピッチとファミリーインデックス
	std::string		fontname = "ＭＳＰゴシック";				// フォント名



	HRESULT hr = D3DXCreateFont(RenderManager::GetInstance()->GetDevice(),
		height, width, weight, mipLevels, isItalic, charSet, qutputPrecision,
		quality, pitchAndFamily, fontname.c_str(), &m_font);

	if (hr == S_OK) {
		return true;
	}
	return false;
}

void DebugSystem::Push(const std::string _buf, int _x, int _y) {
	m_bufContainer.push_back(DEBUG_TEXT(_buf, _x, _y));
}
void DebugSystem::DebugDrawText() const {
	RECT rect = {0,0,0,0};
	for (auto itr = m_bufContainer.begin();itr != m_bufContainer.end();++itr) {
		rect.left = itr->x;
		rect.bottom = itr->y;
		// 文字列のサイズを計算
		m_font->DrawText(NULL, itr->buf.c_str(), -1, &rect, DT_CALCRECT, NULL);
		// 文字列描画（赤色）
		m_font->DrawText(NULL, itr->buf.c_str(), -1, &rect, DT_LEFT | DT_BOTTOM, 0xffff0000);
	}
	
}
void DebugSystem::Clear() {
	m_bufContainer.clear();
}