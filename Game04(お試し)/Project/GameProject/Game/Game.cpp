#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Map.h"
#include "../Title/Title.h"

Game::Game() : Base(eType_Scene) {
	
}

Game::~Game() {
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());
}

void Game::Update() {
	if (!Base::FindObject(eType_Enemy)) {
		SetKill();
	}

	//プレイヤー死亡　ボタン1でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}