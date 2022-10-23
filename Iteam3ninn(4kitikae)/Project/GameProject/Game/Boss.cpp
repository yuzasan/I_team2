#include "Boss.h"
#include "Bullet.h"
#include "Player2.h"
#include "Slash.h"
#include "Map.h"

Boss::Boss(const CVector2D& pos) :Base(eType_Boss) {
	m_img = COPY_RESOURCE("Boss", CImage);
	m_img2 = COPY_RESOURCE("Bosshpbar", CImage);//��
	m_img3 = COPY_RESOURCE("Bosshp", CImage);//�g
	m_pos = pos;
	//���S��ݒ�
	m_img.SetCenter(100, 100);
	//��`��ݒ�	(���A��A�E�A��)
	m_rect = CRect(-100, -100, 100, 100);
	//���a
	m_rad = 16;
	//�q�b�g�|�C���g
	m_hp = 500;
	m_cnt = 1;
	m_time = 1.0;
	m_gen = -0.05;
	m_img2.SetCenter(500, 0);
	m_img3.SetCenter(500, 0);
	hp = 1000;
	c = 0;
	m_damage_no = -1;
	m_attack_no = rand();
}

void Boss::Update() {
	//�ړ��O�̈ʒu
	m_pos_old = m_pos;
	//�J�E���g�A�b�v
	c++;
	//�v���C���[���擾
	Base* b = Base::FindObject(eType_Player);
	//�v���C���[�������
	if (b) {
		//�^�[�Q�b�g�ւ̃x�N�g��
		CVector2D vec = b->m_pos - m_pos;
		m_ang = atan2(vec.x, vec.y);
		if (c % 60 == 0) {
			Base::Add(new Bullet(eType_Enemy_Bullet, m_pos, m_ang, 4));
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

void Boss::Draw() {
	m_img.SetPos(m_pos);
	//m_img.SetAng(m_ang);
	m_img.SetSize(200, 200);
	m_img.Draw();
	m_img3.SetPos(630, 0);
	m_img3.SetSize(1020, 64);
	m_img3.Draw();
	m_img2.SetPos(640, 0);
	m_img2.SetSize(hp, 64);
	m_img2.Draw();
}

void Boss::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				m_damage_no = s->GetAttackNo();
				//printf("Enemy_m_damage_no:%d\n", m_damage_no);
				//m_cnt = 0;
				//printf("��������\n");
				m_hp -= 20;
				hp -= 20;
			}
		}
		break;
	}
}