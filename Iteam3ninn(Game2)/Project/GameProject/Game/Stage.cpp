#include "Stage.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Stage::Stage() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	Base::Add(new Map(1));
	Base::Add(new Player2(CVector2D(32 * 11, 32 * 16), m_ang, 0, 0, false));
	Base::Add(new Enemy(CVector2D(176, 368)));
	Base::Add(new Enemy2(CVector2D(1104, 368)));
	Base::Add(new Enemy(CVector2D(1104, 528)));
	Base::Add(new Enemy2(CVector2D(176, 528)));
	Base::Add(new Boss(CVector2D(32 * 20, 224)));//32 * 20, 32 * 7
}

Stage::~Stage() {
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());
}

void Stage::Update() {
	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//敵全滅　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Enemy) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//エンターキーでゲームシーン終了
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Stage::Draw() {

}