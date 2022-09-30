#include "Player2.h"
#include "Bullet2.h"
#include "Map.h"

Player2::Player2(const CVector2D& pos, float ang, float speed) :Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_pos = pos;
	//中心を設定
	m_img.SetCenter(16, 16);
	//矩形を設定	(左、上、右、下)
	m_rect = CRect(-16, -16, 16, 16);
	//半径
	m_rad = 16;
	m_ang = ang;
	m_cnt = 1;
	m_gen = -0.01;
	m_speed = speed;
}

void Player2::Update() {
	//移動前の位置
	m_pos_old = m_pos;
	if (PUSH(CInput::eMouseR) && m_cnt==1) {
		m_cnt -= 1;
		m_speed = 32;
		//マウスへのベクトル
		CVector2D vec = CInput::GetMousePoint() - m_pos;
		m_ang = atan2(vec.x, vec.y);
		//跳ね返る　ピタッと止まる
		m_vec = CVector2D(sin(m_ang), cos(m_ang));
	}
	if (m_speed > 0) {
		m_speed += m_gen;
		//跳ね返らない　だんだん遅くなり止まる
		//m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
		printf("%f\n", m_speed);
		m_pos += m_vec * m_speed;
	}
	if (m_speed <= 0) {
		m_cnt = 1;
	}
	

	/*
	//左に移動
	if (HOLD(CInput::eLeft))
		m_pos.x -= speed;
	//右に移動
	if (HOLD(CInput::eRight))
		m_pos.x += speed;
	//上に移動
	if (HOLD(CInput::eUp))
		m_pos.y -= speed;
	//下に移動
	if (HOLD(CInput::eDown))
		m_pos.y += speed;
	

	//m_ang += 0.1f;

	//マウスへのベクトル
	CVector2D vec = CInput::GetMousePoint() - m_pos;
	//回転値を逆算
	m_ang = atan2(vec.x, vec.y);


	if (PUSH(CInput::eMouseL)&&m_cnt!=0) {
		Base::Add(new Bullet2(eType_Player_Bullet, m_pos, m_ang, 4));
		m_cnt--;
	}
	if (m_cnt == 0) {
		SetKill();
	}
	*/

}

void Player2::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Player2::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			/*
			int t = m->CollisionMap(m_pos);
			if (t != 0)
				m_pos = m_pos_old;
			*/
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0) {
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
				m_speed -= 0.5;

			}
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y *= -1;
				m_speed -= 0.5;
			}
		}
		break;
	}
}
