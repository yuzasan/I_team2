#include "Arrow.h"

Arrow::Arrow(const CVector2D& pos, float ang) :Base(eType_Arrow) {
	m_img = COPY_RESOURCE("Arrow2", CImage);
	m_pos = pos;
	m_ang = ang;
	m_img.SetCenter(64, 128);
}

void Arrow::Update(){
	CVector2D vec = CInput::GetMousePoint() - m_pos;
	m_ang = atan2(vec.x, vec.y);
	if (!HOLD(CInput::eMouseL)) {
		SetKill();
	}
}

void Arrow::Draw(){
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.SetSize(128, 256);
	m_img.Draw();
}
