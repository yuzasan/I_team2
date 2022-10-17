#include "Game4.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Game4::Game4() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 22) {
	Base* b = Base::FindObject(eType_Player);
	Base::Add(new Map(1));
	for (int i = 1; i <= 4; i++) {
		Base::Add(new Player2(b->m_pos, m_ang, 0, i, false));
	}
	//Base::Add(new Player2(b->m_pos,m_ang,0,0, false));
	Base::Add(new Enemy2(CVector2D(32 * 28, 32 * 4)));
	Base::Add(new Enemy2(CVector2D(32 * 28, 32 * 18)));
	Base::Add(new Enemy2(CVector2D(32 * 37, 32 * 10)));
	Base::Add(new Enemy2(CVector2D(32 * 17, 32 * 7)));
	Base::Add(new Enemy2(CVector2D(32 * 17, 32 * 15)));


}

Game4::~Game4() {
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game4::Update() {
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//�G�S�Ł@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Enemy) && PUSH(CInput::eMouseR)) {
		SetKill();
	}

	//�G���^�[�L�[�ŃQ�[���V�[���I��
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
	m_title_text.Draw(10, 20, 255, 0, 0, "�c��c�e:%d",m_cnt);
	*/
}
