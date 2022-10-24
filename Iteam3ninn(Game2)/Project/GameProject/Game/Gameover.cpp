#include "Gameover.h"
#include "../Title/Title.h"
#include "../Game/Game.h"
#include "../Game/Game2.h"
#include "../Game/Game3.h"
#include "../Game/Game4.h"
#include "../Game/Game5.h"

Gameover::Gameover() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64) {
	m_img = COPY_RESOURCE("Clear2", CImage);
}

Gameover::~Gameover() {
	Base::KillAll();
	if (HOLD(CInput::eButton10)) {//エンターキー
		//ゲームシーンへ
		Base::Add(new Title());
	}
}

void Gameover::Update() {
	//エンターキーでゲームシーン終了
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Gameover::Draw() {
	m_img.Draw();
	m_title_text.Draw(156, 100, 255, 0, 0, "GameOver");
	m_title_text.Draw(500, 100, 255, 0, 0, "あなたの負け");
}