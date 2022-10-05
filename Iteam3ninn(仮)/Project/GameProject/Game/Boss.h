#pragma once
#include "../Base/Base.h"

class Boss : public Base {
private:
	CImage m_img;
	int m_cnt;
	float m_gen;
public:
	Boss(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};
