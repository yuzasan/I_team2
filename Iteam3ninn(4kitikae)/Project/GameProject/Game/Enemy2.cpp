#include "Enemy2.h"
#include "Bullet.h"
#include "Player2.h"
#include "Map.h"

Enemy2::Enemy2(const CVector2D& pos) :Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy2", CImage);
	m_img2 = COPY_RESOURCE("Hp", CImage);
	m_pos = pos;
	//中心を設定
	m_img.SetCenter(60, 60);
	//矩形を設定	(左、上、右、下)
	m_rect = CRect(-60, -60, 60, 60);
	//半径
	m_rad = 16;
	//ヒットポイント
	m_hp = 200;
	m_cnt = 1;
	m_time = 1.0;
	m_gen = -0.05;
	m_img2.SetCenter(100, 0);
	hp = 200;
}

void Enemy2::Update() {
	//移動前の位置
	m_pos_old = m_pos;
	//カウントアップ
	//m_cnt++;
	/*
	//プレイヤーを取得
	Base* b = Base::FindObject(eType_Player);
	//プレイヤーが居れば
	if (b) {
		//ターゲットへのベクトル
		CVector2D vec = b->m_pos - m_pos;
		m_ang = atan2(vec.x, vec.y);
		if (m_cnt >= 120) {
			//Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, m_ang, 4));
			m_cnt = 0;
		}
	}
	*/
	if (m_hp <= 0) {
		SetKill();
	}
}

void Enemy2::Draw() {
	m_img.SetPos(m_pos);
	//m_img.SetAng(m_ang);
	m_img.SetSize(120, 120);
	m_img.Draw();
	m_img2.SetPos(m_pos);
	m_img2.SetSize(hp, 128);
	m_img2.Draw();
}

void Enemy2::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b) && m_cnt == 1) {
			m_cnt = 0;
			//printf("当たった\n");
			m_hp -= 20;
			hp -= 10;
		}
		if (m_time >= 0) {
			m_time += m_gen;
		}
		if (m_time < 0) {
			m_cnt = 1;
		}

		/*
		if (Base::CollisionCircle(this, b)) {
			CVector2D V = m_pos - b->m_pos;
			float l = V.Length();
			float s = m_rad + b->m_rad - l;
			V.Normalize();
			m_pos += V * s;
		}
		*/
		break;
		/*
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			Base* b = Base::FindObject(eType_Player);
			//int t = m->CollisionMap(m_pos);
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos.y), m_rect);
			if (t != 0) {
				int t = m->CollisionMap(m_pos);
				float speed = 10.0f;
				CVector2D v = b->m_pos - m_pos;
				m_pos += v.GetNormalize() * speed;
			}
		}
		break;
		*/
	}
}