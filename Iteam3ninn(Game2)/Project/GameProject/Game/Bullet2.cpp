#include "Bullet2.h"
#include "Player2.h"
#include "Enemy2.h"
#include "Map.h"

Bullet2::Bullet2(int type, const CVector2D& pos, float ang, float speed) :Base(type) {
	if (type == eType_Player_Bullet)
		m_img = COPY_RESOURCE("Bullet", CImage);
	else
		m_img = COPY_RESOURCE("Bullet2", CImage);

	m_pos = pos;
	m_img.SetCenter(16, 16);
	m_rad = 8;
	m_ang = ang;
	m_speed = speed;
	m_cnt = 2;
	m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
}

Bullet2::~Bullet2() {

}

void Bullet2::Update() {
	//�ړ��O�̈ʒu
	m_pos_old = m_pos;
	m_pos += m_vec;

}

void Bullet2::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Bullet2::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Player:
		if (m_type == eType_Enemy_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
		}

		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this, b) && m_cnt == 1) {
			SetKill();
			b->SetKill();
		}
		break;
	case eType_Enemy:
		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
			b->SetKill();
		}
		break;

	case eType_Player_Bullet:
		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
			b->SetKill();
		}
		break;

	case eType_Enemy_Bullet:
		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
			//b->SetKill();
		}
		break;
	}
}