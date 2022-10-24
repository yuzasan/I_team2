#include "Gameclear.h"
#include "../Title/Title.h"
#include "../Game/Game.h"
#include "../Game/Game2.h"
#include "../Game/Game3.h"
#include "../Game/Game4.h"
#include "../Game/Game5.h"

Gameclear::Gameclear() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64) {
	m_img = COPY_RESOURCE("Clear", CImage);
}

Gameclear::~Gameclear() {
	Base::KillAll();
	if (HOLD(CInput::eButton10)) {//エンターキー
		//ゲームシーンへ
		Base::Add(new Title());
	}
}

void Gameclear::Update() {
	//エンターキーでゲームシーン終了
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Gameclear::Draw() {
	m_img.Draw();
	m_title_text.Draw(156, 50, 255, 255, 0, "GameClear");
	m_title_text.Draw(500, 50, 255, 255, 0, "Thank you for playing");
}
