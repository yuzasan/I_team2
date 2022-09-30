#include "Game3.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "../Title/Title.h"

Game3::Game3() :Base(eType_Scene) {
	Base::Add(new Map());
	Base::Add(new Player(CVector2D(32 * 3, 32 * 4)));
	Base::Add(new Enemy(CVector2D(32 * 37, 32 * 10)));


}

Game3::~Game3() {
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game3::Update() {
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//�G�S�Ł@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Enemy) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}
