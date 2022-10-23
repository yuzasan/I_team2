#pragma once
#include "../Base/Base.h"

class Boss : public Base {
private:
	CImage m_img;
	CImage m_img2;
	CImage m_img3;
	int m_cnt;
	float m_gen;
	int hp;
	int m_attack_no;
	int m_damage_no;
public:
	int c;
	Boss(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};
