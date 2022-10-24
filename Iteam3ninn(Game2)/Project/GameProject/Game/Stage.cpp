#include "Stage.h"
#include "Gameclear.h"
#include "Gameover.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Stage::Stage() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 16) {
	Base::Add(new Map(0));
	Base::Add(player[0] = new Player(CVector2D(32 * 8, 32 * 16), m_ang, 0, 0, false));
	Base::Add(player[1] = new Player(CVector2D(32 * 16, 32 * 16), m_ang, 0, 1, false));
	Base::Add(player[2] = new Player(CVector2D(32 * 24, 32 * 16), m_ang, 0, 2, false));
	Base::Add(player[3] = new Player(CVector2D(32 * 32, 32 * 16), m_ang, 0, 3, false));
	Base::Add(new Enemy(CVector2D(208, 176)));//32*6+32*7/2,32*5+32*6/2
	Base::Add(new Enemy2(CVector2D(1072, 176)));//32*33+32*34/2,32*5+32*6/2
	Base::Add(new Enemy2(CVector2D(208, 368)));//32*6+32*7/2,32*15+32*16/2
	Base::Add(new Enemy(CVector2D(1072, 368)));//32*33+32*34/2,32*11+32*12/2
	Base::Add(new Boss(CVector2D(32 * 20, 224)));//32*15+32*16/2,32*13+32*14/2
}

Stage::~Stage() {
	switch (k) {
	case 0:
		//�S�ẴI�u�W�F�N�g��j��
		Base::KillAll();
		Base::Add(new Gameclear());
		break;
	case 1:
		//�S�ẴI�u�W�F�N�g��j��
		Base::KillAll();
		Base::Add(new Gameover());
		break;
	}
}

void Stage::Update() {
	player[turn]->m_state;
	switch (F) {
	case 0:
		player[turn]->m_state = 0;
		F++;
		break;
	case 1:
		if (player[turn]->m_state != Player::eState_Stop)break;
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

	//�{�X���j�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Boss)) {
		SetKill();
	}

	//�v���C���[�S�łŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player)) {
		SetKill();
		k = 1;
	}

	//�G���^�[�L�[�ŃQ�[���V�[���I��
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Stage::Draw() {
	m_title_text.Draw(750, 100, 255, 255, 255, "���z�[���h�ŕ�������");
	m_title_text.Draw(750, 180, 255, 255, 255, "�����Ɣ���");
	m_title_text.Draw(750, 260, 255, 255, 255, "�v���C���[���S�ł����Gameover");
	m_title_text.Draw(750, 340, 255, 255, 255, "�G�����ׂē|���Ǝ��֐i��orGameclear");
	m_title_text.Draw(750, 420, 255, 255, 255, "�G�͎��Ԍo�߂ōU�����Ă���");
	m_title_text.Draw(750, 500, 255, 255, 255, "enter�ŋ����I�ɐi�ނ��Ƃ��ł���");
	m_title_text.Draw(750, 580, 255, 255, 255, "�G�̋߂�(�d�Ȃ��Ă���Ƃ�)�Ƀv���C���[������Ƃ��ꌂ�K�E");
}