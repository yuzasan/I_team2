#pragma once
#include "../Base/Base.h"

class Player2 : public Base{
public:
	enum {
		eState_Idle,
		eState_Move,
		eState_Stop,
	};
	//ó‘Ô•Ï”
	int m_state;

	CImage m_img;
	bool m_flag;

	void StateIdle();
	void StateMove();
	void StateStop();

	float m_speed;
	float m_gen;
	int drag;
	int C;
public:
	int m;
	Player2(const CVector2D& pos, float ang, float speed, int a,bool flag);
	void Update();
	void Draw();
	void Collision(Base* b);
};