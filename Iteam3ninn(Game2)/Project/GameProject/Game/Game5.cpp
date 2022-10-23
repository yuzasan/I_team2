#include "Game5.h"
#include "Gameclear.h"
#include "Gameover.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Game5::Game5() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {

	Base::Add(new Map(2));
	Base::Add(player[0] = new Player2(CVector2D(32 * 8, 32 * 16), m_ang, 0, 0, false));
	Base::Add(player[1] = new Player2(CVector2D(32 * 16, 32 * 16), m_ang, 0, 1, false));
	Base::Add(player[2] = new Player2(CVector2D(32 * 24, 32 * 16), m_ang, 0, 2, false));
	Base::Add(player[3] = new Player2(CVector2D(32 * 32, 32 * 16), m_ang, 0, 3, false));
	Base::Add(new Enemy(CVector2D(230, 150)));
	Base::Add(new Enemy2(CVector2D(1138, 230)));
	Base::Add(new Enemy(CVector2D(1138, 400)));
	Base::Add(new Enemy2(CVector2D(230, 360)));
	Base::Add(new Boss(CVector2D(32 * 20, 224)));//32 * 20, 32 * 7
}

Game5::~Game5() {
	switch (k) {
	case 0:
		//全てのオブジェクトを破棄
		Base::KillAll();
		Base::Add(new Gameclear());
		break;
	case 1:
		//全てのオブジェクトを破棄
		Base::KillAll();
		Base::Add(new Gameover());
		break;
	}
}

void Game5::Update() {
	player[turn]->m_state;
	switch (F) {
	case 0:
		player[turn]->m_state = 0;
		F++;
		break;
	case 1:
		if (player[turn]->m_state != Player2::eState_Stop)break;
		if (PUSH(CInput::eMouseL)) {
			if (c == 0) {
				turn = 0;
				c++;
				printf("turn:%d\n", turn);
				printf("c:%d\n", c);
				F = 0;
				break;
			}
			else {
				c++;
				turn = (turn + 1) % 4;
				printf("turn:%d\n", turn);
				printf("c:%d\n", c);
				F = 0;
			}
		}

		break;
	}

	//ボス撃破でゲームシーン終了
	if (!Base::FindObject(eType_Boss)) {
		SetKill();
	}

	//プレイヤー全滅でゲームシーン終了
	if (!Base::FindObject(eType_Player)) {
		SetKill();
		k = 1;
	}

	//エンターキーでゲームシーン終了
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Game5::Draw() {
	/*
	m_title_text.Draw(750, 100, 255, 255, 255, "WASD 移動");
	m_title_text.Draw(750, 180, 255, 255, 255, "マウスで方向転換");
	m_title_text.Draw(750, 260, 255, 255, 255, "左クリックで発射");
	m_title_text.Draw(750, 340, 255, 255, 255, "敵を押せる");
	m_title_text.Draw(750, 420, 255, 255, 255, "自分の弾に当たる");
	m_title_text.Draw(750, 500, 255, 255, 255, "enterでタイトルに戻る");
	m_title_text.Draw(750, 580, 255, 255, 255, "自分or敵が全滅の時zキーで戻る");
	*/
}