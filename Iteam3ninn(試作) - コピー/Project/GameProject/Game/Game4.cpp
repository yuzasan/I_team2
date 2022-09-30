#include "Game4.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy2.h"
#include "../Title/Title.h"

Game4::Game4() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 22) {
	Base::Add(new Map());
	Base::Add(new Player2(CVector2D(32 * 3, 32 * 4),m_ang,1));
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
	if (!Base::FindObject(eType_Enemy) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}

void Game4::Draw(){
	if (m_cnt>0) {
		if (PUSH(CInput::eMouseL)) {
			m_cnt--;
		}
	}
	m_title_text.Draw(10, 20, 255, 0, 0, "�c��c�e:%d",m_cnt);
}
