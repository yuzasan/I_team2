#include "Player2.h"
#include "Bullet2.h"
#include "Map.h"

Player2::Player2(const CVector2D& pos, float ang, float speed) :Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_pos = pos;
	//���S��ݒ�
	m_img.SetCenter(16, 16);
	//��`��ݒ�	(���A��A�E�A��)
	m_rect = CRect(-16, -16, 16, 16);
	//���a
	m_rad = 16;
	m_ang = ang;
	m_cnt = 1;
	m_gen = -0.01;
	m_speed = speed;
}

void Player2::Update() {
	//�ړ��O�̈ʒu
	m_pos_old = m_pos;
	if (PUSH(CInput::eMouseR) && m_cnt==1) {
		m_cnt -= 1;
		m_speed = 32;
		//�}�E�X�ւ̃x�N�g��
		CVector2D vec = CInput::GetMousePoint() - m_pos;
		m_ang = atan2(vec.x, vec.y);
		//���˕Ԃ�@�s�^�b�Ǝ~�܂�
		m_vec = CVector2D(sin(m_ang), cos(m_ang));
	}
	if (m_speed > 0) {
		m_speed += m_gen;
		//���˕Ԃ�Ȃ��@���񂾂�x���Ȃ�~�܂�
		//m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
		printf("%f\n", m_speed);
		m_pos += m_vec * m_speed;
	}
	if (m_speed <= 0) {
		m_cnt = 1;
	}
	

	/*
	//���Ɉړ�
	if (HOLD(CInput::eLeft))
		m_pos.x -= speed;
	//�E�Ɉړ�
	if (HOLD(CInput::eRight))
		m_pos.x += speed;
	//��Ɉړ�
	if (HOLD(CInput::eUp))
		m_pos.y -= speed;
	//���Ɉړ�
	if (HOLD(CInput::eDown))
		m_pos.y += speed;
	

	//m_ang += 0.1f;

	//�}�E�X�ւ̃x�N�g��
	CVector2D vec = CInput::GetMousePoint() - m_pos;
	//��]�l���t�Z
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
