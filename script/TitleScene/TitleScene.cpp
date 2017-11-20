#include "TitleScene.h"
#include "CWindowMain.h"

#include "input.h"

namespace TITLE_SCENE{
	enum BAR {
		B_LOGIN,
		B_RANKING,
		NUM
	};
}
TitleScene::TitleScene()
{
	Init();
}

void TitleScene::Init() {
	m_backGrd = Image(Vector(SCREEN_X / 2.0f, SCREEN_Y / 2.0f), Vector((float)SCREEN_X, (float)SCREEN_Y));
	m_backGrd.SetAnm(1,1,1);
	m_logo = Image(Vector(SCREEN_X / 2.0f, SCREEN_Y / 2.0f - 100.0f), Vector(640.0f, 200.0f));
	m_logo.SetAnm(1, 1, 1);
	m_selectMngPtr = new SelectManager(false, 2, 30.0f);
	m_selectMngPtr->SetAnm(1, 1, 1);
	m_selectMngPtr->InitCenter(Vector(SCREEN_X / 2.0f, SCREEN_Y / 2.0f + 250.0f), Vector(300.0f, 60.0f));
	m_arrowPos[0] = Vector(m_selectMngPtr->GetFirstPos().x - 180.0f,m_selectMngPtr->GetFirstPos().y);
	m_arrowPos[1] = Vector(m_arrowPos[0].x, m_arrowPos[0].y + 90.0f);
	m_arrow.Set(m_arrowPos[0], Vector(60.0f, 60.0f));
	m_arrow.SetAnm(1,1,1);
	ReadTexture();
}

SCENE TitleScene::Update() {
	if (KeyTrigger(KEY_X)) {
		if (m_selectMngPtr->GetNow() == 0)
			return SCENE::LOGIN;
		if (m_selectMngPtr->GetNow() == 1)
			return SCENE::RANKING;
	}

	m_selectMngPtr->Update();
	UpdateArrow();
	return SCENE::NOT;
}

void TitleScene::Render() {
	m_tex.Set("BackGround");
	m_backGrd.Draw();
	m_tex.Set("TitleLogo");
	m_logo.Draw();
	m_tex.Set("Bar_login");
	m_selectMngPtr->Draw(TITLE_SCENE::B_LOGIN);
	m_tex.Set("Bar_ranking");
	m_selectMngPtr->Draw(TITLE_SCENE::B_RANKING);
	m_tex.Set("Arrow");
	m_arrow.Draw();
}

void TitleScene::Exit() {
	m_selectMngPtr->Exit();
	m_tex.Clear();
}

void TitleScene::ReadTexture() {
	m_tex.Add("assets/title/background.png", "BackGround");
	m_tex.Add("assets/title/logo.png", "TitleLogo");
	m_tex.Add("assets/title/bar_login.png", "Bar_login");
	m_tex.Add("assets/title/bar_ranking.png", "Bar_ranking");
	m_tex.Add("assets/title/UI_arrow.png","Arrow");
}

void TitleScene::UpdateArrow() {
	if (m_selectMngPtr->GetNow() == 0) {
		m_arrow.Move(m_arrowPos[0]);
	}
	else if(m_selectMngPtr->GetNow() == 1){
		m_arrow.Move(m_arrowPos[1]);
	}
}