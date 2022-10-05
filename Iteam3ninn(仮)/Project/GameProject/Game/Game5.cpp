#include "Game5.h"
#include "Map.h"
#include "Player2.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "../Title/Title.h"

Game5::Game5() :Base(eType_Scene), m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 32) {
	Base::Add(new Map());
	Base::Add(new Player2(CVector2D(32 * 11, 32 * 16), m_ang, 0));
	Base::Add(new Enemy(CVector2D(176, 368)));
	Base::Add(new Enemy2(CVector2D(1104, 368)));
	Base::Add(new Enemy(CVector2D(1104, 528)));
	Base::Add(new Enemy2(CVector2D(176, 528)));
	Base::Add(new Boss(CVector2D(32 * 20, 224)));//32 * 20, 32 * 7
}

Game5::~Game5() {
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game5::Update() {
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//�G�S�Ł@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Enemy) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//�G���^�[�L�[�ŃQ�[���V�[���I��
	if (PUSH(CInput::eButton10)) {
		SetKill();
	}
}

void Game5::Draw() {
	m_title_text.Draw(750, 100, 255, 255, 255, "WASD �ړ�");
	m_title_text.Draw(750, 180, 255, 255, 255, "�}�E�X�ŕ����]��");
	m_title_text.Draw(750, 260, 255, 255, 255, "���N���b�N�Ŕ���");
	m_title_text.Draw(750, 340, 255, 255, 255, "�G��������");
	m_title_text.Draw(750, 420, 255, 255, 255, "�����̒e�ɓ�����");
	m_title_text.Draw(750, 500, 255, 255, 255, "enter�Ń^�C�g���ɖ߂�");
	m_title_text.Draw(750, 580, 255, 255, 255, "����or�G���S�ł̎�z�L�[�Ŗ߂�");
}