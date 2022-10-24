#include "Player.h"
#include "Arrow.h"
#include "Bullet2.h"
#include "Enemy.h"
#include "Game.h"
#include "Slash.h"
#include "Map.h"

Player::Player(const CVector2D& pos, float ang, float speed, int a, bool flag) :Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_img2 = COPY_RESOURCE("PlayerHP", CImage);
	m_img3 = COPY_RESOURCE("PlayerHPbar", CImage);
	m_pos_old = m_pos = pos;
	//中心を設定
	m_img.SetCenter(16, 16);
	m_img2.SetCenter(550, 0);
	m_img3.SetCenter(550, 0);
	//矩形を設定	(左、上、右、下)
	m_rect = CRect(-16, -16, 16, 16);
	//半径
	m_rad = 16;
	m_ang = ang;
	m_cnt = 1;
	m_gen = -0.01;
	m_speed = speed;
	m_hp = 100;
	//ボールを管理する変数
	drag = 0;
	C = 0;
	m = a;
	m_flag = flag;
	hp = 1100;
	m_state = eState_Stop;
	m_attack_no = rand();
	m_damage_no = -1;
}

void Player::StateIdle() {
	CVector2D mouse;
	m_pos_old = m_pos;
	mouse = CInput::GetMousePoint();
	if (drag == 0) {
		if (C == 1) {
			if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60 && m_cnt == 1) {
				Base::Add(new Arrow(m_pos, m_ang));
				m_cnt -= 1;
				m_speed = 32;
				drag = 1;
				CVector2D vec = CInput::GetMousePoint() - m_pos;
				m_ang = atan2(vec.x, vec.y);
				m_vec = CVector2D(sin(m_ang), cos(m_ang));
				m_attack_no++;
			}
		}
	}
	if (drag == 1) {
		if (m_pos.x < mouse.x + 1200 && m_pos.x > mouse.x - 1200 && m_pos.y < mouse.y + 1200 && m_pos.y > mouse.y - 1200) {
			drag = 0;
		}
	}
	if (C == 0) {
		if (m_speed > 0) {
			m_cnt = 2;
			m_speed += m_gen;
			m_pos -= m_vec * m_speed;
		}
		if (m_speed <= 0) {
			m_state = eState_Stop;
		}
		drag = 0;
	}
}

void Player::StateMove() {

}

void Player::StateStop() {
	m_cnt = 1;
}

void Player::Update() {
	if (HOLD(CInput::eMouseL)) {
		if (m_cnt == 1)
			C = 1;
	}
	else {
		C = 0;
	}

	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//動く状態
	case eState_Move:
		StateMove();
		break;
		//止まる状態
	case eState_Stop:
		StateStop();
		break;
	}
	if (hp <= 0) {
		SetKill();
	}
}

void Player::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetSize(32, 32);
	m_img.Draw();
	m_img3.SetPos(630, 656);
	m_img3.SetSize(1120, 32);
	m_img3.Draw();
	m_img2.SetPos(640, 656);
	m_img2.SetSize(hp, 32);
	m_img2.Draw();
}

void Player::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t == 1) {
				SOUND("kabeSE")->Play();
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
				m_speed -= 2.0;
			}
			else if (t == 2) {
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
				m_speed -= 4.0;
			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t == 1) {
				SOUND("kabeSE")->Play();
				m_pos.y = m_pos_old.y;
				m_vec.y *= -1;
				m_speed -= 2.0;
			}
			else if (t == 2) {
				m_pos.y = m_pos_old.y;
				m_vec.y *= -1;
				m_speed -= 4.0;
			}
		}
		break;
	case eType_Enemy:
		if (Base::CollisionRect(this, b)) {
			Base::Add(new Slash(m_pos, eType_Attack, m_attack_no));
			m_speed -= 3.0;
		}
		break;
	case eType_Boss:
		if (Base::CollisionRect(this, b)) {
			Base::Add(new Slash(m_pos, eType_Attack, m_attack_no));
			m_speed -= 4.0;
		}
		break;
	case eType_Enemy_Bullet:
		if (m_type == eType_Player && Base::CollisionCircle(this, b)) {
			if (hp > 0) {
				hp -= 100;
			}
		}
		break;
	case eType_Player:
		if (hp <= 0) {
			SetKill();
		}
	}
}
