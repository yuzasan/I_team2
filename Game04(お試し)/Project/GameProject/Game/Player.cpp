#include "Player.h"
#include "Bullet.h"
#include "Map.h"

Player::Player(const CVector2D& pos):Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_pos = pos;
	//���S��ݒ�
	m_img.SetCenter(16, 16);
	//��`��ݒ�	(���A��A�E�A��)
	m_rect = CRect(-16, -16, 16, 16);
	//���a
	m_rad = 16;
}

void Player::Update(){
	//�ړ��O�̈ʒu
	m_pos_old = m_pos;
	const float speed = 4;
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

	if (PUSH(CInput::eMouseL)) {
		Base::Add(new Bullet(eType_Player_Bullet, m_pos, m_ang, 4));
	}

}

void Player::Draw(){
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Player::Collision(Base* b){
	switch (b->m_type){
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			/*
			int t = m->CollisionMap(m_pos);
			if (t != 0)
				m_pos = m_pos_old;
			*/
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0)
				m_pos.y = m_pos_old.y;
		}
		break;
	}
}
