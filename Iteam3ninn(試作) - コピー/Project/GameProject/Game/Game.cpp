#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "../Title/Title.h"

Game::Game() :Base(eType_Scene){
	Base::Add(new Map());
	Base::Add(new Player(CVector2D(32 * 3, 32 * 4)));
	Base::Add(new Enemy(CVector2D(32 * 28, 32 * 4)));
	Base::Add(new Enemy(CVector2D(32 * 28, 32 * 18)));
	Base::Add(new Enemy(CVector2D(32 * 37, 32 * 10)));
	Base::Add(new Enemy(CVector2D(32 * 17, 32 * 7)));
	Base::Add(new Enemy(CVector2D(32 * 17, 32 * 15)));


}

Game::~Game(){
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game::Update(){
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}

	//�G�S�Ł@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Enemy) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}
