#include "Base.h"
std::list<Base*> Base::m_list;
//�X�N���[���l�̒�`
CVector2D Base::m_scroll(0, 0);

Base::Base(int type) :m_type(type),m_kill(false), m_vec(0,0),m_pos(0,0), m_rad(0) {

}
Base::~Base() {

}
void Base::Update() {
	//���z�֐�
	//�ړ������Ȃǂ�h����ŋL�q
}
void Base::Draw() {
	//���z�֐�
	//�`�揈���Ȃǂ�h����ŋL�q
}
void Base::Collision(Base* b)
{
	//���z�֐�
	//b�Ƃ̏Փ˔����h����ŋL�q
}
void Base::UpdateAll()
{
	//�S�ẴI�u�W�F�N�g�̍X�V
	for (auto& b : m_list) {
		b->Update();
	}
}

void Base::DrawAll()
{
	//�S�ẴI�u�W�F�N�g�̕`�揈��
	for (auto& b : m_list) {
		b->Draw();
	}
}

void Base::CollisionAll()
{
	//�擪
	auto it1 = m_list.begin();
	//����
	auto last = m_list.end();
	//�����܂ŌJ��Ԃ�
	while (it1 != last) {
		//it1�̎��̗v�f
		auto it2 = it1;
		it2++;
		//�����܂ŌJ��Ԃ�
		while (it2 != last) {
			//�Փˌ���
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			//����
			it2++;
		}
		//����
		it1++;
	}
}
void Base::CheckKillAll()
{
	//�擪
	auto it = m_list.begin();
	//����
	auto last = m_list.end();
	//�����܂ŌJ��Ԃ�
	while (it != last) {
		if ((*it)->m_kill) {
			//���̂��폜
			delete (*it);
			//���X�g�����菜��
			it = m_list.erase(it);
		} else {
			//����
			it++;
		}
	}
}



void Base::Add(Base* b)
{
	//Type���ɂ��\�[�g
	auto itr = m_list.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_list.end()) {
		//�ǉ��I�u�W�F�N�g���type�̒l���傫���I�u�W�F�N�g����������
		if ((*itr)->m_type > b->m_type) {
			//�����ɑ}��(�O�ɑ}�������)
			m_list.insert(itr, b);
			return;
		}
		itr++;
	}
	//�I�u�W�F�N�gb�𖖔��ɒǉ�
	m_list.push_back(b);
}
void Base::KillAll()
{
	//�S�č폜
	std::list<Base*> ret;
	for (auto& b : m_list) {
		b->SetKill();
	}
}
bool Base::CollisionCircle(Base* b1, Base* b2)
{
	CVector2D v = b1->m_pos - b2->m_pos;
	float l = v.Length();
	if (l < b1->m_rad + b2->m_rad) {
		return true;
	}
	return false;
}

void Base::DrawRect()
{
	//�f�o�b�O�p�@��`�̕\��
	CRect rect = CRect(
		m_pos.x + m_rect.m_left,
		m_pos.y + m_rect.m_top,
		m_pos.x + m_rect.m_right,
		m_pos.y + m_rect.m_bottom);
	Utility::DrawQuad(
		CVector2D(rect.m_left, rect.m_top) - m_scroll,
		CVector2D(rect.m_width, rect.m_height),
		CVector4D(1, 0, 0, 0.5f));
}
bool Base::CollisionRect(Base* b1, Base* b2)
{
	//b1�̋�`
	CRect rect1 = CRect(
		b1->m_pos.x + b1->m_rect.m_left,
		b1->m_pos.y + b1->m_rect.m_top,
		b1->m_pos.x + b1->m_rect.m_right,
		b1->m_pos.y + b1->m_rect.m_bottom);
	//b2�̋�`
	CRect rect2 = CRect(
		b2->m_pos.x + b2->m_rect.m_left,
		b2->m_pos.y + b2->m_rect.m_top,
		b2->m_pos.x + b2->m_rect.m_right,
		b2->m_pos.y + b2->m_rect.m_bottom);

	//��`���m�̔���
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
		return true;

	return false;
}
Base* Base::FindObject(int type)
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_type == type) {
			return (*it);
		}
		it++;
	}
	return nullptr;
}

std::list<Base*> Base::FindObjects(int type)
{
	std::list<Base*> ret;
	for (auto& b : m_list) {
		if (b->m_type == type)
			ret.push_back(b);
	}
	return ret;
}
CVector2D Base::GetScreenPos(const CVector2D& pos)
{
	return pos - m_scroll;
}