#include "Enemy.h"
#include "Bullet.h"
#include "Map.h"

Enemy::Enemy(const CVector2D& pos):Base(eType_Enemy) {
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_pos = pos;
	//���S��ݒ�
	m_img.SetCenter(16, 16);
	//��`��ݒ�	(���A��A�E�A��)
	m_rect = CRect(-10, -10, 10, 10);
	//���a
	m_rad = 16;

}

void Enemy::Update(){
	//�ړ��O�̈ʒu
	m_pos_old = m_pos;
	//�J�E���g�A�b�v
	m_cnt++;
	//�v���C���[���擾
	Base* b = Base::FindObject(eType_Player);
	//�v���C���[�������
	if (b) {
		//�^�[�Q�b�g�ւ̃x�N�g��
		CVector2D vec = b->m_pos - m_pos;
		m_ang = atan2(vec.x, vec.y);
		if (m_cnt >= 120) {
			//Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, m_ang, 4));
			m_cnt = 0;
		}
	}
}

void Enemy::Draw(){
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Enemy::Collision(Base* b){
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionCircle(this, b)) {
			CVector2D V = m_pos - b->m_pos;
			float l = V.Length();
			float s = m_rad + b->m_rad - l;
			V.Normalize();
			m_pos += V * s;
		}
		break;
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
	}
}
