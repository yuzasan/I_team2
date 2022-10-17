#include "Game.h"
#include "Game2.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	Base::Add(new Map(0));
	Base::Add(player[0] = new Player2(CVector2D(32 * 8, 32 * 16), m_ang, 0, 0, false));
	Base::Add(player[1] = new Player2(CVector2D(32 * 16, 32 * 16), m_ang, 0, 1, false));
	Base::Add(player[2] = new Player2(CVector2D(32 * 24, 32 * 16), m_ang, 0, 2, false));
	Base::Add(player[3] = new Player2(CVector2D(32 * 32, 32 * 16), m_ang, 0, 3, false));
	Base::Add(new Enemy(CVector2D(656, 176)));//32*20+32*21/2,32*5+32*6/2
	Base::Add(new Enemy2(CVector2D(272, 240)));//32*8+32*9/2,32*7+32*8/2
	Base::Add(new Enemy2(CVector2D(1040, 240)));//32*32+32*33,32*7+32*8/2
	Base::Add(new Enemy(CVector2D(656, 336)));//32*20+32*21/2,32*10+32*11/2
	


}

Game::~Game(){
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Game2());
}

void Game::Update() {
	//auto list = Base::FindObjects(eType_Player);
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
				turn = (turn + 1) % 4;
				c++;
				printf("turn:%d\n", turn);
				printf("c:%d\n", c);
				F = 0;
			}
		}	
		
		break;
	}
	
	//�G�S�Ł@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Enemy)) {
		SetKill();
	}

	//�G���^�[�L�[�ŃQ�[���V�[���I��
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Game::Draw() {
	/*
	m_title_text.Draw(750, 100, 255, 255, 255, "WASD �ړ�");
	m_title_text.Draw(750, 180, 255, 255, 255, "�}�E�X�ŕ����]��");
	m_title_text.Draw(750, 260, 255, 255, 255, "���N���b�N�Ŕ���");
	m_title_text.Draw(750, 340, 255, 255, 255, "�G��������");
	m_title_text.Draw(750, 420, 255, 255, 255, "�����̒e�ɓ�����");
	m_title_text.Draw(750, 500, 255, 255, 255, "enter�Ń^�C�g���ɖ߂�");
	m_title_text.Draw(750, 580, 255, 255, 255, "����or�G���S�ł̎�z�L�[�Ŗ߂�");
	*/
}
