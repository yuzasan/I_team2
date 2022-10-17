#pragma once
#include "../Base/Base.h"

class Boss : public Base {
private:
	CImage m_img;
	CImage m_img2;
	int m_cnt;
	float m_gen;
	int hp;
public:
	Boss(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};
