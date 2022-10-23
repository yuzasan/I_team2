#include "Enemy.h"
#include "Bullet.h"
#include "Bullet2.h"
#include "Player2.h"
#include "Slash.h"
#include "Map.h"

Enemy::Enemy(const CVector2D& pos) :Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy", CImage);
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
	c = 0;
	m_damage_no = -1;
	m_attack_no = rand();
}

void Enemy::Update() {
	//移動前の位置
	m_pos_old = m_pos;
	//カウントアップ
	c++;
	//プレイヤーを取得
	Base* b = Base::FindObject(eType_Player);
	//プレイヤーが居れば
	if (b) {
		//ターゲットへのベクトル
		CVector2D vec = b->m_pos - m_pos;
		m_ang = atan2(vec.x, vec.y);
		if (c % 240 == 0) {
			Base::Add(new Bullet2(eType_Enemy_Bullet, m_pos, m_ang, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 22.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 45, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 67.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 90, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 112.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 135, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 157.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 180, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 202.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 225, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 247.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 270, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 292.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 315, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 337.5, 4));
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, 360, 4));

			c = 0;
		}
	}
	if (m_hp <= 0) {
		SetKill();
	}
}

void Enemy::Draw() {
	m_img.SetPos(m_pos);
	m_img.SetSize(120,120);
	m_img.Draw();
	m_img2.SetPos(m_pos);
	m_img2.SetSize(hp, 128);
	m_img2.Draw();

}

void Enemy::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 100;
				hp -= 100;
			}
		}
		break;
	}
}
