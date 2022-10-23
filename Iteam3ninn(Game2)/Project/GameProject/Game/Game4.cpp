#include "Game4.h"
#include "Game5.h"
#include "Gameclear.h"
#include "Gameover.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Game4::Game4() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 22) {
	
	Base::Add(new Map(1));
	Base::Add(player[0] = new Player2(CVector2D(32 * 8, 32 * 16), m_ang, 0, 0, false));
	Base::Add(player[1] = new Player2(CVector2D(32 * 16, 32 * 16), m_ang, 0, 1, false));
	Base::Add(player[2] = new Player2(CVector2D(32 * 24, 32 * 16), m_ang, 0, 2, false));
	Base::Add(player[3] = new Player2(CVector2D(32 * 32, 32 * 16), m_ang, 0, 3, false));
	Base::Add(new Enemy2(CVector2D(32 * 34, 32 * 6)));
	Base::Add(new Enemy2(CVector2D(32 * 34, 32 * 13)));
	Base::Add(new Enemy2(CVector2D(32 * 23, 32 * 10)));
	Base::Add(new Enemy2(CVector2D(32 * 10, 32 * 7)));
	


}

Game4::~Game4() {
	switch (k) {
	case 0:
		//全てのオブジェクトを破棄
		Base::KillAll();
		Base::Add(new Game5());
		break;
	case 1:
		//全てのオブジェクトを破棄
		Base::KillAll();
		Base::Add(new Gameover());
		break;
	}
}

void Game4::Update() {
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

	//敵全滅でゲームシーン終了
	if (!Base::FindObject(eType_Enemy)) {
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

void Game4::Draw(){
	/*
	if (m_cnt>0) {
		if (PUSH(CInput::eMouseL)) {
			m_cnt--;
		}
	}
	m_title_text.Draw(10, 20, 255, 0, 0, "残り残弾:%d",m_cnt);
	*/
}
