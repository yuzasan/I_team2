#include "Slash.h"

Slash::Slash(const CVector2D& pos, int type, int attack_no) : Base(type) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_pos = pos;
	m_img.SetSize(32, 32);
	m_img.SetCenter(16, 16);
	m_attack_no = attack_no;
}

void Slash::Update() {
	t++;
	if (t % 10 == 0) {
		SetKill();
		t = 0;
	}
}
void Slash::Draw() {
	//m_img.SetPos(m_pos);
	//m_img.Draw();
}