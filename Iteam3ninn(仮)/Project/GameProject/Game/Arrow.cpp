#include "Arrow.h"

Arrow::Arrow(const CVector2D& pos, float ang) :Base(eType_Arrow) {
	m_img = COPY_RESOURCE("Arrow", CImage);
	m_pos = pos;
	m_ang = ang;
	m_img.SetCenter(16, 32);
}

void Arrow::Update(){

}

void Arrow::Draw(){

}
