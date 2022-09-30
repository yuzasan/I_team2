#pragma once
#include "../Base/Base.h"

class Player2 : public Base {
	CImage m_img;
	float m_speed;
	float m_gen;
public:
	Player2(const CVector2D& pos, float ang, float speed);
	void Update();
	void Draw();
	void Collision(Base* b);
};