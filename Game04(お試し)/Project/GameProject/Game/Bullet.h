#pragma once
#include "../Base/Base.h"

class Bullet : public Base {
	CImage m_img;
	float m_speed;
	int m_cnt;
	int m_h;
public:
	Bullet(int type, const CVector2D& pos, float ang, float speed);
	~Bullet();
	void Update();
	void Draw();
	void Collision(Base* b);

};